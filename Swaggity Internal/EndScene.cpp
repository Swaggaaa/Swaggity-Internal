#include "Hooks.h"
#include <cstdio>
#include <iostream>
#include "IEngineTrace.h"
#include "Cheat.h"
#include "RayTrace.h"
#include "Config.h"
#include "D3D.h"
#include <iso646.h>

enum COLORS {  // Normal Colors
    WHITE = D3DCOLOR_ARGB(255, 255, 255, 255),
    RED = D3DCOLOR_ARGB(255, 220, 20, 60),
    GREEN = D3DCOLOR_ARGB(255, 0, 255, 0),
    BLUE = D3DCOLOR_ARGB(255, 0, 0, 255),
    BLACK = D3DCOLOR_ARGB(255, 0, 0, 0),
    PURPLE = D3DCOLOR_ARGB(255, 125, 0, 255),
    GREY = D3DCOLOR_ARGB(255, 128, 128, 128),
    YELLOW = D3DCOLOR_ARGB(255, 255, 255, 0),
    ORANGE = D3DCOLOR_ARGB(255, 255, 125, 0)
};

#pragma warning (disable : 4244)


void printmenu()
{
    
    int i = 100;

    for (int j = 0; j < Config::BoolSettings.size(); ++j) {

       
        pD3D.DrawString(100, i + 20 * j, Config::BoolSettings[i].first + ' ' + to_string(Config::BoolSettings[i].second), WHITE, true, BLACK, true);

       /* pD3D.DrawString(100, i, "|||Swaggity 'Internal Menu: |||", WHITE, true, BLACK, true);
       
        pD3D.DrawString(100, i + j * 2, "Toggle Legit Recoil " + to_string(Config::LegitRCS), WHITE, true, BLACK, true);
        pD3D.DrawString(100, i + j * 3, "Toggle NoVis Recoil " + to_string(Config::NoVisRecoil), WHITE, true, BLACK, true);
        pD3D.DrawString(100, i + j * 4, "Toggle Rage Aimbot " + to_string(Config::RageAimbot), WHITE, true, BLACK, true);
        pD3D.DrawString(100, i + j * 5, "Toggle Legit Aimbot " + to_string(Config::LegitAimbot), WHITE, true, BLACK, true);
        pD3D.DrawString(100, i + j * 6, "Toggle Silent Aim " + to_string(Config::SilentAim), WHITE, true, BLACK, true);
        pD3D.DrawString(100, i + j * 7, "Toggle Recoil Crosshair " + to_string(Config::CrosshairRecoil), WHITE, true, BLACK, true);
        pD3D.DrawString(100, i + j * 8, "Toggle NoFlash " + to_string(Config::NoFlash), WHITE, true, BLACK, true);
        pD3D.DrawString(100, i + j * 9, "Toggle Bhop " + to_string(Config::Bhop), WHITE, true, BLACK, true);
        pD3D.DrawString(100, i + j * 10, "Toggle ESP " + to_string(Config::ESP), WHITE, true, BLACK, true);
        pD3D.DrawString(100, i + j * 11, "Toggle TriggerBot " + to_string(Config::Trigger), WHITE, true, BLACK, true);
        pD3D.DrawString(100, i + j * 12, "Toggle ShitTalk " + to_string(Config::ShitTalk), WHITE, true, BLACK, true);
        pD3D.DrawString(100, i + j * 13, "Toggle TriggerBot PSilent " + to_string(Config::TriggerSilent), WHITE, true, BLACK, true);

        */

    }
  
   
  
    /*
    cout << "#15 -> Set TriggerBot Delay (ms)"; printStatus(hConsole, false, true, Config::TriggerDelay, false);
    cout << "#16 -> Set TriggerBot Hitchance (%)"; printStatus(hConsole, false, true, Config::TriggerChance, false);
    cout << "#17 -> Set TriggerBot Key (VK_KEY CODE)"; printStatus(hConsole, false, true, Config::TriggerKey, true);
    cout << "#50 ->Exit " << endl;

    */
}

long __stdcall Hooks::EndScene(IDirect3DDevice9 *pDevice)
{

    int height, width;

    Interfaces::Engine->GetScreenSize(width, height);

   
        if (pD3D.Device != pDevice or (width != Config::width or height != Config::height)) {

            if(pD3D.Device)pD3D.Destruct();
            pD3D.init(pDevice);
            Config::width = width;
            Config::height = height;
        }

        if (GetAsyncKeyState(Config::Ovrkey) & 0x8000)
        {
            while (GetAsyncKeyState(Config::Ovrkey) & 0x8000);

            Config::enableovr = !Config::enableovr;
       
        }

        if(Config::enableovr)printmenu();


 
    return oEndScene(pDevice);
}
