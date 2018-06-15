#pragma once



#define session_parent session( )



namespace aura
{


   class CLASS_DECL_AURA session:
      virtual public ::aura::application
   {
   public:


      class CLASS_DECL_AURA map:
         virtual public ::map < index,index, ::aura::session *, ::aura::session * >
      {


      };

      ::map < ::user::e_key, ::user::e_key, bool, bool > *         m_pmapKeyPressed;




      ::user::elemental *                             m_pkeyboardfocusRequest;
      ::user::elemental *                             m_pkeyboardfocus;
      bool                                                     m_bSystemSynchronizedCursor;
      point                                                    m_ptCursor;

      ::visual::cursor *               m_pcursor;
      ::visual::e_cursor               m_ecursorDefault;
      ::visual::e_cursor               m_ecursor;

      ::user::theme_sp                 m_ptheme;
      string_map < ::user::theme_sp >  m_mapTheme;

      ::user::interaction *            m_puiCapture;
      bool                                                     m_bDrawCursor;


      ::user::copydesk *                                       m_pcopydesk;

      ::user::interaction *                                    m_puiMouseMoveCapture;
      ::user::interaction *                                    m_puiLastLButtonDown;


      index                                                    m_iEdge;

      ::ifs *                                                  m_pifs;

      bool                                                     m_bMatterFromHttpCache;

      sp(::fontopus::fontopus)                                 m_pfontopus;
      sp(class ::fontopus::licensing)                          m_splicensing;

      sp(::user::style)										            m_pstyle;


      string_map < ::aura::application * >                     m_mapApplication;



      application_ptra                                         m_appptra;
      sp(::aura::savings)                                      m_psavings;
      ::sockets::sockets *                                     m_psockets;




      ::aura::application *                              m_pappCurrent;

      var                                                m_varTopicFile;
      var                                                m_varCurrentViewFile;
      bool                                               m_bShowPlatform;

      sp(::aura::str_context)                            m_puserstrcontext;


      ptrmap < ::aura::application, string_map < sp(::aura::library) > > m_mapLibrary;

      bool                                                     m_bSystemSynchronizedScreen;
      rect_array                                               m_rectaMonitor;
      rect_array                                               m_rectaWkspace;
      index                                                    m_iMainMonitor;
      index                                                    m_iMainWkspace;

      sp(::user::window_map)        m_pwindowmap;



      session(::aura::application * papp);
      virtual ~session_parent;


      application_ptra & appptra();


      virtual ::sockets::sockets & sockets() { return *m_psockets;  }; // only usable from base.dll and dependants

      ::aura::str_context *                        str_context() { return m_puserstrcontext; }

      virtual bool is_session() override;

      virtual int64_t add_ref() override
      {

         return ::object::add_ref();

      }

      virtual int64_t dec_ref() override
      {

         return ::object::dec_ref();

      }

      virtual void construct(::aura::application * papp, int iPhase);

      virtual bool process_init() override;

      virtual bool init1() override;

      virtual bool init2() override;

      virtual bool init_application() override;

      virtual bool init() override;

      virtual void term() override;

      virtual void term_application() override;

      //virtual ::visual::cursor * get_cursor();

      //virtual ::visual::cursor * get_default_cursor();

      //virtual sp(::aura::application) start_application(const char * pszType,const char * pszAppId, ::create * pcreate);


      virtual void request_create(::create * pcreate) override;
      virtual bool open_by_file_extension(const char * pszPathName,application_bias * pbiasCreate = NULL);
      virtual bool open_by_file_extension(::create * pcc);

      sp(::aura::application) get_new_application(::aura::application * pappParent, const char * pszAppId);

      inline ::aura::savings &                  savings()      { return *m_psavings; }



      using ::aura::application::start_application;
      virtual sp(::aura::application) start_application(const char * pszAppId, ::create * pcreate);


      virtual COLORREF get_default_color(uint64_t ui);


      //virtual index initial_frame_position(LPRECT lprect,const RECT & rect, bool bMove);

      virtual size get_window_minimum_size();


      virtual void frame_pre_translate_message(::message::message * pobj);


      class ::user::window_map & window_map();


      inline sp(::fontopus::fontopus)              fontopus() { return m_pfontopus; }
      inline class ::fontopus::licensing &         licensing() { return *m_splicensing; }
      ::user::copydesk &                           copydesk();


      virtual ::fontopus::fontopus * create_fontopus();


      virtual ::fontopus::user * safe_get_user();


      virtual ::fontopus::user * get_user();
      virtual ::fontopus::user * create_current_user();


      virtual void defer_initialize_user_presence();

      virtual bool is_licensed(const char * pszId, bool bInteractive = true);


      virtual void userstyle(::user::style_context * pcontext);

      virtual bool get_auth(const string & pszForm, string & strUsername, string & strPassword);



      virtual string fontopus_get_user_sessid(const string & str);


      virtual string fontopus_get_cred(::aura::application * papp, const string & strRequestUrl, const RECT & rect, string & strUsername, string & strPassword, string strToken, string strTitle, bool bInteractive, ::user::interactive * pinteractive = NULL) override;


      virtual void on_user_login(::fontopus::user * puser);



      virtual void on_request(::create * pcreate) override;

      ::aura::application * application_get(const char * pszAppId, bool bCreate, bool bSynch, application_bias * pbiasCreate);


      virtual bool is_key_pressed(::user::e_key ekey);

      virtual void set_key_pressed(::user::e_key ekey, bool bPressed);

      virtual ::user::elemental * get_keyboard_focus();
      virtual void set_keyboard_focus(::user::elemental * pkeyboardfocus);

      virtual ::user::primitive * get_active_ui() override;
      virtual ::user::primitive * get_focus_ui();

      virtual void on_finally_focus_set(::user::elemental * pelementalFocus);


      virtual oswindow get_capture();

      virtual void set_cursor(::visual::cursor * pcursor);
      virtual void set_cursor(::visual::e_cursor ecursor);
      virtual void set_default_cursor(::visual::e_cursor ecursor);
      virtual ::visual::cursor * get_cursor();
      virtual ::visual::cursor * get_default_cursor();

      virtual bool on_ui_mouse_message(::user::mouse * pmouse);

      virtual ::user::primitive * GetActiveWindow();
      virtual ::user::primitive * GetFocus();

      //::user::elemental * get_keyboard_focus() override;
      virtual bool ReleaseCapture();
      virtual sp(::user::interaction) GetCapture();

      virtual void translate_os_key_message(::user::key * pkey);
      virtual bool on_create_frame_window();
//         virtual void on_finally_focus_set(::user::elemental * pelementalFocus);

      virtual void get_cursor_pos(LPPOINT lppoint);

//         virtual oswindow get_capture();

      //virtual COLORREF get_default_color(uint64_t ui) override;






      virtual index get_main_monitor(LPRECT lprect = NULL);
      virtual bool set_main_monitor(index iMonitor);
      virtual ::count get_monitor_count();
      virtual bool  get_monitor_rect(index iMonitor, LPRECT lprect);

      virtual index get_main_wkspace(LPRECT lprect = NULL);
      virtual bool set_main_wkspace(index iWkspace);
      virtual ::count get_wkspace_count();
      virtual bool  get_wkspace_rect(index iWkspace, LPRECT lprect);

      virtual bool wkspace_to_monitor(LPRECT lprect, index iMonitor, index iWkspace);
      virtual bool monitor_to_wkspace(LPRECT lprect, index iWkspace, index iMonitor);

      virtual bool wkspace_to_monitor(LPRECT lprect);
      virtual bool monitor_to_wkspace(LPRECT lprect);

      virtual ::count get_desk_monitor_count();
      virtual bool  get_desk_monitor_rect(index iMonitor, LPRECT lprect);

      virtual void  get_monitor(rect_array & rectaMonitor, rect_array & rectaIntersect, const RECT & rect);

      virtual index initial_frame_position(LPRECT lprect, const RECT & rect, bool bMove, ::user::interaction * pui);
      virtual index get_zoneing(LPRECT lprect, const RECT & rect, ::user::e_appearance eappearance);
      virtual index get_best_zoneing(::user::e_appearance * peappearance, LPRECT lprect, const RECT & rect);
      virtual index get_best_monitor(LPRECT lprect, const RECT & rect);
      virtual index get_best_wkspace(LPRECT lprect, const RECT & rect);
      virtual index get_good_iconify(LPRECT lprect, const RECT & rect);
      virtual index get_good_restore(LPRECT lprect, const RECT & rect, ::user::interaction * pui);
      virtual index get_good_move(LPRECT lprect, const RECT & rect, ::user::interaction * pui);
      virtual index get_ui_wkspace(::user::interaction * pui);


      virtual void defer_instantiate_user_theme(const char * pszUiInteractionLibrary = NULL);
      ::user::theme_sp instantiate_user_theme(const char * pszUinteractionLibrary, ::aura::application * papp = NULL);
      ::user::theme_sp get_user_theme(const char * pszUinteractionLibrary, ::aura::application * papp = NULL);


      virtual void _001OnDefaultTabPaneDrawTitle(::user::tab_pane & pane, ::user::tab * ptab, ::draw2d::graphics * pgraphics, LPCRECT lpcrect, ::draw2d::brush_sp & brushText);


   };


} // namespace aura



