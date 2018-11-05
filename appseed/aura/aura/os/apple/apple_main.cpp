//
//  apple_main.cpp
//  aura
//
//  Created by Camilo Sasuke Tsumanuma on 02/10/17.
//

#include "framework.h"
#include "aura/aura/os/os.h"
#include "aura/aura/os/os_os.h"
#include "apple.h"


uint32_t __start_system_with_file(const char ** pszaFile, int iCount);


uint32_t __start_system_with_file(const char * pszFileName)
{

   if(pszFileName == NULL)
   {

      return __start_system_with_file(NULL, 0);

   }

   const char ** psza = (const char **) malloc(sizeof(const char *) * 1);

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

         apple_accumulate_on_open_file(pszaFile, iCount, strExtra);

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



}



string ca2_command_line();



string apple_get_bundle_identifier();



string ca2_command_line2()
{

   string str = apple_get_bundle_identifier();

   if(!::str::begins_eat_ci(str, "cc.ca2."))
   {
    
      ::str::begins_eat_ci(str, "com.ca2.");
      
   }
   
   stringa stra;
   
   stra.explode(".", str);

   if(stra.get_size() >= 2)
   {
      
      stra[1].replace('-', '_');
      
   }
   
   str = stra.implode("/");
   
#ifdef APPLE_IOS

   return "app : app=" + str + " client_only";
   
#else
   
   return "app : app=" + str;
   
#endif

}

