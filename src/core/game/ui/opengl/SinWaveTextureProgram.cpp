//
//  SinWaveTextureProgram.cpp
//  ggj17
//
//  Created by Stephen Gowen on 1/21/17.
//  Copyright © 2017 Noctis Games. All rights reserved.
//

#include "SinWaveTextureProgram.h"

SinWaveTextureProgramStruct SinWaveTextureProgram::build(GLuint program)
{
    return (SinWaveTextureProgramStruct)
    {
        program,
        glGetUniformLocation(program, "u_MvpMatrix"),
        glGetAttribLocation(program, "a_Position"),
        glGetAttribLocation(program, "a_Color"),
        glGetAttribLocation(program, "a_TextureCoordinates"),
        glGetUniformLocation(program, "u_TextureUnit"),
        glGetUniformLocation(program, "u_Offset")
    };
}
