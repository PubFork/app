//
//  apple_main.cpp
//  aura
//
//  Created by Camilo Sasuke Tsumanuma on 02/10/17.
//

#include "framework.h"
#include "apple.h"

//m_plibrary = __node_library_open_ca2(pszPath, m_strMessage);

string transform_to_c_arg(const char * psz)
{

   if(strstr(psz, " ") != NULL)
   {
    
      return string("\"") + ::str::replace(psz, "\"", "\\\"") + "\"";
      
   }
   else
   {
      
      return psz;
      
   }

}


string merge_colon_args(const array < stringa > str2a)
{

   stringa straBeforeColon;
   
   stringa straAfterColon;
   
   string strCommandLine;

   for(auto & stra : str2a)
   {
      
      index iFindColon = stra.find_first(":");
      
      if(stra.get_size() > 0 && iFindColon != 0)
      {
         
         if(strCommandLine.is_empty())
         {
            
            strCommandLine = transform_to_c_arg(stra[0]);
            
         }
         
      }
      
      iFindColon = iFindColon < 0 ? stra.get_size() : 1;
      
      for(index i = 1; i < stra.get_count(); i++)
      {
         
         if(i < iFindColon)
         {
            
            straBeforeColon.add(stra[i]);
            
         }
         else if(i > iFindColon)
         {
            
            string str = stra[i];
            
            if(::str::begins_eat_ci(str, "app="))
            {
               
               if(straAfterColon.find_first_begins("app=") >= 0) // fixed case when added below :D..O
               {
                  
                  straAfterColon.add("fallback_app=" + str);
                  
               }
               else
               {
                  
                  straAfterColon.add("app=" + str); // fixed case :) (excuses, excuses...)
                  
               }
               
            }
            else
            {
            
               straAfterColon.add(str);
               
            }
            
         }
         
      }
      
   }

   strCommandLine += straBeforeColon.pred_implode(&transform_to_c_arg, " ");
   
   strCommandLine += " : ";

   strCommandLine += straAfterColon.pred_implode(&transform_to_c_arg, " ");

   return strCommandLine;

}


uint32_t __start_system_with_file(const char ** pszaFile, int iCount);


uint32_t __start_system_with_file(const char * pszFileName)
{
   
   if(pszFileName == NULL)
   {
      
      return __start_system_with_file(NULL, 0);
      
   }
   
   const char ** psza = (const char **) malloc(sizeof(const char **) * 1);
   
   psza[0] = strdup(pszFileName);
   
   return __start_system_with_file(psza, 1);
   
}

uint32_t __start_system_with_file(const char ** pszaFile, int iCount)
{
   
   string strExtra;
   
   //if(::aura::system::g_p != NULL)
   {
      
      if(pszaFile != NULL)
      {
         
         apple_accumulate_on_open_file(pszaFile, iCount, strExtra, 500);
         //         macos_on_open_file(pszaFile, iCount, strExtra);
         
      }
      else
      {
         
         ::command::command * pcommand = new ::command::command;
         
         pcommand->m_strCommandLine = get_command_line_dup();

         ::aura::system::g_p->startup_command(pcommand);
         
         ::aura::system::g_p->process_command(pcommand);
         
      }
      
      return 0;
      
   }
   
   
//   var varFile;
//
//   {
//
//      stringa stra;
//
//      stra.c_add((char **) pszaFile, iCount);
//
//      ::count c= stra.get_count();
//
//      for(index i = 0; i < c; i++)
//      {
//
//         string str = stra[i];
//
//         strsize iFindColon = str.find(':');
//
//         if(iFindColon == 0)
//         {
//
//            stra.remove_at(i, stra.get_count() - i);
//
//            break;
//
//         }
//
//      }
//
//      varFile = stra;
//
//   }
//
//   int32_t nReturnCode = 0;
//
//   ::aura::system * psystem;
//
//   psystem = create_aura_system();
//
//   ::set_thread(psystem);
//
//   ::command::command * pcommand = new ::command::command;
//
//   pcommand->m_strCommandLine = get_command_line_dup();
//
//   pcommand->m_varFile = varFile;
//
//   psystem->startup_command(pcommand);
//
//   bool bOk = true;
//
//   try
//   {
//
//      if(psystem->begin_synch())
//      {
//
//         bOk = true;
//
//      }
//
//   }
//   catch(...)
//   {
//
//   }
//
//   try
//   {
//
//      if(!bOk)
//      {
//
//         //if(psystem->m_iaErrorCode == 0)
//         //{
//
//           // return -1;
//
//         //}
//
//         //return psystem->m_iErrorCode;
//
//         return -1;
//
//      }
//
//   }
//   catch(...)
//   {
//
//      return -1;
//
//   }
//
//   return nReturnCode;
   
}



string ca2_command_line();


bool node_fill(app_core * pappcore)
{
   
   setlocale(LC_ALL,"");
      
   string strCommandLine = merge_colon_args({
      get_c_args(pappcore->m_pmaindata->m_argc, pappcore->m_pmaindata->m_argv),
      get_c_args(ca2_command_line()),
      get_c_args(pappcore->m_pmaindata->m_lpCmdLine)
   });
   
   set_command_line_dup(strCommandLine);
   
   return true;
   
}




