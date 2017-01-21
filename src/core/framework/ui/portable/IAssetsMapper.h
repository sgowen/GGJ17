//
//  IAssetsMapper.h
//  noctisgames-framework
//
//  Created by Stephen Gowen on 1/15/17.
//  Copyright © 2017 Noctis Games. All rights reserved.
//

#ifndef __noctisgames__IAssetsMapper__
#define __noctisgames__IAssetsMapper__

//// Texture Definitions ////

#define TEXTURE_SIZE_512 512, 512
#define TEXTURE_SIZE_1024 1024, 1024
#define TEXTURE_SIZE_2048 2048, 2048
#define TEXTURE_SIZE_4096 4096, 4096

class IAssetsMapper
{
public:
    IAssetsMapper() {}
    
    virtual ~IAssetsMapper() {}
    
    virtual void mapAssets() {}
};

#endif /* defined(__noctisgames__IAssetsMapper__) */
