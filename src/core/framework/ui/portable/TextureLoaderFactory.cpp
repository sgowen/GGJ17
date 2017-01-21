//
//  TextureLoaderFactory.cpp
//  noctisgames-framework
//
//  Created by Stephen Gowen on 1/15/17.
//  Copyright (c) 2017 Noctis Games. All rights reserved.
//

#include "TextureLoaderFactory.h"

#ifdef __APPLE__
#include "TargetConditionals.h"
#endif

TextureLoaderFactory* TextureLoaderFactory::getInstance()
{
    static TextureLoaderFactory *instance = new TextureLoaderFactory();
    return instance;
}

#if defined TARGET_OS_IPHONE || defined TARGET_OS_OSX || defined __ANDROID__
#include "OpenGLTextureLoader.h"
ITextureLoader* TextureLoaderFactory::createTextureLoader() { return new OpenGLTextureLoader(); }
#elif defined _WIN32
#include "Direct3DTextureLoader.h"
ITextureLoader* TextureLoaderFactory::createTextureLoader() { return new Direct3DTextureLoader(); }
#endif
