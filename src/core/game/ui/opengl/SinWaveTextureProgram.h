//
//  SinWaveTextureProgram.h
//  ggj17
//
//  Created by Stephen Gowen on 1/21/17.
//  Copyright © 2017 Noctis Games. All rights reserved.
//

#ifndef __noctisgames__SinWaveTextureProgram__
#define __noctisgames__SinWaveTextureProgram__

extern "C"
{
#include "platform_gl.h"
}

typedef struct
{
    GLuint program;
    
    GLint u_mvp_matrix_location;
    GLint a_position_location;
    GLint a_color_location;
    GLint a_texture_coordinates_location;
    GLint u_texture_unit_location;
    GLint u_offset_unit_location;
} SinWaveTextureProgramStruct;

class SinWaveTextureProgram
{
public:
    static SinWaveTextureProgramStruct build(GLuint program);
    
private:
    SinWaveTextureProgram();
};

#endif /* defined(__noctisgames__SinWaveTextureProgram__) */
