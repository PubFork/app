#include "framework.h"


#ifdef WINDOWSEX
CLASS_DECL_AURA void attach_thread_input_to_main_thread(bool bAttach);
#endif

CLASS_DECL_AURA mutex * get_cred_mutex();


namespace userex
{


   userex::userex(::aura::application * papp):
      object(papp),
      ::aura::department(papp)
   {

      m_pshell  = NULL;
      m_ptemplateForm = NULL;
      m_ptemplateChildForm = NULL;
      m_ptemplatePlaceHolder = NULL;


   }


   userex::~userex()
   {

      //if (m_ptemplateForm != NULL)
      //{
      //   m_ptemplateForm->close_all_documents(false);

      //   ::aura::del(m_ptemplateForm);

      //}

      //if (m_ptemplateChildForm != NULL)
      //{

      //   m_ptemplateChildForm->close_all_documents(false);

      //   ::aura::del(m_ptemplateChildForm);

      //}

      //if (m_ptemplatePlaceHolder != NULL)
      //{

      //   m_ptemplatePlaceHolder->close_all_documents(false);

      //   ::aura::del(m_ptemplatePlaceHolder);

      //}

      for(auto & pair : m_mapimpactsystem)
      {

         auto & psystem = pair.element2();

         if (psystem != NULL)
         {

            psystem->close_all_documents(false);

            psystem->release();

         }

      }

   }


   bool userex::init1()
   {

      System.factory().creatable_small < keyboard_layout >();


      System.factory().creatable_small < top_edit_view >();
      System.factory().creatable_small < top_toggle_view >();
      System.factory().creatable_small < top_view >();

      System.factory().creatable_small < ::user::tab_view >();



      if(!create_user_shell())
      {

         return false;

      }



      if (!::aura::department::init1())
      {

         return false;

      }

      return true;

   }


   bool userex::init()
   {

      if (!::aura::department::init())
      {

         return false;

      }

      if(!m_typeDefaultMeshData)
      {

         m_typeDefaultMeshData = System.type_info < ::simple_mesh_data >();

      }

      if(!m_typeDefaultListData)
      {

         m_typeDefaultListData = System.type_info < ::simple_list_data >();

      }

      if(!m_typeDefaultListHeader)
      {

         m_typeDefaultListHeader = System.type_info < ::simple_list_header_control >();

      }

      System.factory().cloneable_small < int_biunique >();
      System.factory().creatable_small < ::user::plain_edit >();
      System.factory().cloneable_small < xfplayer_view_line >();
      System.factory().creatable_small < ::user::place_holder >();
      System.factory().creatable_small < ::user::combo_box >();
      System.factory().creatable_small < ::user::check_box >();
      System.factory().creatable_small < ::user::place_holder_container >();

      System.factory().creatable_small < ::fontopus::view >();

      System.factory().cloneable_small < ::user::split_layout >();
      System.factory().cloneable_small < ::user::split_bar >();
      System.factory().cloneable_small < split_view::Pane >();
      System.factory().cloneable_small < simple_frame_window >();
      System.factory().cloneable_small < prodevian_translucent_simple_frame_window >();
      System.factory().creatable_small < ::user::button >();
      System.factory().creatable_small < ::user::menu_list_view >();
      System.factory().cloneable_small < simple_child_frame >();
      System.factory().cloneable_small < simple_main_frame >();
      System.factory().cloneable_small < ::user::document >();
      System.factory().cloneable_small < ::user::split_view >();
      System.factory().cloneable_small < split_view >();

      System.factory().cloneable_small < ::simple_mesh_data >();
      System.factory().cloneable_small < ::simple_list_data >();
      System.factory().cloneable_small < ::simple_list_header_control >();

      System.factory().creatable_small < ::user::tree >();


      System.factory().creatable_small < simple_list_view >();
      System.factory().creatable_small < ::user::document >();
      System.factory().creatable_small < simple_printer_list_view >();
      System.factory().creatable_small < ::user::combo_list >();
      System.factory().creatable_small < ::user::plain_edit >();

      System.factory().creatable_small < ::user::menu_item >(System.type_info < ::user::menu_item >());
      System.factory().creatable_small < ::user::menu >(System.type_info < ::user::menu >());

      System.factory().creatable_small < ::user::button >();

      System.factory().creatable_small < ::user::show < ::user::plain_edit > >();
      System.factory().creatable_small < ::user::show < ::user::tree > >();
      System.factory().creatable_small < ::user::show < ::user::list > >();

      System.factory().creatable_small < menu_document >();
      System.factory().creatable_small < menu_frame >();
      System.factory().creatable_small < menu_view >();

      System.factory().creatable_small < html_document >();
      System.factory().creatable_small < html_view >();
      System.factory().creatable_small < ::html::data::image >();
      System.factory().creatable_small < ::html::data >();

      Application.set_form_impact_system(

      canew(::user::multiple_document_template(
            get_app(),
            "system/form",
            System.type_info < html_document >(),
            System.get_simple_frame_window_type_info(),
            System.type_info < html_view >())),

      canew(::user::multiple_document_template(
            get_app(),
            "system/form",
            System.type_info < html_document >(),
            System.get_simple_child_frame_type_info(),
            System.type_info < html_view >())),

      canew(::user::multiple_document_template(
            get_app(),
            "system/form",
            System.type_info < ::user::document >(),
            System.get_simple_frame_window_type_info(),
            System.type_info < ::user::place_holder >()))

      );

      TRACE("::userex::application::initialize");

      xml::document docUser(get_app());
      string strUser = Application.file().as_string(System.dir().appdata()/"langstyle_settings.xml");
      string strLangUser;
      string strStyleUser;
      if(docUser.load(strUser))
      {
         if(docUser.get_child("lang") != NULL)
         {
            strLangUser = docUser.get_child("lang")->get_value();
         }
         if(docUser.get_child("style") != NULL)
         {
            strStyleUser = docUser.get_child("style")->get_value();
         }
      }

      if(strLangUser.has_char())
         Session.set_locale(strLangUser,::action::source::database());
      if(strStyleUser.has_char())
         Session.set_schema(strStyleUser,::action::source::database());

      string strLicense = Application.get_license_id();


      var & varTopicQuey = System.handler()->m_varTopicQuery;

      bool bHasInstall = varTopicQuey.has_property("install");

      bool bHasUninstall = varTopicQuey.has_property("uninstall");

      if(!(bHasInstall || bHasUninstall)
            && Application.m_bLicense
            && strLicense.has_char())
      {

         if(&ApplicationUser == NULL)
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

         if(!Session.is_licensed(strLicense))
         {

            Session.licensing().m_mapInfo.remove_key(strLicense);

            if(iRetry > 0)
               goto retry_license;

            return false;

         }

      }

      set_data_server(&Application.dataserver());


      System.factory().creatable_small < pane_tab_view >();
      System.factory().creatable_small < form_frame >();
      System.factory().creatable_small < form_child_frame >();

      System.factory().creatable_small < simple_toolbar >();
      System.factory().creatable_small < ::user::orto_button >();

      if (!BaseMenuCentralContainer::initialize_central_container(get_app()))
      {

         return false;

      }

      if (!::aura::department::init())
      {

         return false;

      }

      return true;

   }


   bool userex::init2()
   {

      if (!::aura::department::init2())
      {

         return false;

      }

      return true;

   }


   void userex::term()
   {

      try
      {

         ::aura::department::term();

      }
      catch(...)
      {

      }

      try
      {

         if(!BaseMenuCentralContainer::finalize_central_container())
         {

            TRACE("Errors occurred while finalizing BaseMenuCentralContainer");

         }

      }
      catch(...)
      {

      }

   }


   ::user::shell::shell * userex::shell()
   {

      return m_pshell;

   }


   string userex::message_box(const char * pszMatter,property_set & propertyset)
   {

      class ::userex::message_box box(get_app());

      box.show(pszMatter,&propertyset);

      return box.m_strResponse;

   }


   int32_t userex::simple_message_box(::user::primitive * pwndOwner,const char * pszMessage,UINT fuStyle)
   {

      int iRet = ::simple_message_box(pwndOwner->get_safe_handle(), pszMessage, "ca2", fuStyle);

      return iRet;

//      class ::userex::message_box box(get_app());
//
//      property_set propertyset;
//
//      propertyset["message"] = pszMessage;
//
//      propertyset["application_name"] = pwndOwner == NULL ? Application.m_strAppName : App(pwndOwner->get_app()).m_strAppName;
//
//      string strMatter;
//
//      if(fuStyle & MB_YESNOCANCEL)
//      {
//
//         strMatter = "system\\user\\simple_message_box\\yesnocancel.xhtml";
//
//      }
//      else
//      {
//
//         strMatter = "system\\user\\simple_message_box\\ok.xhtml";
//
//      }
//
//      try
//      {
//
//         if(!box.show(strMatter,&propertyset))
//         {
//
//            string strMessage = pszMessage;
//
//            strMessage.replace("<br>","\r\n");
//
//            return ::simple_message_box(pwndOwner->get_safe_handle(),strMessage,Application.m_strAppName,fuStyle);
//
//         }
//
//      }
//      catch(...)
//      {
//
//         string strMessage = pszMessage;
//
//         strMessage.replace("<br>","\r\n");
//
//         return ::simple_message_box(pwndOwner == NULL ? NULL : pwndOwner->get_handle(),strMessage,Application.m_strAppName,fuStyle);
//
//      }
//
//      if(box.m_strResponse == "ok")
//      {
//
//         return IDOK;
//
//      }
//      else if(box.m_strResponse == "yes")
//      {
//
//         return IDYES;
//
//      }
//      else if(box.m_strResponse == "no")
//      {
//
//         return IDNO;
//
//      }
//      else if(box.m_strResponse == "cancel")
//      {
//
//         return IDCANCEL;
//
//      }
//
//      if(fuStyle & MB_YESNOCANCEL)
//      {
//
//         return IDCANCEL;
//
//      }
//      else
//      {
//
//         return 0;
//
//      }

   }


   int32_t userex::simple_message_box_timeout(::user::primitive * puiOwner,const char * pszMessage,::duration durationTimeout,UINT fuStyle, ::aura::application * papp)
   {

      UNREFERENCED_PARAMETER(puiOwner);

      class ::userex::message_box box(papp == NULL ? get_app() : papp);

      property_set propertyset;

      propertyset["message"] = pszMessage;

      box.m_dwDelay = (DWORD) durationTimeout.get_total_milliseconds();

      string strMatter;

      if(fuStyle & MB_YESNOCANCEL)
      {

         strMatter = "system\\user\\simple_message_box_timeout\\yesnocancel.xhtml";

      }
      else
      {

         strMatter = "system\\user\\simple_message_box_timeout\\ok.xhtml";

      }

      if (!box.show(strMatter, &propertyset))
      {

         _throw(resource_exception(get_app()));

      }

      if(box.m_strResponse == "ok")
      {

         return IDOK;

      }
      else if(box.m_strResponse == "yes")
      {

         return IDYES;

      }
      else if(box.m_strResponse == "no")
      {

         return IDNO;

      }
      else if(box.m_strResponse == "cancel")
      {

         return IDCANCEL;

      }

      if(fuStyle & MB_YESNOCANCEL)
      {

         return IDCANCEL;

      }
      else
      {

         return 0;

      }

   }


   int32_t userex::track_popup_menu(const char * pszMatter,point pt,sp(::user::interaction) puie)
   {

      UNREFERENCED_PARAMETER(pszMatter);
      UNREFERENCED_PARAMETER(pt);
      UNREFERENCED_PARAMETER(puie);

      return 1;

   }


   bool userex::get_fs_size(string & strSize,const char * pszPath,bool & bPending)
   {

      int64_t i64Size;

      if(!get_fs_size(i64Size,pszPath,bPending))
      {

         strSize.Empty();

         return false;

      }

      if(i64Size > 1024 * 1024 * 1024)
      {

         double d = (double)i64Size / (1024.0 * 1024.0 * 1024.0);

         strSize.Format("%0.2f GB",d);

      }
      else if(i64Size > 1024 * 1024)
      {

         double d = (double)i64Size / (1024.0 * 1024.0);

         strSize.Format("%0.1f MB",d);

      }
      else if(i64Size > 1024)
      {

         double d = (double)i64Size / (1024.0);

         strSize.Format("%0.0f KB",d);

      }
      else if(i64Size > 0)
      {

         strSize.Format("1 KB");

      }
      else
      {

         strSize.Format("0 KB");

      }

      if(bPending)
      {

         strSize = "~" + strSize;

      }

      return true;

   }


   bool userex::get_fs_size(int64_t & i64Size,const char * pszPath,bool & bPending)
   {

      db_server * pcentral = dynamic_cast <db_server *> (&System.m_psimpledb->db());

      if (pcentral == NULL)
      {

         return false;

      }

      return pcentral->m_pfilesystemsizeset->get_cache_fs_size(i64Size,pszPath,bPending);

   }


   void userex::data_on_after_change(::message::message * pobj)
   {

      SCAST_PTR(::database::change_event,pchange,pobj);

      if(pchange->m_datakey == "ca2.savings")
      {

         pchange->data_get(Session.savings().m_eresourceflagsShouldSave);

      }

   }



   //void userex::SendMessageToWindows(UINT message,WPARAM wparam,LPARAM lparam)
   //{

   //   sp(::user::interaction) pwnd;

   //   while(Application.get_frame(pwnd))
   //   {

   //      if(pwnd != NULL && pwnd->IsWindow())
   //      {

   //         pwnd->send_message(message,wparam,lparam);

   //         pwnd->send_message_to_descendants(message,wparam,lparam);

   //      }

   //   }

   //}


   void  userex::AddToRecentFileList(const char * lpszPathName)
   {

      UNREFERENCED_PARAMETER(lpszPathName);

   }




   void userex::_001OnFileNew()
   {

      ASSERT(Application.document_manager() != NULL);

      if(Application.document_manager() == NULL)
      {

         return;

      }

      Application.document_manager()->_001OnFileNew();

   }


   void userex::term_instance()
   {

   }


   sp(::user::document) userex::create_form(::aura::application * papp, sp(::user::form) pview, ::user::form_callback * pcallback, sp(::user::interaction) pwndParent, var var)
   {

      if (m_ptemplateForm == NULL)
      {

         return NULL;

      }

      sp(::create) createcontext(papp->allocer());

      createcontext->m_bMakeVisible = false;

      createcontext->m_puiParent = pwndParent;

      createcontext->m_puiAlloc = pview;

      if (var.get_file_path().has_char())
      {

         createcontext->m_spCommandLine.alloc(allocer());

         createcontext->m_spCommandLine->m_varFile = var.get_file_path();

      }

      if (var.get_type() == var::type_propset && var.has_property("hold") && !(bool)var["hold"])
      {

         createcontext->m_bHold = false;

      }

      m_ptemplateForm->request_create(createcontext);

      sp(::user::document) pdoc = ::user::get_document(createcontext);

      if (pdoc.is_null())
      {

         return NULL;

      }

      sp(::user::form_window) pform = pdoc->get_typed_view < ::user::form_window >();

      if (pform.is_set())
      {

         pform->m_pcallback = pcallback;

      }

      return pdoc;

   }


   sp(::user::document) userex::create_form(::aura::application * pauraapp, ::user::form_callback * pcallback,sp(::user::interaction) pwndParent,var var)
   {

      if (m_ptemplateForm == NULL)
      {

         return NULL;

      }

      ::aura::application * papp = pauraapp;

      if (papp == NULL)
      {

         if (pwndParent.is_set())
         {

            papp = pwndParent->get_app();

         }
         else if (pcallback != NULL)
         {

            papp = pcallback->get_app();

         }
         else
         {

            papp = get_app();

         }

      }

      sp(::create) createcontext(papp->allocer());

      createcontext->m_bMakeVisible                   = false;

      createcontext->m_puiParent                      = pwndParent;

      if (var.get_file_path().has_char())
      {

         createcontext->m_spCommandLine.alloc(allocer());

         createcontext->m_spCommandLine->m_varFile = var.get_file_path();

      }

      if(var.get_type() == var::type_propset && var.has_property("hold") && !(bool)var["hold"])
      {

         createcontext->m_bHold                       = false;

      }

      m_ptemplateForm->request_create(createcontext);

      sp(::user::document) pdoc = ::user::get_document(createcontext);

      if (pdoc.is_null())
      {

         return NULL;

      }

      sp(::user::form_window) pform = pdoc->get_typed_view < ::user::form_window >();

      if(pform.is_set())
      {

         pform->m_pcallback = pcallback;

      }

      return pdoc;

   }


   sp(::user::document) userex::create_child_form(::aura::application * pauraapp, sp(::user::form) pview,::user::form_callback * pcallback,sp(::user::interaction) pwndParent,var var)
   {

      if (m_ptemplateChildForm == NULL)
      {

         return NULL;

      }

      ::aura::application * papp = pauraapp;

      if (papp == NULL)
      {

         if (pwndParent.is_set())
         {

            papp = pwndParent->get_app();

         }
         else if (pcallback != NULL)
         {

            papp = pcallback->get_app();

         }
         else
         {

            papp = get_app();

         }

      }


      sp(::create) createcontext(papp->allocer());

      createcontext->m_bMakeVisible                   = false;

      createcontext->m_puiParent                      = pwndParent;

      createcontext->m_puiAlloc                       = pview;

      if (var.get_file_path().has_char())
      {

         createcontext->m_spCommandLine.alloc(allocer());

         createcontext->m_spCommandLine->m_varFile = var.get_file_path();

      }

      if(var.get_type() == var::type_propset && var.has_property("hold") && !(bool)var["hold"])
      {

         createcontext->m_bHold                       = false;

      }

      m_ptemplateChildForm->request_create(createcontext);

      sp(::user::document) pdoc = ::user::get_document(createcontext);

      if (pdoc.is_null())
      {

         return NULL;

      }

      sp(::user::form_window) pform = pdoc->get_typed_view < ::user::form_window >();

      if(pform.is_set())
      {

         pform->m_pcallback = pcallback;

      }

      return pdoc;

   }


   sp(::user::document) userex::create_child_form(::aura::application * pauraapp, ::user::form_callback * pcallback,sp(::user::interaction) pwndParent,var var)
   {

      if (m_ptemplateChildForm == NULL)
      {

         return NULL;

      }

      ::aura::application * papp = pauraapp;

      if (papp == NULL)
      {

         if (pwndParent.is_set())
         {

            papp = pwndParent->get_app();

         }
         else if (pcallback != NULL)
         {

            papp = pcallback->get_app();

         }
         else
         {

            papp = get_app();

         }

      }

      sp(::create) createcontext(papp->allocer());

      createcontext->m_bMakeVisible                   = true;

      createcontext->m_puiParent                      = pwndParent;

      if (var.get_file_path().has_char())
      {

         createcontext->m_spCommandLine.alloc(allocer());

         createcontext->m_spCommandLine->m_varFile = var.get_file_path();

      }

      m_ptemplateChildForm->request_create(createcontext);

      sp(::user::document) pdoc = ::user::get_document(createcontext);

      if (pdoc.is_null())
      {

         return NULL;

      }

      sp(::user::form_window) pform = pdoc->get_typed_view < ::user::form_window >();

      if(pform.is_set())
      {

         pform->m_pcallback = pcallback;

      }

      return pdoc;

   }


   sp(::user::document) userex::create_child_form(::aura::application * papp, sp(::type) pt, sp(::user::interaction) pwndParent, var var)
   {

      if (pt == NULL)
      {

         return NULL;

      }

      ::user::impact_system * psystem = m_mapTemplate[pt];

      if (psystem == NULL)
      {

         psystem = canew(::user::multiple_document_template(
                         papp,
                         m_ptemplateChildForm->m_strMatter,
                         m_ptemplateChildForm->m_typeinfoDocument,
                         m_ptemplateChildForm->m_typeinfoFrame,
                         pt));

         m_mapTemplate[pt] = psystem;

         App(papp).document_manager()->add_document_template(psystem);

      }

      if (papp == NULL)
      {

         if (pwndParent.is_set())
         {

            papp = pwndParent->get_app();

         }
         else
         {

            papp = get_app();

         }

      }

      sp(::create) createcontext(papp->allocer());

      createcontext->m_bMakeVisible = false;

      createcontext->m_puiParent = pwndParent;

      if (var.get_file_path().has_char())
      {

         createcontext->m_spCommandLine.alloc(allocer());

         createcontext->m_spCommandLine->m_varFile = var.get_file_path();

      }

      psystem->request_create(createcontext);

      sp(::user::document) pdoc = ::user::get_document(createcontext);

      if (pdoc.is_null())
      {

         return NULL;

      }

      sp(::user::form_window) pform = pdoc->get_typed_view < ::user::form_window >();

      return pdoc;

   }


   ::user::document * userex::hold(sp(::user::interaction) pui)
   {

      sp(::create) createcontext(pui->allocer());

      createcontext->m_bMakeVisible    = false;

      createcontext->m_bHold           = false;

      m_ptemplatePlaceHolder->request_create(createcontext);

      sp(::user::document) pdoc = ::user::get_document(createcontext);

      sp(::user::place_holder) pholder = pdoc->get_typed_view < ::user::place_holder  >();

      pholder->hold(pui);

      return pdoc;

   }


   void userex::route_command_message(::user::command * pcommand)
   {

      UNREFERENCED_PARAMETER(pcommand);

   }


   ::user::list_header * userex::default_create_list_header(::aura::application * papp)
   {

      return App(papp).alloc<::user::list_header >(default_type_list_header());

   }


   ::user::mesh_data * userex::default_create_mesh_data(::aura::application * papp)
   {

      return App(papp).alloc<::user::list_data >(default_type_list_data());

   }


   ::user::list_data * userex::default_create_list_data(::aura::application * papp)
   {

      return App(papp).alloc<::user::list_data >(default_type_list_data());

   }


   ::type * userex::default_type_mesh_data()
   {

      return m_typeDefaultMeshData;

   }


   ::type * userex::default_type_list_header()
   {

      return m_typeDefaultListHeader;

   }


   ::type * userex::default_type_list_data()
   {

      return m_typeDefaultListData;

   }


   string userex::get_wallpaper(index iScreen)
   {

      return impl_get_wallpaper(iScreen);

   }


   bool userex::set_wallpaper(index iScreen, string strWallpaper)
   {

      return impl_set_wallpaper(iScreen, strWallpaper);

   }


   stringa userex::get_wallpaper()
   {

      ::count iMonitorCount = System.get_monitor_count();

      stringa stra;

      for(index iScreen = 0; iScreen < iMonitorCount; iScreen++)
      {

         stra.add(get_wallpaper(iScreen));

      }

      bool bAllEqual = true;

      for(index iScreen = 1; iScreen < iMonitorCount; iScreen++)
      {

         if(stra[iScreen] != stra[iScreen - 1])
         {

            bAllEqual = false;

         }

      }

      if(bAllEqual && stra.get_count() >= 2)
      {

         stra.set_size(1);

      }

      return stra;

   }


   void userex::set_wallpaper(const stringa & straWallpaper)
   {

      if(straWallpaper.is_empty())
      {

         return;

      }

      ::count iMonitorCount = System.get_monitor_count();

#ifdef LINUX

      if(iMonitorCount > 0)
      {

         set_wallpaper(0, straWallpaper[0]);

      }

#else

      for(index iScreen = 0; iScreen < iMonitorCount; iScreen++)
      {

         string strWallpaper = iScreen % straWallpaper;

         set_wallpaper(iScreen, strWallpaper);

      }

#endif

   }


#ifdef WINDOWSEX

   bool userex::impl_set_wallpaper(index iScreen, string strLocalImagePath)
   {

      return SystemParametersInfoW(SPI_SETDESKWALLPAPER, 0, wstring(strLocalImagePath), SPIF_UPDATEINIFILE | SPIF_SENDCHANGE) != FALSE;

   }


   string userex::impl_get_wallpaper(index iScreen)
   {

      hwstring wsz(MAX_PATH * 8);

      if(!SystemParametersInfoW(SPI_GETDESKWALLPAPER, wsz.count(), wsz, 0))
      {

         return "";

      }

      return wsz;

   }


#elif defined(LINUX)


   bool userex::impl_set_wallpaper(index iScreen, string strLocalImagePath)
   {

      // wall-changer sourceforge.net contribution

      switch(::user::get_edesktop())
      {

      case ::user::desktop_gnome:
      case ::user::desktop_ubuntu_gnome:
      case ::user::desktop_unity_gnome:

         return ::user::gsettings_set("org.gnome.desktop.background", "picture-uri", "file://" + strLocalImagePath);

      case ::user::desktop_mate:

         return ::user::gsettings_set("org.mate.background", "picture-filename", strLocalImagePath);

      case ::user::desktop_lxde:

         call_async("pcmanfm", "-w " + strLocalImagePath, NULL, SW_HIDE, false);

         break;

      case ::user::desktop_xfce:
      {
         //        Q_FOREACH(QString entry, Global::getOutputOfCommand("xfconf-query", QStringList() << "-c" << "xfce4-desktop" << "-p" << "/backdrop" << "-l").split("\n")){
         //          if(entry.contains("image-path") || entry.contains("last-image")){
         //            QProcess::startDetached("xfconf-query", QStringList() << "-c" << "xfce4-desktop" << "-p" << entry << "-s" << image);
         //      }
         //}

      }

      //break;

      default:

         output_debug_string("Failed to change wallpaper. If your Desktop Environment is not listed at \"Preferences->Integration-> Current Desktop Environment\", then it is not supported.");
         return false;

      }

      return true;

   }


   string userex::impl_get_wallpaper(index iScreen)
   {

      char sz[MAX_PATH * 8];

      ZERO(sz);

      // wall-changer sourceforge.net contribution

      switch(::user::get_edesktop())
      {

      case ::user::desktop_gnome:
      case ::user::desktop_ubuntu_gnome:
      case ::user::desktop_unity_gnome:

         ::user::gsettings_get(sz, sizeof(sz), "org.gnome.desktop.background", "picture-uri");

         break;

      case ::user::desktop_mate:

         ::user::gsettings_get(sz, sizeof(sz), "org.mate.background", "picture-filename");

         break;

      case ::user::desktop_lxde:

         //call_async("pcmanfm", "-w " + strLocalImagePath, NULL, SW_HIDE, false);

         break;

      case ::user::desktop_xfce:
      {
         //        Q_FOREACH(QString entry, Global::getOutputOfCommand("xfconf-query", QStringList() << "-c" << "xfce4-desktop" << "-p" << "/backdrop" << "-l").split("\n")){
         //          if(entry.contains("image-path") || entry.contains("last-image")){
         //            QProcess::startDetached("xfconf-query", QStringList() << "-c" << "xfce4-desktop" << "-p" << entry << "-s" << image);
         //      }
         //}

      }

      //break;

      default:

         output_debug_string("Failed to get wallpaper setting. If your Desktop Environment is not listed at \"Preferences->Integration-> Current Desktop Environment\", then it is not supported.");
         //return "";

      }

      string str(sz);

      ::str::begins_eat_ci(str, "file://");

      return str;

   }


#elif defined(APPLE_IOS)

   bool userex::impl_set_wallpaper(index iScreen, string strLocalImagePath)
   {

      // Someday we will be together...
      // What do you mean...
      // Cold Water...

      return false;

   }

   string userex::impl_get_wallpaper(index iScreen)
   {

      return string();

   }

#elif defined(ANDROID)

   bool userex::impl_set_wallpaper(index iScreen, string strLocalImagePath)
   {

      return ::aura::system::g_p->android_set_user_wallpaper(strLocalImagePath);

   }

   string userex::impl_get_wallpaper(index iScreen)
   {

      string strLocalImagePath;

      ::aura::system::g_p->android_get_user_wallpaper(strLocalImagePath);

      return strLocalImagePath;

   }


#elif defined(METROWIN)

   bool userex::impl_set_wallpaper(index iScreen, string strLocalImagePath)
   {

      // Someday we will be together...
      // What do you mean...
      // Cold Water...

      return false;

   }

   string userex::impl_get_wallpaper(index iScreen)
   {

      return string();

   }

#else

   bool userex::impl_set_wallpaper(index iScreen, string strLocalImagePath)
   {

      return macos_set_user_wallpaper((int) iScreen, strLocalImagePath);

   }

   string userex::impl_get_wallpaper(index iScreen)
   {

      return macos_get_user_wallpaper((int) iScreen);

   }

#endif



} //namespace userex












namespace core
{


   bool application::initialize_userex()
   {

      if (is_system())
      {

         System.factory().creatable_small < ::userex::keyboard_layout >();

      }

      return true;

   }


   ::userex::userex * application::create_userex()
   {

      return canew(::userex::userex(this));

   }

   int32_t application::simple_message_box(::user::primitive * puiOwner, const char * pszMessage, UINT fuStyle)
   {

      ::output_debug_string("\n\napp_simple_message_box: " + string(pszMessage) + "\n\n");

      if (&Session == NULL || Session.userex() == NULL)
         return ::base::application::simple_message_box(puiOwner, pszMessage, fuStyle);

      return Session.userex()->simple_message_box(puiOwner, pszMessage, fuStyle);

   }


   int32_t application::simple_message_box_timeout(::user::primitive * pwndOwner, const char * pszMessage, ::duration durationTimeOut, UINT fuStyle)
   {

      if (Session.userex() == NULL)
         return ::base::application::simple_message_box_timeout(pwndOwner, pszMessage, durationTimeOut, fuStyle);

      try
      {

         return Session.userex()->simple_message_box_timeout(pwndOwner, pszMessage, durationTimeOut, fuStyle, this);

      }
      catch (...)
      {

      }

      return ::base::application::simple_message_box_timeout(pwndOwner, pszMessage, durationTimeOut, fuStyle);

   }


   sp(type) application::user_default_controltype_to_typeinfo(::user::e_control_type econtroltype)
   {

      return Sess(this).user()->controltype_to_typeinfo(econtroltype);


   }

   void application::set_form_impact_system(::user::impact_system * pdoctemplate, ::user::impact_system * pdoctemplateChild, ::user::impact_system * pdoctemplatePlaceHolder)
   {
      Session.userex()->m_ptemplateForm = pdoctemplate;
      add_document_template(pdoctemplate);
      Session.userex()->m_ptemplateChildForm = pdoctemplateChild;
      add_document_template(pdoctemplateChild);
      Session.userex()->m_ptemplatePlaceHolder = pdoctemplatePlaceHolder;
      add_document_template(pdoctemplatePlaceHolder);

   }


   sp(::user::document)   application::create_form(::user::form_callback * pcallback, sp(::user::interaction) pwndParent, var var)
   {

      return Sess(this).userex()->create_form(this, pcallback, pwndParent, var);

   }


   sp(::user::document)   application::create_form(sp(::user::form) pview, ::user::form_callback * pcallback, sp(::user::interaction) pwndParent, var var)
   {

      return Sess(this).userex()->create_form(this, pview, pcallback, pwndParent, var);

   }


   sp(::user::document)   application::create_child_form(::user::form_callback * pcallback, sp(::user::interaction) pwndParent, var var)
   {

      return Sess(this).userex()->create_child_form(this, pcallback, pwndParent, var);


   }

   sp(::user::document)  application::create_child_form(sp(::type) pt, sp(::user::interaction) pwndParent, var var)
   {

      return Sess(this).userex()->create_child_form(this, pt, pwndParent, var);

   }

   sp(::user::document)   application::create_child_form(sp(::user::form) pview, ::user::form_callback * pcallback, sp(::user::interaction) pwndParent, var var)
   {

      return Sess(this).userex()->create_child_form(this, pview, pcallback, pwndParent, var);

   }


   ::user::document * application::hold(sp(::user::interaction) pui)
   {

      return Sess(this).userex()->hold(pui);

   }

   string application::get_cred(const string & strRequestUrl, const RECT & rect, string & strUsername, string & strPassword, string strToken, string strTitle, bool bInteractive)
   {

      synch_lock sl(get_cred_mutex());

      string strRet;

      manual_reset_event ev(this);

      ::fork(this, [&]()
      {

         string str = ::fontopus::get_cred(this, strUsername, strPassword, strToken);

         if (str == "ok" && strUsername.has_char() && strPassword.has_char())
         {

            strRet = "ok";

            goto finished;

         }

         if (!bInteractive)
         {

            str = "failed";

            goto finished;

         }

         if (m_pmainpane != NULL && m_pmainpane == NULL)
         {

            try
            {

               strRet = m_pmainpane->get_cred(strRequestUrl, rect, strUsername, strPassword, strToken, strTitle, bInteractive);

               goto finished;

            }
            catch (...)
            {

            }

         }

#if !defined(LINUX) && !defined(APPLEOS) && !defined(VSNORD)
         attach_thread_input_to_main_thread(false);
#endif

         strRet = ::base::application::fontopus_get_cred(get_app(), strRequestUrl, rect, strUsername, strPassword, strToken, strTitle, bInteractive, NULL);

finished:

         ev.SetEvent();

      });

      ev.wait();

      return strRet;

   }


   bool session::initialize1_userex()
   {

      if (!m_puserex->init())
      {

         return false;

      }

      if (!m_puserex->init1())
      {

         return false;

      }

      if (!m_puserex->init2())
      {

         return false;

      }

      return true;

   }


   void session::term_application()
   {

      try
      {

         for(auto & pair : System.m_appmap)
         {

            try
            {

               if(pair.m_element2->m_pcoresession == this)
               {

                  pair.m_element2->m_pcoresession = NULL;

               }

            }
            catch(...)
            {

            }

         }

      }
      catch(...)
      {

      }

      try
      {

         ::base::session::term_application();

      }
      catch (...)
      {

      }

      try
      {

         ::core::application::term_application();

      }
      catch (...)
      {

      }

      try
      {

         if (m_pfilemanager != NULL)
         {

            m_pfilemanager->term();

         }

      }
      catch (...)
      {

      }

      m_pfilemanager.release();

      try
      {

         if(m_puserex != NULL)
         {

            m_puserex->term();

         }

      }
      catch (...)
      {

      }

      m_puserex = NULL;

      ::aura::del(m_pfontlist);

      m_pobjectUserex.release();

   }


   void session::OnFileManagerOpenFile(::filemanager::data * pdata, ::fs::item_array & itema)
   {

      UNREFERENCED_PARAMETER(pdata);

      m_pdocs->m_ptemplate_html->open_document_file(itema[0]->get_friendly_path());

   }


   void session::initialize_bergedge_application_interface()
   {

      //      int32_t iCount = 32; // todo: get from bergedge profile

      m_pdocs->m_pnaturedocument = NULL;

   }


   bool session::process_initialize_userex()
   {

      if (m_puserex == NULL)
      {

         m_puserex = create_userex();

         if (m_puserex == NULL)
            return false;

         m_pobjectUserex = m_puserex;

      }

      return true;

   }


   void session::on_frame_window_drop_files(::user::interaction * pui, ::file::patha & patha)
   {

      ::userex::userex* puser = userex();

      ASSERT(puser != NULL);

      for (auto & path : patha)
      {

         sp(::create) createcontext(allocer());

         createcontext->m_spCommandLine->m_varFile = path;

         puser->request_create(createcontext);

      }

   }


   ::user::document * session::userex_on_request(::create * pcreate)
   {

      userex()->request_create(pcreate);

      return ::user::get_document(pcreate);

   }


   void session::will_use_view_hint(string strView)
   {

      if(strView == "color_sel")
      {

         if(userex()->m_mapimpactsystem["color_sel"] != NULL)
         {

            return;

         }

         System.factory().creatable_small < ::userex::color_view >();


         userex()->m_mapimpactsystem["color_sel"] = new ::user::multiple_document_template(
         get_app(),
         "main",
         System.type_info < ::user::document >(),
         System.type_info < ::prodevian_translucent_simple_frame_window >(),
         System.type_info < ::userex::color_view >());

      }
      else if(strView == "font_sel")
      {

         if (m_pfontlist != NULL)
         {

            return;

         }

         System.factory().creatable_small < ::user::font_list >();
         System.factory().creatable_small < ::user::font_list_view >();
         System.factory().creatable_small < ::userex::font_view >();

         userex()->m_mapimpactsystem["font_sel"] = new ::user::multiple_document_template(
         get_app(),
         "main",
         System.type_info < ::user::document >(),
         System.type_info < ::prodevian_translucent_simple_frame_window >(),
         System.type_info < ::userex::font_view >());


         m_pfontlist = new ::visual::font_list(this);

         System.visual().fonts().defer_create_font_enumeration();

         fork([&]()
         {
            ::multithreading::set_priority(::multithreading::priority_idle);
            System.visual().fonts().update_font_enumeration();

            m_pfontlist->update();

            output_debug_string("fork with idle");

         });

      }

   }


} // namespace core


namespace user
{

   ::user::mesh_data * mesh::create_mesh_data()
   {

      return Session.userex()->default_create_mesh_data(get_app());

   }

   ::user::list_header * list::create_list_header()
   {

      return Session.userex()->default_create_list_header(get_app());

   }


   ::user::mesh_data * list::create_mesh_data()
   {

      return Session.userex()->default_create_list_data(get_app());

   }


} // namespace user
