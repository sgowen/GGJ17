//
//  Circle.cpp
//  noctisgames-framework
//
//  Created by Stephen Gowen on 8/6/13.
//  Copyright (c) 2017 Noctis Games. All rights reserved.
//

#include "Circle.h"

Circle::Circle(float x, float y, float radius) : m_center(x, y), m_fRadius(radius)
{
    // Empty
}

Vector2D& Circle::getCenter()
{
    return m_center;
}

float Circle::getRadius()
{
    return m_fRadius;
}
