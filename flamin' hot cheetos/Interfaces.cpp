#include "Interfaces.h"

CHLClient* g_pClient = nullptr;
IEngineClient* g_pEngine = nullptr;
IClientEntityList* g_pEntityList = nullptr;
ISurface* g_pSurface = nullptr;
IPanel* g_pPanel = nullptr;
IVDebugOverlay* g_pDebugOverlay = nullptr;
IEngineTrace* g_pEngineTrace = nullptr;
CInput* g_pInput = nullptr;

namespace interfaces
{
	void initialize()
	{
		g_pClient = (CHLClient*)tools.getInterface(charenc("client.dll"), charenc("VClient"));
		g_pEngine = (IEngineClient*)tools.getInterface(charenc("engine.dll"), charenc("VEngineClient"));
		g_pEntityList = (IClientEntityList*)tools.getInterface(charenc("client.dll"), charenc("VClientEntityList"));
		g_pSurface = (ISurface*)tools.getInterface(charenc("vguimatsurface.dll"), charenc("VGUI_Surface"));
		g_pPanel = (IPanel*)tools.getInterface(charenc("vgui2.dll"), charenc("VGUI_Panel"));
		g_pDebugOverlay = (IVDebugOverlay*)tools.getInterface(charenc("engine.dll"), charenc("VDebugOverlay"));
		g_pEngineTrace = (IEngineTrace*)tools.getInterface(charenc("engine.dll"), charenc("EngineTraceClient"));

		DWORD* clientVMT = (DWORD*)*(DWORD*)g_pClient;
		g_pInput = *(CInput**)(clientVMT[15] + 0x1);

		g_pEngine->ExecuteClientCmd(charenc("echo [successfully initialized interfaces]"));
	}
}