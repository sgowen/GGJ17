//
//  Player.cpp
//  ggj17
//
//  Created by Stephen Gowen on 1/21/17.
//  Copyright © 2017 Noctis Games. All rights reserved.
//

#include "Player.h"

#include "MathUtil.h"
#include "GameSession.h"
#include "OverlapTester.h"
#include "SoundManager.h"
#include "SoundConstants.h"

Player::Player(int index, float x, float y, float width, float height) : PopcornKernel(x, y, width, height, 0), m_iIndex(index), m_iState(PLAYER_STATE_NONE), m_fHeatManipIntensity(0)
{
    // Empty
}

void Player::update(float deltaTime)
{
	PopcornKernel::update(deltaTime);

    bool clampVelocity = true;
    if (m_iState == PLAYER_STATE_DASHING)
    {
        if (m_fStateTime > 0.6f)
        {
            m_fStateTime = 0;
            m_iState = PLAYER_STATE_NONE;
        }
        
        if (m_fStateTime < 0.3f)
        {
            clampVelocity = false;
        }
    }
    else if (m_iState == PLAYER_STATE_STORING_HEAT)
    {
		m_fHeat += m_fHeatManipIntensity * deltaTime / 6;
    }
    else if (m_iState == PLAYER_STATE_RELEASING_HEAT)
    {
        m_fHeat += m_fHeatManipIntensity * deltaTime / 6;
        
        handleHeatRelease();
    }

	if (m_isKnocked)
	{
		clampVelocity = false;
		m_fKnockedTime += m_fStateTime;
		if (m_fKnockedTime > 1)
		{
			m_fKnockedTime = 0;
			m_isKnocked = false;
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
    
    if (clampVelocity)
    {
        float x = getVelocity().getX();
        float y = getVelocity().getY();
        
        x = clamp(x, m_fClamp, -m_fClamp);
        y = clamp(y, m_fClamp, -m_fClamp);
        
        getVelocity().set(x, y);
    }
}

void Player::storeHeat(float intensity)
{
    if (m_isPopped)
    {
        return;
    }
    
    playStoreHeatSound();
    
    m_acceleration.mul(0.5f);
    m_fClamp = 1.5f;
    m_iState = PLAYER_STATE_STORING_HEAT;
    m_fHeatManipIntensity = intensity;
    m_fStateTime = 0;
    
    int storeHeatSoundId = m_iIndex * 10000;
    storeHeatSoundId += Sound_heatstore * 1000;
    storeHeatSoundId += intensity * 100;
    SOUND_MANAGER->addSoundIdToPlayQueue(storeHeatSoundId);
}

void Player::releaseHeat(float intensity)
{
    if (m_isPopped)
    {
        return;
    }
    
    if (m_fHeat < 0.4f)
    {
		SOUND_MANAGER->addSoundIdToPlayQueue(Sound_heatempty);
    }
    else
    {
        m_fClamp = 0;
        m_acceleration.set(0, 0);
        m_iState = PLAYER_STATE_RELEASING_HEAT;
        m_fHeatManipIntensity = intensity;
        m_fStateTime = 0;
        
        int releaseHeatSoundId = m_iIndex * 10000;
        releaseHeatSoundId += Sound_heatrelease * 1000;
        releaseHeatSoundId += intensity * 100;
        SOUND_MANAGER->addSoundIdToPlayQueue(releaseHeatSoundId);
    }
}

void Player::dash()
{
    if (m_isPopped)
    {
        return;
    }
    
    if (m_iState == PLAYER_STATE_DASHING)
    {
        return;
    }
    
    m_iState = PLAYER_STATE_DASHING;
    m_fStateTime = 0;
    m_fHeat += 0.01f;
    getVelocity().mul(3);
    
    playDashSound();
}

void Player::noAction()
{
    m_iState = PLAYER_STATE_NONE;
    m_fClamp = 3;
}

#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

void Player::playDashSound()
{
    int r = rand() % 2;
    
    switch (m_iIndex)
    {
        case 0:
        {
            switch (r)
            {
                case 0:
                    SOUND_MANAGER->addSoundIdToPlayQueue(Sound_Colonel_dashvoice);
                    break;
                case 1:
                    SOUND_MANAGER->addSoundIdToPlayQueue(Sound_Colonel_dash1);
                    break;
                default:
                    break;
            }
        }
            break;
        case 1:
        {
            switch (r)
            {
                case 0:
                    SOUND_MANAGER->addSoundIdToPlayQueue(Sound_Kobb_dashvoice);
                    break;
                case 1:
                    SOUND_MANAGER->addSoundIdToPlayQueue(Sound_Kobb_dash1);
                    break;
                default:
                    break;
            }
        }
            break;
        case 2:
        {
            switch (r)
            {
                case 0:
                    SOUND_MANAGER->addSoundIdToPlayQueue(Sound_Mazy_dashvoice);
                    break;
                case 1:
                    SOUND_MANAGER->addSoundIdToPlayQueue(Sound_Mazy_dash1);
                    break;
                default:
                    break;
            }
        }
            break;
        case 3:
        {
            switch (r)
            {
                case 0:
                    SOUND_MANAGER->addSoundIdToPlayQueue(Sound_Orville_dashvoice);
                    break;
                case 1:
                    SOUND_MANAGER->addSoundIdToPlayQueue(Sound_Orville_dash1);
                    break;
                default:
                    break;
            }
        }
            break;
        default:
            break;
    }
}

void Player::playHurtSound()
{
	if (m_isPopped)
	{
		return;
	}

    int r = rand() % 2;
    
    switch (m_iIndex)
    {
        case 0:
        {
            switch (r)
            {
                case 0:
                    SOUND_MANAGER->addSoundIdToPlayQueue(Sound_Colonel_hurt2);
                    break;
                case 1:
                    SOUND_MANAGER->addSoundIdToPlayQueue(Sound_Colonel_hurtvoice);
                    break;
                default:
                    break;
            }
        }
            break;
        case 1:
        {
            switch (r)
            {
                case 0:
                    SOUND_MANAGER->addSoundIdToPlayQueue(Sound_Kobb_hurt2);
                    break;
                case 1:
                    SOUND_MANAGER->addSoundIdToPlayQueue(Sound_Kobb_hurtvoice);
                    break;
                default:
                    break;
            }
        }
            break;
        case 2:
        {
            switch (r)
            {
                case 0:
                    SOUND_MANAGER->addSoundIdToPlayQueue(Sound_Mazy_hurt1);
                    break;
                case 1:
                    SOUND_MANAGER->addSoundIdToPlayQueue(Sound_Mazy_hurtvoice);
                    break;
                default:
                    break;
            }
        }
            break;
        case 3:
        {
            switch (r)
            {
                case 0:
                    SOUND_MANAGER->addSoundIdToPlayQueue(Sound_Orville_hurtvoice);
                    break;
                case 1:
                    SOUND_MANAGER->addSoundIdToPlayQueue(Sound_Orville_hurt1);
                    break;
                default:
                    break;
            }
        }
            break;
        default:
            break;
    }
}

void Player::playStoreHeatSound()
{
    if (m_iState == PLAYER_STATE_STORING_HEAT)
    {
        return;
    }
    
    switch (m_iIndex)
    {
        case 0:
            SOUND_MANAGER->addSoundIdToPlayQueue(Sound_Colonel_storeheat);
            break;
        case 1:
            SOUND_MANAGER->addSoundIdToPlayQueue(Sound_Kobb_storeheat);
            break;
        case 2:
            SOUND_MANAGER->addSoundIdToPlayQueue(Sound_Mazy_storeheat);
            break;
        case 3:
            SOUND_MANAGER->addSoundIdToPlayQueue(Sound_Orville_storeheat);
            break;
        default:
            break;
    }
}

void Player::playVictorySound()
{
    switch (m_iIndex)
    {
        case 0:
            SOUND_MANAGER->addSoundIdToPlayQueue(Sound_Colonel_victory);
            break;
        case 1:
            SOUND_MANAGER->addSoundIdToPlayQueue(Sound_Kobb_victory);
            break;
        case 2:
            SOUND_MANAGER->addSoundIdToPlayQueue(Sound_Mazy_victory);
            break;
        case 3:
            SOUND_MANAGER->addSoundIdToPlayQueue(Sound_Orville_victory);
            break;
        default:
            break;
    }
}

void Player::playKnockOutSound()
{
    switch (m_iIndex)
    {
        case 0:
            SOUND_MANAGER->addSoundIdToPlayQueue(Sound_Colonel_KO);
            break;
        case 1:
            SOUND_MANAGER->addSoundIdToPlayQueue(Sound_Kobb_KO);
            break;
        case 2:
            SOUND_MANAGER->addSoundIdToPlayQueue(Sound_Mazy_KO);
            break;
        case 3:
            SOUND_MANAGER->addSoundIdToPlayQueue(Sound_Orville_KO);
            break;
        default:
            break;
    }
}

void Player::handleHeatRelease()
{
	NGRect transferBounds = NGRect(
		getMainBounds().getLeft() - getMainBounds().getWidth() / 2,
		getMainBounds().getBottom() - getMainBounds().getHeight() / 2,
		getMainBounds().getWidth() * 2,
		getMainBounds().getHeight() * 2);

    float heatToTransfer = m_fHeat * m_fHeatManipIntensity;
    
    for (std::vector<PopcornKernel *>::iterator i = GAME_SESSION->getPopcornKernels().begin(); i != GAME_SESSION->getPopcornKernels().end(); i++)
    {
        if (OverlapTester::doNGRectsOverlap(transferBounds, (*i)->getMainBounds())
            && !(*i)->isPopped())
        {
            (*i)->acceptHeatTransfer(this, heatToTransfer);
            m_fHeat -= heatToTransfer;
            m_fHeat = clamp(m_fHeat, 1, 0);
            m_fHeatManipIntensity = 0;
            m_iState = PLAYER_STATE_NONE;
            return;
        }
    }
    
    for (std::vector<Player *>::iterator i = GAME_SESSION->getPlayers().begin(); i != GAME_SESSION->getPlayers().end(); i++)
    {
        if ((*i) != this
            && OverlapTester::doNGRectsOverlap(transferBounds, (*i)->getMainBounds())
            && !(*i)->isPopped())
        {
            (*i)->acceptHeatTransfer(this, heatToTransfer);
            m_fHeat -= heatToTransfer;
            m_fHeat = clamp(m_fHeat, 1, 0);
            m_fHeatManipIntensity = 0;
            m_iState = PLAYER_STATE_NONE;
            return;
        }
    }
}

RTTI_IMPL(Player, PopcornKernel);
