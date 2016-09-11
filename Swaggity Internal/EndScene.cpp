#include "Hooks.h"
#include <cstdio>
#include <iostream>
#include "IEngineTrace.h"
#include "Cheat.h"
#include "RayTrace.h"
#include "Config.h"
#include "D3D.h"
#include <iso646.h>
#include "Utils.h"


bool Utils::controlmenu = false;

enum COLORS {  // Normal Colors
    WHITE = D3DCOLOR_ARGB(255, 255, 255, 255),
    BLACK_NOTMUCH = D3DCOLOR_ARGB(100, 0, 0, 0),
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
    
    int i = 50;

    for (int j = 0; j < Config::BoolSettings.size(); ++j) {

       
       pD3D.DrawString(35, i + 20 * j, Config::BoolSettings[j].first + ':', WHITE, true, BLACK, false);
       pD3D.DrawRect(130, i + 20 * j, 55, 20, 1, BLACK_NOTMUCH, true, true, 1, BLACK);
       if(Config::BoolSettings[j].second)pD3D.DrawString(130, i + 20 * j,  "Enabled", GREEN, true, BLACK ,false);
       else pD3D.DrawString(130 , i + 20 * j,  "Disabled", RED, true, BLACK, false);

     
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

        if (GetAsyncKeyState(Config::Ovrkey) & 0x0001)
        {
            Config::enableovr = !Config::enableovr;
            if (Config::enableovr) {
                if (Interfaces::Engine->IsInGame())Interfaces::Engine->ClientCmd("cl_mouseenable 1");
            }
            else {
                if (Interfaces::Engine->IsInGame())Interfaces::Engine->ClientCmd("cl_mouseenable 0");
            }
        }
        if(Config::enableovr)
        {
            printmenu();
            if(GetAsyncKeyState(0x01) & 0x0001)
            {
              
                POINT pep;
                GetCursorPos(&pep);
                pD3D.DrawCircle(pep.x,pep.y,1,1,BLACK,true,1,BLACK);
                HWND hWnd = GetActiveWindow();
                ScreenToClient(hWnd, &pep);
               
                for (int i = 0; i < Config::BoolSettings.size();++i)
                {
                   if(pep.x > 130 and pep.x < 160 and pep.y > (50 + i*20) and pep.y < (60+ (i)*20 ))
                   {
                       Config::BoolSettings[i].second = !Config::BoolSettings[i].second;
                   }
                }

            }
            POINT pep;
            GetCursorPos(&pep);
            pD3D.DrawCircle(pep.x, pep.y, 1, 1, BLACK, true, 1, BLACK);
           
        }
      
 
    return oEndScene(pDevice);
}
