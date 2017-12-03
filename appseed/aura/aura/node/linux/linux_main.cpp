#include "framework.h"
#include "aura/node/ansios/ansios.h"
#include "linux.h"



CLASS_DECL_AURA int32_t ca2_main();


//CLASS_DECL_AURA extern fixed_alloc_array * g_pfixedallocaWstring;


//CLASS_DECL_AURA fixed_alloc_array * new_wstring_manager();


void CLASS_DECL_AURA __cdecl _ca2_purecall()
{

    _throw(simple_exception(get_app()));

}


void __cdecl _null_se_translator(uint32_t uiCode, EXCEPTION_POINTERS * ppointers)
{

   UNREFERENCED_PARAMETER(uiCode);

   UNREFERENCED_PARAMETER(ppointers);

}




bool node_fill(app_core * pappcore)
{

      //setlocale(LC_ALL,"");

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
  ::command::command * pmaininitdata = new ::command::command;

  //pmaininitdata->m_hInstance = pappcore->m_pmaindata->m_hinstance;
  //pmaininitdata->m_hPrevInstance = pappcore->m_pmaindata->m_hPrevInstance;
  //pmaininitdata->m_nCmdShow = pappcore->m_pmaindata->m_nCmdShow;
  pmaininitdata->m_strAppId = strAppId;

  //if (pszCmdLine == NULL)
  //{

  //pmaininitdata->m_strCommandLine = ::path::module() + " : app=" + strAppId;

  //}
  //else
  //{

  //pmaininitdata->m_strCommandLine = pszCmdLine;
  pmaininitdata->m_strCommandLine = get_command_line_dup();


  //}

  pappcore->m_pmaindata->m_pmaininitdata = pmaininitdata;

   return true;

}




