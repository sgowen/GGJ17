//
//  OpenGLManager.cpp
//  noctisgames-framework
//
//  Created by Stephen Gowen on 11/19/14.
//  Copyright (c) 2017 Noctis Games. All rights reserved.
//

#include "OpenGLManager.h"
#include "OpenGLTextureGpuProgramWrapper.h"
#include "OpenGLGeometryGpuProgramWrapper.h"
#include "OpenGLFramebufferToScreenGpuProgramWrapper.h"
#include "ColorProgram.h"
#include "TextureProgram.h"
#include "FramebufferToScreenProgram.h"
#include "macros.h"

extern "C"
{
#include <assert.h>
}

OpenGLManager* OpenGLManager::s_pInstance = nullptr;

void OpenGLManager::create()
{
    assert(!s_pInstance);
    
    s_pInstance = new OpenGLManager();
}

void OpenGLManager::destroy()
{
    assert(s_pInstance);
    
    delete s_pInstance;
    s_pInstance = nullptr;
}

OpenGLManager * OpenGLManager::getInstance()
{
    return s_pInstance;
}

void OpenGLManager::createDeviceDependentResources(int maxBatchSize)
{
    assert(m_fbos.size() == 0);
    assert(m_fbo_textures.size() == 0);
    
    glGetIntegerv(GL_FRAMEBUFFER_BINDING, &m_iScreenFBO);
    glGetIntegerv(GL_MAX_TEXTURE_SIZE, &m_iMaxTextureSize);
    
    generateIndices(maxBatchSize);
    
    if (m_iScreenWidth > -1
        && m_iScreenHeight > -1
        && m_iNumFramebuffers > -1)
    {
        createFramebufferObjects();
    }
}

void OpenGLManager::createWindowSizeDependentResources(int screenWidth, int screenHeight, int numFramebuffers)
{
    m_iScreenWidth = screenWidth;
    m_iScreenHeight = screenHeight;
    m_iNumFramebuffers = numFramebuffers;
    
    glViewport(0, 0, m_iScreenWidth, m_iScreenHeight);
    
    glScissor(0, 0, m_iScreenWidth, m_iScreenHeight);
    glEnable(GL_SCISSOR_TEST);
    
    releaseFramebuffers();
    createFramebufferObjects();
}

void OpenGLManager::releaseDeviceDependentResources()
{
    m_indices.clear();
    
    releaseFramebuffers();
    
    glDeleteBuffers(1, &sb_vbo_object);
    glDeleteBuffers(1, &gb_vbo_object);
}

void OpenGLManager::createMatrix(float left, float right, float bottom, float top)
{
    vec3 eye = { 0, 0, 1 };
    vec3 center = { 0, 0, 0 };
    vec3 up = { 0, 1, 0 };
    
    mat4x4 projectionMatrix;
    mat4x4 viewMatrix;
    
    mat4x4_ortho(projectionMatrix, left, right, bottom, top, -1, 1);
    mat4x4_look_at(viewMatrix, eye, center, up);
    
    mat4x4_mul(m_viewProjectionMatrix, projectionMatrix, viewMatrix);
}

void OpenGLManager::addVertexCoordinate(GLfloat x, GLfloat y, GLfloat z, GLfloat r, GLfloat g, GLfloat b, GLfloat a, GLfloat u, GLfloat v)
{
    m_textureVertices.push_back(x);
    m_textureVertices.push_back(y);
    m_textureVertices.push_back(z);
    m_textureVertices.push_back(r);
    m_textureVertices.push_back(g);
    m_textureVertices.push_back(b);
    m_textureVertices.push_back(a);
    m_textureVertices.push_back(u);
    m_textureVertices.push_back(v);
}

void OpenGLManager::addVertexCoordinate(GLfloat x, GLfloat y, GLfloat z, GLfloat r, GLfloat g, GLfloat b, GLfloat a)
{
    m_colorVertices.push_back(x);
    m_colorVertices.push_back(y);
    m_colorVertices.push_back(z);
    m_colorVertices.push_back(r);
    m_colorVertices.push_back(g);
    m_colorVertices.push_back(b);
    m_colorVertices.push_back(a);
}

void OpenGLManager::useNormalBlending()
{
    glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ZERO);
    glBlendEquationSeparate(GL_FUNC_ADD, GL_FUNC_ADD);
}

void OpenGLManager::useScreenBlending()
{
    glBlendFuncSeparate(GL_ONE, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
    glBlendEquationSeparate(GL_FUNC_ADD, GL_FUNC_ADD);
}

std::vector<GLshort>& OpenGLManager::getIndices()
{
    return m_indices;
}

std::vector<GLuint>& OpenGLManager::getFbos()
{
    return m_fbos;
}

std::vector<GLuint>& OpenGLManager::getFboTextures()
{
    return m_fbo_textures;
}

std::vector<GLfloat>& OpenGLManager::getTextureVertices()
{
    return m_textureVertices;
}

std::vector<GLfloat>& OpenGLManager::getColorVertices()
{
    return m_colorVertices;
}

GLuint& OpenGLManager::getSbVboObject()
{
    return sb_vbo_object;
}

GLuint& OpenGLManager::getGbVboObject()
{
    return gb_vbo_object;
}

GLint& OpenGLManager::getScreenFBO()
{
    return m_iScreenFBO;
}

GLint& OpenGLManager::getMaxTextureSize()
{
    return m_iMaxTextureSize;
}

mat4x4& OpenGLManager::getViewProjectionMatrix()
{
    return m_viewProjectionMatrix;
}

#pragma mark private

void OpenGLManager::generateIndices(int maxBatchSize)
{
    m_indices.reserve(maxBatchSize * INDICES_PER_RECTANGLE);
    
    GLshort j = 0;
    for (int i = 0; i < maxBatchSize * INDICES_PER_RECTANGLE; i += INDICES_PER_RECTANGLE, j += VERTICES_PER_RECTANGLE)
    {
        m_indices.push_back(j);
        m_indices.push_back(j + 1);
        m_indices.push_back(j + 2);
        m_indices.push_back(j + 2);
        m_indices.push_back(j + 3);
        m_indices.push_back(j + 0);
    }
}

void OpenGLManager::createFramebufferObjects()
{
    for (int i = 0; i < m_iNumFramebuffers; i++)
    {
        createFramebufferObject();
    }
}

void OpenGLManager::createFramebufferObject()
{
    GLuint fbo_texture;
    GLuint fbo;
    
    // Texture
    glActiveTexture(GL_TEXTURE0);
    glGenTextures(1, &fbo_texture);
    glBindTexture(GL_TEXTURE_2D, fbo_texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_iScreenWidth, m_iScreenHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
    glBindTexture(GL_TEXTURE_2D, 0);
    
    // Framebuffer
    glGenFramebuffers(1, &fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, fbo_texture, 0);
    
    GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
    
    glBindFramebuffer(GL_FRAMEBUFFER, m_iScreenFBO);
    
    assert(status == GL_FRAMEBUFFER_COMPLETE);
    
    m_fbo_textures.push_back(fbo_texture);
    m_fbos.push_back(fbo);
}

void OpenGLManager::releaseFramebuffers()
{
    for (std::vector<GLuint>::iterator i = m_fbo_textures.begin(); i != m_fbo_textures.end(); i++)
    {
        glDeleteTextures(1, &(*i));
    }
    
    m_fbo_textures.clear();
    
    for (std::vector<GLuint>::iterator i = m_fbos.begin(); i != m_fbos.end(); i++)
    {
        glDeleteFramebuffers(1, &(*i));
    }
    
    m_fbos.clear();
}

OpenGLManager::OpenGLManager() : sb_vbo_object(0), gb_vbo_object(0), m_iScreenFBO(0), m_iMaxTextureSize(64), m_iScreenWidth(-1), m_iScreenHeight(-1), m_iNumFramebuffers(-1)
{
    // Hide Constructor for Singleton
}

OpenGLManager::~OpenGLManager()
{
    releaseDeviceDependentResources();
}
