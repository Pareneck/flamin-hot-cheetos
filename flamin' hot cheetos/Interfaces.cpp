#include "Interfaces.h"

namespace interfaces
{
	void initialize()
	{
		client = (ValveSDK::CHLClient*)tools.getInterface(charenc("client.dll"), charenc("VClient"));
		engine = (ValveSDK::IEngineClient*)tools.getInterface(charenc("engine.dll"), charenc("VEngineClient"));
		entitylist = (ValveSDK::IClientEntityList*)tools.getInterface(charenc("client.dll"), charenc("VClientEntityList"));
		surface = (ValveSDK::ISurface*)tools.getInterface(charenc("vguimatsurface.dll"), charenc("VGUI_Surface"));
		panel = (ValveSDK::IPanel*)tools.getInterface(charenc("vgui2.dll"), charenc("VGUI_Panel"));
		debugoverlay = (ValveSDK::IVDebugOverlay*)tools.getInterface(charenc("engine.dll"), charenc("VDebugOverlay"));
		enginetrace = (ValveSDK::IEngineTrace*)tools.getInterface(charenc("engine.dll"), charenc("EngineTraceClient"));

		DWORD* clientVMT = (DWORD*)*(DWORD*)client;
		input = *(ValveSDK::CInput**)(clientVMT[15] + 0x1);

		engine->ExecuteClientCmd(charenc("echo [successfully initialized interfaces]"));
	}
}