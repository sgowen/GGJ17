//
//  SoundManager.h
//  noctisgames-framework
//
//  Created by Stephen Gowen on 1/15/17.
//  Copyright (c) 2017 Noctis Games. All rights reserved.
//

#ifndef __noctisgames__SoundManager__
#define __noctisgames__SoundManager__

#include <vector>

#define SOUND_MANAGER (SoundManager::getInstance())

#define MAX_SOUNDS_TO_PLAY_PER_FRAME 4

class SoundManager
{
public:
	static SoundManager* getInstance();
    
    int getCurrentMusicId();
    
    int getCurrentSoundId();
    
    int getFirstSoundId();
    
    void addSoundIdToPlayQueue(int soundId);
    
    void forceAddSoundIdToPlayQueue(int soundId);
    
    void eraseFirstSoundId();
    
    int getFirstMusicId();
    
    void addMusicIdToPlayQueue(int musicId);
    
    void eraseFirstMusicId();
    
    bool isMusicEnabled();
    
    void setMusicEnabled(bool isMusicEnabled);
    
    bool isSoundEnabled();
    
    void setSoundEnabled(bool isSoundEnabled);

private:
    std::vector<int> m_sSoundIds;
    std::vector<int> m_sMusicIds;
    bool m_isMusicEnabled;
    bool m_isSoundEnabled;
    
    // ctor, copy ctor, and assignment should be private in a Singleton
    SoundManager();
    SoundManager(const SoundManager&);
    SoundManager& operator=(const SoundManager&);
};

#endif /* defined(__noctisgames__SoundManager__) */
