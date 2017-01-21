//
//  StateMachine.h
//  noctisgames-framework
//
//  Created by Stephen Gowen on 8/28/15.
//  Copyright (c) 2017 Noctis Games. All rights reserved.
//

#ifndef __noctisgames__StateMachine__
#define __noctisgames__StateMachine__

#include <cassert>

#include "State.h"

template <class entity_type, class state_type>
class StateMachine
{
public:
    
    StateMachine(entity_type* owner) : m_owner(owner), m_currentState(nullptr), m_previousState(nullptr), m_globalState(nullptr)
    {
        // Empty
    }
    
    virtual ~StateMachine()
    {
        // Empty
    }
    
    void setCurrentState(state_type* state)
    {
        m_currentState = state;
    }
    
    void setGlobalState(state_type* state)
    {
        m_globalState = state;
    }
    
    void setPreviousState(state_type* state)
    {
        m_previousState = state;
    }
    
    void execute() const
    {
        if (m_globalState)
        {
            m_globalState->execute(m_owner);
        }
        
        if (m_currentState)
        {
            m_currentState->execute(m_owner);
        }
    }
    
    void changeState(state_type* newState)
    {
        assert(newState && "<StateMachine::ChangeState>:trying to assign null state to current");
        
        m_previousState = m_currentState;
        
        m_currentState->exit(m_owner);
        
        m_currentState = newState;
        
        m_currentState->enter(m_owner);
    }
    
    void revertToPreviousState()
    {
        changeState(m_previousState);
    }
    
    bool isInState(const state_type* st)const
    {
        return m_currentState == st;
    }
    
    state_type* getCurrentState() const
    {
        return m_currentState;
    }
    
    state_type* getGlobalState() const
    {
        return m_globalState;
    }
    
    state_type* getPreviousState() const
    {
        return m_previousState;
    }
    
private:
    entity_type* m_owner;
    
    state_type* m_currentState;
    state_type* m_previousState;
    state_type* m_globalState;
};

#endif /* defined(__noctisgames__StateMachine__) */
