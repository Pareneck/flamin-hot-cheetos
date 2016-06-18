#include "Menu.h"

Menu menu;

Menu::Menu(void)
{
	isCursorActive = false;
	cursorPosition[0] = 0, cursorPosition[1] = 0;

	activeTab = 1;

	isKeyPressed = false;

	isLeftClick = false, isLeftClickReleased = false;
	isRightClick = false, isRightClickReleased = false;
}

void Menu::think(void)
{
	setMouse();
	getMouse();

	drawMenu();
	drawMouse();
}

void Menu::setMouse(void)
{
	if (!isMenuKey(VK_INSERT))
		return;

	isCursorActive = !isCursorActive;

	if (interfaces::engine->InGame())
	{
		char buffer[32];
		w_sprintf_s(buffer, sizeof(buffer), charenc("cl_mouseenable %i"), !isCursorActive);
		interfaces::engine->ExecuteClientCmd(buffer);
	}
}

void Menu::getMouse(void)
{
	if (!isCursorActive)
		return;

	if (GetAsyncKeyState(VK_LBUTTON))
	{
		isLeftClick = true;
	}
	else
	{
		if (isLeftClick)
			isLeftClickReleased = true;
		else
			isLeftClickReleased = false;

		isLeftClick = false;
	}

	if (GetAsyncKeyState(VK_RBUTTON))
	{
		isRightClick = true;
	}
	else
	{
		if (isRightClick)
			isRightClickReleased = true;
		else
			isRightClickReleased = false;

		isRightClick = false;
	}
}

bool Menu::isActive(void)
{
	return isCursorActive;
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
	if ((cursorPosition[0] > x) && (cursorPosition[0] < x + w) && (cursorPosition[1] > y) && (cursorPosition[1] < y + h))
		return true;

	return false;
}

bool Menu::isClicked(int x, int y, int w, int h)
{
	if (isLeftClickReleased && (cursorPosition[0] > x) && (cursorPosition[0] < x + w) && (cursorPosition[1] > y) && (cursorPosition[1] < y + h))
		return true;

	return false;
}

void Menu::drawMenu(void)
{
	if (!isCursorActive)
		return;

	static int x = 400, y = 400;
	int w = 540, h = 340;

	drawBorder(x, y, w, h, charenc("flamin' hot cheetos"));
	dragMenu(x, y, w, 20, 0);

	if (isClicked(x + 1, y + 30, 93, 15))
		activeTab = 1;
	else if (isClicked(x + 93, y + 30, 100, 15))
		activeTab = 2;
	else if (isClicked(x + 193, y + 30, 83, 15))
		activeTab = 3;

	if (isHovered(x + 1, y + 30, 93, 15))
		drawing.drawFilledRect(x + 1, y + 30, 93, 15, Color(255, 165, 0, 150));
	else if (isHovered(x + 93, y + 30, 100, 15))
		drawing.drawFilledRect(x + 93, y + 30, 100, 15, Color(255, 165, 0, 150));
	else if (isHovered(x + 193, y + 30, 83, 15))
		drawing.drawFilledRect(x + 193, y + 30, 83, 15, Color(255, 165, 0, 150));

	drawing.drawString(drawing.menuFont, true, x + 46, y + 32, Color(255, 255, 255), charenc("Aimbot"));
	drawing.drawString(drawing.menuFont, true, x + 140, y + 32, Color(255, 255, 255), charenc("Visuals"));
	drawing.drawString(drawing.menuFont, true, x + 233, y + 32, Color(255, 255, 255), charenc("Misc"));

	if (activeTab == 1)
	{
		drawing.drawFilledRect(x + 1, y + 30, 93, 15, Color(255, 165, 0));
		drawing.drawString(drawing.menuFont, true, x + 46, y + 32, Color(255, 255, 255), charenc("Aimbot"));

		drawCheckbox(x + 30, y + 55, 450, cvar::aimbot_enabled, charenc("Enable"));
		getKeyPressed(x + 30, y + 80, 50, 15, 430, cvar::general_key_aimbot, charenc("Aimbot Key"));
		drawSlider(x + 30, y + 105, 200, 6, 237, 0.f, 180.f, cvar::aimbot_fov, charenc("Field of View"));
		drawSlider(x + 30, y + 130, 200, 6, 237, 1.f, 100.f, cvar::aimbot_smoothing, charenc("Smoothing"));
		drawSlider(x + 30, y + 155, 200, 6, 237, 0.f, 2.f, cvar::aimbot_rcs_min, charenc("Randomize Recoil Control Min"));
		drawSlider(x + 30, y + 180, 200, 6, 237, cvar::aimbot_rcs_min, 2.f, cvar::aimbot_rcs_max, charenc("Randomize Recoil Control Max"));
		drawSlider(x + 30, y + 205, 200, 6, 237, 0.f, 20.f, cvar::aimbot_randomize_hitbox, charenc("Randomize Hitbox"));
		drawSlider(x + 30, y + 230, 200, 6, 237, 0.f, 20.f, cvar::aimbot_randomize_angle, charenc("Randomize Angle"));
	}
	else if (activeTab == 2)
	{
		drawing.drawFilledRect(x + 93, y + 30, 100, 15, Color(255, 165, 0));
		drawing.drawString(drawing.menuFont, true, x + 140, y + 32, Color(255, 255, 255), charenc("Visuals"));

		drawCheckbox(x + 30, y + 55, 450, cvar::esp_enabled, charenc("Enable"));
		drawCheckbox(x + 30, y + 80, 450, cvar::esp_draw_box, charenc("Boxes"));
		drawCheckbox(x + 30, y + 105, 450, cvar::esp_draw_name, charenc("Name"));
		drawCheckbox(x + 30, y + 130, 450, cvar::esp_draw_weapon, charenc("Weapon"));
		drawCheckbox(x + 30, y + 155, 450, cvar::esp_draw_callout, charenc("Callout"));
		drawCheckbox(x + 30, y + 180, 450, cvar::esp_draw_health, charenc("Health Bar"));
		drawCheckbox(x + 30, y + 205, 450, cvar::esp_draw_health_text, charenc("Health Text"));
		drawCheckbox(x + 30, y + 230, 450, cvar::esp_draw_armor, charenc("Armor Bar"));
		drawCheckbox(x + 30, y + 255, 450, cvar::esp_draw_armor_text, charenc("Armor Text"));
		drawCheckbox(x + 30, y + 280, 450, cvar::esp_draw_world, charenc("World"));
		drawCheckbox(x + 30, y + 305, 450, cvar::esp_draw_glow, charenc("Glow"));
	}
	else if (activeTab == 3)
	{
		drawing.drawFilledRect(x + 193, y + 30, 83, 15, Color(255, 165, 0));
		drawing.drawString(drawing.menuFont, true, x + 233, y + 32, Color(255, 255, 255), charenc("Misc"));

		drawCheckbox(x + 30, y + 55, 450, cvar::misc_bunnyhop, charenc("Bunnyhop"));
		drawCheckbox(x + 30, y + 80, 450, cvar::misc_triggerbot, charenc("Triggerbot"));
		getKeyPressed(x + 30, y + 105, 50, 15, 430, cvar::general_key_triggerbot, charenc("Triggerbot Key"));
		drawCheckbox(x + 30, y + 130, 450, cvar::misc_skinchanger, charenc("Skin Changer"));
		drawCheckbox(x + 30, y + 155, 450, cvar::misc_knifechanger, charenc("Knife Changer"));
		drawSlider(x + 30, y + 180, 200, 6, 237, 0, 9, cvar::misc_knifechanger_model, charenc("Knife Model"));
		drawSlider(x + 30, y + 205, 200, 6, 237, 0, 60, cvar::misc_overridefov, charenc("Viewmodel Field of View"));
		drawCheckbox(x + 30, y + 230, 450, cvar::misc_recoilcontrol, charenc("Standalone Recoil Control"));
		drawSlider(x + 30, y + 255, 200, 6, 237, 0.f, 2.f, cvar::misc_recoilcontrol_scale, charenc("Standalone Recoil Control Scale"));
	}

	drawing.drawFilledRect(x + 1, y + 45, w - 2, 2, Color(255, 165, 0));
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

void Menu::drawMouse(void)
{
	if (!isCursorActive)
		return;

	interfaces::surface->GetCursorPos(cursorPosition[0], cursorPosition[1]);

	drawing.drawFilledRect(cursorPosition[0] + 1, cursorPosition[1], 1, 17, Color(3, 6, 26));

	for (int i = 0; i < 11; i++)
		drawing.drawFilledRect(cursorPosition[0] + 2 + i, cursorPosition[1] + 1 + i, 1, 1, Color(3, 6, 26));

	drawing.drawFilledRect(cursorPosition[0] + 8, cursorPosition[1] + 12, 5, 1, Color(3, 6, 26));
	drawing.drawFilledRect(cursorPosition[0] + 8, cursorPosition[1] + 13, 1, 1, Color(3, 6, 26));
	drawing.drawFilledRect(cursorPosition[0] + 9, cursorPosition[1] + 14, 1, 2, Color(3, 6, 26));
	drawing.drawFilledRect(cursorPosition[0] + 10, cursorPosition[1] + 16, 1, 2, Color(3, 6, 26));
	drawing.drawFilledRect(cursorPosition[0] + 8, cursorPosition[1] + 18, 2, 1, Color(3, 6, 26));
	drawing.drawFilledRect(cursorPosition[0] + 7, cursorPosition[1] + 16, 1, 2, Color(3, 6, 26));
	drawing.drawFilledRect(cursorPosition[0] + 6, cursorPosition[1] + 14, 1, 2, Color(3, 6, 26));
	drawing.drawFilledRect(cursorPosition[0] + 5, cursorPosition[1] + 13, 1, 1, Color(3, 6, 26));
	drawing.drawFilledRect(cursorPosition[0] + 4, cursorPosition[1] + 14, 1, 1, Color(3, 6, 26));
	drawing.drawFilledRect(cursorPosition[0] + 3, cursorPosition[1] + 15, 1, 1, Color(3, 6, 26));
	drawing.drawFilledRect(cursorPosition[0] + 2, cursorPosition[1] + 16, 1, 1, Color(3, 6, 26));

	for (int i = 0; i < 4; i++)
		drawing.drawFilledRect(cursorPosition[0] + 2 + i, cursorPosition[1] + 2 + i, 1, 14 - (i * 2), Color(255 - (i * 4), 255 - (i * 4), 255 - (i * 4)));

	drawing.drawFilledRect(cursorPosition[0] + 6, cursorPosition[1] + 6, 1, 8, Color(235, 235, 235));
	drawing.drawFilledRect(cursorPosition[0] + 7, cursorPosition[1] + 7, 1, 9, Color(231, 231, 231));

	for (int i = 0; i < 4; i++)
		drawing.drawFilledRect(cursorPosition[0] + 8 + i, cursorPosition[1] + 8 + i, 1, 4 - i, Color(227 - (i * 4), 227 - (i * 4), 227 - (i * 4)));

	drawing.drawFilledRect(cursorPosition[0] + 8, cursorPosition[1] + 14, 1, 4, Color(207, 207, 207));
	drawing.drawFilledRect(cursorPosition[0] + 9, cursorPosition[1] + 16, 1, 2, Color(203, 203, 203));
}

void Menu::drawCheckbox(int x, int y, int distance, bool& value, const char* text)
{
	drawing.drawString(drawing.menuFont, false, x, y + 1.5f, Color(150, 150, 150), text);

	if (isClicked(x + distance, y + 2, 12, 12))
		value = !value;

	if (value)
		drawing.drawFilledRect(x + distance, y + 2, 12, 12, Color(255, 165, 0));

	drawing.drawOutlinedRect(x + distance, y + 2, 12, 12, Color(150, 150, 150));
}

void Menu::drawSlider(int x, int y, int w, int h, int distance, float min, float max, float& value, const char* text)
{
	drawing.drawString(drawing.menuFont, false, x, y + 1.5f, Color(150, 150, 150), text);

	float sliderPosition = 0.f, barPosition = 0.f;

	if (isHovered(x + distance - 2, y - 2, w + 4, h + 4) && isLeftClick)
	{
		sliderPosition = (cursorPosition[0] - (x + distance));
		float range = (max - min) * (sliderPosition / w);
		value = clamp(min + range, min, max);
	}
	else
	{
		sliderPosition = ((value * 100) * 2) / max;
	}

	if (sliderPosition <= 1)
		sliderPosition = 0;

	barPosition = (sliderPosition / w * 100) * 2;

	if (barPosition > w)
		barPosition = w;

	drawing.drawFilledRect(x + distance, y + 4.5f, barPosition, h, Color(255, 165, 0));
	drawing.drawOutlinedRect(x + distance, y + 4.5f, w + 1, h, Color(0, 0, 0));

	drawing.drawFilledRect(x + barPosition + distance, y + 2.8f, 2, 10, Color(255, 165, 0));
	drawing.drawOutlinedRect(x + barPosition + distance, y + 2.8f, 3, 11, Color(0, 0, 0));

	if (value >= 0.f && value < 10.f)
		drawing.drawString(drawing.menuFont, false, x + w + 15 + distance, y + 1.5f, Color(150, 150, 150), "%.1f", value);
	else if (value > 9.f && value < 100.f)
		drawing.drawString(drawing.menuFont, false, x + w + 15 + distance, y + 1.5f, Color(150, 150, 150), "%.1f", value);
	else if (value > 99.f && value < 1000.f)
		drawing.drawString(drawing.menuFont, false, x + w + 15 + distance, y + 1.5f, Color(150, 150, 150), "%.1f", value);
}

void Menu::drawSlider(int x, int y, int w, int h, int distance, int min, int max, int& value, const char* text)
{
	drawing.drawString(drawing.menuFont, false, x, y + 1.5f, Color(150, 150, 150), text);

	float sliderPosition = 0.f, barPosition = 0.f;

	if (isHovered(x + distance - 2, y - 2, w + 4, h + 4) && isLeftClick)
	{
		sliderPosition = (cursorPosition[0] - (x + distance));
		float range = (max - min) * (sliderPosition / w);
		value = clamp(roundf(min + range), min, max);
	}
	else
	{
		sliderPosition = ((value * 100) * 2) / max;
	}

	if (sliderPosition <= 1)
		sliderPosition = 0;

	barPosition = (sliderPosition / w * 100) * 2;

	if (barPosition > w)
		barPosition = w;

	drawing.drawFilledRect(x + distance, y + 4.5f, barPosition, h, Color(255, 165, 0));
	drawing.drawOutlinedRect(x + distance, y + 4.5f, w + 1, h, Color(0, 0, 0));

	drawing.drawFilledRect(x + barPosition + distance, y + 2.8f, 2, 10, Color(255, 165, 0));
	drawing.drawOutlinedRect(x + barPosition + distance, y + 2.8f, 3, 11, Color(0, 0, 0));

	if (value >= 0 && value < 10)
		drawing.drawString(drawing.menuFont, false, x + w + 15 + distance, y + 1.5f, Color(150, 150, 150), "%i", value);
	else if (value > 9 && value < 100)
		drawing.drawString(drawing.menuFont, false, x + w + 15 + distance, y + 1.5f, Color(150, 150, 150), "%i", value);
	else if (value > 99 && value < 1000)
		drawing.drawString(drawing.menuFont, false, x + w + 15 + distance, y + 1.5f, Color(150, 150, 150), "%i", value);
}

void Menu::getKeyPressed(int x, int y, int w, int h, int distance, int& value, const char* text)
{
	drawing.drawString(drawing.menuFont, false, x, y + (float)1.5, Color(150, 150, 150), text);

	drawing.drawOutlinedRect(x + distance, y, w, h, Color(150, 150, 150));

	if (isClicked(x - 2 + distance, y - 2, w + 4, h + 4))
		isKeyPressed = true;

	if (isKeyPressed)
	{
		drawing.drawString(drawing.menuFont, true, x + w / 2 + distance, y + 1, Color(150, 150, 150), "...");

		for (int i = 1; i < 255; i++)
		{
			if (GetAsyncKeyState(i) & 0x8000)
			{
				value = i;
				isKeyPressed = false;
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

	if (isLeftClick)
	{
		if (cursorPosition[0] > x && cursorPosition[0] < x + w && cursorPosition[1] > (y - 20 - 3) && cursorPosition[1] < (y - 20 - 3) + h || isActive[index][0])
		{
			isActive[index][0] = true;

			if (!isActive[index][1])
			{
				newCursorPosition[0] = cursorPosition[0] - x;
				newCursorPosition[1] = cursorPosition[1] - y;
				isActive[index][1] = true;
			}
		}
		else
		{
			isActive[index][0] = false;
			isActive[index][1] = false;
		}
	}

	if (!isLeftClick && isActive[0][0])
	{
		isActive[index][0] = false;
		isActive[index][1] = false;
	}

	if (isActive[index][0])
	{
		x = cursorPosition[0] - newCursorPosition[0];
		y = cursorPosition[1] - newCursorPosition[1];
	}

	return true;
}