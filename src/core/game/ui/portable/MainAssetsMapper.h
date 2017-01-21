//
//  MainAssetsMapper.h
//  ggj17
//
//  Created by Stephen Gowen on 11/9/16.
//  Copyright © 2017 Noctis Games. All rights reserved.
//

#ifndef __ggj17__MainAssetsMapper__
#define __ggj17__MainAssetsMapper__

#include "IAssetsMapper.h"

class MainAssetsMapper : public IAssetsMapper
{
public:
    MainAssetsMapper() : IAssetsMapper() {}
    
    virtual ~MainAssetsMapper() {}
    
    virtual void mapAssets();
};

#endif /* defined(__ggj17__MainAssetsMapper__) */
