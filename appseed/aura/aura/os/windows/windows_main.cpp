#include "framework.h"
#include <stdio.h>

#include <time.h>
#ifdef __MCRTDBG
#include <crtdbg.h>
#endif

CLASS_DECL_AURA string ca2_command_line();

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

   _throw(simple_exception(get_app()));

}


void __cdecl _null_se_translator(uint32_t uiCode, EXCEPTION_POINTERS * ppointers);





void __cdecl _null_se_translator(uint32_t uiCode, EXCEPTION_POINTERS * ppointers)
{
   UNREFERENCED_PARAMETER(uiCode);
   UNREFERENCED_PARAMETER(ppointers);
}









#undef new


//#ifdef _WIN32
//extern "C"
//{
//#undef APPMACROS_ONLY
//#include <openssl/ms/applink.c>
//}
//#endif


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



CLASS_DECL_AURA bool os_init_application()
{

   return true;

}


CLASS_DECL_AURA void os_term_application()
{



}






string ca2_command_line()
{

   string strAppId = read_resource_as_string_dup(::app_core::s_pappcore->m_pmaindata->m_hinstance, 1, "APPID");

   if (strAppId.is_empty())
   {

      return "";

   }

   return "app.exe : app=" + strAppId;

}




namespace aura
{


   bool application::os_on_start_application()
   {

      return true;

   }


} // namespace aura




void os_post_quit()
{



}


CLASS_DECL_AURA void main_async_runnable(runnable * prunnable)
{

   ::aura::system::g_p->post_pred([prunnable]()
   {

      prunnable->run();

   });

}

CLASS_DECL_AURA void main_synch_runnable(runnable * prunnable)
{

   ::aura::system::g_p->send_pred([prunnable]()
   {

      prunnable->run();

   });

}
