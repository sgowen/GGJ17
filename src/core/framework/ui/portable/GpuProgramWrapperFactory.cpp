//
//  GpuProgramWrapperFactory.cpp
//  noctisgames-framework
//
//  Created by Stephen Gowen on 1/15/17.
//  Copyright (c) 2017 Noctis Games. All rights reserved.
//

#include "GpuProgramWrapperFactory.h"

#ifdef __APPLE__
#include "TargetConditionals.h"
#endif

GpuProgramWrapperFactory* GpuProgramWrapperFactory::getInstance()
{
    static GpuProgramWrapperFactory *instance = new GpuProgramWrapperFactory();
    return instance;
}

#if defined TARGET_OS_IPHONE || defined TARGET_OS_OSX || defined __ANDROID__

#include "OpenGLTextureGpuProgramWrapper.h"
#include "OpenGLGeometryGpuProgramWrapper.h"
#include "OpenGLFramebufferToScreenGpuProgramWrapper.h"

GpuProgramWrapper* GpuProgramWrapperFactory::createTextureGpuProgramWrapper()
{
    return new OpenGLTextureGpuProgramWrapper();
}

GpuProgramWrapper* GpuProgramWrapperFactory::createColorGpuProgramWrapper()
{
    return new OpenGLGeometryGpuProgramWrapper();
}

GpuProgramWrapper* GpuProgramWrapperFactory::createFramebufferToScreenGpuProgramWrapper()
{
    return new OpenGLFramebufferToScreenGpuProgramWrapper();
}
#elif defined _WIN32

#include "Direct3DTextureGpuProgramWrapper.h"
#include "Direct3DGeometryGpuProgramWrapper.h"
#include "Direct3DFramebufferToScreenGpuProgramWrapper.h"

GpuProgramWrapper* GpuProgramWrapperFactory::createTextureGpuProgramWrapper()
{
    return new Direct3DTextureGpuProgramWrapper();
}

GpuProgramWrapper* GpuProgramWrapperFactory::createColorGpuProgramWrapper()
{
    return new Direct3DGeometryGpuProgramWrapper();
}

GpuProgramWrapper* GpuProgramWrapperFactory::createFramebufferToScreenGpuProgramWrapper()
{
    return new Direct3DFramebufferToScreenGpuProgramWrapper();
}
#endif
