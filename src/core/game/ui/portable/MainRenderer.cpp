//
//  Renderer.cpp
//  ggj17
//
//  Created by Stephen Gowen on 2/22/14.
//  Copyright (c) 2017 Noctis Games. All rights reserved.
//

#include "MainRenderer.h"

#include "TextureWrapper.h"
#include "NGRectBatcher.h"
#include "SpriteBatcher.h"
#include "IRendererHelper.h"
#include "Color.h"
#include "Assets.h"
#include "MainAssetsMapper.h"
#include "NGRect.h"
#include "ScreenConstants.h"
#include "ITextureLoader.h"
#include "Assets.h"
#include "TextureRegion.h"

MainRenderer::MainRenderer() : Renderer(), m_demo(new TextureWrapper("demo"))
{
    ASSETS->init(new MainAssetsMapper());
    
    loadTextureSync(m_demo, "demo");
}

MainRenderer::~MainRenderer()
{
    destroyTexture(m_demo);
}

void MainRenderer::tempDraw(float stateTime)
{
    m_rendererHelper->clearFramebufferWithColor(0, 0, 0, 1);
    
    m_rendererHelper->updateMatrix(0, CAM_WIDTH, 0, CAM_HEIGHT);
    
    m_fillNGRectBatcher->beginBatch();
    {
        NGRect r = NGRect(5 - 0.5f, 5 - 0.5f, 1, 1);
        static Color c = Color(1, 0, 0, 1);
        m_fillNGRectBatcher->renderNGRect(r, c);
    }
    
    {
        NGRect r = NGRect(7 - 0.5f, 7 - 0.5f, 1, 1);
        static Color c = Color(0, 1, 0, 1);
        m_fillNGRectBatcher->renderNGRect(r, c);
    }
    
    {
        NGRect r = NGRect(2 - 0.5f, 2 - 0.5f, 1, 1);
        static Color c = Color(0, 0, 1, 1);
        m_fillNGRectBatcher->renderNGRect(r, c);
    }
    
    {
        NGRect r = NGRect(13 - 0.5f, 13 - 0.5f, 1, 1);
        static Color c = Color(1, 1, 0, 1);
        m_fillNGRectBatcher->renderNGRect(r, c);
    }
    m_fillNGRectBatcher->endBatch(*m_colorGpuProgramWrapper);
    
    if (m_demo->gpuTextureWrapper)
    {
        m_spriteBatcher->beginBatch();
        {
            static TextureRegion tr = ASSETS->findTextureRegion("Sonic_Standing");
            m_spriteBatcher->drawSprite(8, 8, 2, 2, 0, tr);
        }
        
        {
            TextureRegion tr = ASSETS->findTextureRegion("Sonic_Idle", stateTime);
            m_spriteBatcher->drawSprite(4, 4, 2, 2, 0, tr);
        }
        m_spriteBatcher->endBatch(*m_demo->gpuTextureWrapper, *m_textureGpuProgramWrapper);
    }
}
