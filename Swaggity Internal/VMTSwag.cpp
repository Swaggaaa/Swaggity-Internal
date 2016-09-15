#include "VMTSwag.h"
#include <ostream>
#include <iostream>

DWORD VMTSwag::hookFunc(DWORD fn, UINT index) const
{
    if (index >= size || !oldVMT || !newVMT)
        return NULL;

    newVMT[index] = fn;
    return oldVMT[index];
    //Yo no quiero hacer lo correcto
    //Pa' esa puta mierda ya no tengo tiempo
    //No vas a escucharme un lamento
    //Pa' esa puta mierda ya no tengo tiempo
    //Antes de morir quiero el cielooooooo
    //El ciento por cientooooo
    //Antes de morir quiero el cieloooooooo
    //El ciento por ciento por cierto
    //Antes de que muera yooo...
}

VMTSwag::VMTSwag()
{
    memset(this, 0, sizeof(VMTSwag));
}

VMTSwag::VMTSwag(DWORD ** base)
{
    tableBase = base;
    oldVMT = *base;
    size = getFuncCount(*base);
    newVMT = new DWORD[size];
    memcpy(newVMT, oldVMT, sizeof(DWORD) * size);
    //Now it will point to our new VMT
    *base = newVMT;
}

VMTSwag::~VMTSwag()
{
    UnHook();
}

void VMTSwag::UnHook()
{
    if (tableBase) //Initialized?
        *tableBase = oldVMT; //Point to old VMT
}

void VMTSwag::ReHook()
{
    if (tableBase)
        *tableBase = newVMT;
}

DWORD VMTSwag::getFuncAddress(UINT index) const
{
    if (index >= size)
        return NULL;

    return oldVMT[index];
}


UINT VMTSwag::getFuncCount(DWORD * vmt)
{
    UINT i = 0;
    while (!IS_INTRESOURCE(vmt[i]))
        ++i;

    std::cout << std::uppercase << "Number of funcs is: 0x" << i << std::endl;
    return i;
}

