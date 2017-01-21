//
//  TextureLoaderFactory.h
//  noctisgames-framework
//
//  Created by Stephen Gowen on 1/15/17.
//  Copyright (c) 2017 Noctis Games. All rights reserved.
//

#ifndef __noctisgames__TextureLoaderFactory__
#define __noctisgames__TextureLoaderFactory__

class ITextureLoader;

#define TEXTURE_LOADER_FACTORY (TextureLoaderFactory::getInstance())

class TextureLoaderFactory
{
public:
	static TextureLoaderFactory* getInstance();
    
    ITextureLoader* createTextureLoader();

private:
    // ctor, copy ctor, and assignment should be private in a Singleton
    TextureLoaderFactory() {}
    TextureLoaderFactory(const TextureLoaderFactory&);
    TextureLoaderFactory& operator=(const TextureLoaderFactory&);
};

#endif /* defined(__noctisgames__TextureLoaderFactory__) */
