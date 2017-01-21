//
//  SpriteBatcher.h
//  noctisgames-framework
//
//  Created by Stephen Gowen on 9/25/14.
//  Copyright (c) 2017 Noctis Games. All rights reserved.
//

#ifndef __noctisgames__SpriteBatcher__
#define __noctisgames__SpriteBatcher__

#include "Color.h"
#include "GpuTextureWrapper.h"

class TextureRegion;
class GpuProgramWrapper;

class SpriteBatcher
{
public:
    SpriteBatcher();
    
    virtual ~SpriteBatcher() {}

    virtual void beginBatch() = 0;

    virtual void endBatch(GpuTextureWrapper textureWrapper, GpuProgramWrapper &gpuProgramWrapper) = 0;

    virtual void drawSprite(float x, float y, float width, float height, float angle, TextureRegion tr) = 0;

    virtual void drawSprite(float x, float y, float width, float height, float angle, Color &c, TextureRegion tr) = 0;

protected:
    int m_iNumSprites;

    virtual void drawSprite(float x, float y, float width, float height, TextureRegion tr) = 0;

    virtual void drawSprite(float x, float y, float width, float height, Color &c, TextureRegion tr) = 0;
};

#endif /* defined(__noctisgames__SpriteBatcher__) */
