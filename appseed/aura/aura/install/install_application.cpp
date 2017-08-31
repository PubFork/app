#include "framework.h"

#define ID_ONE 1

#if defined(INSTALL_SUBSYSTEM)


namespace install
{


   application::application() :
      m_rxchannel(this)
   {

      m_bRunMainLoop = true;
      
      m_pwindow = NULL;

      m_bAdmin = false;

      m_dProgress = -1.0;
      
      m_dProgress1 = -1.0;
      
      m_dProgress2 = -1.0;

      m_pthreadSsl = NULL;
#ifdef WINDOWS

      m_hinstance = ::GetModuleHandleA(NULL);
      
#endif

      m_hmutexSpabootInstall = NULL;

      m_emessage = message_none;

      m_bInstallerInstalling = false;

      construct(NULL);


   }


   application::~application()
   {


   }





   void application::defer_show_debug_box()
   {

      if (::file_exists_dup(::dir::system() / "config/spa/beg_debug_box.txt"))
      {

         string str;

         if (install_get_admin())
         {

            str = "zzzAPPzzz app_appadmin : ";

         }
         else
         {

            str = "zzzAPPzzz install : ";

         }

         str += System.os().get_command_line();

         ::MessageBoxA(NULL, str.c_str(), "zzzAPPzzz install", MB_ICONINFORMATION);

      }


   }


   bool application::initialize_app_install()
   {

      string strMutex;

      strMutex = "Global\\::ca2::fontopus::ca2_spaboot_install_" + process_platform_dir_name2() + "::7807e510-5579-11dd-ae16-0800200c7784";

      m_spmutexAppInstall = canew(::mutex(this, false, strMutex));

      if (m_spmutexAppInstall->already_exists())
      {

         m_iReturnCode = -202;

         return false;

      }

      m_rxchannel.m_preceiver = this;

      prepare_small_bell();

      string strChannel;

      strChannel = "::ca2::fontopus::ca2_spaboot_install_" + process_platform_dir_name2() + "::7807e510-5579-11dd-ae16-0800200c7784";

      if (!m_rxchannel.create(strChannel))
      {

         m_iReturnCode = -1;

         return false;

      }

      return true;

   }


   bool application::start_instance()
   {

      defer_show_debug_box();

      System.m_bMatterFromHttpCache = true;

      m_pinstaller = new class ::install::installer(this);

      System.oprop("do_not_initialize_user_presence") = true;

      return true;

   }


   void application::on_request(::create * pcreate)
   {

#ifdef WINDOWS
      ::CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);
      
#endif

      // this is currently hard-coded:
      System.dir().m_pathCa2Module = dir::program_files_x86() / "ca2/time" / process_platform_dir_name() / System.get_system_configuration();

      System.dir().m_strCa2 = dir::program_files_x86() / "ca2";

      if (install_get_admin())
      {

         m_strInstallTraceLabel = "app-admin-" + System.get_system_configuration() + "-" + ::str::from(OSBIT);

         start_web_server();

         manual_reset_event ev86(this);

         ev86.ResetEvent();

         manual_reset_event ev64(this);

         ev64.ResetEvent();

         ::fork(this, [&]()
         {

            try
            {

#ifdef WINDOWS
               ::CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);
               
#endif

               m_bootstrap["admin:x86"] = new bootstrap(this);

               m_bootstrap["admin:x86"]->m_strTraceLabel = "bootstrap-admin-" + System.get_system_configuration() + "-x86";

               m_bootstrap["admin:x86"]->admin_main("x86");

            }
            catch (...)
            {

            }

            ev86.SetEvent();

         });

         ::fork(this, [&]()
         {

            try
            {

#ifdef WINDOWS
               ::CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);

               m_bootstrap["admin:x64"] = new bootstrap(this);

               m_bootstrap["admin:x64"]->m_strTraceLabel = "bootstrap-admin-" + System.get_system_configuration() + "-x64";

               m_bootstrap["admin:x64"]->admin_main("x64");

#endif
            }
            catch (...)
            {

            }

            ev64.SetEvent();

         });

         ev86.wait();

         ev64.wait();

         ::file::path pathOfficialAdmin = System.dir().m_pathCa2Module / "app_app_admin.exe";

         ::file::path pathThis = ::path::module();

         if (pathThis.compare_ci(pathOfficialAdmin) == 0)
         {

            if (!initialize_app_install())
            {

               System.post_quit();

            }

         }
         else
         {

            start_program_files_app_app_admin(process_platform_dir_name());

         }

      }
      else
      {

         m_strInstallTraceLabel = "install-" + System.get_system_configuration() + "-" + ::str::from(OSBIT);

         m_iReturnCode = app_app_main();

      }

   }


   void application::add_command_line(string str)
   {

      {

         ::mutex mutexCommandFile(get_thread_app(), "Local\\ca2_spa_command:" + process_platform_dir_name2());

         ::file::path path = ::dir::system() / process_platform_dir_name2() / "spa_command.txt";

         stringa stra;
         
         if(file_load_stra(path, stra, false))
         {

            stra.add_unique_ci(str);

            file_save_stra(path, stra);

         }

      }

   }


   string application::pick_command_line()
   {

      ::mutex mutexCommandFile(get_thread_app(), "Local\\ca2_spa_command:" + process_platform_dir_name2());

      ::file::path path = ::dir::system() / process_platform_dir_name2() / "spa_command.txt";

      stringa stra;

      if (!file_load_stra(path, stra, false))
      {

         return "";

      }

      if (stra.is_empty())
      {

         return "";

      }

      string str;

      str = stra[0];

      stra.remove_ci(str);

      file_save_stra(path, stra);

      return str;

   }


   bool application::show_window()
   {

      if (m_pwindow == NULL)
      {

         m_pwindow = new window(this);

      }
      
#ifdef WINDOWS

      if (!::IsWindow(m_pwindow->m_hwnd))
      {

         if (!m_pwindow->create())
         {

            return false;

         }

      }

      if (!m_pwindow->show())
      {

         return false;

      }
      
#endif

      return true;

   }


   bool application::hide_window()
   {

      if (m_pwindow == NULL)
      {

         return true;

      }
      
#ifdef WINDOWS

      if (!::IsWindow(m_pwindow->m_hwnd))
      {

         return true;

      }

      if (!m_pwindow->hide())
      {

         return false;

      }
      
#endif

      return true;

   }


   int application::app_app_main()
   {

      ::install::mutex mutex(process_platform_dir_name2());

      if (mutex.already_exists())
      {

         add_command_line(System.os().get_command_line());

         return -34;

      }

      string str(System.os().get_command_line());

      if (str.find(" install ") < 0)
      {

         if (check_soon_launch(str, true, m_dwInstallGoodToCheckAgain))
         {

            return 0;

         }

      }

      add_command_line(str);

      if (!show_window())
      {

         return -1;

      }

      start_web_server();

      if (!start_app_app(process_platform_dir_name2()))
      {

         return -2;

      }

      m_pwindow->main();

      return m_iReturnCode;

   }

   


   int application::start_app_app(string strPlatform)
   {

      m_bFinished = false;

      m_bootstrap[strPlatform] = new bootstrap(this);

      m_bootstrap[strPlatform]->m_pthreadInstall = ::fork(this, [=]()
      {
         
#ifdef WINDOWS
         
         ::CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);
         
#endif

         m_bootstrap[strPlatform]->m_strPlatform = strPlatform;

         m_bootstrap[strPlatform]->m_strTraceLabel = "bootstrap-" + System.get_system_configuration() + "-" + strPlatform;

         try
         {

            m_iReturnCode = m_bootstrap[strPlatform]->install();

         }
         catch (...)
         {

         }

         end_app_app();

         m_bFinished = true;

         return m_iReturnCode;

      });

      return 1;

   }



   
   void application::start_web_server()
   {

      if (m_pthreadSsl == NULL)
      {

         m_pthreadSsl = new socket_thread(this);

         m_pthreadSsl->m_iSsl = 1;

         m_pthreadSsl->m_strIp = "127.0.0.1";
         
#ifdef WINDOWS

         m_pthreadSsl->m_strCat = "cat://" + read_resource_as_string_dup(NULL, ID_ONE, "CAT");

         if (install_get_admin())
         {
#if OSBIT == 32
            if (m_pthreadSsl->m_iSsl > 0)
            {
               m_pthreadSsl->m_iPort = (port_t)57332;
            }
            else
            {
               m_pthreadSsl->m_iPort = (port_t)37332;
            }
#else
            if (m_pthreadSsl->m_iSsl > 0)
            {
               m_pthreadSsl->m_iPort = (port_t)57364;
            }
            else
            {
               m_pthreadSsl->m_iPort = (port_t)37364;
            }
#endif
         }
         else
         {
#if OSBIT == 32
            if (m_pthreadSsl->m_iSsl > 0)
            {
               m_pthreadSsl->m_iPort = (port_t)57232;
            }
            else
            {
               m_pthreadSsl->m_iPort = (port_t)37232;
            }
#else
            if (m_pthreadSsl->m_iSsl > 0)
            {
               m_pthreadSsl->m_iPort = (port_t)57264;
            }
            else
            {
               m_pthreadSsl->m_iPort = (port_t)37264;
            }
#endif
         }
         
#endif

         m_pthreadSsl->begin();

      }

   }


   bool application::install_get_admin()
   {
      
      return m_bAdmin;

   }


   void application::install_set_admin(bool bSet)
   {

      m_bAdmin = bSet;

   }



   bool application::is_user_service_running()
   {

      ::mutex mutex(get_thread_app(), "Local\\ca2_application_local_mutex:application-core/user_service");

      return mutex.already_exists();

   }









   //string application::get_version(string strVersion)
   //{
   //   static string  s_strVersion;

   //   if (strVersion.has_char())
   //   {
   //      s_strVersion = strVersion;
   //   }

   //   if (s_strVersion.is_empty())
   //   {
   //      if (_ca_is_basis())
   //      {
   //         s_strVersion = "basis";
   //      }
   //      else
   //      {
   //         s_strVersion = "stage";
   //      }
   //   }

   //   return s_strVersion;
   //}










   
   void application::install_set_id(const char * psz)
   {

      m_strInstallBuild = psz;

   }




   //string application::get_latest_build_number(const char * pszVersion)
   //{

   //   if (m_strBuild.length() > 0)
   //   {

   //      return m_strBuild;

   //   }

   //   string strBuildNumber;

   //   string strSpaIgnitionBaseUrl;

   //   string strVersion(pszVersion);

   //   if (file_as_string_dup("C:\\ca2\\config\\system\\ignition_server.txt").length() > 0)
   //   {

   //      strSpaIgnitionBaseUrl = "https://" + file_as_string_dup("C:\\ca2\\config\\system\\ignition_server.txt") + "/api/spaignition";

   //   }
   //   else if (pszVersion != NULL && !strcmp(pszVersion, "basis"))
   //   {

   //      strSpaIgnitionBaseUrl = "https://server.ca2.cc/api/spaignition";

   //   }
   //   else if (pszVersion != NULL && !strcmp(pszVersion, "stage"))
   //   {

   //      strSpaIgnitionBaseUrl = "https://server.ca2.cc/api/spaignition";

   //   }
   //   else
   //   {

   //      if (m_strVersion == "basis")
   //      {

   //         strVersion = "basis";

   //         strSpaIgnitionBaseUrl = "https://server.ca2.cc/api/spaignition";

   //      }
   //      else
   //      {

   //         strVersion = "stage";

   //         strSpaIgnitionBaseUrl = "https://server.ca2.cc/api/spaignition";

   //      }

   //   }

   //   int iRetry = 0;

   //RetryBuildNumber:

   //   if (iRetry > 10)
   //   {

   //      return "";

   //   }

   //   iRetry++;

   //   strBuildNumber = http_get(strSpaIgnitionBaseUrl + "/query?node=build&configuration=" + strVersion);

   //   ::str::_008Trim(strBuildNumber);

   //   if (strBuildNumber.length() != 19)
   //   {

   //      Sleep(100 * iRetry);

   //      goto RetryBuildNumber;

   //   }

   //   return strBuildNumber;

   //}

   




   void application::on_receive(::aura::ipc::rx * prx, const char * pszMessage)
   {

      string strMessage(pszMessage);

      int32_t iRet = 0;

      if (::str::begins_eat_ci(strMessage, "appinstall:"))
      {

         if (System.install().is_installing_ca2())
         {

            iRet = 1;

            return;

         }

         if (m_bInstallerInstalling)
         {

            iRet = 1;

            return;

         }

         m_bInstallerInstalling = true;

         m_pinstaller->install(strMessage);

         m_bInstallerInstalling = false;

      }
      else if (stricmp_dup(strMessage, "ok") == 0)
      {

         m_emessage = message_ok;

      }
      else if (stricmp_dup(strMessage, "failed") == 0)
      {

         m_emessage = message_failed;

      }
      else if (stricmp_dup(strMessage, "exit") == 0)
      {

         post_quit();

      }
      else if (stricmp_dup(strMessage, "quit") == 0)
      {

         post_quit();

      }
      else
      {

         m_emessage = message_unknown;

      }

   }


   int32_t application::exit_application()
   {

      ::aura::application::exit_application();


      if(m_pwindow != NULL)
      {

         ::aura::del(m_pwindow);


      }

      ::aura::del(m_pinstaller);

      return true;

   }


   bool application::are_ca2_framework_shared_libraries_busy()
   {

      stringa stra({ "aura.dll", "axis.dll", "base.dll", "core.dll" });

      ::file::patha patha;

      patha = dir::stage(process_platform_dir_name()) / stra;

      stra.copy_iter(patha);

      if (is_shared_library_busy(stra))
      {

         return true;

      }

      return false;

   }

   void application::get_system_locale_schema(string & strLocale, string & strSchema)
   {

#if defined(WINDOWS)

      LANGID langid = ::GetUserDefaultLangID();

#define SPR_DEUTSCH LANG_GERMAN

      if (langid == LANG_SWEDISH)
      {
         strLocale = "se";
         strSchema = "se";
      }
      else if (langid == MAKELANGID(LANG_PORTUGUESE, SUBLANG_PORTUGUESE_BRAZILIAN))
      {
         strLocale = "pt-br";
         strSchema = "pt-br";
      }
      else if (PRIMARYLANGID(langid) == SPR_DEUTSCH)
      {
         strLocale = "de";
         strSchema = "de";
      }
      else if (PRIMARYLANGID(langid) == LANG_ENGLISH)
      {
         strLocale = "en";
         strSchema = "en";
      }
      else if (PRIMARYLANGID(langid) == LANG_JAPANESE)
      {
         strLocale = "jp";
         strSchema = "jp";
      }
      else if (PRIMARYLANGID(langid) == LANG_POLISH)
      {
         strLocale = "pl";
         strSchema = "pl";
      }

#endif

      if (strLocale.length() <= 0)
         strLocale = "_std";

      if (strSchema.length() <= 0)
         strSchema = "_std";

   }



   void application::end_app_app()
   {

      m_bRunMainLoop = false;

      System.post_quit();


   }


   string application::install_get_id()
   {

      return m_strInstallId;

   }


} // namespace install



#endif





DWORD install_status::calc_when_is_good_to_check_again()
{

   // by default it is good to check again any time sooner
   DWORD dwGoodToCheckAgain = MAX(1, get_tick_count()) - 1;

   if (m_bOk)
   {

      if (m_iCheck > 1)
      {

         // The first and previous probes were not ok and now it is ok,
         // signal it is better to wait a bit to proceed (5s)
         // (a new check can be issued but must not probe for the moment, it should just return true)

         dwGoodToCheckAgain += 5000;

      }

   }
   else
   {

      if (m_iCheck < 4)
      {

         // After the first few failed probes,
         // a sooner check (sooner compared to the *on duty* mode) is suggested, because the
         // solution (installation, update) may be short

         dwGoodToCheckAgain += 3500; // pragmatic pardon, because we know** (it can be short)

      }
      else if (m_iCheck < 10)
      {

         // "On Duty" mode
         // It already took long on failed probes,
         // so suggest to really wait more (coffee, lunch, sleep, vacation)

         dwGoodToCheckAgain += 7000; // pardon precisely infinite - sometimes you find it was never reckt, because was never there? (ghost, devil, "not-blood-and-meat", ::not-actually-present,Imean,SorryTheSystemRequiresAuthenticationAndComingToOfficeToValidateTheRemoteAccessForExampleJustBecauseThereAreSoMany*)

      }
      else
      {

         // "Hell Mode"
         // Can check again as crazy, until the patient goes away
         // ("Will it ever happen to install, update or whatever?" is a hell isn't it?)

         dwGoodToCheckAgain += 250;

      }

   }

   return dwGoodToCheckAgain;

}



