//
//  NGRectBatcherFactory.cpp
//  noctisgames-framework
//
//  Created by Stephen Gowen on 1/14/17.
//  Copyright (c) 2017 Noctis Games. All rights reserved.
//

#include "NGRectBatcherFactory.h"

#ifdef __APPLE__
#include "TargetConditionals.h"
#endif

NGRectBatcherFactory* NGRectBatcherFactory::getInstance()
{
    static NGRectBatcherFactory *instance = new NGRectBatcherFactory();
    return instance;
}

#if defined TARGET_OS_IPHONE || defined TARGET_OS_OSX || defined __ANDROID__
#include "OpenGLNGRectBatcher.h"
NGRectBatcher* NGRectBatcherFactory::createNGRectBatcher(bool isFill) { return new OpenGLNGRectBatcher(isFill); }
#elif defined _WIN32
#include "Direct3DNGRectBatcher.h"
NGRectBatcher* NGRectBatcherFactory::createNGRectBatcher(bool isFill) { return new Direct3DNGRectBatcher(isFill); }
#endif
