#include "Hooks.h"

namespace Hooks
{
	std::unique_ptr<CVFTManager> g_pPanelHook = nullptr;

	void Initialize()
	{
		g_pPanelHook = std::make_unique<CVFTManager>((PPDWORD)g_pPanel, true);
		g_fnPaintTraverse = g_pPanelHook->Hook(41, (tPaintTraverse)PaintTraverse);

		g_pEngine->ExecuteClientCmd(charenc("echo [fhc] successfully hooked functions"));
	}

	void UnhookFunctions()
	{
		g_pPanelHook->RestoreTable();
		Sleep(100);

		g_pEngine->ExecuteClientCmd(charenc("cl_mouseenable 1"));
		g_pEngine->ExecuteClientCmd(charenc("echo [fhc] successfully unhooked functions"));
	}
}