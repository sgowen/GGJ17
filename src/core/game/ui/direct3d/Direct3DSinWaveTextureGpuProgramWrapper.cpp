//
//  Direct3DSinWaveTextureGpuProgramWrapper.cpp
//  ggj17
//
//  Created by Stephen Gowen on 1/21/17.
//  Copyright © 2017 Noctis Games. All rights reserved.
//

#include "pch.h"

#include "Direct3DSinWaveTextureGpuProgramWrapper.h"

#include "Direct3DManager.h"
#include "DeviceResources.h"
#include "PlatformHelpers.h"
#include "ReadData.h"

Direct3DSinWaveTextureGpuProgramWrapper::Direct3DSinWaveTextureGpuProgramWrapper()
{
	DX::DeviceResources* deviceResources = Direct3DManager::getDeviceResources();

	createConstantBuffer();

	auto blob = DX::ReadData(L"TextureVertexShader.cso");
	DirectX::ThrowIfFailed(
		deviceResources->GetD3DDevice()->CreateVertexShader(
			blob.data(),
			blob.size(),
			nullptr,
			&m_vertexShader
		)
	);

	static const D3D11_INPUT_ELEMENT_DESC vertexDesc[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 28, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};

	DirectX::ThrowIfFailed(
		deviceResources->GetD3DDevice()->CreateInputLayout(
			vertexDesc,
			ARRAYSIZE(vertexDesc),
			blob.data(),
			blob.size(),
			&m_inputLayout
		)
	);

	blob = DX::ReadData(L"SinWaveTexturePixelShader.cso");
	DirectX::ThrowIfFailed(
		deviceResources->GetD3DDevice()->CreatePixelShader(
			blob.data(),
			blob.size(),
			nullptr,
			&m_pixelShader
		)
	);
}

void Direct3DSinWaveTextureGpuProgramWrapper::bind()
{
	DX::DeviceResources* deviceResources = Direct3DManager::getDeviceResources();

	deviceResources->GetD3DDeviceContext()->OMSetBlendState(D3DManager->getBlendState().Get(), 0, 0xffffffff);

	deviceResources->GetD3DDeviceContext()->IASetInputLayout(m_inputLayout.Get());

	// set the shader objects as the active shaders
	deviceResources->GetD3DDeviceContext()->VSSetShader(m_vertexShader.Get(), nullptr, 0);
	deviceResources->GetD3DDeviceContext()->PSSetShader(m_pixelShader.Get(), nullptr, 0);

	deviceResources->GetD3DDeviceContext()->VSSetConstantBuffers(0, 1, D3DManager->getMatrixConstantbuffer().GetAddressOf());
	deviceResources->GetD3DDeviceContext()->PSSetConstantBuffers(0, 1, m_offsetConstantBuffer.GetAddressOf());

	// send the final matrix to video memory
	deviceResources->GetD3DDeviceContext()->UpdateSubresource(D3DManager->getMatrixConstantbuffer().Get(), 0, 0, &D3DManager->getMatFinal(), 0, 0);

	// send the new offset to video memory
	deviceResources->GetD3DDeviceContext()->UpdateSubresource(m_offsetConstantBuffer.Get(), 0, 0, &m_fOffset, 0, 0);

	D3D11_MAPPED_SUBRESOURCE mappedResource;
	ZeroMemory(&mappedResource, sizeof(D3D11_MAPPED_SUBRESOURCE));

	//	Disable GPU access to the vertex buffer data.
	deviceResources->GetD3DDeviceContext()->Map(D3DManager->getSbVertexBuffer().Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);

	int numTextureVertices = D3DManager->getTextureVertices().size();
	//	Update the vertex buffer here.
	memcpy(mappedResource.pData, &D3DManager->getTextureVertices()[0], sizeof(TEXTURE_VERTEX) * numTextureVertices);

	//	Reenable GPU access to the vertex buffer data.
	deviceResources->GetD3DDeviceContext()->Unmap(D3DManager->getSbVertexBuffer().Get(), 0);

	// Set the vertex and index buffer
	UINT stride = sizeof(TEXTURE_VERTEX);
	UINT offset = 0;
	deviceResources->GetD3DDeviceContext()->IASetVertexBuffers(0, 1, D3DManager->getSbVertexBuffer().GetAddressOf(), &stride, &offset);
}

void Direct3DSinWaveTextureGpuProgramWrapper::unbind()
{
	// Empty
}

void Direct3DSinWaveTextureGpuProgramWrapper::cleanUp()
{
	m_offsetConstantBuffer.Reset();
	m_vertexShader.Reset();
	m_inputLayout.Reset();
	m_pixelShader.Reset();
}

void Direct3DSinWaveTextureGpuProgramWrapper::createConstantBuffer()
{
	D3D11_BUFFER_DESC bd = { 0 };

	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = 16;
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

	DX::DeviceResources* deviceResources = Direct3DManager::getDeviceResources();

	deviceResources->GetD3DDevice()->CreateBuffer(&bd, nullptr, &m_offsetConstantBuffer);
}
