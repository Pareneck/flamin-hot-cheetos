#ifndef VISUALS_H
#define VISUALS_H

#pragma once

#include "stdafx.h"
#include "Common.h"

// why the hell do I have to make forward declarations

class Visuals
{
public:
	Visuals(void);

	void think(ValveSDK::CBaseEntity* local);

private:
	void drawPlayer(ValveSDK::CBaseEntity* local, ValveSDK::CBaseEntity* entity, player_info_t info);

private:
	Color espColor_;
};

extern Visuals visuals;

#endif