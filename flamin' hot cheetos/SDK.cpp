#include "SDK.h"

CTools g_Tools;

void* CTools::QueryInterface(std::string szModuleName, std::string szInterfaceName)
{
	typedef void* (*CreateInterfaceFn)(const char* pchName, int* piReturnCode);
	CreateInterfaceFn hInterface = nullptr;

	while (!hInterface)
	{
		hInterface = (CreateInterfaceFn)GetProcAddress(GetModuleHandleA(szModuleName.c_str()), charenc("CreateInterface"));
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

CBaseCombatWeapon* CTools::GetActiveWeapon(CBaseEntity* pEntity)
{
	ULONG ulHandle = (ULONG)*(PDWORD)((DWORD)pEntity + 0x2EE8);
	return (CBaseCombatWeapon*)g_pEntityList->GetClientEntityFromHandle(ulHandle);
}

bool CTools::WorldToScreen(Vector& vWorld, Vector& vScreen)
{
	return (g_pDebugOverlay->ScreenPosition(vWorld, vScreen) != 1);
}

float DotProductFloat(const float* v1, const float* v2)
{
	return v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2];
}

void VectorTransformFloat(const float* in1, const matrix3x4& in2, float* out)
{
	Assert(in1 != out);
	out[0] = DotProductFloat(in1, in2[0]) + in2[0][3];
	out[1] = DotProductFloat(in1, in2[1]) + in2[1][3];
	out[2] = DotProductFloat(in1, in2[2]) + in2[2][3];
}

void CTools::VectorTransform(const Vector& in1, const matrix3x4& in2, Vector& out)
{
	VectorTransformFloat(&in1.x, in2, &out.x);
}