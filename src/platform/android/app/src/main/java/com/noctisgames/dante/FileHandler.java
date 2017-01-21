package com.noctisgames.dante;

import android.os.Environment;
import android.util.Log;

import java.io.BufferedInputStream;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileWriter;
import java.io.IOException;

public final class FileHandler
{
    private final File _baseDir;

    public FileHandler(File baseConfigDir)
    {
        _baseDir = baseConfigDir;
        _baseDir.mkdirs();
    }

    public String readFromFile(String fileName)
    {
        waitForMediaMounted();

        File file = getFile(fileName);

        if (!file.exists())
        {
            return null;
        }

        int length = (int) file.length();
        byte[] bytes = new byte[length];
        BufferedInputStream bis = null;
        try
        {
            bis = new BufferedInputStream(new FileInputStream(file));
            bis.read(bytes, 0, length);

            return new String(bytes, "UTF-8");
        } catch (IOException e)
        {
            e.printStackTrace();
        } finally
        {
            if (bis != null)
            {
                try
                {
                    bis.close();
                } catch (IOException e)
                {
                    e.printStackTrace();
                }
            }
        }

        return null;
    }

    public boolean writeToFile(String fileName, String content)
    {
        waitForMediaMounted();

        if (!_baseDir.exists())
        {
            _baseDir.mkdir();
        }

        File file = getFile(fileName);
        BufferedWriter writer = null;
        try
        {
            writer = new BufferedWriter(new FileWriter(file));
            writer.write(content);

            return true;
        } catch (IOException e)
        {
            e.printStackTrace();
        } finally
        {
            if (writer != null)
            {
                try
                {
                    writer.close();
                } catch (IOException e)
                {
                    e.printStackTrace();
                }
            }
        }

        return false;
    }

    public File getFile(String fileName)
    {
        File file = new File(_baseDir, fileName);

        return file;
    }

    private synchronized void waitForMediaMounted()
    {
        String sdcardState = Environment.getExternalStorageState();
        Log.d("FileHandler", "sd card is " + sdcardState);
        while (!Environment.MEDIA_MOUNTED.equals(sdcardState))
        {
            try
            {
                wait(1000);
                sdcardState = Environment.getExternalStorageState();
            } catch (InterruptedException e)
            {
                Log.w("FileHandler", e.toString(), e);
            }
        }
    }
}