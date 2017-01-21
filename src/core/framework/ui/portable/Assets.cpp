//
//  Assets.cpp
//  noctisgames-framework
//
//  Created by Stephen Gowen on 2/22/14.
//  Copyright (c) 2017 Noctis Games. All rights reserved.
//

#include "Assets.h"

#include "IAssetsMapper.h"
#include "TextureRegion.h"
#include "Animation.h"

#include <assert.h>

Assets* Assets::getInstance()
{
    static Assets *instance = new Assets();
    return instance;
}

void Assets::init(IAssetsMapper* assetsMapper)
{
	getTextureRegionMap().clear();
	getAnimationsMap().clear();

    assetsMapper->mapAssets();
    
    delete assetsMapper;
}

TextureRegion& Assets::findTextureRegion(std::string key, float stateTime)
{
    auto q = m_textureRegions.find(key);
    
    if (q != m_textureRegions.end())
    {
        TextureRegion* tr = q->second;
        
        return *tr;
    }
    else
    {
        auto q2 = m_animations.find(key);
        
        assert(q2 != m_animations.end());
        
        Animation* anim = q2->second;
        
        return anim->getTextureRegion(stateTime);
    }
}

TextureRegion& Assets::findTextureRegion(std::string key)
{
    auto q = m_textureRegions.find(key);
    
    assert(q != m_textureRegions.end());
    
    TextureRegion* tr = q->second;
    
    return *tr;
}

Animation& Assets::findAnimation(std::string key)
{
    auto q = m_animations.find(key);
    
    assert(q != m_animations.end());
    
    Animation* anim = q->second;
    
    return *anim;
}

std::map<std::string, TextureRegion*>& Assets::getTextureRegionMap()
{
    return m_textureRegions;
}

std::map<std::string, Animation*>& Assets::getAnimationsMap()
{
    return m_animations;
}

void Assets::initTextureRegion(TextureRegion& tr, int x, int regionWidth, int textureWidth)
{
    tr.init(x, regionWidth, textureWidth);
}
