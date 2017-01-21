//
//  TransitionGpuProgramWrapper.cpp
//  noctisgames-framework
//
//  Created by Stephen Gowen on 1/27/16.
//  Copyright (c) 2017 Noctis Games. All rights reserved.
//

#include "TransitionGpuProgramWrapper.h"

TransitionGpuProgramWrapper::TransitionGpuProgramWrapper() : m_to(nullptr), m_fProgress(0)
{
    // Empty
}

void TransitionGpuProgramWrapper::configure(GpuTextureWrapper* to, float progress)
{
    m_to = to;
    m_fProgress = progress;
}
