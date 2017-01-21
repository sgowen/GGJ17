package com.noctisgames.dante;

import android.app.Activity;
import android.content.SharedPreferences;

public final class SaveData
{
    private static final String KEY_DEMO_DATA = "v0_0_1-demo_data";

    private static SharedPreferences _securePrefs;

    public static void init(Activity activity)
    {
        _securePrefs = new SecurePreferences(activity);
    }

    public static int getDemoData()
    {
        return _securePrefs.getInt(KEY_DEMO_DATA, 0);
    }

    public static void setDemoData(int demoData)
    {
        set(KEY_DEMO_DATA, demoData);
    }

    private static boolean set(String key, String value)
    {
        if (value == null)
        {
            return _securePrefs.edit().remove(key).commit();
        }

        return _securePrefs.edit().putString(key, value).commit();
    }

    private static boolean set(String key, float value)
    {
        return _securePrefs.edit().putFloat(key, value).commit();
    }

    private static boolean set(String key, long value)
    {
        return _securePrefs.edit().putLong(key, value).commit();
    }

    private static boolean set(String key, int value)
    {
        return _securePrefs.edit().putInt(key, value).commit();
    }

    private static boolean set(String key, boolean value)
    {
        return _securePrefs.edit().putBoolean(key, value).commit();
    }
}
