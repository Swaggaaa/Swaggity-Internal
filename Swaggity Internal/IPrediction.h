#pragma once
#include "SDK.h"

class CUserCmd;
class CBasePlayer;
class IMoveHelper;
class CMoveData;

class IPrediction
{
public:
    virtual			~IPrediction(void) {};

    virtual void	Init(void) = 0;
    virtual void	Shutdown(void) = 0;

    // Run prediction
    virtual void	Update
        (
            int startframe,				// World update ( un-modded ) most recently received
            bool validframe,			// Is frame data valid
            int incoming_acknowledged,	// Last command acknowledged to have been run by server (un-modded)
            int outgoing_command		// Last command (most recent) sent to server (un-modded)
            ) = 0;

    // We are about to get a network update from the server.  We know the update #, so we can pull any
    //  data purely predicted on the client side and transfer it to the new from data state.
    virtual void	PreEntityPacketReceived(int commands_acknowledged, int current_world_update_packet) = 0;
    virtual void	PostEntityPacketReceived(void) = 0;
    virtual void	PostNetworkDataReceived(int commands_acknowledged) = 0;

    virtual void	OnReceivedUncompressedPacket(void) = 0;

    // The engine needs to be able to access a few predicted values
    virtual void	GetViewOrigin(Vector& org) = 0;
    virtual void	SetViewOrigin(Vector& org) = 0;
    virtual void	GetViewAngles(QAngle& ang) = 0;
    virtual void	SetViewAngles(QAngle& ang) = 0;
    virtual void	GetLocalViewAngles(QAngle& ang) = 0;
    virtual void	SetLocalViewAngles(QAngle& ang) = 0;
};

class CPrediction : public IPrediction
{
    // Construction
public:
    CPrediction(void);
    virtual			~CPrediction(void);
    virtual void	Init(void);
    virtual void	Shutdown(void);
    virtual void	Update(int startframe, bool validframe, int incoming_acknowledged, int outgoing_command);
    virtual void	OnReceivedUncompressedPacket(void);
    virtual void	PreEntityPacketReceived(int commands_acknowledged, int current_world_update_packet);
    virtual void	PostEntityPacketReceived(void);
    virtual void	PostNetworkDataReceived(int commands_acknowledged);
    virtual bool	InPrediction(void) const;
    virtual bool	IsFirstTimePredicted(void) const;
    virtual int		GetIncomingPacketNumber(void) const;

    float			GetIdealPitch(int nSlot) const
    {
        return 0.f;
    }

    // The engine needs to be able to access a few predicted values
    virtual void	GetViewOrigin(Vector& org);
    virtual void	SetViewOrigin(Vector& org);
    virtual void	GetViewAngles(QAngle& ang);
    virtual void	SetViewAngles(QAngle& ang);
    virtual void	GetLocalViewAngles(QAngle& ang);
    virtual void	SetLocalViewAngles(QAngle& ang);
    virtual void    padding1(); //Fixed ESP
    virtual void	CheckMovingGround(CBasePlayer *player, double frametime);
    virtual void	RunCommand(CBasePlayer *player, CUserCmd *ucmd, IMoveHelper *moveHelper);
    float			GetSavedTime() const;
    virtual void	SetupMove(CBaseEntity *player, CUserCmd *ucmd, IMoveHelper *pHelper, void* mv);
    virtual void	FinishMove(CBaseEntity *player, CUserCmd *ucmd, void* mv);
    virtual void	SetIdealPitch(int nSlot, CBasePlayer *player, const Vector& origin, const QAngle& angles, const Vector& viewheight);
    virtual void	CheckError(int nSlot, CBasePlayer *player, int commands_acknowledged);
    // Called before and after any movement processing
    void			StartCommand(CBasePlayer *player, CUserCmd *cmd);
    void			FinishCommand(CBasePlayer *player);
    // Helpers to call pre and post think for player, and to call think if a think function is set
    void			RunPreThink(CBasePlayer *player);
    void			RunThink(CBasePlayer *ent, double frametime);
    void			RunPostThink(CBasePlayer *player);
    virtual void	_Update(int nSlot, bool received_new_world_update, bool validframe, int incoming_acknowledged, int outgoing_command);

    // Actually does the prediction work, returns false if an error occurred
    bool			PerformPrediction(int nSlot, CBasePlayer *localPlayer, bool received_new_world_update, int incoming_acknowledged, int outgoing_command);
    void			ShiftIntermediateDataForward(int nSlot, int slots_to_remove, int previous_last_slot);
    void			RestoreEntityToPredictedFrame(int nSlot, int predicted_frame);
    int				ComputeFirstCommandToExecute(int nSlot, bool received_new_world_update, int incoming_acknowledged, int outgoing_command);
    void			DumpEntity(CBaseEntity *ent, int commands_acknowledged);
    void			ShutdownPredictables(void);
    void			ReinitPredictables(void);
    void			RemoveStalePredictedEntities(int nSlot, int last_command_packet);
    void			RestoreOriginalEntityState(int nSlot);
    void			RunSimulation(int current_command, float curtime, CUserCmd *cmd, CBasePlayer *localPlayer);
    void			Untouch(int nSlot);
    void			StorePredictionResults(int nSlot, int predicted_frame);
    bool			ShouldDumpEntity(CBaseEntity *ent);
    void			SmoothViewOnMovingPlatform(CBasePlayer *pPlayer, Vector& offset);
    void			ResetSimulationTick();
    void			ShowPredictionListEntry(int listRow, int showlist, CBaseEntity *ent, int &totalsize, int &totalsize_intermediate);
    void			FinishPredictionList(int listRow, int showlist, int totalsize, int totalsize_intermediate);
    void			CheckPredictConvar();
};