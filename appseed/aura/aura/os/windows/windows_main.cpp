#include "framework.h"
#include <stdio.h>

#include <time.h>
#ifdef __MCRTDBG
#include <crtdbg.h>
#endif



//#ifdef WINDOWSEX
//
//typedef int32_t(*PFN_APP_CORE_MAIN)(HINSTANCE hInstance, HINSTANCE hPrevInstance, const char * lpCmdLine, int32_t nCmdShow, app_core & appcore);
//
//CLASS_DECL_AURA int32_t app_common_main(HINSTANCE hinstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int32_t nCmdShow, app_core & appcore);
//CLASS_DECL_AURA int32_t app_common_main(int argc, char *argv[], app_core & appcore);
//
//#else // WINDOWS
//
//typedef int32_t(*PFN_APP_CORE_MAIN)(const char * lpCmdLine, int32_t nCmdShow, app_core & appcore);
//
//#endif
//


//class windows_main_data :
//   public aura_main_data
//{
//public:
//
//
//   HINSTANCE      m_hinstance;
//   HINSTANCE      m_hPrevInstance;
//   LPTSTR         m_lpCmdLine;
//   int32_t        m_nCmdShow;
//
//
//   windows_main_data(HINSTANCE hinstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int32_t nCmdShow)
//   {
//
//      m_bConsole = false;
//
//      m_hinstance = hinstance;
//
//      m_hPrevInstance = hPrevInstance;
//
//      m_lpCmdLine = lpCmdLine;
//
//      m_nCmdShow = nCmdShow;
//
//   }
//
//
//
//};


CLASS_DECL_AURA int32_t ca2_main();


void CLASS_DECL_AURA __cdecl _ca2_purecall()
{

   throw simple_exception(get_thread_app());

}


void __cdecl _null_se_translator(uint32_t uiCode, EXCEPTION_POINTERS * ppointers);





void __cdecl _null_se_translator(uint32_t uiCode, EXCEPTION_POINTERS * ppointers)
{
   UNREFERENCED_PARAMETER(uiCode);
   UNREFERENCED_PARAMETER(ppointers);
}









#undef new


#ifdef _WIN32
extern "C"
{
#undef APPMACROS_ONLY
#include <openssl/ms/applink.c>
}
#endif

BEGIN_EXTERN_C

int32_t WINAPI _tWinMain(HINSTANCE hinstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int32_t nCmdShow)
{

   ap(aura_main_data) pmaindata = new aura_main_data(hinstance, hPrevInstance, lpCmdLine, nCmdShow);

   return aura_aura(pmaindata);

}

END_EXTERN_C

//
//
//
//
//
//#include "aura/node/windows/windows.h"
//
//
//

#define new AURA_NEW








//
//
//CLASS_DECL_AURA int32_t app_common_main(int argc, char *argv[], app_core & appcore)
//{
//
//   int iError = 0;
//
//   ::windows::command * pmaininitdata = NULL;
//
//   ::aura::system * psystem = app_common_prelude(iError, pmaininitdata, appcore);
//
//   if (psystem == NULL)
//   {
//
//      return iError;
//
//   }
//
//   iError = __win_main(psystem, pmaininitdata);
//
//   return app_common_term(iError, psystem, appcore);
//
//}
//
//
//
//
//
//



//
//
//
//
//
//
//
//
//
//
//#include "aura/node/windows/windows.h"













//CLASS_DECL_AURA int32_t app_common_main(int argc, char *argv[], app_core & appcore)
//{
//
//   int iError = 0;
//
//   ::windows::command * pmaininitdata = NULL;
//
//   ::aura::system * psystem = app_common_prelude(iError, pmaininitdata, appcore);
//
//   if (psystem == NULL)
//   {
//
//      return iError;
//
//   }
//
//   iError = __win_main(psystem, pmaininitdata);
//
//   return app_common_term(iError, psystem, appcore);
//
//}




bool node_fill(app_core * pappcore)
{

   string strAppId;

   //if (hinstance == NULL)
   //{

   //   hinstance = ::GetModuleHandle(NULL);

   //}

   //if (::GetProcAddress(hinstance, "get_acid_app") != NULL)
   //{

   //   strAppId = "acid";

   //}

   if (strAppId.is_empty())
   {

      strAppId = read_resource_as_string_dup(pappcore->m_pmaindata->m_hinstance, 1, "APPID");

      if (strAppId.is_empty())
      {

         get_command_line_param(strAppId, string(::GetCommandLineW()), "app");

         if (strAppId.is_empty())
         {

            strAppId = "acid";

         }

      }

   }

   if (strAppId.has_char())
   {

      HMODULE hmodule = NULL;

      bool bInApp = strAppId.compare_ci("acid") == 0;

      if (!bInApp)
      {

         string strLibrary = ::process::app_id_to_app_name(strAppId);

         hmodule = ::LoadLibrary(strLibrary + ".dll");

      }

      if (hmodule != NULL || bInApp)
      {

         PFN_DEFER_INIT defer_init = NULL;

         if ((hmodule = ::GetModuleHandle("core.dll")) != NULL)
         {

            defer_init = (PFN_DEFER_INIT) ::GetProcAddress(hmodule, "defer_core_init");

         }
         else if ((hmodule = ::GetModuleHandle("base.dll")) != NULL)
         {

            defer_init = (PFN_DEFER_INIT) ::GetProcAddress(hmodule, "defer_base_init");

         }
         else if ((hmodule = ::GetModuleHandle("axis.dll")) != NULL)
         {

            defer_init = (PFN_DEFER_INIT) ::GetProcAddress(hmodule, "defer_axis_init");

         }

         if (defer_init != NULL && !defer_init())
         {

            pappcore->on_result(-3);

            return NULL;

         }

      }

   }

   ::windows::command * pmaininitdata = new ::windows::command;

   pmaininitdata->m_hInstance = pappcore->m_pmaindata->m_hinstance;
   pmaininitdata->m_hPrevInstance = pappcore->m_pmaindata->m_hPrevInstance;
   pmaininitdata->m_nCmdShow = pappcore->m_pmaindata->m_nCmdShow;
   pmaininitdata->m_strAppId = strAppId;

   //if (pszCmdLine == NULL)
   //{

   //pmaininitdata->m_strCommandLine = ::path::module() + " : app=" + strAppId;

   //}
   //else
   //{

   //pmaininitdata->m_strCommandLine = pszCmdLine;
   pmaininitdata->m_strCommandLine = ::GetCommandLineW();


   //}

   pappcore->m_pmaindata->m_pmaininitdata = pmaininitdata;

   return true;

}



//int app_common_term(int iError, ::aura::system * psystem, app_core & appcore)
//{
//
//   appcore.m_dwAfterApplicationFirstRequest = psystem->m_dwAfterApplicationFirstRequest;
//
//   try
//   {
//
//      delete psystem;
//
//   }
//   catch (...)
//   {
//
//   }
//
//   psystem = NULL;
//
//
//   return iError;
//
//}
//


