#include "framework.h"
//#include <Shlobj.h>
#include "aura/aura/os/os.h"
#if defined(APPLEOS)
#include <sys/stat.h>
#include <dirent.h>
#elif defined(LINUX)
#include <dlfcn.h>
#include <link.h>
#include <sys/stat.h>
#include <dirent.h>
#elif defined(ANDROID)
#include <sys/stat.h>
#include <dirent.h>
#elif defined(METROWIN)
#include "aura/aura/os/metrowin/metrowin_file_winrt.h"
#elif defined(WINDOWSEX)
#include "aura/aura/os/windows_common/windows_common_cotaskptr.h"
#endif



void TranslateLastError()
{

   if(errno == EEXIST)
   {

      set_last_error(ERROR_ALREADY_EXISTS);

   }
   else
   {

      set_last_error(0);

   }


}

#ifdef WINDOWS

bool __win_file_find_is_dots(WIN32_FIND_DATA & data);

#endif


#if defined(METROWIN)

#pragma push_macro("System")

#undef System

using namespace ::Windows::System;

#pragma pop_macro("System")

#endif


::file::path dir::ca2_module()
{

#if defined(ANDROID)

   if (!br_init_lib(NULL))
      return "";

   char * lpszModule = br_find_exe(NULL);

   if (lpszModule == NULL)
      return "";

   ::file::path path = lpszModule;

   free(lpszModule);

   return path;

#elif defined(METROWIN)

   hwstring lpszModuleFolder(MAX_PATH * 8);

   hwstring lpszModuleFilePath(MAX_PATH * 8);


   if (!GetModuleFileNameW(NULL, lpszModuleFilePath, (DWORD)lpszModuleFilePath.count()))
      return "";

   LPWSTR lpszModuleFileName;

   if (!GetFullPathNameW(lpszModuleFilePath, (DWORD)lpszModuleFilePath.count(), lpszModuleFolder, &lpszModuleFileName))
      return "";

   lpszModuleFolder[lpszModuleFileName - lpszModuleFolder] = '\0';

   if (wcslen(lpszModuleFolder) > 0)
   {

      if (lpszModuleFolder[wcslen(lpszModuleFolder) - 1] == '\\' || lpszModuleFolder[wcslen(lpszModuleFolder) - 1] == '/')
      {

         lpszModuleFolder[wcslen(lpszModuleFolder) - 1] = '\0';

      }

   }
   return string(lpszModuleFolder);

#elif defined(WINDOWS)


   hwstring lpszModuleFolder(MAX_PATH * 8);

   hwstring lpszModuleFilePath(MAX_PATH * 8);

   HMODULE hmodule = ::GetModuleHandleA("core.dll");

   if(hmodule == NULL)
      hmodule = ::GetModuleHandleA("spalib.dll");

   if(hmodule == NULL)
   {

      cotaskp(PWSTR) pwstr;

      HRESULT hr = SHGetKnownFolderPath(
                   FOLDERID_ProgramFilesX86,
                   KF_FLAG_DEFAULT,
                   NULL,
                   &pwstr);

      wcscpy(lpszModuleFilePath, pwstr);

      //if(lpszModuleFilePath[wcslen(lpszModuleFilePath) - 1] == '\\'
      //      || lpszModuleFilePath[wcslen(lpszModuleFilePath) - 1] == '/')
      //{
      //   lpszModuleFilePath[wcslen(lpszModuleFilePath) - 1] = '\0';
      //}
      wcscat(lpszModuleFilePath, L"\\ca2\\");
#ifdef X86
      wcscat(lpszModuleFilePath,L"stage\\x86\\");
#else
      wcscat_dup(lpszModuleFilePath, L"stage\\x64\\");
#endif

      wcscpy(lpszModuleFolder, lpszModuleFilePath);

      return string(lpszModuleFolder);

   }

   if(!GetModuleFileNameW(hmodule,lpszModuleFilePath, (DWORD) lpszModuleFilePath.count()))
      return "";

   LPWSTR lpszModuleFileName;

   if (!GetFullPathNameW(lpszModuleFilePath, (DWORD) lpszModuleFilePath.count(), lpszModuleFolder, &lpszModuleFileName))
      return "";

   lpszModuleFolder[lpszModuleFileName - lpszModuleFolder] = '\0';

   if(wcslen(lpszModuleFolder) > 0)
   {

      if(lpszModuleFolder[wcslen(lpszModuleFolder) - 1] == '\\' || lpszModuleFolder[wcslen(lpszModuleFolder) - 1] == '/')
      {

         lpszModuleFolder[wcslen(lpszModuleFolder) - 1] = '\0';

      }

   }
   return string(lpszModuleFolder);


#elif defined(APPLEOS)

   string str;

   {

      str = ::dir::pathfind(getenv("DYLD_LIBRARY_PATH"), "libaura.dylib", "rfs"); // readable - normal file - non zero sized

      if(str.has_char())
      {
         str = ::file::path(str).folder();
         goto found;

      }


      str = ::dir::pathfind(getenv("DYLD_FALLBACK_LIBRARY_PATH"), "libaura.dylib", "rfs"); // readable - normal file - non zero sized

      if(str.has_char())
      {
         str = ::file::path(str).folder();
         goto found;

      }

      str = get_exe_path();


      if(str.has_char())
      {
         str = ::file::path(str).folder();
         goto found;
      }


   }
found:
   ;

   return str;

#else

   hstring lpszModuleFolder(MAX_PATH * 8);

   void * handle = dlopen("libaura.so", RTLD_NOW);

   if(handle == NULL)
   {

      strcpy(lpszModuleFolder, "/ca2/");

   }
   else
   {

      link_map * plm;

      dlinfo(handle, RTLD_DI_LINKMAP, &plm);

      strcpy(lpszModuleFolder, plm->l_name);


      dlclose(handle);

      strcpy(lpszModuleFolder, ::dir::name(lpszModuleFolder));

   }

   return string(lpszModuleFolder);


#endif


}



















::file::path dir::base_module()
{
#if defined(METROWIN)

   return "";
   /*   unichar lpszModuleFolder[MAX_PATH * 8];

      char lpszModuleFilePath[MAX_PATH * 8];

      HMODULE hmodule = ::LoadPackagedLibrary(L"ca.dll", 0);

      if (hmodule == NULL)
         hmodule = ::LoadPackagedLibrary(L"spalib.dll", 0);

      if (hmodule == NULL)
      {

         string buf;

         _throw(metrowin_todo());
         //HRESULT hr = SHGetKnownFolderPath(FOLDERID_ProgramFiles, KF_FLAG_NO_ALIAS, NULL, wtostring(buf, 4096));
         //if(FAILED(hr))
         // _throw(simple_exception(get_app(), "dir::ca2_module_dup : SHGetKnownFolderPath failed"));

         strcpy(lpszModuleFilePath, buf.c_str());

         if (lpszModuleFilePath[strlen_dup(lpszModuleFilePath) - 1] == '\\'
            || lpszModuleFilePath[strlen_dup(lpszModuleFilePath) - 1] == '/')
         {
            lpszModuleFilePath[strlen_dup(lpszModuleFilePath) - 1] = '\0';
         }
         strcat_dup(lpszModuleFilePath, "\\ca2\\");
   #ifdef X86
         strcat_dup(lpszModuleFilePath, "stage\\x86\\");
   #else
         strcat_dup(lpszModuleFilePath, "stage\\x64\\");
   #endif

         strcpy_dup(lpszModuleFolder, lpszModuleFilePath);

         return lpszModuleFolder;

      }

      _throw(metrowin_todo());
      //GetModuleFileName(hmodule, lpszModuleFilePath, sizeof(lpszModuleFilePath));

      // xxx   LPTSTR lpszModuleFileName;

      _throw(metrowin_todo());
      //GetFullPathName(lpszModuleFilePath, sizeof(lpszModuleFilePath), lpszModuleFolder, &lpszModuleFileName);

      _throw(metrowin_todo());
      //lpszModuleFolder[lpszModuleFileName - lpszModuleFolder] = '\0';

      _throw(metrowin_todo());
      /*
      if(strlen_dup(lpszModuleFolder) > 0)
      {

      if(lpszModuleFolder[strlen_dup(lpszModuleFolder) - 1] == '\\' || lpszModuleFolder[strlen_dup(lpszModuleFolder) - 1] == '/')
      {

      lpszModuleFolder[strlen_dup(lpszModuleFolder) - 1] = '\0';

      }

      }
      */

//   return true;

#elif defined(WINDOWS)

   hwstring lpszModuleFolder(MAX_PATH * 8);

   hwstring lpszModuleFilePath(MAX_PATH * 8);

   HMODULE hmodule = ::GetModuleHandleA("aura.dll");

   if (hmodule == NULL)
      hmodule = ::GetModuleHandleA("spalib.dll");

   if (hmodule == NULL)
   {

      wcscpy(lpszModuleFilePath,_wgetenv(L"PROGRAMFILES(X86)"));

      if(wcslen(lpszModuleFilePath) == 0)
      {

         SHGetSpecialFolderPathW(
         NULL,
         lpszModuleFilePath,
         CSIDL_PROGRAM_FILES,
         FALSE);

      }

      if(lpszModuleFilePath[wcslen(lpszModuleFilePath) - 1] == '\\'
            || lpszModuleFilePath[wcslen(lpszModuleFilePath) - 1] == '/')
      {
         lpszModuleFilePath[wcslen(lpszModuleFilePath) - 1] = '\0';
      }
      wcscat(lpszModuleFilePath, L"\\ca2\\");
#ifdef X86
      wcscat(lpszModuleFilePath,L"stage\\x86\\");
#else
      wcscat_dup(lpszModuleFilePath,L"stage\\x64\\");
#endif

      wcscpy(lpszModuleFolder, lpszModuleFilePath);

      return string(lpszModuleFolder);

   }

   if(!GetModuleFileNameW(hmodule,lpszModuleFilePath, (DWORD) lpszModuleFilePath.count()))
      return "";

   LPWSTR lpszModuleFileName;

   if (!GetFullPathNameW(lpszModuleFilePath, (DWORD) lpszModuleFilePath.count(), lpszModuleFolder, &lpszModuleFileName))
      return "";

   lpszModuleFolder[lpszModuleFileName - lpszModuleFolder] = '\0';

   if (wcslen_dup(lpszModuleFolder) > 0)
   {

      if(lpszModuleFolder[wcslen_dup(lpszModuleFolder) - 1] == '\\' || lpszModuleFolder[wcslen_dup(lpszModuleFolder) - 1] == '/')
      {

         lpszModuleFolder[wcslen_dup(lpszModuleFolder) - 1] = '\0';

      }

   }


   return string(lpszModuleFolder);


#else

   hwstring lpszModuleFolder(MAX_PATH * 8);

   _throw(todo(get_app()));

//   wcscpy_dup(lpszModuleFolder, unitext("/core/"));

   return (unichar *) lpszModuleFolder;

#endif


}


























bool eat_end_level_dup(string & str, int32_t iLevelCount, const char * lpSeparator)
{

   strsize iLast = str.length() - 1;

   if(iLast < 0)
      return iLevelCount <= 0;

   while(str[iLast] == '/' || str[iLast] == '\\')
      iLast--;

   for(int32_t i = 0; i < iLevelCount; i++)
   {

      strsize iFind1 = str.reverse_find('/', iLast);

      strsize iFind2 = str.reverse_find('\\', iLast);

      strsize iFind = MAX(iFind1, iFind2);

      if(iFind >= iLast)
         return false;

      if(iFind < 0)
         return false;

      iLast = iFind;

      while(str[iLast] == '/' || str[iLast] == '\\')
         iLast--;

   }

   str = str.substr(0, iLast + 1);

   return true;

}

string * g_pstrCalcModuleFolderDup = NULL;

string ca2_module_folder_dup()
{

   return *g_pstrCalcModuleFolderDup;


}

string calc_ca2_module_folder_dup()
{

   string str;

#ifdef WINDOWSEX

   hwstring lpszModuleFilePath(MAX_PATH * 8);
   GetModuleFileNameW(::GetModuleHandleA("ca.dll"), lpszModuleFilePath, MAX_PATH + 1);
   hwstring lpszModuleFolder(MAX_PATH * 8);
   unichar * lpszModuleFileName = NULL;
   GetFullPathNameW(lpszModuleFilePath, MAX_PATH + 1, lpszModuleFolder, &lpszModuleFileName);
   str = wstring(lpszModuleFolder, lpszModuleFileName - lpszModuleFolder);

#elif defined(LINUX)

   void * handle = dlopen("libcore.so", RTLD_NOW);

   if(handle == NULL)
      return "";

   link_map * plm;

   dlinfo(handle, RTLD_DI_LINKMAP, &plm);

   string strCa2ModuleFolder = ::dir::name(plm->l_name);

   dlclose(handle);

   str = strCa2ModuleFolder;

#elif defined(METROWIN)

   str = "";

#elif defined(APPLEOS)

   {

      char * pszCurDir = getcwd(NULL, 0);

      string strCurDir = pszCurDir;

      free(pszCurDir);

      /*      if(file_exists_dup(::dir::path(strCurDir, "libbase.dylib")))
            {
               return strCurDir;
            }
      */

      str = ::dir::name(::dir::pathfind(getenv("DYLD_LIBRARY_PATH"), "libbase.dylib", "rfs")); // readable - normal file - non zero sized

      if(str.has_char())
      {

         goto found;

      }

      str = ::dir::name(::dir::pathfind(getenv("DYLD_FALLBACK_LIBRARY_PATH"), "libbase.dylib", "rfs")); // readable - normal file - non zero sized

found:
      ;
   }

#endif

   return str;


}


string ca2_module_dup()
{

   static string * s_pstrCalc = NULL;

   if(s_pstrCalc != NULL)
   {

      return *s_pstrCalc;

   }

   string str;

#ifdef WINDOWSEX

   hwstring lpszModuleFilePath(MAX_PATH * 8);

   GetModuleFileNameW(::GetModuleHandleA("aura.dll"), lpszModuleFilePath, MAX_PATH + 1);

   str = (const unichar *) lpszModuleFilePath;

#elif defined(LINUX)

   void * handle = dlopen("libaura.so", RTLD_NOW);

   if(handle == NULL)
      return "";

   link_map * plm;

   dlinfo(handle, RTLD_DI_LINKMAP, &plm);

   string strCa2ModuleFolder = plm->l_name;

   dlclose(handle);

   str = strCa2ModuleFolder;

#elif defined(METROWIN)

   str = "";

#elif defined(APPLEOS)

   {

      str = get_exe_path();

      if(str.has_char())
      {

         goto found;

      }

      str = ::dir::pathfind(::file::path(str).folder(), "libaura.dylib", "rfs"); // readable - normal file - non zero sized

      if(str.has_char())
      {

         goto found;

      }

      str = ::dir::pathfind(getenv("DYLD_LIBRARY_PATH"), "libaura.dylib", "rfs"); // readable - normal file - non zero sized

      if(str.has_char())
      {

         goto found;

      }

      str = get_exe_path();

      if(str.has_char())
      {

         goto found;

      }

      str = ::dir::pathfind(getenv("DYLD_FALLBACK_LIBRARY_PATH"), "libaura.dylib", "rfs"); // readable - normal file - non zero sized

      if(str.has_char())
      {

         goto found;

      }

   }

found:
   ;

#endif

   s_pstrCalc = new string(str);

   return *s_pstrCalc;


}


CLASS_DECL_AURA::file::path dir::inplace_install(string strAppId, string strPlatform)
{
#ifdef WINDOWSEX

   ::file::path path;

   string strFolder;

   strsize iFind = strAppId.find('/');

   if (strPlatform.compare_ci("win32") == 0 || strPlatform.compare_ci("x86") == 0)
   {

      path = "C:\\Program Files (x86)\\";

   }
   else
   {

      path = "C:\\Program Files\\";

   }

   if (iFind < 0)
   {

      path /= strAppId;

   }
   else
   {

      path /= strAppId.Left(iFind);

      path /= strAppId.Mid(iFind + 1);

   }

   return path;

#elif defined(ANDROID)

   return ::dir::config();

#else

   return ::file::app_module().folder(4);

#endif


}

::file::path dir::install()
{

#ifdef ANDROID

   return ::dir::config();

#else

   return ::file::app_module().folder(4);

#endif

}


bool dir::mkdir(const ::file::path & path)
{

   if(is(path))
   {

      return true;

   }

   if(file_exists_dup(path))
   {

      if(!file_delete_dup(path))
      {

         return false;

      }

   }

#ifdef WINDOWS

   wstring wstr;

   if(is_absolute_path(path))
   {

      wstr = "\\\\?\\" + path;

   }
   else
   {

      wstr = path;

   }

   if(!::CreateDirectoryW(wstr, NULL))
   {

      return false;

   }

#else

   if(::mkdir(path, S_IRWXU | S_IRWXG | S_IRWXO) != 0)
   {

      TranslateLastError();

      return false;

   }

#endif

   return true;

}


bool dir::mk(const ::file::path & path)
{

   if (is(path))
   {

      return true;

   }

   string strName;

   ::file::path pathDir;

   strsize iLastPos;

#ifdef METROWIN

   {

      string strPath = path;

      string strPrefix;

      winrt_folder(strPath, strPrefix);

      pathDir = strPrefix;

      iLastPos = strPrefix.get_length();

   }

#else

   iLastPos = -1;

#endif

   while (true)
   {

      strsize iPos = path.find(::file::path_sep(::file::path_file), iLastPos + 1);

      if(iPos == 0)
      {

         iPos = path.find(::file::path_sep(::file::path_file), 1);

      }

      if(iPos < 0)
      {

         strName = path.substr(iLastPos + 1);

      }
      else
      {

         strName = path.substr(iLastPos + 1, iPos - iLastPos - 1);

      }

      if (pathDir.is_empty())
      {

         pathDir = strName;

      }
      else
      {

         pathDir /= strName;

      }

      if(!::dir::is(pathDir))
      {

         if(!::dir::mkdir(pathDir))
         {

            return false;

         }

      }

      if(iPos < 0)
      {

         return true;

      }

      iLastPos = iPos;

   }

   return true;

}


::file::path dir::module()
{

#ifdef WINDOWS

   hwstring path(MAX_PATH * 8);

   if(!GetModuleFileNameW(NULL,path,path.size()))
   {

      return "";

   }
   else
   {

      return name(string(path));

   }

#else

   return "/core/stage";

#endif

}



bool dir::is(const ::file::path & path1)
{

#ifdef METROWIN

   string str;

   //str = "\\\\?\\";
   //str += path1;

   str = path1;

   while(str_ends_dup(str,"\\") || str_ends_dup(str,"/"))
   {
      str = str.substr(0,str.length() - 1);
   }

   uint32_t dwFileAttributes = ::GetFileAttributesW(wstring(str));

   if (dwFileAttributes != INVALID_FILE_ATTRIBUTES && dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
   {

      return true;

   }
   else
   {

      DWORD dwLastError = ::get_last_error();

      string strPrefix;

      {

         string strRelative = str;

         auto folderBase = winrt_folder(strRelative, strPrefix);

         if (folderBase != nullptr)
         {

            strRelative.replace("/", "\\");

            strPrefix.replace("/", "\\");

            ::str::begins_eat_ci(strRelative, strPrefix);

            strRelative.trim("/\\");

            //strPrefix.trim_right("/\\");

            try
            {

               auto folder = ::wait(folderBase->GetFolderAsync(strRelative));

               if (folder != nullptr)
               {

                  return true;

               }

            }
            catch (...)
            {

            }

         }

      }

      auto folder = wait(::Windows::Storage::StorageFolder::GetFolderFromPathAsync(str));

      bool bOk = folder != nullptr;

      if (!bOk)
      {

         set_last_error(dwLastError);

      }

      return bOk;

   }


#elif defined(WINDOWSEX)

   WCHAR szVolumeName[128];

   string strVolume = path1;

   if (!str::ends(strVolume, "\\"))
   {

      strVolume += "\\";

   }

   wstring wstr = wstring(strVolume);

   if (GetVolumeNameForVolumeMountPointW(wstr, szVolumeName, sizeof(szVolumeName)))
   {

      wstr = szVolumeName;

   }
   else
   {

      string str;

      str = "\\\\?\\";
      str += path1;

      while (str_ends_dup(str, "\\") || str_ends_dup(str, "/"))
      {
         str = str.substr(0, str.length() - 1);
      }

   }


   uint32_t dwFileAttributes = ::GetFileAttributesW(wstr);

   if(dwFileAttributes != INVALID_FILE_ATTRIBUTES && dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
      return true;
   else
      return false;

#else

   // dedicaverse stat -> Sir And Arthur - Cesar Serenato

   return is_dir(path1);

#endif

}


string dir::name(string path)
{

   if(path.is_empty())
   {

      return path;

   }


   strsize iFirstColon = path.find(':');

   strsize iFirstSlash = -1;

   strsize iSecondSlash = -1;

   if (iFirstColon > 0)
   {

      iFirstSlash = path.find('/');

      if (iFirstSlash == iFirstColon + 1)
      {

         iSecondSlash = path.find('/', iFirstSlash + 1);

         if (iSecondSlash == iFirstSlash + 1 && path.get_length() == iSecondSlash + 1)
         {

            return "";

         }

      }

   }

   strsize iEnd = -1;

   if(path.last_char() == '/' || path.last_char() == '\\')
   {

      iEnd = -2;

   }

   strsize iPos1 = path.reverse_find('/',iEnd);

   strsize iPos2 = path.reverse_find('\\',iEnd);

   strsize iPos = MAX(MAX(iPos1, iPos2), 0);

   if (iPos == iSecondSlash)
   {

      path.Truncate(iPos + 1);

   }
   else
   {

      path.Truncate(iPos);

   }

   return path;

}


void dir::rls(::file::patha & stra, const file::path & psz)
{
   ::count start = stra.get_count();
   ls(stra, psz);
   ::count end = stra.get_count();
   for(::index i = start; i < end; i++)
   {
      if(is(stra[i]))
      {
         rls(stra, stra[i]);
      }
   }

}


void dir::rls_dir(::file::patha & stra,const ::file::path & psz)
{

   ::count start = stra.get_count();

   ls_dir(stra, psz);

   ::count end = stra.get_count();

   for(::index i = start; i < end; i++)
   {

      ::file::path path = stra[i];

      rls_dir(stra, path);

   }

}


void dir::ls(::file::patha & stra,const ::file::path & psz)
{

#if defined(LINUX) || defined(APPLEOS) || defined(ANDROID)

   DIR * dirp = opendir(psz);

   if(dirp == NULL)
      return;

   dirent * dp;
   ::file::path path;
   while ((dp = readdir(dirp)) != NULL)
   {

      if(strcmp(dp->d_name, "..") == 0)
         continue;
      else if(strcmp(dp->d_name, ".") == 0)
         continue;
      path = psz / dp->d_name;
      path.m_iDir = is(path) ? 1 : 0;
      stra.add(path);

      //output_debug_string("flood for you: dir::ls ----> " + path);

   }

   closedir(dirp);

#elif defined(METROWIN)

   ::Windows::Storage::StorageFolder ^ folder = nullptr;

   string strPrefix;

   string str = psz;

   try
   {

      if(string(psz).compare_ci("winmetro-Pictures://") == 0)
      {

         strPrefix = "winmetro-Pictures://";

         try
         {

            folder = ::Windows::Storage::KnownFolders::PicturesLibrary;

         }
         catch (...)
         {

            folder = nullptr;

         }

      }
      else if (string(psz).compare_ci("winmetro-Music://") == 0)
      {

         strPrefix = "winmetro-Music://";

         try
         {

            folder = ::Windows::Storage::KnownFolders::MusicLibrary;

         }
         catch (...)
         {

            folder = nullptr;

         }

      }
      else if (string(psz).compare_ci("winmetro-Videos://") == 0)
      {

         strPrefix = "winmetro-Videos://";

         try
         {

            folder = ::Windows::Storage::KnownFolders::VideosLibrary;

         }
         catch (...)
         {

            folder = nullptr;

         }

      }
      else if (string(psz).compare_ci("winmetro-Document://") == 0)
      {

         strPrefix = "winmetro-Document://";

         try
         {

            folder = ::Windows::Storage::KnownFolders::DocumentsLibrary;

         }
         catch (...)
         {

            folder = nullptr;

         }

      }
      else
      {

         if (::str::begins_eat_ci(str, "winmetro-Pictures://"))
         {

            strPrefix = "winmetro-Pictures://";

            try
            {

               folder = ::Windows::Storage::KnownFolders::PicturesLibrary;

            }
            catch (...)
            {

               folder = nullptr;

            }

         }

         if(::str::begins_eat_ci(str, "winmetro-Music://"))
         {

            strPrefix = "winmetro-Music://";

            try
            {

               folder = ::Windows::Storage::KnownFolders::MusicLibrary;

            }
            catch (...)
            {

               folder = nullptr;

            }

         }

         if (::str::begins_eat_ci(str, "winmetro-Videos://"))
         {

            strPrefix = "winmetro-Videos://";

            try
            {

               folder = ::Windows::Storage::KnownFolders::VideosLibrary;

            }
            catch (...)
            {

               folder = nullptr;

            }

         }

         if (::str::begins_eat_ci(str, "winmetro-Document://"))
         {

            strPrefix = "winmetro-Document://";

            try
            {

               folder = ::Windows::Storage::KnownFolders::DocumentsLibrary;

            }
            catch (...)
            {

               folder = nullptr;

            }

         }

         if (strPrefix.has_char())
         {

            stringa stra;

            stra.explode("/", str);

            string str;

            while (stra.get_count() > 0)
            {

               str = stra[0];

               folder = wait(folder->GetFolderAsync(str));

               strPrefix += str + "/";

               stra.remove_at(0);

            }

         }
         else
         {

            folder = wait(Windows::Storage::StorageFolder::GetFolderFromPathAsync(str));

            strPrefix = str + "/";

         }

      }

   }
   catch (...)
   {

      return;

   }

   if(folder == nullptr)
      return;

   ::Windows::Foundation::Collections::IVectorView < ::Windows::Storage::IStorageItem ^ > ^ a = wait(folder->GetItemsAsync());

   for(uint32_t ui = 0; ui < a->Size; ui++)
   {

      string strPath = strPrefix + string(begin(a->GetAt(ui)->Name));

      ::file::path path(strPath);

      string str = path;

      path.m_iDir = a->GetAt(ui)->IsOfType( ::Windows::Storage::StorageItemTypes::Folder) ? 1 :0;

      stra.add(path);

   }


#else

   WIN32_FIND_DATA FindFileData;

   HANDLE hFind;

   hFind = FindFirstFile(psz / "*", &FindFileData);

   if (hFind == INVALID_HANDLE_VALUE)
      return;

   while(true)
   {

      if(!__win_file_find_is_dots(FindFileData) && (FindFileData.dwFileAttributes != INVALID_FILE_ATTRIBUTES))
         stra.add(FindFileData.cFileName);

      //if (stra.has_elements() && stra.last() == "teste")
      //{
      //   output_debug_string("teste");
      //}

      if(!FindNextFile(hFind, &FindFileData))
         break;

   }

   FindClose(hFind);

#endif


}

void dir::ls_dir(::file::patha & stra,const ::file::path & psz)
{

#if defined(LINUX) || defined(APPLEOS) || defined(ANDROID)

   DIR * dirp = opendir(psz);

   if(dirp == NULL)
      return;

   dirent * dp;

   while ((dp = readdir(dirp)) != NULL)
   {
      if(dp->d_name[0] == '.')
      {
         if(dp->d_name[1] == '\0')
            continue;
         if(dp->d_name[1] == '.')
         {
            if(dp->d_name[2] == '\0')
               continue;
         }
      }
      ::file::path strPath = psz /  dp->d_name;
      if(is(strPath))
      {
         stra.add(strPath);
      }

   }

   closedir(dirp);

#elif defined(METROWIN)

   ::Windows::Storage::StorageFolder ^ folder = wait(::Windows::Storage::StorageFolder::GetFolderFromPathAsync(string(psz)));

   ::Windows::Foundation::Collections::IVectorView < ::Windows::Storage::StorageFolder ^ > ^ a = wait(folder->GetFoldersAsync());

   for(uint32_t ui = 0; ui < a->Size; ui++)
   {
      stra.add(begin(a->GetAt(ui)->Path));
   }


#else

   WIN32_FIND_DATA FindFileData;

   HANDLE hFind;

   hFind = FindFirstFile(psz, &FindFileData);

   if (hFind == INVALID_HANDLE_VALUE)
      return;

   while(true)
   {

      if(!__win_file_find_is_dots(FindFileData) && (FindFileData.dwFileAttributes != INVALID_FILE_ATTRIBUTES) && (FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0)
         stra.add(FindFileData.cFileName);


      stra.add(FindFileData.cFileName);

      if(!FindNextFile(hFind, &FindFileData))
         break;

   }

   FindClose(hFind);

#endif


}

void dir::ls_file(::file::patha & stra,const ::file::path & psz)
{

#if defined(LINUX) || defined(APPLEOS) || defined(ANDROID)

   DIR * dirp = opendir(psz);

   if(dirp == NULL)
      return;

   dirent * dp;

   while ((dp = readdir(dirp)) != NULL)
   {
      if(dp->d_name[0] == '.')
      {
         if(dp->d_name[1] == '\0')
            continue;
         if(dp->d_name[1] == '.')
         {
            if(dp->d_name[2] == '\0')
               continue;
         }
      }
      ::file::path strPath = psz /  dp->d_name;
      if(!is(strPath))
      {
         stra.add(strPath);
      }

   }

   closedir(dirp);

#elif defined(METROWIN)

   ::Windows::Storage::StorageFolder ^ folder = wait(::Windows::Storage::StorageFolder::GetFolderFromPathAsync(string(psz)));

   ::Windows::Foundation::Collections::IVectorView < ::Windows::Storage::StorageFolder ^ > ^ a = wait(folder->GetFoldersAsync());

   for(uint32_t ui = 0; ui < a->Size; ui++)
   {
      stra.add(begin(a->GetAt(ui)->Path));
   }


#else

   WIN32_FIND_DATA FindFileData;

   HANDLE hFind;

   hFind = FindFirstFile(psz, &FindFileData);

   if (hFind == INVALID_HANDLE_VALUE)
      return;

   while(true)
   {

      if(!__win_file_find_is_dots(FindFileData) && (FindFileData.dwFileAttributes != INVALID_FILE_ATTRIBUTES) && (FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0)
      {
      }
      else
      {
         stra.add(FindFileData.cFileName);
      }


      stra.add(FindFileData.cFileName);

      if(!FindNextFile(hFind, &FindFileData))
         break;

   }

   FindClose(hFind);

#endif


}


//::file::path dir::default_os_user_path_prefix()
//{
//
//#if defined(WINDOWSEX)
//
//   hwstring buf(MAX_PATH * 8);
//
//   ULONG ulSize = (ULONG) buf.count();
//
//   if(!::GetUserNameExW(NameCanonical, buf, &ulSize))
//   {
//
//      if(!::GetUserNameW(buf, &ulSize))
//      {
//
//         memset(buf, 0, sizeof(buf));
//
//      }
//
//   }
//
//   string str;
//
//   str = str::international::unicode_to_utf8(buf);
//
//   return str;
//
//#elif defined(METROWIN)
//
////#pragma push_macro("System")
////#undef System
////
////   string str(::Windows::System::UserProfile::UserInformation->GetDomainNameAsync()->GetResults()->Data());
////
////#pragma pop_macro("System")
//
//   return "User";
//
//   //return str;
//
//#elif defined(ANDROID)
//
//   string str("ca2user");
//
//   return str;
//
//#else
//
//   memory mem;
//
//   mem.allocate(512);
//
//retry:
//
//   if(getlogin_r((char *) mem.get_data(), mem.get_size()))
//   {
//
//      if(errno == ERANGE)
//      {
//
//         if(mem.get_size() < 65536)
//         {
//
//            mem.allocate(mem.get_size() + 512);
//
//            goto retry;
//
//         }
//
//      }
//
//      return "";
//
//   }
//
//   return mem.to_string();
//
//#endif
//
//}



//::file::path dir::usersystemappdata(string strPlatform, const string & lpcszPrefix)
//{
//
//   return appdata(strPlatform) / lpcszPrefix;
//
//}


//::file::path dir::default_userappdata(const string & lpcszPrefix,const string & lpcszLogin)
//{
//
//   return default_user(lpcszPrefix, lpcszLogin) / "appdata";
//
//}


//::file::path dir::default_userdata(const string & lpcszPrefix,const string & lpcszLogin)
//{
//
//   return default_user(lpcszPrefix, lpcszLogin) /  "data";
//
//}


//::file::path dir::default_user(const string & lpcszPrefix,const string & lpcszLogin)
//{
//
//   return user();
//
//}


//::file::path dir::config()
//{
//
//   ::file::path str;
//
//#ifdef WINDOWSEX
//
//   ::windows::shell_get_special_folder_path(NULL, str, CSIDL_PROFILE, false);
//
//#elif defined(METROWIN)
//
//   str = ::Windows::Storage::KnownFolders::DocumentsLibrary->Path;
//
//#else
//
//   str = getenv("HOME");
//
//#endif
//
//   string strRelative;
//   strRelative = install();
//   index iFind = strRelative.find(':');
//   if(iFind >= 0)
//   {
//      ::index iFind1 = strRelative.reverse_find('\\', iFind);
//      ::index iFind2 = strRelative.reverse_find('/', iFind);
//      ::index iStart = MAX(iFind1 + 1, iFind2 + 1);
//      strRelative = strRelative.substr(0, iFind - 1) + "_" + strRelative.substr(iStart, iFind - iStart) + strRelative.substr(iFind + 1);
//   }
//
//   string strUserFolderShift;
//
//   /*if(App(papp).handler()->m_varTopicQuery.has_property("user_folder_relative_path"))
//   {
//   strUserFolderShift = path(strRelative, App(papp).handler()->m_varTopicQuery["user_folder_relative_path"].get_string());
//   }
//   else*/
//   {
//      strUserFolderShift = strRelative;
//   }
//
//   return ::file::path(str) / "ca2" / strUserFolderShift;
//
//}


::file::path dir::pathfind(const string & pszEnv,const string & pszTopic,const string & pszMode)
{

   stringa stra;

   stra.add_tokens(pszEnv, ":");

   string strCandidate;

   for(int32_t i = 0; i < stra.get_count(); i++)
   {

      if(stra[i].is_empty())
         continue;

      strCandidate = ::file::path(stra[i]) / pszTopic;

      if(file_exists_dup(strCandidate))
      {
         return strCandidate;
      }

   }

   return "";

}



::file::path dir::bergedge()
{

#ifdef WINDOWS

   return "C:\\bergedge";

#else

   return "/bergedge";

#endif

}



::file::path dir::beforeca2()
{

   return dir::name(dir::install());

}


#ifdef WINDOWSEX

#include <Shlobj.h>

::file::path dir::program_files_x86()
{

   hwstring lpszModuleFolder(sizeof(unichar) * 8);

   hwstring lpszModuleFilePath(sizeof(unichar) * 8);

   wcscpy(lpszModuleFilePath,_wgetenv(L"PROGRAMFILES(X86)"));

   if(wcslen(lpszModuleFilePath) == 0)
   {

      SHGetSpecialFolderPathW(
      NULL,
      lpszModuleFilePath,
      CSIDL_PROGRAM_FILES,
      FALSE);

   }

   if(lpszModuleFilePath[wcslen(lpszModuleFilePath) - 1] == '\\' || lpszModuleFilePath[wcslen(lpszModuleFilePath) - 1] == '/')
   {

      lpszModuleFilePath[wcslen(lpszModuleFilePath) - 1] = '\0';

   }

   wcscpy(lpszModuleFolder,lpszModuleFilePath);

   return string(lpszModuleFolder);

}


#else

::file::path dir::program_files_x86()
{


   ::file::path p("/opt/ca2");

   return p;


}


#endif





::file::path dir::stage(string strAppId, string strPlatform)
{

   return inplace_install(strAppId, strPlatform) /  "time" / time_binary_platform(strPlatform) / process_version_dir_name();

}



#if LINUX

::file::path dir::home()
{

   return getenv("HOME");

}

//::file::path dir::ca2config()
//{
//
//   return home() / ".config/ca2";
//
//}


#endif



#if defined(METROWIN) || defined(APPLEOS) || defined(LINUX)

::file::path dir::favorites()
{

   return ::dir::local() / "localconfig/favorites";

}

#endif

#ifdef METROWIN

::file::path dir::home()
{

   return "";

}

#endif


