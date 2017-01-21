//
//  Direct3DSpriteBatcher.h
//  noctisgames-framework
//
//  Created by Stephen Gowen on 9/22/14.
//  Copyright (c) 2017 Noctis Games. All rights reserved.
//

#ifndef __noctisgames__Direct3DSpriteBatcher__
#define __noctisgames__Direct3DSpriteBatcher__

#include "SpriteBatcher.h"

class Direct3DSpriteBatcher : public SpriteBatcher
{
public:
	Direct3DSpriteBatcher();
    
	virtual void beginBatch();

	virtual void endBatch(GpuTextureWrapper textureWrapper, GpuProgramWrapper &gpuProgramWrapper);
    
	virtual void drawSprite(float x, float y, float width, float height, float angle, TextureRegion tr);
    
	virtual void drawSprite(float x, float y, float width, float height, float angle, Color &color, TextureRegion tr);
    
protected:
	virtual void drawSprite(float x, float y, float width, float height, TextureRegion tr);

	virtual void drawSprite(float x, float y, float width, float height, Color &color, TextureRegion tr);
};

#endif /* defined(__noctisgames__Direct3DSpriteBatcher__) */
