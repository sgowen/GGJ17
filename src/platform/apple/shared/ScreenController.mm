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
    short rawSoundId;
    short playerIndex;
    short soundId;
    while ((rawSoundId = SOUND_MANAGER->getCurrentSoundId()) > SOUND_NONE)
    {
        playerIndex = 0;
        while (rawSoundId >= 10000)
        {
            rawSoundId -= 10000;
            playerIndex++;
        }
        
        soundId = 0;
        while (rawSoundId >= 1000)
        {
            rawSoundId -= 1000;
            soundId++;
        }
        
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
				case MUSIC_LOAD_battleloop:
					[self loadMusic:@"Sound_music_battleloop"];
					break;
                case MUSIC_LOAD_menuloop:
                    [self loadMusic:@"Sound_music_menuloop"];
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
    
    [_appleSoundManager loadSound:@"beep" withExtension:@"wav" andNumCopies:4];
    [_appleSoundManager loadSound:@"Colonel_dash1" withExtension:@"wav" andNumCopies:4];
    [_appleSoundManager loadSound:@"Colonel_dashvoice" withExtension:@"wav" andNumCopies:4];
    [_appleSoundManager loadSound:@"Colonel_hurt1" withExtension:@"wav" andNumCopies:4];
    [_appleSoundManager loadSound:@"Colonel_hurt2" withExtension:@"wav" andNumCopies:4];
    [_appleSoundManager loadSound:@"Colonel_hurtvoice" withExtension:@"wav" andNumCopies:4];
    [_appleSoundManager loadSound:@"Colonel_KO" withExtension:@"wav" andNumCopies:4];
    [_appleSoundManager loadSound:@"Colonel_selected" withExtension:@"wav" andNumCopies:4];
    [_appleSoundManager loadSound:@"Colonel_storeheat" withExtension:@"wav" andNumCopies:4];
    [_appleSoundManager loadSound:@"Colonel_victory" withExtension:@"wav" andNumCopies:4];
    [_appleSoundManager loadSound:@"heatempty" withExtension:@"wav" andNumCopies:4];
    [_appleSoundManager loadSound:@"heatrelease" withExtension:@"wav" andNumCopies:4];
    [_appleSoundManager loadSound:@"heatstore" withExtension:@"wav" andNumCopies:4];
    [_appleSoundManager loadSound:@"kernelpop1" withExtension:@"wav" andNumCopies:4];
    [_appleSoundManager loadSound:@"kernelpop2" withExtension:@"wav" andNumCopies:4];
    [_appleSoundManager loadSound:@"kernelpop3" withExtension:@"wav" andNumCopies:4];
    [_appleSoundManager loadSound:@"Kobb_dash1" withExtension:@"wav" andNumCopies:4];
    [_appleSoundManager loadSound:@"Kobb_dash2" withExtension:@"wav" andNumCopies:4];
    [_appleSoundManager loadSound:@"Kobb_dashvoice" withExtension:@"wav" andNumCopies:4];
    [_appleSoundManager loadSound:@"Kobb_hurt1" withExtension:@"wav" andNumCopies:4];
    [_appleSoundManager loadSound:@"Kobb_hurt2" withExtension:@"wav" andNumCopies:4];
    [_appleSoundManager loadSound:@"Kobb_hurtvoice" withExtension:@"wav" andNumCopies:4];
    [_appleSoundManager loadSound:@"Kobb_KO" withExtension:@"wav" andNumCopies:4];
    [_appleSoundManager loadSound:@"Kobb_selected" withExtension:@"wav" andNumCopies:4];
    [_appleSoundManager loadSound:@"Kobb_storeheat" withExtension:@"wav" andNumCopies:4];
    [_appleSoundManager loadSound:@"Kobb_victory" withExtension:@"wav" andNumCopies:4];
    [_appleSoundManager loadSound:@"Mazy_dash1" withExtension:@"wav" andNumCopies:4];
    [_appleSoundManager loadSound:@"Mazy_dashvoice" withExtension:@"wav" andNumCopies:4];
    [_appleSoundManager loadSound:@"Mazy_hurt1" withExtension:@"wav" andNumCopies:4];
    [_appleSoundManager loadSound:@"Mazy_hurt2" withExtension:@"wav" andNumCopies:4];
    [_appleSoundManager loadSound:@"Mazy_hurtvoice" withExtension:@"wav" andNumCopies:4];
    [_appleSoundManager loadSound:@"Mazy_KO" withExtension:@"wav" andNumCopies:4];
    [_appleSoundManager loadSound:@"Mazy_selected" withExtension:@"wav" andNumCopies:4];
    [_appleSoundManager loadSound:@"Mazy_storeheat" withExtension:@"wav" andNumCopies:4];
    [_appleSoundManager loadSound:@"Mazy_victory" withExtension:@"wav" andNumCopies:4];
    [_appleSoundManager loadSound:@"Orville_dash1" withExtension:@"wav" andNumCopies:4];
    [_appleSoundManager loadSound:@"Orville_dash2" withExtension:@"wav" andNumCopies:4];
    [_appleSoundManager loadSound:@"Orville_dashvoice" withExtension:@"wav" andNumCopies:4];
    [_appleSoundManager loadSound:@"Orville_hurt1" withExtension:@"wav" andNumCopies:4];
    [_appleSoundManager loadSound:@"Orville_hurt2" withExtension:@"wav" andNumCopies:4];
    [_appleSoundManager loadSound:@"Orville_hurtvoice" withExtension:@"wav" andNumCopies:4];
    [_appleSoundManager loadSound:@"Orville_KO" withExtension:@"wav" andNumCopies:4];
    [_appleSoundManager loadSound:@"Orville_selected" withExtension:@"wav" andNumCopies:4];
    [_appleSoundManager loadSound:@"Orville_storeheat" withExtension:@"wav" andNumCopies:4];
    [_appleSoundManager loadSound:@"Orville_victory" withExtension:@"wav" andNumCopies:4];
    [_appleSoundManager loadSound:@"Sound_music_gamestart" withExtension:@"wav" andNumCopies:4];
    [_appleSoundManager loadSound:@"Sound_music_loseall" withExtension:@"wav" andNumCopies:4];
    [_appleSoundManager loadSound:@"Sound_music_startbattle" withExtension:@"wav" andNumCopies:4];
    [_appleSoundManager loadSound:@"Sound_music_victory" withExtension:@"wav" andNumCopies:4];
}

@end
