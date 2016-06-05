#include "Main.h"

/* flamin' hot cheetos - rebuild */

// to do:
//  - add in vmt hook manager class [x]
//    - finish hooking painttraverse [x]
//      - do a bunch of shit
//    - hook other shit like createmove
//      - do aimbot and shit
//  - make this project a little prettier
//    - better naming notation (?)
//    - I have trouble deciding whether I should make x variable a class member

bool bUnload = false;

void __stdcall InitRoutine(LPARAM hModule)
{
	Interfaces::Initialize();
	Hooks::Initialize();

	while (!bUnload)
		Sleep(1000);

	Hooks::UnhookFunctions();
	FreeLibraryAndExitThread((HMODULE)hModule, 0);
	return;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpReserved)
{
	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH:
		InitRoutine((LPARAM)hModule);
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}

	return TRUE;
}