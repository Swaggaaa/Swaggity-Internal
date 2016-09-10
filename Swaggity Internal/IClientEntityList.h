#pragma once

class CBaseEntity;

class IClientEntityList
{
public:
    virtual void align1() = 0;
    virtual void align2() = 0;
    virtual void align3() = 0;

    virtual CBaseEntity*	GetClientEntity(int iIndex) = 0;
    virtual CBaseEntity*	GetClientEntityFromHandle(DWORD hHandle) = 0;
    virtual int				NumberOfEntities(bool bIncludeNonNetworkable) = 0;
    virtual int				GetHighestEntityIndex() = 0;
};