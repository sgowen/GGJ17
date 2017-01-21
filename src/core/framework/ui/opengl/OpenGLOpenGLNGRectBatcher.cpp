//
//  OpenGLNGRectBatcher.cpp
//  noctisgames-framework
//
//  Created by Stephen Gowen on 7/15/14.
//  Copyright (c) 2017 Noctis Games. All rights reserved.
//

#include "OpenGLNGRectBatcher.h"

#include "macros.h"
#include "NGRect.h"
#include "Vector2D.h"
#include "GpuProgramWrapper.h"

OpenGLNGRectBatcher::OpenGLNGRectBatcher(bool isFill) : NGRectBatcher(isFill)
{
    // Empty
}

void OpenGLNGRectBatcher::beginBatch()
{
    OGLManager->getColorVertices().clear();
    m_iNumNGRects = 0;
}

void OpenGLNGRectBatcher::endBatch(GpuProgramWrapper &gpuProgramWrapper)
{
    if (m_iNumNGRects > 0)
    {
        gpuProgramWrapper.bind();
        
        if (m_isFill)
        {
            glDrawElements(GL_TRIANGLES, m_iNumNGRects * INDICES_PER_RECTANGLE, GL_UNSIGNED_SHORT, &OGLManager->getIndices()[0]);
        }
        else
        {
            glDrawArrays(GL_LINES, 0, VERTICES_PER_LINE * m_iNumNGRects * 4);
        }
        
        gpuProgramWrapper.unbind();
    }
}

void OpenGLNGRectBatcher::renderNGRect(float x1, float y1, float x2, float y2, Color &c)
{
    if (m_isFill)
    {
        OGLManager->addVertexCoordinate(x1, y1, 0, c.red, c.green, c.blue, c.alpha);
        OGLManager->addVertexCoordinate(x1, y2, 0, c.red, c.green, c.blue, c.alpha);
        OGLManager->addVertexCoordinate(x2, y2, 0, c.red, c.green, c.blue, c.alpha);
        OGLManager->addVertexCoordinate(x2, y1, 0, c.red, c.green, c.blue, c.alpha);
    }
    else
    {
        OGLManager->addVertexCoordinate(x1, y1, 0, c.red, c.green, c.blue, c.alpha);
        OGLManager->addVertexCoordinate(x2, y1, 0, c.red, c.green, c.blue, c.alpha);
        
        OGLManager->addVertexCoordinate(x2, y1, 0, c.red, c.green, c.blue, c.alpha);
        OGLManager->addVertexCoordinate(x2, y2, 0, c.red, c.green, c.blue, c.alpha);
        
        OGLManager->addVertexCoordinate(x2, y2, 0, c.red, c.green, c.blue, c.alpha);
        OGLManager->addVertexCoordinate(x1, y2, 0, c.red, c.green, c.blue, c.alpha);
        
        OGLManager->addVertexCoordinate(x1, y2, 0, c.red, c.green, c.blue, c.alpha);
        OGLManager->addVertexCoordinate(x1, y1, 0, c.red, c.green, c.blue, c.alpha);
    }

    m_iNumNGRects++;
}
