//
//  GridLockedPhysicalEntity.cpp
//  noctisgames-framework
//
//  Created by Stephen Gowen on 2/6/16.
//  Copyright (c) 2017 Noctis Games. All rights reserved.
//

#include "GridLockedPhysicalEntity.h"

#include "GridManager.h"

GridLockedPhysicalEntity::GridLockedPhysicalEntity(int gridX, int gridY, int gridWidth, int gridHeight, float boundsX, float boundsY, float boundsWidth, float boundsHeight) : PhysicalEntity(gridX * GM_GRID_CELL_SIZE, gridY * GM_GRID_CELL_SIZE, gridWidth * GM_GRID_CELL_SIZE, gridHeight * GM_GRID_CELL_SIZE), m_iGridX(gridX), m_iGridY(gridY), m_iGridWidth(gridWidth), m_iGridHeight(gridHeight), m_fBoundsX(boundsX), m_fBoundsY(boundsY), m_fBoundsWidth(boundsWidth), m_fBoundsHeight(boundsHeight)
{
    updateBounds();
    getMainBounds().getLowerLeft().set(gridX * GM_GRID_CELL_SIZE, gridY * GM_GRID_CELL_SIZE);
    m_position.set(m_iGridX * GM_GRID_CELL_SIZE, m_iGridY * GM_GRID_CELL_SIZE);
    m_position.sub(getWidth() * m_fBoundsX, getHeight() * m_fBoundsY);
    m_position.add(getWidth() / 2, getHeight() / 2);
}

void GridLockedPhysicalEntity::updateBounds()
{
	getMainBounds().setWidth(getWidth());
	getMainBounds().setHeight(getHeight());

	PhysicalEntity::updateBounds();

	getMainBounds().getLowerLeft().add(getWidth() * m_fBoundsX, getHeight() * m_fBoundsY);
	getMainBounds().setWidth(getWidth() * m_fBoundsWidth);
	getMainBounds().setHeight(getHeight() * m_fBoundsHeight);
}

void GridLockedPhysicalEntity::snapToGrid(int gridCellSizeScalar)
{
    float left = getMainBounds().getLeft();
    float bottom = getMainBounds().getBottom();
    
    float gridCellSize = GM_GRID_CELL_SIZE * gridCellSizeScalar;
    m_iGridX = left / gridCellSize;
    
    m_iGridY = bottom / gridCellSize;
    
	getMainBounds().getLowerLeft().set(m_iGridX * gridCellSize, m_iGridY * gridCellSize);
    m_position.set(m_iGridX * gridCellSize, m_iGridY * gridCellSize);
    m_position.sub(getWidth() * m_fBoundsX, getHeight() * m_fBoundsY);
    m_position.add(getWidth() / 2, getHeight() / 2);
    
    m_iGridX *= gridCellSizeScalar;
    m_iGridY *= gridCellSizeScalar;

	updateBounds();
}

void GridLockedPhysicalEntity::placeOn(float itemTopY)
{
	m_position.setY(itemTopY);

	if (m_fBoundsY > 0)
	{
		m_position.sub(0, getHeight() * m_fBoundsY);
		m_position.add(0, getHeight() / 2 * .99f);
	}
	else
	{
		m_position.add(0, getMainBounds().getHeight() / 2 * .99f);
	}
	
	updateBounds();
}

int GridLockedPhysicalEntity::getGridX()
{
    return m_iGridX;
}

int GridLockedPhysicalEntity::getGridY()
{
    return m_iGridY;
}

RTTI_IMPL(GridLockedPhysicalEntity, PhysicalEntity);
