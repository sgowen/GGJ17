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
#include "OverlapTester.h"
#include "Player.h"
#include "GameSession.h"
#include "macros.h"
#include "OverlapTester.h"

#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

PopcornKernel::PopcornKernel(float x, float y, float width, float height, float delay) : PhysicalEntity(x, y, width, height), m_fClamp(3), m_fHeat(0), m_fDelay(delay), m_isPopped(false)
{
    // Empty
}

void PopcornKernel::update(float deltaTime)
{
    float xPre = getPosition().getX();
    float yPre = getPosition().getY();
    
    PhysicalEntity::update(deltaTime);

    if (!m_isPopped)
    {
        m_fDelay -= deltaTime;
        
        if (m_fDelay < 0)
        {
            m_fHeat += deltaTime / 4;
            
            if (m_fHeat > 1)
            {
                m_fHeat = 0;
                pop();
            }
            
            m_fHeat = clamp(m_fHeat, 1, 0);
        }
    }
    
    if (!OverlapTester::isPointInCircle(getPosition(), GAME_SESSION->getBoundingCircle()))
    {
        getPosition().set(xPre, yPre);
    }
    
    float x = getPosition().getX();
    float y = getPosition().getY();
    
    x = clamp(x, CAM_WIDTH, 0);
    y = clamp(y, CAM_HEIGHT, 0);
    
	getPosition().set(x, y);
}

void PopcornKernel::acceptHeatTransfer(float heat)
{
    m_fHeat += heat;
    if (m_fHeat > 1)
    {
        m_fHeat = 0;
        m_isPopped = true;
    }
}

float PopcornKernel::getHeat()
{
    return m_fHeat;
}

void PopcornKernel::pop()
{
    if (m_isPopped)
    {
        return;
    }
    
    m_isPopped = true;
    
    for (std::vector<PopcornKernel *>::iterator i = GAME_SESSION->getPopcornKernels().begin(); i != GAME_SESSION->getPopcornKernels().end(); i++)
    {
        if ((*i) != this
            && OverlapTester::doNGRectsOverlap(getMainBounds(), (*i)->getMainBounds()))
        {
            (*i)->onHit(this);
        }
    }
    
    for (std::vector<Player *>::iterator i = GAME_SESSION->getPlayers().begin(); i != GAME_SESSION->getPlayers().end(); i++)
    {
        if (OverlapTester::doNGRectsOverlap(getMainBounds(), (*i)->getMainBounds()))
        {
            (*i)->onHit(this);
        }
    }
}

void PopcornKernel::onHit(PopcornKernel* explodingKernel)
{
    float dist = explodingKernel->getPosition().dist(getPosition());
    dist = clamp(dist, 2, 0);
    Vector2D explodingKernelPos = explodingKernel->getPosition().cpy();
    float angle = explodingKernelPos.sub(m_position.getX(), m_position.getY()).angle();

    float radians = DEGREES_TO_RADIANS(angle);
    float cos = cosf(radians);
    float sin = sinf(radians);
    
    m_velocity.set(cos * (2 - dist), sin * (2 - dist));
}

RTTI_IMPL(PopcornKernel, PhysicalEntity);
