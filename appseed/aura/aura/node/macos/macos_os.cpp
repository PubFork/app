#include "framework.h"
#include "macos.h"
#include "aura/aura/os/os.h"
#include "aura/aura/os/os_os.h"
#if defined(MACOS)
#include <sys/stat.h>
#endif

#undef USERNAME_LENGTH // mysql one

char * ns_get_default_browser_path();
void ns_set_this_process_binary_default_browser();

namespace macos
{

   ::file::path get_default_browser_path()
   {
      
      string strPath;
      
      char * psz = ns_get_default_browser_path();
      
      strPath = psz;
      
      ::str::begins_eat_ci(strPath, "file://");
      
      free(psz);
      
      ::file::path path;
      
      path = strPath;
      
      return path;
      
   }


   os::os(::aura::application * papp) :
   ::object(papp),
   ::aura::os(papp)
   {
   }


   os::~os()
   {
   }

   
   string os::get_command_line()
   {
    
      return get_command_line_dup();
      
   }
   

   bool os::shutdown(bool bIfPowerOff)
   {
      /*      bool retval = true;
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
       return retval;*/

    //  _throw(not_implemented(get_app()));
      return false;

   }

   bool os::reboot()
   {
      /*      HANDLE hToken;
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


       if(!WTSShutdownSystem(WTS_CURRENT_SERVER_HANDLE, WTS_WSD_REBOOT))
       {
       TRACELASTERROR();
       return false;
       }
       if (!ExitWindowsEx(EWX_REBOOT | EWX_FORCE,
       SHTDN_REASON_MAJOR_SOFTWARE | SHTDN_REASON_MINOR_INSTALLATION))
       {
       DWORD dwLastError = ::get_last_error();
       return false;
       }*/
      //reset the previlages
      /*    tkp.Privileges[0].Attributes = 0;
       AdjustTokenPrivileges(hToken, FALSE, &tkp, 0, (PTOKEN_PRIVILEGES) NULL, 0);
       return true;*/
  //    _throw(not_implemented(get_app()));
      return false;

   }

   void os::terminate_processes_by_title(const char * pszName)
   {
//      _throw(not_implemented(get_app()));
      return;

      /*      DWORD dwPid;
       while(get_pid_by_title(pszName, dwPid))
       {
       HANDLE hProcess = OpenProcess( PROCESS_QUERY_INFORMATION |
       PROCESS_VM_READ,
       FALSE, dwPid );
       TerminateProcess(hProcess, (UINT) -1);
       CloseHandle(hProcess);
       ::EnumWindows((WNDENUMPROC)
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

      //  }
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

   ::file::path os::get_process_path(DWORD dwPid)
   {
      /*
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
       return strName;*/
  //    _throw(not_implemented(get_app()));
      return "";

   }

   void os::get_all_processes(uint_array & dwa )
   {

    //  _throw(not_implemented(get_app()));
      return;

      /*
       dwa.set_size(0);
       DWORD cbNeeded = 0;
       while(cbNeeded == natural(dwa.get_count()))
       {
       dwa.set_size(dwa.get_count() + 1024);
       if(!EnumProcesses(
       dwa.get_data(),
       (DWORD) (dwa.get_count() * sizeof(DWORD)),
       &cbNeeded))
       {
       return;
       }
       dwa.set_size(cbNeeded / sizeof(DWORD));
       }*/
   }



   bool os::connection_settings_get_auto_detect()
   {
//      _throw(not_implemented(get_app()));
      return false;

      /*
       registry::Key key1;

       key1.OpenKey(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\Internet Settings\\Connections", false);

       memory mem;

       key1.QueryValue("DefaultConnectionSettings", mem);

       bool bAutoDetect = (((LPBYTE) mem.get_data())[8] & 0x08) != 0;

       return bAutoDetect;
       */
   }



   string os::connection_settings_get_auto_config_url()
   {

//      _throw(not_implemented(get_app()));
      return "";
      /*
       registry::Key key;

       key.OpenKey(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\Internet Settings", false);

       string strUrl;

       key.QueryValue("AutoConfigURL", strUrl);

       return strUrl;
       */
   }

   bool os::local_machine_set_run(const char * pszKey, const char * pszCommand)
   {

 //     _throw(not_implemented(get_app()));
      return false;

      /*
       registry::Key keyKar(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", true);


       keyKar.SetValue(pszKey, pszCommand);


       return true;
       */
   }


   bool os::local_machine_set_run_once(const char * pszKey, const char * pszCommand)
   {


 //     _throw(not_implemented(get_app()));
      return false;
      /*    registry::Key keyKar(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\RunOnce", true);


       keyKar.SetValue(pszKey, pszCommand);
       */

      return false;

   }

   bool os::current_user_set_run(const char * pszKey, const char * pszCommand)
   {

   //   _throw(not_implemented(get_app()));
      return false;

      /*
       registry::Key keyKar(HKEY_CURRENT_USER, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", true);


       keyKar.SetValue(pszKey, pszCommand);
       */

      return false;

   }

   bool os::current_user_set_run_once(const char * pszKey, const char * pszCommand)
   {

 //    _throw(not_implemented(get_app()));
      return false;

      /*
       registry::Key keyKar(HKEY_CURRENT_USER, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\RunOnce", true);


       keyKar.SetValue(pszKey, pszCommand);

       */
      return false;

   }


   bool os::defer_register_ca2_plugin_for_mozilla()
   {
  //    _throw(not_implemented(get_app()));
      return false;

      /*
       registry::Key keyPlugins;

       if(keyPlugins.OpenKey(HKEY_LOCAL_MACHINE, "SOFTWARE\\MozillaPlugins", true))
       {

       registry::Key keyPlugin;

       if(keyPlugin.OpenKey(keyPlugins, "@ca2.cc/npca2", true))
       {

       keyPlugin.SetValue("Description", "ca2 plugin for NPAPI");
       keyPlugin.SetValue("Path", System.m_strCa2Module("npca2.dll"));
       keyPlugin.SetValue("ProductName", "ca2 plugin for NPAPI");
       keyPlugin.SetValue("Vendor", "ca2 Desenvolvimento de Software Ltda.");
       keyPlugin.SetValue("Version", Application.file_as_string(System.dir().ca2("appdata/x86/ca2_build.txt")));

       registry::Key keyApplicationCa2;

       if(keyApplicationCa2.OpenKey(keyPlugin, "application/ca2", true))
       {

       keyApplicationCa2.SetValue("Description", "ca2 Document");

       }

       }

       }

       return true;
       */
   }

   bool os::file_extension_get_open_with_list_keys(stringa & straKey, const char * pszExtension)
   {
   //   _throw(not_implemented(get_app()));
      return false;

      /*
       string strExt;

       strExt = ".";
       strExt += pszExtension;

       string strOpenWithKey;
       strOpenWithKey = strExt + "\\OpenWithList";

       registry::Key key;

       key.OpenKey(HKEY_CLASSES_ROOT, strOpenWithKey, false);

       key.EnumKey(straKey);

       return true;
       */
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

  //    _throw(not_implemented(get_app()));
      return false;

      /*
       string strExtensionNamingClass(pszExtensionNamingClass);

       registry::Key keyLink3(HKEY_CLASSES_ROOT, strExtensionNamingClass, true);
       keyLink3.SetValue("DefaultIcon", pszIconPath);


       return false;
       */
   }


   bool os::file_association_set_shell_open_command(const char * pszExtension, const char * pszExtensionNamingClass,  const char * pszCommand, const char * pszParam)
   {
   //   _throw(not_implemented(get_app()));
      return false;

      /*
       string strExt;

       strExt = ".";
       strExt += pszExtension;

       string strExtensionNamingClass(pszExtensionNamingClass);

       registry::Key key(HKEY_CLASSES_ROOT, strExt, true);
       key.SetValue(NULL, strExtensionNamingClass);

       registry::Key keyLink3(HKEY_CLASSES_ROOT, strExtensionNamingClass + "\\shell", true);
       keyLink3.SetValue(NULL, "open");

       registry::Key keyLink2(keyLink3, "open", true);
       keyLink2.SetValue(NULL, "&Abrir");

       registry::Key keyLink1(keyLink2, "command", true);

       string strFormat;
       strFormat.Format("\"%s\" \"%%L\" %s", pszCommand, pszParam);
       keyLink1.SetValue(NULL, strFormat);

       return true;
       */
   }

   bool os::file_association_get_shell_open_command(const char * pszExtension, string & strExtensionNamingClass, string & strCommand, string & strParam)
   {
  //    _throw(not_implemented(get_app()));
      return false;

      /*
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
       */
   }

   bool os::open_in_ie(const char * lpcsz)
   {

  //    _throw(not_implemented(get_app()));
      return false;

      /*    registry reg;
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
       */

   }

   bool os::create_service(sp(::aura::application) papp)
   {

  //    _throw(not_implemented(get_app()));
      return false;

      /*
       if(papp->m_strAppName.is_empty()
       || papp->m_strAppName.compare_ci("bergedge") == 0
       || !papp->is_serviceable())
       return false;

       SC_HANDLE hdlSCM = OpenSCManager(0, 0, SC_MANAGER_CREATE_SERVICE);

       string strCalling = papp->m_strModulePath + " : app=" + papp->m_strAppId + " service usehostlogin";

       if(hdlSCM == 0)
       {
       //::get_last_error()
       return false;
       }

       SC_HANDLE hdlServ = ::CreateService(
       hdlSCM,                    // SCManager database
       "core-" + papp->m_strAppName,               // name of service
       "ccvotagus ca2 fontopus " + papp->m_strAppName,        // service name to display
       STANDARD_RIGHTS_REQUIRED,  // desired access
       SERVICE_WIN32_OWN_PROCESS | SERVICE_INTERACTIVE_PROCESS, // service type
       SERVICE_AUTO_START,      // start type
       SERVICE_ERROR_NORMAL,      // error control type
       strCalling,                   // service's binary Path name
       0,                      // no load ordering group
       0,                      // no tag identifier
       0,                      // no dependencies
       0,                      // LocalSystem account
       0);                     // no password

       if (!hdlServ)
       {
       CloseServiceHandle(hdlSCM);
       //Ret = ::get_last_error();
       return FALSE;
       }

       CloseServiceHandle(hdlServ);
       CloseServiceHandle(hdlSCM);

       return true;
       */

   }


   bool os::remove_service(sp(::aura::application) papp)
   {
   //   _throw(not_implemented(get_app()));
      return false;

      /*
       if(papp->m_strAppName.is_empty()
       || papp->m_strAppName.compare_ci("bergedge") == 0
       || !papp->is_serviceable())
       return false;

       SC_HANDLE hdlSCM = OpenSCManager(0, 0, SC_MANAGER_ALL_ACCESS);

       if(hdlSCM == 0)
       {
       //::get_last_error();
       return false;
       }

       SC_HANDLE hdlServ = ::OpenService(
       hdlSCM,                    // SCManager database
       "core-" + papp->m_strAppName,               // name of service
       DELETE);                     // no password

       if (!hdlServ)
       {
       // Ret = ::get_last_error();
       CloseServiceHandle(hdlSCM);
       return false;
       }

       ::DeleteService(hdlServ);

       CloseServiceHandle(hdlServ);

       CloseServiceHandle(hdlSCM);

       return false;
       */
   }

   bool os::start_service(sp(::aura::application) papp)
   {
    //  _throw(not_implemented(get_app()));
      return false;

      /*
       if(papp->m_strAppName.is_empty()
       || papp->m_strAppName.compare_ci("bergedge") == 0
       || !papp->is_serviceable())
       return false;

       SC_HANDLE hdlSCM = OpenSCManager(0, 0, SC_MANAGER_ALL_ACCESS);

       if(hdlSCM == 0)
       {
       //::get_last_error();
       return false;
       }

       SC_HANDLE hdlServ = ::OpenService(
       hdlSCM,                    // SCManager database
       "core-" + papp->m_strAppName,               // name of service
       SERVICE_START);                     // no password


       if (!hdlServ)
       {
       CloseServiceHandle(hdlSCM);
       //Ret = ::get_last_error();
       return FALSE;
       }

       bool bOk = StartService(hdlServ, 0, NULL) != FALSE;

       CloseServiceHandle(hdlServ);
       CloseServiceHandle(hdlSCM);

       return bOk != FALSE;
       */
   }

   bool os::stop_service(sp(::aura::application) papp)
   {
  //    _throw(not_implemented(get_app()));
      return false;

      /*
       if(papp->m_strAppName.is_empty()
       || papp->m_strAppName.compare_ci("bergedge") == 0
       || !papp->is_serviceable())
       return false;

       SC_HANDLE hdlSCM = OpenSCManager(0, 0, SC_MANAGER_ALL_ACCESS);

       if(hdlSCM == 0)
       {
       //::get_last_error();
       return false;
       }

       SC_HANDLE hdlServ = ::OpenService(
       hdlSCM,                    // SCManager database
       "core-" + papp->m_strAppName,               // name of service
       SERVICE_STOP);                     // no password

       if (!hdlServ)
       {
       // Ret = ::get_last_error();
       CloseServiceHandle(hdlSCM);
       return false;
       }

       SERVICE_STATUS ss;

       memset(&ss, 0, sizeof(ss));

       bool bOk = ::ControlService(hdlServ, SERVICE_CONTROL_STOP, &ss) != FALSE;

       ::DeleteService(hdlServ);

       CloseServiceHandle(hdlServ);

       CloseServiceHandle(hdlSCM);

       return bOk != FALSE;
       */
   }

   bool os::resolve_link(string & strTarget, string & strFolder, string & strParams, const string & strSource, ::user::primitive * puiMessageParentOptional)
   {

//      _throw(not_implemented(get_app()));
      
      strTarget = strSource;
      
      return true;

      //      return vfxResolveShortcut(strTarget, pszSource, puiMessageParentOptional);

   }

   void os::raise_exception( DWORD dwExceptionCode, DWORD dwExceptionFlags)
   {

      _throw(not_implemented(get_app()));
      return;
      /*
       RaiseException( dwExceptionCode, dwExceptionFlags, 0, NULL );
       */
   }

   bool os::is_remote_session()
   {

//      _throw(not_implemented(get_app()));
      return false;
      /*
       return GetSystemMetrics(SM_REMOTESESSION) != FALSE;
       */
   }
   
   int os::get_pid()
   {
      
      return getpid();
      
   }



   void os::post_to_all_threads(UINT message, WPARAM wparam, LPARAM lparam)
   {

//      _throw(not_implemented(get_app()));
      return;

   }


   bool os::initialize_wallpaper_fileset(::file::set * pfileset, bool bAddSearch)
   {

      if (bAddSearch)
      {

            //string strDir;
            //strDir = System.dir().path(getenv("HOME"), "Pictures");
            //pimagefileset->add_search(strDir);
            string strDir;
            strDir = "/Library/Desktop Pictures";
            pfileset->add_search(strDir, true);
      
      }

      return true;

   }
   
   bool os::get_default_browser(string & strId, ::file::path & path, string & strParam)
   {
      
      path = ::macos::get_default_browser_path();
      
      if(path.find_ci("chrome") >= 0)
      {
         
         strId = "chrome";
         
      }
      else if(path.find_ci("firefox") >= 0)
      {
         
         strId = "firefox";
         
      }
      else if(path.find_ci("commander") >= 0)
      {
         
         strId = "commander";
         
      }
      else
      {
         
         strId = "default";
         
      }
         
      return true;
      
   }


   bool os::set_default_browser(::aura::application * papp)
   {

      ns_set_this_process_binary_default_browser();

      return false;

   }

   ::file::path os::get_app_path(const string & strApp)
   {
      
      if(strApp.is_empty())
      {
         
         return "";
         
      }
      
      if(strApp.begins_ci("/Applications/"))
      {
         
         return strApp;
         
      }
      
      string strAppReturn;
      
      if(strApp.compare_ci("chrome") == 0)
      {
         
         strAppReturn = "Google Chrome";
         
      }
      else
      {
         
         strAppReturn = strApp;
         
      }
      
      strAppReturn.set_at(0, char_to_upper(strAppReturn[0]));
      
      strAppReturn = "/Applications/" + strAppReturn;
      
      if(!strAppReturn.ends_ci(".app"))
      {
         
         strAppReturn += ".app";
         
      }
      
      if(Application.dir().is(strAppReturn))
      {
         
         return strAppReturn;
         
      }
      
      strAppReturn = strApp;
      
      strAppReturn = "/Applications/" + strAppReturn;
      
      if(!strAppReturn.ends_ci(".app"))
      {
         
         strAppReturn += ".app";
         
      }
      
      return strAppReturn;
      
   }
   
   
   void os::on_process_command(::command::command * pcommand)
   {
      
      sp(::handler) phandler = System.handler();
      
      if(phandler->m_spcommandline->m_strExe[0] == '/')
      {
         
         ::file::path p;
         
         p = ::dir::ca2config();
         
         p /= "mypath" / phandler->m_spcommandline->m_varQuery.propset()["app"].get_string() + ".txt";
         
         file_put_contents_dup(p, phandler->m_spcommandline->m_strExe);
         
         string strApp = phandler->m_spcommandline->m_strExe;
         
         strsize iFind = strApp.find_ci(".app/");
         
         if(iFind > 0)
         {
            
            p = ::dir::ca2config();
            
            p /= "mypath" / phandler->m_spcommandline->m_varQuery.propset()["app"].get_string() + "-app";
            
            ::file::path p2;
            
            p2 = ::dir::ca2config();
            
            p2 /= "mypath" / ::file::path(phandler->m_spcommandline->m_varQuery.propset()["app"].get_string()).folder()/ ::file::path(strApp.Left(iFind + strlen(".app"))).name();
            
            ns_create_alias(p2, strApp.Left(iFind + strlen(".app")));
            
            if(::dir::is(::dir::local()/"localconfig/desk/2desk"))
            {
               
               ::file::path p3;
               
               p3 = ::dir::local()/"localconfig/desk/2desk"/::file::path(strApp.Left(iFind + strlen(".app"))).name();
               
               ns_create_alias(p3, strApp.Left(iFind + strlen(".app")));
               
            }
            
            file_put_contents_dup(p, "open -a \""+strApp.Left(iFind + strlen(".app")) + "\"");
            
            chmod(p, 0777);
            
         }
         
      }
      
   }
   
   void os::set_file_status(const char * lpszFileName, const ::file::file_status& status)
   {
      
      
//      DWORD wAttr;
//      FILETIME creationTime;
//      FILETIME lastAccessTime;
//      FILETIME lastWriteTime;
//      LPFILETIME lpCreationTime = NULL;
//      LPFILETIME lpLastAccessTime = NULL;
//      LPFILETIME lpLastWriteTime = NULL;
//      
//      wstring wstr(lpszFileName);
//      
//      if((wAttr = GetFileAttributesW(wstr)) == (DWORD)-1L)
//      {
//         
//         ::windows::file_exception::ThrowOsError(get_app(), (LONG)get_last_error());
//         
//      }
//      
//      if ((DWORD)status.m_attribute != wAttr && (wAttr & ::windows::file::readOnly))
//      {
//         
//         // set file attribute, only if currently readonly.
//         // This way we will be able to modify the time assuming the
//         // caller changed the file from readonly.
//         
//         if (!SetFileAttributesW(wstr, (DWORD)status.m_attribute))
//         {
//            
//            ::windows::file_exception::ThrowOsError(get_app(), (LONG)get_last_error());
//            
//         }
//         
//      }
//      
//      // last modification time
//      if (status.m_mtime.get_time() != 0)
//      {
//         
//         ::windows::TimeToFileTime(get_app(), status.m_mtime, &lastWriteTime);
//         
//         lpLastWriteTime = &lastWriteTime;
//         
//      }
//      
//      // last access time
//      if (status.m_atime.get_time() != 0)
//      {
//         
//         ::windows::TimeToFileTime(get_app(),status.m_atime, &lastAccessTime);
//         
//         lpLastAccessTime = &lastAccessTime;
//         
//      }
//      
//      // create time
//      if (status.m_ctime.get_time() != 0)
//      {
//         
//         ::windows::TimeToFileTime(get_app(),status.m_ctime, &creationTime);
//         
//         lpCreationTime = &creationTime;
//         
//      }
//      
//      HANDLE hFile = ::CreateFileW(wstr, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
//      
//      if(hFile == INVALID_HANDLE_VALUE)
//      {
//         
//         ::windows::file_exception::ThrowOsError(get_app(), (LONG)::get_last_error());
//         
//      }
//      
//      if(!SetFileTime((HANDLE)hFile, lpCreationTime, lpLastAccessTime, lpLastWriteTime))
//      {
//         
//         ::windows::file_exception::ThrowOsError(get_app(), (LONG)::get_last_error());
//         
//      }
//      
//      if(!::CloseHandle(hFile))
//      {
//         
//         ::windows::file_exception::ThrowOsError(get_app(), (LONG)::get_last_error());
//         
//      }
//      
//      if ((DWORD)status.m_attribute != wAttr && !(wAttr & ::windows::file::readOnly))
//      {
//         
//         if (!::SetFileAttributesW(wstr, (DWORD)status.m_attribute))
//         {
//            
//            ::windows::file_exception::ThrowOsError(get_app(), (LONG)get_last_error());
//            
//         }
//         
//      }
      

      
   }

   
   bool os::file_open(::file::path path, string strParams, string strFolder)
   {
      
      path = System.defer_process_path(path, ::get_app());
      
      ns_open_file(path.c_str());
      
      return true;
      
   }
   
   
} // namespace macos





