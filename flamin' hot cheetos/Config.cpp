#include "Config.h"

Config config;

Config::Config()
{
	CreateDirectoryA(charenc("csgo//"), 0);
	CreateDirectoryA(charenc("csgo//cfg//"), 0);
	CreateDirectoryA(charenc("csgo//cfg//cheetos//"), 0);
}

void Config::loadConfig()
{
	if (doesFileExist(charenc("csgo//cfg//cheetos//config.ini")))
	{
		configManager.initialize(charenc("config.ini"));

		configManager.getBoolean(charenc("Aimbot"), charenc("Enabled"), cvar::aimbot_enabled);
		configManager.getInteger(charenc("Aimbot"), charenc("Aimbot Key"), cvar::general_key_aimbot);
		configManager.getFloat(charenc("Aimbot"), charenc("Field of View"), cvar::aimbot_fov);
		configManager.getFloat(charenc("Aimbot"), charenc("Smoothing"), cvar::aimbot_smoothing);
		configManager.getFloat(charenc("Aimbot"), charenc("Recoil Control Min"), cvar::aimbot_rcs_min);
		configManager.getFloat(charenc("Aimbot"), charenc("Recoil Control Max"), cvar::aimbot_rcs_max);
		configManager.getFloat(charenc("Aimbot"), charenc("Randomize Hitbox"), cvar::aimbot_randomize_hitbox);
		configManager.getFloat(charenc("Aimbot"), charenc("Randomize Angles"), cvar::aimbot_randomize_angle);

		configManager.getBoolean(charenc("ESP"), charenc("Enabled"), cvar::esp_enabled);
		configManager.getBoolean(charenc("ESP"), charenc("Box"), cvar::esp_draw_box);
		configManager.getBoolean(charenc("ESP"), charenc("Name"), cvar::esp_draw_name);
		configManager.getBoolean(charenc("ESP"), charenc("Weapon"), cvar::esp_draw_weapon);
		configManager.getBoolean(charenc("ESP"), charenc("Callout"), cvar::esp_draw_callout);
		configManager.getBoolean(charenc("ESP"), charenc("Health"), cvar::esp_draw_health);
		configManager.getBoolean(charenc("ESP"), charenc("Health Text"), cvar::esp_draw_health_text);
		configManager.getBoolean(charenc("ESP"), charenc("Armor"), cvar::esp_draw_armor);
		configManager.getBoolean(charenc("ESP"), charenc("Armor Text"), cvar::esp_draw_armor_text);
		configManager.getBoolean(charenc("ESP"), charenc("World"), cvar::esp_draw_world);
		configManager.getBoolean(charenc("ESP"), charenc("Glow"), cvar::esp_draw_glow);

		configManager.getBoolean(charenc("Misc"), charenc("Bunnyhop"), cvar::misc_bunnyhop);
		configManager.getBoolean(charenc("Misc"), charenc("Triggerbot"), cvar::misc_triggerbot);
		configManager.getInteger(charenc("Misc"), charenc("Triggerbot Key"), cvar::general_key_triggerbot);
		configManager.getBoolean(charenc("Misc"), charenc("Skin Changer"), cvar::misc_skinchanger);
		configManager.getBoolean(charenc("Misc"), charenc("Knife Changer"), cvar::misc_knifechanger);
		configManager.getInteger(charenc("Misc"), charenc("Knife Model"), cvar::misc_knifechanger_model);
		configManager.getInteger(charenc("Misc"), charenc("Viewmodel Field of View"), cvar::misc_overridefov);
		configManager.getBoolean(charenc("Misc"), charenc("Standalone Recoil Control"), cvar::misc_recoilcontrol);
		configManager.getFloat(charenc("Misc"), charenc("Standalone Recoil Control Scale"), cvar::misc_recoilcontrol_scale);
		configManager.getBoolean(charenc("Misc"), charenc("Matchmaking Scoreboard"), cvar::misc_scoreboard);
	}
	else
	{
		saveConfig();
	}
}

void Config::saveConfig()
{
	configManager.initialize(charenc("config.ini"));

	configManager.setBoolean(charenc("Aimbot"), charenc("Enabled"), cvar::aimbot_enabled);
	configManager.setInteger(charenc("Aimbot"), charenc("Aimbot Key"), cvar::general_key_aimbot);
	configManager.setFloat(charenc("Aimbot"), charenc("Field of View"), cvar::aimbot_fov);
	configManager.setFloat(charenc("Aimbot"), charenc("Smoothing"), cvar::aimbot_smoothing);
	configManager.setFloat(charenc("Aimbot"), charenc("Recoil Control Min"), cvar::aimbot_rcs_min);
	configManager.setFloat(charenc("Aimbot"), charenc("Recoil Control Max"), cvar::aimbot_rcs_max);
	configManager.setFloat(charenc("Aimbot"), charenc("Randomize Hitbox"), cvar::aimbot_randomize_hitbox);
	configManager.setFloat(charenc("Aimbot"), charenc("Randomize Angles"), cvar::aimbot_randomize_angle);

	configManager.setBoolean(charenc("ESP"), charenc("Enabled"), cvar::esp_enabled);
	configManager.setBoolean(charenc("ESP"), charenc("Box"), cvar::esp_draw_box);
	configManager.setBoolean(charenc("ESP"), charenc("Name"), cvar::esp_draw_name);
	configManager.setBoolean(charenc("ESP"), charenc("Weapon"), cvar::esp_draw_weapon);
	configManager.setBoolean(charenc("ESP"), charenc("Callout"), cvar::esp_draw_callout);
	configManager.setBoolean(charenc("ESP"), charenc("Health"), cvar::esp_draw_health);
	configManager.setBoolean(charenc("ESP"), charenc("Health Text"), cvar::esp_draw_health_text);
	configManager.setBoolean(charenc("ESP"), charenc("Armor"), cvar::esp_draw_armor);
	configManager.setBoolean(charenc("ESP"), charenc("Armor Text"), cvar::esp_draw_armor_text);
	configManager.setBoolean(charenc("ESP"), charenc("World"), cvar::esp_draw_world);
	configManager.setBoolean(charenc("ESP"), charenc("Glow"), cvar::esp_draw_glow);

	configManager.setBoolean(charenc("Misc"), charenc("Bunnyhop"), cvar::misc_bunnyhop);
	configManager.setBoolean(charenc("Misc"), charenc("Triggerbot"), cvar::misc_triggerbot);
	configManager.setInteger(charenc("Misc"), charenc("Triggerbot Key"), cvar::general_key_triggerbot);
	configManager.setBoolean(charenc("Misc"), charenc("Skin Changer"), cvar::misc_skinchanger);
	configManager.setBoolean(charenc("Misc"), charenc("Knife Changer"), cvar::misc_knifechanger);
	configManager.setInteger(charenc("Misc"), charenc("Knife Model"), cvar::misc_knifechanger_model);
	configManager.setInteger(charenc("Misc"), charenc("Viewmodel Field of View"), cvar::misc_overridefov);
	configManager.setBoolean(charenc("Misc"), charenc("Standalone Recoil Control"), cvar::misc_recoilcontrol);
	configManager.setFloat(charenc("Misc"), charenc("Standalone Recoil Control Scale"), cvar::misc_recoilcontrol_scale);
	configManager.setBoolean(charenc("Misc"), charenc("Matchmaking Scoreboard"), cvar::misc_scoreboard);
}

void Config::loadSkinConfig()
{
	if (doesFileExist(charenc("csgo//cfg//cheetos//skinconfig.ini")))
	{
		configManager.initialize(charenc("skinconfig.ini"));

		for (int i = 1; i <= 65; i++)
		{
			if (!WeaponConfig::isPistol(i) && !WeaponConfig::isAutomatic(i) && !WeaponConfig::isSniper(i) && !WeaponConfig::isShotgun(i) && !WeaponConfig::isKnife(i))
				continue;

			char weaponName[32];
			switch (i)
			{
			case WEAPON_DEAGLE: { strcpy(weaponName, charenc("DEAGLE")); break; }
			case WEAPON_DUALS: { strcpy(weaponName, charenc("DUALIES")); break; }
			case WEAPON_FIVE7: { strcpy(weaponName, charenc("FIVE-SEVEN")); break; }
			case WEAPON_GLOCK: { strcpy(weaponName, charenc("GLOCK")); break; }
			case WEAPON_AK47: { strcpy(weaponName, charenc("AK47")); break; }
			case WEAPON_AUG: { strcpy(weaponName, charenc("AUG")); break; }
			case WEAPON_AWP: { strcpy(weaponName, charenc("AWP")); break; }
			case WEAPON_FAMAS: { strcpy(weaponName, charenc("FAMAS")); break; }
			case WEAPON_G3SG1: { strcpy(weaponName, charenc("G3SG1")); break; }
			case WEAPON_GALIL: { strcpy(weaponName, charenc("GALIL")); break; }
			case WEAPON_M249: { strcpy(weaponName, charenc("M249")); break; }
			case WEAPON_M4A1: { strcpy(weaponName, charenc("M4A1")); break; }
			case WEAPON_MAC10: { strcpy(weaponName, charenc("MAC-10")); break; }
			case WEAPON_P90: { strcpy(weaponName, charenc("P90")); break; }
			case WEAPON_UMP45: { strcpy(weaponName, charenc("UMP-45")); break; }
			case WEAPON_XM1014: { strcpy(weaponName, charenc("XM1014")); break; }
			case WEAPON_BIZON: { strcpy(weaponName, charenc("BIZON")); break; }
			case WEAPON_MAG7: { strcpy(weaponName, charenc("MAG-7")); break; }
			case WEAPON_NEGEV: { strcpy(weaponName, charenc("NEGEV")); break; }
			case WEAPON_SAWEDOFF: { strcpy(weaponName, charenc("SAWED-OFF")); break; }
			case WEAPON_TEC9: { strcpy(weaponName, charenc("TEC-9")); break; }
			case WEAPON_TASER: { strcpy(weaponName, charenc("ZEUS")); break; }
			case WEAPON_P2000: { strcpy(weaponName, charenc("P2000")); break; }
			case WEAPON_MP7: { strcpy(weaponName, charenc("MP7")); break; }
			case WEAPON_MP9: { strcpy(weaponName, charenc("MP9")); break; }
			case WEAPON_NOVA: { strcpy(weaponName, charenc("NOVA")); break; }
			case WEAPON_P250: { strcpy(weaponName, charenc("P250")); break; }
			case WEAPON_SCAR20: {  strcpy(weaponName, charenc("SCAR-20")); break; }
			case WEAPON_SG553: { strcpy(weaponName, charenc("SG553")); break; }
			case WEAPON_SCOUT: { strcpy(weaponName, charenc("SCOUT")); break; }
			case WEAPON_REVOLVER: { strcpy(weaponName, charenc("REVOLVER")); break; }
			case WEAPON_M4A1S: { strcpy(weaponName, charenc("M4A1-S")); break; }
			case WEAPON_USPS: { strcpy(weaponName, charenc("USP-S")); break; }
			case WEAPON_CZ75: { strcpy(weaponName, charenc("CZ-75")); break; }
			}

			configManager.getInteger(weaponName, charenc("Skin"), skincfg.at(i).skin);
			configManager.getInteger(weaponName, charenc("StatTrak"), skincfg.at(i).stattrak);
			configManager.getInteger(weaponName, charenc("Seed"), skincfg.at(i).seed);
			configManager.getFloat(weaponName, charenc("Condition"), skincfg.at(i).wear);
			skincfg.at(i).name = configManager.getString(weaponName, charenc("Name"), skincfg.at(i).name);
		}

		for (int i = 500; i <= 516; i++)
		{
			if (!WeaponConfig::isPistol(i) && !WeaponConfig::isAutomatic(i) && !WeaponConfig::isSniper(i) && !WeaponConfig::isShotgun(i) && !WeaponConfig::isKnife(i))
				continue;

			char weaponName[32];
			switch (i)
			{
			case WEAPON_KNIFE_GUT: { strcpy(weaponName, charenc("GUT KNIFE")); break; }
			case WEAPON_KNIFE_FLIP: { strcpy(weaponName, charenc("FLIP KNIFE")); break; }
			case WEAPON_KNIFE_BAYONET: { strcpy(weaponName, charenc("BAYONET")); break; }
			case WEAPON_KNIFE_KARAMBIT: { strcpy(weaponName, charenc("KARAMBIT")); break; }
			case WEAPON_KNIFE_M9BAYONET: { strcpy(weaponName, charenc("M9 BAYONET")); break; }
			case WEAPON_KNIFE_BUTTERFLY: { strcpy(weaponName, charenc("BUTTERFLY KNIFE")); break; }
			case WEAPON_KNIFE_HUNTSMAN: { strcpy(weaponName, charenc("HUNTSMAN KNIFE")); break; }
			case WEAPON_KNIFE_BOWIE: { strcpy(weaponName, charenc("BOWIE KNIFE")); break; }
			}

			configManager.getInteger(weaponName, charenc("Skin"), skincfg.at(i).skin);
			configManager.getInteger(weaponName, charenc("StatTrak"), skincfg.at(i).stattrak);
			configManager.getInteger(weaponName, charenc("Seed"), skincfg.at(i).seed);
			configManager.getFloat(weaponName, charenc("Condition"), skincfg.at(i).wear);
			skincfg.at(i).name = configManager.getString(weaponName, charenc("Name"), skincfg.at(i).name);
		}
	}
	else
	{
		saveSkinConfig();
	}
}

void Config::saveSkinConfig()
{
	configManager.initialize(charenc("skinconfig.ini"));

	for (int i = 1; i <= 65; i++)
	{
		if (!WeaponConfig::isPistol(i) && !WeaponConfig::isAutomatic(i) && !WeaponConfig::isSniper(i) && !WeaponConfig::isShotgun(i) && !WeaponConfig::isKnife(i))
			continue;

		char weaponName[32];
		switch (i)
		{
		case WEAPON_DEAGLE: { strcpy(weaponName, charenc("DEAGLE")); break; }
		case WEAPON_DUALS: { strcpy(weaponName, charenc("DUALIES")); break; }
		case WEAPON_FIVE7: { strcpy(weaponName, charenc("FIVE-SEVEN")); break; }
		case WEAPON_GLOCK: { strcpy(weaponName, charenc("GLOCK")); break; }
		case WEAPON_AK47: { strcpy(weaponName, charenc("AK47")); break; }
		case WEAPON_AUG: { strcpy(weaponName, charenc("AUG")); break; }
		case WEAPON_AWP: { strcpy(weaponName, charenc("AWP")); break; }
		case WEAPON_FAMAS: { strcpy(weaponName, charenc("FAMAS")); break; }
		case WEAPON_G3SG1: { strcpy(weaponName, charenc("G3SG1")); break; }
		case WEAPON_GALIL: { strcpy(weaponName, charenc("GALIL")); break; }
		case WEAPON_M249: { strcpy(weaponName, charenc("M249")); break; }
		case WEAPON_M4A1: { strcpy(weaponName, charenc("M4A1")); break; }
		case WEAPON_MAC10: { strcpy(weaponName, charenc("MAC-10")); break; }
		case WEAPON_P90: { strcpy(weaponName, charenc("P90")); break; }
		case WEAPON_UMP45: { strcpy(weaponName, charenc("UMP-45")); break; }
		case WEAPON_XM1014: { strcpy(weaponName, charenc("XM1014")); break; }
		case WEAPON_BIZON: { strcpy(weaponName, charenc("BIZON")); break; }
		case WEAPON_MAG7: { strcpy(weaponName, charenc("MAG-7")); break; }
		case WEAPON_NEGEV: { strcpy(weaponName, charenc("NEGEV")); break; }
		case WEAPON_SAWEDOFF: { strcpy(weaponName, charenc("SAWED-OFF")); break; }
		case WEAPON_TEC9: { strcpy(weaponName, charenc("TEC-9")); break; }
		case WEAPON_TASER: { strcpy(weaponName, charenc("ZEUS")); break; }
		case WEAPON_P2000: { strcpy(weaponName, charenc("P2000")); break; }
		case WEAPON_MP7: { strcpy(weaponName, charenc("MP7")); break; }
		case WEAPON_MP9: { strcpy(weaponName, charenc("MP9")); break; }
		case WEAPON_NOVA: { strcpy(weaponName, charenc("NOVA")); break; }
		case WEAPON_P250: { strcpy(weaponName, charenc("P250")); break; }
		case WEAPON_SCAR20: {  strcpy(weaponName, charenc("SCAR-20")); break; }
		case WEAPON_SG553: { strcpy(weaponName, charenc("SG553")); break; }
		case WEAPON_SCOUT: { strcpy(weaponName, charenc("SCOUT")); break; }
		case WEAPON_REVOLVER: { strcpy(weaponName, charenc("REVOLVER")); break; }
		case WEAPON_M4A1S: { strcpy(weaponName, charenc("M4A1-S")); break; }
		case WEAPON_USPS: { strcpy(weaponName, charenc("USP-S")); break; }
		case WEAPON_CZ75: { strcpy(weaponName, charenc("CZ-75")); break; }
		}

		configManager.setInteger(weaponName, charenc("Skin"), skincfg.at(i).skin);
		configManager.setInteger(weaponName, charenc("StatTrak"), skincfg.at(i).stattrak);
		configManager.setInteger(weaponName, charenc("Seed"), skincfg.at(i).seed);
		configManager.setFloat(weaponName, charenc("Condition"), skincfg.at(i).wear);
		configManager.setString(weaponName, charenc("Name"), skincfg.at(i).name);
	}

	for (int i = 500; i <= 516; i++)
	{
		if (!WeaponConfig::isPistol(i) && !WeaponConfig::isAutomatic(i) && !WeaponConfig::isSniper(i) && !WeaponConfig::isShotgun(i) && !WeaponConfig::isKnife(i))
			continue;

		char weaponName[32];
		switch (i)
		{
		case WEAPON_KNIFE_GUT: { strcpy(weaponName, charenc("GUT KNIFE")); break; }
		case WEAPON_KNIFE_FLIP: { strcpy(weaponName, charenc("FLIP KNIFE")); break; }
		case WEAPON_KNIFE_BAYONET: { strcpy(weaponName, charenc("BAYONET")); break; }
		case WEAPON_KNIFE_KARAMBIT: { strcpy(weaponName, charenc("KARAMBIT")); break; }
		case WEAPON_KNIFE_M9BAYONET: { strcpy(weaponName, charenc("M9 BAYONET")); break; }
		case WEAPON_KNIFE_BUTTERFLY: { strcpy(weaponName, charenc("BUTTERFLY KNIFE")); break; }
		case WEAPON_KNIFE_HUNTSMAN: { strcpy(weaponName, charenc("HUNTSMAN KNIFE")); break; }
		case WEAPON_KNIFE_BOWIE: { strcpy(weaponName, charenc("BOWIE KNIFE")); break; }
		}

		configManager.setInteger(weaponName, charenc("Skin"), skincfg.at(i).skin);
		configManager.setInteger(weaponName, charenc("StatTrak"), skincfg.at(i).stattrak);
		configManager.setInteger(weaponName, charenc("Seed"), skincfg.at(i).seed);
		configManager.setFloat(weaponName, charenc("Condition"), skincfg.at(i).wear);
		configManager.setString(weaponName, charenc("Name"), skincfg.at(i).name);
	}
}