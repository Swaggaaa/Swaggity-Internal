#include "Hooks.h"
#include "D3D.h"
#include "Entity.h"
#include "Config.h"
#include <iso646.h>

long __stdcall Hooks::Reset(IDirect3DDevice9* pDevice, DWORD Count, CONST D3DRECT* pRects, DWORD Flags, D3DCOLOR Color, float Z, DWORD Stencil)
 {
    int height, width;
    Interfaces::Engine->GetScreenSize(width, height);
    
    if (pD3D.Device != pDevice or (!pD3D.Line)  or width != Config::configuration[0].lbool[3].second or height != Config::configuration[0].lbool[2].second)
    { 
        bool b4 = false;
        if (Config::configuration[1].lbool[2].second) {
            Config::configuration[1].lbool[2].second = false;
            b4 = true;
        }
      //  if(pD3D.Device)pD3D.Destruct();

        if (b4)Config::configuration[1].lbool[2].second = true;
    }

    return oReset(pDevice, Count, pRects, Flags, Color, Z, Stencil);
    }
