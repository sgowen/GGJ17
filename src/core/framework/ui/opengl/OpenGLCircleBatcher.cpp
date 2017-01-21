//
//  OpenGLCircleBatcher.cpp
//  noctisgames-framework
//
//  Created by Stephen Gowen on 11/15/14.
//  Copyright (c) 2017 Noctis Games. All rights reserved.
//

#define DEGREE_SPACING 6

#include "OpenGLCircleBatcher.h"
#include "macros.h"
#include "Circle.h"
#include "Vector2D.h"
#include "OpenGLManager.h"
#include "DummyGpuProgramWrapper.h"

OpenGLCircleBatcher::OpenGLCircleBatcher() : CircleBatcher()
{
    // Empty
}

void OpenGLCircleBatcher::renderCircle(Circle &circle, Color &c, GpuProgramWrapper &gpuProgramWrapper)
{
    OGLManager->getColorVertices().clear();
    
    m_iNumPoints = 0;
    
    for (int i = 0; i < 360; i += DEGREE_SPACING)
    {
        float rad = DEGREES_TO_RADIANS(i);
        float cos = cosf(rad);
        float sin = sinf(rad);
        
        OGLManager->addVertexCoordinate(cos * circle.getRadius() + circle.getCenter().getX(), sin * circle.getRadius() + circle.getCenter().getY(), 0, c.red, c.green, c.blue, c.alpha);
        
        m_iNumPoints++;
    }
    
    endBatch(gpuProgramWrapper);
}

void OpenGLCircleBatcher::renderPartialCircle(Circle &circle, int arcDegrees, Color &c, GpuProgramWrapper &gpuProgramWrapper)
{
    OGLManager->getColorVertices().clear();
    
    OGLManager->addVertexCoordinate(circle.getCenter().getX(), circle.getCenter().getY(), 0, c.red, c.green, c.blue, c.alpha);
    
    m_iNumPoints = 1;
    
    for (int i = 90 - arcDegrees; i > -270; i -= DEGREE_SPACING)
    {
        float rad = DEGREES_TO_RADIANS(i);
        float cos = cosf(rad);
        float sin = sinf(rad);
        
        OGLManager->addVertexCoordinate(cos * circle.getRadius() + circle.getCenter().getX(), sin * circle.getRadius() + circle.getCenter().getY(), 0, c.red, c.green, c.blue, c.alpha);
        
        m_iNumPoints++;
    }
    
    float rad = DEGREES_TO_RADIANS(-270);
    float cos = cosf(rad);
    float sin = sinf(rad);
    
    OGLManager->addVertexCoordinate(cos * circle.getRadius() + circle.getCenter().getX(), sin * circle.getRadius() + circle.getCenter().getY(), 0, c.red, c.green, c.blue, c.alpha);
    
    m_iNumPoints++;
    
    endBatch(gpuProgramWrapper);
}

void OpenGLCircleBatcher::endBatch(GpuProgramWrapper &gpuProgramWrapper)
{
    gpuProgramWrapper.bind();
    
    glDrawArrays(GL_TRIANGLE_FAN, 0, m_iNumPoints);
    
    gpuProgramWrapper.unbind();
}
