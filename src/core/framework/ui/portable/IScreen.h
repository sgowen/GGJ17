//
//  IScreen.h
//  noctisgames-framework
//
//  Created by Stephen Gowen on 1/15/17.
//  Copyright (c) 2017 Noctis Games. All rights reserved.
//

#ifndef __noctisgames__IScreen__
#define __noctisgames__IScreen__

#include "RTTI.h"

class IScreen
{
    RTTI_DECL;
    
public:
    IScreen();
    
    virtual ~IScreen();
    
    virtual void createDeviceDependentResources() = 0;
    
    virtual void createWindowSizeDependentResources(int screenWidth, int screenHeight, int touchScreenWidth, int touchScreenHeight) = 0;
    
    virtual void releaseDeviceDependentResources() = 0;
    
    virtual void onResume() = 0;
	
    virtual void onPause() = 0;
    
    virtual void update(float deltaTime) = 0;
    
    virtual void render() = 0;
};

#endif /* defined(__noctisgames__IScreen__) */
