#include "framework.h"



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
   
   string str(psz);
   
   free(psz);
   
   return str;
   
}

///const char * g_pszCommandLine = NULL;



int32_t aura_main_command_line(const char * pszParams, int argc, char *argv[])
{
   
   
   pid_t processid;
   
   string strCommandLine;
   
   strCommandLine = argv[0];
   
   if(strCommandLine.find(' ') >= 0)
   {
      
      strCommandLine = "\"" + strCommandLine + "\"";
      
   }
   
   string strP = pszParams;
   
   strsize iFind = strP.find(':');
   
   if(iFind == 0)
   {
   }
   else
   {
      int iQuote;
      while(iFind > 0)
      {
         
         iQuote = 0;
         const char * psz = &strP[iFind];
         for(; psz >= strP.c_str(); psz = ::str::utf8_dec(strP, psz))
         {
            if(*psz == '\"')
            {
               iQuote++;
            }
         }
         
         if(iQuote % 2 == 0)
         {
            break;
            
         }
         iFind = strP.find(':', iFind + 1);
         
      }
      
      
      
   }
   
   
   string str1;
   
   string str2;
   
   if(iFind >= 0)
   {
      
      str1 = strP.Left(iFind);
      
      if(str1.has_char())
      {
         
         str1 = " " + str1 + " ";
         
      }
      
      str2 = strP.Mid(iFind + 1);
      
      if(str2.has_char())
      {
         
         str2 = " " + str2 + " ";
         
      }
      
   }
   
   string strA;
   
   string strB;
   
   processid = getpid();
   
   printf("%d\n", processid);
   
   string strAddUp;
   
   bool bColon = false;
   
   bool bOverride = false;
   
   for(index i = 1; i < argc; i++)
   {
      
      if(strcmp(argv[i], ":") == 0)
      {
         
         bColon = true;
         
      }
      else
      {
         if(!bColon)
         {
            
            if(argv[i][0] == '-')
            {
               
               bColon = true;
               
            }
            
         }
         
         if(!bColon)
         {
            
            //if(strstr(argv[i], " ") != 0)
            {
               
               strA += " \"" + string(argv[i]) + "\"";
               
            }
            //            else
            //            {
            //
            //               strA += string(" ") + argv[i];
            //
            //            }
            
         }
         else
         {
            
            if(::str::begins_ci(argv[i], "app="))
            {
               
               bOverride = true;
               
            }
            
            strB += string(" ") + argv[i];
            
         }
         
      }
      
   }
   
   if(bOverride)
   {
      
      str2.replace_ci("app=", "fallback_app=");
      
   }
   
   strCommandLine += str1 + strA + " : " + str2 + strB;
   
   return raw_main_command_line(strCommandLine, argc, argv);
   
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









int32_t defer_run_system()
{
   
   return __start_system_with_file(NULL);
   
}


int32_t defer_run_system(const char * pszFileName)
{
   
   return __start_system_with_file(pszFileName);
   
}


int32_t defer_run_system(char ** pszaFileName, int iFileCount)
{
   
   return __start_system_with_file((const char **) pszaFileName, iFileCount);
   
}


void macos_on_app_activate()
{
   
   ::aura::system::g_p->on_setting_changed(::aura::setting_app_activation);
   
}


void macos_on_new_file()
{
   
   ::aura::system::g_p->on_open_file(var::type_empty, "");
   
}

// iMillisDelay default 500ms good
void macos_accumulate_on_open_file(const char ** psza, int iCount, const char * pszExtra, int iMillisDelay)
{
   
   stringa stra;
   
   stra.c_add((char **) psza, iCount);
   
   ::aura::system::g_p->accumulate_on_open_file(stra, pszExtra, iMillisDelay);
   
}



void macos_on_open_file(const char ** psza, int iCount, const char * pszExtra)
{
   
   if(iCount <= 0)
   {
    
      macos_on_new_file();
      
   }
   else if(iCount == 1)
   {
   
      ::aura::system::g_p->on_open_file(psza[0], pszExtra);
      
      ::free((void *) psza[0]);
      
      ::free(psza);
      
   }
   else
   {
      
      stringa stra;
      
      stra.c_add((char **) psza, iCount);
      
      ::aura::system::g_p->on_open_file(stra, pszExtra);
      
   }
   
}


