//
//  Player.cpp
//  ggj17
//
//  Created by Stephen Gowen on 1/21/17.
//  Copyright © 2017 Noctis Games. All rights reserved.
//

#include "Player.h"

#include "MathUtil.h"

Player::Player(float x, float y, float width, float height) : PopcornKernel(x, y, width, height)
{
	m_fDelay = 0;
}

void Player::update(float deltaTime)
{
	PopcornKernel::update(deltaTime);

	float x = getVelocity().getX();
	float y = getVelocity().getY();

	x = clamp(x, 5, -5);
	y = clamp(y, 5, -5);

	getVelocity().set(x, y);
}

RTTI_IMPL(Player, PopcornKernel);
