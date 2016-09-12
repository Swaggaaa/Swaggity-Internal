#include "Config.h"

using namespace Config;

vector<pair<string, bool> > Visual::lbool;
vector<pair<string, bool> > Trigger::lbool;
vector<pair<string, bool> > Misc::lbool;
vector<pair<string, bool> > Stuff::lbool;
vector<pair<string, bool> > RCS::lbool;
vector<pair<string, bool> > Aimbot::lbool;
vector<pair<string, uint> > Aimbot::luint;
vector<pair<string, uint> > Trigger::luint;


bool Menu::showMisc;
bool Menu::showRCS;
bool Menu::showAim;
bool Menu::showStuff;
bool Menu::showTrigger;



//vector<lbool>           Config::BoolSettings;

 //vector<lint>           Config::IntSettings = { pair<string,int>("Trigger",0x30)};

 void Config::init()
 {
      Menu::showMisc = true;
      Menu::showRCS = false;
      Menu::showAim = false;
      Menu::showStuff = false;
      Menu::showTrigger = false;
      /*
     RCS::lbool = {
         pair<string, bool>("Active", true),
         pair<string, bool>("RageRCS", true),
         pair<string, bool>("LegitRCS", false),
         pair<string, bool>("NoVisRecoil", true),
         pair<string, bool>("CrosshairRecoil", true),

     };
     Misc::lbool = {
         pair<string, bool>("killAll", true),
         pair<string, bool>("OvrKey", true),
         pair<string, bool>("Height", true),
         pair<string, bool>("width", true)

     };
     Visual::lbool = {
        pair<string, bool>("UI", true),
        pair<string, bool>("ESP", true),
        pair<string, bool>("ESPv2", false)
        
     };

     Stuff::lbool = {
         pair<string, bool>("NoFlash", true),
         pair<string, bool>("Bhop", true),
         pair<string, bool>("ShitTalk", false)

     };
    
     Aimbot::lbool = {
         pair<string, bool>("Active", true),
         pair<string, bool>("RageAimbot", false),
         pair<string, bool>("LegitAimbot", false),
         
     };
     Aimbot::luint = {
         pair<string, bool>("AimbotFOV", 0)
     };
     
       Trigger::lbool = {
         pair<string, bool>("Active", true)
     };

       Trigger::luint = {

       };

       */
      Conf RCS, Misc, Visual, Aimbot, Stuff, Trigger;
     
      Misc.name = "Misc";
      Misc.lbool = {
          pair<string, bool>("killAll", true),
          pair<string, bool>("OvrKey", true),
          pair<string, bool>("Height", true),
          pair<string, bool>("Width", true)

      };
      Visual.name = "Visual";
      Visual.lbool = {
          pair<string, bool>("UI", true),
          pair<string, bool>("ESP", true),
          pair<string, bool>("ESPv2", false)

      };

      RCS.name = "RCS";
      RCS.lbool = {
          pair<string, bool>("Active", true),
          pair<string, bool>("RageRCS", true),
          pair<string, bool>("LegitRCS", false),
          pair<string, bool>("NoVisRecoil", true),
          pair<string, bool>("CrosshairRecoil", true),

      };
      Stuff.name = "Stuff";
      Stuff.lbool = {
          pair<string, bool>("NoFlash", true),
          pair<string, bool>("Bhop", true),
          pair<string, bool>("ShitTalk", false)

      };
      Aimbot.name = "Aimbot";
      Aimbot.lbool = {
          pair<string, bool>("Active", true),
          pair<string, bool>("RageAimbot", false),
          pair<string, bool>("LegitAimbot", false),

      };
      Aimbot.luint = {
          pair<string, bool>("AimbotFOV", 0)
      };
      Trigger.name = "Trigger";
      Trigger.lbool = {
          pair<string, bool>("Active", true)
      };

      Trigger.luint = {

      };

      configuration.push_back(Misc);
      configuration.push_back(Visual);
      configuration.push_back(RCS);
      configuration.push_back(Aimbot);
      configuration.push_back(Trigger);
      configuration.push_back(Stuff);


   

 }
