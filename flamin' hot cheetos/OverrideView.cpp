#include "OverrideView.h"

OverrideView_t originalOverrideView;

void __stdcall OverrideView(CViewSetup* setup)
{
	/*CBaseEntity* local = interfaces::entitylist->GetClientEntity(interfaces::engine->GetLocalPlayer());
	if (local)
	{
		if (cvar::misc_overridefov)
		{
			if (!local->IsScoped())
				setup->fov += cvar::misc_overridefov_value;
		}
	}*/

	originalOverrideView(interfaces::clientMode, setup);
}