#include "Hooks.h"

namespace hooks
{
	std::unique_ptr<VFTManager> clientHook = nullptr;
	std::unique_ptr<VFTManager> panelHook = nullptr;
	std::unique_ptr<VFTManager> surfaceHook = nullptr;

	void initialize()
	{
		panelHook = std::make_unique<VFTManager>((DWORD**)interfaces::panel, true);
		originalPaintTraverse = panelHook->hook(41, (PaintTraverse_t)PaintTraverse);

		clientHook = std::make_unique<VFTManager>((DWORD**)interfaces::client, true);
		originalCreateMove = clientHook->hook(21, (CreateMove_t)CreateMove);

		surfaceHook = std::make_unique<VFTManager>((DWORD**)interfaces::surface, true);
		originalOnScreenSizeChanged = surfaceHook->hook(116, (OnScreenSizeChanged_t)OnScreenSizeChanged);

		interfaces::engine->ExecuteClientCmd(charenc("echo [successfully hooked functions]"));
	}

	void restore()
	{
		panelHook->restoreTable();
		clientHook->restoreTable();
		Sleep(100);

		interfaces::engine->ExecuteClientCmd(charenc("cl_mouseenable 1"));
		interfaces::engine->ExecuteClientCmd(charenc("echo [successfully unhooked functions]"));
	}
}