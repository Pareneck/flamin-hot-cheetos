#include "Menu.h"

CMenu g_Menu;

CMenu::CMenu(void)
{
	m_bCursor = false;

	m_iCursorPosition[0] = 0;
	m_iCursorPosition[1] = 0;

	m_bLeftClick = false;
	m_bLeftClickRelease = false;
	m_bRightClick = false;
	m_bRightClickRelease = false;

	m_bInKeyPressed = false;
}

void CMenu::Think()
{
	static const char* pchCommand = charenc("cl_mouseenable %i");

	if (this->IsMenuKey(VK_INSERT))
	{
		m_bCursor = !m_bCursor;

		if (g_pEngine->InGame())
		{
			char chBuffer[32];
			sprintf(chBuffer, pchCommand, !m_bCursor);
			g_pEngine->ExecuteClientCmd(chBuffer);
		}
	}

	this->GetMouseStatus();
	this->DrawMenu();
	this->DrawMouseCursor();
}

void CMenu::DrawMouseCursor()
{
	if (!m_bCursor)
		return;

	g_pSurface->GetCursorPos(m_iCursorPosition[0], m_iCursorPosition[1]);

	g_Drawing.DrawFilledRect(m_iCursorPosition[0] + 1, m_iCursorPosition[1], 1, 17, Color(3, 6, 26));

	for (int i = 0; i < 11; i++)
		g_Drawing.DrawFilledRect(m_iCursorPosition[0] + 2 + i, m_iCursorPosition[1] + 1 + i, 1, 1, Color(3, 6, 26));

	g_Drawing.DrawFilledRect(m_iCursorPosition[0] + 8, m_iCursorPosition[1] + 12, 5, 1, Color(3, 6, 26));
	g_Drawing.DrawFilledRect(m_iCursorPosition[0] + 8, m_iCursorPosition[1] + 13, 1, 1, Color(3, 6, 26));
	g_Drawing.DrawFilledRect(m_iCursorPosition[0] + 9, m_iCursorPosition[1] + 14, 1, 2, Color(3, 6, 26));
	g_Drawing.DrawFilledRect(m_iCursorPosition[0] + 10, m_iCursorPosition[1] + 16, 1, 2, Color(3, 6, 26));
	g_Drawing.DrawFilledRect(m_iCursorPosition[0] + 8, m_iCursorPosition[1] + 18, 2, 1, Color(3, 6, 26));
	g_Drawing.DrawFilledRect(m_iCursorPosition[0] + 7, m_iCursorPosition[1] + 16, 1, 2, Color(3, 6, 26));
	g_Drawing.DrawFilledRect(m_iCursorPosition[0] + 6, m_iCursorPosition[1] + 14, 1, 2, Color(3, 6, 26));
	g_Drawing.DrawFilledRect(m_iCursorPosition[0] + 5, m_iCursorPosition[1] + 13, 1, 1, Color(3, 6, 26));
	g_Drawing.DrawFilledRect(m_iCursorPosition[0] + 4, m_iCursorPosition[1] + 14, 1, 1, Color(3, 6, 26));
	g_Drawing.DrawFilledRect(m_iCursorPosition[0] + 3, m_iCursorPosition[1] + 15, 1, 1, Color(3, 6, 26));
	g_Drawing.DrawFilledRect(m_iCursorPosition[0] + 2, m_iCursorPosition[1] + 16, 1, 1, Color(3, 6, 26));

	for (int i = 0; i < 4; i++)
		g_Drawing.DrawFilledRect(m_iCursorPosition[0] + 2 + i, m_iCursorPosition[1] + 2 + i, 1, 14 - (i * 2), Color(255 - (i * 4), 255 - (i * 4), 255 - (i * 4)));

	g_Drawing.DrawFilledRect(m_iCursorPosition[0] + 6, m_iCursorPosition[1] + 6, 1, 8, Color(235, 235, 235));
	g_Drawing.DrawFilledRect(m_iCursorPosition[0] + 7, m_iCursorPosition[1] + 7, 1, 9, Color(231, 231, 231));

	for (int i = 0; i < 4; i++)
		g_Drawing.DrawFilledRect(m_iCursorPosition[0] + 8 + i, m_iCursorPosition[1] + 8 + i, 1, 4 - i, Color(227 - (i * 4), 227 - (i * 4), 227 - (i * 4)));

	g_Drawing.DrawFilledRect(m_iCursorPosition[0] + 8, m_iCursorPosition[1] + 14, 1, 4, Color(207, 207, 207));
	g_Drawing.DrawFilledRect(m_iCursorPosition[0] + 9, m_iCursorPosition[1] + 16, 1, 2, Color(203, 203, 203));
}

void CMenu::GetMouseStatus()
{
	if (!m_bCursor)
		return;

	if (GetAsyncKeyState(VK_LBUTTON))
	{
		m_bLeftClick = true;
	}
	else
	{
		if (m_bLeftClick)
			m_bLeftClickRelease = true;
		else
			m_bLeftClickRelease = false;

		m_bLeftClick = false;
	}

	if (GetAsyncKeyState(VK_RBUTTON))
	{
		m_bRightClick = true;
	}
	else
	{
		if (m_bRightClick)
			m_bRightClickRelease = true;
		else
			m_bRightClickRelease = false;

		m_bRightClick = false;
	}
}

bool CMenu::IsMenuKey(int iKey)
{
	static bool bKeyPressed[256];

	if (GetAsyncKeyState(iKey) & 1)
	{
		if (!bKeyPressed[iKey])
		{
			bKeyPressed[iKey] = true;
			return true;
		}
	}
	else
	{
		bKeyPressed[iKey] = false;
	}

	return false;
}

bool CMenu::MouseOver(int x, int y, int w, int h)
{
	if ((m_iCursorPosition[0] > x) && (m_iCursorPosition[0] < x + w) && (m_iCursorPosition[1] > y) && (m_iCursorPosition[1] < y + h))
		return true;

	return false;
}

bool CMenu::LeftClick(int x, int y, int w, int h)
{
	if (m_bLeftClickRelease && (m_iCursorPosition[0] > x) && (m_iCursorPosition[0] < x + w) && (m_iCursorPosition[1] > y) && (m_iCursorPosition[1] < y + h))
		return true;

	return false;
}

void CMenu::DrawCheckbox(int x, int y, int iDistance, bool& bValue, const char* pchName)
{
	g_Drawing.DrawString(g_Drawing.m_MenuFont, false, x, y + 1.5f, Color(150, 150, 150), pchName);

	if (this->LeftClick(x + iDistance, y + 2, 12, 12))
		bValue = !bValue;

	if (bValue)
		g_Drawing.DrawFilledRect(x + iDistance, y + 2, 12, 12, Color(5, 120, 210));

	g_Drawing.DrawOutlinedRect(x + iDistance, y + 2, 12, 12, Color(150, 150, 150));
}

void CMenu::DrawSlider(int x, int y, int w, int h, int iMin, int iMax, int iDistance, float& fValue, const char* pchName)
{
	g_Drawing.DrawString(g_Drawing.m_MenuFont, false, x, y + 1.5f, Color(150, 150, 150), pchName);

	float fSiderPosition, fBarPosition;

	int iXDistance = x + iDistance;

	if (this->MouseOver(iXDistance - 2, y + 1.5f, w + 4, h + 4) && m_bLeftClick)
		fSiderPosition = (m_iCursorPosition[0] - iXDistance);
	else
		fSiderPosition = (((fValue * 100) * 2) / iMax);

	if (fSiderPosition <= 1)
		fSiderPosition = 0;

	fValue = iMax * (fSiderPosition / 2) / 100;

	fBarPosition = (fSiderPosition / w * 100) * 2;

	if (fBarPosition > w)
		fBarPosition = w;

	fValue = clamp(fValue, iMin, iMax);

	g_Drawing.DrawFilledRect(x + iDistance, y + 4.5f, fBarPosition, h, Color(5, 120, 210));
	g_Drawing.DrawOutlinedRect(x + iDistance, y + 4.5f, w + 1, h, Color(0, 0, 0));

	g_Drawing.DrawFilledRect(x + fBarPosition + iDistance, y + 2.8f, 2, 10, Color(5, 120, 210));
	g_Drawing.DrawOutlinedRect(x + fBarPosition + iDistance, y + 2.8f, 3, 11, Color(0, 0, 0));

	if (fValue >= 0.f && fValue < 10.f)
		g_Drawing.DrawString(g_Drawing.m_MenuFont, false, x + w + 15 + iDistance, y + 1.5f, Color(150, 150, 150), "%i", fValue);
	else if (fValue > 9.f && fValue < 100.f)
		g_Drawing.DrawString(g_Drawing.m_MenuFont, false, x + w + 12 + iDistance, y + 1.5f, Color(150, 150, 150), "%i", fValue);
	else if (fValue > 99.f && fValue < 1000.f)
		g_Drawing.DrawString(g_Drawing.m_MenuFont, false, x + w + 9 + iDistance, y + 1.5f, Color(150, 150, 150), "%i", fValue);
	else if (fValue > 999.f && fValue < 10000.f)
		g_Drawing.DrawString(g_Drawing.m_MenuFont, false, x + w + 6 + iDistance, y + 1.5f, Color(150, 150, 150), "%i", fValue);
}

void CMenu::GetKeyPressed(int x, int y, int w, int h, int iDistance, int& iValue, const char* pchName)
{
	g_Drawing.DrawString(g_Drawing.m_MenuFont, false, x, y + (float)1.5, Color(150, 150, 150), pchName);

	g_Drawing.DrawOutlinedRect(x + iDistance, y, w, h, Color(150, 150, 150));

	if (this->LeftClick(x - 2 + iDistance, y - 2, w + 4, h + 4))
		m_bInKeyPressed = true;

	if (m_bInKeyPressed)
	{
		static int iCount = 0;
		iCount++;

		if (iCount > 1500)
			iCount = 0;

		if (iCount > 0 && iCount < 500)
			g_Drawing.DrawString(g_Drawing.m_MenuFont, true, x + w / 2 + iDistance, y + 1, Color(150, 150, 150), ".");
		else if (iCount > 500 && iCount < 1000)
			g_Drawing.DrawString(g_Drawing.m_MenuFont, true, x + w / 2 + iDistance, y + 1, Color(150, 150, 150), "..");
		else if (iCount > 1000 && iCount < 1500)
			g_Drawing.DrawString(g_Drawing.m_MenuFont, true, x + w / 2 + iDistance, y + 1, Color(150, 150, 150), "...");

		for (int i = 1; i < 255; i++)
		{
			if (GetAsyncKeyState(i) & 0x8000)
			{
				iValue = i;
				m_bInKeyPressed = false;
			}
		}
	}
	else
	{
		g_Drawing.DrawString(g_Drawing.m_MenuFont, true, x + w / 2 + iDistance, y + 1, Color(150, 150, 150), "%i", iValue);
	}
}

bool CMenu::DragMenu(int& x, int& y, int w, int h, int iIndex)
{
	static bool bWind[8][2];
	static int iClack[2];

	for (int i = 0; i < 8; i++)
	{
		if (bWind[i][0] && i != 0)
			return false;
	}

	if (m_bLeftClick)
	{
		if (m_iCursorPosition[0] > x && m_iCursorPosition[0] < x + w && m_iCursorPosition[1] > (y - 20 - 3) && m_iCursorPosition[1] < (y - 20 - 3) + h || bWind[iIndex][0])
		{
			bWind[iIndex][0] = true;

			if (!bWind[iIndex][1])
			{
				iClack[0] = m_iCursorPosition[0] - x;
				iClack[1] = m_iCursorPosition[1] - y;
				bWind[iIndex][1] = true;
			}
		}
		else
		{
			bWind[iIndex][0] = false;
			bWind[iIndex][1] = false;
		}
	}

	if (!m_bLeftClick && bWind[0][0])
	{
		bWind[iIndex][0] = false;
		bWind[iIndex][1] = false;
	}

	if (bWind[iIndex][0])
	{
		x = m_iCursorPosition[0] - iClack[0];
		y = m_iCursorPosition[1] - iClack[1];
	}

	return true;
}

void CMenu::DrawBorder(int x, int y, int w, int h, const char* pchText)
{
	g_Drawing.DrawFilledRect(x, y, w, h, Color(0, 0, 0));

	g_Drawing.DrawFilledRect(x + 1, y + 1, w - 2, 20, Color(44, 44, 44));
	g_Drawing.DrawLine(x + 1, y + 1, x + w - 2, y + 1, Color(130, 130, 130, 50));

	if (this->MouseOver(x + 1, y + 1, w - 2, 20))
		g_Drawing.DrawFilledRect(x + 3, y + 3, w - 6, 16, Color(80, 80, 80, 90));

	g_Drawing.DrawString(g_Drawing.m_ESPFont, true, x + w / 2, y + 5, Color(255, 255, 255), pchText);

	g_Drawing.DrawFilledRect(x + 1, y + 22, w - 2, h - 23, Color(50, 50, 50));
	g_Drawing.DrawLine(x + 1, y + 22, x + w - 2, y + 22, Color(130, 130, 130, 50));
}

void CMenu::DrawMenu()
{
	if (!m_bCursor)
		return;

	static int x = 400, y = 400;
	int w = 540, h = 340;

	this->DragMenu(x, y, w, 20, 0);

	static int iTab = 1;
	this->DrawBorder(x, y, w, h, charenc("flamin' hot cheetos"));

	if (this->LeftClick(x + 1, y + 30, 93, 15))
		iTab = 1;
	else if (this->LeftClick(x + 93, y + 30, 100, 15))
		iTab = 2;
	else if (this->LeftClick(x + 193, y + 30, 83, 15))
		iTab = 3;

	if (this->MouseOver(x + 1, y + 30, 93, 15))
		g_Drawing.DrawFilledRect(x + 1, y + 30, 93, 15, Color(5, 120, 210, 150));
	else if (this->MouseOver(x + 93, y + 30, 100, 15))
		g_Drawing.DrawFilledRect(x + 93, y + 30, 100, 15, Color(5, 120, 210, 150));
	else if (this->MouseOver(x + 193, y + 30, 83, 15))
		g_Drawing.DrawFilledRect(x + 193, y + 30, 83, 15, Color(5, 120, 210, 150));

	g_Drawing.DrawString(g_Drawing.m_MenuFont, true, x + 46, y + 32, Color(255, 255, 255), charenc("Aimbot"));
	g_Drawing.DrawString(g_Drawing.m_MenuFont, true, x + 140, y + 32, Color(255, 255, 255), charenc("Visuals"));
	g_Drawing.DrawString(g_Drawing.m_MenuFont, true, x + 233, y + 32, Color(255, 255, 255), charenc("Misc"));

	if (iTab == 1)
	{
		g_Drawing.DrawFilledRect(x + 1, y + 30, 93, 15, Color(5, 120, 210));
		g_Drawing.DrawString(g_Drawing.m_MenuFont, true, x + 46, y + 32, Color(255, 255, 255), charenc("Aimbot"));
	}
	else if (iTab == 2)
	{
		g_Drawing.DrawFilledRect(x + 93, y + 30, 100, 15, Color(5, 120, 210));
		g_Drawing.DrawString(g_Drawing.m_MenuFont, true, x + 140, y + 32, Color(255, 255, 255), charenc("Visuals"));

		this->DrawCheckbox(x + 30, y + 55, 450, CVars::g_bESPEnabled, charenc("Enable ESP"));
		this->DrawCheckbox(x + 30, y + 80, 450, CVars::g_bESPDrawBox, charenc("Draw Boxes"));
		this->DrawCheckbox(x + 30, y + 105, 450, CVars::g_bESPDrawName, charenc("Draw Name"));
		this->DrawCheckbox(x + 30, y + 130, 450, CVars::g_bESPDrawWeapon, charenc("Draw Weapon"));
		this->DrawCheckbox(x + 30, y + 155, 450, CVars::g_bESPDrawCallout, charenc("Draw Callout"));
	}
	else if (iTab == 3)
	{
		g_Drawing.DrawFilledRect(x + 193, y + 30, 83, 15, Color(5, 120, 210));
		g_Drawing.DrawString(g_Drawing.m_MenuFont, true, x + 233, y + 32, Color(255, 255, 255), charenc("Misc"));
	}

	g_Drawing.DrawFilledRect(x + 1, y + 45, w - 2, 2, Color(5, 120, 210));
}