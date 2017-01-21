//
//  DummyGpuProgramWrapper.cpp
//  noctisgames-framework
//
//  Created by Stephen Gowen on 8/27/15.
//  Copyright (c) 2017 Noctis Games. All rights reserved.
//

#include "DummyGpuProgramWrapper.h"

DummyGpuProgramWrapper * DummyGpuProgramWrapper::getInstance()
{
    static DummyGpuProgramWrapper *instance = new DummyGpuProgramWrapper();
    return instance;
}

DummyGpuProgramWrapper::~DummyGpuProgramWrapper()
{
    // Empty
}

void DummyGpuProgramWrapper::bind()
{
    // Empty
}

void DummyGpuProgramWrapper::unbind()
{
    // Empty
}
