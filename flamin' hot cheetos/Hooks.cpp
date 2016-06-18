#include "Hooks.h"

namespace hooks
{
	std::unique_ptr<VFTManager> clienthook = nullptr;
	std::unique_ptr<VFTManager> panelhook = nullptr;
	std::unique_ptr<VFTManager> clientmodehook = nullptr;
	std::unique_ptr<VFTManager> surfacehook = nullptr;
	std::unique_ptr<VFTManager> modelcachehook = nullptr;
	std::unique_ptr<VFTManager> renderviewhook = nullptr;

	void initialize()
	{
		panelhook = std::make_unique<VFTManager>((DWORD**)interfaces::panel, true);
		originalPaintTraverse = panelhook->hook(41, (PaintTraverse_t)PaintTraverse);

		clienthook = std::make_unique<VFTManager>((DWORD**)interfaces::client, true);
		originalCreateMove = clienthook->hook(21, (CreateMove_t)CreateMove);
		originalFrameStageNotify = clienthook->hook(36, (FrameStageNotify_t)FrameStageNotify);
		originalKeyEvent = clienthook->hook(20, (IN_KeyEvent_t)IN_KeyEvent);

		modelcachehook = std::make_unique<VFTManager>((DWORD**)interfaces::modelcache, true);
		originalFindMDL = modelcachehook->hook(10, (FindMDL_t)FindMDL);

		renderviewhook = std::make_unique<VFTManager>((DWORD**)interfaces::viewRender, true);
		originalRenderView = renderviewhook->hook(6, (RenderView_t)RenderView);

		// clientModeHook = std::make_unique<VFTManager>((DWORD**)interfaces::clientMode, true);
		// originalOverrideView = clientModeHook->hook(18, (OverrideView_t)OverrideView);

		surfacehook = std::make_unique<VFTManager>((DWORD**)interfaces::surface, true);
		originalOnScreenSizeChanged = surfacehook->hook(116, (OnScreenSizeChanged_t)OnScreenSizeChanged);

		interfaces::engine->ClientCmd_Unrestricted(charenc("echo [successfully hooked functions]"));
	}

	void restore()
	{
		panelhook->restoreTable();
		clienthook->restoreTable();
		modelcachehook->restoreTable();
		// clientModeHook->restoreTable();
		surfacehook->restoreTable();
		Sleep(300);

		interfaces::engine->ClientCmd_Unrestricted(charenc("cl_mouseenable 1"));
		interfaces::engine->ClientCmd_Unrestricted(charenc("echo [successfully unhooked functions]"));
	}
}