//
//  Text.cpp
//  noctisgames-framework
//
//  Created by Stephen Gowen on 10/6/13.
//  Copyright (c) 2017 Noctis Games. All rights reserved.
//

#include "Text.h"

Text::Text(std::string text, float x, float y, float width, float height, float red, float green, float blue, float alpha) : PhysicalEntity(x, y, width, height)
{
	m_strText = text;

	m_fAlpha = alpha;
	m_fRed = red;
	m_fGreen = green;
	m_fBlue = blue;
}

std::string Text::getText()
{
	return m_strText;
}

void Text::setText(std::string text)
{
	m_strText = text;
}

Color Text::getColor()
{
    Color color = Color(m_fRed, m_fGreen, m_fBlue, m_fAlpha);
	return color;
}

void Text::setColor(float red, float green, float blue, float alpha)
{
	m_fRed = red;
	m_fGreen = green;
	m_fBlue = blue;
	m_fAlpha = alpha;
}
