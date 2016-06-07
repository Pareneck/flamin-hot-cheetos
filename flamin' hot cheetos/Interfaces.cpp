#include "Interfaces.h"

namespace interfaces
{
	CHLClient*         client = nullptr;
	IEngineClient*     engine = nullptr;
	IClientEntityList* entitylist = nullptr;
	ISurface*          surface = nullptr;
	IPanel*            panel = nullptr;
	IVDebugOverlay*    debugoverlay = nullptr;
	IEngineTrace*      enginetrace = nullptr;
	CInput*            input = nullptr;

	void initialize()
	{
		client = (CHLClient*)tools.getInterface(charenc("client.dll"), charenc("VClient"));
		engine = (IEngineClient*)tools.getInterface(charenc("engine.dll"), charenc("VEngineClient"));
		entitylist = (IClientEntityList*)tools.getInterface(charenc("client.dll"), charenc("VClientEntityList"));
		surface = (ISurface*)tools.getInterface(charenc("vguimatsurface.dll"), charenc("VGUI_Surface"));
		panel = (IPanel*)tools.getInterface(charenc("vgui2.dll"), charenc("VGUI_Panel"));
		debugoverlay = (IVDebugOverlay*)tools.getInterface(charenc("engine.dll"), charenc("VDebugOverlay"));
		enginetrace = (IEngineTrace*)tools.getInterface(charenc("engine.dll"), charenc("EngineTraceClient"));

		DWORD* clientVMT = (DWORD*)*(DWORD*)client;
		input = *(CInput**)(clientVMT[15] + 0x1);

		engine->ExecuteClientCmd(charenc("echo [successfully initialized interfaces]"));
	}
}