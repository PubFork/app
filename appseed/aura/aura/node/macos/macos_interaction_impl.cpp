#include "framework.h"


void deactivate_window(oswindow window);


struct __CTLCOLOR
{

   oswindow hWnd;
   HDC hDC;
   UINT nCtlType;

};


WINBOOL PeekMessage(LPMESSAGE lpMsg, oswindow hWnd, UINT wMsgFilterMin, UINT wMsgFilterMax, UINT wRemoveMsg);

WINBOOL GetMessage(LPMESSAGE lpMsg, oswindow hWnd, UINT wMsgFilterMin, UINT wMsgFilterMax);


namespace macos
{

   class round_window_draw_life_time
   {
   public:


      interaction_impl * m_pimpl;

      round_window_draw_life_time(interaction_impl * pimpl) :
         m_pimpl(pimpl)
      {

         m_pimpl->m_uiLastUpdateBeg = get_nanos();

      }

      ~round_window_draw_life_time()
      {

         m_pimpl->m_uiLastUpdateEnd = get_nanos();

      }

   };


   interaction_impl::interaction_impl():
      ::aura::timer_array(get_app())
   {

      m_bEnabled = true;
      set_handle(NULL);

   }


   void interaction_impl::construct(oswindow hWnd)
   {

      set_handle(hWnd);

   }


   interaction_impl::interaction_impl(::aura::application * papp) :
      ::object(papp),
      ::aura::timer_array(papp)
   {

      m_bEnabled = true;
      set_handle(NULL);

   }


   interaction_impl::~interaction_impl()
   {

   }


   void interaction_impl::round_window_add_ref()
   {

      add_ref();

      m_pui->add_ref();

   }


   void interaction_impl::round_window_dec_ref()
   {

      m_pui->dec_ref();

      dec_ref();

   }


   CLASS_DECL_AURA void hook_window_create(::user::interaction * pWnd);

   CLASS_DECL_AURA bool unhook_window_create();

   void CLASS_DECL_AURA __pre_init_dialog(::user::interaction * pWnd, LPRECT lpRectOld, DWORD* pdwStyleOld);

   void CLASS_DECL_AURA __post_init_dialog(::user::interaction * pWnd, const RECT& rectOld, DWORD dwStyleOld);

   LRESULT CALLBACK __activation_window_procedure(oswindow hWnd, UINT nMsg, WPARAM wparam, LPARAM lparam);


   ::user::interaction_impl * interaction_impl::from_os_data(void * pdata)
   {

      return from_handle((oswindow)pdata);

   }


   void * interaction_impl::get_os_data() const
   {

      return ((oswindow &)m_oswindow);

   }


   bool interaction_impl::ModifyStyle(oswindow hWnd, DWORD dwRemove, DWORD dwAdd, UINT nFlags)
   {

      if (!::is_window(hWnd))
         return false;

      DWORD_PTR dw = hWnd->get_window_long_ptr(GWL_STYLE);

      dw &= ~dwRemove;

      dw |= dwAdd;

      hWnd->set_window_long_ptr(GWL_STYLE, dw);

      return true;

   }


   bool interaction_impl::ModifyStyleEx(oswindow hWnd, DWORD dwRemove, DWORD dwAdd, UINT nFlags)
   {

      if (!::is_window(hWnd))
      {

         return false;

      }

      DWORD_PTR dw = hWnd->get_window_long_ptr(GWL_EXSTYLE);

      dw &= ~dwRemove;

      dw |= dwAdd;

      hWnd->set_window_long_ptr(GWL_EXSTYLE, dw);

      return true;

   }


   const MESSAGE * PASCAL interaction_impl::GetCurrentMessage()
   {

      return NULL;

   }


   LRESULT interaction_impl::Default()
   {

      return 0;

   }


   ::user::interaction_impl * interaction_impl::from_handle(oswindow oswindow)
   {

      if (oswindow == NULL)
      {

         return NULL;

      }

      return oswindow->m_pimpl;

   }


   ::user::interaction_impl * interaction_impl::FromHandlePermanent(oswindow oswindow)
   {

      if (oswindow == NULL)
      {

         return NULL;

      }

      return oswindow->m_pimpl;

   }


   bool interaction_impl::Attach(oswindow hWndNew)
   {

      ASSERT(get_handle() == NULL);     // only attach once, detach on destroy
      //  ASSERT(FromHandlePermanent(hWndNew) == NULL);
      // must not already be in permanent ::collection::map

      if (hWndNew == NULL)
      {

         return FALSE;

      }

      //single_lock sl(afxMutexHwnd(), TRUE);
      //hwnd_map * pMap = afxMapHWND(TRUE); // create ::collection::map if not exist
      //ASSERT(pMap != NULL);

      //pMap->set_permanent(set_handle(hWndNew), this);
      //if(m_pui == NULL)
      {
         //m_pui = this;
      }

      m_oswindow = hWndNew;

      return TRUE;

   }

   oswindow interaction_impl::Detach()
   {
      oswindow hWnd = (oswindow)get_handle();
      if (hWnd != NULL)
      {
         //         single_lock sl(afxMutexHwnd(), TRUE);
         //  ;;       hwnd_map * pMap = afxMapHWND(); // don't create if not exist
         //     if (pMap != NULL)
         //      pMap->remove_handle(get_handle());
         //         set_handle(NULL);
         m_oswindow = NULL;
      }

      return hWnd;
   }

   void interaction_impl::pre_subclass_window()
   {
      // no default processing
   }


   bool interaction_impl::create_window_ex(::user::interaction * pui, ::user::create_struct & cs, ::user::interaction *  pParentWnd, id id)
   {

      if (!native_create_window_ex(pui, cs,
                                   pParentWnd == NULL ? NULL : pParentWnd->get_safe_handle(), id))
      {

         return false;

      }

      return true;

   }


   bool interaction_impl::native_create_window_ex(
   ::user::interaction * pui,
   ::user::create_struct & cs,
   oswindow hWndParent,
   id id)
   {

      if (::is_window(get_handle()))
      {

         DestroyWindow();

      }

      m_pui = pui;

      //      ASSERT(lpszClassName == NULL || __is_valid_string(lpszClassName) ||
      //       __is_valid_atom(lpszClassName));
      ENSURE_ARG(cs.lpszName == NULL || __is_valid_string(cs.lpszName));

      // allow modification of several common create parameters
      //::user::create_struct cs;
      //      cs.hwndParent = hWndParent;
      //   cs.hMenu = hWndParent == NULL ? NULL : nIDorHMenu;
      cs.hMenu = NULL;
      //      cs.hInstance = System.m_hInstance;
      //cs.lpCreateParams = lpParam;

      install_message_routing(this);

      hook_window_create(m_pui);

      CGRect rect;

      RECT rectParam;

      rectParam.left = cs.x;
      rectParam.top = cs.y;
      rectParam.right = cs.x + cs.cx;
      rectParam.bottom = cs.y + cs.cy;

      copy(rect, rectParam);

      if (hWndParent == MESSAGE_WINDOW_PARENT)
      {

         return true;

      }
      else
      {

         m_oswindow = oswindow_get(new_round_window(this, rect));

         m_pui->m_pthread = ::get_thread();

         ::copy(&m_rectParentClient, &rectParam);

         m_spgraphics.alloc(allocer());

         m_spgraphics->on_create_window(this);

         m_oswindow->set_user_interaction_impl(this);

         oswindow_assign(m_oswindow, this);

         if(cs.style & WS_VISIBLE)
         {

            ShowWindow(SW_SHOW);

         }
         else
         {

            ShowWindow(SW_HIDE);

         }

      }

      LRESULT lresult = send_message(WM_CREATE, 0, (LPARAM)&cs);

      bool bOk = true;

      if (!unhook_window_create() || lresult == -1)
      {

         bOk = false;

         threadrefa_post_quit();

         threadrefa_wait(one_minute());

         PostNcDestroy();        // cleanup if CreateWindowEx fails too soon

      }

      m_pui->set_need_layout();

      m_pui->add_ref();

      return bOk;

   }


   // for child windows
   bool interaction_impl::pre_create_window(::user::create_struct& cs)
   {
      /*      if (cs.lpszClass == NULL)
       {
       // make sure the default user::interaction class is registered
       VERIFY(__end_defer_register_class(__WND_REG, &cs.lpszClass));

       // no WNDCLASS provided - use child user::interaction default
       ASSERT(cs.style & WS_CHILD);
       }*/
      return true;
   }


   bool interaction_impl::create_window(::user::interaction * pui, const char * lpszClassName,const char * lpszWindowName,uint32_t dwStyle,const RECT & rect,::user::interaction * pParentWnd,id id, ::create * pcreate)
   {
      // can't use for desktop or pop-up windows (use CreateEx instead)

      ASSERT(pParentWnd != NULL);

      ::user::create_struct cs(0, lpszClassName, lpszWindowName,dwStyle, rect, pcreate);

      cs.hwndParent = pParentWnd->get_safe_handle();
      ASSERT((cs.style & WS_POPUP) == 0);

      return create_window_ex(pui, cs, pParentWnd, id);

   }


   bool interaction_impl::create_message_queue(::user::interaction * pui, const char * pszName)
   {

      if (is_window(get_handle()))
      {

         set_window_text(pszName);

      }
      else
      {

         ::user::create_struct cs(0, NULL, pszName, WS_CHILD, null_rect());

         if (!native_create_window_ex(pui, cs, MESSAGE_WINDOW_PARENT, "message_queue"))
         {

            return false;

         }

      }

      return true;

   }


   void interaction_impl::install_message_routing(::message::sender * pinterface)
   {

      last_install_message_routing(pinterface);
      ::user::interaction_impl::install_message_routing(pinterface);

      IGUI_MSG_LINK(WM_NCDESTROY, pinterface, this, &interaction_impl::_001OnNcDestroy);
      if (!m_pui->m_bMessageWindow)
      {
         IGUI_MSG_LINK(WM_PAINT, pinterface, this, &interaction_impl::_001OnPaint);
         IGUI_MSG_LINK(WM_PRINT, pinterface, this, &interaction_impl::_001OnPrint);
      }
      m_pui->install_message_routing(pinterface);
      IGUI_MSG_LINK(WM_CREATE, pinterface, this, &interaction_impl::_001OnCreate);
      if (!m_pui->m_bMessageWindow)
      {
         IGUI_MSG_LINK(WM_SETCURSOR, pinterface, this, &interaction_impl::_001OnSetCursor);
         IGUI_MSG_LINK(WM_ERASEBKGND, pinterface, this, &interaction_impl::_001OnEraseBkgnd);
         //         IGUI_MSG_LINK(WM_NCCALCSIZE,pinterface,this,&interaction_impl::_001OnNcCalcSize);
         IGUI_MSG_LINK(WM_SIZE, pinterface, this, &interaction_impl::_001OnSize);
         //         IGUI_MSG_LINK(WM_WINDOWPOSCHANGING,pinterface,this,&interaction_impl::_001OnWindowPosChanging);
         //         IGUI_MSG_LINK(WM_WINDOWPOSCHANGED,pinterface,this,&interaction_impl::_001OnWindowPosChanged);
         //         IGUI_MSG_LINK(WM_GETMINMAXINFO,pinterface,this,&interaction_impl::_001OnGetMinMaxInfo);
         //         IGUI_MSG_LINK(WM_SETFOCUS,pinterface,this,&interaction_impl::_001OnSetFocus);
         //         IGUI_MSG_LINK(WM_KILLFOCUS,pinterface,this,&interaction_impl::_001OnKillFocus);
         //IGUI_MSG_LINK(ca2m_PRODEVIAN_SYNCH,pinterface,this,&interaction_impl::_001OnProdevianSynch);
         prio_install_message_routing(pinterface);
      }
      IGUI_MSG_LINK(WM_DESTROY, pinterface, this, &interaction_impl::_001OnDestroy);

      //      ::user::interaction_impl::install_message_routing(pinterface);
      //      //m_pbuffer->InstallMessageHandling(pinterface);
      //      IGUI_MSG_LINK(WM_DESTROY           , pinterface, this, &interaction_impl::_001OnDestroy);
      //      IGUI_MSG_LINK(WM_NCDESTROY         , pinterface, this, &interaction_impl::_001OnNcDestroy);
      //      IGUI_MSG_LINK(WM_PAINT             , pinterface, this, &interaction_impl::_001OnPaint);
      //      IGUI_MSG_LINK(WM_PRINT             , pinterface, this, &interaction_impl::_001OnPrint);
      //      if(m_pui != NULL)
      //      {
      //         m_pui->install_message_routing(pinterface);
      //      }
      //      IGUI_MSG_LINK(WM_CREATE            , pinterface, this, &interaction_impl::_001OnCreate);
      //      IGUI_MSG_LINK(WM_SETCURSOR         , pinterface, this, &interaction_impl::_001OnSetCursor);
      //      IGUI_MSG_LINK(WM_ERASEBKGND        , pinterface, this, &interaction_impl::_001OnEraseBkgnd);
      //      IGUI_MSG_LINK(WM_MOVE              , pinterface, this, &interaction_impl::_001OnMove);
      //      IGUI_MSG_LINK(WM_SIZE              , pinterface, this, &interaction_impl::_001OnSize);
      IGUI_MSG_LINK(WM_SHOWWINDOW, pinterface, this, &interaction_impl::_001OnShowWindow);
      //      IGUI_MSG_LINK(ca2m_PRODEVIAN_SYNCH , pinterface, this, &interaction_impl::_001OnProdevianSynch);
      ////      //IGUI_MSG_LINK(WM_TIMER             , pinterface, this, &interaction_impl::_001OnTimer);
   }


   void interaction_impl::_001OnShowWindow(::message::message * pobj)
   {

      UNREFERENCED_PARAMETER(pobj);

//      do_show_flags();
//
//      clear_show_flags();

   }


   void interaction_impl::_001OnMove(::message::message * pobj)
   {

      UNREFERENCED_PARAMETER(pobj);

//      translate();
//
//      clear_need_translation();

   }


   void interaction_impl::_001OnSize(::message::message * pobj)
   {

      UNREFERENCED_PARAMETER(pobj);

      m_pui->layout();

      m_pui->set_need_redraw();

   }


   void interaction_impl::_001OnDestroy(::message::message * pobj)
   {

      UNREFERENCED_PARAMETER(pobj);

      if(GetActiveWindow() == m_pui)
      {

         ::set_active_window(NULL);

      }

      Default();

      round_window_hide();

      delete_all_timers();

//      ::multithreading::post_quit_and_wait(m_pthreadProDevian, seconds(5));
//
//      //for(auto & pthread : m_mapqueue)
//      {
//
//        // ::multithreading::post_quit_and_wait(pthread.element2(), millis(200));
//          ::multithreading::post_quit_and_wait(m_queuethread, millis(5));
//
//      }


   }


   // WM_NCDESTROY is the absolute LAST message sent.
   void interaction_impl::_001OnNcDestroy(::message::message * pobj)
   {

      single_lock sl(m_papp == NULL ? NULL : m_papp->m_pmutex, TRUE);

      pobj->m_bRet = true;

      ::thread* pthread = ::get_thread();

      if (pthread != NULL)
      {

         if (pthread->get_active_ui() == m_pui)
         {

            pthread->set_active_ui(NULL);

         }

      }

      m_bShowFlags = false;

      m_bShowWindow = false;

      ::destroy_window(get_handle());

      Detach();

      ASSERT(get_handle() == NULL);

      PostNcDestroy();

      if (m_pui != NULL)
      {

         m_pui->PostNcDestroy();

         m_pui->release();

      }

   }


   void interaction_impl::PostNcDestroy()
   {

      ::user::interaction_impl::PostNcDestroy();

   }

   void interaction_impl::on_final_release()
   {
      if (get_handle() != NULL)
         DestroyWindow();    // will call PostNcDestroy
      else
         PostNcDestroy();
   }

   void interaction_impl::assert_valid() const
   {
      if (get_handle() == NULL)
         return;     // null (unattached) windows are valid

      // check for special wnd??? values
      //      ASSERT(oswindow_TOP == NULL);       // same as desktop
      /*      if (get_handle() == oswindow_BOTTOM)
       {
       }
       else if (get_handle() == oswindow_TOPMOST)
       {
       }
       else if (get_handle() == oswindow_NOTOPMOST)
       {
       }
       else
       {
       // should be a normal user::interaction
       ASSERT(::is_window(get_handle()));

       // should also be in the permanent or temporary handle ::collection::map
       single_lock sl(afxMutexHwnd(), TRUE);
       hwnd_map * pMap = afxMapHWND();
       if(pMap == NULL) // inside thread not having windows
       return; // let go
       ASSERT(pMap != NULL);

       //         ::ca2::object* p=NULL;
       if(pMap)
       {
       ASSERT( (p = pMap->lookup_permanent(get_handle())) != NULL ||
       (p = pMap->lookup_temporary(get_handle())) != NULL);
       }*/

      //ASSERT(dynamic_cast < ::user::interaction *  > (p) == this);   // must be us

      // Note: if either of the above asserts fire and you are
      // writing a multithreaded application, it is likely that
      // you have passed a C++ object from one thread to another
      // and have used that object in a way that was not intended.
      // (only simple inline wrapper functions should be used)
      //
      // In general, user::interaction objects should be passed by oswindow from
      // one thread to another.  The receiving thread can wrap
      // the oswindow with a user::interaction object by using ::macos::interaction_impl::from_handle.
      //
      // It is dangerous to pass C++ objects from one thread to
      // another, unless the objects are designed to be used in
      // such a manner.
      //      }*/
   }


   void interaction_impl::dump(dump_context & dumpcontext) const
   {
      ::object::dump(dumpcontext);

      dumpcontext << "\nm_hWnd = " << (void *)get_handle();

      /*      if (get_handle() == NULL || get_handle() == oswindow_BOTTOM ||
       get_handle() == oswindow_TOPMOST || get_handle() == oswindow_NOTOPMOST)
       {
       // not a normal user::interaction - nothing more to dump
       return;
       }*/

      /*      if (!::is_window(get_handle()))
       {
       // not a valid user::interaction
       dumpcontext << " (illegal oswindow)";
       return; // don't do anything more
       }*/

      ::user::interaction_impl * pWnd = (::user::interaction_impl *) this;
      if (pWnd != this)
         dumpcontext << " (Detached or temporary user::interaction)";
      else
         dumpcontext << " (permanent user::interaction)";

      // dump out user::interaction specific statistics
      char szBuf[64];
      //      if (!const_cast < user::interaction * > (this)->send_message(WM_QUERYAFXWNDPROC, 0, 0) && pWnd == this)
      //         ((::user::interaction *) this)->get_window_text(szBuf, _countof(szBuf));
      //    else
      //         ::DefWindowProc(get_handle(), WM_GETTEXT, _countof(szBuf), (LPARAM)&szBuf[0]);
      dumpcontext << "\ncaption = \"" << szBuf << "\"";

      //      ::GetClassName(get_handle(), szBuf, _countof(szBuf));
      //    dumpcontext << "\nclass name = \"" << szBuf << "\"";

      rect rect;
      ((::user::interaction_impl *) this)->GetWindowRect(&rect);
      dumpcontext << "\nrect = " << rect;
      dumpcontext << "\nparent ::user::interaction * = " << (void *)((::user::interaction_impl *) this)->GetParent();

      //      dumpcontext << "\nstyle = " << (void *)(dword_ptr)::GetWindowLong(get_handle(), GWL_STYLE);
      //    if (::GetWindowLong(get_handle(), GWL_STYLE) & WS_CHILD)
      //     dumpcontext << "\nid = " << __get_dialog_control_id(get_handle());

      dumpcontext << "\n";
   }


   bool interaction_impl::DestroyWindow()
   {

      return ::user::interaction_impl::DestroyWindow();

   }


   LRESULT interaction_impl::DefWindowProc(UINT nMsg, WPARAM wparam, LPARAM lparam)
   {
      /*  if (m_pfnSuper != NULL)
       return ::CallWindowProc(m_pfnSuper, get_handle(), nMsg, wparam, lparam);

       WNDPROC pfnWndProc;
       if ((pfnWndProc = *GetSuperWndProcAddr()) == NULL)
       return ::DefWindowProc(get_handle(), nMsg, wparam, lparam);
       else
       return ::CallWindowProc(pfnWndProc, get_handle(), nMsg, wparam, lparam);*/

      return 0;
   }

   /*
    WNDPROC* interaction_impl::GetSuperWndProcAddr()
    {
    // Note: it is no longer necessary to override GetSuperWndProcAddr
    //  for each control class with a different WNDCLASS.
    //  This implementation now uses instance data, such that the previous
    //  WNDPROC can be anything.

    return &m_pfnSuper;
    }
    */
   void interaction_impl::pre_translate_message(::message::message * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
      // no default processing
   }


   void interaction_impl::get_window_text(string & str)
   {

      char sz[2048];

      ZERO(sz);

      round_window_get_title(sz, sizeof(sz));

      str = m_strWindowText;

   }


   /*
    int32_t interaction_impl::GetDlgItemText(int32_t nID, string & rString) const
    {
    ASSERT(::is_window(get_handle()));
    rString = "";    // is_empty without deallocating

    oswindow hWnd = ::GetDlgItem(get_handle(), nID);
    if (hWnd != NULL)
    {
    int32_t nLen = ::GetWindowTextLength(hWnd);
    ::GetWindowText(hWnd, rString.GetBufferSetLength(nLen), nLen+1);
    rString.ReleaseBuffer();
    }

    return (int32_t)rString.get_length();
    }
    */

   bool interaction_impl::GetWindowPlacement(WINDOWPLACEMENT* lpwndpl)
   {
      /*    ASSERT(::is_window(get_handle()));
       lpwndpl->length = sizeof(WINDOWPLACEMENT);
       return ::GetWindowPlacement(get_handle(), lpwndpl) != FALSE;*/
      return false;
   }

   bool interaction_impl::SetWindowPlacement(const WINDOWPLACEMENT* lpwndpl)
   {
      /*      ASSERT(::is_window(get_handle()));
       ((WINDOWPLACEMENT*)lpwndpl)->length = sizeof(WINDOWPLACEMENT);
       return ::SetWindowPlacement(get_handle(), lpwndpl) != FALSE;*/
      return false;
   }

   /////////////////////////////////////////////////////////////////////////////
   // user::interaction will delegate owner draw messages to self drawing controls

   // Drawing: for all 4 control types
   // /*   void interaction_impl::OnDrawItem(int32_t /*nIDCtl*/, LPDRAWITEMSTRUCT lpDrawItemStruct)
   // {

   // reflect notification to child user::interaction control
   //  if (ReflectLastMsg(lpDrawItemStruct->hwndItem))
   //   return;     // eat it

   // not handled - do default
   //      Default();
   // }

   // Drawing: for all 4 control types
   //   int32_t interaction_impl::OnCompareItem(int32_t /*nIDCtl*/, LPCOMPAREITEMSTRUCT lpCompareItemStruct)
   // {
   //  // reflect notification to child user::interaction control
   //LRESULT lResult;
   //      if (ReflectLastMsg(lpCompareItemStruct->hwndItem, &lResult))
   //       return (int32_t)lResult;        // eat it

   // not handled - do default
   //  return (int32_t)Default();
   //   }

   // void interaction_impl::OnDeleteItem(int32_t /*nIDCtl*/, LPDELETEITEMSTRUCT lpDeleteItemStruct)
   //{
   // reflect notification to child user::interaction control
   // if (ReflectLastMsg(lpDeleteItemStruct->hwndItem))
   //  return;     // eat it
   // not handled - do default
   //      Default();
   // }

   bool interaction_impl::_EnableToolTips(bool bEnable, UINT nFlag)
   {
      UNREFERENCED_PARAMETER(bEnable);
      UNREFERENCED_PARAMETER(nFlag);
      return FALSE;
   }


   // Measure item implementation relies on unique control/menu IDs
   //   void interaction_impl::OnMeasureItem(int32_t /*nIDCtl*/, LPMEASUREITEMSTRUCT lpMeasureItemStruct)
   /* {
    if (lpMeasureItemStruct->CtlType == ODT_MENU)
    {
    ASSERT(lpMeasureItemStruct->CtlID == 0);
    }
    else
    {
    ::user::interaction * pChild = GetDescendantWindow(lpMeasureItemStruct->CtlID);
    if (pChild != NULL && pChild->SendChildNotifyLastMsg())
    return;     // eaten by child
    }
    // not handled - do default
    Default();
    }*/

   /*   bool interaction_impl::GetWindowInfo(PWINDOWINFO pwi) const
    {
    ASSERT(::is_window((oswindow)get_handle()));
    return ::GetWindowInfo((oswindow)get_handle(), pwi) != FALSE;
    }*/

   /*   ::user::interaction * interaction_impl::GetAncestor(UINT gaFlags) const
    { ASSERT(::is_window((oswindow)get_handle())); return  ::macos::interaction_impl::from_handle(::GetAncestor((oswindow)get_handle(), gaFlags)); }

    */

   /*   bool interaction_impl::GetScrollBarInfo(LONG idObject, PSCROLLBARINFO psbi) const
    {
    ASSERT(::is_window((oswindow)get_handle()));
    ASSERT(psbi != NULL);
    return ::GetScrollBarInfo((oswindow)get_handle(), idObject, psbi) != FALSE;
    }
    */
   /*   bool interaction_impl::GetTitleBarInfo(PTITLEBARINFO pti) const
    {
    ASSERT(::is_window((oswindow)get_handle()));
    ASSERT(pti != NULL);
    return ::GetTitleBarInfo((oswindow)get_handle(), pti) != FALSE;
    }
    */
   /*   bool interaction_impl::AnimateWindow(DWORD dwTime, DWORD dwFlags)
    {
    ASSERT(::is_window((oswindow)get_handle()));
    return ::AnimateWindow((oswindow)get_handle(), dwTime, dwFlags) != FALSE;
    }

    bool interaction_impl::FlashWindowEx(DWORD dwFlags, UINT  uCount, DWORD dwTimeout)
    {
    ASSERT(::is_window((oswindow)get_handle()));
    FLASHWINFO fwi;
    fwi.cbSize = sizeof(fwi);
    fwi.hwnd = (oswindow)get_handle();
    fwi.dwFlags = dwFlags;
    fwi.uCount = uCount;
    fwi.dwTimeout = dwTimeout;

    return ::FlashWindowEx(&fwi) != FALSE;
    }
    */

   /*
    bool interaction_impl::SetLayeredWindowAttributes(COLORREF crKey, BYTE bAlpha, DWORD dwFlags)
    {
    ASSERT(::is_window((oswindow)get_handle()));
    return ::SetLayeredWindowAttributes((oswindow)get_handle(), crKey, bAlpha, dwFlags) != FALSE;
    }

    bool interaction_impl::UpdateLayeredWindow(::draw2d::graphics * pDCDst, POINT *pptDst, SIZE *psize,
    ::draw2d::graphics * pDCSrc, POINT *pptSrc, COLORREF crKey, BLENDFUNCTION *pblend, DWORD dwFlags)
    {
    ASSERT(::is_window((oswindow)get_handle()));
    return ::UpdateLayeredWindow((oswindow)get_handle(), WIN_HDC(pDCDst), pptDst, psize,
    WIN_HDC(pDCSrc), pptSrc, crKey, pblend, dwFlags) != FALSE;
    }

    */
   /*
    bool interaction_impl::GetLayeredWindowAttributes(COLORREF *pcrKey, BYTE *pbAlpha, DWORD *pdwFlags) const
    {
    ASSERT(::is_window((oswindow)get_handle()));
    return ::GetLayeredWindowAttributes((oswindow)get_handle(), pcrKey, pbAlpha, pdwFlags) != FALSE;
    }

    bool interaction_impl::PrintWindow(::draw2d::graphics * pgraphics, UINT nFlags) const
    {
    ASSERT(::is_window((oswindow)get_handle()));
    return ::PrintWindow((oswindow)get_handle(), (HDC)(dynamic_cast<::draw2d_quartz2d::graphics * >(pgraphics))->get_handle(), nFlags) != FALSE;
    }

    */
   LRESULT interaction_impl::OnNTCtlColor(WPARAM wparam, LPARAM lparam)
   {
      return 0;
   }


   void interaction_impl::PrepareForHelp()
   {
      /*if (IsFrameWnd())
       {
       // frame_window windows should be allowed to exit help mode first
       frame_window* pFrameWnd = dynamic_cast < frame_window * >(this);
       pFrameWnd->ExitHelpMode();
       }

       // cancel any tracking modes
       send_message(WM_CANCELMODE);
       send_message_to_descendants(WM_CANCELMODE, 0, 0, TRUE, TRUE);

       // need to use top level parent (for the case where get_handle() is in DLL)
       ::user::interaction * pWnd = EnsureTopLevelParent();
       MAC_WINDOW(pWnd)->send_message(WM_CANCELMODE);
       MAC_WINDOW(pWnd)->send_message_to_descendants(WM_CANCELMODE, 0, 0, TRUE, TRUE);

       // attempt to cancel capture
       oswindow hWndCapture = ::GetCapture();
       if (hWndCapture != NULL)
       ::SendMessage(hWndCapture, WM_CANCELMODE, 0, 0);*/
   }


   /*void interaction_impl::WinHelpInternal(dword_ptr dwData, UINT nCmd)
    {
    UNREFERENCED_PARAMETER(dwData);
    UNREFERENCED_PARAMETER(nCmd);
    _throw(not_implemented(get_app()));

    application* pApp = &System;
    ASSERT_VALID(pApp);
    if (pApp->m_eHelpType == afxHTMLHelp)
    {
    // translate from WinHelp commands and data to to HtmlHelp
    ASSERT((nCmd == HELP_CONTEXT) || (nCmd == HELP_CONTENTS) || (nCmd == HELP_FINDER));
    if (nCmd == HELP_CONTEXT)
    nCmd = HH_HELP_CONTEXT;
    else if (nCmd == HELP_CONTENTS)
    nCmd = HH_DISPLAY_TOC;
    else if (nCmd == HELP_FINDER)
    nCmd = HH_HELP_FINDER;
    HtmlHelp(dwData, nCmd);
    }
    else
    WinHelp(dwData, nCmd);*/
   //}



   void interaction_impl::route_command_message(::user::command * pcommand)
   {

      command_target::route_command_message(pcommand);

      if(pcommand->m_bRet)
      {

         return;

      }

      //      bool b;

      //if(_iguimessageDispatchCommandMessage(pcommand, b))
      // return b;

      command_target * pcmdtarget = dynamic_cast <command_target *> (this);
      return pcmdtarget->command_target::route_command_message(pcommand);
   }


   void interaction_impl::on_control_event(::user::control_event * pevent)
   {
      UNREFERENCED_PARAMETER(pevent);
      return false;
   }

   void interaction_impl::_002OnDraw(::draw2d::dib * pdib)
   {

      //      ::CallWindowProc(*GetSuperWndProcAddr(), get_handle(), WM_PRINT, (WPARAM)((dynamic_cast<::draw2d_quartz2d::graphics * >(pgraphics))->get_handle()), (LPARAM)(PRF_CHILDREN | PRF_CLIENT));

   }


   void interaction_impl::message_handler(::message::base * pbase)
   {

      if (pbase->m_id == WM_SIZE || pbase->m_id == WM_MOVE)
      {

         //         win_update_graqhics();

      }

      if (pbase->m_id == WM_KEYDOWN ||
            pbase->m_id == WM_KEYUP ||
            pbase->m_id == WM_CHAR)
      {

         SCAST_PTR(::message::key, pkey, pbase);

         Session.translate_os_key_message(pkey);

         if (pbase->m_id == WM_KEYDOWN)
         {
            try
            {
               Session.set_key_pressed(pkey->m_ekey, true);
            }
            catch (...)
            {
            }
         }
         else if (pbase->m_id == WM_KEYUP)
         {
            try
            {
               Session.set_key_pressed(pkey->m_ekey, false);
            }
            catch (...)
            {
            }
         }
      }

      if (m_pui != NULL)
      {

         if (m_pui->WfiIsMoving())
         {
            //TRACE("moving: skip pre translate message");
         }
         else if (m_pui->WfiIsSizing())
         {
            //TRACE("sizing: skip pre translate message");
         }
         else
         {

            m_pui->pre_translate_message(pbase);

            if (pbase->m_bRet)
               return;

            pbase->m_uiMessageFlags |= 1;

         }

      }

      if (pbase->m_id == WM_TIMER)
      {
         //         m_papp->m_papp->step_timer();
      }
      else if (pbase->m_id == WM_LBUTTONDOWN)
      {
         //  g_pwndLastLButtonDown = this;
      }
      else if (pbase->m_id == WM_SIZE)
      {
         m_bUpdateGraphics = true;
      }
      /*      else if(pbase->m_id == CA2M_BERGEDGE)
       {
       if(pbase->m_wparam == BERGEDGE_GETAPP)
       {
       ::application ** ppapp= (::application **) pbase->m_lparam;
       *ppapp = get_app();
       pbase->m_bRet = true;
       return;
       }
       }*/
      pbase->set_lresult(0);


      if (pbase->m_id == WM_LBUTTONDOWN ||
            pbase->m_id == WM_LBUTTONUP ||
            pbase->m_id == WM_MBUTTONDOWN ||
            pbase->m_id == WM_MBUTTONUP ||
            pbase->m_id == WM_RBUTTONDOWN ||
            pbase->m_id == WM_RBUTTONUP ||
            pbase->m_id == WM_RBUTTONDBLCLK ||
            pbase->m_id == WM_LBUTTONDBLCLK ||
            pbase->m_id == WM_MOUSEMOVE ||
            pbase->m_id == WM_MOUSEMOVE ||
            pbase->m_id == WM_MOUSEWHEEL)
      {

         if (pbase->m_id == WM_LBUTTONDOWN)
         {

            output_debug_string("\nWM_LBUTTONDOWN");

         }

         ::message::mouse * pmouse = (::message::mouse *) pbase;


         // user presence status activity reporting

         Session.on_ui_mouse_message(pmouse);


         if (m_papp->m_psession != NULL)
         {

            Session.m_ptCursor = pmouse->m_pt;

         }

         if (m_bTranslateMouseMessageCursor)
         {

            rect rect;

            if(!pmouse->m_bTranslated)
            {

               pmouse->m_bTranslated = true;

               if (System.get_monitor_count() > 0)
               {

                  System.get_monitor_rect(0, &rect);

               }
               else
               {

                  if (m_bScreenRelativeMouseMessagePosition)
                  {

                     ::GetWindowRect(get_handle(), &rect);

                  }
                  else
                  {

                     m_pui->GetWindowRect(rect);

                  }

               }

               if (rect.left >= 0)
               {

                  pmouse->m_pt.x += (LONG)rect.left;

               }

               if (rect.top >= 0)
               {

                  pmouse->m_pt.y += (LONG)rect.top;

               }

            }

         }

         if (pbase->m_id == WM_MOUSEMOVE)
         {
            // We are at the message handler procedure.
            // mouse messages originated from message handler and that are mouse move events should end up with the correct cursor.
            // So the procedure starts by setting to the default cursor,
            // what forces, at the end of message processing, setting the bergedge cursor to the default cursor, if no other
            // handler has set it to another one.
            pmouse->m_ecursor = visual::cursor_default;

         }

         _008OnMouse(pmouse);

         return;

      }
      else if (pbase->m_id == WM_KEYDOWN ||
               pbase->m_id == WM_KEYUP ||
               pbase->m_id == WM_CHAR)
      {

         ::message::key * pkey = (::message::key *) pbase;

         ::user::interaction * puiFocus = dynamic_cast <::user::interaction *> (Session.get_keyboard_focus());

         if (puiFocus != NULL
               && puiFocus->IsWindow()
               && puiFocus->GetTopLevel() != NULL)
         {

            puiFocus->send(pkey);

            if (pbase->m_bRet)
            {

               return;

            }

         }
         else if (!pkey->m_bRet)
         {

            if (m_pui != NULL)
            {

               m_pui->_000OnKey(pkey);

               if (pbase->m_bRet)
               {

                  return;

               }

            }

         }

         pbase->set_lresult(DefWindowProc((UINT) pbase->m_id.i64(), pbase->m_wparam, pbase->m_lparam));

         return;

      }

      if (pbase->m_id == ::message::message_event)
      {

         if (m_pui != NULL)
         {

            m_pui->on_control_event((::user::control_event *) pbase->m_lparam.m_lparam);

         }
         else
         {

            on_control_event((::user::control_event *) pbase->m_lparam.m_lparam);

         }

         return;

      }

      //(this->*m_pfnDispatchWindowProc)(pobj);

      route_message(pbase);

      if (pbase->m_bRet)
      {

         return;

      }

      pbase->set_lresult(DefWindowProc((UINT) pbase->m_id.i64(), pbase->m_wparam, pbase->m_lparam));

   }


   bool interaction_impl::IsTopParentActive()
   {

      ASSERT(get_handle() != NULL);

      ASSERT_VALID(this);

      ::user::interaction *pWndTopLevel = EnsureTopLevel();

      return interaction_impl::GetForegroundWindow() == pWndTopLevel->GetLastActivePopup();

   }


   void interaction_impl::ActivateTopParent()
   {
      // special activate logic for floating toolbars and palettes
//      ::user::interaction * pActiveWnd = GetForegroundWindow();
      //      if (pActiveWnd == NULL || !(MAC_WINDOW(pActiveWnd)->get_handle() == get_handle() || ::IsChild(MAC_WINDOW(pActiveWnd)->get_handle(), get_handle())))
      {
         // clicking on floating frame when it does not have
         // focus itself -- activate the toplevel frame instead.
         EnsureTopLevel()->SetForegroundWindow();
      }
   }


   /*

   sp(::user::frame_window) interaction_impl::GetTopLevelFrame()
   {
      if (get_handle() == NULL) // no oswindow attached
         return NULL;

      ASSERT_VALID(this);

      ::user::frame_window* pFrameWnd = NULL;
      if(m_pui != NULL)
         pFrameWnd = dynamic_cast < ::user::frame_window * > (m_pui);
      if (pFrameWnd == NULL || !pFrameWnd->is_frame_window())
         pFrameWnd = GetParentFrame();

      if (pFrameWnd != NULL)
      {
         ::user::frame_window* pTemp;
         while ((pTemp = pFrameWnd->GetParentFrame()) != NULL)
            pFrameWnd = pTemp;
      }
      return pFrameWnd;
   }


    */




   int32_t interaction_impl::message_box(const char * lpszText, const char * lpszCaption, UINT nType)
   {

      string strCaption;

      if (lpszCaption == NULL)
         lpszCaption = Application.m_strAppName;
      else
         lpszCaption = strCaption;

      int32_t nResult = ::MessageBox((oswindow)get_handle(), lpszText, lpszCaption, nType);

      return nResult;

   }


   ::user::interaction *  PASCAL interaction_impl::GetDescendantWindow(::user::interaction *  hWnd, id id)
   {
      single_lock sl(hWnd->m_papp->m_pmutex, TRUE);
      // GetDlgItem recursive (return first found)
      // breadth-first for 1 level, then depth-first for next level

      // use GetDlgItem since it is a fast USER function
//      ::user::interaction * pWndChild;
      /*      if ((pWndChild = hWnd->GetDlgItem(id)) != NULL)
       {
       if (pWndChild->GetTopWindow() != NULL)
       {
       // children with the same ID as their parent have priority
       pWndChild = GetDescendantWindow(pWndChild, id);
       if (pWndChild != NULL)
       return pWndChild;
       }
       if (pWndChild != NULL)
       return pWndChild;
       }*/

      for (int32_t i = 0; i < hWnd->m_uiptraChild.get_count(); i++)
      {
         if (hWnd->m_uiptraChild[i]->GetDlgCtrlId() == id)
         {
            if (hWnd->m_uiptraChild[i]->GetDescendantWindow(id))
               return hWnd->m_uiptraChild[i]->GetDescendantWindow(id);
            else
               return hWnd->m_uiptraChild[i];
         }
      }
      //
      //      if(pWndChild == NULL)
      //         return NULL;
      //
      //      // walk each child
      //      for (pWndChild = pWndChild->GetTopWindow(); pWndChild != NULL;
      //           pWndChild = pWndChild->GetNextWindow(GW_HWNDNEXT))
      //      {
      //         pWndChild = GetDescendantWindow(pWndChild, id);
      //         if (pWndChild != NULL)
      //            return pWndChild;
      //      }
      return NULL;    // not found
   }

   void PASCAL interaction_impl::send_message_to_descendants(void * hWnd, UINT message,
         WPARAM wparam, lparam lparam, bool bDeep, bool bOnlyPerm)
   {
      // walk through oswindows to avoid creating temporary user::interaction objects
      // unless we need to call this function recursively
      /*for (oswindow hWndChild = ::GetTopWindow(hWnd); hWndChild != NULL;
       hWndChild = ::GetNextWindow(hWndChild, GW_HWNDNEXT))*/
      {
         // if bOnlyPerm is TRUE, don't m_pui->send to non-permanent windows
         /*if (bOnlyPerm)
          {
          ::user::interaction * pWnd = ::macos::interaction_impl::FromHandlePermanent(hWndChild);
          if (pWnd != NULL)
          {
          // call user::interaction proc directly since it is a C++ user::interaction
          __call_window_procedure(dynamic_cast < ::user::interaction * > (pWnd), MAC_WINDOW(pWnd)->get_handle(), message, wparam, lparam);
          }
          }
          else
          {
          try
          {
          // m_pui->send message with oswindows SendMessage API
          ::SendMessage(hWndChild, message, wparam, lparam);
          }
          catch(...)
          {
          }
          }
          if (bDeep && ::GetTopWindow(hWndChild) != NULL)
          {
          // m_pui->send to child windows after parent
          try
          {
          send_message_to_descendants(hWndChild, message, wparam, lparam,
          bDeep, bOnlyPerm);
          }
          catch(...)
          {
          }
          } */
      }

   }

   /////////////////////////////////////////////////////////////////////////////
   // Scroll bar helpers
   //  hook for user::interaction functions
   //    only works for derived class (eg: ::view) that override 'GetScrollBarCtrl'
   // if the user::interaction doesn't have a _visible_ windows scrollbar - then
   //   look for a sibling with the appropriate ID

//   CScrollBar* interaction_impl::GetScrollBarCtrl(int32_t) const
   // {
   //  return NULL;        // no special scrollers supported
   // }

   int32_t interaction_impl::SetScrollPos(int32_t nBar, int32_t nPos, bool bRedraw)
   {
      //      return ::SetScrollPos(get_handle(), nBar, nPos, bRedraw);
      return 0;
   }

   int32_t interaction_impl::GetScrollPos(int32_t nBar) const
   {
      //return ::GetScrollPos(get_handle(), nBar);
      return 0;
   }

   void interaction_impl::SetScrollRange(int32_t nBar, int32_t nMinPos, int32_t nMaxPos, bool bRedraw)
   {
      //::SetScrollRange(get_handle(), nBar, nMinPos, nMaxPos, bRedraw);
   }

   void interaction_impl::GetScrollRange(int32_t nBar, LPINT lpMinPos, LPINT lpMaxPos) const
   {
      //::GetScrollRange(get_handle(), nBar, lpMinPos, lpMaxPos);
   }

   // Turn on/off non-control scrollbars
   //   for WS_?SCROLL scrollbars - show/hide them
   //   for control scrollbar - enable/disable them
   void interaction_impl::EnableScrollBarCtrl(int32_t nBar, bool bEnable)
   {
      // WS_?SCROLL scrollbar - show or hide
      ShowScrollBar(nBar, bEnable);
   }

   /*
    bool interaction_impl::SetScrollInfo(int32_t nBar, LPSCROLLINFO lpScrollInfo, bool bRedraw)
    {
    ASSERT(lpScrollInfo != NULL);

    oswindow hWnd = get_handle();
    lpScrollInfo->cbSize = sizeof(*lpScrollInfo);
    ::SetScrollInfo(hWnd, nBar, lpScrollInfo, bRedraw);
    return true;
    }

    bool interaction_impl::GetScrollInfo(int32_t nBar, LPSCROLLINFO lpScrollInfo, UINT nMask)
    {
    UNREFERENCED_PARAMETER(nMask);
    ASSERT(lpScrollInfo != NULL);

    oswindow hWnd = get_handle();
    return ::GetScrollInfo(hWnd, nBar, lpScrollInfo) != FALSE;
    }
    */


   int32_t interaction_impl::GetScrollLimit(int32_t nBar)
   {

      int32_t nMin = 0, nMax = 0;

      GetScrollRange(nBar, &nMin, &nMax);

      return nMax;

   }


   void interaction_impl::ScrollWindow(int32_t xAmount, int32_t yAmount,
                                       LPCRECT lpRect, LPCRECT lpClipRect)
   {

   }


   void interaction_impl::CalcWindowRect(LPRECT lpClientRect, UINT nAdjustType)
   {

   }

   bool interaction_impl::HandleFloatingSysCommand(UINT nID, LPARAM lparam)
   {
      /*      ::user::interaction* pParent = GetTopLevelParent();
       switch (nID & 0xfff0)
       {
       case SC_PREVWINDOW:
       case SC_NEXTWINDOW:
       if (LOWORD(lparam) == VK_F6 && pParent != NULL)
       {
       pParent->SetFocus();
       return true;
       }
       break;

       case SC_CLOSE:
       case SC_KEYMENU:
       // Check lparam.  If it is 0L, then the ::fontopus::user may have done
       // an Alt+Tab, so just ignore it.  This breaks the ability to
       // just press the Alt-key and have the first menu selected,
       // but this is minor compared to what happens in the Alt+Tab
       // case.
       if ((nID & 0xfff0) == SC_CLOSE || lparam != 0L)
       {
       if (pParent != NULL)
       {
       // Sending the above WM_SYSCOMMAND may destroy the cast,
       // so we have to be careful about restoring activation
       // and focus after sending it.
       oswindow hWndSave = get_handle();
       oswindow hWndFocus = ::GetFocus();
       pParent->SetActiveWindow();
       pParent->send_message(WM_SYSCOMMAND, nID, lparam);

       // be very careful here...
       if (::is_window(hWndSave))
       ::set_active_window(hWndSave);
       if (::is_window(hWndFocus))
       ::SetFocus(hWndFocus);
       }
       }
       return true;
       }
       return false;*/
      return false;
   }

   void interaction_impl::WalkPreTranslateTree(::user::interaction *  puiStop, ::message::message * pobj)
   {
      ASSERT(puiStop == NULL || puiStop->IsWindow());
      ASSERT(pobj != NULL);

      SCAST_PTR(::message::base, pbase, pobj);
      // walk from the target user::interaction up to the hWndStop user::interaction checking
      //  if any user::interaction wants to translate this message

      for (sp(::user::interaction) pui = pbase->m_pwnd; pui != NULL; pui->GetParent())
      {

         pui->pre_translate_message(pobj);

         if (pobj->m_bRet)
            return; // trapped by target user::interaction (eg: accelerators)

         // got to hWndStop user::interaction without interest
         if (pui == puiStop)
            break;

      }
      // no special processing
   }


   bool interaction_impl::SendChildNotifyLastMsg(LRESULT* pResult)
   {

      return false;

   }

   bool PASCAL interaction_impl::ReflectLastMsg(oswindow hWndChild, LRESULT* pResult)
   {
      // get the ::collection::map, and if no ::collection::map, then this message does not need reflection
      /*      single_lock sl(afxMutexHwnd(), TRUE);
       hwnd_map * pMap = afxMapHWND();
       if (pMap == NULL)
       return FALSE;

       // check if in permanent ::collection::map, if it is reflect it (could be OLE control)
       ::user::interaction * pWnd = dynamic_cast < ::user::interaction * > (pMap->lookup_permanent(hWndChild)); */
      ::user::interaction * pWnd = dynamic_cast <::user::interaction *> (FromHandlePermanent(hWndChild));
      ASSERT(pWnd == NULL || pWnd->get_handle() == hWndChild);
      if (pWnd == NULL)
      {
         return FALSE;
      }

      // only OLE controls and permanent windows will get reflected msgs
      ASSERT(pWnd != NULL);
      _throw(todo(pWnd->get_app()));
      //return pWnd->SendChildNotifyLastMsg(pResult);

      return FALSE;
   }

   bool interaction_impl::OnChildNotify(UINT uMsg, WPARAM wparam, LPARAM lparam, LRESULT* pResult)
   {

      return ReflectChildNotify(uMsg, wparam, lparam, pResult);
   }

   bool interaction_impl::ReflectChildNotify(UINT uMsg, WPARAM wparam, LPARAM lparam, LRESULT* pResult)
   {
      UNREFERENCED_PARAMETER(wparam);
      // Note: reflected messages are m_pui->send directly to interaction_impl::OnWndMsg
      //  and interaction_impl::_001OnCommand for speed and because these messages are not
      //  routed by normal _001OnCommand routing (they are only dispatched)

      switch (uMsg)
      {
      // normal messages (just wparam, lparam through OnWndMsg)
      case WM_HSCROLL:
      case WM_VSCROLL:
      case WM_PARENTNOTIFY:
      case WM_DRAWITEM:
      case WM_MEASUREITEM:
      case WM_DELETEITEM:
      case WM_VKEYTOITEM:
      case WM_CHARTOITEM:
      case WM_COMPAREITEM:
         // reflect the message through the message ::collection::map as WM_REFLECT_BASE+uMsg
         //return interaction_impl::OnWndMsg(WM_REFLECT_BASE+uMsg, wparam, lparam, pResult);
         return FALSE;

      // special case for WM_COMMAND
      case WM_COMMAND:
      {
         // reflect the message through the message ::collection::map as OCM_COMMAND
         /* xxx         int32_t nCode = HIWORD(wparam);
          if (interaction_impl::_001OnCommand(0, MAKELONG(nCode, WM_REFLECT_BASE+WM_COMMAND), NULL, NULL))
          {
          if (pResult != NULL)
          *pResult = 1;
          return TRUE;
          } */
      }
      break;

      // special case for WM_NOTIFY
      /*      case WM_NOTIFY:
       {
       // reflect the message through the message ::collection::map as OCM_NOTIFY
       NMHDR* pNMHDR = (NMHDR*)lparam;
       //            int32_t nCode = pNMHDR->code;
       //            __NOTIFY notify;
       //          notify.pResult = pResult;
       //        notify.pNMHDR = pNMHDR;
       // xxxx         return interaction_impl::_001OnCommand(0, MAKELONG(nCode, WM_REFLECT_BASE+WM_NOTIFY), &notify, NULL);
       }

       // other special cases (WM_CTLCOLOR family)*/
      default:
         if (uMsg >= WM_CTLCOLORMSGBOX && uMsg <= WM_CTLCOLORSTATIC)
         {
            // fill in special struct for compatiblity with 16-bit WM_CTLCOLOR
            /*__CTLCOLOR ctl;
             ctl.hDC = (HDC)wparam;
             ctl.nCtlType = uMsg - WM_CTLCOLORMSGBOX;
             //ASSERT(ctl.nCtlType >= CTLCOLOR_MSGBOX);
             ASSERT(ctl.nCtlType <= CTLCOLOR_STATIC);

             // reflect the message through the message ::collection::map as OCM_CTLCOLOR
             bool bResult = interaction_impl::OnWndMsg(WM_REFLECT_BASE+WM_CTLCOLOR, 0, (LPARAM)&ctl, pResult);
             if ((HBRUSH)*pResult == NULL)
             bResult = FALSE;
             return bResult;*/
            return false;
         }
         break;
      }

      return false;   // let the parent handle it
   }

   void interaction_impl::OnParentNotify(UINT message, LPARAM lparam)
   {
      if ((LOWORD(message) == WM_CREATE || LOWORD(message) == WM_DESTROY))
      {
         if (ReflectLastMsg((oswindow)lparam))
            return;     // eat it
      }
      // not handled - do default
      Default();
   }

   void interaction_impl::OnSetFocus(::user::interaction *)
   {
      bool bHandled;

      bHandled = FALSE;
      if (!bHandled)
      {
         Default();
      }
   }


   LRESULT interaction_impl::OnActivateTopLevel(WPARAM wparam, LPARAM)
   {

      return 0;

   }

   void interaction_impl::OnSysColorChange()
   {
      _throw(not_implemented(get_app()));

      /*      application* pApp = &System;
       if (pApp != NULL && pApp->GetMainWnd() == this)
       {
       // recolor global brushes used by control bars
       afxData.UpdateSysColors();
       }

       // forward this message to all other child windows
       if (!(GetStyle() & WS_CHILD))
       send_message_to_descendants(WM_SYSCOLORCHANGE, 0, 0L, TRUE, TRUE);

       Default();*/
   }

   bool gen_GotScrollLines;

   void interaction_impl::OnSettingChange(UINT uFlags, const char * lpszSection)
   {
      //      UNUSED_ALWAYS(uFlags);
      //    UNUSED_ALWAYS(lpszSection);

      // force refresh of settings that we cache
      gen_GotScrollLines = FALSE;


      interaction_impl::OnDisplayChange(0, 0);    // to update system metrics, etc.
   }

   /*   void interaction_impl::OnDevModeChange(__in LPTSTR lpDeviceName)
    {
    UNREFERENCED_PARAMETER(lpDeviceName);
    _throw(not_implemented(get_app()));
    application* pApp = &System;
    if (pApp != NULL && pApp->GetMainWnd() == this)
    pApp->DevModeChange(lpDeviceName);

    // forward this message to all other child windows
    if (!(GetStyle() & WS_CHILD))
    {
    const MESSAGE* pMsg = GetCurrentMessage();
    send_message_to_descendants(pMsg->message, pMsg->wparam, pMsg->lparam,
    TRUE, TRUE);
    }*/
   //}


   //
   //   bool interaction_impl::OnHelpInfo(HELPINFO* /*pHelpInfo*/)
   //   {
   //      if (!(GetStyle() & WS_CHILD))
   //      {
   //         ::user::interaction* pMainWnd = System.GetMainWnd();
   //         if (pMainWnd != NULL &&
   //            GetKeyState(VK_SHIFT) >= 0 &&
   //            GetKeyState(VK_CONTROL) >= 0 &&
   //            GetKeyState(VK_MENU) >= 0)
   //         {
   //            //            pMainWnd->SendMessage(WM_COMMAND, ID_HELP);
   //            return TRUE;
   //         }
   //      }
   //      return Default() != 0;
   //   }
   //
   LRESULT interaction_impl::OnDisplayChange(WPARAM, LPARAM)
   {
      if (!(GetStyle() & WS_CHILD))
      {
         const MESSAGE* pMsg = GetCurrentMessage();
         send_message_to_descendants(pMsg->message, pMsg->wParam, pMsg->lParam, TRUE, TRUE);
      }

      return Default();
   }

   LRESULT interaction_impl::OnDragList(WPARAM, LPARAM lparam)
   {

      _throw(not_implemented(get_app()));
      //
      //      LPDRAGLISTINFO lpInfo = (LPDRAGLISTINFO)lparam;
      //      ASSERT(lpInfo != NULL);
      //
      //      LRESULT lResult;
      //      if (ReflectLastMsg(lpInfo->hWnd, &lResult))
      //         return (int32_t)lResult;    // eat it
      //
      //      // not handled - do default
      //      return (int32_t)Default();
   }



   void interaction_impl::prodevian_task()
   {

      if (m_pthreadProDevian.is_null())
      {

         m_pthreadProDevian = fork([&]()
         {

            DWORD dwStart;

            bool bUpdateScreen = false;

            while (::get_thread_run())
            {

               try
               {

                  dwStart = ::get_tick_count();

                  if(m_pui == NULL)
                  {

                     break;

                  }

                  if(m_oswindow != NULL)
                  {

                     m_oswindow->m_bNsWindowRect = false;

                  }

                  if (!m_pui->m_bLockWindowUpdate)
                  {

                     bool bUpdateBuffer =
                     m_pui->m_bProDevian ||
                     m_pui->check_need_layout()||
                     m_pui->check_need_zorder() ||
                     m_pui->check_show_flags();

                     if(bUpdateBuffer)
                     {

                     }
                     else if(m_pui->IsWindowVisible())
                     {

                        bUpdateBuffer = m_pui->has_pending_graphical_update();

                     }

                     if(bUpdateBuffer)
                     {

                        _001UpdateBuffer();

                        if(m_pui == NULL)
                        {

                           break;

                        }

                        m_pui->on_after_graphical_update();

                        bUpdateScreen = true;

                     }

                  }

                  if(bUpdateScreen)
                  {

                     u64 now = get_nanos();

                     u64 delta1 = now - m_uiLastUpdateBeg;

                     i64 delta2 = (i64) m_uiLastUpdateBeg - (i64) m_uiLastUpdateEnd;

                     u64 frameNanos = 1000000000LL / m_dFps;

                     if(delta1 < frameNanos || (delta2 > 0 && delta2 < 10000000000LL))
                     {

                        output_debug_string("opt_out set need redraw");

                     }
                     else
                     {

                        bUpdateScreen = false;

                        _001UpdateScreen();

                     }

                  }

                  DWORD dwSpan = ::get_tick_count() - dwStart;

                  if (dwSpan < 50)
                  {

                     Sleep(50 - dwSpan);

                  }

               }
               catch(...)
               {

                  break;

               }

            }

            output_debug_string("m_pthreadDraw has finished!");

         });

      }


   }


   void interaction_impl::_001OnCreate(::message::message * pobj)
   {

      UNREFERENCED_PARAMETER(pobj);

      Default();

      if (m_pui->is_message_only_window())
      {

         TRACE("good : opt out!");

      }
      else
      {

      }

   }


   void interaction_impl::release_graphics_resources()
   {

      m_spgraphics.release();


   }


   void interaction_impl::_001OnTimer(::timer * ptimer)
   {

      ::user::interaction_impl::_001OnTimer(ptimer);;

//      if (ptimer->m_nIDEvent == 2049)
      //    {
//
      //       set_need_redraw();
//
      //    }

   }


   /*


      void interaction_impl::OnHScroll(UINT, UINT, CScrollBar* pScrollBar)
      {
         UNREFERENCED_PARAMETER(pScrollBar);
         Default();
      }

      void interaction_impl::OnVScroll(UINT, UINT, CScrollBar* pScrollBar)
      {
         UNREFERENCED_PARAMETER(pScrollBar);
         Default();
      }
      */
   bool CALLBACK interaction_impl::GetAppsEnumWindowsProc(oswindow hwnd, LPARAM lparam)
   {
      user::oswindow_array * phwnda = (user::oswindow_array *) lparam;
      phwnda->add(hwnd);
      return TRUE;
   }

   void interaction_impl::get_app_wnda(user::oswindow_array & wnda)
   {

      _throw(not_implemented(::get_app()));
      //      EnumWindows(GetAppsEnumWindowsProc, (LPARAM) &wnda);
   }

   /*   void interaction_impl::_001OnDeferPaintLayeredWindowBackground(::draw2d::dib * pdib)
    {
    _001DeferPaintLayeredWindowBackground(pgraphics);
    }*/


   class print_window :
      virtual ::object
   {
   public:



      manual_reset_event m_event;
      oswindow m_hwnd;
      HDC m_hdc;

      print_window(::aura::application * papp, oswindow hwnd, HDC hdc, DWORD dwTimeout) :
         ::object(papp),
         m_event(papp)

      {
         m_event.ResetEvent();
         m_hwnd = hwnd;
         m_hdc = hdc;
         __begin_thread(papp, &print_window::s_print_window, (LPVOID) this, ::multithreading::priority_normal);
         if (m_event.wait(millis(dwTimeout)).timeout())
         {
            TRACE("print_window::time_out");
         }
      }


      static_function UINT c_cdecl s_print_window(LPVOID pvoid)
      {
         //         print_window * pprintwindow = (print_window *) pvoid;
         //         try
         //         {
         //            HANDLE hevent = (HANDLE) pprintwindow->m_event.get_handle();
         //            _throw(not_implemented(pprintwindow->get_app()));
         //            /*            ::PrintWindow(pprintwindow->m_hwnd, pprintwindow->m_hdc, 0);
         //             ::SetEvent(hevent);*/
         //         }
         //         catch(...)
         //         {
         //         }
         return 0;
      }
   };


   void interaction_impl::_001DeferPaintLayeredWindowBackground(HDC hdc)
   {

      rect rectClient;

      GetClientRect(rectClient);


      //pgraphics->FillSolidRect(rectClient, 0x00000000);

      //return;
      rect rectUpdate;
      GetWindowRect(rectUpdate);
      //      SetViewportOrgEx(hdc, 0, 0, NULL);
      rect rectPaint;
      rectPaint = rectUpdate;
      ScreenToClient(rectPaint);
      user::oswindow_array wndaApp;



   }


   void interaction_impl::_001OnProdevianSynch(::message::message * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
      //      System.get_event(m_papp->m_papp)->SetEvent();
      //    System.get_event(System.get_twf())->wait(millis(8400));
   }

   void interaction_impl::_001OnPaint(::message::message * pobj)
   {

      //lock lock(m_pui, 1984);

      _throw(not_implemented(get_app()));

   }


   void interaction_impl::_001OnPrint(::message::message * pobj)
   {
      _throw(not_implemented(get_app()));
      //      SCAST_PTR(::message::base, pbase, pobj);
      //
      //      if(pbase->m_wparam == NULL)
      //         return;
      //
      //      ::draw2d::graphics_sp graphics(get_app());
      //      WIN_DC(graphics.m_p)->Attach((HDC) pbase->m_wparam);
      //      rect rectx;
      //      ::draw2d::bitmap * pbitmap = &graphics->GetCurrentBitmap();
      //      ::GetCurrentObject((HDC) pbase->m_wparam, OBJ_BITMAP);
      //      //      DWORD dw = ::get_last_error();
      //      class size size = pbitmap->get_size();
      //      rectx.left = 0;
      //      rectx.top = 0;
      //      rectx.right = size.cx;
      //      rectx.bottom = size.cy;
      //      try
      //      {
      //         rect rectWindow;
      //         GetWindowRect(rectWindow);
      //
      //         ::draw2d::dib_sp dib(get_app());
      //         if(!dib->create(rectWindow.bottom_right()))
      //            return;
      //
      //         ::draw2d::graphics * pgraphics = dib->get_graphics();
      //
      //         if(pgraphics->get_handle() == NULL)
      //            return;
      //
      //         rect rectPaint;
      //         rect rectUpdate;
      //         rectUpdate = rectWindow;
      //         rectPaint = rectWindow;
      //         rectPaint.offset(-rectPaint.top_left());
      //         (dynamic_cast<::draw2d_quartz2d::graphics * >(pgraphics))->SelectClipRgn(NULL);
      //         if(m_pui != NULL && m_pui != this)
      //         {
      //            m_pui->_001OnDeferPaintLayeredWindowBackground(pgraphics);
      //         }
      //         else
      //         {
      //            _001OnDeferPaintLayeredWindowBackground(pgraphics);
      //         }
      //         (dynamic_cast<::draw2d_quartz2d::graphics * >(pgraphics))->SelectClipRgn(NULL);
      //         (dynamic_cast<::draw2d_quartz2d::graphics * >(pgraphics))->SetViewportOrg(point(0, 0));
      //         _000OnDraw(pgraphics);
      //         (dynamic_cast<::draw2d_quartz2d::graphics * >(pgraphics))->SetViewportOrg(point(0, 0));
      //         //(dynamic_cast<::draw2d_quartz2d::graphics * >(pgraphics))->FillSolidRect(rectUpdate.left, rectUpdate.top, 100, 100, 255);
      //         (dynamic_cast<::draw2d_quartz2d::graphics * >(pgraphics))->SelectClipRgn(NULL);
      //         (dynamic_cast<::draw2d_quartz2d::graphics * >(pgraphics))->SetViewportOrg(point(0, 0));
      //
      //         graphics->SelectClipRgn( NULL);
      //         graphics->BitBlt(rectPaint.left, rectPaint.top,
      //            rectPaint.width(), rectPaint.height(),
      //            pgraphics, rectUpdate.left, rectUpdate.top,
      //            SRCCOPY);
      //
      //         graphics->text_out(0, 0, "Te Amo Carlinhos!!", 11);
      //      }
      //      catch(...)
      //      {
      //      }
      //      graphics->FillSolidRect(rectx, RGB(255, 255, 255));
      //      WIN_DC(graphics.m_p)->Detach();
      //      pobj->m_bRet = true;
      //      pbase->set_lresult(0);
   }


   void interaction_impl::OnEnterIdle(UINT /*nWhy*/, ::user::interaction * /*pWho*/)
   {
      // In some OLE inplace active scenarios, OLE will m_pui->send a
      // message instead of sending it.  This causes so many WM_ENTERIDLE
      // messages to be sent that tasks running in the background stop
      // running.  By dispatching the pending WM_ENTERIDLE messages
      // when the first one is received, we trick oswindows into thinking
      // that only one was really sent and dispatched.
      {
         //         MESSAGE msg;
         _throw(not_implemented(get_app()));
         //while (PeekMessage(&msg, NULL, WM_ENTERIDLE, WM_ENTERIDLE, PM_REMOVE))
         //while (PeekMessage(&msg, ::caNULL, WM_ENTERIDLE, WM_ENTERIDLE, TRUE))
         // DispatchMessage(&msg);
      }

      //Default();
   }

   HBRUSH interaction_impl::OnCtlColor(::draw2d::graphics *, ::user::interaction * pWnd, UINT)
   {
//      ASSERT(pWnd != NULL && pWnd->get_handle() != NULL);
//      LRESULT lResult;
//      if (pWnd->SendChildNotifyLastMsg(&lResult))
//         return (HBRUSH)lResult;     // eat it
//      return (HBRUSH)Default();
      _throw(todo(get_app()));
      return NULL;
   }

   // implementation of OnCtlColor for default gray backgrounds
   //   (works for any user::interaction containing controls)
   //  return value of FALSE means caller must call DefWindowProc's default
   //  TRUE means that 'hbrGray' will be used and the appropriate text
   //    ('clrText') and background colors are set.
   bool PASCAL interaction_impl::GrayCtlColor(HDC hDC, oswindow hWnd, UINT nCtlColor,
         HBRUSH hbrGray, COLORREF clrText)
   {

      _throw(not_implemented(::get_app()));
      //      if (hDC == NULL)
      //      {
      //         // sometimes Win32 passes a NULL hDC in the WM_CTLCOLOR message.
      //         //         TRACE(::ca2::trace::category_AppMsg, 0, "Warning: hDC is NULL in interaction_impl::GrayCtlColor; WM_CTLCOLOR not processed.\n");
      //         return FALSE;
      //      }
      //
      //      if (hbrGray == NULL ||
      //         nCtlColor == CTLCOLOR_EDIT || nCtlColor == CTLCOLOR_MSGBOX ||
      //         nCtlColor == CTLCOLOR_SCROLLBAR)
      //      {
      //         return FALSE;
      //      }
      //
      //      if (nCtlColor == CTLCOLOR_LISTBOX)
      //      {
      //         // only handle requests to draw the space between edit and drop button
      //         //  in a drop-down combo (not a drop-down list)
      //         if (!__is_combo_box_control(hWnd, (UINT)CBS_DROPDOWN))
      //            return FALSE;
      //      }
      //
      //      // set background color and return handle to brush
      //      LOGBRUSH logbrush;
      //      VERIFY(::GetObject(hbrGray, sizeof(LOGBRUSH), (LPVOID)&logbrush));
      //      ::SetBkColor(hDC, logbrush.lbColor);
      //      if (clrText == (COLORREF)-1)
      //         clrText = ::GetSysColor(COLOR_WINDOWTEXT);  // normal text
      //      ::SetTextColor(hDC, clrText);
      //      return TRUE;
   }



   /////////////////////////////////////////////////////////////////////////////
   // Centering dialog support (works for any non-child user::interaction)

   void interaction_impl::CenterWindow(::user::interaction *  pAlternateOwner)
   {
      _throw(not_implemented(get_app()));
   }

   bool interaction_impl::CheckAutoCenter()
   {
      return TRUE;
   }

   /////////////////////////////////////////////////////////////////////////////
   // Dialog initialization support

   bool interaction_impl::ExecuteDlgInit(const char * lpszResourceName)
   {
      // find resource handle
      LPVOID lpResource = NULL;
      HGLOBAL hResource = NULL;
      if (lpszResourceName != NULL)
      {
         //         HINSTANCE hInst = ::ca2::FindResourceHandle(lpszResourceName, RT_DLGINIT);
         //       HRSRC hDlgInit = ::FindResource(hInst, lpszResourceName, RT_DLGINIT);
         /*     if (hDlgInit != NULL)
          {
          // load it
          hResource = LoadResource(hInst, hDlgInit);
          if (hResource == NULL)
          return FALSE;
          // lock it
          lpResource = LockResource(hResource);
          ASSERT(lpResource != NULL);
          }*/
      }

      // execute it
      bool bResult = ExecuteDlgInit(lpResource);

      // cleanup
      if (lpResource != NULL && hResource != NULL)
      {
         _throw(not_implemented(get_app()));
         //         UnlockResource(hResource);
         //         FreeResource(hResource);
      }
      return bResult;
   }

   bool interaction_impl::ExecuteDlgInit(LPVOID lpResource)
   {
      _throw(not_implemented(get_app()));
      //      bool bSuccess = TRUE;
      //      if (lpResource != NULL)
      //      {
      //         UNALIGNED WORD* lpnRes = (WORD*)lpResource;
      //         while (bSuccess && *lpnRes != 0)
      //         {
      //            WORD nIDC = *lpnRes++;
      //            WORD nMsg = *lpnRes++;
      //            DWORD dwLen = *((UNALIGNED DWORD*&)lpnRes)++;
      //
      //            // In Win32 the WM_ messages have changed.  They have
      //            // to be translated from the 32-bit values to 16-bit
      //            // values here.
      //
      //#define WIN16_LB_ADDSTRING  0x0401
      //#define WIN16_CB_ADDSTRING  0x0403
      //#define __CB_ADDSTRING   0x1234
      //
      //            // unfortunately, WIN16_CB_ADDSTRING == CBEM_INSERTITEM
      //            if (nMsg == __CB_ADDSTRING)
      //               nMsg = CBEM_INSERTITEM;
      //            else if (nMsg == WIN16_LB_ADDSTRING)
      //               nMsg = LB_ADDSTRING;
      //            else if (nMsg == WIN16_CB_ADDSTRING)
      //               nMsg = CB_ADDSTRING;
      //
      //            // check for invalid/unknown message types
      //            ASSERT(nMsg == LB_ADDSTRING || nMsg == CB_ADDSTRING ||
      //               nMsg == CBEM_INSERTITEM);
      //
      //#ifdef DEBUG
      //            // For AddStrings, the count must exactly delimit the
      //            // string, including the NULL termination.  This check
      //            // will not catch all mal-formed ADDSTRINGs, but will
      //            // catch some.
      //            if (nMsg == LB_ADDSTRING || nMsg == CB_ADDSTRING || nMsg == CBEM_INSERTITEM)
      //               ASSERT(*((LPBYTE)lpnRes + (UINT)dwLen - 1) == 0);
      //#endif
      //
      //            if (nMsg == CBEM_INSERTITEM)
      //            {
      //               COMBOBOXEXITEM item = {0};
      //               item.mask = CBEIF_TEXT;
      //               item.iItem = -1;
      //               string strText(reinterpret_cast<LPTSTR>(lpnRes));
      //               item.pszText = const_cast<LPTSTR>(strText.GetString());
      //               if (::SendDlgItemMessage(get_handle(), nIDC, nMsg, 0, (LPARAM) &item) == -1)
      //                  bSuccess = FALSE;
      //            }
      //            {
      //               // List/Combobox returns -1 for error
      //               if (::SendDlgItemMessageA(get_handle(), nIDC, nMsg, 0, (LPARAM) lpnRes) == -1)
      //                  bSuccess = FALSE;
      //            }
      //
      //
      //            // skip past data
      //            lpnRes = (WORD*)((LPBYTE)lpnRes + (UINT)dwLen);
      //         }
      //      }
      //
      //      // m_pui->send update message to all controls after all other siblings loaded
      //      if (bSuccess)
      //         send_message_to_descendants(WM_INITIALUPDATE, 0, 0, FALSE, FALSE);
      //
      //      return bSuccess;
   }

   void interaction_impl::UpdateDialogControls(command_target* pTarget, bool bDisableIfNoHndler)
   {
      UNREFERENCED_PARAMETER(pTarget);
      UNREFERENCED_PARAMETER(bDisableIfNoHndler);
      ::user::command state(get_app());
      user::interaction wndTemp;       // very temporary user::interaction just for CmdUI update

      // walk all the kids - assume the IDs are for buttons
      /* xxx   for (oswindow hWndChild = ::GetTopWindow(get_handle()); hWndChild != NULL;
       hWndChild = ::GetNextWindow(hWndChild, GW_HWNDNEXT))
       {
       // m_pui->send to buttons
       wndTemp.set_handle(hWndChild); // quick and dirty attach
       state.m_nID = __get_dialog_control_id(hWndChild);
       state.m_pOther = &wndTemp;

       // check for reflect handlers in the child user::interaction
       ::user::interaction * pWnd = ::macos::interaction_impl::FromHandlePermanent(hWndChild);
       if (pWnd != NULL)
       {
       // call it directly to disable any routing
       if (MAC_WINDOW(pWnd)->interaction_impl::_001OnCommand(0, MAKELONG(0xffff,
       WM_COMMAND+WM_REFLECT_BASE), &state, NULL))
       continue;
       }

       // check for handlers in the parent user::interaction
       if (interaction_impl::_001OnCommand((UINT)state.m_nID, CN_UPDATE_::user::command, &state, NULL))
       continue;

       // determine whether to disable when no handler exists
       bool bDisableTemp = bDisableIfNoHndler;
       if (bDisableTemp)
       {
       if ((wndTemp.SendMessage(WM_GETDLGCODE) & DLGC_BUTTON) == 0)
       {
       // non-button controls don't get automagically disabled
       bDisableTemp = FALSE;
       }
       else
       {
       // only certain button controls get automagically disabled
       UINT nStyle = (UINT)(wndTemp.GetStyle() & 0x0F);
       if (nStyle == (UINT)BS_AUTOCHECKBOX ||
       nStyle == (UINT)BS_AUTO3STATE ||
       nStyle == (UINT)BS_GROUPBOX ||
       nStyle == (UINT)BS_AUTORADIOBUTTON)
       {
       bDisableTemp = FALSE;
       }
       }
       }
       // check for handlers in the target (owner)
       state.DoUpdate(pTarget, bDisableTemp);
       }
       wndTemp.set_handle(NULL);      // quick and dirty detach */
   }


   bool interaction_impl::IsFrameWnd()
   {
      return FALSE;
   }

   bool interaction_impl::SubclassWindow(oswindow hWnd)
   {
      if (!Attach(hWnd))
         return FALSE;

      // allow any other subclassing to occur
      pre_subclass_window();

      _throw(not_implemented(get_app()));
      //      m_pfnSuper = (WNDPROC)::GetWindowLongPtr(hWnd, GWLP_WNDPROC);

      // now hook into the AFX WndProc
      //      WNDPROC* lplpfn = GetSuperWndProcAddr();
      //      WNDPROC oldWndProc = (WNDPROC)::SetWindowLongPtr(hWnd, GWLP_WNDPROC,
      //         (int_ptr)__get_window_procedure());
      //      ASSERT(oldWndProc != __get_window_procedure());
      //
      //      if (*lplpfn == NULL)
      //         *lplpfn = oldWndProc;   // the first control of that type created
      //#ifdef DEBUG
      //      else if (*lplpfn != oldWndProc)
      //      {
      //         TRACE(::ca2::trace::category_AppMsg, 0, "p: Trying to use SubclassWindow with incorrect user::interaction\n");
      //         TRACE(::ca2::trace::category_AppMsg, 0, "\tderived class.\n");
      //         TRACE(::ca2::trace::category_AppMsg, 0, "\thWnd = $%08X (nIDC=$%08X) is not a %hs.\n", (UINT)(uint_ptr)hWnd,
      //            __get_dialog_control_id(hWnd), typeid(*this).name());
      //         ASSERT(FALSE);
      //         // undo the subclassing if continuing after assert
      //         ::SetWindowLongPtr(hWnd, GWLP_WNDPROC, (int_ptr)oldWndProc);
      //      }
      //#endif
      //      ::message::size size(get_app());
      //      _001OnSize(&size);
      //      return TRUE;
      //   }
      //
      //   bool interaction_impl::SubclassDlgItem(UINT nID, ::user::interaction * pParent)
      //   {
      //      ASSERT(pParent != NULL);
      //      ASSERT(::is_window(MAC_WINDOW(pParent)->get_handle()));
      //
      //      // check for normal dialog control first
      //      oswindow hWndControl = ::GetDlgItem(MAC_WINDOW(pParent)->get_handle(), nID);
      //      if (hWndControl != NULL)
      //         return SubclassWindow(hWndControl);
      //
      //
      //      return FALSE;   // control not found
   }

   oswindow interaction_impl::UnsubclassWindow()
   {
      ASSERT(::is_window(get_handle()));

      _throw(not_implemented(get_app()));
      //      // set WNDPROC back to original value
      //      WNDPROC* lplpfn = GetSuperWndProcAddr();
      //      SetWindowLongPtr(get_handle(), GWLP_WNDPROC, (int_ptr)*lplpfn);
      //      *lplpfn = NULL;
      //
      //      // and Detach the oswindow from the user::interaction object
      //      return Detach();
   }


   /*   view_update_hint::view_update_hint(::aura::application * papp) :
    ::object(papp)
    {
    }
    */



   bool interaction_impl::IsChild(::user::interaction *  pWnd)
   {
      ASSERT(::is_window(get_handle()));
      if (pWnd->get_handle() == NULL)
      {
         return ::user::interaction_impl::IsChild(pWnd);
      }
      else
      {
         //         return ::IsChild(get_handle(), MAC_WINDOW(pWnd)->get_handle()) != FALSE;
         return FALSE;
      }
   }

   bool interaction_impl::IsWindow() const
   {
      return ::is_window(m_oswindow) != FALSE;
   }


   ::user::interaction * interaction_impl::get_wnd() const
   {

      return m_pui;

   }


   void interaction_impl::MoveWindow(int32_t x, int32_t y, int32_t nWidth, int32_t nHeight, bool bRepaint)
   {

      ASSERT(::is_window(get_handle()));

      SetWindowPos(0, x, y, nWidth, nHeight, bRepaint ? SWP_SHOWWINDOW : 0);

   }


   pointd interaction_impl::client_to_screen()
   {

      class rect64 rectWindow;

      if (!m_pui->GetWindowRect(rectWindow))
      {

         return point(0.0, 0.0);

      }

      return rectWindow.top_left();

   }


   bool interaction_impl::GetWindowRect(RECT64 * lprect)
   {

      return ::user::interaction_impl::GetWindowRect(lprect);

   }


   bool interaction_impl::GetClientRect(RECT64 * lprect)
   {

      if (!::is_window(get_handle()))
      {

         return false;

      }

      rect rect32;

      if (!::GetClientRect(get_handle(), rect32))
      {

         return false;

      }

      ::copy(lprect, rect32);

      return true;

   }


   id interaction_impl::SetDlgCtrlId(id id)
   {

      return m_pui->SetDlgCtrlId((id));

   }


   id interaction_impl::GetDlgCtrlId()
   {

      return m_pui->GetDlgCtrlId();

   }


   void interaction_impl::_001WindowMaximize()
   {

      ::user::interaction_impl::_001WindowMaximize();

   }


   void interaction_impl::_001WindowRestore()
   {

      m_pui->m_eappearance = user::appearance_normal;

      if (m_pui != NULL)
      {

         m_pui->m_eappearance = user::appearance_normal;

      }

   }


   bool interaction_impl::ShowWindow(int32_t nCmdShow)
   {

      if (!::is_window(get_handle()))
      {

         return false;

      }

      ::ShowWindow(get_handle(), nCmdShow);

      //m_pui->send_message(WM_SHOWWINDOW, ::IsWindowVisible(get_handle()));

      return m_pui->IsWindowVisible();

   }


   bool interaction_impl::WfiIsIconic()
   {

      ASSERT(::is_window(get_handle()));

      if (GetExStyle() & WS_EX_LAYERED)
      {

         return m_pui->m_eappearance == user::appearance_iconic;

      }
      else
      {

         return ::IsIconic(get_handle()) != FALSE;

      }

   }


   bool interaction_impl::WfiIsZoomed()
   {

      ASSERT(::is_window(get_handle()));

      return m_pui->m_eappearance == user::appearance_zoomed;

   }


   ::user::interaction * interaction_impl::GetParent() const
   {

      return NULL;

   }


   LONG interaction_impl::GetWindowLong(int32_t nIndex)
   {

      return ::GetWindowLong(get_handle(), nIndex);

   }


   LONG interaction_impl::SetWindowLong(int32_t nIndex, LONG lValue)
   {

      return ::SetWindowLong(get_handle(), nIndex, lValue);

   }


   DWORD interaction_impl::GetStyle() const
   {

      ASSERT(::is_window(get_handle()));

      return (DWORD)::GetWindowLong(get_handle(), GWL_STYLE);

   }


   DWORD interaction_impl::GetExStyle() const
   {

      ASSERT(::is_window(get_handle()));

      return (DWORD)::GetWindowLong(get_handle(), GWL_EXSTYLE);

   }


   bool interaction_impl::ModifyStyle(DWORD dwRemove, DWORD dwAdd, UINT nFlags)
   {

      ASSERT(::is_window(get_handle()));

      return ModifyStyle(get_handle(), dwRemove, dwAdd, nFlags);

   }


   bool interaction_impl::ModifyStyleEx(DWORD dwRemove, DWORD dwAdd, UINT nFlags)
   {

      ASSERT(::is_window(get_handle()));

      return ModifyStyleEx(get_handle(), dwRemove, dwAdd, nFlags);

   }


   ::user::interaction *  interaction_impl::SetOwner(::user::interaction *  pOwnerWnd)
   {

      return NULL;

   }


   LRESULT interaction_impl::send_message(UINT message, WPARAM wparam, lparam lparam)
   {

      return ::user::interaction_impl::send_message(message, wparam, lparam);

   }


   bool interaction_impl::post_message(UINT message, WPARAM wparam, lparam lparam)
   {

      if (m_pui->m_pthread == NULL)
      {

         return false;

      }

      return m_pui->m_pthread->post_message((::user::primitive *) m_pui, message, wparam, lparam);

   }


   bool interaction_impl::DragDetect(POINT pt) const
   {

      _throw(not_implemented(get_app()));

   }


   void interaction_impl::set_window_text(const char * lpszString)
   {

      m_strWindowText = lpszString;

      round_window_set_title(m_strWindowText);

   }


   void interaction_impl::DragAcceptFiles(bool bAccept)
   {

      _throw(not_implemented(get_app()));

   }


   void interaction_impl::MoveWindow(LPCRECT lpRect, bool bRepaint)
   {

      MoveWindow(lpRect->left, lpRect->top, lpRect->right - lpRect->left, lpRect->bottom - lpRect->top, bRepaint);

   }


   UINT interaction_impl::ArrangeIconicWindows()
   {

      _throw(not_implemented(get_app()));

   }


   int32_t interaction_impl::SetWindowRgn(HRGN hRgn, bool bRedraw)
   {

      _throw(not_implemented(get_app()));

   }


   int32_t interaction_impl::GetWindowRgn(HRGN hRgn)
   {

      _throw(not_implemented(get_app()));

   }


   void interaction_impl::BringToTop(int nCmdShow)
   {

      if (nCmdShow != SW_HIDE)
      {

         BringWindowToTop();

         round_window_show();

      }

   }


   bool interaction_impl::BringWindowToTop()
   {

      bool b = ::BringWindowToTop(get_handle()) != FALSE;

      return b;

   }


   void interaction_impl::MapWindowPoints(::user::interaction * pwndTo, LPPOINT lpPoint, UINT nCount)
   {

      _throw(not_implemented(get_app()));

   }


   void interaction_impl::MapWindowPoints(::user::interaction * pwndTo, LPRECT lpRect)
   {

      _throw(not_implemented(get_app()));

   }


   ::draw2d::graphics * interaction_impl::GetDC()
   {

      return NULL;

   }


   ::draw2d::graphics * interaction_impl::GetWindowDC()
   {

      return NULL;

   }


   bool interaction_impl::ReleaseDC(::draw2d::graphics * pgraphics)
   {

      if (pgraphics == NULL)
      {

         return false;

      }

      return true;

   }


   void interaction_impl::UpdateWindow()
   {

      _throw(not_implemented(get_app()));

   }


   void interaction_impl::SetRedraw(bool bRedraw)
   {

      _throw(not_implemented(get_app()));

   }


   bool interaction_impl::GetUpdateRect(LPRECT lpRect, bool bErase)
   {

      _throw(not_implemented(get_app()));

   }


   int32_t interaction_impl::GetUpdateRgn(::draw2d::region* pRgn, bool bErase)
   {

      _throw(not_implemented(get_app()));

   }


   void interaction_impl::Invalidate(bool bErase)
   {

      m_bNeedsUpdate = true;

   }


   void interaction_impl::InvalidateRect(LPCRECT lpRect, bool bErase)
   {

      _throw(not_implemented(get_app()));

   }


   void interaction_impl::InvalidateRgn(::draw2d::region* pRgn, bool bErase)
   {

      _throw(not_implemented(get_app()));

   }


   void interaction_impl::ValidateRect(LPCRECT lpRect)
   {

      _throw(not_implemented(get_app()));

   }


   void interaction_impl::ValidateRgn(::draw2d::region* pRgn)
   {

      _throw(not_implemented(get_app()));

   }


   bool interaction_impl::IsWindowVisible()
   {

      if (!::is_window(get_handle()))
      {

         return false;

      }

      if (m_pui != NULL)
      {

         if (!m_pui->is_this_visible())
         {

            return false;

         }

         if (m_pui->GetParent() != NULL && !m_pui->GetParent()->IsWindowVisible())
         {

            return false;

         }

      }

      if (!::IsWindowVisible(get_handle()))
      {

         return false;

      }

      return true;

   }


   void interaction_impl::ShowOwnedPopups(bool bShow)
   {

      _throw(not_implemented(get_app()));

   }


   void interaction_impl::send_message_to_descendants(UINT message, WPARAM wparam, lparam lparam, bool bDeep, bool bOnlyPerm)
   {

      ASSERT(::is_window(get_handle()));

      // walk through oswindows to avoid creating temporary user::interaction objects
      // unless we need to call this function recursively
      user::interaction * pui = m_pui->top_child();

      while (pui != NULL)
      {

         try
         {

            pui->send_message(message, wparam, lparam);

         }
         catch (...)
         {

         }

         if (bDeep)
         {

            // m_pui->send to child windows after parent

            try
            {

               pui->send_message_to_descendants(message, wparam, lparam, bDeep, bOnlyPerm);

            }
            catch (...)
            {

            }

         }

         try
         {

            pui = pui->under_sibling();

         }
         catch (...)
         {

            break;

         }

      }

   }


   ::user::interaction * interaction_impl::GetDescendantWindow(id id)
   {

      single_lock sl(m_papp->m_pmutex, TRUE);

      for (int32_t i = 0; i < m_pui->m_uiptraChild.get_count(); i++)
      {

         if (m_pui->m_uiptraChild[i]->GetDlgCtrlId() == id)
         {

            if (m_pui->m_uiptraChild[i]->GetDescendantWindow(id))
            {

               return m_pui->m_uiptraChild[i]->GetDescendantWindow(id);

            }
            else
            {

               return m_pui->m_uiptraChild[i];

            }

         }

      }

      return NULL;

   }


   ::draw2d::graphics * interaction_impl::GetDCEx(::draw2d::region* prgnClip, DWORD flags)
   {

      _throw(not_implemented(get_app()));

   }


   bool interaction_impl::LockWindowUpdate()
   {

      _throw(not_implemented(get_app()));

   }


   void interaction_impl::UnlockWindowUpdate()
   {

      _throw(not_implemented(get_app()));

   }


   void interaction_impl::on_do_show_flags()
   {

      ::user::interaction_impl::on_do_show_flags();

      if((m_bShowFlags && (m_iShowFlags & SWP_SHOWWINDOW))
            || (m_bShowWindow && (m_iShowWindow != SW_HIDE)))
      {

         round_window_show();

      }
      else if((m_bShowFlags && (m_iShowFlags & SWP_HIDEWINDOW))
              || (m_bShowWindow && (m_iShowWindow == SW_HIDE)))
      {

         round_window_hide();

      }

   }


   void interaction_impl::on_zorder()
   {

      if (m_bZ)
      {

         ::SetWindowPos(m_oswindow, (oswindow) m_iZ,
                        0,
                        0,
                        0,
                        0,
                        SWP_NOSIZE
                        | SWP_NOMOVE
                        | (m_bZ ? 0 : SWP_NOZORDER)
                        | SWP_NOREDRAW
                        | SWP_NOCOPYBITS
                        | SWP_NOACTIVATE
                        | SWP_NOOWNERZORDER
                        | SWP_NOSENDCHANGING
                        | SWP_DEFERERASE);

         m_bZ = false;

      }

      //::user::interaction_impl::on_translate();

   }


   void interaction_impl::on_translate()
   {

      if (m_rectLastOsPlacement.top_left() != m_rectParentClientRequest.top_left())
      {

         ::SetWindowPos(m_oswindow, (oswindow) m_iZ,
                        (int) m_rectParentClientRequest.left,
                        (int) m_rectParentClientRequest.top,
                        0,
                        0,
                        SWP_NOSIZE
                        | (m_bZ ? 0 : SWP_NOZORDER)
                        | SWP_NOREDRAW
                        | SWP_NOCOPYBITS
                        | SWP_NOACTIVATE
                        | SWP_NOOWNERZORDER
                        | SWP_NOSENDCHANGING
                        | SWP_DEFERERASE);

         m_rectLastOsPlacement.move_to(m_rectParentClientRequest.top_left());

      }

      //::user::interaction_impl::on_translate();

   }


   void interaction_impl::on_layout()
   {

      if (m_rectLastOsPlacement != m_rectParentClientRequest)
      {

         ::SetWindowPos(m_oswindow, (oswindow) m_iZ,
                        (int) m_rectParentClientRequest.left,
                        (int) m_rectParentClientRequest.top,
                        (int) m_rectParentClientRequest.width(),
                        (int) m_rectParentClientRequest.height(),
                        (m_bZ ? 0 : SWP_NOZORDER)
                        | SWP_NOREDRAW
                        | SWP_NOCOPYBITS
                        | SWP_NOACTIVATE
                        | SWP_NOOWNERZORDER
                        | SWP_NOSENDCHANGING
                        | SWP_DEFERERASE);

         m_rectParentClient = m_rectParentClientRequest;

         m_rectLastOsPlacement = m_rectParentClientRequest;

      }

      //::user::interaction_impl::on_layout();

   }


   void interaction_impl::_001UpdateScreen()
   {

      if (IsWindowVisible())
      {

         round_window_redraw();

      }

   }


   bool interaction_impl::DrawAnimatedRects(int32_t idAni, CONST RECT *lprcFrom, CONST RECT * lprcTo)
   {

      _throw(not_implemented(get_app()));

   }


   bool interaction_impl::DrawCaption(::draw2d::graphics * pgraphics, LPCRECT lprc, UINT uFlags)
   {

      _throw(not_implemented(get_app()));

   }


   bool interaction_impl::SetTimer(uint_ptr nIDEvent, UINT nElapse, PFN_TIMER pfnTimer)
   {

      return ::user::interaction_impl::SetTimer(nIDEvent, nElapse, pfnTimer);

   }


   bool interaction_impl::KillTimer(uint_ptr nIDEvent)
   {

      return ::user::interaction_impl::KillTimer(nIDEvent);

   }


   bool interaction_impl::IsWindowEnabled()
   {

      return true;

   }


   bool interaction_impl::enable_window(bool bEnable)
   {

      m_bEnabled = bEnable;

      return true;

   }


   ::user::interaction *  interaction_impl::GetActiveWindow()
   {

      ::user::interaction_impl * pimpl = ::macos::interaction_impl::from_handle(::get_active_window());

      if(pimpl == NULL)
      {

         return NULL;

      }

      try
      {

         return pimpl->m_pui;

      }
      catch(...)
      {

      }

      return NULL;

   }


   ::user::interaction *  interaction_impl::SetActiveWindow()
   {

      ::user::interaction_impl * pimpl = ::macos::interaction_impl::from_handle(::set_active_window(get_handle()));

      if(pimpl == NULL)
      {

         return NULL;

      }

      return pimpl->m_pui;

   }


   ::user::interaction *  interaction_impl::GetFocus()
   {

      ::user::interaction_impl * pimpl = ::macos::interaction_impl::from_handle(::get_focus());

      if(pimpl == NULL)
      {

         return NULL;

      }

      return pimpl->m_pui;

   }


   bool  interaction_impl::SetFocus()
   {

      ::user::interaction_impl * pimpl = ::macos::interaction_impl::from_handle(::set_focus(get_handle()));

      if(pimpl == NULL)
      {

         return NULL;

      }

      return pimpl->m_pui;

   }


   ::user::interaction *  interaction_impl::get_desktop_window()
   {

      return NULL;

   }


   // Helper for radio buttons
   int32_t interaction_impl::GetCheckedRadioButton(int32_t nIDFirstButton, int32_t nIDLastButton)
   {

      for (int32_t nID = nIDFirstButton; nID <= nIDLastButton; nID++)
      {

         if (IsDlgButtonChecked(nID))
         {

            return nID; // id that matched

         }

      }

      return 0; // invalid ID

   }


   void interaction_impl::CheckDlgButton(int32_t nIDButton, UINT nCheck)
   {

      _throw(not_implemented(get_app()));

   }


   void interaction_impl::CheckRadioButton(int32_t nIDFirstButton, int32_t nIDLastButton, int32_t nIDCheckButton)
   {

      _throw(not_implemented(get_app()));

   }


   int32_t interaction_impl::DlgDirList(LPTSTR lpPathSpec, int32_t nIDListBox, int32_t nIDStaticPath, UINT nFileType)
   {

      _throw(not_implemented(get_app()));

   }


   int32_t interaction_impl::DlgDirListComboBox(LPTSTR lpPathSpec, int32_t nIDComboBox, int32_t nIDStaticPath, UINT nFileType)
   {

      _throw(not_implemented(get_app()));

   }


   bool interaction_impl::DlgDirSelect(LPTSTR lpString, int32_t nSize, int32_t nIDListBox)
   {

      _throw(not_implemented(get_app()));

   }


   bool interaction_impl::DlgDirSelectComboBox(LPTSTR lpString, int32_t nSize, int32_t nIDComboBox)
   {

      _throw(not_implemented(get_app()));

   }


   ::user::interaction * interaction_impl::GetNextDlgGroupItem(::user::interaction * pWndCtl, bool bPrevious) const
   {

      _throw(not_implemented(get_app()));

   }


   ::user::interaction * interaction_impl::GetNextDlgTabItem(::user::interaction * pWndCtl, bool bPrevious) const
   {

      _throw(not_implemented(get_app()));

   }


   UINT interaction_impl::IsDlgButtonChecked(int32_t nIDButton) const
   {

      _throw(not_implemented(get_app()));

   }


   LPARAM interaction_impl::SendDlgItemMessage(int32_t nID, UINT message, WPARAM wparam, LPARAM lparam)
   {

      _throw(not_implemented(get_app()));

   }


   void interaction_impl::SetDlgItemInt(int32_t nID, UINT nValue, bool bSigned)
   {

      _throw(not_implemented(get_app()));

   }


   void interaction_impl::SetDlgItemText(int32_t nID, const char * lpszString)
   {

      _throw(not_implemented(get_app()));

   }


   int32_t interaction_impl::ScrollWindowEx(int32_t dx, int32_t dy, LPCRECT lpRectScroll, LPCRECT lpRectClip, ::draw2d::region* prgnUpdate, LPRECT lpRectUpdate, UINT flags)
   {

      _throw(not_implemented(get_app()));

   }


   void interaction_impl::ShowScrollBar(UINT nBar, bool bShow)
   {

      _throw(not_implemented(get_app()));

   }


   ::user::interaction *  interaction_impl::ChildWindowFromPoint(POINT point)
   {

      _throw(not_implemented(get_app()));

   }


   ::user::interaction *  interaction_impl::ChildWindowFromPoint(POINT point, UINT nFlags)
   {

      _throw(not_implemented(get_app()));

   }


   ::user::interaction * PASCAL interaction_impl::FindWindow(const char * lpszClassName, const char * lpszWindowName)
   {

      return NULL;

   }


   ::user::interaction * interaction_impl::FindWindowEx(oswindow hwndParent, oswindow hwndChildAfter, const char * lpszClass, const char * lpszWindow)
   {

      _throw(not_implemented(::get_app()));

   }


   ::user::interaction *  interaction_impl::GetNextWindow(UINT nFlag)
   {

      return NULL;

   }


   ::user::interaction *  interaction_impl::GetTopWindow()
   {

      if (m_pui->m_uiptraChild.get_size() <= 0)
         return NULL;

      return m_pui->m_uiptraChild[0];

   }


   ::user::interaction *  interaction_impl::GetWindow(UINT nCmd)
   {

      ASSERT(::is_window(get_handle()));

      return NULL;

   }


   ::user::interaction *  interaction_impl::GetLastActivePopup()
   {

      _throw(todo(get_app()));

   }


   ::user::interaction * interaction_impl::SetParent(::user::interaction * pWndNewParent)
   {

      ::user::interaction_impl * pimpl = ::macos::interaction_impl::from_handle(::SetParent(get_handle(), (oswindow)pWndNewParent->get_handle()));

      if(pimpl == NULL)
      {

         return NULL;

      }

      return pimpl->m_pui;

   }


   ::user::interaction * PASCAL interaction_impl::oswindowFromPoint(POINT point)
   {

      _throw(not_implemented(::get_app()));

   }


   bool interaction_impl::FlashWindow(bool bInvert)
   {

      _throw(not_implemented(get_app()));
      //      ASSERT(::is_window(get_handle()));
      //      return ::FlashWindow(get_handle(), bInvert) != FALSE;

   }

   bool interaction_impl::ChangeClipboardChain(oswindow hWndNext)
   {

      _throw(not_implemented(get_app()));
      //      ASSERT(::is_window(get_handle()));
      //      return ::ChangeClipboardChain(get_handle(), hWndNext) != FALSE;

   }

   oswindow interaction_impl::SetClipboardViewer()
   {

      _throw(not_implemented(get_app()));
      //      ASSERT(::is_window(get_handle()));
      //      return ::SetClipboardViewer(get_handle());

   }

   bool interaction_impl::OpenClipboard()
   {

      _throw(not_implemented(get_app()));
      //      ASSERT(::is_window(get_handle()));
      //      return ::OpenClipboard(get_handle()) != FALSE;

   }

   ::user::interaction * PASCAL interaction_impl::GetOpenClipboardWindow()
   {

      _throw(not_implemented(::get_app()));
      //      return ::macos::interaction_impl::from_handle(::GetOpenClipboardWindow());

   }

   ::user::interaction * PASCAL interaction_impl::GetClipboardOwner()
   {

      _throw(not_implemented(::get_app()));
      //      return ::macos::interaction_impl::from_handle(::GetClipboardOwner());

   }

   ::user::interaction * PASCAL interaction_impl::GetClipboardViewer()
   {

      _throw(not_implemented(::get_app()));
      //      return ::macos::interaction_impl::from_handle(::GetClipboardViewer());

   }

   void interaction_impl::CreateCaret(::draw2d::bitmap* pBitmap)
   {

      _throw(not_implemented(::get_app()));
      //      ASSERT(::is_window(get_handle()));
      //      ::CreateCaret(get_handle(), (HBITMAP)pBitmap->get_handle(), 0, 0);

   }

   void interaction_impl::CreateSolidCaret(int32_t nWidth, int32_t nHeight)
   {

      _throw(not_implemented(get_app()));
      //      ASSERT(::is_window(get_handle()));
      //      ::CreateCaret(get_handle(), (HBITMAP)0, nWidth, nHeight);

   }

   void interaction_impl::CreateGrayCaret(int32_t nWidth, int32_t nHeight)
   {

      _throw(not_implemented(get_app()));
      //      ASSERT(::is_window(get_handle()));
      //      ::CreateCaret(get_handle(), (HBITMAP)1, nWidth, nHeight);

   }

   point PASCAL interaction_impl::GetCaretPos()
   {

      _throw(not_implemented(::get_app()));
      //      point point;
      //      ::GetCaretPos((LPPOINT)&point); return point;

   }

   void PASCAL interaction_impl::SetCaretPos(POINT point)
   {

      _throw(not_implemented(::get_app()));
      //      ::SetCaretPos(point.x, point.y);

   }

   void interaction_impl::HideCaret()
   {

      _throw(not_implemented(::get_app()));
      //      ::HideCaret(get_handle());

   }

   void interaction_impl::ShowCaret()
   {

      _throw(not_implemented(::get_app()));
      //    ::ShowCaret(get_handle());

   }

   bool interaction_impl::SetForegroundWindow()
   {

      bool b = ::SetForegroundWindow(get_handle()) != FALSE;

      //      round_window_show();

      return b;

   }

   ::user::interaction * PASCAL interaction_impl::GetForegroundWindow()
   {

      return NULL;
      // return ::macos::interaction_impl::from_handle(::GetForegroundWindow());

   }

   bool interaction_impl::SendNotifyMessage(UINT message, WPARAM wparam, LPARAM lparam)
   {

      _throw(not_implemented(get_app()));
      //      return ::SendNotifyMessage(get_handle(), message, wparam, lparam) != FALSE;

   }


   void interaction_impl::Print(::draw2d::graphics * pgraphics, DWORD dwFlags) const
   {

      _throw(not_implemented(get_app()));
      //      ASSERT(::is_window(get_handle()));
      //      const_cast < user::interaction * > (this)->send_message(WM_PRINT, (WPARAM)(dynamic_cast<::draw2d_quartz2d::graphics * >(pgraphics))->get_handle(), dwFlags);

   }

   void interaction_impl::PrintClient(::draw2d::graphics * pgraphics, DWORD dwFlags) const
   {

      _throw(not_implemented(get_app()));
      //      ASSERT(::is_window(get_handle()));
      //      const_cast < user::interaction * > (this)->send_message(WM_PRINTCLIENT, (WPARAM)(dynamic_cast<::draw2d_quartz2d::graphics * >(pgraphics))->get_handle(), dwFlags);

   }

   bool interaction_impl::SetWindowContextHelpId(DWORD dwContextHelpId)
   {

      _throw(not_implemented(get_app()));
      //      ASSERT(::is_window(get_handle()));
      //      return ::SetWindowContextHelpId(get_handle(), dwContextHelpId) != FALSE;

   }

   DWORD interaction_impl::GetWindowContextHelpId() const
   {

      _throw(not_implemented(get_app()));
      //      ASSERT(::is_window(get_handle()));
      //      return ::GetWindowContextHelpId(get_handle());

   }


   // Default message ::collection::map implementations
   void interaction_impl::OnActivateApp(bool, DWORD)
   {
      Default();
   }
   void interaction_impl::OnActivate(UINT, ::user::interaction *, bool)
   {
      Default();
   }
   void interaction_impl::OnCancelMode()
   {
      Default();
   }
   void interaction_impl::OnChildActivate()
   {
      Default();
   }
   void interaction_impl::OnClose()
   {
      Default();
   }
   void interaction_impl::OnContextMenu(::user::interaction *, point)
   {
      Default();
   }

   bool interaction_impl::OnCopyData(::user::interaction *, COPYDATASTRUCT*)
   {

      return Default() != FALSE;

   }

   void interaction_impl::OnEnable(bool)
   {
      Default();
   }
   void interaction_impl::OnEndSession(bool)
   {
      Default();
   }

   bool interaction_impl::OnEraseBkgnd(::draw2d::graphics *)
   {

      return Default() != FALSE;

   }

   void interaction_impl::OnGetMinMaxInfo(MINMAXINFO*)
   {
      Default();
   }
   void interaction_impl::OnIconEraseBkgnd(::draw2d::graphics *)
   {
      Default();
   }
   void interaction_impl::OnKillFocus(::user::interaction *)
   {
      Default();
   }
   LRESULT interaction_impl::OnMenuChar(UINT, UINT, ::user::menu*)
   {
      return Default();
   }
   void interaction_impl::OnMenuSelect(UINT, UINT, HMENU)
   {
      Default();
   }
   void interaction_impl::OnMove(int32_t, int32_t)
   {
      Default();
   }
   HCURSOR interaction_impl::OnQueryDragIcon()
   {
      return (HCURSOR)Default();
   }

   bool interaction_impl::OnQueryEndSession()
   {

      return Default() != FALSE;

   }

   bool interaction_impl::OnQueryNewPalette()
   {

      return Default() != FALSE;

   }

   bool interaction_impl::OnQueryOpen()
   {

      return Default() != FALSE;

   }

   void interaction_impl::_001OnSetCursor(::message::message * pobj)
   {
      SCAST_PTR(::message::base, pbase, pobj);
      if (Session.get_cursor() != NULL
            && Session.get_cursor()->m_ecursor != ::visual::cursor_system)
      {

         _throw(not_implemented(get_app()));
         //         ::SetCursor(NULL);
      }
      pbase->set_lresult(1);
      pbase->m_bRet = true;
      //(bool)Default();
   }
   void interaction_impl::OnShowWindow(bool, UINT)
   {
      Default();
   }
   void interaction_impl::OnSize(UINT, int32_t, int32_t)
   {
      Default();
   }
   void interaction_impl::OnTCard(UINT, DWORD)
   {
      Default();
   }
   void interaction_impl::OnWindowPosChanging(WINDOWPOS*)
   {
      Default();
   }
   void interaction_impl::OnWindowPosChanged(WINDOWPOS*)
   {
      Default();
   }
   void interaction_impl::OnDropFiles(HDROP)
   {
      Default();
   }
   void interaction_impl::OnPaletteIsChanging(::user::interaction *)
   {
      Default();
   }

   bool interaction_impl::OnNcActivate(bool)
   {

      return Default() != FALSE;

   }

   void interaction_impl::OnNcCalcSize(bool, NCCALCSIZE_PARAMS*)
   {
      Default();
   }

   bool interaction_impl::OnNcCreate(::user::create_struct *)
   {

      return Default() != FALSE;

   }

   LRESULT interaction_impl::OnNcHitTest(point)
   {
      return Default();
   }
   void interaction_impl::OnNcLButtonDblClk(UINT, point)
   {
      Default();
   }
   void interaction_impl::OnNcLButtonDown(UINT, point)
   {
      Default();
   }
   void interaction_impl::OnNcLButtonUp(UINT, point)
   {
      Default();
   }
   void interaction_impl::OnNcMButtonDblClk(UINT, point)
   {
      Default();
   }
   void interaction_impl::OnNcMButtonDown(UINT, point)
   {
      Default();
   }
   void interaction_impl::OnNcMButtonUp(UINT, point)
   {
      Default();
   }
   void interaction_impl::OnNcMouseMove(UINT, point)
   {
      Default();
   }
   void interaction_impl::OnNcPaint()
   {
      Default();
   }
   void interaction_impl::OnNcRButtonDblClk(UINT, point)
   {
      Default();
   }
   void interaction_impl::OnNcRButtonDown(UINT, point)
   {
      Default();
   }
   void interaction_impl::OnNcRButtonUp(UINT, point)
   {
      Default();
   }
   void interaction_impl::OnSysChar(UINT, UINT, UINT)
   {
      Default();
   }
   void interaction_impl::OnSysCommand(UINT, LPARAM)
   {
      Default();
   }
   void interaction_impl::OnSysDeadChar(UINT, UINT, UINT)
   {
      Default();
   }
   void interaction_impl::OnSysKeyDown(UINT, UINT, UINT)
   {
      Default();
   }
   void interaction_impl::OnSysKeyUp(UINT, UINT, UINT)
   {
      Default();
   }
   void interaction_impl::OnCompacting(UINT)
   {
      Default();
   }
   void interaction_impl::OnFontChange()
   {
      Default();
   }
   void interaction_impl::OnPaletteChanged(::user::interaction *)
   {
      Default();
   }
   void interaction_impl::OnSpoolerStatus(UINT, UINT)
   {
      Default();
   }
   void interaction_impl::OnTimeChange()
   {
      Default();
   }
   void interaction_impl::OnChar(UINT, UINT, UINT)
   {
      Default();
   }
   void interaction_impl::OnDeadChar(UINT, UINT, UINT)
   {
      Default();
   }
   void interaction_impl::OnKeyDown(UINT, UINT, UINT)
   {
      Default();
   }
   void interaction_impl::OnKeyUp(UINT, UINT, UINT)
   {
      Default();
   }
   void interaction_impl::OnLButtonDblClk(UINT, point)
   {
      Default();
   }
   void interaction_impl::OnLButtonDown(UINT, point)
   {
      Default();
   }
   void interaction_impl::OnLButtonUp(UINT, point)
   {
      Default();
   }
   void interaction_impl::OnMButtonDblClk(UINT, point)
   {
      Default();
   }
   void interaction_impl::OnMButtonDown(UINT, point)
   {
      Default();
   }
   void interaction_impl::OnMButtonUp(UINT, point)
   {
      Default();
   }
   int32_t interaction_impl::OnMouseActivate(::user::interaction *, UINT, UINT)
   {
      return (int32_t)Default();
   }
   void interaction_impl::OnMouseMove(UINT, point)
   {
      Default();
   }

   bool interaction_impl::OnMouseWheel(UINT, short, point)
   {

      return Default() != FALSE;

   }

   LRESULT interaction_impl::OnRegisteredMouseWheel(WPARAM, LPARAM)
   {
      return Default();
   }
   void interaction_impl::OnRButtonDblClk(UINT, point)
   {
      Default();
   }
   void interaction_impl::OnRButtonDown(UINT, point)
   {
      Default();
   }
   void interaction_impl::OnRButtonUp(UINT, point)
   {
      Default();
   }
   void interaction_impl::OnTimer(uint_ptr)
   {
      Default();
   }
   void interaction_impl::OnInitMenu(::user::menu*)
   {
      Default();
   }
   void interaction_impl::OnInitMenuPopup(::user::menu*, UINT, bool)
   {
      Default();
   }
   void interaction_impl::OnAskCbFormatName(UINT nMaxCount, LPTSTR pszName)
   {
      //      (nMaxCount);
      if (nMaxCount > 0)
      {
         /* defwindow proc should do this for us, but to be safe, we'll do it here too */
         pszName[0] = '\0';
      }
      Default();
   }
   void interaction_impl::OnChangeCbChain(oswindow, oswindow)
   {
      Default();
   }
   void interaction_impl::OnDestroyClipboard()
   {
      Default();
   }
   void interaction_impl::OnDrawClipboard()
   {
      Default();
   }
   void interaction_impl::OnHScrollClipboard(::user::interaction *, UINT, UINT)
   {
      Default();
   }
   void interaction_impl::OnPaintClipboard(::user::interaction *, HGLOBAL)
   {
      Default();
   }
   void interaction_impl::OnRenderAllFormats()
   {
      Default();
   }
   void interaction_impl::OnRenderFormat(UINT)
   {
      Default();
   }
   void interaction_impl::OnSizeClipboard(::user::interaction *, HGLOBAL)
   {
      Default();
   }
   void interaction_impl::OnVScrollClipboard(::user::interaction *, UINT, UINT)
   {
      Default();
   }
   UINT interaction_impl::OnGetDlgCode()
   {
      return (UINT)Default();
   }
   void interaction_impl::OnMDIActivate(bool, ::user::interaction *, ::user::interaction *)
   {
      Default();
   }
   void interaction_impl::OnEnterMenuLoop(bool)
   {
      Default();
   }
   void interaction_impl::OnExitMenuLoop(bool)
   {
      Default();
   }
   // Win4 support
   //   void interaction_impl::OnStyleChanged(int32_t, LPSTYLESTRUCT)
   //   { Default(); }
   //   void interaction_impl::OnStyleChanging(int32_t, LPSTYLESTRUCT)
   //   { Default(); }
   void interaction_impl::OnSizing(UINT, LPRECT)
   {
      Default();
   }
   void interaction_impl::OnMoving(UINT, LPRECT)
   {
      Default();
   }
   void interaction_impl::OnCaptureChanged(::user::interaction *)
   {
      Default();
   }

   bool interaction_impl::OnDeviceChange(UINT, uint_ptr)
   {

      return Default() != FALSE;

   }

   void interaction_impl::OnWinIniChange(const char *)
   {
      Default();
   }
   void interaction_impl::OnChangeUIState(UINT, UINT)
   {
      Default();
   }
   void interaction_impl::OnUpdateUIState(UINT, UINT)
   {
      Default();
   }

   UINT interaction_impl::OnQueryUIState()
   {

      return (UINT)Default();

   }

   // user::interaction dialog data support
   //    void interaction_impl::DoDataExchange(CDataExchange*)
   //   { } // default does nothing

   // user::interaction modality support

   void interaction_impl::BeginModalState()
   {

      _throw(todo(get_app()));

      //::EnableWindow(get_handle(), FALSE);

   }

   void interaction_impl::EndModalState()
   {

      _throw(todo(get_app()));

      //::EnableWindow(get_handle(), TRUE);

   }

   // frame_window
   /*    void frame_window::DelayUpdateFrameTitle()
    { m_nIdleFlags |= idleTitle; }
    void frame_window::DelayRecalcLayout(bool bNotify)
    { m_nIdleFlags |= (idleLayout | (bNotify ? idleNotify : 0)); };
    bool frame_window::InModalState() const
    { return m_cModalStack != 0; }
    void frame_window::set_title(const char * lpszTitle)
    { m_strTitle = lpszTitle; }
    string frame_window::get_title() const
    { return m_strTitle; }
    */



   void interaction_impl::CloseWindow()
   {

      _throw(not_implemented(get_app()));
      //      ASSERT(::is_window(get_handle()));
      //      ::CloseWindow(get_handle());

   }

   bool interaction_impl::OpenIcon()
   {

      _throw(not_implemented(get_app()));
      //      ASSERT(::is_window(get_handle()));
      //      return ::OpenIcon(get_handle()) != FALSE;

   }

   ////////////////////////////////////////////////////////////////////////////
   // UI related ::user::interaction functions

   oswindow PASCAL interaction_impl::GetSafeOwner_(oswindow hParent, oswindow* pWndTop)
   {

      return NULL;

   }

   LRESULT CALLBACK __cbt_filter_hook(int32_t code, WPARAM wparam, LPARAM lparam)
   {

      _throw(not_implemented(get_app()));

   }



   void interaction_impl::_001OnEraseBkgnd(::message::message * pobj)
   {
      SCAST_PTR(::message::erase_bkgnd, perasebkgnd, pobj);
      perasebkgnd->m_bRet = true;
      perasebkgnd->set_result(TRUE);
   }

   void interaction_impl::_001BaseWndInterfaceMap()
   {

      Session.window_map().set((int_ptr)get_handle(), this);

   }


   void interaction_impl::_001OnTriggerMouseInside()
   {


      //_throw(not_implemented(get_app()));
      //      m_bMouseHover = true;
      //      TRACKMOUSEEVENT tme = { sizeof(tme) };
      //      tme.dwFlags = TME_LEAVE;
      //      tme.hwndTrack = get_handle();
      //      TrackMouseEvent(&tme);

   }


   void interaction_impl::round_window_draw(CGContextRef cgc)
   {

      round_window_draw_life_time roundwindowdrawlifetime(this);

      uint64_t delta = m_uiLastUpdateBeg - m_uiLastUpdateEnd;

      delta /= 1000 * 1000;

      if(delta < 10)
      {

         output_debug_string("round_window_draw less than 10\n");

      }
      else if(delta < 20)
      {

         output_debug_string("round_window_draw less than 20\n");

      }
      else if(delta < 50)
      {

         output_debug_string("round_window_draw less than 20\n");

      }
      else if(delta < 100)
      {

         output_debug_string("round_window_draw less than 100\n");

      }


      if (m_bUpdateGraphics)
      {

         update_graphics_resources();

      }

//      if(m_bOfflineRender)
//      {
//
//         return;
//
//      }


      cslock slDisplay(cs_display());

      window_buffer * pbuffer = m_spgraphics.cast < window_buffer >();

      if(pbuffer == NULL)
      {

         return;

      }

      synch_lock sl1(pbuffer->m_pmutex);

      ::draw2d::dib_sp & spdibBuffer = pbuffer->get_buffer();

      if (spdibBuffer.is_null())
      {

         return;

      }

      if (spdibBuffer->get_data() == NULL)
      {

         return;

      }

      ::draw2d::graphics_sp g(allocer());

      g->attach(cgc);

      ::rect rectClient;

      GetClientRect(rectClient);

      g->set_alpha_mode(::draw2d::alpha_mode_set);

      g->BitBlt(0, 0, spdibBuffer->m_size.cx, spdibBuffer->m_size.cy, spdibBuffer->get_graphics(), 0, 0, SRCCOPY);

   }


   bool interaction_impl::round_window_key_down(unsigned int uiKeyCode)
   {

      sp(::message::base) spbase;

      ::message::key * pkey = canew(::message::key(get_app()));

      pkey->m_id = WM_KEYDOWN;

      pkey->m_nChar = uiKeyCode;

      spbase = pkey;

      if(m_pui == NULL)
      {

         return false;

      }

      m_pui->post(spbase);

      return spbase->m_bRet;

   }


   bool interaction_impl::round_window_key_up(unsigned int uiKeyCode)
   {

      sp(::message::base) spbase;

      ::message::key * pkey = canew(::message::key(get_app()));

      pkey->m_id = WM_KEYUP;

      pkey->m_nChar = uiKeyCode;

      spbase = pkey;

      if(m_pui == NULL)
      {

         return false;

      }

      m_pui->post(spbase);

      return spbase->m_bRet;

   }


   bool interaction_impl::round_window_key_down(unsigned int vk, unsigned int scan)
   {

      sp(::message::base) spbase;

      ::message::key * pkey = canew(::message::key(get_app()));

      LRESULT l = 0;

      pkey->set(m_pui, WM_KEYDOWN, vk, (LPARAM)(scan << 16), l);

      spbase = pkey;

      if(m_pui == NULL)
      {

         return false;

      }

      m_pui->post(spbase);

      return spbase->m_bRet;

   }


   bool interaction_impl::round_window_key_up(unsigned int vk, unsigned int scan)
   {

      sp(::message::base) spbase;

      ::message::key * pkey = canew(::message::key(get_app()));

      LRESULT l = 0;

      pkey->set(m_pui, WM_KEYUP, vk, (LPARAM)(scan << 16), l);

      spbase = pkey;

      if(m_pui == NULL)
      {

         return false;

      }

      m_pui->post(spbase);

      return spbase->m_bRet;

   }


   void interaction_impl::round_window_mouse_down(int iButton, double x, double y)
   {

      sp(::message::base) spbase;

      if (::get_active_window() != get_handle())
      {

         try
         {

            ::message::mouse_activate * pmouseactivate = canew(::message::mouse_activate(get_app()));

            pmouseactivate->m_id = WM_MOUSEACTIVATE;

            spbase = pmouseactivate;

            m_pui->send(spbase);

            if (spbase->get_lresult() == MA_ACTIVATE || spbase->get_lresult() == MA_ACTIVATEANDEAT)
            {

               ::message::activate * pactivate = canew(::message::activate(get_app()));

               pactivate->m_id = WM_ACTIVATE;
               pactivate->m_wparam = WA_CLICKACTIVE;
               pactivate->m_nState = WA_CLICKACTIVE;
               pactivate->m_bMinimized = false;

               spbase = pactivate;

               if(m_pui == NULL)
               {

                  return;

               }

               m_pui->send(spbase);

            }

         }
         catch (...)
         {

         }

      }

      {

         ::message::mouse * pmouse = canew(::message::mouse(get_app()));

         if (iButton == 1)
         {

            pmouse->m_id = WM_RBUTTONDOWN;

         }
         else
         {

            pmouse->m_id = WM_LBUTTONDOWN;

         }

         pmouse->m_pt.x = (LONG)x;
         pmouse->m_pt.y = (LONG)y;
         pmouse->m_bTranslated = true;

         spbase = pmouse;

         if(m_pui == NULL)
         {

            return;

         }

         m_pui->post(spbase);

      }

   }


   void interaction_impl::round_window_mouse_up(int iButton, double x, double y)
   {

      sp(::message::base) spbase;

      ::message::mouse * pmouse = canew(::message::mouse(get_app()));

      if (iButton == 1)
      {

         pmouse->m_id = WM_RBUTTONUP;

      }
      else
      {

         pmouse->m_id = WM_LBUTTONUP;

      }

      pmouse->m_pt.x = (LONG)x;
      pmouse->m_pt.y = (LONG)y;
      pmouse->m_bTranslated = true;

      spbase = pmouse;

      if(m_pui == NULL)
      {

         return;

      }

      m_pui->post(spbase);

   }


   void interaction_impl::round_window_double_click(int iButton, double x, double y)
   {

      sp(::message::base) spbase;

      ::message::mouse * pmouse = canew(::message::mouse(get_app()));

      if (iButton == 1)
      {

         pmouse->m_id = WM_RBUTTONDBLCLK;

      }
      else
      {

         pmouse->m_id = WM_LBUTTONDBLCLK;

      }

      pmouse->m_pt.x = (LONG)x;
      pmouse->m_pt.y = (LONG)y;
      pmouse->m_bTranslated = true;

      spbase = pmouse;

      if(m_pui == NULL)
      {

         return;

      }

      m_pui->post(spbase);

   }


   void interaction_impl::round_window_mouse_moved(double x, double y, unsigned long ulAppleMouseButton)
   {

      sp(::message::base) spbase;

      ::message::mouse * pmouse = canew(::message::mouse(get_app()));

      pmouse->m_id = WM_MOUSEMOVE;
      pmouse->m_pt.x = (LONG)x;
      pmouse->m_pt.y = (LONG)y;
      pmouse->m_bTranslated = true;

      if(ulAppleMouseButton & 1)
      {

         pmouse->m_wparam |= MK_LBUTTON;

      }

      if(ulAppleMouseButton & 2)
      {

         pmouse->m_wparam |= MK_RBUTTON;

      }

      pmouse->m_nFlags = pmouse->m_wparam;

      spbase = pmouse;

      if(m_pui == NULL)
      {

         return;

      }

      m_pui->post(spbase);

   }


   void interaction_impl::round_window_mouse_dragged(double x, double y, unsigned long ulAppleMouseButton)
   {

      sp(::message::base) spbase;

      ::message::mouse * pmouse = canew(::message::mouse(get_app()));

      pmouse->m_id = WM_MOUSEMOVE;
      pmouse->m_pt.x = (LONG)x;
      pmouse->m_pt.y = (LONG)y;
      pmouse->m_bTranslated = true;

      if(ulAppleMouseButton & 1)
      {

         pmouse->m_wparam |= MK_LBUTTON;

      }

      if(ulAppleMouseButton & 2)
      {

         pmouse->m_wparam |= MK_RBUTTON;

      }

      pmouse->m_nFlags = pmouse->m_wparam;

      spbase = pmouse;

      if(m_pui == NULL)
      {

         return;

      }

      m_pui->post(spbase);

   }


   void interaction_impl::round_window_mouse_wheel(double deltaY, double x, double y)
   {

      sp(::message::base) spbase;

      {

         ::message::mouse_wheel * pwheel = canew(::message::mouse_wheel(get_app()));

         pwheel->m_id = WM_MOUSEWHEEL;

         pwheel->m_pt.x = (LONG)x;
         pwheel->m_pt.y = (LONG)y;
         pwheel->m_bTranslated = true;

         short delta = deltaY * WHEEL_DELTA / 3.0;

         pwheel->m_wparam = delta << 16;

         spbase = pwheel;

         if(m_pui == NULL)
         {

            return;

         }

         m_pui->post(spbase);

      }

   }


   void interaction_impl::round_window_resized(CGRect rect)
   {

      if(m_pui == NULL)
      {

         return;

      }

      ::size sz;

      point64 pt(rect.origin.x, rect.origin.y);

      bool bMove = false;

      {

         synch_lock sl(m_pui->m_pmutex);

         if (pt != m_rectParentClient.top_left())
         {

            bMove = true;

         }

         m_rectParentClient.move_to(pt);

         m_rectParentClient.size(rect.size.width, rect.size.height);

         sz = m_rectParentClient.get_size();

      }

      if(m_pui == NULL)
      {

         return;

      }

      m_pui->post_message(WM_SIZE, 0, sz.lparam());

      if (bMove)
      {

         m_pui->post_message(WM_MOVE, 0, pt.lparam());

      }

   }


   void interaction_impl::round_window_moved(CGPoint point)
   {

      ::point pt;

      {

         synch_lock sl(m_pui->m_pmutex);

         m_rectParentClient.move_to(point.x, point.y);

         pt = m_rectParentClient.top_left();

      }

      if(m_pui == NULL)
      {

         return;

      }

      m_pui->post_message(WM_MOVE, 0, pt.lparam());

   }


   void interaction_impl::round_window_activate()
   {

      ::set_active_window(get_handle());

      if(m_pui == NULL)
      {

         return;

      }

      m_pui->set_need_redraw();

   }


   void interaction_impl::round_window_deactivate()
   {

      ::deactivate_window(get_handle());

      if(m_pui == NULL)
      {

         return;

      }

      m_pui->set_need_redraw();

   }


   void interaction_impl::round_window_iconified()
   {

      if(m_pui == NULL)
      {

         return;

      }

      m_pui->m_eappearanceBefore = m_pui->m_eappearance;

      m_pui->m_eappearance = ::user::appearance_iconic;

   }


   void interaction_impl::round_window_deiconified()
   {

      if(m_pui == NULL)
      {

         return;

      }

      if(m_pui->m_eappearanceBefore == ::user::appearance_iconic)
      {

         m_pui->m_eappearanceBefore = ::user::appearance_normal;

      }

      m_pui->_001OnDeiconify(m_pui->m_eappearanceBefore);

   }


   void interaction_impl::round_window_on_show()
   {

      if(m_pui == NULL)
      {

         return;

      }

      m_pui->message_call(WM_SHOWWINDOW, 1);

   }


   void interaction_impl::round_window_on_hide()
   {

      if(m_pui == NULL)
      {

         return;

      }

      m_pui->message_call(WM_SHOWWINDOW, 0);

   }



   __STATIC void CLASS_DECL_AURA __pre_init_dialog(
   ::user::interaction * pWnd, LPRECT lpRectOld, DWORD* pdwStyleOld)
   {
      ASSERT(lpRectOld != NULL);
      ASSERT(pdwStyleOld != NULL);

      pWnd->GetWindowRect(lpRectOld);
      *pdwStyleOld = pWnd->GetStyle();
   }

//   __STATIC void CLASS_DECL_AURA __post_init_dialog(
//      ::user::interaction * p, const RECT& rectOld, DWORD dwStyleOld)
//   {
//      // must be hidden to start with
//      if (dwStyleOld & WS_VISIBLE)
//         return;
//
//      // must not be visible after WM_INITDIALOG
//      if (pWnd->GetStyle() & (WS_VISIBLE | WS_CHILD))
//         return;
//
//      // must not move during WM_INITDIALOG
//      rect rect;
//      pWnd->GetWindowRect(rect);
//      if (rectOld.left != rect.left || rectOld.top != rect.top)
//         return;
//
//      // must be unowned or owner disabled
//      ::user::interaction * pParent = pWnd->GetWindow(GW_OWNER);
//      if (pParent != NULL && pParent->is_window_enabled())
//         return;
//
//      if (!pWnd->CheckAutoCenter())
//         return;
//
//      // center modal dialog boxes/message boxes
//      //MAC_WINDOW(pWnd)->CenterWindow();
//   }



   CLASS_DECL_AURA void hook_window_create(::user::interaction * pui)
   {

      UNREFERENCED_PARAMETER(pui);

   }


   CLASS_DECL_AURA bool unhook_window_create()
   {

      return true;

   }


   __STATIC void CLASS_DECL_AURA
   __handle_activate(::user::interaction * pWnd, WPARAM nState, ::user::interaction * pWndOther)
   {

      _throw(not_implemented(get_app()));
      //   ASSERT(pWnd != NULL);
      //
      //   // m_pui->send WM_ACTIVATETOPLEVEL when top-level parents change
      //   if (!(MAC_WINDOW(pWnd)->GetStyle() & WS_CHILD))
      //   {
      //      ::user::interaction * pTopLevel= MAC_WINDOW(pWnd)->GetTopLevelParent();
      //      if (pTopLevel && (pWndOther == NULL || !::is_window(MAC_WINDOW(pWndOther)->get_handle()) || pTopLevel != MAC_WINDOW(pWndOther)->GetTopLevelParent()))
      //      {
      //         // lparam points to user::interaction getting the WM_ACTIVATE message and
      //         //  hWndOther from the WM_ACTIVATE.
      //         oswindow hWnd2[2];
      //         hWnd2[0] = MAC_WINDOW(pWnd)->get_handle();
      //         if(pWndOther == NULL || MAC_WINDOW(pWndOther) == NULL)
      //         {
      //            hWnd2[1] = NULL;
      //         }
      //         else
      //         {
      //            hWnd2[1] = MAC_WINDOW(pWndOther)->get_handle();
      //         }
      //         // m_pui->send it...
      //         pTopLevel->send_message(WM_ACTIVATETOPLEVEL, nState, (LPARAM)&hWnd2[0]);
      //      }
      //   }
   }

   __STATIC bool CLASS_DECL_AURA
   __handle_set_cursor(::user::interaction * pWnd, UINT nHitTest, UINT nMsg)
   {

      _throw(not_implemented(get_app()));
      //   if (nHitTest == HTERROR &&
      //      (nMsg == WM_LBUTTONDOWN || nMsg == WM_MBUTTONDOWN ||
      //      nMsg == WM_RBUTTONDOWN))
      //   {
      //      // activate the last active user::interaction if not active
      //      ::user::interaction * pLastActive = MAC_WINDOW(pWnd)->GetTopLevelParent();
      //      if (pLastActive != NULL)
      //         pLastActive = pLastActive->GetLastActivePopup();
      //      if (pLastActive != NULL &&
      //         pLastActive != ::macos::interaction_impl::GetForegroundWindow() &&
      //         pLastActive->IsWindowEnabled())
      //      {
      //         pLastActive->SetForegroundWindow();
      //         return TRUE;
      //      }
      //   }
      //   return FALSE;
   }





   LRESULT CALLBACK
   __activation_window_procedure(oswindow hWnd, UINT nMsg, WPARAM wparam, LPARAM lparam)
   {

      _throw(not_implemented(get_app()));
      //   WNDPROC oldWndProc = (WNDPROC)::GetProp(hWnd, gen_OldWndProc);
      //   ASSERT(oldWndProc != NULL);
      //
      //   LRESULT lResult = 0;
      //   try
      //   {
      //      bool bCallDefault = TRUE;
      //      switch (nMsg)
      //      {
      //      case WM_INITDIALOG:
      //         {
      //            DWORD dwStyle;
      //            rect rectOld;
      //            ::user::interaction * pWnd = ::macos::interaction_impl::from_handle(hWnd);
      //            __pre_init_dialog(pWnd, &rectOld, &dwStyle);
      //            bCallDefault = FALSE;
      //            lResult = CallWindowProc(oldWndProc, hWnd, nMsg, wparam, lparam);
      //            __post_init_dialog(pWnd, rectOld, dwStyle);
      //         }
      //         break;
      //
      //      case WM_ACTIVATE:
      //         __handle_activate(::macos::interaction_impl::from_handle(hWnd), wparam,
      //            ::macos::interaction_impl::from_handle((oswindow)lparam));
      //         break;
      //
      //      case WM_SETCURSOR:
      //         bCallDefault = !__handle_set_cursor(::macos::interaction_impl::from_handle(hWnd),
      //            (short)LOWORD(lparam), HIWORD(lparam));
      //         break;
      //
      //      case WM_NCDESTROY:
      //         SetWindowLongPtr(hWnd, GWLP_WNDPROC, reinterpret_cast<int_ptr>(oldWndProc));
      //         RemoveProp(hWnd, gen_OldWndProc);
      //         GlobalDeleteAtom(GlobalFindAtom(gen_OldWndProc));
      //         break;
      //      }
      //
      //      // call original wndproc for default handling
      //      if (bCallDefault)
      //         lResult = CallWindowProc(oldWndProc, hWnd, nMsg, wparam, lparam);
      //   }
      //   catch(::exception::aura * pe)
      //   {
      //      // handle exception
      //      MESSAGE msg;
      //      msg.hwnd = hWnd;
      //      msg.message = nMsg;
      //      msg.wparam = wparam;
      //      msg.lparam = lparam;
      //
      //      //lResult = __process_window_procedure_exception(pe, &msg);
      //      //      TRACE(::ca2::trace::category_AppMsg, 0, "Warning: Uncaught exception in __activation_window_procedure (returning %ld).\n",
      //      //       lResult);
      //      pe->Delete();
      //   }
      //
      //
      //   return lResult;
   }


   void interaction_impl::offset_viewport_org(LPRECT lprectScreen)
   {

   }


   void interaction_impl::set_viewport_org(::draw2d::graphics * pgraphics)
   {

      // graphics will be already set its view port to the user::interaction for linux - cairo with xlib

      pgraphics->SetViewportOrg(point(0, 0));

   }


   void interaction_impl::_001WindowMinimize()
   {

      if(get_handle() == NULL)
      {

         return;

      }

      round_window_iconified();

      get_handle()->iconify();

   }


} // namespace macos



