//
//  texture.h
//  noctisgames-framework
//
//  Created by Stephen Gowen on 2/22/14.
//  Copyright (c) 2017 Noctis Games. All rights reserved.
//

#ifndef __noctisgames__texture__
#define __noctisgames__texture__

#include "platform_gl.h"

GLuint load_texture(const GLsizei width, const GLsizei height, const GLenum type, const GLvoid* pixels, int repeat_s, int mipmap);

#endif /* defined(__noctisgames__texture__) */
