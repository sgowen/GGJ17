//
//  EntityUtil.cpp
//  noctisgames-framework
//
//  Created by Stephen Gowen on 1/14/17.
//  Copyright (c) 2017 Noctis Games. All rights reserved.
//

#include "EntityUtil.h"

#include "Entity.h"

void EntityUtil::updateAndClean(std::vector<Entity *>& items, float deltaTime)
{
    for (std::vector<Entity *>::iterator i = items.begin(); i != items.end(); )
    {
        (*i)->update(deltaTime);
        
        if ((*i)->isRequestingDeletion())
        {
            (*i)->onDeletion();
            
            delete *i;
            i = items.erase(i);
        }
        else
        {
            i++;
        }
    }
}
