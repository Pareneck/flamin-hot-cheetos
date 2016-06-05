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

private:
	void DrawPlayer(CBaseEntity* pLocal, CBaseEntity* pEntity);

private:
	Vector	m_vOrigin;
	Vector	m_vScreenPosHead, m_vScreenPosFeet;
	float	m_fWidth, m_fHeight;

	Color	m_clrESP;
};

extern CVisuals g_Visuals;

#endif