#pragma once



namespace frame
{


   class FrameSchema;


}


namespace user
{


   class control_bar;


} // namespace user


class BaseDockBar;
class BaseReBar;
class BaseMiniDockFrameWnd;

class CLASS_DECL_CORE simple_frame_window :
   virtual public ::user::frame_window,
   virtual public ::user::wndfrm::frame::WorkSetClientInterface,
   virtual public ::user::wndfrm::frame::WorkSetListener,
   virtual public ::user::notify_icon_listener
{
public:



   class helper_task:
      public thread
   {
   public:

      static manual_reset_event * g_pevent;
      simple_frame_window *         m_pframe;
      //bool                          m_bSizeMove;
      //manual_reset_event            m_ev;
      //DWORD                         m_dwLastSizeMoveRequest;



      helper_task(simple_frame_window * pframe);


      virtual void run() override;

      // very loose defer - "I know what you are doing and how you are performing, I have confidence on you!!"
      // but this _new implementation which does not respond promptly on set event cat daemons relying on manual_reset_event consuming resources
      // can loose a save event if move window and suddenly fastly switch to keyboard and press ALT+F4 or fastly target close button and press it...
      // the real looser: the tester that will be happy that unplugging a computer without UPS is good, or maybe short circuit his astounding untouchable thing...
      // (many times a year, oh God, or at least, Satan the God of earth, this astounding or in someones mind, outstanding planet, thank you for your spiritual ministers: we should learn something with this phase here meating in these bodies surrounded by astounding subproducts...)
      void defer_save_window_rect();


   };


   bool                                m_bPendingSaveWindowPlacement;
   bool                                m_bDefaultCreateToolbar;
   bool                                m_bTransparentFrameEnable;
   sp(helper_task)                     m_phelpertask;
   bool                                m_bFullScreenAlt;
   bool                                m_bFullScreenCtrl;
   visual::dib_sp                      m_dibBk;
   bool                                m_bCustomFrameBefore;
   rect                                m_FullScreenWindowRect;
   visual::fastblur                    m_fastblur;
   ::user::e_translucency              m_etranslucency;

   ::user::style_sp                    m_pstyle;

   map < ::id, const ::id &, ::user::toolbar * > m_toolbarmap;

   bool                                m_bTransparentFrame;

   ::draw2d::dib_sp                    m_dibAlpha;
   ::database::key                     m_datakeyFrame;


   sp(::user::wndfrm::frame::frame)    m_pframeschema;


   bool                                m_bDefaultNotifyIcon;
   bool                                m_bShowTask;
   sp(::visual::icon)                  m_piconNotify;
   sp(::user::notify_icon)             m_pnotifyicon;

   var                                 m_varFrame;


   simple_frame_window(::aura::application * papp);
   simple_frame_window(::aura::application * papp, bool bProdevian, bool bTranslucent);
   virtual ~simple_frame_window();


   void simple_frame_window_common_construct(bool bProdevian, bool bTranslucent);


   using ::user::frame_window::create_window;
   virtual bool create_window(const char * lpszClassName,const char * lpszWindowName,uint32_t dwStyle = WS_OVERLAPPEDWINDOW,const RECT & rect = ::null_rect(),sp(::user::interaction) pParentWnd = NULL,const char * lpszMenuName = NULL,uint32_t dwExStyle = 0, ::create * pcreate = NULL);

   virtual bool create_bars();
   virtual bool on_create_bars();

   virtual void install_message_routing(::message::sender * pinterface) override;

   virtual bool on_before_set_parent(sp(::user::interaction) pinterface);
   virtual void on_set_parent(::user::interaction * puiParent) override;

   virtual bool GetClientRect(LPRECT lprect) override;

   virtual bool is_application_main_window();


   bool GetCustomFrame();
   void SetCustomFrame(bool bCustom);
   void SetBorderRect(const RECT & rect) override;
   virtual void GetBorderRect(LPRECT lprect) override;
   void ViewOnActivateFrame(sp(::user::impact) pview, UINT user, sp(::user::interaction) pframe);

   virtual void ToggleFullScreen();
   virtual bool IsFullScreen() override;
   virtual void WfiOnFullScreen() override;
   virtual void WfiOnExitFullScreen() override;
   virtual void ShowControlBars(bool bShow = true, bool bLeaveFullScreenBarsOnHide = false);

   virtual bool IsNotifyIconEnabled() override;
   void OnUpdateControlBarMenu(::user::command * pcommand);

   virtual sp(::user::wndfrm::frame::frame) create_frame_schema();

   virtual bool LoadFrame(const char * pszMatter, uint32_t dwDefaultStyle = WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, ::user::interaction * pParentWnd = NULL, ::create * pcreate = NULL) override;

   DECL_GEN_SIGNAL(_001OnActivate);
   DECL_GEN_SIGNAL(_001OnActivateApp);
   DECL_GEN_SIGNAL(_001OnNcActivate);
   DECL_GEN_SIGNAL(_001OnDisplayChange);
   DECL_GEN_SIGNAL(_001OnTaskbarCreated);

   void _001OnDeferPaintLayeredWindowBackground(::draw2d::graphics * pgraphics) override;

   virtual void defer_create_notification_icon();

   virtual bool LoadToolBar(sp(::type) sptype,id idToolBar,const char * pszToolBar,uint32_t dwCtrlStyle = TBSTYLE_FLAT,uint32_t dwStyle = WS_CHILD | WS_VISIBLE | CBRS_ALIGN_TOP);

   template < class TOOLBAR >
   bool LoadToolBar(id idToolBar,const char * pszToolBar,uint32_t dwCtrlStyle = TBSTYLE_FLAT,uint32_t dwStyle = WS_CHILD | WS_VISIBLE | CBRS_ALIGN_TOP);

   virtual bool LoadToolBar(id idToolBar,const char * pszToolBar,uint32_t dwCtrlStyle = TBSTYLE_FLAT,uint32_t dwStyle = WS_CHILD | WS_VISIBLE | CBRS_ALIGN_TOP) override
   {
      return LoadToolBar < simple_toolbar >(idToolBar,pszToolBar,dwCtrlStyle,dwStyle);
   }


   virtual void InitialFramePosition(bool bForceRestore = false) override;

   sp(::user::interaction) WindowDataGetWnd();
   virtual void on_layout() override;
   virtual void ActivateFrame(int32_t nCmdShow = -1) override;
   virtual bool on_create_client(::user::create_struct * lpcs, ::create * pcreate) override;
   virtual bool pre_create_window(::user::create_struct& cs) override;
   virtual void pre_translate_message(::message::message * pobj) override;

   virtual void _000OnDraw(::draw2d::graphics * pgraphics) override;
   virtual void draw_frame_and_control_box_over(::draw2d::graphics * pgraphics);

   virtual void _001OnDraw(::draw2d::graphics * pgraphics) override;
   virtual void draw_frame(::draw2d::graphics * pgraphics);


   virtual void _001OnClip(::draw2d::graphics * pgraphics) override;



   virtual bool _001CanEnterScreenSaver();

   DECL_GEN_SIGNAL(_001OnCreate);
   DECL_GEN_SIGNAL(_001OnDdeInitiate);
   DECL_GEN_SIGNAL(_001OnDestroy);
   DECL_GEN_SIGNAL(_001OnSize);
   DECL_GEN_SIGNAL(_001OnMove);
   DECL_GEN_SIGNAL(_001OnClose);
   DECL_GEN_SIGNAL(_001OnShowWindow);
   DECL_GEN_SIGNAL(_001OnSysCommand);
   DECL_GEN_SIGNAL(_001OnViewFullScreen);
   DECL_GEN_SIGNAL(_001OnMouseMove);
   DECL_GEN_SIGNAL(_001OnUpdateViewFullScreen);
   DECL_GEN_SIGNAL(_001OnToggleCustomFrame);
   DECL_GEN_SIGNAL(_001OnUpdateToggleCustomFrame);
   DECL_GEN_SIGNAL(_001OnToggleTransparentFrame);
   DECL_GEN_SIGNAL(_001OnUpdateToggleTransparentFrame);
   DECL_GEN_SIGNAL(_001OnGetMinMaxInfo);
   DECL_GEN_SIGNAL(_001OnAppExit);
   DECL_GEN_SIGNAL(_001OnNotifyIconTopic);


#ifdef WINDOWSEX
   void OnNcCalcSize(bool bCalcValidRects, NCCALCSIZE_PARAMS FAR* lpncsp);
#endif

   // persistent frame implemenation using updowntarget

   virtual bool WndFrameworkDownUpGetUpEnable() override;
   virtual bool WndFrameworkDownUpGetDownEnable() override;

   using ::user::wndfrm::frame::WorkSetListener::attach;
   DECL_GEN_SIGNAL(guserbaseOnInitialUpdate);
   DECL_GEN_SIGNAL(_001OnDwm);
   DECL_GEN_SIGNAL(_001OnNcCalcSize);


   virtual class mini_dock_frame_window* CreateFloatingFrame(uint32_t dwStyle);
   virtual void NotifyFloatingWindows(uint32_t dwFlags) override;


   virtual void WfiOnDown() override;
   virtual void WfiOnUp() override;

   virtual bool WfiIsMoving() override;
   virtual bool WfiIsSizing() override;

   virtual bool calc_layered() override;


   virtual string get_window_default_matter() override;


   virtual void assert_valid() const override;
   virtual void dump(dump_context & dumpcontext) const override;


   void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
   void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
   virtual void on_simple_command(::message::simple_command * psimplecommand) override;

#ifdef WINDOWSEX
   virtual void OnDropFiles(HDROP hDropInfo);
   virtual bool OnQueryEndSession();
   virtual void OnEndSession(bool bEnding);
#endif


   LRESULT OnDDEInitiate(WPARAM wParam, LPARAM lParam) override;
   LRESULT OnDDEExecute(WPARAM wParam, LPARAM lParam) override;
   LRESULT OnDDETerminate(WPARAM wParam, LPARAM lParam) override;

   void _001OnQueryEndSession(::message::message * pobj);

   virtual void on_control_event(::user::control_event * pevent) override;

   virtual bool WfiOnMove(bool bTracking) override;
   virtual bool WfiOnSize(bool bTracking) override;

   virtual void WfiOnClose() override;
   virtual void WfiOnMaximize() override;
   virtual void WfiOnMinimize(bool bNoActivate) override;
   virtual void WfiOnRestore() override;
   virtual void WfiOnDock(::user::e_appearance eappearance) override;

   virtual bool DeferFullScreen(bool bFullScreen, bool bRestore);

   virtual void route_command_message(::user::command * pcommand) override;

   virtual void data_on_after_change(::message::message * pobj);



   virtual bool set_appearance(::user::e_appearance eappearance) override;

   virtual void InitialUpdateFrame(::user::document * pDoc,bool bMakeVisible) override;

   virtual void _001OnTimer(::timer * ptimer) override;

   virtual bool WfiToggleTransparentFrame() override;


   virtual bool frame_is_transparent() override;


   virtual void OnNotifyIconContextMenu(UINT uiNotifyIcon) override;
   virtual void OnNotifyIconLButtonDblClk(UINT uiNotifyIcon) override;
   virtual void OnNotifyIconLButtonDown(UINT uiNotifyIcon) override;


   virtual void OnInitialFrameUpdate(bool bMakeVisible) override;

   virtual void OnUpdateToolWindow(bool bVisible);

   virtual void show_task(bool bShow);

   virtual void defer_set_icon();

   using ::user::frame_window::get_color;

   virtual void on_select_user_style();

   virtual void notification_area_action(const char * pszId) override;

   virtual string notification_area_extra_get_xml_menu();

   virtual void nextstyle(::user::style_context * pcontext) override;

};





class CLASS_DECL_CORE prodevian_translucent_simple_frame_window :
   virtual public simple_frame_window
{
public:


   prodevian_translucent_simple_frame_window(::aura::application * papp);
   virtual ~prodevian_translucent_simple_frame_window();


};




