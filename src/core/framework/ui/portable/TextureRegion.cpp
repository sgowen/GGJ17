//
//  TextureRegion.cpp
//  noctisgames-framework
//
//  Created by Stephen Gowen on 2/22/14.
//  Copyright (c) 2017 Noctis Games. All rights reserved.
//

#include "TextureRegion.h"

TextureRegion::TextureRegion(std::string textureName, int x, int y, int regionWidth, int regionHeight, int textureWidth, int textureHeight) : m_textureName(textureName)
{
    init(x, y, regionWidth, regionHeight, textureWidth, textureHeight);
}

void TextureRegion::init(int x, int y, int regionWidth, int regionHeight, int textureWidth, int textureHeight)
{
    m_fX = (float) x;
    m_fY = (float) y;
    m_fRegionWidth = (float) regionWidth;
    m_fRegionHeight = (float) regionHeight;
    m_fTextureWidth = (float) textureWidth;
    m_fTextureHeight = (float) textureHeight;
    
    u1 = m_fX / m_fTextureWidth;
    v1 = m_fY / m_fTextureHeight;
    u2 = u1 + m_fRegionWidth / m_fTextureWidth;
    v2 = v1 + m_fRegionHeight / m_fTextureHeight;
}

void TextureRegion::init(int x, int regionWidth, int textureWidth)
{
    m_fX = (float)x;
    m_fRegionWidth = (float) regionWidth;
    m_fTextureWidth = (float)textureWidth;
    
    u1 = x / (float) textureWidth;
    u2 = u1 + m_fRegionWidth / (float) textureWidth;
}
