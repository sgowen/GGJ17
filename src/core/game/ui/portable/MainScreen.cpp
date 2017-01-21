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
		m_playerCoords[i] = CAM_WIDTH / 2;
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
    
    INPUT_MANAGER->processTouchEvents();
    
    std::vector<TouchEvent*> touchEvents = INPUT_MANAGER->getTouchEvents();

    for (std::vector<TouchEvent*>::iterator i = touchEvents.begin(); i != touchEvents.end(); i++)
    {
        Vector2D& touchPoint = TOUCH_CONVERTER->touchToWorld(*(*i));
        
        switch ((*i)->getTouchType())
        {
            case DOWN:
            {
                continue;
            }
            case DRAGGED:
            {
                continue;
            }
            case UP:
            {
                SOUND_MANAGER->addSoundIdToPlayQueue(SOUND_DEMO);
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
