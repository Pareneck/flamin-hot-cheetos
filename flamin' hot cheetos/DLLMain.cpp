#include "stdafx.h"
#include <future>

//------------------------------------------------------------------------------------------
// flamin' hot cheetos
//------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------
// to do:
//  - make this project a little prettier
//    - working on converting from messy hungarian to http://geosoft.no/development/cppstyle.html
//    - I have trouble deciding whether I should make x variable a class member
//  - use engine button handling to replace getasynckeystate
//  - figure out this 'undefined class' shit (circular header includes?)
//------------------------------------------------------------------------------------------

bool shouldUnload = false;

void initializeRoutine(void* hInstance)
{
	while (!GetModuleHandleA(charenc("client.dll")))
		Sleep(100);

	config.loadConfig();
	config.loadSkinConfig();

	interfaces::initialize();
	offsets::initialize();
	hooks::initialize();

	while (!shouldUnload)
		std::this_thread::sleep_for(std::chrono::seconds(1));

	FreeLibraryAndExitThread((HMODULE)hInstance, 0);
}

BOOL APIENTRY DllMain(HMODULE hInstance, DWORD dwReason, LPVOID lpReserved)
{
	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH:
		DisableThreadLibraryCalls(hInstance);
		std::async(std::launch::async, initializeRoutine, hInstance);
		break;
	case DLL_PROCESS_DETACH:
		hooks::restore();
		break;
	}

	return TRUE;
}