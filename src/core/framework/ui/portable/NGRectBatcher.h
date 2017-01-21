//
//  NGRectBatcher.h
//  noctisgames-framework
//
//  Created by Stephen Gowen on 9/25/14.
//  Copyright (c) 2017 Noctis Games. All rights reserved.
//

#ifndef __noctisgames__NGRectBatcher__
#define __noctisgames__NGRectBatcher__

#include "Color.h"

class GpuProgramWrapper;
class NGRect;

class NGRectBatcher
{
public:
    NGRectBatcher(bool isFill = false);
    
    virtual ~NGRectBatcher() {}
    
    virtual void beginBatch() = 0;
    
    virtual void endBatch(GpuProgramWrapper &gpuProgramWrapper) = 0;
    
    virtual void renderNGRect(float leftX, float bottomY, float rightX, float topY, Color &color) = 0;
    
    void renderNGRect(NGRect &rectangle, Color &color);
    
protected:
    bool m_isFill;
    int m_iNumNGRects;
};

#endif /* defined(__noctisgames__NGRectBatcher__) */
