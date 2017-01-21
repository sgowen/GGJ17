//
//  PopcornKernel.cpp
//  ggj17
//
//  Created by Stephen Gowen on 1/21/17.
//  Copyright © 2017 Noctis Games. All rights reserved.
//

#include "PopcornKernel.h"

#include "MathUtil.h"
#include "ScreenConstants.h"

PopcornKernel::PopcornKernel(float x, float y, float width, float height) : PhysicalEntity(x, y, width, height), m_fHeat(0)
{
    // Empty
}

void PopcornKernel::update(float deltaTime)
{
    PhysicalEntity::update(deltaTime);
    
    float x = getPosition().getX();
    float y = getPosition().getY();
    
    x = clamp(x, CAM_WIDTH, 0);
    y = clamp(y, CAM_HEIGHT, 0);
    
    getPosition().set(x, y);
}

float PopcornKernel::getHeat()
{
    return m_fHeat;
}

RTTI_IMPL(PopcornKernel, PhysicalEntity);
