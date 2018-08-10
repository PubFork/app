#include "framework.h"

#ifdef METROWIN

#include <Psapi.h>

#endif

#ifndef METROWIN
#ifndef CUBE
#ifdef METROWIN
[Platform::MTAThread]
#endif
BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{

   xxdebug_box("aura.dll DllMain (0)", "box", MB_OK);

   UNREFERENCED_PARAMETER(hInstance);

   UNREFERENCED_PARAMETER(lpReserved);

   if (dwReason == DLL_PROCESS_ATTACH)
   {

      output_debug_string(L"aura.dll initializing.\n");

      xxdebug_box("aura.dll DllMain", "box", MB_OK);

   }
   else if (dwReason == DLL_PROCESS_DETACH)
   {

      output_debug_string(L"aura.dll terminating.\n");

   }

   return 1;

}

#endif
#endif


#include "framework.h"


#ifndef CUBE

#ifdef METROWIN
[MTAThread]
#endif
WINBOOL CLASS_DECL_AURA _001DefaultDllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{

   wchar_t wsz[1024];

   ::GetModuleFileNameExW(::GetCurrentProcess(), hInstance, wsz, sizeof(wsz) / sizeof(wchar_t));

   wchar_t wsz2[1024];

   wcscpy(wsz2, wcsrchr(wsz, '\\'));

   wcscpy(wsz, wsz2 + 1);

   UNREFERENCED_PARAMETER(hInstance);

   UNREFERENCED_PARAMETER(lpReserved);

   if (dwReason == DLL_PROCESS_ATTACH)
   {

      wcscat(wsz, L" initializing.\n");

      ::output_debug_string(wsz);

   }
   else if (dwReason == DLL_PROCESS_DETACH)
   {

      wcscat(wsz, L" terminating.\n");

      ::output_debug_string(wsz);

   }

   return 1;

}

#endif



