#ifndef VISUALS_H
#define VISUALS_H

#pragma once

#include "stdafx.h"

class Visuals
{
	struct plist_t
	{
		char* name;
		char* steamid;
		int   money;
		int   health;
		int   mmwins;
		char* mmrank;
	}players[64];

public:
	Visuals();

	void think(CBaseEntity* local);

private:
	void drawPlayer(CBaseEntity* local, CBaseEntity* entity, player_info_t info);
	void drawWorld(CBaseEntity* entity);
	void drawBoundingBox(CBaseEntity* entity, Color color, const char* text);
	void drawGlow(CBaseEntity* entity);
	void drawScoreboard(CBaseEntity* local);

private:
	Color espColor;
	Color glowColor;
};

typedef CGlowObjectManager*(__thiscall* GlowObjectPointer_t)();

extern Visuals visuals;

#endif