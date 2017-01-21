//
//  Direct3DRendererHelper.cpp
//  noctisgames-framework
//
//  Created by Stephen Gowen on 1/15/17.
//  Copyright (c) 2017 Noctis Games. All rights reserved.
//

#include "Direct3DRendererHelper.h"

#include "GpuTextureWrapper.h"
#include "Direct3DManager.h"

Direct3DRendererHelper::Direct3DRendererHelper() : IRendererHelper(), m_iFramebufferIndex(0), m_isBoundToScreen(false)
{
    // Empty
}

Direct3DRendererHelper::~Direct3DRendererHelper()
{
    // Empty
}

void Direct3DRendererHelper::beginFrame()
{
    // Empty
}

void Direct3DRendererHelper::endFrame()
{
    // Empty
}

GpuTextureWrapper Direct3DRendererHelper::getFramebuffer(int index)
{
    return D3DManager->getOffscreenShaderResourceViews().at(index);
}

void Direct3DRendererHelper::updateMatrix(float left, float right, float bottom, float top)
{
    D3DManager->updateMatrix(left, right, bottom, top);
}

void Direct3DRendererHelper::bindToOffscreenFramebuffer(int index)
{
	DX::DeviceResources* deviceResources = Direct3DManager::getDeviceResources();

	deviceResources->GetD3DDeviceContext()->OMSetRenderTargets(1, &D3DManager->getOffscreenRenderTargetViews().at(index), nullptr);
    
	m_iFramebufferIndex = index;
    m_isBoundToScreen = false;
}

void Direct3DRendererHelper::clearFramebufferWithColor(float r, float g, float b, float a)
{
    float color[] = { r, g, b, a };
    
	DX::DeviceResources* deviceResources = Direct3DManager::getDeviceResources();

    ID3D11RenderTargetView * targets[1] = {};
    if (m_isBoundToScreen)
    {
        targets[0] = deviceResources->GetRenderTargetView();
    }
    else
    {
        targets[0] = D3DManager->getOffscreenRenderTargetViews().at(m_iFramebufferIndex);
    }
    
	deviceResources->GetD3DDeviceContext()->ClearRenderTargetView(targets[0], color);
}

void Direct3DRendererHelper::bindToScreenFramebuffer()
{
	DX::DeviceResources* deviceResources = Direct3DManager::getDeviceResources();

    ID3D11RenderTargetView *const targets[1] = { deviceResources->GetRenderTargetView() };
	deviceResources->GetD3DDeviceContext()->OMSetRenderTargets(1, targets, nullptr);
    
    m_isBoundToScreen = true;
}

void Direct3DRendererHelper::destroyTexture(GpuTextureWrapper& textureWrapper)
{
    if (textureWrapper.texture)
    {
        textureWrapper.texture->Release();
    }
}
