//
//  OpenGLNGRectBatcher.h
//  noctisgames-framework
//
//  Created by Stephen Gowen on 7/15/14.
//  Copyright (c) 2017 Noctis Games. All rights reserved.
//

#ifndef __noctisgames__OpenGLNGRectBatcher__
#define __noctisgames__OpenGLNGRectBatcher__

#include "NGRectBatcher.h"
#include "OpenGLManager.h"

class OpenGLNGRectBatcher : public NGRectBatcher
{
public:
    OpenGLNGRectBatcher(bool isFill = false);
    
    virtual void beginBatch();
    
    virtual void endBatch(GpuProgramWrapper &gpuProgramWrapper);
    
    virtual void renderNGRect(float x1, float y1, float x2, float y2, Color &color);
};

#endif /* defined(__noctisgames__OpenGLNGRectBatcher__) */
