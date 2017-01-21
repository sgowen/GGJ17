//
//  CircleBatcher.h
//  noctisgames-framework
//
//  Created by Stephen Gowen on 11/15/14.
//  Copyright (c) 2017 Noctis Games. All rights reserved.
//

#ifndef __noctisgames__CircleBatcher__
#define __noctisgames__CircleBatcher__

#include "Color.h"

class Circle;
class GpuProgramWrapper;

class CircleBatcher
{
public:
    CircleBatcher();
    
    virtual ~CircleBatcher() {}
    
    virtual void renderCircle(Circle &circle, Color &c, GpuProgramWrapper &gpuProgramWrapper) = 0;
    
    virtual void renderPartialCircle(Circle &circle, int arcDegrees, Color &c, GpuProgramWrapper &gpuProgramWrapper) = 0;
    
protected:
    int m_iNumPoints;
    
    virtual void endBatch(GpuProgramWrapper &gpuProgramWrapper) = 0;
};

#endif /* defined(__noctisgames__CircleBatcher__) */
