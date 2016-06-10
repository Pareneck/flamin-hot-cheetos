#include "Visuals.h"

Visuals visuals;

Visuals::Visuals(void)
{
	espColor = Color(0, 0, 0, 0);
}

void Visuals::think(CBaseEntity* local)
{
	player_info_t info;

	for (int i = 1; i <= interfaces::entitylist->GetHighestEntityIndex(); i++)
	{
		if (i == local->GetIndex())
			continue;

		CBaseEntity* entity = interfaces::entitylist->GetClientEntity(i);
		if (!entity
			|| entity->IsDormant())
			continue;

		if (cvar::esp_draw_world)
			drawWorld(entity);

		if (entity->GetClientClass()->GetClassID() != CCSPlayer
			|| entity->GetLifeState() != LIFE_ALIVE
			|| entity->GetTeamNum() == local->GetTeamNum()
			|| !interfaces::engine->GetPlayerInfo(i, &info))
			continue;

		drawPlayer(local, entity, info);
	}
}

void Visuals::drawPlayer(CBaseEntity* local, CBaseEntity* entity, player_info_t info)
{
	const matrix3x4& trans = *(matrix3x4*)((DWORD)entity + offsets::entity::m_rgflCoordinateFrame);

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

	if (!tools.WorldToScreen(transformed[3], flb)
		|| !tools.WorldToScreen(transformed[0], blb)
		|| !tools.WorldToScreen(transformed[2], frb)
		|| !tools.WorldToScreen(transformed[6], blt)
		|| !tools.WorldToScreen(transformed[5], brt)
		|| !tools.WorldToScreen(transformed[4], frt)
		|| !tools.WorldToScreen(transformed[1], brb)
		|| !tools.WorldToScreen(transformed[7], flt))
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
			espColor = Color(255, 0, 0);
		else if (entity->GetTeamNum() == 3)
			espColor = Color(0, 0, 255);
	}
	else
	{
		if (entity->GetTeamNum() == 2)
			espColor = Color(255, 255, 0);
		else if (entity->GetTeamNum() == 3)
			espColor = Color(0, 255, 0);
	}

	if (cvar::esp_draw_box)
		drawing.drawOutlinedBox(x, y, w, h, espColor, Color(0, 0, 0));

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

void Visuals::drawWorld(CBaseEntity* entity)
{
	if (entity->GetAbsAngles().x == 0.f && entity->GetAbsAngles().z == 0.f)
		return;

	std::string modelName = interfaces::modelinfo->GetModelName(entity->GetModel());
	if (modelName.find(charenc("models/weapons/w_pist_")) != std::string::npos && modelName.find(charenc("_dropped.mdl")) != std::string::npos
		|| modelName.find(charenc("models/weapons/w_rif_")) != std::string::npos && modelName.find(charenc("_dropped.mdl")) != std::string::npos
		|| modelName.find(charenc("models/weapons/w_mach_")) != std::string::npos && modelName.find(charenc("_dropped.mdl")) != std::string::npos
		|| modelName.find(charenc("models/weapons/w_snip_")) != std::string::npos && modelName.find(charenc("_dropped.mdl")) != std::string::npos
		|| modelName.find(charenc("models/weapons/w_eq_")) != std::string::npos && modelName.find(charenc("_dropped.mdl")) != std::string::npos
		|| modelName.find(charenc("models/weapons/w_shot_")) != std::string::npos && modelName.find(charenc("_dropped.mdl")) != std::string::npos
		|| modelName.find(charenc("models/weapons/w_smg_")) != std::string::npos && modelName.find(charenc("_dropped.mdl")) != std::string::npos)
	{
		modelName.erase(0, modelName.find_first_of("_", std::string(charenc("abc")).length()) + 1);
		modelName.erase(modelName.find_last_of("_"), 12);
		modelName.erase(0, modelName.find_first_of("_", std::string(charenc("abc")).length()) + 1);

		if (!strcmp(modelName.c_str(), charenc("ied")))
			modelName = charenc("c4");
		else if (!strcmp(modelName.c_str(), charenc("223")))
			modelName = charenc("usp-s");
		else if (!strcmp(modelName.c_str(), charenc("75")))
			modelName = charenc("cz75");
		else if (!strcmp(modelName.c_str(), charenc("s")))
			modelName = charenc("m4a1-s");

		drawBoundingBox(entity, Color(255, 255, 255), modelName.c_str());
	}
}

void Visuals::drawBoundingBox(CBaseEntity* entity, Color color, const char* text)
{
	const matrix3x4& trans = *(matrix3x4*)((DWORD)entity + offsets::entity::m_rgflCoordinateFrame);

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

	float h = (bottom - top);
	float w = (right - left);

	drawing.drawLine(left, bottom, left, top, color);
	drawing.drawLine(left - 1, bottom - 1, left - 1, top + 2, Color(0, 0, 0));
	drawing.drawLine(left + 1, bottom + 1, left + 1, top + 2, Color(0, 0, 0));

	drawing.drawLine(right, top, right, bottom, color);
	drawing.drawLine(right + 1, top + 1, right + 1, bottom - 1, Color(0, 0, 0));
	drawing.drawLine(right - 1, top - 1, right - 1, bottom + 1, Color(0, 0, 0));

	drawing.drawLine(left, top, right, top, color);
	drawing.drawLine(left + 1, top - 1, right + 1, top - 1, Color(0, 0, 0));
	drawing.drawLine(left, top + 1, right + 1, top + 1, Color(0, 0, 0));

	drawing.drawLine(right, bottom, left, bottom, color);
	drawing.drawLine(right + 1, bottom - 1, left - 1, bottom - 1, Color(0, 0, 0));
	drawing.drawLine(right - 1, bottom + 1, left + 1, bottom + 1, Color(0, 0, 0));

	if (text)
		drawing.drawString(drawing.espFont, true, left + w / 2, top - 15, color, text);
}