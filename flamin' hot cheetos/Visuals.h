#ifndef VISUALS_H
#define VISUALS_H

#pragma once

#include "Main.h"

// why the hell do I have to make forward declarations
class CBaseEntity;

class Visuals
{
public:
	Visuals(void);

	void think(CBaseEntity* pLocal);

private:
	void drawPlayer(CBaseEntity* pLocal, CBaseEntity* pEntity, player_info_t playerInfo);

private:
	Color espColor_;
};

extern Visuals visuals;

#endif