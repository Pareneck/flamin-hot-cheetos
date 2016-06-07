#include "Miscellaneous.h"

Misc misc;

void Misc::Bunnyhop(CBaseEntity* local, CInput::CUserCmd* cmd)
{
	if ((cmd->buttons & IN_JUMP) && !(local->GetFlags() & FL_ONGROUND))
		cmd->buttons &= ~IN_JUMP;
}