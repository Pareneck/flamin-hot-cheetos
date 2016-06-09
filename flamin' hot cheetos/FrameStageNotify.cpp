#include "FrameStageNotify.h"

FrameStageNotify_t originalFrameStageNotify;

void __stdcall FrameStageNotify(ClientFrameStage_t curStage)
{
	originalFrameStageNotify(interfaces::client, curStage);

	if (curStage == FRAME_NET_UPDATE_POSTDATAUPDATE_START)
	{
		if (cvar::misc_skinchanger)
		{
			player_info_t info;

			CBaseEntity* local = interfaces::entitylist->GetClientEntity(interfaces::engine->GetLocalPlayer());
			if (!local
				|| local->GetLifeState() != LIFE_ALIVE
				|| !interfaces::engine->GetPlayerInfo(local->GetIndex(), &info))
				return;

			for (int i = 1; i <= interfaces::entitylist->GetHighestEntityIndex(); i++)
			{
				if (i == local->GetIndex())
					continue;

				CBaseEntity* entity = interfaces::entitylist->GetClientEntity(i);
				if (!entity)
					continue;

				std::string modelName = interfaces::modelinfo->GetModelName(entity->GetModel());
				if (modelName.find(charenc("models/weapons")) == std::string::npos)
					continue;

				CBaseEntity* owner = interfaces::entitylist->GetClientEntityFromHandle(entity->GetOwner());
				if (!owner
					|| owner != local)
					continue;

				CBaseCombatWeapon* weapon = (CBaseCombatWeapon*)entity;

				if (weapon->GetItemDefinitionIndex() == WEAPON_AK47)
					weapon->SetPattern(info, 243, 0.000000f, 1337, 1337, "flamin' hot cheetos");
			}
		}
	}
}