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
#include "Circle.h"
#include "CircleBatcher.h"

MainRenderer::MainRenderer() : Renderer(),
m_sinWaveGpuProgramWrapper(MAIN_GPU_PROGRAM_WRAPPER_FACTORY->createSinWaveTextureGpuProgramWrapper()),
m_demo(new TextureWrapper("main")),
m_scene(new TextureWrapper("scene"))
{
    ASSETS->init(new MainAssetsMapper());
    
    loadTextureSync(m_demo, "main");
    loadTextureSync(m_scene, "scene");
}

MainRenderer::~MainRenderer()
{
	delete m_sinWaveGpuProgramWrapper;

    destroyTexture(m_demo);
    destroyTexture(m_scene);
}

void MainRenderer::mainDraw(float stateTime)
{
    m_rendererHelper->clearFramebufferWithColor(0, 0, 0, 1);
    
    if (GAME_SESSION->isSessionLive())
    {
        float out = 0;
        if (GAME_SESSION->getStateTime() < 3)
        {
            out = 3 - GAME_SESSION->getStateTime();
        }
        
        m_rendererHelper->updateMatrix(-CAM_WIDTH * out, CAM_WIDTH + CAM_WIDTH * out, -CAM_HEIGHT * out, CAM_HEIGHT + CAM_HEIGHT * out);
        
        m_sinWaveGpuProgramWrapper->setOffset(stateTime / 12);
        
        m_spriteBatcher->beginBatch();
        
        TextureRegion& microwavePlate = ASSETS->findTextureRegion("Microwave_Scene");
        m_spriteBatcher->drawSprite(CAM_WIDTH / 2, CAM_HEIGHT / 2, CAM_WIDTH / 2, CAM_HEIGHT, 0, microwavePlate);
        
        TextureRegion& microwaveCover = ASSETS->findTextureRegion("Microwave_Cover");
        m_spriteBatcher->drawSprite(CAM_WIDTH / 2, CAM_HEIGHT / 2, CAM_WIDTH / 2, CAM_HEIGHT, 0, microwaveCover);
        
        m_spriteBatcher->endBatch(*m_scene->gpuTextureWrapper, *m_textureGpuProgramWrapper);
        
        m_spriteBatcher->beginBatch();
        
        for (std::vector<PopcornKernel *>::iterator i = GAME_SESSION->getPopcornKernels().begin(); i != GAME_SESSION->getPopcornKernels().end(); i++)
        {
            Color c = Color((*i)->getHeat(), 0, 0, 1);

			{
				TextureRegion& popcornTrCom = ASSETS->findTextureRegion("PopcornCom", (*i)->getStateTime());
				TextureRegion& poppedTr = ASSETS->findTextureRegion("Popped", (*i)->getStateTime());

				renderPhysicalEntityWithColor(*(*i), (*i)->isPopped() ? poppedTr : popcornTrCom, c);
			}
        }
        
        TextureRegion& popcornTr1 = ASSETS->findTextureRegion("Popcorn1", stateTime);
        TextureRegion& popcornTr2 = ASSETS->findTextureRegion("Popcorn2", stateTime);
        TextureRegion& popcornTr3 = ASSETS->findTextureRegion("Popcorn3", stateTime);
        TextureRegion& popcornTr4 = ASSETS->findTextureRegion("Popcorn4", stateTime);
        
        for (std::vector<Player *>::iterator i = GAME_SESSION->getPlayers().begin(); i != GAME_SESSION->getPlayers().end(); i++)
        {
            Circle circ = Circle((*i)->getPosition().getX(), (*i)->getMainBounds().getBottom(), (*i)->getWidth() / 2, (*i)->getWidth() / 2);
            Color circColor = Color(0, 0, 0, 1);
            switch ((*i)->getIndex())
            {
                case 0:
                    circColor.red = 0.47843137254902f;
                    circColor.green = 0.44313725490196f;
                    circColor.blue = 0.35294117647059f;
                    break;
                case 1:
                    circColor.red = 0.63529411764706f;
                    circColor.green = 0.1921568627451f;
                    circColor.blue = 0.0078431372549f;
                    break;
                case 2:
                    circColor.red = 0.50588235294118f;
                    circColor.green = 0.50980392156863f;
                    circColor.blue = 0.69803921568627f;
                    break;
                case 3:
                default:
                    circColor.red = 0.9921568627451f;
                    circColor.green = 0.64313725490196f;
                    circColor.blue = 0.0078431372549f;
                    break;
            }
            m_circleBatcher->renderCircle(circ, circColor, *m_colorGpuProgramWrapper);
            
            if ((*i)->isPopped())
            {
                Color c = Color(1, 1, 1, 1);
				TextureRegion& poppedTr = ASSETS->findTextureRegion("Popped", (*i)->getStateTime());
                renderPhysicalEntityWithColor(*(*i), poppedTr, c);
            }
            else
            {
                Color c = Color((*i)->getHeat(), 0, 0, 1);
                switch ((*i)->getIndex())
                {
                    case 0:
                        renderPhysicalEntityWithColor(*(*i), popcornTr1, c);
                        break;
                    case 1:
                        renderPhysicalEntityWithColor(*(*i), popcornTr2, c);
                        break;
                    case 2:
                        renderPhysicalEntityWithColor(*(*i), popcornTr3, c);
                        break;
                    case 3:
                    default:
                        renderPhysicalEntityWithColor(*(*i), popcornTr4, c);
                        break;
                }
            }
        }
        m_spriteBatcher->endBatch(*m_demo->gpuTextureWrapper, *m_textureGpuProgramWrapper);
    }
    else
    {
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
            
            {
                int numPlayers = GAME_SESSION->getNumPlayersConnected();
                float startButtonTime = 0;
                if (numPlayers > 0)
                {
                    startButtonTime = stateTime;
                }
                
                TextureRegion tr = ASSETS->findTextureRegion("Start_Button", startButtonTime);
                m_spriteBatcher->drawSprite(CAM_WIDTH * 0.876953125f, CAM_HEIGHT * 0.12704174228675f, CAM_WIDTH * 0.140625f, CAM_HEIGHT * 0.06170598911071f, 0, tr);
            }
            
            {
                TextureRegion tr = ASSETS->findTextureRegion("Zero_Clock", stateTime);
                m_spriteBatcher->drawSprite(CAM_WIDTH * 0.876953125f, CAM_HEIGHT * 0.87295825771325f, CAM_WIDTH * 0.140625f, CAM_HEIGHT * 0.11978221415608f, 0, tr);
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
                        m_spriteBatcher->drawSprite(CAM_WIDTH * 0.876953125f, CAM_HEIGHT * 0.6016333938294f, CAM_WIDTH * 0.1484375f, CAM_HEIGHT * 0.23411978221416f, 0, tr);
                    }
                        break;
                    case 1:
                    {
                        static TextureRegion tr = ASSETS->findTextureRegion("NumPad1");
                        m_spriteBatcher->drawSprite(CAM_WIDTH * 0.876953125f, CAM_HEIGHT * 0.6016333938294f, CAM_WIDTH * 0.1484375f, CAM_HEIGHT * 0.23411978221416f, 0, tr);
                    }
                        break;
                    case 2:
                    {
                        static TextureRegion tr = ASSETS->findTextureRegion("NumPad2");
                        m_spriteBatcher->drawSprite(CAM_WIDTH * 0.876953125f, CAM_HEIGHT * 0.6016333938294f, CAM_WIDTH * 0.1484375f, CAM_HEIGHT * 0.23411978221416f, 0, tr);
                    }
                        break;
                    case 3:
                    {
                        static TextureRegion tr = ASSETS->findTextureRegion("NumPad3");
                        m_spriteBatcher->drawSprite(CAM_WIDTH * 0.876953125f, CAM_HEIGHT * 0.6016333938294f, CAM_WIDTH * 0.1484375f, CAM_HEIGHT * 0.23411978221416f, 0, tr);
                    }
                        break;
                    case 4:
                    {
                        static TextureRegion tr = ASSETS->findTextureRegion("NumPad4");
                        m_spriteBatcher->drawSprite(CAM_WIDTH * 0.876953125f, CAM_HEIGHT * 0.6016333938294f, CAM_WIDTH * 0.1484375f, CAM_HEIGHT * 0.23411978221416f, 0, tr);
                    }
                        break;
                    default:
                        break;
                }
            }
            
            m_spriteBatcher->endBatch(*m_demo->gpuTextureWrapper, *m_textureGpuProgramWrapper);
        }
    }
}
