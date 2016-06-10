#ifndef OVERRIDEVIEW_H
#define OVERRIDEVIEW_H

#pragma once

#include "stdafx.h"

void __stdcall OverrideView(CViewSetup* setup);

typedef void(__thiscall* OverrideView_t)(void*, CViewSetup*);
extern OverrideView_t originalOverrideView;

#endif