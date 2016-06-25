#include "Miscellaneous.h"

Misc misc;

void Misc::doBunnyhop(CBaseEntity* local, CInput::CUserCmd* cmd)
{
	if (!cvar::misc_bunnyhop)
		return;

	if ((cmd->buttons & IN_JUMP) && !(local->GetFlags() & FL_ONGROUND))
		cmd->buttons &= ~IN_JUMP;
}

void Misc::doRecoilControl(CBaseEntity* local, CBaseCombatWeapon* weapon, CInput::CUserCmd* cmd)
{
	if (!cvar::misc_recoilcontrol || cvar::misc_recoilcontrol_scale <= 0.f)
		return;

	if (weapon->IsOther() || weapon->IsKnife())
		return;

	static QAngle oldPunchAngles = QAngle(0.f, 0.f, 0.f);

	QAngle punchAngles = local->GetPunchAngles();
	if (punchAngles.x == 0.f || punchAngles.y == 0.f)
		return;

	if (punchAngles.Length2D() < 0.f || punchAngles.Length2D() > 6.f)
	{
		oldPunchAngles.Zero();
		return;
	}

	int shotsFired = local->GetShotsFired(), oldShotsFired = 0;

	if (cmd->buttons & IN_ATTACK && shotsFired > 1 && shotsFired > oldShotsFired)
	{
		QAngle compensatedAngles = QAngle(punchAngles.x - oldPunchAngles.x, punchAngles.y - oldPunchAngles.y, 0);
		compensatedAngles *= cvar::misc_recoilcontrol_scale;
		tools.normalizeAngles(compensatedAngles);

		QAngle viewAngles = cmd->viewangles;
		tools.normalizeAngles(viewAngles);

		QAngle deltaAngles = viewAngles - compensatedAngles;
		tools.normalizeAngles(deltaAngles);
		tools.clampAngles(deltaAngles);

		if (oldPunchAngles.Length2D() > 0.f && oldPunchAngles.Length2D() < 6.f)
			interfaces::engine->SetViewAngles(deltaAngles);

		oldShotsFired = shotsFired;
	}

	oldPunchAngles = punchAngles;
}