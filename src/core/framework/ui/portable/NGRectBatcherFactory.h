//
//  NGRectBatcherFactory.h
//  noctisgames-framework
//
//  Created by Stephen Gowen on 1/14/17.
//  Copyright (c) 2017 Noctis Games. All rights reserved.
//

#ifndef __noctisgames__NGRectBatcherFactory__
#define __noctisgames__NGRectBatcherFactory__

class NGRectBatcher;

#define RECTANGLE_BATCHER_FACTORY (NGRectBatcherFactory::getInstance())

class NGRectBatcherFactory
{
public:
	static NGRectBatcherFactory* getInstance();
    
    NGRectBatcher* createNGRectBatcher(bool isFill = false);

private:
    // ctor, copy ctor, and assignment should be private in a Singleton
    NGRectBatcherFactory() {}
    NGRectBatcherFactory(const NGRectBatcherFactory&);
    NGRectBatcherFactory& operator=(const NGRectBatcherFactory&);
};

#endif /* defined(__noctisgames__NGRectBatcherFactory__) */
