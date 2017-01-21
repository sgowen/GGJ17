//
//  NGRect.cpp
//  noctisgames-framework
//
//  Created by Stephen Gowen on 2/22/14.
//  Copyright (c) 2017 Noctis Games. All rights reserved.
//

#include "NGRect.h"

NGRect::NGRect(float x, float y, float width, float height, float angle)
{
    m_lowerLeft = Vector2D(x, y);
    m_fWidth = width;
    m_fHeight = height;
    m_fAngle = angle;
}

Vector2D& NGRect::getLowerLeft()
{
    return m_lowerLeft;
}

float NGRect::getRight()
{
    return m_lowerLeft.getX() + m_fWidth;
}

float NGRect::getTop()
{
    return m_lowerLeft.getY() + m_fHeight;
}

float NGRect::getLeft()
{
    return m_lowerLeft.getX();
}

float NGRect::getBottom()
{
    return m_lowerLeft.getY();
}

float NGRect::getWidth()
{
    return m_fWidth;
}

void NGRect::setWidth(float width)   
{
    m_fWidth = width;
}

float NGRect::getHeight()
{
    return m_fHeight;
}

void NGRect::setHeight(float height)
{
    m_fHeight = height;
}

float NGRect::getAngle()
{
    return m_fAngle;
}

void NGRect::setAngle(float angle)
{
    m_fAngle = angle;
}
