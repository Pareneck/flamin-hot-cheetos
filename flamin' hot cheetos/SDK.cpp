#include "SDK.h"

Tools tools;

void* Tools::getInterface(std::string moduleName, std::string interfaceName)
{
	typedef void* (*CreateInterfaceFn)(const char* name, int* returnCode);
	CreateInterfaceFn CreateInterface = nullptr;

	while (!CreateInterface)
	{
		CreateInterface = (CreateInterfaceFn)GetProcAddress(GetModuleHandleA(moduleName.c_str()), charenc("CreateInterface"));
		Sleep(5);
	}

	char buffer[256];

	for (int i = 0; i < 100; i++)
	{
		sprintf_s(buffer, "%s%0.3d", interfaceName.c_str(), i);
		void* interface = CreateInterface(buffer, nullptr);

		if (interface && interface != nullptr)
			break;
	}

	return CreateInterface(buffer, nullptr);
}

bool Tools::isVisible(ValveSDK::Vector& start, ValveSDK::Vector& end, ValveSDK::CBaseEntity* entity)
{
	ValveSDK::IEngineTrace::trace_t tr;
	ValveSDK::IEngineTrace::Ray_t ray;
	ValveSDK::IEngineTrace::CTraceFilter filter;
	filter.pSkip = entitylist->GetClientEntity(engine->GetLocalPlayer());

	ray.Init(start, end);
	enginetrace->TraceRay(ray, 0x4600400B, &filter, &tr);

	return (tr.pEntity == entity || tr.fraction > 0.99f);
}

ValveSDK::CBaseCombatWeapon* Tools::getActiveWeapon(ValveSDK::CBaseEntity* entity)
{
	ULONG weaponHandle = (ULONG)*(DWORD*)((DWORD)entity + 0x2EE8);
	return (ValveSDK::CBaseCombatWeapon*)entitylist->GetClientEntityFromHandle(weaponHandle);
}

bool Tools::WorldToScreen(ValveSDK::Vector& world, ValveSDK::Vector& screen)
{
	return (debugoverlay->ScreenPosition(world, screen) != 1);
}

float DotProductFloat(const float* v1, const float* v2)
{
	return (v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2]);
}

void VectorTransformFloat(const float* in1, const matrix3x4& in2, float* out)
{
	Assert(in1 != out);
	out[0] = DotProductFloat(in1, in2[0]) + in2[0][3];
	out[1] = DotProductFloat(in1, in2[1]) + in2[1][3];
	out[2] = DotProductFloat(in1, in2[2]) + in2[2][3];
}

void Tools::VectorTransform(const ValveSDK::Vector& in1, const matrix3x4& in2, ValveSDK::Vector& out)
{
	VectorTransformFloat(&in1.x, in2, &out.x);
}

ValveSDK::CHLClient*         client = nullptr;
ValveSDK::IEngineClient*     engine = nullptr;
ValveSDK::IClientEntityList* entitylist = nullptr;
ValveSDK::ISurface*          surface = nullptr;
ValveSDK::IPanel*            panel = nullptr;
ValveSDK::IVDebugOverlay*    debugoverlay = nullptr;
ValveSDK::IEngineTrace*      enginetrace = nullptr;
ValveSDK::CInput*            input = nullptr;