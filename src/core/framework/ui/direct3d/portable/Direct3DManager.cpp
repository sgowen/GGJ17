//
//  Direct3DManager.cpp
//  noctisgames-framework
//
//  Created by Stephen Gowen on 11/17/14.
//  Copyright (c) 2017 Noctis Games. All rights reserved.
//

#include "pch.h"

#include "Direct3DManager.h"

#include "Direct3DTextureGpuProgramWrapper.h"
#include "Direct3DGeometryGpuProgramWrapper.h"
#include "Direct3DFramebufferToScreenGpuProgramWrapper.h"
#include "GpuTextureWrapper.h"
#include "PlatformHelpers.h"

extern "C"
{
#include <assert.h>
}

using namespace DirectX;

Direct3DManager* Direct3DManager::s_pInstance = nullptr;
DX::DeviceResources* Direct3DManager::s_pDeviceResources = nullptr;

void Direct3DManager::setDeviceResources(DX::DeviceResources* deviceResources)
{
	assert(!s_pDeviceResources);

	s_pDeviceResources = deviceResources;
}

DX::DeviceResources* Direct3DManager::getDeviceResources()
{
	assert(s_pDeviceResources);

	return s_pDeviceResources;
}

void Direct3DManager::create()
{
    assert(!s_pInstance);
    
    s_pInstance = new Direct3DManager();
}

void Direct3DManager::destroy()
{
    assert(s_pInstance);
    
    delete s_pInstance;
    s_pInstance = nullptr;
}

Direct3DManager * Direct3DManager::getInstance()
{
    return s_pInstance;
}

void Direct3DManager::createDeviceDependentResources(int maxBatchSize)
{
	assert(m_offscreenRenderTargets.size() == 0);
	assert(m_offscreenRenderTargetViews.size() == 0);
	assert(m_offscreenShaderResourceViews.size() == 0);
    
    createBlendStates();
	createSamplerStates();
	createVertexBufferForSpriteBatcher(maxBatchSize);
	createVertexBufferForGeometryBatchers(maxBatchSize);
	createIndexBuffer(maxBatchSize);
	createConstantBuffer();
}

void Direct3DManager::createWindowSizeDependentResources(int screenWidth, int screenHeight, int numFramebuffers)
{
    m_iScreenWidth = screenWidth;
    m_iScreenHeight = screenHeight;
    m_iNumFramebuffers = numFramebuffers;

	releaseFramebuffers();
    createFramebufferObjects();
}

void Direct3DManager::releaseDeviceDependentResources()
{
    releaseFramebuffers();

	m_blendState.Reset();
	m_screenBlendState.Reset();
	m_matrixConstantbuffer.Reset();
	m_indexbuffer.Reset();
	m_sbSamplerState.Reset();
	m_sbVertexBuffer.Reset();
	m_textureVertices.clear();
	m_gbVertexBuffer.Reset();
	m_colorVertices.clear();
}

void Direct3DManager::updateMatrix(float left, float right, float bottom, float top)
{
	using namespace DirectX;

	XMVECTOR eye = XMVectorSet(0, 0, 1, 0);
	XMVECTOR center = XMVectorSet(0, 0, 0, 0);
	XMVECTOR up = XMVectorSet(0, 1, 0, 0);

	XMMATRIX matProjection = XMMatrixOrthographicOffCenterRH(left, right, bottom, top, -1.0, 1.0);
	XMMATRIX matView = XMMatrixLookAtRH(eye, center, up);

	XMMATRIX matFinal;
#if !defined(WINAPI_FAMILY) || (WINAPI_FAMILY == WINAPI_FAMILY_DESKTOP_APP)
	matFinal = matView * matProjection;
#else
	XMFLOAT4X4 orientation = s_pDeviceResources->GetOrientationTransform3D();

	XMMATRIX orientationMatrix = XMLoadFloat4x4(&orientation);

	matFinal = matView * matProjection * orientationMatrix;
#endif
	XMStoreFloat4x4(&m_matFinal, matFinal);
}

void Direct3DManager::addVertexCoordinate(float x, float y, float z, float r, float g, float b, float a, float u, float v)
{
	TEXTURE_VERTEX tv = { x, y, z, r, g, b, a, u, v };
	D3DManager->getTextureVertices().push_back(tv);
}

void Direct3DManager::addVertexCoordinate(float x, float y, float z, float r, float g, float b, float a)
{
	COLOR_VERTEX cv = { x, y, z, r, g, b, a };
	D3DManager->getColorVertices().push_back(cv);
}

void Direct3DManager::useNormalBlending()
{
    s_pDeviceResources->GetD3DDeviceContext()->OMSetBlendState(D3DManager->m_blendState.Get(), 0, 0xffffffff);
}

void Direct3DManager::useScreenBlending()
{
    s_pDeviceResources->GetD3DDeviceContext()->OMSetBlendState(D3DManager->m_screenBlendState.Get(), 0, 0xffffffff);
}

std::vector<ID3D11Texture2D*>& Direct3DManager::getOffscreenRenderTargets()
{
	return m_offscreenRenderTargets;
}

std::vector<ID3D11RenderTargetView*>& Direct3DManager::getOffscreenRenderTargetViews()
{
	return m_offscreenRenderTargetViews;
}

std::vector<ID3D11ShaderResourceView*>& Direct3DManager::getOffscreenShaderResourceViews()
{
	return m_offscreenShaderResourceViews;
}

Microsoft::WRL::ComPtr<ID3D11BlendState>& Direct3DManager::getBlendState()
{
	return m_blendState;
}

Microsoft::WRL::ComPtr<ID3D11BlendState>& Direct3DManager::getScreenBlendState()
{
	return m_screenBlendState;
}

Microsoft::WRL::ComPtr<ID3D11Buffer>& Direct3DManager::getMatrixConstantbuffer()
{
	return m_matrixConstantbuffer;
}

Microsoft::WRL::ComPtr<ID3D11Buffer>& Direct3DManager::getIndexbuffer()
{
	return m_indexbuffer;
}

Microsoft::WRL::ComPtr<ID3D11SamplerState>& Direct3DManager::getSbSamplerState()
{
	return m_sbSamplerState;
}

Microsoft::WRL::ComPtr<ID3D11SamplerState>& Direct3DManager::getSbWrapSamplerState()
{
	return m_sbWrapSamplerState;
}

Microsoft::WRL::ComPtr<ID3D11Buffer>& Direct3DManager::getSbVertexBuffer()
{
	return m_sbVertexBuffer;
}

std::vector<TEXTURE_VERTEX>& Direct3DManager::getTextureVertices()
{
	return m_textureVertices;
}

Microsoft::WRL::ComPtr<ID3D11Buffer>& Direct3DManager::getGbVertexBuffer()
{
	return m_gbVertexBuffer;
}

std::vector<COLOR_VERTEX>& Direct3DManager::getColorVertices()
{
	return m_colorVertices;
}

DirectX::XMFLOAT4X4& Direct3DManager::getMatFinal()
{
	return m_matFinal;
}

// private

void Direct3DManager::createBlendStates()
{
	{
		D3D11_BLEND_DESC bd;
		bd.RenderTarget[0].BlendEnable = TRUE;
		bd.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
		bd.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
		bd.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
		bd.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
		bd.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
		bd.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
		bd.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
		bd.IndependentBlendEnable = FALSE;
		bd.AlphaToCoverageEnable = FALSE;

		s_pDeviceResources->GetD3DDevice()->CreateBlendState(&bd, &m_blendState);
	}

	{
		D3D11_BLEND_DESC bd;
		bd.RenderTarget[0].BlendEnable = TRUE;
		bd.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
		bd.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;
		bd.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
		bd.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
		bd.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
		bd.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
		bd.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
		bd.IndependentBlendEnable = FALSE;
		bd.AlphaToCoverageEnable = FALSE;

		s_pDeviceResources->GetD3DDevice()->CreateBlendState(&bd, &m_screenBlendState);
	}
}

void Direct3DManager::createSamplerStates()
{
	{
		D3D11_SAMPLER_DESC sd;
		sd.Filter = D3D11_FILTER_ANISOTROPIC;
		sd.MaxAnisotropy = 16;
		sd.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
		sd.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
		sd.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
		sd.BorderColor[0] = 0.0f;
		sd.BorderColor[1] = 0.0f;
		sd.BorderColor[2] = 0.0f;
		sd.BorderColor[3] = 0.0f;
		sd.MinLOD = 0.0f;
		sd.MaxLOD = FLT_MAX;
		sd.MipLODBias = 0.0f;
		sd.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR; // linear filtering
		sd.MinLOD = 5.0f; // mip level 5 will appear blurred

		s_pDeviceResources->GetD3DDevice()->CreateSamplerState(&sd, m_sbSamplerState.GetAddressOf());
	}

	{
		D3D11_SAMPLER_DESC sd;
		sd.Filter = D3D11_FILTER_ANISOTROPIC;
		sd.MaxAnisotropy = 16;
		sd.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
		sd.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
		sd.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
		sd.BorderColor[0] = 0.0f;
		sd.BorderColor[1] = 0.0f;
		sd.BorderColor[2] = 0.0f;
		sd.BorderColor[3] = 0.0f;
		sd.MinLOD = 0.0f;
		sd.MaxLOD = FLT_MAX;
		sd.MipLODBias = 0.0f;
		sd.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR; // linear filtering
		sd.MinLOD = 5.0f; // mip level 5 will appear blurred

		s_pDeviceResources->GetD3DDevice()->CreateSamplerState(&sd, m_sbWrapSamplerState.GetAddressOf());
	}
}

void Direct3DManager::createVertexBufferForSpriteBatcher(int maxBatchSize)
{
	m_textureVertices.reserve(maxBatchSize * VERTICES_PER_RECTANGLE);
	TEXTURE_VERTEX tv = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	for (int i = 0; i < maxBatchSize * VERTICES_PER_RECTANGLE; i++)
	{
		m_textureVertices.push_back(tv);
	}

	D3D11_BUFFER_DESC vertexBufferDesc = { 0 };
	vertexBufferDesc.ByteWidth = sizeof(TEXTURE_VERTEX) * m_textureVertices.size();
	vertexBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	vertexBufferDesc.MiscFlags = 0;
	vertexBufferDesc.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA vertexBufferData;
	vertexBufferData.pSysMem = &m_textureVertices[0];
	vertexBufferData.SysMemPitch = 0;
	vertexBufferData.SysMemSlicePitch = 0;

	DirectX::ThrowIfFailed(s_pDeviceResources->GetD3DDevice()->CreateBuffer(&vertexBufferDesc, &vertexBufferData, &m_sbVertexBuffer));
}

void Direct3DManager::createVertexBufferForGeometryBatchers(int maxBatchSize)
{
	m_colorVertices.reserve(maxBatchSize * VERTICES_PER_RECTANGLE);
	COLOR_VERTEX cv = { 0, 0, 0, 0, 0, 0, 0 };
	for (int i = 0; i < maxBatchSize * VERTICES_PER_RECTANGLE; i++)
	{
		m_colorVertices.push_back(cv);
	}

	D3D11_BUFFER_DESC vertexBufferDesc = { 0 };
	vertexBufferDesc.ByteWidth = sizeof(COLOR_VERTEX) * m_colorVertices.size();
	vertexBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	vertexBufferDesc.MiscFlags = 0;
	vertexBufferDesc.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA vertexBufferData;
	vertexBufferData.pSysMem = &m_colorVertices[0];
	vertexBufferData.SysMemPitch = 0;
	vertexBufferData.SysMemSlicePitch = 0;

	DirectX::ThrowIfFailed(s_pDeviceResources->GetD3DDevice()->CreateBuffer(&vertexBufferDesc, &vertexBufferData, &m_gbVertexBuffer));
}

void Direct3DManager::createIndexBuffer(int maxBatchSize)
{
	D3D11_BUFFER_DESC indexBufferDesc = { 0 };

	indexBufferDesc.ByteWidth = sizeof(short) * maxBatchSize * INDICES_PER_RECTANGLE;
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;

	auto indexValues = createIndexValues(maxBatchSize);

	D3D11_SUBRESOURCE_DATA indexDataDesc = { 0 };

	indexDataDesc.pSysMem = &indexValues.front();

	s_pDeviceResources->GetD3DDevice()->CreateBuffer(&indexBufferDesc, &indexDataDesc, &m_indexbuffer);

	s_pDeviceResources->GetD3DDeviceContext()->IASetIndexBuffer(m_indexbuffer.Get(), DXGI_FORMAT_R16_UINT, 0);
}

void Direct3DManager::createConstantBuffer()
{
	D3D11_BUFFER_DESC bd = { 0 };

	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = 64;
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

	DirectX::ThrowIfFailed(s_pDeviceResources->GetD3DDevice()->CreateBuffer(&bd, nullptr, &m_matrixConstantbuffer));
}

std::vector<short> Direct3DManager::createIndexValues(int maxBatchSize)
{
	std::vector<short> indices;

	indices.reserve(maxBatchSize * INDICES_PER_RECTANGLE);

	short j = 0;
	for (int i = 0; i < maxBatchSize * INDICES_PER_RECTANGLE; i += INDICES_PER_RECTANGLE, j += VERTICES_PER_RECTANGLE)
	{
		indices.push_back(j);
		indices.push_back(j + 1);
		indices.push_back(j + 2);
		indices.push_back(j + 2);
		indices.push_back(j + 3);
		indices.push_back(j + 0);
	}

	return indices;
}

void Direct3DManager::createFramebufferObjects()
{
    for (int i = 0; i < m_iNumFramebuffers; i++)
    {
        createFramebufferObject();
    }
}

void Direct3DManager::createFramebufferObject()
{
    ID3D11Texture2D* m_offscreenRenderTarget;
    ID3D11RenderTargetView* m_offscreenRenderTargetView;
    ID3D11ShaderResourceView* m_offscreenShaderResourceView;
    
    D3D11_TEXTURE2D_DESC textureDesc;
    D3D11_RENDER_TARGET_VIEW_DESC renderTargetViewDesc;
    D3D11_SHADER_RESOURCE_VIEW_DESC shaderResourceViewDesc;
    
    // Initialize the render target texture description.
    ZeroMemory(&textureDesc, sizeof(textureDesc));
    
    // Setup the render target texture description.
    textureDesc.Width = m_iScreenWidth;
    textureDesc.Height = m_iScreenHeight;
    textureDesc.MipLevels = 1;
    textureDesc.ArraySize = 1;
    textureDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
    textureDesc.SampleDesc.Count = 1;
    textureDesc.Usage = D3D11_USAGE_DEFAULT;
    textureDesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
    textureDesc.CPUAccessFlags = 0;
    textureDesc.MiscFlags = 0;
    
    // Create the render target texture.
    DirectX::ThrowIfFailed(s_pDeviceResources->GetD3DDevice()->CreateTexture2D(&textureDesc, NULL, &m_offscreenRenderTarget));
    
    // Setup the description of the render target view.
    renderTargetViewDesc.Format = textureDesc.Format;
    renderTargetViewDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
    renderTargetViewDesc.Texture2D.MipSlice = 0;
    
    // Create the render target view.
    DirectX::ThrowIfFailed(s_pDeviceResources->GetD3DDevice()->CreateRenderTargetView(m_offscreenRenderTarget, &renderTargetViewDesc, &m_offscreenRenderTargetView));
    
    // Setup the description of the shader resource view.
    shaderResourceViewDesc.Format = textureDesc.Format;
    shaderResourceViewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
    shaderResourceViewDesc.Texture2D.MostDetailedMip = 0;
    shaderResourceViewDesc.Texture2D.MipLevels = 1;
    
    // Create the shader resource view.
    DirectX::ThrowIfFailed(s_pDeviceResources->GetD3DDevice()->CreateShaderResourceView(m_offscreenRenderTarget, &shaderResourceViewDesc, &m_offscreenShaderResourceView));
    
    m_offscreenRenderTargets.push_back(m_offscreenRenderTarget);
    m_offscreenRenderTargetViews.push_back(m_offscreenRenderTargetView);
    m_offscreenShaderResourceViews.push_back(m_offscreenShaderResourceView);
}

void Direct3DManager::releaseFramebuffers()
{
    for (std::vector<ID3D11Texture2D*>::iterator i = m_offscreenRenderTargets.begin(); i != m_offscreenRenderTargets.end(); )
    {
        (*i)->Release();
    }
    
    for (std::vector<ID3D11RenderTargetView*>::iterator i = m_offscreenRenderTargetViews.begin(); i != m_offscreenRenderTargetViews.end(); )
    {
        (*i)->Release();
    }
    
    for (std::vector<ID3D11ShaderResourceView*>::iterator i = m_offscreenShaderResourceViews.begin(); i != m_offscreenShaderResourceViews.end(); )
    {
        (*i)->Release();
    }
    
    m_offscreenRenderTargets.clear();
    m_offscreenRenderTargetViews.clear();
    m_offscreenShaderResourceViews.clear();
}

Direct3DManager::Direct3DManager() :
	m_iScreenWidth(-1),
	m_iScreenHeight(-1),
	m_iNumFramebuffers(-1)
{
	// Hide Constructor for Singleton
}

Direct3DManager::~Direct3DManager()
{
	releaseDeviceDependentResources();
}
