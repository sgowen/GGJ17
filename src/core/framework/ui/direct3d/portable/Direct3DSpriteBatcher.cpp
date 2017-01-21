//
//  Direct3DSpriteBatcher.cpp
//  noctisgames-framework
//
//  Created by Stephen Gowen on 9/22/14.
//  Copyright (c) 2017 Noctis Games. All rights reserved.
//

#include "pch.h"

#include "Direct3DSpriteBatcher.h"

#include "Direct3DManager.h"
#include "macros.h"
#include "TextureRegion.h"
#include "GpuProgramWrapper.h"

#include <vector>
#include <stdlib.h>

Direct3DSpriteBatcher::Direct3DSpriteBatcher() : SpriteBatcher()
{
    // Empty
}

void Direct3DSpriteBatcher::beginBatch()
{
	D3DManager->getTextureVertices().clear();
	m_iNumSprites = 0;
}

void Direct3DSpriteBatcher::endBatch(GpuTextureWrapper textureWrapper, GpuProgramWrapper &gpuProgramWrapper)
{
	if (m_iNumSprites > 0)
	{
		// tell the GPU which texture to use
		DX::DeviceResources* deviceResources = Direct3DManager::getDeviceResources();
		deviceResources->GetD3DDeviceContext()->PSSetShaderResources(0, 1, &textureWrapper.texture);

		// set the primitive topology
		deviceResources->GetD3DDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		gpuProgramWrapper.bind();

		deviceResources->GetD3DDeviceContext()->DrawIndexed(m_iNumSprites * INDICES_PER_RECTANGLE, 0, 0);

		gpuProgramWrapper.unbind();

		ID3D11ShaderResourceView *pSRV[1] = { NULL };
		deviceResources->GetD3DDeviceContext()->PSSetShaderResources(0, 1, pSRV);
	}
}

void Direct3DSpriteBatcher::drawSprite(float x, float y, float width, float height, float angle, TextureRegion tr)
{
	if (angle != 0)
	{
		float halfWidth = width / 2;
		float halfHeight = height / 2;

		float rad = DEGREES_TO_RADIANS(angle);
		float cos = cosf(rad);
		float sin = sinf(rad);

		float x1 = -halfWidth * cos - (-halfHeight) * sin;
		float y1 = -halfWidth * sin + (-halfHeight) * cos;

		float x2 = halfWidth * cos - (-halfHeight) * sin;
		float y2 = halfWidth * sin + (-halfHeight) * cos;

		float x3 = halfWidth * cos - halfHeight * sin;
		float y3 = halfWidth * sin + halfHeight * cos;

		float x4 = -halfWidth * cos - halfHeight * sin;
		float y4 = -halfWidth * sin + halfHeight * cos;

		x1 += x;
		y1 += y;

		x2 += x;
		y2 += y;

		x3 += x;
		y3 += y;

		x4 += x;
		y4 += y;

		D3DManager->addVertexCoordinate(x1, y1, 0, 1, 1, 1, 1, tr.u1, tr.v2);
		D3DManager->addVertexCoordinate(x4, y4, 0, 1, 1, 1, 1, tr.u1, tr.v1);
		D3DManager->addVertexCoordinate(x3, y3, 0, 1, 1, 1, 1, tr.u2, tr.v1);
		D3DManager->addVertexCoordinate(x2, y2, 0, 1, 1, 1, 1, tr.u2, tr.v2);
	}
	else
	{
		drawSprite(x, y, width, height, tr);
	}

	m_iNumSprites++;
}

void Direct3DSpriteBatcher::drawSprite(float x, float y, float width, float height, float angle, Color &color, TextureRegion tr)
{
	if (angle != 0)
	{
		float halfWidth = width / 2;
		float halfHeight = height / 2;

		float rad = DEGREES_TO_RADIANS(angle);
		float cos = cosf(rad);
		float sin = sinf(rad);

		float x1 = -halfWidth * cos - (-halfHeight) * sin;
		float y1 = -halfWidth * sin + (-halfHeight) * cos;

		float x2 = halfWidth * cos - (-halfHeight) * sin;
		float y2 = halfWidth * sin + (-halfHeight) * cos;

		float x3 = halfWidth * cos - halfHeight * sin;
		float y3 = halfWidth * sin + halfHeight * cos;

		float x4 = -halfWidth * cos - halfHeight * sin;
		float y4 = -halfWidth * sin + halfHeight * cos;

		x1 += x;
		y1 += y;

		x2 += x;
		y2 += y;

		x3 += x;
		y3 += y;

		x4 += x;
		y4 += y;

		D3DManager->addVertexCoordinate(x1, y1, 0, color.red, color.green, color.blue, color.alpha, tr.u1, tr.v2);
		D3DManager->addVertexCoordinate(x4, y4, 0, color.red, color.green, color.blue, color.alpha, tr.u1, tr.v1);
		D3DManager->addVertexCoordinate(x3, y3, 0, color.red, color.green, color.blue, color.alpha, tr.u2, tr.v1);
		D3DManager->addVertexCoordinate(x2, y2, 0, color.red, color.green, color.blue, color.alpha, tr.u2, tr.v2);
	}
	else
	{
		drawSprite(x, y, width, height, color, tr);
	}

	m_iNumSprites++;
}

#pragma mark <Private>

void Direct3DSpriteBatcher::drawSprite(float x, float y, float width, float height, TextureRegion tr)
{
	float halfWidth = width / 2;
	float halfHeight = height / 2;
	float x1 = x - halfWidth;
	float y1 = y - halfHeight;
	float x2 = x + halfWidth;
	float y2 = y + halfHeight;

	D3DManager->addVertexCoordinate(x1, y1, 0, 1, 1, 1, 1, tr.u1, tr.v2);
	D3DManager->addVertexCoordinate(x1, y2, 0, 1, 1, 1, 1, tr.u1, tr.v1);
	D3DManager->addVertexCoordinate(x2, y2, 0, 1, 1, 1, 1, tr.u2, tr.v1);
	D3DManager->addVertexCoordinate(x2, y1, 0, 1, 1, 1, 1, tr.u2, tr.v2);
}

void Direct3DSpriteBatcher::drawSprite(float x, float y, float width, float height, Color &color, TextureRegion tr)
{
	float halfWidth = width / 2;
	float halfHeight = height / 2;
	float x1 = x - halfWidth;
	float y1 = y - halfHeight;
	float x2 = x + halfWidth;
	float y2 = y + halfHeight;

	D3DManager->addVertexCoordinate(x1, y1, 0, color.red, color.green, color.blue, color.alpha, tr.u1, tr.v2);
	D3DManager->addVertexCoordinate(x1, y2, 0, color.red, color.green, color.blue, color.alpha, tr.u1, tr.v1);
	D3DManager->addVertexCoordinate(x2, y2, 0, color.red, color.green, color.blue, color.alpha, tr.u2, tr.v1);
	D3DManager->addVertexCoordinate(x2, y1, 0, color.red, color.green, color.blue, color.alpha, tr.u2, tr.v2);
}
