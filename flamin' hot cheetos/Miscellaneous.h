#ifndef MISCELLANEOUS_H
#define MISCELLANEOUS_H

#pragma once

#include "stdafx.h"

class CBaseEntity;
class CUserCmd;

class Misc
{
public:
	void bunnyhop(CBaseEntity* local, CUserCmd* cmd);
};

extern Misc misc;

#endif