#include "framework.h"


BEGIN_EXTERN_C


CLASS_DECL_AURA DWORD get_last_error()
{

   return GetLastError();

}


CLASS_DECL_AURA void set_last_error(DWORD dw)
{

   SetLastError(dw);

}


END_EXTERN_C


