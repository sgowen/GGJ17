//
//  Font.cpp
//  noctisgames-framework
//
//  Created by Stephen Gowen on 2/22/14.
//  Copyright (c) 2017 Noctis Games. All rights reserved.
//

#include "Font.h"

#include "TextureRegion.h"
#include "SpriteBatcher.h"

Font::Font(std::string textureName, int offsetX, int offsetY, int glyphsPerRow, int glyphWidth, int glyphHeight, int textureWidth, int textureHeight)
{
	int x = offsetX;
	int y = offsetY;

	for (int i = 0; i < 176; i++)
	{
		m_glyphs.push_back(TextureRegion(textureName, x, y, glyphWidth, glyphHeight, textureWidth, textureHeight));

		x += glyphWidth;

		if (x == offsetX + glyphsPerRow * glyphWidth)
		{
			x = offsetX;
			y += glyphHeight;
		}
	}
}

void Font::renderText(SpriteBatcher &spriteBatcher, std::string &text, float x, float y, float width, float height, Color color, bool isCentered, bool isRightJustified, int charOffset)
{
	if (isCentered)
	{
		int len = (int)text.length();
		float result = width / 2;
		x -= len * result;
		x += width / 2;
	}
	else if (isRightJustified)
	{
		x -= (text.length() - 1) * width;
	}

	for (unsigned int i = 0; i < text.length(); i++)
	{
		int c = ((int)text.at(i)) - charOffset;

        renderAsciiChar(spriteBatcher, c, x, y, width, height, color);

		x += width;
	}
}

void Font::renderAsciiChar(SpriteBatcher &spriteBatcher, int asciiChar, float x, float y, float width, float height, Color color)
{
    if (asciiChar < 0 || asciiChar > 175)
    {
        return;
    }
    
    spriteBatcher.drawSprite(x, y, width, height, 0, color, m_glyphs[asciiChar]);
}
