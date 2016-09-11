#pragma once
#include "VMTSwag.h"
#include "CUserCmd.h"
#include <d3d9.h>
#include <d3dx9.h>
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

typedef bool(__fastcall *CreateMoveFn)(void*, void*, float, CUserCmd*);
extern CreateMoveFn oCreateMove;
    
typedef void(__fastcall *PaintTraverseFn)(void*, void*, unsigned int, bool, bool);
extern PaintTraverseFn oPaintTraverse;

typedef void(__stdcall *OverrideViewFn)(CViewSetup*);
extern OverrideViewFn oOverrideView;

typedef void(__thiscall *FrameStageNotifyFn)(void*, ClientFrameStage_t);
extern FrameStageNotifyFn oFrameStageNotify;

typedef long(__stdcall *EndSceneFn)(IDirect3DDevice9*);
extern EndSceneFn oEndScene;

typedef long(__stdcall *ResetFn)(IDirect3DDevice9*, DWORD, CONST D3DRECT*, DWORD, D3DCOLOR, float, DWORD);
extern ResetFn oReset;


namespace Hooks
{
    extern VMTSwag* Client;
    extern VMTSwag* ClientMode;
    extern VMTSwag* Events;
    extern VMTSwag* Surface;
    extern VMTSwag* VPanel;
    extern VMTSwag* D3D9;
    bool __fastcall CreateMove(void* thisptr, void* edx, float flInputSampleTime, CUserCmd* cmd);
    void __stdcall OverrideView(CViewSetup* pViewSetup);
    void __fastcall FrameStageNotify(void* ecx, void* edx, ClientFrameStage_t frameStage);
    void __fastcall PaintTraverse(void* thisptr, void* edx, unsigned int panel, bool forceRepaint, bool allowForce);
    long __stdcall EndScene(IDirect3DDevice9* pDevice);
    long __stdcall Reset(IDirect3DDevice9* pDevice, DWORD Count, CONST D3DRECT* pRects, DWORD Flags, D3DCOLOR Color, float Z, DWORD Stencil);
}