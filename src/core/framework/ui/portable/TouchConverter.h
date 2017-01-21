//
//  TouchConverter.h
//  noctisgames-framework
//
//  Created by Stephen Gowen on 1/15/17.
//  Copyright (c) 2017 Noctis Games. All rights reserved.
//

#ifndef __noctisgames__TouchConverter__
#define __noctisgames__TouchConverter__

#include "Vector2D.h"

#define TOUCH_CONVERTER (TouchConverter::getInstance())

class TouchEvent;

class TouchConverter
{
public:
    static TouchConverter* getInstance();
    
    Vector2D& touchToWorld(TouchEvent& touchEvent);
    
    void setTouchScreenSize(int width, int height);
    
    void setCamSize(float camWidth, float camHeight);
    
private:
    Vector2D m_touchPoint;
    float m_fTouchScreenWidth;
    float m_fTouchScreenHeight;
    float m_fCamWidth;
    float m_fCamHeight;
    
    // ctor, copy ctor, and assignment should be private in a Singleton
    TouchConverter();
    TouchConverter(const TouchConverter&);
    TouchConverter& operator=(const TouchConverter&);
};

#endif /* defined(__noctisgames__TouchConverter__) */
