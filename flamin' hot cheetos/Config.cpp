#include "Config.h"

Config config;

Config::Config(void)
{
	configManager.initialize();
}

void Config::load(void)
{
	configManager.getBoolean(charenc("Aimbot"), charenc("Enabled"), cvar::aimbot_enabled);
	configManager.getInteger(charenc("Aimbot"), charenc("Key"), cvar::general_key_aimbot);
	configManager.getFloat(charenc("Aimbot"), charenc("Field of View"), cvar::aimbot_fov);
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

	configManager.getBoolean(charenc("Misc"), charenc("Bunnyhop"), cvar::misc_bunnyhop);
	configManager.getBoolean(charenc("Misc"), charenc("Triggerbot"), cvar::misc_triggerbot);
	configManager.getInteger(charenc("Misc"), charenc("Key"), cvar::general_key_triggerbot);
	configManager.getBoolean(charenc("Misc"), charenc("Skin Changer"), cvar::misc_skinchanger);
}

void Config::save(void)
{
	configManager.setBoolean(charenc("Aimbot"), charenc("Enabled"), cvar::aimbot_enabled);
	configManager.setInteger(charenc("Aimbot"), charenc("Key"), cvar::general_key_aimbot);
	configManager.setFloat(charenc("Aimbot"), charenc("Field of View"), cvar::aimbot_fov);
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

	configManager.setBoolean(charenc("Misc"), charenc("Bunnyhop"), cvar::misc_bunnyhop);
	configManager.setBoolean(charenc("Misc"), charenc("Triggerbot"), cvar::misc_triggerbot);
	configManager.setInteger(charenc("Misc"), charenc("Key"), cvar::general_key_triggerbot);
	configManager.setBoolean(charenc("Misc"), charenc("Skin Changer"), cvar::misc_skinchanger);
}