//
//  TextureProgram.h
//  noctisgames-framework
//
//  Created by Stephen Gowen on 8/4/15.
//  Copyright (c) 2017 Noctis Games. All rights reserved.
//

#ifndef __noctisgames__TextureProgram__
#define __noctisgames__TextureProgram__

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
} TextureProgramStruct;

class TextureProgram
{
public:
    static TextureProgramStruct build(GLuint program);
    
private:
    TextureProgram();
};

#endif /* defined(__noctisgames__TextureProgram__) */
