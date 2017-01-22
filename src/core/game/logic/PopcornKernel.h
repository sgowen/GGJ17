//
//  PopcornKernel.h
//  ggj17
//
//  Created by Stephen Gowen on 1/21/17.
//  Copyright © 2017 Noctis Games. All rights reserved.
//

#ifndef PopcornKernel_hpp
#define PopcornKernel_hpp

#include "PhysicalEntity.h"

class PopcornKernel : public PhysicalEntity
{
    RTTI_DECL;
    
public:
    PopcornKernel(float x, float y, float width, float height, float delay);
    
    virtual void update(float deltaTime);
    
    void acceptHeatTransfer(float heat);
    
    float getHeat();
    
    bool isPopped() { return m_isPopped; }
    
    void pop();
    
    void onHit(PopcornKernel* explodingKernel);

	void onPushed(PopcornKernel* pushingKernel);
    
protected:
    float m_fClamp;
    float m_fHeat;
	float m_fDelay;
    bool m_isPopped;
	float m_fKnockedTime;
	bool m_isKnocked;
	bool m_hasReceivedHeatTransfer;
	bool m_isPushed;
};

#endif /* PopcornKernel_hpp */
