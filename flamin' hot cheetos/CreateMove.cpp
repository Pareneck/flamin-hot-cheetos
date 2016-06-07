#include "CreateMove.h"

CreateMove_t originalCreateMove;

void __stdcall CreateMove(int sequence_number, float input_sample_frametime, bool active)
{
	originalCreateMove(interfaces::client, sequence_number, input_sample_frametime, active);

	CUserCmd* cmd = interfaces::input->GetUserCmd(0, sequence_number);
	if (!cmd)
		return;

	CVerifiedUserCmd* verifiedCmd = *(CVerifiedUserCmd**)((DWORD)interfaces::input + VERIFIEDCMDOFFSET);
	CVerifiedUserCmd* verified = &verifiedCmd[sequence_number % MULTIPLAYER_BACKUP];
	if (!verified)
		return;

	CBaseEntity* local = interfaces::entitylist->GetClientEntity(interfaces::engine->GetLocalPlayer());
	if (local)
	{
		if (cvar::misc_bunnyhop)
			misc.bunnyhop(local, cmd);
	}

	verified->m_cmd = *cmd;
	verified->m_crc = cmd->GetChecksum();
}