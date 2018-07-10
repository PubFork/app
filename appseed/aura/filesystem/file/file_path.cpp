#include "framework.h"


namespace path
{


   ::file::path app(string strPlatform, string strConfiguration)
   {

#ifdef WINDOWS

      return ::dir::stage("ca2 Store", strPlatform, strConfiguration) / "app.exe";

#else

      return ::dir::stage("ca2 Store", strPlatform, strConfiguration) / "app";

#endif

   }

   ::file::path app_app_admin(string strPlatform, string strConfiguration)
   {

      return ::dir::stage("ca2 Store", strPlatform, strConfiguration) / "app_app_admin.exe";

   }


   ::file::path app_app_nest(string strPlatform, string strConfiguration)
   {

      return ::dir::stage("ca2 Store", strPlatform, strConfiguration) / "app_app_nest.exe";

   }


   ::file::path app_app(string strPlatform, string strConfiguration)
   {

#ifdef WINDOWS

      return ::dir::stage("ca2 Store", strPlatform, strConfiguration) / "app_app.exe";

#else

      return ::dir::stage("ca2 Store", strPlatform, strConfiguration) / "app_app";

#endif

   }




   ::file::path vcredist(string strPlatform, string strConfiguration)
   {

      return ::dir::stage("ca2 Store", strPlatform, strConfiguration) / "vcredist.exe";

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

   ::file::path install_log(string strPlatform, string strConfiguration)
   {

      return dir::install() / ("install-" + strPlatform + ".log");

   }

   string from(string str)
   {

      string strFsSafe;

      for (index i = 0; i < str.length(); i++)
      {

         if (isalnum_dup(str[i]))
         {

            strFsSafe += str[i];

         }
         else
         {

            strFsSafe += "-" + ::hex::lower_from(str[i]);

         }

      }

      return strFsSafe;

   }


} // namespace path




