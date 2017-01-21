//
//  Direct3DLineBatcher.cpp
//  noctisgames-framework
//
//  Created by Stephen Gowen on 11/16/14.
//  Copyright (c) 2017 Noctis Games. All rights reserved.
//

#include "pch.h"

#include "Direct3DLineBatcher.h"

#include "Line.h"
#include "Vector2D.h"
#include "Direct3DProgram.h"
#include "Direct3DManager.h"
#include "GpuProgramWrapper.h"
#include "Direct3DGeometryGpuProgramWrapper.h"

Direct3DLineBatcher::Direct3DLineBatcher() : LineBatcher()
{
	// Empty
}

void Direct3DLineBatcher::beginBatch()
{
	D3DManager->getColorVertices().clear();
	m_iNumLines = 0;
}

void Direct3DLineBatcher::endBatch(GpuProgramWrapper &gpuProgramWrapper)
{
	if (m_iNumLines > 0)
	{
		// set the primitive topology
		DX::DeviceResources* deviceResources = Direct3DManager::getDeviceResources();
		deviceResources->GetD3DDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);

		gpuProgramWrapper.bind();

		deviceResources->GetD3DDeviceContext()->Draw(m_iNumLines * VERTICES_PER_LINE, 0);

		gpuProgramWrapper.unbind();
	}
}

void Direct3DLineBatcher::renderLine(float originX, float originY, float endX, float endY, Color &color)
{
	D3DManager->addVertexCoordinate(originX, originY, 0, color.red, color.green, color.blue, color.alpha);
	D3DManager->addVertexCoordinate(endX, endY, 0, color.red, color.green, color.blue, color.alpha);

	m_iNumLines++;
}
