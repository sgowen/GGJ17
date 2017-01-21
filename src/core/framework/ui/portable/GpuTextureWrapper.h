//
//  GpuTextureWrapper.h
//  noctisgames-framework
//
//  Created by Stephen Gowen on 9/25/14.
//  Copyright (c) 2017 Noctis Games. All rights reserved.
//

#ifndef __noctisgames__GpuTextureWrapper__
#define __noctisgames__GpuTextureWrapper__

#ifdef __APPLE__
#include "TargetConditionals.h"
#endif

#if defined TARGET_OS_IPHONE || defined TARGET_OS_OSX || defined __ANDROID__
extern "C"
{
#include "platform_gl.h"
}
#elif defined _WIN32
#include <d3d11_1.h>
#endif

struct GpuTextureWrapper
{
#if defined TARGET_OS_IPHONE || defined TARGET_OS_OSX || defined __ANDROID__
    GLuint texture;
    
    GpuTextureWrapper(GLuint textureIn) : texture(textureIn)
    {
        // Empty
    }
#elif defined _WIN32
    ID3D11ShaderResourceView *texture;
    
    GpuTextureWrapper(ID3D11ShaderResourceView *textureIn) : texture(textureIn)
    {
        // Empty
    }
#endif
};

#endif /* defined(__noctisgames__GpuTextureWrapper__) */
