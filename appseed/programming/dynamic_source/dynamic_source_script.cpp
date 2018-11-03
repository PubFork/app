#include "framework.h"
#include "dynamic_source.h"


#if defined(LINUX) || defined(APPLEOS)
#if defined(APPLEOS)

#ifndef APPLEOS
#define _DARWIN_C_SOURCE
#endif

#endif
#include <dlfcn.h>
#include <sys/stat.h>
#endif


namespace dynamic_source
{


   script::script(::aura::application * papp) :
      ::object(papp),
      m_memfileError(papp)
   {

      defer_create_mutex();

   }


   script::~script()
   {

   }


   void script::run(script_instance * pinstance)
   {
      pinstance->run();
   }


   bool script::ShouldBuild()
   {

      return true;

   }


   ds_script::ds_script(::aura::application * papp) :
      ::object(papp),
      script(papp),
      m_evCreationEnabled(papp)
   {

      m_lpfnCreateInstance       = NULL;
      m_bShouldBuild             = true;
      m_bShouldCalcTempError     = true;
      m_bHasTempError            = false;
      m_bHasTempOsError          = false;
      m_bUnloading               = false;
      m_evCreationEnabled.SetEvent();



   }





   ds_script::~ds_script()
   {

      Unload();

   }


   bool ds_script::DoesMatchVersion()
   {

      if(get_tick_count() - m_dwLastVersionCheck < (5000))
      {
         return m_bLastVersionCheck;
      }

      m_dwLastVersionCheck = get_tick_count();

      synch_lock sl(m_pmutex);

      bool bMatches = false;

      auto ft = get_file_time(m_strSourcePath);

      bMatches = m_ft == ft;

      m_bLastVersionCheck = bMatches;
      return bMatches;
   }

   bool ds_script::ShouldBuild()
   {

      synch_lock sl(m_pmutex);

      bool bManagerShouldBuild = m_pmanager->should_build(m_strSourcePath);

      if (bManagerShouldBuild)
      {

         return true;

      }

      return m_bShouldBuild || HasDelayedTempError() || !DoesMatchVersion();

   }

   void ds_script::on_start_build()
   {

      synch_lock sl(m_pmutex);

      m_bShouldCalcTempError     = true;

      m_bShouldBuild             = false;

      m_bHasTempOsError          = false;

      m_memfileError.set_length(0);

      m_strError.Empty();

      Unload();

   }

   bool ds_script::HasTimedOutLastBuild()
   {
      synch_lock sl(m_pmutex);
      return (::get_tick_count() - m_dwLastBuildTime) >
             (m_pmanager->m_dwBuildTimeWindow + System.math().RandRange(0, m_pmanager->m_dwBuildTimeRandomWindow));
   }

   bool ds_script::HasCompileOrLinkError()
   {
      synch_lock sl(m_pmutex);

      string str;

      str = m_strError;

      if(str.find(" error(") >= 0)
         return true;
      if(str.find(" error ") >= 0)
         return true;
      if(str.find(" get_last_error ") >= 0)
         return true;
      return false;
   }

   bool ds_script::HasDelayedTempError()
   {

      return HasTempError() && HasTimedOutLastBuild();

   }


   bool ds_script::HasTempError()
   {
      synch_lock sl(m_pmutex);
      // if m_strError is empty, sure there is a error... at least the
      // successfull compilation/linking message ("error message" => m_strError) should exist
      // If it is empty, it is considered a temporary error (due locks or race conditions...)
      if(m_strError.is_empty() || m_bShouldCalcTempError)
      {
         m_bShouldCalcTempError = false;
         m_bHasTempError = CalcHasTempError();
      }
      return m_bHasTempError;
   }

   bool ds_script::CalcHasTempError()
   {

      synch_lock sl(m_pmutex);

      if (m_bHasTempOsError)
         return true;

      string str;

      str = m_strError;

      str.trim();

      if(str.is_empty())
         return true;

      {
         strsize iFind1 = str.find(" C1033:");
         if(iFind1 >= 0)
            return true;
      }
      {
         strsize iFind1 = str.find(" C1083:"); // Permission Denied
         if(iFind1 >= 0)
            return true;
      }
      {
         strsize iFind1 = str.find(" C1041:"); // fatal error C1041: cannot open program database
         if(iFind1 >= 0)
            return true;
      }
      {
         strsize iFind1 = str.find(".dll: does not exist.");
         if(iFind1 >= 0)
         {
            // if dll does not exist
            {
               strsize iFind1 = str.find(" error(");
               strsize iFind2 = str.find(" error ");
               strsize iFind3 = str.find("Linking...");
               // and have compile error (others than the ones above, that are considered temporary as they may be due temporary file locks, for example...).
               if((iFind3 >= 0 && ((iFind1 < iFind3 && iFind1 >= 0) ||
                                   (iFind2 < iFind3 && iFind2 >= 0))))
               {
                  return false;
               }
            }

         }
      }

      {
         strsize iFind1 = str.find("warning LNK4099:");
         if(iFind1 >= 0)
            return true;
      }
      {
         strsize iFind1 = str.find("fatal error LNK1168:");
         if(iFind1 >= 0)
            return true;
      }
      {
         strsize iFind1 = str.find(" error(");
         strsize iFind2 = str.find(" error ");
         strsize iFind3 = str.find("Linking...");
         if(iFind3 >= 0 && (iFind1 > iFind3 || iFind2 > iFind3))
         {
            return true;
         }
      }
      if(str.find(" get_last_error ") >= 0)
         return true;
      return false;
   }


   void ds_script::Load()
   {

      synch_lock sl(m_pmutex);

      if(!Application.file().exists(m_strScriptPath))
      {

         if(HasTempError())
         {

            m_memfileError << m_strScriptPath << ": does not exist because of \"temp\" error.";

         }
         else
         {

            m_memfileError << m_strScriptPath << ": does not exist.";

         }

         m_lpfnCreateInstance = NULL;

         return;

      }

      if (m_plibrary.is_null() || m_plibrary->is_closed())
      {

         m_plibrary.alloc(allocer());

         string strStagePath = m_pmanager->get_full_stage_path(m_strScriptPath);

         ::file_copy_dup(strStagePath, m_strScriptPath, true);

         m_plibrary->open(strStagePath, true);

         if(m_plibrary->is_closed())
         {

#ifdef LINUX

            const char * psz = dlerror();

#endif

            uint32_t dwMessageId = get_last_error();

            if(dwMessageId == 0x139)
            {

               debug_break();

            }

            TRACE("Error Message Id: %d\n", dwMessageId);

            string strError = get_system_error_message(::get_last_error());

            string str;

            str.Format("%d - ", ::get_last_error());

            m_memfileError << strStagePath << " : LoadLibrary, get_last_error : " << str << strError;

         }

      }

      if (m_plibrary.is_set() && !m_plibrary->is_closed())
      {

         m_lpfnCreateInstance = m_plibrary->get < NET_NODE_CREATE_INSTANCE_PROC >("create_dynamic_source_script_instance");

         if (m_lpfnCreateInstance == NULL)
         {

            TRACE("create_dynamic_source_script_instance error");

         }

      }

   }


   void ds_script::Unload()
   {

      if (m_bUnloading)
      {

         return;

      }

      keep < bool > unloading(&m_bUnloading,true,false,true);

      m_evCreationEnabled.ResetEvent();

      synch_lock sl(m_pmutex);

      if(m_plibrary != NULL && m_plibrary->is_opened())
      {

         m_plibrary->m_bAutoUnload = true;

         m_plibrary->close();

         string strStagePath = m_pmanager->get_stage_path(m_strScriptPath);

         m_lpfnCreateInstance = (NET_NODE_CREATE_INSTANCE_PROC) NULL;

      }

   }


   script_instance * ds_script::create_instance()
   {

      synch_lock slCompiler(&Application.m_semCompiler);

      synch_lock sl(m_pmutex);

      defer_build();

      script_instance * pinstance = NULL;

      if(m_lpfnCreateInstance == NULL)
      {

         return NULL;

      }

      try
      {

         pinstance = m_lpfnCreateInstance(this);

      }
      catch (...)
      {

      }

      pinstance->m_pmanager = m_pmanager;

      pinstance->m_dwCreate = get_tick_count();

      return pinstance;

   }


   void ds_script::defer_build()
   {

      synch_lock sl(m_pmutex);

      if (m_plibrary.is_set() && !m_plibrary->is_closed())
      {

         return;

      }

      if (m_strSourcePath.find_ci("\\applications\\basic\\") > 0)
      {

         TRACE("/applications/basic/");

      }

      try
      {

         ::multithreading::set_priority(::multithreading::priority_highest);

      }
      catch (...)
      {

      }

      string str;

      int32_t iRetry = 0;

      bool bHasTempError = false;

      do
      {

         if (iRetry > 0)
         {

            Sleep((DWORD)System.math().RandRange(2000, 4000));

         }

         m_pmanager->m_pcompiler->compile(this);

         str = m_strError;

         if (iRetry == 0)
         {

            TRACE("Build: %s\n%s\n", m_strName.c_str(), str.c_str());

         }
         else
         {

            TRACE("Retry(%d): %s\nError: %s\n", iRetry, m_strName.c_str(), str.c_str());

         }

         iRetry++;

      }
      while ((bHasTempError = HasTempError()) && iRetry < 8 && ::get_thread_run());

      if (!::get_thread_run())
      {

         return;

      }

      m_dwLastBuildTime = ::get_tick_count();

      m_ft = get_file_time(m_strSourcePath);

      Load();

      if (!::get_thread_run())
      {

         return;

      }

      m_bShouldBuild = false;

      {

         synch_lock sl(&m_pmanager->m_mutexShouldBuild);

         m_pmanager->m_mapShouldBuild[m_strSourcePath] = false;

      }

   }


   sp(::aura::application) ds_script::get_app() const
   {

      return m_pmanager->get_app();

   }


} // namespace dynamic_source



