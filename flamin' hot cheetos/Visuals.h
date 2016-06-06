#ifndef VISUALS_H
#define VISUALS_H

#pragma once

#include "Main.h"

// why the hell do I have to make forward declarations
class CBaseEntity;

class CVisuals
{
public:
	CVisuals(void);

	void Think(CBaseEntity* pLocal);

private:
	void DrawPlayer(CBaseEntity* pLocal, CBaseEntity* pEntity, player_info_t pInfo);

private:
	Color m_clrESP;
};

extern CVisuals g_Visuals;

#endif