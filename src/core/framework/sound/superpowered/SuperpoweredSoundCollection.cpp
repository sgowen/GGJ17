//
//  SuperpoweredSoundManager.h
//  noctisgames-framework
//
//  Created by Stephen Gowen on 10/20/16.
//  Copyright (c) 2017 Noctis Games. All rights reserved.
//

#include "SuperpoweredSoundCollection.h"

#include "SuperpoweredSound.h"

#include "VectorUtil.h"

SuperpoweredSoundCollection::SuperpoweredSoundCollection(const char *path, unsigned int sampleRate, int rawResourceId, int numCopies, int fileOffset, int fileLength) :
m_iSoundIndex(0),
m_iRawResourceId(rawResourceId),
m_iNumCopies(numCopies)
{
    for (int i = 0; i < m_iNumCopies; i++)
    {
        m_sounds.push_back(new SuperpoweredSound(path, sampleRate, rawResourceId, fileOffset, fileLength));
    }
}

SuperpoweredSoundCollection::~SuperpoweredSoundCollection()
{
    VectorUtil::cleanUpVectorOfPointers(m_sounds);
}

SuperpoweredSound* SuperpoweredSoundCollection::getSound()
{
    SuperpoweredSound* ret = m_sounds[m_iSoundIndex++];
    if (m_iSoundIndex >= m_iNumCopies)
    {
        m_iSoundIndex = 0;
    }
    
    return ret;
}

std::vector<SuperpoweredSound *>& SuperpoweredSoundCollection::getSounds()
{
    return m_sounds;
}

int SuperpoweredSoundCollection::getSoundIndex()
{
    return m_iSoundIndex;
}

int SuperpoweredSoundCollection::getRawResourceId()
{
    return m_iRawResourceId;
}

int SuperpoweredSoundCollection::getNumCopies()
{
    return m_iNumCopies;
}
