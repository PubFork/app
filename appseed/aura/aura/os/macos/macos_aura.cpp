#include "framework.h"
#include "aura/aura/os/apple/apple.h"


void ns_app_run();

void ns_shared_application(int argc, char *argv[]);

void ns_app_terminate();
//extern thread_pointer < os_thread > t_posthread;







CLASS_DECL_AURA bool __node_aura_pre_init()
{

   
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



char * mm_ca2_command_line();

string ca2_command_line()
{
   
   char * psz = mm_ca2_command_line();
   
   string str1(psz);
   
   string str2 = apple_bundle_identifier();
   
   if(!::str::begins_eat_ci(str2, "com.ca2."))
   {
      
      ::str::begins_eat_ci(str2, "cc.ca2.");
      
   }

   str2.replace(".", "/");
   
   if(str2.has_char())
   {
   
      str2 = "app : app=" + str2;
      
   }
   
   string strCommandLine = merge_colon_args(
                                            {
                                               get_c_args(str1),
                                               get_c_args(str2)
                                            });

   
   free(psz);
   
   return strCommandLine;
   
}

///const char * g_pszCommandLine = NULL;

int32_t aura_main_command_line(const char * pszParams, int argc, char *argv[])
{
   
   return raw_main_command_line(pszParams, argc, argv);
   
}


int32_t raw_main_command_line(const char * pszCommandLine, int argc, char *argv[])
{
   
   setlocale(LC_ALL,"");
   
   set_command_line_dup(pszCommandLine);
   
   ns_shared_application(argc, argv);
   
   ns_app_run();
   
   delete ::aura::system::g_p;
   
   return 0;
   
}






void macos_on_app_activate()
{
 
   ::aura::system::g_p->on_setting_changed(::aura::setting_app_activation);
      
}
