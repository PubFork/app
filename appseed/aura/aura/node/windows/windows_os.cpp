#include "framework.h"
#include <wincred.h>
#include <wtsapi32.h>

#include <shobjidl.h>

CREDUIAPI
BOOL
WINAPI
CredPackAuthenticationBufferWfoo(
_In_ DWORD                                      dwFlags,
_In_ LPWSTR                                     pszUserName,
_In_ LPWSTR                                     pszPassword,
_Out_writes_bytes_opt_(*pcbPackedCredentials) PBYTE   pPackedCredentials,
_Inout_ DWORD*                                  pcbPackedCredentials
);


//#include <Wtsapi32.h>
//#include <Psapi.h>
//#include <WinCred.h>

CLASS_DECL_AURA HBITMAP get_icon_hbitmap(HICON hICON);

namespace windows
{


   os::os(::aura::application * papp) :
      object(papp),
      ::aura::os(papp)
   {
   }


   os::~os()
   {
   }


   string os::get_command_line()
   {

      return GetCommandLineW();

   }


   bool os::shutdown(bool bIfPowerOff)
   {
      bool retval = true;
      HANDLE hToken;
      TOKEN_PRIVILEGES tkp;
      if (!OpenProcessToken(GetCurrentProcess(),
                            TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken))
         return false;
      LookupPrivilegeValue(NULL, SE_SHUTDOWN_NAME, &tkp.Privileges[0].Luid);
      tkp.PrivilegeCount = 1;
      tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
      AdjustTokenPrivileges(hToken, FALSE, &tkp, 0, (PTOKEN_PRIVILEGES) NULL, 0);
      if (bIfPowerOff)
         retval = ExitWindowsEx(EWX_POWEROFF, 0) != FALSE;
      else
         retval = ExitWindowsEx(EWX_SHUTDOWN, 0) != FALSE;

      //reset the previlages
      tkp.Privileges[0].Attributes = 0;
      AdjustTokenPrivileges(hToken, FALSE, &tkp, 0, (PTOKEN_PRIVILEGES) NULL, 0);
      return retval;
   }

   bool os::reboot()
   {
      HANDLE hToken;
      TOKEN_PRIVILEGES tkp;
      if (!OpenProcessToken(GetCurrentProcess(),
                            TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken))
         return false;
      if(!LookupPrivilegeValue(NULL, SE_SHUTDOWN_NAME, &tkp.Privileges[0].Luid))
      {
         TRACELASTERROR();
         return false;
      }
      tkp.PrivilegeCount = 1;
      tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
      if(!AdjustTokenPrivileges(hToken, FALSE, &tkp, 0, (PTOKEN_PRIVILEGES) NULL, 0))
      {
         TRACELASTERROR();
         return false;
      }
      if (get_last_error() == ERROR_NOT_ALL_ASSIGNED)
      {
         return false;
      }
      if(!LookupPrivilegeValue(NULL, SE_REMOTE_SHUTDOWN_NAME, &tkp.Privileges[0].Luid))
      {
         TRACELASTERROR();
         return false;
      }
      tkp.PrivilegeCount = 1;
      tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
      if(!AdjustTokenPrivileges(hToken, FALSE, &tkp, 0, (PTOKEN_PRIVILEGES) NULL, 0))
      {
         TRACELASTERROR();
         return false;
      }
      if (get_last_error() == ERROR_NOT_ALL_ASSIGNED)
      {
         return false;
      }


      if(!LIBCALL(wtsapi32,WTSShutdownSystem)(WTS_CURRENT_SERVER_HANDLE,WTS_WSD_REBOOT))
      {
         TRACELASTERROR();
         return false;
      }
      /*if (!ExitWindowsEx(EWX_REBOOT | EWX_FORCE,
      SHTDN_REASON_MAJOR_SOFTWARE | SHTDN_REASON_MINOR_INSTALLATION))
      {
      DWORD dwLastError = ::get_last_error();
      return false;
      }*/
      //reset the previlages
      tkp.Privileges[0].Attributes = 0;
      AdjustTokenPrivileges(hToken, FALSE, &tkp, 0, (PTOKEN_PRIVILEGES) NULL, 0);
      return true;
   }

   void os::terminate_processes_by_title(const char * pszName)
   {
      DWORD dwPid;
      while(get_pid_by_title(pszName, dwPid))
      {
         HANDLE hProcess = OpenProcess( PROCESS_QUERY_INFORMATION |
                                        PROCESS_VM_READ,
                                        FALSE, dwPid );
         TerminateProcess(hProcess, (UINT) -1);
         CloseHandle(hProcess);
         /*::EnumWindows((WNDENUMPROC)
         CKillProcessHelper::TerminateAppEnum,
         (LPARAM) dwId);
         // Wait on the handle. If it signals, great.

         //If it times out, then you kill it.

         if(WaitForSingleObject(hProcess, 5000)
         !=WAIT_OBJECT_0)
         bResult = TerminateProcess(hProcess,0);
         else
         bResult = TRUE;
         CloseHandle(hProcess);
         return bResult == TRUE;*/

      }
   }

   bool os::get_pid_by_path(const char * pszName, DWORD & dwPid)
   {
      uint_array dwa;
      get_all_processes(dwa);
      for(int32_t i = 0; i < dwa.get_count(); i++)
      {
         if(get_process_path(dwa[i]).compare_ci(pszName) == 0)
         {
            dwPid = dwa[i];
            return true;
         }
      }
      return false;
   }

   bool os::get_pid_by_title(const char * pszName, DWORD & dwPid)
   {
      uint_array dwa;
      get_all_processes(dwa);
      for(int32_t i = 0; i < dwa.get_count(); i++)
      {
         if(get_process_path(dwa[i]).title().compare_ci(pszName) == 0)
         {
            dwPid = dwa[i];
            return true;
         }
      }
      return false;
   }


   int os::get_pid()
   {

      return (int) ::get_current_process_id();

   }




   ::file::path os::get_process_path(DWORD dwPid)
   {
      string strName = ":<unknown>";
      // get a handle to the process.
      HANDLE hProcess = OpenProcess( PROCESS_QUERY_INFORMATION |
                                     PROCESS_VM_READ,
                                     FALSE, dwPid );

      // get the process name.

      if (NULL != hProcess )
      {
         HMODULE hMod;
         DWORD cbNeeded;

         if(EnumProcessModules( hProcess, &hMod, sizeof(hMod),
                                &cbNeeded) )
         {
            strName = get_module_path(hMod);
         }
      }

      CloseHandle( hProcess );
      return strName;
   }

   void os::get_all_processes(uint_array & dwa )
   {
      dwa.allocate(0);
      DWORD cbNeeded = 0;
      while(cbNeeded == natural(dwa.get_count()))
      {
         dwa.allocate(dwa.get_count() + 1024);
         if(!EnumProcesses(
               (DWORD *) dwa.get_data(),
               (DWORD) (dwa.get_count() * sizeof(DWORD)),
               &cbNeeded))
         {
            return;
         }
         dwa.allocate(cbNeeded / sizeof(DWORD));
      }
   }

   ::file::path os::get_module_path(HMODULE hmodule)
   {
      wstring wstrPath;
      DWORD dwSize = 1;
      while(natural(wstrPath.get_length() + 1) == dwSize)
      {
         dwSize = ::GetModuleFileNameW(
                  hmodule,
                  wstrPath.alloc(dwSize + 1024),
                  (dwSize + 1024));
         wstrPath.release_buffer();
      }
      return ::str::international::unicode_to_utf8(wstrPath);
   }


   bool os::connection_settings_get_auto_detect()
   {

      registry::Key key1;

      key1.OpenKey(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\Internet Settings\\Connections", false);

      memory mem;

      key1.QueryValue("DefaultConnectionSettings", mem);

      bool bAutoDetect = (((LPBYTE) mem.get_data())[8] & 0x08) != 0;

      return bAutoDetect;

   }


   string os::connection_settings_get_auto_config_url()
   {

      registry::Key key;

      key.OpenKey(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\Internet Settings", false);

      string strUrl;

      key.QueryValue("AutoConfigURL", strUrl);

      return strUrl;

   }

   bool os::local_machine_set_run(const char * pszKey, const char * pszCommand, bool bSet)
   {


      registry::Key keyKar(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", true);


      if (bSet)
      {

         keyKar.SetValue(pszKey, string(pszCommand));

      }
      else
      {

         keyKar.DeleteValue(pszKey);

      }

      return true;

   }


   bool os::local_machine_set_run_once(const char * pszKey, const char * pszCommand, bool bSet)
   {


      registry::Key keyKar(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\RunOnce", true);


      if (bSet)
      {

         keyKar.SetValue(pszKey, string(pszCommand));

      }
      else
      {

         keyKar.DeleteValue(pszKey);

      }
      return false;

   }

   bool os::current_user_set_run(const char * pszKey, const char * pszCommand, bool bSet)
   {

      registry::Key keyKar(HKEY_CURRENT_USER, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", true);

      if (bSet)
      {

         keyKar.SetValue(pszKey, string(pszCommand));

      }
      else
      {

         keyKar.DeleteValue(pszKey);

      }

      return false;

   }

   bool os::current_user_set_run_once(const char * pszKey, const char * pszCommand, bool bSet)
   {


      registry::Key keyKar(HKEY_CURRENT_USER, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\RunOnce", true);


      if (bSet)
      {

         keyKar.SetValue(pszKey, string(pszCommand));

      }
      else
      {

         keyKar.DeleteValue(pszKey);

      }
      return false;

   }


   bool os::defer_register_ca2_plugin_for_mozilla()
   {

      registry::Key keyPlugins;

      if(keyPlugins.OpenKey(HKEY_LOCAL_MACHINE, "SOFTWARE\\MozillaPlugins", true))
      {

         registry::Key keyPlugin;

         if(keyPlugin.OpenKey(keyPlugins, "@ca2.cc/npca2", true))
         {

            keyPlugin.SetValue("Description", "ca2 plugin for NPAPI");
            keyPlugin.SetValue("Path", System.dir().ca2module() /"npca2.dll");
            keyPlugin.SetValue("ProductName", "ca2 plugin for NPAPI");
            keyPlugin.SetValue("Vendor", "ca2 Desenvolvimento de Software Ltda.");
            keyPlugin.SetValue("Version", Application.file().as_string(System.dir().install()/"appdata/x86/ca2_build.txt"));

            registry::Key keyApplicationCa2;

            if(keyApplicationCa2.OpenKey(keyPlugin, "application/core", true))
            {

               keyApplicationCa2.SetValue("Description", "core Document");

            }

         }

      }

      return true;

   }

   bool os::file_extension_get_open_with_list_keys(stringa & straKey, const char * pszExtension)
   {

      string strExt;

      strExt = ".";
      strExt += pszExtension;

      string strOpenWithKey;
      strOpenWithKey = strExt + "\\OpenWithList";

      registry::Key key;

      key.OpenKey(HKEY_CLASSES_ROOT, strOpenWithKey, false);

      key.EnumKey(straKey);

      return true;

   }


   bool os::file_extension_get_open_with_list_commands(stringa & straCommand, const char * pszExtension)
   {

      stringa straKey;

      if(!file_extension_get_open_with_list_keys(straKey, pszExtension))
         return false;


      return true;

   }

   bool os::file_association_set_default_icon(const char * pszExtension, const char * pszExtensionNamingClass, const char * pszIconPath)
   {


      string strExtensionNamingClass(pszExtensionNamingClass);

      registry::Key keyLink3(HKEY_CLASSES_ROOT, strExtensionNamingClass, true);
      keyLink3.SetValue("DefaultIcon", pszIconPath);


      return false;

   }


   bool os::file_association_set_shell_open_command(const char * pszExtension, const char * pszExtensionNamingClass,  const char * pszCommand, const char * pszParam)
   {

      string strExt;

      strExt += pszExtension;

      string strExtensionNamingClass(pszExtensionNamingClass);

      registry::Key key(HKEY_CLASSES_ROOT, strExt, true);
      key.SetValue(NULL, strExtensionNamingClass);

      registry::Key keyLink3(HKEY_CLASSES_ROOT, strExtensionNamingClass + "\\shell", true);
      keyLink3.SetValue("", "open");

      registry::Key keyLink2(keyLink3, "open", true);
      keyLink2.SetValue("", "");

      registry::Key keyLink1(keyLink2, "command", true);

      string strCommand(pszCommand);

      strCommand = solve_relative_compressions(strCommand);

      string strFormat;

      strFormat.Format("\"%s\" %s", strCommand, pszParam);

      keyLink1.SetValue("", strFormat);

      return true;

   }

   bool os::file_association_get_shell_open_command(const char * pszExtension, string & strExtensionNamingClass, string & strCommand, string & strParam)
   {

      string strExt;

      strExt = ".";
      strExt += pszExtension;

      registry::Key key(HKEY_CLASSES_ROOT, strExt, false);
      if(!key.QueryValue(NULL, strExtensionNamingClass))
         return false;

      registry::Key keyLink(HKEY_CLASSES_ROOT, strExtensionNamingClass + "\\shell\\open\\command", false);

      string strFormat;
      if(keyLink.QueryValue(NULL, strFormat))
      {

         const char * psz = strFormat;

         try
         {

            strCommand = ::str::consume_quoted_value(psz);
            ::str::consume_spaces(psz);
            ::str::consume(psz, "\"%L\"");
            strParam = psz;

         }
         catch(...)
         {
         }


      }

      return true;

   }

   bool os::open_in_ie(const char * lpcsz)
   {

      registry reg;
      string str;
      string str2;
      string strCommand;
      registry::Key key;
      if(key.OpenKey(HKEY_CLASSES_ROOT, ".html", false))
      {
         if(reg.RegQueryValue(key.m_hkey, "", str))
         {
            if(key.OpenKey(HKEY_CLASSES_ROOT, ".html\\shell\\opennew\\command", false))
            {
               string str;
               if(reg.RegQueryValue(HKEY_CLASSES_ROOT, str, str2))
               {
                  string strCommand(str2);
                  strCommand.replace("%1", lpcsz);
                  WinExec(strCommand,SW_SHOW);
               }
            }
            else
            {
               if(key.OpenKey(HKEY_CLASSES_ROOT, str, false))
               {
                  str += "\\shell\\opennew\\command";
                  if(key.OpenKey(HKEY_CLASSES_ROOT, str, false))
                  {
                     if(reg.RegQueryValue(key.m_hkey, "", str2))
                     {
                        string strCommand(str2);
                        strCommand.replace("%1", lpcsz);
                        WinExec(strCommand,SW_SHOW);
                     }
                  }
               }
            }
         }
      }

      return true;

   }


   //------------------------------------------------------------------------
   // The following function retrieves the identity of the current user.
   // This is a helper function and is not part of the Windows Biometric
   // Framework API.
   //
   struct TOKEN_INFO
   {
      TOKEN_USER tokenUser;
      BYTE buffer[SECURITY_MAX_SID_SIZE];
   };
   HRESULT GetCurrentUserIdentity(TOKEN_INFO & tokenInfo)
   {
      // Declare variables.
      bool bOk = true;
      HANDLE tokenHandle = NULL;
      DWORD bytesReturned = 0;


      // Open the access token associated with the
      // current process
      if(!OpenProcessToken(
            GetCurrentProcess(),            // Process handle
            TOKEN_READ,                     // Read access only
            &tokenHandle))                  // Access token handle
      {
         DWORD win32Status = get_last_error();
         debug_print("Cannot open token handle: %d\n",win32Status);
         bOk = false;
      }

      // Zero the tokenInfoBuffer structure.
      ZeroMemory(&tokenInfo,sizeof(tokenInfo));

      // Retrieve information about the access token. In this case,
      // retrieve a SID.
      if(!GetTokenInformation(
            tokenHandle,                    // Access token handle
            TokenUser,                      // User for the token
            &tokenInfo.tokenUser,     // Buffer to fill
            sizeof(tokenInfo),        // Size of the buffer
            &bytesReturned))                // Size needed
      {
         DWORD win32Status = get_last_error();
         debug_print("Cannot query token information: %d\n",win32Status);
         bOk = false;
      }

      if(tokenHandle != NULL)
      {
         CloseHandle(tokenHandle);
      }

      return bOk;
   }
   BOOL
   GetAccountSid(
   LPTSTR SystemName,
   LPTSTR AccountName,
   PSID *Sid
   )
   {
      LPTSTR ReferencedDomain=NULL;
      DWORD cbSid=128;    // initial allocation attempt
      DWORD cchReferencedDomain=16; // initial allocation size
      SID_NAME_USE peUse;
      BOOL bSuccess=FALSE; // assume this function will fail

      __try
      {

         //
         // initial memory allocations
         //
         if((*Sid=HeapAlloc(
                  GetProcessHeap(),
                  0,
                  cbSid
                  )) == NULL) __leave;

         if((ReferencedDomain=(LPTSTR)HeapAlloc(
                              GetProcessHeap(),
                              0,
                              cchReferencedDomain * sizeof(TCHAR)
                              )) == NULL) __leave;

         //
         // Obtain the SID of the specified account on the specified system.
         //
         while(!LookupAccountName(
               SystemName,         // machine to lookup account on
               AccountName,        // account to lookup
               *Sid,               // SID of interest
               &cbSid,             // size of SID
               ReferencedDomain,   // domain account was found on
               &cchReferencedDomain,
               &peUse
               ))
         {
            if(get_last_error() == ERROR_INSUFFICIENT_BUFFER)
            {
               //
               // reallocate memory
               //
               if((*Sid=HeapReAlloc(
                        GetProcessHeap(),
                        0,
                        *Sid,
                        cbSid
                        )) == NULL) __leave;

               if((ReferencedDomain=(LPTSTR)HeapReAlloc(
                                    GetProcessHeap(),
                                    0,
                                    ReferencedDomain,
                                    cchReferencedDomain * sizeof(TCHAR)
                                    )) == NULL) __leave;
            }
            else __leave;
         }

         //
         // Indicate success.
         //
         bSuccess=TRUE;

      } // finally
      __finally
      {

         //
         // Cleanup and indicate failure, if appropriate.
         //

         HeapFree(GetProcessHeap(),0,ReferencedDomain);

         if(!bSuccess)
         {
            if(*Sid != NULL)
            {
               HeapFree(GetProcessHeap(),0,*Sid);
               *Sid = NULL;
            }
         }

      } // finally

      return bSuccess;
   }























   bool getCredentialsForService(::aura::application * papp, const string & strService,WCHAR * szUsername,WCHAR *szPassword)
   {






      HRESULT hr = S_OK;
      DWORD   dwResult;
      sec_cotaskptr < PVOID > pvInAuthBlob;
      sec_cotaskptr < PVOID > pvAuthBlob;
      CREDUI_INFOW ui;
      ULONG   ulAuthPackage = 0;
      BOOL    fSave = FALSE;
      WCHAR szDomainAndUser[CREDUI_MAX_USERNAME_LENGTH + CREDUI_MAX_DOMAIN_TARGET_LENGTH + 1];
      WCHAR szDomain[CREDUI_MAX_DOMAIN_TARGET_LENGTH + 1];
//      TOKEN_INFO ti;

      DWORD maxLenName = CREDUI_MAX_USERNAME_LENGTH + 1;
      DWORD maxLenPass = CREDUI_MAX_PASSWORD_LENGTH + 1;
      DWORD maxLenDomain = CREDUI_MAX_DOMAIN_TARGET_LENGTH + 1;

      HICON hicon = NULL;


      // Display a dialog box to request credentials.
      ZERO(ui);
      ui.cbSize = sizeof(ui);
      ui.hwndParent = NULL;



      // Retrieve the user name and domain name.
//      SID_NAME_USE    SidUse;
      DWORD           cchTmpUsername = CREDUI_MAX_USERNAME_LENGTH +1;
      DWORD           cchTmpDomain = CREDUI_MAX_DOMAIN_TARGET_LENGTH + 1;
      DWORD           cchDomainAndUser = CREDUI_MAX_USERNAME_LENGTH + CREDUI_MAX_DOMAIN_TARGET_LENGTH + 1;

      wstring wstrCaption("\"ca2 : " + strService + "\" Authentication");
      wstring wstrMessage("The Service \"ca2 : " + strService + "\" requires current user password for installing Windows Service.");

      DWORD lenUserName = CREDUI_MAX_USERNAME_LENGTH + 1;

      //::GetUserNameW(szUsername,&lenUserName);


      DWORD dwLastError = 0;



      bool bOk;


      //if(!GetCurrentUserIdentity(ti))
      //   return false;
      ////szDomain[0] ='.';
      ////         szDomain[1] ='\0';
      //if(!LookupAccountSidW(
      //   NULL,             // Local computer
      //   ti.tokenUser.User.Sid,             // Security identifier for user
      //   szUsername,       // User name
      //   &cchTmpUsername,  // Size of user name
      //   szDomain,         // Domain name
      //   &cchTmpDomain,    // Size of domain name
      //   &SidUse))         // Account type
      //{
      //   dwResult = get_last_error();
      //   debug_print("\n getCredentialsForService LookupAccountSidLocalW failed: win32 error = 0x%x\n",dwResult);
      //   return false;
      //}

      ULONG l = sizeof(szDomainAndUser) / sizeof(WCHAR);

      ::GetUserNameExW(NameSamCompatible,szDomainAndUser,&l);

      // Combine the domain and user names.
      /*swprintf_s(
         szDomainAndUser,
         cchDomainAndUser,
         L"%s\\%s",
         szDomain,
         szUsername);*/
      zero(szPassword,CREDUI_MAX_PASSWORD_LENGTH);

      // Call CredPackAuthenticationBufferW once to determine the size,
      // in bytes, of the authentication buffer.

      if(!LIBCALL(credui,CredPackAuthenticationBufferW)(
            0,                // Reserved
            szDomainAndUser,  // Domain\User name
            szPassword,       // User Password
            NULL,             // Packed credentials
            &pvInAuthBlob.m_size)    // Size, in bytes, of credentials
            && get_last_error() != ERROR_INSUFFICIENT_BUFFER)
      {
         dwResult = get_last_error();
         debug_print("\n getCredentialsForService CredPackAuthenticationBufferW (1) failed: win32 error = 0x%x\n",dwResult);
         return false;
      }

      // Allocate memory for the input buffer.
      pvInAuthBlob.alloc();

      if(pvInAuthBlob.is_null())
      {

         debug_print("\n getCredentialsForService CoTaskMemAlloc() Out of memory.\n");

         return false;

      }

      // Call CredPackAuthenticationBufferW again to retrieve the
      // authentication buffer.
      if(!LIBCALL(credui,CredPackAuthenticationBufferW)(
            0,
            szDomainAndUser,
            szPassword,
            (PBYTE)pvInAuthBlob.m_p,
            &pvInAuthBlob.m_size))
      {
         dwResult = get_last_error();
         debug_print("\n CredPackAuthenticationBufferW (2) failed: win32 error = 0x%x\n",dwResult);
      }


      ui.pszCaptionText = wstrCaption;
      ui.pszMessageText = wstrMessage;
      hicon = (HICON) ::LoadImageW(::GetModuleHandle(NULL),MAKEINTRESOURCEW(1),IMAGE_ICON,48,48,LR_DEFAULTCOLOR);


      if(hicon != NULL)
      {

         ui.hbmBanner = get_icon_hbitmap(hicon);

         ::DeleteObject(hicon);

      }

retry:

      dwResult = LIBCALL(credui,CredUIPromptForWindowsCredentialsW)(
                 &ui,             // Customizing information
                 dwLastError,               // Error code to display
                 &ulAuthPackage,  // Authorization package
                 pvInAuthBlob,    // Credential byte array
                 pvInAuthBlob.m_size,    // Size of credential input buffer
                 &pvAuthBlob,     // Output credential byte array
                 &pvAuthBlob.m_size,     // Size of credential byte array
                 &fSave,          // Select the save check box.
                 //CREDUIWIN_SECURE_PROMPT |
                 CREDUIWIN_IN_CRED_ONLY |
                 CREDUIWIN_ENUMERATE_CURRENT_USER
                 );


      if(dwResult == NO_ERROR)
      {

         DWORD lenName = maxLenName;
         DWORD lenDomain = maxLenDomain;
         DWORD lenPass = maxLenPass;

         bOk = LIBCALL(credui, CredUnPackAuthenticationBufferW)(CRED_PACK_PROTECTED_CREDENTIALS,
               pvAuthBlob,
               pvAuthBlob.m_size,
               szUsername,
               &lenName,
               szDomain,
               &lenDomain,
               szPassword,
               &lenPass) != FALSE;


         if(!bOk)
         {
            dwLastError = ::get_last_error();
            goto retry;
         }

         //wcscpy(szDomainAndUser,szUsername);

         ::GetUserNameExW(NameSamCompatible,szDomainAndUser,&l);

         bOk = LIBCALL(credui,CredUIParseUserNameW)(
               szDomainAndUser,
               szUsername,
               CREDUI_MAX_USERNAME_LENGTH,
               szDomain,
               CREDUI_MAX_DOMAIN_TARGET_LENGTH
               ) == NO_ERROR ;

         if(!bOk)
         {
            dwLastError = ::get_last_error();
            goto retry;
         }

         HANDLE h;



         if(::LogonUserW(
               szUsername,
               szDomain,
               szPassword,
               LOGON32_LOGON_SERVICE,
               LOGON32_PROVIDER_DEFAULT,
               &h))
         {
            ::CloseHandle(h);
         }
         else
         {
            dwLastError = ::get_last_error();
            goto retry;
         }

         wcscpy(szUsername,szDomainAndUser);


      }
      else
      {

         if(dwResult != ERROR_CANCELLED)
            goto retry;

         hr = HRESULT_FROM_WIN32(dwResult);
         bOk = false;
      }

      if(ui.hbmBanner != NULL)
      {

         ::DeleteObject(ui.hbmBanner);

      }

      return bOk;

   }


































   string os::calc_service_name(::aura::application * papp)
   {

      if(papp->m_strAppName.is_empty()
            || papp->m_strAppName.compare_ci("bergedge") == 0
            || !papp->is_serviceable())
         return "";

      string strServiceName = papp->m_strAppId;

      strServiceName.replace("/","-");

      strServiceName.replace("\\","-");

      return strServiceName;

   }





   bool os::create_service(::aura::application * papp)
   {

      string strServiceName = calc_service_name(papp);

      if(strServiceName.is_empty())
         return false;

      SC_HANDLE hdlSCM = OpenSCManagerW(0, 0, SC_MANAGER_CREATE_SERVICE);

      if(hdlSCM == 0)
      {

         DWORD dwLastError = ::get_last_error();

         return false;

      }

      string strDisplayName(strServiceName);

      strDisplayName.replace("-"," ");

      string strExe(strServiceName);

      strExe.replace("-","_");

      strExe += ".exe";

      string strCalling = Sys(papp).dir().module() / strExe + " : service";

      if(System.handler()->m_varTopicQuery.has_property("no_remote_simpledb"))
      {

         strCalling += " no_remote_simpledb";

      }

      WCHAR * pname = NULL;
      WCHAR * ppass = NULL;

      WCHAR pszName[CREDUI_MAX_USERNAME_LENGTH + CREDUI_MAX_DOMAIN_TARGET_LENGTH + 1];
      WCHAR pszPass[CREDUI_MAX_PASSWORD_LENGTH + 1];


      if(App(papp).is_user_service())
      {

         if(getCredentialsForService(papp, papp->m_strAppId,pszName,pszPass))
         {

            pname = pszName;
            ppass = pszPass;

         }
         else
         {

            return false;

         }

      }

      return create_service(strServiceName,strDisplayName,strCalling,pname,ppass);

   }


   bool os::remove_service(::aura::application * papp)
   {

      string strServiceName = calc_service_name(papp);

      if(strServiceName.is_empty())
         return false;

      return remove_service(strServiceName);

   }

   bool os::start_service(::aura::application * papp)
   {

      string strServiceName = calc_service_name(papp);

      if(strServiceName.is_empty())
         return false;

      return start_service(strServiceName);

   }

   bool os::create_service(const string & strServiceName,const string & strDisplayName,const string & strCommand,const string & strUser,const string & strPass)
   {

      if(strServiceName.is_empty())
         return false;

      SC_HANDLE hdlSCM = OpenSCManagerW(0,0,SC_MANAGER_CREATE_SERVICE);

      if(hdlSCM == 0)
      {
         //::get_last_error()
         return false;
      }

      WCHAR pszName[CREDUI_MAX_USERNAME_LENGTH + CREDUI_MAX_DOMAIN_TARGET_LENGTH + 1];
      WCHAR pszPass[CREDUI_MAX_PASSWORD_LENGTH + 1];

      wcscpy(pszName,wstring(strUser));
      wcscpy(pszPass,wstring(strPass));

      SC_HANDLE hdlServ = ::CreateServiceW(
                          hdlSCM,                    // SCManager database
                          wstring(strServiceName),
                          wstring(strDisplayName),        // service name to display
                          STANDARD_RIGHTS_REQUIRED,  // desired access
                          SERVICE_WIN32_OWN_PROCESS, // service type
                          SERVICE_AUTO_START,      // start type
                          SERVICE_ERROR_NORMAL,      // error control type
                          wstring(strCommand),                   // service's binary Path name
                          0,                      // no load ordering group
                          0,                      // no tag identifier
                          0,                      // no dependencies
                          strUser.has_char() ? pszName : NULL,                      // LocalSystem account
                          strPass.has_char() ? pszPass : NULL);                     // no password


      if(!hdlServ)
      {
         DWORD Ret = ::get_last_error();
         TRACELASTERROR();
         CloseServiceHandle(hdlSCM);
         return false;
      }

      SecureZeroMemory(pszName,sizeof(pszName));
      SecureZeroMemory(pszPass,sizeof(pszPass));


      CloseServiceHandle(hdlServ);
      CloseServiceHandle(hdlSCM);

      return true;

   }


   bool os::remove_service(const string & strServiceName)
   {

      if(strServiceName.is_empty())
         return false;

      SC_HANDLE hdlSCM = OpenSCManagerW(0,0,SC_MANAGER_ALL_ACCESS);

      if(hdlSCM == 0)
      {
         //::get_last_error();
         return false;
      }


      SC_HANDLE hdlServ = ::OpenServiceW(
                          hdlSCM,                    // SCManager database
                          wstring(strServiceName),
                          DELETE);

      if(!hdlServ)
      {
         DWORD Ret = ::get_last_error();
         CloseServiceHandle(hdlSCM);
         if(Ret == 1060) // O serviço já não existe. Service already doesn't exist.
            return true; // do self-healing
         return false;
      }

      if(!::DeleteService(hdlServ))
      {
         DWORD Ret = ::get_last_error();
         CloseServiceHandle(hdlServ);
         CloseServiceHandle(hdlSCM);
         return false;
      }

      CloseServiceHandle(hdlServ);

      CloseServiceHandle(hdlSCM);

      return true;

   }

   bool os::stop_service(::aura::application * papp)
   {

      string strServiceName = calc_service_name(papp);

      if(strServiceName.is_empty())
         return false;

      return stop_service(strServiceName);

   }


   bool os::start_service(const string & strServiceName)
   {

      if(strServiceName.is_empty())
         return false;

      SC_HANDLE hdlSCM = OpenSCManagerW(0,0,SC_MANAGER_ALL_ACCESS);

      if(hdlSCM == 0)
      {
         //::get_last_error();
         return false;
      }

      SC_HANDLE hdlServ = ::OpenServiceW(
                          hdlSCM,                    // SCManager database
                          wstring(strServiceName),
                          SERVICE_START);                     // no password


      if(!hdlServ)
      {
         CloseServiceHandle(hdlSCM);
         //Ret = ::get_last_error();
         return FALSE;
      }

      bool bOk = StartService(hdlServ,0,NULL) != FALSE;

      CloseServiceHandle(hdlServ);
      CloseServiceHandle(hdlSCM);

      return bOk != FALSE;
   }

   bool os::stop_service(const string & strServiceName)
   {

      if(strServiceName.is_empty())
         return false;

      SC_HANDLE hdlSCM = OpenSCManagerW(0,0,SC_MANAGER_ALL_ACCESS);

      if(hdlSCM == 0)
      {
         //::get_last_error();
         return false;
      }

      SC_HANDLE hdlServ = ::OpenServiceW(
                          hdlSCM,                    // SCManager database
                          wstring(strServiceName),
                          SERVICE_STOP);                     // no password

      if(!hdlServ)
      {
         // Ret = ::get_last_error();
         CloseServiceHandle(hdlSCM);
         return false;
      }

      SERVICE_STATUS ss;

      memset(&ss,0,sizeof(ss));

      bool bOk = ::ControlService(hdlServ,SERVICE_CONTROL_STOP,&ss) != FALSE;

      ::DeleteService(hdlServ);

      CloseServiceHandle(hdlServ);

      CloseServiceHandle(hdlSCM);

      return bOk != FALSE;
   }


   DECLSPEC_NO_RETURN void os::raise_exception( DWORD dwExceptionCode, DWORD dwExceptionFlags)
   {
      RaiseException( dwExceptionCode, dwExceptionFlags, 0, NULL );
   }

   bool os::is_remote_session()
   {

      return GetSystemMetrics(SM_REMOTESESSION) != FALSE;

   }




   void os::set_file_status(const char * lpszFileName, const ::file::file_status& status)
   {

      DWORD wAttr;
      FILETIME creationTime;
      FILETIME lastAccessTime;
      FILETIME lastWriteTime;
      LPFILETIME lpCreationTime = NULL;
      LPFILETIME lpLastAccessTime = NULL;
      LPFILETIME lpLastWriteTime = NULL;

      wstring wstr(lpszFileName);

      if((wAttr = GetFileAttributesW(wstr)) == (DWORD)-1L)
      {

         ::windows::file_exception::ThrowOsError(get_app(), (LONG)get_last_error());

      }

      if ((DWORD)status.m_attribute != wAttr && (wAttr & ::windows::file::readOnly))
      {

         // set file attribute, only if currently readonly.
         // This way we will be able to modify the time assuming the
         // caller changed the file from readonly.

         if (!SetFileAttributesW(wstr, (DWORD)status.m_attribute))
         {

            ::windows::file_exception::ThrowOsError(get_app(), (LONG)get_last_error());

         }

      }

      // last modification time
      if (status.m_mtime.get_time() != 0)
      {

         ::windows::time_to_filetime(get_app(), status.m_mtime, &lastWriteTime);

         lpLastWriteTime = &lastWriteTime;

      }

      // last access time
      if (status.m_atime.get_time() != 0)
      {

         ::windows::time_to_filetime(get_app(),status.m_atime, &lastAccessTime);

         lpLastAccessTime = &lastAccessTime;

      }

      // create time
      if (status.m_ctime.get_time() != 0)
      {

         ::windows::time_to_filetime(get_app(),status.m_ctime, &creationTime);

         lpCreationTime = &creationTime;

      }

      HANDLE hFile = ::CreateFileW(wstr, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

      if(hFile == INVALID_HANDLE_VALUE)
      {

         ::windows::file_exception::ThrowOsError(get_app(), (LONG)::get_last_error());

      }

      if(!SetFileTime((HANDLE)hFile, lpCreationTime, lpLastAccessTime, lpLastWriteTime))
      {

         ::windows::file_exception::ThrowOsError(get_app(), (LONG)::get_last_error());

      }

      if(!::CloseHandle(hFile))
      {

         ::windows::file_exception::ThrowOsError(get_app(), (LONG)::get_last_error());

      }

      if ((DWORD)status.m_attribute != wAttr && !(wAttr & ::windows::file::readOnly))
      {

         if (!::SetFileAttributesW(wstr, (DWORD)status.m_attribute))
         {

            ::windows::file_exception::ThrowOsError(get_app(), (LONG)get_last_error());

         }

      }

   }


   bool os::resolve_link(::file::path & pathLink, string & strFolder, string & strParams, const string & strSource, ::user::primitive * puiMessageParentOptional)
   {

      sp(::user::primitive) pui = puiMessageParentOptional;

      if (!::str::ends_ci(strSource, ".lnk"))
      {

         pathLink = strSource;

         return true;

      }

      if (strSource.contains("0318") && strSource.contains("removal"))
      {

         output_debug_string("app.removal.tool link?!");

      }

      wstring wstrFileIn = ::str::international::utf8_to_unicode(strSource);

      bool bNativeUnicode = is_windows_native_unicode() != FALSE;

      SHFILEINFOW info;

      ZERO(info);

      DWORD_PTR dw = ::windows::shell::SHGetFileInfo(wstrFileIn, 0, &info, sizeof(info), SHGFI_ATTRIBUTES);

      if(dw == 0 || !(info.dwAttributes & SFGAO_LINK))
      {

         pathLink = wstrFileIn;

         return false;

      }

      HRESULT hr ;

      comptr < IShellLinkW > pshelllink;

      if (FAILED(hr = pshelllink.CoCreateInstance(CLSID_ShellLink, NULL, CLSCTX_INPROC_SERVER)))
      {

         return false;

      }

      bool bOk = false;

      comptr < IPersistFile > ppersistfile;

      if(SUCCEEDED(hr = pshelllink.As(ppersistfile)))
      {

         if(SUCCEEDED(hr = ppersistfile->Load(wstrFileIn,STGM_READ)))
         {

            HWND hwnd = pui == NULL ? NULL : pui->get_handle();

            DWORD fFlags = 0;

            fFlags |= pui == NULL ? (SLR_NO_UI | (10 << 16)) : 0;

            fFlags |= SLR_NOUPDATE;

            fFlags |= SLR_NOSEARCH;

            fFlags |= SLR_NOTRACK;

            /* Resolve the link, this may post UI to find the link */
            //if(SUCCEEDED(pshelllink->Resolve(hwnd, fFlags)))
            {

               wstring wstr;

               wstr.alloc(MAX_PATH * 8);

               if(SUCCEEDED(pshelllink->GetPath(wstr,MAX_PATH * 8,NULL,0)))
               {

                  bOk = true;

                  wstr.release_buffer();

                  string strLink = ::str::international::unicode_to_utf8((LPCWSTR)wstr);

                  if (strLink.is_empty())
                  {

                     pshelllink->GetIDList(&pathLink.m_idlist.m_pidl);

                  }
                  else
                  {

                     pathLink = strLink;

                  }

               }

               wstr.alloc(MAX_PATH * 8);

               if(SUCCEEDED(pshelllink->GetWorkingDirectory(wstr,MAX_PATH * 8)))
               {

                  wstr.release_buffer();

                  strFolder = ::str::international::unicode_to_utf8((LPCWSTR)wstr);

               }

               wstr.alloc(MAX_PATH * 8);

               if(SUCCEEDED(pshelllink->GetArguments(wstr,MAX_PATH * 8)))
               {

                  wstr.release_buffer();

                  strParams = ::str::international::unicode_to_utf8((LPCWSTR)wstr);

               }

            }

         }

      }

      return bOk;

   }


   bool os::get_default_browser(string & strId, ::file::path & path, string & strParam)
   {

      registry::Key key;

      key.OpenKey(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\FileExts\\.html\\UserChoice", false);

      string strProgId;

      string strHash;
      key.QueryValue("Hash", strHash);
      key.QueryValue("ProgId", strProgId);

      if (::str::begins(strProgId, "App") && strHash.has_char())
      {

         strId = "edge";

      }
      if (::str::begins_ci(strProgId, "IE."))
      {

         strId = "ie";

      }
      else if (::str::begins_ci(strProgId, "ChromeHTML"))
      {

         strId = "chrome";

      }
      else if (::str::begins_ci(strProgId, "FirefoxHTML"))
      {

         strId = "firefox";

      }
      else if (::str::begins_ci(strProgId, "Opera"))
      {

         strId = "opera";

      }
      else if (::str::begins_ci(strProgId, "VivaldiHTM."))
      {

         strId = "vivaldi";

      }
      else if (::str::ends_ci(strProgId, "app_core_commander"))
      {

         strId = "commander";

      }
      else
      {

         strId = "commander";

      }

      string strDefault;

      key.OpenKey(HKEY_CLASSES_ROOT, strProgId + "\\shell\\open\\command", false);

      key.QueryValue("", strDefault);

      if (strDefault.is_empty())
      {

         return false;

      }

      bool bQuote = ::str::begins_eat_ci(strDefault, "\"");

      strsize iFind = strDefault.find_ci(".exe");

      if (iFind <= 0)
      {

         return false;

      }

      path = strDefault.Left(iFind);

      path += ".exe";

      //MessageBox(NULL, path, "pathProgram", MB_OK);

      strParam = strDefault.Mid(iFind + 5);

      if (bQuote)
      {

         ::str::begins_eat_ci(strParam, "\"");

      }

      return true;

   }


   bool os::initialize_wallpaper_fileset(::file::set * pfileset, bool bAddSearch)
   {

      if (bAddSearch)
      {

         ::file::path pathFolder;

         ::windows::shell_get_special_folder_path(NULL, pathFolder, CSIDL_WINDOWS, FALSE);

         pathFolder /= "Web/Wallpaper";

         pfileset->add_search(pathFolder, true);

      }

      return true;

   }
//#elif defined(LINUX)
//   //string strDir;
//   //strDir = System.dir().path(getenv("HOME"), "Pictures");
//   //pimagefileset->add_search(strDir);
//   string strDir;
//   strDir = "/usr/share/backgrounds";
//   pimagefileset->add_search(strDir, true);
//            }
//
//#elif defined(MACOS)
//   //string strDir;
//   //strDir = System.dir().path(getenv("HOME"), "Pictures");
//   //pimagefileset->add_search(strDir);
//   string strDir;
//   strDir = "/Library/Desktop Pictures";
//   pimagefileset->add_search(strDir, true);
//            }
//
//#else


   bool os::file_open(::aura::application * papp, ::file::path path, string strParams, string strFolder)
   {

      path = System.defer_process_path(path, papp);

      fork([=]()
      {

         ::CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);

         SHELLEXECUTEINFOW si;

         ZERO(si);

         PeekMessage(NULL, NULL, 0, 0, 0);

         wstring wstrTarget(path);

         wstring wstrFolder(strFolder);

         wstring wstrParams(strParams);

         const wchar_t * pwszParams = wstrParams.c_str();

         const wchar_t * pwszFolder = wstrFolder.c_str();

         si.cbSize = sizeof(si);

         si.fMask = SEE_MASK_ASYNCOK;

         si.hwnd = NULL;

         si.lpVerb = L"open";

         if (wstrTarget.is_empty())
         {

            si.fMask |= SEE_MASK_IDLIST;

            si.lpIDList = path.m_idlist.m_pidl;

         }
         else
         {

            si.lpFile = wstrTarget;

         }

         si.lpParameters = pwszParams;

         si.lpDirectory = pwszFolder;

         si.nShow = SW_SHOW;

         si.hInstApp = NULL;

         ShellExecuteExW(&si);

         //DWORD dwLastError = ::GetLastError();

         //int iResult = (int) si.hInstApp;

         //string str;

         //str.Format("ShellExecuteExW %d GetLastError = %d", iResult, dwLastError);

         //output_debug_string(str);


         //thread_pump_sleep(60 * 1000);


         //int iRet = (int) (int_ptr) ::ShellExecuteW(NULL, L"open", wstring(path), pwszParams, pwszFolder, SW_RESTORE);

         //if (iRet < 32)
         //{

         //   /*0
         //      The operating system is out of memory or resources.
         //      ERROR_FILE_NOT_FOUND
         //      The specified file was not found.
         //      ERROR_PATH_NOT_FOUND
         //      The specified path was not found.
         //      ERROR_BAD_FORMAT
         //      The.exe file is invalid(non - Win32.exe or error in.exe image).
         //      SE_ERR_ACCESSDENIED
         //      The operating system denied access to the specified file.
         //      SE_ERR_ASSOCINCOMPLETE
         //      The file name association is incomplete or invalid.
         //      SE_ERR_DDEBUSY
         //      The DDE transaction could not be completed because other DDE transactions were being processed.
         //      SE_ERR_DDEFAIL
         //      The DDE transaction failed.
         //      SE_ERR_DDETIMEOUT
         //      The DDE transaction could not be completed because the request timed out.
         //      SE_ERR_DLLNOTFOUND
         //      The specified DLL was not found.
         //      SE_ERR_FNF
         //      The specified file was not found.
         //      SE_ERR_NOASSOC
         //      There is no application associated with the given file name extension.This error will also be returned if you attempt to print a file that is not printable.
         //      SE_ERR_OOM
         //      There was not enough memory to complete the operation.
         //      SE_ERR_PNF
         //      The specified path was not found.
         //      SE_ERR_SHARE
         //      A sharing violation occurred.*/

         //   simple_message_box(NULL, "Error opening file \"" + path + "\"", "Could not open file", MB_ICONEXCLAMATION);

         //}

      });

      return true;

   }


   bool os::register_user_auto_start(string strId, string strCommand, bool bRegister)
   {

      current_user_set_run(strId, strCommand, bRegister);

      return true;

   }

   bool os::is_user_auto_start(string strId)
   {

      registry::Key keyKar;

      if (keyKar.OpenKey(HKEY_CURRENT_USER, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", false))
      {

         string strValue;

         if (keyKar.QueryValue(strId, strValue))
         {

            if (strValue.has_char())
            {

               return true;

            }

         }

      }

      return false;

   }

   ::file::path os::get_app_path(const string & strApp)
   {

      string str(strApp);

      registry::Key key;

      string strDefault;

repeat:

      if (key.OpenKey(HKEY_LOCAL_MACHINE, "Software\\Microsoft\\Windows\\CurrentVersion\\App Paths\\" + str, false))
      {

         if (key.QueryValue("", strDefault))
         {

            if (strDefault.has_char())
            {

               return strDefault;

            }

         }

      }

      if (!::str::ends_ci(str, ".exe"))
      {

         str += ".exe";

         goto repeat;

      }

      return ::aura::os::get_app_path(str);

   }


   bool os::set_default_browser(::aura::application * papp)
   {

      string strTargetProgId;
      string strModule = solve_relative_compressions(::file::app_module());

      strTargetProgId = papp->m_strAppName;

      strTargetProgId.replace("-", "_");
      strTargetProgId.replace("\\", "_");
      strTargetProgId.replace("/", "_");
      {

         ::windows::registry::Key regkey(HKEY_LOCAL_MACHINE, "SOFTWARE\\RegisteredApplications", true);

         string strValue;

         regkey.SetValue(strTargetProgId, "Software\\Clients\\StartMenuInternet\\" + strTargetProgId + "\\Capabilities");



      }
      {

         ::windows::registry::Key regkey(HKEY_LOCAL_MACHINE, "Software\\Clients\\StartMenuInternet\\" + strTargetProgId, true);

         string strValue;

         regkey.SetValue("", papp->oprop("ApplicationName").get_string());



      }
      {

         ::windows::registry::Key regkey(HKEY_LOCAL_MACHINE, "Software\\Clients\\StartMenuInternet\\" + strTargetProgId + "\\Capabilities", true);

         string strValue;

         regkey.SetValue("ApplicationDescription", papp->oprop("ApplicationDescription").get_string());
         regkey.SetValue("ApplicationIcon", papp->oprop("ApplicationIcon").get_string());
         regkey.SetValue("ApplicationName", papp->oprop("ApplicationName").get_string());



      }

      {

         ::windows::registry::Key regkey(HKEY_LOCAL_MACHINE, "Software\\Clients\\StartMenuInternet\\" + strTargetProgId + "\\Capabilities\\FileAssociations", true);

         string strValue;

         regkey.SetValue(".htm", strTargetProgId);
         regkey.SetValue(".html", strTargetProgId);
         regkey.SetValue(".pdf", strTargetProgId);
         regkey.SetValue(".shtml", strTargetProgId);
         regkey.SetValue(".svg", strTargetProgId);
         regkey.SetValue(".webp", strTargetProgId);
         regkey.SetValue(".xht", strTargetProgId);
         regkey.SetValue(".xhtml", strTargetProgId);

      }

      {

         ::windows::registry::Key regkey(HKEY_LOCAL_MACHINE, "Software\\Clients\\StartMenuInternet\\" + strTargetProgId + "\\Capabilities\\Startmenu", true);

         string strValue;

         regkey.SetValue("StartMenuInternet", strTargetProgId);

      }

      {

         ::windows::registry::Key regkey(HKEY_LOCAL_MACHINE, "Software\\Clients\\StartMenuInternet\\" + strTargetProgId + "\\Capabilities\\URLAssociations", true);

         string strValue;

         regkey.SetValue("ftp", strTargetProgId);
         regkey.SetValue("http", strTargetProgId);
         regkey.SetValue("https", strTargetProgId);
         regkey.SetValue("irc", strTargetProgId);
         regkey.SetValue("mailto", strTargetProgId);
         regkey.SetValue("mms", strTargetProgId);
         regkey.SetValue("news", strTargetProgId);
         regkey.SetValue("nntp", strTargetProgId);
         regkey.SetValue("sms", strTargetProgId);
         regkey.SetValue("smsto", strTargetProgId);
         regkey.SetValue("tel", strTargetProgId);
         regkey.SetValue("urn", strTargetProgId);
         regkey.SetValue("webcal", strTargetProgId);

      }

      {

         ::windows::registry::Key regkey(HKEY_LOCAL_MACHINE, "Software\\Clients\\StartMenuInternet\\" + strTargetProgId + "\\DefaultIcon", true);

         string strValue;

         regkey.SetValue("", strModule + ",0");

      }


      {

         ::windows::registry::Key regkey(HKEY_LOCAL_MACHINE, "Software\\Clients\\StartMenuInternet\\" + strTargetProgId + "\\InstallInfo", true);

         string strValue;

         regkey.SetValue("HideIconsCommand", "\""+strModule + "\" : hide_icons");
         regkey.SetValue("IconsVisible", 1);
         regkey.SetValue("ReinstallCommand", "\""+strModule + "\" : install");
         regkey.SetValue("ShowIconsCommand", "\""+strModule + "\" : show_icons");

      }


      {

         ::windows::registry::Key regkey(HKEY_LOCAL_MACHINE, "Software\\Clients\\StartMenuInternet\\" + strTargetProgId + "\\shell\\open\\command", true);

         string strValue;

         regkey.SetValue("", "\""+strModule + "\" : browser_weather=default");

      }


      {

         registry::Key regkey(HKEY_CLASSES_ROOT, strTargetProgId, true);

         regkey.SetValue("", strTargetProgId + " HTML Document");
         regkey.SetValue("AppUserModelId", papp->oprop("AppUserModelId").get_string());

      }
      {

         registry::Key regkey(HKEY_CLASSES_ROOT, strTargetProgId + "\\Application", true);

         regkey.SetValue("ApplicationCompany", papp->oprop("ApplicationCompany").get_string());
         regkey.SetValue("ApplicationDescription", papp->oprop("ApplicationDescription").get_string());
         regkey.SetValue("ApplicationIcon", papp->oprop("ApplicationIcon").get_string());
         regkey.SetValue("ApplicationName", papp->oprop("ApplicationName").get_string());
         regkey.SetValue("AppUserModelId", papp->oprop("AppUserModelId").get_string());

      }
      {

         registry::Key regkey(HKEY_CLASSES_ROOT, strTargetProgId + "\\DefaultIcon", true);

         regkey.SetValue("", papp->oprop("DefaultIcon").get_string());

      }

      file_association_set_shell_open_command(strTargetProgId, strTargetProgId, strModule, "\"%1\"");
      {

         ::windows::registry::Key regkey(HKEY_CURRENT_USER, "SOFTWARE\\Microsoft\\Windows\\shell\\Associations\\UrlAssociations\\http\\UserChoice", true);

         string strProgId;

         regkey.QueryValue("ProgId", strProgId);

         if (strProgId != strTargetProgId)
         {

            regkey.DeleteValue("Hash");
            regkey.SetValue("ProgId", strTargetProgId);

         }

      }


      {

         ::windows::registry::Key regkey(HKEY_CURRENT_USER, "SOFTWARE\\Microsoft\\Windows\\shell\\Associations\\UrlAssociations\\https\\UserChoice", true);

         string strProgId;

         regkey.QueryValue("ProgId", strProgId);

         if (strProgId != strTargetProgId)
         {

            regkey.DeleteValue("Hash");
            regkey.SetValue("ProgId", strTargetProgId);

         }

      }
      {

         registry::Key regkey(HKEY_CURRENT_USER, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Explorer\\FileExts\\.html\\UserChoice", true);
         string strProgId;

         regkey.QueryValue("ProgId", strProgId);

         if (strProgId != strTargetProgId)
         {

            regkey.DeleteValue("Hash");
            regkey.SetValue("ProgId", strTargetProgId);

         }

      }
      {

         registry::Key regkey(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\FileExts\\.htm\\UserChoice", true);
         string strProgId;

         regkey.QueryValue("ProgId", strProgId);

         if (strProgId != strTargetProgId)
         {

            regkey.DeleteValue("Hash");
            regkey.SetValue("ProgId", strTargetProgId);

         }

      }
      {

         registry::Key regkey(HKEY_CLASSES_ROOT, ".html\\OpenWithProgids", true);

         if (!regkey.SetValue(strTargetProgId, ""))
         {

            TRACE("Failure to set .html/OpenWithProgids");

         }

      }
      {

         registry::Key regkey(HKEY_CLASSES_ROOT, ".htm\\OpenWithProgids", true);

         if(!regkey.SetValue(strTargetProgId, ""))
         {

            TRACE("Failure to set .htm/OpenWithProgids");

         }

      }
      //file_association_set_shell_open_command(".htm", strTargetProgId, strModule, "\"%1\"");
      //file_association_set_shell_open_command(".html", strTargetProgId, strModule, "\"%1\"");
      //file_association_set_shell_open_command("http", strTargetProgId, strModule, "\"%1\"");
      //file_association_set_shell_open_command("https", strTargetProgId, strModule, "\"%1\"");
      SHChangeNotify(SHCNE_ASSOCCHANGED, SHCNF_DWORD | SHCNF_FLUSH, nullptr, nullptr);
      Sleep(1000);



      return true;

   }


   bool os::add_default_program(::aura::application * papp, stringa & straExtension, stringa & straMimeType)
   {

      string strTargetProgId;

      string strModule = solve_relative_compressions(::file::app_module());

      string strApplicationRegistryPath = papp->oprop("ApplicationRegistryPath");

      ::file::path pathApplication;

      pathApplication = "Software";

      pathApplication /= strApplicationRegistryPath;

      pathApplication /= strTargetProgId;

      strTargetProgId = papp->m_strAppName;

      strTargetProgId.replace("-", "_");
      strTargetProgId.replace("\\", "_");
      strTargetProgId.replace("/", "_");

      {

         ::windows::registry::Key regkey(HKEY_LOCAL_MACHINE, pathApplication, true);

         string strValue;

         regkey.SetValue("", papp->oprop("ApplicationName").get_string());

      }

      {

         ::windows::registry::Key regkey(HKEY_LOCAL_MACHINE, pathApplication / "DefaultIcon", true);

         string strValue;

         regkey.SetValue("", strModule + ",0");

      }


      {

         ::windows::registry::Key regkey(HKEY_LOCAL_MACHINE, pathApplication / "InstallInfo", true);

         string strValue;

         regkey.SetValue("HideIconsCommand", "\"" + strModule + "\" : hide_icons");
         regkey.SetValue("IconsVisible", 1);
         regkey.SetValue("ReinstallCommand", "\"" + strModule + "\" : install");
         regkey.SetValue("ShowIconsCommand", "\"" + strModule + "\" : show_icons");

      }

      {

         ::windows::registry::Key regkey(HKEY_LOCAL_MACHINE, pathApplication / "shell/open/command", true);

         string strValue;

         regkey.SetValue("", "\"" + strModule + "\" \"%1\"");

      }


      ::file::path pathApplicationCapabilities;

      pathApplicationCapabilities = pathApplication / "Capabilities";

      {

         ::windows::registry::Key regkey(HKEY_LOCAL_MACHINE, "SOFTWARE\\RegisteredApplications", true);

         string strValue;

         regkey.SetValue(strTargetProgId, pathApplicationCapabilities);

      }

      {

         ::windows::registry::Key regkey(HKEY_LOCAL_MACHINE, pathApplicationCapabilities, true);

         string strValue;

         regkey.SetValue("ApplicationDescription", papp->oprop("ApplicationDescription").get_string());
         regkey.SetValue("ApplicationIcon", papp->oprop("ApplicationIcon").get_string());
         regkey.SetValue("ApplicationName", papp->oprop("ApplicationName").get_string());

      }

      {

         ::windows::registry::Key regkey(HKEY_LOCAL_MACHINE, pathApplicationCapabilities / "FileAssociations", true);

         string strValue;

         regkey.SetValue(".mp4", strTargetProgId);

      }

      //{

      //   ::windows::registry::Key regkey(HKEY_LOCAL_MACHINE, "Software\\Clients\\StartMenuInternet\\" + strTargetProgId + "\\Capabilities\\Startmenu", true);

      //   string strValue;

      //   regkey.SetValue("StartMenuInternet", strTargetProgId);

      //}

      {

         ::windows::registry::Key regkey(HKEY_LOCAL_MACHINE, pathApplicationCapabilities / "FileAssociations", true);

         for (index i = 0; i < straMimeType.get_count(); i++)
         {

            string strExtension = straExtension[i];

            regkey.SetValue("." + strExtension, strTargetProgId + "." + strExtension);

         }

      }

      {

         ::windows::registry::Key regkey(HKEY_LOCAL_MACHINE, pathApplicationCapabilities / "MimeAssociations", true);

         for (index i = 0; i < straMimeType.get_count(); i++)
         {

            string strMimeType = straMimeType[i];

            string strExtension = straExtension[i];

            regkey.SetValue(strMimeType, strTargetProgId + "." + strExtension);

         }

      }

      //{

      //   registry::Key regkey(HKEY_CLASSES_ROOT, strTargetProgId, true);

      //   regkey.SetValue("", strTargetProgId + " HTML Document");
      //   regkey.SetValue("AppUserModelId", papp->oprop("AppUserModelId").get_string());

      //}
      {

         registry::Key regkey(HKEY_CLASSES_ROOT, strTargetProgId + "\\Application", true);

         regkey.SetValue("ApplicationCompany", papp->oprop("ApplicationCompany").get_string());
         regkey.SetValue("ApplicationDescription", papp->oprop("ApplicationDescription").get_string());
         regkey.SetValue("ApplicationIcon", papp->oprop("ApplicationIcon").get_string());
         regkey.SetValue("ApplicationName", papp->oprop("ApplicationName").get_string());
         regkey.SetValue("AppUserModelId", papp->oprop("AppUserModelId").get_string());

      }
      {

         registry::Key regkey(HKEY_CLASSES_ROOT, strTargetProgId + "\\DefaultIcon", true);

         regkey.SetValue("", papp->oprop("DefaultIcon").get_string());

      }

      for (index i = 0; i < straExtension.get_count(); i++)
      {

         string strExtension = straExtension[i];

         file_association_set_shell_open_command(strExtension, strTargetProgId + "." + strExtension, strModule, "\"%1\"");

         {

            registry::Key regkey(HKEY_CLASSES_ROOT, "." + strExtension + "\\OpenWithProgids", true);

            if (!regkey.SetValue(strTargetProgId, ""))
            {

               TRACE("Failure to set ." + strExtension + "\\OpenWithProgids");

            }

         }

      }

      //{

      //   ::windows::registry::Key regkey(HKEY_CURRENT_USER, "SOFTWARE\\Microsoft\\Windows\\shell\\Associations\\UrlAssociations\\http\\UserChoice", true);

      //   string strProgId;

      //   regkey.QueryValue("ProgId", strProgId);

      //   if (strProgId != strTargetProgId)
      //   {

      //      regkey.DeleteValue("Hash");
      //      regkey.SetValue("ProgId", strTargetProgId);

      //   }

      //}

      //{

      //   ::windows::registry::Key regkey(HKEY_CURRENT_USER, "SOFTWARE\\Microsoft\\Windows\\shell\\Associations\\UrlAssociations\\https\\UserChoice", true);

      //   string strProgId;

      //   regkey.QueryValue("ProgId", strProgId);

      //   if (strProgId != strTargetProgId)
      //   {

      //      regkey.DeleteValue("Hash");
      //      regkey.SetValue("ProgId", strTargetProgId);

      //   }

      //}

      //{

      //   registry::Key regkey(HKEY_CURRENT_USER, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Explorer\\FileExts\\.html\\UserChoice", true);
      //   string strProgId;

      //   regkey.QueryValue("ProgId", strProgId);

      //   if (strProgId != strTargetProgId)
      //   {

      //      regkey.DeleteValue("Hash");
      //      regkey.SetValue("ProgId", strTargetProgId);

      //   }

      //}
      //{

      //   registry::Key regkey(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\FileExts\\.htm\\UserChoice", true);
      //   string strProgId;

      //   regkey.QueryValue("ProgId", strProgId);

      //   if (strProgId != strTargetProgId)
      //   {

      //      regkey.DeleteValue("Hash");
      //      regkey.SetValue("ProgId", strTargetProgId);

      //   }

      //}
      //{

      //   registry::Key regkey(HKEY_CLASSES_ROOT, ".htm\\OpenWithProgids", true);

      //   if(!regkey.SetValue(strTargetProgId, ""))
      //   {

      //      TRACE("Failure to set .htm/OpenWithProgids");

      //   }

      //}
      //file_association_set_shell_open_command(".htm", strTargetProgId, strModule, "\"%1\"");
      //file_association_set_shell_open_command(".html", strTargetProgId, strModule, "\"%1\"");
      //file_association_set_shell_open_command("http", strTargetProgId, strModule, "\"%1\"");
      //file_association_set_shell_open_command("https", strTargetProgId, strModule, "\"%1\"");
      SHChangeNotify(SHCNE_ASSOCCHANGED, SHCNF_DWORD | SHCNF_FLUSH, nullptr, nullptr);
      Sleep(1000);



      return true;

   }


   bool os::browse_file_open(oswindow oswindowOwner, property_set & set)
   {

      bool bOk = false;

      try
      {

         ::EnableWindow(oswindowOwner, FALSE);

      }
      catch (...)
      {


      }

      try
      {

         defer_co_initialize_ex(false);

         comptr < IFileOpenDialog > pfileopen;

         HRESULT hr = pfileopen.CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_ALL);

         if (SUCCEEDED(hr))
         {

            FILEOPENDIALOGOPTIONS options = 0;

            hr = pfileopen->GetOptions(&options);

            array < COMDLG_FILTERSPEC > rgSpec;

            array < wstring > wstraSpecs;

            ::lemon::array::copy(wstraSpecs, set["file_filter_specs"].stra());

            array < wstring > wstraNames;

            ::lemon::array::copy(wstraNames, set["file_filter_names"].stra());

            rgSpec.set_size(MIN(wstraSpecs.get_size(), wstraNames.get_size()));

            for (index i = 0; i < rgSpec.get_size(); i++)
            {

               rgSpec[i].pszName = wstraNames[i];

               rgSpec[i].pszSpec = wstraSpecs[i];

               //{ L"CSV files", L"*.csv" },
               //{ L"Text files", L"*.txt" },
               //{ L"All files", L"*.*" },

            }

            if (rgSpec.get_size() > 0)
            {

               pfileopen->SetFileTypes(UINT(rgSpec.get_size()), rgSpec.get_data());

            }

            if ((bool)set["allow_multi_select"])
            {

               options |= FOS_ALLOWMULTISELECT;

            }

            hr = pfileopen->SetOptions(options);

            if (set["default_file_extension"].get_string().get_length() > 0)
            {

               pfileopen->SetDefaultExtension(wstring(set["default_file_extension"].get_string()));

            }

            if (set["file_name"].get_string().get_length() > 0)
            {

               pfileopen->SetFileName(wstring(set["file_name"].get_string()));

            }

            if (set["folder"].get_string().get_length() > 0)
            {

               wstring wstr(set["folder"].get_string());

               comptr < IShellItem > psi;

               hr = SHCreateItemFromParsingName(wstr, NULL, IID_IShellItem, (void **)&psi);

               if (SUCCEEDED(hr))
               {

                  pfileopen->SetFolder(psi);

               }

            }

            // Show the Save dialog box.
            hr = pfileopen->Show(NULL);

            if (SUCCEEDED(hr))
            {

               if (options & FOS_ALLOWMULTISELECT)
               {

                  comptr < IShellItemArray > pitema;

                  hr = pfileopen->GetResults(&pitema);

                  if (SUCCEEDED(hr))
                  {
                     DWORD dwNumItems = 0; // number of items in multiple selection

                     hr = pitema->GetCount(&dwNumItems);  // get number of selected items

                     // Loop through IShellItemArray and construct string for display
                     for (DWORD i = 0; i < dwNumItems; i++)
                     {
                        comptr < IShellItem > pitem;

                        hr = pitema->GetItemAt(i, &pitem); // get a selected item from the IShellItemArray

                        if (SUCCEEDED(hr))
                        {

                           cotaskp(PWSTR) pwszFilePath;

                           hr = pitem->GetDisplayName(SIGDN_FILESYSPATH, &pwszFilePath);

                           // Display the file name to the user.
                           if (SUCCEEDED(hr))
                           {

                              set["file_name"].stra().add(string((PWSTR)pwszFilePath));

                              bOk = true;

                           }

                        }

                     }

                  }

               }
               else
               {

                  // Get the file name from the dialog box.
                  comptr < IShellItem > pitem;

                  hr = pfileopen->GetResult(&pitem);

                  if (SUCCEEDED(hr))
                  {

                     cotaskp(PWSTR) pwszFilePath;

                     hr = pitem->GetDisplayName(SIGDN_FILESYSPATH, &pwszFilePath);

                     // Display the file name to the user.
                     if (SUCCEEDED(hr))
                     {

                        set["file_name"] = string((PWSTR)pwszFilePath);

                        bOk = true;

                     }

                  }

               }

            }

         }

      }
      catch (...)
      {


      }

      try
      {

         ::EnableWindow(oswindowOwner, TRUE);

         ::SetWindowPos(oswindowOwner, HWND_TOP, 0, 0, 0, 0, SWP_SHOWWINDOW);

         ::SetForegroundWindow(oswindowOwner);

         ::BringWindowToTop(oswindowOwner);

      }
      catch (...)
      {


      }

      return bOk;

   }


   bool os::browse_file_save(oswindow oswindowOwner, property_set & set)
   {

      bool bOk = false;

      try
      {

         ::EnableWindow(oswindowOwner, FALSE);

      }
      catch (...)
      {


      }

      try
      {

         defer_co_initialize_ex(false);

         comptr < IFileSaveDialog > pfilesave;

         // Create the FileSaveDialog object.
         HRESULT hr = pfilesave.CoCreateInstance(CLSID_FileSaveDialog, NULL, CLSCTX_ALL);

         if (SUCCEEDED(hr))
         {

            //COMDLG_FILTERSPEC rgSpec[] =
            //{
            // { L"CSV files", L"*.csv" },
            // { L"Text files", L"*.txt" },
            // { L"All files", L"*.*" },
            //};

            //pFileSave->SetFileTypes(3, rgSpec);



            //pFileSave->SetFileName(L"Twitter Automator Export");

            array < COMDLG_FILTERSPEC > rgSpec;

            array < wstring > wstraSpecs;

            ::lemon::array::copy(wstraSpecs, set["file_filter_specs"].stra());

            array < wstring > wstraNames;

            ::lemon::array::copy(wstraNames, set["file_filter_names"].stra());

            rgSpec.set_size(MIN(wstraSpecs.get_size(), wstraNames.get_size()));

            for (index i = 0; i < rgSpec.get_size(); i++)
            {

               rgSpec[i].pszName = wstraNames[i];

               rgSpec[i].pszSpec = wstraSpecs[i];

               //{ L"CSV files", L"*.csv" },
               //{ L"Text files", L"*.txt" },
               //{ L"All files", L"*.*" },

            }

            if (rgSpec.get_size() > 0)
            {

               pfilesave->SetFileTypes(UINT (rgSpec.get_size()), rgSpec.get_data());

            }

            if (set["default_file_extension"].get_string().get_length() > 0)
            {

               pfilesave->SetDefaultExtension(wstring(set["default_file_extension"].get_string()));

            }

            if (set["file_name"].get_string().get_length() > 0)
            {

               pfilesave->SetFileName(wstring(set["file_name"].get_string()));

            }

            if (set["folder"].get_string().get_length() > 0)
            {

               wstring wstr(set["folder"].get_string());

               comptr < IShellItem > psi;

               hr = SHCreateItemFromParsingName(wstr, NULL, IID_IShellItem, (void **)&psi);

               if (SUCCEEDED(hr))
               {

                  pfilesave->SetFolder(psi);

               }

            }

            // Show the Save dialog box.
            hr = pfilesave->Show(NULL);

            if (SUCCEEDED(hr))
            {

               // Get the file name from the dialog box.
               comptr < IShellItem > pitem;

               hr = pfilesave->GetResult(&pitem);

               if (SUCCEEDED(hr))
               {

                  cotaskp(PWSTR) pwszFilePath;

                  hr = pitem->GetDisplayName(SIGDN_FILESYSPATH, &pwszFilePath);

                  // Display the file name to the user.
                  if (SUCCEEDED(hr))
                  {

                     set["file_name"] = string(pwszFilePath);

                     bOk = true;

                  }

               }

            }

         }

      }
      catch (...)
      {

      }

      try
      {

         ::EnableWindow(oswindowOwner, TRUE);

         ::SetWindowPos(oswindowOwner, HWND_TOP, 0, 0, 0, 0, SWP_SHOWWINDOW);

         ::SetForegroundWindow(oswindowOwner);

         ::BringWindowToTop(oswindowOwner);

      }
      catch (...)
      {

      }

      return bOk;

   }



   bool os::browse_folder(oswindow oswindowOwner, property_set & set)
   {

      bool bOk = false;

      try
      {

         ::EnableWindow(oswindowOwner, FALSE);

      }
      catch (...)
      {


      }

      try
      {

         defer_co_initialize_ex(false);

         comptr < IFileOpenDialog > pfileopen;

         // Create the FileOpenDialog object.
         HRESULT hr = pfileopen.CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_ALL);

         if (SUCCEEDED(hr))
         {

            if (set["folder"].get_string().get_length() > 0)
            {

               wstring wstr(set["folder"].get_string());

               comptr < IShellItem > psi;

               hr = SHCreateItemFromParsingName(wstr, NULL, IID_IShellItem, (void **)&psi);

               if (SUCCEEDED(hr))
               {

                  pfileopen->SetFolder(psi);

               }

            }

            pfileopen->SetOptions(FOS_PICKFOLDERS);

            // Show the Open dialog box.
            hr = pfileopen->Show(NULL);

            if (SUCCEEDED(hr))
            {

               // Get the file name from the dialog box.
               comptr < IShellItem > pitem;

               hr = pfileopen->GetResult(&pitem);

               if (SUCCEEDED(hr))
               {

                  cotaskp(PWSTR) pwszFilePath;

                  hr = pitem->GetDisplayName(SIGDN_FILESYSPATH, &pwszFilePath);

                  // Display the file name to the user.
                  if (SUCCEEDED(hr))
                  {

                     set["folder"] = string((PWSTR) pwszFilePath);

                     bOk = true;

                  }

               }

            }

         }

      }
      catch (...)
      {

      }

      try
      {

         ::EnableWindow(oswindowOwner, TRUE);

         ::SetWindowPos(oswindowOwner, HWND_TOP, 0, 0, 0, 0, SWP_SHOWWINDOW);

         ::SetForegroundWindow(oswindowOwner);

         ::BringWindowToTop(oswindowOwner);

      }
      catch (...)
      {


      }

      return bOk;

   }

   bool os::browse_file_or_folder(oswindow oswindowOwner, property_set & set)
   {

      bool bOk = false;

      try
      {

         ::EnableWindow(oswindowOwner, FALSE);

      }
      catch (...)
      {


      }

      try
      {

         defer_co_initialize_ex(false);

         comptr < IFileOpenDialog > pfileopen;

         // Create the FileOpenDialog object.
         HRESULT hr = pfileopen.CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_ALL);

         if (SUCCEEDED(hr))
         {

            if (set["folder"].get_string().get_length() > 0)
            {

               wstring wstr(set["folder"].get_string());

               comptr < IShellItem > psi;

               hr = SHCreateItemFromParsingName(wstr, NULL, IID_IShellItem, (void **)&psi);

               if (SUCCEEDED(hr))
               {

                  pfileopen->SetFolder(psi);

               }

            }

            pfileopen->SetOptions(FOS_PATHMUSTEXIST | FOS_PICKFOLDERS);

            // Show the Open dialog box.
            hr = pfileopen->Show(NULL);

            if (SUCCEEDED(hr))
            {

               // Get the file name from the dialog box.
               comptr < IShellItem > pitem;

               hr = pfileopen->GetResult(&pitem);

               if (SUCCEEDED(hr))
               {

                  cotaskp(PWSTR) pwszFilePath;

                  hr = pitem->GetDisplayName(SIGDN_FILESYSPATH, &pwszFilePath);

                  // Display the file name to the user.
                  if (SUCCEEDED(hr))
                  {

                     set["path"] = string((PWSTR)pwszFilePath);

                     bOk = true;

                  }

               }

            }

         }

      }
      catch (...)
      {

      }

      try
      {

         ::EnableWindow(oswindowOwner, TRUE);

         ::SetWindowPos(oswindowOwner, HWND_TOP, 0, 0, 0, 0, SWP_SHOWWINDOW);

         ::SetForegroundWindow(oswindowOwner);

         ::BringWindowToTop(oswindowOwner);

      }
      catch (...)
      {


      }

      return bOk;


   }

} // namespace windows








// CreateLink - Uses the Shell's IShellLink and IPersistFile interfaces
//              to create and store a shortcut to the specified object.
//
// Returns the result of calling the member functions of the interfaces.
//
// Parameters:
// lpszPathObj  - Address of a buffer that contains the path of the object,
//                including the file name.
// lpszPathLink - Address of a buffer that contains the path where the
//                Shell link is to be stored, including the file name.
// lpszDesc     - Address of a buffer that contains a description of the
//                Shell link, stored in the Comment field of the link
//                properties.


HRESULT win_create_link(LPCWSTR lpszPathObj, LPCWSTR lpszPathLink, LPCWSTR lpszDesc, LPCWSTR lpszIconPath, INT iIcon)
{

   HRESULT hres;

   IShellLinkW* psl;

   defer_co_initialize_ex(false);

   // Get a pointer to the IShellLink interface. It is assumed that CoInitialize
   // has already been called.
   hres = CoCreateInstance(CLSID_ShellLink, NULL, CLSCTX_INPROC_SERVER, IID_IShellLinkW, (LPVOID*)&psl);
   if (SUCCEEDED(hres))
   {
      IPersistFile* ppf;

      // set the path to the shortcut target and add the description.
      psl->SetPath(lpszPathObj);
      psl->SetDescription(lpszDesc);
      if (lpszIconPath != NULL && *lpszIconPath != L'\0')
      {
         psl->SetIconLocation(lpszIconPath, iIcon);
      }

      // Query IShellLink for the IPersistFile interface, used for saving the
      // shortcut in persistent storage.
      hres = psl->QueryInterface(IID_IPersistFile, (LPVOID*)&ppf);

      if (SUCCEEDED(hres))
      {
         //WCHAR wsz[MAX_PATH];

         // Ensure that the string is Unicode.
         //            MultiByteToWideChar(CP_ACP, 0, lpszPathLink, -1, wsz, MAX_PATH);

         // Add code here to check return value from MultiByteWideChar
         // for success.

         // Save the link by calling IPersistFile::Save.
         hres = ppf->Save(lpszPathLink, TRUE);
         ppf->Release();
      }
      psl->Release();
   }
   return hres;

}





CLASS_DECL_AURA HRESULT os_create_link(::file::path pathObj, ::file::path pathLnk, string strDesc, ::file::path pathIco, int iIcon)
{

   wstring wstrObj(pathObj);
   wstring wstrLnk(pathLnk);
   wstring wstrDsc(strDesc);
   wstring wstrIco(pathIco);

   return win_create_link(wstrObj, wstrLnk, wstrDsc, wstrIco, iIcon);

}
