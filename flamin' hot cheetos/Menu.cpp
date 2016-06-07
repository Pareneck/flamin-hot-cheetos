#include "Menu.h"

Menu menu;

Menu::Menu(void)
{
	isCursorActive_ = false;
	cursorPosition_[0] = 0, cursorPosition_[1] = 0;

	activeTab_ = 0;

	isKeyPressed_ = false;

	isLeftClick_ = false, isLeftClickReleased_ = false;
	isRightClick_ = false, isRightClickReleased_ = false;
}

void Menu::think()
{
	setMouse();
	getMouse();

	drawMenu();
	drawMouse();
}

void Menu::setMouse()
{
	if (!isMenuKey(VK_INSERT))
		return;

	isCursorActive_ = !isCursorActive_;

	if (interfaces::engine->InGame())
	{
		char buffer[32];
		w_sprintf_s(buffer, sizeof(buffer), charenc("cl_mouseenable %i"), !isCursorActive_);
		interfaces::engine->ExecuteClientCmd(buffer);
	}
}

void Menu::getMouse()
{
	if (!isCursorActive_)
		return;

	if (GetAsyncKeyState(VK_LBUTTON))
	{
		isLeftClick_ = true;
	}
	else
	{
		if (isLeftClick_)
			isLeftClickReleased_ = true;
		else
			isLeftClickReleased_ = false;

		isLeftClick_ = false;
	}

	if (GetAsyncKeyState(VK_RBUTTON))
	{
		isRightClick_ = true;
	}
	else
	{
		if (isRightClick_)
			isRightClickReleased_ = true;
		else
			isRightClickReleased_ = false;

		isRightClick_ = false;
	}
}

bool Menu::isMenuKey(int key)
{
	static bool isKeyPressed[256];

	if (GetAsyncKeyState(key) & 1)
	{
		if (!isKeyPressed[key])
		{
			isKeyPressed[key] = true;
			return true;
		}
	}
	else
	{
		isKeyPressed[key] = false;
	}

	return false;
}

bool Menu::isHovered(int x, int y, int w, int h)
{
	if ((cursorPosition_[0] > x) && (cursorPosition_[0] < x + w) && (cursorPosition_[1] > y) && (cursorPosition_[1] < y + h))
		return true;

	return false;
}

bool Menu::isClicked(int x, int y, int w, int h)
{
	if (isLeftClickReleased_ && (cursorPosition_[0] > x) && (cursorPosition_[0] < x + w) && (cursorPosition_[1] > y) && (cursorPosition_[1] < y + h))
		return true;

	return false;
}

void Menu::drawMenu()
{
	if (!isCursorActive_)
		return;

	static int x = 400, y = 400;
	int w = 540, h = 340;

	drawBorder(x, y, w, h, charenc("flamin' hot cheetos"));
	dragMenu(x, y, w, 20, 0);

	if (isClicked(x + 1, y + 30, 93, 15))
		activeTab_ = 1;
	else if (isClicked(x + 93, y + 30, 100, 15))
		activeTab_ = 2;
	else if (isClicked(x + 193, y + 30, 83, 15))
		activeTab_ = 3;

	if (isHovered(x + 1, y + 30, 93, 15))
		drawing.drawFilledRect(x + 1, y + 30, 93, 15, Color(5, 120, 210, 150));
	else if (isHovered(x + 93, y + 30, 100, 15))
		drawing.drawFilledRect(x + 93, y + 30, 100, 15, Color(5, 120, 210, 150));
	else if (isHovered(x + 193, y + 30, 83, 15))
		drawing.drawFilledRect(x + 193, y + 30, 83, 15, Color(5, 120, 210, 150));

	drawing.drawString(drawing.menuFont, true, x + 46, y + 32, Color(255, 255, 255), charenc("Aimbot"));
	drawing.drawString(drawing.menuFont, true, x + 140, y + 32, Color(255, 255, 255), charenc("Visuals"));
	drawing.drawString(drawing.menuFont, true, x + 233, y + 32, Color(255, 255, 255), charenc("Misc"));

	if (activeTab_ == 1)
	{
		drawing.drawFilledRect(x + 1, y + 30, 93, 15, Color(5, 120, 210));
		drawing.drawString(drawing.menuFont, true, x + 46, y + 32, Color(255, 255, 255), charenc("Aimbot"));
	}
	else if (activeTab_ == 2)
	{
		drawing.drawFilledRect(x + 93, y + 30, 100, 15, Color(5, 120, 210));
		drawing.drawString(drawing.menuFont, true, x + 140, y + 32, Color(255, 255, 255), charenc("Visuals"));

		drawCheckbox(x + 30, y + 55, 450, cvar::esp_enabled, charenc("Enable ESP"));
		drawCheckbox(x + 30, y + 80, 450, cvar::esp_draw_box, charenc("Draw Boxes"));
		drawCheckbox(x + 30, y + 105, 450, cvar::esp_draw_name, charenc("Draw Name"));
		drawCheckbox(x + 30, y + 130, 450, cvar::esp_draw_weapon, charenc("Draw Weapon"));
		drawCheckbox(x + 30, y + 155, 450, cvar::esp_draw_callout, charenc("Draw Callout"));
	}
	else if (activeTab_ == 3)
	{
		drawing.drawFilledRect(x + 193, y + 30, 83, 15, Color(5, 120, 210));
		drawing.drawString(drawing.menuFont, true, x + 233, y + 32, Color(255, 255, 255), charenc("Misc"));

		drawCheckbox(x + 30, y + 55, 450, cvar::misc_bunnyhop, charenc("Bunnyhop"));
	}

	drawing.drawFilledRect(x + 1, y + 45, w - 2, 2, Color(5, 120, 210));
}

void Menu::drawBorder(int x, int y, int w, int h, const char* text)
{
	drawing.drawFilledRect(x, y, w, h, Color(0, 0, 0));

	drawing.drawFilledRect(x + 1, y + 1, w - 2, 20, Color(44, 44, 44));
	drawing.drawLine(x + 1, y + 1, x + w - 2, y + 1, Color(130, 130, 130, 50));

	if (isHovered(x + 1, y + 1, w - 2, 20))
		drawing.drawFilledRect(x + 3, y + 3, w - 6, 16, Color(80, 80, 80, 90));

	drawing.drawString(drawing.menuTitleFont, true, x + w / 2, y + 5, Color(255, 255, 255), text);

	drawing.drawFilledRect(x + 1, y + 22, w - 2, h - 23, Color(50, 50, 50));
	drawing.drawLine(x + 1, y + 22, x + w - 2, y + 22, Color(130, 130, 130, 50));
}

void Menu::drawMouse()
{
	if (!isCursorActive_)
		return;

	interfaces::surface->GetCursorPos(cursorPosition_[0], cursorPosition_[1]);

	drawing.drawFilledRect(cursorPosition_[0] + 1, cursorPosition_[1], 1, 17, Color(3, 6, 26));

	for (int i = 0; i < 11; i++)
		drawing.drawFilledRect(cursorPosition_[0] + 2 + i, cursorPosition_[1] + 1 + i, 1, 1, Color(3, 6, 26));

	drawing.drawFilledRect(cursorPosition_[0] + 8, cursorPosition_[1] + 12, 5, 1, Color(3, 6, 26));
	drawing.drawFilledRect(cursorPosition_[0] + 8, cursorPosition_[1] + 13, 1, 1, Color(3, 6, 26));
	drawing.drawFilledRect(cursorPosition_[0] + 9, cursorPosition_[1] + 14, 1, 2, Color(3, 6, 26));
	drawing.drawFilledRect(cursorPosition_[0] + 10, cursorPosition_[1] + 16, 1, 2, Color(3, 6, 26));
	drawing.drawFilledRect(cursorPosition_[0] + 8, cursorPosition_[1] + 18, 2, 1, Color(3, 6, 26));
	drawing.drawFilledRect(cursorPosition_[0] + 7, cursorPosition_[1] + 16, 1, 2, Color(3, 6, 26));
	drawing.drawFilledRect(cursorPosition_[0] + 6, cursorPosition_[1] + 14, 1, 2, Color(3, 6, 26));
	drawing.drawFilledRect(cursorPosition_[0] + 5, cursorPosition_[1] + 13, 1, 1, Color(3, 6, 26));
	drawing.drawFilledRect(cursorPosition_[0] + 4, cursorPosition_[1] + 14, 1, 1, Color(3, 6, 26));
	drawing.drawFilledRect(cursorPosition_[0] + 3, cursorPosition_[1] + 15, 1, 1, Color(3, 6, 26));
	drawing.drawFilledRect(cursorPosition_[0] + 2, cursorPosition_[1] + 16, 1, 1, Color(3, 6, 26));

	for (int i = 0; i < 4; i++)
		drawing.drawFilledRect(cursorPosition_[0] + 2 + i, cursorPosition_[1] + 2 + i, 1, 14 - (i * 2), Color(255 - (i * 4), 255 - (i * 4), 255 - (i * 4)));

	drawing.drawFilledRect(cursorPosition_[0] + 6, cursorPosition_[1] + 6, 1, 8, Color(235, 235, 235));
	drawing.drawFilledRect(cursorPosition_[0] + 7, cursorPosition_[1] + 7, 1, 9, Color(231, 231, 231));

	for (int i = 0; i < 4; i++)
		drawing.drawFilledRect(cursorPosition_[0] + 8 + i, cursorPosition_[1] + 8 + i, 1, 4 - i, Color(227 - (i * 4), 227 - (i * 4), 227 - (i * 4)));

	drawing.drawFilledRect(cursorPosition_[0] + 8, cursorPosition_[1] + 14, 1, 4, Color(207, 207, 207));
	drawing.drawFilledRect(cursorPosition_[0] + 9, cursorPosition_[1] + 16, 1, 2, Color(203, 203, 203));
}

void Menu::drawCheckbox(int x, int y, int distance, bool& value, const char* text)
{
	drawing.drawString(drawing.menuFont, false, x, y + 1.5f, Color(150, 150, 150), text);

	if (isClicked(x + distance, y + 2, 12, 12))
		value = !value;

	if (value)
		drawing.drawFilledRect(x + distance, y + 2, 12, 12, Color(5, 120, 210));

	drawing.drawOutlinedRect(x + distance, y + 2, 12, 12, Color(150, 150, 150));
}

void Menu::drawSlider(int x, int y, int w, int h, int min, int max, int distance, float& value, const char* text)
{
	drawing.drawString(drawing.menuFont, false, x, y + 1.5f, Color(150, 150, 150), text);

	float sliderPosition = 0.f, barPosition = 0.f;

	if (isHovered(x + distance - 2, y + 1.5f, w + 4, h + 4) && isLeftClick_)
		sliderPosition = (cursorPosition_[0] - x + distance);
	else
		sliderPosition = (((value * 100) * 2) / max);

	if (sliderPosition <= 1)
		sliderPosition = 0;

	value = max * (sliderPosition / 2.f) / 100;

	barPosition = (sliderPosition / w * 100) * 2;

	if (barPosition > w)
		barPosition = w;

	value = clamp(value, min, max);

	drawing.drawFilledRect(x + distance, y + 4.5f, barPosition, h, Color(5, 120, 210));
	drawing.drawOutlinedRect(x + distance, y + 4.5f, w + 1, h, Color(0, 0, 0));

	drawing.drawFilledRect(x + barPosition + distance, y + 2.8f, 2, 10, Color(5, 120, 210));
	drawing.drawOutlinedRect(x + barPosition + distance, y + 2.8f, 3, 11, Color(0, 0, 0));

	if (value >= 0.f && value < 10.f)
		drawing.drawString(drawing.menuFont, false, x + w + 15 + distance, y + 1.5f, Color(150, 150, 150), "%i", value);
	else if (value > 9.f && value < 100.f)
		drawing.drawString(drawing.menuFont, false, x + w + 12 + distance, y + 1.5f, Color(150, 150, 150), "%i", value);
	else if (value > 99.f && value < 1000.f)
		drawing.drawString(drawing.menuFont, false, x + w + 9 + distance, y + 1.5f, Color(150, 150, 150), "%i", value);
	else if (value > 999.f && value < 10000.f)
		drawing.drawString(drawing.menuFont, false, x + w + 6 + distance, y + 1.5f, Color(150, 150, 150), "%i", value);
}

void Menu::getKeyPressed(int x, int y, int w, int h, int distance, int& value, const char* text)
{
	drawing.drawString(drawing.menuFont, false, x, y + (float)1.5, Color(150, 150, 150), text);

	drawing.drawOutlinedRect(x + distance, y, w, h, Color(150, 150, 150));

	if (isClicked(x - 2 + distance, y - 2, w + 4, h + 4))
		isKeyPressed_ = true;

	if (isKeyPressed_)
	{
		static int iCount = 0;
		iCount++;

		if (iCount > 1500)
			iCount = 0;

		if (iCount > 0 && iCount < 500)
			drawing.drawString(drawing.menuFont, true, x + w / 2 + distance, y + 1, Color(150, 150, 150), ".");
		else if (iCount > 500 && iCount < 1000)
			drawing.drawString(drawing.menuFont, true, x + w / 2 + distance, y + 1, Color(150, 150, 150), "..");
		else if (iCount > 1000 && iCount < 1500)
			drawing.drawString(drawing.menuFont, true, x + w / 2 + distance, y + 1, Color(150, 150, 150), "...");

		for (int i = 1; i < 255; i++)
		{
			if (GetAsyncKeyState(i) & 0x8000)
			{
				value = i;
				isKeyPressed_ = false;
			}
		}
	}
	else
	{
		drawing.drawString(drawing.menuFont, true, x + w / 2 + distance, y + 1, Color(150, 150, 150), "%i", value);
	}
}

bool Menu::dragMenu(int& x, int& y, int w, int h, int index)
{
	static bool isActive[8][2];
	static int newCursorPosition[2];

	for (int i = 0; i < 8; i++)
	{
		if (isActive[i][0] && i != 0)
			return false;
	}

	if (isLeftClick_)
	{
		if (cursorPosition_[0] > x && cursorPosition_[0] < x + w && cursorPosition_[1] > (y - 20 - 3) && cursorPosition_[1] < (y - 20 - 3) + h || isActive[index][0])
		{
			isActive[index][0] = true;

			if (!isActive[index][1])
			{
				newCursorPosition[0] = cursorPosition_[0] - x;
				newCursorPosition[1] = cursorPosition_[1] - y;
				isActive[index][1] = true;
			}
		}
		else
		{
			isActive[index][0] = false;
			isActive[index][1] = false;
		}
	}

	if (!isLeftClick_ && isActive[0][0])
	{
		isActive[index][0] = false;
		isActive[index][1] = false;
	}

	if (isActive[index][0])
	{
		x = cursorPosition_[0] - newCursorPosition[0];
		y = cursorPosition_[1] - newCursorPosition[1];
	}

	return true;
}