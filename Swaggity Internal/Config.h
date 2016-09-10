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
    extern uint                 AimbotFOV;
    extern uint                 SmoothFactor;
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
}