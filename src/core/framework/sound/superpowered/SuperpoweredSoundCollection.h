//
//  SuperpoweredSoundManager.h
//  noctisgames-framework
//
//  Created by Stephen Gowen on 10/20/16.
//  Copyright (c) 2017 Noctis Games. All rights reserved.
//

#ifndef __noctisgames__SuperpoweredSoundCollection__
#define __noctisgames__SuperpoweredSoundCollection__

#include <vector>

class SuperpoweredSound;

class SuperpoweredSoundCollection
{
public:
    SuperpoweredSoundCollection(const char *path, unsigned int sampleRate, int rawResourceId, int numCopies = 1, int fileOffset = -1, int fileLength = -1);
    
    ~SuperpoweredSoundCollection();
    
    SuperpoweredSound* getSound();
    
    std::vector<SuperpoweredSound *>& getSounds();
    int getSoundIndex();
    int getRawResourceId();
    int getNumCopies();
    
private:
    std::vector<SuperpoweredSound *> m_sounds;
    int m_iSoundIndex;
    int m_iRawResourceId;
    int m_iNumCopies;
};

#endif /* defined(__noctisgames__SuperpoweredSoundCollection__) */
