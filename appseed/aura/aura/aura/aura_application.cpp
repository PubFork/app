#include "framework.h"
#ifdef WINDOWSEX
#include "aura/aura/os/windows/windows_system_interaction_impl.h"
#endif

#ifdef LINUX
#include <sys/stat.h>
#include <fcntl.h>
#endif

extern "C"
{

   typedef void FN_ca2_factory_exchange(::aura::application * papp);

   typedef FN_ca2_factory_exchange * PFN_ca2_factory_exchange;

}



#ifdef WINDOWSEX

CLASS_DECL_AURA void windows_install_crash_dump_reporting(::aura::application * papp);

#endif

#ifdef METROWIN

CLASS_DECL_IMPORT void draw2d_factory_exchange(::aura::application * papp);

#endif

#ifdef MACOS
::file::path macos_app_path(string strApp);
void ns_app_terminate();
void ns_launch_app(const char * psz, const char ** argv);
#endif

#if defined(LINUX)
#ifdef _GNU_SOURCE
#undef _GNU_SOURCE

#include "aura/node/ansios/ansios.h"
#include "aura/node/linux/linux.h"

//#include <X11/cursorfont.h>
#include <sys/time.h>
#include <link.h>
#include <pthread.h>

#endif
#define _GNU_SOURCE
//#include <link.h>
#elif defined(APPLEOS)
//#include <dlfcn.h>
#elif defined(ANDROID)

#include "aura/node/ansios/ansios.h"
#include "aura/node/android/android.h"

//#elif defined(WINDOWSEX)

//#include "aura/aura/node/windows/windows_registry.h"

#endif


#if defined(APPLE_IOS) || defined(METROWIN)
CLASS_DECL_AURA int ui_open_url(const char * psz);
#endif


extern void * g_pf1;


namespace aura
{


   application_message::application_message(e_application_message esignal)
   {

      m_id = ::message::type_application;
      m_esignal = esignal;
      m_bOk = true;

   }


   application::application() :
      m_allocer(this),
      m_mutexMatterLocator(this),
      m_mutexStr(this)
   {


//      string strAppId = m_strAppId;
//
//      string strBuild = m_strBuild;
//
//      string strPlatform = m_strPlatform;
//
//      string strConfiguration = m_strConfiguration;
//
//      string strLocale = m_strLocale;
//
//      string strSchema = m_strSchema;

      m_strBuild = "installed";

      m_strLocale = "_std";

      m_strSchema = "_std";

      m_bSimpleMessageLoop = false;

      // default value for acid apps
      // (but any acid app can have installer, just change this flag to true in the derived application class constructor).
      m_bAppHasInstallerProtected = true;
      m_bAppHasInstallerChangedProtected = false;


      m_strHttpUserAgentToken = "ca2";
      m_strHttpUserAgentVersion = "1.0";

      m_http.set_app(this);

      m_eexclusiveinstance = ExclusiveInstanceNone;

      m_pevAppBeg = NULL;
      m_pevAppEnd = NULL;

      m_bAgreeExit = true;
      m_bAgreeExitOk = true;
      m_bFranceExit = true;

      //m_pmutex = new mutex(this);

      m_paurasystem = NULL;
      m_paurasession = NULL;
      m_paxisapp = NULL;
      m_paxissystem = NULL;
      m_paxissession = NULL;
      m_pbaseapp = NULL;
      m_pbasesystem = NULL;
      m_pbasesession = NULL;
      m_pcoreapp = NULL;
      m_pcoresystem = NULL;
      m_pcoresession = NULL;
      //m_peventReady = NULL;
      m_pimaging = NULL;


#ifdef WINDOWS

      m_hinstance = NULL;

#endif

      if (m_pauraapp == NULL)
      {

         m_pauraapp = this;

      }

      if (m_pauraapp != NULL)
      {

         m_paurasystem = m_pauraapp->m_paurasystem;

         m_paxissystem = m_pauraapp->m_paxissystem;

         m_paxissession = m_pauraapp->m_paxissession;

         m_paxisapp = m_pauraapp->m_paxisapp;

         m_pbasesystem = m_pauraapp->m_pbasesystem;

         m_pbasesession = m_pauraapp->m_pbasesession;

         m_pbaseapp = m_pauraapp->m_pbaseapp;

         m_pcoresystem = m_pauraapp->m_pcoresystem;

         m_pcoresession = m_pauraapp->m_pcoresession;

         m_pcoreapp = m_pauraapp->m_pcoreapp;

         if (m_pauraapp->m_paurasession == NULL && m_paurasystem != NULL)
         {

            m_paurasession = m_paurasystem->m_paurasession;

         }
         else
         {

            m_paurasession = m_pauraapp->m_paurasession;

         }

#ifdef WINDOWS

         m_hinstance = m_pauraapp->m_hinstance;

#endif

      }
      else
      {

         m_paurasystem = NULL;

      }


      m_puiptraFrame = new ::user::interaction_spa();


      //      m_pcoreapp                 = NULL;





      m_phandler = canew(::handler(this));

      m_bLicense = false;

      m_bAuraProcessInitialize = false;
      m_bAuraProcessInitializeResult = false;

      m_bAuraInitialize1 = false;
      m_bAuraInitialize1Result = false;

      m_bAuraInitialize = false;
      m_bAuraInitializeResult = false;

      m_bAuraInitializeInstance = false;
      m_bAuraInitializeInstanceResult = false;

#if defined(LINUX)

      ::linux::shell::theLinuxShell.Initialize();

#elif defined(ANDROID)

      ::android::shell::theLinuxShell.Initialize();

#endif // LINUX

   }


   void application::set_has_installer(bool bSet)
   {

      m_bAppHasInstallerProtected = bSet;

      m_bAppHasInstallerChangedProtected = true;

   }


   application::~application()
   {
      ::aura::del(m_puiptraFrame);
//      if (m_peventReady != NULL)
//      {
//
//         delete m_peventReady;
//
//      }

   }

   void application::assert_valid() const
   {

      thread::assert_valid();

   }


   void application::dump(dump_context & dumpcontext) const
   {

      thread::dump(dumpcontext);

#ifdef WINDOWS

      dumpcontext << "m_hinstance = " << (void *)m_hinstance;

#endif

      //dumpcontext << "\nm_strCmdLine = " << m_strCmdLine;
      //dumpcontext << "\nm_nCmdShow = " << m_nCmdShow;
      dumpcontext << "\nm_bHelpMode = " << m_strAppName;

      dumpcontext << "\n";

   }

   void application::install_message_routing(::message::sender * psender)
   {

      ::message::receiver::install_message_routing(psender);

      ::thread::install_message_routing(psender);

   }


   imaging & application::imaging()
   {

      return *m_pimaging;

   }


   string application::get_title()
   {

      if(m_strAppTitle.has_char())
      {

         return m_strAppTitle;

      }

      stringa stra;

      stra.explode("/", m_strAppName);

      string strTitle;

      if(stra.get_count() > 1)
      {

         strTitle = stra.implode("/", 1);

         if(strTitle.length() > 0)
         {

            return strTitle;

         }

      }

      if(m_strAppName.has_char())
      {

         return m_strAppName;

      }

      stra.explode("/", m_strAppId);

      if(stra.get_count() > 1)
      {

         strTitle = stra.implode("/", 1);

         if(strTitle.length() > 0)
         {

            return strTitle;

         }

      }

      if(m_strAppId.has_char())
      {

         return m_strAppId;

      }

      return System.file().module().title();

   }


   stringa application::get_categories()
   {

      return m_straAppCategory;

   }


   bool application::app_data_set(class id id, ::file::ostream & os)
   {

      return false;

   }


   bool application::app_data_get(class id id, ::file::istream & is)
   {

      return false;

   }


   bool application::app_data_set(class id id, ::file::serializable & obj)
   {

      return false;

   }


   bool application::app_data_get(class id id, ::file::serializable & obj)
   {

      return false;

   }


   void application::handle_command(::command::command * pcommand)
   {

      if (pcommand->m_ecommand == ::command_on_agree_exit)
      {

         m_bAgreeExit = _001OnAgreeExit();

         m_bAgreeExitOk = true;

      }
      else if (pcommand->m_ecommand == ::command_france_exit)
      {

         _001FranceExit();

      }
      else
      {

         ::thread::handle_command(pcommand);

      }

   }




//    void application::throw_not_installed()
//    {

//       _throw(not_installed(get_app(), m_strAppId, "application"));

//    }



   void application::on_create(::create * pcreate)
   {

      pcreate->set_app(this);

      try
      {

         on_request(pcreate);

      }
      // catch (not_installed * pexception)
      // {

      //    esp671 esp(pexception);

      //    System.on_run_exception(esp);

      //    _throw(exit_exception(esp->get_app(), ::exit_application));

      // }
      catch(exit_exception * pexception)
      {

         throw pexception;

      }
      catch(::exception::exception * pexception)
      {

         esp671 esp(pexception);

         if (!Application.on_run_exception(esp))
         {

            _throw(exit_exception(esp->get_app(), ::exit_application));

         }

      }

      // Verry Sory for the per request overhead here for the needed information of only first request
      if (System.m_dwAfterApplicationFirstRequest == 0)
      {

         System.m_dwAfterApplicationFirstRequest = ::get_tick_count(); // cross your fingers that the first recorded is not 0, it will be cleaned up by other requests.

      }

      try
      {

         pcreate->m_spCommandLine->m_varQuery["document"].unset();

      }
      catch (...)
      {

      }

      //sp(::core::session) pbergedge = pcreate->m_spCommandLine->m_varQuery["bergedge_callback"].cast < ::core::session >();
      // todobergedge
      /*if(pbergedge != NULL)
      {
      pbergedge->on_app_request_bergedge_callback(this);
      }*/
      pcreate->m_spCommandLine->m_eventReady.SetEvent();

   }

   //void application::tellme_destroyed(::user::primitive * pui, bool * pDestroyed, bool bTell)
   //{

   //   UNREFERENCED_PARAMETER(pui);
   //   UNREFERENCED_PARAMETER(pDestroyed);
   //   UNREFERENCED_PARAMETER(bTell);

   //}



   ::thread_toolset * application::create_thread_toolset(::thread::e_tool etool)
   {

      auto ptools = get_thread_tools();

      if (ptools == NULL)
      {

         return NULL;

      }

      if (etool == ::thread::tool_draw2d)
      {

         return ptools->create_thread_toolset < ::draw2d::thread_tool >();

      }

      return NULL;

   }


   int32_t application::simple_message_box(::user::primitive * puiOwner, const char * pszMessage, UINT fuStyle)
   {

      return ::simple_message_box(get_safe_handle(puiOwner), pszMessage, m_strAppName, fuStyle);

   }


   int32_t application::simple_message_box(const char * pszMessage, UINT fuStyle)
   {

      return ::simple_message_box(NULL, pszMessage, m_strAppName, fuStyle);

   }

   string application::message_box(const string & pszMatter, property_set & propertyset)
   {

      simple_message_box(pszMatter, 0);

      return "";

   }

   // lang string
   // load string
   string application::lstr(id id, string strDefault)
   {

      string str;

      if (!load_string(str, id))
      {

         if (strDefault.has_char())
            return strDefault;

         return "";

      }

      return str;

   }


   string application::load_string(id id)
   {
      string str;
      if (!load_string(str, id))
      {
         return (const string &)id;
      }
      return str;
   }

   bool application::load_string(string & str, id id)
   {
      if (!load_cached_string(str, id, true))
      {
         return false;
      }
      return true;
   }

   bool application::load_cached_string(string & str, id id, bool bLoadStringTable)
   {

      ::xml::document doc(this);

      if (!doc.load(id))
      {

         if (load_cached_string_by_id(str, id, bLoadStringTable))
         {

            return true;

         }

      }

      sp(::xml::node) pnodeRoot = doc.get_root();

      if (pnodeRoot->get_name() == "string")
      {

         string strId = pnodeRoot->attr("id");

         if (load_cached_string_by_id(str, strId, bLoadStringTable))
         {

            return true;
         }

         str = pnodeRoot->get_value();

         return true;

      }

      return false;

   }


   bool application::load_cached_string_by_id(string & str, id id, bool bLoadStringTable)
   {

      synch_lock sl(&m_mutexStr);

      string strId(id.str());

      string strTable;

      string strString;

      string_to_string * pmap = NULL;

      index iFind = 0;

      if ((iFind = strId.find(':')) <= 0)
      {

         strTable = "";

         strString = strId;

      }
      else
      {

         strTable = strId.Mid(0, iFind);

         strString = strId.Mid(iFind + 1);

      }

      if (m_stringtableStd.Lookup(strTable, pmap))
      {

         if (pmap->Lookup(strString, str))
         {

            return true;

         }

      }
      else if (m_stringtable.Lookup(strTable, pmap))
      {

         if (pmap->Lookup(strString, str))
         {

            return true;

         }

      }
      else if (bLoadStringTable)
      {

         load_string_table(strTable, "");

         return load_cached_string_by_id(str, id, false);

      }

      return false;

   }


   void application::load_string_table(const string & pszApp, const string & pszId)
   {

   }




   void application::load_string_table()
   {
      load_string_table("", "");
   }


   object * application::alloc(sp(type) info)
   {
      return System.alloc(this, info);
   }

   object * application::alloc(const  id & idType)
   {
      return System.alloc(this, idType);
   }

   bool application::is_system()
   {

      return false;

   }

   bool application::is_session()
   {

      return false;

   }


   bool application::is_serviceable()
   {

      return false;

   }


   bool application::is_user_service()
   {

      bool bIsUserService = true;

      bool bIsService = is_serviceable();

      return bIsUserService && bIsService;

   }


   bool application::app_map_lookup(const char * psz, ::aura::application * & p)
   {

      return m_appmap.Lookup(psz, p) != FALSE;

   }


   void application::app_map_set(const char * psz, ::aura::application * p)
   {

      m_appmap.set_at(psz, p);

   }


   void application::open_profile_link(string strUrl, string strProfile, string strTarget)
   {

      fork([=]()
      {

         sync_open_profile_link(strUrl, strProfile, strTarget);

      });

   }


   ::file::path command_find_path(const char * pszCommand)
   {

#ifdef METROWIN

      return "";

#else

      string strPath = getenv("PATH");

      stringa straPath;

      straPath.explode(":", strPath);

      for (auto & str : straPath)
      {

         ::file::path path;

         path = str;

         path /= pszCommand;

         if (file_exists_dup(path))
         {

            return path;

         }

      }

      return pszCommand;

#endif

   }
#ifdef WINDOWSEX


   class open_browser_enum
   {
   public:

      string                           m_strWindowEnd;
      string                           m_strTopic;
      string                           m_strCounterTopic;
      oswindow                         m_hwnd;
      comparable_array < oswindow >    m_hwndaTopic;
      comparable_array < oswindow >    m_hwndaCounterTopic;

   };


   WINBOOL CALLBACK enum_proc(oswindow hwnd, LPARAM lparam)
   {

      open_browser_enum * penum = (open_browser_enum *)lparam;

      string str = ::str::get_window_text_timeout(hwnd, 1000);

      if (::str::ends_ci(str, penum->m_strWindowEnd))
      {

         penum->m_hwnd = hwnd;

         return FALSE;

      }

      return TRUE;

   }


   WINBOOL CALLBACK enum_proc_ff_topic(oswindow hwnd, LPARAM lparam)
   {

      open_browser_enum * penum = (open_browser_enum *)lparam;

      string str = ::str::get_window_text_timeout(hwnd);

      if (::str::ends_ci(str, penum->m_strTopic))
      {

         penum->m_hwndaTopic.add(hwnd);

      }

      return TRUE;

   }

   WINBOOL CALLBACK enum_proc_ff_counter_topic(oswindow hwnd, LPARAM lparam)
   {

      open_browser_enum * penum = (open_browser_enum *)lparam;

      string str = ::str::get_window_text_timeout(hwnd, 1000);

      if (::str::ends_ci(str, penum->m_strCounterTopic))
      {

         penum->m_hwndaCounterTopic.add(hwnd);

      }

      return TRUE;

   }

   void close_browser(const array < oswindow > & wa, int & iStep)
   {

      if (iStep < 0)
      {

         iStep = 0;

      }

      uint32_array uia;

      for (auto w : wa)
      {

         switch (iStep % 3)
         {
         //case 0:
         //{
         //   DWORD dwPid;
         //   GetWindowThreadProcessId(w, &dwPid);
         //   uia.add_unique(dwPid);

         //}
         //break;
         case 0:
            ::PostMessage(w, WM_CLOSE, NULL, NULL);
            break;
         case 1:
            ::PostMessage(w, WM_CLOSE, NULL, NULL);
            break;
         case 2:
            ::PostMessage(w, WM_CLOSE, NULL, NULL);
            break;
         case 3:
            ::PostMessage(w, WM_QUIT, NULL, NULL);
            break;
         default:
            ::PostMessage(w, WM_CLOSE, NULL, NULL);
            break;
         };

      }

      switch (iStep % 4)
      {
      //case 0:
      //   User32EndTask(w, FALSE,FALSE);
      //   break;
      //case 0:

      //{
      //   for (auto dwPid : uia)
      //   {


      //      string str;
      //      str.Format("taskkill /pid " + ::str::from((unsigned int)dwPid));
      //      ::system(str);

      //   }
      //   Sleep(2000);
      //}
      //   break;
      case 0:
         Sleep(300);
         break;
      case 1:
         Sleep(500);
         break;
      case 2:
         Sleep(800);
         break;
      case 3:
         Sleep(1000);
         break;
      default:
         break;
      };


      iStep++;


   }

#endif


   void application::chromium(string strUrl, string strBrowser, string strId, ::file::path path, string strProfile, string strParam)
   {


#ifdef METROWIN

      ui_open_url(strUrl);

#else

//      manual_reset_event evClose(this);

      ::file::path pathDir;

      pathDir = path.folder();

      ::file::path pathAppDataDir(::dir::ca2config());

      ::file::path pathProfile;

      string strBrowserProfile;

      if (strId == "chrome" || strId == "commander")
      {

         strBrowserProfile = "Chrome";


      }
      else if (strId == "vivaldi")
      {

         strBrowserProfile = "Vivaldi";

      }
      else
      {

         strBrowserProfile = "Chromium";

      }


      try
      {

         bool bFound = false;

         pathProfile = pathAppDataDir / strBrowserProfile / "Profile" / strProfile;

//#ifdef WINDOWSEX
//
//         open_browser_enum e;
//
//         if (strId == "chrome" || strId == "commander")
//         {
//
//            e.m_strTopic = " - Google Chrome";
//
//            e.m_strCounterTopic = " - Google Chrome";
//
//         }
//         else if (strId == "vivaldi")
//         {
//
//         }
//         else
//         {
//
//         }
//
//         e.m_hwndaTopic.remove_all();
//
//         ::EnumWindows(&enum_proc_ff_topic, (LPARAM)&e);
//
//         bFound = false;
//
//         if (e.m_hwndaTopic.has_elements())
//         {
//
//            for (auto w : e.m_hwndaTopic)
//            {
//
//               DWORD dwPid = 0;
//
//               ::GetWindowThreadProcessId(w, &dwPid);
//
//               if (dwPid != 0)
//               {
//
//                  HANDLE h = OpenProcess(PROCESS_ALL_ACCESS, TRUE, dwPid);
//
//                  if (h != INVALID_HANDLE_VALUE)
//                  {
//
//                     string strCmd = get_command_line(h);
//
//                     if (strCmd.contains_ci(strProfile))
//                     {
//
//                        bFound = true;
//
//                        ShowWindow(w, SW_SHOWNORMAL);
//
//                        ::SetWindowPos(w, HWND_TOP, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
//
//                        ::BringWindowToTop(w);
//
//                        ::SetForegroundWindow(w);
//
//                        if (strUrl.has_char())
//                        {
//
//                           var var;
//
//                           var["action"] = "open_url";
//
//                           var["url"] = strUrl;
//
//                           Application.file().put_contents(::dir::system() / strProfile + "-request.json", var.get_json());
//
//                        }
//
//                     }
//
//                  }
//
//                  ::CloseHandle(h);
//
//               }
//
//            }
//
//         }
//
//#endif

         if (!bFound)
         {

            if (strUrl.has_char())
            {

               strsize iFind = strParam.find("%1");

               if (iFind >= 0)
               {

                  strParam = strParam.Left(iFind) + strUrl + strParam.Mid(iFind + 2) + " ";

               }
               else
               {

                  strParam = "\"" + strUrl + "\" ";

               }

            }
            else
            {

               strParam = "";

            }

         }

#ifdef WINDOWS

         {

            if (strParam.trimmed().begins_ci("--"))
            {

               strParam = "--user-data-dir=\"" + pathProfile + "\" " + strParam;

            }
            else
            {

               strParam += "--user-data-dir=\"" + pathProfile + "\"";

            }

            call_async(path, strParam, pathDir, SW_SHOWDEFAULT, false);

         }

#else

#ifdef MACOS

//         string strApp = System.url().url_decode(path);
//
//         strApp.trim("\"");
//
//         path = strApp;
//
//         path /= "Contents/MacOS/Google Chrome";
//
//         strApp = "\"";
//
//         strApp += path;
//
//         strApp += "\"";
//
//         strParam += " --user-data-dir=\"" + pathProfile + "\"";
//
//         output_debug_string(strParam);
//
//         pathDir = ::dir::home();
//
//         run_pred_on_main_thread([=]()
//         {
//
//            call_async(strApp, strParam, pathDir, SW_SHOWDEFAULT, false);
//
//         });


         ::file::path shell;

         shell = "/bin/bash";

         strParam += " --user-data-dir=\"" + pathProfile + "\"";

         string strApp = System.url().url_decode(path);

         strApp.trim("\"");

         string strCmd = "open -na \"" + strApp + "\" --args " + strParam;

         strParam = " -c '" + strCmd + "'";

         run_pred_on_main_thread([=]()
         {

            call_async(shell, strParam, pathDir, SW_SHOWDEFAULT, false);

         });

#else

         ::file::path shell;

         shell = "/bin/bash";

         strParam += "--user-data-dir=\"" + pathProfile + "\"";

         string strCmd = path + " " + strParam;

         strCmd.replace("\'", "\\\'");

         strParam = " -c '" + strCmd + "'";

         output_debug_string(strParam);

         call_async(shell, strParam, pathDir, SW_SHOWDEFAULT, false);

#endif

#endif

      }
      catch (...)
      {


      }

#endif

   }


//   void application::commander(string strUrl, string strWeather, string strUser, ::file::path path, string strParam)
//   {
//
//#ifdef METROWIN
//
//      ui_open_url(strUrl);
//
//#else
//
//      ::file::path pathDir;
//
//      pathDir = path.folder();
//
//      if (strUrl.has_char())
//      {
//
//         strsize iFind = strParam.find("%1");
//
//         if (iFind >= 0)
//         {
//
//            strParam = strParam.Left(iFind) + strUrl + strParam.Mid(iFind + 2) + " ";
//
//         }
//         else
//         {
//
//            strParam = "\"" + strUrl + "\" ";
//
//         }
//
//      }
//      else
//      {
//         strParam.trim_left();
//
//         strsize iFind = strParam.find("%1");
//
//         if (iFind == 0 || iFind == 1)
//         {
//
//            if (strParam.get_length() <= 4)
//            {
//
//               strParam = "";
//
//            }
//            else
//            {
//
//               if (iFind == 0)
//               {
//
//                  strParam = strParam.Mid(2);
//
//               }
//               else
//               {
//
//                  strParam = strParam.Mid(4);
//
//               }
//
//            }
//         }
//         else if (iFind >= 2)
//         {
//
//            if (strParam[iFind - 1] == '\"' && strParam[iFind + 2] == '\"')
//            {
//
//               strParam = strParam.Left(iFind - 1) + strParam.Mid(iFind + 3);
//
//            }
//            else if (strParam[iFind - 1] == '\"' && strParam[iFind + 2] == '\"')
//            {
//
//               strParam = strParam.Left(iFind - 1) + strParam.Mid(iFind + 3);
//
//            }
//            else
//            {
//
//               strParam = strParam.Left(iFind) + strParam.Mid(iFind + 2);
//
//            }
//
//         }
//
//      }
//
//      string strExtraParam = " : " + strWeather + "=" + strUser;
//
//
//#ifdef WINDOWS
//
//      call_async(path, strParam, pathDir, SW_SHOWDEFAULT, false);
//
//#else
//
//      ::file::path shell;
//
//      shell = "/bin/bash";
//
//#ifdef MACOS
//
///*
//
//      path = System.url().url_decode(path);
//
//      path.trim("\"");
//
//      pathDir = dir::home();
//
//      run_pred_on_main_thread([=]()
//      {
//
//         string strCmd = "open -a \"" + path + "\" --args " + strParam + strExtraParam;
//
//         string strBashParam = "-c '" + strCmd + "'";
//
//         ::file::path pathDir = dir::home();
//
//         output_debug_string(strBashParam);
//
//         call_async(shell, strBashParam, pathDir, SW_SHOWDEFAULT, false);
//
//      });
//
// */
//
//      path = System.url().url_decode(path);
//
//      path.trim("\"");
//
//      pathDir = dir::home();
//
//      shell = "\"" + path + "/Contents/MacOS/commander\"";
//
//      run_pred_on_main_thread([=]()
//      {
//
//         string strCmd = strParam + strExtraParam;
//
//         ::file::path pathDir = dir::home();
//
//         output_debug_string(strCmd);
//
//         call_async(shell, strCmd, pathDir, SW_SHOWDEFAULT, false);
//
//      });
//
//#else
//
//      string strCmd = path + " " + strParam + strExtraParam;
//
//      strCmd.replace("\"", "\\\"");
//
//      strParam = " -c \"" + strCmd + "\"";
//
//      output_debug_string(strParam);
//
//      call_async(shell, strParam, pathDir, SW_SHOWDEFAULT, false);
//
//#endif
//
//
//#endif
//
//#endif
//
//   }


   void application::defer_create_firefox_profile(::file::path pathFirefox, string strProfileName, ::file::path pathProfile)
   {

#ifdef METROWIN


#else

      if (Application.dir().is(pathProfile))
      {

         return;

      }

      ::file::path pathDir;

      pathDir = pathFirefox.folder();

      ::file::path pathProfileDir;

      pathProfileDir = pathProfile.folder();

      Application.dir().mk(pathProfileDir);

      string strParam = "-no-remote -CreateProfile \"" + strProfileName + " " + pathProfile + "\"";

      call_sync(pathFirefox, strParam, pathDir, SW_SHOWDEFAULT, false);

#endif

   }

   // GitHub app#21
   void application::firefox(string strUrl, string strBrowser, string strProfile, string strParam)
   {

#ifdef METROWIN

      ui_open_url(strUrl);

#else

      string strBrowserPath;
      string strBrowserDir;
      string strBrowserHelperPath;
      string strBrowserHelperDir;

      ::file::path pathAppDataDir(getenv("APPDATA"));

      ::file::path pathProfile;

      strParam = "-no-remote -P \"" + strProfile + "\"";

      if (strBrowser != "browser_night")
      {

         // == browser_day or something else

         //xxx m_strTopic = " - Mozilla Firefox";
         //xxx m_strCounterTopic = " - Firefox Developer Edition";

         strBrowser = "browser_day";
         strBrowserPath = "C:\\Program Files (x86)\\Mozilla Firefox\\Firefox.exe";
         strBrowserDir = "C:\\Program Files (x86)\\Mozilla Firefox";
         strBrowserHelperPath = "C:\\Program Files (x86)\\Mozilla Firefox\\uninstall\\helper.exe";
         strBrowserHelperDir = "C:\\Program Files (x86)\\Mozilla Firefox\\uninstall";

         pathProfile = pathAppDataDir / "ca2/Firefox/Profile" / strProfile;


      }
      else
      {

         // == browser_night

         //xxx m_strTopic = " - Firefox Developer Edition";
         //xxx m_strCounterTopic = " - Mozilla Firefox";

         pathProfile = pathAppDataDir / "ca2/FirefoxDev/Profile" / strProfile;

         defer_create_firefox_profile(strBrowserPath, strProfile, pathProfile);

         strBrowser = "browser_night";
         strBrowserPath = "C:\\Program Files (x86)\\Firefox Developer Edition\\Firefox.exe";
         strBrowserDir = "C:\\Program Files (x86)\\Firefox Developer Edition\\";
         strBrowserHelperPath = "C:\\Program Files (x86)\\Firefox Developer Edition\\uninstall\\helper.exe";
         strBrowserHelperDir = "C:\\Program Files (x86)\\Firefox Developer Edition\\uninstall";

      }

      defer_create_firefox_profile(strBrowserPath, strProfile, pathProfile);

      bool bFound = false;

#ifdef WINDOWSEX

      manual_reset_event evClose(this);

      open_browser_enum e;

      ::fork(get_app(), [&]()
      {

         int iStep = 0;

         while (true)
         {

            e.m_hwndaCounterTopic.remove_all();

            ::EnumWindows(&enum_proc_ff_counter_topic, (LPARAM)&e);

            if (e.m_hwndaCounterTopic.is_empty())
            {

               break;

            }

            close_browser(e.m_hwndaCounterTopic, iStep);

         }

         evClose.SetEvent();


      });

      e.m_hwndaTopic.remove_all();

      //::EnumWindows(&enum_proc_ff_topic, (LPARAM)&e);

      //if (e.m_hwndaTopic.has_elements())
      //{

      //   for (auto w : e.m_hwndaTopic)
      //   {

      //      DWORD dwPid = 0;

      //      ::GetWindowThreadProcessId(w, &dwPid);

      //      if (dwPid != 0)
      //      {

      //         HANDLE h = OpenProcess(PROCESS_ALL_ACCESS, TRUE, dwPid);

      //         if (h != INVALID_HANDLE_VALUE)
      //         {

      //            string strCmd = get_command_line(h);

      //            if (strCmd.contains_ci(strProfile))
      //            {

      //               bFound = true;

      //               ShowWindow(w, SW_SHOW);

      //               ::SetWindowPos(w, HWND_TOP, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);

      //               ::BringWindowToTop(w);

      //               ::SetForegroundWindow(w);

      //            }

      //         }

      //         ::CloseHandle(h);

      //      }

      //   }

      //}

#endif

      if (!bFound)
      {

         call_async(strBrowserPath, strParam, strBrowserDir, SW_SHOW, false);

         call_async(strBrowserHelperPath, "/SetAsDefaultAppUser", strBrowserHelperDir, SW_HIDE, false);

      }

      if (strBrowser.has_char())
      {

         Application.file().put_contents_utf8(::dir::system() / "browser.txt", strBrowser);

         Application.file().put_contents_utf8(::dir::system() / "browser_path.txt", strBrowserPath);

         Application.file().put_contents_utf8(::dir::system() / "browser_dir.txt", strBrowserDir);

      }

#ifdef WINDOWSEX

      evClose.wait(seconds(60));

#endif

#endif

   }


   void application::browser(string strUrl, string strBrowser, string strProfile, string strTarget)
   {

      string strBrowserPath;
      string strBrowserDir;
      string strBrowserHelperPath;
      string strBrowserHelperDir;

      string strId;

      ::file::path path;

      string strParam;

      System.os().get_default_browser(strId, path, strParam);

      if (strProfile.is_empty() || strProfile == "native")
      {

         strProfile = "default";

      }

      string strUser = strProfile;

      string strWeather = strBrowser;

      if (strWeather.is_empty() || !strWeather.begins_ci("browser_"))
      {

         strWeather = Application.file().as_string(::dir::system() / "browser_weather.txt");

      }

      if (strWeather.is_empty() || !strWeather.begins_ci("browser_"))
      {

         strWeather = "browser_day";

      }

      strProfile = strProfile + "." + strWeather;

      if (strUrl.has_char())
      {

         if (strBrowser == "firefox")
         {

            //strUrl = "https://ca2.cc/open_f___?url=" + System.url_encode(strUrl) + "&profile=" + System.url_encode(strProfile) + "&target=" + System.url_encode(strTarget);

         }
         else
         {

            //strUrl = "https://ca2.cc/open_tab?url=" + System.url_encode(strUrl) + "&profile=" + System.url_encode(strProfile) + "&target=" + System.url_encode(strTarget);

         }

      }


      if (strId == "firefox")
      {

         firefox(strUrl, strBrowser, strProfile, strParam);

      }
      else if (strId == "chrome")
      {

         chromium(strUrl, strBrowser, strId, path, strProfile, strParam);

      }
      else if (strId == "vivaldi")
      {

         chromium(strUrl, strBrowser, strId, path, strProfile, strParam);

      }
      else if (strId == "commander")
      {

         //if (m_strAppName == "app-core/commander")
         {

            chromium(strUrl, strBrowser, strId, System.os().get_app_path("chrome"), strProfile, strParam);

         }
         //else
         {

            //commander(strUrl, strWeather, strUser, path, strParam);

         }

      }
      else
      {

#if defined(METROWIN)


         string * pstrNew = new string(strUrl);

         Windows::ApplicationModel::Core::CoreApplication::MainView->CoreWindow->Dispatcher->RunAsync(::Windows::UI::Core::CoreDispatcherPriority::Normal,
               ref new Windows::UI::Core::DispatchedHandler([pstrNew]()
         {

            ::Windows::Foundation::Uri ^ uri = ref new ::Windows::Foundation::Uri(*pstrNew);

            delete pstrNew;

            LauncherOptions ^ options = ref new LauncherOptions();

            options->TreatAsUntrusted = false;

            Launcher::LaunchUriAsync(uri, options);

         }));

         //#elif defined(LINUX)
         //
         //      ::system("xdg-open \"" + strUrl + "\"");
         //
         //      return true;
         //
         //#elif defined(APPLEOS)
         //    openURL(strLink);
         //  return true;
#elif defined(VSNORD)

         string strOpenUrl;

         if (System.node_ddx()->m_pszOpenUrl != NULL)
         {

            strOpenUrl = System.node_ddx()->m_pszOpenUrl;

            try
            {

               ::free((void *)System.node_ddx()->m_pszOpenUrl);

            }
            catch (...)
            {


            }

            System.node_ddx()->m_pszOpenUrl = NULL;

         }


         //strOpenUrl = strUrl + str::has_char(strOpenUrl, ";");

         //if (strOpenUrl.has_char())
         {

            // System.m_pandroidinitdata->m_pszOpenUrl = strdup(strLink);

            System.node_ddx()->m_pszOpenUrl = strdup(strUrl);

         }


#elif defined(MACOS)

         ::system("open -a /Applications/Safari.app \"" + strUrl + "\"");

#elif defined(APPLE_IOS)

         ui_open_url(strUrl);

#elif defined(WINDOWSEX)

         if (strUrl.is_empty())
         {

            strUrl = "foo.html";

         }

         ::ShellExecuteW(NULL, L"open", wstring(strUrl), NULL, L"C:\\Windows", SW_SHOWDEFAULT);

         //::file::path path = getenv("APPDATA");

         //path /= strProfile;

         //call_sync("C:\\Program Files\\Opera.exe", "--user-data-dir=\"" + path + "\" " + strUrl, "C:\\Users\\camilo\\AppData\\Local\\Vivaldi\\Application", SW_SHOWNORMAL, 0);

#else

         if (strUrl.has_char())
         {

            strParam = "\"" + strUrl + "\"";

         }

         ::file::path pathDir;

         pathDir = path.folder();

         ::file::path shell;

         shell = "/bin/bash";

         if (strBrowser == "vivaldi")
         {

            ::file::path pathHome(getenv("HOME"));

            ::file::path pathProfile;

            pathProfile = pathHome / "ca2/Vivaldi/Profile" / strProfile;

            call_async(shell, " -c \"" + path + " --user-data-dir=\\\"" + pathProfile + "\\\" " + strParam, pathHome, SW_SHOWDEFAULT, false);

         }
         else if (strBrowser == "chrome")
         {

            ::file::path pathHome(getenv("HOME"));

            ::file::path pathProfile;

            pathProfile = pathHome / "ca2/Chrome/Profile" / strProfile;

            string strCmd = path + " --user-data-dir=\"" + pathProfile + "\" " + strParam;

            strCmd.replace("\"", "\\\"");

            strParam = " -c \"" + strCmd + "\"";

            //MessageBox(NULL, strParam, path, MB_OK);

            call_async(shell, strParam, pathHome, SW_SHOWDEFAULT, false);

         }
         else if (strBrowser == "firefox")
         {

            ::file::path pathHome(getenv("HOME"));

            ::file::path pathProfile;

            pathProfile = pathHome / "ca2/Firefox/Profile" / strProfile;

            call_async(shell, "-c \"" + path + " -profile=\\\"" + pathProfile + "\\\" " + strParam + "\"", pathHome, SW_SHOWDEFAULT, false);

         }
         else
         {

            ::system("xdg-open " + strUrl);

         }



#endif

      }

   }


   void application::sync_open_profile_link(string strUrl, string strProfile, string strTarget)
   {

      browser(strUrl, "", strProfile, strTarget);

   }


   bool application::open_link(string strLink, string strProfile, string strTarget)
   {

      if (is_system())
      {

         open_profile_link(strLink, strProfile, strTarget);

         return true;

      }
      else
      {

         return System.open_link(strLink, strProfile, strTarget);

      }

      return false;

   }


   void application::TermThread(HINSTANCE hInstTerm)
   {

      ::exception::throw_interface_only(this);

   }


   void application::SetCurrentHandles()
   {

      if(m_hthread == NULL)
      {

         //dappy(string(typeid(*this).name()) + " : SetCurrentHandles 1 : " + ::str::from(m_iErrorCode));

         set_os_data((void *) ::get_current_thread());

         //dappy(string(typeid(*this).name()) + " : SetCurrentHandles 2 : " + ::str::from(m_iErrorCode));

         set_os_int(::get_current_thread_id());

         //dappy(string(typeid(*this).name()) + " : SetCurrentHandles impled : " + ::str::from(m_iErrorCode));
      }

   }


   bool application::_001OnDDECommand(const char * lpcsz)
   {

      ::exception::throw_interface_only(this);

      return false;

   }



   /*::user::document *  application::_001OpenDocumentFile(var varFile)
   {

      ::exception::throw_interface_only(this);

      return NULL;

   }*/


   void application::_001OnFileNew(::message::message * pobj)
   {

      ::exception::throw_interface_only(this);

   }


   //bool application::update_module_paths()
   //{


   //   if(is_system())
   //   {

   //      if(!m_pimpl->update_module_paths())
   //         return false;


   //   }

   //   return true;


   //}













   void application::process_machine_event_data(machine_event_data * pdata)
   {

      if (pdata->m_fixed.m_bRequestCloseApplication)
      {

         _001CloseApplication();

      }

   }


   void application::_001CloseApplication()
   {

      _throw(todo(get_app()));

   }












   void application::DoWaitCursor(int32_t nCode) // 0 => restore, 1=> begin, -1=> end
   {

      UNREFERENCED_PARAMETER(nCode);

   }


   //   void application::ShowWaitCursor(bool bShow)
   //   {
   //
   //      if (m_pappimpl.is_null())
   //         return;
   //
   //      m_pappimpl->ShowWaitCursor(bShow);
   //
   //
   //   }
   //
   //
   //#ifndef METROWIN
   //
   //
   //   void application::get_time(timeval *p)
   //   {
   //
   //      m_pappimpl->get_time(p);
   //
   //   }
   //
   //
   //#endif


//   string CLASS_DECL_AURA application::get_cred(const string & strRequestUrl, const RECT & rect, string & strUsername, string & strPassword, string strToken, string strTitle, bool bInteractive)
   // {

   //  _throw(not_implemented(this));

   //}




   bool application::get_temp_file_name_template(string & strRet, const char * pszName, const char * pszExtension, const char * pszTemplate)
   {

      _throw(not_implemented(this));

      return false;

   }


   bool application::get_temp_file_name(string & strRet, const char * pszName, const char * pszExtension)
   {

      return get_temp_file_name_template(strRet, pszName, pszExtension, NULL);

   }











   bool application::final_handle_exception(::exception::exception * pe)
   {

      UNREFERENCED_PARAMETER(pe);

      //linux      exit(-1);

      if (!is_system())
      {

         // get_app() may be it self, it is ok...
         if (System.final_handle_exception(pe))
            return true;


      }

      return false;
   }


   void application::main()
   {

      TRACE(string(typeid(*this).name()) + " main");;

      dappy(string(typeid(*this).name()) + " : application::main 1");

      try
      {

         TRACE(string(typeid(*this).name()) + " on_run");;

         //dappy(string(typeid(*this).name()) + " : going to on_run : " + ::str::from(m_iErrorCode));

         //m_iErrorCode = 0;

         m_bReady = true;

         on_run();

//         if(m_iErrorCode != 0)
//         {
//
//            dappy(string(typeid(*this).name()) + " : on_run failure : " + ::str::from(m_iErrorCode));
//
//            ::output_debug_string("application::main on_run termination failure\n");
//
//         }

      }
      catch(exit_exception * pexception)
      {

         esp671 esp(pexception);

//         thisexit << "exit_exception: " << m_iErrorCode;
//

         //m_error.set(&e);

         dappy(string(typeid(*this).name()) + " : on_run exit_exception");

         pexception->post_quit();

      }
      catch(::exception::exception *pexception)
      {

         esp671 esp(pexception);

      }
      catch (...)
      {

         dappy(string(typeid(*this).name()) + " : on_run general exception");

      }

   }


   bool application::init_thread()
   {

      try
      {

         if (!pre_run())
         {

            return false;

         }

      }
      catch (exit_exception * pexception)
      {

         throw pexception;

      }
      catch (::exception::exception  * pexception)
      {

         esp671 esp(pexception);

         return false;

      }
      catch (...)
      {

         return false;

      }

      return true;

   }


   void application::term_thread()
   {

      try
      {

         Application.signal_close_dependent_threads();

      }
      catch (...)
      {

      }

      try
      {

         wait_close_dependent_threads(seconds(60));

      }
      catch (...)
      {

      }

      thisstart;

      m_dwAlive = ::get_tick_count();

      try
      {

         pos_run();

      }
      catch (...)
      {

      }

   }


   bool application::pre_run()
   {

      thisstart;

      try
      {

         m_dwAlive = ::get_tick_count();

         if(!application_pre_run())
         {

            m_bReady = true;

            return false;

         }

         //    if(!check_install())
         //    {

         //       m_bReady = true;

         //       return false;

         //    }

//         if(!is_system() && !is_session())
//         {
//
//            if(!is_installed())
//            {
//
//
//            }
//
//         }

         xxdebug_box("pre_run 1 ok", "pre_run 1 ok", MB_ICONINFORMATION);

         if (!initial_check_directrix())
         {

            m_bReady = true;

            return false;

         }

         m_dwAlive = ::get_tick_count();

         if (!os_native_bergedge_start())
         {

            m_bReady = true;

            return false;

         }

         thisend;

         return true;

      }
      catch (exit_exception * pexception)
      {

         _rethrow(pexception);

      }
      catch(::exception::exception * pexception)
      {

         esp671 esp(pexception);

         thisexcall << 3.9;

      }
      catch (...)
      {

         thisexcall << 4;

      }

      return false;

   }


   void application::on_run()
   {

      try
      {

         application_message message(application_message_beg);

         route_message(&message);

      }
      catch (...)
      {

      }

      //thisstart << m_iErrorCode;

      thread * pthread = ::get_thread();

      install_message_routing(pthread);

      //thisok << 1 << m_iErrorCode;

      try
      {

         m_bReady = true;

         if (m_pevAppBeg != NULL)
         {

            m_pevAppBeg->SetEvent();

         }

      }
      catch (...)
      {

      }

      try
      {

run:

         try
         {

            run();

         }
         catch (exit_exception * pexception)
         {

            throw pexception;

         }
         catch(::exception::exception * pexception)
         {

            esp671 esp(pexception);

            if (on_run_exception(esp))
            {

               goto run;

            }

            if (final_handle_exception(esp))
            {

               goto run;

            }

         }

      }
      catch (...)
      {

         // here was a comment about recovering from bug...
         // kinda : universe in eletron? OMG
         // (no problem, but continue to be eletron...)
         // more real example? a PC for controlling sensor of refrigerator... no problem... bias agains it?!
         // (yes I have bias against someone that supposedly has intelligence but behave as dumb...)
         // (but javascript brogrammers probably will do it because they will forget the laws of physics
         // and create rust/node/swift/java alliance effort with great AI to gather just the temperature...)
         // (but then there is the button... and it will be ch(i)(ea)p anyway, so one PC for each PC component, and sure each eletron will have one PC (remember 10e23 atoms per mol of component...)
         // ...
         // ..
         // .
         // PS. assembly mul byte_volts = temperature * constant(byte255) (but WTF is it? it is not from alliance <3 <==3 <======3 )
         // the only thing I know (and not one of the things) .....
         // (oh other P.S. now I am burning, firing... but some people want to die...)
         // their strange thought: because your human byte_volts extreme_high, do you want cup of milk exactly
         // now? how are you, fine(d)?... and you shouldn't commit z-degree extermination... z->8 lay down...
         // and it is what exactly what exactly ca2 ca2 is about, this can of mean thing... so you stop at 8 ca2...
         // what you have back support? C++ and machines and components and reality stack...
      }

      try
      {

         if (m_pevAppEnd != NULL)
         {

            m_pevAppEnd->SetEvent();

         }

      }
      catch (...)
      {

      }

   }


   void application::on_pos_run_thread()
   {

   }


   void application::pos_run()
   {

      thisstart;

      try
      {

         m_dwAlive = ::get_tick_count();

         application_pos_run();

         xxdebug_box("pre_run 1 ok", "pre_run 1 ok", MB_ICONINFORMATION);

      }
      catch (...)
      {

         thisexcall << 4;

      }

   }


   bool application::init_instance()
   {

      return true;

   }


   void application::term_instance()
   {


   }

   bool application::ca_init3()
   {

      application_message message(application_message_init3);

      route_message(&message);

      return message.m_bOk;

   }


   void application::ca_process_term()
   {

      application_message message(application_message_process_term);

      route_message(&message);

      //return message.m_bOk;

   }


   void application::TermApplication()
   {


   }


   bool application::application_pre_run()
   {

      thisstart;

#ifdef WINDOWSEX

      MESSAGE msg;

      // Create Windows Message Queue
      ::PeekMessageA(&msg, NULL, 0, 0xffff, 0);

      if (!is_system() && (bool)oprop("SessionSynchronizedInput"))
      {

         ::AttachThreadInput(GetCurrentThreadId(), (uint32_t)System.get_os_int(), TRUE);

      }

#endif

      m_dwAlive = ::get_tick_count();

      try
      {

         if (!InitApplication())
         {

            return false;

         }

      }
      catch (::exit_exception * pe)
      {

         throw pe;

      }
      catch (const ::exception::exception * pe)
      {

         //thisexc << 1 << m_iErrorCode;

         ::aura::del(pe);

         return false;

      }
      catch (...)
      {

         //thisexcall << 1 << m_iErrorCode;

         return false;

      }

      m_dwAlive = ::get_tick_count();

      try
      {

         if (!process_init())
         {

            return false;

         }

      }
      catch (::exit_exception * pe)
      {

         throw pe;

      }
      catch (const ::exception::exception * pe)
      {

         ::aura::del(pe);

         return false;

      }
      catch (...)
      {

         return false;

      }

      System.install_progress_add_up();

      m_dwAlive = ::get_tick_count();

      try
      {

         if (!init_application())
         {

            return false;

         }

      }
      catch (exit_exception * pexception)
      {

         _rethrow(pexception);

      }
      catch(::exception::exception * pexception)
      {

         esp671 esp(pexception);

         return false;

      }
      catch (...)
      {

         return false;

      }

      m_dwAlive = ::get_tick_count();

      try
      {

         if (!is_system() && !is_session())
         {

            if (System.handler()->m_varTopicQuery.has_property("uninstall"))
            {

               do_uninstall();

               return true;

            }
            else if (System.handler()->m_varTopicQuery.has_property("install"))
            {

               do_install();

               return true;

            }

         }

         if (!init_instance())
         {

            return false;

         }

      }
      catch (exit_exception * pexception)
      {

         _rethrow(pexception);

      }
      catch(::exception::exception * pexception)
      {

         esp671 esp(pexception);

         return false;

      }
      catch (...)
      {

         return false;

      }

      return true;

   }


   void application::application_pos_run()
   {

      try
      {

         //if (!is_installing() && !is_unstalling())
         {

            term_instance();

         }

      }
      catch (...)
      {

      }

      try
      {

         term_application();

      }
      catch (...)
      {

      }

      m_dwAlive = ::get_tick_count();

      try
      {

         process_term();

      }
      catch (...)
      {

      }

      try
      {

         TermApplication();

      }
      catch (...)
      {

      }



   }

   bool application::InitApplication()
   {

      return true;

   }



   bool application::do_install()
   {

      if (!on_install())
      {

         ::output_debug_string("Failed at on_install : " + m_strAppId + "\n\n");

         //System.m_iErrorCode = -1;

         System.m_error.set(-1);

         return false;

      }

      string strBuild = m_strBuild;

      string strAppId = m_strAppId;

      xxdebug_box("on_install1", strAppId, 0);

      system_add_app_install(strAppId, strBuild);

//         if (strAppId.is_empty())
//         {
//
//            strAppId = m_strAppName;
//
//         }
//
//         if (strAppId.has_char() && handler()->m_varTopicQuery.has_property("app") && strAppId == handler()->m_varTopicQuery["app"])
//         {
//
//            system_add_app_install(strAppId, "installed");
//
//            if (strBuild.has_char())
//            {
//
//               system_add_app_install(strAppId, strBuild);
//
//            }
//
//         }
//         else if (strAppId.has_char() && handler()->m_varTopicQuery.has_property("session_start") && strAppId == handler()->m_varTopicQuery["session_start"])
//         {
//
//            system_add_app_install(strAppId, "installed");
//
//            if (strBuild.has_char())
//            {
//
//               system_add_app_install(strAppId, strBuild);
//
//            }
//
//         }
//         else if (m_strInstallToken.has_char())
//         {
//
//            system_add_app_install(m_strInstallToken, "installed");
//
//            if (strBuild.has_char())
//            {
//
//               system_add_app_install(m_strInstallToken, strBuild);
//
//            }
//
//         }

      return true;

   }


   bool application::initial_check_directrix()
   {

      string strLicense = get_license_id();

      var & varTopicQuey = System.handler()->m_varTopicQuery;

      bool bHasInstall = varTopicQuey.has_property("install");

      bool bHasUninstall = varTopicQuey.has_property("uninstall");

      if (!(bHasInstall || bHasUninstall)
            && m_bLicense
            && strLicense.has_char())
      {

         if (!Session.assert_user_logged_in())
         {
            return false;
         }

         // call application's is_licensed function
         // because if delay is needed for authentication -
         // or either asking for authentication -
         // current application startup won't be
         // exited by timeout.

         int32_t iRetry = 1;

retry_license:

         iRetry--;

         if (!Session.is_licensed(strLicense))
         {

            if (iRetry > 0)
               goto retry_license;

            return false;

         }

      }


      ::output_debug_string("initial_check_directrix : ok (" + string(typeid(*this).name()) + ")" + m_strAppId + "\n\n");


      return true;

   }



   bool application::do_uninstall()
   {

      if (!on_uninstall())
      {

         return false;

//         System.install().remove_spa_start(m_strAppId);

      }

      return true;

   }




   bool application::on_install()
   {

      if (is_serviceable())
      {

         if (!create_service())
            return false;

         start_service();

      }
      else
      {

#ifdef WINDOWSEX

         windows_install_crash_dump_reporting(this);

#endif

      }
      return true;

   }


   bool application::on_uninstall()
   {

      //bool bOk = axis::application::on_uninstall();

      bool bOk = true;


      if (is_serviceable())
      {

         if (!remove_service())
            bOk = false;

      }

      return bOk;

   }


   bool application::system_add_app_install(const char * pszId, const char * pszBuild)
   {

      // cool install

      string strBuild(pszBuild);

      if (strBuild.is_empty())
      {

         return false;

      }

      synch_lock sl(System.m_spmutexSystemAppData);

      string strId(pszId);
      string strSystemLocale = System.m_strLocale;
      string strSystemSchema = System.m_strSchema;
      stringa straLocale = m_phandler->m_varTopicQuery["locale"].stra();
      stringa straSchema = m_phandler->m_varTopicQuery["schema"].stra();

      //System.install().remove_spa_start(strId);
      //System.install().add_app_install(strId, strBuild, strSystemLocale, m_strSchema);
      //System.install().add_app_install(strId, strBuild, strSystemLocale, strSystemSchema);
      //System.install().add_app_install(strId, strBuild, m_strLocale, m_strSchema);

      //for (index iLocale = 0; iLocale < straLocale.get_count(); iLocale++)
      //{

      //   System.install().add_app_install(strId, strBuild, straLocale[iLocale], m_strSchema);

      //}

      //for (index iSchema = 0; iSchema < straSchema.get_count(); iSchema++)
      //{

      //   System.install().add_app_install(strId, strBuild, m_strLocale, straSchema[iSchema]);

      //}

      //for (index iLocale = 0; iLocale < straLocale.get_count(); iLocale++)
      //{

      //   for (index iSchema = 0; iSchema < straSchema.get_count(); iSchema++)
      //   {

      //      System.install().add_app_install(strId, strBuild, straLocale[iLocale], straSchema[iSchema]);

      //   }

      //}

      //System.install().add_app_install(strId, strBuild, strSystemLocale, "");
      //System.install().add_app_install(strId, strBuild, m_strLocale, "");

      //for (index iLocale = 0; iLocale < straLocale.get_count(); iLocale++)
      //{

      //   System.install().add_app_install(strId, strBuild, straLocale[iLocale], "");

      //}

      //System.install().add_app_install(strId, strBuild, "", m_strSchema);
      //System.install().add_app_install(strId, strBuild, "", strSystemSchema);

      //for (index iSchema = 0; iSchema < straSchema.get_count(); iSchema++)
      //{

      //   System.install().add_app_install(strId, strBuild, "", straSchema[iSchema]);

      //}

      //System.install().add_app_install(strId, strBuild, "", "");

      return true;

   }


   bool application::os_native_bergedge_start()
   {

      return true;

   }


   void application::on_request(::create * pcreate)
   {

      ::object::on_request(pcreate);

      m_phandler->merge(pcreate);

   }


   void application::run()
   {

      if (!is_system() && !is_session())
      {

         if (handler()->m_varTopicQuery.has_property("service"))
         {

            create_new_service();

            ::service_base::serve(*m_pservice);

         }
         else if (handler()->m_varTopicQuery.has_property("run") || is_serviceable())
         {

            create_new_service();

            m_pservice->Start(0);

         }

      }

      ::thread::run();

   }


   bool application::safe_is_running()
   {

      bool bRunning = false;

      try
      {

         if (is_running())
         {

            bRunning = true;

         }

      }
      catch (...)
      {

         bRunning = false;

      }


      return bRunning;

   }


   sp(application) application::assert_running(const char * pszAppId)
   {

      sp(application) papp;

      papp = Session.m_appptra.find_running_defer_try_quit_damaged(pszAppId);

      if (papp.is_null())
      {

         sp(::create) spcreate(allocer());

         papp = Session.start_application(pszAppId, spcreate);

      }

      return papp;

   }










   /*::file::file_sp application::friendly_get_file(var varFile, UINT nOpenFlags)
   {

   try
   {

   return m_file.get_file(varFile, nOpenFlags);

   }
   catch (::file::exception & e)
   {

   string strMessage = e.get_message();

   App(this).simple_message_box(NULL, strMessage, MB_OK);

   return NULL;

   }

   }
   */




//   bool application::is_installing()
//   {
//
//      if (handler() == NULL)
//      {
//
//         return false;
//
//      }
//
//      return handler()->has_property("install");
//
//   }
//
//
//   bool application::is_unstalling()
//   {
//
//      if (handler() == NULL)
//      {
//
//         return false;
//
//      }
//
//      return handler()->has_property("uninstall");
//
//   }


   bool application::create_new_service()
   {

      if (m_pservice != NULL)
         return false;

      m_pservice = allocate_new_service();

      if (m_pservice == NULL)
         return false;

      return true;

   }



   bool application::create_service()
   {

      return System.os().create_service(this);

   }

   bool application::remove_service()
   {

      return System.os().remove_service(this);

   }

   bool application::start_service()
   {

      return System.os().start_service(this);

   }


   bool application::stop_service()
   {

      return System.os().stop_service(this);

   }


   void application::on_service_request(::create * pcreate)
   {

      if (!is_serviceable())
      {

         return;

      }

      if (pcreate->m_spCommandLine->m_varQuery.has_property("create_service"))
      {

         create_service();

      }
      else if (pcreate->m_spCommandLine->m_varQuery.has_property("start_service"))
      {

         start_service();

      }
      else if (pcreate->m_spCommandLine->m_varQuery.has_property("stop_service"))
      {

         stop_service();

      }
      else if (pcreate->m_spCommandLine->m_varQuery.has_property("remove_service"))
      {

         remove_service();

      }

   }


   bool application::process_init()
   {

      if (!m_bAppHasInstallerChangedProtected)
      {

#ifdef METROWIN

         set_has_installer(false);

#else

         set_has_installer(!m_paurasystem->m_pappcore->m_bAcidApp);

#endif

      }

      if (m_bAuraProcessInitialize)
      {

         return m_bAuraProcessInitializeResult;

      }

      thisstart;

      m_bAuraProcessInitialize = true;

      m_bAuraProcessInitializeResult = false;

      if (!is_system())
      {

         if (m_paurasystem != NULL)
         {

            m_bThreadToolsForIncreasedFps = m_paurasystem->m_bThreadToolsForIncreasedFps;

         }

      }

      m_spdir.alloc(allocer());

      m_spfile.alloc(allocer());

      if (::get_thread() == NULL)
      {

         ::set_thread(dynamic_cast <thread *> (this));

      }

      if (!ca_process_init())
      {

         thisfail << 1;

         return false;

      }

      if (!impl_process_init())
      {

         thisfail << 2;

         return false;

      }

      m_bAuraProcessInitializeResult = true;

      thisend;

      return true;

   }


   void application::process_term()
   {

      try
      {

         impl_process_term();

      }
      catch(...)
      {

      }

      try
      {

         ca_process_term();

      }
      catch(...)
      {

      }

      try
      {

         release_exclusive();

      }
      catch(...)
      {

      }

      m_phandler.release();

//      try
//      {
//
//         route_message(&message);
//
//      }
//      catch (...)
//      {
//
//      }

      try
      {

         if (!is_session() && !is_system())
         {

            if (m_paurasystem != NULL && m_paurasystem->m_phandler.is_set())
            {

               m_paurasystem->m_phandler->handle(::command_check_exit);

            }

         }

      }
      catch(...)
      {

      }

      try
      {

         for (auto & p : m_stringtable)
         {

            ::aura::del(p.m_element2);

         }

         m_stringtable.remove_all();

         for (auto & p : m_stringtableStd)
         {

            ::aura::del(p.m_element2);

         }

         m_stringtableStd.remove_all();

      }
      catch(...)
      {

      }

      m_spfile.release();

      m_spdir.release();

      ::aura::del(m_pimaging);

      if (!is_session() && !is_system())
      {

         try
         {

            if (Session.appptra().get_count() <= 1)
            {

               if (System.thread::get_os_data() != NULL)
               {

                  ::multithreading::post_quit(&System);

               }

            }

         }
         catch (...)
         {

         }

      }

   }


   bool application::init_application()
   {

      if (m_bAuraInitializeInstance)
      {

         return m_bAuraInitializeInstanceResult;

      }

      thisstart;

      m_bAuraInitializeInstance = true;

      m_bAuraInitializeInstanceResult = false;

      m_dwAlive = ::get_tick_count();

      if (!init1())
      {

         //dappy(string(typeid(*this).name()) + " : init1 failure : " + ::str::from(m_iErrorCode));

         return false;

      }

      xxdebug_box("check_exclusive", "check_exclusive", MB_ICONINFORMATION);

      if (!is_system() && !is_session())
      {

         try
         {

            m_pipi = create_ipi();

         }
         catch (...)
         {

         }

         thisok << 0.1;

         bool bHandled = false;

         if (!check_exclusive(bHandled))
         {

            if (!bHandled && (!System.handler()->m_varTopicQuery.has_property("install")
                              && !System.handler()->m_varTopicQuery.has_property("uninstall")))
            {

               duration durationTimeout;

#ifdef DEBUG

               durationTimeout = minutes(5);

#else

               durationTimeout = seconds(15);

#endif

               simple_message_box_timeout(NULL, "Another instance of \"" + m_strAppName + "\" is already running (and some exclusivity policy is active).", durationTimeout, MB_ICONASTERISK);

            }

            thisfail << 0.2;

            _throw(exit_exception(m_paurasession, ::exit_application));

         }

         thisok << 0.2;

         if (m_pipi != NULL)
         {

            try
            {

               for (index i = 0; i < 1; i++)
               {

                  m_pipi->ecall(m_pipi->m_strApp, { System.os().get_pid() }, "application", "on_new_instance", System.file().module(), System.os().get_pid());

               }

            }
            catch (...)
            {

            }

         }

      }

      xxdebug_box("check_exclusive ok", "check_exclusive ok", MB_ICONINFORMATION);

      System.install_progress_add_up(); // 2

      xxdebug_box("init1 ok", "init1 ok", MB_ICONINFORMATION);

      m_dwAlive = ::get_tick_count();

      if (!init2())
      {

         //dappy(string(typeid(*this).name()) + " : init2 failure : " + ::str::from(m_iErrorCode));

         return false;

      }

      System.install_progress_add_up(); // 3

      xxdebug_box("init2 ok", "init2 ok", MB_ICONINFORMATION);

      m_dwAlive = ::get_tick_count();

      if (!init3())
      {

         //dappy(string(typeid(*this).name()) + " : init3 failure : " + ::str::from(m_iErrorCode));

         return false;

      }

      System.install_progress_add_up(); // 4

      xxdebug_box("init3 ok", "init3 ok", MB_ICONINFORMATION);

      m_dwAlive = ::get_tick_count();

      //dappy(string(typeid(*this).name()) + " : init3 ok : " + ::str::from(m_iErrorCode));

      try
      {

         if (!init())
         {

            //dappy(string(typeid(*this).name()) + " : initialize failure : " + ::str::from(m_iErrorCode));

            return false;

         }

      }
      catch (const char * psz)
      {

         if (!strcmp(psz, "You have not logged in! Exiting!"))
         {

            return false;

         }

         return false;

      }

      System.install_progress_add_up(); // 5

      m_bAuraInitializeInstanceResult = true;

      return true;

   }


   ::aura::ipi * application::create_ipi()
   {

      try
      {

         return canew(::aura::ipi(this, m_strAppName));

      }
      catch (...)
      {

         return NULL;

      }

   }


   bool application::init1()
   {

      g_pf1 = (void *)(uint_ptr) ::str::to_uint64(file().as_string(::dir::system() / "config\\system\\pf1.txt"));

      if (m_bAuraInitialize1)
         return m_bAuraInitialize1Result;

      m_bAuraInitialize1 = true;

      m_bAuraInitialize1Result = false;

      m_dwAlive = ::get_tick_count();

      m_straMatterLocator.add_unique(System.dir_appmatter_locator(this));

      if (!ca_init1())
      {

         return false;

      }

      if (!impl_init1())
      {

         return false;

      }

      if (m_pimaging == NULL)
      {

         m_pimaging = new class imaging(get_app());

         if (m_pimaging == NULL)
         {

            _throw(memory_exception(get_app()));

         }

      }

      string strLocaleSystem;

      string strSchemaSystem;

      string strPath = System.dir().appdata() / "langstyle_settings.xml";

      if (file().exists(strPath))
      {

         string strSystem = file().as_string(strPath);

         ::xml::document docSystem(get_app());

         if (docSystem.load(strSystem))
         {

            if (docSystem.get_child("lang") != NULL)
            {

               strLocaleSystem = docSystem.get_child("lang")->get_value();

            }

            if (docSystem.get_child("style") != NULL)
            {

               strSchemaSystem = docSystem.get_child("style")->get_value();

            }

         }

      }

      string strLocale;

      string strSchema;

#ifdef METROWIN

      stringa stra;

      try
      {

         stra.explode("-", ::Windows::Globalization::ApplicationLanguages::PrimaryLanguageOverride);

      }
      catch (long)
      {


      }

      strLocale = stra[0];

      strSchema = stra[0];

#elif defined(WINDOWS)

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

      if (strLocale.is_empty())
      {

         strLocale = "_std";

      }

      if (strSchema.is_empty())
      {

         strSchema = "_std";

      }

      if (strLocaleSystem.has_char())
         strLocale = strLocaleSystem;

      if (strSchemaSystem.has_char())
         strSchema = strSchemaSystem;

      if (Sys(this).handler()->m_varTopicQuery["locale"].get_count() > 0)
         strLocale = Sys(this).handler()->m_varTopicQuery["locale"].stra()[0];

      if (Sys(this).handler()->m_varTopicQuery["schema"].get_count() > 0)
         strSchema = Sys(this).handler()->m_varTopicQuery["schema"].stra()[0];

      if (App(this).handler()->m_varTopicQuery["locale"].get_count() > 0)
         strLocale = App(this).handler()->m_varTopicQuery["locale"].stra()[0];

      if (App(this).handler()->m_varTopicQuery["schema"].get_count() > 0)
         strSchema = App(this).handler()->m_varTopicQuery["schema"].stra()[0];


      set_locale(strLocale, ::action::source::database());
      set_schema(strSchema, ::action::source::database());


      m_bAuraInitialize1Result = true;

      return true;

   }


   void application::term1()
   {

      try
      {

         impl_term1();

      }
      catch (...)
      {

      }

      try
      {

         ca_term1();

      }
      catch(...)
      {

      }

   }

   bool application::init2()
   {

      if (!impl_init2())
      {

         return false;

      }

      if (!ca_init2())
      {

         return false;

      }

      return true;

   }

   void application::term2()
   {

      try
      {

         impl_term2();

      }
      catch (...)
      {

      }

      try
      {

         ca_term2();

      }
      catch(...)
      {

      }

   }

   bool application::init3()
   {

      string strFolder = m_strAppName;

      strFolder.replace(".", "_");
      strFolder.replace("::", "-");
      strFolder.replace(":", "_");

      m_strRelativeFolder = strFolder;

      if (!impl_init3())
      {

         return false;

      }

      if (!ca_init3())
      {

         return false;

      }

      return true;

   }


   void application::term3()
   {

      try
      {

         impl_term3();

      }
      catch (...)
      {

      }

      try
      {

         ca_term3();

      }
      catch(...)
      {

      }

   }


   bool application::init()
   {

      return true;


   }


   void application::term()
   {

      ::aura::del(m_pimaging);

//      bool bOk = true;
//
//      return bOk;

   }



   void application::term_application()
   {

      try
      {

         term();

      }
      catch(...)
      {


      }

      try
      {

         term3();

      }
      catch(...)
      {


      }

      try
      {

         term2();

      }
      catch(...)
      {


      }

      try
      {

         term1();

      }
      catch(...)
      {


      }
//
//
//
//      return m_iErrorCode;

   }






//   bool application::impl_process_init()
//   {
//
//      return true;
//
//   }

//   bool application::impl_init1()
//   {
//
//      //set_run();
//
//      return true;
//
//   }

//   bool application::impl_init2()
//   {
//      return true;
//   }

//   bool application::impl_init3()
//   {
//      return true;
//   }

   // thread termination
//   void application::impl_process_term() // default will 'delete this'
//   {
//
//      set_os_data(NULL);
//
//      //int32_t iRet = ::aura::application::term_instance();
//
//      //return 0;
//
//   }


//   void application::impl_term3()
//   {
//
//
//   }
//
//
//   void application::impl_term2()
//   {
//
//
//   }
//
//
//   void application::impl_term1()
//   {
//
//
//   }
   bool application::is_running()
   {

      return is_alive();

   }


   service_base * application::allocate_new_service()
   {

      return NULL;

   }


   bool application::ca_init2()
   {

      application_message message(application_message_init2);

      route_message(&message);

      return message.m_bOk;

   }

   void application::ca_term2()
   {

      application_message message(application_message_term2);

      route_message(&message);

   }


   void application::ca_term3()
   {

      application_message message(application_message_init3);

      route_message(&message);

//      if (!message.m_bOk)
//         return false;
//
//      return true;

   }










   bool application::check_exclusive(bool & bHandled)
   {

#ifdef METROWIN

      return true;

#endif

      bool bSetOk;

      LPSECURITY_ATTRIBUTES lpsa = NULL;

      bool bResourceException = false;

#ifdef WINDOWSEX

      bSetOk = false;

      SECURITY_ATTRIBUTES MutexAttributes;
      ZeroMemory(&MutexAttributes, sizeof(MutexAttributes));
      MutexAttributes.nLength = sizeof(MutexAttributes);
      MutexAttributes.bInheritHandle = FALSE; // object uninheritable
      // declare and initialize a security descriptor
      SECURITY_DESCRIPTOR SD;
      bool bInitOk = InitializeSecurityDescriptor(&SD, SECURITY_DESCRIPTOR_REVISION) != FALSE;
      if (bInitOk)
      {
         // give the security descriptor a Null Dacl
         // done using the  "TRUE, (PACL)NULL" here
         bSetOk = SetSecurityDescriptorDacl(&SD,
                                            TRUE,
                                            (PACL)NULL,
                                            FALSE) != FALSE;
      }

      if (bSetOk)
      {

         MutexAttributes.lpSecurityDescriptor = &SD;

         lpsa = &MutexAttributes;

      }

#else

      bSetOk = true;

#endif

      if (bSetOk)
      {
         // Make the security attributes point
         // to the security descriptor
         bResourceException = false;
         try
         {
            m_pmutexGlobal = canew(mutex(this, FALSE, get_global_mutex_name(), lpsa));
         }
         catch (resource_exception &)
         {
            try
            {
               m_pmutexGlobal = canew(mutex(this, FALSE, get_global_mutex_name()));
            }
            catch (resource_exception &)
            {
               bResourceException = true;
            }
         }

         if (m_eexclusiveinstance == ExclusiveInstanceGlobal
               && (::get_last_error() == ERROR_ALREADY_EXISTS || bResourceException))
         {
            // Should in some way activate the other instance, but this is global, what to do? do not know yet.
            //System.simple_message_box("A instance of the application:<br><br>           - " + string(m_strAppName) + "<br><br>seems to be already running at the same machine<br>Only one instance of this application can run globally: at the same machine.<br><br>Exiting this new instance.");
            TRACE("A instance of the application:<br><br>           - " + string(m_strAppName) + "<br><br>seems to be already running at the same machine<br>Only one instance of this application can run globally: at the same machine.<br><br>Exiting this new instance.");
            bHandled = on_exclusive_instance_conflict(ExclusiveInstanceGlobal);
            return false;
         }
         if (m_eexclusiveinstance == ExclusiveInstanceGlobalId)
         {
            bResourceException = false;
            try
            {
               m_pmutexGlobalId = canew(mutex(this, FALSE, get_global_id_mutex_name(), lpsa));
            }
            catch (resource_exception &)
            {
               try
               {
                  m_pmutexGlobalId = canew(mutex(this, FALSE, get_global_id_mutex_name()));
               }
               catch (resource_exception &)
               {
                  bResourceException = true;
               }
            }
            if (::get_last_error() == ERROR_ALREADY_EXISTS || bResourceException)
            {
               // Should in some way activate the other instance
               TRACE("A instance of the application:<br><br>           - " + string(m_strAppName) + "with the id \"" + get_local_mutex_id() + "\" <br><br>seems to be already running at the same machine<br>Only one instance of this application can run globally: at the same machine with the same id.<br><br>Exiting this new instance.");
               bHandled = on_exclusive_instance_conflict(ExclusiveInstanceGlobalId);
               return false;
            }
         }
         bResourceException = false;

#if defined(MACOS) || defined(LINUX)

         ::file::path p;

         p = "/var/tmp";

         p /= get_local_mutex_name();

         ::dir::mk(p.folder());

         int i = open(p, O_WRONLY | O_CREAT, 0777);

         //int err = errno;

         i = lockf(i, F_TLOCK, 0);

         if (m_eexclusiveinstance == ExclusiveInstanceLocal && i < 0)
#else

         try
         {
            m_pmutexLocal = canew(mutex(this, FALSE, get_local_mutex_name(), lpsa));
         }
         catch (resource_exception &)
         {
            try
            {
               m_pmutexLocal = canew(mutex(this, FALSE, get_local_mutex_name()));
            }
            catch (resource_exception &)
            {
               bResourceException = true;
            }
         }
         if (m_eexclusiveinstance == ExclusiveInstanceLocal && (::get_last_error() == ERROR_ALREADY_EXISTS || bResourceException))
#endif
         {
            try
            {
               // Should in some way activate the other instance
               TRACE("A instance of the application:<br><br>           - " + string(m_strAppName) + "<br><br>seems to be already running at the same account.<br>Only one instance of this application can run locally: at the same account.<br><br>Exiting this new instance.");

               bHandled = on_exclusive_instance_conflict(ExclusiveInstanceLocal);

            }
            catch (...)
            {
            }

//            if(bHandled)
//            {
//
//               _throw(exit_exception(this, exit_application));
//
//            }
//
            //::aura::post_quit_thread(&System);
            return false;
         }
         if (m_eexclusiveinstance == ExclusiveInstanceLocalId)
         {
            bResourceException = false;
            try
            {
               m_pmutexLocalId = canew(mutex(this, FALSE, get_local_id_mutex_name(), lpsa));
            }
            catch (resource_exception &)
            {
               try
               {
                  m_pmutexLocalId = canew(mutex(this, FALSE, get_local_id_mutex_name()));
               }
               catch (resource_exception &)
               {
                  bResourceException = true;
               }
            }
            if (::get_last_error() == ERROR_ALREADY_EXISTS || bResourceException)
            {
               try
               {
                  // Should in some way activate the other instance
                  TRACE("A instance of the application:<br><br>           - " + string(m_strAppName) + "with the id \"" + get_local_mutex_id() + "\" <br><br>seems to be already running at the same account.<br>Only one instance of this application can run locally: at the same ac::count with the same id.<br><br>Exiting this new instance.");
                  bHandled = on_exclusive_instance_conflict(ExclusiveInstanceLocalId);
               }
               catch (...)
               {
               }
               release_exclusive();
               return false;
            }
         }
      }
      else
      {
         return false;
      }

      return true;

   }

   bool application::release_exclusive()
   {
      if (m_pmutexGlobal.is_set())
      {
         m_pmutexGlobal.release();
      }
      if (m_pmutexGlobalId.is_set())
      {
         m_pmutexGlobalId.release();
      }
      if (m_pmutexLocal.is_set())
      {
         m_pmutexLocal.release();
      }
      if (m_pmutexLocalId.is_set())
      {
         m_pmutexLocalId.release();
      }
      return true;
   }



   bool application::ca_process_init()
   {

      application_message message(application_message_process_init);

      route_message(&message);

      return true;

   }


   bool application::ca_init1()
   {

      application_message message(application_message_init1);

      route_message(&message);

      return message.m_bOk;

   }



   void application::ca_term1()
   {

      application_message message(application_message_term1);

      try
      {

         route_message(&message);

      }
      catch (...)
      {

      }

      //return message.m_bOk;

   }



   string application::get_local_mutex_name(const char * pszAppName)
   {
      string strMutex;
      strMutex.Format("Local\\ca2_application_local_mutex:%s", pszAppName);
      return strMutex;
   }

   string application::get_local_id_mutex_name(const char * pszAppName, const char * pszId)
   {
      string strId(pszId);
      string strMutex;
      strMutex.Format("Local\\ca2_application_local_mutex:%s, id:%s", pszAppName, strId.c_str());
      return strMutex;
   }

   string application::get_global_mutex_name(const char * pszAppName)
   {
      string strMutex;
      strMutex.Format("Global\\ca2_application_global_mutex:%s", pszAppName);
      return strMutex;
   }

   string application::get_global_id_mutex_name(const char * pszAppName, const char * pszId)
   {
      string strId(pszId);
      string strMutex;
      strMutex.Format("Global\\ca2_application_global_mutex:%s, id:%s", pszAppName, strId.c_str());
      return strMutex;
   }

   string application::get_local_mutex_name()
   {
      return get_local_mutex_name(get_mutex_name_gen());
   }

   string application::get_local_id_mutex_name()
   {
      return get_local_id_mutex_name(get_mutex_name_gen(), get_local_mutex_id());
   }

   string application::get_global_mutex_name()
   {
      return get_global_mutex_name(get_mutex_name_gen());
   }

   string application::get_global_id_mutex_name()
   {
      return get_global_id_mutex_name(get_mutex_name_gen(), get_global_mutex_id());
   }




   bool application::on_exclusive_instance_conflict(EExclusiveInstance eexclusive)
   {

      if (eexclusive == ExclusiveInstanceLocal)
      {

         return on_exclusive_instance_local_conflict();

      }

      return false;

   }


   bool application::on_exclusive_instance_local_conflict()
   {

      try
      {

         if (m_pipi != NULL)
         {

            int_map < var > map = m_pipi->ecall(m_pipi->m_strApp, { System.os().get_pid() }, "application", "on_exclusive_instance_local_conflict", System.file().module(), System.os().get_pid(), string(System.handler()->m_spcommandline->m_strCommandLine));

            for(auto & p : map)
            {

               if((bool) p.element2())
               {

                  return true;

               }

            }

         }

      }
      catch (...)
      {


      }

      return false;

   }


   bool application::on_exclusive_instance_local_conflict(string strModule, int iPid, string strCommandLine)
   {

      return false;

   }


   void application::on_new_instance(string strModule, int iPid)
   {

   }


   string application::get_mutex_name_gen()
   {
      return m_strAppName;
   }

   string application::get_local_mutex_id()
   {
      return handler()->m_varTopicQuery["local_mutex_id"];
   }

   string application::get_global_mutex_id()
   {
      return handler()->m_varTopicQuery["global_mutex_id"];
   }

   ::mutex * application::get_local_mutex()
   {
      return m_pmutexLocal;
   }

   ::mutex * application::get_global_mutex()
   {
      return m_pmutexGlobal;
   }



   bool application::Ex2OnAppInstall()
   {

      return true;

   }


   bool application::Ex2OnAppUninstall()
   {

      return true;

   }


   void application::on_set_scalar(e_scalar escalar, int64_t iValue, int iFlags)
   {

      //if (escalar == scalar_app_install_progress)
      //{

      //   m_iProgressInstallStep = iValue;

      //}
      //else if (escalar == scalar_app_install_progress_min)
      //{

      //   m_iProgressInstallStart = iValue;

      //}
      //else if (escalar == scalar_app_install_progress_max)
      //{

      //   m_iProgressInstallEnd = iValue;

      //}
      //else
      {

         return ::int_scalar_source::on_set_scalar(escalar, iValue, iFlags);

      }

   }


   void application::get_scalar_minimum(e_scalar escalar, int64_t & i)
   {

      //if (escalar == scalar_app_install_progress)
      //{

      //   i = m_iProgressInstallStart;

      //}
      //else if (escalar == scalar_app_install_progress_min)
      //{

      //   i = 0;

      //}
      //else if (escalar == scalar_app_install_progress_max)
      //{

      //   i = 0;

      //}
      //else
      {

         ::int_scalar_source::get_scalar_minimum(escalar, i);

      }

   }

   void application::get_scalar(e_scalar escalar, int64_t & i)
   {

      //if (escalar == scalar_app_install_progress)
      //{

      //   i = m_iProgressInstallStep;

      //}
      //else if (escalar == scalar_app_install_progress_min)
      //{

      //   i = m_iProgressInstallStart;

      //}
      //else if (escalar == scalar_app_install_progress_max)
      //{

      //   i = m_iProgressInstallEnd;

      //}
      //else
      {

         ::int_scalar_source::get_scalar(escalar, i);

      }

   }

   void application::get_scalar_maximum(e_scalar escalar, int64_t & i)
   {

      //if (escalar == scalar_download_size)
      //{

      //   i = m_iProgressInstallEnd;

      //}
      //else if (escalar == scalar_app_install_progress_min)
      //{

      //   i = 0x7fffffff;

      //}
      //else if (escalar == scalar_app_install_progress_max)
      //{

      //   i = 0x7fffffff;

      //}
      //else
      {

         ::int_scalar_source::get_scalar_minimum(escalar, i);

      }

   }


   int32_t application::simple_message_box_timeout(::user::primitive * pwndOwner, const char * pszMessage, ::duration durationTimeOut, UINT fuStyle)
   {
      UNREFERENCED_PARAMETER(durationTimeOut);
      return simple_message_box(pwndOwner, pszMessage, fuStyle);
   }



   service_base * application::get_service()
   {

      return m_pservice;

   }








   application * application_ptra::find_by_app_name(const string & strAppName)
   {

      application * papp = NULL;

      for (int32_t i = 0; i < get_count(); i++)
      {
         try
         {

            papp = element_at(i).m_p;

            if (papp == NULL)
               continue;

            if (papp->m_strAppName == strAppName)
            {

               return papp;

            }

         }
         catch (...)
         {

         }

      }

      return NULL;


   }


   application * application_ptra::find_running_defer_try_quit_damaged(const string & strAppName)
   {

      sp(application) papp = find_by_app_name(strAppName);

      if (papp.is_null())
         return NULL;

      if (papp->safe_is_running())
         return papp;

      try
      {

         papp->post_quit();

      }
      catch (...)
      {

      }

      try
      {

         papp.release();

      }
      catch (...)
      {

      }

      return NULL;

   }




   string application::get_license_id()
   {

      return m_strAppId;

   }





   bool application::gudo_get(const string & strKey, ::file::serializable & obj)
   {

      ::file::path strPath(strKey);

      strPath.replace("::", "/");

      synch_lock sl(System.m_spmutexUserAppData);

      {

         ::file::file_sp file = this->file().get_file(System.dir().appdata() / "gudo" / strPath, ::file::mode_read);

         if (file.is_null())
         {

            return false;

         }

         ::file::buffered_file buffer(this, file);

         ::file::byte_istream is(&buffer);

         try
         {

            obj.read(is);

         }
         catch (...)
         {

         }

      }

      return true;

   }

   bool application::gudo_set(const string & strKey, ::file::serializable & obj)
   {

      string strPath(strKey);

      strPath.replace("::", "/");

      synch_lock sl(System.m_spmutexUserAppData);

      {

         ::file::file_sp file = this->file().get_file(System.dir().appdata() / "gudo" / strPath, ::file::mode_write | ::file::mode_create | ::file::defer_create_directory);

         if (file.is_null())
         {

            return false;

         }

         ::file::buffered_file buffer(this, file);

         ::file::byte_ostream os(&buffer);

         try
         {

            obj.write(os);

         }
         catch (...)
         {

         }

      }

      return true;

   }


   bool application::assert_user_logged_in()
   {

      return false;

   }


   bool application::startup_command(::command::command * pcommand)
   {

      m_pcommand = pcommand;

      return true;

   }


   string application::http_get_locale_schema(const char * pszUrl, const char * pszLocale, const char * pszSchema)
   {

      ::exception::throw_interface_only(get_app());

      return "";

   }


   void application::process_message_filter(int32_t code, ::message::message * pobj)
   {

      //if(pobj == NULL)
      //   return;   // not handled

      //SCAST_PTR(::message::base,pbase,pobj);

      //sp(::user::frame_window) pTopFrameWnd;
      //::user::primitive * pMainWnd;
      //::user::primitive * pMsgWnd;
      //switch(code)
      //{
      ////case MSGF_DDEMGR:
      //   // Unlike other WH_MSGFILTER codes, MSGF_DDEMGR should
      //   //  never call the next hook.
      //   // By returning FALSE, the message will be dispatched
      //   //  instead (the default behavior).
      //   //return;

      //case MSGF_MENU:
      //   pMsgWnd = pbase->m_pwnd;
      //   if(pMsgWnd != NULL)
      //   {
      //      pTopFrameWnd = pMsgWnd->GetTopLevelFrame();
      //      if(pTopFrameWnd != NULL && pTopFrameWnd->IsTracking() &&
      //         pTopFrameWnd->m_bHelpMode)
      //      {
      //         //pMainWnd = __get_main_window();
      //         //if((m_puiMain != NULL) && (IsEnterKey(pbase) || IsButtonUp(pbase)))
      //         //{
      //         //   //                  pMainWnd->SendMessage(WM_COMMAND, ID_HELP);
      //         //   pbase->m_bRet = true;
      //         //   return;
      //         //}
      //      }
      //   }
      //   // fall through...

      //case MSGF_DIALOGBOX:    // handles message boxes as well.
      //   //pMainWnd = __get_main_window();
      //   if(code == MSGF_DIALOGBOX && m_pthread->m_puiActive != NULL &&
      //      pbase->m_id >= WM_KEYFIRST && pbase->m_id <= WM_KEYLAST)
      //   {
      //      //// need to translate messages for the in-place container
      //      //___THREAD_STATE* pThreadState = __get_thread_state();
      //      //ENSURE(pThreadState);

      //      //if (pThreadState->m_bInMsgFilter)
      //      //   return;
      //      //pThreadState->m_bInMsgFilter = TRUE;    // avoid reentering this code
      //      //if (m_puiActive->is_window_enabled())
      //      //{
      //      //   pre_translate_message(pobj);
      //      //   if(pobj->m_bRet)
      //      //   {
      //      //      pThreadState->m_bInMsgFilter = FALSE;
      //      //      return;
      //      //   }
      //      //}
      //      //pThreadState->m_bInMsgFilter = FALSE;    // ok again
      //   }
      //   break;
      //}
      //// default to not handled

   }

   bool application::on_thread_on_idle(::thread * pthread, LONG lCount)
   {

      UNREFERENCED_PARAMETER(pthread);

      return lCount < 0;

   }


   bool application::post_user_message(::thread * pthread, ::user::primitive * pui, UINT message, WPARAM wparam, lparam lparam)
   {

      UNREFERENCED_PARAMETER(pthread);
      UNREFERENCED_PARAMETER(pui);
      UNREFERENCED_PARAMETER(message);
      UNREFERENCED_PARAMETER(wparam);
      UNREFERENCED_PARAMETER(lparam);

      return false;

   }


   void application::message_handler(::message::base * pbase)
   {

      ::thread::message_handler(pbase);

   }


   bool application::is_window(::user::primitive * pui)
   {

      UNREFERENCED_PARAMETER(pui);

      return false;

   }

   LRESULT application::send_message(::user::primitive * pui, UINT message, WPARAM wparam, lparam lparam)
   {

      UNREFERENCED_PARAMETER(pui);
      UNREFERENCED_PARAMETER(message);
      UNREFERENCED_PARAMETER(wparam);
      UNREFERENCED_PARAMETER(lparam);

      return 0;

   }

   oswindow application::get_safe_handle(::user::primitive * pui)
   {

      UNREFERENCED_PARAMETER(pui);

      return NULL;

   }


   void application::dispatch_user_message(::message::message * pbase)
   {

      UNREFERENCED_PARAMETER(pbase);

   }


   ::user::primitive * application::get_parent(::user::primitive * pui)
   {

      UNREFERENCED_PARAMETER(pui);

      return NULL;

   }

   bool application::enable_window(::user::primitive * pui, bool bEnable)
   {

      UNREFERENCED_PARAMETER(pui);
      UNREFERENCED_PARAMETER(bEnable);

      return false;

   }


   bool application::set_window_text(::user::primitive * pui, const string & strText)
   {

      UNREFERENCED_PARAMETER(pui);
      UNREFERENCED_PARAMETER(strText);

      return false;

   }



   //void application::window_graphics_update_window(window_graphics ** ppdata,oswindow interaction_impl,COLORREF * pOsBitmapData,const RECT & rect,int cxParam,int cyParam,int iStride,bool bTransferBuffer)
   //{

   //   // derived classes should implement this function in order to update window

   //}

   //sp(::message::base) application::get_message_base(LPMESSAGE lpmsg)
   //{

   //   sp(::message::base) pbase = canew(::message::base(get_app()));

   //   if (pbase == NULL)
   //      return NULL;

   //   pbase->set(NULL, lpmsg->message, lpmsg->wParam, lpmsg->lParam);

   //   return pbase;

   //}


   //void application::process_message(::message::base * pbase)
   //{

   //   message_handler(pbase);

   //}


   void application::set_locale(const string & lpcsz, ::action::context actioncontext)
   {
      string strLocale(lpcsz);
      strLocale.trim();
      m_strLocale = strLocale;
      on_set_locale(m_strLocale, actioncontext);
   }

   void application::set_schema(const string & lpcsz, ::action::context actioncontext)
   {
      string strSchema(lpcsz);
      strSchema.trim();
      m_strSchema = strSchema;
      on_set_schema(m_strSchema, actioncontext);
   }

   void application::on_set_locale(const string & lpcsz, ::action::context actioncontext)
   {
      UNREFERENCED_PARAMETER(actioncontext);
      UNREFERENCED_PARAMETER(lpcsz);
      //System.appa_load_string_table();
   }

   void application::on_set_schema(const string & lpcsz, ::action::context actioncontext)
   {
      UNREFERENCED_PARAMETER(actioncontext);
      UNREFERENCED_PARAMETER(lpcsz);
      //System.appa_load_string_table();
   }


   string application::get_locale()
   {
      return m_strLocale;
   }

   string application::get_schema()
   {
      return m_strSchema;
   }


   ::file::path application::get_locale_schema_dir()
   {

      return ::file::path(get_locale()) / get_schema();

   }


   ::file::path application::get_locale_schema_dir(const string & strLocale)
   {

      if (strLocale.is_empty())
      {

         return ::file::path(get_locale()) / get_schema();

      }
      else
      {

         return ::file::path(strLocale) / get_schema();

      }

   }


   ::file::path application::get_locale_schema_dir(const string & strLocale, const string & strSchema)
   {

      if (strLocale.is_empty())
      {

         if (strSchema.is_empty())
         {

            return ::file::path(get_locale()) / get_schema();

         }
         else
         {

            return ::file::path(get_locale()) / strSchema;

         }

      }
      else
      {

         if (strSchema.is_empty())
         {

            return ::file::path(strLocale) / get_schema();

         }
         else
         {

            return ::file::path(strLocale) / strSchema;

         }

      }

   }


   void application::fill_locale_schema(::str::international::locale_schema & localeschema, const string & pszLocale, const string & pszSchema)
   {


      localeschema.m_idaLocale.remove_all();
      localeschema.m_idaSchema.remove_all();


      string strLocale(pszLocale);
      string strSchema(pszSchema);


      localeschema.m_idLocale = pszLocale;
      localeschema.m_idSchema = pszSchema;


      localeschema.add_locale_variant(strLocale, strSchema);
      localeschema.add_locale_variant(get_locale(), strSchema);
      localeschema.add_locale_variant(__id(std), strSchema);
      localeschema.add_locale_variant(__id(en), strSchema);


      localeschema.finalize();


   }


   void application::fill_locale_schema(::str::international::locale_schema & localeschema)
   {


      localeschema.m_idaLocale.remove_all();
      localeschema.m_idaSchema.remove_all();


      //localeschema.m_bAddAlternateStyle = true;


      stringa straLocale;
      stringa straSchema;

      straLocale.add(get_locale());
      straSchema.add(get_schema());


      stringa stra;

      stra = Application.handler()->m_varTopicQuery["locale"].stra();

      stra.remove_ci("_std");

      straLocale.add_unique(Application.handler()->m_varTopicQuery["locale"].stra());

      stra = Application.handler()->m_varTopicQuery["schema"].stra();

      stra.remove_ci("_std");

      straSchema.add_unique(Application.handler()->m_varTopicQuery["schema"].stra());


      localeschema.m_idLocale = straLocale[0];
      localeschema.m_idSchema = straSchema[0];

      for (index iLocale = 0; iLocale < straLocale.get_count(); iLocale++)
      {

         for (index iSchema = 0; iSchema < straSchema.get_count(); iSchema++)
         {

            localeschema.add_locale_variant(straLocale[iLocale], straSchema[iSchema]);

         }

      }

      for (index iSchema = 0; iSchema < straSchema.get_count(); iSchema++)
      {

         localeschema.add_locale_variant(get_locale(), straSchema[iSchema]);

      }

      for (index iSchema = 0; iSchema < straSchema.get_count(); iSchema++)
      {

         localeschema.add_locale_variant(__id(std), straSchema[iSchema]);

      }


      for (index iSchema = 0; iSchema < straSchema.get_count(); iSchema++)
      {

         localeschema.add_locale_variant(__id(en), straSchema[iSchema]);

      }

      localeschema.finalize();


   }


   //   void application::defer_add_thread_run_wait(sync_object_ptra & soa)
   //   {
   //
   ////      soa.add(&axiom()->m_ev);
   //
   //   }
   //

   bool application::platform_open_by_file_extension(index iEdge, const char * pszPathName, application_bias * pbiasCreate)
   {

      return false;

   }


   bool application::platform_open_by_file_extension(index iEdge, ::create * pcc)
   {

      return false;

   }


   sp(::aura::application) application::instantiate_application(const char * pszAppId, application_bias * pbias)
   {

      thisstart;

      sp(::aura::application) papp;

      string strAppId(pszAppId);

      if (strAppId.compare_ci("session") == 0)
      {

         papp = create_platform(m_pauraapp->m_paurasession);

         papp->m_strAppId = "session";

      }
      else
      {

         papp = Session.get_new_application(pbias == NULL ? this : pbias->get_app(), strAppId);

         if (papp == NULL)
         {

            return NULL;

         }

         papp->m_paurasession = m_paurasession;

         papp->m_paxissession = m_paxissession;

         papp->m_pbasesession = m_pbasesession;

         if (papp != NULL)
         {

            if (strAppId == "bergedge" || strAppId == "cube")
            {

               papp->m_strAppId = strAppId;

            }

            if (papp->m_strInstallToken.is_empty())
            {

               papp->m_strInstallToken = papp->m_strAppId;

            }

         }

      }

      papp->m_pcoresystem = m_pcoresystem;

      papp->m_pbasesystem = m_pbasesystem;

      papp->handler()->merge(System.handler());

      papp->handler()->merge(handler());

      if (pbias != NULL)
      {

         papp->oprop_set().merge(pbias->m_set);

      }
      else
      {

         papp->oprop("SessionSynchronizedInput") = true;
         papp->oprop("NativeWindowFocus") = true;

      }

      if ((papp == NULL || papp->m_strAppId != strAppId)
            &&
            (!Application.handler()->m_varTopicQuery.has_property("install")
             && !Application.handler()->m_varTopicQuery.has_property("uninstall")))
      {

         TRACE("Failed to instantiate %s, going to try installation through ca2_cube_install", strAppId);

         string strCommand;

         strCommand = "app=" + strAppId;

         strCommand += " locale=" + Session.m_strLocale;

         strCommand += " style=" + Session.m_strSchema;

         strCommand += " install";

         //System.start_installation(strCommand);

         _throw(installing_exception(get_app()));

         return NULL;

      }

      return papp;

   }


   sp(::aura::application) application::create_application(const char * pszAppId, bool bSynch, application_bias * pbias)
   {

      sp(::aura::application) pbaseapp = instantiate_application(pszAppId, pbias);

      if (pbaseapp == NULL)
      {

         return NULL;

      }

      ::aura::application * papp = pbaseapp;

      if (!papp->start_application(bSynch, pbias))
      {

         return NULL;

      }

      return pbaseapp;

   }


   sp(::aura::application) application::create_platform(::aura::session * psession)
   {

      return NULL;

   }


   bool application::on_start_application()
   {

      string strAppId = m_strAppId;

      string strJson = Application.file().as_string(::dir::system() / "config" / strAppId / +"http.json");

      if (strJson.has_char())
      {

         try
         {

            Application.http().m_setHttp.parse_json(strJson);

         }
         catch (...)
         {

         }

      }

      if(!os_on_start_application())
      {

         return false;

      }

      return true;

   }


   bool application::start_application(bool bSynch, application_bias * pbias)
   {

      try
      {

         if (pbias != NULL)
         {

            if (pbias->m_pcallback != NULL)
            {

               pbias->m_pcallback->connect_to(this);

            }

         }
      }
      catch (...)
      {
      }

      if (pbias != NULL)
      {

         m_biasCalling = *pbias;

      }

      if (bSynch)
      {

         if (!begin_synch())
         {

            return false;

         }

      }
      else
      {

         begin();

      }


      return true;

   }



   bool application::on_run_exception(::exception::exception * pe)
   {

      ::output_debug_string("aura::application::on_run_exception An unexpected error has occurred and no special exception handling is available.");

      if (pe->m_bHandled)
      {

         return pe->m_bContinue;

      }

//      if (typeid(*pe) == typeid(not_installed))
//      {
//
//         not_installed * pnotinstalled = dynamic_cast <not_installed *> (pe);
//
//         return handle_not_installed(pnotinstalled);
//
//      }

      //simple_message_box_timeout("An unexpected error has occurred and no special exception handling is available.<br>Timeout: $simple_message_box_timeout", 5000);

      return true; // continue or exit application? by default: continue by returning true

   }


//   bool application::handle_not_installed(::not_installed * pnotinstalled)
//   {
//
//      pnotinstalled->m_bHandled = true;
//
//      pnotinstalled->m_bContinue = true;
//
//      bool bDebuggerCheck = true;
//
//#ifdef APPLEOS
//
//      bDebuggerCheck = false;
//
//#endif
//
//      if (((!bDebuggerCheck || ::is_debugger_attached()) && !file_exists_dup(::dir::system() / "config\\plugin\\disable_manual_install_warning.txt")
//            && !file_exists_dup(::dir::system() / "config\\system\\skip_debug_install.txt")) || file_exists_dup(::dir::system() / "config\\system\\enable_debug_install.txt"))
//         //|| (App(notinstalled.get_app()).is_serviceable() && !App(notinstalled.get_app()).is_user_service()))
//      {
//
//         try
//         {
//
//            ::file::path pathModule;
//
//            ::process::exit_status exitstatus;
//
//            bool bTimedOut = false;
//
//            string strParam;
//
//            ::file::path path;
//
//#ifdef LINUX
//
//            path = System.dir().ca2module() / ::process::app_id_to_app_name(pnotinstalled->m_strAppId);
//
//#else
//
//            path = System.dir().ca2module() / "app";
//
//#endif
//
//#ifdef WINDOWS
//
//            path += ".exe";
//
//#elif defined(APPLEOS)
//
//
//            //                     strPath += ".app/Contents/MacOS/app";
//            // please be extremely careful with code below.
//            // Package app.app project with the <your-app> project!
//            // The code below will seem to be guilty and blameable if you skipp app.app packaging with your app.
////            ::file::path path = get_exe_path();
////
////            index i = 5;
////
////            while(i >= 0)
////            {
////
////               path = path.folder();
////
////               strPath = path / "app";
////
////               output_debug_string("\n xyzxyzx " + strPath + "\n");
////               output_debug_string("\n xyzxyzx " + strPath + "\n");
////               output_debug_string("\n xyzxyzx " + strPath + "\n");
////               output_debug_string("\n xyzxyzx " + strPath + "\n");
////               output_debug_string("\n xyzxyzx " + strPath + "\n");
////
////               if(Application.file().exists(strPath))
////               {
////
////                  output_debug_string("\n OK OK K " + strPath + "\n");
////
////                  break;
////
////               }
////
////               i--;
////
////            }
////
////            //                     setenv("DYLD_FALLBACK_LIBRARY_PATH",System.dir().ca2module(), 1 );
////            //                     setenv("DYLD_FALLBACK_LIBRARY_PATH",strPath, 1 );
//
//            path = get_exe_path();
//
//            ::output_debug_string("\n\n xyzxyzx OK OK K " + path + "\n\n");
//
//            path = "\"" + path + "\"";
//
//#endif
//
//            pathModule = path;
//
//            //#if defined(APPLEOS)
//            //                   strPath = "/usr/bin/open -n " + strPath + " --args : app=" + notinstalled.m_strId + " install build=" + strBuild + " locale=" + notinstalled.m_strLocale + " schema=" + //notinstalled.m_strSchema;
//            //#else
//
//            //strParam = " : install app=" + pnotinstalled->m_strAppId + " platform=" + pnotinstalled->m_strPlatform + " configuration=" + pnotinstalled->m_strConfiguration + " locale=" + pnotinstalled->m_strLocale + " schema=" + pnotinstalled->m_strSchema;
//
//            strParam = " : install ";
//
//            stringa straKeys;
//
//#ifdef WINDOWS
//
//            straKeys.add("app");
//
//            //strParam += " app=" + pnotinstalled->m_strAppId;
//
//#endif
//
//            straKeys.add("platform");
//
//            straKeys.add("configuration");
//
//            straKeys.add("locale");
//
//            straKeys.add("schema");
//
//            strParam += System.handler()->m_spcommandline->m_varQuery.propset().get_command_line(straKeys);
//
//            //{
//
//            //   strParam
//
//            //}
//
//            //#endif
//
//            //               if(App(notinstalled.get_app()).is_serviceable() && !App(notinstalled.get_app()).is_user_service())
//            //               {
//            //
//            //
//            //                  HANDLE hToken = NULL;
//            //
//            //                  //if(LogonUserW(L"LocalServer",L"NT AUTHORITY",NULL,LOGON32_LOGON_SERVICE,LOGON32_PROVIDER_DEFAULT,&hToken))
//            //                  //{
//            //                  //
//            //                  //   ::simple_message_box(NULL,"Failed to Login at Local System Account","Debug only message, please install.",MB_ICONINFORMATION | MB_OK);
//            //                  //}
//            //
//            //                  // os << "Impersonation OK!!<br>";
//            //
//            ////                  strPath = "\"" + System.file().name_(strModuleFilePath) + "\" : install";
//            //                  string strCmdLine = strPath + strParam;
//            //                  wstring wstrCmdLine = strCmdLine;
//            //                  string strModuleFolder = System.get_module_folder();
//            //                  wstring wstrModuleFolder = strModuleFolder;
//            //                  LPSTR lpsz = (char *)(const char *)(strCmdLine);
//            //                  LPWSTR lpwsz = (unichar *)(const unichar *)(wstrCmdLine);
//            //                  STARTUPINFO m_si;
//            //                  PROCESS_INFORMATION m_pi;
//            //                  memset(&m_si,0,sizeof(m_si));
//            //                  memset(&m_pi,0,sizeof(m_pi));
//            //                  m_si.cb = sizeof(m_si);
//            //                  m_si.wShowWindow = SW_HIDE;
//            //
//            //                  if(LaunchAppIntoSystemAcc(strModuleFilePath,lpsz,strModuleFolder,&m_si,&m_pi))
//            //                  //if(LaunchAppIntoDifferentSession(strModuleFilePath,lpsz,strModuleFolder,&m_si,&m_pi, 0))
//            //                  //if(::CreateProcessAsUserW(hToken,wstring(strModuleFilePath),lpsz,NULL,NULL,TRUE,CREATE_NEW_CONSOLE,NULL,wstrModuleFolder,&m_si,&m_pi))
//            //                  {
//            //                     TRACE("Launched");
//            //
//            //
//            //                  }
//            //                  else
//            //                  {
//            //                     uint32_t dwLastError = ::get_last_error();
//            //                     TRACE("Not Launched");
//            //
//            //                     WCHAR wsz[1024];
//            //
//            //                     DWORD dwSize = sizeof(wsz) / sizeof(WCHAR);
//            //
//            //                     GetUserNameW(wsz,&dwSize);
//            //
//            //                     string strUserName = wsz;
//            //
//            //                     if(strUserName != "NetworkService")
//            //                     {
//            //
//            //                        goto Launch;
//            //
//            //                     }
//            //
//            //                  }
//            //
//            //                  dwExitCode = 0;
//            //
//            //                  while(::GetExitCodeProcess(m_pi.hProcess,&dwExitCode))
//            //                  {
//            //
//            //                     if(dwExitCode == STILL_ACTIVE)
//            //                     {
//            //
//            //                        Sleep(100);
//            //
//            //                     }
//            //                     else
//            //                     {
//            //                        break;
//            //                     }
//            //
//            //                  }
//            //
//            //               }
//            //               else
//
//            int iRet = IDNO;
//
//            output_debug_string("\n not_installed parameters: " + strParam + "\n");
//
//            {
//
//               if (!(bool)System.oprop("not_installed_message_already_shown"))
//               {
//
////                  if ((App(pnotinstalled->get_app()).is_serviceable() && !App(pnotinstalled->get_app()).is_user_service())
////                        || (IDYES == (iRet = ::simple_message_box(NULL, "Debug only message, please install:\n\n\n\t" + pnotinstalled->m_strAppId + "\n\tconfiguration = " + pnotinstalled->m_strConfiguration + "\n\tplatform = " + pnotinstalled->m_strPlatform + "\n\tlocale = " + pnotinstalled->m_strLocale + "\n\tschema = " + pnotinstalled->m_strSchema + "\n\n\nThere are helper scripts under <solution directory>/nodeapp/stage/install/", "Debug only message, please install.", MB_ICONINFORMATION | MB_YESNO))))
//                  {
//
//                     ::duration durationWait = minutes(1);
//
//#ifdef LINUX
//
//                     exitstatus = System.process().synch(string(path) + strParam, SW_HIDE, durationWait, &bTimedOut);
//
//#else
//
//                     exitstatus = System.process().elevated_synch(string(path) + strParam, SW_HIDE, durationWait, &bTimedOut);
//
//#endif
//
//                  }
//
//               }
//
//            }
//
//            if (iRet == IDNO)
//            {
//
//               pnotinstalled->m_bContinue = false;
//
//            }
//            else if (bTimedOut)
//            {
//
//               ::simple_message_box(NULL, " - " + pnotinstalled->m_strAppId + "\nhas timed out while trying to install.\n\nFor developers it is recommended to\nfix this installation timeout problem.\n\nIt is recommended to kill manually :\n - \"" + string(path) + strParam + "\"\nif it has not been terminated yet.", "Debug only message, please install.", MB_ICONINFORMATION | MB_OK);
//
//               pnotinstalled->m_bContinue = false;
//
//            }
//            else if (exitstatus.m_iExitCode == 0)
//            {
//
//               ::simple_message_box(NULL, "Successfully run : " + string(path) + strParam, "Installation Succesful", MB_ICONINFORMATION | MB_OK);
//
//               pnotinstalled->m_bContinue = false;
//
//            }
//            else
//            {
//
//               string strMessage;
//
//               strMessage.Format("Failed return code : %d (%d, %d)",
//                                 exitstatus.m_iExitCode,
//                                 exitstatus.m_iExitSignal,
//                                 exitstatus.m_iExitStop);
//
//               ::simple_message_box(NULL, string(path) + strParam + "\n\n" + strMessage, "Debug only message, please install.", MB_ICONINFORMATION | MB_OK);
//
//               pnotinstalled->m_bContinue = false;
//
//            }
//
//         }
//         catch (...)
//         {
//
//         }
//
//      }
//      else
//      {
//
//         string strAddUp;
//
//         if (System.handler()->m_varTopicQuery.has_property("enable_desktop_launch"))
//         {
//
//            if (System.handler()->m_varTopicQuery["enable_desktop_launch"].has_char())
//            {
//
//               strAddUp = " enable_desktop_launch=" + System.handler()->m_varTopicQuery["enable_desktop_launch"];
//
//            }
//            else
//            {
//
//               strAddUp = " enable_desktop_launch=" + System.handler()->m_varTopicQuery["app"];
//
//            }
//
//         }
//
//         hotplugin_host_starter_start_sync(": app=" + pnotinstalled->m_strAppId + " install locale=" + pnotinstalled->m_strLocale + " schema=" + pnotinstalled->m_strSchema + " configuration=" + pnotinstalled->m_strConfiguration + " platform=" + pnotinstalled->m_strPlatform + strAddUp, get_app(), NULL);
//
//      }
//
//      _throw_exit(exit_system);
//
//      return false;
//   }


   int32_t application::hotplugin_host_starter_start_sync(const char * pszCommandLine, ::aura::application * papp, hotplugin::host * phost, hotplugin::plugin * pplugin)
   {

      return -1;

   }


   bool application::is_application()
   {

      return !is_session() && !is_system();

   }


   ::file::listing & application::perform_file_listing(::file::listing & listing)
   {

      return dir().ls(listing);

   }

   ::file::listing & application::perform_file_relative_name_listing(::file::listing & listing)
   {

      return dir().ls_relative_name(listing);

   }

   bool application::_001OnAgreeExit()
   {

      return true;

   }

   void application::_001OnFranceExit()
   {

      post_quit();

   }


   void application::_001FranceExit()
   {

      _001OnFranceExit();

      m_bFranceExit = true;

   }


   void application::dispatch_user_message_object(::object * pobject)
   {

      _throw(interface_only_exception(this));

   }


   void application::play_audio(var varFile, bool bSynch)
   {

      UNREFERENCED_PARAMETER(varFile);
      UNREFERENCED_PARAMETER(bSynch);

   }

   void application::post_critical_error_message(const char * pszMessage, bool bShowLog)
   {

      string strMessage;

      strMessage = System.datetime().international().get_gmt_date_time();
      strMessage += " ";
      strMessage += pszMessage;
      strMessage += "\n";

      {

         synch_lock sl(m_pmutex);

         file().add_contents(System.dir().appdata() / (System.file().module().sname() + "_log_error.txt"), strMessage);

      }

      if (bShowLog)
      {

         show_critical_error_log();

      }

   }


   string application::get_app_user_friendly_task_bar_name()
   {

      ::file::path path = m_strAppName;

      string strTitle = path.title();

      return strTitle;

   }

   void application::show_critical_error_log()
   {

      string strFile = System.dir().appdata() / (System.file().module().sname() + "_log_error.txt");

#ifdef METROWIN

      output_debug_string(strFile);

#elif defined(WINDOWS)

      call_async("C:\\Program Files (x86)\\Notepad++\\Notepad++.exe", "\"" + strFile + "\"", "", SW_SHOW, false);

#elif defined(LINUX)

      call_async("gedit", "\"" + strFile + "\"", "", SW_SHOW, false);

#else

      ::fork(this, [=]()
      {

         system("open \"" + strFile + "\"");

      });


#endif




   }


   void application::on_setting_changed(::aura::e_setting esetting)
   {


   }


   string application::http_get(const string & strUrl, ::property_set & set)
   {

      UNREFERENCED_PARAMETER(strUrl);
      UNREFERENCED_PARAMETER(set);

      return "";

   }


   bool application::compress_ungz(::file::ostream & ostreamUncompressed, const ::file::path & lpcszGzFileCompressed)
   {

      return System.compress().ungz(this, ostreamUncompressed, lpcszGzFileCompressed);

   }


   bool application::compress_ungz(::primitive::memory_base & mem)
   {

      return System.compress().ungz(this, mem);

   }


   bool application::compress_gz(::file::file * pfileOut, const ::file::path & lpcszUncompressed, int iLevel)
   {

      return System.compress().gz(this, pfileOut, lpcszUncompressed, iLevel);

   }


   bool application::compress_gz(::file::file * pfileOut, ::file::file * pfileIn, int iLevel)
   {

      return System.compress().gz(this, pfileOut, pfileIn, iLevel);

   }

   string application::fontopus_get_cred(::aura::application * papp, const string & strRequestUrl, const RECT & rect, string & strUsername, string & strPassword, string strToken, string strTitle, bool bInteractive, ::user::interactive * pinteractive)
   {

      return Sess(papp).fontopus_get_cred(papp, strRequestUrl, rect, strUsername, strPassword, strToken, strTitle, bInteractive, pinteractive);

   }


   ::file::path application::get_executable_path()
   {

      return ::dir::module() / (get_executable_title() + get_executable_extension());


   }


   string application::get_executable_extension()
   {

#ifdef WINDOWS

      return ".exe";

#else

      return "";

#endif

   }


   string application::get_executable_title()
   {

      string strTitle = get_executable_appid();

      strTitle.replace("-", "_");

      strTitle.replace("/", "_");

      return strTitle;

   }


   string application::get_executable_appid()
   {

      return m_strAppId;

   }


   void application::draw2d_factory_exchange()
   {

//#if defined(METROWIN) || defined(CUBE)
#if defined(CUBE)

      ::draw2d_factory_exchange(this);

#else

      sp(::aura::library) & library = System.m_mapLibrary["draw2d"];

      if (library->is_opened())
         return;

      string strLibrary;

      if (handler()->m_varTopicQuery.has_property("draw2d"))
      {

         string strDraw2d = handler()->m_varTopicQuery["draw2d"];

         strDraw2d.trim();

         if (strDraw2d.has_char())
         {

            ::str::begins_eat_ci(strDraw2d, "draw2d_");

            ::str::begins_eat_ci(strDraw2d, "draw2d");

            strLibrary = "draw2d_" + strDraw2d;

         }

      }

      if (strLibrary.has_char())
      {

         library->open(strLibrary);

         if (library->is_opened())
            goto finalize;

      }

      strLibrary = draw2d_get_default_library_name();

      if (strLibrary.is_empty())
#ifdef WINDOWS
         strLibrary = "draw2d_gdiplus";
#else
         strLibrary = "draw2d_cairo";
#endif

      library->open(strLibrary);

      if (library->is_opened())
         goto finalize;

#ifdef WINDOWSEX

      if (strLibrary != "draw2d_gdiplus")
      {

         library->open("draw2d_gdiplus");

         if (library->is_opened())
            goto finalize;

      }


#endif

      if (strLibrary != "draw2d_cairo")
      {


         library->open("draw2d_cairo");

         if (library->is_opened())
            goto finalize;

      }

      output_debug_string("No draw2d pluging available!!.");
      return;

finalize:

      PFN_ca2_factory_exchange pfn_ca2_factory_exchange = library->get < PFN_ca2_factory_exchange >("ca2_factory_exchange");

      pfn_ca2_factory_exchange(this);

#endif


   }


   bool application::http_download(const char * pszUrl, const char * pszFile)
   {

      string strUrl = pszUrl;

      property_set set;

      set["raw_http"] = true;

      set["disable_common_name_cert_check"] = true;

      return http().download(strUrl, pszFile, set);

   }


   string application::http_get(const char * pszUrl)
   {

      property_set set;

      set["get_response"] = "";

      set["raw_http"] = true;

      set["disable_common_name_cert_check"] = true;

      if (!http().get(pszUrl, set))
      {

         return "";

      }

      string strResponse = set["get_response"].get_string();

      return strResponse;

   }


   bool application::sys_set(string strPath, string strValue)
   {

      return Application.file().put_contents_utf8(::dir::system() / "config" / strPath, strValue);

   }


   string application::sys_get(string strPath, string strDefault)
   {

      string strValue = Application.file().as_string(::dir::system() / "config" / strPath);

      if (strValue.is_empty())
      {

         return strDefault;

      }

      return strValue;

   }


   bool application::app_set(string strPath, string strValue)
   {

      return sys_set(::file::path(m_strAppName) / strPath, strValue);

   }


   string application::app_get(string strPath, string strDefault)
   {

      return sys_get(::file::path(m_strAppName) / strPath, strDefault);

   }


   bool application::on_open_document_file(var varFile)
   {

      request_file(varFile);

      return varFile["document"].cast < ::object > () != NULL;

   }



   void application::install_trace(const string & str)
   {

      synch_lock sl(m_pmutex);

      //::install::trace_file(this, m_strInstallTraceLabel).print(str);

   }


   void application::install_trace(double dRate)
   {

      synch_lock sl(m_pmutex);

      //::install::trace_file(this, m_strInstallTraceLabel).print(dRate);

   }


   bool application::register_spa_file_type()
   {

#ifdef WINDOWSEX

      HKEY hkey;

      wstring extension = L".spa";                     // file extension
      wstring desc = L"spafile";          // file type description
      wstring content_type = L"application/x-spa";

      wstring app(::dir::stage(m_strAppId, "x86"));

      wstring icon(app);

      app = L"\"" + app + L"\"" + L" \"%1\"";
      icon = L"\"" + icon + L"\",107";

      wstring action = L"Open";

      wstring sub = L"\\shell\\";

      wstring path = L"spafile\\shell\\open\\command";


      // 1: Create subkey for extension -> HKEY_CLASSES_ROOT\.002
      if (RegCreateKeyExW(HKEY_CLASSES_ROOT, extension.c_str(), 0, 0, 0, KEY_ALL_ACCESS, 0, &hkey, 0) != ERROR_SUCCESS)
      {
         output_debug_string("Could not create or open a registrty key\n");
         return 0;
      }
      RegSetValueExW(hkey, L"", 0, REG_SZ, (BYTE*)desc.c_str(), DWORD (desc.length() * sizeof(wchar_t))); // default vlaue is description of file extension
      RegSetValueExW(hkey, L"ContentType", 0, REG_SZ, (BYTE*)content_type.c_str(), DWORD (content_type.length() * sizeof(wchar_t))); // default vlaue is description of file extension
      RegCloseKey(hkey);



      // 2: Create Subkeys for action ( "Open with my program" )
      // HKEY_CLASSES_ROOT\.002\Shell\\open with my program\\command
      if (RegCreateKeyExW(HKEY_CLASSES_ROOT, path.c_str(), 0, 0, 0, KEY_ALL_ACCESS, 0, &hkey, 0) != ERROR_SUCCESS)
      {
         output_debug_string("Could not create or open a registrty key\n");
         return 0;
      }
      RegSetValueExW(hkey, L"", 0, REG_SZ, (BYTE*)app.c_str(), DWORD(app.length() * sizeof(wchar_t)));
      RegCloseKey(hkey);


      path = L"spafile\\DefaultIcon";

      if (RegCreateKeyExW(HKEY_CLASSES_ROOT, path.c_str(), 0, 0, 0, KEY_ALL_ACCESS, 0, &hkey, 0) != ERROR_SUCCESS)
      {
         output_debug_string("Could not create or open a registrty key\n");
         return 0;
      }
      RegSetValueExW(hkey, L"", 0, REG_SZ, (BYTE*)icon.c_str(), DWORD (icon.length() * sizeof(wchar_t)));
      RegCloseKey(hkey);

      wstring wstr(dir::stage(m_strAppId, "x86") / "spa_register.txt");

      int iRetry = 9;

      while (!file_exists_dup(u8(wstr.c_str())) && iRetry > 0)
      {

         dir::mk(dir::name(u8(wstr.c_str())).c_str());

         file_put_contents_dup(u8(wstr.c_str()).c_str(), "");

         iRetry--;

         Sleep(100);

      }

#endif

      return true;

   }


   bool application::low_is_app_app_admin_running(string strPlatform)
   {

      ::install::admin_mutex smutex(strPlatform);

      return smutex.already_exists();

   }


   void application::defer_start_program_files_app_app_admin(string strPlatform)
   {

      if (low_is_app_app_admin_running(strPlatform))
      {

         return;

      }

      start_program_files_app_app_admin(strPlatform);

   }


   void application::start_program_files_app_app_admin(string strPlatform)
   {

#ifdef WINDOWSEX

      SHELLEXECUTEINFOW sei = {};

      string str = ::path::app_app_admin(strPlatform);

      if (!::file_exists_dup(str))
      {

         return;

      }

      ::install::admin_mutex mutexStartup("-startup");

      wstring wstr(str);

      sei.cbSize = sizeof(SHELLEXECUTEINFOW);
      sei.fMask = SEE_MASK_NOASYNC | SEE_MASK_NOCLOSEPROCESS;
      sei.lpVerb = L"RunAs";
      sei.lpFile = wstr.c_str();
      ::ShellExecuteExW(&sei);
      DWORD dwGetLastError = get_last_error();

#endif

   }


   string application::get_app_id(string wstr)
   {

      if (wstr.length() <= 0)
      {

         return "";

      }

      wstr.trim();

      ::str::trim_any_quotes(wstr);

      wstr.trim();

      if (wstr.length() <= 0)
      {

         return "";

      }

      ::xml::document doc(get_app());

      ::string strPath = wstr.c_str();

      ::string strContents = file_as_string_dup(strPath.c_str());

      if (!doc.load(strContents.c_str()))
      {

         return "";

      }

      sp(xml::node) pnode = doc.get_root();

      if (pnode == NULL)
      {

         return "";

      }

      const char * psz = pnode->GetChildAttrValue("launch", "app");

      if (psz == NULL || *psz == '\0')
      {

         return "";

      }

      return psz;

   }


   LPWAVEOUT application::waveout_open(int iChannel, LPAUDIOFORMAT pformat, LPWAVEOUT_CALLBACK pcallback)
   {

      _throw(interface_only_exception(NULL));

      return NULL;

   }


   bool application::keyboard_focus_is_focusable(::user::elemental * pue)
   {

      return false;

   }


   bool application::keyboard_focus_OnSetFocus(::user::elemental * pue)
   {

      return true;

   }

   bool application::get_frame(sp(::user::interaction) & pui)
   {

#ifdef VSNORD

      if (System.m_possystemwindow != NULL)
      {

         if (System.m_possystemwindow->m_pui != NULL)
         {

            return System.m_possystemwindow->m_pui->m_uiptraChild.get_child(pui);

         }

      }

#endif

      synch_lock sl(&m_mutexFrame);

      return m_puiptraFrame->get_child(pui);

   }




   void application::add_frame(::user::interaction * pwnd)
   {

#if !defined(LINUX) && !defined(METROWIN) && !defined(APPLEOS) && !defined(VSNORD)

      if (dynamic_cast <::user::system_interaction_impl *>(pwnd) != NULL)
      {

         return;

      }

#endif

      if (pwnd == NULL)
      {

         return;

      }

      synch_lock sl(&m_mutexFrame); // recursive lock (on m_framea.add(pwnd)) but m_puiMain is "cared" by m_frame.m_mutex

      if (m_puiptraFrame->add_unique(pwnd))
      {

         TRACE("::base::application::add_frame ::user::interaction = %0x016x (%s) app=%s", pwnd, typeid(*pwnd).name(), typeid(*this).name());

         System.defer_create_system_frame_window();

         Session.on_create_frame_window();

         if (m_puiMain == NULL)
         {

            m_puiMain = pwnd;

         }

      }

   }


   void application::remove_frame(::user::interaction * pwnd)
   {

      synch_lock sl(&m_mutexFrame); // recursive lock (on m_framea.remove(pwnd)) but m_puiMain is "cared" by m_frame.m_mutex


      //if(get_active_uie() == pwnd)
      //{

      //   set_a

      //}


      if (m_puiMain == pwnd)
      {

         m_puiMain = NULL;

      }

      if (m_puiptraFrame != NULL)
      {

         if (m_puiptraFrame->remove(pwnd) > 0)
         {

            TRACE("::base::application::remove_frame ::user::interaction = %0x016x (%s) app=%s", pwnd, typeid(*pwnd).name(), typeid(*this).name());

         }

      }


   }



   bool application::send_message_to_windows(UINT message, WPARAM wparam, LPARAM lparam) // with tbs in <3
   {

      sp(::user::interaction) pwnd;

      try
      {

         while (get_frame(pwnd))
         {

            try
            {

               if (pwnd != NULL && pwnd->IsWindow())
               {

                  try
                  {

                     pwnd->send_message(message, wparam, lparam);

                  }
                  catch (...)
                  {

                  }

                  try
                  {

                     pwnd->send_message_to_descendants(message, wparam, lparam);

                  }
                  catch (...)
                  {


                  }

               }

            }
            catch (...)
            {

            }

         }

      }
      catch (...)
      {

      }

      return true;

   }


   bool application::route_message_to_windows(::message::message * pmessage) // with tbs in <3
   {

      sp(::user::interaction) pwnd;

      try
      {

         while (get_frame(pwnd))
         {

            try
            {

               if (pwnd != NULL && pwnd->IsWindow())
               {

                  try
                  {

                     pwnd->route_message(pmessage);

                  }
                  catch (...)
                  {

                  }

                  try
                  {

                     pwnd->route_message_to_descendants(pmessage);

                  }
                  catch (...)
                  {


                  }

               }

            }
            catch (...)
            {

            }

         }

      }
      catch (...)
      {


      }

      return true;

   }


   void application::send_language_change_message()
   {

      ::message::message message(::message::type_language);

      route_message_to_windows(&message);

   }

   sp(::message::base) application::get_message_base(UINT message, WPARAM wparam, lparam lparam)
   {

      MESSAGE msg;

      ZERO(msg);

      msg.message = message;
      msg.wParam = wparam;
      msg.lParam = lparam;


      return get_message_base(&msg);





   }

   sp(::message::base) application::get_message_base(LPMESSAGE lpmsg)
   {

      ::user::interaction * pui = NULL;

      if (pui == NULL && lpmsg->hwnd != NULL)
      {

         if (lpmsg->message == 126)
         {

            TRACE("WM_DISPLAYCHANGE");

         }

         ::user::interaction_impl * pimpl = System.impl_from_handle(lpmsg->hwnd);

         if (pimpl != NULL)
         {

            try
            {

               pui = pimpl->m_pui;

            }
            catch (...)
            {

               pui = NULL;

            }

         }

         if (pui == NULL)
            return NULL;

      }

      if (pui != NULL)
      {

         return pui->get_message_base(lpmsg->message, lpmsg->wParam, lpmsg->lParam);

      }

      sp(::message::base) pbase = canew(::message::base(get_app()));

      if (pbase == NULL)
         return NULL;

      pbase->set(NULL, lpmsg->message, lpmsg->wParam, lpmsg->lParam);

      return pbase;



   }


   void application::process_message(::message::base * pbase)
   {

      if (pbase->m_pwnd == NULL)
      {

         try
         {

            message_handler(pbase);

         }
         catch (::exception::exception * pexception)
         {

            esp671 esp(pexception);

            process_window_procedure_exception(pexception, pbase);

            TRACE("application::process_message : error processing application thread message (const ::exception::exception & )");

            if (App(this).on_run_exception(esp))
               goto run;

            if (App(this).final_handle_exception(esp))
               goto run;

            __post_quit_message(-1);

            pbase->set_lresult(-1);

            return;

         }
         catch (...)
         {

            TRACE("application::process_message : error processing application thread message (...)");

         }

         return;

      }

      try
      {

         pbase->m_pwnd->m_puiThis->message_handler(pbase);

      }
      catch (::exception::exception * pexception)
      {

         esp671 esp(pexception);

         process_window_procedure_exception(pexception, pbase);

         TRACE("application::process_message : error processing window message (const ::exception::exception & )");

         if (App(this).on_run_exception(esp))
            goto run;

         if (App(this).final_handle_exception(esp))
            goto run;

         __post_quit_message(-1);

         pbase->set_lresult(-1);

         return;

      }
      catch (...)
      {

         TRACE("application::process_message : error processing window message (...)");

      }

run:
      ;

   }


   ::user::interaction * application::main_window()
   {

      if (m_puiMain == NULL)
         return NULL;

      return m_puiMain->m_puiThis;

   }
   string application::preferred_userschema()
   {

      return "";

   }

   ::user::document *application::place_hold(::user::interaction * pui)
   {

      return NULL;

   }


   ::visual::icon * application::set_icon(object * pobject, ::visual::icon * picon, bool bBigIcon)
   {

      ::visual::icon * piconOld = get_icon(pobject, bBigIcon);

      if (bBigIcon)
      {

         pobject->oprop("big_icon").operator =((sp(object)) picon);

      }
      else
      {

         pobject->oprop("small_icon").operator =((sp(object)) picon);

      }

      return piconOld;

   }


   ::visual::icon * application::get_icon(object * pobject, bool bBigIcon) const
   {

      if (bBigIcon)
      {

         return const_cast <object *> (pobject)->oprop("big_icon").cast < ::visual::icon >();

      }
      else
      {

         return const_cast <object *> (pobject)->oprop("small_icon").cast < ::visual::icon >();

      }

   }


} // namespace aura










