#include "Visuals.h"

Visuals visuals;

Visuals::Visuals(void)
{
	espColor_ = Color(0, 0, 0, 0);
}

void Visuals::think(CBaseEntity* local)
{
	player_info_t info;

	for (int i = 1; i <= interfaces::entitylist->GetHighestEntityIndex(); i++)
	{
		if (i == local->GetIndex())
			continue;

		CBaseEntity* entity = interfaces::entitylist->GetClientEntity(i);
		if (!entity)
			continue;
		if (entity->IsDormant() || entity->GetLifeState() != LIFE_ALIVE)
			continue;
		if (entity->GetClientClass()->GetClassID() != CCSPlayer)
			continue;
		if (entity->GetTeamNum() == local->GetTeamNum())
			continue;
		if (!interfaces::engine->GetPlayerInfo(i, &info))
			continue;

		drawPlayer(local, entity, info);
	}
}

void Visuals::drawPlayer(CBaseEntity* local, CBaseEntity* entity, player_info_t info)
{
	const matrix3x4& trans = *(matrix3x4*)((DWORD)entity + (0x470 - 0x30));

	Vector min, max;
	entity->GetRenderBounds(min, max);

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

	bool isVisible = tools.isVisible(local->GetEyePosition(), entity->GetEyePosition(), entity);
	if (isVisible)
	{
		if (entity->GetTeamNum() == 2)
			espColor_ = Color(255, 0, 0);
		else if (entity->GetTeamNum() == 3)
			espColor_ = Color(0, 0, 255);
	}
	else
	{
		if (entity->GetTeamNum() == 2)
			espColor_ = Color(255, 255, 0);
		else if (entity->GetTeamNum() == 3)
			espColor_ = Color(0, 255, 0);
	}

	if (cvar::esp_draw_box)
		drawing.drawOutlinedBox(x, y, w, h, espColor_, Color(0, 0, 0));

	if (cvar::esp_draw_health)
		drawing.drawBar(x - 4, y + h / 2 - 1, 4, h + 1, Color(255.f - entity->GetHealth() * 2.55f, entity->GetHealth() * 2.55f, 0), entity->GetHealth());

	if (cvar::esp_draw_armor)
		drawing.drawBar(x - 9, y + h / 2 - 1, 4, h + 1, Color(255.f - entity->GetArmor() * 2.55f, entity->GetArmor() * 2.55f, 0), entity->GetArmor());

	if (cvar::esp_draw_name)
		drawing.drawString(drawing.espFont, true, x + w / 2, y - 16, Color(255, 255, 255), info.m_szPlayerName);

	if (cvar::esp_draw_weapon)
	{
		CBaseCombatWeapon* weapon = tools.getActiveWeapon(entity);
		if (weapon)
		{
			char buffer[32];

			if (!weapon->IsKnife() && !weapon->IsOther())
				sprintf_s(buffer, sizeof(buffer), "%s | %i", weapon->GetWeaponName(), weapon->GetClip1());
			else
				sprintf_s(buffer, sizeof(buffer), "%s", weapon->GetWeaponName());

			drawing.drawString(drawing.espFont, true, x + w / 2, top + 2, Color(255, 255, 255), buffer);
		}
	}

	int place = 0;

	if (cvar::esp_draw_health_text)
		drawing.drawString(drawing.espFont, false, x + w + 5, y - 4 + (place++ * 11), Color(255, 255, 255), charenc("%i HP"), entity->GetHealth());

	if (cvar::esp_draw_armor_text)
		drawing.drawString(drawing.espFont, false, x + w + 5, y - 4 + (place++ * 11), Color(255, 255, 255), charenc("%i AP"), entity->GetArmor());

	if (cvar::esp_draw_callout)
		drawing.drawString(drawing.espFont, false, x + w + 5, y - 4 + (place++ * 11), Color(255, 255, 255), entity->GetLastPlaceName());
}