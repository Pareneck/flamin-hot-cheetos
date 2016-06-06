#ifndef SDK_H
#define SDK_H

#ifdef CreateFont
#undef CreateFont
#endif

#pragma once

#include "Main.h"
#include "dt_recv.h"
#include "checksum_crc.h"
#include "SDKDefinitions.h"

//----------------------------------------
// TYPEDEFS
//----------------------------------------

typedef float matrix3x4[3][4];
typedef float matrix4x4[4][4];

//----------------------------------------
// FORWARD DECLARATIONS
//----------------------------------------

class CBaseEntity;
class CBaseCombatWeapon;
class CInput;
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
	char GetLifeState(void)
	{
		return *(char*)((DWORD)this + 0x25B);
	}
	int GetHealth(void)
	{
		return *(int*)((DWORD)this + 0xFC);
	}
	int GetTeamNum(void)
	{
		return *(int*)((DWORD)this + 0xF0);
	}
	bool IsProtected(void)
	{
		return *(bool*)((DWORD)this + 0x38A0);
	}
	int GetFlags(void)
	{
		return *(int*)((DWORD)this + 0x100);
	}
	const char* GetLastPlaceName(void)
	{
		return (char*)((DWORD)this + 0x3598);
	}
	Vector GetViewOffset(void)
	{
		return *(Vector*)((DWORD)this + 0x104);
	}
	Vector GetOrigin(void)
	{
		return *(Vector*)((DWORD)this + 0x134);
	}
	Vector GetEyePosition(void)
	{
		return (this->GetOrigin() + this->GetViewOffset());
	}
	Vector& GetAbsOrigin(void)
	{
		__asm
		{
			MOV ECX, this
			MOV EAX, DWORD PTR DS : [ECX]
				CALL DWORD PTR DS : [EAX + 0x28]
		}
	}
	int GetIndex(void)
	{
		__asm
		{
			MOV EDI, this
			LEA ECX, DWORD PTR DS : [EDI + 0x8]
				MOV EDX, DWORD PTR DS : [ECX]
				CALL DWORD PTR DS : [EDX + 0x28]
		}
	}
	bool IsDormant(void)
	{
		__asm
		{
			MOV EDI, this
			LEA ECX, [EDI + 0x8]
				MOV EDX, DWORD PTR DS : [ecx]
				CALL[EDX + 0x24]
		}
	}
	IVClientClass* GetClientClass(void)
	{
		void* pNetworkable = (void*)(this + 0x8);
		typedef IVClientClass* (__thiscall* fnOriginal)(void*);
		return GetVirtualFunction<fnOriginal>(pNetworkable, 2)(pNetworkable);
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
	int GetItemDefinitionIndex(void)
	{
		return *(int*)((DWORD)this + 0x2F88);
	}
	int GetClip1(void)
	{
		return *(int*)((DWORD)this + 0x31F4);
	}
	const char* GetWeaponName(void)
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
	bool IsKnife(void)
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
	bool IsOther(void)
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
};

//----------------------------------------
// CLIENT INTERFACE
//----------------------------------------

class CHLClient
{
public:
	IVClientClass* GetAllClasses(void)
	{
		typedef IVClientClass* (__thiscall* fnOriginal)(void*);
		return GetVirtualFunction<fnOriginal>(this, 8)(this);
	}
}; extern CHLClient* g_pClient;

//----------------------------------------
// CLIENTCLASS INTERFACE
//----------------------------------------

class IVClientClass
{
public:
	const char* GetName(void)
	{
		return *(char**)(this + 0x8);
	}
	RecvTable* GetTable(void)
	{
		return *(RecvTable**)(this + 0xC);
	}
	IVClientClass* NextClass(void)
	{
		return *(IVClientClass**)(this + 0x10);
	}
	int GetClassID(void)
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
		typedef CBaseEntity* (__thiscall* fnOriginal)(void*, int);
		return GetVirtualFunction<fnOriginal>(this, 3)(this, entnum);
	}
	CBaseEntity* GetClientEntityFromHandle(int hEnt)
	{
		typedef CBaseEntity* (__thiscall* fnOriginal)(void*, int);
		return GetVirtualFunction<fnOriginal>(this, 4)(this, hEnt);
	}
	int GetHighestEntityIndex(void)
	{
		typedef int(__thiscall* fnOriginal)(void*);
		return GetVirtualFunction<fnOriginal>(this, 6)(this);
	}
}; extern IClientEntityList* g_pEntityList;

//----------------------------------------
// PANEL INTERFACE
//----------------------------------------

class IPanel
{
public:
	const char* GetName(unsigned int vguiPanel)
	{
		typedef const char*(__thiscall* fnOriginal)(void*, unsigned int);
		return GetVirtualFunction<fnOriginal>(this, 36)(this, vguiPanel);
	}
}; extern IPanel* g_pPanel;

//----------------------------------------
// SURFACE INTERFACE
//----------------------------------------

class ISurface
{
public:
	void DrawSetColor(int r, int g, int b, int a)
	{
		typedef void(__thiscall* fnOriginal)(void*, int, int, int, int);
		GetVirtualFunction<fnOriginal>(this, 15)(this, r, g, b, a);
	}
	void DrawFilledRect(int x0, int y0, int x1, int y1)
	{
		typedef void(__thiscall* fnOriginal)(void*, int, int, int, int);
		GetVirtualFunction<fnOriginal>(this, 16)(this, x0, y0, x1, y1);
	}
	void DrawOutlinedRect(int x0, int y0, int x1, int y1)
	{
		typedef void(__thiscall* fnOriginal)(void*, int x0, int y0, int x1, int y1);
		GetVirtualFunction<fnOriginal>(this, 18)(this, x0, y0, x1, y1);
	}
	void DrawLine(int x0, int y0, int x1, int y1)
	{
		typedef void(__thiscall* fnOriginal)(void*, int, int, int, int);
		GetVirtualFunction<fnOriginal>(this, 19)(this, x0, y0, x1, y1);
	}
	void DrawSetTextFont(unsigned long font)
	{
		typedef void(__thiscall* fnOriginal)(void*, unsigned long);
		GetVirtualFunction<fnOriginal>(this, 23)(this, font);
	}
	void DrawSetTextColor(int r, int g, int b, int a)
	{
		typedef void(__thiscall* fnOriginal)(void*, int, int, int, int);
		GetVirtualFunction<fnOriginal>(this, 25)(this, r, g, b, a);
	}
	void DrawSetTextPos(int x, int y)
	{
		typedef void(__thiscall* fnOriginal)(void*, int, int);
		GetVirtualFunction<fnOriginal>(this, 26)(this, x, y);
	}
	void DrawPrintText(const wchar_t* text, int textLen)
	{
		typedef void(__thiscall* fnOriginal)(void*, const wchar_t *, int, int);
		GetVirtualFunction<fnOriginal>(this, 28)(this, text, textLen, 0);
	}
	unsigned long CreateFont()
	{
		typedef unsigned int(__thiscall* fnOriginal)(void*);
		return GetVirtualFunction<fnOriginal>(this, 71)(this);
	}
	void SetFontGlyphSet(unsigned long& font, const char* windowsFontName, int tall, int weight, int blur, int scanlines, int flags)
	{
		typedef void(__thiscall* fnOriginal)(void*, unsigned long, const char*, int, int, int, int, int, int, int);
		GetVirtualFunction<fnOriginal>(this, 72)(this, font, windowsFontName, tall, weight, blur, scanlines, flags, 0, 0);
	}
	bool AddCustomFontFile(const char* fontName)
	{
		typedef bool(__thiscall* fnOriginal)(void*, const char*);
		return GetVirtualFunction<fnOriginal>(this, 73)(this, fontName);
	}
	void GetTextSize(unsigned long font, const wchar_t *text, int &wide, int &tall)
	{
		typedef void(__thiscall* fnOriginal)(void*, unsigned long font, const wchar_t *text, int &wide, int &tall);
		GetVirtualFunction<fnOriginal>(this, 79)(this, font, text, wide, tall);
	}
	void GetCursorPos(int& x, int& y)
	{
		typedef void(__thiscall* fnOriginal)(void*, int &, int &);
		GetVirtualFunction<fnOriginal>(this, 100)(this, x, y);
	}
	void SetCursorPos(int x, int y)
	{
		typedef void(__thiscall* fnOriginal)(void*, int, int);
		GetVirtualFunction<fnOriginal>(this, 101)(this, x, y);
	}
	const char* GetFontName(unsigned long font)
	{
		typedef const char*(__thiscall* fnOriginal)(void*, unsigned long);
		return GetVirtualFunction<fnOriginal>(this, 134)(this, font);
	}
}; extern ISurface* g_pSurface;

//----------------------------------------
// DEBUG OVERLAY INTERFACE
//----------------------------------------

class IVDebugOverlay
{
public:
	void AddBoxOverlay(const Vector& origin, const Vector& mins, const Vector& max, Vector const& orientation, int r, int g, int b, int a, float duration)
	{
		typedef void(__thiscall* fnOriginal)(void*, const Vector&, const Vector&, const Vector&, Vector const&, int, int, int, int, float);
		GetVirtualFunction<fnOriginal>(this, 3)(this, origin, mins, max, orientation, r, g, b, a, duration);
	}
	void AddLineOverlay(const Vector& origin, const Vector& dest, int r, int g, int b, bool noDepthTest, float duration)
	{
		typedef void(__thiscall* fnOriginal)(void*, const Vector& origin, const Vector& dest, int r, int g, int b, bool noDepthTest, float duration);
		GetVirtualFunction<fnOriginal>(this, 5)(this, origin, dest, r, g, b, noDepthTest, duration);
	}
	void AddSweptBoxOverlay(const Vector& origin, const Vector& end, const Vector& mins, const Vector& max, Vector const& orientation, int r, int g, int b, int a, float duration)
	{
		typedef void(__thiscall* fnOriginal)(void*, const Vector&, const Vector&, const Vector&, const Vector&, Vector const&, int, int, int, int, float);
		GetVirtualFunction<fnOriginal>(this, 9)(this, origin, end, mins, max, orientation, r, g, b, a, duration);
	}
	bool ScreenPosition(const Vector& vIn, Vector& vOut)
	{
		typedef bool(__thiscall* fnOriginal)(void*, const Vector&, Vector&);
		return GetVirtualFunction<fnOriginal>(this, 13)(this, vIn, vOut);
	}
}; extern IVDebugOverlay* g_pDebugOverlay;

//----------------------------------------
// ENGINE CLIENT INTERFACE
//----------------------------------------

class IEngineClient
{
public:
	bool GetPlayerInfo(int iIndex, player_info_t* pInfo)
	{
		typedef bool(__thiscall* fnOriginal)(void*, int, player_info_t*);
		return GetVirtualFunction<fnOriginal>(this, 8)(this, iIndex, pInfo);
	}
	int GetLocalPlayer(void)
	{
		typedef int(__thiscall* fnOriginal)(void*);
		return GetVirtualFunction<fnOriginal>(this, 12)(this);
	}
	int GetMaxClients(void)
	{
		typedef int(__thiscall* fnOriginal)(void*);
		return GetVirtualFunction<fnOriginal>(this, 20)(this);
	}
	bool InGame(void)
	{
		typedef bool(__thiscall* fnOriginal)(void*);
		return GetVirtualFunction<fnOriginal>(this, 26)(this);
	}
	bool IsConnected(void)
	{
		typedef bool(__thiscall* fnOriginal)(void*);
		return GetVirtualFunction<fnOriginal>(this, 27)(this);
	}
	void ExecuteClientCmd(char const* pszCommand)
	{
		typedef void(__thiscall* fnOriginal)(void*, char const*);
		GetVirtualFunction<fnOriginal>(this, 108)(this, pszCommand);
	}
}; extern IEngineClient* g_pEngine;

//----------------------------------------
// INPUT INTERFACE
//----------------------------------------

class CInput
{
public:
	class CUserCmd
	{
	public:
		CRC32_t GetChecksum(void) const
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
		Vector		viewangles;
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
		typedef CUserCmd* (__thiscall* fnOriginal)(void*, int, int);
		return GetVirtualFunction<fnOriginal>(this, 8)(this, slot, seq);
	}
}; extern CInput* g_pInput;

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
		VectorAligned	 m_Start;	// starting point, centered within the extents
		VectorAligned	 m_Delta;	// direction + length of the ray
		VectorAligned	 m_StartOffset;	// Add this to m_Start to get the actual ray start
		VectorAligned	 m_Extents;	// Describes an axis aligned box extruded along a ray
		const matrix3x4* m_pWorldAxisTransform;
		bool			 m_IsRay;	// are the extents zero?
		bool			 m_IsSwept;	// is delta != 0?

		Ray_t() : m_pWorldAxisTransform(NULL) {}

		void Init(Vector const& start, Vector const& end)
		{
			Assert(&end);
			VectorSubtract(end, start, m_Delta);

			m_IsSwept = (m_Delta.LengthSqr() != 0);

			VectorClear(m_Extents);
			m_pWorldAxisTransform = NULL;
			m_IsRay = true;

			VectorClear(m_StartOffset);
			VectorCopy(start, m_Start);
		}
		void Init(Vector const& start, Vector const& end, Vector const& mins, Vector const& maxs)
		{
			Assert(&end);
			VectorSubtract(end, start, m_Delta); //wait

			m_pWorldAxisTransform = NULL;
			m_IsSwept = (m_Delta.LengthSqr() != 0);

			VectorSubtract(maxs, mins, m_Extents);
			m_Extents *= 0.5f;
			m_IsRay = (m_Extents.LengthSqr() < 1e-6);

			VectorAdd(mins, maxs, m_StartOffset);
			m_StartOffset *= 0.5f;
			VectorAdd(start, m_StartOffset, m_Start);
			m_StartOffset *= -1.f;
		}
		Vector InvDelta() const
		{
			Vector vecInvDelta;

			for (int iAxis = 0; iAxis < 3; ++iAxis)
			{
				if (m_Delta[iAxis] != 0.f)
					vecInvDelta[iAxis] = 1.f / m_Delta[iAxis];
				else
					vecInvDelta[iAxis] = FLT_MAX;
			}

			return vecInvDelta;
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
		WORD		 nWorldSurfaceIndex;
		CBaseEntity* pEntity;
		int			 hitbox;

		bool DidHitWorld(IClientEntityList* EntList)
		{
			return pEntity == (CBaseEntity*)EntList->GetClientEntity(0);
		}
		bool DidHitNonWorldEntity(IClientEntityList* EntList)
		{
			return pEntity != NULL && !DidHitWorld(EntList);
		}
		bool DidHit() const
		{
			return fraction < 1.f || allSolid || startSolid;
		}
	};

	class ITraceFilter
	{
	public:
		virtual bool ShouldHitEntity(CBaseEntity *pEntity, int contentsMask) = 0;
		virtual TraceType_t GetTraceType() const = 0;
	};

	class CTraceFilter : public ITraceFilter
	{
	public:
		bool ShouldHitEntity(CBaseEntity* pEntityHandle, int contentsMask)
		{
			return !(pEntityHandle == pSkip);
		}
		virtual TraceType_t GetTraceType() const
		{
			return TRACE_EVERYTHING;
		}

		void* pSkip;
	};

	class CTraceFilterSkipTwoEntities : public ITraceFilter
	{
	public:
		CTraceFilterSkipTwoEntities(void *pPassEnt1, void *pPassEnt2)
		{
			passentity1 = pPassEnt1;
			passentity2 = pPassEnt2;
		}
		virtual bool ShouldHitEntity(CBaseEntity* pEntityHandle, int contentsMask)
		{
			return !(pEntityHandle == passentity1 || pEntityHandle == passentity2);
		}
		virtual TraceType_t GetTraceType() const
		{
			return TRACE_EVERYTHING;
		}

		void *passentity1;
		void *passentity2;
	};
public:
	void TraceRay(const Ray_t &ray, unsigned int fMask, CTraceFilter *pTraceFilter, trace_t *pTrace)
	{
		typedef void(__thiscall* fnOriginal)(PVOID, const Ray_t&, unsigned int, CTraceFilter *, trace_t*);
		GetVirtualFunction<fnOriginal>(this, 5)(this, ray, fMask, pTraceFilter, pTrace);
	}
	void ClipRayToEntity(const Ray_t &ray, unsigned int fMask, CBaseEntity *pEnt, trace_t *pTrace)
	{
		typedef void(__thiscall* fnOriginal)(PVOID, const Ray_t &, unsigned int, CBaseEntity *, trace_t *);
		GetVirtualFunction<fnOriginal>(this, 3)(this, ray, fMask, pEnt, pTrace);
	}
	int GetPointContents(const Vector &vecAbsPosition, unsigned int fMask, CBaseEntity** ppEntity = NULL)
	{
		typedef int(__thiscall* fnOriginal)(PVOID, const Vector &, unsigned int, CBaseEntity**);
		return GetVirtualFunction<fnOriginal>(this, 0)(this, vecAbsPosition, fMask, ppEntity);
	}
}; extern IEngineTrace* g_pEngineTrace;

//----------------------------------------
// TOOLS CLASS
//----------------------------------------

class CTools
{
public:
	void* QueryInterface(std::string szModuleName, std::string szInterfaceName);
	bool IsVisible(Vector& vecStart, Vector& vecEnd, CBaseEntity* pEntity);
	CBaseCombatWeapon* GetActiveWeapon(CBaseEntity* pEntity);
}; extern CTools g_Tools;

#endif