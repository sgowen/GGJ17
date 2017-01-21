//
//  CircleBatcherFactory.h
//  noctisgames-framework
//
//  Created by Stephen Gowen on 1/14/17.
//  Copyright (c) 2017 Noctis Games. All rights reserved.
//

#ifndef __noctisgames__CircleBatcherFactory__
#define __noctisgames__CircleBatcherFactory__

class CircleBatcher;

#define CIRCLE_BATCHER_FACTORY (CircleBatcherFactory::getInstance())

class CircleBatcherFactory
{
public:
	static CircleBatcherFactory* getInstance();
    
    CircleBatcher* createCircleBatcher();

private:
    // ctor, copy ctor, and assignment should be private in a Singleton
    CircleBatcherFactory() {}
    CircleBatcherFactory(const CircleBatcherFactory&);
    CircleBatcherFactory& operator=(const CircleBatcherFactory&);
};

#endif /* defined(__noctisgames__CircleBatcherFactory__) */
