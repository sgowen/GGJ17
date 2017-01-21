//
//  OpenGLSpriteBatcher.h
//  noctisgames-framework
//
//  Created by Stephen Gowen on 2/22/14.
//  Copyright (c) 2017 Noctis Games. All rights reserved.
//

#ifndef __noctisgames__OpenGLSpriteBatcher__
#define __noctisgames__OpenGLSpriteBatcher__

#include "SpriteBatcher.h"

class OpenGLSpriteBatcher : public SpriteBatcher
{
public:
    OpenGLSpriteBatcher();
    
    virtual void beginBatch();
    
    virtual void endBatch(GpuTextureWrapper textureWrapper, GpuProgramWrapper &gpuProgramWrapper);
    
    virtual void drawSprite(float x, float y, float width, float height, float angle, TextureRegion tr);
    
    virtual void drawSprite(float x, float y, float width, float height, float angle, Color &c, TextureRegion tr);
    
protected:
    virtual void drawSprite(float x, float y, float width, float height, TextureRegion tr);
    
    virtual void drawSprite(float x, float y, float width, float height, Color &c, TextureRegion tr);
};

#endif /* defined(__noctisgames__OpenGLSpriteBatcher__) */
