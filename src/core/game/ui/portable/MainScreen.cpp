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

MainScreen::MainScreen() : IScreen(),
m_deviceHelper(DEVICE_HELPER_FACTORY->createDeviceHelper()),
m_renderer(new MainRenderer()),
m_fStateTime(0),
m_iRequestedUiAction(0)
{
	for (int i = 0; i < 8; i++)
	{
		m_playerCoords[i] = 0;
	}

    SOUND_MANAGER->addMusicIdToPlayQueue(MUSIC_LOAD_DEMO);
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
				updatePlayerCoords(playerIndex, x, y);
                continue;
            }
            case STICK_RIGHT:
            {
				updatePlayerCoords(playerIndex, x, y);
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
                return;
            }
            default:
                break;
        }
    }
}

void MainScreen::render()
{
    m_renderer->beginFrame();
    
    m_renderer->tempDraw(m_fStateTime
		, m_playerCoords[0]
		, m_playerCoords[1]
		, m_playerCoords[2]
		, m_playerCoords[3]
		, m_playerCoords[4]
		, m_playerCoords[5]
		, m_playerCoords[6]
		, m_playerCoords[7]);
    
    m_renderer->endFrame();
}

void MainScreen::updatePlayerCoords(int playerIndex, float x, float y)
{
	m_playerCoords[playerIndex * 2] += x;
	m_playerCoords[playerIndex * 2] = clamp(m_playerCoords[playerIndex * 2], CAM_WIDTH, 0);
	
	m_playerCoords[playerIndex * 2 + 1] += y;
	m_playerCoords[playerIndex * 2 + 1] = clamp(m_playerCoords[playerIndex * 2 + 1], CAM_HEIGHT, 0);
}

RTTI_IMPL(MainScreen, IScreen);
