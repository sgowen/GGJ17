//
//  sound_manager.cpp
//  dante
//
//  Created by Stephen Gowen on 10/20/16.
//  Copyright (c) 2016 Noctis Games. All rights reserved.
//

#include <jni.h>
#include <stdio.h>
#include "macros.h"

#include "SuperpoweredSoundManager.h"
#include "SuperpoweredAndroidAudioIO.h"

#include <SLES/OpenSLES.h>
#include <SLES/OpenSLES_AndroidConfiguration.h>

SuperpoweredSoundManager *superpoweredSoundManager;
std::vector<SuperpoweredAndroidAudioIO*> m_audioSystems;

static bool audioProcessingMusic(void *clientData, short int *audioIO, int numberOfSamples, int __unused samplerate)
{
    return ((SuperpoweredSoundManager *)clientData)->processMusic(audioIO, (unsigned int)numberOfSamples);
}

static bool audioProcessingSound1(void *clientData, short int *audioIO, int numberOfSamples, int __unused samplerate)
{
    return ((SuperpoweredSoundManager *)clientData)->processSound1(audioIO, (unsigned int)numberOfSamples);
}

static bool audioProcessingSound2(void *clientData, short int *audioIO, int numberOfSamples, int __unused samplerate)
{
    return ((SuperpoweredSoundManager *)clientData)->processSound2(audioIO, (unsigned int)numberOfSamples);
}

static bool audioProcessingSound3(void *clientData, short int *audioIO, int numberOfSamples, int __unused samplerate)
{
    return ((SuperpoweredSoundManager *)clientData)->processSound3(audioIO, (unsigned int)numberOfSamples);
}

static bool audioProcessingSound4(void *clientData, short int *audioIO, int numberOfSamples, int __unused samplerate)
{
    return ((SuperpoweredSoundManager *)clientData)->processSound4(audioIO, (unsigned int)numberOfSamples);
}

static bool audioProcessingSound5(void *clientData, short int *audioIO, int numberOfSamples, int __unused samplerate)
{
    return ((SuperpoweredSoundManager *)clientData)->processSound5(audioIO, (unsigned int)numberOfSamples);
}

static bool audioProcessingSound6(void *clientData, short int *audioIO, int numberOfSamples, int __unused samplerate)
{
    return ((SuperpoweredSoundManager *)clientData)->processSound6(audioIO, (unsigned int)numberOfSamples);
}

static bool audioProcessingSound7(void *clientData, short int *audioIO, int numberOfSamples, int __unused samplerate)
{
    return ((SuperpoweredSoundManager *)clientData)->processSound7(audioIO, (unsigned int)numberOfSamples);
}

static bool audioProcessingSound8(void *clientData, short int *audioIO, int numberOfSamples, int __unused samplerate)
{
    return ((SuperpoweredSoundManager *)clientData)->processSound8(audioIO, (unsigned int)numberOfSamples);
}

static bool audioProcessingSound9(void *clientData, short int *audioIO, int numberOfSamples, int __unused samplerate)
{
    return ((SuperpoweredSoundManager *)clientData)->processSound9(audioIO, (unsigned int)numberOfSamples);
}

static bool audioProcessingSound10(void *clientData, short int *audioIO, int numberOfSamples, int __unused samplerate)
{
    return ((SuperpoweredSoundManager *)clientData)->processSound10(audioIO, (unsigned int)numberOfSamples);
}

static bool audioProcessingSound11(void *clientData, short int *audioIO, int numberOfSamples, int __unused samplerate)
{
    return ((SuperpoweredSoundManager *)clientData)->processSound11(audioIO, (unsigned int)numberOfSamples);
}

/* These functions are called from Java. */
extern "C"
{
JNIEXPORT void JNICALL Java_com_noctisgames_dante_sound_SoundManager_init_1sound_1manager(JNIEnv* env, jclass cls, jint sample_rate, jint buffer_size);
    
JNIEXPORT void JNICALL Java_com_noctisgames_dante_sound_SoundManager_load_1sound(JNIEnv* env, jclass cls, jint rawResourceId, jstring apk_path, jint num_copies, jint fileOffset, jint fileLength);
    
JNIEXPORT void JNICALL Java_com_noctisgames_dante_sound_SoundManager_play_1sound(JNIEnv* env, jclass cls, jint rawResourceId, jfloat volume, jboolean isLooping);
    
JNIEXPORT void JNICALL Java_com_noctisgames_dante_sound_SoundManager_stop_1sound(JNIEnv* env, jclass cls, jint rawResourceId);
    
JNIEXPORT void JNICALL Java_com_noctisgames_dante_sound_SoundManager_stop_1all_1sounds(JNIEnv* env, jclass cls);
    
JNIEXPORT void JNICALL Java_com_noctisgames_dante_sound_SoundManager_stop_1all_1looping_1sounds(JNIEnv* env, jclass cls);
    
JNIEXPORT void JNICALL Java_com_noctisgames_dante_sound_SoundManager_load_1music(JNIEnv* env, jclass cls, jint rawResourceId, jstring apk_path, jint fileOffset, jint fileLength);
    
JNIEXPORT void JNICALL Java_com_noctisgames_dante_sound_SoundManager_play_1music(JNIEnv* env, jclass cls, jfloat volume, jboolean isLooping);
    
JNIEXPORT void JNICALL Java_com_noctisgames_dante_sound_SoundManager_set_1music_1volume(JNIEnv* env, jclass cls, jfloat volume);
    
JNIEXPORT void JNICALL Java_com_noctisgames_dante_sound_SoundManager_resume_1music(JNIEnv* env, jclass cls);
    
JNIEXPORT void JNICALL Java_com_noctisgames_dante_sound_SoundManager_pause_1music(JNIEnv* env, jclass cls);
};

JNIEXPORT void JNICALL Java_com_noctisgames_dante_sound_SoundManager_init_1sound_1manager(JNIEnv* env, jclass cls, jint sample_rate, jint buffer_size)
{
	UNUSED(cls);

    int sampleRate = sample_rate;
    int bufferSize = buffer_size;
	
    superpoweredSoundManager = new SuperpoweredSoundManager(sampleRate, bufferSize);
    
    m_audioSystems.push_back(new SuperpoweredAndroidAudioIO(sampleRate, bufferSize, false, true, audioProcessingMusic, superpoweredSoundManager, -1, SL_ANDROID_STREAM_MEDIA, bufferSize * 2));
    
    m_audioSystems.push_back(new SuperpoweredAndroidAudioIO(sampleRate, bufferSize, false, true, audioProcessingSound1, superpoweredSoundManager, -1, SL_ANDROID_STREAM_MEDIA, bufferSize * 2));
    m_audioSystems.push_back(new SuperpoweredAndroidAudioIO(sampleRate, bufferSize, false, true, audioProcessingSound2, superpoweredSoundManager, -1, SL_ANDROID_STREAM_MEDIA, bufferSize * 2));
    m_audioSystems.push_back(new SuperpoweredAndroidAudioIO(sampleRate, bufferSize, false, true, audioProcessingSound3, superpoweredSoundManager, -1, SL_ANDROID_STREAM_MEDIA, bufferSize * 2));
    m_audioSystems.push_back(new SuperpoweredAndroidAudioIO(sampleRate, bufferSize, false, true, audioProcessingSound4, superpoweredSoundManager, -1, SL_ANDROID_STREAM_MEDIA, bufferSize * 2));
    m_audioSystems.push_back(new SuperpoweredAndroidAudioIO(sampleRate, bufferSize, false, true, audioProcessingSound5, superpoweredSoundManager, -1, SL_ANDROID_STREAM_MEDIA, bufferSize * 2));
    m_audioSystems.push_back(new SuperpoweredAndroidAudioIO(sampleRate, bufferSize, false, true, audioProcessingSound6, superpoweredSoundManager, -1, SL_ANDROID_STREAM_MEDIA, bufferSize * 2));
    m_audioSystems.push_back(new SuperpoweredAndroidAudioIO(sampleRate, bufferSize, false, true, audioProcessingSound7, superpoweredSoundManager, -1, SL_ANDROID_STREAM_MEDIA, bufferSize * 2));
    m_audioSystems.push_back(new SuperpoweredAndroidAudioIO(sampleRate, bufferSize, false, true, audioProcessingSound8, superpoweredSoundManager, -1, SL_ANDROID_STREAM_MEDIA, bufferSize * 2));
    m_audioSystems.push_back(new SuperpoweredAndroidAudioIO(sampleRate, bufferSize, false, true, audioProcessingSound9, superpoweredSoundManager, -1, SL_ANDROID_STREAM_MEDIA, bufferSize * 2));
    m_audioSystems.push_back(new SuperpoweredAndroidAudioIO(sampleRate, bufferSize, false, true, audioProcessingSound10, superpoweredSoundManager, -1, SL_ANDROID_STREAM_MEDIA, bufferSize * 2));
    m_audioSystems.push_back(new SuperpoweredAndroidAudioIO(sampleRate, bufferSize, false, true, audioProcessingSound11, superpoweredSoundManager, -1, SL_ANDROID_STREAM_MEDIA, bufferSize * 2));
}

JNIEXPORT void JNICALL Java_com_noctisgames_dante_sound_SoundManager_load_1sound(JNIEnv* env, jclass cls, jint rawResourceId, jstring apk_path, jint num_copies, jint fileOffset, jint fileLength)
{
    UNUSED(env);
    UNUSED(cls);
    
    const char *path = env->GetStringUTFChars(apk_path, JNI_FALSE);
    
    superpoweredSoundManager->loadSound(rawResourceId, path, num_copies, fileOffset, fileLength);
}

JNIEXPORT void JNICALL Java_com_noctisgames_dante_sound_SoundManager_play_1sound(JNIEnv* env, jclass cls, jint rawResourceId, jfloat volume, jboolean isLooping)
{
    UNUSED(env);
    UNUSED(cls);
    
    superpoweredSoundManager->playSound(rawResourceId, volume, isLooping);
}

JNIEXPORT void JNICALL Java_com_noctisgames_dante_sound_SoundManager_stop_1sound(JNIEnv* env, jclass cls, jint rawResourceId)
{
    UNUSED(env);
    UNUSED(cls);
    
    superpoweredSoundManager->stopSound(rawResourceId);
}

JNIEXPORT void JNICALL Java_com_noctisgames_dante_sound_SoundManager_stop_1all_1sounds(JNIEnv* env, jclass cls)
{
    UNUSED(env);
    UNUSED(cls);
    
    superpoweredSoundManager->stopAllSounds();
}

JNIEXPORT void JNICALL Java_com_noctisgames_dante_sound_SoundManager_stop_1all_1looping_1sounds(JNIEnv* env, jclass cls)
{
    UNUSED(env);
    UNUSED(cls);
    
    superpoweredSoundManager->stopAllLoopingSounds();
}

JNIEXPORT void JNICALL Java_com_noctisgames_dante_sound_SoundManager_load_1music(JNIEnv* env, jclass cls, jint rawResourceId, jstring apk_path, jint fileOffset, jint fileLength)
{
    UNUSED(env);
    UNUSED(cls);
    
    const char *path = env->GetStringUTFChars(apk_path, JNI_FALSE);
    
    superpoweredSoundManager->loadMusic(rawResourceId, path, fileOffset, fileLength);
}

JNIEXPORT void JNICALL Java_com_noctisgames_dante_sound_SoundManager_play_1music(JNIEnv* env, jclass cls, jfloat volume, jboolean isLooping)
{
    UNUSED(env);
    UNUSED(cls);
    
    superpoweredSoundManager->playMusic(volume, isLooping);
}

JNIEXPORT void JNICALL Java_com_noctisgames_dante_sound_SoundManager_set_1music_1volume(JNIEnv* env, jclass cls, jfloat volume)
{
    UNUSED(env);
    UNUSED(cls);
    
    superpoweredSoundManager->setMusicVolume(volume);
}

JNIEXPORT void JNICALL Java_com_noctisgames_dante_sound_SoundManager_resume_1music(JNIEnv* env, jclass cls)
{
    UNUSED(env);
    UNUSED(cls);
    
    superpoweredSoundManager->resumeMusic();
}

JNIEXPORT void JNICALL Java_com_noctisgames_dante_sound_SoundManager_pause_1music(JNIEnv* env, jclass cls)
{
    UNUSED(env);
    UNUSED(cls);
    
    superpoweredSoundManager->pauseMusic();
}
