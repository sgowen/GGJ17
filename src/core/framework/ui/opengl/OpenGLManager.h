//
//  OpenGLManager.h
//  noctisgames-framework
//
//  Created by Stephen Gowen on 11/19/14.
//  Copyright (c) 2017 Noctis Games. All rights reserved.
//

#ifndef __noctisgames__OpenGLManager__
#define __noctisgames__OpenGLManager__

#define VERTICES_PER_LINE 2
#define VERTICES_PER_RECTANGLE 4
#define INDICES_PER_RECTANGLE 6

#define OGLManager (OpenGLManager::getInstance())

extern "C"
{
#include "platform_gl.h"
#include "linmath.h"
}

#include <memory>
#include <vector>

class GpuProgramWrapper;

class OpenGLManager
{
public:
    static void create();
    
    static void destroy();
    
    static OpenGLManager * getInstance();
    
    void createDeviceDependentResources(int maxBatchSize);
    
    void createWindowSizeDependentResources(int screenWidth, int screenHeight, int numFramebuffers);
    
    void releaseDeviceDependentResources();
    
    void createMatrix(float left, float right, float bottom, float top);
    
    // Called by Batchers
    void addVertexCoordinate(GLfloat x, GLfloat y, GLfloat z, GLfloat r, GLfloat g, GLfloat b, GLfloat a, GLfloat u, GLfloat v);
    void addVertexCoordinate(GLfloat x, GLfloat y, GLfloat z, GLfloat r, GLfloat g, GLfloat b, GLfloat a);
    
    void useNormalBlending();
    void useScreenBlending();
    
    std::vector<GLshort>& getIndices();
    std::vector<GLuint>& getFbos();
    std::vector<GLuint>& getFboTextures();
    std::vector<GLfloat>& getTextureVertices();
    std::vector<GLfloat>& getColorVertices();
    GLuint& getSbVboObject(); // For Sprite Batcher
    GLuint& getGbVboObject(); // For Geometry Batcher
    GLint& getScreenFBO();
    GLint& getMaxTextureSize();
    mat4x4& getViewProjectionMatrix();
    
private:
    static OpenGLManager* s_pInstance;
    
    std::vector<GLshort> m_indices;
    
    std::vector<GLuint> m_fbos;
    std::vector<GLuint> m_fbo_textures;
    
    std::vector<GLfloat> m_textureVertices;
    std::vector<GLfloat> m_colorVertices;
    
    GLuint sb_vbo_object; // For Sprite Batcher
    GLuint gb_vbo_object; // For Geometry Batcher
    
    GLint m_iScreenFBO;
    GLint m_iMaxTextureSize;
    
    mat4x4 m_viewProjectionMatrix;
    
    int m_iScreenWidth;
    int m_iScreenHeight;
    int m_iNumFramebuffers;
    
    void generateIndices(int maxBatchSize);
    void createFramebufferObjects();
    void createFramebufferObject();
    void releaseFramebuffers();
    
    // ctor, copy ctor, and assignment should be private in a Singleton
    OpenGLManager();
    ~OpenGLManager();
    OpenGLManager(const OpenGLManager&);
    OpenGLManager& operator=(const OpenGLManager&);
};

#endif /* defined(__noctisgames__OpenGLManager__) */
