//
//  MathUtil.h
//  noctisgames-framework
//
//  Created by Stephen Gowen on 7/28/16.
//  Copyright © 2017 Noctis Games. All rights reserved.
//

#ifndef __noctisgames__MathUtil__
#define __noctisgames__MathUtil__

#include <math.h>

inline float clamp(float x, float upper, float lower)
{
    return fminf(upper, fmaxf(x, lower));
}

#endif /* defined(__noctisgames__MathUtil__) */
