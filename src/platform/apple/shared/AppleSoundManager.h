//
//  AppleSoundManager.h
//  ggj17
//
//  Created by Stephen Gowen on 10/23/16.
//  Copyright © 2017 Noctis Games. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface AppleSoundManager : NSObject

- (void)loadSound:(NSString *)path withExtension:(NSString *)ext andNumCopies:(int)nc;

- (void)playSound:(int)rawResourceId volume:(float)volume isLooping:(bool)isLooping;

- (void)stopSound:(int)rawResourceId;

- (void)stopAllSounds;

- (void)stopAllLoopingSounds;

- (void)loadMusic:(NSString *)path withExtension:(NSString *)ext;

- (void)playMusic:(float)volume isLooping:(bool)isLooping;

- (void)setMusicVolume:(float)volume;

- (void)resumeMusic;

- (void)pauseMusic;

@end
