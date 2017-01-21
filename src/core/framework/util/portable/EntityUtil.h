//
//  EntityUtil.h
//  noctisgames-framework
//
//  Created by Stephen Gowen on 9/23/15.
//  Copyright (c) 2017 Noctis Games. All rights reserved.
//

#ifndef __noctisgames__EntityUtil__
#define __noctisgames__EntityUtil__

#include <vector>

class Entity;

class EntityUtil
{
public:
    static void updateAndClean(std::vector<Entity *>& items, float deltaTime);
    
private:
    // ctor, copy ctor, and assignment should be private in a Singleton
    EntityUtil();
    EntityUtil(const EntityUtil&);
    EntityUtil& operator=(const EntityUtil&);
};

#endif /* defined(__noctisgames__EntityUtil__) */
