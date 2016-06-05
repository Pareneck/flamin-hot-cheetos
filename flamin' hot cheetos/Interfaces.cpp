#include "Interfaces.h"

CHLClient* g_pClient = nullptr;
IEngineClient* g_pEngine = nullptr;
IClientEntityList* g_pEntityList = nullptr;
ISurface* g_pSurface = nullptr;
IPanel* g_pPanel = nullptr;
IVDebugOverlay* g_pDebugOverlay = nullptr;
IEngineTrace* g_pEngineTrace = nullptr;
CInput* g_pInput = nullptr;

namespace Interfaces
{
	void Initialize()
	{
		g_pClient = (CHLClient*)g_Tools.QueryInterface(charenc("client.dll"), charenc("VClient"));
		g_pEngine = (IEngineClient*)g_Tools.QueryInterface(charenc("engine.dll"), charenc("VEngineClient"));
		g_pEntityList = (IClientEntityList*)g_Tools.QueryInterface(charenc("client.dll"), charenc("VClientEntityList"));
		g_pSurface = (ISurface*)g_Tools.QueryInterface(charenc("vguimatsurface.dll"), charenc("VGUI_Surface"));
		g_pPanel = (IPanel*)g_Tools.QueryInterface(charenc("vgui2.dll"), charenc("VGUI_Panel"));
		g_pDebugOverlay = (IVDebugOverlay*)g_Tools.QueryInterface(charenc("engine.dll"), charenc("VDebugOverlay"));
		g_pEngineTrace = (IEngineTrace*)g_Tools.QueryInterface(charenc("engine.dll"), charenc("EngineTraceClient"));

		DWORD* pdwClientVMT = (DWORD*)*(DWORD*)g_pClient;
		g_pInput = *(CInput**)(pdwClientVMT[15] + 0x1);

		g_pEngine->ExecuteClientCmd(charenc("echo [successfully initialized interfaces]"));
	}
}