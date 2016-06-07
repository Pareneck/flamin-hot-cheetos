#include "PaintTraverse.h"

PaintTraverse_t originalPaintTraverse;

void __stdcall PaintTraverse(unsigned int vguiPanel, bool forceRepaint, bool allowForce)
{
	originalPaintTraverse(g_pPanel, vguiPanel, forceRepaint, allowForce);

	if (GetAsyncKeyState(VK_DELETE) & 1)
		shouldUnload = true;

	static bool bOnce = false;
	if (!bOnce)
	{
		drawing.initializeFonts();
		bOnce = true;
	}

	const char* panelName = g_pPanel->GetName(vguiPanel);
	if (!panelName)
		return;

	// MatSystemTopPanel
	if (panelName[0] == 'M' && panelName[3] == 'S' && panelName[9] == 'T')
	{
		if (g_pEngine->InGame() && g_pEngine->IsConnected())
		{
			CBaseEntity* pLocal = g_pEntityList->GetClientEntity(g_pEngine->GetLocalPlayer());
			if (!pLocal)
				return;

			if (cvar::esp_enabled)
				visuals.think(pLocal);
		}

		menu.think();

		drawing.drawString(drawing.menuTitleFont, false, 3, 3, Color(255, 255, 255), charenc("flamin' hot cheetos"));
	}
}