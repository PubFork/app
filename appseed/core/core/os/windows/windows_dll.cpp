#include "framework.h"

#ifndef CUBE

#ifdef METROWIN
[MTAThread]
#endif
BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{

   xxdebug_box("core.dll DllMain (0)", "box", MB_OK);

   UNREFERENCED_PARAMETER(hInstance);

   UNREFERENCED_PARAMETER(lpReserved);

   if (dwReason == DLL_PROCESS_ATTACH)
   {

      output_debug_string(L"core.dll initializing.\n");

      xxdebug_box("core.dll initializing", "box", MB_OK);

   }
   else if (dwReason == DLL_PROCESS_DETACH)
   {

      output_debug_string(L"core.dll terminating.\n");

   }
   else if (dwReason == DLL_THREAD_ATTACH)
   {

      xxdebug_box("core.dll DllMain", "box", MB_OK);

   }
   else if (dwReason == DLL_THREAD_DETACH)
   {

   }

   return 1;

}

#endif
