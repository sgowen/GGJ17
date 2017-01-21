//
//  GamePadEvent.cpp
//  noctisgames-framework
//
//  Created by Stephen Gowen on 1/21/17.
//  Copyright (c) 2017 Noctis Games. All rights reserved.
//

#include "GamePadEvent.h"

GamePadEvent::GamePadEvent(int playerIndex, float x, float y, GamePad_Event_Type type) :
	m_iPlayerIndex(playerIndex),
	m_fX(x),
	m_fY(y),
	m_type(type)
{
	// Empty
}

GamePad_Event_Type GamePadEvent::getType()
{
	return m_type;
}

void GamePadEvent::setType(GamePad_Event_Type touchType)
{
	m_type = touchType;
}

float GamePadEvent::getX()
{
	return m_fX;
}

void GamePadEvent::setX(float x)
{
	m_fX = x;
}

float GamePadEvent::getY()
{
	return m_fY;
}

void GamePadEvent::setY(float y)
{
	m_fY = y;
}

int GamePadEvent::getPlayerIndex()
{
	return m_iPlayerIndex;
}

void GamePadEvent::setPlayerIndex(int playerIndex)
{
	m_iPlayerIndex = playerIndex;
}