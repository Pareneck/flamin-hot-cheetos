#include "CreateMove.h"

CreateMove_t originalCreateMove;

void __stdcall CreateMove(int sequence_number, float input_sample_frametime, bool active)
{
	originalCreateMove(client, sequence_number, input_sample_frametime, active);

	ValveSDK::CInput::CUserCmd* userCmd = input->GetUserCmd(0, sequence_number);
	if (!userCmd)
		return;

	ValveSDK::CInput::CVerifiedUserCmd* verifiedCommands = *(ValveSDK::CInput::CVerifiedUserCmd**)((DWORD)input + VERIFIEDCMDOFFSET);
	ValveSDK::CInput::CVerifiedUserCmd* verified = &verifiedCommands[sequence_number % MULTIPLAYER_BACKUP];
	if (!verified)
		return;

	ValveSDK::CBaseEntity* local = entitylist->GetClientEntity(engine->GetLocalPlayer());
	if (local)
	{
		if (cvar::misc_bunnyhop)
		{
			// g_Misc.Bunnyhop(pLocal, pUserCmd);

			if ((userCmd->buttons & IN_JUMP) && !(local->GetFlags() & FL_ONGROUND))
				userCmd->buttons &= ~IN_JUMP;
		}
	}

	verified->m_cmd = *userCmd;
	verified->m_crc = userCmd->GetChecksum();
}