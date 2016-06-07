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

private:
	Color espColor_;
};

extern Visuals visuals;

#endif