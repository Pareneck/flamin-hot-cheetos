#ifndef MISCELLANEOUS_H
#define MISCELLANEOUS_H

#pragma once

#include "stdafx.h"

class CBaseEntity;

class Misc
{
public:
	void Bunnyhop(CBaseEntity* local, CInput::CUserCmd* cmd);
};

extern Misc misc;

#endif