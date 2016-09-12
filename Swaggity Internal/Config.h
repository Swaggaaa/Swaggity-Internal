#pragma once
#include <vector>
using namespace std;
typedef unsigned int uint;



namespace Config
{


    struct Conf
    {
        string name;
        /* extern bool                    active;
        extern bool                    RageRCS;
        extern bool                    LegitRCS;
        extern bool                    NoVisRecoil;
        extern bool                    CrosshairRecoil;

        */

         vector<pair<string, bool> > lbool;
         vector<pair<string, uint> > luint;

    };

   extern vector<Conf> configuration;


    namespace RCS
    {
       /* extern bool                    active;
        extern bool                    RageRCS;
        extern bool                    LegitRCS;
        extern bool                    NoVisRecoil;
        extern bool                    CrosshairRecoil;

        */

        extern vector<pair<string, bool> > lbool;
    };

    namespace Misc
    {
       /* extern bool                 active;

       extern bool                 kill;
       extern int                  Ovrkey;
       extern int                  height;
       extern int                  width;
       */
       extern vector<pair<string, bool> > lbool;
    }

    namespace Visual
    {
       /* extern bool                 ESP;
        extern bool                 UI;
        extern bool                 ESPv2;
        extern bool enableovr;

        */
        extern vector<pair<string, bool> > lbool;
    }

    namespace Aimbot
    {
        /*
        extern bool                 active;
        extern bool                 RageAimbot;
        extern bool                 LegitAimbot;
        extern uint                 AimbotFOV;

        */
        extern vector<pair<string, uint> > luint;
        extern vector<pair<string, bool> > lbool;
    }

    namespace Stuff
    {
        /*
        extern bool                 NoFlash;
        extern bool                 Bhop;
        extern bool                 ShitTalk;

        */

        extern vector<pair<string, bool> > lbool;
    }

    namespace Trigger
    {
        /*
        extern bool                 active;
        extern uint                 TriggerDelay;
        extern uint                 TriggerChance;
        extern uint                 TriggerKey;

        */

        extern vector<pair<string, bool> > lbool;
        extern vector<pair<string, uint> > luint;

    }

    namespace Menu
    {
        extern bool showMisc;
        extern bool showRCS;
        extern bool showStuff;
        extern bool showAim;
        extern bool showMisc;
        extern bool showTrigger;
    }



    extern bool                 DistanceBasedFOV;
  
    extern bool                 TriggerSilent;
    extern bool                 SilentAim;
   
   
    extern uint                 SmoothFactor;
    extern uint                 AimbotFOV;
   
    
    extern vector<bool>         ESPFeatures;
    



   
   


    void init();

}