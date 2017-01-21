//
//  SpriteBatcherFactory.h
//  noctisgames-framework
//
//  Created by Stephen Gowen on 1/14/17.
//  Copyright (c) 2017 Noctis Games. All rights reserved.
//

#ifndef __noctisgames__SpriteBatcherFactory__
#define __noctisgames__SpriteBatcherFactory__

class SpriteBatcher;

#define SPRITE_BATCHER_FACTORY (SpriteBatcherFactory::getInstance())

class SpriteBatcherFactory
{
public:
	static SpriteBatcherFactory* getInstance();
    
    SpriteBatcher* createSpriteBatcher();

private:
    // ctor, copy ctor, and assignment should be private in a Singleton
    SpriteBatcherFactory() {}
    SpriteBatcherFactory(const SpriteBatcherFactory&);
    SpriteBatcherFactory& operator=(const SpriteBatcherFactory&);
};

#endif /* defined(__noctisgames__SpriteBatcherFactory__) */
