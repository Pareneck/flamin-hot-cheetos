#include "Main.h"

/* flamin' hot cheetos - rebuild */

void __stdcall InitRoutine(LPARAM dwModule)
{
	g_pEngine = (IEngine*)g_Tools.QueryInterface("engine.dll", "VEngineClient");
	g_pEngine->ExecuteClientCmd("echo initializing main cheat routine...");

	std::cout << "Successfully Injected!" << std::endl;
	return;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpReserved)
{
	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH:
		InitRoutine((DWORD)hModule);
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}

	return TRUE;
}

