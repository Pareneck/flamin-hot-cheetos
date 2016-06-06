#include "Visuals.h"

CVisuals g_Visuals;

void CVisuals::Think(CBaseEntity* pLocal)
{
	player_info_t pInfo;

	for (int i = 1; i <= g_pEntityList->GetHighestEntityIndex(); i++)
	{
		if (i == pLocal->GetIndex())
			continue;

		CBaseEntity* pEntity = g_pEntityList->GetClientEntity(i);
		if (!pEntity)
			continue;
		if (pEntity->IsDormant() || pEntity->GetLifeState() != LIFE_ALIVE)
			continue;
		if (pEntity->GetClientClass()->GetClassID() != CCSPlayer)
			continue;
		if (pEntity->GetTeamNum() == pLocal->GetTeamNum())
			continue;
		if (!g_pEngine->GetPlayerInfo(i, &pInfo))
			continue;

		this->DrawPlayer(pLocal, pEntity, pInfo);
	}
}

void CVisuals::DrawPlayer(CBaseEntity* pLocal, CBaseEntity* pEntity, player_info_t pInfo)
{
	const matrix3x4& trans = *(matrix3x4*)( (DWORD)pEntity + Offsets::m_rgflCoordinateFrame );

	Vector min, max;
	pEntity->GetRenderBounds( min, max );

	Vector pointList[] = {
		Vector( min.x, min.y, min.z ),
		Vector( min.x, max.y, min.z ),
		Vector( max.x, max.y, min.z ),
		Vector( max.x, min.y, min.z ),
		Vector( max.x, max.y, max.z ),
		Vector( min.x, max.y, max.z ),
		Vector( min.x, min.y, max.z ),
		Vector( max.x, min.y, max.z )
	};

	Vector transformed[ 8 ];

	for ( int i = 0; i < 8; i++ )
		U::VectorTransform( pointList[ i ], trans, transformed[ i ] );

	Vector flb, brt, blb, frt, frb, brb, blt, flt;

	if ( !WorldToScreen( transformed[ 3 ], flb ) ||
		!WorldToScreen( transformed[ 0 ], blb ) ||
		!WorldToScreen( transformed[ 2 ], frb ) ||
		!WorldToScreen( transformed[ 6 ], blt ) ||
		!WorldToScreen( transformed[ 5 ], brt ) ||
		!WorldToScreen( transformed[ 4 ], frt ) ||
		!WorldToScreen( transformed[ 1 ], brb ) ||
		!WorldToScreen( transformed[ 7 ], flt ) )
		return;

	Vector arr[] = { flb, brt, blb, frt, frb, brb, blt, flt };

	float left = flb.x;
	float top = flb.y;
	float right = flb.x;
	float bottom = flb.y;

	for ( int i = 0; i < 8; i++ )
	{
		if ( left > arr[ i ].x )
			left = arr[ i ].x;
		if ( top < arr[ i ].y )
			top = arr[ i ].y;
		if ( right < arr[ i ].x )
			right = arr[ i ].x;
		if ( bottom > arr[ i ].y )
			bottom = arr[ i ].y;
	}

	float x = left;
	float y = bottom;
	float w = right - left;
	float h = top - bottom;

	if (pEntity->GetFlags() & FL_DUCKING)
		m_vOrigin = pEntity->GetAbsOrigin() + Vector(0.f, 0.f, 52.f);
	else
		m_vOrigin = pEntity->GetAbsOrigin() + Vector(0.f, 0.f, 72.f);

	if (!g_pDebugOverlay->ScreenPosition(m_vOrigin, m_vScreenPosHead) != 1 || !g_pDebugOverlay->ScreenPosition(pEntity->GetAbsOrigin(), m_vScreenPosFeet) != 1)
		return;

	m_fHeight = m_vScreenPosFeet.y - m_vScreenPosHead.y;
	m_fWidth = m_fHeight / 4.f;

	bool bVisible = g_Tools.IsVisible(pLocal->GetEyePosition(), pEntity->GetEyePosition(), pEntity);
	if (bVisible)
	{
		if (pEntity->GetTeamNum() == 2)
			m_clrESP = Color(255, 0, 0);
		else if (pEntity->GetTeamNum() == 3)
			m_clrESP = Color(0, 0, 255);
	}
	else
	{
		if (pEntity->GetTeamNum() == 2)
			m_clrESP = Color(255, 255, 0);
		else if (pEntity->GetTeamNum() == 3)
			m_clrESP = Color(0, 255, 0);
	}

	if (CVars::g_bESPDrawBox)
		g_Drawing.DrawESPBox(m_vScreenPosHead.x - m_fWidth, m_vScreenPosHead.y + 1, m_fWidth * 2, m_fHeight, m_clrESP, Color(0, 0, 0));

	if (CVars::g_bESPDrawName)
		g_Drawing.DrawString(g_Drawing.m_ESPFont, true, m_vScreenPosHead.x, m_vScreenPosHead.y - 14, Color(255, 255, 255), pInfo.m_szPlayerName);

	if (CVars::g_bESPDrawWeapon)
	{
		CBaseCombatWeapon* pWeapon = g_Tools.GetActiveWeapon(pEntity);
		if (pWeapon)
		{
			char chBuffer[32];

			if (!pWeapon->IsKnife() && !pWeapon->IsOther())
				sprintf_s(chBuffer, sizeof chBuffer, "%s | %i", pWeapon->GetWeaponName(), pWeapon->GetClip1());
			else
				sprintf_s(chBuffer, sizeof chBuffer, "%s", pWeapon->GetWeaponName());

			g_Drawing.DrawString(g_Drawing.m_ESPFont, true, m_vScreenPosHead.x, m_vScreenPosFeet.y + 3, Color(255, 255, 255), chBuffer);
		}
	}

	int iPlace = 0;

	if (CVars::g_bESPDrawCallout)
		g_Drawing.DrawString(g_Drawing.m_ESPFont, false, m_vScreenPosHead.x + m_fWidth + 5, m_vScreenPosHead.y - 3 + (iPlace++ * 11), Color(255, 255, 255), pEntity->GetLastPlaceName());
}