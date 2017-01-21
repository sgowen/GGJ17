//
//  MainScreen.cpp
//  ggj17
//
//  Created by Stephen Gowen on 2/22/14.
//  Copyright (c) 2017 Noctis Games. All rights reserved.
//

#include "MainScreen.h"

#include "TouchType.h"
#include "TouchEvent.h"
#include "MainRenderer.h"
#include "InputManager.h"
#include "TouchConverter.h"
#include "IDeviceHelper.h"
#include "DeviceHelperFactory.h"
#include "ScreenConstants.h"
#include "SoundManager.h"
#include "MusicConstants.h"
#include "SoundConstants.h"
#include "Vector2D.h"
#include "MathUtil.h"
#include "GameSession.h"
#include "Player.h"

MainScreen::MainScreen() : IScreen(),
m_deviceHelper(DEVICE_HELPER_FACTORY->createDeviceHelper()),
m_renderer(new MainRenderer()),
m_fStateTime(0),
m_iRequestedUiAction(0)
{
	//SOUND_MANAGER->addMusicIdToPlayQueue(MUSIC_LOAD_DEMO);
    //SOUND_MANAGER->addMusicIdToPlayQueue(MUSIC_PLAY_LOOP);
}

MainScreen::~MainScreen()
{
    delete m_renderer;
	delete m_deviceHelper;
}

void MainScreen::createDeviceDependentResources()
{
    m_deviceHelper->createDeviceDependentResources(MAX_BATCH_SIZE);
    
    delete m_renderer;
    m_renderer = new MainRenderer();
}

void MainScreen::createWindowSizeDependentResources(int screenWidth, int screenHeight, int touchScreenWidth, int touchScreenHeight)
{
    TOUCH_CONVERTER->setTouchScreenSize(touchScreenWidth, touchScreenHeight);
    TOUCH_CONVERTER->setCamSize(CAM_WIDTH, CAM_HEIGHT);
    
    m_deviceHelper->createWindowSizeDependentResources(screenWidth, screenHeight, NUM_FRAMEBUFFERS);
}

void MainScreen::releaseDeviceDependentResources()
{
    m_deviceHelper->releaseDeviceDependentResources();
}

void MainScreen::onResume()
{
    m_iRequestedUiAction = 0;
}

void MainScreen::onPause()
{
    m_iRequestedUiAction = 0;
}

void MainScreen::update(float deltaTime)
{
    m_fStateTime += deltaTime;
    
    GAME_SESSION->update(deltaTime);
    
    INPUT_MANAGER->processGamePadEvents();
    
    std::vector<GamePadEvent*> gpEvents = INPUT_MANAGER->getGamePadEvents();

    for (std::vector<GamePadEvent*>::iterator i = gpEvents.begin(); i != gpEvents.end(); i++)
    {
		int playerIndex = (*i)->getPlayerIndex();
		float x = (*i)->getX();
		float y = (*i)->getY();
		switch ((*i)->getType())
        {
            case STICK_LEFT:
            {
				GAME_SESSION->getPlayers().at(playerIndex)->getAcceleration().set(x * 5, y * 5);
                continue;
            }
            case TRIGGER:
            {
				if (x > 0)
				{
					int storeHeatSoundId = playerIndex * 10000;
					storeHeatSoundId += SOUND_STORE_HEAT * 1000;
					storeHeatSoundId += x * 100;
					SOUND_MANAGER->addSoundIdToPlayQueue(storeHeatSoundId);
				}

				if (y > 0)
				{
					int releaseHeatSoundId = playerIndex * 10000;
					releaseHeatSoundId += SOUND_RELEASE_HEAT * 1000;
					releaseHeatSoundId += y * 100;
					SOUND_MANAGER->addSoundIdToPlayQueue(releaseHeatSoundId);
				}
				continue;
            }
			case A_BUTTON:
			{
				GAME_SESSION->getPlayers().at(playerIndex)->getVelocity().set(0, 0);
				continue;
			}
			case START_BUTTON:
			{
				GAME_SESSION->startGame();
				continue;
			}
            default:
                break;
        }
    }
}

void MainScreen::render()
{
    m_renderer->beginFrame();
    
    m_renderer->mainDraw(m_fStateTime);
    
    m_renderer->endFrame();
}

RTTI_IMPL(MainScreen, IScreen);
