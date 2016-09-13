#include "Hooks.h"
#include "D3D.h"
#include "Entity.h"
#include "Config.h"
#include <iso646.h>

long __stdcall Hooks::Reset(IDirect3DDevice9* pDevice, DWORD Count, CONST D3DRECT* pRects, DWORD Flags, D3DCOLOR Color, float Z, DWORD Stencil)
 {
    int height, width;
    Interfaces::Engine->GetScreenSize(width, height);
    
    if (pD3D.Device != pDevice or (!pD3D.Line)  or width != General.getwidth() or height != General.getheight())
    { 
        bool b4 = false;
        if (General.getUI()) {
            General.setUI(false);
            b4 = true;
        }
      //  if(pD3D.Device)pD3D.Destruct();

        if (b4)General.setUI(true);
    }

    return oReset(pDevice, Count, pRects, Flags, Color, Z, Stencil);
    }
