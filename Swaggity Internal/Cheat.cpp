#include "Cheat.h"
#include "Entity.h"
#include "RayTrace.h"
#include "SDK.h"
#include "Config.h"
#include <string>
#include <iostream>
#include "Utils.h"

void Cheat::ClampAngles()
{
    if (Global::UserCmd->viewangles.x < -89)
        Global::UserCmd->viewangles.x = -89;
    else if (Global::UserCmd->viewangles.x > 89)
        Global::UserCmd->viewangles.x = 89;

    if (Global::UserCmd->viewangles.y < -180)
        Global::UserCmd->viewangles.y = -180;
    else if (Global::UserCmd->viewangles.y > 180)
        Global::UserCmd->viewangles.y = 180;
}

void Cheat::BunnyHop()
{
    static int nJumps = rand() % 10 + 2;

    if (Global::UserCmd->buttons & IN_JUMP)
    {
        if (Global::LocalPlayer->GetFlags() & FL_ONGROUND)
        {
            Global::UserCmd->buttons |= IN_JUMP;
            nJumps = rand() % 10 + 2;
        }
        else
        {
            if (nJumps != 0)
            {
                if (nJumps % 2 == 0)
                    Global::UserCmd->buttons |= IN_JUMP;
                else
                    Global::UserCmd->buttons &= ~IN_JUMP;

                --nJumps;
            }
            else
                Global::UserCmd->buttons &= ~IN_JUMP;
        }
    }
}

Vector oldPunch(0.f, 0.f, 0.f);

void Cheat::NoRecoil()
{
    if (Global::LocalPlayer->GetWeapon() == nullptr)
        return;

    switch (Global::LocalPlayer->GetWeapon()->GetWeaponID())
    {
    case WEAPON_AK47:
    case WEAPON_AUG:
    case WEAPON_SG556:
    case WEAPON_FAMAS:
    case WEAPON_GALILAR:
    case WEAPON_M249:
    case WEAPON_M4A1:
    case WEAPON_MAC10:
    case WEAPON_P90:
    case WEAPON_UMP45:
    case WEAPON_BIZON:
    case WEAPON_NEGEV:
    case WEAPON_MP7:
    case WEAPON_MP9:
    case WEAPON_M4A1_SILENCER:
    case WEAPON_CZ75A:
        break;
    default:
        return;
    }
    
    if (Global::UserCmd->buttons & IN_ATTACK)
    {
        Vector newPunch = Global::LocalPlayer->GetPunch() * 2.f;
        Vector tmp = Global::UserCmd->viewangles;
        tmp += oldPunch - newPunch;

        QAngle angles;
        angles.x = tmp.x;
        angles.y = tmp.y;
        angles.z = tmp.z;

        angles.Clamp();
        Interfaces::Engine->SetViewAngles(angles);
        oldPunch = newPunch;
        ClampAngles();
    }
    else if (Global::LastShot > 250)  //Temporary fix
    {
        oldPunch.Zero();
    }
    
}

void Cheat::RageNoRecoil()
{
    if (Global::LocalPlayer->GetWeapon() == nullptr)
        return;

    switch (Global::LocalPlayer->GetWeapon()->GetWeaponID())
    {
    case WEAPON_AK47:
    case WEAPON_AUG:
    case WEAPON_SG556:
    case WEAPON_FAMAS:
    case WEAPON_GALILAR:
    case WEAPON_M249:
    case WEAPON_M4A1:
    case WEAPON_MAC10:
    case WEAPON_P90:
    case WEAPON_UMP45:
    case WEAPON_BIZON:
    case WEAPON_NEGEV:
    case WEAPON_MP7:
    case WEAPON_MP9:
    case WEAPON_M4A1_SILENCER:
    case WEAPON_CZ75A:
        break;
    default:
        return;
    }

    if (Global::UserCmd->buttons & IN_ATTACK)
    {
        Global::UserCmd->viewangles -= Global::LocalPlayer->GetPunch() * 2.f;
        ClampAngles();
    }
}

UINT tick = 0;

void Cheat::TriggerBot()
{
    if (GetAsyncKeyState(Config::TriggerKey) & 0x8000)
    {
        if (Config::RageAimbot) //Holding trigger makes it autofire when visible
        {
            RageAimbot();
            return;
        }

        trace_t trace;
        Ray_t ray;
        CTraceFilter filter;

        Vector viewAngle = Global::UserCmd->viewangles;
        if (!Config::RageRCS)
            viewAngle += Global::LocalPlayer->GetPunch() * 2.f;

        float cy, sy, cx, sx;
        Vector forward, src, dst;

        SinCos(DEG2RAD(viewAngle.y), &sx, &cx);
        SinCos(DEG2RAD(viewAngle.x), &sy, &cy);

        forward.x = cy*cx;
        forward.y = cy*sx;
        forward.z = -sy;

        forward *= 8192;
        filter.pSkip = Global::LocalPlayer;
        src = Global::LocalPlayer->GetEyePosition();
        dst = src + forward;

        ray.Init(src, dst);
        Interfaces::EngineTrace->TraceRay(ray, 0x4600400B, &filter, &trace);

        if (!trace.m_pEnt)
            return;

        /*if ((Global::LocalPlayer->GetWeapon()->GetWeaponID() != WEAPON_AWP &&
            Global::LocalPlayer->GetWeapon()->GetWeaponID() != WEAPON_SSG08 &&
            Global::LocalPlayer->GetWeapon()->GetWeaponID() != WEAPON_G3SG1 &&
            Global::LocalPlayer->GetWeapon()->GetWeaponID() != WEAPON_AUG) &&
            trace.hitgroup != HITGROUP_HEAD)
                return;
                */

        if (trace.m_pEnt->IsValid())
        {
            float hitchance = 75.f + Config::TriggerChance / 4;
            if ((1.0f - Global::LocalPlayer->GetWeapon()->GetAccuracyPenalty()) * 100.f >= hitchance && (GetTickCount() - tick >= Config::TriggerDelay))
            {
                /*if (Global::LocalPlayer->GetShotsFired() == 0)
                {
                    Interfaces::Engine->
                }
                */
                tick = GetTickCount();
                if (Global::LocalPlayer->GetWeapon()->GetWeaponID() == WEAPON_KNIFE || Global::LocalPlayer->GetWeapon()->GetWeaponID() == WEAPON_KNIFE_T)
                    Global::UserCmd->buttons |= IN_ATTACK2;
                else
                {
                    if (Config::TriggerSilent)
                    {
                        Vector headPos = trace.m_pEnt->GetBonePosition(6); //HEAD
                        QAngle destination = Utils::CalcAngle(Global::LocalPlayer->GetEyePosition(), headPos);
                        QAngle origin = Global::UserCmd->viewangles;
                        destination.Clamp();
                        Vector tmp(destination.x, destination.y, destination.z);

                        switch (Global::LocalPlayer->GetWeapon()->GetWeaponID())
                        {
                        case WEAPON_USP_SILENCER:
                        case WEAPON_P250:
                        case WEAPON_DEAGLE:
                        case WEAPON_FIVESEVEN:
                        case WEAPON_TEC9:
                        case WEAPON_CZ75A:
                        case WEAPON_SSG08:
                        {
                            if (Utils::GetFOV(tmp) < 1.5f)
                            {
                                Global::OldAngles = Global::UserCmd->viewangles;
                                Global::bSendPackets = false;
                                Global::NextTick = true;
                                Global::UserCmd->viewangles = tmp;
                            }
                            else
                                Global::UserCmd->buttons |= IN_ATTACK;
                            break;
                        }
                        default:
                            Global::UserCmd->buttons |= IN_ATTACK;
                            break;
                        }
                    }
                    else
                        Global::UserCmd->buttons |= IN_ATTACK;
                }

                Global::LastShot = tick;
            }
            else if (tick == 0)
                tick = GetTickCount();
        }
    }
}

void Cheat::RageAimbot()
{
    float distance = 1337.f;
    uint id = 1337;

    switch (Global::LocalPlayer->GetWeapon()->GetWeaponID())
    {
        case WEAPON_USP_SILENCER:
        case WEAPON_P250:
        case WEAPON_DEAGLE:
        case WEAPON_FIVESEVEN:
        case WEAPON_TEC9:
        case WEAPON_SSG08:
        case WEAPON_AWP:
        case WEAPON_SCAR20:
        case WEAPON_KNIFE:
        case WEAPON_KNIFE_T:
        case WEAPON_DECOY:
        case WEAPON_HEGRENADE:
        case WEAPON_FLASHBANG:
        case WEAPON_SMOKEGRENADE:
        case WEAPON_MOLOTOV:
        case WEAPON_C4:
        case WEAPON_INCGRENADE:
        case WEAPON_G3SG1:
            return;

        default:
            break;
    }
      

    for (uint i = 0; i < uint(Interfaces::EntityList->GetHighestEntityIndex()); ++i)
    {
        CBaseEntity* entity = Interfaces::EntityList->GetClientEntity(i);

        if (!entity->IsValid() ||  !entity->IsVisible(6))
            continue;

        Vector dist = entity->GetOrigin() - Global::LocalPlayer->GetOrigin();
        float tmp = dist.Length();

        if (distance == 1337.f || tmp < distance)
        {
            distance = tmp;
            id = i;
        }
    }

    CBaseEntity* ent = Interfaces::EntityList->GetClientEntity(id);
    if (!ent || id == -1337)
        return;
    //Vector dst = ent->GetOrigin() - Global::LocalPlayer->Get      No hacemos el smooth aun. Hacemos rage sin steps.
    Vector headPos = ent->GetBonePosition(6);
    QAngle angle = Utils::CalcAngle(Global::LocalPlayer->GetEyePosition(), headPos);

    if (!Config::RageRCS)
        angle -= Global::LocalPlayer->GetPunch() * 2.f;

    angle.Clamp();

    Vector vAngle(angle.x, angle.y, angle.z);

    if (!Config::SilentAim)
        Interfaces::Engine->SetViewAngles(angle);

    Global::UserCmd->viewangles = vAngle; //So LegitRCS works without SilentAim
    if (!(Global::UserCmd->buttons & IN_ATTACK))
        Global::UserCmd->buttons |= IN_ATTACK;
}

void Cheat::LegitAimbot()
{
    float fov = 1337.f;
    uint id = 1337;
   
    for (uint i = 0; i < uint(Interfaces::EntityList->GetHighestEntityIndex()); ++i)
    {
        CBaseEntity* entity = Interfaces::EntityList->GetClientEntity(i);

        if (!entity->IsValid() || !entity->IsVisible(6))
            continue;

        Vector headPos = entity->GetBonePosition(6);
        QAngle angles = Utils::CalcAngle(Global::LocalPlayer->GetEyePosition(), headPos);
        float tmp = Utils::GetFOV(Vector(angles.x, angles.y, angles.z));

        if (fov == 1337.f || tmp < fov)
        {
            id = i;
            fov = tmp;
        }
    }

    CBaseEntity* entity = Interfaces::EntityList->GetClientEntity(id);

    if (!entity || id == 1337)
        return;

    if (fov > Config::AimbotFOV)
        return;

    QAngle dst = Utils::CalcAngle(Global::LocalPlayer->GetEyePosition(), entity->GetBonePosition(6));
    dst -= Global::LocalPlayer->GetPunch() * 2.f;
    QAngle origin = Global::UserCmd->viewangles;
    QAngle delta = dst - origin;
    delta.Clamp();

    dst = origin + delta / float(Config::SmoothFactor);
    dst.Clamp();
    Vector vAngles(dst.x, dst.y, dst.z);
    Interfaces::Engine->SetViewAngles(dst);
    Global::UserCmd->viewangles = vAngles;
}
