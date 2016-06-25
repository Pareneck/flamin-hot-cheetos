#include "OverrideView.h"

OverrideView_t originalOverrideView;

void __stdcall OverrideView(CViewSetup* setup)
{
	originalOverrideView(interfaces::clientMode, setup);
}