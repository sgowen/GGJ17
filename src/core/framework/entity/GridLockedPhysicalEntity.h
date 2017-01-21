//
//  GridLockedPhysicalEntity.h
//  noctisgames-framework
//
//  Created by Stephen Gowen on 2/6/16.
//  Copyright (c) 2017 Noctis Games. All rights reserved.
//

#ifndef __noctisgames__GridLockedPhysicalEntity__
#define __noctisgames__GridLockedPhysicalEntity__

#include "PhysicalEntity.h"

#include "RTTI.h"

class GridLockedPhysicalEntity : public PhysicalEntity
{
    RTTI_DECL;
    
public:
    GridLockedPhysicalEntity(int gridX, int gridY, int gridWidth, int gridHeight, float boundsX = 0, float boundsY = 0, float boundsWidth = 1, float boundsHeight = 1);
    
	virtual void updateBounds();

	virtual void placeOn(float itemTopY);
		
	virtual void snapToGrid(int gridCellSizeScalar = 1);

	int getGridX();
    
    int getGridY();
    
protected:
	float m_fBoundsX;
	float m_fBoundsY;
	float m_fBoundsWidth;
	float m_fBoundsHeight;
    int m_iGridX;
    int m_iGridY;
    int m_iGridWidth;
    int m_iGridHeight;
};

#endif /* defined(__noctisgames__GridLockedPhysicalEntity__) */
