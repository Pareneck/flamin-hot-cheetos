#include "Interfaces.h"

IEngine* g_pEngine = nullptr;
ISurface* g_pSurface = nullptr;
IPanel* g_pPanel = nullptr;

namespace Interfaces
{
	void Initialize()
	{
		g_pEngine = (IEngine*)g_Tools.QueryInterface("engine.dll", "VEngineClient");
		g_pSurface = (ISurface*)g_Tools.QueryInterface("vguimatsurface.dll", "VGUI_Surface");
		g_pPanel = (IPanel*)g_Tools.QueryInterface("vgui2.dll", "VGUI_Panel");

		g_pEngine->ExecuteClientCmd("echo [fhc] successfully initialized interfaces");
	}
}