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
	ASSETS->getTextureRegionMap()["Microwave"] = new TextureRegion("main", 0, 0, 1004, 616, TEXTURE_SIZE_4096);
    
    ASSETS->getTextureRegionMap()["Popcorn"] = new TextureRegion("main", 1008, 0, 188, 174, TEXTURE_SIZE_4096);
    
//    ASSETS->getAnimationsMap()["Sonic_Idle"] = new Animation("demo", 34, 48, 32, 40, 204, 40, TEXTURE_SIZE_512, true, 0.1f, 6, 0, 2);
}
