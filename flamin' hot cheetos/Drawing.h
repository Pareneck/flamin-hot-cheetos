#ifndef DRAWING_H
#define DRAWING_H

#pragma once

#include "Main.h"

class CDrawing
{
public:
	CDrawing(void);

	void InitializeFonts(void);

	void DrawLine(int x1, int y1, int x2, int y2, Color clrColor);
	void DrawFilledRect(int x, int y, int w, int h, Color clrColor);
	void DrawOutlinedRect(int x, int y, int w, int h, Color clrColor);

	void DrawString(unsigned long ulFont, bool bCenter, int x, int y, Color clrString, const char* pchInput, ...);
	void DrawESPBox(int x, int y, int w, int h, Color clrBox, Color clrOutline);

public:
	unsigned long m_MenuFont, m_MenuTitle;
	unsigned long m_ESPFont;
};

extern CDrawing g_Drawing;

#endif