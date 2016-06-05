#include "Hooks.h"

namespace Hooks
{
	std::unique_ptr<CVFTManager> g_pClientHook = nullptr;
	std::unique_ptr<CVFTManager> g_pPanelHook = nullptr;

	void Initialize()
	{
		g_pPanelHook = std::make_unique<CVFTManager>((DWORD**)g_pPanel, true);
		g_fnPaintTraverse = g_pPanelHook->Hook(41, (PaintTraverse_t)PaintTraverse);

		g_pClientHook = std::make_unique<CVFTManager>((DWORD**)g_pClient, true);
		g_fnCreateMove = g_pClientHook->Hook(21, (CreateMove_t)CreateMove);

		g_pEngine->ExecuteClientCmd(charenc("echo [successfully hooked functions]"));
	}

	void UnhookFunctions()
	{
		g_pPanelHook->RestoreTable();
		g_pClientHook->RestoreTable();
		Sleep(100);

		g_pEngine->ExecuteClientCmd(charenc("cl_mouseenable 1"));
		g_pEngine->ExecuteClientCmd(charenc("echo [successfully unhooked functions]"));
	}
}