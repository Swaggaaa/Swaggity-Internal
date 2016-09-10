#include "Offsets.h"
#include <Psapi.h>
#define INRANGE(x,a,b)    (x >= a && x <= b)
#define getBits( x )    (INRANGE((x&(~0x20)),'A','F') ? ((x&(~0x20)) - 'A' + 0xa) : (INRANGE(x,'0','9') ? x - '0' : 0))
#define getByte(x)  (getBits(x[0]) << 4 | getBits(x[1]))

COffsets offsets;

DWORD FindPattern(std::string moduleName, std::string pattern)
{
    const char* pat = pattern.c_str();
    DWORD firstMatch = 0;
    DWORD rangeStart = (DWORD)GetModuleHandleA(moduleName.c_str());
    MODULEINFO miModInfo; GetModuleInformation(GetCurrentProcess(), (HMODULE)rangeStart, &miModInfo, sizeof(MODULEINFO));
    DWORD rangeEnd = rangeStart + miModInfo.SizeOfImage;
    for (DWORD pCur = rangeStart; pCur < rangeEnd; pCur++)
    {
        if (!*pat)
            return firstMatch;

        if (*(PBYTE)pat == '\?' || *(BYTE*)pCur == getByte(pat))
        {
            if (!firstMatch)
                firstMatch = pCur;

            if (!pat[2])
                return firstMatch;

            if (*(PWORD)pat == '\?\?' || *(PBYTE)pat != '\?')
                pat += 3;

            else
                pat += 2;    //one ?
        }
        else
        {
            pat = pattern.c_str();
            firstMatch = 0;
        }
    }
    return NULL;
}

void Offsets::GrabOffsets()
{
    NetVarManager->Initialize();

    offsets.m_iHealth = NetVarManager->GetOffset("DT_CSPlayer", "m_iHealth");
    offsets.m_iTeamNum = NetVarManager->GetOffset("DT_CSPlayer", "m_iTeamNum");
    offsets.m_ArmorValue = NetVarManager->GetOffset("DT_CSPlayer", "m_ArmorValue");
    offsets.m_bHasHelmet = NetVarManager->GetOffset("DT_CSPlayer", "m_bHasHelmet");
    offsets.m_iClass = NetVarManager->GetOffset("DT_CSPlayer", "m_iClass");
    offsets.m_bDormant = 0xE9;
    offsets.m_bGunGameImmunity = NetVarManager->GetOffset("DT_CSPlayer", "m_bGunGameImmunity");
    offsets.m_lifeState = NetVarManager->GetOffset("DT_CSPlayer", "m_lifeState");
    offsets.m_fFlags = NetVarManager->GetOffset("DT_CSPlayer", "m_fFlags");
    offsets.m_Local = NetVarManager->GetOffset("DT_BasePlayer", "m_Local");
    offsets.m_nTickBase = NetVarManager->GetOffset("DT_CSPlayer", "m_nTickBase");
    offsets.m_nForceBone = NetVarManager->GetOffset("DT_CSPlayer", "m_nForceBone");
    offsets.m_angEyeAngles = NetVarManager->GetOffset("DT_CSPlayer", "m_angEyeAngles");
    offsets.m_flFlashDuration = NetVarManager->GetOffset("DT_CSPlayer", "m_flFlashDuration");
    offsets.m_iGlowIndex = offsets.m_flFlashDuration + 0x18;
    offsets.m_mBoneMatrix = offsets.m_nForceBone + 0x1C;
    offsets.m_nModelIndex = NetVarManager->GetOffset("DT_BasePlayer", "m_nModelIndex");
    offsets.m_viewPunchAngle = NetVarManager->GetOffset("DT_BasePlayer", "m_viewPunchAngle");
    offsets.m_aimPunchAngle = NetVarManager->GetOffset("DT_BasePlayer", "m_aimPunchAngle");
    offsets.m_vecOrigin = NetVarManager->GetOffset("DT_BasePlayer", "m_vecOrigin");
    offsets.m_vecViewOffset = NetVarManager->GetOffset("DT_CSPlayer", "m_vecViewOffset[0]");
    offsets.m_vecVelocity = NetVarManager->GetOffset("DT_CSPlayer", "m_vecVelocity[0]");
    offsets.m_szLastPlaceName = NetVarManager->GetOffset("DT_CSPlayer", "m_szLastPlaceName");
    offsets.m_hActiveWeapon = NetVarManager->GetOffset("DT_CSPlayer", "m_hActiveWeapon");
    offsets.m_fAccuracyPenalty = NetVarManager->GetOffset("DT_WeaponCSBase", "m_fAccuracyPenalty");
    offsets.m_Collision = NetVarManager->GetOffset("DT_BasePlayer", "m_Collision");
    offsets.m_CollisionGroup = NetVarManager->GetOffset("DT_BasePlayer", "m_CollisionGroup");
    offsets.m_iShotsFired = NetVarManager->GetOffset("DT_CSPlayer", "m_iShotsFired");
    offsets.m_iWeaponID = NetVarManager->GetOffset("DT_WeaponCSBase", "m_fAccuracyPenalty") + 0x2C;
    offsets.m_hOwnerEntity = NetVarManager->GetOffset("DT_BaseEntity", "m_hOwnerEntity");
    offsets.m_nMoveType = 0x258;
    offsets.m_nHitboxSet = NetVarManager->GetOffset("DT_BasePlayer", "m_nHitboxSet");
    offsets.m_bIsBroken = NetVarManager->GetOffset("DT_BreakableSurface", "m_bIsBroken");
    offsets.m_flC4Blow = NetVarManager->GetOffset("DT_PlantedC4", "m_flC4Blow");

    offsets.m_bReloadVisuallyComplete = NetVarManager->GetOffset("DT_WeaponCSBase", "m_bReloadVisuallyComplete");
    offsets.m_flNextPrimaryAttack = NetVarManager->GetOffset("DT_BaseCombatWeapon", "m_flNextPrimaryAttack");
    offsets.m_nFallbackPaintKit = NetVarManager->GetOffset("DT_BaseCombatWeapon", "m_nFallbackPaintKit");
    offsets.m_nFallbackSeed = NetVarManager->GetOffset("DT_BaseCombatWeapon", "m_nFallbackSeed");
    offsets.m_flFallbackWear = NetVarManager->GetOffset("DT_BaseCombatWeapon", "m_flFallbackWear");
    offsets.m_nFallbackStatTrak = NetVarManager->GetOffset("DT_BaseCombatWeapon", "m_nFallbackStatTrak");
    offsets.m_AttributeManager = NetVarManager->GetOffset("DT_BaseCombatWeapon", "m_AttributeManager");
    offsets.m_Item = NetVarManager->GetOffset("DT_BaseCombatWeapon", "m_Item");
    offsets.m_iEntityLevel = NetVarManager->GetOffset("DT_BaseCombatWeapon", "m_iEntityLevel");
    offsets.m_iItemIDHigh = NetVarManager->GetOffset("DT_BaseCombatWeapon", "m_iItemIDHigh");
    offsets.m_iItemIDLow = NetVarManager->GetOffset("DT_BaseCombatWeapon", "m_iItemIDLow");
    offsets.m_iAccountID = NetVarManager->GetOffset("DT_BaseCombatWeapon", "m_iAccountID");
    offsets.m_iEntityQuality = NetVarManager->GetOffset("DT_BaseCombatWeapon", "m_iEntityQuality");
    offsets.m_iClip1 = NetVarManager->GetOffset("DT_BaseCombatWeapon", "m_iClip1");
    offsets.m_OriginalOwnerXuidLow = NetVarManager->GetOffset("DT_BaseAttributableItem", "m_OriginalOwnerXuidLow");
    offsets.m_OriginalOwnerXuidHigh = NetVarManager->GetOffset("DT_BaseAttributableItem", "m_OriginalOwnerXuidHigh");
    offsets.m_iItemDefinitionIndex = NetVarManager->GetOffset("DT_BaseAttributableItem", "m_iItemDefinitionIndex");

    offsets.d3d9Device = **reinterpret_cast<DWORD**>(FindPattern("shaderapidx9.dll", "A1 ?? ?? ?? ?? 50 8B 08 FF 51 0C") + 0x01);
    offsets.MoveHelper = **reinterpret_cast<DWORD**>(FindPattern("client.dll", "8B 0D ? ? ? ? C7 87 ? ? ? ? ? ? ? ? 8B 46 08") + 0x02);
}