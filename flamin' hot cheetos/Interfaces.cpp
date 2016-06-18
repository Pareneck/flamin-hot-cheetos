#include "Interfaces.h"

namespace interfaces
{
	DWORD              clientdll = 0;

	CHLClient*         client = nullptr;
	void*              clientMode = nullptr;
	IEngineClient*     engine = nullptr;
	IClientEntityList* entitylist = nullptr;
	ISurface*          surface = nullptr;
	IPanel*            panel = nullptr;
	IVDebugOverlay*    debugoverlay = nullptr;
	IEngineTrace*      enginetrace = nullptr;
	CInput*            input = nullptr;
	IVModelInfo*       modelinfo = nullptr;
	CGlobalVars*       globalvars = nullptr;
	IMDLCache*         modelcache = nullptr;
	void*              viewRender = nullptr;

	void initialize()
	{
		while (!clientdll)
			clientdll = (DWORD)GetModuleHandleA(charenc("client.dll"));

		client = (CHLClient*)tools.getInterface(charenc("client.dll"), charenc("VClient"));
		clientMode = **(void***)((*(DWORD**)interfaces::client)[10] + 0x5);
		engine = (IEngineClient*)tools.getInterface(charenc("engine.dll"), charenc("VEngineClient"));
		entitylist = (IClientEntityList*)tools.getInterface(charenc("client.dll"), charenc("VClientEntityList"));
		surface = (ISurface*)tools.getInterface(charenc("vguimatsurface.dll"), charenc("VGUI_Surface"));
		panel = (IPanel*)tools.getInterface(charenc("vgui2.dll"), charenc("VGUI_Panel"));
		debugoverlay = (IVDebugOverlay*)tools.getInterface(charenc("engine.dll"), charenc("VDebugOverlay"));
		enginetrace = (IEngineTrace*)tools.getInterface(charenc("engine.dll"), charenc("EngineTraceClient"));
		modelinfo = (IVModelInfo*)tools.getInterface(charenc("engine.dll"), charenc("VModelInfoClient"));
		globalvars = (CGlobalVars*)*(DWORD*)*(DWORD*)(tools.getPatternOffset(charenc("client.dll"), (PBYTE)charenc("\xA1\x00\x00\x00\x00\x8B\x40\x10\x89\x41\x04"), charenc("x????xxxxxx")) + 0x1);
		modelcache = (IMDLCache*)tools.getInterface(charenc("datacache.dll"), charenc("MDLCache"));
		viewRender = **(void***)((DWORD)tools.getPatternOffset(charenc("client.dll"), (PBYTE)charenc("\xFF\x50\x14\xE8\x00\x00\x00\x00\x5D"), charenc("xxxx????x")) - 7);

		DWORD* clientVmt = (DWORD*)*(DWORD*)client;
		input = *(CInput**)(clientVmt[15] + 0x1);

		engine->ClientCmd_Unrestricted(charenc("echo [successfully initialized interfaces]"));
	}
}