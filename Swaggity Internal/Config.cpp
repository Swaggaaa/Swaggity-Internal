#include "Config.h"

using namespace Confg;

/*vector<pair<string, bool> > Visual::lbool;
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

*/



//vector<lbool>           Config::BoolSettings;

 //vector<lint>           Config::IntSettings = { pair<string,int>("Trigger",0x30)};

bool Config::getActiveRCS()
{
	return RCS[0].second;

}

bool Config::getRageRCS()
{
	return RCS[1].second;
}

bool Config::getLegitRCS()
{
	return RCS[2].second;

}

bool Config::getNoVisRecoil()
{
	return RCS[3].second;
}

bool Config::getCorsshairRecoil()
{
	return RCS[4].second;
}

void Config::setActiveRCS(bool dep)
{
	 RCS[0].second = dep;

}

void Config::setRageRCS(bool dep)
{
	RCS[1].second = dep;
}

void Config::setLegitRCS(bool dep)
{
	RCS[2].second = dep;
}

void Config::setNoVisRecoil(bool dep)
{
	RCS[3].second = dep;
}

void Config::setCorsshairRecoil(bool dep)
{
	RCS[4].second = dep;
}

bool Config::getKill()
{
	return Misc[0].second;
}

bool Config::getOvrkey()
{
	return Misc[1].second;
}

int Config::getwidth()
{
	return width;
}

int Config::getheight()
{
	return height;
}

void Config::setKill(bool dep)
{
	Misc[0].second = dep;
}

void Config::setOvrkey(bool dep)
{
	Misc[1].second = dep;
}

void Config::setwidth(int dep)
{
	width = dep;
}

void Config::setheight(int dep)
{
	height = dep;
}

bool Config::getESP()
{
	return Visual[0].second;
}

bool Config::getUI()
{
	return Visual[1].second;
}

bool Config::getESPv2()
{
	return Visual[2].second;
}

bool Config::getESPName()
{
	return Visual[3].second;
}

bool Config::getESPHealth()
{
	return Visual[4].second;
}

bool Config::getESPDistance()
{
	return Visual[5].second;
}

bool Config::getESPGun()
{
	return Visual[6].second;
}

bool Config::getESPHead()
{
	return Visual[7].second;
}


void Config::setESP(bool dep)
{
	Visual[0].second = dep;
}

void Config::setUI(bool dep)
{
	Visual[1].second = dep;
}

void Config::setESPv2(bool dep)
{
	Visual[2].second = dep;
}
void Config::setESPName(bool dep)
{
	Visual[3].second = dep;
}

void Config::setESPHealth(bool dep)
{
	Visual[4].second = dep;
}

void Config::setESPDistance(bool dep)
{
	Visual[5].second = dep;
}

void Config::setESPGun(bool dep)
{
	Visual[6].second = dep;
}

void Config::setESPHead(bool dep)
{
	Visual[7].second = dep;
}

bool Config::getActiveAimbot()
{
	return Aimbot[0].second;
}

bool Config::getRageAimbot()
{
	return Aimbot[1].second;
}

bool Config::getLegitAimbot()
{

	return Aimbot[2].second;
}

bool Config::getSilentAim()
{
	return Aimbot[3].second;
}

bool Config::getAutoShoot()
{
	return Aimbot[4].second;
}

uint Config::getAimbotFOV()
{
	return Aimbotuint[0].second;
}

void Config::setAimbotFOV(uint dep)
{
	Aimbotuint[0].second = dep;
}

void Config::setActiveAimbot(bool dep)
{
	Aimbot[0].second = dep;
}

void Config::setRageAimbot(bool dep)
{
	Aimbot[1].second = dep;
}

void Config::setLegitAimbot(bool dep)
{
	Aimbot[2].second = dep;
}

void Config::setSilentAim(bool dep)
{
	Aimbot[3].second = dep;
}

void Config::setAutoShoot(bool dep)
{
	Aimbot[4].second = dep;
}

void Config::setMinBullets(uint dep)
{
    Aimbotuint[1].second = dep;
}

uint Config::getMinBullets()
{
    return Aimbotuint[1].second;
}

void Config::setMaxBullets(uint dep)
{
    Aimbotuint[2].second = dep;
}

uint Config::getMaxBullets()
{
    return Aimbotuint[2].second;
}

bool Config::getNoFlash()
{
	return Stuff[0].second;
}

bool Config::getBhop()
{
	return Stuff[1].second;
}

bool Config::getShitTalk()
{
	return Stuff[2].second;
}

uint Config::getMinBhops()
{
    return Stuffint[0].second;
}

uint Config::getMaxBhops()
{
    return Stuffint[1].second;
}

void Config::setMinBhops(uint dep)
{
    Stuffint[0].second = dep;
}

void Config::setMaxBhops(uint dep)
{
    Stuffint[1].second = dep;
}

void Config::setNoFlash(bool dep)
{
	Stuff[0].second = dep;
}

void Config::setBhop(bool dep)
{
	Stuff[1].second = dep;
}

void Config::setShitTalk(bool dep)
{
	Stuff[2].second = dep;
}

bool Config::getActiveTrigger()
{
	return Trigger[0].second;
}

void Config::setActiveTrigger(bool dep)
{
	Trigger[0].second = dep;
}

bool Config::getTriggerSilent()
{
	return Trigger[1].second;
}

void Config::setTriggerSilent(bool dep)
{
	Trigger[1].second = dep;
}

uint Config::getTriggerDelay()
{
	return Triggerint[0].second;
}

uint Config::getTriggerChance()
{
	return Triggerint[1].second;
}
uint Config::getTriggerKey()
{
	return Triggerint[2].second;
}

void Config::setTriggerDelay(uint dep)
{
	Triggerint[0].second = dep;
}

void Config::setTriggerChance(uint dep)
{
	Triggerint[1].second = dep;
}

void Config::setTriggerKey(uint dep)
{
	Triggerint[2].second = dep;
}





Config::Config()
 {
     movex = movey = 0;
      showMisc = true;
      showRage = false;
      showLegit = false;
      showVisual = false;
      
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
     
     
    
      Misc = {
          pair<string, bool>("EnableUI",true),
          pair<string, bool>("killAll", true),
          pair<string, bool>("OvrKey", true),
          pair<string, bool>("Height", true),
          pair<string, bool>("Width", true)

      };
	 
	  Visual = {
		  pair<string, bool>("UI", true),
		  pair<string, bool>("ESP", false),
		  pair<string, bool>("ESPv2", true),
		  pair<string,bool>("ESPName",true),
		  pair<string,bool>("ESPHealth",true),
		  pair<string,bool>("ESPDistance",true),
		  pair<string,bool>("ESPGun",true),
		  pair<string,bool>("ESPHead",true)
      };
   
      RCS = {
          pair<string, bool>("Active", true),
          pair<string, bool>("NoRecoil", false), //Rage
          pair<string, bool>("RCS", true), //Legit
          pair<string, bool>("NoVisRecoil", true),
          pair<string, bool>("CrosshairRecoil", true),

      };
     
      Stuff = {
          pair<string, bool>("NoFlash", false),
          pair<string, bool>("Bhop", true),
          pair<string, bool>("ShitTalk", false)

      };
     
	  Aimbot = {
		  pair<string, bool>("Active", true),
		  pair<string, bool>("Aimbot", false), //Rage
		  pair<string, bool>("Aimbot", false), //Aimbot
		  pair<string, bool>("SilentAim",false),
		  pair<string,bool>("AutoShoot",false)
		  
      };


      Aimbotuint = {
          pair<string, uint>("AimbotFOV", 0),
          pair<string, uint>("MinBullets", 2),
          pair<string, uint>("MaxBullets", 9)
      };
      
      Triggerint = {
		  pair<string, uint>("TriggerDelay", 7),
		  pair<string, uint>("TriggerChance", 25),
		  pair<string, uint>("TriggerKey", 0x05)
      };

      Trigger = {
		  pair<string,bool>("Active", true),
		  pair<string,bool>("TriggerSilent",true)
      };

      viewoptions  = { 
          pair<string, bool>("Rage",true),
          pair<string, bool>("Legit", false),
          pair<string, bool>("Visual", false),
          pair<string,bool>("Misc",false),

      };

      Stuffint = {
          pair<string, uint>("MinBhops", 4),
          pair<string,uint>("MaxBhops", 6)
      };


 }

 void Config::updateviewoptions()
 {
     showRage = viewoptions[0].second;
	 showLegit = viewoptions[1].second;
	 showVisual = viewoptions[2].second;
	 showMisc = viewoptions[3].second;
 }

 void Config::updatevectroveiw()
 { 
     viewoptions[0].second = showRage;
	 viewoptions[1].second = showLegit;
	 viewoptions[2].second = showVisual;
     viewoptions[3].second = showMisc;
	
 }


