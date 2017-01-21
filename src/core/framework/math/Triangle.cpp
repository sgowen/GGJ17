//
//  Triangle.cpp
//  noctisgames-framework
//
//  Created by Stephen Gowen on 2/22/14.
//  Copyright (c) 2017 Noctis Games. All rights reserved.
//

#include "Triangle.h"

Triangle::Triangle(float x1, float y1, float x2, float y2, float x3, float y3) :
m_sideA(x1, y1, x2, y2),
m_sideB(x2, y2, x3, y3),
m_sideC(x3, y3, x1, y1)
{
    // Empty
}

void Triangle::set(float x1, float y1, float x2, float y2, float x3, float y3)
{
    m_sideA.getOrigin().set(x1, y1);
    m_sideA.getEnd().set(x2, y2);
    m_sideB.getOrigin().set(x2, y2);
    m_sideB.getEnd().set(x3, y3);
    m_sideC.getOrigin().set(x3, y3);
    m_sideC.getEnd().set(x1, y1);
}

Vector2D& Triangle::getPointA()
{
    return m_sideA.getOrigin();
}

Vector2D& Triangle::getPointB()
{
    return m_sideB.getOrigin();
}

Vector2D& Triangle::getPointC()
{
    return m_sideC.getOrigin();
}

Line& Triangle::getSideA()
{
    return m_sideA;
}

Line& Triangle::getSideB()
{
    return m_sideB;
}

Line& Triangle::getSideC()
{
    return m_sideC;
}
