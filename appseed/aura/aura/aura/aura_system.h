#pragma once


CLASS_DECL_AURA ::file::path application_installer_folder(const ::file::path & pathExe, const char * pszPlatform, const char * pszConfiguration, const char * pszLocale, const char * pszSchema);
CLASS_DECL_AURA bool is_application_installed(const ::file::path & pathExe, string & strBuild, const char * pszPlatform, const char * pszConfiguration, const char * pszLocale, const char * pszSchema);
CLASS_DECL_AURA bool set_application_installed(const ::file::path & pathExe, const char * pszBuild, const char * pszPlatform, const char * pszConfiguration, const char * pszLocale, const char * pszSchema);
CLASS_DECL_AURA ::file::path get_application_path(string strAppId, const char * pszPlatform, const char * pszConfiguration);
CLASS_DECL_AURA ::file::path get_installed_application_path_file(string strAppId);
CLASS_DECL_AURA ::file::path get_installed_application_path(string strAppId);


namespace aura
{


   class CLASS_DECL_AURA system:
      virtual public ::aura::application
#ifndef WINDOWS
      ,virtual public ::exception::translator
#endif
   {
   public:

      bool on_application_menu_action(const char * pszCommand) override;
#ifdef WINDOWSEX

      ::user::system_interaction_impl *      m_psystemwindow;

#endif

      ::os_system_window *                   m_possystemwindow;

#ifdef APPLE_IOS

      plane_system *                         m_pplanesystem;

#endif

      ::app_core *                           m_pappcore;

#ifdef DEBUG

      ::dump_context *                       m_pdumpcontext;

#endif

      ::aura::session::map                         m_aurabergedgemap;

      ::object *                                   m_pDraw2dFactoryExchange;
      sp(::visual::visual)                         m_pvisual;

      ::file::path                                 m_pathConfig;
      ::file::path                                 m_pathCa2Config;
      pointer_array < ::aura::application * >      m_appptra;


      sp(class ::datetime::department)             m_pdatetime;
      ::crypto::crypto_sp                          m_spcrypto;
      class ::fontopus::user_set                   m_userset;




//         sp(::aura::audio::wave_out)                  m_spwaveout;

      stridsp(type)                                m_typemap;
      spa(service_base)                            m_serviceptra;
      sp(base_factory)                             m_pfactory;
      sp(class ::xml::department)                  m_pxml;
      const id_pool                                m_cidpool;
      sp(class ::aura::log)                        m_plog;
      sp(math::math)                               m_pmath;
      sp(geometry::geometry)                       m_pgeometry;

      sp(::aura::str)                              m_puserstr;


      static ::id                              idEmpty;
      sp(class ::str::base64)                      m_spbase64;

      ::string_to_string                           m_mapAppLibrary;
      sp(class machine_event_central)              m_pmachineeventcentral;
      string_map < int_to_string >                 m_mapEnumToName;
      string_map < string_to_int >                 m_mapNameToEnum;
      ::aura::os_sp                                m_spos;
      //array < ::aura::session * >                  m_basesessionptra;
      colorertake5::ParserFactory *                m_pparserfactory;

      static system *                              g_p;

#ifdef WINDOWS
      float                                        m_dpi;
      //ID2D1DeviceContext *                         m_pdevicecontext;
      //mutex                                        m_mutexDc;
#endif

      void *                                       m_ftlibrary;



      sp(mutex)                                    m_spmutexUserAppData;
      sp(mutex)                                    m_spmutexSystemAppData;

      sp(mutex)                                    m_spmutexMatter;

      mutex                                        m_mutexFactory;


      //bool                                         m_bMatterFromHttpCache;
      bool                                         m_bGudoNetCache;


      sp(::process::department)                    m_spprocess;


      int32_t                                      m_nCmdShow;
      size_t                                       m_nSafetyPoolSize;      // ideal size
//      ::html::html *                               m_phtml; // only defined  in core;


      bool                                         m_bDoNotExitIfNoApplications;

      bool (system::*                              m_pfnVerb)();

      ::html::html *                               m_phtml; // only defined and set in html library/component
      ::url::department *                          m_purldepartment;
      ::compress_department *                      m_pcompress;

      ::file::system_sp                            m_spfile;
      ::file::dir::system_sp                       m_spdir;

      sp(::http::system)                           m_sphttpsystem;



      string                                       m_strInstallVersion;
      string                                       m_strInstallPlatform;

      DWORD                                        m_dwMainStartTime;
      DWORD                                        m_dwAfterApplicationFirstRequest;


      sp(mutex)                                    m_spmutexOpenweatherCity;

      stringa                                      m_straCityLo;
      stringa                                      m_straCity;
      int64_array                                  m_iaIds;
      double_array                                 m_daLon;
      double_array                                 m_daLat;

      string_map < sp(::aura::library) >           m_mapLibrary;

      string_map < openweather_city * >            m_mapCity;

      string                                       m_strIosHome;
      string                                       m_strIosTemp;
      string_to_string                             m_mapCachedLatestBuild;

//      sp(::install::install)                       m_spinstall;

      sp(::net::email_department)                     m_spemaildepartment;

      stringa                                      m_straCommandLineAccumul;
      stringa                                      m_straCommandLineExtra;
      DWORD                                        m_dwCommandLineLast;
      int                                          m_iCommandLineDelay;
      sp(::thread)                                 m_pthreadCommandLine;


      bool                                         m_bSystemSynchronizedCursor;
      bool                                         m_bSystemSynchronizedScreen;

      sp(builtin_strlangmap)                       m_pstrlangmap;
#ifdef WINDOWSEX


      raw_array < MONITORINFO >                    m_monitorinfoa;
      raw_array < HMONITOR >                       m_hmonitora;
      raw_array < MONITORINFO >                    m_monitorinfoaDesk;

#else

      rect_array                                   m_rectaMonitor;
      rect_array                                   m_rectaWork;

#endif



      map < ::file::path, const ::file::path &, ::visual::dib_sp > m_mapDib;

      sp(::user::window_map)                       m_pwindowmap;


      system(::aura::application * papp, app_core * pappcore);
      virtual ~system();


      application_ptra                                get_appptra();


      //spa(::aura::session)                         &  basesessionptra();

      class ::user::window_map & window_map();



      class ::aura::os                             &  os();
      class base_factory                           &  factory();


      ::aura::str                                  & str();
      ::process::department                       &  process();


      ::xml::department                            &  xml();
      class ::str::base64                          &  base64();
      class ::aura::log                            &  log();
      class ::machine_event_central                &  machine_event_central();

      geometry::geometry                           &  geometry()
      {
         return *m_pgeometry;
      }
      math::math                                   &  math()
      {
         return *m_pmath;
      }

      inline class ::visual::visual                & visual() { return *m_pvisual; }

      //::colorertake5::ParserFactory                &  parser_factory();
      inline ::url::department                     &  url()
      {
         return *m_purldepartment;   // only usable from base.dll and dependants
      }
      inline class ::compress_department           &  compress()
      {
         return *m_pcompress;   // only usable from base.dll and dependants
      }

      inline ::file::system                        &  file()
      {
         return *m_spfile;
      }
      inline ::file::dir::system                   &  dir()
      {
         return *m_spdir;
      }
      ::net::email_department               & email();

      ::fontopus::user_set                         & userset();

      ::datetime::department                       &  datetime();

      virtual string url_encode(const string & str);

      virtual void on_allocation_error(::aura::application * papp, ::type * ptype);
      //   sp(object) alloc(::aura::application * papp, sp(type) info);
      object * alloc(::aura::application * papp,const std_type_info & info);
      //   virtual sp(object) on_alloc(::aura::application * papp, sp(type) info);

      mutex * get_openweather_city_mutex();

      using ::aura::application::alloc;
      virtual object * alloc(::aura::application * papp,::type * ptype);
      virtual object * alloc(::aura::application * papp,const ::id & idType);

      virtual object * on_alloc(::aura::application * papp,::type * ptype);
      virtual object * clone() override;
      virtual node_data_exchange * node_ddx();

      template < typename T >
      inline T * cast_clone(T * pt)
      {

         return ::clone(pt);

      }

      ::visual::dib_sp & get_dib(::aura::application * papp, ::file::path path, bool bAsync = false);

      template < class T >
      ::type * type_info()
      {

         return get_type_info(typeid(T));

      }


      virtual ::type * get_type_info(const ::std_type_info & info);

      ::type * get_type_info(const ::id & idType)
      {

         if(idType.is_empty())
            return NULL;

         synch_lock sl(&m_mutexFactory);

         return m_typemap[idType].m_p;

      }


      virtual void discard_to_factory(::object * pca);





      virtual UINT os_post_to_all_threads(UINT uiMessage,WPARAM wparam = 0,lparam lparam = 0);

      virtual bool init_application() override;

      virtual bool process_init() override;

      virtual bool init() override;

      virtual bool init1() override;

      virtual bool init2() override;


      virtual void term_application() override;

      virtual void term2() override;

      virtual void term1() override;

      virtual void term() override;

      virtual void TermApplication() override;


      virtual void process_term() override;


      virtual bool is_system() override;



      static inline ::id id(const ::std_type_info & info);
      static inline ::id id(const char * psz);
      static inline ::id id(const string & str);
      static inline ::id id(int64_t i);
      static inline ::id_space & id();
      inline ::id id(const var & var);
      inline ::id id(const property & prop);


      virtual int32_t _001OnDebugReport(int32_t i1,const char * psz1,int32_t i2,const char * psz2,const char * psz3,va_list args);
      virtual int32_t _debug_logging_report(int32_t iReportType, const char * pszFilename, int32_t iLinenumber, const char * iModuleName, const char * pszFormat, va_list list);
      virtual bool assert_failed_line(const char * lpszFileName,int32_t iLine);
      virtual bool on_assert_failed_line(const char * pszFileName,int32_t iLine);


      void set_enum_name(sp(type) etype,int32_t i,const char * psz)
      {
         m_mapEnumToName[etype->name()][i] = psz;
         m_mapNameToEnum[etype->name()][psz] = i;
      }
      string get_enum_name(sp(type) info,int32_t i)
      {
         return m_mapEnumToName[info->name()].get(i,"");
      }

      template < class E,E edefault>
      void from_name(base_enum < E,edefault > & b,const char * psz,E iDefault = edefault)
      {
         b = enum_from_name(System.type_info < E >(),psz,iDefault);
      }

      template < class E,E edefault>
      string get_name(const base_enum < E,edefault > & b)
      {
         return get_enum_name(System.type_info < E >(),(int32_t)(E)b);
      }

      template < class ENUM >
      ENUM enum_from_name(sp(type) info,const char * psz,int32_t iDefault = 0)
      {
         return (ENUM)m_mapNameToEnum[info->name()].get(psz,iDefault);
      }
      int32_t enum_from_name(sp(type) info,const char * psz,int32_t iDefault = 0)
      {
         return m_mapNameToEnum[info->name()].get(psz,iDefault);
      }
      int32_t enum_from_name(const std_type_info & info,const char * psz,int32_t iDefault = 0)
      {
#ifdef WINDOWS
         return m_mapNameToEnum[info.name()].get(psz,iDefault);
#else
         return m_mapNameToEnum[info.name()].get(psz, iDefault);
#endif
      }

      template < class TYPE >
      void set_enum_name(sp(type) etype,TYPE e,const char * psz)
      {
         set_enum_name(etype,(int32_t)e,psz);
      }
      template < class TYPE >
      string get_enum_name(sp(type) etype,TYPE e)
      {
         return get_enum_name(etype,(int32_t)e);
      }

      template < class TYPE >
      void set_enum_name(const std_type_info & info,TYPE e,const char * psz)
      {
         set_enum_name(get_type_info(info),(int32_t)e,psz);
      }
      template < class TYPE >
      string get_enum_name(const std_type_info & info,TYPE e)
      {
         return get_enum_name(get_type_info(info),(int32_t)e);
      }

      template < class TYPE >
      void set_enum_name(TYPE e,const char * psz)
      {
         set_enum_name(System.type_info < TYPE >(),(int32_t)e,psz);
      }
      template < class TYPE >
      string get_enum_name(TYPE e)
      {
         return get_enum_name(System.type_info < TYPE >(),(int32_t)e);
      }

      virtual ::aura::session * query_session(index iEdge);

      virtual bool initialize_log(const char * pszId);


      virtual void appa_load_string_table();
      virtual void appa_set_locale(const char * pszLocale,::action::context actioncontext);
      virtual void appa_set_schema(const char * pszStyle,::action::context actioncontext);

      virtual bool assert_running_global(const char * pszAppName,const char * pszId = NULL);
      virtual bool assert_running_local(const char * pszAppName,const char * pszId = NULL);



      virtual ::count get_application_count();


      virtual string crypto_md5_text(const string & str);

      inline class ::http::system                  & http()
      {
         return *m_sphttpsystem;
      }

      class ::crypto::crypto                       & crypto();

      virtual void * & ftlibrary();

      virtual ::file::path defer_make_file_system_url(string str, ::aura::application * papp);

      virtual ::file::path defer_process_path(::file::path path, ::aura::application * papp, bool bOptional = true, bool bNoCache = false);

      virtual ::file::path defer_process_matter_path(::file::path path, ::aura::application * papp, bool bOptional = true, bool bNoCache = false);
      virtual ::file::path get_matter_path(string strMatter);
      virtual ::file::path get_matter_cache_path(string strMatter, bool bOptional = true, bool bNoCache = false);
      virtual ::file::path local_get_matter_cache_path(string strMatter);
      virtual ::file::path side_get_matter_path(string strMatter);

      virtual bool find_applications_from_cache();
      virtual bool find_applications_to_cache(bool bSave = true);
      virtual bool map_application_library(const char * pszLibrary);


      virtual void install_progress_add_up(int iAddUp = 1);

      virtual bool alloc_session();

      virtual ::aura::session * on_create_session();


      virtual ::aura::session * get_session(index iEdge,application_bias * pbiasCreation = NULL);


      virtual void on_request(::create * pcreate) override;


      virtual string get_system_platform();
      virtual string get_system_configuration();
      virtual string get_latest_build_number(const char * pszConfiguration, const char * pszAppId);


      virtual void on_start_find_applications_from_cache();
      virtual void on_end_find_applications_from_cache(serialize & is);

      virtual void on_end_find_applications_to_cache(serialize & os);

      virtual void on_map_application_library(::aura::library & library);

      virtual bool process_command(::command::command * command) override;

      virtual void request_exit();

      virtual void defer_check_exit();

      virtual void handle_command(::command::command * pcommand) override;

      virtual void defer_check_openweather_city_list();

      virtual openweather_city * openweather_find_city(string strQuery);
      virtual index openweather_find_city2(string strQuery, string & strCit, int64_t & iId, double & dLat, double & dLon);
      virtual index openweather_find_city2(string strQ1, string strQ2, string & strCit, int64_t & iId, double & dLat, double & dLon, bool bPrefix);

#ifdef VSNORD

      virtual bool android_set_user_wallpaper(string strUrl);
      virtual bool android_get_user_wallpaper(string & strUrl);

#endif

      virtual bool defer_accumulate_on_open_file(stringa stra, string strExtra);

      virtual bool merge_accumulated_on_open_file(::create * pcreate);

      virtual bool on_open_file(var varFile, string strExtra);

      virtual LPWAVEOUT waveout_open(int iChannel, LPAUDIOFORMAT pformat, LPWAVEOUT_CALLBACK pcallback) override;

      virtual bool initialize_native_window1();

      virtual void * initialize_native_window2(LPCRECT lpcrect);

      virtual void on_os_text(e_os_text etext, string strText);

      virtual ::user::interaction_impl * impl_from_handle(void * posdata);
      virtual ::user::interaction * ui_from_handle(void * posdata);

      virtual bool defer_create_system_frame_window();

      void enum_display_monitors();

#if defined(WINDOWS)
      static_function BOOL CALLBACK monitor_enum_proc(HMONITOR hmonitor, HDC hdcMonitor, LPRECT lprcMonitor, LPARAM dwData);
      void monitor_enum(HMONITOR hmonitor, HDC hdcMonitor, LPRECT lprcMonitor);
#endif

      virtual index get_main_monitor(LPRECT lprect = NULL);
      virtual ::count get_monitor_count();
      virtual bool  get_monitor_rect(index iMonitor, LPRECT lprect);
      virtual ::count get_desk_monitor_count();
      virtual bool  get_desk_monitor_rect(index iMonitor, LPRECT lprect);

      virtual index get_main_wkspace(LPRECT lprect = NULL);
      virtual ::count get_wkspace_count();
      virtual bool  get_wkspace_rect(index iWkspace, LPRECT lprect);
      virtual ::count get_desk_wkspace_count();
      virtual bool  get_desk_wkspace_rect(index iWkspace, LPRECT lprect);
      virtual index get_ui_wkspace(::user::interaction * pui);

      virtual void on_extra(string str);

      virtual string standalone_setting(string str);
      virtual bool set_standalone_setting(string str, string strSetting);


   };


} // namespace aura


CLASS_DECL_AURA ::aura::system * create_aura_system(app_core * pappcore);


