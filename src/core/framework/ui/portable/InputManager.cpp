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

#pragma mark private

TouchEvent* InputManager::newTouchEvent()
{
    TouchEvent* touchEvent = m_touchEventsPool.at(m_iPoolIndex++);
    
    if (m_iPoolIndex >= STARTING_TOUCH_EVENT_POOL_SIZE)
    {
        m_iPoolIndex = 0;
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

InputManager::InputManager() : m_iPoolIndex(0), m_isPressed(false)
{
    for (int i = 0; i < STARTING_TOUCH_EVENT_POOL_SIZE; i++)
    {
        m_touchEventsPool.push_back(new TouchEvent(0, 0, Touch_Type::DOWN));
    }
}
