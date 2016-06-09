#ifndef CONTROL_VARIABLES_H
#define CONTROL_VARIABLES_H

#pragma once

namespace cvar
{
	extern int general_key_aimbot;
	extern int general_key_triggerbot;

	extern bool aimbot_enabled;
	extern float aimbot_fov;
	extern float aimbot_rcs_min;
	extern float aimbot_rcs_max;
	extern float aimbot_randomize_hitbox;
	extern float aimbot_randomize_angle;

	extern bool esp_enabled;
	extern bool esp_draw_box;
	extern bool esp_draw_name;
	extern bool esp_draw_weapon;
	extern bool esp_draw_callout;
	extern bool esp_draw_health;
	extern bool esp_draw_health_text;
	extern bool esp_draw_armor;
	extern bool esp_draw_armor_text;
	extern bool esp_draw_world;

	extern bool misc_bunnyhop;
	extern bool misc_triggerbot;
	extern bool misc_skinchanger;
}

#endif