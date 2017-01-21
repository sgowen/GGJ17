//
//  OpenGLFramebufferToScreenGpuProgramWrapper.cpp
//  noctisgames-framework
//
//  Created by Stephen Gowen on 9/3/15.
//  Copyright (c) 2017 Noctis Games. All rights reserved.
//

#include "OpenGLFramebufferToScreenGpuProgramWrapper.h"

#include "OpenGLManager.h"
#include "macros.h"

extern "C"
{
#include "asset_utils.h"
}

OpenGLFramebufferToScreenGpuProgramWrapper::OpenGLFramebufferToScreenGpuProgramWrapper()
{
    m_program = FramebufferToScreenProgram::build(build_program_from_assets("frame_buffer_to_screen_shader.vsh", "frame_buffer_to_screen_shader.fsh"));
    m_isLoaded = true;
}

OpenGLFramebufferToScreenGpuProgramWrapper::~OpenGLFramebufferToScreenGpuProgramWrapper()
{
    glDeleteProgram(m_program.program);
}

void OpenGLFramebufferToScreenGpuProgramWrapper::bind()
{
    OGLManager->useScreenBlending();
    
    glUseProgram(m_program.program);
    
    glUniform1i(m_program.u_texture_unit_location, 0);
    
    glGenBuffers(1, &OGLManager->getSbVboObject());
    glBindBuffer(GL_ARRAY_BUFFER, OGLManager->getSbVboObject());
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * OGLManager->getTextureVertices().size(), &OGLManager->getTextureVertices()[0], GL_STATIC_DRAW);
    
    glVertexAttribPointer(m_program.a_position_location, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 9, BUFFER_OFFSET(0));
    
    glEnableVertexAttribArray(m_program.a_position_location);
}

void OpenGLFramebufferToScreenGpuProgramWrapper::unbind()
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    
    glDeleteBuffers(1, &OGLManager->getSbVboObject());
    
    glUseProgram(0);
}
