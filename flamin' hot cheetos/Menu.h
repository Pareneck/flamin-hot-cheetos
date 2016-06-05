#ifndef MENU_H
#define MENU_H

#pragma once

#include "Main.h"

__forceinline float clamp(float fValue, float fMinValue, float fMaxValue)
{
#if defined(__i386__) || defined(_M_IX86)
	_mm_store_ss(&fValue,
		_mm_min_ss(
			_mm_max_ss(
				_mm_load_ss(&fValue),
				_mm_load_ss(&fMinValue)),
			_mm_load_ss(&fMaxValue)));
#else
	val = fpmax(fMinValue, fValue);
	val = fpmin(fMaxValue, fValue);
#endif
	return fValue;
}

class CMenu
{
public:
	CMenu(void);

	void Think();

private:
	void DrawMouseCursor();

	void GetMouseStatus();
	bool IsMenuKey(int iKey);
	bool MouseOver(int x, int y, int w, int h);
	bool LeftClick(int x, int y, int w, int h);

	void DrawCheckbox(int x, int y, int iDistance, bool& bValue, const char* pchName);
	void DrawSlider(int x, int y, int w, int h, int iMin, int iMax, int iDistance, float& fValue, const char* pchName);

	void GetKeyPressed(int x, int y, int w, int h, int iDistance, int& iValue, const char* pchName);

	bool DragMenu(int& x, int& y, int w, int h, int iIndex);
	void DrawBorder(int x, int y, int w, int h, const char* pchText);
	void DrawMenu();

private:
	bool	m_bCursor;
	int		m_iCursorPosition[2];

	bool	m_bInKeyPressed;

	bool	m_bLeftClick, m_bRightClick;
	bool	m_bLeftClickRelease, m_bRightClickRelease;
};

extern CMenu g_Menu;

#endif