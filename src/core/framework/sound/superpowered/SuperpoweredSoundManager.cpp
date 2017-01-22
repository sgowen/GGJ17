//
//  SuperpoweredSoundManager.cpp
//  noctisgames-framework
//
//  Created by Stephen Gowen on 10/20/16.
//  Copyright (c) 2017 Noctis Games. All rights reserved.
//

#include "SuperpoweredSoundManager.h"

#include "SuperpoweredSound.h"
#include "SuperpoweredSoundCollection.h"
#include "VectorUtil.h"

#include <SuperpoweredSimple.h>

#import <stdlib.h>

#ifdef __APPLE__
#include "TargetConditionals.h"
#endif

SuperpoweredSoundManager::SuperpoweredSoundManager(unsigned int sampleRate, unsigned int bufferSize) :
m_music(nullptr),
m_activeSounds(),
m_iSampleRate(sampleRate),
m_iSoundIndex(0)
{
    for (int i = 0; i < MAX_NUM_SOUND_PLAYERS; i++)
    {
        float* stereoBuffer;
#if defined TARGET_OS_IPHONE || defined TARGET_OS_OSX
        if (posix_memalign((void **)&stereoBuffer, 16, 4096 + 128) != 0) abort(); // Allocating memory, aligned to 16.
#elif defined __ANDROID__
        stereoBuffer = (float *)memalign(16, (bufferSize + 16) * sizeof(float) * 2);
#endif
        m_stereoBuffers.push_back(stereoBuffer);
    }
}

SuperpoweredSoundManager::~SuperpoweredSoundManager()
{
    delete m_music;
    
    VectorUtil::cleanUpVectorOfPointers(m_sounds);
    
    for (int i = 0; i < MAX_NUM_SOUND_PLAYERS; i++)
    {
        free(m_stereoBuffers[i]);
    }
}

void SuperpoweredSoundManager::loadSound(int rawResourceId, const char *path, int numCopies, int fileOffset, int fileLength)
{
    m_sounds.push_back(new SuperpoweredSoundCollection(path, m_iSampleRate, rawResourceId, numCopies, fileOffset, fileLength));
}

void SuperpoweredSoundManager::playSound(int rawResourceId, float volume, bool isLooping)
{
    for (std::vector<SuperpoweredSoundCollection *>::iterator i = m_sounds.begin(); i != m_sounds.end(); i++)
    {
        if ((*i)->getRawResourceId() == rawResourceId)
        {
            SuperpoweredSound* sound = (*i)->getSound();
            
            sound->play(isLooping);
            
            for (int j = 0; j < (MAX_NUM_SOUND_PLAYERS - 1); j++)
            {
                if (m_activeSounds[j] == sound)
                {
                    return;
                }
            }
            
            int count = 0;
            bool isGoodToBreak = false;
            while (true)
            {
                if (!m_activeSounds[m_iSoundIndex]
                    || !m_activeSounds[m_iSoundIndex]->isPlaying())
                {
                    m_activeSounds[m_iSoundIndex] = sound;
                    
                    isGoodToBreak = true;
                }
                
                m_iSoundIndex++;
                if (m_iSoundIndex > (MAX_NUM_SOUND_PLAYERS - 3))
                {
                    m_iSoundIndex = 0;
                }
                
                count++;
                if (isGoodToBreak
                    || count > (MAX_NUM_SOUND_PLAYERS - 1))
                {
                    break;
                }
            }
            
            return;
        }
    }
}

void SuperpoweredSoundManager::stopSound(int rawResourceId)
{
    for (std::vector<SuperpoweredSoundCollection *>::iterator i = m_sounds.begin(); i != m_sounds.end(); i++)
    {
        if ((*i)->getRawResourceId() == rawResourceId)
        {
            for (int j = 0; j < (*i)->getNumCopies(); j++)
            {
                SuperpoweredSound* sound = (*i)->getSound();
                if (sound->isPlaying())
                {
                    sound->stop();
                    
                    return;
                }
            }
            
            return;
        }
    }
}

void SuperpoweredSoundManager::stopAllSounds(bool stopOnlyLoopingSounds)
{
    for (std::vector<SuperpoweredSoundCollection *>::iterator i = m_sounds.begin(); i != m_sounds.end(); i++)
    {
        for (int j = 0; j < (*i)->getNumCopies(); j++)
        {
            SuperpoweredSound* sound = (*i)->getSound();
            if (sound->isPlaying())
            {
                if (!stopOnlyLoopingSounds
                    || (stopOnlyLoopingSounds
                    && sound->isLooping()))
                {
                    sound->stop();
                }
            }
        }
    }
}

void SuperpoweredSoundManager::stopAllLoopingSounds()
{
    stopAllSounds(true);
}

void SuperpoweredSoundManager::loadMusic(int rawResourceId, const char *path, int fileOffset, int fileLength)
{
    if (m_music)
    {
        m_music->pause();
        
        delete m_music;
    }
    
    m_music = new SuperpoweredSound(path, m_iSampleRate, rawResourceId, fileOffset, fileLength, 1);
}

void SuperpoweredSoundManager::playMusic(float volume, bool isLooping)
{
    if (m_music)
    {
        m_music->play(isLooping);
        m_music->setVolume(volume);
    }
}

void SuperpoweredSoundManager::setMusicVolume(float volume)
{
    if (m_music)
    {
        m_music->setVolume(volume);
    }
}

void SuperpoweredSoundManager::resumeMusic()
{
    if (m_music)
    {
        m_music->resume();
    }
}

void SuperpoweredSoundManager::pauseMusic()
{
    if (m_music)
    {
        m_music->pause();
    }
}

bool SuperpoweredSoundManager::processMusic(void *output, unsigned int numberOfSamples, unsigned int sampleRate)
{
    return m_music && m_music->process(m_stereoBuffers[0], output, numberOfSamples, sampleRate);
}

bool SuperpoweredSoundManager::processSound1(void *output, unsigned int numberOfSamples, unsigned int sampleRate)
{
    return processSound(output, numberOfSamples, m_activeSounds[0], m_stereoBuffers[1], sampleRate);
}

bool SuperpoweredSoundManager::processSound2(void *output, unsigned int numberOfSamples, unsigned int sampleRate)
{
    return processSound(output, numberOfSamples, m_activeSounds[1], m_stereoBuffers[2], sampleRate);
}

bool SuperpoweredSoundManager::processSound3(void *output, unsigned int numberOfSamples, unsigned int sampleRate)
{
    return processSound(output, numberOfSamples, m_activeSounds[2], m_stereoBuffers[3], sampleRate);
}

bool SuperpoweredSoundManager::processSound4(void *output, unsigned int numberOfSamples, unsigned int sampleRate)
{
    return processSound(output, numberOfSamples, m_activeSounds[3], m_stereoBuffers[4], sampleRate);
}

bool SuperpoweredSoundManager::processSound5(void *output, unsigned int numberOfSamples, unsigned int sampleRate)
{
    return processSound(output, numberOfSamples, m_activeSounds[4], m_stereoBuffers[5], sampleRate);
}

bool SuperpoweredSoundManager::processSound6(void *output, unsigned int numberOfSamples, unsigned int sampleRate)
{
    return processSound(output, numberOfSamples, m_activeSounds[5], m_stereoBuffers[6], sampleRate);
}

bool SuperpoweredSoundManager::processSound7(void *output, unsigned int numberOfSamples, unsigned int sampleRate)
{
    return processSound(output, numberOfSamples, m_activeSounds[6], m_stereoBuffers[7], sampleRate);
}

bool SuperpoweredSoundManager::processSound8(void *output, unsigned int numberOfSamples, unsigned int sampleRate)
{
    return processSound(output, numberOfSamples, m_activeSounds[7], m_stereoBuffers[8], sampleRate);
}

bool SuperpoweredSoundManager::processSound9(void *output, unsigned int numberOfSamples, unsigned int sampleRate)
{
    return processSound(output, numberOfSamples, m_activeSounds[8], m_stereoBuffers[9], sampleRate);
}

bool SuperpoweredSoundManager::processSound10(void *output, unsigned int numberOfSamples, unsigned int sampleRate)
{
    return processSound(output, numberOfSamples, m_activeSounds[9], m_stereoBuffers[10], sampleRate);
}

bool SuperpoweredSoundManager::processSound11(void *output, unsigned int numberOfSamples, unsigned int sampleRate)
{
    return processSound(output, numberOfSamples, m_activeSounds[10], m_stereoBuffers[11], sampleRate);
}

bool SuperpoweredSoundManager::processSound(void *output, unsigned int numberOfSamples, SuperpoweredSound *sound, float *stereoBuffer, unsigned int sampleRate)
{
    return sound && sound->process(stereoBuffer, output, numberOfSamples, sampleRate);
}
