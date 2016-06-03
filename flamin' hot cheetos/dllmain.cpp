#include "Main.h"

/* flamin' hot cheetos - rebuild */

void __stdcall InitRoutine(LPARAM dwModule)
{
	std::cout << "Successfully Injected!";
	return;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
	switch (ul_reason_for_call)
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

