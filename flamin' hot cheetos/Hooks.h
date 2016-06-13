#ifndef HOOKS_H
#define HOOKS_H

#pragma once

#include "stdafx.h"

#include "VFTManager.h"

#include "PaintTraverse.h"
#include "CreateMove.h"
#include "FrameStageNotify.h"
#include "OverrideView.h"
#include "RenderView.h"
#include "OnScreenSizeChanged.h"
#include "IN_KeyEvent.h"

namespace hooks
{
	void initialize();
	void restore();
}

#endif