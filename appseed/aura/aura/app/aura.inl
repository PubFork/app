#include "aura/aura/aura/aura.h"


#ifdef LINUX


BEGIN_EXTERN_C

void bloat_pad_run(const char * pszAppName, const char * pszProgName);

END_EXTERN_C

#include <sys/types.h>

#include <sys/stat.h>

#include <fcntl.h>

const char * g_psz_br_init_symbol_app = "";

#ifndef LINUX_COMMAND_LINE

#define GET_COMMAND_LINE(RET, ARGC, ARGV) linux_get_command_line(RET, ARGC, ARGV)

#endif

class string;

void linux_get_command_line(string & str, int argc, char ** argv);

#endif // LINUX


#ifdef METROWIN

//#include "core/core/core.h"
//
//#undef CoreApplication
//

#undef new

[MTAThread]
int main(Array < String ^ > ^ refstra)
{

   class aura_aura aura;

   ap(aura_main_data) pmaindata = new aura_main_data(refstra);

#ifdef MAIN_STRING

   pmaindata->m_strCommandLine = MAIN_STRING;

#endif

   return (int)aura_aura(pmaindata);

}

#else


#undef new

int main(int argc, char * argv[])
{

//#ifdef LINUX
//
//   signal(SIGCHLD, SIG_IGN);
//
//   {
//
//      int fd = open("/dev/null",O_RDWR, 0);
//
//      if (fd != -1)
//      {
//
//         dup2 (fd, STDIN_FILENO);
//         dup2 (fd, STDOUT_FILENO);
//         dup2 (fd, STDERR_FILENO);
//
//         if (fd > 2)
//         {
//
//            close (fd);
//
//         }
//
//      }
//
//   }
//
//   /*resetting File Creation Mask */
//   umask(0);
//
//#endif
   //bloat_pad_run("app-core/weather", "cc.ca2.app-core.weather");

   class aura_aura aura;



   ap(aura_main_data) pmaindata = new aura_main_data(argc, argv);

#ifdef LINUX

   br_init_set_symbol(g_psz_br_init_symbol_app);

#endif


#ifdef MAIN_STRING

   pmaindata->m_strCommandLine = MAIN_STRING;

#endif


#ifdef GET_COMMAND_LINE

   GET_COMMAND_LINE(pmaindata->m_strCommandLine, argc, argv);

#endif // GET_COMMAND_LINE

#if defined(LINUX)

   int iExitCode = aura_aura(pmaindata);

   //exit(iExitCode);

   return iExitCode;

#else

   return (int)aura_aura(pmaindata);

#endif

}


#ifdef WINDOWS

BEGIN_EXTERN_C

int32_t WINAPI _tWinMain(HINSTANCE hinstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int32_t nCmdShow)
{

   class aura_aura aura;

   ap(aura_main_data) pmaindata = new aura_main_data(hinstance, hPrevInstance, lpCmdLine, nCmdShow);

   return aura_aura(pmaindata);

}

END_EXTERN_C

#endif


#endif



#ifdef WINDOWS

#include "include/applink.cpp"

#endif


#define APP_PRELUDE_LEVEL(prefix) \
extern "C" \
::aura::application * prefix##_get_new_app(::aura::application * papp); \
aura_prelude auraprelude(&prefix##_get_new_app);


#define LIBRARY_PRELUDE(prefix) \
extern "C" \
::aura::library * prefix##_get_new_library(::aura::application * papp); \
aura_prelude auraprelude(&prefix##_get_new_library);


#if defined(LINUX) && !defined(LINUX_COMMAND_LINE)

void linux_get_command_line(string & str, int argc, char ** argv)
{

   string strAppId(MAINAPPID);

   str = string(argv[0]) + " : " + "app=" + strAppId;

}

#endif

