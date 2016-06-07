#include "Visuals.h"

Visuals visuals;

Visuals::Visuals(void)
{
	espColor_ = Color(0, 0, 0, 0);
}

void Visuals::think(CBaseEntity* pLocal)
{
	player_info_t playerInfo;

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
		if (!g_pEngine->GetPlayerInfo(i, &playerInfo))
			continue;

		drawPlayer(pLocal, pEntity, playerInfo);
	}
}

void Visuals::drawPlayer(CBaseEntity* pLocal, CBaseEntity* pEntity, player_info_t playerInfo)
{
	const matrix3x4& trans = *(matrix3x4*)((DWORD)pEntity + (0x470 - 0x30));

	Vector min, max;
	pEntity->GetRenderBounds(min, max);

	Vector pointList[] = {
		Vector(min.x, min.y, min.z),
		Vector(min.x, max.y, min.z),
		Vector(max.x, max.y, min.z),
		Vector(max.x, min.y, min.z),
		Vector(max.x, max.y, max.z),
		Vector(min.x, max.y, max.z),
		Vector(min.x, min.y, max.z),
		Vector(max.x, min.y, max.z)
	};

	Vector transformed[8];

	for (int i = 0; i < 8; i++)
		tools.VectorTransform(pointList[i], trans, transformed[i]);

	Vector flb, brt, blb, frt, frb, brb, blt, flt;

	if (!tools.WorldToScreen(transformed[3], flb) ||
		!tools.WorldToScreen(transformed[0], blb) ||
		!tools.WorldToScreen(transformed[2], frb) ||
		!tools.WorldToScreen(transformed[6], blt) ||
		!tools.WorldToScreen(transformed[5], brt) ||
		!tools.WorldToScreen(transformed[4], frt) ||
		!tools.WorldToScreen(transformed[1], brb) ||
		!tools.WorldToScreen(transformed[7], flt))
		return;

	Vector arr[] = { flb, brt, blb, frt, frb, brb, blt, flt };

	float left = flb.x;
	float top = flb.y;
	float right = flb.x;
	float bottom = flb.y;

	for (int i = 0; i < 8; i++)
	{
		if (left > arr[i].x)
			left = arr[i].x;
		if (top < arr[i].y)
			top = arr[i].y;
		if (right < arr[i].x)
			right = arr[i].x;
		if (bottom > arr[i].y)
			bottom = arr[i].y;
	}

	float x = left;
	float y = bottom;
	float w = right - left;
	float h = top - bottom;

	bool isVisible = tools.isVisible(pLocal->GetEyePosition(), pEntity->GetEyePosition(), pEntity);
	if (isVisible)
	{
		if (pEntity->GetTeamNum() == 2)
			espColor_ = Color(255, 0, 0);
		else if (pEntity->GetTeamNum() == 3)
			espColor_ = Color(0, 0, 255);
	}
	else
	{
		if (pEntity->GetTeamNum() == 2)
			espColor_ = Color(255, 255, 0);
		else if (pEntity->GetTeamNum() == 3)
			espColor_ = Color(0, 255, 0);
	}

	if (cvar::esp_draw_box)
		drawing.drawOutlinedBox(x, y, w, h, espColor_, Color(0, 0, 0));

	if (cvar::esp_draw_name)
		drawing.drawString(drawing.espFont, true, x + w / 2, y - 16, Color(255, 255, 255), playerInfo.m_szPlayerName);

	if (cvar::esp_draw_weapon)
	{
		CBaseCombatWeapon* pWeapon = tools.getActiveWeapon(pEntity);
		if (pWeapon)
		{
			char buffer[32];

			if (!pWeapon->IsKnife() && !pWeapon->IsOther())
				sprintf_s(buffer, sizeof(buffer), "%s | %i", pWeapon->GetWeaponName(), pWeapon->GetClip1());
			else
				sprintf_s(buffer, sizeof(buffer), "%s", pWeapon->GetWeaponName());

			drawing.drawString(drawing.espFont, true, x + w / 2, top + 2, Color(255, 255, 255), buffer);
		}
	}

	int place = 0;

	if (cvar::esp_draw_callout)
		drawing.drawString(drawing.espFont, false, x + w + 5, y - 4 + (place++ * 11), Color(255, 255, 255), pEntity->GetLastPlaceName());
}