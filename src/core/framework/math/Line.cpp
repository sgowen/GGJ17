//
//  Line.cpp
//  noctisgames-framework
//
//  Created by Stephen Gowen on 2/22/14.
//  Copyright (c) 2017 Noctis Games. All rights reserved.
//

#include "Line.h"

Line::Line(float x1, float y1, float x2, float y2) : m_origin(x1, y1), m_end(x2, y2)
{
    // Empty
}

Vector2D& Line::getOrigin()
{
    return m_origin;
}

Vector2D& Line::getEnd()
{
    return m_end;
}
