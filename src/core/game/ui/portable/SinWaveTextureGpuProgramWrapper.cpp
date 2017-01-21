//
//  SinWaveTextureGpuProgramWrapper.cpp
//  ggj17
//
//  Created by Stephen Gowen on 1/21/17.
//  Copyright © 2017 Noctis Games. All rights reserved.
//

#include "SinWaveTextureGpuProgramWrapper.h"

SinWaveTextureGpuProgramWrapper::SinWaveTextureGpuProgramWrapper() : m_fOffset(0.0f)
{
    // Empty
}

void SinWaveTextureGpuProgramWrapper::setOffset(float offset)
{
    m_fOffset = offset;
}
