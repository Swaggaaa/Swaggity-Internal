#pragma once
#include "Entity.h"
#include "IEngineTrace.h"

#define	CONTENTS_EMPTY			0		// No contents

#define	CONTENTS_SOLID			0x1		// an eye is never valid in a solid
#define	CONTENTS_WINDOW			0x2		// translucent, but not watery (glass)
#define	CONTENTS_AUX			0x4
#define	CONTENTS_GRATE			0x8		// alpha-tested "grate" textures.  Bullets/sight pass through, but solids don't
#define	CONTENTS_SLIME			0x10
#define	CONTENTS_WATER			0x20
#define	CONTENTS_BLOCKLOS		0x40	// block AI line of sight
#define CONTENTS_OPAQUE			0x80	// things that cannot be seen through (may be non-solid though)
#define	LAST_VISIBLE_CONTENTS	0x80

#define ALL_VISIBLE_CONTENTS (LAST_VISIBLE_CONTENTS | (LAST_VISIBLE_CONTENTS-1))

#define CONTENTS_TESTFOGVOLUME	0x100
#define CONTENTS_UNUSED			0x200	

// unused 
// NOTE: If it's visible, grab from the top + update LAST_VISIBLE_CONTENTS
// if not visible, then grab from the bottom.
#define CONTENTS_UNUSED6		0x400

#define CONTENTS_TEAM1			0x800	// per team contents used to differentiate collisions 
#define CONTENTS_TEAM2			0x1000	// between players and objects on different teams

// ignore CONTENTS_OPAQUE on surfaces that have SURF_NODRAW
#define CONTENTS_IGNORE_NODRAW_OPAQUE	0x2000

// hits entities which are MOVETYPE_PUSH (doors, plats, etc.)
#define CONTENTS_MOVEABLE		0x4000

// remaining contents are non-visible, and don't eat brushes
#define	CONTENTS_AREAPORTAL		0x8000

#define	CONTENTS_PLAYERCLIP		0x10000
#define	CONTENTS_MONSTERCLIP	0x20000

// currents can be added to any other contents, and may be mixed
#define	CONTENTS_CURRENT_0		0x40000
#define	CONTENTS_CURRENT_90		0x80000
#define	CONTENTS_CURRENT_180	0x100000
#define	CONTENTS_CURRENT_270	0x200000
#define	CONTENTS_CURRENT_UP		0x400000
#define	CONTENTS_CURRENT_DOWN	0x800000

#define	CONTENTS_ORIGIN			0x1000000	// removed before bsping an entity

#define	CONTENTS_MONSTER		0x2000000	// should never be on a brush, only in game
#define	CONTENTS_DEBRIS			0x4000000
#define	CONTENTS_DETAIL			0x8000000	// brushes to be added after vis leafs
#define	CONTENTS_TRANSLUCENT	0x10000000	// auto set if any surface has trans
#define	CONTENTS_LADDER			0x20000000
#define CONTENTS_HITBOX			0x40000000	// use accurate hitboxes on trace

#define	MASK_SHOT					(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_MONSTER|CONTENTS_WINDOW|CONTENTS_DEBRIS|CONTENTS_HITBOX)

class VectorAligned : public Vector
{
public:
    VectorAligned() {}

    VectorAligned(const Vector &vec)
    {
        this->x = vec.x;
        this->y = vec.y;
        this->z = vec.z;
    }

    float w;
};

enum TraceType_t
{
    TRACE_EVERYTHING = 0,
    TRACE_WORLD_ONLY,				// NOTE: This does *not* test static props!!!
    TRACE_ENTITIES_ONLY,			// NOTE: This version will *not* test static props
    TRACE_EVERYTHING_FILTER_PROPS,	// NOTE: This version will pass the IHandleEntity for props through the filter, unlike all other filters
};

struct Ray_t
{
    Ray_t() { }

    VectorAligned		m_Start;
    VectorAligned		m_Delta;
    VectorAligned		m_StartOffset;
    VectorAligned		m_Extents;
    const matrix3x4_t	*m_pWorldAxisTransform;
    bool				m_IsRay;
    bool				m_IsSwept;

    void Init(Vector vecStart, Vector vecEnd)
    {
        m_Delta = VectorAligned(vecEnd - vecStart);
        m_IsSwept = (m_Delta.LengthSqr() != 0);
        m_Extents.Zero();
        m_pWorldAxisTransform = NULL;
        m_IsRay = true;
        m_StartOffset.Zero();
        m_Start = vecStart;
    }
};

struct cplane_t
{
    Vector	normal;
    float	dist;
    byte	type;
    byte	signbits;
    byte	pad[2];
};

class ITraceFilter
{
public:
    virtual bool ShouldHitEntity(CBaseEntity* pEntityHandle, int contentsMask)
    {
        return !(pEntityHandle == pSkip);
    }
    virtual TraceType_t	GetTraceType()
    {
        return TRACE_EVERYTHING;
    }
    void* pSkip;
};

class CTraceFilter : public ITraceFilter
{
public:
    virtual bool ShouldHitEntity(CBaseEntity* pEntityHandle, int contentsMask)
    {
        return !(pEntityHandle == pSkip);
    }

    virtual TraceType_t	GetTraceType() const
    {
        return TRACE_EVERYTHING;
    }
    void* pSkip;
};

class CTraceFilterSkipTwoEntities : public ITraceFilter
{
public:
    CTraceFilterSkipTwoEntities(void *pPassEnt1, void *pPassEnt2)
    {
        pPassEntity1 = pPassEnt1;
        pPassEntity2 = pPassEnt2;
    }

    virtual bool ShouldHitEntity(CBaseEntity *pEntityHandle, int contentsMask)
    {
        return !(pEntityHandle == pPassEntity1 || pEntityHandle == pPassEntity2);
    }

    virtual TraceType_t GetTraceType() const
    {
        return TRACE_EVERYTHING;
    }

    void *pPassEntity1;
    void *pPassEntity2;
};

typedef bool(*ShouldHitFunc_t)(IHandleEntity *pHandleEntity, int contentsMask);

class CTraceFilterSimple : public CTraceFilter
{
public:
    // It does have a base, but we'll never network anything below here..
    CTraceFilterSimple(const IHandleEntity *passentity, int collisionGroup, ShouldHitFunc_t pExtraShouldHitCheckFn = NULL);
    virtual bool ShouldHitEntity(IHandleEntity *pHandleEntity, int contentsMask);
    virtual void SetPassEntity(const IHandleEntity *pPassEntity) { m_pPassEnt = pPassEntity; }
    virtual void SetCollisionGroup(int iCollisionGroup) { m_collisionGroup = iCollisionGroup; }

    const IHandleEntity *GetPassEntity(void) { return m_pPassEnt; }

private:
    const IHandleEntity *m_pPassEnt;
    int m_collisionGroup;
    ShouldHitFunc_t m_pExtraShouldHitCheckFunction;

};

class CBaseTrace
{
public:
    Vector			startpos;
    Vector			endpos;
    cplane_t		plane;

    float			fraction;

    int				contents;
    unsigned short	dispFlags;

    bool			allsolid;
    bool			startsolid;

    CBaseTrace() {}
};

struct csurface_t
{
    const char*		name;
    short			surfaceProps;
    unsigned short	flags;
};

class CGameTrace : public CBaseTrace
{
public:
    bool                    DidHitWorld() const;
    bool                    DidHitNonWorldEntity() const;
    int                     GetEntityIndex() const;
    bool                    DidHit() const;
    bool					IsVisible() const;

public:

    float                   fractionleftsolid;
    csurface_t              surface;
    int                     hitgroup;
    short                   physicsbone;
    unsigned short          worldSurfaceIndex;
    CBaseEntity*            m_pEnt;
    int                     hitbox;

    CGameTrace() { }

private:
    CGameTrace(const CGameTrace& vOther);
};

typedef CGameTrace trace_t;