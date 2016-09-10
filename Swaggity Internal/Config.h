#pragma once
#include <vector>
using namespace std;
typedef unsigned int uint;

namespace Config
{
    extern bool                 RageRCS;
    extern bool                 LegitRCS;
    extern bool                 RageAimbot;
    extern bool                 LegitAimbot;
    extern bool                 SilentAim;
    extern bool                 NoVisRecoil;
    extern bool                 CrosshairRecoil;
    extern bool                 NoFlash;
    extern bool                 Bhop;
    extern bool                 Trigger;
    extern uint                 TriggerDelay;
    extern uint                 TriggerChance;
    extern uint                 TriggerKey;
    extern bool                 ESP;
    extern vector<bool>         ESPFeatures;
    extern bool                 ShitTalk;
    extern bool                 TriggerSilent;
    extern bool                 kill;
    extern int                  Ovrkey;
    extern int                  height;
    extern int                  width;
}