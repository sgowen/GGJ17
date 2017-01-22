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
#include "SoundManager.h"
#include "SoundConstants.h"
#include "Player.h"

#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

PopcornKernel::PopcornKernel(float x, float y, float width, float height, float delay) : PhysicalEntity(x, y, width, height), m_fClamp(3), m_fHeat(0), m_fDelay(delay), m_isPopped(false), m_isKnocked(false), m_fKnockedTime(0), m_hasReceivedHeatTransfer(false), m_isPushed(false)
{
	m_fStateTime = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 2));
}

void PopcornKernel::update(float deltaTime)
{
	float xPre = getPosition().getX();
    float yPre = getPosition().getY();
    
    PhysicalEntity::update(deltaTime);

	if (m_isPopped)
	{
		m_fHeat = 0;
	}

    if (!m_isPopped)
    {
		if (m_hasReceivedHeatTransfer)
		{
			m_fDelay = -1;
		}

        m_fDelay -= deltaTime;
        
        if (m_fDelay < 0)
        {
            m_fHeat += deltaTime / 6;
        }

		if (m_fHeat > 1)
		{
			m_fHeat = 0;
			pop();
		}

		m_fHeat = clamp(m_fHeat, 1, 0);
    }

	if (m_isPushed)
	{
		if (m_velocity.getX() < 0
			&& m_acceleration.getX() < 0)
		{
			m_velocity.setX(0);
			m_acceleration.setX(0);
		}
		
		if (m_velocity.getX() > 0
			&& m_acceleration.getX() > 0)
		{
			m_velocity.setX(0);
			m_acceleration.setX(0);
		}

		if (m_velocity.getY() < 0
			&& m_acceleration.getY() < 0)
		{
			m_velocity.setY(0);
			m_acceleration.setY(0);
		}

		if (m_velocity.getY() > 0
			&& m_acceleration.getY() > 0)
		{
			m_velocity.setY(0);
			m_acceleration.setY(0);
		}
	}
    
	if (m_velocity.len() > 0)
	{
		if (!OverlapTester::isPointInCircle(getPosition(), GAME_SESSION->getBoundingCircle()))
		{
			getPosition().set(xPre, yPre);
		}
	}

	for (std::vector<PopcornKernel *>::iterator i = GAME_SESSION->getPopcornKernels().begin(); i != GAME_SESSION->getPopcornKernels().end(); i++)
	{
		if ((*i) != this
			&& OverlapTester::doNGRectsOverlap(getMainBounds(), (*i)->getMainBounds()))
		{
			(*i)->onPushed(this);
			break;
		}
	}
    
    float x = getPosition().getX();
    float y = getPosition().getY();
    
    x = clamp(x, CAM_WIDTH, 0);
    y = clamp(y, CAM_HEIGHT, 0);
    
	getPosition().set(x, y);
}

void PopcornKernel::acceptHeatTransfer(PopcornKernel* fromPopcornKernel, float heat)
{
    m_fHeat += heat;
    if (m_fHeat > 1)
    {
        m_fHeat = 0;
		pop();
        
        if (fromPopcornKernel
            && fromPopcornKernel->getRTTI().derivesFrom(Player::rtti))
        {
            Player* fromPlayer = reinterpret_cast<Player *>(fromPopcornKernel);
            fromPlayer->playKnockOutSound();
        }
    }

	m_hasReceivedHeatTransfer = true;
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
	
    
    if (getRTTI().derivesFrom(Player::rtti))
    {
        SOUND_MANAGER->addSoundIdToPlayQueue(Sound_kernelpop1);
    }
    else
    {
        SOUND_MANAGER->addSoundIdToPlayQueue(Sound_kernelpop3);
    }
    
	NGRect explodeBounds = NGRect(
		getMainBounds().getLeft() - getMainBounds().getWidth() * 2,
		getMainBounds().getBottom() - getMainBounds().getHeight() * 2,
		getMainBounds().getWidth() * 5,
		getMainBounds().getHeight() * 5);
    for (std::vector<PopcornKernel *>::iterator i = GAME_SESSION->getPopcornKernels().begin(); i != GAME_SESSION->getPopcornKernels().end(); i++)
    {
        if ((*i) != this
            && OverlapTester::doNGRectsOverlap(explodeBounds, (*i)->getMainBounds()))
        {
            (*i)->onHit(this);
        }
    }
    
    for (std::vector<Player *>::iterator i = GAME_SESSION->getPlayers().begin(); i != GAME_SESSION->getPlayers().end(); i++)
    {
        if ((*i) != this
			&& OverlapTester::doNGRectsOverlap(explodeBounds, (*i)->getMainBounds()))
        {
            (*i)->onHit(this);
        }
    }
}

void PopcornKernel::onHit(PopcornKernel* explodingKernel)
{
    float dist = explodingKernel->getPosition().cpy().dist(getPosition());
    dist = clamp(dist, 4, 0);
	Vector2D subjectKernelPos = getPosition().cpy(); 
	Vector2D explodingKernelPos = explodingKernel->getPosition().cpy();
    float angle = subjectKernelPos.sub(explodingKernelPos.getX(), explodingKernelPos.getY()).angle();

    float radians = DEGREES_TO_RADIANS(angle);
    float cos = cosf(radians);
    float sin = sinf(radians);
    
    m_velocity.set(cos * (2 - dist) * 2, sin * (2 - dist) * 2);

	
	m_fKnockedTime = 0;
	m_isKnocked = true;
    
    playHurtSound();
}

void PopcornKernel::onPushed(PopcornKernel* kernel)
{
	m_velocity.set(kernel->getVelocity().getX() / 3, kernel->getVelocity().getY() / 3);
	m_acceleration.set(-kernel->getVelocity().getX() / 4, -kernel->getVelocity().getY() / 4);

	m_isPushed = true;

	
}

RTTI_IMPL(PopcornKernel, PhysicalEntity);
