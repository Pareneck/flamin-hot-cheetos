#pragma once

#include "SDKDefinitions.h"

namespace WeaponConfig
{
	bool isPistol(int index);
	bool isShotgun(int index);
	bool isAutomatic(int index);
	bool isSniper(int index);
	bool isKnife(int index);

	const char* getWeaponName(int index);
}