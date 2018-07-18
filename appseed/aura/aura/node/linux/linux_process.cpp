#include "framework.h"


#include <sys/wait.h>
#include <unistd.h>
#include <spawn.h>


extern char **environ;


string ca2_module_folder_dup();


struct chldstatus
{

   bool m_bRet;
   int  m_iExitCode;

};


typedef int_ptr_map < chldstatus > chldstatus_map;


critical_section * g_pcsPid2 = NULL;


chldstatus_map * g_ppid = NULL;


critical_section * get_pid_cs()
{

   cslock cs(g_pcsGlobal);

   if(g_pcsPid2 == NULL)
   {

      g_pcsPid2 = new critical_section();

      g_ppid = new chldstatus_map();


   }

   return g_pcsPid2;

}


chldstatus get_chldstatus(int iPid)
{

   cslock sl(get_pid_cs());

   return g_ppid->operator[](iPid);

}

// must be called under get_pid_cs lock
void init_chldstatus(int iPid)
{

   auto & s = g_ppid->operator[](iPid);

   s.m_bRet = false;

   s.m_iExitCode = 0;

}


void ansios_sigchld_handler(int sig)
{

   int saved_errno = errno;

   int iExitCode;

   int iPid;

   while((iPid = waitpid(-1, &iExitCode,
                          WUNTRACED
#ifdef WNOHANG
                          | WNOHANG
#endif
#ifdef WCONTINUED
                          | WCONTINUED
#endif
                         )) > 0)
   {

      {

         cslock sl(get_pid_cs());

         auto ppair = g_ppid->PLookup(iPid);

         if(ppair != NULL)
         {

            ppair->m_element2.m_bRet = true;

            ppair->m_element2.m_iExitCode = iExitCode;

         }

      }

   }

   errno = saved_errno;

}


void install_sigchld_handler()
{

   struct sigaction sa;

   ZERO(sa);

   sa.sa_handler = &ansios_sigchld_handler;

   sigemptyset(&sa.sa_mask);

   sa.sa_flags = SA_RESTART | SA_NOCLDSTOP;

   sigaction(SIGCHLD, &sa, NULL);

}


CLASS_DECL_AURA void process_get_os_priority(int32_t * piOsPolicy, sched_param * pparam, int32_t iCa2Priority);


namespace ansios
{


   process::process(::aura::application * papp):
      object(papp),
      ::process::process(papp)
   {

   }


   process::~process()
   {

   }


   bool process::create_child_process(const char * pszCmdLine,bool bPiped,const char * pszDir,int32_t iCa2Priority)
   {

      if(!::process::process::create_child_process(pszCmdLine,bPiped,pszDir,iCa2Priority))
      {

         return false;

      }

      stringa straParam;

      pointer_array < char * > argv;

      straParam.explode_command_line(pszCmdLine, &argv);

      posix_spawnattr_t attr;

      posix_spawnattr_init(&attr);

      if(iCa2Priority != (int32_t) ::multithreading::priority_none)
      {

         int32_t iPolicy = SCHED_OTHER;

         sched_param schedparam;

         schedparam.sched_priority = 0;

         process_get_os_priority(&iPolicy,&schedparam,iCa2Priority);

         posix_spawnattr_setschedpolicy(&attr,iPolicy);

         posix_spawnattr_setschedparam(&attr,&schedparam);

      }

      posix_spawn_file_actions_t actions;

      posix_spawn_file_actions_init(&actions);

      if(bPiped)
      {

         pipe * ppipeOut = m_pipe.m_sppipeOut.cast < pipe >();

         posix_spawn_file_actions_adddup2(&actions, ppipeOut->m_fd[1],STDOUT_FILENO);

         posix_spawn_file_actions_adddup2(&actions, ppipeOut->m_fd[1],STDERR_FILENO);

         pipe * ppipeIn = m_pipe.m_sppipeIn.cast < pipe >();

         posix_spawn_file_actions_adddup2(&actions, ppipeIn->m_fd[0],STDIN_FILENO);

      }

      pointer_array < char * > env;

      char * const * e = environ;

      string strFallback;

      if(::str::begins_ci(strFallback, "/Users/"))
      {

         index i = 0;

         int iPrevious = -1;

         const char * psz;

         while((psz = environ[i]) != NULL)
         {
            if(i <= iPrevious)
               break;

            env.add((char *) psz);

            iPrevious = (int) i;

            i++;

         }

         env.add(NULL);

         e = (char * const *)env.get_data();

      }

      int status = 0;

      {

         cslock sl(get_pid_cs());

         status = posix_spawn(&m_iPid,argv[0],&actions,&attr,(char * const *)argv.get_data(),e);

         init_chldstatus(m_iPid);

      }

      return status == 0;

   }


   bool process::has_exited()
   {

      int iExitCode;

#if 0

      {

         int iPid;

         iPid = waitpid(m_iPid, &iExitCode,
                             WUNTRACED
   #ifdef WNOHANG
                             | WNOHANG
   #endif
   #ifdef WCONTINUED
                             | WCONTINUED
   #endif
                            );

         if(iPid == 0)
         {

            return false;

         }
         else if(iPid == -1)
         {

            return true;

         }

      }

#else

      {

         auto chldstatus = get_chldstatus(m_iPid);

         if(!chldstatus.m_bRet)
         {

            return false;

         }

         iExitCode = chldstatus.m_iExitCode;

      }

#endif

      if(WIFEXITED(iExitCode))
      {

         m_exitstatus.m_iExitCode = WEXITSTATUS(iExitCode);

         return true;

      }
      else if(WIFSIGNALED(iExitCode))
      {

         m_exitstatus.m_iExitSignal = WTERMSIG(iExitCode);

         m_exitstatus.m_iExitCode = 0x80000000;

         return true;

      }
      else if(WIFSTOPPED(iExitCode))
      {

         m_exitstatus.m_iExitStop = WSTOPSIG(iExitCode);

         m_exitstatus.m_iExitCode = 0x80000000;

         return true;

      }

#ifdef WIFCONTINUED

      else if(WIFCONTINUED(iExitCode))
      {

         return false;

      }

#endif

      return true;

   }


   bool process::synch_elevated(const char * pszCmdLineParam,int iShow,const ::duration & durationTimeOut,bool * pbTimeOut)
   {

      stringa straParam;

      pointer_array < char * > argv;

      if (access("/usr/bin/gksu", X_OK) != 0)
      {

         m_exitstatus.m_iExitCode = -1;

         ::simple_message_box(NULL,"gksu is not installed, please install gksu.","Please, install gksu.",MB_ICONINFORMATION);

         return ;

      }

      string pszCmdLine = "/usr/bin/gksu " + string(pszCmdLineParam);

      straParam.explode_command_line(pszCmdLine, &argv);

      posix_spawnattr_t attr;

      posix_spawnattr_init(&attr);

      posix_spawn_file_actions_t actions;

      posix_spawn_file_actions_init(&actions);

      int status= 0;

      {

         cslock sl(get_pid_cs());

         status = posix_spawn(&m_iPid,argv[0],&actions,&attr,(char * const *)argv.get_data(),environ);

         init_chldstatus(m_iPid);

      }

      //int status = posix_spawn(&m_iPid,argv[0],NULL,NULL,(char * const *)argv.get_data(),environ);

      debug_print("synch_elevated : posix_spawn return status %d", status);

      DWORD dwStart = get_tick_count();

      while(!has_exited() && get_tick_count() - dwStart < durationTimeOut.get_total_milliseconds())
      {

         Sleep(100);

      }

      DWORD dwExitCode = 0;

      if(!has_exited())
      {

         if(pbTimeOut != NULL)
         {

            *pbTimeOut = true;

         }

      }

   }


} // namespace ansios




