//
//  OpenGLLineBatcher.h
//  noctisgames-framework
//
//  Created by Stephen Gowen on 11/15/14.
//  Copyright (c) 2017 Noctis Games. All rights reserved.
//

#ifndef __noctisgames__OpenGLLineBatcher__
#define __noctisgames__OpenGLLineBatcher__

#include "LineBatcher.h"

class OpenGLLineBatcher : public LineBatcher
{
public:
    OpenGLLineBatcher();
    
    virtual ~OpenGLLineBatcher() {}
    
    virtual void beginBatch();
    
    virtual void endBatch(GpuProgramWrapper &gpuProgramWrapper);
    
    virtual void renderLine(float originX, float originY, float endX, float endY, Color &c);
};

#endif /* defined(__noctisgames__OpenGLLineBatcher__) */
