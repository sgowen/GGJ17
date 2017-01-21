//
//  SaveData.h
//  ggj17
//
//  Created by Stephen Gowen on 3/11/16.
//  Copyright (c) 2017 Noctis Games. All rights reserved.
//

#ifdef __APPLE__
#include "TargetConditionals.h"
#endif

#if TARGET_OS_IPHONE
// Empty
#elif TARGET_OS_OSX
#import <Cocoa/Cocoa.h>
#endif

@interface SaveData : NSObject
{
    // Empty
}

+ (int)getDemoData;
+ (void)setDemoData:(int)demoData;

@end
