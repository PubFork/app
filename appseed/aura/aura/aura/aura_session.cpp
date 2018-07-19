#include "framework.h"
#include "aura/net/sockets/bsd/sockets_sockets.h"


#ifdef METROWIN

#include "aura/os/metrowin/metrowin_user_impl.h"

#endif



namespace aura
{


   session::session(::aura::application * papp) :
      object(papp),
      ::thread(papp)
   {


      m_pauraapp = papp;

      m_paurasession = this;

      m_paurasystem = papp->m_paurasystem;

      m_strAppId = "session";

      m_ecursorDefault = ::visual::cursor_arrow;

      m_ecursor = ::visual::cursor_default;

      m_ecursorDefault = ::visual::cursor_arrow;

      m_ecursor = ::visual::cursor_default;

      m_bDrawCursor = false;

      m_pappCurrent = NULL;
      m_psockets = NULL;
      m_paurasession = this;
      m_bMatterFromHttpCache = m_paurasystem->m_bMatterFromHttpCache;

      m_puiLastLButtonDown = NULL;


#ifdef WINDOWS

      if (m_hinstance == NULL)
      {

         m_hinstance = m_pauraapp->m_hinstance;

      }

#endif

      m_psavings = canew(class ::aura::savings(this));

      m_bZipIsDir = true;

      m_iEdge = 0;
      m_bShowPlatform = false;
      m_pappCurrent = NULL;


   }


   void session::construct(::aura::application * papp, int iPhase)
   {

   }


   session::~session_parent
   {


   }


   bool session::is_session()
   {

      return true;

   }


   sp(::aura::application) session::start_application(const char * pszAppId, ::create * pcreate)
   {

      string strApp(pszAppId);

      sp(::aura::application) papp = application_get(strApp, true, true, pcreate->m_spCommandLine->m_pbiasCreate);

      if (papp == NULL)
      {

         return NULL;

      }

      if (pcreate->m_spCommandLine->m_varQuery.has_property("install")
            || pcreate->m_spCommandLine->m_varQuery.has_property("uninstall"))
      {

         Session.appptra().remove(papp);

         return NULL;

      }

      pcreate->m_spCommandLine->m_eventReady.ResetEvent();

      //Session.m_appptra.add(papp);

      m_pappCurrent = papp;

      if (strApp != "session")
      {

         System.merge_accumulated_on_open_file(pcreate);

         papp->post_object(message_system, system_message_command, pcreate);

         while (thread_get_run())
         {

            if (pcreate->m_spCommandLine->m_eventReady.wait(millis(84)).signaled())
               break;

         }

      }

      return papp;

   }


   COLORREF session::get_default_color(uint64_t ui)
   {

      switch (ui)
      {
      case COLOR_3DFACE:
         return ARGB(127, 192, 192, 184);
      case COLOR_WINDOW:
         return ARGB(127, 255, 255, 255);
      case COLOR_3DLIGHT:
         return ARGB(127, 218, 218, 210);
      case COLOR_3DHIGHLIGHT:
         return ARGB(127, 238, 238, 230);
      case COLOR_3DSHADOW:
         return ARGB(127, 138, 138, 130);
      case COLOR_3DDKSHADOW:
         return ARGB(127, 84, 90, 80);
      default:
         break;
      }

      return ARGB(127, 0, 0, 0);

   }






   size session::get_window_minimum_size()
   {

      return size(300, 300);

   }




   bool session::process_init()
   {

      thisstart;

      if (!::aura::application::process_init())
         return false;


      m_puserstrcontext = canew(::aura::str_context(this));

      if (m_puserstrcontext == NULL)
         return false;

      thisok << 2;

      if (m_psockets == NULL)
      {

         m_psockets = new ::sockets::sockets(this);

         m_psockets->construct(this);

         if (!m_psockets->init1())
         {

            thisfail << 4;

            return false;

         }

         thisok << 4;

         if (!m_psockets->init())
         {

            thisfail << 4.1;

            return false;

         }

         thisok << 4.1;

      }

      m_splicensing = canew(class ::fontopus::licensing(this));

      m_pwindowmap = canew(class ::user::window_map(get_app()));


      thisend;

      return true;

   }


   bool session::init1()
   {

      if (!::aura::application::init1())
         return false;





      return true;

   }


   bool session::init2()
   {

      if (!::aura::application::init2())
         return false;

      return true;

   }


   bool session::init_application()
   {

      if (!::aura::application::init_application())
         return false;

      return true;

   }


   bool session::init()
   {

      if (!::aura::application::init())
      {

         return false;

      }

      return true;

   }


   void session::term()
   {

      try
      {

         ::aura::application::term();

      }
      catch (...)
      {

         m_error.set(-1);

      }


      for (auto i : m_mapLibrary)
      {

         for (auto j : i.m_element2)
         {

            j.m_element2.release();

         }

      }

   }


   void session::term_application()
   {

      try
      {

         for (auto & pair : System.m_appmap)
         {

            try
            {

               if (pair.m_element2->m_paurasession == this)
               {

                  pair.m_element2->m_paurasession = NULL;

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


      ::aura::application::term_application();

   }


   application_ptra & session::appptra()
   {

      return m_appptra;

   }

   //// only usable from base.dll and dependants
   //::sockets::sockets & session::sockets()
   //{

   //   _throw(interface_only_exception(get_app()));
   //
   //   return *((::sockets::sockets *) NULL); // only usable from base.dll and dependants
   //
   //}



   //string session::get_cred(::aura::application * papp,const string & strRequestUrlParam,const RECT & rect,string & strUsername,string & strPassword,string strToken,string strTitle,bool bInteractive)
   //{

   //   _throw(interface_only_exception(papp));

   //   return "";

   //}

   ::fontopus::fontopus * session::create_fontopus()
   {

      return canew(::fontopus::fontopus(this));

   }


   ::fontopus::user * session::safe_get_user()
   {

      if (m_pfontopus == NULL)
         return NULL;

      return m_pfontopus->m_puser;

   }





   void session::frame_pre_translate_message(::message::message * pobj)
   {

      UNREFERENCED_PARAMETER(pobj);

   }


   void session::on_request(::create * pcreate)
   {

      TRACE("::aura::session::on_request(sp(::create)) " + demangle(typeid(*this).name()));

      ::output_debug_string("::aura::session::on_request(sp(::create)) " + THIS_FRIENDLY_NAME());

      if (pcreate->m_spCommandLine->m_varQuery["app"].array_get_count() > 1)
      {

         start_application(pcreate->m_spCommandLine->m_varQuery["app"].stra()[0], pcreate);

         return;

      }

      string strApp = pcreate->m_spCommandLine->m_strApp;

      if (strApp == "app/sphere/userstack")
      {

         start_application("app/sphere/userstack", pcreate);

      }

      m_varCurrentViewFile = pcreate->m_spCommandLine->m_varFile;


      //string strApp;

      if ((pcreate->m_spCommandLine->m_varQuery["app"].array_get_count() > 1
            || pcreate->m_spCommandLine->m_varQuery["show_platform"] == 1 || handler()->m_varTopicQuery["show_platform"] == 1)
            && (!(bool)pcreate->m_spCommandLine->m_varQuery.has_property("client_only") && !(bool)handler()->m_varTopicQuery.has_property("client_only"))
            && (!pcreate->m_spCommandLine->m_varQuery.has_property("client_only") && !handler()->m_varTopicQuery.has_property("client_only")))
      {
         m_bShowPlatform = true;
      }

      bool bCreate = true;
      if (pcreate->m_spCommandLine->m_strApp.is_empty())
      {
         if (!pcreate->m_spCommandLine->m_varFile.is_empty())
         {
            if (!open_by_file_extension(pcreate))
            {
               if (m_pappCurrent != NULL)
               {
                  App(m_pappCurrent).request_command(pcreate->m_spCommandLine);
               }
            }
         }
         else if (m_bShowPlatform)
         {
            //create_bergedge(pcreate);
            //if(get_document() != NULL && get_document()->get_typed_view < ::bergedge::view >() != NULL)
            //{
            //   sp(::simple_frame_window) pframe =  (get_document()->get_typed_view < ::bergedge::view >()->GetParentFrame());
            //   if(pframe != NULL)
            //   {
            //      pframe->ShowWindow(SW_SHOW);
            //      pframe->InitialFramePosition();
            //   }
            //}
         }
         if (pcreate->m_spCommandLine->m_varQuery["app"].array_get_count() <= 0)
         {
            bCreate = false;
         }
      }
      if (bCreate)
      {
         if (pcreate->m_spCommandLine->m_strApp == "bergedge")
         {
            if (pcreate->m_spCommandLine->m_varQuery.has_property("session_start"))
            {
               strApp = pcreate->m_spCommandLine->m_varQuery["session_start"];
            }
            else
            {
               strApp = "bergedge";
            }
         }
         else
         {
            strApp = pcreate->m_spCommandLine->m_strApp;
         }


         if (pcreate->m_spCommandLine->m_varQuery["app"].stra().find_first_ci(strApp) < 0)
         {

            pcreate->m_spCommandLine->m_varQuery["app"].stra().insert_at(0, strApp);

         }

         for (int32_t i = 0; i < pcreate->m_spCommandLine->m_varQuery["app"].stra().get_count(); i++)
         {

            strApp = pcreate->m_spCommandLine->m_varQuery["app"].stra()[i];

            if (strApp.is_empty() || strApp == "bergedge")
            {

               return;

            }

            if (strApp == "session")
            {

               continue;

            }

            ::aura::application * papp = application_get(strApp, true, true, pcreate->m_spCommandLine->m_pbiasCreate);

            if (papp == NULL)
            {

               if(System.handler()->m_spcommandline->m_varQuery.has_property("install")
                     || System.handler()->m_spcommandline->m_varQuery.has_property("uninstall"))
               {

                  ::multithreading::post_quit(&System);

               }
               else
               {

                  simple_message_box("Could not create requested application: \"" + strApp + "\"", MB_OK);

                  ::count c = System.handler()->m_spcommandline->m_varQuery["app"].array_get_count();

                  if (c == 1 && System.handler()->m_spcommandline->m_varQuery["app"] == strApp)
                  {

                     ::multithreading::post_quit(&System);

                  }

               }

               return;

            }

            pcreate->m_spCommandLine->m_eventReady.ResetEvent();

            if (strApp != "bergedge")
            {

               if(!papp->on_start_application())
               {

                  TRACE("One or more errors occurred during on_start_application execution.");

               }

               if (System.handler()->m_varTopicQuery.has_property("install"))
               {

                  papp->do_install();

                  System.post_quit();

               }
               else
               {

                  if (!papp->is_system() && !papp->is_session())
                  {

                     System.merge_accumulated_on_open_file(pcreate);

                  }

                  papp->handler()->handle(pcreate);

               }

               m_pappCurrent = papp;

            }

         }

      }

   }


//      m_varCurrentViewFile = pcreate->m_spCommandLine->m_varFile;
//
//      if ((pcreate->m_spCommandLine->m_varQuery["show_platform"] == 1 || handler()->m_varTopicQuery["show_platform"] == 1)
//            && (!(bool)pcreate->m_spCommandLine->m_varQuery.has_property("client_only") && !(bool)handler()->m_varTopicQuery.has_property("client_only"))
//            && (!pcreate->m_spCommandLine->m_varQuery.has_property("client_only") && !handler()->m_varTopicQuery.has_property("client_only")))
//      {
//         m_bShowPlatform = true;
//      }
//
//      bool bCreate = true;
//      if (pcreate->m_spCommandLine->m_strApp.is_empty())
//      {
//         if (!pcreate->m_spCommandLine->m_varFile.is_empty())
//         {
//            if (!open_by_file_extension(pcreate))
//            {
//               if (m_pappCurrent != NULL)
//               {
//                  App(m_pappCurrent).request_command(pcreate->m_spCommandLine);
//               }
//            }
//            bCreate = false;
//         }
//         else if (m_bShowPlatform)
//         {
//            strApp = "bergedge";
//
//
//            bCreate = true;
//
//         }
//
//      }
//      if (bCreate)
//      {
//
//         if (pcreate->m_spCommandLine->m_varQuery["app"].stra().get_count() <= 0)
//         {
//            pcreate->m_spCommandLine->m_varQuery["app"].stra().add(strApp);
//         }
//         else if (pcreate->m_spCommandLine->m_varQuery["app"].stra().get_count() > 1)
//         {
//
//            start_application("app-core/desk", pcreate);
//
//            return;
//
//         }
//
//         for (int32_t i = 0; i < pcreate->m_spCommandLine->m_varQuery["app"].stra().get_count(); i++)
//         {
//
//            string strApp = pcreate->m_spCommandLine->m_varQuery["app"].stra()[i];
//
//            if (strApp.is_empty() || strApp == "session")
//            {
//               if (pcreate->m_spCommandLine->m_strApp == "session")
//               {
//                  if (pcreate->m_spCommandLine->m_varQuery.has_property("session_start"))
//                  {
//                     strApp = pcreate->m_spCommandLine->m_varQuery["session_start"];
//                  }
//                  else
//                  {
//                     strApp = "session";
//                  }
//               }
//               else
//               {
//                  strApp = pcreate->m_spCommandLine->m_strApp;
//               }
//            }
//
//            if (strApp.is_empty() || strApp == "session")
//            {
//               if (pcreate->m_spCommandLine->m_varQuery.has_property("install")
//                     || pcreate->m_spCommandLine->m_varQuery.has_property("uninstall"))
//               {
//                  //System.planesessionptra().remove(this);
//                  return;
//               }
//               return;
//            }
//
//            start_application(strApp, pcreate);
//
//         }
//
//      }

//   }

   bool session::open_by_file_extension(const char * pszPathName, application_bias * pbiasCreate)
   {

      return Application.platform_open_by_file_extension(m_iEdge, pszPathName, pbiasCreate);

   }


   bool session::open_by_file_extension(::create * pcc)
   {

      return Application.platform_open_by_file_extension(m_iEdge, pcc);

   }


   ::aura::application * session::application_get(const char * pszAppId, bool bCreate, bool bSynch, application_bias * pbiasCreate)
   {

      ::aura::application * papp = NULL;

      if (m_paurasession->m_mapApplication.Lookup(string(pszAppId), papp))
      {

         return papp;

      }
      else
      {

         if (!bCreate)
         {

            return NULL;

         }

         papp = NULL;

         try
         {

            papp = create_application(pszAppId, bSynch, pbiasCreate);

         }
         catch (exit_exception * pexception)
         {

            _rethrow(pexception);

         }
         catch (::exception::exception * pexception)
         {

            esp671 esp(pexception);

            // aura::session, axis::session and ::base::session, could get more specialized handling in core::application (core::system)
            // Thank you Mummi (em São Paulo, cuidando do Lucinho e ajudando um monte a Carô 2015-02-03) !! Thank you God!!
            if (!Sys(this).on_run_exception(esp))
            {

               if (!App(this).on_run_exception(esp))
               {

                  papp = NULL;

               }

            }

         }
         catch (...)
         {

            papp = NULL;

         }

         if (papp == NULL)
         {

            return NULL;

         }

         if (&App(papp) == NULL)
         {

            ::aura::del(papp);

            return NULL;

         }

         m_paurasession->m_mapApplication.set_at(string(pszAppId), papp);

         return papp;

      }

   }


   sp(::aura::application) session::get_new_application(::aura::application * pappParent, const char * pszAppId)
   {

      string strAppId(pszAppId);

//#if !defined(METROWIN) && !defined(VSNORD) && !defined(APPLE_IOS)
//
//      if (System.m_pappcore->m_pfnNewApp == NULL && !System.handler()->m_varTopicQuery.has_property("noinstall") && ((!System.handler()->m_varTopicQuery.has_property("install")
//            && !System.handler()->m_varTopicQuery.has_property("uninstall"))
//                                                    ) //         || (papp->is_serviceable() && !papp->is_user_service() && strUserName != "NetworkService"))
//            && strAppId.has_char()
//            && !System.is_application_installed(strAppId, "installed"))
//      {
//
//         _throw(not_installed(get_app(), strAppId));
//
//      }
//
//#endif

      sp(::aura::application) papp;

      if (System.m_pappcore != NULL && System.m_pappcore->m_pfnNewApp != NULL)
      {

         papp = System.m_pappcore->m_pfnNewApp(pappParent);

         if (papp.is_null())
         {

            return NULL;

         }

         papp->m_strLibraryName = strAppId;


      }
//    abandoned because needs the dirty trick of exporting function from executable file
//    (Yes, it requires to export (generally through .def file) the function get_acid_app from the .exe file).
//      else if (strAppId == "acid")
//      {
//
//#ifdef WINDOWS
//
//         PFN_GET_NEW_APP lpfnNewApp = (PFN_GET_NEW_APP) ::GetProcAddress(System.m_hinstance, "get_acid_app");
//
//         if (lpfnNewApp == NULL)
//         {
//
//            return NULL;
//
//         }
//
//         papp = lpfnNewApp(pappParent);
//
//         if (papp.is_null())
//         {
//
//            return NULL;
//
//         }
//
//         papp->m_strLibraryName = "acid";
//
//#endif
//
//      }
      else
      {

         sp(::aura::library) & plibrary = m_mapLibrary[pappParent][pszAppId];

         if (plibrary == NULL)
         {

            if (System.m_pappcore != NULL && System.m_pappcore->m_pfnNewLibrary != NULL)
            {

               plibrary = System.m_pappcore->m_pfnNewLibrary(pappParent);

            }
            else
            {

               ::aura_app * pauraapp = ::aura_app::get(pszAppId);

               if(pauraapp != NULL)
               {

                  if(pauraapp->m_pfnNewLibrary != NULL)
                  {

                     plibrary = pauraapp->m_pfnNewLibrary(pappParent);

                  }
                  else if(pauraapp->m_pfnNewApp != NULL)
                  {

                     papp = pauraapp->m_pfnNewApp(pappParent);

                     if (papp.is_null())
                     {

                        return NULL;

                     }

                     papp->m_strLibraryName = pszAppId;

                  }

               }

               if(papp.is_null() && plibrary == NULL)
               {

                  plibrary = new ::aura::library(pappParent, 0, NULL);

                  string strLibrary = strAppId;

                  strLibrary.replace("/", "_");

                  strLibrary.replace("-", "_");

                  ::output_debug_string("\n\n::aura::session::get_new_application assembled library path " + strLibrary + "\n\n");

                  if (!plibrary->open(strLibrary, false))
                  {

#ifndef METROWIN

                     ::MessageBox(NULL, "Application \"" + strAppId + "\" cannot be created.\n\nThe library \"" + strLibrary + "\" could not be loaded. " + plibrary->m_strMessage, "ca2", MB_ICONERROR);

#endif

                     return NULL;

                  }

                  ::output_debug_string("\n\n::aura::session::get_new_application Found library : " + strLibrary + "\n\n");

                  // error anticipation maybe counter-self-healing
//               if (!plibrary->is_opened())
//               {
//
//                  ::output_debug_string("\n\n::aura::session::get_new_application Failed to load library : " + strLibrary + "\n\n");
//
//                  return NULL;
//
//               }

                  ::output_debug_string("\n\n::aura::session::get_new_application Opened library : " + strLibrary + "\n\n");

                  if (!plibrary->open_ca2_library())
                  {

                     ::output_debug_string("\n\n::aura::session::get_new_application open_ca2_library failed(2) : " + strLibrary + "\n\n");

                     return NULL;

                  }

                  ::output_debug_string("\n\n\n|(5)----");
                  ::output_debug_string("| app : " + strAppId + "\n");
                  ::output_debug_string("|\n");
                  ::output_debug_string("|\n");
                  ::output_debug_string("|----");

               }

            }

         }

         if(papp.is_null())

         {

            ::aura::library & library = *plibrary;


            papp = library.get_new_application(strAppId);

            ::output_debug_string("\n\n\n|(4)----");
            ::output_debug_string("| app : " + strAppId + "(papp=0x" + ::hex::upper_from((uint_ptr)papp.m_p) + ")\n");
            ::output_debug_string("|\n");
            ::output_debug_string("|\n");
            ::output_debug_string("|----");

         }

         if (papp == NULL)
            return NULL;

#ifdef WINDOWSEX

         WCHAR wsz[1024];

         DWORD dwSize = sizeof(wsz) / sizeof(WCHAR);

         GetUserNameW(wsz, &dwSize);

         string strUserName = wsz;

#endif // WINDOWSEX

         ::output_debug_string("\n\n\n|(3)----");
         ::output_debug_string("| app : " + strAppId + "\n");
         ::output_debug_string("|\n");
         ::output_debug_string("|\n");
         ::output_debug_string("|----");



         ::output_debug_string("\n\n\n|(2)----");
         ::output_debug_string("| app : " + strAppId + "\n");
         ::output_debug_string("|\n");
         ::output_debug_string("|\n");
         ::output_debug_string("|----");

#if !defined(VSNORD)

         if (!papp->is_serviceable() || papp->is_user_service())
         {

            System.m_spmutexUserAppData = canew(mutex(m_paurasystem, false, "Local\\ca2.UserAppData"));
            System.m_spmutexSystemAppData = canew(mutex(m_paurasystem, false, "Local\\ca2.SystemAppData"));

         }

#endif

      }


      ::output_debug_string("\n\n\n|(1)----");
      ::output_debug_string("| app : " + strAppId + "\n");
      ::output_debug_string("|\n");
      ::output_debug_string("|\n");
      ::output_debug_string("|----");

      sp(::aura::application) pgenapp = (papp);

      if (pgenapp->m_strAppId.is_empty())
      {

         pgenapp->m_strAppId = pszAppId;

      }

      pgenapp->m_paurasystem = m_paurasystem;

      pgenapp->m_paxissystem = m_paxissystem;

      pgenapp->m_pbasesystem = m_pbasesystem;

      pgenapp->m_pcoresystem = m_pcoresystem;

      pgenapp->m_pcoresession = m_pcoresession;

#ifdef WINDOWS

      pgenapp->m_hinstance = m_hinstance;

#endif

      //pgenapp->construct(NULL);

      return papp;

   }



   void session::request_create(::create * pcreate)
   {

      //      if(m_pbergedgeInterface != NULL)
      {

         if (m_pappCurrent != NULL && m_pappCurrent != this
               && (pcreate->m_spCommandLine->m_strApp.is_empty()
                   || App(m_pappCurrent).m_strAppName == pcreate->m_spCommandLine->m_strApp))
         {
            //if(get_document() != NULL && get_document()->get_typed_view < ::bergedge::pane_view >() != NULL)
            //{
            //   get_document()->get_typed_view < ::bergedge::pane_view >()->set_cur_tab_by_id("app:" + App(m_pappCurrent).m_strAppName);
            //}
            App(m_pappCurrent).request_create(pcreate);
            //if(pcreate->m_spCommandLine->m_varQuery["document"].cast < ::user::document > () == NULL)
            {
               //             goto alt1;
            }

         }
         else
         {
            //alt1:
            if (pcreate->m_spCommandLine->m_varFile.get_type() == var::type_string)
            {
               if (::str::ends_ci(pcreate->m_spCommandLine->m_varFile, ".core"))
               {
                  string strCommand = Application.file().as_string(pcreate->m_spCommandLine->m_varFile);
                  if (::str::begins_eat(strCommand, "ca2prompt\r")
                        || ::str::begins_eat(strCommand, "ca2prompt\n"))
                  {
                     strCommand.trim();
                     handler()->add_fork_uri(strCommand);
                  }
                  return;
               }
               //else if(pcreate->m_spCommandLine->m_strApp.has_char()
               //   && get_document() != NULL
               //   && get_document()->get_typed_view < ::bergedge::pane_view >() != NULL)
               //{
               //   get_document()->get_typed_view < ::bergedge::pane_view >()->set_cur_tab_by_id("app:" + pcreate->m_spCommandLine->m_strApp);
               //   App(m_pappCurrent).request_create(pcreate);
               //}
               else
               {
                  on_request(pcreate);
                  return;
               }
            }
            //else if(pcreate->m_spCommandLine->m_strApp.has_char() &&
            //   get_document() != NULL && get_document()->get_typed_view < ::bergedge::pane_view >() != NULL
            //   && (!pcreate->m_spApplicationBias.is_set() || pcreate->m_spApplicationBias->m_puiParent == NULL))
            //{
            //   //simple_message_box(NULL, "request3", "request3", MB_ICONEXCLAMATION);
            //   get_document()->get_typed_view < ::bergedge::pane_view >()->set_cur_tab_by_id("app:" + pcreate->m_spCommandLine->m_strApp);
            //   App(m_pappCurrent).request_create(pcreate);
            //}
            //else
            {
               //simple_message_box(NULL, "request4", "request4", MB_ICONEXCLAMATION);
               on_request(pcreate);
            }
         }
         return;

      }

//      if (pcreate->m_spCommandLine->m_varFile.get_type() == var::type_string)
//      {
//         if (::str::ends_ci(pcreate->m_spCommandLine->m_varFile, ".core"))
//         {
//            string strCommand = Application.file().as_string(pcreate->m_spCommandLine->m_varFile);
//            if (::str::begins_eat(strCommand, "ca2prompt\r")
//                  || ::str::begins_eat(strCommand, "ca2prompt\n"))
//            {
//               strCommand.trim();
//               handler()->add_fork_uri(strCommand);
//               System.m_bDoNotExitIfNoApplications = true;
//            }
//            return;
//         }
//         else
//         {
//            on_request(pcreate);
//         }
//      }
//      else if (m_pappCurrent != NULL && m_pappCurrent != this
//               && (pcreate->m_spCommandLine->m_strApp.is_empty()
//                   || App(m_pappCurrent).m_strAppName == pcreate->m_spCommandLine->m_strApp))
//      {
//
//
//         /*         if(get_document() != NULL && get_document()->get_typed_view < ::platform::pane_view >() != NULL)
//         {
//         get_document()->get_typed_view < ::platform::pane_view >()->set_cur_tab_by_id("app:" + App(m_pappCurrent).m_strAppName);
//         }*/
//         App(m_pappCurrent).request_create(pcreate);
//      }
//      else
//      {
//         on_request(pcreate);
//      }

   }


   //::visual::cursor * session::get_cursor()
   //{

   //   return NULL;

   //}


   //::visual::cursor * session::get_default_cursor()
   //{

   //   return NULL;

   //}


   //oswindow session::get_capture()
   //{

   //   return NULL;

   //}


   string session::fontopus_get_user_sessid(const string & str)
   {

      return "";

   }


   string session::fontopus_get_cred(::aura::application * papp, const string & strRequestUrl, const RECT & rect, string & strUsername, string & strPassword, string strToken, string strTitle, bool bInteractive, ::user::interactive * pinteractive)
   {

      _throw(not_implemented(papp));

      return "";

   }



   void session::on_user_login(::fontopus::user * puser)
   {



   }


   bool session::is_licensed(const char * pszId, bool bInteractive)
   {

      if (handler()->m_varTopicQuery.has_property("install"))
         return true;

      if (handler()->m_varTopicQuery.has_property("uninstall"))
         return true;

      if (is_null_ref(licensing()))
      {

         return false;

      }

      if (!licensing().has(pszId, bInteractive))
      {

         licensing().m_mapInfo.remove_key(pszId);

         return false;

      }

      return true;

   }

   ::fontopus::user * session::get_user()
   {

      return m_pfontopus->get_user();

   }


   /*::fontopus::user * application::create_user(const string & pszLogin)
   {
   return NULL;
   }*/

   ::fontopus::user * session::create_current_user()
   {
      return NULL;
      /*   string str = get_current_user_login();
      return create_user(str);*/
   }

   /*string application::get_current_user_login()
   {
   return "";
   }*/







   bool session::get_auth(const string & pszForm, string & strUsername, string & strPassword)
   {

      return fontopus()->get_auth(pszForm, strUsername, strPassword);

   }


   void session::defer_initialize_user_presence()
   {


   }

   void session::translate_os_key_message(::user::key * pkey)
   {

   }

   void session::set_cursor(::visual::cursor * pcursor)
   {

      m_ecursor = ::visual::cursor_visual;

      m_pcursor = pcursor;

      if (pcursor != NULL)
      {

         pcursor->set_current(this);

      }
      else
      {

         ::visual::cursor::reset(this);

      }


   }


   void session::set_cursor(::visual::e_cursor ecursor)
   {

      m_ecursor = ecursor;

//      if(ecursor == ::visual::cursor_size_bottom_right
//         || (ecursor == ::visual::cursor_default
//             && m_ecursorDefault == ::visual::cursor_size_bottom_right))
//      {
//
//         output_debug_string("\nbottom_right_cursor   ");
//
//      }
//      else
//      {
//
//         output_debug_string("\nNOT_bottom_right_cursor   ");
//
//      }

      ::visual::cursor * pcursor = get_cursor();

      if (pcursor != NULL)
      {

         pcursor->set_current(this);

      }
      else
      {

         ::visual::cursor::reset(this);

      }

   }


   void session::set_default_cursor(::visual::e_cursor ecursor)
   {

      if (ecursor == ::visual::cursor_default)
      {

         m_ecursorDefault = ::visual::cursor_arrow;

      }
      else
      {

         m_ecursorDefault = ecursor;

      }

   }


   bool session::on_create_frame_window()
   {

      if (m_pcopydesk != NULL)
         return true;

      if (m_pcoresession == NULL)
      {
         return true;

      }

      alloc(m_pcopydesk);

      if (!m_pcopydesk->initialize())
         return false;

      return true;

   }


   ::user::primitive * session::GetFocus()
   {

#ifdef METROWIN

      return System.ui_from_handle(::WinGetFocus());

#else

      return System.ui_from_handle(::GetFocus());

#endif

   }


   ::user::primitive * session::GetActiveWindow()
   {

#ifdef METROWIN

      return System.ui_from_handle(::WinGetActiveWindow());

#else

      return System.ui_from_handle(::GetActiveWindow());

#endif

   }


   //::user::elemental * session::get_keyboard_focus()
   //{

   //   if (m_pauraapp == NULL)
   //   {

   //      return NULL;

   //   }

   //   if (Application.is_session())
   //   {

   //      sp(::user::elemental) puieFocus;

   //      try
   //      {

   //         puieFocus = Session.get_focus_ui();

   //      }
   //      catch (...)
   //      {

   //      }

   //      if (m_pkeyboardfocus != NULL && puieFocus != NULL)
   //      {


   //         if ((bool)oprop("NativeWindowFocus") && puieFocus != m_pkeyboardfocus)
   //         {

   //            return NULL;

   //         }

   //         return m_pkeyboardfocus;

   //      }
   //      else
   //      {

   //         return NULL;

   //      }

   //   }
   //   else if (Application.is_system())
   //   {

   //      return m_pkeyboardfocus;

   //   }
   //   else if (Application.m_pbasesession != NULL)
   //   {

   //      return Session.get_keyboard_focus();

   //   }
   //   else if (Application.m_pbasesystem != NULL)
   //   {

   //      return Session.get_keyboard_focus();

   //   }
   //   else
   //   {

   //      return NULL;

   //   }

   //}



   ::user::elemental * session::get_keyboard_focus()
   {

      if (m_pauraapp == NULL)
         return NULL;


      if (m_pkeyboardfocus == NULL)
         return NULL;

      //sp(::user::elemental) puieFocus;

      //try
      //{

      //   puieFocus = System.ui_.get_focus_ui();

      //}
      //catch(...)
      //{

      //}

      //if(puieFocus == NULL)
      //   return NULL;

      //sp(::user::interaction) puiFocus = m_pkeyboardfocus;

      //if(puiFocus.is_null())
      //   return NULL;

      //if(!puiFocus->is_descendant_of(puieFocus.cast < ::user::interaction >()))
      //   return NULL;


      //if((bool)oprop("NativeWindowFocus") && puieFocus != m_pkeyboardfocus)
      //   return NULL;
      return m_pkeyboardfocus;

   }


   void session::set_keyboard_focus(::user::elemental * pkeyboardfocus)
   {

      if (pkeyboardfocus == NULL)
      {

         pkeyboardfocus = (::user::elemental *) (ulong_ptr) 1;

      }

      if (m_pkeyboardfocus != NULL && m_pkeyboardfocus != pkeyboardfocus && m_pkeyboardfocusRequest != pkeyboardfocus)
      {

         ::user::elemental * pkeyboardfocusOld = m_pkeyboardfocus;

         m_pkeyboardfocusRequest = pkeyboardfocus;

         try
         {

            if (pkeyboardfocusOld != NULL)
            {

               output_debug_string("axis::session::set_keyboard_focus pkeyboardfocusOld->keyboard_focus_OnKillFocus()\n");

               if (!pkeyboardfocusOld->keyboard_focus_OnKillFocus())
               {

                  return;

               }

               sp(::user::interaction) pui = pkeyboardfocusOld;

               if (pui.is_set())
               {

                  pui->send_message(WM_KILLFOCUS);

               }

            }

         }
         catch (...)
         {

         }

      }

      if (pkeyboardfocus == (::user::elemental *) (ulong_ptr) 1)
      {

         pkeyboardfocus = NULL;

      }

      if (pkeyboardfocus != NULL)
      {

         if (!pkeyboardfocus->keyboard_focus_OnSetFocus())
         {

            return;

         }

         if (pkeyboardfocus->get_wnd() != NULL)
         {

            if (!pkeyboardfocus->get_wnd_elemental()->on_keyboard_focus(pkeyboardfocus))
            {

               return;

            }

         }

      }

      m_pkeyboardfocus = pkeyboardfocus;

      on_finally_focus_set(pkeyboardfocus);

   }


   //void session::on_finally_focus_set(::user::elemental * pelementalFocus)
   //{



   //}

   ::user::primitive * session::get_active_ui()
   {

      return NULL;

   }


   ::user::primitive * session::get_focus_ui()
   {

      return NULL;

   }



   void session::on_finally_focus_set(::user::elemental * pelementalFocus)
   {

      if (pelementalFocus == NULL)
         return;

      sp(::user::interaction) puiFocus = pelementalFocus;

      if (puiFocus.is_set())
      {

         if (puiFocus->GetActiveWindow() != puiFocus->get_wnd())
         {

            puiFocus->get_wnd()->SetActiveWindow();

         }

         if (puiFocus->GetFocus() != puiFocus->get_wnd())
         {

            puiFocus->get_wnd()->SetFocus();

         }

         //puiFocus->send_message(WM_SETFOCUS);


#if defined(APPLE_IOS)


         dispatch_async(dispatch_get_main_queue(), ^
         {
            //this runs on the main thread.  Use theData
            sp(::ios::interaction_impl) pimpl = System.m_possystemwindow->m_pui->m_pimpl;

            if (pimpl.is_set())
            {

               pimpl->defer_update_text_view();

            }
         });

#endif



      }


   }

   bool session::on_ui_mouse_message(::user::mouse * pmouse)
   {


      //::axis::session::on_ui_mouse_message(pmouse);

      if (pmouse->m_pt == pmouse->m_ptDesired)
      {

         m_ptCursor = pmouse->m_pt;

      }


      return true;

   }


   ::visual::cursor * session::get_cursor()
   {

      if (m_ecursor == ::visual::cursor_none)
         return NULL;
      else if (m_ecursor == ::visual::cursor_default)
         return System.visual().get_cursor(m_ecursorDefault);
      else
         return System.visual().get_cursor(m_ecursor);

   }


   ::visual::cursor * session::get_default_cursor()
   {

      return NULL;

   }


   void session::get_cursor_pos(LPPOINT lppoint)
   {

      if (m_bSystemSynchronizedCursor)
      {

#ifdef METROWIN

         Windows::Foundation::Point p;

         p = System.m_possystemwindow->m_pwindow->get_cursor_pos();

         m_ptCursor.x = (LONG)p.X;

         m_ptCursor.y = (LONG)p.Y;

#else

         ::GetCursorPos(&m_ptCursor);

#endif

      }

      if (lppoint != NULL)
      {

         *lppoint = m_ptCursor;

      }
   }


   oswindow session::get_capture()
   {

#ifdef METROWIN

      return ::WinGetCapture();

#else

      return ::GetCapture();

#endif

   }

   bool session::ReleaseCapture()
   {

#ifdef METROWIN
      oswindow oswindowCapture = ::WinGetCapture();
#else
      oswindow oswindowCapture = ::GetCapture();
#endif

      if (oswindowCapture == NULL)
         return false;

#ifdef METROWIN
      ::WinReleaseCapture();
#else
      ::ReleaseCapture();
#endif

      m_puiCapture = NULL;

      return true;


   }


   sp(::user::interaction) session::GetCapture()
   {

#ifdef METROWIN
      oswindow oswindowCapture = ::WinGetCapture();
#else
      oswindow oswindowCapture = ::GetCapture();
#endif

      if (oswindowCapture == NULL)
         return NULL;

      sp(::user::interaction) pui = System.ui_from_handle(oswindowCapture);

      if (pui == NULL)
         return NULL;

      return pui->GetCapture();

   }





   //::user::elemental * session::get_keyboard_focus()
   //{

   //   if (m_pauraapp == NULL)
   //      return NULL;


   //   if (m_pkeyboardfocus == NULL)
   //      return NULL;

   //   //sp(::user::elemental) puieFocus;

   //   //try
   //   //{

   //   //   puieFocus = System.ui_.get_focus_ui();

   //   //}
   //   //catch(...)
   //   //{

   //   //}

   //   //if(puieFocus == NULL)
   //   //   return NULL;

   //   //sp(::user::interaction) puiFocus = m_pkeyboardfocus;

   //   //if(puiFocus.is_null())
   //   //   return NULL;

   //   //if(!puiFocus->is_descendant_of(puieFocus.cast < ::user::interaction >()))
   //   //   return NULL;


   //   //if((bool)oprop("NativeWindowFocus") && puieFocus != m_pkeyboardfocus)
   //   //   return NULL;
   //   return m_pkeyboardfocus;

   //}




   ::user::copydesk & session::copydesk()
   {

      return *m_pcopydesk;

   }



   index session::get_main_wkspace(LPRECT lprect)
   {

      if (m_bSystemSynchronizedScreen)
      {

         if (m_iMainWkspace >= 0 && m_iMainWkspace < System.get_monitor_count())
         {

            return System.get_main_wkspace(lprect);

         }
         else
         {

            if (System.get_monitor_rect(m_iMainWkspace, lprect))
            {

               return m_iMainMonitor;

            }
            else
            {

               System.get_wkspace_rect(0, lprect);

               return 0;

            }

         }

      }
      else
      {

         index iMainWkspace = m_iMainWkspace;

         if (iMainWkspace < 0 || iMainWkspace >= m_rectaWkspace.get_count())
         {

            iMainWkspace = 0;

         }

         if (m_rectaWkspace.get_count() <= 0)
         {

            return -1;

         }

         if(lprect != NULL)
         {

            *lprect = m_rectaWkspace[iMainWkspace];

         }

         return iMainWkspace;

      }

   }


   bool session::set_main_wkspace(index iWkspace)
   {

      if (iWkspace == -1)
      {

         m_iMainWkspace = -1;

         return true;

      }
      else if (iWkspace < 0 || iWkspace >= get_wkspace_count())
      {

         return false;

      }
      else
      {

         m_iMainWkspace = iWkspace;

         return true;

      }

   }

   index session::get_main_monitor(LPRECT lprect)
   {

      if (m_bSystemSynchronizedScreen)
      {

         if (m_iMainMonitor < 0 || m_iMainMonitor >= System.get_monitor_count())
         {

            return System.get_main_monitor(lprect);

         }
         else
         {

            if (System.get_monitor_rect(m_iMainMonitor, lprect))
            {

               return m_iMainMonitor;

            }
            else
            {

               System.get_monitor_rect(0, lprect);

               return 0;

            }

         }

      }
      else
      {

         index iMainMonitor = m_iMainMonitor;

         if (iMainMonitor < 0 || iMainMonitor >= m_rectaMonitor.get_count())
         {

            iMainMonitor = 0;

         }

         if (m_rectaMonitor.get_count() <= 0)
         {

            return -1;

         }

         *lprect = m_rectaMonitor[iMainMonitor];

         return iMainMonitor;

      }

   }


   bool session::set_main_monitor(index iMonitor)
   {

      if (iMonitor == -1)
      {

         m_iMainMonitor = -1;

         return true;

      }
      else if (iMonitor < 0 || iMonitor >= get_monitor_count())
      {

         return false;

      }
      else
      {

         m_iMainMonitor = iMonitor;

         return true;

      }

   }


   ::count session::get_wkspace_count()
   {

      if (m_bSystemSynchronizedScreen)
      {

         return System.get_wkspace_count();

      }
      else
      {

         return m_rectaWkspace.get_count();

      }

   }


   ::count session::get_monitor_count()
   {

      if (m_bSystemSynchronizedScreen)
      {

         return System.get_monitor_count();

      }
      else
      {

         return m_rectaMonitor.get_count();

      }

   }


   bool session::get_monitor_rect(index iMonitor, LPRECT lprect)
   {

      if (m_bSystemSynchronizedScreen)
      {

         return System.get_monitor_rect(iMonitor, lprect);

      }
      else
      {

         if (iMonitor < 0 || iMonitor >= m_rectaMonitor.get_count())
         {

            return false;

         }

         *lprect = m_rectaMonitor[iMonitor];

         return true;

      }

   }

   bool session::wkspace_to_monitor(LPRECT lprect, index iMonitor, index iWkspace)
   {

      rect rect(lprect);

      ::rect rectWkspace;

      if (!get_wkspace_rect(iWkspace, rectWkspace))
         return false;

      rect -= rectWkspace.top_left();

      ::rect rectMonitor;

      if (!get_monitor_rect(iMonitor, rectMonitor))
         return false;

      rect += rectMonitor.top_left();

      *lprect = rect;

      return true;

   }


   bool session::wkspace_to_monitor(LPRECT lprect)
   {

      index iWkspace = get_best_wkspace(NULL, rect(lprect));

      return wkspace_to_monitor(lprect, iWkspace, iWkspace);

   }


   bool session::monitor_to_wkspace(LPRECT lprect)
   {

      index iMonitor = get_best_monitor(NULL, rect(lprect));

      return monitor_to_wkspace(lprect, iMonitor, iMonitor);

   }


   bool session::monitor_to_wkspace(LPRECT lprect, index iWkspace, index iMonitor)
   {

      rect rect(lprect);

      ::rect rectMonitor;

      if (!get_monitor_rect(iMonitor, rectMonitor))
         return false;

      rect -= rectMonitor.top_left();

      ::rect rectWkspace;

      if (!get_wkspace_rect(iWkspace, rectWkspace))
         return false;

      rect += rectWkspace.top_left();

      *lprect = rect;

      return true;

   }




   bool session::get_wkspace_rect(index iWkspace, LPRECT lprect)
   {

      if (m_bSystemSynchronizedScreen)
      {

         return System.get_wkspace_rect(iWkspace, lprect);

      }
      else
      {

         if (iWkspace < 0 || iWkspace >= m_rectaWkspace.get_count())
         {

            return false;

         }

         *lprect = m_rectaWkspace[iWkspace];

         return true;

      }

   }

   ::count session::get_desk_monitor_count()
   {

      return get_monitor_count();

   }


   bool session::get_desk_monitor_rect(index iMonitor, LPRECT lprect)
   {

      return get_monitor_rect(iMonitor, lprect);

   }


   void session::get_monitor(rect_array & rectaMonitor, rect_array & rectaIntersect, const RECT & rectParam)
   {

      for (index iMonitor = 0; iMonitor < get_monitor_count(); iMonitor++)
      {

         rect rectIntersect;

         rect rectMonitor;

         if (get_monitor_rect(iMonitor, rectMonitor))
         {

            if (rectIntersect.top_left_null_intersect(&rectParam, rectMonitor))
            {

               if (rectIntersect.area() >= 0)
               {

                  rectaMonitor.add(rectMonitor);

                  rectaIntersect.add(rectIntersect);

               }

            }

         }

      }

   }

   index session::get_zoneing(LPRECT lprect, const RECT & rectParam, ::user::e_appearance eappearance)
   {

      index iMonitor = get_best_wkspace(lprect, rectParam);

      int cx = width(lprect);
      int cy = height(lprect);

      if (cx <= 0 || cy <= 0)
      {

         return -1;

      }

      if (width(rectParam) <= 0 || height(rectParam) <= 0)
      {

         return -1;

      }


      int midcx = cx / 2;
      int midcy = cy / 2;

      if (eappearance == ::user::appearance_top)
      {
         *lprect = rect_dim(0, 0, cx, midcy) + top_left(lprect);
      }
      else if (eappearance == ::user::appearance_left)
      {
         *lprect = rect_dim(0, 0, midcx, cy) + top_left(lprect);
      }
      else if (eappearance == ::user::appearance_right)
      {
         *lprect = rect_dim(midcx, 0, midcx, cy) + top_left(lprect);
      }
      else if (eappearance == ::user::appearance_bottom)
      {
         *lprect = rect_dim(0, midcy, cx, midcy) + top_left(lprect);
      }
      else if (eappearance == ::user::appearance_top_left)
      {
         *lprect = rect_dim(0, 0, midcx, midcy) + top_left(lprect);
      }
      else if (eappearance == ::user::appearance_top_right)
      {
         *lprect = rect_dim(midcx, 0, midcx, midcy) + top_left(lprect);
      }
      else if (eappearance == ::user::appearance_bottom_left)
      {
         *lprect = rect_dim(0, midcy, midcx, midcy) + top_left(lprect);
      }
      else if (eappearance == ::user::appearance_bottom_right)
      {
         *lprect = rect_dim(midcx, midcy, midcx, midcy) + top_left(lprect);
      }
      else
      {
         return -1;
      }

      return iMonitor;

   }

   index session::get_best_zoneing(::user::e_appearance * peappearance, LPRECT lprect, const RECT & rectParam)
   {

      index iMonitor = get_best_monitor(lprect, rectParam);

      int cx = width(lprect);
      int cy = height(lprect);

      if (cx <= 0 || cy <= 0)
      {

         *peappearance = ::user::appearance_zoomed;

         return iMonitor;

      }

      if (width(rectParam) <= 0 || height(rectParam) <= 0)
      {

         *peappearance = ::user::appearance_zoomed;

         return iMonitor;

      }


      int midcx = cx / 2;
      int midcy = cy / 2;

      rect_array recta;
      array < ::user::e_appearance > aa;

      aa.add(::user::appearance_top);
      recta.add_dim(0, 0, cx, midcy);

      aa.add(::user::appearance_left);
      recta.add_dim(0, 0, midcx, cy);

      aa.add(::user::appearance_right);
      recta.add_dim(midcx, 0, midcx, cy);

      aa.add(::user::appearance_bottom);
      recta.add_dim(0, midcy, cx, midcy);

      aa.add(::user::appearance_top_left);
      recta.add_dim(0, 0, midcx, midcy);

      aa.add(::user::appearance_top_right);
      recta.add_dim(midcx, 0, midcx, midcy);

      aa.add(::user::appearance_bottom_left);
      recta.add_dim(0, midcy, midcx, midcy);

      aa.add(::user::appearance_bottom_right);
      recta.add_dim(midcx, midcy, midcx, midcy);

      index iFoundAppearance = recta.max_normal_intersect_area(rectParam, *lprect);

      if (iFoundAppearance < 0)
      {

         *peappearance = ::user::appearance_zoomed;

         return iMonitor;

      }

      if (lprect != NULL)
      {

         *lprect = recta[iFoundAppearance];

      }

      *peappearance = aa[iFoundAppearance];

      return iMonitor;

   }

   index session::get_best_monitor(LPRECT lprect, const RECT & rectParam)
   {

      index iMatchingMonitor = -1;
      int64_t iBestArea = -1;
      rect rectMatch;
      rect r(rectParam);

      if (r.is_null())
      {

         get_cursor_pos((POINT *)&r.left);
         *((POINT*)&r.right) = *((POINT*)&r.left);

      }

      for (index iMonitor = 0; iMonitor < get_monitor_count(); iMonitor++)
      {

         rect rectIntersect;

         rect rectMonitor;

         if (get_monitor_rect(iMonitor, rectMonitor))
         {

            if (rectIntersect.top_left_null_intersect(&r, rectMonitor))
            {

               if (rectIntersect.area() > iBestArea)
               {

                  iMatchingMonitor = iMonitor;

                  iBestArea = rectIntersect.area();

                  rectMatch = rectMonitor;

               }

            }
            else if (rectMonitor.contains(r))
            {

               iMatchingMonitor = iMonitor;

               rectMatch = rectMonitor;

            }

         }

      }

      if (iMatchingMonitor >= 0)
      {

         if (lprect != NULL)
         {

            *lprect = rectMatch;

         }

         return iMatchingMonitor;

      }

      iMatchingMonitor = get_main_monitor(lprect);

      return iMatchingMonitor;

   }


   index session::get_best_wkspace(LPRECT lprect, const RECT & rectParam)
   {

      index iMatchingWkspace = -1;
      int64_t iBestArea = -1;
      rect rectMatch;
      rect r(rectParam);

      if (r.is_null())
      {

         get_cursor_pos((POINT *)&r.left);
         *((POINT*)&r.right) = *((POINT*)&r.left);

      }

      for (index iWkspace = 0; iWkspace < get_wkspace_count(); iWkspace++)
      {

         rect rectIntersect;

         rect rectMonitor;

         if (get_wkspace_rect(iWkspace, rectMonitor))
         {

            if (rectIntersect.top_left_null_intersect(&r, rectMonitor))
            {

               if (rectIntersect.area() > iBestArea)
               {

                  iMatchingWkspace = iWkspace;

                  iBestArea = rectIntersect.area();

                  rectMatch = rectMonitor;

               }

            }
            else if (rectMonitor.contains(r))
            {

               iMatchingWkspace = iWkspace;

               rectMatch = rectMonitor;

            }


         }

      }

      if (iMatchingWkspace >= 0)
      {

         if(lprect != NULL)
         {

            *lprect = rectMatch;

         }

         return iMatchingWkspace;

      }

      iMatchingWkspace = get_main_wkspace(lprect);

      return iMatchingWkspace;

   }


   index session::get_good_iconify(LPRECT lprect, const RECT & rectParam)
   {

      rect rectMonitor;

      index iMatchingMonitor = get_best_monitor(rectMonitor, rectParam);

      lprect->left = rectMonitor.left;
      lprect->top = rectMonitor.top;
      lprect->right = rectMonitor.left;
      lprect->bottom = rectMonitor.top;

      return iMatchingMonitor;

   }





   index session::initial_frame_position(LPRECT lprect, const RECT & rectParam, bool bMove, ::user::interaction * pui)
   {

      rect rectRestore(rectParam);

      rect rectMonitor;

      index iMatchingMonitor = get_best_monitor(rectMonitor, rectParam);

      ::size sizeMin;

      if (pui != NULL)
      {

         sizeMin  = pui->get_window_minimum_size();

      }
      else
      {

         sizeMin = get_window_minimum_size();

      }

      rect rectIntersect;

      if (bMove)
      {

         rect_array rectaMonitor;

         rect_array rectaIntersect;

         get_monitor(rectaMonitor, rectaIntersect, rectParam);

         rectaIntersect.get_box(rectIntersect);

      }
      else
      {

         rectIntersect.intersect(rectMonitor, &rectParam);

      }

      if (rectIntersect.width() < sizeMin.cx || rectIntersect.height() < sizeMin.cy)
      {

         if (rectMonitor.width() / 7 + MAX(sizeMin.cx, rectMonitor.width() * 2 / 5) > rectMonitor.width()
               || rectMonitor.height() / 7 + MAX(sizeMin.cy, rectMonitor.height() * 2 / 5) > rectMonitor.width())
         {

            rectRestore = rectMonitor;

         }
         else
         {

            rectRestore.left = rectMonitor.left + rectMonitor.width() / 7;

            rectRestore.top = rectMonitor.top + rectMonitor.height() / 7;

            rectRestore.right = rectRestore.left + MAX(sizeMin.cx, rectMonitor.width() * 2 / 5);

            rectRestore.bottom = rectRestore.top + MAX(sizeMin.cy, rectMonitor.height() * 2 / 5);

            if (rectRestore.right > rectMonitor.right - rectMonitor.width() / 7)
            {

               rectRestore.offset(rectMonitor.right - rectMonitor.width() / 7 - rectRestore.right, 0);

            }

            if (rectRestore.bottom > rectMonitor.bottom - rectMonitor.height() / 7)
            {

               rectRestore.offset(0, rectMonitor.bottom - rectMonitor.height() / 7 - rectRestore.bottom);

            }

         }

         *lprect = rectRestore;

         return iMatchingMonitor;

      }
      else
      {

         if (!bMove)
         {

            *lprect = rectIntersect;

         }

         return -1;

      }

   }



   index session::get_good_restore(LPRECT lprect, const RECT & rectParam, ::user::interaction * pui)
   {

      return initial_frame_position(lprect, rectParam, false, pui);

   }


   index session::get_good_move(LPRECT lprect, const RECT & rectParam, ::user::interaction * pui)
   {

      index iMatchingMonitor = initial_frame_position(lprect, rectParam, true, pui);

      if (memcmp(lprect, &rectParam, sizeof(RECT)))
      {

         return iMatchingMonitor;

      }
      else
      {

         return -1;

      }


   }




   index session::get_ui_wkspace(::user::interaction * pui)
   {

      if (m_bSystemSynchronizedScreen)
      {

         return System.get_ui_wkspace(pui);

      }
      else
      {

         ::rect rect;

         pui->GetWindowRect(rect);

         return get_best_wkspace(NULL, rect);

      }


   }





   //   void session::get_cursor_pos(LPPOINT lppoint)
   //    {


   //       if(lppoint != NULL)
   //       {

   //          *lppoint = m_ptCursor;

   //       }

   //    }






   bool session::is_key_pressed(::user::e_key ekey)
   {

      if (m_pmapKeyPressed == NULL)
      {

         m_pmapKeyPressed = new ::map < ::user::e_key, ::user::e_key, bool, bool >;

      }

      bool bPressed = false;
      if (ekey == ::user::key_shift)
      {
         m_pmapKeyPressed->Lookup(::user::key_shift, bPressed);
         if (bPressed)
            goto ret;
         m_pmapKeyPressed->Lookup(::user::key_lshift, bPressed);
         if (bPressed)
            goto ret;
         m_pmapKeyPressed->Lookup(::user::key_rshift, bPressed);
         if (bPressed)
            goto ret;
      }
      else if (ekey == ::user::key_control)
      {
         m_pmapKeyPressed->Lookup(::user::key_control, bPressed);
         if (bPressed)
            goto ret;
         m_pmapKeyPressed->Lookup(::user::key_lcontrol, bPressed);
         if (bPressed)
            goto ret;
         m_pmapKeyPressed->Lookup(::user::key_rcontrol, bPressed);
         if (bPressed)
            goto ret;
      }
      else if (ekey == ::user::key_alt)
      {
         m_pmapKeyPressed->Lookup(::user::key_alt, bPressed);
         if (bPressed)
            goto ret;
         m_pmapKeyPressed->Lookup(::user::key_lalt, bPressed);
         if (bPressed)
            goto ret;
         m_pmapKeyPressed->Lookup(::user::key_ralt, bPressed);
         if (bPressed)
            goto ret;
      }
      else
      {

         m_pmapKeyPressed->Lookup(ekey, bPressed);

      }

ret:

      return bPressed;

   }

   void session::set_key_pressed(::user::e_key ekey, bool bPressed)
   {

      if (m_pmapKeyPressed == NULL)
      {

         m_pmapKeyPressed = new ::map < ::user::e_key, ::user::e_key, bool, bool >;

      }

      (*m_pmapKeyPressed)[ekey] = bPressed;

   }

   ::user::theme_sp session::get_user_theme(const char * pszUinteractionLibrary, ::aura::application * papp)
   {

      ::user::theme_sp & p = m_mapTheme[pszUinteractionLibrary];

      if (p.is_null())
      {

         p = instantiate_user_theme(pszUinteractionLibrary, papp);

      }

      if (m_puserstyle == NULL || m_puserstyle == this)
      {

         m_puserstyle = p;

      }

      return p;

   }


   ::user::theme_sp session::instantiate_user_theme(const char * pszUinteractionLibrary, ::aura::application * papp)
   {

      thisstart;

      if (papp == NULL)
      {

         papp = get_app();

      }

      stringa straLibrary;

      {

         string strId(pszUinteractionLibrary);

         if (strId.has_char())
         {

            straLibrary.add(strId);

         }

      }


      {

         string strId(App(papp).preferred_userschema());

         if (strId.has_char())
         {

            straLibrary.add(strId);

         }

      }

      {

         string strConfig = Application.handler()->m_varTopicQuery["wndfrm"];

         if (strConfig.has_char())
         {

            string strLibrary = string("wndfrm_") + strConfig;

            straLibrary.add(strConfig);

         }

      }



      {

         string strWndFrm = App(papp).file().as_string(::dir::system() / "config" / App(papp).m_strAppName / "wndfrm.txt");

         if (strWndFrm.has_char())
         {

            straLibrary.add(strWndFrm);

         }

      }

      {

         string strWndFrm = App(papp).file().as_string(::dir::system() / "config" / ::file::path(App(papp).m_strAppName).folder() / "wndfrm.txt");

         if (strWndFrm.has_char())
         {

            straLibrary.add(strWndFrm);

         }

      }

      {

         string strWndFrm = App(papp).file().as_string(::dir::system() / "config" / ::file::path(App(papp).m_strAppName).name() / "wndfrm.txt");

         if (strWndFrm.has_char())
         {

            straLibrary.add(strWndFrm);

         }

      }


      {

         string strWndFrm = App(papp).file().as_string(::dir::system() / "config/system/wndfrm.txt");

         if (strWndFrm.has_char())
         {

            straLibrary.add(strWndFrm);

         }

      }

      straLibrary.add("wndfrm_metro");

      straLibrary.add("wndfrm_rootkiller");

      straLibrary.add("wndfrm_hyper");

      straLibrary.add("wndfrm_core");

      ::user::theme_sp ptheme;

      for (string strLibrary : straLibrary)
      {

         ::aura::library * plibrary = new ::aura::library(papp, 0, NULL);

         strLibrary.replace("-", "_");

         strLibrary.replace("/", "_");

         if (!::str::begins_ci(strLibrary, "wndfrm_"))
         {

            strLibrary = "wndfrm_" + strLibrary;

         }

         if (!plibrary->open(strLibrary, false))
         {

            thisinfo << "Failed to load " << strLibrary;

            ::aura::del(plibrary);

            continue;

         }

         if (!plibrary->open_ca2_library())
         {

            thisinfo << "Failed to load (2) " << strLibrary;

            ::aura::del(plibrary);

            continue;

         }

         stringa stra;

         plibrary->get_app_list(stra);

         if (stra.get_size() != 1)
         {

            // a wndfrm OSLibrary should have one wndfrm
            thisinfo << "a wndfrm OSLibrary should have one wndfrm " << strLibrary;

            ::aura::del(plibrary);

            continue;

         }

         string strAppId = stra[0];

         if (strAppId.is_empty())
         {

            // trivial validity check
            thisinfo << "app id should not be empty " << strLibrary;

            ::aura::del(plibrary);

            continue;

         }

         ptheme = plibrary->create_object(papp, "user_theme", NULL);

         if (ptheme.is_null())
         {

            thisinfo << "could not create user_style from " << strLibrary;

            ::aura::del(plibrary);

            continue;

         }

         ptheme->m_plibrary = plibrary;

         break;

      }

      if (ptheme.is_null())
      {

         ptheme = canew(::user::theme(this));

      }

      if (ptheme.is_set())
      {

         ptheme->initialize_theme();


      }


      return ptheme;

   }



   void session::defer_instantiate_user_theme(const char * pszUiInteractionLibrary)
   {

      if (m_ptheme.is_null())
      {

         m_ptheme = get_user_theme(pszUiInteractionLibrary);

         if (m_ptheme.is_null())
         {

            thisfail << 1;

            _throw(resource_exception(this));

         }

      }

   }


   void session::userstyle(::user::style_context * pcontext)
   {

      pcontext->m_pstyle = m_ptheme;

   }


   class ::user::window_map & session::window_map()
   {

      return *m_pwindowmap;

   }


   void session::_001OnDefaultTabPaneDrawTitle(::user::tab_pane & pane, ::user::tab * ptab, ::draw2d::graphics * pgraphics, LPCRECT lpcrect, ::draw2d::brush_sp & brushText)
   {

      _throw(interface_only_exception(this));

   }

} // namespace aura


