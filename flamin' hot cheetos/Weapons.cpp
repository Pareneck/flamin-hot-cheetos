#include "Weapons.h"

namespace WeaponConfig
{
	bool isPistol(int index)
	{
		switch (index)
		{
		case WEAPON_DEAGLE:
			return true;
		case WEAPON_DUALS:
			return true;
		case WEAPON_FIVE7:
			return true;
		case WEAPON_GLOCK:
			return true;
		case WEAPON_TEC9:
			return true;
		case WEAPON_P2000:
			return true;
		case WEAPON_USPS:
			return true;
		case WEAPON_P250:
			return true;
		case WEAPON_CZ75:
			return true;
		case WEAPON_REVOLVER:
			return true;
		default:
			return false;
		}
	}
	bool isShotgun(int index)
	{
		switch (index)
		{
		case WEAPON_XM1014:
			return true;
		case WEAPON_MAG7:
			return true;
		case WEAPON_SAWEDOFF:
			return true;
		case WEAPON_NOVA:
			return true;
		default:
			return false;
		}
	}
	bool isAutomatic(int index)
	{
		switch (index)
		{
		case WEAPON_AK47:
			return true;
		case WEAPON_AUG:
			return true;
		case WEAPON_FAMAS:
			return true;
		case WEAPON_GALIL:
			return true;
		case WEAPON_M249:
			return true;
		case WEAPON_M4A1:
			return true;
		case WEAPON_M4A1S:
			return true;
		case WEAPON_MAC10:
			return true;
		case WEAPON_P90:
			return true;
		case WEAPON_UMP45:
			return true;
		case WEAPON_BIZON:
			return true;
		case WEAPON_NEGEV:
			return true;
		case WEAPON_MP7:
			return true;
		case WEAPON_MP9:
			return true;
		case WEAPON_SG553:
			return true;
		default:
			return false;
		}
	}
	bool isSniper(int index)
	{
		switch (index)
		{
		case WEAPON_AWP:
			return true;
		case WEAPON_G3SG1:
			return true;
		case WEAPON_SCAR20:
			return true;
		case WEAPON_SCOUT:
			return true;
		default:
			return false;
		}
	}
	bool isKnife(int index)
	{
		switch (index)
		{
		case WEAPON_KNIFE_CT:
			return true;
		case WEAPON_KNIFE_T:
			return true;
		case WEAPON_KNIFE_GUT:
			return true;
		case WEAPON_KNIFE_FLIP:
			return true;
		case WEAPON_KNIFE_BAYONET:
			return true;
		case WEAPON_KNIFE_M9BAYONET:
			return true;
		case WEAPON_KNIFE_KARAMBIT:
			return true;
		case WEAPON_KNIFE_HUNTSMAN:
			return true;
		case WEAPON_KNIFE_BUTTERFLY:
			return true;
		case WEAPON_KNIFE_BOWIE:
			return true;
		case WEAPON_KNIFE_FALCHION:
			return true;
		case WEAPON_KNIFE_DAGGER:
			return true;
		default:
			return false;
		}
	}
	const char* getWeaponName(int index)
	{
		switch (index)
		{
		case WEAPON_DEAGLE:
			return "DEAGLE"; break;
		case WEAPON_DUALS:
			return "DUALS"; break;
		case WEAPON_FIVE7:
			return "FIVE SEVEN"; break;
		case WEAPON_GLOCK:
			return "GLOCK"; break;
		case WEAPON_AK47:
			return "AK47"; break;
		case WEAPON_AUG:
			return "AUG"; break;
		case WEAPON_AWP:
			return "AWP"; break;
		case WEAPON_FAMAS:
			return "FAMAS"; break;
		case WEAPON_G3SG1:
			return "G3SG1"; break;
		case WEAPON_GALIL:
			return "GALIL"; break;
		case WEAPON_M249:
			return "M249"; break;
		case WEAPON_M4A1:
			return "M4A1"; break;
		case WEAPON_MAC10:
			return "MAC10"; break;
		case WEAPON_P90:
			return "P90"; break;
		case WEAPON_UMP45:
			return "UMP45"; break;
		case WEAPON_XM1014:
			return "XM1014"; break;
		case WEAPON_BIZON:
			return "BIZON"; break;
		case WEAPON_MAG7:
			return "MAG7"; break;
		case WEAPON_NEGEV:
			return "NEGEV"; break;
		case WEAPON_SAWEDOFF:
			return "SAWED OFF"; break;
		case WEAPON_TEC9:
			return "TEC9"; break;
		case WEAPON_TASER:
			return "TASER"; break;
		case WEAPON_P2000:
			return "P2000"; break;
		case WEAPON_MP7:
			return "MP7"; break;
		case WEAPON_MP9:
			return "MP9"; break;
		case WEAPON_NOVA:
			return "NOVA"; break;
		case WEAPON_P250:
			return "P250"; break;
		case WEAPON_SCAR20:
			return "SCAR20"; break;
		case WEAPON_SG553:
			return "SG553"; break;
		case WEAPON_SCOUT:
			return "SCOUT"; break;
		case WEAPON_REVOLVER:
			return "REVOLVER"; break;
		case WEAPON_C4:
			return "BOMB"; break;
		case WEAPON_KNIFE_CT:
			return "KNIFE"; break;
		case WEAPON_KNIFE_T:
			return "KNIFE"; break;
		case WEAPON_KNIFE_GUT:
			return "GUT KNIFE"; break;
		case WEAPON_KNIFE_FLIP:
			return "FLIP KNIFE"; break;
		case WEAPON_KNIFE_BAYONET:
			return "BAYONET"; break;
		case WEAPON_KNIFE_KARAMBIT:
			return "KARAMBIT"; break;
		case WEAPON_KNIFE_M9BAYONET:
			return "M9 BAYONET"; break;
		case WEAPON_KNIFE_BUTTERFLY:
			return "BUTTERFLY"; break;
		case WEAPON_KNIFE_FALCHION:
			return "FALCHION"; break;
		case WEAPON_KNIFE_HUNTSMAN:
			return "HUNTSMAN"; break;
		case WEAPON_KNIFE_DAGGER:
			return "SHADOW DAGGERS"; break;
		case WEAPON_KNIFE_BOWIE:
			return "BOWIE"; break;
		case WEAPON_FLASH:
			return "FLASHBANG"; break;
		case WEAPON_HE:
			return "HE GRENADE"; break;
		case WEAPON_SMOKE:
			return "SMOKE"; break;
		case WEAPON_MOLOTOV:
			return "MOLOTOV"; break;
		case WEAPON_DECOY:
			return "DECOY"; break;
		case WEAPON_INC:
			return "INC GRENADE"; break;
		case WEAPON_M4A1S:
			return "M4A1-S"; break;
		case WEAPON_USPS:
			return "USP-S"; break;
		case WEAPON_CZ75:
			return "CZ75"; break;
		}

		return "";
	}
}