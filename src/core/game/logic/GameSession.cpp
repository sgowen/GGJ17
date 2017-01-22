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
#include "Circle.h"
#include "OverlapTester.h"
#include "SoundManager.h"
#include "SoundConstants.h"
#include "MusicConstants.h"

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
    if (m_isSessionLive)
    {
        return;
    }
    
	/* initialize random seed: */
	srand((unsigned int)time(0));

	int numPlayersConnected = m_iNumPlayersConnected;

	reset();

	for (int i = 0; i < 252; i++)
	{
		float x = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / CAM_WIDTH));
		float y = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / CAM_HEIGHT));

		Vector2D pos = Vector2D(x, y);
		while (!OverlapTester::isPointInCircle(pos, *m_circle))
		{
			x = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / CAM_WIDTH));
			y = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / CAM_HEIGHT));

			pos = Vector2D(x, y);
		}

        float delay = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 24));
		m_popcornKernels.push_back(new PopcornKernel(x, y, 0.4f, 0.4f, delay));
	}

	m_iNumPlayersConnected = numPlayersConnected;
	
	while (m_iNumPlayersConnected > m_players.size())
	{
        int index = m_players.size();

		float x = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / CAM_WIDTH));
		float y = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / CAM_HEIGHT));

		Vector2D pos = Vector2D(x, y);
		while (!OverlapTester::isPointInCircle(pos, *m_circle))
		{
			x = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / CAM_WIDTH));
			y = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / CAM_HEIGHT));

			pos = Vector2D(x, y);
		}

		m_players.push_back(new Player(index, x, y, 0.4f, 0.4f));
	}
    
    m_isSessionLive = true;
}

void GameSession::update(float deltaTime)
{
    if (!m_isSessionLive)
    {
        return;
    }
    
    m_fStateTime += deltaTime;
    
    if (m_fStateTime < 4)
    {
        return;
    }
    
    if (!m_startUpSoundHasPlayed)
    {
        SOUND_MANAGER->addMusicIdToPlayQueue(MUSIC_LOAD_battleloop);
        SOUND_MANAGER->addMusicIdToPlayQueue(MUSIC_PLAY_LOOP);
        
        m_startUpSoundHasPlayed = true;
    }
    
    if (m_hasGameEnded)
    {
        m_fGameEndTime += deltaTime;
        
		if (m_fGameEndTime > 2)
		{
			if (m_iWinningPlayerIndex > -1)
			{
				Player* player = m_players.at(m_iWinningPlayerIndex);
				player->update(deltaTime);

				if (!m_hasPlayedPlayerVictorySound)
				{
					player->playVictorySound();

					m_hasPlayedPlayerVictorySound = true;
				}
			}
		}
		else if (m_fGameEndTime < 1)
		{
			if (m_iWinningPlayerIndex > -1)
			{
				Player* player = m_players.at(m_iWinningPlayerIndex);
				player->update(deltaTime);

				if (!m_hasPlayedVictorySound)
				{
					SOUND_MANAGER->addSoundIdToPlayQueue(SOUND_victory);
					SOUND_MANAGER->addMusicIdToPlayQueue(MUSIC_PAUSE);

					m_hasPlayedVictorySound = true;
				}
			}
			else
			{
				if (!m_hasPlayedVictorySound)
				{
					SOUND_MANAGER->addSoundIdToPlayQueue(SOUND_loseall);
					SOUND_MANAGER->addMusicIdToPlayQueue(MUSIC_PAUSE);

					m_hasPlayedVictorySound = true;
				}
			}
		}
        
        return;
    }
    
    EntityUtil::updateAndClean(m_popcornKernels, deltaTime);
    EntityUtil::update(m_players, deltaTime);
    
    int winningPlayerIndex = -1;
    int numKernelsAlive = 0;
    int numPlayersAlive = 0;
    for (int i = 0; i < m_players.size(); i++)
    {
        Player* player = m_players.at(i);
        if (!player->isPopped())
        {
            winningPlayerIndex = i;
            numKernelsAlive++;
            numPlayersAlive++;
        }
    }
    
    for (int i = 0; i < m_popcornKernels.size(); i++)
    {
        PopcornKernel* popcornKernel = m_popcornKernels.at(i);
        if (!popcornKernel->isPopped())
        {
            numKernelsAlive++;
        }
    }
    
    if (numKernelsAlive == 1
		&& numPlayersAlive == 1)
    {
        m_iWinningPlayerIndex = winningPlayerIndex;
        m_hasGameEnded = true;
    }
    else if (numKernelsAlive == 0
             || numPlayersAlive == 0)
    {
        m_iWinningPlayerIndex = -1;
        m_hasGameEnded = true;
    }
}

#ifdef __APPLE__
#include "TargetConditionals.h"
#endif

void GameSession::reset()
{
	VectorUtil::cleanUpVectorOfPointers(m_popcornKernels);
    VectorUtil::cleanUpVectorOfPointers(m_players);
    
    m_iNumPlayersConnected = 0;
    m_isSessionLive = false;
    m_fStateTime = 0;
    m_iWinningPlayerIndex = -1;
    m_fGameEndTime = 0;
    m_hasGameEnded = false;
    m_startUpSoundHasPlayed = false;
    m_fGameTime = 0;
    m_battleMusicLoopStarted = false;
    m_hasPlayedVictorySound = false;
	m_hasPlayedPlayerVictorySound = false;
    
#if defined TARGET_OS_IPHONE || defined TARGET_OS_OSX || defined __ANDROID__
    setNumPlayersConnected(1);
#endif
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
        int index = m_players.size();
		m_players.push_back(new Player(index, 4, 4, 0.4f, 0.4f));
        
        SOUND_MANAGER->addSoundIdToPlayQueue(Sound_beep);
	}
}

Circle& GameSession::getBoundingCircle()
{
    return *m_circle;
}

int GameSession::getNumPlayersConnected()
{
    return m_iNumPlayersConnected;
}

GameSession::GameSession() : m_circle(new Circle(CAM_WIDTH / 2, CAM_HEIGHT / 2, CAM_WIDTH, CAM_HEIGHT)), m_iNumPlayersConnected(0), m_fStateTime(0), m_isSessionLive(false), m_iWinningPlayerIndex(-1), m_hasGameEnded(false), m_fGameEndTime(0), m_startUpSoundHasPlayed(false), m_fGameTime(0), m_battleMusicLoopStarted(false), m_hasPlayedVictorySound(false), m_hasPlayedPlayerVictorySound(false)
{
    // Empty
}
