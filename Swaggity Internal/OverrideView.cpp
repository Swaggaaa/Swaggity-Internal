#include "Hooks.h"
#include "SDK.h"
#include "Entity.h"
#include "Cheat.h"
#include <iostream>


void __stdcall Hooks::OverrideView(CViewSetup* pViewSetup)
{
    /*
    if (!Interfaces::Engine->IsInGame())
        return;

    if (Global::UserCmd->buttons & IN_ATTACK)
    {
        Vector tmp = Global::LocalPlayer->GetPunch();
        QAngle kek(tmp.x, tmp.y, tmp.z);
        std::cout << "hi" << std::endl;

        pViewSetup->angles -= kek * 2 * 0.45f;
    }
    */
    oOverrideView(pViewSetup);
}

