//
//  OpenGLSinWaveTextureGpuProgramWrapper.cpp
//  ggj17
//
//  Created by Stephen Gowen on 1/21/17.
//  Copyright © 2017 Noctis Games. All rights reserved.
//

#include "OpenGLSinWaveTextureGpuProgramWrapper.h"
#include "OpenGLManager.h"
#include "macros.h"

extern "C"
{
#include "asset_utils.h"
}

OpenGLSinWaveTextureGpuProgramWrapper::OpenGLSinWaveTextureGpuProgramWrapper()
{
    m_program = SinWaveTextureProgram::build(build_program_from_assets("texture_shader.vsh", "sin_wave_texture_shader.fsh"));
    m_isLoaded = true;
}

void OpenGLSinWaveTextureGpuProgramWrapper::bind()
{
    OGLManager->useNormalBlending();
    
    glUseProgram(m_program.program);
    
    glUniformMatrix4fv(m_program.u_mvp_matrix_location, 1, GL_FALSE, (GLfloat*)OGLManager->getViewProjectionMatrix());
    glUniform1i(m_program.u_texture_unit_location, 0);
    glUniform1f(m_program.u_offset_unit_location, m_fOffset);
    
    glGenBuffers(1, &OGLManager->getSbVboObject());
    glBindBuffer(GL_ARRAY_BUFFER, OGLManager->getSbVboObject());
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * OGLManager->getTextureVertices().size(), &OGLManager->getTextureVertices()[0], GL_STATIC_DRAW);
    
    glVertexAttribPointer(m_program.a_position_location, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 9, BUFFER_OFFSET(0));
    glVertexAttribPointer(m_program.a_color_location, 4, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 9, BUFFER_OFFSET(3 * sizeof(GL_FLOAT)));
    glVertexAttribPointer(m_program.a_texture_coordinates_location, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 9, BUFFER_OFFSET(7 * sizeof(GL_FLOAT)));
    
    glEnableVertexAttribArray(m_program.a_position_location);
    glEnableVertexAttribArray(m_program.a_color_location);
    glEnableVertexAttribArray(m_program.a_texture_coordinates_location);
}

void OpenGLSinWaveTextureGpuProgramWrapper::unbind()
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    
    glDeleteBuffers(1, &OGLManager->getSbVboObject());
    
    glUseProgram(0);
}

void OpenGLSinWaveTextureGpuProgramWrapper::cleanUp()
{
    glDeleteProgram(m_program.program);
}
