#include "SDK.h"

CTools g_Tools;

void* CTools::GetInterface(std::string szModuleName, std::string szInterfaceName, bool bSkip)
{
	if (szModuleName.empty() || szInterfaceName.empty())
		return nullptr;

	typedef PVOID(*CreateInterfaceFn)(const char* pszName, int* piReturnCode);
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
		PVOID pInterface = hInterface(szBuffer, nullptr);

		if (pInterface && pInterface != NULL)
		{
			if (bSkip) sprintf_s(szBuffer, "%s%0.3d", szInterfaceName.c_str(), i + 1);
			Sleep(5);
			break;
		}
	}

	return hInterface(szBuffer, nullptr);
}