#ifndef RENDERVIEW_H
#define RENDERVIEW_H

#pragma once

#include "stdafx.h"

void __stdcall RenderView(CViewSetup& view, int nClearFlags, int whatToDraw);

typedef void(__thiscall* RenderView_t)(CHLClient*, CViewSetup&, int, int);
extern RenderView_t originalRenderView;

#endif