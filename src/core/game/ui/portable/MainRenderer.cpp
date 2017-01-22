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
#include "GameSession.h"
#include "Player.h"
#include "SinWaveTextureGpuProgramWrapper.h"
#include "MainGpuProgramWrapperFactory.h"

MainRenderer::MainRenderer() : Renderer(),
m_sinWaveGpuProgramWrapper(MAIN_GPU_PROGRAM_WRAPPER_FACTORY->createSinWaveTextureGpuProgramWrapper()),
m_demo(new TextureWrapper("main"))
{
    ASSETS->init(new MainAssetsMapper());
    
    loadTextureSync(m_demo, "main");
}

MainRenderer::~MainRenderer()
{
	delete m_sinWaveGpuProgramWrapper;

    destroyTexture(m_demo);
}

void MainRenderer::mainDraw(float stateTime)
{
    m_sinWaveGpuProgramWrapper->setOffset(stateTime / 8);
    
    m_rendererHelper->clearFramebufferWithColor(0, 0, 0, 1);
    
    m_rendererHelper->updateMatrix(0, CAM_WIDTH, 0, CAM_HEIGHT);
    
    m_fillNGRectBatcher->beginBatch();
    {
        NGRect r = NGRect(0, 0, CAM_WIDTH, CAM_HEIGHT);
        static Color c = Color(0, 1, 0, 1);
        m_fillNGRectBatcher->renderNGRect(r, c);
    }
    
    m_fillNGRectBatcher->endBatch(*m_colorGpuProgramWrapper);
    
    if (m_demo->gpuTextureWrapper)
    {
        m_spriteBatcher->beginBatch();
        
        {
            static TextureRegion tr = ASSETS->findTextureRegion("Microwave");
            m_spriteBatcher->drawSprite(CAM_WIDTH / 2, CAM_HEIGHT / 2, CAM_WIDTH, CAM_HEIGHT, 0, tr);
        }
        
        m_spriteBatcher->endBatch(*m_demo->gpuTextureWrapper, *m_textureGpuProgramWrapper);
        
        m_spriteBatcher->beginBatch();
        
        {
            TextureRegion tr = ASSETS->findTextureRegion("Logo", stateTime);
            m_spriteBatcher->drawSprite(CAM_WIDTH * 0.39599609375f, CAM_HEIGHT * 0.50453720508167f, CAM_WIDTH * 0.470703125f, CAM_HEIGHT * 0.56261343012704f, 0, tr);
        }
        
        m_spriteBatcher->endBatch(*m_demo->gpuTextureWrapper, *m_textureGpuProgramWrapper);
        
        m_spriteBatcher->beginBatch();
        {
            static TextureRegion tr = ASSETS->findTextureRegion("Glare");
            m_spriteBatcher->drawSprite(CAM_WIDTH / 4 - 0.5f, CAM_HEIGHT * 2 / 3, CAM_WIDTH * 0.140625f, CAM_HEIGHT * 0.27404718693285f, 0, tr);
        }
        m_spriteBatcher->endBatch(*m_demo->gpuTextureWrapper, *m_textureGpuProgramWrapper);
        
        m_spriteBatcher->beginBatch();
        {
            int numPlayers = GAME_SESSION->getNumPlayersConnected();
            switch (numPlayers)
            {
                case 0:
                {
                    static TextureRegion tr = ASSETS->findTextureRegion("NumPad0");
                    m_spriteBatcher->drawSprite(CAM_WIDTH * 0.876953125f, CAM_HEIGHT - 3, CAM_WIDTH * 0.1484375f, CAM_HEIGHT * 0.23411978221416f, 0, tr);
                }
                    break;
                case 1:
                {
                    static TextureRegion tr = ASSETS->findTextureRegion("NumPad1");
                    m_spriteBatcher->drawSprite(CAM_WIDTH * 0.876953125f, CAM_HEIGHT - 3, CAM_WIDTH * 0.1484375f, CAM_HEIGHT * 0.23411978221416f, 0, tr);
                }
                    break;
                case 2:
                {
                    static TextureRegion tr = ASSETS->findTextureRegion("NumPad2");
                    m_spriteBatcher->drawSprite(CAM_WIDTH * 0.876953125f, CAM_HEIGHT - 3, CAM_WIDTH * 0.1484375f, CAM_HEIGHT * 0.23411978221416f, 0, tr);
                }
                    break;
                case 3:
                {
                    static TextureRegion tr = ASSETS->findTextureRegion("NumPad3");
                    m_spriteBatcher->drawSprite(CAM_WIDTH * 0.876953125f, CAM_HEIGHT - 3, CAM_WIDTH * 0.1484375f, CAM_HEIGHT * 0.23411978221416f, 0, tr);
                }
                    break;
                case 4:
                {
                    static TextureRegion tr = ASSETS->findTextureRegion("NumPad4");
                    m_spriteBatcher->drawSprite(CAM_WIDTH * 0.876953125f, CAM_HEIGHT - 3, CAM_WIDTH * 0.1484375f, CAM_HEIGHT * 0.23411978221416f, 0, tr);
                }
                    break;
                default:
                    break;
            }
        }
        
        m_spriteBatcher->endBatch(*m_demo->gpuTextureWrapper, *m_textureGpuProgramWrapper);
        
        TextureRegion popcornTr = ASSETS->findTextureRegion("Popcorn", stateTime);
        TextureRegion poppedTr = ASSETS->findTextureRegion("Popped", stateTime);
        
        m_spriteBatcher->beginBatch();
		for (std::vector<PopcornKernel *>::iterator i = GAME_SESSION->getPopcornKernels().begin(); i != GAME_SESSION->getPopcornKernels().end(); i++)
		{
            Color c = Color((*i)->getHeat(), 0, 0, 1);
            
            renderPhysicalEntityWithColor(*(*i), (*i)->isPopped() ? poppedTr : popcornTr, c);
		}

		for (std::vector<Player *>::iterator i = GAME_SESSION->getPlayers().begin(); i != GAME_SESSION->getPlayers().end(); i++)
		{
            Color c = Color((*i)->getHeat(), 0, 0, 1);
            renderPhysicalEntityWithColor(*(*i), (*i)->isPopped() ? poppedTr : popcornTr, c);
		}
        m_spriteBatcher->endBatch(*m_demo->gpuTextureWrapper, *m_textureGpuProgramWrapper);
    }
}
