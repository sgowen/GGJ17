//
//  FramebufferToScreenProgram.h
//  noctisgames-framework
//
//  Created by Stephen Gowen on 9/3/15.
//  Copyright (c) 2017 Noctis Games. All rights reserved.
//

#ifndef __noctisgames__FramebufferToScreenProgram__
#define __noctisgames__FramebufferToScreenProgram__

extern "C"
{
#include "platform_gl.h"
}

typedef struct
{
    GLuint program;
    
    GLint a_position_location;
    GLint u_texture_unit_location;
    GLint u_direction_location;
} FramebufferToScreenProgramStruct;

class FramebufferToScreenProgram
{
public:
    static FramebufferToScreenProgramStruct build(GLuint program);
    
private:
    FramebufferToScreenProgram();
};

#endif /* defined(__noctisgames__FramebufferToScreenProgram__) */
