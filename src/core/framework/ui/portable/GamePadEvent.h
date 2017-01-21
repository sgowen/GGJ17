//
//  GamePadEvent.h
//  noctisgames-framework
//
//  Created by Stephen Gowen on 1/21/17.
//  Copyright (c) 2017 Noctis Games. All rights reserved.
//

#ifndef GamePadEvent_H
#define GamePadEvent_H

#include "GamePadEventType.h"

class GamePadEvent
{
private:
	GamePad_Event_Type m_type;
    float m_fX;
    float m_fY;
	int m_iPlayerIndex;
    
public:
    GamePadEvent(int playerIndex, float x, float y, GamePad_Event_Type type);

	GamePad_Event_Type getType();

	void setType(GamePad_Event_Type type);

	float getX();

	void setX(float x);

	float getY();

	void setY(float y);

	int getPlayerIndex();

	void setPlayerIndex(int playerIndex);
};

#endif /* GamePadEvent_H */
