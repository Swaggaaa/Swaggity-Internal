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
uint                    Config::TriggerDelay       = 7;
uint                    Config::TriggerChance      = 25;
uint                    Config::TriggerKey         = 0x05;     //VK_XBUTTON1
bool                    Config::ESP                = false;
vector<bool>            Config::ESPFeatures(5, false);
bool                    Config::ShitTalk           = false;
bool                    Config::TriggerSilent      = true;
bool                    Config::kill               = false;
int                     Config::Ovrkey             = 0x30;  // KEY 0
int                     Config::height             = 0;
int                     Config::width              = 0;