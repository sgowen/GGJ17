//
//  VectorUtil.h
//  noctisgames-framework
//
//  Created by Stephen Gowen on 1/14/17.
//  Copyright (c) 2017 Noctis Games. All rights reserved.
//

#ifndef __noctisgames__VectorUtil__
#define __noctisgames__VectorUtil__

#include <vector>

class VectorUtil
{
public:
    template<typename T>
    static void cleanUpVectorOfPointers(std::vector<T*>& items)
    {
        for (typename std::vector<T*>::iterator i = items.begin(); i != items.end(); )
        {
            delete *i;
            i = items.erase(i);
        }
    }
    
private:
    // ctor, copy ctor, and assignment should be private in a Singleton
    VectorUtil();
    VectorUtil(const VectorUtil&);
    VectorUtil& operator=(const VectorUtil&);
};

#endif /* defined(__noctisgames__VectorUtil__) */
