#include "Aimbot.h"

Aimbot aimbot;

Aimbot::Aimbot(void)
{
	bestTarget_ = -1;

	viewAngles_ = Vector(0, 0, 0);
	hitboxPosition_ = Vector(0, 0, 0);
	finalAngles_ = Vector(0, 0, 0);
}

void Aimbot::think(CBaseEntity* local, CBaseCombatWeapon* weapon)
{
	if (!(GetAsyncKeyState(0x1) & 0x8000))
		return;

	bestTarget_ = getBestTarget(local, weapon, hitboxPosition_);
	if (bestTarget_ == -1)
		return;

	CBaseEntity* entity = interfaces::entitylist->GetClientEntity(bestTarget_);
	if (!entity)
		return;

	if (tools.getDistance(hitboxPosition_, local->GetEyePosition()) > 8192.f)
		return;

	hitboxPosition_.x += tools.random(-cvar::aimbot_randomize_hitbox, cvar::aimbot_randomize_hitbox);
	hitboxPosition_.y += tools.random(-cvar::aimbot_randomize_hitbox, cvar::aimbot_randomize_hitbox);
	hitboxPosition_.z += tools.random(-cvar::aimbot_randomize_hitbox, cvar::aimbot_randomize_hitbox);

	tools.computeAngle(local->GetEyePosition(), hitboxPosition_, finalAngles_);
	tools.normalizeAngles(finalAngles_);

	finalAngles_.x -= getRandomizedRecoil(local).x;
	finalAngles_.y -= getRandomizedRecoil(local).y;
	tools.normalizeAngles(finalAngles_);

	finalAngles_ = viewAngles_ - finalAngles_;
	tools.normalizeAngles(finalAngles_);

	float sensitivity = *(float*)(interfaces::clientdll + 0xA34CB4);
	if (!sensitivity)
		return;

	float pixels = sensitivity * 0.22f / tools.random(0.7f, 1.1f);
	float smoothRate = tools.random(0.7f, 1.1f) * 2.f;

	if (finalAngles_.x > smoothRate)
		finalAngles_.x = smoothRate;
	else if (finalAngles_.x < -smoothRate)
		finalAngles_.x = -smoothRate;

	if (finalAngles_.y > smoothRate)
		finalAngles_.y = smoothRate;
	else if (finalAngles_.y < -smoothRate)
		finalAngles_.y = -smoothRate;

	// randomizeAngles(finalAngles_);
	tools.normalizeAngles(finalAngles_);

	finalAngles_.x /= pixels * -1.f;
	finalAngles_.y /= pixels;
	finalAngles_.y += tools.random(-cvar::aimbot_randomize_angle, cvar::aimbot_randomize_angle);

	tools.normalizeAngles(finalAngles_);

	setAngles(finalAngles_.y, finalAngles_.x);
}

void Aimbot::setAngles(float x, float y)
{
	INPUT input = { 0 };
	input.type = INPUT_MOUSE;
	input.mi.dx = x;
	input.mi.dy = y;
	input.mi.dwFlags = MOUSEEVENTF_MOVE;
	SendInput(1, &input, sizeof(INPUT));
}

Vector Aimbot::getRandomizedRecoil(CBaseEntity* local)
{
	QAngle punchAngle = local->GetPunchAngles() * tools.random(cvar::aimbot_rcs_min, cvar::aimbot_rcs_max);
	return (local->GetShotsFired() > 1 ? punchAngle : Vector(0, 0, 0));
}

bool Aimbot::getClosestHitbox(CBaseEntity* local, CBaseEntity* entity, Vector& dest)
{
	int bestHitbox = -1;
	float bestFoV = 180.f;

	std::vector<int> hitboxes;
	hitboxes.push_back(HITBOX_HEAD);
	hitboxes.push_back(HITBOX_NECK);
	hitboxes.push_back(HITBOX_UPPER_CHEST);
	hitboxes.push_back(HITBOX_CHEST);
	hitboxes.push_back(HITBOX_BODY);

	for (auto hitbox : hitboxes)
	{
		Vector temp;
		if (!tools.getHitboxPosition(hitbox, temp, entity))
			continue;

		float fov = tools.getFov(viewAngles_ + getRandomizedRecoil(local), tools.computeAngle(local->GetEyePosition(), temp));
		if (fov < bestFoV)
		{
			bestFoV = fov;
			bestHitbox = hitbox;
		}
	}

	if (bestHitbox != -1)
	{
		if (!tools.getHitboxPosition(bestHitbox, dest, entity))
			return true;
	}

	return false;
}

int Aimbot::getBestTarget(CBaseEntity* local, CBaseCombatWeapon* weapon, Vector& dest)
{
	int bestTarget = -1;
	float bestFov = 180.f;

	interfaces::engine->GetViewAngles(viewAngles_);

	for (int i = 1; i <= interfaces::engine->GetMaxClients(); i++)
	{
		if (i == local->GetIndex())
			continue;

		CBaseEntity* entity = interfaces::entitylist->GetClientEntity(i);
		if (!entity)
			continue;
		if (entity->IsDormant() || entity->GetLifeState() != LIFE_ALIVE)
			continue;
		if (entity->IsProtected())
			continue;
		if (entity->GetClientClass()->GetClassID() != CCSPlayer)
			continue;
		if (entity->GetTeamNum() == local->GetTeamNum())
			continue;

		Vector hitbox;
		if (getClosestHitbox(local, entity, hitbox))
			continue;

		float fov = tools.getFov(viewAngles_ + getRandomizedRecoil(local), tools.computeAngle(local->GetEyePosition(), hitbox));
		if (fov < bestFov && fov < cvar::aimbot_fov)
		{
			if (tools.isVisible(local->GetEyePosition(), hitbox, entity))
			{
				bestFov = fov;
				dest = hitbox;
				bestTarget = i;
			}
		}
	}

	return bestTarget;
}