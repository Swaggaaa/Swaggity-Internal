#include "Hooks.h"
#include <cstdio>
#include <iostream>
#include "IEngineTrace.h"
#include "Cheat.h"
#include "RayTrace.h"

#pragma warning (disable : 4244)

long __stdcall Hooks::EndScene(IDirect3DDevice9 *pDevice)
{
    return oEndScene(pDevice);
}
