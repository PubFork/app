#include "framework.h"

#ifdef WINDOWS

#ifdef TRANQUILLUMWIN
[MTAThread]
#endif
BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{


   UNREFERENCED_PARAMETER(hInstance);
   UNREFERENCED_PARAMETER(lpReserved);


   if (dwReason == DLL_PROCESS_ATTACH)
   {


      ::output_debug_string(L"wndfrm_tranquillum.dll :: initializing!\n");


   }
   else if (dwReason == DLL_PROCESS_DETACH)
   {


      ::output_debug_string(L"wndfrm_tranquillum.dll :: terminating!\n");


   }

   return 1;   // ok

}


#endif




