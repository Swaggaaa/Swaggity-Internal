#pragma once
#include "SDK.h"

class IPhysicsSurfaceProps;
struct soundlevel_t;
enum PLAYER_ANIM;

class IMoveHelper
{
public:
    // Call this to set the singleton
    static IMoveHelper* GetSingleton() { return sm_pSingleton; }

    // Methods associated with a particular entity
    virtual	char const*		GetName(EntityHandle_t handle) const = 0;

    // sets the entity being moved
    virtual void	SetHost(CBaseEntity *host) = 0;

    // Adds the trace result to touch list, if contact is not already in list.
    virtual void	ResetTouchList(void) = 0;
    virtual bool	AddToTouched(const CGameTrace& tr, const Vector& impactvelocity) = 0;
    virtual void	ProcessImpacts(void) = 0;

    // Numbered line printf
    virtual void	Con_NPrintf(int idx, char const* fmt, ...) = 0;

    // These have separate server vs client impementations
    virtual void	StartSound(const Vector& origin, int channel, char const* sample, float volume, soundlevel_t soundlevel, int fFlags, int pitch) = 0;
    virtual void	StartSound(const Vector& origin, const char *soundname) = 0;
    virtual void	PlaybackEventFull(int flags, int clientindex, unsigned short eventindex, float delay, Vector& origin, Vector& angles, float fparam1, float fparam2, int iparam1, int iparam2, int bparam1, int bparam2) = 0;

    // Apply falling damage to m_pHostPlayer based on m_pHostPlayer->m_flFallVelocity.
    virtual bool	PlayerFallingDamage(void) = 0;

    // Apply falling damage to m_pHostPlayer based on m_pHostPlayer->m_flFallVelocity.
    virtual void	PlayerSetAnimation(PLAYER_ANIM playerAnim) = 0;

    virtual IPhysicsSurfaceProps *GetSurfaceProps(void) = 0;

    virtual bool IsWorldEntity(const CBaseHandle &handle) = 0;

protected:
    // Inherited classes can call this to set the singleton
    static void SetSingleton(IMoveHelper* pMoveHelper) { sm_pSingleton = pMoveHelper; }

    // Clients shouldn't call delete directly
    virtual			~IMoveHelper() {}

    // The global instance
    static IMoveHelper* sm_pSingleton;
};
