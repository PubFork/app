﻿#include "framework.h"
#include <time.h>


PFN_AURA_APP_CORE aura_prelude::s_pfnPrelude = NULL;

::aura::PFN_GET_NEW_APP aura_prelude::s_pfnNewApp = NULL;


#ifdef WINDOWS

#define APP_CORE_BASE_DIR "C:\\ca2\\config\\system"

#else

#define APP_CORE_BASE_DIR "/var/tmp/ca2/config/system"

#endif

// ATTENTION
// This class should (if it uses) member functions with care:
// It is used after all application app_core (library) finalization,
// when even new/delete/strings/ids can be used anymore for example.

app_core::app_core(aura_main_data * pdata)
{

   m_pmaindata = pdata;

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


   if (!defer_aura_init())
   {

      ::output_debug_string("Failed to defer_core_init");

      return on_result(-4);

   }

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


void app_core::run()
{

   m_bAcidApp = m_pfnNewApp != NULL;

   if (!node_fill(this))
   {

      on_result(-1);

      return;

   }

   m_psystem = g_pfn_create_system(this);

   if (m_psystem == NULL)
   {

      on_result(-1);

      return;

   }

   m_psystem->startup_command(m_pmaindata->m_pmaininitdata);

   // what could influence time before main?
   // cold start (never previously called program and its Dlls...)?
   m_psystem->m_dwMainStartTime = m_dwStartTime;

   m_psystem->m_strAppId = m_pmaindata->m_pmaininitdata->m_strAppId;

   xxdebug_box("box1", "box1", MB_ICONINFORMATION);

   set_main_thread(GetCurrentThread());

   set_main_thread_id(GetCurrentThreadId());

   if (!m_psystem->pre_run())
   {

      return;

   }

   on_result(m_psystem->main());

   try
   {

      m_psystem->exit_thread();

   }
   catch (...)
   {


   }

   try
   {

      m_dwAfterApplicationFirstRequest = m_psystem->m_dwAfterApplicationFirstRequest;

   }
   catch (...)
   {

   }

   ::aura::del(m_psystem);

}


void app_core::end()
{

   char szEllapsed[MAX_PATH * 2];

   strncpy(szEllapsed, ::file::path(APP_CORE_BASE_DIR) / "show_elapsed.txt", sizeof(szEllapsed));

   if (!defer_aura_term())
   {

      ::output_debug_string("Failed to defer_core_term");

      on_result(-10000);

   }

   DWORD dwEnd = ::get_tick_count();

   char szTimeMessage[2048];

   ::time_t timet = ::time(NULL);

   tm t;

   errno_t err = _localtime64_s(&t, &timet);

   char szTime[2048];

   sprintf(szTime, "%04d-%02d-%02d %02d:%02d:%02d", t.tm_year + 1900, t.tm_mon + 1, t.tm_mday, t.tm_hour, t.tm_min, t.tm_sec);

   sprintf(szTimeMessage, "\n\n\n---------------------------------------------------------------------------------------------\n|\n|\n|  Just After First Application Request Completion %d", (uint32_t)m_dwAfterApplicationFirstRequest - m_dwStartTime);
   ::output_debug_string(szTimeMessage);
   printf(szTimeMessage);

   int iMillisecondsTotal = dwEnd - m_dwStartTime;

   sprintf(szTimeMessage, "\n|  Total Elapsed Time %d ms", (uint32_t)iMillisecondsTotal);
   ::output_debug_string(szTimeMessage);
   printf(szTimeMessage);

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
   printf(szTimeMessage);

   sprintf(szTimeMessage, "\n|");
   ::output_debug_string(szTimeMessage);
   printf(szTimeMessage);

   sprintf(szTimeMessage, "\n|  %s", szTime);
   ::output_debug_string(szTimeMessage);
   printf(szTimeMessage);

   sprintf(szTimeMessage, "\n|");
   ::output_debug_string(szTimeMessage);
   printf(szTimeMessage);

   sprintf(szTimeMessage, "\n|");
   ::output_debug_string(szTimeMessage);
   printf(szTimeMessage);

   sprintf(szTimeMessage, "\n-------------------------------------------------------------------------------------------- - ");
   ::output_debug_string(szTimeMessage);
   printf(szTimeMessage);

   sprintf(szTimeMessage, "\n");
   ::output_debug_string(szTimeMessage);
   printf(szTimeMessage);

   sprintf(szTimeMessage, "\n");
   ::output_debug_string(szTimeMessage);
   printf(szTimeMessage);

   sprintf(szTimeMessage, "\n");
   ::output_debug_string(szTimeMessage);
   printf(szTimeMessage);

   sprintf(szTimeMessage, "\n");
   ::output_debug_string(szTimeMessage);
   printf(szTimeMessage);


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



CLASS_DECL_AURA int32_t __win_main(sp(::aura::system) psystem, ::windows::command * pmaininitdata);


typedef bool DEFER_INIT();
typedef DEFER_INIT * PFN_DEFER_INIT;



#undef new


CLASS_DECL_AURA int main(int argc, char * argv[])
{

   ap(aura_main_data) pmaindata = new aura_main_data(argc, argv);

   return aura_aura(pmaindata);

   //app_core appcore(&maindata);

   //int iError = 0;

   //iError = appcore.start();

   //if (iError != NOERROR)
   //{

   //   return iError;

   //}

   //iError = app_common_main(argc, argv, appcore);

   //return appcore.end();

}


long aura_aura(aura_main_data * pmaindata)
{

   ap(app_core) pappcore;

   pappcore = new app_core(pmaindata);

   if(!pappcore->beg())
   {

      return pappcore->m_iTotalErrorCount;

   }

   aura_boot(pappcore);

   return pappcore->m_iTotalErrorCount;

}


CLASS_DECL_AURA void aura_boot(app_core * pappcore)
{

   if (::aura_prelude::s_pfnPrelude != NULL)
   {

      if (!::aura_prelude::s_pfnPrelude(pappcore))
      {

         pappcore->on_result(-1);

         return;

      }

   }

   aura_main(pappcore);

}



CLASS_DECL_AURA void aura_main(app_core * pappcore)
{

   pappcore->run();

   pappcore->end();

}


#define new AURA_NEW





aura_prelude::aura_prelude(PFN_AURA_APP_CORE pprelude)
{

   s_pfnPrelude = pprelude;

}


aura_prelude::aura_prelude(::aura::PFN_GET_NEW_APP pgetnewapp)
{

   s_pfnPrelude = &acid_get_preamble;

   s_pfnNewApp = pgetnewapp;

}


bool aura_prelude::acid_get_preamble(app_core * pappcore)
{

   pappcore->m_pfnNewApp = s_pfnNewApp;

   return true;

}
