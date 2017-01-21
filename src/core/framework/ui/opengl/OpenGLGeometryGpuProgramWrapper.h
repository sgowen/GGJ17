//
//  OpenGLGeometryGpuProgramWrapper.h
//  noctisgames-framework
//
//  Created by Stephen Gowen on 8/27/15.
//  Copyright (c) 2017 Noctis Games. All rights reserved.
//

#ifndef __noctisgames__OpenGLGeometryGpuProgramWrapper__
#define __noctisgames__OpenGLGeometryGpuProgramWrapper__

#include "GpuProgramWrapper.h"

#include "ColorProgram.h"

class OpenGLGeometryGpuProgramWrapper : public GpuProgramWrapper
{
public:
    OpenGLGeometryGpuProgramWrapper();
    
    virtual ~OpenGLGeometryGpuProgramWrapper();
    
    virtual void bind();
    
    virtual void unbind();
    
private:
    ColorProgramStruct m_program;
};

#endif /* defined(__noctisgames__OpenGLGeometryGpuProgramWrapper__) */
