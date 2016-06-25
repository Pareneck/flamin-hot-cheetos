#include "Triggerbot.h"

Triggerbot triggerbot;

Triggerbot::Triggerbot()
{
	viewAngles = QAngle(0.f, 0.f, 0.f);
}

void Triggerbot::think(CBaseEntity* local, CBaseCombatWeapon* weapon, CInput::CUserCmd* cmd)
{
	if (!cvar::misc_triggerbot)
		return;

	if (weapon->IsOther() || weapon->IsKnife())
		return;

	if (!(GetAsyncKeyState(cvar::general_key_triggerbot) & 0x8000))
		return;

	interfaces::engine->GetViewAngles(viewAngles);
	viewAngles += local->GetPunchAngles() * 2.f;

	Vector traceStart, traceEnd;
	tools.angleVectors(viewAngles, traceEnd);

	traceStart = local->GetEyePosition();
	traceEnd = traceStart + (traceEnd * 8192.f);

	IEngineTrace::trace_t trace;
	IEngineTrace::Ray_t ray;
	IEngineTrace::CTraceFilter filter;
	filter.skip = local;

	ray.Init(traceStart, traceEnd);
	interfaces::enginetrace->TraceRay(ray, 0x46004003, &filter, &trace);

	if (!trace.entity
		|| trace.entity == local
		|| trace.entity->GetLifeState() != LIFE_ALIVE
		|| trace.entity->IsProtected()
		|| trace.entity->GetTeamNum() == local->GetTeamNum())
		return;

	if (!(trace.hitgroup < 10 && trace.hitgroup > 0))
		return;

	weapon->GetItemDefinitionIndex() == WEAPON_REVOLVER ? cmd->buttons |= IN_ATTACK2 : cmd->buttons |= IN_ATTACK;

	if (weapon->IsPistol() && tools.isNotAbleToShoot(local, weapon))
		weapon->GetItemDefinitionIndex() == WEAPON_REVOLVER ? cmd->buttons &= ~IN_ATTACK2 : cmd->buttons &= ~IN_ATTACK;
}