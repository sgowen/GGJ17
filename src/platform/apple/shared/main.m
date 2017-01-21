//
//  main.m
//  ggj17
//
//  Created by Stephen Gowen on 2/22/14.
//  Copyright (c) 2017 Noctis Games. All rights reserved.
//

#ifdef __APPLE__
#include "TargetConditionals.h"
#endif

#if TARGET_OS_IPHONE
#import <UIKit/UIKit.h>
#import "AppDelegate.h"
#elif TARGET_OS_OSX
#import <Cocoa/Cocoa.h>
#endif

int main(int argc, char * argv[])
{
#if TARGET_OS_IPHONE
    @autoreleasepool
    {
        return UIApplicationMain(argc, argv, nil, NSStringFromClass([AppDelegate class]));
    }
#elif TARGET_OS_OSX
    return NSApplicationMain(argc, (const char**)argv);
#endif
}
