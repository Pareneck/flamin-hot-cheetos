#include "Hooks.h"

namespace hooks
{
	std::unique_ptr<VFTManager> clientHook = nullptr;
	std::unique_ptr<VFTManager> panelHook = nullptr;
	std::unique_ptr<VFTManager> clientModeHook = nullptr;
	std::unique_ptr<VFTManager> surfaceHook = nullptr;
	std::unique_ptr<VFTManager> renderViewHook = nullptr;

	void initialize()
	{
		panelHook = std::make_unique<VFTManager>((DWORD**)interfaces::panel, true);
		originalPaintTraverse = panelHook->hook(41, (PaintTraverse_t)PaintTraverse);

		clientHook = std::make_unique<VFTManager>((DWORD**)interfaces::client, true);
		originalCreateMove = clientHook->hook(21, (CreateMove_t)CreateMove);

		originalFrameStageNotify = clientHook->hook(36, (FrameStageNotify_t)FrameStageNotify);
		originalKeyEvent = clientHook->hook(20, (IN_KeyEvent_t)IN_KeyEvent);

		renderViewHook = std::make_unique<VFTManager>((DWORD**)interfaces::viewRender, true);
		originalRenderView = renderViewHook->hook(6, (RenderView_t)RenderView);

		// clientModeHook = std::make_unique<VFTManager>((DWORD**)interfaces::clientMode, true);
		// originalOverrideView = clientModeHook->hook(18, (OverrideView_t)OverrideView);

		surfaceHook = std::make_unique<VFTManager>((DWORD**)interfaces::surface, true);
		originalOnScreenSizeChanged = surfaceHook->hook(116, (OnScreenSizeChanged_t)OnScreenSizeChanged);

		interfaces::engine->ClientCmd_Unrestricted(charenc("echo [successfully hooked functions]"));
	}

	void restore()
	{
		panelHook->restoreTable();
		clientHook->restoreTable();
		// clientModeHook->restoreTable();
		surfaceHook->restoreTable();
		Sleep(300);

		interfaces::engine->ClientCmd_Unrestricted(charenc("cl_mouseenable 1"));
		interfaces::engine->ClientCmd_Unrestricted(charenc("echo [successfully unhooked functions]"));
	}
}