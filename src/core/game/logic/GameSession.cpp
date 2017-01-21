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

GameSession* GameSession::getInstance()
{
    static GameSession *instance = new GameSession();
    return instance;
}

void GameSession::startGame()
{
    for (int i = 0; i < m_iNumPlayersConnected; i++)
    {
        m_players.push_back(new Player(4, 4, 2, 2));
    }
}

void GameSession::update(float deltaTime)
{
    for (std::vector<PopcornKernel *>::iterator i = m_popcornKernels.begin(); i != m_popcornKernels.end(); i++)
    {
        (*i)->update(deltaTime);
    }
    
    for (std::vector<Player *>::iterator i = m_players.begin(); i != m_players.end(); i++)
    {
        (*i)->update(deltaTime);
    }
}

void GameSession::reset()
{
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
}

int GameSession::getNumPlayersConnected()
{
    return m_iNumPlayersConnected;
}

GameSession::GameSession() : m_iNumPlayersConnected(0)
{
    // Empty
}
