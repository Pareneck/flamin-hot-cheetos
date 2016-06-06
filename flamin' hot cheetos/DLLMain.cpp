#include "Main.h"

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
//    - better naming notation (?) -- NOTE: Hungarian notation isn't extremely useful anymore, since the compiler can detect the variable type (wasn't the case back then)
//    - I have trouble deciding whether I should make x variable a class member
//  - figure out this 'undefined class' shit (circular header includes?)
//------------------------------------------------------------------------------------------

bool bUnload = false;

DWORD __stdcall InitRoutine(LPVOID hModule)
{
	while (!GetModuleHandleA(charenc("client.dll")) || !GetModuleHandleA(charenc("engine.dll")))
		Sleep(100);

	Interfaces::Initialize();
	Hooks::Initialize();

	while (!bUnload)
		Sleep(1000);

	Hooks::UnhookFunctions();
	FreeLibraryAndExitThread((HMODULE)hModule, 0);

	return 0;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpReserved)
{
	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH:
		CreateThread(0, 0, InitRoutine, hModule, 0, 0);
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}

	TerminateThread(InitRoutine, 0);

	return TRUE;
}