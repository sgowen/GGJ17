//
//  DummyGpuProgramWrapper.h
//  noctisgames-framework
//
//  Created by Stephen Gowen on 8/27/15.
//  Copyright (c) 2017 Noctis Games. All rights reserved.
//

#ifndef __noctisgames__DummyGpuProgramWrapper__
#define __noctisgames__DummyGpuProgramWrapper__

#include "GpuProgramWrapper.h"

class DummyGpuProgramWrapper : public GpuProgramWrapper
{
public:
    static DummyGpuProgramWrapper * getInstance();
    
    virtual ~DummyGpuProgramWrapper();
    
    virtual void bind();
    
    virtual void unbind();
    
private:
    // ctor, copy ctor, and assignment should be private in a Singleton
    DummyGpuProgramWrapper() {}
    DummyGpuProgramWrapper(const DummyGpuProgramWrapper&);
    DummyGpuProgramWrapper& operator=(const DummyGpuProgramWrapper&);
};

#endif /* defined(__noctisgames__DummyGpuProgramWrapper__) */
