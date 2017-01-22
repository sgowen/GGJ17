//
//  GameSession.cpp
//  ggj17
//
//  Created by Stephen Gowen on 1/21/17.
//  Copyright © 2017 Noctis Games. All rights reserved.
//

#include "GameSession.h"

#include "VectorUtil.h"

#include "PopcornKernel.h"
#include "Player.h"
#include "ScreenConstants.h"
#include "EntityUtil.h"

#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

GameSession* GameSession::getInstance()
{
    static GameSession *instance = new GameSession();
    return instance;
}

void GameSession::startGame()
{
	/* initialize random seed: */
	srand((unsigned int)time(0));

	int numPlayersConnected = m_iNumPlayersConnected;

	reset();

	for (int i = 0; i < 333; i++)
	{
		float x = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / CAM_WIDTH));
		float y = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / CAM_HEIGHT));
        float delay = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 52));
		m_popcornKernels.push_back(new PopcornKernel(x, y, 0.4f, 0.4f, delay));
	}

	m_iNumPlayersConnected = numPlayersConnected;
	
	while (m_iNumPlayersConnected > m_players.size())
	{
		m_players.push_back(new Player(4, 4, 0.4f, 0.4f));
	}
}

void GameSession::update(float deltaTime)
{
	EntityUtil::updateAndClean(m_popcornKernels, deltaTime);
	EntityUtil::update(m_players, deltaTime);
}

void GameSession::reset()
{
	VectorUtil::cleanUpVectorOfPointers(m_popcornKernels);
    VectorUtil::cleanUpVectorOfPointers(m_players);
    
    m_iNumPlayersConnected = 0;
}

std::vector<PopcornKernel *>& GameSession::getPopcornKernels()
{
    return m_popcornKernels;
}

std::vector<Player *>& GameSession::getPlayers()
{
    return m_players;
}

void GameSession::setNumPlayersConnected(int numPlayers)
{
    m_iNumPlayersConnected = numPlayers;

	while (m_iNumPlayersConnected > m_players.size())
	{
		m_players.push_back(new Player(4, 4, 0.4f, 0.4f));
	}
}

int GameSession::getNumPlayersConnected()
{
    return m_iNumPlayersConnected;
}

GameSession::GameSession() : m_iNumPlayersConnected(0)
{
    // Empty
}
