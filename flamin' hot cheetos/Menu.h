#ifndef MENU_H
#define MENU_H

#pragma once

#include "stdafx.h"

__forceinline float clamp(float value, float minValue, float maxValue)
{
#if defined(__i386__) || defined(_M_IX86)
	_mm_store_ss(&value,
		_mm_min_ss(
			_mm_max_ss(
				_mm_load_ss(&value),
				_mm_load_ss(&minValue)),
			_mm_load_ss(&maxValue)));
#else
	val = fpmax(minValue, value);
	val = fpmin(maxValue, value);
#endif
	return value;
}

class Menu
{
public:
	Menu(void);

	void think();

private:
	void setMouse();
	void getMouse();

	bool isMenuKey(int key);
	bool isHovered(int x, int y, int w, int h);
	bool isClicked(int x, int y, int w, int h);

	void drawMenu();
	void drawBorder(int x, int y, int w, int h, const char* text);
	void drawMouse();
	void drawCheckbox(int x, int y, int distance, bool& value, const char* text);
	void drawSlider(int x, int y, int w, int h, int distance, float min, float max, float& value, const char* text);
	void drawSlider(int x, int y, int w, int h, int distance, int min, int max, int& value, const char* text);

	void getKeyPressed(int x, int y, int w, int h, int distance, int& value, const char* text);

	bool dragMenu(int& x, int& y, int w, int h, int index);

private:
	bool isCursorActive_;
	int  cursorPosition_[2];

	int  activeTab_;

	bool isKeyPressed_;

	bool isLeftClick_, isRightClick_;
	bool isLeftClickReleased_, isRightClickReleased_;
};

extern Menu menu;

#endif