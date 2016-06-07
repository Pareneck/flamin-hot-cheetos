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

bool Tools::isVisible(Vector& start, Vector& end, CBaseEntity* entity)
{
	IEngineTrace::trace_t trace;
	IEngineTrace::Ray_t ray;
	IEngineTrace::CTraceFilter filter;
	filter.skip = interfaces::entitylist->GetClientEntity(interfaces::engine->GetLocalPlayer());

	ray.Init(start, end);
	interfaces::enginetrace->TraceRay(ray, 0x4600400B, &filter, &trace);

	return (trace.entity == entity || trace.fraction > 0.99f);
}

CBaseCombatWeapon* Tools::getActiveWeapon(CBaseEntity* entity)
{
	ULONG weaponHandle = (ULONG)*(DWORD*)((DWORD)entity + 0x2EE8);
	return (CBaseCombatWeapon*)interfaces::entitylist->GetClientEntityFromHandle(weaponHandle);
}

bool Tools::WorldToScreen(Vector& world, Vector& screen)
{
	return (interfaces::debugoverlay->ScreenPosition(world, screen) != 1);
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

void Tools::VectorTransform(const Vector& in1, const matrix3x4& in2, Vector& out)
{
	VectorTransformFloat(&in1.x, in2, &out.x);
}

void Tools::normalizeAngle(QAngle& angle)
{
	for (int i = 0; i < 2; ++i)
	{
		if (angle[i] < -180.f)
			angle[i] += 360.f;

		if (angle[i] > 180.f)
			angle[i] -= 360.f;
	}

	angle[2] = 0.f;
}

void Tools::clampAngle(QAngle& angle)
{
	if (angle.x < -89.f)
		angle.x = -89.f;

	if (angle.x > 89.f)
		angle.x = 89.f;

	if (angle.y < -180.f)
		angle.y = -180.f;

	if (angle.y > 180.f)
		angle.y = 180.f;

	angle.z = 0.f;
}