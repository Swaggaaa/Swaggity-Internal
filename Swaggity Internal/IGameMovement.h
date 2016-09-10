#pragma once
#include <sal.h>
#define PRINTF_FORMAT_STRING _Printf_format_string_

class Vector;
class CMoveData;

class IGameMovement
{
public:
    virtual			~IGameMovement(void) {}

    // Process the current movement command
    virtual void	ProcessMovement(CBaseEntity *pPlayer, void* mv) = 0;
    virtual void    padding() = 0; //Fixed ESP Crash
    virtual void	StartTrackPredictionErrors(CBaseEntity *pPlayer) = 0;
    virtual void	FinishTrackPredictionErrors(CBaseEntity *pPlayer) = 0;
    virtual void	DiffPrint(PRINTF_FORMAT_STRING char const *fmt, ...) = 0;   //Removed 1 param because WHAT ARE THOOOOOOOOOSE

    // Allows other parts of the engine to find out the normal and ducked player bbox sizes
    virtual Vector	GetPlayerMins(bool ducked) const = 0;
    virtual Vector	GetPlayerMaxs(bool ducked) const = 0;
    virtual Vector  GetPlayerViewOffset(bool ducked) const = 0;

};
