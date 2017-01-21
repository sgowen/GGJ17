//
//  AppleSoundManager.m
//  ggj17
//
//  Created by Stephen Gowen on 10/23/16.
//  Copyright © 2017 Noctis Games. All rights reserved.
//

#import "AppleSoundManager.h"

#ifdef __APPLE__
#include "TargetConditionals.h"
#endif

#if TARGET_OS_IPHONE
#import "SuperpoweredIOSAudioIO.h"
#elif TARGET_OS_OSX
#import "SuperpoweredOSXAudioIO.h"
#endif

#include "SuperpoweredSoundManager.h"

@interface AppleSoundManager ()
{
    SuperpoweredSoundManager* _superpoweredSoundManager;
    NSMutableArray *_audioSystems;
    int _soundIndexCounter;
}

@end

@implementation AppleSoundManager

#if TARGET_OS_IPHONE
static bool audioProcessingMusic(void *clientData, float **buffers, unsigned int inputChannels, unsigned int outputChannels, unsigned int numberOfSamples, unsigned int sampleRate, uint64_t hostTime)
{
    return ((SuperpoweredSoundManager *)clientData)->processMusic(buffers, (unsigned int)numberOfSamples, sampleRate);
}

static bool audioProcessingSound1(void *clientData, float **buffers, unsigned int inputChannels, unsigned int outputChannels, unsigned int numberOfSamples, unsigned int sampleRate, uint64_t hostTime)
{
    return ((SuperpoweredSoundManager *)clientData)->processSound1(buffers, (unsigned int)numberOfSamples, sampleRate);
}

static bool audioProcessingSound2(void *clientData, float **buffers, unsigned int inputChannels, unsigned int outputChannels, unsigned int numberOfSamples, unsigned int sampleRate, uint64_t hostTime)
{
    return ((SuperpoweredSoundManager *)clientData)->processSound2(buffers, (unsigned int)numberOfSamples, sampleRate);
}

static bool audioProcessingSound3(void *clientData, float **buffers, unsigned int inputChannels, unsigned int outputChannels, unsigned int numberOfSamples, unsigned int sampleRate, uint64_t hostTime)
{
    return ((SuperpoweredSoundManager *)clientData)->processSound3(buffers, (unsigned int)numberOfSamples, sampleRate);
}

static bool audioProcessingSound4(void *clientData, float **buffers, unsigned int inputChannels, unsigned int outputChannels, unsigned int numberOfSamples, unsigned int sampleRate, uint64_t hostTime)
{
    return ((SuperpoweredSoundManager *)clientData)->processSound4(buffers, (unsigned int)numberOfSamples, sampleRate);
}

static bool audioProcessingSound5(void *clientData, float **buffers, unsigned int inputChannels, unsigned int outputChannels, unsigned int numberOfSamples, unsigned int sampleRate, uint64_t hostTime)
{
    return ((SuperpoweredSoundManager *)clientData)->processSound5(buffers, (unsigned int)numberOfSamples, sampleRate);
}

static bool audioProcessingSound6(void *clientData, float **buffers, unsigned int inputChannels, unsigned int outputChannels, unsigned int numberOfSamples, unsigned int sampleRate, uint64_t hostTime)
{
    return ((SuperpoweredSoundManager *)clientData)->processSound6(buffers, (unsigned int)numberOfSamples, sampleRate);
}

static bool audioProcessingSound7(void *clientData, float **buffers, unsigned int inputChannels, unsigned int outputChannels, unsigned int numberOfSamples, unsigned int sampleRate, uint64_t hostTime)
{
    return ((SuperpoweredSoundManager *)clientData)->processSound7(buffers, (unsigned int)numberOfSamples, sampleRate);
}

static bool audioProcessingSound8(void *clientData, float **buffers, unsigned int inputChannels, unsigned int outputChannels, unsigned int numberOfSamples, unsigned int sampleRate, uint64_t hostTime)
{
    return ((SuperpoweredSoundManager *)clientData)->processSound8(buffers, (unsigned int)numberOfSamples, sampleRate);
}

static bool audioProcessingSound9(void *clientData, float **buffers, unsigned int inputChannels, unsigned int outputChannels, unsigned int numberOfSamples, unsigned int sampleRate, uint64_t hostTime)
{
    return ((SuperpoweredSoundManager *)clientData)->processSound9(buffers, (unsigned int)numberOfSamples, sampleRate);
}

static bool audioProcessingSound10(void *clientData, float **buffers, unsigned int inputChannels, unsigned int outputChannels, unsigned int numberOfSamples, unsigned int sampleRate, uint64_t hostTime)
{
    return ((SuperpoweredSoundManager *)clientData)->processSound10(buffers, (unsigned int)numberOfSamples, sampleRate);
}

static bool audioProcessingSound11(void *clientData, float **buffers, unsigned int inputChannels, unsigned int outputChannels, unsigned int numberOfSamples, unsigned int sampleRate, uint64_t hostTime)
{
    return ((SuperpoweredSoundManager *)clientData)->processSound11(buffers, (unsigned int)numberOfSamples, sampleRate);
}
#elif TARGET_OS_OSX
static bool audioProcessingMusic(void *clientData, float **inputBuffers, unsigned int inputChannels, float **outputBuffers, unsigned int outputChannels, unsigned int numberOfSamples, unsigned int sampleRate, uint64_t hostTime)
{
    return ((SuperpoweredSoundManager *)clientData)->processMusic(outputBuffers, (unsigned int)numberOfSamples, sampleRate);
}

static bool audioProcessingSound1(void *clientData, float **inputBuffers, unsigned int inputChannels, float **outputBuffers, unsigned int outputChannels, unsigned int numberOfSamples, unsigned int sampleRate, uint64_t hostTime)
{
    return ((SuperpoweredSoundManager *)clientData)->processSound1(outputBuffers, (unsigned int)numberOfSamples, sampleRate);
}

static bool audioProcessingSound2(void *clientData, float **inputBuffers, unsigned int inputChannels, float **outputBuffers, unsigned int outputChannels, unsigned int numberOfSamples, unsigned int sampleRate, uint64_t hostTime)
{
    return ((SuperpoweredSoundManager *)clientData)->processSound2(outputBuffers, (unsigned int)numberOfSamples, sampleRate);
}

static bool audioProcessingSound3(void *clientData, float **inputBuffers, unsigned int inputChannels, float **outputBuffers, unsigned int outputChannels, unsigned int numberOfSamples, unsigned int sampleRate, uint64_t hostTime)
{
    return ((SuperpoweredSoundManager *)clientData)->processSound3(outputBuffers, (unsigned int)numberOfSamples, sampleRate);
}

static bool audioProcessingSound4(void *clientData, float **inputBuffers, unsigned int inputChannels, float **outputBuffers, unsigned int outputChannels, unsigned int numberOfSamples, unsigned int sampleRate, uint64_t hostTime)
{
    return ((SuperpoweredSoundManager *)clientData)->processSound4(outputBuffers, (unsigned int)numberOfSamples, sampleRate);
}

static bool audioProcessingSound5(void *clientData, float **inputBuffers, unsigned int inputChannels, float **outputBuffers, unsigned int outputChannels, unsigned int numberOfSamples, unsigned int sampleRate, uint64_t hostTime)
{
    return ((SuperpoweredSoundManager *)clientData)->processSound5(outputBuffers, (unsigned int)numberOfSamples, sampleRate);
}

static bool audioProcessingSound6(void *clientData, float **inputBuffers, unsigned int inputChannels, float **outputBuffers, unsigned int outputChannels, unsigned int numberOfSamples, unsigned int sampleRate, uint64_t hostTime)
{
    return ((SuperpoweredSoundManager *)clientData)->processSound6(outputBuffers, (unsigned int)numberOfSamples, sampleRate);
}

static bool audioProcessingSound7(void *clientData, float **inputBuffers, unsigned int inputChannels, float **outputBuffers, unsigned int outputChannels, unsigned int numberOfSamples, unsigned int sampleRate, uint64_t hostTime)
{
    return ((SuperpoweredSoundManager *)clientData)->processSound7(outputBuffers, (unsigned int)numberOfSamples, sampleRate);
}

static bool audioProcessingSound8(void *clientData, float **inputBuffers, unsigned int inputChannels, float **outputBuffers, unsigned int outputChannels, unsigned int numberOfSamples, unsigned int sampleRate, uint64_t hostTime)
{
    return ((SuperpoweredSoundManager *)clientData)->processSound8(outputBuffers, (unsigned int)numberOfSamples, sampleRate);
}

static bool audioProcessingSound9(void *clientData, float **inputBuffers, unsigned int inputChannels, float **outputBuffers, unsigned int outputChannels, unsigned int numberOfSamples, unsigned int sampleRate, uint64_t hostTime)
{
    return ((SuperpoweredSoundManager *)clientData)->processSound9(outputBuffers, (unsigned int)numberOfSamples, sampleRate);
}

static bool audioProcessingSound10(void *clientData, float **inputBuffers, unsigned int inputChannels, float **outputBuffers, unsigned int outputChannels, unsigned int numberOfSamples, unsigned int sampleRate, uint64_t hostTime)
{
    return ((SuperpoweredSoundManager *)clientData)->processSound10(outputBuffers, (unsigned int)numberOfSamples, sampleRate);
}

static bool audioProcessingSound11(void *clientData, float **inputBuffers, unsigned int inputChannels, float **outputBuffers, unsigned int outputChannels, unsigned int numberOfSamples, unsigned int sampleRate, uint64_t hostTime)
{
    return ((SuperpoweredSoundManager *)clientData)->processSound11(outputBuffers, (unsigned int)numberOfSamples, sampleRate);
}
#endif

- (instancetype)init
{
    self = [super init];
    
    if (self)
    {
        int sampleRate = 44100;
        _superpoweredSoundManager = new SuperpoweredSoundManager(sampleRate);
        
        _audioSystems = [[NSMutableArray alloc] init];
        
#if TARGET_OS_IPHONE
        [_audioSystems addObject:[[SuperpoweredIOSAudioIO alloc] initWithDelegate:(id<SuperpoweredIOSAudioIODelegate>)self preferredBufferSize:12 preferredMinimumSamplerate:sampleRate audioSessionCategory:AVAudioSessionCategoryPlayback channels:2 audioProcessingCallback:audioProcessingMusic clientdata:_superpoweredSoundManager]];
         
         [_audioSystems addObject:[[SuperpoweredIOSAudioIO alloc] initWithDelegate:(id<SuperpoweredIOSAudioIODelegate>)self preferredBufferSize:12 preferredMinimumSamplerate:sampleRate audioSessionCategory:AVAudioSessionCategoryPlayback channels:2 audioProcessingCallback:audioProcessingSound1 clientdata:_superpoweredSoundManager]];
        [_audioSystems addObject:[[SuperpoweredIOSAudioIO alloc] initWithDelegate:(id<SuperpoweredIOSAudioIODelegate>)self preferredBufferSize:12 preferredMinimumSamplerate:sampleRate audioSessionCategory:AVAudioSessionCategoryPlayback channels:2 audioProcessingCallback:audioProcessingSound2 clientdata:_superpoweredSoundManager]];
        [_audioSystems addObject:[[SuperpoweredIOSAudioIO alloc] initWithDelegate:(id<SuperpoweredIOSAudioIODelegate>)self preferredBufferSize:12 preferredMinimumSamplerate:sampleRate audioSessionCategory:AVAudioSessionCategoryPlayback channels:2 audioProcessingCallback:audioProcessingSound3 clientdata:_superpoweredSoundManager]];
        [_audioSystems addObject:[[SuperpoweredIOSAudioIO alloc] initWithDelegate:(id<SuperpoweredIOSAudioIODelegate>)self preferredBufferSize:12 preferredMinimumSamplerate:sampleRate audioSessionCategory:AVAudioSessionCategoryPlayback channels:2 audioProcessingCallback:audioProcessingSound4 clientdata:_superpoweredSoundManager]];
        [_audioSystems addObject:[[SuperpoweredIOSAudioIO alloc] initWithDelegate:(id<SuperpoweredIOSAudioIODelegate>)self preferredBufferSize:12 preferredMinimumSamplerate:sampleRate audioSessionCategory:AVAudioSessionCategoryPlayback channels:2 audioProcessingCallback:audioProcessingSound5 clientdata:_superpoweredSoundManager]];
        [_audioSystems addObject:[[SuperpoweredIOSAudioIO alloc] initWithDelegate:(id<SuperpoweredIOSAudioIODelegate>)self preferredBufferSize:12 preferredMinimumSamplerate:sampleRate audioSessionCategory:AVAudioSessionCategoryPlayback channels:2 audioProcessingCallback:audioProcessingSound6 clientdata:_superpoweredSoundManager]];
        [_audioSystems addObject:[[SuperpoweredIOSAudioIO alloc] initWithDelegate:(id<SuperpoweredIOSAudioIODelegate>)self preferredBufferSize:12 preferredMinimumSamplerate:sampleRate audioSessionCategory:AVAudioSessionCategoryPlayback channels:2 audioProcessingCallback:audioProcessingSound7 clientdata:_superpoweredSoundManager]];
        [_audioSystems addObject:[[SuperpoweredIOSAudioIO alloc] initWithDelegate:(id<SuperpoweredIOSAudioIODelegate>)self preferredBufferSize:12 preferredMinimumSamplerate:sampleRate audioSessionCategory:AVAudioSessionCategoryPlayback channels:2 audioProcessingCallback:audioProcessingSound8 clientdata:_superpoweredSoundManager]];
        [_audioSystems addObject:[[SuperpoweredIOSAudioIO alloc] initWithDelegate:(id<SuperpoweredIOSAudioIODelegate>)self preferredBufferSize:12 preferredMinimumSamplerate:sampleRate audioSessionCategory:AVAudioSessionCategoryPlayback channels:2 audioProcessingCallback:audioProcessingSound9 clientdata:_superpoweredSoundManager]];
        [_audioSystems addObject:[[SuperpoweredIOSAudioIO alloc] initWithDelegate:(id<SuperpoweredIOSAudioIODelegate>)self preferredBufferSize:12 preferredMinimumSamplerate:sampleRate audioSessionCategory:AVAudioSessionCategoryPlayback channels:2 audioProcessingCallback:audioProcessingSound10 clientdata:_superpoweredSoundManager]];
        [_audioSystems addObject:[[SuperpoweredIOSAudioIO alloc] initWithDelegate:(id<SuperpoweredIOSAudioIODelegate>)self preferredBufferSize:12 preferredMinimumSamplerate:sampleRate audioSessionCategory:AVAudioSessionCategoryPlayback channels:2 audioProcessingCallback:audioProcessingSound11 clientdata:_superpoweredSoundManager]];
#elif TARGET_OS_OSX
        [_audioSystems addObject:[[SuperpoweredOSXAudioIO alloc] initWithDelegate:nil preferredBufferSizeMs:12 numberOfChannels:2 enableInput:false enableOutput:true]];
        
        [_audioSystems addObject:[[SuperpoweredOSXAudioIO alloc] initWithDelegate:nil preferredBufferSizeMs:12 numberOfChannels:2 enableInput:false enableOutput:true]];
        [_audioSystems addObject:[[SuperpoweredOSXAudioIO alloc] initWithDelegate:nil preferredBufferSizeMs:12 numberOfChannels:2 enableInput:false enableOutput:true]];
        [_audioSystems addObject:[[SuperpoweredOSXAudioIO alloc] initWithDelegate:nil preferredBufferSizeMs:12 numberOfChannels:2 enableInput:false enableOutput:true]];
        [_audioSystems addObject:[[SuperpoweredOSXAudioIO alloc] initWithDelegate:nil preferredBufferSizeMs:12 numberOfChannels:2 enableInput:false enableOutput:true]];
        [_audioSystems addObject:[[SuperpoweredOSXAudioIO alloc] initWithDelegate:nil preferredBufferSizeMs:12 numberOfChannels:2 enableInput:false enableOutput:true]];
        [_audioSystems addObject:[[SuperpoweredOSXAudioIO alloc] initWithDelegate:nil preferredBufferSizeMs:12 numberOfChannels:2 enableInput:false enableOutput:true]];
        [_audioSystems addObject:[[SuperpoweredOSXAudioIO alloc] initWithDelegate:nil preferredBufferSizeMs:12 numberOfChannels:2 enableInput:false enableOutput:true]];
        [_audioSystems addObject:[[SuperpoweredOSXAudioIO alloc] initWithDelegate:nil preferredBufferSizeMs:12 numberOfChannels:2 enableInput:false enableOutput:true]];
        [_audioSystems addObject:[[SuperpoweredOSXAudioIO alloc] initWithDelegate:nil preferredBufferSizeMs:12 numberOfChannels:2 enableInput:false enableOutput:true]];
        [_audioSystems addObject:[[SuperpoweredOSXAudioIO alloc] initWithDelegate:nil preferredBufferSizeMs:12 numberOfChannels:2 enableInput:false enableOutput:true]];
        [_audioSystems addObject:[[SuperpoweredOSXAudioIO alloc] initWithDelegate:nil preferredBufferSizeMs:12 numberOfChannels:2 enableInput:false enableOutput:true]];
        
        [[_audioSystems objectAtIndex:0] setProcessingCallback_C:audioProcessingMusic clientdata:_superpoweredSoundManager];
        
        [[_audioSystems objectAtIndex:1] setProcessingCallback_C:audioProcessingSound1 clientdata:_superpoweredSoundManager];
        [[_audioSystems objectAtIndex:2] setProcessingCallback_C:audioProcessingSound2 clientdata:_superpoweredSoundManager];
        [[_audioSystems objectAtIndex:3] setProcessingCallback_C:audioProcessingSound3 clientdata:_superpoweredSoundManager];
        [[_audioSystems objectAtIndex:4] setProcessingCallback_C:audioProcessingSound4 clientdata:_superpoweredSoundManager];
        [[_audioSystems objectAtIndex:5] setProcessingCallback_C:audioProcessingSound5 clientdata:_superpoweredSoundManager];
        [[_audioSystems objectAtIndex:6] setProcessingCallback_C:audioProcessingSound6 clientdata:_superpoweredSoundManager];
        [[_audioSystems objectAtIndex:7] setProcessingCallback_C:audioProcessingSound7 clientdata:_superpoweredSoundManager];
        [[_audioSystems objectAtIndex:8] setProcessingCallback_C:audioProcessingSound8 clientdata:_superpoweredSoundManager];
        [[_audioSystems objectAtIndex:9] setProcessingCallback_C:audioProcessingSound9 clientdata:_superpoweredSoundManager];
        [[_audioSystems objectAtIndex:10] setProcessingCallback_C:audioProcessingSound10 clientdata:_superpoweredSoundManager];
        [[_audioSystems objectAtIndex:11] setProcessingCallback_C:audioProcessingSound11 clientdata:_superpoweredSoundManager];
#endif
        
        for (NSObject *audioSystem in _audioSystems)
        {
            [audioSystem performSelector:@selector(start) withObject:nil];
        }
        
        _soundIndexCounter = 0;
    }
    
    return self;
}

- (void)loadSound:(NSString *)path withExtension:(NSString *)ext andNumCopies:(int)nc
{
    const char *bundlePath = [[[NSBundle mainBundle] pathForResource:path ofType:ext] fileSystemRepresentation];
    
    _superpoweredSoundManager->loadSound(_soundIndexCounter++, bundlePath, nc);
}

- (void)playSound:(int)rawResourceId volume:(float)volume isLooping:(bool)isLooping
{
    _superpoweredSoundManager->playSound(rawResourceId, volume, isLooping);
}

- (void)stopSound:(int)rawResourceId
{
    _superpoweredSoundManager->stopSound(rawResourceId);
}

- (void)stopAllSounds
{
    _superpoweredSoundManager->stopAllSounds();
}

- (void)stopAllLoopingSounds
{
    _superpoweredSoundManager->stopAllLoopingSounds();
}

- (void)loadMusic:(NSString *)path withExtension:(NSString *)ext
{
    const char *bundlePath = [[[NSBundle mainBundle] pathForResource:path ofType:ext] fileSystemRepresentation];
    
    _superpoweredSoundManager->loadMusic(1337, bundlePath);
}

- (void)playMusic:(float)volume isLooping:(bool)isLooping
{
    _superpoweredSoundManager->playMusic(volume, isLooping);
}

- (void)setMusicVolume:(float)volume
{
    _superpoweredSoundManager->setMusicVolume(volume);
}

- (void)resumeMusic
{
    _superpoweredSoundManager->resumeMusic();
}

- (void)pauseMusic
{
    _superpoweredSoundManager->pauseMusic();
}

#if TARGET_OS_IPHONE
- (void)interruptionStarted {}
- (void)interruptionEnded {}
- (void)recordPermissionRefused {}
- (void)mapChannels:(multiOutputChannelMap *)outputMap inputMap:(multiInputChannelMap *)inputMap externalAudioDeviceName:(NSString *)externalAudioDeviceName outputsAndInputs:(NSString *)outputsAndInputs {}
#endif

@end
