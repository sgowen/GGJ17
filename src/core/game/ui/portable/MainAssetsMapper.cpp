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
    
    ASSETS->getAnimationsMap()["PopcornComDown"] = new Animation("main", 2574, 704, 144, 144, 144, 432, TEXTURE_SIZE_4096, true, 0.1f, 3);
    ASSETS->getAnimationsMap()["PopcornComLeft"] = new Animation("main", 2574, 1136, 144, 144, 144, 288, TEXTURE_SIZE_4096, true, 0.1f, 2);
    ASSETS->getAnimationsMap()["PopcornComRight"] = new Animation("main", 2574, 1424, 144, 144, 144, 288, TEXTURE_SIZE_4096, true, 0.1f, 2);
    ASSETS->getAnimationsMap()["PopcornComTop"] = new Animation("main", 2788, 1712, 144, 144, 144, 432, TEXTURE_SIZE_4096, true, 0.1f, 3);
    
    ASSETS->getAnimationsMap()["Popcorn1Down"] = new Animation("main", 3438, 704, 144, 144, 144, 432, TEXTURE_SIZE_4096, true, 0.1f, 3);
    ASSETS->getAnimationsMap()["Popcorn2Down"] = new Animation("main", 3004, 704, 144, 144, 144, 432, TEXTURE_SIZE_4096, true, 0.1f, 3);
    ASSETS->getAnimationsMap()["Popcorn3Down"] = new Animation("main", 3224, 704, 144, 144, 144, 432, TEXTURE_SIZE_4096, true, 0.1f, 3);
    ASSETS->getAnimationsMap()["Popcorn4Down"] = new Animation("main", 2788, 704, 144, 144, 144, 432, TEXTURE_SIZE_4096, true, 0.1f, 3);
    
    ASSETS->getAnimationsMap()["Popcorn1Left"] = new Animation("main", 3438, 1136, 144, 144, 144, 288, TEXTURE_SIZE_4096, true, 0.1f, 2);
    ASSETS->getAnimationsMap()["Popcorn2Left"] = new Animation("main", 3004, 1136, 144, 144, 144, 288, TEXTURE_SIZE_4096, true, 0.1f, 2);
    ASSETS->getAnimationsMap()["Popcorn3Left"] = new Animation("main", 3224, 1136, 144, 144, 144, 288, TEXTURE_SIZE_4096, true, 0.1f, 2);
    ASSETS->getAnimationsMap()["Popcorn4Left"] = new Animation("main", 2788, 1136, 144, 144, 144, 288, TEXTURE_SIZE_4096, true, 0.1f, 2);
    
    ASSETS->getAnimationsMap()["Popcorn1Right"] = new Animation("main", 3438, 1424, 144, 144, 144, 288, TEXTURE_SIZE_4096, true, 0.1f, 2);
    ASSETS->getAnimationsMap()["Popcorn2Right"] = new Animation("main", 3004, 1424, 144, 144, 144, 288, TEXTURE_SIZE_4096, true, 0.1f, 2);
    ASSETS->getAnimationsMap()["Popcorn3Right"] = new Animation("main", 3224, 1424, 144, 144, 144, 288, TEXTURE_SIZE_4096, true, 0.1f, 2);
    ASSETS->getAnimationsMap()["Popcorn4Right"] = new Animation("main", 2788, 1424, 144, 144, 144, 288, TEXTURE_SIZE_4096, true, 0.1f, 2);
    
    ASSETS->getAnimationsMap()["Popcorn1Top"] = new Animation("main", 3438, 1712, 144, 144, 144, 432, TEXTURE_SIZE_4096, true, 0.1f, 3);
    ASSETS->getAnimationsMap()["Popcorn2Top"] = new Animation("main", 3004, 1712, 144, 144, 144, 432, TEXTURE_SIZE_4096, true, 0.1f, 3);
    ASSETS->getAnimationsMap()["Popcorn3Top"] = new Animation("main", 3224, 1712, 144, 144, 144, 432, TEXTURE_SIZE_4096, true, 0.1f, 3);
    ASSETS->getAnimationsMap()["Popcorn4Top"] = new Animation("main", 2788, 1712, 144, 144, 144, 432, TEXTURE_SIZE_4096, true, 0.1f, 3);
    
    ASSETS->getAnimationsMap()["Popcorn1BR"] = new Animation("main", 3438, 2144, 144, 144, 144, 432, TEXTURE_SIZE_4096, true, 0.1f, 3);
    ASSETS->getAnimationsMap()["Popcorn2BR"] = new Animation("main", 3004, 2144, 144, 144, 144, 432, TEXTURE_SIZE_4096, true, 0.1f, 3);
    ASSETS->getAnimationsMap()["Popcorn3BR"] = new Animation("main", 3224, 2144, 144, 144, 144, 432, TEXTURE_SIZE_4096, true, 0.1f, 3);
    ASSETS->getAnimationsMap()["Popcorn4BR"] = new Animation("main", 2788, 2144, 144, 144, 144, 432, TEXTURE_SIZE_4096, true, 0.1f, 3);
    
    ASSETS->getAnimationsMap()["Popcorn1BL"] = new Animation("main", 3438, 2576, 144, 144, 144, 432, TEXTURE_SIZE_4096, true, 0.1f, 3);
    ASSETS->getAnimationsMap()["Popcorn2BL"] = new Animation("main", 3004, 2576, 144, 144, 144, 432, TEXTURE_SIZE_4096, true, 0.1f, 3);
    ASSETS->getAnimationsMap()["Popcorn3BL"] = new Animation("main", 3224, 2576, 144, 144, 144, 432, TEXTURE_SIZE_4096, true, 0.1f, 3);
    ASSETS->getAnimationsMap()["Popcorn4BL"] = new Animation("main", 2788, 2576, 144, 144, 144, 432, TEXTURE_SIZE_4096, true, 0.1f, 3);
    
    ASSETS->getAnimationsMap()["Popcorn1TL"] = new Animation("main", 3438, 3008, 144, 144, 144, 432, TEXTURE_SIZE_4096, true, 0.1f, 3);
    ASSETS->getAnimationsMap()["Popcorn2TL"] = new Animation("main", 3004, 3008, 144, 144, 144, 432, TEXTURE_SIZE_4096, true, 0.1f, 3);
    ASSETS->getAnimationsMap()["Popcorn3TL"] = new Animation("main", 3224, 3008, 144, 144, 144, 432, TEXTURE_SIZE_4096, true, 0.1f, 3);
    ASSETS->getAnimationsMap()["Popcorn4TL"] = new Animation("main", 2788, 3008, 144, 144, 144, 432, TEXTURE_SIZE_4096, true, 0.1f, 3);
    
    ASSETS->getAnimationsMap()["Popcorn1TR"] = new Animation("main", 3438, 3440, 144, 144, 144, 432, TEXTURE_SIZE_4096, true, 0.1f, 3);
    ASSETS->getAnimationsMap()["Popcorn2TR"] = new Animation("main", 3004, 3440, 144, 144, 144, 432, TEXTURE_SIZE_4096, true, 0.1f, 3);
    ASSETS->getAnimationsMap()["Popcorn3TR"] = new Animation("main", 3224, 3440, 144, 144, 144, 432, TEXTURE_SIZE_4096, true, 0.1f, 3);
    ASSETS->getAnimationsMap()["Popcorn4TR"] = new Animation("main", 2788, 3440, 144, 144, 144, 432, TEXTURE_SIZE_4096, true, 0.1f, 3);
    
    ASSETS->getAnimationsMap()["Popped"] = new Animation("main", 0, 3350, 256, 256, 2048, 512, TEXTURE_SIZE_4096, true, 0.1f, 13);
    
    ASSETS->getAnimationsMap()["Start_Button"] = new Animation("demo", 448, 2442, 312, 68, 626, 68, TEXTURE_SIZE_4096, true, 0.1f, 2, 0, 2);
    
    ASSETS->getAnimationsMap()["Zero_Clock"] = new Animation("demo", 448, 2042, 314, 132, 630, 132, TEXTURE_SIZE_4096, true, 0.1f, 2, 0, 2);
 
    ASSETS->getTextureRegionMap()["GameOver_Menu"] = new TextureRegion("main", 0, 2688, 1024, 512, TEXTURE_SIZE_4096);
    ASSETS->getTextureRegionMap()["GameOver_Rematch"] = new TextureRegion("main", 1024, 2688, 1024, 512, TEXTURE_SIZE_4096);
    
    ASSETS->getTextureRegionMap()["Microwave_Scene"] = new TextureRegion("scene", 0, 0, 2048, 2048, TEXTURE_SIZE_4096);
    ASSETS->getTextureRegionMap()["Microwave_Game_Scene"] = new TextureRegion("scene", 2052, 718, 407, 229, TEXTURE_SIZE_4096);
    ASSETS->getTextureRegionMap()["Microwave_Cover"] = new TextureRegion("scene", 2052, 0, 736, 684, TEXTURE_SIZE_4096);
}
