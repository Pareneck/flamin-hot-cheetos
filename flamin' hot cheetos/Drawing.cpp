#include "Drawing.h"

CDrawing g_Drawing;

CDrawing::CDrawing()
{
	m_MenuFont = 0;
	m_ESPFont = 0;
}

void CDrawing::InitializeFonts()
{
	m_MenuFont = g_pSurface->CreateFontA();
	g_pSurface->SetFontGlyphSet(m_MenuFont, charenc("Verdana"), 13, 20, 0, 0, 0x10);

	m_ESPFont = g_pSurface->CreateFontA();
	g_pSurface->SetFontGlyphSet(m_ESPFont, charenc("Tahoma"), 13, 600, 0, 0, 0);
}

int GetWidth(unsigned long ulFont, const char* pchInput, ...)
{
	int iWide = 0, iTall = 0;
	int iBufferSize = MultiByteToWideChar(CP_UTF8, 0x0, pchInput, -1, NULL, 0);

	wchar_t* wchUnicode = new wchar_t[iBufferSize];
	MultiByteToWideChar(CP_UTF8, 0x0, pchInput, -1, wchUnicode, iBufferSize);

	g_pSurface->GetTextSize(ulFont, wchUnicode, iWide, iTall);
	delete[] wchUnicode;

	return iWide;
}

std::wstring GetWide(const std::string& strText)
{
	std::wstring wstrWide(strText.length(), L' ');
	std::copy(strText.begin(), strText.end(), wstrWide.begin());

	return wstrWide;
}

void CDrawing::DrawString(unsigned long ulFont, bool bCenter, int x, int y, Color clrString, const char* pchInput, ...)
{
	if (!pchInput)
		return;

	char chBuffer[MAX_PATH];

	vsprintf_s(chBuffer, pchInput, (char*)&pchInput + _INTSIZEOF(pchInput));

	if (bCenter)
		x -= GetWidth(ulFont, chBuffer) / 2;

	g_pSurface->DrawSetTextColor(clrString.r(), clrString.g(), clrString.b(), clrString.a());
	g_pSurface->DrawSetTextFont(ulFont);
	g_pSurface->DrawSetTextPos(x, y);

	std::wstring wstrWide = GetWide(std::string(chBuffer));
	g_pSurface->DrawPrintText(wstrWide.c_str(), wstrWide.length());
}

void CDrawing::DrawLine(int x1, int y1, int x2, int y2, Color clrColor)
{
	g_pSurface->DrawSetColor(clrColor.r(), clrColor.g(), clrColor.b(), clrColor.a());
	g_pSurface->DrawLine(x1, y1, x2, y2);
}

void CDrawing::DrawFilledRect(int x, int y, int w, int h, Color clrColor)
{
	g_pSurface->DrawSetColor(clrColor.r(), clrColor.g(), clrColor.b(), clrColor.a());
	g_pSurface->DrawFilledRect(x, y, x + w, y + h);
}

void CDrawing::DrawOutlinedRect(int x, int y, int w, int h, Color clrColor)
{
	g_pSurface->DrawSetColor(clrColor.r(), clrColor.g(), clrColor.b(), clrColor.a());
	g_pSurface->DrawOutlinedRect(x, y, x + w, y + h);
}

void CDrawing::DrawESPBox(int x, int y, int w, int h, Color clrBox, Color clrOutline)
{
	this->DrawOutlinedRect(x, y, w, h, clrBox);

	g_pSurface->DrawSetColor(clrOutline.r(), clrOutline.g(), clrOutline.b(), clrOutline.a());
	g_pSurface->DrawOutlinedRect(x + 1, y + 1, x + w - 1, y + h - 1);
	g_pSurface->DrawOutlinedRect(x - 1, y - 1, x + w + 1, y + h + 1);
}