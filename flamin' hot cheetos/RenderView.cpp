#include "RenderView.h"

RenderView_t originalRenderView;

void __stdcall RenderView(CViewSetup& view, int nClearFlags, int whatToDraw)
{
	CBaseEntity* local = interfaces::entitylist->GetClientEntity(interfaces::engine->GetLocalPlayer());
	if (local)
	{
		if (cvar::misc_overridefov)
			view.fovViewmodel += cvar::misc_overridefov;
	}

	originalRenderView(interfaces::viewRender, view, nClearFlags, whatToDraw);
}