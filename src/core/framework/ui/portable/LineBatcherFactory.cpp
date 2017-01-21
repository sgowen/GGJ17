//
//  LineBatcherFactory.cpp
//  noctisgames-framework
//
//  Created by Stephen Gowen on 1/14/17.
//  Copyright (c) 2017 Noctis Games. All rights reserved.
//

#include "LineBatcherFactory.h"

#ifdef __APPLE__
#include "TargetConditionals.h"
#endif

LineBatcherFactory* LineBatcherFactory::getInstance()
{
    static LineBatcherFactory *instance = new LineBatcherFactory();
    return instance;
}

#if defined TARGET_OS_IPHONE || defined TARGET_OS_OSX || defined __ANDROID__
#include "OpenGLLineBatcher.h"
LineBatcher* LineBatcherFactory::createLineBatcher() { return new OpenGLLineBatcher(); }
#elif defined _WIN32
#include "Direct3DLineBatcher.h"
LineBatcher* LineBatcherFactory::createLineBatcher() { return new Direct3DLineBatcher(); }
#endif
