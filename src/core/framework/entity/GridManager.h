//
//  GridLockedPhysicalEntity.h
//  noctisgames-framework
//
//  Created by Stephen Gowen on 2/6/16.
//  Copyright (c) 2017 Noctis Games. All rights reserved.
//

#ifndef __noctisgames__GridManager__
#define __noctisgames__GridManager__

#define GRID_MANAGER (GridManager::getInstance())
#define GM_GRID_CELL_SIZE (GRID_MANAGER->getGridCellSize())

class GridManager
{
public:
    static GridManager* getInstance();
    
    void setGridCellSize(float gridCellSize);
    
    float getGridCellSize();
    
private:
    float m_fGridCellSize;
    
    // ctor, copy ctor, and assignment should be private in a Singleton
    GridManager() {}
    GridManager(const GridManager&);
    GridManager& operator=(const GridManager&);
};

#endif /* defined(__noctisgames__GridManager__) */
