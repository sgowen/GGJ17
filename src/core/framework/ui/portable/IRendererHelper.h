//
//  IRendererHelper.h
//  noctisgames-framework
//
//  Created by Stephen Gowen on 1/15/17.
//  Copyright © 2017 Noctis Games. All rights reserved.
//

#ifndef __noctisgames__IRendererHelper__
#define __noctisgames__IRendererHelper__

struct GpuTextureWrapper;

class IRendererHelper
{
public:
    IRendererHelper() {}
    
    virtual ~IRendererHelper() {}
    
    virtual void beginFrame() = 0;
    
    virtual void endFrame() = 0;
    
    virtual GpuTextureWrapper getFramebuffer(int index) = 0;
    
    virtual void updateMatrix(float left, float right, float bottom, float top) = 0;
    
    virtual void bindToOffscreenFramebuffer(int index) = 0;
    
    virtual void clearFramebufferWithColor(float r, float g, float b, float a) = 0;
    
    virtual void bindToScreenFramebuffer() = 0;
    
    virtual void destroyTexture(GpuTextureWrapper& textureWrapper) = 0;
};

#endif /* defined(__noctisgames__IRendererHelper__) */
