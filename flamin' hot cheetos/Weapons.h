#pragma once
#pragma warning(disable: 4172)
#pragma warning(disable: 4996)

#define _CRT_SECURE_NO_WARNINGS

#include "SDKDefinitions.h"
#include "cx_strenc.h"

namespace WeaponConfig
{
	bool isPistol(int index);
	bool isShotgun(int index);
	bool isAutomatic(int index);
	bool isSniper(int index);
	bool isKnife(int index);
}