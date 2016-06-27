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
	void getScreenSize();

private:
	void drawPlayer(CBaseEntity* local, CBaseEntity* entity);
	void drawWorld(CBaseEntity* entity);
	void drawBoundingBox(CBaseEntity* entity, Color color, const char* text);
	void drawGlow(CBaseEntity* entity);
	void drawScoreboard(CBaseEntity* local);

public:
	int width;
	int height;

private:
	Color espColor;
	Color glowColor;

private:
	player_info_t info;
};

typedef CGlowObjectManager*(__thiscall* GlowObjectPointer_t)();

extern Visuals visuals;

#endif