#include "framework.h"
#include "aura/net/net_sockets.h"


#include <stdio.h>
// #include <stdarg.h>

#if defined(LINUX) || defined(ANDROID)
//#include <sys/types.h>
//#include <unistd.h>
#endif

namespace aura
{





   log::log(::aura::application * papp) :
      object(papp),
      m_mutexTrace(papp)
   {

#if !ENABLE_TRACE

      m_bTrace = false;

#else

      ::file::path pathTrace = ::dir::appdata("system") / "trace.txt";

#ifdef DEBUG

      if (!file_exists_dup(pathTrace))
      {

         ::file_put_contents_dup(pathTrace, "yes");

      }

#endif

      m_bTrace = ::is_debugger_attached() || ::file_is_true_dup(pathTrace);

#endif

      m_pmutex          = new mutex(papp);
      m_ptrace          = new ::aura::trace::trace(papp);
      m_bLog            = true;

      m_pfile           = NULL;

      m_bInitialized    = false;



      m_iYear           = -1;
      m_iMonth          = -1;
      m_iDay            = -1;
      m_straSeparator.add("\r\n");
      m_straSeparator.add("\r");
      m_straSeparator.add("\n");

      set_trace_category(::aura::trace::category_General, "category_General", 3000);
      set_trace_category(::aura::trace::category_COM, "category_COM", 0);
      set_trace_category(::aura::trace::category_QI, "category_QI", 0);
      set_trace_category(::aura::trace::category_Registrar, "category_Registrar", 0);
      set_trace_category(::aura::trace::category_Refcount, "category_Refcount", 0);
      set_trace_category(::aura::trace::category_Windowing, "category_Windowing", 0);
      set_trace_category(::aura::trace::category_Controls, "category_Controls", 0);
      set_trace_category(::aura::trace::category_Hosting, "category_Hosting", 0);
      set_trace_category(::aura::trace::category_DBClient, "category_DBClient", 0);
      set_trace_category(::aura::trace::category_DBProvider, "category_DBProvider", 0);
      set_trace_category(::aura::trace::category_Snapin, "category_Snapin", 0);
      set_trace_category(::aura::trace::category_NotImpl, "category_NotImpl", 0);
      set_trace_category(::aura::trace::category_Allocation, "category_Allocation", 0);
      set_trace_category(::aura::trace::category_Exception, "category_Exception", 0);
      set_trace_category(::aura::trace::category_Time, "category_Time", 0);
      set_trace_category(::aura::trace::category_Cache, "category_Cache", 0);
      set_trace_category(::aura::trace::category_Stencil, "category_Stencil", 0);
      set_trace_category(::aura::trace::category_String, "category_String", 0);
      set_trace_category(::aura::trace::category_Map, "category_Map", 0);
      set_trace_category(::aura::trace::category_Util, "category_Util", 0);
      set_trace_category(::aura::trace::category_Security, "category_Security", 0);
      set_trace_category(::aura::trace::category_Sync, "category_Sync", 0);
      set_trace_category(::aura::trace::category_ISAPI, "category_ISAPI", 0);

      set_trace_category(::aura::trace::category_User, "category_User", 0);
      set_trace_category(::aura::trace::category_User2, "category_User2", 0);
      set_trace_category(::aura::trace::category_User3, "category_User3", 0);
      set_trace_category(::aura::trace::category_User4, "category_User4", 0);


      set_trace_category(::aura::trace::category_AppMsg, "AppMsg", 0);        // main message pump trace (includes DDE)
      set_trace_category(::aura::trace::category_WinMsg, "category_WinMsg", 0);         // Windows message tracing
      set_trace_category(::aura::trace::category_CmdRouting, "category_CmdRouting", 0);     // Windows command routing trace
      set_trace_category(::aura::trace::category_Ole, "category_Ole", 0);           // special OLE callback trace
      set_trace_category(::aura::trace::category_Database, "category_Database", 0);      // special database trace
      set_trace_category(::aura::trace::category_Internet, "category_Internet", 0);      // special Internet client trace
      set_trace_category(::aura::trace::category_dumpContext, "category_dumpContext", 0);    // traces from dump_context
      set_trace_category(::aura::trace::category_Memory, "category_Memory", 0);       // generic non-kernel memory traces
      set_trace_category(::aura::trace::category_Html, "category_Html", 0);          // Html traces
      set_trace_category(::aura::trace::category_Socket, "category_Socket", 0);       // socket traces

   }


   log::~log()
   {

      ::aura::del(m_ptrace);

   }


//   extern sp(::aura::application) g_papp;

   CLASS_DECL_AURA int32_t SimpleDebugReport(int32_t iReportType, const char * pszFileName,int32_t iLine,const char *,const char * pszFormat, va_list list)
   {
#ifdef WIN32

      if(iReportType == _CRT_ASSERT)
      {

         if(is_debugger_attached())
         {

            string str;

            str += "\r\nAssertion Failed \r\n";
            str += "File : ";
            str += pszFileName;
            str += "\r\nLine : ";
            str += ::str::from(iLine);
            str += "\r\n";

            string strCaption;

            strCaption = "Assertion Failed";

            output_debug_string(wstring(str));
            /*if(simple_message_box(NULL, str, strCaption, MB_ICONINFORMATION | MB_OKCANCEL | MB_DEFBUTTON1) == IDCANCEL)
            {
               string strCmdLine = "\"C:\\Program Files (x86)\\Microsoft Visual Studio 11.0\\Common7\\IDE\\devenv.exe\" /edit \""+string(pszFileName)+ "\" /command \"edit.goto "+::str::from(iLine)+"\"";
               ::system(strCmdLine);
               exit(0);
            }
            */
         }



      }
      else
      {

         char buf[2048];
         vsnprintf_s(buf, sizeof(buf), sizeof(buf), pszFormat, list);
         output_debug_string(wstring(buf));

      }

#else
      vprintf(pszFormat, list);
#endif
      return 0;
   }

   void log::set_extended_log(bool bSet)
   {
      m_bExtendedLog = bSet;
   }

   bool log::get_extended_log()
   {
      return m_bExtendedLog;
   }


   void log::success(const char * psz)
   {
      print(psz);
   }

   void log::trace_v(const char *pszFileName, int32_t nLine, uint32_t dwCategory, uint32_t nLevel, const char * pszFormat, va_list args) const
   {

      string str;

      str.FormatV(pszFormat, args);

      trace_str(pszFileName, nLine, dwCategory, nLevel, str);

   }

   void log::trace_str(const char *pszFileName, int32_t nLine, uint32_t dwCategory, uint32_t nLevel, const char * psz) const
   {

      UNREFERENCED_PARAMETER(nLine);
      UNREFERENCED_PARAMETER(pszFileName);

      synch_lock sl2(&((log *)this)->m_mutexTrace);

      //((log * )this)->print(pszFormat, args);
      //m_trace.TraceV(pszFileName, nLine, dwCategory, nLevel, pszFmt, args);

      //sl.lock();
      log * plog = (log *) this;
      ::aura::trace::category & category = plog->m_ptrace->m_map[dwCategory];
      if(category.m_estatus == ::aura::trace::status_disabled || category.m_uiLevel > nLevel)
         return;
      //sl.unlock();
      stringa stra;
      stra.add_lines(psz, FALSE);
      /*for(int32_t i = 0; i < stra.get_size(); i++)
      {
         if(stra[i].get_length() > 200)
         {
            string & strLine = stra[i];
            const char * psz = strLine;
            int32_t j = 200;
            while(*psz != NULL && j >= 0 && !::str::ch::is_space_char(psz))
            {
               j--;
               psz = ::str::utf8_inc(psz);
            }
            if(j <= 0)
               j = 200;
            stra.insert_at(i + 1, string(strLine, psz - (LPCSTR)strLine));
            stra[i] = stra[i].Left(j);
            continue;
         }
      }*/
      string strPre;
      ::datetime::time time;
      time = time.get_current_time();
      time.Format(strPre, "%Y-%m-%d %H:%M:%S");
      string strTick;
      uint64_t uiTotalMillis = ::get_tick_count() - ::get_first_tick();
      uint64_t uiMillis = uiTotalMillis % 1000;
      uint64_t uiTotalSeconds = uiTotalMillis / 1000;
      uint64_t uiSeconds = uiTotalSeconds % 60;
      uint64_t uiTotalMinutes = uiTotalSeconds / 60;
      uint64_t uiMinutes = uiTotalMinutes % 60;
      uint64_t uiTotalHours = uiTotalMinutes / 60;
      uint64_t uiHours = uiTotalHours % 24;
      uint64_t uiTotalDays = uiTotalHours / 24;
      // sipman LCTV learning to format hours, minutes and seconds.... (me (re) learning too)...
      if (uiTotalDays > 0)
      {
         strTick.Format(" %d:%d:%d:%d.%03d ", uiTotalDays, uiHours, uiMinutes, uiSeconds, uiMillis);
      }
      else if(uiTotalHours > 0)
      {
         strTick.Format(" %d:%d:%d.%03d ", uiHours, uiMinutes, uiSeconds, uiMillis);
      }
      else if (uiTotalMinutes > 0)
      {
         strTick.Format(" %d:%d.%03d ", uiMinutes, uiSeconds, uiMillis);
      }
      else if (uiTotalSeconds > 0)
      {
         strTick.Format(" %d.%03ds ", uiSeconds, uiMillis);
      }
      else
      {
         strTick.Format(" %3dms ", uiMillis);
      }

      //sl.lock();
      if(m_bTrace &&
         (plog->m_pfile == NULL
         || plog->m_iYear != time.GetYear()
         || plog->m_iMonth != time.GetMonth()
         || plog->m_iDay != time.GetDay()))
      {
         if(plog->m_pfile != NULL)
         {
            fflush(plog->m_pfile);
            fclose(plog->m_pfile);
            plog->m_pfile = NULL;
         }
         int32_t iRetry = 0;
retry:
         string strRelative;
         time.Format(strRelative, "%Y/%m/%d");
         string strIndex;
#ifdef WINDOWS
         strIndex.Format("%d-%05d", GetCurrentProcessId(), iRetry);
#else
         strIndex.Format("%d-%05d", getpid(), iRetry);
#endif

         string strPath;

#ifdef WINDOWSEX

         unichar wsz[4096];

         if(!GetModuleFileNameW(NULL,wsz,sizeof(wsz) / sizeof(unichar)))
         {

            strPath = "_";

         }
         else
         {

            strPath = ::str::international::unicode_to_utf8(wsz);

         }

#elif defined(METROWIN)

#else

         char * psz = br_find_exe("unknown-app");

         strPath = psz;

         free(psz);

#endif

         strPath.replace("\\", "/");

         strPath = solve_relative_compressions(strPath);

         strPath.replace(":","_");

         plog->m_strLogPath = ::dir::sys_temp() /  string(m_id) / strPath/  strRelative + "-" + strIndex + ".log";

         try
         {
            if(!::dir::is(::dir::name(plog->m_strLogPath)))
            {
               ::dir::mk(::dir::name(plog->m_strLogPath));
            }
            if(!(plog->m_pfile = fopen(m_strLogPath, "at")))
            {
               int32_t iError = errno;
               if(iError == ENOENT)
               {
                  goto skip_further_possible_recursive_impossible_logging_in_file;
               }
               else
               {
                  if(iError == EAGAIN)
                  {
                  }
                  else
                  {
                     iRetry++;
                     if(iRetry >= 100000)
                        return;
                     goto retry;

                  }
               }
            }
         }
         catch(...)
         {
            try
            {
               if(plog->m_pfile)
               {
                  fclose(plog->m_pfile);
                  plog->m_pfile = NULL;
               }

               iRetry++;
               if(iRetry >= 100000)
                  return;
               goto retry;
            }
            catch(...)
            {
            }
         }
         plog->m_iYear     = time.GetYear();
         plog->m_iMonth    = time.GetMonth();
         plog->m_iDay      = time.GetDay();
         plog->print("<log>Starting Log</log>"); // <<  this is one of the "...possible_recursive_impossible_logging_in_file"...
      }

skip_further_possible_recursive_impossible_logging_in_file:

      if(m_bTrace && plog->m_pfile != NULL)
      {

         fseek(plog->m_pfile,0,SEEK_END);

      }

      for(int32_t i = 0; i < stra.get_size(); i++)
      {

         string strLine = strPre + strTick + stra[i] + "\r\n";

         try
         {
#ifdef VSNORD
            ::output_debug_string(stra[i]);
#else
            ::output_debug_string(strLine);
#endif

            if(m_bTrace && plog->m_pfile)
            {

               fputs(strLine,plog->m_pfile);

            }

         }
         catch(::exception::exception &)
         {

            // Ignore exception here because this class/function is used for debugging

         }

      }

   }

   /*   void log::trace_v(const char *pszFileName, int32_t nLine, uint32_t dwCategory, uint32_t nLevel, const unichar * pszFmt, va_list args) const
      {
      }*/

   /*   void log::set_trace_category(uint32_t dwCategory, const char * pszName, uint32_t uiLevel)
      {
      }*/

   void log::trace2(uint32_t dwCategory, UINT nLevel, const char * pszFormat, ...)
   {
      if(!m_bTrace)
         return;
      va_list ptr;
      va_start(ptr, pszFormat);
      trace_v(NULL, -1, dwCategory, nLevel, pszFormat, ptr);
      va_end(ptr);

   }

   void log::sockets_log(::sockets::base_socket_handler * phandler, ::sockets::base_socket * sock, const string & strUser, int32_t iError, const string & strSystem, ::aura::log::e_level elevel)
   {

      string strLevel = ::log_level_name(elevel);

      if (sock)
      {
         trace("fd %d :: %s: %d %s (%s)\n", sock->GetSocket(), strUser.c_str(), iError, strSystem.c_str(), strLevel.c_str());
      }
      else
      {
         trace("%s: %d %s (%s)\n", strUser.c_str(), iError, strSystem.c_str(), strLevel.c_str());
      }

   }


   void log::print(const char * pszFormat, ...)
   {
      va_list ptr;
      va_start(ptr, pszFormat);
      trace_v(NULL, -1, ::aura::trace::category_General, 0, pszFormat, ptr);
      va_end(ptr);
   }

   bool log::initialize(const char * pszId)
   {
      return initialize(id(pszId));
   }

   bool log::initialize(id id)
   {
      single_lock sl(m_pmutex, TRUE);
      if(m_bInitialized)
         return false;
      //if(!::aura::log::initialize(id))
      // return false;
      m_id = id;
      m_bInitialized = true;
      if(file_exists_dup(::dir::appdata(process_platform_dir_name2()) / "debug.txt"))
      {
         string str = file_as_string_dup(::dir::appdata(process_platform_dir_name2())/"debug.txt");
         if(str.get_length() == 0 || str.Left(2).trim() != "0")
         {
            m_bLog = true;
         }
         else
         {
            m_bLog = false;
         }
      }
      else
      {
         m_bLog = is_debugger_attached() != FALSE;
      }
      sl.unlock();
      print("<log>Log Initialized!!</log>");
      return true;
   }

   bool log::finalize()
   {
      single_lock sl(m_pmutex, TRUE);
      if(!m_bInitialized)
         return false;
      bool bOk = ::aura::log::finalize();
      fclose(m_pfile);
      m_pfile = NULL;
      m_bInitialized = false;
      return bOk;
   }



   void log::set_trace_category(uint32_t dwCategory, const char * pszName, uint32_t uiLevel)
   {
      ::aura::trace::category & category = m_ptrace->operator[](dwCategory);
      category.m_strCategory = pszName;
      category.m_dwCategory = dwCategory;
      category.m_uiLevel = uiLevel;
      category.m_estatus = uiLevel >= 1 ? ::aura::trace::status_enabled : ::aura::trace::status_disabled;
   }


   void log::trace(const char * pszFormat, ...)
   {

      if (void_ptr_is_null(this))
      {
         va_list ptr;
         va_start(ptr, pszFormat);
         vprintf(pszFormat, ptr);
         va_end(ptr);
         return;
      }

      va_list ptr;
      va_start(ptr, pszFormat);
      trace_v(NULL, -1, ::aura::trace::category_General, 0, pszFormat, ptr);
      va_end(ptr);
   }

   /*void log::trace2(uint32_t dwCategory, UINT nLevel, const char * pszFormat, ...)
   {
      if(!m_bTrace)
         return;
      va_list ptr;
      va_start(ptr, pszFormat);
      trace_v(NULL, -1, dwCategory, nLevel, pszFormat, ptr);
      va_end(ptr);
   }*/

} // namespace core



