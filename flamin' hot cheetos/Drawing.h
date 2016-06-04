#ifndef DRAWING_H
#define DRAWING_H

#pragma once

#include "Main.h"

class CDrawing
{
public:
	CDrawing();

	void InitializeFonts();

	// Draw Helpers
	void DrawString(unsigned long ulFont, bool bCenter, int x, int y, Color clrString, const char* pchInput, ...);
	void DrawESPBox(int x, int y, int w, int h, Color clrBox, Color clrOutline);

	unsigned long m_ESPFont;
};

extern CDrawing g_Drawing;

#endif