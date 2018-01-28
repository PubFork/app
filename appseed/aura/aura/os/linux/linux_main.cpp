#include "framework.h"
#include <gio/gio.h>
//#include "linux_bloat_pad.h"
#include "libsn/sn.h"

#if 1

#include "linux_bloat_pad.h"

#endif

void os_post_quit();

CLASS_DECL_AURA int32_t ca2_main();

gboolean linux_start_system(gpointer data);

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




GMainContext * gtk_main_context;


void app_core::run()
{

   g_thread_init(NULL);

   gtk_main_context = g_main_context_default();

   //gtk_init_check(0, 0);

   string strPrgName = app_core::s_pappcore->m_strAppId;

   strPrgName.replace("/", ".");

   strPrgName.replace("_", "-");

   strPrgName = "cc.ca2." + strPrgName;

   {

      Display * dpy = x11_get_display();

      xdisplay d(dpy);

      SnDisplay * pd = sn_display_new(dpy, &x_display_error_trap_push, &x_display_error_trap_pop);

      g_psncontext = sn_launchee_context_new(pd, 0, strPrgName);

   }

   g_set_prgname(strPrgName);

   //g_pgtkapp = gtk_application_new (strPrgName, G_APPLICATION_FLAGS_NONE);

   if(m_bGtkApp)
   {

      g_pappBloatPad = bloat_pad_new(strPrgName, strPrgName);

      if(g_pappBloatPad == NULL)
      {

         output_debug_string("Failed to initialize GtkApplication (gtk_application_new return NULL)");

         return;

      }

   }

   //output_debug_string("created GtkApplication");

   if(!m_psystem->begin_synch())
   {

      output_debug_string("Failed to begin_synch the system (::aura::system or ::aura::system derived)");

      return;

   }

   //set_main_thread(m_psystem->m_hthread);

   //set_main_thread_id(m_psystem->m_uiThread);

   auto idle_source = g_idle_source_new();

   g_source_set_callback(idle_source, &linux_start_system, (::aura::system *) m_psystem, NULL);

   g_source_attach(idle_source, gtk_main_context);

   gtk_init_check(0, 0);

   ///GApplication * papp = g_application_get_default ();



   if(m_bGtkApp)
   {

      int status = g_application_run (G_APPLICATION (g_pappBloatPad), 0, NULL);

      g_object_unref(g_pappBloatPad);

      g_pappBloatPad = NULL;

   }
   else
   {

      gtk_main();

   }

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

gboolean linux_start_system(gpointer data)
{

   ::aura::system * psystem = (::aura::system *) data;

   psystem->m_strAppId = psystem->m_pappcore->m_pmaindata->m_pmaininitdata->m_strAppId;

   psystem->startup_command(psystem->m_pappcore->m_pmaindata->m_pmaininitdata);

   psystem->process_command(psystem->m_pcommand);

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
