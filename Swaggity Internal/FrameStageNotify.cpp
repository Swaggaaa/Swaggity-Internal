#include "Hooks.h"
#include "SDK.h"
#include "Global.h"
#include "Config.h"

void __fastcall Hooks::FrameStageNotify(void* ecx, void* edx, ClientFrameStage_t frameStage)
{

    if (General.getNoVisRecoil() && Interfaces::Engine->IsInGame() && frameStage == FRAME_RENDER_START && Global::LocalPlayer->GetAlive())
    {
        switch (Global::LocalPlayer->GetWeapon()->GetWeaponID())
        {
        case WEAPON_DEAGLE:
        case WEAPON_USP_SILENCER:
        case WEAPON_GLOCK:
        case WEAPON_FIVESEVEN:
        case WEAPON_P250:
        case WEAPON_AWP:
        case WEAPON_SSG08:
        case WEAPON_SCAR20:
        case WEAPON_G3SG1:
            oFrameStageNotify(ecx, frameStage);
            return;
        default:
            break;
        }

        QAngle* punchPtr = reinterpret_cast<QAngle*>(DWORD(Global::LocalPlayer) + offsets.m_aimPunchAngle);
        QAngle punch = *punchPtr;
        QAngle* viewpunchPtr = reinterpret_cast<QAngle*>(DWORD(Global::LocalPlayer) + offsets.m_viewPunchAngle);
        QAngle viewpunch = *viewpunchPtr;

        punchPtr->x = 0.f;
        punchPtr->y = 0.f;
        punchPtr->z = 0.f;

        viewpunchPtr->x = 0.f;
        viewpunchPtr->y = 0.f;
        viewpunchPtr->z = 0.f;

        oFrameStageNotify(ecx, frameStage);

        *punchPtr = punch;
        *viewpunchPtr = viewpunch;
    }
    else   
        oFrameStageNotify(ecx, frameStage);
}
