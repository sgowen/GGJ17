//
//  ScreenController.m
//  ggj17
//
//  Created by Stephen Gowen on 10/14/16.
//  Copyright © 2017 Noctis Games. All rights reserved.
//

#import "ScreenController.h"

#import "AppleSoundManager.h"
#import "SaveData.h"

// C++
#include "SoundConstants.h"
#include "MusicConstants.h"
#include "SoundManager.h"

@interface ScreenController ()
{
    MainScreen *_screen;
    AppleSoundManager *_appleSoundManager;
}

@end

@implementation ScreenController

- (instancetype)initWithScreen:(MainScreen *)screen
{
    self = [super init];
    
    if (self)
    {
        _screen = screen;
        
        [self initSoundEngine];
    }
    
    return self;
}

- (void)update:(float)deltaTime
{
    _screen->update(deltaTime);
}

- (void)present
{
    _screen->render();
    
    [self handleSound];
    [self handleMusic];
}

- (void)resume
{
    _screen->onResume();
}

- (void)pause
{
    _screen->onPause();
    
    [self pauseMusic];
}

#pragma mark Private

- (void)handleSound
{
    short soundId;
    while ((soundId = SOUND_MANAGER->getCurrentSoundId()) > SOUND_NONE)
    {
        [self playSound:soundId];
    }
}

- (void)handleMusic
{
    short musicId;
    while ((musicId = SOUND_MANAGER->getCurrentMusicId()) > MUSIC_NONE)
    {
		if (musicId > MUSIC_SET_VOLUME)
		{
			[self setMusicVolume:((musicId % 1000) / 100.0f)];
		}
		else
		{
			switch (musicId)
			{
				case MUSIC_LOAD_DEMO:
					[self loadMusic:@"music_demo"];
					break;
				case MUSIC_PLAY:
					[self playMusic:NO];
					break;
				case MUSIC_PLAY_LOOP:
					[self playMusic:YES];
					break;
				case MUSIC_PAUSE:
					[self pauseMusic];
					break;
				case MUSIC_RESUME:
					[self resumeMusic];
					break;
				default:
					break;
			}
		}
    }
}

- (void)loadMusic:(NSString *)fileName
{
    [_appleSoundManager loadMusic:fileName withExtension:@"wav"];
}

- (void)playMusic:(BOOL)isLooping
{
    [_appleSoundManager playMusic:1 isLooping:isLooping];
}

- (void)playSound:(int)soundId isLooping:(BOOL)isLooping
{
    int soundIndex = soundId - 1;
    [_appleSoundManager playSound:soundIndex volume:1.0f isLooping:isLooping];
}

- (void)playSound:(int)soundId
{
    [self playSound:soundId isLooping:NO];
}

- (void)stopSound:(int)soundId
{
    int soundIndex = soundId - 1;
    [_appleSoundManager stopSound:soundIndex];
}

- (void)stopAllSounds
{
    [_appleSoundManager stopAllSounds];
}

- (void)stopAllLoopingSounds
{
    [_appleSoundManager stopAllLoopingSounds];
}

- (void)pauseMusic
{
    [_appleSoundManager pauseMusic];
}

- (void)resumeMusic
{
    [_appleSoundManager resumeMusic];
}

- (void)setMusicVolume:(float)volume
{
    [_appleSoundManager setMusicVolume:volume];
}

- (void)initSoundEngine
{
    _appleSoundManager = [[AppleSoundManager alloc] init];
    
    [_appleSoundManager loadSound:@"sound_demo" withExtension:@"wav" andNumCopies:1];
}

@end
