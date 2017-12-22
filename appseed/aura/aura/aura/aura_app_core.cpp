#include "framework.h"
#include <time.h>


typedef bool DEFER_INIT();
typedef DEFER_INIT * PFN_DEFER_INIT;




//string merge_colon_args(const array < stringa > & str2a);
//string transform_to_c_arg(const char * psz);
//stringa get_c_args(const char * psz);
//stringa get_c_args(int argc, char ** argv);

::aura_prelude * aura_prelude::s_pprelude = NULL;

//::aura::PFN_GET_NEW_APP aura_prelude::s_pfnNewApp = NULL;


#ifdef APPLEOS

size_t ns_get_bundle_identifier(char * psz, size_t iSize);

string apple_get_bundle_identifier();

string ca2_command_line2();

#endif


#ifdef WINDOWS

#define APP_CORE_BASE_DIR "C:\\ca2\\config\\system"

#else

#define APP_CORE_BASE_DIR "/var/tmp/ca2/config/system"

#endif

aura_main_data::aura_main_data(int argc, char ** argv)
{

   m_bConsole = true;

   m_argc = argc;

   m_argv = argv;

#ifdef WINDOWSEX

   m_hinstance = ::GetModuleHandle(NULL);

   m_hPrevInstance = NULL;

   m_nCmdShow = SW_SHOWDEFAULT;

#endif

}

#ifdef WINDOWSEX

aura_main_data::aura_main_data(HINSTANCE hinstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int32_t nCmdShow)
{

   m_bConsole = false;

   m_hinstance = hinstance;

   m_hPrevInstance = hPrevInstance;

   m_strCommandLine = lpCmdLine;

   m_nCmdShow = nCmdShow;

}


#elif defined(METROWIN)

aura_main_data::aura_main_data(Array < String ^ > ^ refstra)
{

   m_bConsole = false;

   stringa stra(refstra);

}

#endif

aura_main_data::aura_main_data(LPTSTR lpCmdLine)
{

   m_bConsole = false;

   m_strCommandLine = lpCmdLine;

}


aura_main_data::~aura_main_data()
{

}


app_core * app_core::s_pappcore = NULL;


// ATTENTION
// This class should (if it uses) member functions with care:
// It is used after all application app_core (library) finalization,
// when even new/delete/strings/ids can be used anymore for example.

app_core::app_core(aura_main_data * pdata)
{

   s_pappcore = this;

   m_pmaindata = pdata;

}

app_core::~app_core()
{

}


bool app_core::on_result(int iResultCode)
{

   if (iResultCode == 0)
   {

      return true;

   }

   if (m_iErrorCount >= APP_CORE_MAXIMUM_ERROR_COUNT)
   {

      m_iTotalErrorCount++;

      return false;

   }

   m_iaError[m_iErrorCount] = iResultCode;

   m_iErrorCount++;

   m_iTotalErrorCount = m_iErrorCount;

   return false;

}


bool app_core::beg()
{

   aura_prelude::defer_call_construct(this);

//#ifdef APPLEOS
//
//   if(m_pmaindata->m_lpCmdLine == NULL)
//   {
//
//      string str = apple_get_bundle_identifier();
//
//      ::str::begins_eat_ci(str, "com.ca2.");
//
//      str.replace(".", "/");
//
//      m_pmaindata->m_lpCmdLine = ::str::dup("app : app=" + str);
//
//   }
//
//#endif

   m_dwStartTime = ::get_first_tick();

   m_dwAfterApplicationFirstRequest = m_dwStartTime;

   if (file_exists_dup(::file::path(APP_CORE_BASE_DIR) / "wait_on_beg.txt"))
   {

      Sleep(10000);

   }

   if (file_exists_dup(::file::path(APP_CORE_BASE_DIR) / "beg_debug_box.txt"))
   {

      debug_box("zzzAPPzzz app", "zzzAPPzzz app", MB_ICONINFORMATION);

   }

   return true;

}

bool app_core::ini()
{

   m_bAcidApp = m_pfnNewApp != NULL;

   string strAppId;

   string strCommandLine = merge_colon_args(
   {
#ifdef WINDOWS
      get_c_args(string(::GetCommandLineW())),
#else
      get_c_args(m_pmaindata->m_argc, m_pmaindata->m_argv),
      get_c_args(m_pmaindata->m_strCommandLine)
#endif
      ,get_c_args(ca2_command_line())
#ifdef APPLEOS
      ,get_c_args(ca2_command_line2())
#endif
   });

   set_command_line_dup(strCommandLine);

   get_command_line_param(strAppId, strCommandLine, "app");

   if (strAppId.is_empty())
   {

      if (m_bAcidApp)
      {

         strAppId = "acid";

         strCommandLine += " app=acid";

      }

   }

   if (strAppId.has_char())
   {

      m_strAppId = strAppId;

   }

   ::command::command * pmaininitdata = new ::command::command;

   pmaininitdata->m_strAppId = strAppId;

   pmaininitdata->m_strCommandLine = strCommandLine;

   m_pmaindata->m_pmaininitdata = pmaininitdata;

   string strDerivedApplication;

   get_command_line_param(strDerivedApplication, strCommandLine, "derived_application");

   g_iDerivedApplication = atoi(strDerivedApplication);

   defer_load_backbone_libraries(strAppId);

   m_psystem = g_pfn_create_system(this);

   if (m_psystem == NULL)
   {

      on_result(-1);

      return false;

   }

   // what could influence time before main?
   // cold start (never previously called program and its Dlls...)?
   m_psystem->m_dwMainStartTime = m_dwStartTime;

   xxdebug_box("box1", "box1", MB_ICONINFORMATION);

   return true;

}


void app_core::defer_load_backbone_libraries(string strAppId)
{

   if (strAppId.has_char())
   {

      void * hmodule = NULL;

      bool bInApp = strAppId.compare_ci("acid") == 0;

      string strMessage;

      if (!bInApp)
      {

         string strLibrary = ::process::app_id_to_app_name(strAppId);

         hmodule = __node_library_open(strLibrary, strMessage);

      }

      if (hmodule != NULL || bInApp)
      {

         PFN_DEFER_INIT defer_init = NULL;

         if ((hmodule = __node_library_touch("core", strMessage)) != NULL)
         {

            defer_init = (PFN_DEFER_INIT) __node_library_raw_get(hmodule, "defer_core_init");

         }
         else if ((hmodule = __node_library_touch("base", strMessage)) != NULL)
         {

            defer_init = (PFN_DEFER_INIT) __node_library_raw_get(hmodule, "defer_base_init");

         }
         else if ((hmodule = __node_library_touch("axis", strMessage)) != NULL)
         {

            defer_init = (PFN_DEFER_INIT) __node_library_raw_get(hmodule, "defer_axis_init");

         }

         if (defer_init != NULL && !defer_init())
         {

            on_result(-3);

         }

      }

   }

}


void app_core::run()
{

   set_main_thread(GetCurrentThread());

   set_main_thread_id(GetCurrentThreadId());

   m_psystem->m_strAppId = m_pmaindata->m_pmaininitdata->m_strAppId;

   m_psystem->startup_command(m_pmaindata->m_pmaininitdata);

   if (!m_psystem->pre_run())
   {

      return;

   }


   if (!m_psystem->process_command(m_psystem->m_pcommand))
   {

      return;

   }

   try
   {

      m_psystem->main();

      for(int i = 0; i < m_psystem->m_error.m_iaErrorCode2.get_count(); i++)
      {

         on_result(m_psystem->m_error.m_iaErrorCode2[i]);

      }

   }
   catch (...)
   {

      on_result(-2004);

   }

   try
   {

      m_psystem->term_thread();

   }
   catch (...)
   {

      on_result(-2005);

   }

   try
   {

      m_dwAfterApplicationFirstRequest = m_psystem->m_dwAfterApplicationFirstRequest;

   }
   catch (...)
   {

      on_result(-2006);

   }

   ::aura::del(m_psystem);

}


void app_core::end()
{

   char szEllapsed[MAX_PATH * 2];

   strncpy(szEllapsed, ::file::path(APP_CORE_BASE_DIR) / "show_elapsed.txt", sizeof(szEllapsed));

   //if (!defer_aura_term())
   //{

   //   ::output_debug_string("Failed to defer_core_term");

   //   on_result(-10000);

   //}

   DWORD dwEnd = ::get_tick_count();

   char szTimeMessage[2048];

   ::time_t timet = ::time(NULL);

   tm t;

#ifdef WINDOWS

   errno_t err = _localtime64_s(&t, &timet);

#else

   localtime_r(&timet, &t);

   errno_t err = errno;

#endif

   char szTime[2048];

   sprintf(szTime, "%04d-%02d-%02d %02d:%02d:%02d", t.tm_year + 1900, t.tm_mon + 1, t.tm_mday, t.tm_hour, t.tm_min, t.tm_sec);

   sprintf(szTimeMessage, "\n\n\n---------------------------------------------------------------------------------------------\n|\n|\n|  Just After First Application Request Completion %d", (uint32_t)m_dwAfterApplicationFirstRequest - m_dwStartTime);
   ::output_debug_string(szTimeMessage);
   printf("%s", szTimeMessage);

   int iMillisecondsTotal = dwEnd - m_dwStartTime;

   sprintf(szTimeMessage, "\n|  Total Elapsed Time %d ms", (uint32_t)iMillisecondsTotal);
   ::output_debug_string(szTimeMessage);
   printf("%s", szTimeMessage);

   int iMilliseconds = iMillisecondsTotal % 1000;
   int iSecondsTotal = iMillisecondsTotal / 1000;
   int iSeconds = iSecondsTotal % 60;
   int iMinutesTotal = iSecondsTotal / 60;
   int iMinutes = iMinutesTotal % 60;
   int iHoursTotal = iMinutesTotal / 60;
   int iHours = iHoursTotal % 24;
   int iDays = iHoursTotal / 24;

   if (iDays > 0)
   {

      sprintf(szTimeMessage, "\n|  Total Elapsed Time %d days %02d:%02d:%02d %03d ms", iDays, iHours, iMinutes, iSeconds, iMilliseconds);

   }
   else if (iHours > 0)
   {

      sprintf(szTimeMessage, "\n|  Total Elapsed Time %02d:%02d:%02d %03d ms", iHours, iMinutes, iSeconds, iMilliseconds);

   }
   else if (iMinutes > 0)
   {

      sprintf(szTimeMessage, "\n|  Total Elapsed Time %02d:%02d %03d ms", iMinutes, iSeconds, iMilliseconds);

   }
   else
   {

      sprintf(szTimeMessage, "\n|  Total Elapsed Time %02ds %03d ms", iSeconds, iMilliseconds);

   }

   ::output_debug_string(szTimeMessage);
   printf("%s", szTimeMessage);

   sprintf(szTimeMessage, "\n|");
   ::output_debug_string(szTimeMessage);
   printf("%s", szTimeMessage);

   sprintf(szTimeMessage, "\n|  %s", szTime);
   ::output_debug_string(szTimeMessage);
   printf("%s", szTimeMessage);

   sprintf(szTimeMessage, "\n|");
   ::output_debug_string(szTimeMessage);
   printf("%s", szTimeMessage);

   sprintf(szTimeMessage, "\n|");
   ::output_debug_string(szTimeMessage);
   printf("%s", szTimeMessage);

   sprintf(szTimeMessage, "\n-------------------------------------------------------------------------------------------- - ");
   ::output_debug_string(szTimeMessage);
   printf("%s", szTimeMessage);

   sprintf(szTimeMessage, "\n");
   ::output_debug_string(szTimeMessage);
   printf("%s", szTimeMessage);

   sprintf(szTimeMessage, "\n");
   ::output_debug_string(szTimeMessage);
   printf("%s", szTimeMessage);

   sprintf(szTimeMessage, "\n");
   ::output_debug_string(szTimeMessage);
   printf("%s", szTimeMessage);

   sprintf(szTimeMessage, "\n");
   ::output_debug_string(szTimeMessage);
   printf("%s", szTimeMessage);


   if (file_exists_raw(szEllapsed))
   {
      char szUTCTime[2048];
      //      char szLocalTime[2048];
      time_t rawtime;
      struct tm * l;
      struct tm * g;
      time(&rawtime);
      l = localtime(&rawtime);
      g = gmtime(&rawtime);
      sprintf(szUTCTime, "%04d-%02d-%02d %02d:%02d:%02d UTC", g->tm_year + 1900, g->tm_mon, g->tm_mday, g->tm_hour, g->tm_min, g->tm_sec);
      //   sprintf(szLocalTime,"%04d-%02d-%02d %02d:%02d:%02d local : ",l->tm_year + 1900,l->tm_mon,l->tm_mday,l->tm_hour,l->tm_min,l->tm_sec);
      char szTimeMessage1[2048];
      sprintf(szTimeMessage1, " Just After First Application Request Completion %d", (uint32_t)m_dwAfterApplicationFirstRequest - m_dwStartTime);
      if (file_length_raw(szEllapsed) > 0)
      {
         file_add_contents_raw(szEllapsed, "\n");
      }
      file_add_contents_raw(szEllapsed, szUTCTime);
      file_add_contents_raw(szEllapsed, szTimeMessage1);
      //file_add_contents_raw(szEllapsed,szLocalTime);
      file_add_contents_raw(szEllapsed, "\n");
      char szTimeMessage2[2048];
      sprintf(szTimeMessage2, " Total Elapsed Time %d", (uint32_t)dwEnd - m_dwStartTime);
      file_add_contents_raw(szEllapsed, szUTCTime);
      file_add_contents_raw(szEllapsed, szTimeMessage2);

   }

#ifdef __MCRTDBG

   _CrtDumpMemoryLeaks();

#endif

}



//CLASS_DECL_AURA int32_t __win_main(sp(::aura::system) psystem, ::windows::command * pmaininitdata);


typedef bool DEFER_INIT();
typedef DEFER_INIT * PFN_DEFER_INIT;



#undef new





long aura_aura(aura_main_data * pmaindata)
{

   sp(app_core) pappcore;

   pappcore = canew(app_core(pmaindata));

   if(!pappcore->beg())
   {

      return pappcore->m_iTotalErrorCount;

   }

   aura_boot(pappcore);

   return pappcore->m_iTotalErrorCount;

}


CLASS_DECL_AURA void aura_boot(app_core * pappcore)
{

   if (!::aura_prelude::defer_call_prelude(pappcore))
   {

      pappcore->on_result(-1);

      return;

   }

   aura_main(pappcore);

}



CLASS_DECL_AURA void aura_main(app_core * pappcore)
{

   pappcore->ini();

#ifdef APPLEOS

   if(pappcore->m_psystem->begin_synch())
   {

      set_main_thread(pappcore->m_psystem->m_hthread);

      set_main_thread_id(pappcore->m_psystem->m_uiThread);

      ns_shared_application(pappcore->m_pmaindata->m_argc, pappcore->m_pmaindata->m_argv);

      ns_app_run();

   }

#elif defined(METROWIN)

   pappcore->m_psystem->m_strAppId = pappcore->m_pmaindata->m_pmaininitdata->m_strAppId;

   pappcore->m_psystem->startup_command(pappcore->m_pmaindata->m_pmaininitdata);

   auto source = ::metrowin::new_directx_application_source(pappcore->m_psystem, pappcore->m_pmaindata->m_pmaininitdata->m_strCommandLine);

   ::Windows::ApplicationModel::Core::CoreApplication::Run(source);

#else

   pappcore->run();

#endif

   pappcore->end();

}


#define new AURA_NEW



aura_prelude::aura_prelude()
{

   s_pprelude = this;

}


aura_prelude::aura_prelude(::aura::PFN_GET_NEW_APP pgetnewapp)
{

   s_pprelude = this;

   m_pfnNewApp = pgetnewapp;

}


aura_prelude::~aura_prelude()
{

}


bool aura_prelude::defer_call_construct(app_core * pappcore)
{

   if(s_pprelude == NULL)
   {

      return NULL;

   }

   if(!s_pprelude->construct(pappcore))
   {

      return NULL;

   }

   return true;

}


bool aura_prelude::construct(app_core * pappcore)
{

   return true;

}


bool aura_prelude::defer_call_prelude(app_core * pappcore)
{

   if(s_pprelude == NULL)
   {

      return true;

   }

   if(!s_pprelude->prelude(pappcore))
   {

      return false;

   }

   return true;

}



bool aura_prelude::prelude(app_core * pappcore)
{

   pappcore->m_pfnNewApp = m_pfnNewApp;

   return true;

}


stringa get_c_args(const char * psz)
{

   stringa stra;

   if(psz == NULL)
   {

      return stra;

   }

   stringa straBeforeColon;

   stringa straAfterColon;

   const char * pszEnd = psz + strlen(psz);

   string str;

   int i = 0;

   bool bColon = false;

   while(psz < pszEnd)
   {

      ::str::consume_spaces(psz, 0, pszEnd);

      if(psz >= pszEnd)
      {

         break;

      }
      if(*psz == '\"')
      {

         str = ::str::consume_quoted_value_ex(psz, pszEnd);

      }
      else if(*psz == '\'')
      {

         str = ::str::consume_quoted_value_ex(psz, pszEnd);

      }
      else
      {

         str = ::str::consume_non_spaces(psz, pszEnd);

      }

      if (str == ":")
      {

         bColon = true;

      }
      else if (!bColon && (i == 0 || str[0] != '-'))
      {

         straBeforeColon.add(str);

      }
      else
      {

         straAfterColon.add(str);

      }

      i++;

   }

   stra = straBeforeColon;

   if (straAfterColon.has_elements())
   {

      stra.add(":");

      stra += straAfterColon;

   }

   return stra;

}

stringa get_c_args_for_c(const char * psz)
{
   
   stringa stra;
   
   if(psz == NULL)
   {
      
      return stra;
      
   }
   
   const char * pszEnd = psz + strlen(psz);
   
   string str;
   
   while(psz < pszEnd)
   {
      
      ::str::consume_spaces(psz, 0, pszEnd);
      
      if(psz >= pszEnd)
      {
         
         break;
         
      }
      
      if(*psz == '\"')
      {
         
         str = ::str::consume_quoted_value(psz, pszEnd);
         
      }
      else if(*psz == '\'')
      {
         
         str = ::str::consume_quoted_value(psz, pszEnd);
         
      }
      else
      {
         
         str = ::str::consume_non_spaces(psz, pszEnd);
         
      }
      
      stra.add(str);
         
   }
   
   return stra;
   
}


stringa get_c_args(int argc, char ** argv)
{

   stringa straBeforeColon;

   stringa straAfterColon;

   if(argc > 0)
   {

      straBeforeColon.add(argv[0]);

   }

   bool bColon = false;

   for(int i = 1; i < argc; i++)
   {

      if(strcmp(argv[i], ":") == 0)
      {
         bColon = true;
      }
#ifdef WINDOWS
      else if(bColon || straAfterColon.has_elements() || argv[i][0] == '-' || (argv[i][0] == '/' && strlen(argv[i]) == 2))
#else
      else if(bColon || straAfterColon.has_elements() || argv[i][0] == '-')
#endif
      {

         straAfterColon.add(argv[i]);

      }
      else
      {

         straBeforeColon.add(argv[i]);

      }

   }

   stringa stra;

   stra = straBeforeColon;

   if (straAfterColon.has_elements())
   {

      stra.add(":");

      stra += straAfterColon;

   }

   return stra;

}


typedef size_t FN_GET_STRING(char * psz, size_t s);
typedef FN_GET_STRING * PFN_GET_STRING;



#ifdef APPLEOS

string apple_get_bundle_identifier()
{

   return ::str::get_string(&ns_get_bundle_identifier);

}

#endif







string transform_to_c_arg(const char * psz)
{
   
   bool bNeedWrap = false;
   
   const char * pszParse = psz;
   
   char chQuote = '\0';
   
   while(*pszParse)
   {
      
      if(chQuote != '\0')
      {
         
         if(*pszParse == '\\')
         {
            
            pszParse = ::str::utf8_inc(pszParse);
            
         }
         else if(*pszParse == chQuote)
         {
            
            chQuote = '\0';
            
         }
         
      }
      else if(::str::ch::is_whitespace(pszParse)
              || *pszParse == ':')
      {
         
         bNeedWrap = true;
         
         break;
         
      }
      
      pszParse = ::str::utf8_inc(pszParse);
      
   }
   
   if (bNeedWrap)
   {

      return string("\"") + ::str::replace("\"", "\\\"", psz) + "\"";

   }
   else
   {

      return psz;

   }

}


string merge_colon_args(const array < stringa > & str2a)
{

   stringa straBeforeColon;

   stringa straAfterColon;

   string strCommandLine;

   for (auto & stra : str2a)
   {

      index iFindColon = stra.find_first(":");

      if (stra.get_size() > 0 && iFindColon != 0)
      {

         if (strCommandLine.is_empty())
         {

            strCommandLine = transform_to_c_arg(stra[0]);

         }

      }

      if (iFindColon < 0)
      {

         iFindColon = stra.get_size();

      }

      for (index i = 1; i < stra.get_count(); i++)
      {

         string str = stra[i];

         if (i < iFindColon)
         {

            straBeforeColon.add(str);

         }
         else if (i > iFindColon)
         {

            if (::str::begins_eat_ci(str, "app="))
            {

               if (straAfterColon.find_first_begins("app=") >= 0) // fixed case when added below :D..O
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

   strCommandLine += ::str::has_char(straBeforeColon.pred_implode(&transform_to_c_arg, " "), " ");

   strCommandLine += " : ";

   strCommandLine += straAfterColon.pred_implode(&transform_to_c_arg, " ");

   return strCommandLine;

}

