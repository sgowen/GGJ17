//
//  MainScreen.h
//  ggj17
//
//  Created by Stephen Gowen on 2/22/14.
//  Copyright (c) 2017 Noctis Games. All rights reserved.
//

#ifndef __ggj17__MainScreen__
#define __ggj17__MainScreen__

#include "IScreen.h"

#include "RTTI.h"

class MainRenderer;
class IDeviceHelper;

class MainScreen : public IScreen
{
    RTTI_DECL;
    
public:
    MainScreen();
    
    virtual ~MainScreen();
    
    virtual void createDeviceDependentResources();
    
    virtual void createWindowSizeDependentResources(int screenWidth, int screenHeight, int touchScreenWidth, int touchScreenHeight);
    
    virtual void releaseDeviceDependentResources();
    
    virtual void onResume();
    
    virtual void onPause();
    
    virtual void update(float deltaTime);
    
    virtual void render();

private:
	IDeviceHelper* m_deviceHelper;
    MainRenderer* m_renderer;
    float m_fStateTime;
    int m_iRequestedUiAction;
};

#endif /* defined(__ggj17__MainScreen__) */
