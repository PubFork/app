#pragma once


namespace aura
{


   class CLASS_DECL_AURA application :
      virtual public ::thread,
      virtual public int_scalar_source,
      virtual public ::file::listing_provider,
      virtual public ::user::interactive,
      virtual public ::user::style
   {
   public:

      // former ::aura::application_interface // moved on 2015-05-23 Sammstag while listening to RocketBeansTV (a German channel?) at TwitchTV
      class imaging *                                 m_pimaging;
      ::aura::system *                                m_paurasystem;
      ::aura::session *                               m_paurasession;
      :: axis :: application *                        m_paxisapp; // can be used only from axis and upper
      :: axis ::system *                              m_paxissystem; // can be used only from axis and upper
      :: axis ::session *                             m_paxissession; // can be used only from axis and upper
      :: base :: application *                        m_pbaseapp; // can be used only from base and upper
      ::base::system *                                m_pbasesystem; // can be used only from base and upper
      ::base::session *                               m_pbasesession; // can be used only from base and upper
      ::core::application *                           m_pcoreapp; // can be used only from core and upper
      ::core::system *                                m_pcoresystem; // can be used only from core and upper
      ::core::session *                               m_pcoresession; // can be used only from core and upper


      DWORD                                           m_dwInstallGoodToCheckAgain;


      bool                                            m_bAppHasInstallerProtected;
      bool                                            m_bAppHasInstallerChangedProtected;
      ::install::installer *                          m_pinstaller;
      string                                          m_strInstallTraceLabel;
      string                                          m_strInstallBuild;







      bool                                            m_bAgreeExit;
      bool                                            m_bAgreeExitOk;
      bool                                            m_bFranceExit;

      //sp(application)                                 m_pappimpl;
      sp(ipi)                                         m_pipi;
      sp(service_base)                                m_pservice;

      bool                                            m_bAuraProcessInitialize;
      bool                                            m_bAuraProcessInitializeResult;

      bool                                            m_bAuraInitializeInstance;
      bool                                            m_bAuraInitializeInstanceResult;

      bool                                            m_bAuraInitialize1;
      bool                                            m_bAuraInitialize1Result;

      bool                                            m_bAuraInitialize;
      bool                                            m_bAuraInitializeResult;

      string                                          m_strHttpUserAgentToken;
      string                                          m_strHttpUserAgentVersion;
      mutex                                           m_mutexFrame;
      ::user::interaction_spa *                       m_puiptraFrame;

      string_map < ::aura::application * >            m_appmap;
      string                                          m_strAppName;
      string                                          m_strAppTitle;
      stringa                                         m_straAppCategory;
      ::aura::allocatorsp                             m_allocer;

      sp(::command::command)                          m_pcommand;

      ::http::application                             m_http;


      EExclusiveInstance                              m_eexclusiveinstance;

      sp(::mutex)                                     m_pmutexLocal;
      sp(::mutex)                                     m_pmutexLocalId;
      sp(::mutex)                                     m_pmutexGlobal;
      sp(::mutex)                                     m_pmutexGlobalId;

      bool                                            m_bService;

      ::file::patha                                   m_straMatterLocator;
      string                                          m_strLibraryName;
      string                                          m_strAppId;
      string                                          m_strRelativeFolder;
      string                                          m_strBuild;

      HINSTANCE                                       m_hinstance;


      bool                                            m_bUpdateMatterOnInstall;


      bool                                            m_bLicense;
      string                                          m_strBaseSupportId;


      string                                          m_strRoot;
      string                                          m_strDomain;
      string                                          m_strLocale;
      string                                          m_strSchema;

      // Initial state of the application's interaction_impl; normally,
      // this is an argument to ShowWindow().
      manual_reset_event *                            m_pevAppBeg;
      manual_reset_event *                            m_pevAppEnd;
      string                                          m_strInstallToken;
      mutex                                           m_mutexMatterLocator;



      mutex                                           m_mutexStr;
      string_table                                    m_stringtable;
      string_table                                    m_stringtableStd;
      map < id, id, string, string >                  m_stringmap;


      ::file::dir::application_sp                     m_spdir;
      ::file::application_sp                          m_spfile;
      application_bias                                m_biasCalling;



      application();
      virtual ~application();


      virtual void assert_valid() const override;
      virtual void dump(dump_context & dumpcontext) const override;


      virtual bool app_data_set(class id id, ::file::ostream & os);
      virtual bool app_data_get(class id id, ::file::istream & is);

      virtual bool app_data_set(class id id, ::file::serializable & obj);
      virtual bool app_data_get(class id id, ::file::serializable & obj);

      virtual void install_message_routing(::message::sender * psender) override;


      virtual object * alloc(sp(type) info);
      virtual object * alloc(const id & idType);

      template < typename T >
      void alloc(T * & pt);
      template < typename T >
      T * alloc(sp(type) info)
      {
         object * p = alloc(info);
         if(p == NULL)
            return NULL;
         T * pt = dynamic_cast <T *>(p);
         if(pt == NULL)
         {
            ::release(p);
            return NULL;
         }
         return pt;
      }
      template < typename T >
      T * alloc(const id & idType)
      {
         object * p = alloc(idType);
         if(p == NULL)
            return NULL;
         T * pt = dynamic_cast <T *>(p);
         if(pt == NULL)
         {
            ::release(p);
            return NULL;
         }
         return pt;
      }


      //virtual void tellme_destroyed(::user::primitive * pui, bool * pDestroyed, bool bTell = true);
      virtual ::thread_toolset * create_thread_toolset(::thread::e_tool etool);

      virtual int32_t simple_message_box(::user::primitive * puiOwner,const char * pszMessage,UINT fuStyle = MB_OK);
      virtual int32_t simple_message_box_timeout(::user::primitive * pwndOwner,const char * pszMessage,::duration durationTimeOut,UINT fuStyle);
      int32_t simple_message_box(const char * pszMessage,UINT fuStyle);
      virtual string message_box(const string & pszMatter,property_set & propertyset);


      virtual string load_string(id id);
      virtual bool load_string(string & str,id id);
      virtual void load_string_table();
      //   virtual string load_string(id id);
      // virtual bool load_string(string & str, id id);
      virtual bool load_cached_string(string & str,id id,bool bLoadStringTable);
      virtual bool load_cached_string_by_id(string & str,id id,bool bLoadStringTable);
      virtual void load_string_table(const string & pszApp,const string & pszId);

      virtual int32_t hotplugin_host_starter_start_sync(const char * pszCommandLine,::aura::application * papp,hotplugin::host * phost,hotplugin::plugin * pplugin = NULL);

      inline class ::file::dir::application &   dir()
      {
         return *m_spdir;
      }
      inline class ::file::application &        file()
      {
         return *m_spfile;
      }
      inline class ::http::application &        http()
      {
         return m_http;
      }

      virtual class imaging & imaging();


      virtual string get_title();
      virtual stringa get_categories();


      virtual bool on_run_exception(::exception::exception * pe) override;
      //virtual bool handle_not_installed(::not_installed  * pnotinstalled);

      virtual bool is_system() override;
      virtual bool is_session() override;
      virtual bool is_serviceable();
      virtual bool is_user_service();

      void set_has_installer(bool bSet);

      void process_machine_event_data(machine_event_data * pdata);

      virtual bool open_link(string strLink, string strProfile, string strTarget);
      virtual void open_profile_link(string strUrl, string strProfile, string strTarget);
      virtual void sync_open_profile_link(string strUrl, string strProfile, string strTarget);

      void chromium(string strUrl, string strBrowser, string strId, ::file::path path, string strProfile, string strParam);

//      void commander(string strUrl, string strWeather, string strUser, ::file::path path, string strParam);

      void defer_create_firefox_profile(::file::path pathFirefox, string strProfileName, ::file::path pathProfile);

      void firefox(string strUrl, string strBrowser, string strProfile, string strParam);

      virtual void browser(string strUrl, string strBrowser, string strProfile, string strTarget);


      virtual void DoWaitCursor(int32_t nCode); // 0 => restore, 1=> begin, -1=> end
      virtual void ShowWaitCursor(bool bShow = true);


//#ifndef METROWIN

      virtual void get_time(timeval *p);

//#endif

      virtual void process_message_filter(int32_t code,::message::message * pobj) override;

      virtual bool on_thread_on_idle(::thread * pthread,LONG lCount) override;
      virtual bool post_user_message(::thread * pthread,::user::primitive * pui,UINT message,WPARAM wparam = 0,lparam lparam = 0);

      virtual bool is_window(::user::primitive * pui);

      using ::thread::send_message;
      virtual LRESULT send_message(::user::primitive * pui, UINT message, WPARAM wparam = 0, lparam lparam = 0);

      virtual oswindow get_safe_handle(::user::primitive * pui);
      virtual void dispatch_user_message(::message::message * pobj);
      virtual ::user::primitive * get_parent(::user::primitive * pui);
      virtual bool enable_window(::user::primitive * pui, bool bEnable = true);
      virtual bool set_window_text(::user::primitive * pui, const string & strText);
      //virtual void window_graphics_update_window(window_graphics **  ppdata,oswindow interaction_impl,COLORREF * pOsBitmapData,const RECT & rect,int cxParam,int cyParam,int iStride = -1,bool bTransferBuffer = true);




      virtual bool sys_set(string strPath, string strValue);
      virtual string sys_get(string strPath, string strDefault = "");
      virtual bool app_set(string strPath, string strValue);
      virtual string app_get(string strPath, string strDefault = "");


      //virtual bool verb() override;



      virtual bool app_map_lookup(const char * psz,::aura::application * &);
      virtual void app_map_set(const char * psz,::aura::application *);

      virtual bool Ex2OnAppInstall();
      virtual bool Ex2OnAppUninstall();

      template < class APP >
      APP & cast_app()
      {

         return *dynamic_cast < APP * > (this);

      }

      virtual void _001CloseApplication();

      virtual string get_license_id();

      virtual string get_version();

      virtual ::aura::ipi * create_ipi();

      virtual bool process_init();
      virtual void process_term();

      virtual bool impl_process_init();
      virtual bool impl_init1();
      virtual bool impl_init2();
      virtual bool impl_init3();

      virtual void impl_process_term();
      virtual void impl_term1();
      virtual void impl_term2();
      virtual void impl_term3();

      virtual bool init1();
      virtual bool init2();
      virtual bool init3();

      virtual void term1();
      virtual void term2();
      virtual void term3();

      virtual bool init_thread() override;
      virtual bool init_application();
      virtual void term_application();
      virtual void term_thread() override;

      virtual bool init_instance();
      virtual void term_instance();

      virtual bool init();
      virtual void term();

      virtual bool ca_process_init();
      virtual bool ca_init1();
      virtual bool ca_init2();
      virtual bool ca_init3();

      virtual void ca_term3();
      virtual void ca_term2();
      virtual void ca_term1();
      virtual void ca_process_term();

      // virtual bool is_installing();
      // virtual bool is_unstalling();

      //virtual string get_version();
      virtual void run() override;
      virtual void main() override;
      virtual void on_run();

      virtual bool initial_check_directrix();
      virtual bool os_native_bergedge_start();

      virtual bool pre_run();
      virtual bool application_pre_run();

      virtual void on_pos_run_thread() override;
      virtual void pos_run();
      virtual void application_pos_run();

      virtual bool InitApplication();
      virtual void TermApplication();

      virtual bool on_install();
      virtual bool on_uninstall();

      virtual bool system_add_app_install(const char * pszId, const char * pszBuild);

      virtual void TermThread(HINSTANCE hInstTerm);

      virtual void SetCurrentHandles();

      virtual void set_env_var(const string & var,const string & value);
      virtual IDTHREAD get_thread_id();


      virtual bool _001OnDDECommand(const char * lpcsz);
      virtual void _001EnableShellOpen();
      virtual void _001OnFileNew(::message::message * pobj);


      virtual string draw2d_get_default_library_name();
      virtual string multimedia_audio_get_default_library_name();
      virtual string multimedia_audio_mixer_get_default_library_name();
      virtual string veriwell_multimedia_music_midi_get_default_library_name();

      virtual bool get_temp_file_name_template(string & str,const char * pszName,const char * pszExtension,const char * pszTemplate);

      virtual bool get_temp_file_name(string & str,const char * pszName,const char * pszExtension);
      virtual bool final_handle_exception(::exception::exception * pe);

      service_base * get_service();
      virtual service_base * allocate_new_service();
      virtual bool create_new_service();

      virtual bool create_service();
      virtual bool remove_service();

      virtual bool start_service();
      virtual bool stop_service();

      virtual void on_service_request(::create * pcreate);

      virtual sp(application) assert_running(const char * pszAppId);

      virtual bool is_running();

      virtual string get_mutex_name_gen();

      /// return true if handled
      virtual bool on_exclusive_instance_conflict(EExclusiveInstance eexclusive);

      /// return true if handled
      virtual bool on_exclusive_instance_local_conflict();

      /// return true if handled
      virtual bool on_exclusive_instance_local_conflict(string strModule,int iPid, string strCommandLine);

      virtual void on_new_instance(string strModule,int iPid);

      virtual string get_local_mutex_id();
      virtual string get_global_mutex_id();

      virtual ::mutex * get_local_mutex();
      virtual ::mutex * get_global_mutex();

      virtual string get_local_mutex_name(const char * pszAppName);
      virtual string get_local_id_mutex_name(const char * pszAppName,const char * pszId);
      virtual string get_global_mutex_name(const char * pszAppName);
      virtual string get_global_id_mutex_name(const char * pszAppName,const char * pszId);
      virtual string get_local_mutex_name();
      virtual string get_local_id_mutex_name();
      virtual string get_global_mutex_name();
      virtual string get_global_id_mutex_name();

      virtual bool check_exclusive(bool & bHandled);
      virtual bool release_exclusive();

      virtual void on_set_scalar(e_scalar escalar,int64_t iValue,int iFlags) override;
      virtual void get_scalar_minimum(e_scalar escalar,int64_t & i) override;
      virtual void get_scalar(e_scalar escalar,int64_t & i) override;
      virtual void get_scalar_maximum(e_scalar escalar,int64_t & i) override;



      bool safe_is_running();


      virtual void on_request(::create * pcreate) override;

      // name by Mummi (Japanese -> Guddo : from English : Good, ca2 interpretation : Goods).
      // get/set serializables to user directory
      bool gudo_get(const string & strKey,::file::serializable & obj);
      bool gudo_set(const string & strKey,::file::serializable & obj);


      virtual bool assert_user_logged_in();

      virtual bool startup_command(::command::command * pcommand);

      virtual bool process_command(::command::command * pcommand);

      virtual string http_get_locale_schema(const char * pszUrl,const char * pszLocale,const char * pszSchema);

      virtual sp(::message::base) get_message_base(LPMESSAGE lpmsg);
      virtual sp(::message::base) get_message_base(UINT message, WPARAM wparam, lparam lparam);

#ifdef LINUX

      virtual sp(::message::base) get_message_base(void * pevent,::user::interaction * pwnd = NULL);

#endif


      virtual void process_message(::message::base * base);

      virtual void message_handler(::message::base * pbase) override;


      virtual string get_locale();
      virtual string get_schema();
      virtual ::file::path get_locale_schema_dir(const string & strLocale,const string & strSchema);
      virtual ::file::path get_locale_schema_dir(const string & strLocale);
      virtual ::file::path get_locale_schema_dir();

      virtual void set_locale(const string & lpcsz,::action::context actioncontext);
      virtual void set_schema(const string & lpcsz,::action::context actioncontext);
      virtual void on_set_locale(const string & lpcsz,::action::context actioncontext);
      virtual void on_set_schema(const string & lpcsz,::action::context actioncontext);


      virtual void fill_locale_schema(::str::international::locale_schema & localeschema);
      virtual void fill_locale_schema(::str::international::locale_schema & localeschema,const string & pszLocale,const string & pszSchema);


      //virtual void defer_add_thread_run_wait(sync_object_ptra & soa) override;


      //DECL_GEN_SIGNAL(_001OnApplicationRequest);







      virtual bool platform_open_by_file_extension(index iEdge, const char * pszPathName,application_bias * pbiasCreate = NULL);
      virtual bool platform_open_by_file_extension(index iEdge,::create * pcc);


      virtual sp(::aura::application) instantiate_application(const char * pszAppId, application_bias * pbias);
      virtual sp(::aura::application) create_application(const char * pszAppId, bool bSynch, application_bias * pbias);
      virtual sp(::aura::application) create_platform(::aura::session * psession);
      virtual bool start_application(bool bSynch, application_bias * pbias);

      virtual bool on_start_application();

      virtual bool os_on_start_application();

      virtual bool is_application() override;

      virtual ::file::listing & perform_file_listing(::file::listing & listing) override;
      virtual ::file::listing & perform_file_relative_name_listing(::file::listing & listing) override;

      virtual bool _001OnAgreeExit();
      virtual void _001OnFranceExit();
      virtual void _001FranceExit();

      virtual string lstr(id id, string strDefault = "") override;

      virtual bool do_install();
      virtual bool do_uninstall();



      void handle_command(::command::command * pcommand) override;
      void on_create(::create * pcreate) override;

      virtual void dispatch_user_message_object(::object * pobject);

      //virtual void throw_not_installed();

      virtual void play_audio(var varFile, bool bSynch = false);

      virtual void post_critical_error_message(const char * pszMessage, bool bShowLog = true);

      virtual void show_critical_error_log();

      virtual string get_app_user_friendly_task_bar_name();

      virtual void on_setting_changed(::aura::e_setting esetting);

      virtual string http_get(const string & strUrl, ::property_set & set);

      virtual bool compress_ungz(::file::ostream & ostreamUncompressed, const ::file::path & lpcszGzFileCompressed);
      virtual bool compress_ungz(::primitive::memory_base & mem);
      virtual bool compress_gz(::file::file * pfileOut, const ::file::path & lpcszUncompressed, int iLevel = 6);
      virtual bool compress_gz(::file::file * pfileOut, ::file::file * pfileIn, int iLevel = 6);


      virtual string fontopus_get_cred(::aura::application * papp, const string & strRequestUrl, const RECT & rect, string & strUsername, string & strPassword, string strToken, string strTitle, bool bInteractive, ::user::interactive * pinteractive = NULL) override;

      virtual void draw2d_factory_exchange();

      virtual ::file::path get_executable_path();
      virtual string get_executable_extension();
      virtual string get_executable_title();
      virtual string get_executable_appid();

      virtual bool http_download(const char * pszUrl, const char * pszFile);
      virtual string http_get(const char * pszUrl);


      virtual bool on_open_document_file(var varFile);

      virtual string get_app_id(string wstr);


      virtual void install_trace(const string & str);
      virtual void install_trace(double dRate);
      virtual bool register_spa_file_type();

      virtual bool low_is_app_app_admin_running(string strPlatform, string strConfiguration);
      virtual void defer_start_program_files_app_app_admin(string strPlatform, string strConfiguration);
      virtual void start_program_files_app_app_admin(string strPlatform, string strConfiguration);



      virtual bool keyboard_focus_is_focusable(::user::elemental * pue);
      virtual bool keyboard_focus_OnSetFocus(::user::elemental * pue);

      virtual ::user::interaction * main_window();

//         virtual sp(::message::base) get_message_base(LPMESSAGE lpmsg) override;

      virtual bool get_frame(sp(::user::interaction) & pui);
      virtual void add_frame(::user::interaction * pwnd);
      virtual void remove_frame(::user::interaction * pwnd);

      virtual bool send_message_to_windows(UINT message, WPARAM wparam, LPARAM lparam); // with tbs in <3
      virtual bool route_message_to_windows(::message::message * pmessage); // with tbs in <3


      virtual void send_language_change_message();


      virtual LPWAVEOUT waveout_open(int iChannel, LPAUDIOFORMAT pformat, LPWAVEOUT_CALLBACK pcallback);


      virtual string preferred_userschema();


      virtual ::user::document * place_hold(::user::interaction * pui);


      virtual ::visual::icon * set_icon(object * pobject, ::visual::icon * picon, bool bBigIcon);

      virtual ::visual::icon * get_icon(object * pobject, bool bBigIcon) const;

      virtual void on_control_event(::user::control_event * pevent);

   };


} // namespace aura



