#ifndef VISUALS_H
#define VISUALS_H

#pragma once

#include "stdafx.h"

// why the hell do I have to make forward declarations
class CBaseEntity;

class Visuals
{
public:
	Visuals(void);

	void think(CBaseEntity* local);

private:
	void drawPlayer(CBaseEntity* local, CBaseEntity* entity, player_info_t info);
	void drawWorld(CBaseEntity* entity);

	void drawBoundingBox(CBaseEntity* entity, Color color, const char* text);

private:
	Color espColor;
};

extern Visuals visuals;

#endif