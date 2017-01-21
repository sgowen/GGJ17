//
//  Renderer.h
//  noctisgames-framework
//
//  Created by Stephen Gowen on 2/22/14.
//  Copyright (c) 2017 Noctis Games. All rights reserved.
//

#ifndef __noctisgames__Renderer__
#define __noctisgames__Renderer__

#include <string>

class SpriteBatcher;
class NGRectBatcher;
class LineBatcher;
class CircleBatcher;
class ITextureLoader;
class IRendererHelper;
class GpuProgramWrapper;
class PhysicalEntity;
class TextureRegion;
struct Color;
struct TextureWrapper;

class Renderer
{
public:
    Renderer();
    
    virtual ~Renderer();
    
    void beginFrame();
    
    void setFramebuffer(int framebufferIndex);
    
    void renderFramebufferToScreen(int framebufferIndex);
    
    void endFrame();
    
protected:
    SpriteBatcher* m_spriteBatcher;
    NGRectBatcher* m_fillNGRectBatcher;
    NGRectBatcher* m_boundsNGRectBatcher;
    LineBatcher* m_lineBatcher;
    CircleBatcher* m_circleBatcher;
    
    ITextureLoader* m_textureLoader;
    IRendererHelper* m_rendererHelper;
    
    GpuProgramWrapper* m_textureGpuProgramWrapper;
    GpuProgramWrapper* m_colorGpuProgramWrapper;
    GpuProgramWrapper* m_framebufferToScreenGpuProgramWrapper;
    
    void renderPhysicalEntity(PhysicalEntity &go, TextureRegion& tr);

	void renderPhysicalEntityWithColor(PhysicalEntity &go, TextureRegion& tr, Color c);
    
    void loadTextureSync(TextureWrapper* textureWrapper, std::string textureName);
    
    void destroyTexture(TextureWrapper* textureWrapper);
};

#endif /* defined(__noctisgames__Renderer__) */
