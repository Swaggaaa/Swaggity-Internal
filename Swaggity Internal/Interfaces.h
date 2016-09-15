#pragma once
#include <string>
#include "IEngineClient.h"
#include "IBaseClientDll.h"
#include "IClientEntityList.h"
#include "IClientModeShared.h"
#include "IEngineTrace.h"
#include "IGameEvents.h"
#include "ISurface.h"
#include "IVPanel.h"
#include "IPrediction.h"
#include "IMoveHelper.h"
#include "IGlobalVars.h"
#include "IGameMovement.h"

namespace Interfaces
{
    extern IEngineClient*           Engine;
    extern IEngineTrace*            EngineTrace;
    extern IClientEntityList*       EntityList;
    extern IBaseClientDll*          Client;
    extern IClientModeShared*       ClientMode;
    extern IGameEventManager2*      Events;
    extern ISurface*                Surface;
    extern IVPanel*                 VPanel;
    extern CPrediction*             Prediction;
    extern IMoveHelper*             MoveHelper;
    extern IGlobalVars*             GlobalVars;
    extern IGameMovement*           Movement;
}

template<typename T>
T CreateInterface(const std::string& sModule, const std::string& sInterface)
{
    typedef T (*CreateInterfaceFn)(const char *pName, int *pReturnCode);
	CreateInterfaceFn fn = nullptr;
	
		while (!fn)
		 fn = CreateInterfaceFn(GetProcAddress(GetModuleHandleA(sModule.c_str()), "CreateInterface"));
    return fn(sInterface.c_str(), nullptr);
}

template<typename T>
T GetVFunc(const void* table, const DWORD& index)
{
    return (*(T**)table)[index];
}