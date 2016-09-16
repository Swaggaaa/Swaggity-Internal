#include "Config.h"

bool                    Config::RageRCS            = true;
bool                    Config::LegitRCS           = false;
bool                    Config::RageAimbot         = true;
bool                    Config::LegitAimbot        = false;
uint                    Config::MinBullets;
uint                    Config::MaxBullets;
uint                    Config::AimbotFOV;
bool                    Config::DistanceBasedFOV   = true;
uint                    Config::SmoothFactor;
bool                    Config::SilentAim          = false;
bool                    Config::NoVisRecoil        = true;
bool                    Config::CrosshairRecoil    = false;
bool                    Config::NoFlash            = true;
bool                    Config::Bhop               = true;
uint                    Config::BhopMinJumps;
uint                    Config::BhopMaxJumps;
bool                    Config::Trigger            = true;
uint                    Config::TriggerDelay       = 7;
uint                    Config::TriggerChance      = 25;
uint                    Config::TriggerKey         = 0x05;     //VK_XBUTTON1
bool                    Config::ESP                = false;
vector<bool>            Config::ESPFeatures(5, false);
bool                    Config::ShitTalk           = false;
bool                    Config::TriggerSilent      = true;