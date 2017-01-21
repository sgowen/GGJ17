//
//  RendererHelperFactory.h
//  noctisgames-framework
//
//  Created by Stephen Gowen on 1/15/17.
//  Copyright (c) 2017 Noctis Games. All rights reserved.
//

#ifndef __noctisgames__RendererHelperFactory__
#define __noctisgames__RendererHelperFactory__

class IRendererHelper;

#define RENDERER_HELPER_FACTORY (RendererHelperFactory::getInstance())

class RendererHelperFactory
{
public:
	static RendererHelperFactory* getInstance();
    
    IRendererHelper* createRendererHelper();

private:
    // ctor, copy ctor, and assignment should be private in a Singleton
    RendererHelperFactory() {}
    RendererHelperFactory(const RendererHelperFactory&);
    RendererHelperFactory& operator=(const RendererHelperFactory&);
};

#endif /* defined(__noctisgames__RendererHelperFactory__) */
