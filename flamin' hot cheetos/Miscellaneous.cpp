#include "Miscellaneous.h"

Misc misc;

void Misc::bunnyhop(CBaseEntity* local, CUserCmd* cmd)
{
	if ((cmd->buttons & IN_JUMP) && !(local->GetFlags() & FL_ONGROUND))
		cmd->buttons &= ~IN_JUMP;
}