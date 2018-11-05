#include "framework.h"



void ns_app_run();

void ns_app_terminate();





CLASS_DECL_AURA bool __node_aura_pre_init()
{

   setlocale(LC_ALL,"");
   
   return true;

}



CLASS_DECL_AURA bool __node_aura_pos_init()
{
   
//   t_posthread = new os_thread(NULL, NULL);
//   
//   t_posthread->m_bRun = true;
   
   return true;
   
}





CLASS_DECL_AURA bool __node_aura_pre_term()
{
  
//   if(t_posthread != NULL)
//   {
//      
//      try
//      {
//         
//         delete t_posthread;
//         
//      }
//      catch(...)
//      {
//         
//      }
//      
//      t_posthread = NULL;
//      
//   }
   
   return true;
   
}



CLASS_DECL_AURA bool __node_aura_pos_term()
{
   
//#ifdef MACOS
//   
   ns_app_terminate();
//
//#elif defined(APPLEIOS)
//
//   ui_app_terminate();
//
//#endif


   return true;
   
}


void macos_desktop_image_changed()
{
   
   ::aura::system::g_p->on_setting_changed(::aura::setting_wallpaper);
   
}



//char * mm_ca2_command_line();
//
//string ca2_command_line()
//{
//   
//   char * psz = mm_ca2_command_line();
//   
//   string str(psz);
//   
//   free(psz);
//   
//   return str;
//   
//}






void macos_on_app_activate()
{
 
   ::aura::system::g_p->on_setting_changed(::aura::setting_app_activation);
      
}
