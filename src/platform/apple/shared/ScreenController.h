//
//  ScreenController.h
//  ggj17
//
//  Created by Stephen Gowen on 10/14/16.
//  Copyright © 2017 Noctis Games. All rights reserved.
//

#import <Foundation/Foundation.h>

// C++
#include "MainScreen.h"

@interface ScreenController : NSObject

- (instancetype)initWithScreen:(MainScreen *)screen;

- (void)update:(float)deltaTime;

- (void)present;

- (void)resume;

- (void)pause;

@end
