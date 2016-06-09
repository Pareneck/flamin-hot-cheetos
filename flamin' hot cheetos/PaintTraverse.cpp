#include "PaintTraverse.h"

PaintTraverse_t originalPaintTraverse;

void __stdcall PaintTraverse(unsigned int vguiPanel, bool forceRepaint, bool allowForce)
{
	originalPaintTraverse(interfaces::panel, vguiPanel, forceRepaint, allowForce);

	if (GetAsyncKeyState(VK_DELETE) & 1)
		shouldUnload = true;

	if (GetAsyncKeyState(VK_HOME) & 1)
		config.load();
	else if (GetAsyncKeyState(VK_END) & 1)
		config.save();

	static bool doOnce = false;
	if (!doOnce)
	{
		drawing.initializeFonts();
		doOnce = true;
	}

	const char* panelName = interfaces::panel->GetName(vguiPanel);
	if (!panelName)
		return;

	// MatSystemTopPanel
	if (panelName[0] == 'M' && panelName[3] == 'S' && panelName[9] == 'T')
	{
		if (interfaces::engine->InGame() && interfaces::engine->IsConnected())
		{
			CBaseEntity* local = interfaces::entitylist->GetClientEntity(interfaces::engine->GetLocalPlayer());
			if (!local)
				return;

			if (cvar::esp_enabled)
				visuals.think(local);
		}

		menu.think();

		drawing.drawString(drawing.menuTitleFont, false, 3, 3, Color(255, 255, 255), charenc("flamin' hot cheetos"));
	}
}