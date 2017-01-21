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

class EntityUtil
{
public:
	template<typename T>
	static void update(std::vector<T>& items, float deltaTime)
	{
		for (typename std::vector<T>::iterator i = items.begin(); i != items.end(); i++)
		{
			(*i)->update(deltaTime);
		}
	}

	template<typename T>
	static void updateAndClean(std::vector<T*>& items, float deltaTime)
	{
		for (typename std::vector<T*>::iterator i = items.begin(); i != items.end(); )
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
    
private:
    // ctor, copy ctor, and assignment should be private in a Singleton
    EntityUtil();
    EntityUtil(const EntityUtil&);
    EntityUtil& operator=(const EntityUtil&);
};

#endif /* defined(__noctisgames__EntityUtil__) */
