#include "framework.h"


string ca2_command_line()
{

   return "";

}

void app_core::main()
{

   if (!ini())
   {

      end();

      return;

   }

   run();

}


void app_core::run()
{

   {

      string strPrgName = m_strAppId;

      strPrgName.replace("/", ".");

      strPrgName.replace("_", "-");

      m_strProgName = "cc.ca2." + strPrgName;

   }

   set_main_thread(m_psystem->m_hthread);

   set_main_thread_id(m_psystem->m_uiThread);

   m_psystem->m_strAppId = m_pmaindata->m_pmaininitdata->m_strAppId;

   if (!m_psystem->begin_synch())
   {

      output_debug_string("Failed to begin_synch the system (::aura::system or ::aura::system derived)");

      return;

   }

   ::aura::system * psystem = ::aura::system::g_p;

   try
   {

      psystem->m_possystemwindow->m_pui = new ::user::interaction(psystem);

      ::user::native_window_initialize initialize;

      initialize.m_rect.left = 0;

      initialize.m_rect.top = 0;

      node_data_exchange * pdataexchange = psystem->node_ddx();

      initialize.m_rect.right = pdataexchange->m_iScreenWidth;

      initialize.m_rect.bottom = pdataexchange->m_iScreenHeight;

      psystem->m_possystemwindow->m_pui->initialize_native_window(&initialize);

      ::oswindow_data * pwindow = new oswindow_data;

      oswindow window = pwindow;

      psystem->m_possystemwindow->m_oswindow = pwindow;

   }
   catch (...)
   {

      psystem->m_error.set(-1);

      return;

   }

   m_psystem->startup_command(m_pmaindata->m_pmaininitdata);

   m_psystem->process_command(m_pmaindata->m_pmaininitdata);

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



void os_post_quit()
{



}

