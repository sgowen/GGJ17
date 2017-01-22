//
//  GameSession.h
//  ggj17
//
//  Created by Stephen Gowen on 1/21/17.
//  Copyright © 2017 Noctis Games. All rights reserved.
//

#ifndef GameSession_h
#define GameSession_h

#include <vector>

#define GAME_SESSION (GameSession::getInstance())

class PopcornKernel;
class Player;
class Circle;

class GameSession
{
public:
    static GameSession* getInstance();
    
    void startGame();
    
    void update(float deltaTime);
    
    void reset();
    
    std::vector<PopcornKernel *>& getPopcornKernels();
    
    std::vector<Player *>& getPlayers();
    
    void setNumPlayersConnected(int numPlayers);
    
    Circle& getBoundingCircle();
    
    int getNumPlayersConnected();
    
    bool isSessionLive() { return m_isSessionLive; }
    
    float getStateTime() { return m_fStateTime; }
    
    int getWinningPlayerIndex() { return m_iWinningPlayerIndex; }
    
    bool hasGameEnded() { return m_hasGameEnded; }
    
    float getGameEndTime() { return m_fGameEndTime; }
    
private:
    std::vector<PopcornKernel *> m_popcornKernels; // TODO, randomly generate this using a file named "popcorn.bag"
    std::vector<Player *> m_players;
    Circle* m_circle;
    int m_iNumPlayersConnected;
    float m_fStateTime;
    float m_fGameEndTime;
    bool m_isSessionLive;
    int m_iWinningPlayerIndex;
    bool m_hasGameEnded;
    
    // ctor, copy ctor, and assignment should be private in a Singleton
    GameSession();
    GameSession(const GameSession&);
    GameSession& operator=(const GameSession&);
};

#endif /* GameSession_hpp */
