#include "framework.h"


#if defined(ANDROID)
#include <sys/wait.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#elif defined(LINUX)
#include <sys/wait.h>
#include <unistd.h>
#include <spawn.h>
extern char **environ;
#elif defined(APPLEOS)
//#include <sys/wait.h>
//#include <unistd.h>
#include <spawn.h>
//#include <pthread.h>
//#include <stdlib.h>
extern char * const * environ;
#endif


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
         return false;

      stringa straParam;

      pointer_array < char * > argv;

      straParam.explode_command_line(pszCmdLine, &argv);

      //char * argv[] ={(char *)pszCmdLine,0};
#if defined(LINUX) || defined(APPLEOS)

      posix_spawnattr_t attr;

      posix_spawnattr_init(&attr);


#ifdef LINUX

      if(iCa2Priority != (int32_t) ::multithreading::priority_none)
      {

         int32_t iPolicy = SCHED_OTHER;

         sched_param schedparam;

         schedparam.sched_priority = 0;

         process_get_os_priority(&iPolicy,&schedparam,iCa2Priority);

         posix_spawnattr_setschedpolicy(&attr,iPolicy);

         posix_spawnattr_setschedparam(&attr,&schedparam);

      }

#endif

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

#ifdef MACOS

      strFallback = ::ca2_module_folder_dup();

#endif

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

#ifdef MACOS

         string strCurrent = getenv("DYLD_FALLBACK_LIBRARY_PATH");

         if(strCurrent.has_char())
         {

            strFallback += ":" + strCurrent;

         }

         strFallback = string("DYLD_FALLBACK_LIBRARY_PATH=") + strFallback;

         env.add((char *) (const char *) strFallback);

#endif

         env.add(NULL);

         e = (char * const *)env.get_data();

      }


      int status = 0;

      {

         cslock sl(get_pid_cs());

         status = posix_spawn(&m_iPid,argv[0],&actions,&attr,(char * const *)argv.get_data(),e);

         init_chldstatus(m_iPid);

      }

#ifdef APPLEOS

      if(iCa2Priority != (int32_t) ::multithreading::priority_none)
      {

         int32_t iOsPriority = process_get_os_priority(iCa2Priority);

         setpriority(PRIO_PROCESS,m_iPid,iOsPriority);

      }

#endif

      return status == 0;

#else

      char *   cmd_line;

      cmd_line = strdup(pszCmdLine);

      if(cmd_line == NULL)
      {

         return 0;

      }

      //strcpy_dup(cmd_line, pszCmdLine);

      char *   exec_path_name = cmd_line;

      cslock sl(get_pid_cs());

      if((m_iPid = ::fork()) == 0)
      {

         if(bPiped)
         {

            dup2(m_pipe.m_sppipeOut.cast < pipe >()->m_fd[1],STDOUT_FILENO);

            dup2(m_pipe.m_sppipeOut.cast < pipe >()->m_fd[1],STDERR_FILENO);

            dup2(m_pipe.m_sppipeIn.cast < pipe >()->m_fd[0],STDIN_FILENO);

         }



         char *      argv[1024 + 1];

         int32_t		argc = 0;

         prepare_argc_argv(argc, argv, cmd_line);

         int iExitCode = execv(exec_path_name, argv);

         free(cmd_line);

         exit(iExitCode);

      }
      else if(m_iPid == -1)
      {

         // in parent, but error

         m_iPid = 0;

         free(cmd_line);

         return 0;

      }

      // in parent, success

      init_chldstatus(m_iPid);

      return 1;

#endif

   }


   bool process::has_exited()
   {

      auto chldstatus = get_chldstatus(m_iPid);

      if(!chldstatus.m_bRet)
      {

         return false;

      }

      int iExitCode = chldstatus.m_iExitCode;

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


   void process::synch_elevated(const char * pszCmdLineParam,int iShow,const ::duration & durationTimeOut,bool * pbTimeOut)
   {

#if defined(MACOS)

//      string strFallback = ::ca2_module_folder_dup();

      string str(pszCmdLineParam);

      {

         stringa stra;

         pointer_array < char * > argv;

         stra.explode_command_line(str, &argv);

         str = argv[0];

      }

      string strFallback;

      ::file::path path = str;

      if(Application.file().exists(path.folder() / "libaura.dylib"))
      {

         ::file::path folderNew = path.folder();

         folderNew -= 3;

         if(Application.file().exists(folderNew / "libaura.dylib"))
         {

            strFallback = folderNew;

         }
         else
         {

            strFallback = path.folder();

         }

      }
      else
      {

         string strFolder = path.folder();

         if(::str::ends_eat_ci(strFolder, path.folder()/"Contents"/ "MacOS"))
         {

            strFallback = strFolder;

         }
         else
         {

            strFallback = ::ca2_module_folder_dup();

         }

      }

      string strFolder = strFallback;

//      ::dir::eat_end_level(strFolder, 2, NULL);

      string strCurrent = getenv("DYLD_FALLBACK_LIBRARY_PATH");

      if(strCurrent == strFallback || ::str::ends(strCurrent, ":" + strFallback) || str::begins(strCurrent, strFallback + ":") || strCurrent.contains(":"+strFallback +":"))
      {

         strFallback = strCurrent;

      }
      else if(strCurrent.has_char())
      {

         strFallback += ":" + strCurrent;

      }

      setenv("DYLD_FALLBACK_LIBRARY_PATH", strFallback, TRUE);

      // Create authorization reference
      OSStatus status;

      AuthorizationRef authorizationRef;

      // AuthorizationCreate and pass NULL as the initial
      // AuthorizationRights set so that the AuthorizationRef gets created
      // successfully, and then later call AuthorizationCopyRights to
      // determine or extend the allowable rights.
      // http://developer.apple.com/qa/qa2001/qa1172.html
      status = AuthorizationCreate(NULL, kAuthorizationEmptyEnvironment, kAuthorizationFlagDefaults, &authorizationRef);

      if (status != errAuthorizationSuccess)
      {

         TRACE("Error Creating Initial Authorization: %d", status);

         return -1;

      }

      // kAuthorizationRightExecute == "system.privilege.admin"
      AuthorizationItem right = {kAuthorizationRightExecute, 0, NULL, 0};
      AuthorizationRights rights = {1, &right};
      AuthorizationFlags flags = kAuthorizationFlagDefaults | kAuthorizationFlagInteractionAllowed |
                                 kAuthorizationFlagPreAuthorize | kAuthorizationFlagExtendRights;



      // Call AuthorizationCopyRights to determine or extend the allowable rights.
      status = AuthorizationCopyRights(authorizationRef, &rights, NULL, flags, NULL);
      if (status != errAuthorizationSuccess)
      {
         TRACE("Copy Rights Unsuccessful: %d", status);
         return -1;
      }

      TRACE("\n\n** %s **\n\n", "This command should work.");


      stringa straParam;

      pointer_array < char * > argv;

      straParam.add("/bin/bash");

      straParam.add("-c");

      string strC = "ignit_phase2 () { export DYLD_FALLBACK_LIBRARY_PATH=\""+strFallback+"\" ; cd "+strFolder+" ; "+string(pszCmdLineParam)+" ; } ; ignit_phase2 ;";
//            string strC = "export DYLD_FALLBACK_LIBRARY_PATH="+strFallback;

      straParam.add(strC);

      for(index i = 0; i < straParam.get_count(); i++)
      {

         argv.add((char *)(const char *)straParam[i]);

      }

      argv.add(NULL);



      char *tool = (char * )argv[0];
      char **args = (char **) &argv.get_data()[1];
      FILE *pipe = NULL;

//      int uid = getuid();

      ::output_debug_string("---\n");
      ::output_debug_string("---\n");
      ::output_debug_string("---\n");
      ::output_debug_string("---\n");
      ::output_debug_string("---\n");
      ::output_debug_string("---\n");
      ::output_debug_string("---\n");
      ::output_debug_string("---\n");
      ::output_debug_string("---\n");
      ::output_debug_string("---\n");
      ::output_debug_string("---\n");
      ::output_debug_string("---\n");
      ::output_debug_string("---\n");
      ::output_debug_string("---\n");
      ::output_debug_string("---\n");
      ::output_debug_string("---\n");
      ::output_debug_string("---\n");
      ::output_debug_string("---\n");
      ::output_debug_string("---\n");
      ::output_debug_string("---\n");

//      int i = setuid(0);

      //    if(i != 0)
      //  {
      //   TRACE("Failed to setuid: %d", i);
      // return -1;
      //}


      /*
      stringa straParam;

      ref_array < char > argv;


      straParam.explode_command_line(pszCmdLineParam, &argv);

      posix_spawnattr_t attr;

      posix_spawnattr_init(&attr);


      posix_spawn_file_actions_t actions;

      posix_spawn_file_actions_init(&actions);


      status = posix_spawn(&m_iPid,argv[0],&actions,&attr,(char * const *)argv.get_data(),environ);

      //int status = posix_spawn(&m_iPid,argv[0],NULL,NULL,(char * const *)argv.get_data(),environ);

      debug_print("synch_elevated : posix_spawn return status %d", status);


      DWORD dwStart = get_tick_count();

      while(!has_exited() && get_tick_count() - dwStart < durationTimeOut.get_total_milliseconds())
      {
         Sleep(100);
      }
      DWORD dwExitCode = 0;
      if(!has_exited(&dwExitCode))
      {
         if(pbTimeOut != NULL)
         {
            *pbTimeOut = true;
         }
      }
      */

//      setuid(uid);

      status = AuthorizationExecuteWithPrivileges(authorizationRef, tool, kAuthorizationFlagDefaults, args, &pipe);
      if (status != errAuthorizationSuccess)
      {
         TRACE("AuthorizationExecuteWithPrivileges Error: %d", status);
         return -1;
      }

      /*

      straParam.remove_all();
      argv.remove_all();
      straParam.explode_command_line(pszCmdLineParam, &argv);

      tool = (char * )argv[0];
      args = (char **) &argv.get_data()[1];
      pipe = NULL;


      status = AuthorizationExecuteWithPrivileges(authorizationRef, tool, kAuthorizationFlagDefaults, args, &pipe);
      if (status != errAuthorizationSuccess)
      {
         TRACE("AuthorizationExecuteWithPrivileges Error: %d", status);
         return -1;
      }

       */

      if(pipe != NULL)
      {

//        int pptp_pid = 0;

         //       fscanf(pipe, "%d", &pptp_pid);
         bool bNewLine = true;
         index i = 0;
         while(i < 1000)
         {
            char szBuffer[1000];
            memset(szBuffer, 0, sizeof(szBuffer));
            fgets(szBuffer, sizeof(szBuffer), pipe);
            if(szBuffer[sizeof(szBuffer)-2] == '\n' || szBuffer[sizeof(szBuffer)-2] == '\0')
            {
               if(bNewLine)
               {
                  string strLine = szBuffer;
                  if(::str::begins_eat_ci(strLine, "application_process_id="))
                  {
                     m_iPid = atoi(strLine);
                     break;
                  }
               }
               else
               {
                  bNewLine = true;
               }
            }
            else
            {
               bNewLine = false;
            }
            i++;
         }

//         pid_t pptp_pid = 0;

         //       fread(&pptp_pid,sizeof(pptp_pid),1,pipe); // get pid

         //     m_iPid = pptp_pid;

         DWORD dwStart = get_tick_count();

         DWORD dwTimeOut = (DWORD) durationTimeOut.get_total_milliseconds();

         char sz[1025];

         int iRead;

         while(!has_exited() && get_tick_count() - dwStart < dwTimeOut)
         {
//            memset(sz, 0, sizeof(sz));
//               iRead = fread(sz,1,1024, pipe);
//               if(iRead >0)
//               {
//                  ::output_debug_string(sz);
//               }
//               else if(ferror(pipe))
//               {
//                  TRACE("Error reading from file");
//                  break;
//               }
//               else
//               {
//               }

            Sleep(100);
         }
         if(!has_exited(&dwExitCode))
         {
            if(pbTimeOut != NULL)
            {
               *pbTimeOut = true;
            }
         }

         /*         char c;

                  int iRead;

                  string strRead;

                  while(true)
                  {
                     iRead = fread(&c,1,1, pipe);
                     if(iRead == 1)
                     {
                        strRead += c;
                     }
                     else if(ferror(pipe))
                     {
                        TRACE("Error reading from file");
                        break;
                     }
                     else
                     {
                     }
                  }

                  fclose(pipe);

                  TRACE0(strRead);*/


      }

      // The only way to guarantee that a credential acquired when you
      // request a right is not shared with other authorization instances is
      // to destroy the credential.  To do so, call the AuthorizationFree
      // function with the flag kAuthorizationFlagDestroyRights.
      // http://developer.apple.com/documentation/Security/Conceptual/authorization_concepts/02authconcepts/chapter_2_section_7.html
      status = AuthorizationFree(authorizationRef, kAuthorizationFlagDestroyRights);

      if (status != errAuthorizationSuccess)
      {
         TRACE("AuthorizationFree Error: %d", status);
      }

      return dwExitCode;
#else

      stringa straParam;

      pointer_array < char * > argv;

#ifdef MACOS

      straParam.add("/usr/bin/osascript");
      straParam.add("-e");
      straParam.add("'do shell script \"" + string(pszCmdLineParam) + "\" with administrator privileges'");

      argv.add((char *) (const char *) straParam[0]);
      argv.add((char *) (const char *) straParam[1]);
      argv.add((char *) (const char *) straParam[2]);
      argv.add(NULL);

#else

      if (access("/usr/bin/gksu", X_OK) != 0)
      {

         m_exitstatus.m_iExitCode = -1;

         ::simple_message_box(NULL,"gksu is not installed, please install gksu.","Please, install gksu.",MB_ICONINFORMATION);

         return ;

      }

      string pszCmdLine = "/usr/bin/gksu " + string(pszCmdLineParam);

      straParam.explode_command_line(pszCmdLine, &argv);

#endif


      //char * argv[] ={(char *)pszCmdLine,0};
#if defined(LINUX) || defined(APPLEOS)

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

#else

      char *   cmd_line;

      cmd_line = (char *) memory_alloc(strlen(pszCmdLine ) + 1 );

      if(cmd_line == NULL)
      {

         return 0;

      }

      strcpy_dup(cmd_line, pszCmdLine);

      char *   exec_path_name = cmd_line;


      cslock sl(get_pid_cs());

      if((m_iPid = ::fork()) == 0)
      {

         //if(bPiped)
         //{
         //   dup2(m_pipe.m_sppipeOut.cast < pipe >()->m_fd[1],STDOUT_FILENO);
         //   dup2(m_pipe.m_sppipeOut.cast < pipe >()->m_fd[1],STDERR_FILENO);
         //   dup2(m_pipe.m_sppipeIn.cast < pipe >()->m_fd[0],STDIN_FILENO);
         //}


         // child
         char     *pArg, *pPtr;
         char     *argv[1024 + 1];
         int32_t      argc;
         if( ( pArg = strrchr_dup( exec_path_name, '/' ) ) != NULL )
            pArg++;
         else
            pArg = exec_path_name;
         argv[0] = pArg;
         argc = 1;

         if( cmd_line != NULL && *cmd_line != '\0' )
         {
            pArg = strtok_r_dup(cmd_line, " ", &pPtr);
            while( pArg != NULL )
            {
               argv[argc] = pArg;
               argc++;
               if( argc >= 1024 )
                  break;
               pArg = strtok_r_dup(NULL, " ", &pPtr);
            }
         }
         argv[argc] = NULL;

         execv(exec_path_name, argv);
         free(cmd_line);
         exit( -1 );
      }
      else if(m_iPid == -1)
      {
         // in parent, but error
         m_iPid = 0;
         free(cmd_line);
         return 0;
      }

      init_chldstatus(m_iPid);

      // in parent, success
      return 1;
#endif

#endif

   }

} // namespace ansios




