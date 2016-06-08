#ifndef HOOKS_H
#define HOOKS_H

#pragma once

#include "stdafx.h"

#include "VFTManager.h"

#include "PaintTraverse.h"
#include "CreateMove.h"
#include "OnScreenSizeChanged.h"

namespace hooks
{
	void initialize();
	void restore();
}

#endif