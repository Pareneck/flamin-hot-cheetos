#ifndef INTERFACES_H
#define INTERFACES_H

#pragma once

#include "stdafx.h"

class CHLClient;
class IEngineClient;
class IClientEntityList;
class ISurface;
class IPanel;
class IVDebugOverlay;
class IEngineTrace;
class CInput;

namespace interfaces
{
	extern CHLClient*         client;
	extern IEngineClient*     engine;
	extern IClientEntityList* entitylist;
	extern ISurface*          surface;
	extern IPanel*            panel;
	extern IVDebugOverlay*    debugoverlay;
	extern IEngineTrace*      enginetrace;
	extern CInput*            input;

	void initialize();
}

#endif