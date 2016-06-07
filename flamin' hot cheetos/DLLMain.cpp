#include "stdafx.h"

//------------------------------------------------------------------------------------------
// flamin' hot cheetos | rebuild
//------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------
// to do:
//  - add in vmt hook manager class [x]
//    - finish hooking painttraverse [x]
//      - do a bunch of shit
//    - hook other shit like createmove [x]
//      - do aimbot and shit
//  - make this project a little prettier
//    - working on converting from messy hungarian to http://geosoft.no/development/cppstyle.html (mixed case / camelcase)
//    - I have trouble deciding whether I should make x variable a class member
//  - figure out this 'undefined class' shit (circular header includes?)
//------------------------------------------------------------------------------------------

bool shouldUnload = false;

DWORD __stdcall initializeRoutine(LPVOID hModule)
{
	while (!GetModuleHandleA(charenc("client.dll")) || !GetModuleHandleA(charenc("engine.dll")))
		Sleep(100);

	interfaces::initialize();
	hooks::initialize();

	while (!shouldUnload)
		Sleep(1000);

	hooks::restore();
	FreeLibraryAndExitThread((HMODULE)hModule, 0);

	return 0;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpReserved)
{
	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH:
		CreateThread(0, 0, initializeRoutine, hModule, 0, 0);
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}

	TerminateThread(initializeRoutine, 0);

	return TRUE;
}