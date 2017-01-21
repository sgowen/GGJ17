//
//  Assets.h
//  noctisgames-framework
//
//  Created by Stephen Gowen on 2/22/14.
//  Copyright (c) 2017 Noctis Games. All rights reserved.
//

#ifndef __noctisgames__Assets__
#define __noctisgames__Assets__

#include <map>
#include <string.h>

#define ASSETS (Assets::getInstance())

class IAssetsMapper;
class TextureRegion;
class Animation;

class Assets
{
public:
	static Assets* getInstance();
    
    void init(IAssetsMapper* assetsMapper);
    
    TextureRegion& findTextureRegion(std::string key, float stateTime);
    
    TextureRegion& findTextureRegion(std::string key);
    
    Animation& findAnimation(std::string key);
    
    std::map<std::string, TextureRegion*>& getTextureRegionMap();
    
    std::map<std::string, Animation*>& getAnimationsMap();
    
    void initTextureRegion(TextureRegion& tr, int x, int regionWidth, int textureWidth); // Useful for parallax

private:
    std::map<std::string, TextureRegion*> m_textureRegions;
    std::map<std::string, Animation*> m_animations;
    
    // ctor, copy ctor, and assignment should be private in a Singleton
    Assets() {}
    Assets(const Assets&);
    Assets& operator=(const Assets&);
};

#endif /* defined(__noctisgames__Assets__) */
