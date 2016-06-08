#ifndef TRIGGERBOT_H
#define TRIGGERBOT_H

#pragma once

#include "stdafx.h"

class Triggerbot
{
public:
	Triggerbot(void);

	void think(CBaseEntity* local, CBaseCombatWeapon* weapon, CUserCmd* cmd);

private:
	QAngle viewAngles_;
};

extern Triggerbot triggerbot;

#endif