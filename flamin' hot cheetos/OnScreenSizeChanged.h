#ifndef ONSCREENSIZECHANGED_H
#define ONSCREENSIZECHANGED_H

#pragma once

#include "stdafx.h"

void __stdcall OnScreenSizeChanged(int nOldWidth, int nOldHeight);

typedef void(__thiscall* OnScreenSizeChanged_t)(ISurface*, int, int);

extern OnScreenSizeChanged_t originalOnScreenSizeChanged;

#endif