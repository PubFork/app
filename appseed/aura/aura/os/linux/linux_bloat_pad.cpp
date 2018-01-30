#include "framework.h"
#include "linux_bloat_pad.h"


G_DEFINE_TYPE (BloatPad, bloat_pad, GTK_TYPE_APPLICATION)


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

   ::aura::system * psystem = (::aura::system *) ::aura::system::g_p;

   psystem->m_strAppId = psystem->m_pappcore->m_pmaindata->m_pmaininitdata->m_strAppId;

   psystem->startup_command(psystem->m_pappcore->m_pmaindata->m_pmaininitdata);

   psystem->process_command(psystem->m_pcommand);

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



