//
//  RTTI.h
//  noctisgames-framework
//
//  Created by Stephen Gowen on 11/4/16.
//  Copyright (c) 2017 Noctis Games. All rights reserved.
//

#include "RTTI.h"

bool RTTI::derivesFrom(const RTTI & rtti) const
{
    const RTTI * pCompare = this;
    
    while (pCompare)
    {
        if (pCompare == &rtti)
        {
            return true;
        }
        
        pCompare = pCompare->m_pBaseRTTI;
    }
    
    return false;
}
