//
//  MainAssetsMapper.cpp
//  ggj17
//
//  Created by Stephen Gowen on 11/9/16.
//  Copyright © 2017 Noctis Games. All rights reserved.
//

#include "MainAssetsMapper.h"

#include "Assets.h"

#include "TextureRegion.h"
#include "Animation.h"

void MainAssetsMapper::mapAssets()
{
    ASSETS->getTextureRegionMap()["Microwave"] = new TextureRegion("main", 0, 624, 2048, 1102, TEXTURE_SIZE_4096);
    
	ASSETS->getAnimationsMap()["Logo"] = new Animation("main", 0, 0, 964, 620, 3860, 620, TEXTURE_SIZE_4096, true, 0.20f, 4, 0, 2);
    
    ASSETS->getTextureRegionMap()["NumPad0"] = new TextureRegion("main", 0, 1728, 304, 258, TEXTURE_SIZE_4096);
    ASSETS->getTextureRegionMap()["NumPad1"] = new TextureRegion("main", 306, 1728, 304, 258, TEXTURE_SIZE_4096);
    ASSETS->getTextureRegionMap()["NumPad2"] = new TextureRegion("main", 612, 1728, 304, 258, TEXTURE_SIZE_4096);
    ASSETS->getTextureRegionMap()["NumPad3"] = new TextureRegion("main", 918, 1728, 304, 258, TEXTURE_SIZE_4096);
    ASSETS->getTextureRegionMap()["NumPad4"] = new TextureRegion("main", 1224, 1728, 304, 258, TEXTURE_SIZE_4096);
    
    ASSETS->getTextureRegionMap()["Glare"] = new TextureRegion("main", 0, 1988, 288, 302, TEXTURE_SIZE_4096);
    
    ASSETS->getTextureRegionMap()["Popcorn"] = new TextureRegion("main", 0, 3200, 264, 332, TEXTURE_SIZE_4096);
    
    ASSETS->getTextureRegionMap()["Popped"] = new TextureRegion("main", 266, 3200, 264, 332, TEXTURE_SIZE_4096);
    
//    ASSETS->getAnimationsMap()["Sonic_Idle"] = new Animation("demo", 34, 48, 32, 40, 204, 40, TEXTURE_SIZE_512, true, 0.1f, 6, 0, 2);
}
