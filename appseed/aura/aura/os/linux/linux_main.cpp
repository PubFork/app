#include "framework.h"
#include <gio/gio.h>
#include "libsn/sn.h"
#include "linux_bloat_pad.h"

void os_post_quit();

CLASS_DECL_AURA int32_t ca2_main();

BEGIN_EXTERN_C

gboolean linux_start_system(gpointer data);

END_EXTERN_C

void CLASS_DECL_AURA __cdecl _ca2_purecall()
{

    _throw(simple_exception(get_app()));

}


void __cdecl _null_se_translator(uint32_t uiCode, EXCEPTION_POINTERS * ppointers)
{

   UNREFERENCED_PARAMETER(uiCode);

   UNREFERENCED_PARAMETER(ppointers);

}


string ca2_command_line()
{

   return "";

}


SnLauncheeContext* g_psncontext = NULL;


void x_display_error_trap_push(SnDisplay * sndisplay, Display * display);

void x_display_error_trap_pop(SnDisplay * sndisplay, Display * display);

BEGIN_EXTERN_C

void sn_start_context()
{


   Display * dpy = x11_get_display();

   xdisplay d(dpy);

   SnDisplay * pd = sn_display_new(dpy, &x_display_error_trap_push, &x_display_error_trap_pop);

   g_psncontext = sn_launchee_context_new(pd, 0, app_core::s_pappcore->m_strProgName);

}

END_EXTERN_C


GMainContext * gtk_main_context;


void app_core::run()
{

   //Sleep(30000);

   {

      string strPrgName = m_strAppId;

      strPrgName.replace("/", ".");

      strPrgName.replace("_", "-");

      m_strProgName = "cc.ca2." + strPrgName;

   }

   if(!m_bGtkApp)
   {

      g_thread_init(NULL);

      gtk_main_context = g_main_context_default();

      g_set_application_name(m_strAppId);

      g_set_prgname(m_strProgName);

      auto idle_source = g_idle_source_new();

      g_source_set_callback(idle_source, &linux_start_system, (::aura::system *) m_psystem, NULL);

      g_source_attach(idle_source, gtk_main_context);

      gtk_init_check(NULL, NULL);

   }


   if(!m_psystem->begin_synch())
   {

      output_debug_string("Failed to begin_synch the system (::aura::system or ::aura::system derived)");

      return;

   }


//   set_main_thread(GetCurrentThread());
//
//   set_main_thread_id(GetCurrentThreadId());
//
//   m_psystem->m_strAppId = m_pmaindata->m_pmaininitdata->m_strAppId;
//
//   m_psystem->startup_command(m_pmaindata->m_pmaininitdata);
//
//   if (!m_psystem->pre_run())
//   {
//
//      return;
//
//   }
//
//
//   if (!m_psystem->process_command(m_psystem->m_pcommand))
//   {
//
//      return;
//
//   }
//
//   try
//   {
//
//      m_psystem->main();
//
//      for(int i = 0; i < m_psystem->m_error.m_iaErrorCode2.get_count(); i++)
//      {
//
//         on_result(m_psystem->m_error.m_iaErrorCode2[i]);
//
//      }
//
//   }
//   catch (...)
//   {
//
//      on_result(-2004);
//
//   }
//
//   try
//   {
//
//      m_psystem->term_thread();
//
//   }
//   catch (...)
//   {
//
//      on_result(-2005);
//
//   }
//
//   try
//   {
//
//      m_dwAfterApplicationFirstRequest = m_psystem->m_dwAfterApplicationFirstRequest;
//
//   }
//   catch (...)
//   {
//
//      on_result(-2006);
//
//   }
//
//   ::aura::del(m_psystem);


   if(m_bGtkApp)
   {

      bloat_pad_run(m_strAppId, m_strProgName);

   }
   else
   {

      gtk_main();

   }

   ::multithreading::post_quit_and_wait(m_psystem, one_minute());

}


bool os_init_application()
{

   return true;

}


void os_term_application()
{

//   if(g_pappBloatPad != NULL)
//   {
//
//      g_application_quit(G_APPLICATION(g_pappBloatPad));
//
//   }

}


gboolean gtk_quit_callback(gpointer data)
{

   gtk_main_quit();

   return FALSE;

}




void os_post_quit()
{

   auto idle_source = g_idle_source_new();

   g_source_set_callback(idle_source, &gtk_quit_callback, NULL, NULL);

   g_source_attach(idle_source, gtk_main_context);

}



gboolean gdk_callback_run_runnable(gpointer pdata)
{

   ::runnable * prunnable = (::runnable * ) pdata;

   prunnable->run();

   return FALSE;

}
