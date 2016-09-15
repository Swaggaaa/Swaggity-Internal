#pragma once
#include <cstring>
#include "Windows.h"

class VMTSwag
{
    DWORD** tableBase;
    DWORD*  oldVMT;
    DWORD*  newVMT;
    UINT   size;

public:
    VMTSwag();

    explicit VMTSwag(DWORD** base);

    ~VMTSwag();
    void UnHook();
    void ReHook();
    DWORD hookFunc(DWORD fn, UINT index) const;

    DWORD getFuncAddress(UINT index) const;

    static UINT getFuncCount(DWORD* vmt);
};