#ifndef VISUALS_H
#define VISUALS_H

#pragma once

#include "stdafx.h"

class Visuals
{
public:
	Visuals(void);

	void think(CBaseEntity* local);

private:
	void drawPlayer(CBaseEntity* local, CBaseEntity* entity, player_info_t info);
	void drawWorld(CBaseEntity* entity);

	void drawBoundingBox(CBaseEntity* entity, Color color, const char* text);
	void drawGlow(CBaseEntity* entity);

private:
	Color espColor;
	Color glowColor;
};

typedef CGlowObjectManager*(__thiscall* GlowObjectPointer_t)(void);

extern Visuals visuals;

#endif