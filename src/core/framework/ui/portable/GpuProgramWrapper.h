//
//  GpuProgramWrapper.h
//  noctisgames-framework
//
//  Created by Stephen Gowen on 8/27/15.
//  Copyright (c) 2017 Noctis Games. All rights reserved.
//

#ifndef __noctisgames__GpuProgramWrapper__
#define __noctisgames__GpuProgramWrapper__

class GpuProgramWrapper
{
public:
    GpuProgramWrapper();
    
    virtual ~GpuProgramWrapper();
    
    virtual void bind() = 0;
    
    virtual void unbind() = 0;

	bool isLoaded();

protected:
	bool m_isLoaded;
};

#endif /* defined(__noctisgames__GpuProgramWrapper__) */
