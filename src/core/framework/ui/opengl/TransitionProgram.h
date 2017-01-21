//
//  TransitionProgram.h
//  noctisgames-framework
//
//  Created by Stephen Gowen on 1/27/16.
//  Copyright (c) 2017 Noctis Games. All rights reserved.
//

#ifndef __noctisgames__TransitionProgram__
#define __noctisgames__TransitionProgram__

extern "C"
{
#include "platform_gl.h"
}

typedef struct
{
    GLuint program;
    
    GLint a_position_location;
    GLint u_from_location;
    GLint u_to_location;
    GLint u_progress_location;
} TransitionProgramStruct;

class TransitionProgram
{
public:
    static TransitionProgramStruct build(GLuint program);
    
private:
    TransitionProgram();
};

#endif /* defined(__noctisgames__TransitionProgram__) */
