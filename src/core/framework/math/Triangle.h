//
//  Triangle.h
//  noctisgames-framework
//
//  Created by Stephen Gowen on 2/22/14.
//  Copyright (c) 2017 Noctis Games. All rights reserved.
//

#ifndef __noctisgames__Triangle__
#define __noctisgames__Triangle__

#include "Line.h"
#include "Vector2D.h"

class Triangle
{
public:
    Triangle(float x1, float y1, float x2, float y2, float x3, float y3);
    
    void set(float x1, float y1, float x2, float y2, float x3, float y3);
    
    Vector2D& getPointA();
    
    Vector2D& getPointB();
    
    Vector2D& getPointC();
    
    Line& getSideA();
    
    Line& getSideB();
    
    Line& getSideC();
    
private:
    Line m_sideA;
    Line m_sideB;
    Line m_sideC;
};

#endif /* defined(__noctisgames__Triangle__) */
