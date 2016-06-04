#include "PaintTraverse.h"

tPaintTraverse g_fnPaintTraverse = nullptr;

void __stdcall PaintTraverse(unsigned int vguiPanel, bool forceRepaint, bool allowForce)
{
	g_fnPaintTraverse(g_pPanel, vguiPanel, forceRepaint, allowForce);

	if (GetAsyncKeyState(VK_DELETE) & 1)
		bUnload = true;

	static bool bOnce = false;
	if (!bOnce)
	{
		g_Drawing.InitializeFonts();
		bOnce = true;
	}

	const char* pchPanel = g_pPanel->GetName(vguiPanel);
	if (!pchPanel)
		return;

	// MatSystemTopPanel
	if (pchPanel[0] == 'M' && pchPanel[3] == 'S' && pchPanel[9] == 'T')
	{
		if (g_pEngine->InGame() && g_pEngine->IsConnected())
		{
			CBaseEntity* pLocal = g_pEntityList->GetClientEntity(g_pEngine->GetLocalPlayer());
			if (!pLocal)
				return;

			g_Visuals.Think(pLocal);
		}

		g_Drawing.DrawString(g_Drawing.m_ESPFont, false, 3, 3, Color(255, 255, 255), "flamin' hot cheetos");
	}
}