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
		g_pEngine = (IEngineClient*)g_Tools.QueryInterface(charenc("engine.dll"), charenc("VEngineClient"));
		g_pSurface = (ISurface*)g_Tools.QueryInterface(charenc("vguimatsurface.dll"), charenc("VGUI_Surface"));
		g_pPanel = (IPanel*)g_Tools.QueryInterface(charenc("vgui2.dll"), charenc("VGUI_Panel"));
		g_pEntityList = (IClientEntityList*)g_Tools.QueryInterface(charenc("client.dll"), charenc("VClientEntityList"));
		g_pDebugOverlay = (IVDebugOverlay*)g_Tools.QueryInterface(charenc("engine.dll"), charenc("VDebugOverlay"));
		g_pEngineTrace = (IEngineTrace*)g_Tools.QueryInterface(charenc("engine.dll"), charenc("EngineTraceClient"));

		g_pEngine->ExecuteClientCmd(charenc("echo [successfully initialized interfaces]"));
	}
}