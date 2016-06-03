#pragma once

#include "Main.h"

class CTools
{
public:
	void* GetInterface(std::string szModuleName, std::string szInterfaceName, bool bSkip = false);
};

extern CTools g_Tools;