#include "Global.h"

CUserCmd*       Global::UserCmd;
CBaseEntity*    Global::LocalPlayer;
int             Global::LastShot;
bool            Global::bSendPackets = true;
bool            Global::NextTick = false;
Vector          Global::OldAngles;