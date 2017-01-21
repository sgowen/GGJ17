//
//  RendererHelperFactory.cpp
//  noctisgames-framework
//
//  Created by Stephen Gowen on 1/15/17.
//  Copyright (c) 2017 Noctis Games. All rights reserved.
//

#include "RendererHelperFactory.h"

#ifdef __APPLE__
#include "TargetConditionals.h"
#endif

RendererHelperFactory* RendererHelperFactory::getInstance()
{
    static RendererHelperFactory *instance = new RendererHelperFactory();
    return instance;
}

#if defined TARGET_OS_IPHONE || defined TARGET_OS_OSX || defined __ANDROID__
#include "OpenGLRendererHelper.h"
IRendererHelper* RendererHelperFactory::createRendererHelper()
{
    return new OpenGLRendererHelper();
}
#elif defined _WIN32
#include "Direct3DRendererHelper.h"
IRendererHelper* RendererHelperFactory::createRendererHelper() { return new Direct3DRendererHelper(); }
#endif
