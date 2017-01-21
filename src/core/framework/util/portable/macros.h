//
//  macros.h
//  noctisgames-framework
//
//  Created by Stephen Gowen on 2/22/14.
//  Copyright (c) 2017 Noctis Games. All rights reserved.
//

#ifndef Macros_H
#define Macros_H

#define NG_M_PI 3.14159265358979323846

#define UNUSED(x) (void)(x)

#define BUFFER_OFFSET(i) ((void*)(i))

#define DEGREES_TO_RADIANS(angle) ((angle) / 180.0f * NG_M_PI)
#define RADIANS_TO_DEGREES(angle) ((angle) / NG_M_PI * 180.0f)

#endif /* Macros_H */
