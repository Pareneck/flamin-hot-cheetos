#include "CreateMove.h"

CreateMove_t originalCreateMove;

void __stdcall CreateMove(int sequence_number, float input_sample_frametime, bool active)
{
	originalCreateMove(g_pClient, sequence_number, input_sample_frametime, active);

	CInput::CUserCmd* pUserCmd = g_pInput->GetUserCmd(0, sequence_number);
	if (!pUserCmd)
		return;

	CInput::CVerifiedUserCmd* pVerifiedCommands = *(CInput::CVerifiedUserCmd**)((DWORD)g_pInput + VERIFIEDCMDOFFSET);
	CInput::CVerifiedUserCmd* pVerified = &pVerifiedCommands[sequence_number % MULTIPLAYER_BACKUP];
	if (!pVerified)
		return;

	CBaseEntity* pLocal = g_pEntityList->GetClientEntity(g_pEngine->GetLocalPlayer());
	if (pLocal)
	{
		if (cvar::misc_bunnyhop)
		{
			// g_Misc.Bunnyhop(pLocal, pUserCmd);

			if ((pUserCmd->buttons & IN_JUMP) && !(pLocal->GetFlags() & FL_ONGROUND))
				pUserCmd->buttons &= ~IN_JUMP;
		}
	}

	pVerified->m_cmd = *pUserCmd;
	pVerified->m_crc = pUserCmd->GetChecksum();
}