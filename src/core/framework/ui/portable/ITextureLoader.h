//
//  ITextureLoader.h
//  noctisgames-framework
//
//  Created by Stephen Gowen on 1/15/17.
//  Copyright © 2017 Noctis Games. All rights reserved.
//

#ifndef __noctisgames__ITextureLoader__
#define __noctisgames__ITextureLoader__

struct GpuTextureDataWrapper;
struct GpuTextureWrapper;

class ITextureLoader
{
public:
    ITextureLoader() {}
    
    virtual ~ITextureLoader() {}
    
    virtual GpuTextureDataWrapper* loadTextureData(const char* textureName) = 0;
    
    virtual GpuTextureWrapper* loadTexture(GpuTextureDataWrapper* textureData, int repeatS = 0) = 0;
};

#endif /* defined(__noctisgames__ITextureLoader__) */
