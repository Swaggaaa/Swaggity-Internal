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

enum COLORS
{ // Normal Colors
    WHITE = D3DCOLOR_ARGB(255, 255, 255, 255),
    BLACK_NOTMUCH = D3DCOLOR_ARGB(255, 30, 30, 30),
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
    for (int j = 0; j < Config::BoolSettings.size(); ++j)
    {
        int x, y, xx, yy, middle;


        x = pD3D.vpages[pD3D.actpage].boxes[j].x;
        y = pD3D.vpages[pD3D.actpage].boxes[j].y;
        xx = pD3D.vpages[pD3D.actpage].boxes[j].xx;
        yy = pD3D.vpages[pD3D.actpage].boxes[j].yy;
        middle = pD3D.vpages[pD3D.actpage].boxes[j].middle;
       
            pD3D.DrawRect(x, y, xx - x, yy - y, 1, BLACK_NOTMUCH, true, true, 1, BLACK);
            pD3D.DrawRect(middle, y, xx - middle, yy - y, 1, BLACK_NOTMUCH, true, true, 1, BLACK);
            pD3D.DrawString(x + 10, y, Config::BoolSettings[j].first + ':', WHITE, true, BLACK, false);


            if (Config::BoolSettings[j].second)pD3D.DrawString(middle, y, "Enabled", GREEN, true, BLACK, false);
            else pD3D.DrawString(middle, y, "Disabled", RED, true, BLACK, false);

       

        /*
          pD3D.DrawString(x, i + 20 * j, Config::BoolSettings[j].first + ':', WHITE, true, BLACK, false);
        pD3D.DrawRect(x, i + 20 * j, xx-x, yy-y, 1, BLACK_NOTMUCH, true, true, 1, BLACK);
        if(Config::BoolSettings[j].second)pD3D.DrawString(middle, i + 20 * j,  "Enabled", GREEN, true, BLACK ,false);
        else pD3D.DrawString(middle , i + 20 * j,  "Disabled", RED, true, BLACK, false);
        */


        /* pD3D.DrawString(100, i, "|||Swaggity 'Internal Menu: |||", WHITE, true, BLACK, true);
        
         pD3D.DrawString(100, i + j * 2, "Toggle Legit Recoil " + to_string(Config::configuration[2].lbool[2].second), WHITE, true, BLACK, true);
         pD3D.DrawString(100, i + j * 3, "Toggle NoVis Recoil " + to_string(Config::configuration[2].lbool[3].second), WHITE, true, BLACK, true);
         pD3D.DrawString(100, i + j * 4, "Toggle Rage Aimbot " + to_string(Config::configuration[3].lbool[1].second), WHITE, true, BLACK, true);
         pD3D.DrawString(100, i + j * 5, "Toggle Legit Aimbot " + to_string(Config::LegitAimbot), WHITE, true, BLACK, true);
         pD3D.DrawString(100, i + j * 6, "Toggle Silent Aim " + to_string(Config::SilentAim), WHITE, true, BLACK, true);
         pD3D.DrawString(100, i + j * 7, "Toggle Recoil Crosshair " + to_string(Config::configuration[2].lbool[4].second), WHITE, true, BLACK, true);
         pD3D.DrawString(100, i + j * 8, "Toggle NoFlash " + to_string(Config::configuration[5].lbool[0].second), WHITE, true, BLACK, true);
         pD3D.DrawString(100, i + j * 9, "Toggle Bhop " + to_string(Config::configuration[5].lbool[1].second), WHITE, true, BLACK, true);
         pD3D.DrawString(100, i + j * 10, "Toggle ESP " + to_string(Config::ESP), WHITE, true, BLACK, true);
         pD3D.DrawString(100, i + j * 11, "Toggle TriggerBot " + to_string(Config::Trigger), WHITE, true, BLACK, true);
         pD3D.DrawString(100, i + j * 12, "Toggle ShitTalk " + to_string(Config::configuration[5].lbool[2].second), WHITE, true, BLACK, true);
         pD3D.DrawString(100, i + j * 13, "Toggle TriggerBot PSilent " + to_string(Config::TriggerSilent), WHITE, true, BLACK, true);
 
         */
    }
}

long __stdcall Hooks::EndScene(IDirect3DDevice9* pDevice)
{
  
    if (Config::NeoESP) {
        int height, width;
        Interfaces::Engine->GetScreenSize(width, height);
        if (pD3D.Device != pDevice or (!pD3D.Line))
        {
            if(pD3D.Device)pD3D.Destruct();
            pD3D.init(pDevice);
            Config::configuration[0].lbool[3].second = width;
            Config::configuration[0].lbool[2].second = height;
        }

        if ((GetAsyncKeyState(0x30) & 0x0001) and width != 0 and height != 0)
        {
            if( Config::configuration[1].lbool[0].second)pD3D.Destruct();
            Config::configuration[1].lbool[0].second = !Config::configuration[1].lbool[0].second;
            if (Config::configuration[1].lbool[0].second)pD3D.init(pDevice);
            if (Config::configuration[1].lbool[0].second)
            {
                if (Interfaces::Engine->IsInGame())Interfaces::Engine->ClientCmd("cl_mouseenable 0");
            }
            else
            {
                if (Interfaces::Engine->IsInGame())Interfaces::Engine->ClientCmd("cl_mouseenable 1");
            }
        }
        if (Config::configuration[1].lbool[0].second and Config::NeoESP and  width != 0 and height != 0)
        {

            printmenu();


            POINT pep;
            if (GetCursorPos(&pep))
            {
                HWND hWnd = GetForegroundWindow();

                if (ScreenToClient(hWnd, &pep))
                {
                    pD3D.DrawCross(pep.x, pep.y, 50, 5, ORANGE, true, 1, BLACK);

                    if (GetAsyncKeyState(0x01) & 0x0001)
                    {
                        for (int i = 0; i < Config::BoolSettings.size(); ++i)
                        {
                            int middle, xx, y, yy;
                            if (i < pD3D.vpages[pD3D.actpage].boxes.size())
                            {

                                middle = pD3D.vpages[pD3D.actpage].boxes[i].middle;
                                xx = pD3D.vpages[pD3D.actpage].boxes[i].xx;
                                y = pD3D.vpages[pD3D.actpage].boxes[i].y;
                                yy = pD3D.vpages[pD3D.actpage].boxes[i].yy;

                                if (pep.x > middle and pep.x < xx and pep.y > y and pep.y < yy)
                                {
                                    Config::BoolSettings[i].second = !Config::BoolSettings[i].second;
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    return oEndScene(pDevice);
}
