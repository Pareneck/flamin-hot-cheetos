#include "Drawing.h"

Drawing drawing;

Drawing::Drawing(void)
{
	menuFont = 0, menuTitleFont = 0;
	espFont = 0;
}

void Drawing::initializeFonts(void)
{
	menuFont = surface->CreateFont();
	surface->SetFontGlyphSet(menuFont, charenc("Verdana"), 13, 20, 0, 0, FONTFLAG_ANTIALIAS);

	menuTitleFont = surface->CreateFont();
	surface->SetFontGlyphSet(menuTitleFont, charenc("Tahoma"), 13, 600, 0, 0, FONTFLAG_ANTIALIAS);

	espFont = surface->CreateFont();
	surface->SetFontGlyphSet(espFont, charenc("Tahoma"), 13, 1250, 0, 0, FONTFLAG_DROPSHADOW);
}

int getWidth(unsigned long ulFont, const char* pchInput, ...)
{
	int iWide = 0, iTall = 0;
	int iBufferSize = MultiByteToWideChar(CP_UTF8, 0x0, pchInput, -1, 0, 0);

	wchar_t* wchUnicode = new wchar_t[iBufferSize];
	MultiByteToWideChar(CP_UTF8, 0x0, pchInput, -1, wchUnicode, iBufferSize);

	surface->GetTextSize(ulFont, wchUnicode, iWide, iTall);
	delete[] wchUnicode;

	return iWide;
}

std::wstring getWide(const std::string& text)
{
	std::wstring wide(text.length(), L' ');
	std::copy(text.begin(), text.end(), wide.begin());

	return wide;
}

void Drawing::drawString(unsigned long font, bool shouldCenter, int x, int y, Color color, const char* text, ...)
{
	if (!text)
		return;

	char buffer[MAX_PATH];

	vsprintf_s(buffer, text, (char*)&text + _INTSIZEOF(text));

	if (shouldCenter)
		x -= getWidth(font, buffer) / 2;

	surface->DrawSetTextColor(color.r(), color.g(), color.b(), color.a());
	surface->DrawSetTextFont(font);
	surface->DrawSetTextPos(x, y);

	std::wstring wide = getWide(std::string(buffer));
	surface->DrawPrintText(wide.c_str(), wide.length());
}

void Drawing::drawLine(int x1, int y1, int x2, int y2, Color color)
{
	surface->DrawSetColor(color.r(), color.g(), color.b(), color.a());
	surface->DrawLine(x1, y1, x2, y2);
}

void Drawing::drawFilledRect(int x, int y, int w, int h, Color color)
{
	surface->DrawSetColor(color.r(), color.g(), color.b(), color.a());
	surface->DrawFilledRect(x, y, x + w, y + h);
}

void Drawing::drawOutlinedRect(int x, int y, int w, int h, Color color)
{
	surface->DrawSetColor(color.r(), color.g(), color.b(), color.a());
	surface->DrawOutlinedRect(x, y, x + w, y + h);
}

void Drawing::drawOutlinedBox(int x, int y, int w, int h, Color color, Color colorOutline)
{
	drawOutlinedRect(x, y, w, h, color);

	surface->DrawSetColor(colorOutline.r(), colorOutline.g(), colorOutline.b(), colorOutline.a());
	surface->DrawOutlinedRect(x + 1, y + 1, x + w - 1, y + h - 1);
	surface->DrawOutlinedRect(x - 1, y - 1, x + w + 1, y + h + 1);
}