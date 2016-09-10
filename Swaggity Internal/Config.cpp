#include "Config.h"

bool                    Config::RageRCS            = true;
bool                    Config::LegitRCS           = false;
bool                    Config::RageAimbot         = true;
bool                    Config::LegitAimbot        = false;
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
vector<lbool>           Config::BoolSettings {make_pair("RageRCS",true), make_pair("LegitRCS",false), make_pair("RageAim",true), 
                                                      make_pair("LegitAim",false),make_pair("SilentAim",false),make_pair("NoVisRecoil",true),
                                                      make_pair("CrosshairRecoil",false),make_pair("NoFlash",true),make_pair("Bhop",true),make_pair("Trigger",true),
                                                      make_pair("ESP",false),make_pair("ShitTalk",false),make_pair("TriggerSilent",true) };

vector<lint>                 Config::IntSettings { make_pair("Trigger",0x30)};

