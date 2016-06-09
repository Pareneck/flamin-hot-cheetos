#ifndef OFFSETS_H
#define OFFSETS_H

#pragma once

#include <windows.h>
#include "cx_strenc.h"

namespace offsets
{
	void initialize();

	namespace player
	{
		extern DWORD m_iHealth;
		extern DWORD m_ArmorValue;
		extern DWORD m_iTeamNum;
		extern DWORD m_fFlags;
		extern DWORD m_szLastPlaceName;
		extern DWORD m_lifeState;
		extern DWORD m_vecOrigin;
		extern DWORD m_vecViewOffset;
		extern DWORD m_bGunGameImmunity;
		extern DWORD m_nTickBase;
		extern DWORD m_hActiveWeapon;
		extern DWORD m_iShotsFired;
		extern DWORD m_hOwner;
		extern DWORD m_vecPunchAngle;
	}
	namespace weapon
	{
		extern DWORD m_iClip1;
		extern DWORD m_flNextPrimaryAttack;
		extern DWORD m_iItemDefinitionIndex;
		extern DWORD m_iViewModelIndex;
		extern DWORD m_iWorldModelIndex;
		extern DWORD m_iWorldDroppedModelIndex;
		extern DWORD m_OriginalOwnerXuidLow;
		extern DWORD m_OriginalOwnerXuidHigh;
		extern DWORD m_nFallbackSeed;
		extern DWORD m_nFallbackPaintKit;
		extern DWORD m_flFallbackWear;
		extern DWORD m_iItemIDHigh;
		extern DWORD m_iEntityQuality;
		extern DWORD m_nFallbackStatTrak;
		extern DWORD m_szCustomName;
		extern DWORD m_iAccountID;
	}
	namespace entity
	{
		extern DWORD m_CollisionGroup;
		extern DWORD m_rgflCoordinateFrame;
	}
}

#endif