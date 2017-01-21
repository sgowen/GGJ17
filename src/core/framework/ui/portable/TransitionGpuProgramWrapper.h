//
//  TransitionGpuProgramWrapper.h
//  noctisgames-framework
//
//  Created by Stephen Gowen on 1/27/16.
//  Copyright (c) 2017 Noctis Games. All rights reserved.
//

#ifndef __noctisgames__TransitionGpuProgramWrapper__
#define __noctisgames__TransitionGpuProgramWrapper__

#include "GpuProgramWrapper.h"

#include "GpuTextureWrapper.h"

class TransitionGpuProgramWrapper : public GpuProgramWrapper
{
public:
    TransitionGpuProgramWrapper();
    
    void configure(GpuTextureWrapper* to, float progress);
    
protected:
    GpuTextureWrapper* m_to;
    float m_fProgress;
};

#endif /* defined(__noctisgames__TransitionGpuProgramWrapper__) */
