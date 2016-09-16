#include "Entity.h"
#include "Config.h"
#include "Global.h"
#include "RayTrace.h"

bool CBaseEntity::GetAlive()
{
    return static_cast<bool>(*reinterpret_cast<int*>(DWORD(this) + offsets.m_lifeState) == 0);
}

player_info_t CBaseEntity::GetPlayerInfo()
{
    player_info_t info;
    Interfaces::Engine->GetPlayerInfo(this->index, &info);
    return info;
}

string CBaseEntity::GetName()
{
    return GetPlayerInfo().name;
}

int CBaseEntity::GetFlags()
{
    return *reinterpret_cast<int*>(DWORD(this) + offsets.m_fFlags);
}

float CBaseEntity::GetFlashDuration()
{
    return *reinterpret_cast<float*>(DWORD(this) + offsets.m_flFlashDuration);
}

Vector CBaseEntity::GetViewPunch()
{
    return *reinterpret_cast<Vector*>(DWORD(this) + offsets.m_viewPunchAngle);
}

Vector CBaseEntity::GetPunch()
{
    return *reinterpret_cast<Vector*>(DWORD(this) + offsets.m_aimPunchAngle);
}

Vector CBaseEntity::GetEyeAngles()
{
    return *reinterpret_cast<Vector*>(DWORD(this) + offsets.m_angEyeAngles);
}

Vector CBaseEntity::GetOrigin()
{
    return *reinterpret_cast<Vector*>(DWORD(this) + offsets.m_vecOrigin);
}

Vector CBaseEntity::GetEyePosition()
{
    Vector origin = this->GetOrigin();
    Vector offset = *reinterpret_cast<Vector*>(DWORD(this) + offsets.m_vecViewOffset);

    return (origin + offset);
}

int CBaseEntity::GetHealth()
{
    return *reinterpret_cast<int*>(DWORD(this) + offsets.m_iHealth);
}

CBaseCombatWeapon* CBaseEntity::GetWeapon()
{
    return reinterpret_cast<CBaseCombatWeapon*>(
        Interfaces::EntityList->GetClientEntityFromHandle(*reinterpret_cast<DWORD*>(
            DWORD(this) + offsets.m_hActiveWeapon)));
}

WeaponInfo_t* CBaseCombatWeapon::GetCSWpnData()
{
    if (!this)
        return nullptr;

    typedef WeaponInfo_t*(__thiscall *OriginalFn)(void*);
    return GetVFunc<OriginalFn>(this, 456)(this);
}


void CBaseEntity::SetFlashDuration()
{
    *reinterpret_cast<float*>(DWORD(this) + offsets.m_flFlashDuration) = Config::NoFlash ? 0.f : 25.f;

}

int& CBaseCombatWeapon::GetWeaponID()
{
    return *reinterpret_cast<int*>(DWORD(this) + offsets.m_iItemDefinitionIndex);
}

float& CBaseCombatWeapon::GetNextPrimaryAttack()
{
    return *reinterpret_cast<float*>(DWORD(this) + offsets.m_flNextPrimaryAttack);
}

float & CBaseCombatWeapon::GetAccuracyPenalty()
{
    return *reinterpret_cast<float*>(DWORD(this) + offsets.m_fAccuracyPenalty);
}

bool CBaseEntity::GetImmune()
{
    return *reinterpret_cast<bool*>(DWORD(this) + offsets.m_bGunGameImmunity);
}

int CBaseEntity::GetTickBase()
{
    return *reinterpret_cast<int*>(DWORD(this) + offsets.m_nTickBase);
}


int CBaseEntity::GetShotsFired()
{
    return *reinterpret_cast<int*>(DWORD(this) + offsets.m_iShotsFired);
}

int CBaseEntity::GetTeam()
{
    return *reinterpret_cast<int*>(DWORD(this) + offsets.m_iTeamNum);
}

bool CBaseEntity::IsEnemy()
{
    if (!Global::LocalPlayer)
        return false;

    return GetTeam() == Global::LocalPlayer->GetTeam();
}

bool CBaseEntity::GetDormant()
{
    return *reinterpret_cast<bool*>(DWORD(this) + offsets.m_bDormant);
}

ICollideable* CBaseEntity::GetCollideable()
{
    return reinterpret_cast<ICollideable*>(DWORD(this) + offsets.m_Collision);
}

bool CBaseCombatWeapon::IsGun()
{
    if (!this)
        return false;

    int id = this->GetWeaponID();

    switch (id)
    {
    case WEAPON_DEAGLE:
    case WEAPON_ELITE:
    case WEAPON_FIVESEVEN:
    case WEAPON_GLOCK:
    case WEAPON_AK47:
    case WEAPON_AUG:
    case WEAPON_AWP:
    case WEAPON_FAMAS:
    case WEAPON_G3SG1:
    case WEAPON_GALILAR:
    case WEAPON_M249:
    case WEAPON_M4A1:
    case WEAPON_MAC10:
    case WEAPON_P90:
    case WEAPON_UMP45:
    case WEAPON_XM1014:
    case WEAPON_BIZON:
    case WEAPON_MAG7:
    case WEAPON_NEGEV:
    case WEAPON_SAWEDOFF:
    case WEAPON_TEC9:
        return true;
    case WEAPON_TASER:
        return false;
    case WEAPON_HKP2000:
    case WEAPON_MP7:
    case WEAPON_MP9:
    case WEAPON_NOVA:
    case WEAPON_P250:
    case WEAPON_SCAR20:
    case WEAPON_SG556:
    case WEAPON_SSG08:
        return true;
    case WEAPON_KNIFE:
    case WEAPON_FLASHBANG:
    case WEAPON_HEGRENADE:
    case WEAPON_SMOKEGRENADE:
    case WEAPON_MOLOTOV:
    case WEAPON_DECOY:
    case WEAPON_INCGRENADE:
    case WEAPON_C4:
    case WEAPON_KNIFE_T:
        return false;
    case WEAPON_M4A1_SILENCER:
    case WEAPON_USP_SILENCER:
    case WEAPON_CZ75A:
    case WEAPON_REVOLVER:
        return true;
    default:
        return false;
    }
}

bool CBaseCombatWeapon::IsPistol()
{
    if (!this)
        return false;

    switch (this->GetWeaponID())
    {
        case WEAPON_GLOCK:
        case WEAPON_USP_SILENCER:
        case WEAPON_P250:
        case WEAPON_TEC9:
        case WEAPON_CZ75A:
        case WEAPON_ELITE:
        case WEAPON_DEAGLE:
        case WEAPON_FIVESEVEN:
            return true;
        default:
            return false;
    }
}

bool CBaseCombatWeapon::IsSniper()
{
    if (!this)
        return false;

    switch (this->GetWeaponID())
    {
        case WEAPON_AWP:
        case WEAPON_SSG08:
        case WEAPON_SCAR20:
        case WEAPON_G3SG1:
            return true;
        default:
            return false;
    }
}

bool CBaseCombatWeapon::IsShotgun()
{
    if (!this)
        return false;

    switch (this->GetWeaponID())
    {
    case WEAPON_NOVA:
    case WEAPON_XM1014:
    case WEAPON_MAG7:
    case WEAPON_SAWEDOFF:
        return true;
    default:
        return false;
    }
}

Vector CBaseEntity::GetBonePosition(int iBone)
{
    matrix3x4_t boneMatrixes[128];
    if (this->SetupBones(boneMatrixes, 128, 0x100, 0))
    {
        matrix3x4_t boneMatrix = boneMatrixes[iBone];
        return Vector(boneMatrix.m_flMatVal[0][3], boneMatrix.m_flMatVal[1][3], boneMatrix.m_flMatVal[2][3]);
    }
    else return Vector(0, 0, 0);
}

bool CBaseEntity::SetupBones(matrix3x4_t *pBoneToWorldOut, int nMaxBones, int boneMask, float currentTime)
{
    __asm
    {
        mov edi, this
        lea ecx, dword ptr ds : [edi + 0x4]
            mov edx, dword ptr ds : [ecx]
            push currentTime
            push boneMask
            push nMaxBones
            push pBoneToWorldOut
            call dword ptr ds : [edx + 0x34]
    }
}

bool CBaseEntity::IsVisible(int bone)
{
    Ray_t ray;
    trace_t tr;
    CTraceFilter filter;
    filter.pSkip = Global::LocalPlayer;
    m_visible = false;


    matrix3x4_t matrix[MAXSTUDIOBONES];

    if (!SetupBones(matrix, MAXSTUDIOBONES, 0x100, 0))
        return false;

    for (uint i = 0; i < MAXSTUDIOBONES; ++i)
    {
        if (bone != -1) //Just 1 iteration
            i = bone;

        ray.Init(Global::LocalPlayer->GetEyePosition(), GetBonePosition(i));
        Interfaces::EngineTrace->TraceRay(ray, 0x4600400B, &filter, &tr);

        if (tr.m_pEnt == this)
        {
            m_visible = true;
            return true;
        }

        if (bone != -1) //Just 1 iteration
            return false;
    }

    return false;
}

bool CBaseEntity::IsTargetingLocal()
{
    return false;
}

bool CBaseEntity::IsValid()
{
    if (!this || GetHealth() <= 0 || GetImmune() || GetDormant() || this == Global::LocalPlayer || GetTeam() == Global::LocalPlayer->GetTeam())
        return false;

    return true;
}