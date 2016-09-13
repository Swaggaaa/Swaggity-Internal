#include "Hooks.h"
#include "Interfaces.h"
#include "Entity.h"
#include "IEngineClient.h"
#include <iostream>
#include "Cheat.h"
#include "Config.h"

BYTE mv[0x300];

void Prediction(float& oCurTime, float& oFrameTime)
{
    Interfaces::MoveHelper->SetHost(Global::LocalPlayer);

    oCurTime = Interfaces::GlobalVars->curtime;
    oFrameTime = Interfaces::GlobalVars->frametime;

    Interfaces::GlobalVars->curtime = Global::LocalPlayer->GetTickBase() * Interfaces::GlobalVars->interval_per_tick;
    Interfaces::GlobalVars->frametime = Interfaces::GlobalVars->interval_per_tick;

    memset(&mv, 0, sizeof(mv));

    Interfaces::Movement->StartTrackPredictionErrors(Global::LocalPlayer);
    Interfaces::Prediction->SetupMove(Global::LocalPlayer, Global::UserCmd, nullptr, &mv);
    Interfaces::Movement->ProcessMovement(Global::LocalPlayer, &mv);
    Interfaces::Prediction->FinishMove(Global::LocalPlayer, Global::UserCmd, &mv);
}

void RestorePrediction(float oCurTime, float oFrameTime)
{
    Interfaces::Movement->FinishTrackPredictionErrors(Global::LocalPlayer);
    Interfaces::GlobalVars->curtime = oCurTime;
    Interfaces::GlobalVars->frametime = oFrameTime;
    Interfaces::MoveHelper->SetHost(nullptr);
}

bool __fastcall Hooks::CreateMove(void* thisptr, void* edx, float flInputSampleTime, CUserCmd* cmd)
{
    oCreateMove(thisptr, edx, flInputSampleTime, cmd);

    Global::LocalPlayer = Interfaces::EntityList->GetClientEntity(Interfaces::Engine->GetLocalPlayer());
    Global::UserCmd = cmd;

    if (cmd->command_number == 0 || !Interfaces::Engine->IsInGame())
        return false;

    if (!Global::LocalPlayer || Global::LocalPlayer->GetHealth() <= 0)
        return false;

    float oCurTime, oFrameTime;

    //Let's assign bSendPackets
    DWORD* framePointer;
    __asm mov framePointer, ebp;
    *reinterpret_cast<bool*>(*framePointer - 0x1C) = Global::bSendPackets;

    //Prediction(oCurTime, oFrameTime);

    if (Global::UserCmd->buttons & IN_ATTACK)
        Global::LastShot = GetTickCount();

    if (!Global::bSendPackets && Global::NextTick)
    {
        Global::UserCmd->buttons |= IN_ATTACK;
        Global::UserCmd->viewangles = Global::OldAngles;
        Global::bSendPackets = true;
        Global::NextTick = false;
    }

    if (Global::UserCmd->buttons & IN_ATTACK)
    {
        if (General.getRageAimbot())
            Cheat::RageAimbot();
        else if (General.getLegitAimbot())
            Cheat::LegitAimbot();
    }

    if (General.getBhop() && Global::UserCmd->buttons & IN_JUMP)
        Cheat::BunnyHop();

    if (General.getActiveTrigger())
        Cheat::TriggerBot();

    if (General.getLegitRCS())
        Cheat::NoRecoil();
    else if (General.getRageRCS())
        Cheat::RageNoRecoil();

    Global::LocalPlayer->SetFlashDuration();

    //RestorePrediction(oCurTime, oFrameTime);

    return false;
}
