#include "aura/aura/aura/aura.h"


#ifdef _WIN32
extern "C"
{
#undef APPMACROS_ONLY
#include <openssl/ms/applink.c>
}
#endif

extern
::aura::PFN_GET_NEW_APP g_pfnNewApp;

BEGIN_EXTERN_C

int32_t WINAPI _tWinMain(HINSTANCE hinstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int32_t nCmdShow)
{
   if (!defer_aura_init())
      return -1;

   g_pfnNewApp = &get_acid_app;

   int iReturn = node_main(hinstance, hPrevInstance, lpCmdLine, nCmdShow);

   defer_aura_term();

   return iReturn;

}

END_EXTERN_C

