#ifndef MISCELLANEOUS_H
#define MISCELLANEOUS_H

#pragma once

#include "Main.h"

// why the hell do I have to make forward declarations

class CMisc
{
public:
	void Bunnyhop(CBaseEntity* pLocal, CInput::CUserCmd* pUserCmd);
};

extern CMisc g_Misc;

#endif