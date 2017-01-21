//
//  InputManager.cpp
//  noctisgames-framework
//
//  Created by Stephen Gowen on 1/15/17.
//  Copyright (c) 2017 Noctis Games. All rights reserved.
//

#include "InputManager.h"

InputManager* InputManager::getInstance()
{
    static InputManager *instance = new InputManager();
    return instance;
}

void InputManager::onTouch(Touch_Type type, float x, float y)
{
    if (type == Touch_Type::DRAGGED
		&& (m_touchEventsBuffer.size() >= MAX_DRAGGED_EVENTS_PER_FRAME
			|| !m_isPressed))
    {
        return;
    }
    
    addTouchEventForType(type, x, y);
}

void InputManager::processTouchEvents()
{
    m_touchEvents.clear();
    m_touchEvents.swap(m_touchEventsBuffer);
    m_touchEventsBuffer.clear();
}

std::vector<TouchEvent*>& InputManager::getTouchEvents()
{
    return m_touchEvents;
}

void InputManager::onGamePadInput(GamePad_Event_Type type, int playerIndex, float x, float y)
{
	addGamePadEventForType(type, playerIndex, x, y);
}

void InputManager::processGamePadEvents()
{
	m_gamePadEvents.clear();
	m_gamePadEvents.swap(m_gamePadEventsBuffer);
	m_gamePadEventsBuffer.clear();
}

std::vector<GamePadEvent*>& InputManager::getGamePadEvents()
{
	return m_gamePadEvents;
}

#pragma mark private

TouchEvent* InputManager::newTouchEvent()
{
    TouchEvent* touchEvent = m_touchEventsPool.at(m_iTouchPoolIndex++);
    
    if (m_iTouchPoolIndex >= STARTING_TOUCH_EVENT_POOL_SIZE)
    {
        m_iTouchPoolIndex = 0;
    }
    
    return touchEvent;
}

void InputManager::addTouchEventForType(Touch_Type type, float x, float y)
{
    TouchEvent* touchEvent = newTouchEvent();
    touchEvent->setTouchType(type);
    touchEvent->setX(x);
    touchEvent->setY(y);
    
    m_touchEventsBuffer.push_back(touchEvent);

	m_isPressed = type == DOWN || type == DRAGGED;
}

GamePadEvent* InputManager::newGamePadEvent()
{
	GamePadEvent* gamePadEvent = m_gamePadEventsPool.at(m_iGamePadPoolIndex++);

	if (m_iGamePadPoolIndex >= STARTING_TOUCH_EVENT_POOL_SIZE)
	{
		m_iGamePadPoolIndex = 0;
	}

	return gamePadEvent;
}

void InputManager::addGamePadEventForType(GamePad_Event_Type type, int playerIndex, float x, float y)
{
	GamePadEvent* gamePadEvent = newGamePadEvent();
	gamePadEvent->setType(type);
	gamePadEvent->setPlayerIndex(playerIndex);
	gamePadEvent->setX(x);
	gamePadEvent->setY(y);

	m_gamePadEventsBuffer.push_back(gamePadEvent);
}

InputManager::InputManager() : m_iTouchPoolIndex(0), m_iGamePadPoolIndex(0), m_isPressed(false)
{
    for (int i = 0; i < STARTING_TOUCH_EVENT_POOL_SIZE; i++)
    {
        m_touchEventsPool.push_back(new TouchEvent(0, 0, Touch_Type::DOWN));
    }

	for (int i = 0; i < STARTING_TOUCH_EVENT_POOL_SIZE; i++)
	{
		m_gamePadEventsPool.push_back(new GamePadEvent(0, 0, 0, GamePad_Event_Type::STICK_LEFT));
	}
}
