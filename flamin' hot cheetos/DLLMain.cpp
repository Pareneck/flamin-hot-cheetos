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
//    - hook shit like framestagenotify [x]
//  - make this project a little prettier
//    - working on converting from messy hungarian to http://geosoft.no/development/cppstyle.html (mixed case / camelcase)
//    - I have trouble deciding whether I should make x variable a class member
//  - use engine button handling to replace getasynckeystate
//  - figure out this 'undefined class' shit (circular header includes?)
//------------------------------------------------------------------------------------------

bool shouldUnload = false;

DWORD __stdcall initializeRoutine(LPVOID hinstDLL)
{
	while (!GetModuleHandleA(charenc("client.dll")) || !GetModuleHandleA(charenc("engine.dll")))
		Sleep(100);

	config.loadConfig();
	config.loadSkinConfig();

	interfaces::initialize();
	offsets::initialize();
	hooks::initialize();

	while (!shouldUnload)
		Sleep(1000);

	FreeLibraryAndExitThread((HMODULE)hinstDLL, 0);

	return 0;
}

BOOL APIENTRY DllMain(HMODULE hinstDLL, DWORD dwReason, LPVOID lpReserved)
{
	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH:
		CreateThread(0, 0, initializeRoutine, hinstDLL, 0, 0);
		break;
	case DLL_PROCESS_DETACH:
		hooks::restore();
		break;
	}

	return TRUE;
}