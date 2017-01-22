//
//  Circle.cpp
//  noctisgames-framework
//
//  Created by Stephen Gowen on 8/6/13.
//  Copyright (c) 2017 Noctis Games. All rights reserved.
//

#include "Circle.h"

Circle::Circle(float x, float y, float radiusWidth, float radiusHeight) : m_center(x, y), m_fRadiusWidth(radiusWidth), m_fRadiusHeight(radiusHeight)
{
    // Empty
}

Vector2D& Circle::getCenter()
{
    return m_center;
}

float Circle::getRadiusWidth()
{
    return m_fRadiusWidth;
}

float Circle::getRadiusHeight()
{
    return m_fRadiusHeight;
}
