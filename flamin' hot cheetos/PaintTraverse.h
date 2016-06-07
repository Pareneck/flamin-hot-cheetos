#ifndef PAINTTRAVERSE_H
#define PAINTTRAVERSE_H

#pragma once

#include "stdafx.h"

void __stdcall PaintTraverse(unsigned int vguiPanel, bool forceRepaint, bool allowForce);

typedef void(__thiscall* PaintTraverse_t)(IPanel*, unsigned int, bool, bool);
extern PaintTraverse_t originalPaintTraverse;

#endif