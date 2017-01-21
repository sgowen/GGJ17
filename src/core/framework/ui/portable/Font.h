//
//  Font.h
//  noctisgames-framework
//
//  Created by Stephen Gowen on 2/22/14.
//  Copyright (c) 2017 Noctis Games. All rights reserved.
//

#ifndef __noctisgames__Font__
#define __noctisgames__Font__

#include <vector>
#include <string>

class SpriteBatcher;
class TextureRegion;
struct Color;

class Font
{
public:
	Font(std::string textureName, int offsetX, int offsetY, int glyphsPerRow, int glyphWidth, int glyphHeight, int textureWidth, int textureHeight);
	   
	void renderText(SpriteBatcher &spriteBatcher, std::string &text, float x, float y, float width, float height, Color color, bool isCentered = false, bool isRightJustified = false, int charOffset = 0);
    
    void renderAsciiChar(SpriteBatcher &spriteBatcher, int asciiChar, float x, float y, float width, float height, Color color);

private:
    std::vector<TextureRegion> m_glyphs;
};

#endif /* defined(__noctisgames__Font__) */
