#include "Hooks.h"
#include "D3D.h"
#include "Entity.h"
#include "Config.h"
#include <iso646.h>

long __stdcall Hooks::Reset(IDirect3DDevice9* pDevice, DWORD Count, CONST D3DRECT* pRects, DWORD Flags, D3DCOLOR Color, float Z, DWORD Stencil)
 {
    int height, width;
    Interfaces::Engine->GetScreenSize(width, height);
    
    if (width != General.getwidth() or height != General.getheight())
    { 
        if (Direct3D.ini) {
            Direct3D.Font->OnResetDevice();
            Direct3D.Font20->OnResetDevice();
            Direct3D.Line->OnResetDevice();
        }
        bool b4 = false;
        if (General.getUI()) {
            General.setUI(false);
            b4 = true;
        }
     

        if (b4)General.setUI(true);
    }

    return oReset(pDevice, Count, pRects, Flags, Color, Z, Stencil);
    }
