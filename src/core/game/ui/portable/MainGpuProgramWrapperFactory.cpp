//
//  MainGpuProgramWrapperFactory.cpp
//  ggj17
//
//  Created by Stephen Gowen on 1/21/17.
//  Copyright (c) 2017 Noctis Games. All rights reserved.
//

#include "MainGpuProgramWrapperFactory.h"

#ifdef __APPLE__
#include "TargetConditionals.h"
#endif

MainGpuProgramWrapperFactory* MainGpuProgramWrapperFactory::getInstance()
{
    static MainGpuProgramWrapperFactory *instance = new MainGpuProgramWrapperFactory();
    return instance;
}

#if defined TARGET_OS_IPHONE || defined TARGET_OS_OSX || defined __ANDROID__

#include "OpenGLSinWaveTextureGpuProgramWrapper.h"

SinWaveTextureGpuProgramWrapper* MainGpuProgramWrapperFactory::createSinWaveTextureGpuProgramWrapper()
{
    return new OpenGLSinWaveTextureGpuProgramWrapper();
}
#elif defined _WIN32

#include "Direct3DSinWaveTextureGpuProgramWrapper.h"

SinWaveTextureGpuProgramWrapper* MainGpuProgramWrapperFactory::createSinWaveTextureGpuProgramWrapper()
{
    return new Direct3DSinWaveTextureGpuProgramWrapper();
}
#endif
