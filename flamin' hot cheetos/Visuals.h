#ifndef VISUALS_H
#define VISUALS_H

#pragma once

#include "Main.h"

// wtf?
class CBaseEntity;

class CVisuals
{
public:
	void Think(CBaseEntity* pLocal);
	void DrawPlayer(CBaseEntity* pLocal, CBaseEntity* pEntity);

private:
	Vector	m_vOrigin;
	Vector	m_vScreenPosHead, m_vScreenPosFeet;

	float	m_flWidth, m_flHeight;

	Color	m_clrESP;
};

extern CVisuals g_Visuals;

#endif