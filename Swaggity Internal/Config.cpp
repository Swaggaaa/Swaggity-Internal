#include "Config.h"

bool                    Config::RageRCS            = true;
bool                    Config::LegitRCS           = false;
bool                    Config::RageAimbot         = true;
bool                    Config::LegitAimbot        = false;
uint                    Config::AimbotFOV;
uint                    Config::SmoothFactor;
bool                    Config::SilentAim          = false;
bool                    Config::NoVisRecoil        = true;
bool                    Config::CrosshairRecoil    = false;
bool                    Config::NoFlash            = true;
bool                    Config::Bhop               = true;
bool                    Config::Trigger            = true;
bool                    Config::ESP                = false;
bool                    Config::ShitTalk           = false;
bool                    Config::TriggerSilent      = true;
bool                    Config::kill = false;
uint                    Config::TriggerDelay       = 7;
uint                    Config::TriggerChance      = 25;
uint                    Config::TriggerKey         = 0x05;     //VK_XBUTTON1
bool                    Config::enableovr          = false;
vector<bool>            Config::ESPFeatures(5, false);
int                     Config::Ovrkey             = 0x30;  // KEY 0
int                     Config::height             = 0;
int                     Config::width              = 0;
bool                    Config::NeoESP = true;
vector<lbool>           Config::BoolSettings = {pair<string,bool>("RageRCS",true), pair<string,bool>("LegitRCS",false), pair<string,bool>("RageAim",true), pair<string,bool>("LegitAim",false),pair<string,bool>("SilentAim",false),pair<string,bool>("NoVisRecoil",true), pair<string,bool>("CHRecoil",false),pair<string,bool>("NoFlash",true),pair<string,bool>("Bhop",true),pair<string,bool>("Trigger",true),pair<string,bool>("ESP",false),pair<string,bool>("ShitTalk",false),pair<string,bool>("TriggerSilent",true) };

 vector<lint>           Config::IntSettings = { pair<string,int>("Trigger",0x30)};

