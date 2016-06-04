#ifndef SDK_H
#define SDK_H

#pragma once

#include "Main.h"

///////////////////////////////
// GET VIRTUAL FUNCTIONS
///////////////////////////////

inline void**& GetVirtualTable(void* inst, size_t offset = 0)
{
	return *reinterpret_cast<void***>((size_t)inst + offset);
}
inline const void** GetVirtualTable(const void* inst, size_t offset = 0)
{
	return *reinterpret_cast<const void***>((size_t)inst + offset);
}

template<typename Fn>
inline Fn GetVirtualFunction(const void* inst, size_t index, size_t offset = 0)
{
	return reinterpret_cast<Fn>(GetVirtualTable(inst, offset)[index]);
}

///////////////////////////////
// PANEL INTERFACE
///////////////////////////////

class IPanel
{
public:
	const char* GetName(unsigned int vguiPanel)
	{
		typedef const char*(__thiscall* fnOriginal)(void*, unsigned int);
		return GetVirtualFunction<fnOriginal>(this, 36)(this, vguiPanel);
	}
}; extern IPanel* g_pPanel;

///////////////////////////////
// SURFACE INTERFACE
///////////////////////////////

class ISurface
{
public:
	void DrawSetColor(int r, int g, int b, int a)
	{
		typedef void(__thiscall* fnOriginal)(void*, int, int, int, int);
		GetVirtualFunction<fnOriginal>(this, 15)(this, r, g, b, a);
	}
	void DrawFilledRect(int x0, int y0, int x1, int y1)
	{
		typedef void(__thiscall* fnOriginal)(void*, int, int, int, int);
		GetVirtualFunction<fnOriginal>(this, 16)(this, x0, y0, x1, y1);
	}
	void DrawOutlinedRect(int x0, int y0, int x1, int y1)
	{
		typedef void(__thiscall* fnOriginal)(void*, int x0, int y0, int x1, int y1);
		GetVirtualFunction<fnOriginal>(this, 18)(this, x0, y0, x1, y1);
	}
	void DrawLine(int x0, int y0, int x1, int y1)
	{
		typedef void(__thiscall* fnOriginal)(void*, int, int, int, int);
		GetVirtualFunction<fnOriginal>(this, 19)(this, x0, y0, x1, y1);
	}
	void DrawSetTextFont(unsigned long font)
	{
		typedef void(__thiscall* fnOriginal)(void*, unsigned long);
		GetVirtualFunction<fnOriginal>(this, 23)(this, font);
	}
	void DrawSetTextColor(int r, int g, int b, int a)
	{
		typedef void(__thiscall* fnOriginal)(void*, int, int, int, int);
		GetVirtualFunction<fnOriginal>(this, 25)(this, r, g, b, a);
	}
	void DrawSetTextPos(int x, int y)
	{
		typedef void(__thiscall* fnOriginal)(void*, int, int);
		GetVirtualFunction<fnOriginal>(this, 26)(this, x, y);
	}
	void DrawPrintText(const wchar_t* text, int textLen)
	{
		typedef void(__thiscall* fnOriginal)(void*, const wchar_t *, int, int);
		GetVirtualFunction<fnOriginal>(this, 28)(this, text, textLen, 0);
	}
	unsigned long CreateFont()
	{
		typedef unsigned int(__thiscall* fnOriginal)(void*);
		return GetVirtualFunction<fnOriginal>(this, 71)(this);
	}
	void SetFontGlyphSet(unsigned long& font, const char* windowsFontName, int tall, int weight, int blur, int scanlines, int flags)
	{
		typedef void(__thiscall* fnOriginal)(void*, unsigned long, const char*, int, int, int, int, int, int, int);
		GetVirtualFunction<fnOriginal>(this, 72)(this, font, windowsFontName, tall, weight, blur, scanlines, flags, 0, 0);
	}
	bool AddCustomFontFile(const char* fontName)
	{
		typedef bool(__thiscall* fnOriginal)(void*, const char*);
		return GetVirtualFunction<fnOriginal>(this, 73)(this, fontName);
	}
	void GetTextSize(unsigned long font, const wchar_t *text, int &wide, int &tall)
	{
		typedef void(__thiscall* fnOriginal)(void*, unsigned long font, const wchar_t *text, int &wide, int &tall);
		GetVirtualFunction<fnOriginal>(this, 79)(this, font, text, wide, tall);
	}
	void SurfaceGetCursorPos(int& x, int& y)
	{
		typedef void(__thiscall* fnOriginal)(void*, int &, int &);
		GetVirtualFunction<fnOriginal>(this, 100)(this, x, y);
	}
	void SurfaceSetCursorPos(int x, int y)
	{
		typedef void(__thiscall* fnOriginal)(void*, int, int);
		GetVirtualFunction<fnOriginal>(this, 101)(this, x, y);
	}
	const char* GetFontName(unsigned long font)
	{
		typedef const char*(__thiscall* fnOriginal)(void*, unsigned long);
		return GetVirtualFunction<fnOriginal>(this, 134)(this, font);
	}
}; extern ISurface* g_pSurface;

///////////////////////////////
// ENGINE INTERFACE
///////////////////////////////

class IEngine
{
public:
	void ExecuteClientCmd(char const* pszCommand)
	{
		typedef void(__thiscall* fnOriginal)(void*, char const*);
		GetVirtualFunction<fnOriginal>(this, 108)(this, pszCommand);
	}
}; extern IEngine* g_pEngine;

///////////////////////////////
// TOOLS CLASS
///////////////////////////////

class CTools
{
public:
	void* QueryInterface(std::string szModuleName, std::string szInterfaceName);
}; extern CTools g_Tools;

#endif