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

#define PLAYER_STATE_NONE 0
#define PLAYER_STATE_DASHING 1
#define PLAYER_STATE_STORING_HEAT 2
#define PLAYER_STATE_RELEASING_HEAT 3

class Player : public PopcornKernel
{
    RTTI_DECL;
    
public:
    Player(float x, float y, float width, float height);
    
    virtual void update(float deltaTime);
    
    void storeHeat(float intensity, int playerIndex);
    
    void releaseHeat(float intensity, int playerIndex);
    
    void dash();
    
    void noAction();
    
private:
    int m_iState;
    float m_fHeatManipIntensity;
    
    void handleHeatRelease();
};

#endif /* Player_hpp */
