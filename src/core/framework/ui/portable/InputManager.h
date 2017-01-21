//
//  InputManager.h
//  noctisgames-framework
//
//  Created by Stephen Gowen on 1/15/17.
//  Copyright (c) 2017 Noctis Games. All rights reserved.
//

#ifndef __noctisgames__InputManager__
#define __noctisgames__InputManager__

#include "TouchEvent.h"
#include "GamePadEvent.h"

#include <vector>

#define INPUT_MANAGER (InputManager::getInstance())

#define MAX_DRAGGED_EVENTS_PER_FRAME 3
#define STARTING_TOUCH_EVENT_POOL_SIZE 50

class InputManager
{
public:
    static InputManager* getInstance();
    
    void onTouch(Touch_Type type, float x, float y);
    
    void processTouchEvents();
    
    std::vector<TouchEvent*>& getTouchEvents();

	void onGamePadInput(GamePad_Event_Type type, int playerIndex, float x, float y);

	void processGamePadEvents();

	std::vector<GamePadEvent*>& getGamePadEvents();
    
private:
    std::vector<TouchEvent*> m_touchEvents;
    std::vector<TouchEvent*> m_touchEventsPool;
    std::vector<TouchEvent*> m_touchEventsBuffer;
	std::vector<GamePadEvent*> m_gamePadEvents;
	std::vector<GamePadEvent*> m_gamePadEventsPool;
	std::vector<GamePadEvent*> m_gamePadEventsBuffer;
    
    int m_iTouchPoolIndex;
	int m_iGamePadPoolIndex;
	bool m_isPressed;
    
    TouchEvent* newTouchEvent();
    
    void addTouchEventForType(Touch_Type type, float x, float y);

	GamePadEvent* newGamePadEvent();

	void addGamePadEventForType(GamePad_Event_Type type, int playerIndex, float x, float y);
    
    // ctor, copy ctor, and assignment should be private in a Singleton
    InputManager();
    InputManager(const InputManager&);
    InputManager& operator=(const InputManager&);
};

#endif /* defined(__noctisgames__InputManager__) */
