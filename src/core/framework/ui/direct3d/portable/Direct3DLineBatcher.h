//
//  Direct3DLineBatcher.h
//  noctisgames-framework
//
//  Created by Stephen Gowen on 11/16/14.
//  Copyright (c) 2017 Noctis Games. All rights reserved.
//

#ifndef __noctisgames__Direct3DLineBatcher__
#define __noctisgames__Direct3DLineBatcher__

#include "LineBatcher.h"

#include "pch.h"

class Direct3DLineBatcher : public LineBatcher
{
public:
	Direct3DLineBatcher();
    
    virtual void beginBatch();

	virtual void endBatch(GpuProgramWrapper &gpuProgramWrapper);
    
    virtual void renderLine(float originX, float originY, float endX, float endY, Color &color);
};

#endif /* defined(__noctisgames__Direct3DLineBatcher__) */
