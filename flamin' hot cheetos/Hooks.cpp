#include "Hooks.h"

namespace hooks
{
	std::unique_ptr<VFTManager> clientHook = nullptr;
	std::unique_ptr<VFTManager> panelHook = nullptr;

	void initialize()
	{
		panelHook = std::make_unique<VFTManager>((DWORD**)g_pPanel, true);
		originalPaintTraverse = panelHook->hook(41, (PaintTraverse_t)PaintTraverse);

		clientHook = std::make_unique<VFTManager>((DWORD**)g_pClient, true);
		originalCreateMove = clientHook->hook(21, (CreateMove_t)CreateMove);

		g_pEngine->ExecuteClientCmd(charenc("echo [successfully hooked functions]"));
	}

	void restore()
	{
		panelHook->restoreTable();
		clientHook->restoreTable();
		Sleep(100);

		g_pEngine->ExecuteClientCmd(charenc("cl_mouseenable 1"));
		g_pEngine->ExecuteClientCmd(charenc("echo [successfully unhooked functions]"));
	}
}