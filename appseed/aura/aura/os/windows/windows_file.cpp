#include "framework.h"
#include <stdio.h>
#include <share.h>
#include <io.h>
#include <fcntl.h>


BEGIN_EXTERN_C

int_bool read_resource_as_file_dup(const char * pszFile, HINSTANCE hinstance, UINT nID, LPCTSTR lpcszType)
{

   HRSRC hrsrc = FindResource(hinstance, MAKEINTRESOURCE(nID), lpcszType);
   HGLOBAL hglobalResource;
   uint32_t dwResourseSize;
   int_bool bOk;
   UINT FAR* pResource;
   FILE * file;

   if(hrsrc == NULL)
      return FALSE;

   hglobalResource = LoadResource(hinstance, hrsrc);

   if(hglobalResource == NULL)
      return FALSE;

   dwResourseSize = SizeofResource(hinstance, hrsrc);

   if(hglobalResource != NULL)
   {

      bOk = FALSE;

      pResource = (UINT FAR*) LockResource(hglobalResource);

      dir::mk(dir::name(pszFile));

      file = fopen_dup(pszFile, "wb", _SH_DENYNO);

      if(file != NULL)
      {

         auto dwWritten = fwrite(pResource, 1, dwResourseSize, file);

         fclose(file);

         bOk = dwWritten == dwResourseSize;

      }

      FreeResource(hglobalResource);

      return bOk;

   }

   return FALSE;

}


int_bool file_exists_dup(const char * path1)
{

   wstring wstr;

   wstr.alloc(strlen_dup(path1) + 256);

   wcscat(wstr, L"\\\\?\\");

   utf8_to_utf16((unichar *) wstr + wcslen(wstr), path1);

   wstr.set_length(wcslen(wstr));

   unichar * pwsz = (unichar *) wstr;
   while(*pwsz != L'\0')
   {
      if(*pwsz == '/')
      {
         *pwsz = '\\';
      }
      pwsz++;
   }

   uint32_t dwFileAttributes = GetFileAttributesW(wstr);

   if(dwFileAttributes == INVALID_FILE_ATTRIBUTES || (dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0)
      return FALSE;

   return true;

}



int_bool file_put_contents_dup(const char * path, const char * contents, count len)
{

   dir::mk(dir::name(path));

   wstring wstr(path);

   FILE * file = fopen_dup(path, "w", _SH_DENYWR);

   if (file == NULL)
   {

      return false;

   }

   count dwWrite;

   if(len < 0)
      dwWrite = strlen_dup(contents);
   else
      dwWrite = len;

   auto dwWritten = fwrite(contents, 1, (uint32_t) dwWrite, file);

   int_bool bOk = dwWritten == dwWrite;

   fclose(file);

   return dwWrite == dwWritten && bOk != FALSE;

}


uint64_t file_length_dup(const char * path)
{

   HANDLE hfile = CreateFileW(wstring(path), GENERIC_READ, FILE_SHARE_WRITE | FILE_SHARE_READ | FILE_SHARE_DELETE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

   if(hfile == INVALID_HANDLE_VALUE)
      return 0;

   DWORD dwHi = 0;

   uint64_t ui = GetFileSize(hfile, &dwHi);

   ui |= ((uint64_t)dwHi) << 32ULL;

   CloseHandle(hfile);

   return ui;

}










int_bool file_is_equal_path_dup(const char * psz1, const char * psz2)
{

   const int32_t iBufSize = MAX_PATH * 8;
   wstring pwsz1 = ::str::international::utf8_to_unicode(psz1);
   wstring pwsz2 = ::str::international::utf8_to_unicode(psz2);
   unichar * pwszFile1;
   unichar * pwszFile2;
   unichar * pwszPath1 = new unichar[iBufSize];
   unichar * pwszPath2 = new unichar[iBufSize];
   int32_t iCmp = -1;
   if(GetFullPathNameW(pwsz1, iBufSize, pwszPath1, &pwszFile1))
   {
      if(GetFullPathNameW(pwsz2, iBufSize, pwszPath2, &pwszFile2))
      {
         string p1 = ::str::international::unicode_to_utf8(pwszPath1);
         string p2 = ::str::international::unicode_to_utf8(pwszPath2);
         iCmp = stricmp_dup(p1, p2);
      }
   }
   delete pwszPath1;
   delete pwszPath2;
   return iCmp == 0;

}



END_EXTERN_C































string file_get_mozilla_firefox_plugin_container_path()
{

   string strPath;
   HKEY hkeyMozillaFirefox;

   if(::RegOpenKey(HKEY_LOCAL_MACHINE, "SOFTWARE\\Mozilla\\Mozilla Firefox", &hkeyMozillaFirefox) != ERROR_SUCCESS)
      return "";
   {

      DWORD dwType;
      DWORD dwData;
      dwData = 0;
      if(::WinRegGetValueW(hkeyMozillaFirefox, NULL, L"CurrentVersion", RRF_RT_REG_SZ, &dwType, NULL, &dwData) != ERROR_SUCCESS)
      {
         goto ret1;
      }

      wstring wstrVersion;
      wstrVersion.alloc(dwData);
      if(::WinRegGetValueW(hkeyMozillaFirefox, NULL, L"CurrentVersion", RRF_RT_REG_SZ, &dwType, wstrVersion, &dwData) != ERROR_SUCCESS)
      {
         goto ret1;
      }
      wstrVersion.release_buffer();

      wstring wstrMainSubKey = wstrVersion + L"\\Main";
      dwData = 0;

      if(::WinRegGetValueW(hkeyMozillaFirefox, wstrMainSubKey, L"Install Directory", RRF_RT_REG_SZ, &dwType, NULL, &dwData) != ERROR_SUCCESS)
      {
         goto ret1;
      }

      wstring wstrDir;
      wstrDir.alloc(dwData);
      if(::WinRegGetValueW(hkeyMozillaFirefox, wstrMainSubKey, L"Install Directory", RRF_RT_REG_SZ, &dwType, wstrDir, &dwData) != ERROR_SUCCESS)
      {
         goto ret1;
      }
      wstrDir.release_buffer();

      ::file::path strDir;

      strDir = ::str::international::unicode_to_utf8(wstrDir);

      strPath = strDir / "plugin-container.exe";
   }

ret1:
   ::RegCloseKey(hkeyMozillaFirefox);
   return strPath;

}






::file::path dir::sys_temp()
{

   return ::dir::appdata() / "time";

}



string file_as_string_dup(const char * path)
{

   string str;

   FILE * file = ::fopen_dup(path, "r", _SH_DENYNO);

   if (file == NULL)
   {

      DWORD dw = ::get_last_error();

      return "";

   }

   DWORD dwSize;

   dwSize = (DWORD) fsize_dup(file);

   LPSTR lpsz = str.GetBufferSetLength(dwSize);

   auto dwRead = fread(lpsz, 1, dwSize, file);

   lpsz[dwSize] = '\0';

   str.ReleaseBuffer(dwSize);

   fclose(file);

   return str;


}



bool file_get_memory_dup(::primitive::memory_base & memory, const char * path)
{

   memory.allocate(0);

   FILE * file = ::fopen_dup(path, "r", _SH_DENYNO);

   if (file == NULL)
   {

      return false;

   }

   uint64_t uiSize = fsize_dup(file);

   if(uiSize > ((uint64_t) -1))
   {

      ::fclose(file);

      return false;

   }

   memory.allocate((::count) uiSize);

   auto dwRead = ::fread(memory.get_data(), 1, (uint32_t) memory.get_size(), file);

   ::fclose(file);

   return true;

}









//#define NT_SUCCESS(Status) ((NTSTATUS)(Status) >= 0)

struct PROCESS_INFO_t
{
   string csProcess;
   uint32_t dwImageListIndex;
};


#if !defined(LINUX) && !defined(MACOS) && !defined(METROWIN) && !defined(ANDROID)

//#include <Tlhelp32.h>
//#include <Psapi.h>


void EnumerateLoadedModules( string& csPath, OF_CALLBACK CallBackProc, uint_ptr pUserContext );
void EnumerateOpenedFiles( string& csPath, OF_CALLBACK CallBackProc, uint_ptr pUserContext, HANDLE hDriver, GetFinalPathNameByHandleDef pGetFinalPathNameByHandle );

const LPCTSTR DRV_DOS_NAME = _T("\\\\.\\ListFileDrv");
const LPCTSTR DRV_NAME = _T("ListOpenedFileDrv");
const LPCTSTR DRV_FILE_NAME = _T("ListOpenedFileDrv.sys");

#define DRIVER_FILE_NAME_32 _T("\\ListOpenedFileDrv_32.sys")
#define DRIVER_FILE_NAME_64 _T("\\ListOpenedFileDrv_64.sys")


// This Function install the driver and starts it
HANDLE OnlyGetDrv()
{


   HMODULE hModule = GetModuleHandle(_T("core.dll"));
   if( !hModule )
   {
      output_debug_string( L"GetModuleHandle(_T(\"core.dll\")); failed" );
      return 0;
   }
   string csFilePath;
   LPTSTR lpPath = csFilePath.GetBuffer( MAX_PATH );
   GetModuleFileName( hModule,lpPath, MAX_PATH );
   LIBCALL(shlwapi,PathRemoveFileSpecA)(lpPath);
   csFilePath.ReleaseBuffer();
   if(IsWow64())
   {
      csFilePath += DRIVER_FILE_NAME_64;
   }
   else
   {
      csFilePath += DRIVER_FILE_NAME_32;
   }

   if(!LIBCALL(shlwapi, PathFileExistsA)(csFilePath))
   {
      simple_message_box(NULL,"Cannot find driver " + csFilePath,"Cannot find driver " + csFilePath,MB_OK);
      return 0;
   }



   // Delete the temp file...
   //DeleteFile( csPath );
   HANDLE hFile = CreateFile( DRV_DOS_NAME, GENERIC_READ|GENERIC_WRITE,
                              FILE_SHARE_READ | FILE_SHARE_WRITE, 0,
                              OPEN_EXISTING, FILE_FLAG_OVERLAPPED, 0 );
   return hFile;

}


extern "C" CLASS_DECL_AURA void GetOpenedFiles(LPCWSTR lpPath, OF_TYPE Filter, OF_CALLBACK CallBackProc, uint_ptr pUserContext)
{
   string csPath = lpPath;
   csPath.make_lower();
   EnableTokenPrivilege( SE_DEBUG_NAME );
   if( Filter& MODULES_ONLY )
   {
      EnumerateLoadedModules( csPath, CallBackProc, pUserContext );
   }

   if( Filter& FILES_ONLY )
   {


      // Extract the driver from the resource and install it.
      //HANDLE hDriver = ExtractAndInstallDrv();
      //HANDLE hDriver = OnlyGetDrv();
      HANDLE hDriver = NULL;
      GetFinalPathNameByHandleDef pGetFinalPathNameByHandle = 0;
      if(  !hDriver )
      {
         pGetFinalPathNameByHandle = (GetFinalPathNameByHandleDef)GetProcAddress( GetModuleHandle(_T("kernel32.dll")), "GetFinalPathNameByHandleW" );
      }
      // Now walk all handles
      EnumerateOpenedFiles( csPath, CallBackProc, pUserContext, hDriver, pGetFinalPathNameByHandle );
      //if( hDriver )
      {
         // Time to wind up
         //StopAndUninstallDrv( hDriver );
      }
   }
}

#ifndef METROWIN

typedef struct _SYSTEM_HANDLE_INFORMATION
{
   uint32_t         dwCount;
   SYSTEM_HANDLE Handles[1];
} SYSTEM_HANDLE_INFORMATION, *PSYSTEM_HANDLE_INFORMATION, **PPSYSTEM_HANDLE_INFORMATION;

typedef enum _SYSTEM_INFORMATION_CLASS2
{
   SystemHandleInformation = 0X10,
} SYSTEM_INFORMATION_CLASS2;

#endif

typedef NTSTATUS ( WINAPI *PNtQuerySystemInformation)
( IN SYSTEM_INFORMATION_CLASS2 SystemInformationClass,
  OUT   PVOID              SystemInformation,
  IN ULONG              SystemInformationLength,
  OUT   PULONG                ReturnLength OPTIONAL );

UINT g_CurrentIndex = 0;
struct THREAD_PARAMS
{
   PSYSTEM_HANDLE_INFORMATION pSysHandleInformation;
   GetFinalPathNameByHandleDef pGetFinalPathNameByHandle;
   LPWSTR lpPath;
   int32_t nFileType;
   HANDLE hStartEvent;
   HANDLE hFinishedEvent;
   bool bStatus;
};

uint32_t ThreadProc(void * lParam)
{
   THREAD_PARAMS* pThreadParam = (THREAD_PARAMS*)lParam;

   FILE_NAME_INFO * pinfo = (FILE_NAME_INFO *)new BYTE[MAX_PATH * 8];

   GetFinalPathNameByHandleDef pGetFinalPathNameByHandle = pThreadParam->pGetFinalPathNameByHandle;
   for( g_CurrentIndex; g_CurrentIndex < pThreadParam->pSysHandleInformation->dwCount;  )
   {

      WaitForSingleObject( pThreadParam->hStartEvent, INFINITE );
      ResetEvent( pThreadParam->hStartEvent );
      pThreadParam->bStatus = false;
      SYSTEM_HANDLE& sh = pThreadParam->pSysHandleInformation->Handles[g_CurrentIndex];
      g_CurrentIndex++;
      HANDLE hDup = (HANDLE)sh.wValue;
      HANDLE hProcess = OpenProcess( PROCESS_DUP_HANDLE, FALSE, sh.dwProcessId );
      if( hProcess )
      {
         bool b = DuplicateHandle( hProcess, (HANDLE)sh.wValue, GetCurrentProcess(), &hDup, 0, FALSE, DUPLICATE_SAME_ACCESS ) != FALSE;
         if( !b )
         {
            hDup = (HANDLE)sh.wValue;
         }
         CloseHandle( hProcess );
      }
      //uint32_t dwRet = pGetFinalPathNameByHandle( hDup, pThreadParam->lpPath, MAX_PATH, 0 );
      //uint32_t dwRet = GetFileInformationByHandleEx(hDup, FileNameInfo, pinfo, MAX_PATH * 8);
      uint32_t dwRet = GetFinalPathNameByHandleW( hDup, pThreadParam->lpPath, MAX_PATH, 0 );
      //wcsncpy(pThreadParam->lpPath, pinfo->FileName, pinfo->FileNameLength);
      if( hDup && (hDup != (HANDLE)sh.wValue))
      {
         CloseHandle( hDup );
      }
      if(dwRet)
      {
         pThreadParam->bStatus = true;
      }
      SetEvent( pThreadParam->hFinishedEvent );

   }
   delete[] (BYTE *) pinfo;
   return 0;
}

void EnumerateOpenedFiles( string& csPath, OF_CALLBACK CallBackProc, uint_ptr pUserContext, HANDLE hDriver,
                           GetFinalPathNameByHandleDef pGetFinalPathNameByHandle )
{
   int32_t nFileType;

   if(is_windows_vista_or_greater())
   {
      nFileType = VISTA_FILETYPE;
   }
   else
   {
      nFileType = XP_FILETYPE;
   }

   LPCTSTR lpPath = csPath;
   string csShortName;
   GetShortPathName( csPath, csShortName.GetBuffer( MAX_PATH), MAX_PATH );
   csShortName.ReleaseBuffer();
   csShortName.make_lower();
   bool bShortPath = false;
   LPCTSTR lpShortPath = csShortName;
   if(  csShortName != csPath && FALSE == csShortName.is_empty())
   {
      bShortPath = true;
   }

   HMODULE hModule = GetModuleHandle(_T("ntdll.dll"));
   PNtQuerySystemInformation NtQuerySystemInformation = (PNtQuerySystemInformation)GetProcAddress( hModule, "NtQuerySystemInformation" );
   if( 0 == NtQuerySystemInformation )
   {
      output_debug_string( L"Getting proc of NtQuerySystemInformation failed" );
      return;
   }

   // Get the list of all handles in the file_system
   PSYSTEM_HANDLE_INFORMATION pSysHandleInformation = new SYSTEM_HANDLE_INFORMATION;
   uint32_t size = sizeof(SYSTEM_HANDLE_INFORMATION);
   DWORD needed = 0;
   NTSTATUS status = NtQuerySystemInformation( SystemHandleInformation, pSysHandleInformation, size, &needed );
   if( !NT_SUCCESS(status))
   {
      if( 0 == needed )
      {
         return;// some other error
      }
      // The previously supplied buffer wasn't enough.
      delete pSysHandleInformation;
      size = needed + 1024;
      pSysHandleInformation = (PSYSTEM_HANDLE_INFORMATION)new BYTE[size];
      status = NtQuerySystemInformation( SystemHandleInformation, pSysHandleInformation, size, &needed );
      if( !NT_SUCCESS(status))
      {
         // some other error so quit.
         delete pSysHandleInformation;
         return;
      }
   }

   if( pGetFinalPathNameByHandle )// there is no driver, we have do it ugly way
   {
      g_CurrentIndex = 0;
//    TCHAR tcFileName[MAX_PATH+1];
      THREAD_PARAMS ThreadParams;
      wstring wstrFileName;

      wstrFileName.alloc(MAX_PATH * 8);
      ThreadParams.lpPath = wstrFileName;
      ThreadParams.nFileType = nFileType;
      ThreadParams.pGetFinalPathNameByHandle = pGetFinalPathNameByHandle;
      ThreadParams.pSysHandleInformation = pSysHandleInformation;
      ThreadParams.hStartEvent = ::CreateEvent( 0, TRUE, FALSE, 0 );
      ThreadParams.hFinishedEvent = ::CreateEvent( 0, TRUE, FALSE, 0 );
      HANDLE ThreadHandle = 0;
      while( g_CurrentIndex < pSysHandleInformation->dwCount )
      {
         if( !ThreadHandle )
         {
            ThreadHandle = create_thread( 0, 0, ThreadProc, &ThreadParams, 0, 0 );
         }
         ResetEvent( ThreadParams.hFinishedEvent );
         SetEvent( ThreadParams.hStartEvent );
         if( WAIT_TIMEOUT == WaitForSingleObject( ThreadParams.hFinishedEvent, 100 ))
         {
            string csError;
            csError.Format("Query hang for handle %d", (int32_t)pSysHandleInformation->Handles[g_CurrentIndex - 1].wValue);
            output_debug_string(csError );
            TerminateThread( ThreadHandle, 0 );
            CloseHandle( ThreadHandle );
            ThreadHandle = 0;
            continue;
         }
         if( !ThreadParams.bStatus )
         {
            continue;
         }
         int32_t nCmpStart = 4;
         string csFileName( ::str::international::unicode_to_utf8(&ThreadParams.lpPath[nCmpStart]));
         csFileName.make_lower();
         if(csFileName.find("vs11_dp_ctp") >= 0)
         {
            continue;
         }
         else if( 0 != _tcsncmp( lpPath, csFileName, csPath.get_length()))
         {
            continue;
         }
         OF_INFO_t stOFInfo;
         stOFInfo.dwPID = pSysHandleInformation->Handles[g_CurrentIndex - 1].dwProcessId;
         wstring wstrCallback;
         wstrCallback = ::str::international::utf8_to_unicode(csFileName);
         stOFInfo.lpFile = wstrCallback;
         stOFInfo.hFile  = (HANDLE)pSysHandleInformation->Handles[g_CurrentIndex - 1].wValue;
         CallBackProc( stOFInfo, pUserContext );
      }
      if( ThreadHandle )
      {
         if( WAIT_TIMEOUT == WaitForSingleObject( ThreadHandle, 1000 ))
         {
            TerminateThread( ThreadHandle, 0 );
         }
         CloseHandle( ThreadHandle );
      }
      CloseHandle( ThreadParams.hStartEvent );
      CloseHandle( ThreadParams.hFinishedEvent );
      return;
   }

   // Walk through the handle list
   for ( uint32_t i = 0; i < pSysHandleInformation->dwCount; i++ )
   {
      SYSTEM_HANDLE& sh = pSysHandleInformation->Handles[i];
      if( sh.bObjectType != nFileType )// Under windows XP file handle is of type 28
      {
         continue;
      }

      string csFileName;
      string csDir;
      if( hDriver )
      {
         HANDLE_INFO stHandle = {0};
         ADDRESS_INFO stAddress;
         stAddress.pAddress = sh.pAddress;
         DWORD dwReturn = 0;
         bool bSuccess = DeviceIoControl( hDriver, IOCTL_LISTDRV_BUFFERED_IO, &stAddress, sizeof(ADDRESS_INFO), &stHandle, sizeof(HANDLE_INFO), &dwReturn, NULL ) != FALSE;


         if( bSuccess && stHandle.tcFileName[0] != 0 &&
               stHandle.uType != FILE_DEVICE_SOUND &&
               stHandle.uType != FILE_DEVICE_NAMED_PIPE )
         {

            if( stHandle.uType != FILE_DEVICE_NETWORK_FILE_SYSTEM  )
            {
               // Get the drive name from the dos device name
               if( !GetDrive( (LPCTSTR)stHandle.tcDeviceName, csFileName, true ))
               {
                  output_debug_string( L"GetDrive failed" );
               }
               csFileName += (LPCTSTR)stHandle.tcFileName;
            }
            else
            {
               csFileName = _T("\\");
               csFileName += (LPCTSTR)stHandle.tcFileName;
            }
         }
         else
         {
            continue;
         }
      }
      else
      {
         return;
      }


      csFileName.make_lower();
      // Check whether the file belongs to the specified folder
//       if( -1 == csFileName.Find( csPath ))
//       {
//          if( bShortPath )
//          {
//             // Some times the file name may be in int16_t path form.
//             if( -1 == csFileName.Find( csShortName ))
//             {
//                continue;
//             }
//          }
//          else
//          {
//             continue;
//          }
//       }

      if( 0 != _tcsncmp( lpPath, csFileName, csPath.get_length()))
      {
         if( bShortPath )
         {
            // Some times the file name may be in int16_t path form.
            if( 0 != _tcsncmp( lpShortPath, csFileName, csShortName.get_length()))
            {
               continue;
            }
         }
         else
         {
            continue;
         }
      }
      OF_INFO_t stOFInfo;
      stOFInfo.dwPID = sh.dwProcessId;
      wstring wstrCallback;
      wstrCallback = ::str::international::utf8_to_unicode(csFileName);
      stOFInfo.lpFile = wstrCallback;
      stOFInfo.hFile  = (HANDLE)sh.wValue;
      CallBackProc( stOFInfo, pUserContext );
   }
   delete pSysHandleInformation;

}


void EnumerateLoadedModules( string& csPath, OF_CALLBACK CallBackProc, uint_ptr pUserContext )
{
   string csShortName;
   GetShortPathName( csPath, csShortName.GetBuffer( MAX_PATH), MAX_PATH );
   csShortName.ReleaseBuffer();
   csShortName.make_lower();
   bool bShortPath = false;
   if(  csShortName != csPath && FALSE == csShortName.is_empty())
   {
      bShortPath = true;
   }

   uint32_t dwsize = 300;
   PDWORD pDwId = (PDWORD)new BYTE[dwsize];
   DWORD dwReturned = dwsize;
   // Enum all the process first
   while( 1 )
   {
      EnumProcesses( pDwId, dwsize, &dwReturned );
      if( dwsize > dwReturned  )
      {
         break;
      }
      delete pDwId;
      dwsize += 50;
      pDwId = (PDWORD)new BYTE[dwsize];
   }
   int32_t nCount = dwReturned / sizeof(uint32_t);
   int32_t nItemCount = -1;
   // Enumerate modules of the above process
   for( int32_t nIdx = 0; nIdx < nCount; nIdx++ )
   {
      if( 0 != pDwId[nIdx] )
      {
         HANDLE hModuleSnap = INVALID_HANDLE_VALUE;
         MODULEENTRY32 me32;
         // Take a snapshot of all modules in the specified process.
         hModuleSnap = CreateToolhelp32Snapshot( TH32CS_SNAPMODULE, pDwId[nIdx] );
         if( hModuleSnap == INVALID_HANDLE_VALUE )
         {
            continue;
         }
         me32.dwSize = sizeof( MODULEENTRY32 );
         if( !Module32First( hModuleSnap, &me32 ) )
         {
            CloseHandle( hModuleSnap );
            continue;
         }
         bool bFirst = true;
         PROCESS_INFO_t stInfo;
         do
         {
            string csModule;
            if( bFirst )
            {
               // First module is always the exe name
               bFirst = false;
               if(!LIBCALL(shlwapi,PathFileExistsA)(me32.szExePath))
               {
                  TCHAR tcFileName[MAX_PATH];
                  HANDLE hProcess = OpenProcess( PROCESS_QUERY_INFORMATION|PROCESS_VM_READ, TRUE, pDwId[nIdx] );
                  if( GetProcessImageFileName( hProcess, tcFileName, MAX_PATH ))
                  {
                     GetDrive( tcFileName, csModule, false );
                  }
                  CloseHandle( hProcess );
               }
               else
               {
                  csModule = me32.szExePath;
               }
               csModule.make_lower();
            }
            else
            {
               csModule = me32.szExePath;
               csModule.make_lower();
            }
            if( -1 == csModule.find( csPath ))
            {
               if( bShortPath )
               {
                  if( -1 == csModule.find( csShortName ))
                  {
                     continue;
                  }
               }
               else
               {
                  continue;
               }
            }
            OF_INFO_t stOFInfo;
            stOFInfo.dwPID = pDwId[nIdx];
            wstring wstrCallback;

            wstrCallback = ::str::international::utf8_to_unicode(csModule);

            stOFInfo.lpFile = wstrCallback;
            CallBackProc( stOFInfo, pUserContext );
         }
         while( Module32Next( hModuleSnap, &me32 ) );
         CloseHandle( hModuleSnap );
      }
   }

   delete pDwId;

}



#endif // LINUX





int ftruncate(int file, file_size_t len)
{
   return _chsize_s (file, len);
}





int_bool ensure_file_size_fd(int32_t fd, size_t iSize)
{

   if(ftruncate(fd, iSize) == -1)
      return 0;

   return 1;

}

int_bool ensure_file_size(FILE * file, size_t iSize)
{

   return ensure_file_size_fd(_fileno(file), iSize);

}


int_bool ensure_file_size_handle(HANDLE h, uint64_t iSize)
{

   DWORD dwHi;

   DWORD dwLo = GetFileSize(h, &dwHi);

   if(((uint64_t) dwLo | ((uint64_t)dwHi << 32)) != iSize)
   {

      LONG l = (iSize >> 32) & 0xffffffff;

      if(SetFilePointer(h, iSize & 0xffffffff, &l, SEEK_SET) != (DWORD) (iSize & 0xffffffff))
         return false;

      if(l != ((iSize >> 32) & 0xffffffff))
         return false;

      if(!SetEndOfFile(h))
         return false;

   }


   return 1;

}































int_bool file_set_length(const char * pszName, size_t iSize)
{

   wstring wstr(pszName);

   HANDLE h = ::CreateFileW(wstr, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

   if(h == INVALID_HANDLE_VALUE)
      return false;

   if(!ensure_file_size_handle(h, iSize))
   {

      ::CloseHandle(h);

      return false;

   }

   ::CloseHandle(h);

   return true;

}





int_bool file_move_dup(const char * lpszNewName, const char * lpszOldName)
{

   if(!::MoveFile((LPTSTR)lpszOldName,(LPTSTR)lpszNewName))
      return FALSE;

   return TRUE;

}

int_bool file_delete_dup(const char * lpszFileName)
{


   if(!::DeleteFile((LPTSTR)lpszFileName))
      return FALSE;

   return TRUE;


}




int_bool file_is_equal_path(const char * psz1,const char * psz2)
{

   wstring pwsz1 = ::str::international::utf8_to_unicode(psz1);

   wstring pwsz2 = ::str::international::utf8_to_unicode(psz2);

   unichar * pwszFile1;

   unichar * pwszFile2;

   ::aura::malloc < unichar * > pwszPath1;

   ::aura::malloc < unichar * > pwszPath2;

   pwszPath1.alloc(pwsz1.get_length() * 2 * sizeof(unichar));

   pwszPath2.alloc(pwsz2.get_length() * 2 * sizeof(unichar));

   int32_t iCmp = -1;

   if(GetFullPathNameW(pwsz1, (DWORD)( pwszPath1.m_iSize / sizeof(unichar)), pwszPath1, &pwszFile1))
   {

      if(GetFullPathNameW(pwsz2, (DWORD) (pwszPath2.m_iSize / sizeof(unichar)), pwszPath2, &pwszFile2))
      {

         iCmp = _wcsicmp(pwszPath1, pwszPath2);

      }

   }

   return iCmp == 0;

}





char get_drive_letter(const char * lpDevicePath)
{

   char d = 'A';

   while(d <= 'Z')
   {
      char szDeviceName[3] = {d,':','\0'};
      char szTarget[512] = {0};
      if(QueryDosDevice(szDeviceName,szTarget,511) != 0)
         if(_tcscmp(lpDevicePath,szTarget) == 0)
            return d;
      d++;
   }

   return '\0';

}




memory file_as_memory_dup(const char * path)
{

   memory mem;

   file_get_memory_dup(mem, path);

   return mem;

}



//#include "framework.h"
//#include <Winsvc.h>

//const LPCTSTR DRV_DOS_NAME = _T("\\\\.\\ListFileDrv");
//const LPCTSTR DRV_NAME = _T("ListOpenedFileDrv");
//const LPCTSTR DRV_FILE_NAME = _T("ListOpenedFileDrv.sys");

// Function resolves the fosedevice name to drive name
bool GetDrive(LPCTSTR pszDosName, string& csDrive, bool bDriveLetterOnly)
{
   TCHAR tcDeviceName[50];
   TCHAR tcDrive[3] = _T("A:");

   // Iterating through the drive letters
   for (TCHAR actDrive = _T('A'); actDrive <= _T('Z'); actDrive++)
   {
      tcDrive[0] = actDrive;
      // Query the device for the drive letter
      if (QueryDosDevice(tcDrive, tcDeviceName, 50) != 0)
      {
         // Is this the drive letter we are looking for?
         if (_tcsnicmp(tcDeviceName, pszDosName, _tcslen(tcDeviceName)) == 0)
         {
            if (bDriveLetterOnly)
            {
               csDrive = tcDrive;
            }
            else
            {
               csDrive = pszDosName;
               csDrive.replace(tcDeviceName, tcDrive);
            }
            return TRUE;
         }
      }
   }
   return FALSE;
}

//#ifdef _M_IX86
//#define DRVIER_ID IDR_XPDRIVER32
//#else
//#define DRVIER_ID IDR_XPDRIVER64
//#endif

//#ifdef _M_IX86
#define DRIVER_FILE_NAME_32 _T("\\ListOpenedFileDrv_32.sys")
//#else
#define DRIVER_FILE_NAME_64 _T("\\ListOpenedFileDrv_64.sys")
//#endif

// This Function install the driver and starts it
HANDLE ExtractAndInstallDrv()
{
   SC_HANDLE hSCManager = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
   SC_HANDLE hService = OpenService(hSCManager, DRV_NAME, SERVICE_ALL_ACCESS);
   string csPath;
   if (0 == hService)
   {
      //Service not installed. So install the service.

      /*OSVERSIONINFO info = { 0 };
      info.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
      GetVersionEx(&info);
      int32_t nDriverId = IDR_VISTA_DRIVER;
      if( info.dwMajorVersion == 5 )
      {
      nDriverId = IDR_XPDRIVER;
      }*/


      /*// First extract the resource
      HINSTANCE hModule= __get_instance_handle();
      HRSRC hRsrc = FindResource(hModule, MAKEINTRESOURCE(DRVIER_ID),_T("BINARY"));
      HGLOBAL hDrvRsrc = LoadResource(hModule, hRsrc);
      uint32_t dwDriverSize = SizeofResource(hModule, hRsrc);
      LPVOID lpvDriver = LockResource(hDrvRsrc);
      CFile File;
      if( !File.Open( DRV_FILE_NAME, CFile::modeCreate|CFile::modeWrite ))
      {
      return 0;
      }
      File.Write( lpvDriver, dwDriverSize );
      csPath = File.GetFilePath();
      File.Close();*/


      HMODULE hModule = GetModuleHandle(_T("core.dll"));
      if (!hModule)
      {
         output_debug_string(L"GetModuleHandle(_T(\"core.dll\")); failed");
         return 0;
      }
      string csFilePath;
      LPTSTR lpPath = csFilePath.GetBuffer(MAX_PATH);
      GetModuleFileName(hModule, lpPath, MAX_PATH);
      LIBCALL(shlwapi, PathRemoveFileSpecA)(lpPath);
      csFilePath.ReleaseBuffer();
      if (IsWow64())
      {
         csFilePath += DRIVER_FILE_NAME_64;
      }
      else
      {
         csFilePath += DRIVER_FILE_NAME_32;
      }

      if (!LIBCALL(shlwapi, PathFileExistsA)(csFilePath))
      {
         simple_message_box(NULL, "Cannot find driver " + csFilePath, "Cannot find driver " + csFilePath, MB_OK);
         return 0;
      }



      hService = CreateService(hSCManager, DRV_NAME, DRV_NAME, SERVICE_ALL_ACCESS,
                               SERVICE_KERNEL_DRIVER, SERVICE_DEMAND_START, SERVICE_ERROR_NORMAL,
                               csFilePath, NULL, NULL, NULL, NULL, NULL);

      if (0 == hService)
      {
         output_debug_string(L"CreateService failed");
         CloseServiceHandle(hSCManager);
         return 0;
      }
   }

   if (!StartService(hService, 0, NULL))
   {
      uint32_t dwLastError = get_last_error();
      if (dwLastError != ERROR_SERVICE_ALREADY_RUNNING)
      {
         DeleteService(hService);
         CloseServiceHandle(hService);
         CloseServiceHandle(hSCManager);
         //DeleteFile( csPath );
         output_debug_string(L"StartService failed");
         return 0;
      }

   }
   // Delete the temp file...
   //DeleteFile( csPath );
   HANDLE hFile = CreateFile(DRV_DOS_NAME, GENERIC_READ | GENERIC_WRITE,
                             FILE_SHARE_READ | FILE_SHARE_WRITE, 0,
                             OPEN_EXISTING, FILE_FLAG_OVERLAPPED, 0);
   if (INVALID_HANDLE_VALUE == hFile)
   {
      hFile = 0;
      SERVICE_STATUS  stSrvStatus = { 0 };
      ControlService(hService, SERVICE_CONTROL_STOP, &stSrvStatus);
   }
   CloseServiceHandle(hService);
   CloseServiceHandle(hSCManager);
   return hFile;
}

// Function stops the service and then deletes it.
int_bool StopAndUninstallDrv(HANDLE hDrvHandle)
{
   CloseHandle(hDrvHandle);
   SC_HANDLE hSCManager = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
   SC_HANDLE hService = OpenService(hSCManager, DRV_NAME, SERVICE_ALL_ACCESS);
   SERVICE_STATUS  stSrvStatus = { 0 };
   ControlService(hService, SERVICE_CONTROL_STOP, &stSrvStatus);
   int_bool bDeleted = DeleteService(hService);
   CloseServiceHandle(hService);
   CloseServiceHandle(hSCManager);
   return bDeleted;
}




#ifdef WINDOWSEX

int_bool IsWow64()
{

   int_bool bIsWow64 = FALSE;

   if (!IsWow64Process(GetCurrentProcess(), &bIsWow64))
   {
      return FALSE;
   }

   return bIsWow64 != FALSE;

}

#endif







int_bool EnableTokenPrivilege(LPCTSTR pszPrivilege)
{
   // do it only once
   static int_bool bEnabled = FALSE;
   if (bEnabled)
   {
      return TRUE;
   }
   bEnabled = TRUE;

   HANDLE hToken = 0;
   TOKEN_PRIVILEGES tkp = { 0 };

   // Get a token for this process.
   if (!OpenProcessToken(GetCurrentProcess(),
                         TOKEN_ADJUST_PRIVILEGES |
                         TOKEN_QUERY, &hToken))
   {
      return FALSE;
   }

   // Get the LUID for the privilege.
   if (LookupPrivilegeValue(NULL, pszPrivilege,
                            &tkp.Privileges[0].Luid))
   {
      tkp.PrivilegeCount = 1;  // one privilege to set
      tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

      // set the privilege for this process.
      AdjustTokenPrivileges(hToken, FALSE, &tkp, 0,
                            (PTOKEN_PRIVILEGES)NULL, 0);

      if (get_last_error() != ERROR_SUCCESS)
         return FALSE;

      return TRUE;
   }

   return FALSE;
}




CLASS_DECL_AURA bool read_resource_as_memory_dup(memory & m, HINSTANCE hinstance, UINT nID, LPCTSTR lpcszType)
{

   HRSRC hrsrc = FindResource(hinstance, MAKEINTRESOURCE(nID), lpcszType);
   HGLOBAL hglobalResource;
   uint32_t dwResourceSize;
   int_bool bOk;
   UINT FAR* pResource;

   if (hrsrc == NULL)
      return FALSE;

   hglobalResource = LoadResource(hinstance, hrsrc);

   if (hglobalResource == NULL)
      return FALSE;

   dwResourceSize = SizeofResource(hinstance, hrsrc);

   if (hglobalResource != NULL)
   {

      bOk = FALSE;

      pResource = (UINT FAR*) LockResource(hglobalResource);

      m.assign(pResource, dwResourceSize);

      FreeResource(hglobalResource);

      return bOk;
   }

   return FALSE;

}
