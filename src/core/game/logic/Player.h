//
//  Player.h
//  ggj17
//
//  Created by Stephen Gowen on 1/21/17.
//  Copyright © 2017 Noctis Games. All rights reserved.
//

#ifndef Player_hpp
#define Player_hpp

#include "PopcornKernel.h"

class Player : public PopcornKernel
{
    RTTI_DECL;
    
public:
    Player(float x, float y, float width, float height);
    
    virtual void update(float deltaTime);
};

#endif /* Player_hpp */
