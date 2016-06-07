#ifndef PAINTTRAVERSE_H
#define PAINTTRAVERSE_H

#pragma once

#include "stdafx.h"
#include "Common.h"

void __stdcall PaintTraverse(unsigned int vguiPanel, bool forceRepaint, bool allowForce);

typedef void(__thiscall* PaintTraverse_t)(ValveSDK::IPanel*, unsigned int, bool, bool);
extern PaintTraverse_t originalPaintTraverse;

#endif