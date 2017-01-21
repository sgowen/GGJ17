//
//  IDeviceHelper.h
//  noctisgames-framework
//
//  Created by Stephen Gowen on 1/15/17.
//  Copyright © 2017 Noctis Games. All rights reserved.
//

#ifndef __noctisgames__IDeviceHelper__
#define __noctisgames__IDeviceHelper__

class IDeviceHelper
{
public:
    IDeviceHelper() {}
    
    virtual ~IDeviceHelper() {}
    
    virtual void createDeviceDependentResources(int maxBatchSize) = 0;
    
    virtual void createWindowSizeDependentResources(int screenWidth, int screenHeight, int numFramebuffers) = 0;
    
    virtual void releaseDeviceDependentResources() = 0;
};

#endif /* defined(__noctisgames__IDeviceHelper__) */
