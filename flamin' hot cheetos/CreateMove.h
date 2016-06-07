#ifndef CREATEMOVE_H
#define CREATEMOVE_H

#pragma once

#include "Main.h"

class CHLClient;

void __stdcall CreateMove(int sequence_number, float input_sample_frametime, bool active);

typedef void(__thiscall* CreateMove_t)(CHLClient*, int, float, bool);
extern CreateMove_t originalCreateMove;

#endif