//
//  Direct3DRendererHelper.h
//  noctisgames-framework
//
//  Created by Stephen Gowen on 1/15/17.
//  Copyright (c) 2017 Noctis Games. All rights reserved.
//

#ifndef __noctisgames__Direct3DRendererHelper__
#define __noctisgames__Direct3DRendererHelper__

#include "IRendererHelper.h"

class Direct3DRendererHelper : public IRendererHelper
{
public:
    Direct3DRendererHelper();
    
    virtual ~Direct3DRendererHelper();
    
    virtual void beginFrame();
    
    virtual void endFrame();
    
    virtual GpuTextureWrapper getFramebuffer(int index);
    
    virtual void updateMatrix(float left, float right, float bottom, float top);
    
    virtual void bindToOffscreenFramebuffer(int index);
    
    virtual void clearFramebufferWithColor(float r, float g, float b, float a);
    
    virtual void bindToScreenFramebuffer();
    
    virtual void destroyTexture(GpuTextureWrapper& textureWrapper);
    
private:
	int m_iFramebufferIndex;
    bool m_isBoundToScreen;
};

#endif /* defined(__noctisgames__Direct3DRendererHelper__) */
