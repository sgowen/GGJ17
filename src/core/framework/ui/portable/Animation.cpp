//
//  Animation.cpp
//  noctisgames-framework
//
//  Created by Stephen Gowen on 9/3/15.
//  Copyright (c) 2017 Noctis Games. All rights reserved.
//

#include "Animation.h"
#include "TextureRegion.h"
#include <stdarg.h>

Animation::Animation(std::string textureName, int x, int y, int regionWidth, int regionHeight, int animationWidth, int animationHeight, int textureWidth, int textureHeight, bool looping, int numFrames) : m_textureName(textureName), m_fCycleTime(0), m_iFirstLoopingFrame(0), m_looping(looping)
{
	loadTextureRegions(x, y, regionWidth, regionHeight, animationWidth, animationHeight, textureWidth, textureHeight, numFrames);
}

Animation::Animation(std::string textureName, int x, int y, int regionWidth, int regionHeight, int animationWidth, int animationHeight, int textureWidth, int textureHeight, bool looping, float frameTime, int numFrames, int firstLoopingFrame, int xPadding, int yPadding) : m_textureName(textureName), m_fCycleTime(0), m_iFirstLoopingFrame(firstLoopingFrame), m_looping(looping)
{
	loadTextureRegions(x, y, regionWidth, regionHeight, animationWidth, animationHeight, textureWidth, textureHeight, numFrames, xPadding, yPadding);

	for (int i = 0; i < numFrames; i++)
	{
		m_frameTimes.push_back(frameTime);
		m_fCycleTime += frameTime;
	}
}

Animation::~Animation()
{
    m_textureRegions.clear();
    m_frameTimes.clear();
}

void Animation::setFrameTimes(int numFrames, ...)
{
    va_list arguments;
    
    va_start(arguments, numFrames);
    
    for (int i = 0; i < numFrames; i++)
    {
        float f = va_arg(arguments, double);
        m_frameTimes.push_back(f);
        m_fCycleTime += f;
    }
    
    va_end(arguments);
}

TextureRegion& Animation::getTextureRegion(float stateTime)
{
	int keyFrameNumber = getKeyFrameNumber(stateTime);

	return getTextureRegion(keyFrameNumber);
}

TextureRegion& Animation::getTextureRegion(int keyFrameNumber)
{
	return m_textureRegions.at(keyFrameNumber);
}

int Animation::getKeyFrameNumber(float stateTime)
{
    unsigned int i = 0;
    
    if (stateTime > m_fCycleTime && m_fCycleTime > 0)
    {
        if (m_looping)
        {
            float cycleTime = m_fCycleTime;
            for ( ; i < m_iFirstLoopingFrame; i++)
            {
                cycleTime -= m_frameTimes.at(i);
            }
            
            while (stateTime > cycleTime)
            {
                stateTime -= cycleTime;
            }
        }
        else
        {
            return ((int) m_frameTimes.size()) - 1;
        }
    }
    
    for ( ; i < m_frameTimes.size(); i++)
    {
        float frameTime = m_frameTimes.at(i);
        
        if (stateTime < frameTime)
        {
            return i;
        }
        
        stateTime -= frameTime;
    }
    
    return 0;
}

bool Animation::hasFrameTimes()
{
    return m_frameTimes.size() > 0;
}

void Animation::loadTextureRegions(int x, int y, int regionWidth, int regionHeight, int animationWidth, int animationHeight, int textureWidth, int textureHeight, int numFrames, int xPadding, int yPadding)
{
	int right = x + animationWidth;
	int bottom = y + animationHeight;
	int numTextureRegionsAdded = 0;
	for (int j = y; j < bottom; j += regionHeight + yPadding)
	{
		for (int i = x; i < right; i += regionWidth + xPadding)
		{
			TextureRegion tr = TextureRegion(m_textureName, i, j, regionWidth, regionHeight, textureWidth, textureHeight);
			m_textureRegions.push_back(tr);
			numTextureRegionsAdded++;

			if (numTextureRegionsAdded == numFrames)
			{
				return;
			}
		}
	}
}
