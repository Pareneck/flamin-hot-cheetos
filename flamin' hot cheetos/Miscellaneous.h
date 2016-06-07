#ifndef MISCELLANEOUS_H
#define MISCELLANEOUS_H

#pragma once

#include "stdafx.h"
#include "Common.h"

class Misc
{
public:
	void Bunnyhop(ValveSDK::CBaseEntity* local, ValveSDK::CInput::CUserCmd* cmd);
};

extern Misc misc;

#endif