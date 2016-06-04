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