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
    
    int getNumPlayersConnected();
    
private:
    std::vector<PopcornKernel *> m_popcornKernels; // TODO, randomly generate this using a file named "popcorn.bag"
    std::vector<Player *> m_players;
    int m_iNumPlayersConnected;
    
    // ctor, copy ctor, and assignment should be private in a Singleton
    GameSession();
    GameSession(const GameSession&);
    GameSession& operator=(const GameSession&);
};

#endif /* GameSession_hpp */
