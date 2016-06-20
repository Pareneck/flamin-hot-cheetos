#ifndef SDK_H
#define SDK_H

#ifdef CreateFont
#undef CreateFont
#endif

#pragma once
#pragma warning(disable: 4307)

#include <windows.h>

#include "Interfaces.h"
#include "Color.h"
#include "Offsets.h"
#include "Vector.h"

#include "SDKDefinitions.h"

#include "dt_recv.h"
#include "checksum_crc.h"

//----------------------------------------
// TYPEDEFS
//----------------------------------------

typedef float matrix3x4[3][4];
typedef float matrix4x4[4][4];

//----------------------------------------
// FORWARD DECLARATIONS
//----------------------------------------

class model_t;
class IVClientClass;

//----------------------------------------
// GET VIRTUAL FUNCTIONS
//----------------------------------------

inline void**& GetVirtualTable(void* inst, size_t offset = 0)
{
	return *reinterpret_cast<void***>((size_t)inst + offset);
}
inline const void** GetVirtualTable(const void* inst, size_t offset = 0)
{
	return *reinterpret_cast<const void***>((size_t)inst + offset);
}

template<typename Fn>
inline Fn GetVirtualFunction(const void* inst, size_t index, size_t offset = 0)
{
	return reinterpret_cast<Fn>(GetVirtualTable(inst, offset)[index]);
}

//----------------------------------------
// ENTITY CLASS
//----------------------------------------

class CBaseEntity
{
public:
	char GetLifeState()
	{
		return *(char*)((DWORD)this + offsets::player::m_lifeState);
	}
	int GetHealth()
	{
		return *(int*)((DWORD)this + offsets::player::m_iHealth);
	}
	int GetArmor()
	{
		return *(int*)((DWORD)this + offsets::player::m_ArmorValue);
	}
	int GetTeamNum()
	{
		return *(int*)((DWORD)this + offsets::player::m_iTeamNum);
	}
	bool IsProtected()
	{
		return *(bool*)((DWORD)this + offsets::player::m_bGunGameImmunity);
	}
	bool IsScoped()
	{
		return *(bool*)((DWORD)this + offsets::player::m_bIsScoped);
	}
	int GetFlags()
	{
		return *(int*)((DWORD)this + offsets::player::m_fFlags);
	}
	int GetShotsFired()
	{
		return *(int*)((DWORD)this + offsets::player::m_iShotsFired);
	}
	int GetTickBase()
	{
		return *(int*)((DWORD)this + offsets::player::m_nTickBase);
	}
	const char* GetLastPlaceName()
	{
		return (char*)((DWORD)this + offsets::player::m_szLastPlaceName);
	}
	Vector GetViewOffset()
	{
		return *(Vector*)((DWORD)this + offsets::player::m_vecViewOffset);
	}
	Vector GetOrigin()
	{
		return *(Vector*)((DWORD)this + offsets::player::m_vecOrigin);
	}
	Vector GetEyePosition()
	{
		return (GetOrigin() + GetViewOffset());
	}
	Vector GetVelocity()
	{
		return *(Vector*)((DWORD)this + offsets::player::m_vecVelocity);
	}
	QAngle GetPunchAngles()
	{
		return *(QAngle*)((DWORD)this + offsets::player::m_vecPunchAngle);
	}
	ULONG GetOwner()
	{
		return *(ULONG*)((DWORD)this + offsets::player::m_hOwner);
	}
	Vector& GetAbsOrigin()
	{
		__asm
		{
			MOV ECX, this
			MOV EAX, DWORD PTR DS : [ECX]
				CALL DWORD PTR DS : [EAX + 0x28]
		}
	}
	Vector GetAbsAngles()
	{
		__asm
		{
			MOV ECX, this;
			MOV EAX, DWORD PTR DS : [ECX]; Ge
				CALL DWORD PTR DS : [EAX + 0x2C]
		}
	}
	int GetIndex()
	{
		__asm
		{
			MOV EDI, this
			LEA ECX, DWORD PTR DS : [EDI + 0x8]
				MOV EDX, DWORD PTR DS : [ECX]
				CALL DWORD PTR DS : [EDX + 0x28]
		}
	}
	bool IsDormant()
	{
		__asm
		{
			MOV EDI, this
			LEA ECX, [EDI + 0x8]
				MOV EDX, DWORD PTR DS : [ecx]
				CALL[EDX + 0x24]
		}
	}
	bool SetupBones(matrix3x4* matrix, int maxbones, int mask, float time)
	{
		__asm
		{
			MOV EDI, this
			LEA ECX, DWORD PTR DS : [EDI + 0x4]
				MOV EDX, DWORD PTR DS : [ECX]
				PUSH time
				PUSH mask
				PUSH maxbones
				PUSH matrix
				CALL DWORD PTR DS : [EDX + 0x34]
		}
	}
	model_t* GetModel()
	{
		__asm
		{
			MOV EDI, this
			LEA ECX, [EDI + 0x4]
				MOV EDX, DWORD PTR DS : [ECX]
				CALL[EDX + 0x20]
		}
	}
	IVClientClass* GetClientClass()
	{
		void* pNetworkable = (void*)(this + 0x8);
		typedef IVClientClass* (__thiscall* original)(void*);
		return GetVirtualFunction<original>(pNetworkable, 2)(pNetworkable);
	}
	void GetRenderBounds(Vector& mins, Vector& maxs)
	{
		void* pRenderable = (void*)(this + 0x4);
		typedef void(__thiscall* original)(void*, Vector&, Vector&);
		GetVirtualFunction<original>(pRenderable, 17)(pRenderable, mins, maxs);
	}
};

//----------------------------------------
// WEAPON ENTITY CLASS
//----------------------------------------

class CBaseCombatWeapon : public CBaseEntity
{
private:
	DWORD dwBase;
public:
	int GetItemDefinitionIndex()
	{
		return *(int*)((DWORD)this + offsets::weapon::m_iItemDefinitionIndex);
	}
	int GetClip1()
	{
		return *(int*)((DWORD)this + offsets::weapon::m_iClip1);
	}
	float GetNextPrimaryAttack()
	{
		return *(float*)((DWORD)this + offsets::weapon::m_flNextPrimaryAttack);
	}
	const char* GetWeaponName()
	{
		switch (this->GetItemDefinitionIndex())
		{
		case ITEM_NONE:
			return "None"; break;
		case WEAPON_DEAGLE:
			return "Deagle"; break;
		case WEAPON_DUALS:
			return "Dualies"; break;
		case WEAPON_FIVE7:
			return "Five-Seven"; break;
		case WEAPON_GLOCK:
			return "Glock"; break;
		case WEAPON_AK47:
			return "AK-47"; break;
		case WEAPON_AUG:
			return "AUG"; break;
		case WEAPON_AWP:
			return "AWP"; break;
		case WEAPON_FAMAS:
			return "Famas"; break;
		case WEAPON_G3SG1:
			return "G3SG1"; break;
		case WEAPON_GALIL:
			return "Galil"; break;
		case WEAPON_M249:
			return "M249"; break;
		case WEAPON_M4A1:
			return "M4A4"; break;
		case WEAPON_MAC10:
			return "MAC-10"; break;
		case WEAPON_P90:
			return "P90"; break;
		case WEAPON_UMP45:
			return "UMP-45"; break;
		case WEAPON_XM1014:
			return "XM1014"; break;
		case WEAPON_BIZON:
			return "Bizon"; break;
		case WEAPON_MAG7:
			return "MAG-7"; break;
		case WEAPON_NEGEV:
			return "Negev"; break;
		case WEAPON_SAWEDOFF:
			return "Sawed-Off"; break;
		case WEAPON_TEC9:
			return "TEC-9"; break;
		case WEAPON_TASER:
			return "Zeus"; break;
		case WEAPON_P2000:
			return "P2000"; break;
		case WEAPON_MP7:
			return "MP7"; break;
		case WEAPON_MP9:
			return "MP9"; break;
		case WEAPON_NOVA:
			return "Nova"; break;
		case WEAPON_P250:
			return "P250"; break;
		case WEAPON_SCAR20:
			return "SCAR-20"; break;
		case WEAPON_SG553:
			return "SG-553"; break;
		case WEAPON_SCOUT:
			return "Scout"; break;
		case WEAPON_REVOLVER:
			return "Revolver"; break;
		case WEAPON_KNIFE_CT:
			return "Knife"; break;
		case WEAPON_KNIFE_T:
			return "Knife"; break;
		case WEAPON_KNIFE_GUT:
			return "Gut Knife"; break;
		case WEAPON_KNIFE_FLIP:
			return "Flip Knife"; break;
		case WEAPON_KNIFE_BAYONET:
			return "Bayonet"; break;
		case WEAPON_KNIFE_KARAMBIT:
			return "Karambit"; break;
		case WEAPON_KNIFE_M9BAYONET:
			return "M9 Bayonet"; break;
		case WEAPON_KNIFE_BUTTERFLY:
			return "Butterfly Knife"; break;
		case WEAPON_KNIFE_FALCHION:
			return "Falchion Knife"; break;
		case WEAPON_KNIFE_HUNTSMAN:
			return "Huntsman Knife"; break;
		case WEAPON_KNIFE_BOWIE:
			return "Bowie Knife"; break;
		case WEAPON_FLASH:
			return "Flashbang"; break;
		case WEAPON_HE:
			return "HE Grenade"; break;
		case WEAPON_SMOKE:
			return "Smoke"; break;
		case WEAPON_MOLOTOV:
			return "Molotov"; break;
		case WEAPON_DECOY:
			return "Decoy"; break;
		case WEAPON_INC:
			return "Inc Grenade"; break;
		case WEAPON_M4A1S:
			return "M4A1-S"; break;
		case WEAPON_USPS:
			return "USP-S"; break;
		case WEAPON_CZ75:
			return "CZ-75"; break;
		case WEAPON_C4:
			return "C4"; break;
		}

		return "";
	}
	bool IsPistol()
	{
		switch (this->GetItemDefinitionIndex())
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
	bool IsKnife()
	{
		switch (this->GetItemDefinitionIndex())
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
	bool IsOther()
	{
		switch (this->GetItemDefinitionIndex())
		{
		case ITEM_NONE:
			return true;
		case WEAPON_TASER:
			return true;
		case WEAPON_FLASH:
			return true;
		case WEAPON_HE:
			return true;
		case WEAPON_SMOKE:
			return true;
		case WEAPON_MOLOTOV:
			return true;
		case WEAPON_DECOY:
			return true;
		case WEAPON_INC:
			return true;
		case WEAPON_C4:
			return true;
		default:
			return false;
		}
	}
	void SetPattern(player_info_t info, int skin, float wear, int seed, int stattrak, const char* name = "")
	{
		if (this->IsOther())
			return;

		*(int*)((DWORD)this + offsets::weapon::m_OriginalOwnerXuidLow) = 0;
		*(int*)((DWORD)this + offsets::weapon::m_OriginalOwnerXuidHigh) = 0;
		*(int*)((DWORD)this + offsets::weapon::m_nFallbackSeed) = seed;
		*(int*)((DWORD)this + offsets::weapon::m_nFallbackPaintKit) = skin;
		*(float*)((DWORD)this + offsets::weapon::m_flFallbackWear) = wear;
		*(int*)((DWORD)this + offsets::weapon::m_iAccountID) = info.m_nXuidLow;
		*(int*)((DWORD)this + offsets::weapon::m_iItemIDHigh) = 1;

		if (stattrak > 0)
			*(int*)((DWORD)this + offsets::weapon::m_nFallbackStatTrak) = stattrak;

		if (stattrak > 0 && !this->IsKnife())
			*(int*)((DWORD)this + offsets::weapon::m_iEntityQuality) = 1;
		else if (this->IsKnife())
			*(int*)((DWORD)this + offsets::weapon::m_iEntityQuality) = 3;
		else
			*(int*)((DWORD)this + offsets::weapon::m_iEntityQuality) = 4;

		if (name)
			sprintf_s((char*)this + offsets::weapon::m_szCustomName, 32, "%s", name);
	}
};

//----------------------------------------
// CLIENT INTERFACE
//----------------------------------------

class CHLClient
{
public:
	IVClientClass* GetAllClasses()
	{
		typedef IVClientClass* (__thiscall* original)(void*);
		return GetVirtualFunction<original>(this, 8)(this);
	}
};

//----------------------------------------
// CLIENTCLASS INTERFACE
//----------------------------------------

class IVClientClass
{
public:
	const char* GetName()
	{
		return *(char**)(this + 0x8);
	}
	RecvTable* GetTable()
	{
		return *(RecvTable**)(this + 0xC);
	}
	IVClientClass* NextClass()
	{
		return *(IVClientClass**)(this + 0x10);
	}
	int GetClassID()
	{
		return *(int*)(this + 0x14);
	}
};

//----------------------------------------
// CLIENT ENTITY LIST INTERFACE
//----------------------------------------

class IClientEntityList
{
public:
	CBaseEntity* GetClientEntity(int entnum)
	{
		typedef CBaseEntity* (__thiscall* original)(void*, int);
		return GetVirtualFunction<original>(this, 3)(this, entnum);
	}
	CBaseEntity* GetClientEntityFromHandle(int hEnt)
	{
		typedef CBaseEntity* (__thiscall* original)(void*, int);
		return GetVirtualFunction<original>(this, 4)(this, hEnt);
	}
	int GetHighestEntityIndex()
	{
		typedef int(__thiscall* original)(void*);
		return GetVirtualFunction<original>(this, 6)(this);
	}
};

//----------------------------------------
// PANEL INTERFACE
//----------------------------------------

class IPanel
{
public:
	const char* GetName(unsigned int vguiPanel)
	{
		typedef const char*(__thiscall* original)(void*, unsigned int);
		return GetVirtualFunction<original>(this, 36)(this, vguiPanel);
	}
};

//----------------------------------------
// SURFACE INTERFACE
//----------------------------------------

class ISurface
{
public:
	void DrawSetColor(int r, int g, int b, int a)
	{
		typedef void(__thiscall* original)(void*, int, int, int, int);
		GetVirtualFunction<original>(this, 15)(this, r, g, b, a);
	}
	void DrawFilledRect(int x0, int y0, int x1, int y1)
	{
		typedef void(__thiscall* original)(void*, int, int, int, int);
		GetVirtualFunction<original>(this, 16)(this, x0, y0, x1, y1);
	}
	void DrawOutlinedRect(int x0, int y0, int x1, int y1)
	{
		typedef void(__thiscall* original)(void*, int x0, int y0, int x1, int y1);
		GetVirtualFunction<original>(this, 18)(this, x0, y0, x1, y1);
	}
	void DrawLine(int x0, int y0, int x1, int y1)
	{
		typedef void(__thiscall* original)(void*, int, int, int, int);
		GetVirtualFunction<original>(this, 19)(this, x0, y0, x1, y1);
	}
	void DrawSetTextFont(unsigned long font)
	{
		typedef void(__thiscall* original)(void*, unsigned long);
		GetVirtualFunction<original>(this, 23)(this, font);
	}
	void DrawSetTextColor(int r, int g, int b, int a)
	{
		typedef void(__thiscall* original)(void*, int, int, int, int);
		GetVirtualFunction<original>(this, 25)(this, r, g, b, a);
	}
	void DrawSetTextPos(int x, int y)
	{
		typedef void(__thiscall* original)(void*, int, int);
		GetVirtualFunction<original>(this, 26)(this, x, y);
	}
	void DrawPrintText(const wchar_t* text, int textLen)
	{
		typedef void(__thiscall* original)(void*, const wchar_t *, int, int);
		GetVirtualFunction<original>(this, 28)(this, text, textLen, 0);
	}
	unsigned long CreateFont()
	{
		typedef unsigned int(__thiscall* original)(void*);
		return GetVirtualFunction<original>(this, 71)(this);
	}
	void SetFontGlyphSet(unsigned long& font, const char* windowsFontName, int tall, int weight, int blur, int scanlines, int flags)
	{
		typedef void(__thiscall* original)(void*, unsigned long, const char*, int, int, int, int, int, int, int);
		GetVirtualFunction<original>(this, 72)(this, font, windowsFontName, tall, weight, blur, scanlines, flags, 0, 0);
	}
	bool AddCustomFontFile(const char* fontName)
	{
		typedef bool(__thiscall* original)(void*, const char*);
		return GetVirtualFunction<original>(this, 73)(this, fontName);
	}
	void GetTextSize(unsigned long font, const wchar_t *text, int &wide, int &tall)
	{
		typedef void(__thiscall* original)(void*, unsigned long font, const wchar_t *text, int &wide, int &tall);
		GetVirtualFunction<original>(this, 79)(this, font, text, wide, tall);
	}
	void GetCursorPos(int& x, int& y)
	{
		typedef void(__thiscall* original)(void*, int &, int &);
		GetVirtualFunction<original>(this, 100)(this, x, y);
	}
	void SetCursorPos(int x, int y)
	{
		typedef void(__thiscall* original)(void*, int, int);
		GetVirtualFunction<original>(this, 101)(this, x, y);
	}
	const char* GetFontName(unsigned long font)
	{
		typedef const char*(__thiscall* original)(void*, unsigned long);
		return GetVirtualFunction<original>(this, 134)(this, font);
	}
};

//----------------------------------------
// DEBUG OVERLAY INTERFACE
//----------------------------------------

class IVDebugOverlay
{
public:
	void AddBoxOverlay(const Vector& origin, const Vector& mins, const Vector& max, Vector const& orientation, int r, int g, int b, int a, float duration)
	{
		typedef void(__thiscall* original)(void*, const Vector&, const Vector&, const Vector&, Vector const&, int, int, int, int, float);
		GetVirtualFunction<original>(this, 3)(this, origin, mins, max, orientation, r, g, b, a, duration);
	}
	void AddLineOverlay(const Vector& origin, const Vector& dest, int r, int g, int b, bool noDepthTest, float duration)
	{
		typedef void(__thiscall* original)(void*, const Vector& origin, const Vector& dest, int r, int g, int b, bool noDepthTest, float duration);
		GetVirtualFunction<original>(this, 5)(this, origin, dest, r, g, b, noDepthTest, duration);
	}
	void AddSweptBoxOverlay(const Vector& origin, const Vector& end, const Vector& mins, const Vector& max, Vector const& orientation, int r, int g, int b, int a, float duration)
	{
		typedef void(__thiscall* original)(void*, const Vector&, const Vector&, const Vector&, const Vector&, Vector const&, int, int, int, int, float);
		GetVirtualFunction<original>(this, 9)(this, origin, end, mins, max, orientation, r, g, b, a, duration);
	}
	bool ScreenPosition(const Vector& vIn, Vector& vOut)
	{
		typedef bool(__thiscall* original)(void*, const Vector&, Vector&);
		return GetVirtualFunction<original>(this, 13)(this, vIn, vOut);
	}
};

//----------------------------------------
// ENGINE CLIENT INTERFACE
//----------------------------------------

class IEngineClient
{
public:
	bool GetPlayerInfo(int iIndex, player_info_t* pInfo)
	{
		typedef bool(__thiscall* original)(void*, int, player_info_t*);
		return GetVirtualFunction<original>(this, 8)(this, iIndex, pInfo);
	}
	int GetLocalPlayer()
	{
		typedef int(__thiscall* original)(void*);
		return GetVirtualFunction<original>(this, 12)(this);
	}
	float GetLastTimeStamp()
	{
		typedef float(__thiscall* original)(void*);
		return GetVirtualFunction<original>(this, 14)(this);
	}
	void GetViewAngles(QAngle& angles)
	{
		typedef void(__thiscall* original)(void*, QAngle&);
		GetVirtualFunction< original >(this, 18)(this, angles);
	}
	void SetViewAngles(QAngle& angles)
	{
		typedef void(__thiscall* original)(void*, QAngle&);
		GetVirtualFunction<original>(this, 19)(this, angles);
	}
	int GetMaxClients()
	{
		typedef int(__thiscall* original)(void*);
		return GetVirtualFunction<original>(this, 20)(this);
	}
	bool InGame()
	{
		typedef bool(__thiscall* original)(void*);
		return GetVirtualFunction<original>(this, 26)(this);
	}
	bool IsConnected()
	{
		typedef bool(__thiscall* original)(void*);
		return GetVirtualFunction<original>(this, 27)(this);
	}
	void ExecuteClientCmd(const char* command)
	{
		typedef void(__thiscall* original)(void*, const char*);
		GetVirtualFunction<original>(this, 108)(this, command);
	}
	void ClientCmd_Unrestricted(const char* command)
	{
		typedef void(__thiscall* original)(void*, const char *);
		GetVirtualFunction<original>(this, 114)(this, command);
	}
};

//----------------------------------------
// INPUT INTERFACE
//----------------------------------------

class CInput
{
public:
	class CUserCmd
	{
	public:
		CRC32_t GetChecksum() const
		{
			CRC32_t crc;
			CRC32_Init(&crc);
			CRC32_ProcessBuffer(&crc, &command_number, sizeof(command_number));
			CRC32_ProcessBuffer(&crc, &tick_count, sizeof(tick_count));
			CRC32_ProcessBuffer(&crc, &viewangles, sizeof(viewangles));
			CRC32_ProcessBuffer(&crc, &aimdirection, sizeof(aimdirection));
			CRC32_ProcessBuffer(&crc, &forwardmove, sizeof(forwardmove));
			CRC32_ProcessBuffer(&crc, &sidemove, sizeof(sidemove));
			CRC32_ProcessBuffer(&crc, &upmove, sizeof(upmove));
			CRC32_ProcessBuffer(&crc, &buttons, sizeof(buttons));
			CRC32_ProcessBuffer(&crc, &impulse, sizeof(impulse));
			CRC32_ProcessBuffer(&crc, &weaponselect, sizeof(weaponselect));
			CRC32_ProcessBuffer(&crc, &weaponsubtype, sizeof(weaponsubtype));
			CRC32_ProcessBuffer(&crc, &random_seed, sizeof(random_seed));
			CRC32_ProcessBuffer(&crc, &mousedx, sizeof(mousedx));
			CRC32_ProcessBuffer(&crc, &mousedy, sizeof(mousedy));
			CRC32_Final(&crc);
			return crc;
		}

		BYTE		u1[4];
		int			command_number;
		int			tick_count;
		QAngle		viewangles;
		Vector		aimdirection;
		float		forwardmove;
		float		sidemove;
		float		upmove;
		int			buttons;
		BYTE		impulse;
		int			weaponselect;
		int			weaponsubtype;
		int			random_seed;
		short		mousedx;
		short		mousedy;
		bool		hasbeenpredicted;
		Vector		headangles;
		Vector		headoffset;
	};

	class CVerifiedUserCmd
	{
	public:
		CUserCmd		m_cmd;
		unsigned long	m_crc;
	};

	CUserCmd* GetUserCmd(int slot, int seq)
	{
		typedef CUserCmd* (__thiscall* original)(void*, int, int);
		return GetVirtualFunction<original>(this, 8)(this, slot, seq);
	}
};

//----------------------------------------
// ENGINE TRACE INTERFACE
//----------------------------------------

class IEngineTrace
{
public:
	enum TraceType_t
	{
		TRACE_EVERYTHING = 0,
		TRACE_WORLD_ONLY,				// NOTE: This does *not* test static props!!!
		TRACE_ENTITIES_ONLY,			// NOTE: This version will *not* test static props
		TRACE_EVERYTHING_FILTER_PROPS,	// NOTE: This version will pass the IHandleEntity for props through the filter, unlike all other filters
	};

	struct cplane_t
	{
		Vector normal;
		float dist;
		BYTE type;
		BYTE signBits;
		BYTE pad[2];
	};

	struct csurface_t
	{
		const char*		name;
		short			surfaceProps;
		unsigned short	flags;
	};

	struct Ray_t
	{
		VectorAligned	 m_start;	// starting point, centered within the extents
		VectorAligned	 m_delta;	// direction + length of the ray
		VectorAligned	 m_startOffset;	// Add this to m_Start to get the actual ray start
		VectorAligned	 m_extents;	// Describes an axis aligned box extruded along a ray
		const matrix3x4* m_worldAxisTransform;
		bool			 m_isRay;	// are the extents zero?
		bool			 m_isSwept;	// is delta != 0?

		Ray_t() : m_worldAxisTransform(0) {}

		void Init(Vector const& start, Vector const& end)
		{
			(&end);
			VectorSubtract(end, start, m_delta);

			m_isSwept = (m_delta.LengthSqr() != 0);

			VectorClear(m_extents);
			m_worldAxisTransform = 0;
			m_isRay = true;

			VectorClear(m_startOffset);
			VectorCopy(start, m_start);
		}
		void Init(Vector const& start, Vector const& end, Vector const& mins, Vector const& maxs)
		{
			(&end);
			VectorSubtract(end, start, m_delta); //wait

			m_worldAxisTransform = 0;
			m_isSwept = (m_delta.LengthSqr() != 0);

			VectorSubtract(maxs, mins, m_extents);
			m_extents *= 0.5f;
			m_isRay = (m_extents.LengthSqr() < 1e-6);

			VectorAdd(mins, maxs, m_startOffset);
			m_startOffset *= 0.5f;
			VectorAdd(start, m_startOffset, m_start);
			m_startOffset *= -1.f;
		}
		Vector InvDelta() const
		{
			Vector invDelta;

			for (int i = 0; i < 3; ++i)
			{
				if (m_delta[i] != 0.f)
					invDelta[i] = 1.f / m_delta[i];
				else
					invDelta[i] = FLT_MAX;
			}

			return invDelta;
		}
	};

	struct trace_t
	{
		Vector		 start;
		Vector		 endpos;
		cplane_t	 plane;
		float		 fraction;
		int			 contents;
		WORD		 dispFlags;
		bool		 allSolid;
		bool		 startSolid;
		float		 fractionLeftSolid;
		csurface_t	 surface;
		int			 hitgroup;
		short		 physicsBone;
		WORD		 worldSurfaceIndex;
		CBaseEntity* entity;
		int			 hitbox;

		bool DidHitWorld(IClientEntityList* entitylist)
		{
			return entity == (CBaseEntity*)entitylist->GetClientEntity(0);
		}
		bool DidHitNonWorldEntity(IClientEntityList* entitylist)
		{
			return entity != 0 && !DidHitWorld(entitylist);
		}
		bool DidHit() const
		{
			return fraction < 1.f || allSolid || startSolid;
		}
	};

	class ITraceFilter
	{
	public:
		virtual bool ShouldHitEntity(CBaseEntity* entity, int contentsMask) = 0;
		virtual TraceType_t GetTraceType() const = 0;
	};

	class CTraceFilter : public ITraceFilter
	{
	public:
		bool ShouldHitEntity(CBaseEntity* entityHandle, int contentsMask)
		{
			return !(entityHandle == skip);
		}
		virtual TraceType_t GetTraceType() const
		{
			return TRACE_EVERYTHING;
		}

		void* skip;
	};

	class CTraceFilterSkipTwoEntities : public ITraceFilter
	{
	public:
		CTraceFilterSkipTwoEntities(void* passEntity1, void* passEntity2)
		{
			passentity1 = passEntity1;
			passentity2 = passEntity2;
		}
		virtual bool ShouldHitEntity(CBaseEntity* entityHandle, int contentsMask)
		{
			return !(entityHandle == passentity1 || entityHandle == passentity2);
		}
		virtual TraceType_t GetTraceType() const
		{
			return TRACE_EVERYTHING;
		}

		void* passentity1;
		void* passentity2;
	};

public:
	void TraceRay(const Ray_t& ray, unsigned int mask, CTraceFilter* filter, trace_t* trace)
	{
		typedef void(__thiscall* original)(void*, const Ray_t&, unsigned int, CTraceFilter*, trace_t*);
		GetVirtualFunction<original>(this, 5)(this, ray, mask, filter, trace);
	}
	void ClipRayToEntity(const Ray_t& ray, unsigned int mask, CBaseEntity* entity, trace_t* trace)
	{
		typedef void(__thiscall* original)(void*, const Ray_t&, unsigned int, CBaseEntity*, trace_t*);
		GetVirtualFunction<original>(this, 3)(this, ray, mask, entity, trace);
	}
	int GetPointContents(const Vector& absPosition, unsigned int mask, CBaseEntity** entity = 0)
	{
		typedef int(__thiscall* original)(void*, const Vector&, unsigned int, CBaseEntity**);
		return GetVirtualFunction<original>(this, 0)(this, absPosition, mask, entity);
	}
};

//----------------------------------------
// GLOBAL VARIABLES
//----------------------------------------

class CGlobalVars
{
public:
	float     realtime;
	int       framecount;
	float     absoluteframetime;
	float     unknown;
	float     curtime;
	float     frametime;
	int       maxclients;
	int       tickcount;
	float     interval_per_tick;
	float     interpolation_amount;
};

//----------------------------------------
// MDL CACHE INTERFACE
//----------------------------------------

class IMDLCache
{
public:
};

//----------------------------------------
// MATERIAL INTERFACE
//----------------------------------------

class IMaterial
{
public:
};

//----------------------------------------
// MODEL INFO INTERFACE
//----------------------------------------

class IVModelInfo
{
public:
	int GetModelIndex(const char* modelName)
	{
		typedef int(__thiscall* original)(void*, const char*);
		return GetVirtualFunction<original>(this, 2)(this, modelName);
	}
	const char* GetModelName(const model_t* pModel)
	{
		typedef const char* (__thiscall* original)(void*, const model_t*);
		return GetVirtualFunction<original>(this, 3)(this, pModel);
	}
	int GetInt(const char* keyName, int defaultValue = 0)
	{
		typedef int(__thiscall* original)(void*, const char*, int);
		return GetVirtualFunction<original>(this, 6)(this, keyName, defaultValue);
	}
	void GetModelMaterials(const model_t* model, int count, IMaterial** ppMaterial)
	{
		typedef void(__thiscall* original)(void*, const model_t*, int, IMaterial**);
		return GetVirtualFunction< original >(this, 17)(this, model, count, ppMaterial);
	}
	studiohdr_t* GetStudioModel(const model_t* model)
	{
		typedef studiohdr_t* (__thiscall* original)(void*, const model_t*);
		return GetVirtualFunction<original>(this, 30)(this, model);
	}
};

//----------------------------------------
// TOOLS CLASS
//----------------------------------------

class Tools
{
public:
	void*              getInterface(std::string moduleName, std::string interfaceName);
	DWORD_PTR          getPatternOffset(std::string moduleName, PBYTE pattern, std::string mask, DWORD_PTR codeBase = NULL, DWORD_PTR codeSize = NULL);

	bool               isVisible(Vector& start, Vector& end, CBaseEntity* entity);
	CBaseCombatWeapon* getActiveWeapon(CBaseEntity* entity);
	bool               WorldToScreen(Vector& world, Vector& screen);

	void               VectorTransform(const Vector& in1, const matrix3x4& in2, Vector& out);
	void               sinCos(float radians, float* sine, float* cosine);

	void               angleVectors(const Vector angles, Vector& forward);

	bool               getHitboxPosition(int hitbox, Vector& origin, CBaseEntity* entity);
	Vector             getPredictedPosition(Vector src, Vector velocity);
	float              getDistance(Vector origin, Vector other);
	float              getFov(QAngle viewAngles, QAngle aimAngles);

	void               computeAngle(Vector source, Vector dest, QAngle& angles);
	QAngle             computeAngle(Vector source, Vector dest);
	void               normalizeAngles(QAngle& angles);
	void               clampAngles(QAngle& angles);

	bool               isAbleToShoot(CBaseEntity* entity, CBaseCombatWeapon* weapon);
	bool               isNotAbleToShoot(CBaseEntity* entity, CBaseCombatWeapon* weapon);

	int                random(int min, int max);
	float              random(float min, float max);
}; extern Tools tools;

#endif