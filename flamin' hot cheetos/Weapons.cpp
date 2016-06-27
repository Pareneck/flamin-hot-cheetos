#include "Weapons.h"

namespace WeaponConfig
{
	bool isPistol(int index)
	{
		switch (index)
		{
		case WEAPON_DEAGLE: return true;
		case WEAPON_DUALS: return true;
		case WEAPON_FIVE7: return true;
		case WEAPON_GLOCK: return true;
		case WEAPON_TEC9: return true;
		case WEAPON_P2000: return true;
		case WEAPON_USPS: return true;
		case WEAPON_P250: return true;
		case WEAPON_CZ75: return true;
		case WEAPON_REVOLVER: return true;
		default: return false;
		}
	}
	bool isShotgun(int index)
	{
		switch (index)
		{
		case WEAPON_XM1014: return true;
		case WEAPON_MAG7: return true;
		case WEAPON_SAWEDOFF: return true;
		case WEAPON_NOVA: return true;
		default: return false;
		}
	}
	bool isAutomatic(int index)
	{
		switch (index)
		{
		case WEAPON_AK47: return true;
		case WEAPON_AUG: return true;
		case WEAPON_FAMAS: return true;
		case WEAPON_GALIL: return true;
		case WEAPON_M249: return true;
		case WEAPON_M4A1: return true;
		case WEAPON_M4A1S: return true;
		case WEAPON_MAC10: return true;
		case WEAPON_P90: return true;
		case WEAPON_UMP45: return true;
		case WEAPON_BIZON: return true;
		case WEAPON_NEGEV: return true;
		case WEAPON_MP7: return true;
		case WEAPON_MP9: return true;
		case WEAPON_SG553: return true;
		default: return false;
		}
	}
	bool isSniper(int index)
	{
		switch (index)
		{
		case WEAPON_AWP: return true;
		case WEAPON_G3SG1: return true;
		case WEAPON_SCAR20: return true;
		case WEAPON_SCOUT: return true;
		default: return false;
		}
	}
	bool isKnife(int index)
	{
		switch (index)
		{
		case WEAPON_KNIFE_CT: return true;
		case WEAPON_KNIFE_T: return true;
		case WEAPON_KNIFE_GUT: return true;
		case WEAPON_KNIFE_FLIP: return true;
		case WEAPON_KNIFE_BAYONET: return true;
		case WEAPON_KNIFE_M9BAYONET: return true;
		case WEAPON_KNIFE_KARAMBIT: return true;
		case WEAPON_KNIFE_HUNTSMAN: return true;
		case WEAPON_KNIFE_BUTTERFLY: return true;
		case WEAPON_KNIFE_BOWIE: return true;
		case WEAPON_KNIFE_FALCHION: return true;
		case WEAPON_KNIFE_DAGGER: return true;
		default: return false;
		}
	}
}