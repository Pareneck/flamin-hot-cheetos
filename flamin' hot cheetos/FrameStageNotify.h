#ifndef FRAMESTAGENOTIFY_H
#define FRAMESTAGENOTIFY_H

#pragma once

#include "stdafx.h"

void __stdcall FrameStageNotify(ClientFrameStage_t curStage);

typedef void(__thiscall* FrameStageNotify_t)(CHLClient*, ClientFrameStage_t);
extern FrameStageNotify_t originalFrameStageNotify;

#endif