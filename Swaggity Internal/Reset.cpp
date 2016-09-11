#include "Hooks.h"

long __stdcall Hooks::Reset(IDirect3DDevice9* pDevice, DWORD Count, CONST D3DRECT* pRects, DWORD Flags, D3DCOLOR Color, float Z, DWORD Stencil)
{
    return oReset(pDevice, Count, pRects, Flags, Color, Z, Stencil);
}