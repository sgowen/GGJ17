//
//  OpenGLRendererHelper.cpp
//  noctisgames-framework
//
//  Created by Stephen Gowen on 1/15/17.
//  Copyright (c) 2017 Noctis Games. All rights reserved.
//

#include "OpenGLRendererHelper.h"

#include "GpuTextureWrapper.h"
#include "OpenGLManager.h"

extern "C"
{
#include "platform_gl.h"
}

OpenGLRendererHelper::OpenGLRendererHelper() : IRendererHelper()
{
    // Empty
}

OpenGLRendererHelper::~OpenGLRendererHelper()
{
    // Empty
}

void OpenGLRendererHelper::beginFrame()
{
    glEnable(GL_TEXTURE_2D);
    
    glEnable(GL_BLEND);
}

void OpenGLRendererHelper::endFrame()
{
    glDisable(GL_BLEND);
    
    glDisable(GL_TEXTURE_2D);
}

GpuTextureWrapper OpenGLRendererHelper::getFramebuffer(int index)
{
    return GpuTextureWrapper(OGLManager->getFboTextures().at(index));
}

void OpenGLRendererHelper::updateMatrix(float left, float right, float bottom, float top)
{
    OGLManager->createMatrix(left, right, bottom, top);
}

void OpenGLRendererHelper::bindToOffscreenFramebuffer(int index)
{
    glBindFramebuffer(GL_FRAMEBUFFER, OGLManager->getFbos().at(index));
}

void OpenGLRendererHelper::clearFramebufferWithColor(float r, float g, float b, float a)
{
    glClearColor(r, g, b, a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}

void OpenGLRendererHelper::bindToScreenFramebuffer()
{
    glBindFramebuffer(GL_FRAMEBUFFER, OGLManager->getScreenFBO());
}

void OpenGLRendererHelper::destroyTexture(GpuTextureWrapper& textureWrapper)
{
    glDeleteTextures(1, &textureWrapper.texture);
}
