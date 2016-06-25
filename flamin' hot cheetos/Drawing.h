#ifndef DRAWING_H
#define DRAWING_H

#pragma once

#include "stdafx.h"

class Drawing
{
public:
	Drawing();

	void resetFonts();
	void initializeFonts();

	void drawLine(int x1, int y1, int x2, int y2, Color color);
	void drawFilledRect(int x, int y, int w, int h, Color color);
	void drawOutlinedRect(int x, int y, int w, int h, Color color);

	void drawString(unsigned long font, bool shouldCenter, int x, int y, Color color, const char* text, ...);
	void drawOutlinedBox(int x, int y, int w, int h, Color color, Color colorOutline);
	void drawBar(int x, int y, int w, int h, Color color, float value);

public:
	unsigned long menuFont, menuTitleFont;
	unsigned long espFont;
	unsigned long scoreboardFont;
};

extern Drawing drawing;

#endif