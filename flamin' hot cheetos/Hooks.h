#ifndef HOOKS_H
#define HOOKS_H

#pragma once

#include "Main.h"
#include "VFTManager.h"

#include "PaintTraverse.h"
#include "CreateMove.h"

namespace Hooks
{
	void Initialize();
	void UnhookFunctions();
}

#endif