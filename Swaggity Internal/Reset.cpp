#include "Hooks.h"
#include "D3D.h"
#include "Entity.h"
#include "Config.h"
#include <iso646.h>

long __stdcall Hooks::Reset(IDirect3DDevice9* pDevice, DWORD Count, CONST D3DRECT* pRects, DWORD Flags, D3DCOLOR Color, float Z, DWORD Stencil)
 {
    int height, width;
    Interfaces::Engine->GetScreenSize(width, height);
    
    if (width != Config::width or height != Config::height) {
        pD3D.Destruct();
        Config::width = width;
        Config::height = height;
    }

    return oReset(pDevice, Count, pRects, Flags, Color, Z, Stencil);
    }
