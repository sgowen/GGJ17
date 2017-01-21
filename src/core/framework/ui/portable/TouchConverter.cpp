//
//  TouchConverter.cpp
//  noctisgames-framework
//
//  Created by Stephen Gowen on 1/15/17.
//  Copyright (c) 2017 Noctis Games. All rights reserved.
//

#include "TouchConverter.h"

#include "TouchEvent.h"

#ifdef __APPLE__
#include "TargetConditionals.h"
#endif

TouchConverter* TouchConverter::getInstance()
{
    static TouchConverter *instance = new TouchConverter();
    return instance;
}

TouchConverter::TouchConverter() :
m_touchPoint(),
m_fTouchScreenWidth(160),
m_fTouchScreenHeight(90),
m_fCamWidth(1),
m_fCamHeight(1)
{
    // Empty
}

Vector2D& TouchConverter::touchToWorld(TouchEvent& touchEvent)
{
#if TARGET_OS_IPHONE
    m_touchPoint.set((touchEvent.getX() / m_fTouchScreenWidth) * m_fCamWidth, (1 - touchEvent.getY() / m_fTouchScreenHeight) * m_fCamHeight);
#elif TARGET_OS_OSX
    m_touchPoint.set((touchEvent.getX() / m_fTouchScreenWidth) * m_fCamWidth, (touchEvent.getY() / m_fTouchScreenHeight) * m_fCamHeight);
#elif __ANDROID__
    m_touchPoint.set((touchEvent.getX() / m_fTouchScreenWidth) * m_fCamWidth, (1 - touchEvent.getY() / m_fTouchScreenHeight) * m_fCamHeight);
#elif defined _WIN32
	m_touchPoint.set(touchEvent.getX() / m_fTouchScreenWidth * m_fCamWidth, m_fCamHeight - (touchEvent.getY() / m_fTouchScreenHeight * m_fCamHeight));
#endif
    
    return m_touchPoint;
}

void TouchConverter::setTouchScreenSize(int width, int height)
{
    m_fTouchScreenWidth = (float) width;
    m_fTouchScreenHeight = (float) height;
}

void TouchConverter::setCamSize(float camWidth, float camHeight)
{
    m_fCamWidth = camWidth;
    m_fCamHeight = camHeight;
}
