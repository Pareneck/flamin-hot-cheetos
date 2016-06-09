#ifndef LEGITBOT_H
#define LEGITBOT_H

#pragma once

#include "stdafx.h"

class Aimbot
{
public:
	Aimbot(void);

	void   think(CBaseEntity* local, CBaseCombatWeapon* weapon);

private:
	bool   getClosestHitbox(CBaseEntity* local, CBaseEntity* entity, Vector& dest);
	int    getBestTarget(CBaseEntity* local, CBaseCombatWeapon* weapon, Vector& dest);
	Vector getRandomizedRecoil(CBaseEntity* local);

	void   moveMouse(float x, float y);

private:
	int    bestTarget;

	QAngle viewAngles;
	Vector hitboxPosition;
	QAngle finalAngles;
};

extern Aimbot aimbot;

#endif