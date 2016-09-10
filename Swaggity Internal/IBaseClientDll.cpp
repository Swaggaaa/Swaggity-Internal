#include "IBaseClientDll.h"
#include "Interfaces.h"

ClientClass* IBaseClientDll::GetAllClasses()
{
    typedef ClientClass*(__thiscall* OriginalFn)(void*);
    return GetVFunc<OriginalFn>(this, 8)(this);
}
