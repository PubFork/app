#include "framework.h"
//#include "metrowin.h"
//#include "sal.h"


CLASS_DECL_AURA int ca2_main();


//CLASS_DECL_BOOT extern fixed_alloc_array * g_pfixedallocaWstring;

//CLASS_DECL_BOOT fixed_alloc_array * new_wstring_manager();

void CLASS_DECL_AURA __cdecl _ca2_purecall()
{
   _throw(simple_exception(get_app()));
}


CLASS_DECL_AURA void __cdecl _null_se_translator(unsigned int uiCode, EXCEPTION_POINTERS * ppointers);


//::aura::application *     win_application_create(::aura::application * pappSystem, const char * pszId);
//::aura::application *     win_instantiate_application(::aura::application * pappSystem, const char * pszId);
//int                     win_application_procedure(::aura::application * pappSystem)
//UINT c_cdecl          win_application_thread_proc(LPVOID);
/////////////////////////////////////////////////////////////////////////////
// Standard WinMain implementation
//  Can be replaced as long as '::ca2::WinInit' is called first


int CLASS_DECL_AURA win_main(::aura::system * psystem, ::Array < ::String ^ > ^ args)
{

   if(!main_initialize())
      return -1;


   _set_purecall_handler(_ca2_purecall);


   int nReturnCode = 0;


   ::metrowin::command * pcommand       = canew(::metrowin::command);

//    pcommand->m_hInstance               = NULL;
//    pcommand->m_hPrevInstance           = NULL;
//    pcommand->m_nCmdShow                = 0;

   //pinitmaindata->m_hInstance             = hInstance;
   //pinitmaindata->m_hPrevInstance         = hPrevInstance;
   //pinitmaindata->m_strCommandLine        = ::str::international::unicode_to_utf8(::GetCommandLineW());
   //pinitmaindata->m_nCmdShow              = nCmdShow;


   psystem->startup_command(pcommand);

   //MessageBox(NULL, "box1", "box1", MB_ICONINFORMATION);

   psystem->main();

   try
   {

      main_finalize();

   }
   catch(...)
   {
   }

   try
   {
      delete psystem;
   }
   catch(...)
   {
   }

   psystem = NULL;


   try
   {
//      delete __get_module_state()->m_pmapHWND;
   }
   catch(...)
   {
   }
   /*   try
      {
         delete __get_module_state()->m_pmapHDC;
      }
      catch(...)
      {
      }*/
   /*   try
      {
         delete __get_module_state()->m_pmapHGDIOBJ;
      }
      catch(...)
      {
      }*/
//      delete __get_module_state()->m_pmapHMENU;

   //try
   //{
   //   __get_module_state()->m_pmapHWND     = NULL;
   //}
   //catch(...)
   //{
   //}
   /*   try
      {
         __get_module_state()->m_pmapHDC      = NULL;
      }
      catch(...)
      {
      }*/
   /*   try
      {
         __get_module_state()->m_pmapHGDIOBJ  = NULL;
      }
      catch(...)
      {
      }*/


//   set_heap_mutex(NULL);

   return nReturnCode;


}


//int CLASS_DECL_AURA ca2_main(HINSTANCE hInstance, HINSTANCE hPrevInstance, const char * lpCmdLine, int nCmdShow)
//{
//   try
//   {
//
//      _set_purecall_handler(_ca2_purecall);
//
//      ::core::system * psystem = new ::core::system();
//
//
//      //Sleep(30 * 1000);
//
//
//      ASSERT(hPrevInstance == NULL);
//
//      int nReturnCode = 0;
//
//      ::metrowin::main_init_data * pinitmaindata  = new ::metrowin::main_init_data;
//
//      pinitmaindata->m_hInstance             = hInstance;
//      pinitmaindata->m_hPrevInstance         = hPrevInstance;
//      pinitmaindata->m_strCommandLine        = lpCmdLine;
//      pinitmaindata->m_nCmdShow              = nCmdShow;
//
//
//      psystem->init_main_data(pinitmaindata);
//
//
//      nReturnCode = psystem->main();
//
//
//      __win_term();
//
//
//      try
//      {
//         delete psystem;
//      }
//      catch(...)
//      {
//      }
//
//      psystem = NULL;
//
//      try
//      {
////         delete __get_module_state()->m_pmapHWND;
//      }
//      catch(...)
//      {
//      }
///*      try
//      {
//         delete __get_module_state()->m_pmapHDC;
//      }
//      catch(...)
//      {
//      }*/
///*      try
//      {
//         delete __get_module_state()->m_pmapHGDIOBJ;
//      }
//      catch(...)
//      {
//      }*/
////      delete __get_module_state()->m_pmapHMENU;
//      try
//      {
//         __get_module_state()->m_pmapHWND     = NULL;
//      }
//      catch(...)
//      {
//      }
///*      try
//      {
//         __get_module_state()->m_pmapHDC      = NULL;
//      }
//      catch(...)
//      {
//      }
//      try
//      {
//         __get_module_state()->m_pmapHGDIOBJ  = NULL;
//      }
//      catch(...)
//      {
//      }*/
//
////      set_heap_mutex(NULL);
//
//
//      return nReturnCode;
//   }
//   catch(...)
//   {
//   }
//   return -1;
//}
//
//

void CLASS_DECL_AURA __cdecl _null_se_translator(unsigned int uiCode, EXCEPTION_POINTERS * ppointers)
{
   UNREFERENCED_PARAMETER(uiCode);
   UNREFERENCED_PARAMETER(ppointers);
}


bool node_fill(app_core * pappcore)
{

   string strAppId;

   set_command_line_dup(string(pappcore->m_pmaindata->m_lpCmdLine));

   strAppId = get_command_line_param(get_command_line_dup(), "app");

   if (strAppId.has_char())
   {

      HMODULE hmodule = NULL;

      bool bInApp = strAppId.compare_ci("acid") == 0;

      if (!bInApp)
      {

         string strLibrary = ::process::app_id_to_app_name(strAppId);

         hmodule = ::LoadPackagedLibrary(wstring(strLibrary + ".dll"), 0);

      }

      if (hmodule != NULL || bInApp)
      {

         PFN_DEFER_INIT defer_init = NULL;

         if ((hmodule = ::LoadPackagedLibrary(L"core.dll",0)) != NULL)
         {

            defer_init = (PFN_DEFER_INIT) ::GetProcAddress(hmodule, "defer_core_init");

         }
         else if ((hmodule = ::LoadPackagedLibrary(L"base.dll",0)) != NULL)
         {

            defer_init = (PFN_DEFER_INIT) ::GetProcAddress(hmodule, "defer_base_init");

         }
         else if ((hmodule = ::LoadPackagedLibrary(L"axis.dll",0)) != NULL)
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


   ::command::command * pcommand = new ::command::command;

   pcommand->m_strCommandLine = get_command_line_dup();

   pcommand->m_strAppId = strAppId;

   pappcore->m_pmaindata->m_pmaininitdata = pcommand;

   return true;

}
