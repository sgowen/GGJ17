//
//  FlagUtil.h
//  noctisgames-framework
//
//  Created by Stephen Gowen on 8/6/13.
//  Copyright (c) 2017 Noctis Games. All rights reserved.
//

#ifndef __noctisgames__FlagUtil__
#define __noctisgames__FlagUtil__

class FlagUtil
{
public:
    static bool isFlagSet(int value, int flag)
	{
		return (value & flag) == flag;
	}
    
    static int setFlag(int value, int flag)
	{
		return value | flag;
	}
    
    static int removeFlag(int value, int flag)
	{
		return value & ~flag;
	}
};

#endif /* defined(__noctisgames__FlagUtil__) */
