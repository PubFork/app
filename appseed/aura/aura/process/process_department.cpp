#include "framework.h"


void install_sigchld_handler();


namespace process
{


   department::department(::aura::application * papp):
      object(papp),
      ::aura::department(papp)
   {

   #ifndef WINDOWS

      install_sigchld_handler();

   #endif

   }


   department::~department()
   {

   }


   var department::get_output(const char * pszCmdLine,const ::duration & dur,int32_t iShow, bool * pbPotentialTimeout)
   {

      string strRead;

      process_processor proc(get_app(), pszCmdLine, dur, pbPotentialTimeout, &strRead);

      //Process proc(get_app(), pszCmdLine, "");

      //strRead = proc.read_stdout.to_string();

      //strRead += proc.read_stderr.to_string();

      return strRead;

   }



   exit_status department::retry(const char * pszCmdLine,const ::duration & dur,int32_t iShow, bool * pbPotentialTimeout)
   {

      process_processor proc(get_app(), pszCmdLine, dur, pbPotentialTimeout);

      return proc.m_exitstatus;

   }


   exit_status department::synch(const char * pszCmdLine,int32_t iShow, const ::duration & dur, bool * pbPotentialTimeout)
   {

      process_processor proc(get_app(), pszCmdLine, dur, pbPotentialTimeout);

      return proc.m_exitstatus;

   }


   bool department::launch(const char * pszCmdLine,int32_t iShow, const char * pszDir)
   {

      const char * pszEnd = NULL;

      string strBin = consume_param(pszCmdLine,&pszEnd);

#ifndef METROWIN

      int32_t iOk = call_async(strBin,pszEnd,pszDir,iShow, false);

      return iOk != 0;

#else

      _throw(todo(get_app()));

#endif

   }


   exit_status department::elevated_synch(const char * pszCmdLine,int32_t iShow,const ::duration & dur,bool * pbPotentialTimeout)
   {

      process_processor proc(get_app(),pszCmdLine,dur,pbPotentialTimeout, NULL, true);

      return proc.m_exitstatus;

   }


   department::process_thread::process_thread(::aura::application * papp,const string & strCmdLine,const ::duration & dur,bool * pbPotentialTimeout,string * pstrRead,bool bElevated):
      object(papp),
      thread(papp),
      simple_thread(papp),
      m_strCmdLine(strCmdLine),
      m_spprocess(allocer()),
      m_pstrRead(pstrRead)
   {

      if(dur.is_pos_infinity())
      {

         m_uiTimeout = 0;

      }
      else
      {

         m_uiTimeout =  dur.tick_duration();

      }


      m_pbPotentialTimeout    = pbPotentialTimeout;
      m_pbInitFailure         = NULL;
      m_bElevated             = bElevated;

   }


   void department::process_thread::run()
   {

      if(m_bElevated)
      {

         run_elevated();

      }
      else
      {

         run_normal();

      }

   }


   void department::process_thread::run_normal()
   {

      if(!m_spprocess->create_child_process(m_strCmdLine,true))
      {

         if(m_pbInitFailure != NULL)
         {

            *m_pbInitFailure = true;

         }

         if(m_pevReady != NULL)
         {

            m_pevReady->SetEvent();

         }

         m_error.set_if_not_set();

         return;

      }

      m_uiStartTime = ::get_tick_count();

      string strRead;

      while(!m_spprocess->has_exited())
      {

         strRead = m_spprocess->m_pipe.m_sppipeOut->read();

         if(m_pstrRead != NULL)
         {

            *m_pstrRead += strRead;

         }

         if(!retry())
         {

            break;

         }

         Sleep(100);

      }

      if(m_pexitstatus)
      {

         *m_pexitstatus = m_spprocess->m_exitstatus;

      }

      while(thread_get_run())
      {

         strRead = m_spprocess->m_pipe.m_sppipeOut->read();

         if(strRead.is_empty())
         {

            break;

         }
         else
         {

            if(m_pstrRead != NULL)
            {

               *m_pstrRead += strRead;

            }

         }

      }

      if(m_pevReady != NULL)
      {

         m_pevReady->SetEvent();

      }

   }


   void department::process_thread::run_elevated()
   {

      m_spprocess->synch_elevated(m_strCmdLine,SW_HIDE,millis(m_uiTimeout),m_pbPotentialTimeout);

      m_error.set(m_spprocess->m_exitstatus.m_iExitCode);

      if(m_pexitstatus != NULL)
      {

         *m_pexitstatus = m_spprocess->m_exitstatus;

      }

      if(m_pevReady != NULL)
      {

         m_pevReady->SetEvent();

      }

   }


   bool department::process_thread::retry()
   {

      if(m_uiTimeout > 0 && ::get_tick_count() - m_uiStartTime > m_uiTimeout)
      {

         if(m_pbPotentialTimeout != NULL)
         {

            *m_pbPotentialTimeout = true;

         }

         return false;

      }

      return true;

   }


   department::process_processor::process_processor(::aura::application * papp,const string & strCmdLine,const duration & dur,bool * pbPotentialTimeout,string * pstrRead,bool bElevated):
      object(papp),
      m_evReady(papp)
   {

      m_bInitFailure = false;

      m_bPotentialTimeout = false;

      m_pbPotentialTimeout = pbPotentialTimeout;

      m_bElevated = bElevated;

      m_pthread = new process_thread(papp,strCmdLine,dur,&m_bPotentialTimeout,pstrRead, bElevated);

      //m_pthread->m_bAutoDelete = true;

      m_pthread->m_pbInitFailure = &m_bInitFailure;

      m_pthread->m_pbPotentialTimeout = &m_bPotentialTimeout;

      m_pthread->m_pevReady = &m_evReady;

      if(m_pthread->m_pexitstatus != NULL)
      {

         *m_pthread->m_pexitstatus = m_exitstatus;

      }

      if(dur.is_pos_infinity())
      {

         m_pthread->run();

         ::aura::del(m_pthread);

      }
      else
      {

         m_evReady.ResetEvent();

         m_pthread->begin();

         m_evReady.wait();

      }

   }

   department::process_processor::~process_processor()
   {

      if(m_pbPotentialTimeout != NULL)
      {

         *m_pbPotentialTimeout = m_bPotentialTimeout;

      }

   }



} // namespace process




