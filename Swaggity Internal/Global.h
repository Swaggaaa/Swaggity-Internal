#pragma once
#include "CUserCmd.h"
#include "Entity.h"

namespace Global
{
    extern CUserCmd*    UserCmd;

    extern CBaseEntity* LocalPlayer;

    extern int          LastShot;

    extern bool         bSendPackets;

    extern bool         NextTick;

    extern Vector       OldAngles;

    extern int          CurrentTargetID;

    extern int          CurrentSmoothStep;
}
