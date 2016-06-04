#include "SDK.h"

CTools g_Tools;

void* CTools::QueryInterface(std::string szModuleName, std::string szInterfaceName)
{
	typedef void* (*CreateInterfaceFn)(const char* pchName, int* piReturnCode);
	CreateInterfaceFn hInterface = nullptr;

	while (!hInterface)
	{
		hInterface = (CreateInterfaceFn)GetProcAddress(GetModuleHandleA(szModuleName.c_str()), "CreateInterface");
		Sleep(5);
	}

	char szBuffer[256];

	for (int i = 0; i < 100; i++)
	{
		sprintf_s(szBuffer, "%s%0.3d", szInterfaceName.c_str(), i);
		void* pInterface = hInterface(szBuffer, nullptr);

		if (pInterface && pInterface != nullptr)
			break;
	}

	return hInterface(szBuffer, nullptr);
}

bool CTools::IsVisible(Vector& vecStart, Vector& vecEnd, CBaseEntity* pEntity)
{
	IEngineTrace::trace_t tr;
	IEngineTrace::Ray_t ray;
	IEngineTrace::CTraceFilter filter;
	filter.pSkip = g_pEntityList->GetClientEntity(g_pEngine->GetLocalPlayer());

	ray.Init(vecStart, vecEnd);
	g_pEngineTrace->TraceRay(ray, 0x4600400B, &filter, &tr);

	return (tr.pEntity == pEntity || tr.fraction > 0.99f);
}