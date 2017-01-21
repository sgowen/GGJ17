//
//  Renderer.cpp
//  noctisgames-framework
//
//  Created by Stephen Gowen on 2/22/14.
//  Copyright (c) 2017 Noctis Games. All rights reserved.
//

#include "Renderer.h"

#include "SpriteBatcher.h"
#include "NGRectBatcher.h"
#include "LineBatcher.h"
#include "CircleBatcher.h"
#include "ITextureLoader.h"
#include "IRendererHelper.h"
#include "GpuProgramWrapper.h"
#include "PhysicalEntity.h"
#include "TextureRegion.h"
#include "Color.h"
#include "TextureWrapper.h"
#include "GpuTextureWrapper.h"

#include "SpriteBatcherFactory.h"
#include "NGRectBatcherFactory.h"
#include "LineBatcherFactory.h"
#include "CircleBatcherFactory.h"
#include "TextureLoaderFactory.h"
#include "RendererHelperFactory.h"
#include "GpuProgramWrapperFactory.h"

#include <assert.h>

Renderer::Renderer() :
m_spriteBatcher(SPRITE_BATCHER_FACTORY->createSpriteBatcher()),
m_fillNGRectBatcher(RECTANGLE_BATCHER_FACTORY->createNGRectBatcher(true)),
m_boundsNGRectBatcher(RECTANGLE_BATCHER_FACTORY->createNGRectBatcher(false)),
m_lineBatcher(LINE_BATCHER_FACTORY->createLineBatcher()),
m_circleBatcher(CIRCLE_BATCHER_FACTORY->createCircleBatcher()),
m_textureLoader(TEXTURE_LOADER_FACTORY->createTextureLoader()),
m_rendererHelper(RENDERER_HELPER_FACTORY->createRendererHelper()),
m_textureGpuProgramWrapper(GPU_PROGRAM_WRAPPER_FACTORY->createTextureGpuProgramWrapper()),
m_colorGpuProgramWrapper(GPU_PROGRAM_WRAPPER_FACTORY->createColorGpuProgramWrapper()),
m_framebufferToScreenGpuProgramWrapper(GPU_PROGRAM_WRAPPER_FACTORY->createFramebufferToScreenGpuProgramWrapper())
{
    // Empty
}

Renderer::~Renderer()
{
    delete m_spriteBatcher;
    delete m_fillNGRectBatcher;
    delete m_boundsNGRectBatcher;
    delete m_lineBatcher;
    delete m_circleBatcher;
    
    delete m_textureLoader;
    delete m_rendererHelper;
    
	delete m_textureGpuProgramWrapper;
	delete m_colorGpuProgramWrapper;
    delete m_framebufferToScreenGpuProgramWrapper;
}

void Renderer::beginFrame()
{
	m_rendererHelper->bindToScreenFramebuffer();
    m_rendererHelper->beginFrame();
}

void Renderer::setFramebuffer(int framebufferIndex)
{
    assert(framebufferIndex >= 0);
    
    m_rendererHelper->bindToOffscreenFramebuffer(framebufferIndex);
    m_rendererHelper->clearFramebufferWithColor(0, 0, 0, 1);
}

void Renderer::renderFramebufferToScreen(int framebufferIndex)
{
    assert(framebufferIndex >= 0);
    
    m_rendererHelper->bindToScreenFramebuffer();
    m_rendererHelper->clearFramebufferWithColor(0, 0, 0, 1);
    
    static TextureRegion tr = TextureRegion("framebuffer", 0, 0, 1, 1, 1, 1);
    
    m_spriteBatcher->beginBatch();
    m_spriteBatcher->drawSprite(0, 0, 2, 2, 0, tr);
    m_spriteBatcher->endBatch(m_rendererHelper->getFramebuffer(framebufferIndex), *m_framebufferToScreenGpuProgramWrapper);
}

void Renderer::endFrame()
{
    m_rendererHelper->endFrame();
}

#pragma mark protected

void Renderer::renderPhysicalEntity(PhysicalEntity &pe, TextureRegion& tr)
{
    m_spriteBatcher->drawSprite(pe.getPosition().getX(), pe.getPosition().getY(), pe.getWidth(), pe.getHeight(), pe.getAngle(), tr);
}

void Renderer::renderPhysicalEntityWithColor(PhysicalEntity &pe, TextureRegion& tr, Color c)
{
    m_spriteBatcher->drawSprite(pe.getPosition().getX(), pe.getPosition().getY(), pe.getWidth(), pe.getHeight(), pe.getAngle(), c, tr);
}

void Renderer::loadTextureSync(TextureWrapper* textureWrapper, std::string textureName)
{
    textureWrapper->gpuTextureDataWrapper = m_textureLoader->loadTextureData(textureName.c_str());
    textureWrapper->gpuTextureWrapper = m_textureLoader->loadTexture(textureWrapper->gpuTextureDataWrapper);
    
    delete textureWrapper->gpuTextureDataWrapper;
    textureWrapper->gpuTextureDataWrapper = nullptr;
}

void Renderer::destroyTexture(TextureWrapper* textureWrapper)
{
    if (textureWrapper->gpuTextureWrapper)
    {
        m_rendererHelper->destroyTexture(*textureWrapper->gpuTextureWrapper);
        
        delete textureWrapper->gpuTextureWrapper;
        textureWrapper->gpuTextureWrapper = nullptr;
    }
    
    if (textureWrapper->gpuTextureDataWrapper)
    {
        delete textureWrapper->gpuTextureDataWrapper;
        textureWrapper->gpuTextureDataWrapper = nullptr;
    }
    
    delete textureWrapper;
    textureWrapper = nullptr;
}
