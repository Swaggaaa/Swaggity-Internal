#pragma once

#ifndef LSL_CONFIG
#define LSL_CONFIG
#include <vector>
using namespace std;
typedef unsigned int uint;



namespace Confg
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
    

   // void init();

}

class Config
{
private:
		/* extern bool                 active;
		extern bool                    RageRCS;
		extern bool                    LegitRCS;
		extern bool                    NoVisRecoil;
		extern bool                    CrosshairRecoil;

		*/
		 vector<pair<string, bool> > RCS;
		
		/* extern bool                 active;

		extern bool                 kill;
		extern int                  Ovrkey;
		extern int                   width;
		extern int                 height;
		*/
		 vector<pair<string, bool> > Misc;

		/* extern bool                 ESP;
		extern bool                 UI;
		extern bool                 ESPv2;
		extern bool enableovr;

		*/
		vector<pair<string, bool> > Visual;
	
		/*
		extern bool                 active;
		extern bool                 RageAimbot;
		extern bool                 LegitAimbot;
		extern uint                 AimbotFOV;

		*/

		 vector<pair<string, uint> > Aimbotuint;
		 vector<pair<string, bool> > Aimbot;
		
		/*
		extern bool                 NoFlash;
		extern bool                 Bhop;
		extern bool                 ShitTalk;

		*/

		 vector<pair<string, bool> > Stuff;
		 vector<pair<string, bool> > Trigger;
		 vector<pair<string, uint> > Triggerint;

public:
		 bool getActiveRCS();
		 bool getRageRCS();
		 bool getLegitRCS();
		 bool getNoVisRecoil();
		 bool getCorsshairRecoil();

		 void setActiveRCS(bool dep);
		 void setRageRCS(bool dep);
		 void setLegitRCS(bool dep);
		 void setNoVisRecoil(bool dep);
		 void setCorsshairRecoil(bool dep);

		 bool getKill();
		 bool getOvrkey();
		 int getwidth();
		 int getheight();

		 void setKill(bool dep);
		 void setOvrkey(bool dep);
		 void setwidth(int dep);
		 void setheight(int dep);

		 bool getESP();
		 bool getUI();
		 bool getESPv2();
		 bool getESPName();
		 bool getESPHealth();
		 bool getESPDistance();
		 bool getESPGun();
		 bool getESPHead();

		 void setESP(bool dep);
		 void setUI(bool dep);
		 void setESPv2(bool dep);
		 void setESPName(bool dep);
		 void setESPHealth(bool dep);
		 void setESPDistance(bool dep);
		 void setESPGun(bool dep);
		 void setESPHead(bool dep);

		 bool getActiveAimbot();
		 bool getRageAimbot();
		 bool getLegitAimbot();
		 bool getSilentAim();
		 bool getAutoShoot();

		 uint getAimbotFOV();
		 void setAimbotFOV(uint dep);

		 void setActiveAimbot(bool dep);
		 void setRageAimbot(bool dep);
		 void setLegitAimbot(bool dep);
		 void setSilentAim(bool dep);
		 void setAutoShoot(bool dep);

		 bool getNoFlash();
		 bool getBhop();
		 bool getShitTalk();
		 
		 void setNoFlash(bool dep);
		 void setBhop(bool dep);
		 void setShitTalk(bool dep);

		/*
		extern bool                 active;
		extern uint                 TriggerDelay;
		extern uint                 TriggerChance;
		extern uint                 TriggerKey;

		*/

		 bool getActiveTrigger();
		 void setActiveTrigger(bool dep);

		 bool getTriggerSilent();
		 void setTriggerSilent(bool dep);
		 uint getTriggerDelay();
		 uint getTriggerChance();
		 uint getTriggerKey();

		 void setTriggerDelay(uint dep);
		 void setTriggerChance(uint dep);
		 void setTriggerKey(uint dep);
		

		
         vector < pair<string, bool> > viewoptions;

		 bool showMisc = true;
		 bool showLegit = false;
		 bool showRage = false;
		 bool showVisual = false;
		
		 bool move;
         int movex, movey;
		 bool mpressed;

         int height, width;

		 int xmouse, ymouse;



		  Config();

		  void updateviewoptions();

		  void updatevectroveiw();

		  



		

};
extern Config General;





#endif
