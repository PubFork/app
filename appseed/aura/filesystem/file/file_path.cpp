#include "framework.h"


namespace path
{


   ::file::path app(string strPlatform)
   {

#ifdef WINDOWS

      return ::dir::stage("ca2 Store", strPlatform) / "app.exe";

#else

      return ::dir::stage("ca2 Store", strPlatform) / "app";

#endif

   }

   ::file::path app_app_admin(string strPlatform)
   {

      return ::dir::stage("ca2 Store", strPlatform) / "app_app_admin.exe";

   }


   ::file::path app_app_nest(string strPlatform)
   {

      return ::dir::stage("ca2 Store", strPlatform) / "app_app_nest.exe";

   }


   ::file::path app_app(string strPlatform)
   {

#ifdef WINDOWS

      return ::dir::stage("ca2 Store", strPlatform) / "app_app.exe";

#else

      return ::dir::stage("ca2 Store", strPlatform) / "app_app";

#endif

   }




   ::file::path vcredist(string strPlatform)
   {

      return ::dir::stage("ca2 Store", strPlatform) / "vcredist.exe";

   }


   ::file::path module(HMODULE hmodule)
   {
#ifdef WINDOWSEX

      hwstring wstr(MAX_PATH * 8);

      GetModuleFileNameW(hmodule,wstr,(DWORD) wstr.count());

      return solve_relative_compressions(string(wstr));


#elif defined(METROWIN)

      return "m_app.exe";

#else

      char * lpszModuleFilePath = br_find_exe_dir("app");

      if(lpszModuleFilePath == NULL)
         return "";

      string strModuleFileName(lpszModuleFilePath);

      free(lpszModuleFilePath);

      return strModuleFileName;

#endif

   }

   ::file::path install_log(string strPlatform)
   {

      return dir::install() / ("install-" + strPlatform + ".log");

   }


} // namespace path




