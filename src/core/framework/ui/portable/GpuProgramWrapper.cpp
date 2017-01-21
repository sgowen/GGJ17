//
//  GpuProgramWrapper.cpp
//  noctisgames-framework
//
//  Created by Stephen Gowen on 8/27/15.
//  Copyright (c) 2017 Noctis Games. All rights reserved.
//

#include "GpuProgramWrapper.h"

GpuProgramWrapper::GpuProgramWrapper() : m_isLoaded(false)
{
    // Empty
}

GpuProgramWrapper::~GpuProgramWrapper()
{
    // Override
}

bool GpuProgramWrapper::isLoaded()
{
	return m_isLoaded;
}
