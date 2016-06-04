#include "Drawing.h"

CDrawing g_Drawing;

CDrawing::CDrawing()
{
	m_ESPFont = 0;
}

void CDrawing::InitializeFonts()
{
	m_ESPFont = g_pSurface->CreateFontA();
	g_pSurface->SetFontGlyphSet(m_ESPFont, "Tahoma", 13, 600, 0, 0, 0);
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

void CDrawing::DrawString(unsigned long ulFont, bool bCenter, int x, int y, int r, int g, int b, int a, const char* pchInput, ...)
{
	if (!pchInput)
		return;

	char chBuffer[MAX_PATH];

	vsprintf_s(chBuffer, pchInput, (char*)&pchInput + _INTSIZEOF(pchInput));

	if (bCenter)
		x -= GetWidth(ulFont, chBuffer) / 2;

	g_pSurface->DrawSetTextColor(r, g, b, a);
	g_pSurface->DrawSetTextFont(ulFont);
	g_pSurface->DrawSetTextPos(x, y);

	std::wstring wstrWide = GetWide(std::string(chBuffer));
	g_pSurface->DrawPrintText(wstrWide.c_str(), wstrWide.length());
}