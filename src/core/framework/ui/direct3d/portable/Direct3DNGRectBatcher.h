//
//  Direct3DNGRectBatcher.h
//  noctisgames-framework
//
//  Created by Stephen Gowen on 9/22/14.
//  Copyright (c) 2017 Noctis Games. All rights reserved.
//

#ifndef __noctisgames__Direct3DNGRectBatcher__
#define __noctisgames__Direct3DNGRectBatcher__

#include "NGRectBatcher.h"

#include "pch.h"

class NGRect;

class Direct3DNGRectBatcher : public NGRectBatcher
{
public:
	Direct3DNGRectBatcher(bool isFill = false);

	virtual void beginBatch();

	virtual void endBatch(GpuProgramWrapper &gpuProgramWrapper);

	void renderNGRect(NGRect &rectangle, Color &color);

	virtual void renderNGRect(float x1, float y1, float x2, float y2, Color &color);
};

#endif /* defined(__noctisgames__Direct3DNGRectBatcher__) */
