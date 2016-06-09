#include "Offsets.h"

namespace offsets
{
	void initialize()
	{
		player::m_iHealth = 0xFC;
		player::m_ArmorValue = 0xA9E8;
		player::m_iTeamNum = 0xF0;
		player::m_iShotsFired = 0xA2B0;
		player::m_fFlags = 0x100;
		player::m_lifeState = 0x25B;
		player::m_bGunGameImmunity = 0x38A0;
		player::m_vecOrigin = 0x134;
		player::m_vecViewOffset = 0x104;
		player::m_nTickBase = 0x3414;
		player::m_hActiveWeapon = 0x2EE8;
		player::m_szLastPlaceName = 0x3598;
		player::m_hOwner = 0x31C0;
		player::m_vecPunchAngle = 0x3018;

		weapon::m_iClip1 = 0x31F4;
		weapon::m_flNextPrimaryAttack = 0x31C8;
		weapon::m_iItemDefinitionIndex = 0x2F88;
		weapon::m_iViewModelIndex = 0x31D0;
		weapon::m_iWorldModelIndex = 0x31D4;
		weapon::m_iWorldDroppedModelIndex = 0x31D8;
		weapon::m_OriginalOwnerXuidHigh = 0x3164;
		weapon::m_OriginalOwnerXuidLow = 0x3160;
		weapon::m_nFallbackSeed = 0x316C;
		weapon::m_nFallbackPaintKit = 0x3168;
		weapon::m_flFallbackWear = 0x3170;
		weapon::m_iItemIDHigh = 0x2FA0;
		weapon::m_iEntityQuality = 0x2F8C;
		weapon::m_nFallbackStatTrak = 0x3174;
		weapon::m_szCustomName = 0x301C;
		weapon::m_iAccountID = 0x2FA8;

		entity::m_CollisionGroup = 0x470;
		entity::m_rgflCoordinateFrame = entity::m_CollisionGroup - 0x30;
	}

	namespace player
	{
		DWORD m_iHealth = 0;
		DWORD m_ArmorValue = 0;
		DWORD m_iTeamNum = 0;
		DWORD m_fFlags = 0;
		DWORD m_szLastPlaceName = 0;
		DWORD m_lifeState = 0;
		DWORD m_vecOrigin = 0;
		DWORD m_vecViewOffset = 0;
		DWORD m_bGunGameImmunity = 0;
		DWORD m_nTickBase = 0;
		DWORD m_hActiveWeapon = 0;
		DWORD m_iShotsFired = 0;
		DWORD m_hOwner = 0;
		DWORD m_vecPunchAngle = 0;
	}
	namespace weapon
	{
		DWORD m_iClip1 = 0;
		DWORD m_flNextPrimaryAttack = 0;
		DWORD m_iItemDefinitionIndex = 0;
		DWORD m_iViewModelIndex = 0;
		DWORD m_iWorldModelIndex = 0;
		DWORD m_iWorldDroppedModelIndex = 0;
		DWORD m_OriginalOwnerXuidLow = 0;
		DWORD m_OriginalOwnerXuidHigh = 0;
		DWORD m_nFallbackSeed = 0;
		DWORD m_nFallbackPaintKit = 0;
		DWORD m_flFallbackWear = 0;
		DWORD m_iItemIDHigh = 0;
		DWORD m_iEntityQuality = 0;
		DWORD m_nFallbackStatTrak = 0;
		DWORD m_szCustomName = 0;
		DWORD m_iAccountID = 0;
	}
	namespace entity
	{
		DWORD m_CollisionGroup = 0;
		DWORD m_rgflCoordinateFrame = 0;
	}
}