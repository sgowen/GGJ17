package com.noctisgames.dante.sound;

import android.app.Activity;
import android.content.Context;
import android.content.res.AssetFileDescriptor;
import android.media.AudioManager;
import android.os.Build;
import android.util.Log;

import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

public final class SoundManager
{
    public static native void init_sound_manager(int sample_rate, int buffer_size);

    public static native void load_sound(int rawResourceId, String apk_path, int numCopies, int fileOffset, int fileLength);

    public static native void play_sound(int rawResourceId, float volume, boolean isLooping);

    public static native void stop_sound(int rawResourceId);

    public static native void stop_all_sounds();

    public static native void stop_all_looping_sounds();

    public static native void load_music(int rawResourceId, String apk_path, int fileOffset, int fileLength);

    public static native void play_music(float volume, boolean isLooping);

    public static native void set_music_volume(float volume);

    public static native void resume_music();

    public static native void pause_music();

    private final String _packageResourcePath;
    private final List<Sound> _sounds = new ArrayList<>();

    public SoundManager(Activity activity)
    {
        // Get the device's sample rate and buffer size to enable low-latency Android audio output, if available.
        String sampleRateString = null;
        String bufferSizeString = null;

        if (Build.VERSION.SDK_INT >= 17)
        {
            AudioManager audioManager = (AudioManager) activity.getSystemService(Context.AUDIO_SERVICE);
            sampleRateString = audioManager.getProperty(AudioManager.PROPERTY_OUTPUT_SAMPLE_RATE);
            bufferSizeString = audioManager.getProperty(AudioManager.PROPERTY_OUTPUT_FRAMES_PER_BUFFER);
        }

        if (sampleRateString == null)
        {
            sampleRateString = "44100";
        }

        if (bufferSizeString == null)
        {
            bufferSizeString = "512";
        }

        _packageResourcePath = activity.getPackageResourcePath();
        int sampleRate = Integer.parseInt(sampleRateString);
        int bufferSize = Integer.parseInt(bufferSizeString);

        SoundManager.init_sound_manager(sampleRate, bufferSize);
    }

    public void loadMusic(Activity activity, int rawResourceId)
    {
        Sound sound = load(activity, rawResourceId);
        SoundManager.load_music(sound._rawResourceId, _packageResourcePath, sound._fileOffset, sound._fileLength);
    }

    public void playMusic(float volume, boolean isLooping)
    {
        SoundManager.play_music(volume, isLooping);
    }

    public void loadSound(Activity activity, int rawResourceId, int numCopies)
    {
        Sound sound = load(activity, rawResourceId);
        SoundManager.load_sound(sound._rawResourceId, _packageResourcePath, numCopies, sound._fileOffset, sound._fileLength);

        _sounds.add(sound);
    }

    public void pauseMusic()
    {
        SoundManager.pause_music();
    }

    public void resumeMusic()
    {
        SoundManager.resume_music();
    }

    public void setMusicVolume(float volume)
    {
        SoundManager.set_music_volume(volume);
    }

    public void playSound(int soundIndex, float volume, boolean isLooping)
    {
        Sound sound = _sounds.get(soundIndex);
        SoundManager.play_sound(sound._rawResourceId, volume, isLooping);
    }

    public void stopSound(int soundIndex)
    {
        Sound sound = _sounds.get(soundIndex);
        SoundManager.stop_sound(sound._rawResourceId);
    }

    private Sound load(Activity activity, int rawResourceId)
    {
        // Files under res/raw are not zipped, just copied into the APK. Get the offset and length to know where our files are located.
        AssetFileDescriptor fd = activity.getResources().openRawResourceFd(rawResourceId);
        int fileOffset = (int) fd.getStartOffset(), fileLength = (int) fd.getLength();
        try
        {
            fd.getParcelFileDescriptor().close();
        } catch (IOException e)
        {
            Log.e("dante", "Close error.");
        }

        return new Sound(rawResourceId, fileOffset, fileLength);
    }

    private static final class Sound
    {
        final int _rawResourceId;
        final int _fileOffset;
        final int _fileLength;

        Sound(int rawResourceId, int fileOffset, int fileLength)
        {
            _rawResourceId = rawResourceId;
            _fileOffset = fileOffset;
            _fileLength = fileLength;
        }
    }
}
