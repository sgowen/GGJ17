//
//  Direct3DDeviceHelper.h
//  noctisgames-framework
//
//  Created by Stephen Gowen on 1/15/17.
//  Copyright (c) 2017 Noctis Games. All rights reserved.
//

#ifndef __noctisgames__Direct3DDeviceHelper__
#define __noctisgames__Direct3DDeviceHelper__

#include "IDeviceHelper.h"

class Direct3DDeviceHelper : public IDeviceHelper
{
public:
    Direct3DDeviceHelper();
    
	virtual ~Direct3DDeviceHelper();
    
    virtual void createDeviceDependentResources(int maxBatchSize);
    
    virtual void createWindowSizeDependentResources(int screenWidth, int screenHeight, int numFramebuffers);
    
    virtual void releaseDeviceDependentResources();
};

#endif /* defined(__noctisgames__Direct3DDeviceHelper__) */
