#pragma once


#include "user_interaction_base.h"


namespace user
{


   class CLASS_DECL_AURA interaction_impl_base:
      virtual public ::user::interaction_base,
      virtual public ::aura::timer_array
   {
   public:


      rect64                              m_rectParentClientRequest;
      bool                                m_bShowFlags;
      int                                 m_iShowFlags;
      bool                                m_bShowWindow;
      int                                 m_iShowWindow;
      bool                                m_bZ;
      int_ptr                             m_iZ;

      rect64                              m_rectParentClient;
      ::user::interaction *               m_pui;
      bool                                m_bIgnoreSizeEvent;
      bool                                m_bIgnoreMoveEvent;
      ap(critical_section)                m_pcsDisplay;

      mutex                               m_mutexLongPtr;
      int_ptr_to_int_ptr                  m_longptr;

      bool                                m_bPendingRedraw;
      uint32_t                            m_uiLastRedraw;



      interaction_impl_base();
      virtual ~interaction_impl_base();

      inline critical_section * cs_display() { return m_pcsDisplay; }
      virtual ::user::interaction_impl * get_user_interaction_impl();
      virtual ::user::interaction_child * get_user_interaction_child();


      virtual void prio_install_message_routing(::message::sender * pinterface);
      virtual void last_install_message_routing(::message::sender * pinterface);


      virtual void queue_message_handler(::message::base * pbase);


      virtual bool check_need_layout();
      virtual void clear_need_layout();
      virtual void set_need_layout();
      virtual void on_layout() override;

      virtual bool check_need_translation();
      virtual void clear_need_translation();
      virtual void on_translate() override;

      virtual bool check_show_flags();
      virtual void clear_show_flags();
      virtual void on_do_show_flags() override;

      virtual bool check_need_zorder();
      virtual void clear_need_zorder();
      virtual void on_zorder();


      virtual bool has_pending_redraw_flags() override;


//      virtual void _001UpdateScreen(bool bUpdateBuffer = true);
//      virtual void _001UpdateBuffer();
      virtual bool create_message_queue(::user::interaction * pui, const char * pszName);
      virtual bool create_window(::user::interaction * pui, const RECT & rect, ::user::interaction *pparent, id id);
      virtual bool create_window(::user::interaction * pui, const char * lpszClassName, const char * lpszWindowName, uint32_t dwStyle, const RECT & rect, ::user::interaction * pParentWnd, id id, ::create * pcreate = NULL);
      virtual bool create_window_ex(::user::interaction * pui, ::user::create_struct & cs, ::user::interaction * puiParent = NULL, id id = ::id());


      virtual void _001WindowMinimize(bool bNoActivate) override;
      virtual void _001WindowMaximize() override;
      virtual void _001WindowFullScreen() override;
      virtual void _001WindowRestore() override;
      virtual void _001WindowDock(::user::e_appearance eappearance);

      virtual void RepositionBars(UINT nIDFirst,UINT nIDLast,id nIdLeftOver,UINT nFlags,LPRECT lpRectParam,LPCRECT lpRectClient,bool bStretch) override;

      virtual bool GetClientRect(LPRECT lprect) override;
      virtual bool GetClientRect(RECT64 * lprect) override;
      virtual bool GetWindowRect(LPRECT lprect) override;
      virtual bool GetWindowRect(RECT64 * lprect) override;
      //virtual bool ClientToScreen(LPRECTD lprect) override;
      //virtual bool ClientToScreen(LPRECT lprect) override;
      //virtual bool ClientToScreen(RECT64 * lprect) override;
      //virtual bool ClientToScreen(LPPOINTD lppoint) override;
      //virtual bool ClientToScreen(LPPOINT lppoint) override;
      //virtual bool ClientToScreen(POINT64 * lppoint) override;
      //virtual bool ScreenToClient(LPRECTD lprect) override;
      //virtual bool ScreenToClient(LPRECT lprect) override;
      //virtual bool ScreenToClient(RECT64 * lprect) override;
      //virtual bool ScreenToClient(LPPOINTD lppoint) override;
      //virtual bool ScreenToClient(LPPOINT lppoint) override;
      //virtual bool ScreenToClient(POINT64 * lprect) override;
      virtual rect GetWindowRect() override;
      virtual rect64 GetWindowRect64() override;
      virtual bool SetPlacement(const RECT & rect,UINT nFlags = SWP_SHOWWINDOW) override;
      virtual bool RepositionWindow(const RECT & rect,UINT nFlags = SWP_SHOWWINDOW) override;
      virtual bool RepositionWindow(int32_t x,int32_t y,int32_t cx,int32_t cy,UINT nFlags = SWP_SHOWWINDOW) override;
      virtual bool MoveWindow(int32_t x,int32_t y,UINT nFlags = SWP_SHOWWINDOW) override;
      virtual bool MoveWindow(POINT pt,UINT nFlags = SWP_SHOWWINDOW) override;
      virtual bool SizeWindow(int32_t x,int32_t y,UINT nFlags = SWP_SHOWWINDOW) override;
      virtual bool SizeWindow(SIZE sz,UINT nFlags = SWP_SHOWWINDOW) override;
      virtual bool ResizeWindow(int32_t cx,int32_t cy,UINT nFlags = SWP_SHOWWINDOW) override;
      virtual bool ResizeWindow(SIZE sz,UINT nFlags = SWP_SHOWWINDOW) override;
      virtual bool SetWindowPos(int_ptr z,const RECT & rect,UINT nFlags = SWP_SHOWWINDOW) override;
      virtual bool SetWindowPos(int_ptr z,int32_t x,int32_t y,int32_t cx,int32_t cy,UINT nFlags = SWP_SHOWWINDOW) override;
      virtual bool defer_set_window_pos(int_ptr z, const RECT & rect, UINT nFlags) override; // only set_windows_pos if get_parent()->ScreenToClient(get_window_rect) different of rect(x, y, cx, cy)      virtual bool set_placement(LPRECT lprect);
      virtual bool defer_set_window_pos(int_ptr z,int32_t x,int32_t y,int32_t cx,int32_t cy,UINT nFlags) override; // only set_windows_pos if get_parent()->ScreenToClient(get_window_rect) different of rect(x, y, cx, cy)      virtual bool set_placement(LPRECT lprect);
      //virtual int32_t SetWindowRgn(HRGN hRgn,bool bRedraw);
      //virtual int32_t GetWindowRgn(HRGN hRgn);


#ifdef WINDOWS

      virtual bool RedrawWindow(LPCRECT lpRectUpdate = NULL,::draw2d::region* prgnUpdate = NULL,UINT flags = RDW_INVALIDATE | RDW_ERASE) override;

#else

      virtual bool RedrawWindow(LPCRECT lpRectUpdate = NULL,::draw2d::region* prgnUpdate = NULL,UINT flags = 0) override;

#endif




      virtual void _001Print(::draw2d::graphics * pgraphics) override;
      virtual void _000OnDraw(::draw2d::graphics * pgraphics) override;
      virtual void _001DrawThis(::draw2d::graphics * pgraphics) override;
      virtual void _001DrawChildren(::draw2d::graphics * pgraphics) override;
      virtual void _001OnDraw(::draw2d::graphics * pgraphics) override;
      virtual void draw_control_background(::draw2d::graphics * pgraphics) override;


      virtual ::user::interaction * get_wnd() const override;


      virtual void set_viewport_org(::draw2d::graphics * pgraphics) override;

      virtual void viewport_screen_to_client(POINT * ppt) override;
      virtual void viewport_client_to_screen(POINT * ppt) override;
      virtual void viewport_client_to_screen(RECT * ppt) override;
      virtual void viewport_screen_to_client(RECT * ppt) override;




      virtual uint32_t GetStyle() const override;
      virtual uint32_t GetExStyle() const override;
      virtual bool ModifyStyle(uint32_t dwRemove,uint32_t dwAdd,UINT nFlags = 0) override;
      virtual bool ModifyStyleEx(uint32_t dwRemove,uint32_t dwAdd,UINT nFlags = 0) override;

      virtual LONG get_window_long(int32_t nIndex) const override;
      virtual LONG set_window_long(int32_t nIndex,LONG lValue) override;

      virtual LONG_PTR get_window_long_ptr(int32_t nIndex) const override;
      virtual LONG_PTR set_window_long_ptr(int32_t nIndex,LONG_PTR lValue) override;

      virtual id GetDlgCtrlId() const override;
      virtual id SetDlgCtrlId(::id id) override;

      virtual ::user::interaction * first_child() override;
      virtual ::user::interaction * top_child() override;
      virtual ::user::interaction * under_sibling() override;
      virtual ::user::interaction * above_sibling() override;

      virtual ::user::interaction * above_sibling(::user::interaction * pui) override;
      virtual ::user::interaction * under_sibling(::user::interaction * pui) override;


      virtual UINT ArrangeIconicWindows();
      virtual void BringToTop(int nCmdShow) override;
      virtual bool BringWindowToTop() override;


      virtual bool IsAscendant(const ::user::interaction * puiIsAscendant) const override;
      virtual bool IsParent(const ::user::interaction * puiIsParent) const override;
      virtual bool IsChild(const ::user::interaction * puiIsChild) const override;
      virtual bool IsDescendant(const ::user::interaction * puiIsDescendant) const override;


//      virtual ::user::interaction * get_wnd() const;
      virtual ::user::interaction * get_wnd(UINT nCmd) const override;


      virtual ::user::interaction * GetTopWindow() const override;
      virtual ::user::interaction * GetParent() const override;
      virtual ::user::interaction * GetTopLevel() const override;
      virtual ::user::interaction * GetParentTopLevel() const override;
      virtual ::user::interaction * EnsureTopLevel() override;
      virtual ::user::interaction * EnsureParentTopLevel() override;
      virtual ::user::interaction * GetOwner() const override;
      virtual ::user::interaction * GetParentOwner() const override;
      virtual ::user::interaction * GetParentOrOwner() const override;
      virtual ::user::interaction * GetTopLevelOwner() const override;
      virtual ::user::frame * GetFrame() const override;
      virtual ::user::frame * GetParentFrame() const override;
      virtual ::user::frame * GetTopLevelFrame() const override;
      virtual ::user::frame * GetParentTopLevelFrame() const override;
      virtual ::user::frame * EnsureParentFrame() override;


      virtual LRESULT message_call(UINT uiMessage, WPARAM wparam, lparam lparam) override;


      virtual void send_message_to_descendants(UINT message,WPARAM wParam = 0,lparam lParam = 0,bool bDeep = TRUE,bool bOnlyPerm = FALSE) override;


      virtual void pre_translate_message(::message::message * pobj) override;


      virtual bool SetCapture(::user::interaction * pui = NULL) override;
      virtual bool ReleaseCapture() override;
      virtual ::user::interaction * GetCapture() override;


      virtual bool SetFocus() override;


      virtual bool get_rect_normal(LPRECT lprect);

      virtual bool SetTimer(uint_ptr nIDEvent,UINT nElapse, PFN_TIMER pfnTimer) override;
      virtual bool KillTimer(uint_ptr nIDEvent) override;

      virtual void _001OnTimer(::timer * ptimer) override;

      virtual bool DestroyWindow() override;


      virtual void prodevian_task();


      void mouse_hover_add(::user::interaction * pinterface) override;
      void mouse_hover_remove(::user::interaction * pinterface) override;


      virtual void register_drop_target();


      virtual ::user::elemental * get_focus_elemental();
      virtual bool set_focus_elemental(::user::elemental * pelemental);


      virtual void PostNcDestroy() override;

      virtual bool ShowWindow(int32_t nCmdShow) override;

      DECL_GEN_SIGNAL(_001OnShowWindow);
      DECL_GEN_SIGNAL(_001OnDestroyWindow);

      virtual void show_task(bool bShow);

      virtual void redraw_add(::object * p);
      virtual void redraw_remove(::object * p);
      virtual bool has_redraw();

      virtual void show_software_keyboard(bool bShow, string str, strsize iBeg, strsize iEnd);

   };


} // namespace user



















