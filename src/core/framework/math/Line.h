//
//  Line.h
//  noctisgames-framework
//
//  Created by Stephen Gowen on 2/22/14.
//  Copyright (c) 2017 Noctis Games. All rights reserved.
//

#ifndef __noctisgames__Line__
#define __noctisgames__Line__

#include "Vector2D.h"

class Line
{
public:
    Line(float x1, float y1, float x2, float y2);
    
    Vector2D& getOrigin();
    
    Vector2D& getEnd();
    
private:
    Vector2D m_origin;
    Vector2D m_end;
};

#endif /* defined(__noctisgames__Line__) */
