#ifndef IN_KEYEVENT_H
#define IN_KEYEVENT_H

#pragma once

#include "stdafx.h"

int __stdcall IN_KeyEvent(int eventcode, int keynum, const char* pszCurrentBinding);

typedef int(__thiscall* IN_KeyEvent_t)(CHLClient*, int, int, const char*);
extern IN_KeyEvent_t originalKeyEvent;

#endif