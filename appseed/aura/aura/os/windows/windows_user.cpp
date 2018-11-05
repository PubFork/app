
#include "framework.h"




CLASS_DECL_AURA HMONITOR GetUiMonitorHandle(HWND hwnd)
{

   return MonitorFromWindow(hwnd, MONITOR_DEFAULTTOPRIMARY);

}


CLASS_DECL_AURA HMONITOR GetPrimaryMonitorHandle()
{

   const POINT ptZero = { 0,0 };

   return MonitorFromPoint(ptZero, MONITOR_DEFAULTTOPRIMARY);

}


CLASS_DECL_AURA bool GetPrimaryMonitorRect(LPRECT lprect)
{

   MONITORINFO mi;

   ZERO(mi);

   mi.cbSize = sizeof(MONITORINFO);

   if (GetMonitorInfo(GetPrimaryMonitorHandle(), &mi))
   {

      *lprect = mi.rcMonitor;

   }
   else
   {

      if (!::GetWindowRect(::get_desktop_window(), lprect))
      {

         return false;

      }

   }

   return true;

}

