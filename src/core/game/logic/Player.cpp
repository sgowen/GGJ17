//
//  Player.cpp
//  ggj17
//
//  Created by Stephen Gowen on 1/21/17.
//  Copyright © 2017 Noctis Games. All rights reserved.
//

#include "Player.h"

Player::Player(float x, float y, float width, float height) : PopcornKernel(x, y, width, height)
{
    // Empty
}

void Player::update(float deltaTime)
{
    PhysicalEntity::update(deltaTime);
    
    // TODO
}

RTTI_IMPL(Player, PopcornKernel);
