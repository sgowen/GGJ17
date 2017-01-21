//
//  SuperpoweredSound.cpp
//  noctisgames-framework
//
//  Created by Stephen Gowen on 10/20/16.
//  Copyright (c) 2017 Noctis Games. All rights reserved.
//

#include "SuperpoweredSound.h"

#include <math.h>

#include <SuperpoweredSimple.h>

#ifdef __APPLE__
#include "TargetConditionals.h"
#endif

#define HEADROOM_DECIBEL 3.0f
static const float headroom = powf(10.0f, -HEADROOM_DECIBEL * 0.025f);

static void playerEventCallback(void *clientData, SuperpoweredAdvancedAudioPlayerEvent event, void * __unused value)
{
    SuperpoweredSound *sps = (SuperpoweredSound *)clientData;

    if (event == SuperpoweredAdvancedAudioPlayerEvent_LoadSuccess)
    {
    	sps->getPlayer()->setFirstBeatMs(0);
        sps->getPlayer()->setPosition(sps->getPlayer()->firstBeatMs, false, false);
    }
    else if (event == SuperpoweredAdvancedAudioPlayerEvent_EOF)
    {
        bool *pBoolValue = (bool *)value;
        *pBoolValue = !sps->isLooping();
    }
}

SuperpoweredSound::SuperpoweredSound(const char *path, unsigned int sampleRate, int rawResourceId, int fileOffset, int fileLength, float volume) :
m_path(path),
m_fVolume(volume * headroom),
m_iRawResourceId(-1),
m_iLastSamplerate(sampleRate),
m_isLooping(false)
{
    m_iRawResourceId = rawResourceId;
    
    m_player = new SuperpoweredAdvancedAudioPlayer(this, playerEventCallback, sampleRate, 0);
    
    if (fileOffset > -1 && fileLength > -1)
    {
        m_player->open(m_path, fileOffset, fileLength);
    }
    else
    {
        m_player->open(m_path);
    }
}

SuperpoweredSound::~SuperpoweredSound()
{
    delete m_player;
}

void SuperpoweredSound::play(bool isLooping)
{
    m_isLooping = isLooping;
 
    m_player->seek(0);
    
    m_player->play(false);
}

void SuperpoweredSound::resume()
{
    m_player->play(false);
}

void SuperpoweredSound::pause()
{
    m_player->pause();
}

void SuperpoweredSound::stop()
{
    m_isLooping = false;
    
    pause();
}

void SuperpoweredSound::setVolume(float volume)
{
    m_fVolume = volume * headroom;
}

bool SuperpoweredSound::process(float *stereoBuffer, void *output, unsigned int numberOfSamples, unsigned int sampleRate)
{
    if (m_fVolume <= 0)
    {
        return false;
    }
    
    if (sampleRate != -1
        && sampleRate != m_iLastSamplerate)
    {
        // Has samplerate changed?
        m_iLastSamplerate = sampleRate;
        m_player->setSamplerate(sampleRate);
    }
    
    bool ret = m_player->process(stereoBuffer, false, numberOfSamples, m_fVolume);
    
    // The stereoBuffer is ready now, let's put the finished audio into the requested buffers.
    if (ret)
    {
#if defined TARGET_OS_IPHONE || defined TARGET_OS_OSX
        float **buffers = (float **)output;
        SuperpoweredDeInterleave(stereoBuffer, buffers[0], buffers[1], numberOfSamples); // The stereoBuffer is ready now, let's put the finished audio into the requested buffers.
#elif defined __ANDROID__
        short int *realOutput = (short int *)output;
        SuperpoweredFloatToShortInt(stereoBuffer, realOutput, numberOfSamples);
#endif
    }
    
    return ret;
}
