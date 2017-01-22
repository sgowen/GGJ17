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

Player::Player(float x, float y, float width, float height) : PopcornKernel(x, y, width, height, 0), m_iState(PLAYER_STATE_NONE), m_fHeatManipIntensity(0)
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
        m_fHeat += m_fHeatManipIntensity * deltaTime / 4;
    }
    else if (m_iState == PLAYER_STATE_RELEASING_HEAT)
    {
        handleHeatRelease();
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

void Player::storeHeat(float intensity, int playerIndex)
{
    if (m_isPopped)
    {
        return;
    }
    
    m_acceleration.mul(0.5f);
    m_fClamp = 1.5f;
    m_iState = PLAYER_STATE_STORING_HEAT;
    m_fHeatManipIntensity = intensity;
    m_fStateTime = 0;
    
    log();
    
    int storeHeatSoundId = playerIndex * 10000;
    storeHeatSoundId += SOUND_STORE_HEAT * 1000;
    storeHeatSoundId += intensity * 100;
    SOUND_MANAGER->addSoundIdToPlayQueue(storeHeatSoundId);
}

void Player::releaseHeat(float intensity, int playerIndex)
{
    if (m_isPopped)
    {
        return;
    }
    
    m_fClamp = 0;
    m_acceleration.set(0, 0);
    m_iState = PLAYER_STATE_RELEASING_HEAT;
    m_fHeatManipIntensity = intensity;
    m_fStateTime = 0;
    
    log();
    
    int releaseHeatSoundId = playerIndex * 10000;
    releaseHeatSoundId += SOUND_RELEASE_HEAT * 1000;
    releaseHeatSoundId += intensity * 100;
    SOUND_MANAGER->addSoundIdToPlayQueue(releaseHeatSoundId);
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
    m_fHeat += 0.1f;
    getVelocity().mul(3);
    
    log();
}

void Player::noAction()
{
    m_iState = PLAYER_STATE_NONE;
    m_fStateTime = 0;
    m_fClamp = 3;
    
    log();
}

void Player::handleHeatRelease()
{
    float heatToTransfer = m_fHeat * m_fHeatManipIntensity;
    
    for (std::vector<PopcornKernel *>::iterator i = GAME_SESSION->getPopcornKernels().begin(); i != GAME_SESSION->getPopcornKernels().end(); i++)
    {
        if (OverlapTester::doNGRectsOverlap(getMainBounds(), (*i)->getMainBounds())
            && !(*i)->isPopped())
        {
            (*i)->acceptHeatTransfer(heatToTransfer);
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
            && OverlapTester::doNGRectsOverlap(getMainBounds(), (*i)->getMainBounds())
            && !(*i)->isPopped())
        {
            (*i)->acceptHeatTransfer(heatToTransfer);
            m_fHeat -= heatToTransfer;
            m_fHeat = clamp(m_fHeat, 1, 0);
            m_fHeatManipIntensity = 0;
            m_iState = PLAYER_STATE_NONE;
            return;
        }
    }
}

RTTI_IMPL(Player, PopcornKernel);
