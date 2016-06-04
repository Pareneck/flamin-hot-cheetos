#ifndef PAINTTRAVERSE_H
#define PAINTTRAVERSE_H

#pragma once

#include "Main.h"

class IPanel;

void __stdcall PaintTraverse(unsigned int vguiPanel, bool forceRepaint, bool allowForce);

typedef void(__thiscall* tPaintTraverse)(IPanel*, unsigned int, bool, bool);
extern tPaintTraverse g_fnPaintTraverse;

#endif