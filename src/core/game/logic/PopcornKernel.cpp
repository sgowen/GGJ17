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

#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

PopcornKernel::PopcornKernel(float x, float y, float width, float height) : PhysicalEntity(x, y, width, height), m_fHeat(0), m_fDelay(0)
{
	m_fDelay = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 110));
}

void PopcornKernel::update(float deltaTime)
{
    PhysicalEntity::update(deltaTime);

	m_fDelay -= deltaTime;

	if (m_fDelay < 0)
	{
		m_fHeat += deltaTime / 8;

		if (m_fHeat > 1)
		{
			// TODO, explode!
			m_isRequestingDeletion = true;
		}

		m_fHeat = clamp(m_fHeat, 1, 0);
	}
    
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
