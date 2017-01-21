package com.noctisgames.dante;

import android.app.Activity;
import android.opengl.GLSurfaceView.Renderer;
import android.util.Log;

import com.noctisgames.dante.platform.PlatformAssetUtils;
import com.noctisgames.dante.sound.SoundManager;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

public final class GameRenderer implements Renderer
{
    private static final short MUSIC_NONE = 0; // Does Nothing
    private static final short MUSIC_LOAD_DEMO = 1;

    private static final short MUSIC_PLAY = 1001; // Assuming music is loaded
    private static final short MUSIC_PLAY_LOOP = 1002; // Assuming music is loaded
    private static final short MUSIC_PAUSE = 1003;
    private static final short MUSIC_RESUME = 1004;
    private static final short MUSIC_SET_VOLUME = 2000; // Passed in this format: [2][0-100], where the first digit is the action and the rest determines the volume (0-100), e.g. 2100 or 2050

    private static final short SOUND_NONE = 0; // Does Nothing

    private final Activity _activity;
    private SoundManager _soundManager;

    private long _startTime;

    public GameRenderer(Activity activity)
    {
        _activity = activity;

        SaveData.init(activity);

        Game.triggerStaticBlock();

        PlatformAssetUtils.init_asset_manager(_activity.getAssets());

        initSoundEngine(activity);

        Game.init();
    }

    @Override
    public void onSurfaceCreated(GL10 gl, EGLConfig config)
    {
        Log.d("GameRenderer", "GL Surface created!");

        Game.on_surface_created();

        _startTime = System.nanoTime();
    }

    @Override
    public void onSurfaceChanged(GL10 gl, int width, int height)
    {
        Log.d("GameRenderer", "GL Surface changed!");

        Game.on_surface_changed(width, height);
        Game.on_resume();
    }

    @Override
    public void onDrawFrame(GL10 gl)
    {
        float deltaTime = (System.nanoTime() - _startTime) / 1000000000.0f;
        _startTime = System.nanoTime();

        Game.update(deltaTime);
        Game.render();

        handleSound();
        handleMusic();
    }

    public void onResume()
    {
        Log.d("GameRenderer", "onResume");

        Game.on_resume();
    }

    public void onPause()
    {
        Log.d("GameRenderer", "onPause");

        Game.on_pause();

        _soundManager.pauseMusic();
    }

    public void handleTouchDown(float rawX, float rawY)
    {
        Game.on_touch_down(rawX, rawY);
    }

    public void handleTouchDragged(float rawX, float rawY)
    {
        Game.on_touch_dragged(rawX, rawY);
    }

    public void handleTouchUp(float rawX, float rawY)
    {
        Game.on_touch_up(rawX, rawY);
    }

    public boolean handleOnBackPressed()
    {
        return Game.handle_on_back_pressed();
    }

    private void handleSound()
    {
        short soundId;
        while ((soundId = Game.get_current_sound_id()) > SOUND_NONE)
        {
            playSound(soundId, false);
        }
    }

    private void handleMusic()
    {
        short musicId;
		while ((musicId = Game.get_current_music_id()) > MUSIC_NONE)
		{
			if (musicId > MUSIC_SET_VOLUME)
			{
				_soundManager.setMusicVolume((musicId % 1000) / 100.0f);
			}
			else
			{
				switch (musicId)
				{
					case MUSIC_LOAD_DEMO:
						_soundManager.loadMusic(_activity, R.raw.music_demo);
						break;
					case MUSIC_PLAY:
						_soundManager.playMusic(1, false);
						break;
					case MUSIC_PLAY_LOOP:
						_soundManager.playMusic(1, true);
						break;
					case MUSIC_PAUSE:
						_soundManager.pauseMusic();
						break;
					case MUSIC_RESUME:
						_soundManager.resumeMusic();
						break;
					default:
						break;
				}
			}
        }
    }

    private void playSound(int soundId, boolean isLooping)
    {
        _soundManager.playSound(soundId - 1, 1, isLooping);
    }

    private void playSound(int soundId)
    {
        _soundManager.playSound(soundId - 1, 1, false);
    }

    private void stopSound(int soundId)
    {
        _soundManager.stopSound(soundId - 1);
    }

    private void stopAllSounds()
    {
        SoundManager.stop_all_sounds();
    }

    private void stopAllLoopingSounds()
    {
        SoundManager.stop_all_looping_sounds();
    }

    private void initSoundEngine(Activity activity)
    {
        _soundManager = new SoundManager(activity);

        _soundManager.loadSound(activity, R.raw.sound_demo, 1);
    }
}
