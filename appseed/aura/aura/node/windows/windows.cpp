#include "framework.h"


namespace windows
{


   int32_t windows::function()
   {

      return 0;

   }


   HINSTANCE load_library(const char * lpsz)
   {

      return ::LoadLibraryW(::str::international::utf8_to_unicode(lpsz));

   }


   bool CLASS_DECL_AURA shell_get_special_folder_path(oswindow oswindow,::file::path &str,int32_t csidl,bool fCreate)
   {

      return ::SHGetSpecialFolderPathW(oswindow,wtostring(str,MAX_PATH * 8),csidl,fCreate) != FALSE;

   }


   DWORD get_file_attributes(const char * lpFileName)
   {

      return ::GetFileAttributesW(::str::international::utf8_to_unicode(lpFileName));

   }


   bool create_directory(const char * lpPathName,LPSECURITY_ATTRIBUTES lpSecurityAttributes)
   {

      return ::CreateDirectoryW(::str::international::utf8_to_unicode(lpPathName),lpSecurityAttributes) != FALSE;

   }


   DWORD get_current_directory(string & str)
   {

      return ::GetCurrentDirectoryW(MAX_PATH * 8,wtostring(str,MAX_PATH * 8));

   }


   DWORD get_temp_path(string & str)
   {

      return ::GetTempPathW(MAX_PATH * 8,wtostring(str,MAX_PATH * 8));

   }


   LONG reg_query_value(HKEY hkey,const char * lpszSubKey,string & str)
   {

      DWORD dwType = 0;
      DWORD dwSize = 0;
      LONG lResult = RegQueryValueEx(hkey,lpszSubKey,NULL,&dwType,NULL,&dwSize);
      if(lResult != ERROR_SUCCESS)
         return lResult;
      ASSERT(dwType == REG_SZ || dwType == REG_MULTI_SZ || dwType == REG_EXPAND_SZ);
      if(dwType == REG_SZ || dwType == REG_MULTI_SZ || dwType == REG_EXPAND_SZ)
      {
         lResult = RegQueryValueEx(hkey,lpszSubKey,NULL,&dwType,(LPBYTE)str.GetBufferSetLength(dwSize),&dwSize);
         str.ReleaseBuffer(dwSize);

         return lResult;

      }
      else
      {

         return ERROR_NOT_SUPPORTED;

      }

   }


   HICON extract_icon(HINSTANCE hInst,const char * lpszExeFileName,UINT nIconIndex)
   {

      return ::ExtractIconW(hInst,::str::international::utf8_to_unicode(lpszExeFileName),nIconIndex);

   }


   bool delete_file(const char * lpFileName)
   {

      return ::DeleteFileW(::str::international::utf8_to_unicode(lpFileName)) != FALSE;

   }


   CLASS_DECL_AURA void time_to_filetime(::aura::application * papp,const ::datetime::time& time,LPFILETIME pFileTime)
   {

      SYSTEMTIME sysTime;

      sysTime.wYear           = (WORD)time.GetYear();
      sysTime.wMonth          = (WORD)time.GetMonth();
      sysTime.wDay            = (WORD)time.GetDay();
      sysTime.wHour           = (WORD)time.GetHour();
      sysTime.wMinute         = (WORD)time.GetMinute();
      sysTime.wSecond         = (WORD)time.GetSecond();
      sysTime.wMilliseconds   = 0;

      // convert system time to local file time
      FILETIME localTime;
      if(!SystemTimeToFileTime((LPSYSTEMTIME)&sysTime,&localTime))
         ::windows::file_exception::ThrowOsError(papp,(LONG)::GetLastError());

      // convert local file time to UTC file time
      if(!LocalFileTimeToFileTime(&localTime,pFileTime))
         ::windows::file_exception::ThrowOsError(papp,(LONG)::GetLastError());

   }



} // namespace windows




CLASS_DECL_AURA int32_t app_main(::aura::system * psystem, HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int32_t nCmdShow)
{

   __node_init_main_data(psystem, hInstance, hPrevInstance, lpCmdLine, nCmdShow);

   //t32_t iRet;

   //iRet = psystem->main();

   error error;

   psystem->main();

   try
   {

      error = psystem->m_error;

      delete psystem;

      psystem = NULL;

   }
   catch (...)
   {

   }

   return error.get_exit_code();


}





