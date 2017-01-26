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
	SOUND_MANAGER->addMusicIdToPlayQueue(MUSIC_LOAD_menuloop);
    SOUND_MANAGER->addMusicIdToPlayQueue(MUSIC_PLAY_LOOP);
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
                if (GAME_SESSION->isSessionLive()
					&& GAME_SESSION->getStateTime() > 4)
                {
                    GAME_SESSION->getPlayers().at(playerIndex)->getAcceleration().set(x * 12, y * 12);
                }
                continue;
            }
            case TRIGGER:
            {
                if (GAME_SESSION->isSessionLive()
					&& GAME_SESSION->getStateTime() > 4)
                {
                    if (x > 0)
                    {
                        GAME_SESSION->getPlayers().at(playerIndex)->storeHeat(x);
                    }
                    else if (y > 0)
                    {
                        GAME_SESSION->getPlayers().at(playerIndex)->releaseHeat(y);
                    }
                    else
                    {
                        GAME_SESSION->getPlayers().at(playerIndex)->noAction();
                    }
                }
				continue;
            }
			case A_BUTTON:
			{
                if (GAME_SESSION->isSessionLive()
					&& GAME_SESSION->getStateTime() > 4)
                {
                    GAME_SESSION->getPlayers().at(playerIndex)->dash();
                }
				continue;
			}
			case START_BUTTON:
			{
                SOUND_MANAGER->addSoundIdToPlayQueue(Sound_beep);
                
                if (!GAME_SESSION->isSessionLive())
                {
                    SOUND_MANAGER->addMusicIdToPlayQueue(MUSIC_PAUSE);
                    SOUND_MANAGER->addSoundIdToPlayQueue(SOUND_gamestart);
                    
                    GAME_SESSION->startGame();
                }
                
				continue;
			}
            case BACK_BUTTON:
            {
                if (GAME_SESSION->isSessionLive())
                {
                    SOUND_MANAGER->addSoundIdToPlayQueue(Sound_beep);
                    
                    GAME_SESSION->reset();
                    
                    SOUND_MANAGER->addMusicIdToPlayQueue(MUSIC_LOAD_menuloop);
                    SOUND_MANAGER->addMusicIdToPlayQueue(MUSIC_PLAY_LOOP);
                }
                
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
