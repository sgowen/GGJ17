//
//  LineBatcher.h
//  noctisgames-framework
//
//  Created by Stephen Gowen on 11/15/14.
//  Copyright (c) 2017 Noctis Games. All rights reserved.
//

#ifndef __noctisgames__LineBatcher__
#define __noctisgames__LineBatcher__

#include "Color.h"

class Line;
class GpuProgramWrapper;

class LineBatcher
{
public:
    LineBatcher();
    
    virtual ~LineBatcher() {}
    
    virtual void beginBatch() = 0;
    
    virtual void endBatch(GpuProgramWrapper &gpuProgramWrapper) = 0;
    
    virtual void renderLine(float originX, float originY, float endX, float endY, Color &c) = 0;
    
    void renderLine(Line &line, Color &c);
    
protected:
    int m_iNumLines;
};

#endif /* defined(__noctisgames__LineBatcher__) */
