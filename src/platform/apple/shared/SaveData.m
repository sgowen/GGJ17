//
//  SaveData.m
//  ggj17
//
//  Created by Stephen Gowen on 3/11/16.
//  Copyright (c) 2017 Noctis Games. All rights reserved.
//

#import "SaveData.h"

#import "NSUserDefaults+SecureAdditions.h"

@implementation SaveData

static NSString *KEY_DEMO_DATA;

+ (void)initialize
{
    [[NSUserDefaults standardUserDefaults] setSecret:@"noctis_games_ggj17"];
    
    KEY_DEMO_DATA = @"v0_0_1-demo_data";
}

+ (int)getDemoData
{
    return (int) [[NSUserDefaults standardUserDefaults] secretIntegerForKey:KEY_DEMO_DATA];
}

+ (void)setDemoData:(int)demoData
{
    [[NSUserDefaults standardUserDefaults] setSecretInteger:demoData forKey:KEY_DEMO_DATA];
}

@end
