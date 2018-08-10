#include "framework.h"

#ifdef WINDOWS

#ifdef METROWIN
[MTAThread]
#endif
extern "C" int32_t WINAPI DllMain(HINSTANCE hInstance, uint32_t dwReason, LPVOID)
{

   if (dwReason == DLL_PROCESS_ATTACH)
   {

      ::output_debug_string(L"sphere.dll initializing.\n");

   }
   else if (dwReason == DLL_THREAD_DETACH)
   {

   }
   else if (dwReason == DLL_PROCESS_DETACH)
   {

      ::output_debug_string(L"sphere.dll terminating.\n");

   }

   return TRUE;

}

#endif


