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
    ORANGE = D3DCOLOR_ARGB(255, 255, 125, 0),
};

#pragma warning (disable : 4244)

void drawRage(){

	Direct3D.vpages[0].checkboxes[0].checked = General.getRageAimbot();
	Direct3D.vpages[0].checkboxes[0].write = "Aimbot";
	Direct3D.DrawCheck(Direct3D.vpages[0].checkboxes[0],true);

	Direct3D.vpages[0].checkboxes[1].checked = General.getAutoShoot();
	Direct3D.vpages[0].checkboxes[1].write = "AutoShoot";
	Direct3D.DrawCheck(Direct3D.vpages[0].checkboxes[1], true);



}

void printoverlay()
{

    for (int j = 0; j < Direct3D.overlay.boxes.size(); ++j)
    {
        int x, y, xx, yy, middle;
        x = Direct3D.overlay.boxes[j].x + General.movex;
        y = Direct3D.overlay.boxes[j].y + General.movey;
        xx = Direct3D.overlay.boxes[j].xx + General.movex;
        yy = Direct3D.overlay.boxes[j].yy + General.movey;
        bool line = Direct3D.overlay.boxes[j].line;
        D3DCOLOR rolm = Direct3D.overlay.boxes[j].linecolourin;

        Direct3D.DrawRect(x, y, xx - x, yy - y, 1, Direct3D.overlay.boxes[j].colourin, true, line, 1, rolm);
    }

    for (int j = 0; j < Direct3D.overlay.boxes4.size(); ++j)
    {
        int x, y, xx, yy;
        x = Direct3D.overlay.boxes4[j].x + General.movex;
        y = Direct3D.overlay.boxes4[j].y + General.movey;
        xx = Direct3D.overlay.boxes4[j].xx + General.movex;
        yy = Direct3D.overlay.boxes4[j].yy + General.movey;

        bool line = Direct3D.overlay.boxes4[j].line;
        D3DCOLOR rolm = Direct3D.overlay.boxes4[j].linecolourin;
        if (General.viewoptions[j].second)Direct3D.DrawRect(x, y, xx - x, yy - y, 1, D3D::BLUE2, true, line, 1, rolm);
        else Direct3D.DrawRect(x, y, xx - x, yy - y, 1, Direct3D.overlay.boxes4[j].colourin, true, line, 1, rolm);
    }

    Direct3D.DrawString(Direct3D.overlay.Titulo.x + General.movex, Direct3D.overlay.Titulo.y + General.movey, Direct3D.overlay.Titulo.write, Direct3D.overlay.Titulo.colourin, Direct3D.overlay.Titulo.line, Direct3D.overlay.Titulo.linecolourin, false, 20);

    for (int i = 0; i < Direct3D.overlay.labels.size(); ++i) {

        int x, y, xx, yy, middle;
        x = Direct3D.overlay.labels[i].x + General.movex;
        y = Direct3D.overlay.labels[i].y + General.movey;

        string kek = Direct3D.overlay.labels[i].write;
        bool line = Direct3D.overlay.labels[i].line;
        D3DCOLOR rolm = Direct3D.overlay.labels[i].linecolourin;


        Direct3D.DrawString(x, y, kek, Direct3D.overlay.labels[i].colourin, line, rolm, false, 20);

    }
   
	/*   checkbox rolf;
    rolf.x = 500;
    rolf.y = 500;
    rolf.size = 15;
    rolf.distance = 3;
    rolf.boxcolor = BLACK;
    rolf.checkedcolor = D3D::BLUE2;
    rolf.checked = false;
    rolf.write = "fucking boss";
    Direct3D.DrawCheck(rolf,true);

    rolf.x = 400;
    rolf.y = 400;
    rolf.checked = true;

    Direct3D.DrawCheck(rolf,true);

	*/
    
}

void checkoverlay(POINT kek)
{
    for (int i = 0; i < Direct3D.overlay.boxes4.size();++i)
    {
       if(i >= Direct3D.overlay.labels.size()){}
       if(kek.x > ( Direct3D.overlay.labels[i].x  + General.movex )and kek.x < ( Direct3D.overlay.boxes4[i].xx + General.movex) and kek.y > ( Direct3D.overlay.boxes4[i].y + General.movey) and kek.y < ( Direct3D.overlay.boxes4[i].yy + General.movey))
       {
           General.viewoptions[i].second = true;
           for (int j = 0; j < General.viewoptions.size();++j)
           {
               if (j == i)continue;
               General.viewoptions[j].second = false;
           }
       }
    }
}

long __stdcall Hooks::EndScene(IDirect3DDevice9* pDevice)
{
    if (Direct3D.Device)Direct3D.Destruct();
    Direct3D.init(pDevice);

    if (General.getESPv2())
    {
        int height, width;
        Interfaces::Engine->GetScreenSize(width, height);
        
        // General.setwidth(width);
        // General.setheight(height);


        if ((GetAsyncKeyState(0x30) & 0x0001) and width != 0 and height != 0)
        {
            //  if( General.getUI())Direct3D.Destruct();
            General.setUI(!General.getUI());

            if (General.getUI())
            {
                Direct3D.init(pDevice);
                if (Interfaces::Engine->IsInGame())Interfaces::Engine->ClientCmd("cl_mouseenable 0");
            }
            else
            {
                if (Interfaces::Engine->IsInGame())Interfaces::Engine->ClientCmd("cl_mouseenable 1");
            }
        }
        if (General.getUI() and width != 0 and height != 0)
        {
       

            printoverlay();
			if (General.viewoptions[0].second)drawRage();
			if (Global::LocalPlayer) {
			//	Vector rekt = Global::LocalPlayer->GetVelocity();

			}

             

            POINT pep;
            if (GetCursorPos(&pep))
            {
                HWND hWnd = GetForegroundWindow();
				

				if (ScreenToClient(hWnd, &pep))
				{
					if (General.move)
					{
						General.movex += pep.x - General.xmouse;
						General.movey += pep.y - General.ymouse;
						General.xmouse = pep.x;
						General.ymouse = pep.y;
					}
					Direct3D.DrawCross(pep.x, pep.y, 10, 2, D3D::BLUE2, true, 1, BLACK);

					Direct3D.DrawString(10, 10, to_string(pep.x) + ' ' + to_string(pep.y), YELLOW, true, BLACK, false, 18);

					if (GetAsyncKeyState(0x01) & 0x0001)
					{
						checkoverlay(pep);
					//	General.move = false;
					}
					else if (GetAsyncKeyState(0x01) & 0x8000)
					{
						General.mpressed = true;
						if (pep.x > (Direct3D.overlay.boxes[0].x + General.movex) and pep.x < (Direct3D.overlay.boxes[0].xx + General.movex) and pep.y >(Direct3D.overlay.boxes[0].y + General.movey) and pep.y < (Direct3D.overlay.boxes[1].y + General.movey)) {
							//General.movex +=  pep.x - General.xmouse ;
							//General.movey += pep.y - General.ymouse;
							General.move = true;
						}

					}
					else
					{
						if (General.mpressed)General.move = false;
						General.xmouse = pep.x;
						General.ymouse = pep.y;
					}

				}

				
            }
         
        }
       
    }
     Direct3D.Destruct();
    return oEndScene(pDevice);
}
