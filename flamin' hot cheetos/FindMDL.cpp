#include "FindMDL.h"

FindMDL_t originalFindMDL;

MDLHandle_t __stdcall FindMDL(const char* pMDLRelativePath)
{
	if (strstr(pMDLRelativePath, charenc("v_knife_default_ct.mdl")) || strstr(pMDLRelativePath, charenc("v_knife_default_t.mdl")))
	{
		const char* modelPath = "";

		switch (cvar::misc_knifechanger_model)
		{
		case 1:
			modelPath = charenc("models/weapons/v_knife_butterfly.mdl");
			break;
		default:
			modelPath = charenc("models/weapons/v_knife_butterfly.mdl");
			break;
		}

		interfaces::engine->ClientCmd_Unrestricted("echo changed knife!");
		return originalFindMDL(interfaces::modelcache, modelPath);
	}

	return originalFindMDL(interfaces::modelcache, pMDLRelativePath);
}