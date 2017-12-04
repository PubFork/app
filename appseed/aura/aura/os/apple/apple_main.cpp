//
//  apple_main.cpp
//  aura
//
//  Created by Camilo Sasuke Tsumanuma on 02/10/17.
//

#include "framework.h"
#include "apple.h"




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






bool node_fill(app_core * pappcore)
{
   
      setlocale(LC_ALL,"");
      
   int argc = pappcore->m_pmaindata->m_argc;
   
   char * * argv = pappcore->m_pmaindata->m_argv;
      //pid_t processid;
   
   string strCommandLine;
   
   strCommandLine = argv[0];
   
   if(strCommandLine.find(' ') >= 0)
   {
      
      strCommandLine = "\"" + strCommandLine + "\"";
      
   }
   
   //string strP = pszParams;
   
   //strsize iFind = strP.find(':');
   
//   if(iFind == 0)
//   {
//   }
//   else
//   {
//      int iQuote;
//      while(iFind > 0)
//      {
//         
//         iQuote = 0;
//         const char * psz = &strP[iFind];
//         for(; psz >= strP.c_str(); psz = ::str::utf8_dec(strP, psz))
//         {
//            if(*psz == '\"')
//            {
//               iQuote++;
//            }
//         }
//         
//         if(iQuote % 2 == 0)
//         {
//            break;
//            
//         }
//         iFind = strP.find(':', iFind + 1);
//         
//      }
//      
//      
//      
//   }
   
   
   string str1;
   
   string str2;
   
//   if(iFind >= 0)
//   {
//      
//      str1 = strP.Left(iFind);
//      
//      if(str1.has_char())
//      {
//         
//         str1 = " " + str1 + " ";
//         
//      }
//      
//      str2 = strP.Mid(iFind + 1);
//      
//      if(str2.has_char())
//      {
//         
//         str2 = " " + str2 + " ";
//         
//      }
//      
//   }
   
   string strA;
   
   string strB;
   
   //processid = getpid();
   
   //printf("%d\n", processid);
   
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
   
   string strAppId;
   
   get_command_line_param(strAppId, strCommandLine, "app");
   
   if(strAppId.is_empty() && pappcore->m_bAcidApp)
   {
    
      strCommandLine += " app=acid";
      
   }

set_command_line_dup(strCommandLine);

//   string strAppId;
//   
//   //if (hinstance == NULL)
//   //{
//   
//   //   hinstance = ::GetModuleHandle(NULL);
//   
//   //}
//   
//   //if (::GetProcAddress(hinstance, "get_acid_app") != NULL)
//   //{
//   
//   //   strAppId = "acid";
//   
//   //}
//   
//   if (strAppId.is_empty())
//   {
//      
//      strAppId = read_resource_as_string_dup(pappcore->m_pmaindata->m_hinstance, 1, "APPID");
//      
//      if (strAppId.is_empty())
//      {
//         
//         get_command_line_param(strAppId, string(::GetCommandLineW()), "app");
//         
//         if (strAppId.is_empty())
//         {
//            
//            strAppId = "acid";
//            
//         }
//         
//      }
//      
//   }
//   
//   if (strAppId.has_char())
//   {
//      
//      HMODULE hmodule = NULL;
//      
//      bool bInApp = strAppId.compare_ci("acid") == 0;
//      
//      if (!bInApp)
//      {
//         
//         string strLibrary = ::process::app_id_to_app_name(strAppId);
//         
//         hmodule = ::LoadLibrary(strLibrary + ".dll");
//         
//      }
//      
//      if (hmodule != NULL || bInApp)
//      {
//         
//         PFN_DEFER_INIT defer_init = NULL;
//         
//         if ((hmodule = ::GetModuleHandle("core.dll")) != NULL)
//         {
//            
//            defer_init = (PFN_DEFER_INIT) ::GetProcAddress(hmodule, "defer_core_init");
//            
//         }
//         else if ((hmodule = ::GetModuleHandle("base.dll")) != NULL)
//         {
//            
//            defer_init = (PFN_DEFER_INIT) ::GetProcAddress(hmodule, "defer_base_init");
//            
//         }
//         else if ((hmodule = ::GetModuleHandle("axis.dll")) != NULL)
//         {
//            
//            defer_init = (PFN_DEFER_INIT) ::GetProcAddress(hmodule, "defer_axis_init");
//            
//         }
//         
//         if (defer_init != NULL && !defer_init())
//         {
//            
//            pappcore->on_result(-3);
//            
//            return NULL;
//            
//         }
//         
//      }
//      
//   }
//   
//   ::windows::command * pmaininitdata = new ::windows::command;
//   
//   pmaininitdata->m_hInstance = pappcore->m_pmaindata->m_hinstance;
//   pmaininitdata->m_hPrevInstance = pappcore->m_pmaindata->m_hPrevInstance;
//   pmaininitdata->m_nCmdShow = pappcore->m_pmaindata->m_nCmdShow;
//   pmaininitdata->m_strAppId = strAppId;
//   
//   //if (pszCmdLine == NULL)
//   //{
//   
//   //pmaininitdata->m_strCommandLine = ::path::module() + " : app=" + strAppId;
//   
//   //}
//   //else
//   //{
//   
//   //pmaininitdata->m_strCommandLine = pszCmdLine;
//   pmaininitdata->m_strCommandLine = ::GetCommandLineW();
//   
//   
//   //}
//   
//   pappcore->m_pmaindata->m_pmaininitdata = pmaininitdata;
   
   return true;
   
}




