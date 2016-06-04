#include "Interfaces.h"

IEngineClient* g_pEngine = nullptr;
ISurface* g_pSurface = nullptr;
IPanel* g_pPanel = nullptr;
IClientEntityList* g_pEntityList = nullptr;
IVDebugOverlay* g_pDebugOverlay = nullptr;
IEngineTrace* g_pEngineTrace = nullptr;

namespace Interfaces
{
	void Initialize()
	{
		g_pEngine = (IEngineClient*)g_Tools.QueryInterface("engine.dll", "VEngineClient");
		g_pSurface = (ISurface*)g_Tools.QueryInterface("vguimatsurface.dll", "VGUI_Surface");
		g_pPanel = (IPanel*)g_Tools.QueryInterface("vgui2.dll", "VGUI_Panel");
		g_pEntityList = (IClientEntityList*)g_Tools.QueryInterface("client.dll", "VClientEntityList");
		g_pDebugOverlay = (IVDebugOverlay*)g_Tools.QueryInterface("engine.dll", "VDebugOverlay");
		g_pEngineTrace = (IEngineTrace*)g_Tools.QueryInterface("engine.dll", "EngineTraceClient");

		g_pEngine->ExecuteClientCmd("echo [fhc] successfully initialized interfaces");
	}
}