#include "framework.h"
#include <gio/gio.h>
#include "linux_bloat_pad.h"
#include "libsn/sn.h"



CLASS_DECL_AURA int32_t ca2_main();


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


void x_display_error_trap_push(SnDisplay * display, Display * xdisplay);

void x_display_error_trap_pop(SnDisplay * display, Display * xdisplay);


BloatPad * g_pappBloatPad = NULL;


BloatPad * bloat_pad_new (string strAppName, string strAppId)
{

  BloatPad *bloat_pad;

  g_set_application_name (strAppName);

  bloat_pad = (BloatPad *) g_object_new (bloat_pad_get_type (),
                            "application-id", strAppId,
                            "flags", G_APPLICATION_HANDLES_OPEN,
                            //"flags", G_APPLICATION_HANDLES_OPEN | G_APPLICATION_IS_SERVICE,
                            //"inactivity-timeout", 30000,
                            "register-session", TRUE,
                            NULL);

  return bloat_pad;

}


void bloat_pad_activate(GApplication * application)
{

   //GCancellable * pc = g_cancellable_new();

   //GError * perror = NULL;

   //g_application_register(application, pc, &perror);
   //new_window(application, NULL);

}

void bloat_pad_run_mainloop(GApplication * application)
{

   BloatPad * bloatpad = (BloatPad *) application;

   GtkApplication * app = GTK_APPLICATION (application);

   G_APPLICATION_CLASS (bloat_pad_parent_class)->run_mainloop(application);

}

void bloat_pad_init (BloatPad *app)
{

}


void bloat_pad_startup (GApplication *application)
{

   BloatPad * bloatpad = (BloatPad *) application;

   GtkApplication * app = GTK_APPLICATION (application);

   G_APPLICATION_CLASS (bloat_pad_parent_class)->startup (application);

   ::aura::system::g_p->process_command(::aura::system::g_p->m_pcommand);

   g_application_hold(application);

}


void bloat_pad_open(GApplication * application, GFile ** files, gint n_files, const gchar * hint)
{

//   gint i;
//
//   for (i = 0; i < n_files; i++)
//   {
//
//      new_window (application, files[i]);
//
//   }

}


void bloat_pad_finalize (GObject *object)
{

   G_OBJECT_CLASS (bloat_pad_parent_class)->finalize (object);

}


void bloat_pad_shutdown(GApplication *application)
{

   BloatPad * bloatpad = (BloatPad *) application;

   /*

   if (bloatpad->timeout)
   {

      g_source_remove (bloatpad->timeout);

      bloatpad->timeout = 0;

   }

   */

   G_APPLICATION_CLASS (bloat_pad_parent_class)->shutdown (application);

}


void bloat_pad_class_init (BloatPadClass * pclass)
{

  GApplicationClass *application_class    = G_APPLICATION_CLASS (pclass);

  GObjectClass *object_class              = G_OBJECT_CLASS (pclass);

  application_class->startup              = &bloat_pad_startup;
  application_class->shutdown             = &bloat_pad_shutdown;
  application_class->activate             = &bloat_pad_activate;
  application_class->open                 = &bloat_pad_open;

  application_class->run_mainloop         = &bloat_pad_run_mainloop;

  object_class->finalize                  = &bloat_pad_finalize;

}


void app_core::run()
{

   //gtk_init_check(0, 0);

   string strPrgName = app_core::s_pappcore->m_strAppId;

   strPrgName.replace("/", ".");

   strPrgName.replace("_", "-");

   strPrgName = "cc.ca2." + strPrgName;

//   {
//
//      Display * dpy = x11_get_display();
//
//      xdisplay d(dpy);
//
//      SnDisplay * pd = sn_display_new(dpy, &x_display_error_trap_push, &x_display_error_trap_pop);
//
//      g_psncontext = sn_launchee_context_new(pd, 0, strPrgName);
//
//   }
//
   //g_set_prgname(strPrgName);

   //g_pgtkapp = gtk_application_new (strPrgName, G_APPLICATION_FLAGS_NONE);

   //g_pappBloatPad = bloat_pad_new(strPrgName, strPrgName);

   //if(g_pappBloatPad == NULL)
   //{

     // output_debug_string("Failed to initialize GtkApplication (gtk_application_new return NULL)");

      //return;

   //}

   //output_debug_string("created GtkApplication");

   if(!m_psystem->pre_run())
   {

      output_debug_string("Failed to begin_synch the system (::aura::system or ::aura::system derived)");

      return;

   }

   //set_main_thread(m_psystem->m_hthread);

   //set_main_thread_id(m_psystem->m_uiThread);

   m_psystem->m_strAppId = m_pmaindata->m_pmaininitdata->m_strAppId;

   m_psystem->startup_command(m_pmaindata->m_pmaininitdata);

   m_psystem->process_command(m_psystem->m_pcommand);

   m_psystem->main();

   //int status = g_application_run (G_APPLICATION (g_pappBloatPad), 0, NULL);

   //g_object_unref(g_pappBloatPad);

   //g_pappBloatPad = NULL;

}


bool os_init_application()
{

   return true;

}


void os_term_application()
{

   if(g_pappBloatPad != NULL)
   {

      g_application_quit(G_APPLICATION(g_pappBloatPad));

   }

   gtk_main_quit();

}

