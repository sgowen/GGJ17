//
//  Direct3DNGRectBatcher.cpp
//  noctisgames-framework
//
//  Created by Stephen Gowen on 9/22/14.
//  Copyright (c) 2017 Noctis Games. All rights reserved.
//

#include "pch.h"

#include "Direct3DNGRectBatcher.h"

#include "NGRect.h"
#include "Vector2D.h"
#include "Direct3DProgram.h"
#include "Direct3DManager.h"
#include "GpuProgramWrapper.h"
#include "Direct3DGeometryGpuProgramWrapper.h"

Direct3DNGRectBatcher::Direct3DNGRectBatcher(bool isFill) : NGRectBatcher(isFill)
{
    // Empty
}

void Direct3DNGRectBatcher::beginBatch()
{
	D3DManager->getColorVertices().clear();
	m_iNumNGRects = 0;
}

void Direct3DNGRectBatcher::endBatch(GpuProgramWrapper &gpuProgramWrapper)
{
	if (m_iNumNGRects > 0)
	{
		// set the primitive topology
		DX::DeviceResources* deviceResources = Direct3DManager::getDeviceResources();
		deviceResources->GetD3DDeviceContext()->IASetPrimitiveTopology(m_isFill ? D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST : D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP);

		gpuProgramWrapper.bind();

		deviceResources->GetD3DDeviceContext()->DrawIndexed(m_iNumNGRects * INDICES_PER_RECTANGLE, 0, 0);

		gpuProgramWrapper.unbind();
	}
}

void Direct3DNGRectBatcher::renderNGRect(NGRect &rectangle, Color &color)
{
	float x1 = rectangle.getLeft();
	float y1 = rectangle.getBottom();
	float x2 = x1 + rectangle.getWidth();
	float y2 = y1 + rectangle.getHeight();

	renderNGRect(x1, y1, x2, y2, color);
}

void Direct3DNGRectBatcher::renderNGRect(float x1, float y1, float x2, float y2, Color &color)
{
	D3DManager->addVertexCoordinate(x1, y1, 0, color.red, color.green, color.blue, color.alpha);
	D3DManager->addVertexCoordinate(x1, y2, 0, color.red, color.green, color.blue, color.alpha);
	D3DManager->addVertexCoordinate(x2, y2, 0, color.red, color.green, color.blue, color.alpha);
	D3DManager->addVertexCoordinate(x2, y1, 0, color.red, color.green, color.blue, color.alpha);

	m_iNumNGRects++;
}
