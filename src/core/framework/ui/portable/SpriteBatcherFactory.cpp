//
//  SpriteBatcherFactory.cpp
//  noctisgames-framework
//
//  Created by Stephen Gowen on 1/14/17.
//  Copyright (c) 2017 Noctis Games. All rights reserved.
//

#include "SpriteBatcherFactory.h"

#ifdef __APPLE__
#include "TargetConditionals.h"
#endif

SpriteBatcherFactory* SpriteBatcherFactory::getInstance()
{
    static SpriteBatcherFactory *instance = new SpriteBatcherFactory();
    return instance;
}

#if defined TARGET_OS_IPHONE || defined TARGET_OS_OSX || defined __ANDROID__
#include "OpenGLSpriteBatcher.h"
SpriteBatcher* SpriteBatcherFactory::createSpriteBatcher() { return new OpenGLSpriteBatcher(); }
#elif defined _WIN32
#include "Direct3DSpriteBatcher.h"
SpriteBatcher* SpriteBatcherFactory::createSpriteBatcher() { return new Direct3DSpriteBatcher(); }
#endif
