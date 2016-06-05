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
		g_Drawing.DrawString(g_Drawing.m_ESPFont, true, m_vScreenPosHead.x, m_vScreenPosHead.y - 15, Color(255, 255, 255), pInfo.m_szPlayerName);

	if (CVars::g_bESPDrawWeapon)
	{
		CBaseCombatWeapon* pWeapon = g_Tools.GetActiveWeapon(pEntity);
		if (pWeapon)
			g_Drawing.DrawString(g_Drawing.m_ESPFont, true, m_vScreenPosHead.x, m_vScreenPosFeet.y, Color(255, 255, 255), pWeapon->GetWeaponName());
	}

	int iPlace = 0;

	if (CVars::g_bESPDrawCallout)
		g_Drawing.DrawString(g_Drawing.m_ESPFont, true, m_vScreenPosHead.x + m_fWidth + 4, m_vScreenPosHead.y - 2 + (iPlace++ * 11), Color(255, 255, 255), pEntity->GetLastPlaceName());
}