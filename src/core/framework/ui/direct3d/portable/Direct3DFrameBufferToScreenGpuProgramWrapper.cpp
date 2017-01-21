//
//  Direct3DFramebufferToScreenGpuProgramWrapper.cpp
//  noctisgames-framework
//
//  Created by Stephen Gowen on 9/7/15.
//  Copyright (c) 2017 Noctis Games. All rights reserved.
//

#include "pch.h"

#include "Direct3DFramebufferToScreenGpuProgramWrapper.h"

#include "Direct3DManager.h"
#include "DeviceResources.h"
#include "macros.h"
#include "PlatformHelpers.h"
#include "ReadData.h"

Direct3DFramebufferToScreenGpuProgramWrapper::Direct3DFramebufferToScreenGpuProgramWrapper() : GpuProgramWrapper()
{
	DX::DeviceResources* deviceResources = Direct3DManager::getDeviceResources();

	auto blob = DX::ReadData(L"FramebufferToScreenVertexShader.cso");
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

	blob = DX::ReadData(L"FramebufferToScreenPixelShader.cso");
	DirectX::ThrowIfFailed(
		deviceResources->GetD3DDevice()->CreatePixelShader(
			blob.data(),
			blob.size(),
			nullptr,
			&m_pixelShader
		)
	);
}

Direct3DFramebufferToScreenGpuProgramWrapper::~Direct3DFramebufferToScreenGpuProgramWrapper()
{
    m_vertexShader.Reset();
    m_pixelShader.Reset();
    m_inputLayout.Reset();
}

void Direct3DFramebufferToScreenGpuProgramWrapper::bind()
{
    D3DManager->useScreenBlending();

	DX::DeviceResources* deviceResources = Direct3DManager::getDeviceResources();

	deviceResources->GetD3DDeviceContext()->IASetInputLayout(m_inputLayout.Get());

	// set the shader objects as the active shaders
	deviceResources->GetD3DDeviceContext()->VSSetShader(m_vertexShader.Get(), nullptr, 0);
	deviceResources->GetD3DDeviceContext()->PSSetShader(m_pixelShader.Get(), nullptr, 0);

	deviceResources->GetD3DDeviceContext()->PSSetSamplers(0, 1, D3DManager->getSbSamplerState().GetAddressOf());

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

void Direct3DFramebufferToScreenGpuProgramWrapper::unbind()
{
	// Empty
}
