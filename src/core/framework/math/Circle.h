//
//  Circle.h
//  noctisgames-framework
//
//  Created by Stephen Gowen on 8/6/13.
//  Copyright (c) 2017 Noctis Games. All rights reserved.
//

#ifndef __noctisgames__Circle__
#define __noctisgames__Circle__

#include "Vector2D.h"

class Circle
{
public:
	Circle(float x, float y, float radiusWidth, float radiusHeight);
    
	Vector2D& getCenter();
    
    float getRadiusWidth();
    
    float getRadiusHeight();

private:
    Vector2D m_center;
    float m_fRadiusWidth;
    float m_fRadiusHeight;
};

#endif /* defined(__noctisgames__Circle__) */
