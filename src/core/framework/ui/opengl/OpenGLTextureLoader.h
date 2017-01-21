//
//  OpenGLTextureLoader.h
//  noctisgames-framework
//
//  Created by Stephen Gowen on 1/15/17.
//  Copyright (c) 2017 Noctis Games. All rights reserved.
//

#ifndef __noctisgames__OpenGLTextureLoader__
#define __noctisgames__OpenGLTextureLoader__

#include "ITextureLoader.h"

class OpenGLTextureLoader : public ITextureLoader
{
public:
    OpenGLTextureLoader();
    
    virtual ~OpenGLTextureLoader() {}
    
    virtual GpuTextureDataWrapper* loadTextureData(const char* textureName);
    
    virtual GpuTextureWrapper* loadTexture(GpuTextureDataWrapper* textureData, int repeatS = 0);
};

#endif /* defined(__noctisgames__OpenGLTextureLoader__) */
