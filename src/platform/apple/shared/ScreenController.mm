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
        
        [self playSound:rawSoundId];
    }
}

- (void)handleMusic
{
    short musicId;
    while ((musicId = SOUND_MANAGER->getCurrentMusicId()) > MUSIC_NONE)
    {
		if (musicId >= MUSIC_SET_VOLUME)
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
    
    [_appleSoundManager loadSound:@"Sound_beep" withExtension:@"wav" andNumCopies:1];
    [_appleSoundManager loadSound:@"Sound_Colonel_dash1" withExtension:@"wav" andNumCopies:1];
    [_appleSoundManager loadSound:@"Sound_Colonel_dashvoice" withExtension:@"wav" andNumCopies:1];
    [_appleSoundManager loadSound:@"Sound_Colonel_hurt1" withExtension:@"wav" andNumCopies:1];
    [_appleSoundManager loadSound:@"Sound_Colonel_hurt2" withExtension:@"wav" andNumCopies:1];
    [_appleSoundManager loadSound:@"Sound_Colonel_hurtvoice" withExtension:@"wav" andNumCopies:1];
    [_appleSoundManager loadSound:@"Sound_Colonel_KO" withExtension:@"wav" andNumCopies:1];
    [_appleSoundManager loadSound:@"Sound_Colonel_selected" withExtension:@"wav" andNumCopies:1];
    [_appleSoundManager loadSound:@"Sound_Colonel_storeheat" withExtension:@"wav" andNumCopies:1];
    [_appleSoundManager loadSound:@"Sound_Colonel_victory" withExtension:@"wav" andNumCopies:1];
    [_appleSoundManager loadSound:@"Sound_heatempty" withExtension:@"wav" andNumCopies:1];
    [_appleSoundManager loadSound:@"Sound_heatrelease" withExtension:@"wav" andNumCopies:1];
    [_appleSoundManager loadSound:@"Sound_heatstore" withExtension:@"wav" andNumCopies:1];
    [_appleSoundManager loadSound:@"Sound_kernelpop1" withExtension:@"wav" andNumCopies:6];
    [_appleSoundManager loadSound:@"Sound_kernelpop2" withExtension:@"wav" andNumCopies:1];
    [_appleSoundManager loadSound:@"Sound_kernelpop3" withExtension:@"wav" andNumCopies:6];
    [_appleSoundManager loadSound:@"Sound_Kobb_dash1" withExtension:@"wav" andNumCopies:1];
    [_appleSoundManager loadSound:@"Sound_Kobb_dash2" withExtension:@"wav" andNumCopies:1];
    [_appleSoundManager loadSound:@"Sound_Kobb_dashvoice" withExtension:@"wav" andNumCopies:1];
    [_appleSoundManager loadSound:@"Sound_Kobb_hurt1" withExtension:@"wav" andNumCopies:1];
    [_appleSoundManager loadSound:@"Sound_Kobb_hurt2" withExtension:@"wav" andNumCopies:1];
    [_appleSoundManager loadSound:@"Sound_Kobb_hurtvoice" withExtension:@"wav" andNumCopies:1];
    [_appleSoundManager loadSound:@"Sound_Kobb_KO" withExtension:@"wav" andNumCopies:1];
    [_appleSoundManager loadSound:@"Sound_Kobb_selected" withExtension:@"wav" andNumCopies:1];
    [_appleSoundManager loadSound:@"Sound_Kobb_storeheat" withExtension:@"wav" andNumCopies:1];
    [_appleSoundManager loadSound:@"Sound_Kobb_victory" withExtension:@"wav" andNumCopies:1];
    [_appleSoundManager loadSound:@"Sound_Mazy_dash1" withExtension:@"wav" andNumCopies:1];
    [_appleSoundManager loadSound:@"Sound_Mazy_dashvoice" withExtension:@"wav" andNumCopies:1];
    [_appleSoundManager loadSound:@"Sound_Mazy_hurt1" withExtension:@"wav" andNumCopies:1];
    [_appleSoundManager loadSound:@"Sound_Mazy_hurt2" withExtension:@"wav" andNumCopies:1];
    [_appleSoundManager loadSound:@"Sound_Mazy_hurtvoice" withExtension:@"wav" andNumCopies:1];
    [_appleSoundManager loadSound:@"Sound_Mazy_KO" withExtension:@"wav" andNumCopies:1];
    [_appleSoundManager loadSound:@"Sound_Mazy_selected" withExtension:@"wav" andNumCopies:1];
    [_appleSoundManager loadSound:@"Sound_Mazy_storeheat" withExtension:@"wav" andNumCopies:1];
    [_appleSoundManager loadSound:@"Sound_Mazy_victory" withExtension:@"wav" andNumCopies:1];
    [_appleSoundManager loadSound:@"Sound_Orville_dash1" withExtension:@"wav" andNumCopies:1];
    [_appleSoundManager loadSound:@"Sound_Orville_dash2" withExtension:@"wav" andNumCopies:1];
    [_appleSoundManager loadSound:@"Sound_Orville_dashvoice" withExtension:@"wav" andNumCopies:1];
    [_appleSoundManager loadSound:@"Sound_Orville_hurt1" withExtension:@"wav" andNumCopies:1];
    [_appleSoundManager loadSound:@"Sound_Orville_hurt2" withExtension:@"wav" andNumCopies:1];
    [_appleSoundManager loadSound:@"Sound_Orville_hurtvoice" withExtension:@"wav" andNumCopies:1];
    [_appleSoundManager loadSound:@"Sound_Orville_KO" withExtension:@"wav" andNumCopies:1];
    [_appleSoundManager loadSound:@"Sound_Orville_selected" withExtension:@"wav" andNumCopies:1];
    [_appleSoundManager loadSound:@"Sound_Orville_storeheat" withExtension:@"wav" andNumCopies:1];
    [_appleSoundManager loadSound:@"Sound_Orville_victory" withExtension:@"wav" andNumCopies:1];
    [_appleSoundManager loadSound:@"Sound_music_gamestart" withExtension:@"wav" andNumCopies:1];
    [_appleSoundManager loadSound:@"Sound_music_loseall" withExtension:@"wav" andNumCopies:1];
    [_appleSoundManager loadSound:@"Sound_music_startbattle" withExtension:@"wav" andNumCopies:1];
    [_appleSoundManager loadSound:@"Sound_music_victory" withExtension:@"wav" andNumCopies:1];
    [_appleSoundManager loadSound:@"Sound_beep2" withExtension:@"wav" andNumCopies:1];
}

@end
