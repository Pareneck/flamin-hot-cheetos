#pragma once

#include "Main.h"

typedef void(__thiscall* tPaintTraverse)(unsigned int, bool, bool);
void __stdcall PaintTraverse(unsigned int vguiPanel, bool forceRepaint, bool allowForce);