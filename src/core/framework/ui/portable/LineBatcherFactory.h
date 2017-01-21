//
//  LineBatcherFactory.h
//  noctisgames-framework
//
//  Created by Stephen Gowen on 1/14/17.
//  Copyright (c) 2017 Noctis Games. All rights reserved.
//

#ifndef __noctisgames__LineBatcherFactory__
#define __noctisgames__LineBatcherFactory__

class LineBatcher;

#define LINE_BATCHER_FACTORY (LineBatcherFactory::getInstance())

class LineBatcherFactory
{
public:
	static LineBatcherFactory* getInstance();
    
    LineBatcher* createLineBatcher();

private:
    // ctor, copy ctor, and assignment should be private in a Singleton
    LineBatcherFactory() {}
    LineBatcherFactory(const LineBatcherFactory&);
    LineBatcherFactory& operator=(const LineBatcherFactory&);
};

#endif /* defined(__noctisgames__LineBatcherFactory__) */
