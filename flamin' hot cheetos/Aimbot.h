#ifndef LEGITBOT_H
#define LEGITBOT_H

#pragma once

#include "stdafx.h"

class CBaseCombatWeapon;

class Aimbot
{
public:
	Aimbot(void);

	void   think(CBaseEntity* local, CBaseCombatWeapon* weapon);

private:
	bool   getClosestHitbox(CBaseEntity* local, CBaseEntity* entity, Vector& dest);
	int    getBestTarget(CBaseEntity* local, CBaseCombatWeapon* weapon, Vector& dest);
	Vector getRandomizedRecoil(CBaseEntity* local);

	void   setAngles(float x, float y);

private:
	int    bestTarget_;

	QAngle viewAngles_;
	Vector hitboxPosition_;
	QAngle finalAngles_;
};

extern Aimbot aimbot;

#endif