#include "Visuals.h"

CVisuals g_Visuals;

void CVisuals::Think(CBaseEntity* pLocal)
{
	for (int i = 1; i <= g_pEntityList->GetHighestEntityIndex(); i++)
	{
		if (i == pLocal->GetIndex())
			continue;

		CBaseEntity* pEntity = g_pEntityList->GetClientEntity(i);
		if (!pEntity)
			continue;
		if (pEntity->IsDormant() || pEntity->GetLifeState() != (int)LifeState::LIFE_ALIVE)
			continue;
		if (pEntity->GetClientClass()->GetClassID() != (int)ClassID::CCSPlayer)
			continue;
		if (pEntity->GetTeamNum() == pLocal->GetTeamNum())
			continue;

		this->DrawPlayer(pLocal, pEntity);
	}
}

void CVisuals::DrawPlayer(CBaseEntity* pLocal, CBaseEntity* pEntity)
{
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
			m_clrESP = Color(0, 255, 255);
	}

	if (pEntity->GetFlags() & (int)Flags::FL_DUCKING)
		m_vOrigin = pEntity->GetAbsOrigin() + Vector(0.f, 0.f, 52.f);
	else
		m_vOrigin = pEntity->GetAbsOrigin() + Vector(0.f, 0.f, 72.f);

	if (!g_pDebugOverlay->ScreenPosition(m_vOrigin, m_vScreenPosHead) != 1 || !g_pDebugOverlay->ScreenPosition(pEntity->GetAbsOrigin(), m_vScreenPosFeet) != 1)
		return;

	m_flHeight = m_vScreenPosFeet.y - m_vScreenPosHead.y;
	m_flWidth = m_flHeight / 4.f;

	if (CVars::g_bESPDrawBox)
		g_Drawing.DrawESPBox(m_vScreenPosHead.x - m_flWidth, m_vScreenPosHead.y + 1, m_flWidth * 2, m_flHeight, m_clrESP, Color(0, 0, 0));
}