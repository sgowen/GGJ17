//
//  CircleBatcherFactory.cpp
//  noctisgames-framework
//
//  Created by Stephen Gowen on 1/14/17.
//  Copyright (c) 2017 Noctis Games. All rights reserved.
//

#include "CircleBatcherFactory.h"

#ifdef __APPLE__
#include "TargetConditionals.h"
#endif

CircleBatcherFactory* CircleBatcherFactory::getInstance()
{
    static CircleBatcherFactory *instance = new CircleBatcherFactory();
    return instance;
}

#if defined TARGET_OS_IPHONE || defined TARGET_OS_OSX || defined __ANDROID__
#include "OpenGLCircleBatcher.h"
CircleBatcher* CircleBatcherFactory::createCircleBatcher() { return new OpenGLCircleBatcher(); }
#elif defined _WIN32
#include "Direct3DCircleBatcher.h"
CircleBatcher* CircleBatcherFactory::createCircleBatcher() { return new Direct3DCircleBatcher(); }
#endif
