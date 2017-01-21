//
//  SoundManager.cpp
//  noctisgames-framework
//
//  Created by Stephen Gowen on 2/22/14.
//  Copyright (c) 2017 Noctis Games. All rights reserved.
//

#include "SoundManager.h"

SoundManager* SoundManager::getInstance()
{
    static SoundManager *instance = new SoundManager();
    return instance;
}

short SoundManager::getCurrentMusicId()
{
    short musicId = getFirstMusicId();
    eraseFirstMusicId();
    
    return musicId;
}

short SoundManager::getCurrentSoundId()
{
    short playThisSound = getFirstSoundId();
    eraseFirstSoundId();
    
    return playThisSound;
}

short SoundManager::getFirstSoundId()
{
    return m_sSoundIds.size() > 0 ? m_sSoundIds.front() : 0;
}

void SoundManager::addSoundIdToPlayQueue(short soundId)
{
    if (m_sSoundIds.size() < MAX_SOUNDS_TO_PLAY_PER_FRAME)
    {
        m_sSoundIds.push_back(soundId);
    }
}

void SoundManager::forceAddSoundIdToPlayQueue(short soundId)
{
    m_sSoundIds.push_back(soundId);
}

void SoundManager::eraseFirstSoundId()
{
    if (m_sSoundIds.size() > 0)
    {
        m_sSoundIds.erase(m_sSoundIds.begin());
    }
}

short SoundManager::getFirstMusicId()
{
    return m_sMusicIds.size() > 0 ? m_sMusicIds.front() : 0;
}

void SoundManager::addMusicIdToPlayQueue(short musicId)
{
    m_sMusicIds.push_back(musicId);
}

void SoundManager::eraseFirstMusicId()
{
    if (m_sMusicIds.size() > 0)
    {
        m_sMusicIds.erase(m_sMusicIds.begin());
    }
}

bool SoundManager::isMusicEnabled()
{
    return m_isMusicEnabled;
}

void SoundManager::setMusicEnabled(bool isMusicEnabled)
{
    m_isMusicEnabled = isMusicEnabled;
    
    addMusicIdToPlayQueue(m_isMusicEnabled ? 1 : 0);
}

bool SoundManager::isSoundEnabled()
{
    return m_isSoundEnabled;
}

void SoundManager::setSoundEnabled(bool isSoundEnabled)
{
    m_isSoundEnabled = isSoundEnabled;
}

SoundManager::SoundManager() : m_isMusicEnabled(true), m_isSoundEnabled(true)
{
    // Empty
}
