#include "Main.h"

//------------------------------------------------------------------------------------------
// flamin' hot cheetos | rebuild
//------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------
// to do:
//  - add in vmt hook manager class [x]
//    - finish hooking painttraverse [x]
//      - do a bunch of shit
//    - hook other shit like createmove
//      - do aimbot and shit
//  - make this project a little prettier
//    - better naming notation (?)
//    - I have trouble deciding whether I should make x variable a class member
//------------------------------------------------------------------------------------------

bool bUnload = false;

void __stdcall InitRoutine(LPARAM hModule)
{
	while (!GetModuleHandleA(charenc("client.dll")) || !GetModuleHandleA(charenc("engine.dll")))
		Sleep(100);

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
		CreateThread(0, 0, (LPTHREAD_START_ROUTINE)InitRoutine, hModule, 0, 0);
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}

	TerminateThread(InitRoutine, 0);

	return TRUE;
}