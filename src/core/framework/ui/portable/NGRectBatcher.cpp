//
//  NGRectBatcher.cpp
//  noctisgames-framework
//
//  Created by Stephen Gowen on 9/25/14.
//  Copyright (c) 2017 Noctis Games. All rights reserved.
//

#include "NGRectBatcher.h"
#include "NGRect.h"
#include "Vector2D.h"

NGRectBatcher::NGRectBatcher(bool isFill) : m_isFill(isFill), m_iNumNGRects(0)
{
    // Empty
}

void NGRectBatcher::renderNGRect(NGRect &rectangle, Color &color)
{
    float x1 = rectangle.getLeft();
    float y1 = rectangle.getBottom();
    float x2 = x1 + rectangle.getWidth();
    float y2 = y1 + rectangle.getHeight();
    
    renderNGRect(x1, y1, x2, y2, color);
}
