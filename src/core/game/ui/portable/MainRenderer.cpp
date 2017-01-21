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

void MainRenderer::tempDraw(float stateTime, float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4)
{
    m_rendererHelper->clearFramebufferWithColor(0, 0, 0, 1);
    
    m_rendererHelper->updateMatrix(0, CAM_WIDTH, 0, CAM_HEIGHT);
    
    m_fillNGRectBatcher->beginBatch();
    {
        NGRect r = NGRect(0, 0, CAM_WIDTH / 2, CAM_HEIGHT * 6);
        static Color c = Color(0, 1, 0, 1);
        m_fillNGRectBatcher->renderNGRect(r, c);
    }
    
    m_fillNGRectBatcher->endBatch(*m_colorGpuProgramWrapper);
    
    if (m_demo->gpuTextureWrapper)
    {
		TextureRegion tr = ASSETS->findTextureRegion("Sonic_Idle", stateTime);
		
		m_spriteBatcher->beginBatch(); 
		m_spriteBatcher->drawSprite(x1, y1, 2, 2, 0, tr);
		m_spriteBatcher->drawSprite(x2, y2, 2, 2, 0, tr);
		m_spriteBatcher->drawSprite(x3, y3, 2, 2, 0, tr);
		m_spriteBatcher->drawSprite(x4, y4, 2, 2, 0, tr);
        m_spriteBatcher->endBatch(*m_demo->gpuTextureWrapper, *m_textureGpuProgramWrapper);
    }
}
