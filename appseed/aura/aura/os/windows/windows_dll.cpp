#include "framework.h"

/*BEGIN_EXTERN_C

BOOL WINAPI openssl_DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved);

END_EXTERN_C*/
#ifndef CUBE
#ifdef METROWIN
[Session::MTAThread]
#endif
BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
   
   //Sleep(30000);

//   ASSERT(FALSE);

   xxdebug_box("aura.dll DllMain (0)", "box", MB_OK);

   UNREFERENCED_PARAMETER(hInstance);
   UNREFERENCED_PARAMETER(lpReserved);


   //openssl_DllMain(hInstance, dwReason, lpReserved);


   if (dwReason == DLL_PROCESS_ATTACH)
   {

      output_debug_string(L"aura.dll initializing!\n");

      xxdebug_box("aura.dll DllMain", "box", MB_OK);
      
   }
   else if (dwReason == DLL_PROCESS_DETACH)
   {




      output_debug_string(L"aura.dll terminating!\n");


   }

   return 1;   // ok

}

#endif



#include "framework.h"


#ifndef CUBE

#ifdef METROWIN
[MTAThread]
#endif
WINBOOL CLASS_DECL_AURA _001DefaultDllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{

   char sz[1024];

   ::GetModuleFileNameEx(::GetCurrentProcess(), hInstance, sz, sizeof(sz));

   char sz2[1024];

   strcpy(sz2, strrchr(sz, '\\'));

   strcpy(sz, sz2 + 1);



   UNREFERENCED_PARAMETER(hInstance);

   UNREFERENCED_PARAMETER(lpReserved);

   if (dwReason == DLL_PROCESS_ATTACH)
   {
      
      strcat(sz, " ::initializing!\n");

      ::output_debug_string(sz);

   }
   else if (dwReason == DLL_PROCESS_DETACH)
   {

      strcat(sz, " ::terminating!\n");

      ::output_debug_string(sz);

   }

   return 1;   // ok

}


#endif