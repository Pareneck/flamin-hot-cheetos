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
class IVModelInfo;
class CGlobalVars;

namespace interfaces
{
	extern DWORD              clientdll;

	extern CHLClient*         client;
	extern IEngineClient*     engine;
	extern IClientEntityList* entitylist;
	extern ISurface*          surface;
	extern IPanel*            panel;
	extern IVDebugOverlay*    debugoverlay;
	extern IEngineTrace*      enginetrace;
	extern CInput*            input;
	extern IVModelInfo*       modelinfo;
	extern CGlobalVars*       globalvars;

	void initialize();
}

#endif