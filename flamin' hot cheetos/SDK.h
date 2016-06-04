#pragma once

#include "Main.h"

///////////////////////////////
// GET VIRTUAL FUNCTIONS
///////////////////////////////

inline void**& GetVirtualTable(void* inst, size_t offset = 0)
{
	return *reinterpret_cast<void***>((size_t)inst + offset);
}
inline const void** GetVirtualTable(const void* inst, size_t offset = 0)
{
	return *reinterpret_cast<const void***>((size_t)inst + offset);
}

template<typename Fn>
inline Fn GetVirtualFunction(const void* inst, size_t index, size_t offset = 0)
{
	return reinterpret_cast<Fn>(GetVirtualTable(inst, offset)[index]);
}

///////////////////////////////
// PANEL INTERFACE
///////////////////////////////

class IPanel
{
public:
	const char* GetName(unsigned int vguiPanel)
	{
		typedef void(__thiscall* fnOriginal)(void*, unsigned int vguiPanel);
		GetVirtualFunction<fnOriginal>(this, 36)(this, vguiPanel);
	}
}; extern IPanel* g_pPanel;

///////////////////////////////
// SURFACE INTERFACE
///////////////////////////////

class ISurface
{
public:
	
}; extern ISurface* g_pSurface;

///////////////////////////////
// ENGINE INTERFACE
///////////////////////////////

class IEngine
{
public:
	void ExecuteClientCmd(char const* pszCommand)
	{
		typedef void(__thiscall* fnOriginal)(void*, char const* pszCommand);
		GetVirtualFunction<fnOriginal>(this, 108)(this, pszCommand);
	}
}; extern IEngine* g_pEngine;

///////////////////////////////
// TOOLS CLASS
///////////////////////////////

class CTools
{
public:
	void* QueryInterface(std::string szModuleName, std::string szInterfaceName);
}; extern CTools g_Tools;