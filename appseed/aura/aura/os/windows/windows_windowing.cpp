#include "framework.h"



CLASS_DECL_AURA void defer_dock_application(bool bDock)
{

   UNREFERENCED_PARAMETER(bDock);

}



CLASS_DECL_AURA bool os_init_windowing()
{

   return true;

}


CLASS_DECL_AURA void os_term_windowing()
{

}



::user::interaction * get_system_window_interaction(::os_system_window * psystemwindow)
{

   return NULL;

}

