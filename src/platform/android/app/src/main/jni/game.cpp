//
//  game.cpp
//  dante
//
//  Created by Stephen Gowen on 2/22/14.
//  Copyright (c) 2016 Noctis Games. All rights reserved.
//

#include <jni.h>
#include <stdio.h>

#include "macros.h"
#include "MainScreen.h"
#include "InputManager.h"
#include "SoundManager.h"

MainScreen *screen;

/* These functions are called from Java. */
extern "C"
{
JNIEXPORT void JNICALL Java_com_noctisgames_dante_Game_init(JNIEnv* env, jclass cls);

JNIEXPORT void JNICALL Java_com_noctisgames_dante_Game_on_1surface_1created(JNIEnv * env, jclass cls);

JNIEXPORT void JNICALL Java_com_noctisgames_dante_Game_on_1surface_1changed(JNIEnv * env, jclass cls, jint pixel_width, jint pixel_height);

JNIEXPORT void JNICALL Java_com_noctisgames_dante_Game_on_1resume(JNIEnv* env, jclass cls);

JNIEXPORT void JNICALL Java_com_noctisgames_dante_Game_on_1pause(JNIEnv* env, jclass cls);

JNIEXPORT void JNICALL Java_com_noctisgames_dante_Game_update(JNIEnv* env, jclass cls, jfloat delta_time);

JNIEXPORT void JNICALL Java_com_noctisgames_dante_Game_render(JNIEnv* env, jclass cls);

JNIEXPORT void JNICALL Java_com_noctisgames_dante_Game_on_1touch_1down(JNIEnv* env, jclass cls, jfloat raw_touch_x, jfloat raw_touch_y);

JNIEXPORT void JNICALL Java_com_noctisgames_dante_Game_on_1touch_1dragged(JNIEnv* env, jclass cls, jfloat raw_touch_x, jfloat raw_touch_y);

JNIEXPORT void JNICALL Java_com_noctisgames_dante_Game_on_1touch_1up(JNIEnv* env, jclass cls, jfloat raw_touch_x, jfloat raw_touch_y);

JNIEXPORT short JNICALL Java_com_noctisgames_dante_Game_get_1current_1music_1id(JNIEnv* env, jclass cls);

JNIEXPORT short JNICALL Java_com_noctisgames_dante_Game_get_1current_1sound_1id(JNIEnv* env, jclass cls);

JNIEXPORT int JNICALL Java_com_noctisgames_dante_Game_get_1requested_1action(JNIEnv* env, jclass cls);

JNIEXPORT void JNICALL Java_com_noctisgames_dante_Game_clear_1requested_1action(JNIEnv* env, jclass cls);

JNIEXPORT bool JNICALL Java_com_noctisgames_dante_Game_handle_1on_1back_1pressed(JNIEnv* env, jclass cls);
};

JNIEXPORT void JNICALL Java_com_noctisgames_dante_Game_init(JNIEnv* env, jclass cls)
{
	UNUSED(env);
	UNUSED(cls);

    screen = nullptr;
}

JNIEXPORT void JNICALL Java_com_noctisgames_dante_Game_on_1surface_1created(JNIEnv * env, jclass cls)
{
	UNUSED(env);
	UNUSED(cls);

    screen = new MainScreen();
    screen->createDeviceDependentResources();
}

JNIEXPORT void JNICALL Java_com_noctisgames_dante_Game_on_1surface_1changed(JNIEnv * env, jclass cls, jint pixel_width, jint pixel_height)
{
	UNUSED(env);
	UNUSED(cls);
    
    if (!screen)
    {
        return;
    }

    screen->createWindowSizeDependentResources(pixel_width, pixel_height, pixel_width, pixel_height);
}

JNIEXPORT void JNICALL Java_com_noctisgames_dante_Game_on_1resume(JNIEnv* env, jclass cls)
{
	UNUSED(env);
	UNUSED(cls);
    
    if (!screen)
    {
        return;
    }

	screen->onResume();
}

JNIEXPORT void JNICALL Java_com_noctisgames_dante_Game_on_1pause(JNIEnv* env, jclass cls)
{
	UNUSED(env);
	UNUSED(cls);
    
    if (!screen)
    {
        return;
    }

	screen->onPause();
}

JNIEXPORT void JNICALL Java_com_noctisgames_dante_Game_update(JNIEnv* env, jclass cls, jfloat delta_time)
{
	UNUSED(env);
	UNUSED(cls);
    
    if (!screen)
    {
        return;
    }

	screen->update(delta_time);
}

JNIEXPORT void JNICALL Java_com_noctisgames_dante_Game_render(JNIEnv* env, jclass cls)
{
	UNUSED(env);
	UNUSED(cls);
    
    if (!screen)
    {
        return;
    }

	screen->render();
}

JNIEXPORT void JNICALL Java_com_noctisgames_dante_Game_on_1touch_1down(JNIEnv* env, jclass cls, jfloat raw_touch_x, jfloat raw_touch_y)
{
	UNUSED(env);
	UNUSED(cls);

	INPUT_MANAGER->onTouch(DOWN, raw_touch_x, raw_touch_y);
}

JNIEXPORT void JNICALL Java_com_noctisgames_dante_Game_on_1touch_1dragged(JNIEnv* env, jclass cls, jfloat raw_touch_x, jfloat raw_touch_y)
{
	UNUSED(env);
	UNUSED(cls);

	INPUT_MANAGER->onTouch(DRAGGED, raw_touch_x, raw_touch_y);
}

JNIEXPORT void JNICALL Java_com_noctisgames_dante_Game_on_1touch_1up(JNIEnv* env, jclass cls, jfloat raw_touch_x, jfloat raw_touch_y)
{
	UNUSED(env);
	UNUSED(cls);

	INPUT_MANAGER->onTouch(UP, raw_touch_x, raw_touch_y);
}

JNIEXPORT short JNICALL Java_com_noctisgames_dante_Game_get_1current_1music_1id(JNIEnv* env, jclass cls)
{
	UNUSED(env);
	UNUSED(cls);

    return SOUND_MANAGER->getCurrentMusicId();
}

JNIEXPORT short JNICALL Java_com_noctisgames_dante_Game_get_1current_1sound_1id(JNIEnv* env, jclass cls)
{
	UNUSED(env);
	UNUSED(cls);

	return SOUND_MANAGER->getCurrentSoundId();
}

JNIEXPORT int JNICALL Java_com_noctisgames_dante_Game_get_1requested_1action(JNIEnv* env, jclass cls)
{
	UNUSED(env);
	UNUSED(cls);

    return 0; // TODO
}

JNIEXPORT void JNICALL Java_com_noctisgames_dante_Game_clear_1requested_1action(JNIEnv* env, jclass cls)
{
	UNUSED(env);
	UNUSED(cls);

	// TODO
}

JNIEXPORT bool JNICALL Java_com_noctisgames_dante_Game_handle_1on_1back_1pressed(JNIEnv* env, jclass cls)
{
	UNUSED(env);
	UNUSED(cls);

	return false; // TODO
}
