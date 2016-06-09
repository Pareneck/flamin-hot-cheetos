#ifndef MISCELLANEOUS_H
#define MISCELLANEOUS_H

#pragma once

#include "stdafx.h"

class Misc
{
public:
	void bunnyhop(CBaseEntity* local, CInput::CUserCmd* cmd);
};

extern Misc misc;

#endif