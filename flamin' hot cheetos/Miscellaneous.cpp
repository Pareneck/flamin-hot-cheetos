#include "Miscellaneous.h"

Misc misc;

void Misc::Bunnyhop(ValveSDK::CBaseEntity* local, ValveSDK::CInput::CUserCmd* userCmd)
{
	if ((userCmd->buttons & IN_JUMP) && !(local->GetFlags() & FL_ONGROUND))
		userCmd->buttons &= ~IN_JUMP;
}