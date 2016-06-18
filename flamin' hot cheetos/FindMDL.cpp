#include "FindMDL.h"

FindMDL_t originalFindMDL;

MDLHandle_t __stdcall FindMDL(const char* pMDLRelativePath)
{
	if (cvar::misc_knifechanger)
	{
		if (strstr(pMDLRelativePath, charenc("v_knife_default_ct.mdl")) || strstr(pMDLRelativePath, charenc("v_knife_default_t.mdl")))
		{
			const char* knifeModelPath;

			switch (cvar::misc_knifechanger_model)
			{
			case 0:
				knifeModelPath = charenc("models/weapons/v_knife_bayonet.mdl");
				break;
			case 1:
				knifeModelPath = charenc("models/weapons/v_knife_flip.mdl");
				break;
			case 2:
				knifeModelPath = charenc("models/weapons/v_knife_gut.mdl");
				break;
			case 3:
				knifeModelPath = charenc("models/weapons/v_knife_karam.mdl");
				break;
			case 4:
				knifeModelPath = charenc("models/weapons/v_knife_m9_bay.mdl");
				break;
			case 5:
				knifeModelPath = charenc("models/weapons/v_knife_tactical.mdl");
				break;
			case 6:
				knifeModelPath = charenc("models/weapons/v_knife_falchion_advanced.mdl");
				break;
			case 7:
				knifeModelPath = charenc("models/weapons/v_knife_butterfly.mdl");
				break;
			case 8:
				knifeModelPath = charenc("models/weapons/v_knife_push.mdl");
				break;
			case 9:
				knifeModelPath = charenc("models/weapons/v_knife_survival_bowie.mdl");
				break;
			default:
				knifeModelPath = charenc("models/weapons/v_knife_bayonet.mdl");
				break;
			}

			return originalFindMDL(interfaces::modelcache, knifeModelPath);
		}
	}

	return originalFindMDL(interfaces::modelcache, pMDLRelativePath);
}