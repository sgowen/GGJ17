//
//  Direct3DCircleBatcher.h
//  noctisgames-framework
//
//  Created by Stephen Gowen on 11/16/14.
//  Copyright (c) 2017 Noctis Games. All rights reserved.
//

#ifndef __noctisgames__Direct3DCircleBatcher__
#define __noctisgames__Direct3DCircleBatcher__

#include "CircleBatcher.h"

#include "pch.h"

class Direct3DCircleBatcher : public CircleBatcher
{
public:
	Direct3DCircleBatcher();

	virtual void renderCircle(Circle &circle, Color &c, GpuProgramWrapper &gpuProgramWrapper);

	virtual void renderPartialCircle(Circle &circle, int arcDegrees, Color &c, GpuProgramWrapper &gpuProgramWrapper);

protected:
	virtual void endBatch(GpuProgramWrapper &gpuProgramWrapper);

private:
	void addVertexCoordinate(float x, float y, float z, float r, float g, float b, float a);
};

#endif /* defined(__noctisgames__Direct3DCircleBatcher__) */
