#include "PaintTraverse.h"

PaintTraverse_t originalPaintTraverse;

void __stdcall PaintTraverse(unsigned int vguiPanel, bool forceRepaint, bool allowForce)
{
	originalPaintTraverse(panel, vguiPanel, forceRepaint, allowForce);

	if (GetAsyncKeyState(VK_DELETE) & 1)
		shouldUnload = true;

	static bool isDone = false;
	if (!isDone)
	{
		drawing.initializeFonts();
		isDone = true;
	}

	const char* panelName = panel->GetName(vguiPanel);
	if (!panelName)
		return;

	// MatSystemTopPanel
	if (panelName[0] == 'M' && panelName[3] == 'S' && panelName[9] == 'T')
	{
		if (engine->InGame() && engine->IsConnected())
		{
			ValveSDK::CBaseEntity* local = entitylist->GetClientEntity(engine->GetLocalPlayer());
			if (!local)
				return;

			if (cvar::esp_enabled)
				visuals.think(local);
		}

		menu.think();

		drawing.drawString(drawing.menuTitleFont, false, 3, 3, Color(255, 255, 255), charenc("flamin' hot cheetos"));
	}
}