#include "Miscellaneous.h"

Misc misc;

void Misc::Bunnyhop(ValveSDK::CBaseEntity* local, ValveSDK::CInput::CUserCmd* cmd)
{
	if ((cmd->buttons & IN_JUMP) && !(local->GetFlags() & FL_ONGROUND))
		cmd->buttons &= ~IN_JUMP;
}