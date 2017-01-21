//
//  NGRect.h
//  noctisgames-framework
//
//  Created by Stephen Gowen on 2/22/14.
//  Copyright (c) 2017 Noctis Games. All rights reserved.
//

#ifndef __noctisgames__NGRect__
#define __noctisgames__NGRect__

#include "Vector2D.h"

class NGRect
{
public:
    NGRect(float x, float y, float width, float height, float angle = 0);

	NGRect(const NGRect &) {}
    
    Vector2D& getLowerLeft();
    
    float getRight();
    
    float getTop();
    
    float getLeft();
    
    float getBottom();
    
    float getWidth();
    
    void setWidth(float width);
    
    float getHeight();
    
    void setHeight(float height);
    
    float getAngle();
    
    void setAngle(float angle);
    
private:
    Vector2D m_lowerLeft;
    float m_fWidth;
    float m_fHeight;
    float m_fAngle;
};

#endif /* defined(__noctisgames__NGRect__) */
