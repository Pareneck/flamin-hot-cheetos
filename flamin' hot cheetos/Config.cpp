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

			configManager.getInteger(WeaponConfig::getWeaponName(i), charenc("Skin"), skincfg.at(i).skin);
			configManager.getInteger(WeaponConfig::getWeaponName(i), charenc("StatTrak"), skincfg.at(i).stattrak);
			configManager.getInteger(WeaponConfig::getWeaponName(i), charenc("Seed"), skincfg.at(i).seed);
			configManager.getFloat(WeaponConfig::getWeaponName(i), charenc("Condition"), skincfg.at(i).wear);
			skincfg.at(i).name = configManager.getString(WeaponConfig::getWeaponName(i), charenc("Name"), skincfg.at(i).name);
		}

		for (int i = 500; i <= 516; i++)
		{
			if (!WeaponConfig::isPistol(i) && !WeaponConfig::isAutomatic(i) && !WeaponConfig::isSniper(i) && !WeaponConfig::isShotgun(i) && !WeaponConfig::isKnife(i))
				continue;

			configManager.getInteger(WeaponConfig::getWeaponName(i), charenc("Skin"), skincfg.at(i).skin);
			configManager.getInteger(WeaponConfig::getWeaponName(i), charenc("StatTrak"), skincfg.at(i).stattrak);
			configManager.getInteger(WeaponConfig::getWeaponName(i), charenc("Seed"), skincfg.at(i).seed);
			configManager.getFloat(WeaponConfig::getWeaponName(i), charenc("Condition"), skincfg.at(i).wear);
			skincfg.at(i).name = configManager.getString(WeaponConfig::getWeaponName(i), charenc("Name"), skincfg.at(i).name);
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

		configManager.setInteger(WeaponConfig::getWeaponName(i), charenc("Skin"), skincfg.at(i).skin);
		configManager.setInteger(WeaponConfig::getWeaponName(i), charenc("StatTrak"), skincfg.at(i).stattrak);
		configManager.setInteger(WeaponConfig::getWeaponName(i), charenc("Seed"), skincfg.at(i).seed);
		configManager.setFloat(WeaponConfig::getWeaponName(i), charenc("Condition"), skincfg.at(i).wear);
		configManager.setString(WeaponConfig::getWeaponName(i), charenc("Name"), skincfg.at(i).name);
	}

	for (int i = 500; i <= 516; i++)
	{
		if (!WeaponConfig::isPistol(i) && !WeaponConfig::isAutomatic(i) && !WeaponConfig::isSniper(i) && !WeaponConfig::isShotgun(i) && !WeaponConfig::isKnife(i))
			continue;

		configManager.setInteger(WeaponConfig::getWeaponName(i), charenc("Skin"), skincfg.at(i).skin);
		configManager.setInteger(WeaponConfig::getWeaponName(i), charenc("StatTrak"), skincfg.at(i).stattrak);
		configManager.setInteger(WeaponConfig::getWeaponName(i), charenc("Seed"), skincfg.at(i).seed);
		configManager.setFloat(WeaponConfig::getWeaponName(i), charenc("Condition"), skincfg.at(i).wear);
		configManager.setString(WeaponConfig::getWeaponName(i), charenc("Name"), skincfg.at(i).name);
	}
}