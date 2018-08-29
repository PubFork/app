#include "framework.h"

#ifdef WINDOWSEX
#include <dde.h>
#include <dwmapi.h>
#include <VersionHelpers.h>
#include <shellapi.h>
#pragma comment(lib, "Dwmapi.lib" )
#ifndef WM_NCUAHDRAWCAPTION
#define WM_NCUAHDRAWCAPTION (0x00AE)
#endif
#ifndef WM_NCUAHDRAWFRAME
#define WM_NCUAHDRAWFRAME (0x00AF)
#endif
static bool has_autohide_appbar(UINT edge, RECT mon) // Interface Update - Infinisys Ltd.
{
   if (IsWindows8Point1OrGreater())
   {
      APPBARDATA data = {};
      data.cbSize = sizeof(APPBARDATA);
      data.uEdge = edge;
      data.rc = mon;
      return SHAppBarMessage(0x0000000b, &data);
   }

   /* Before Windows 8.1, it was not possible to specify a monitor when
    checking for hidden appbars, so check only on the primary monitor */
   if (mon.left != 0 || mon.top != 0)
      return false;
   APPBARDATA data = {};
   data.cbSize = sizeof(APPBARDATA);
   data.uEdge = edge;
   return SHAppBarMessage(ABM_GETAUTOHIDEBAR, &data);
}
#endif


#define TEST 0


extern CLASS_DECL_CORE thread_int_ptr < DWORD_PTR > t_time1;


simple_frame_window::helper_task::helper_task(simple_frame_window * pframe) :
   ::object(pframe->get_app()),
   ::thread(pframe->get_app()),
   m_pframe(pframe)
{

   begin();

}


void simple_frame_window::helper_task::run()
{

   while(thread_get_run())
   {

      Sleep(500);

      if(m_pframe->m_bPendingSaveWindowPlacement && m_pframe->m_bEnableSaveWindowRect)
      {

         if(::get_tick_count() - m_pframe->m_dwLastSizeMove > 300)
         {

            m_pframe->m_bSizeMove = false;

            try
            {

               if(m_pframe->WindowDataSaveWindowRect())
               {

                  m_pframe->m_bPendingSaveWindowPlacement = false;

               }

            }
            catch(...)
            {

            }

         }

      }

   }

}


void simple_frame_window::helper_task::defer_save_window_rect()
{

}

prodevian_translucent_simple_frame_window::prodevian_translucent_simple_frame_window(::aura::application * papp) :
   object(papp),
   simple_frame_window(papp, true, true)
{

}


simple_frame_window::simple_frame_window(::aura::application * papp) :
   object(papp),
   m_dibBk(allocer()),
   m_fastblur(allocer())
{

   simple_frame_window_common_construct(false, false);

}


simple_frame_window::simple_frame_window(::aura::application * papp, bool bProdevian, bool bTranslucent) :
   object(papp),
   m_dibBk(allocer()),
   m_fastblur(allocer())
{

   simple_frame_window_common_construct(bProdevian, bTranslucent);

}


void simple_frame_window::simple_frame_window_common_construct(bool bProdevian, bool bTranslucent)
{

   if (bProdevian)
   {



   }

   if (bTranslucent)
   {

      set_translucent();

   }

   m_bPendingSaveWindowPlacement = false;

   m_bDefaultCreateToolbar = true;

   m_etranslucency = ::user::translucency_undefined;

   m_bShowTask = true;

   m_bDefaultNotifyIcon = false;

   m_bTransparentFrame = false;

#if defined(METROWIN)

   m_bTransparentFrameEnable = false;

#else

   m_bTransparentFrameEnable = true;

#endif

   //m_bblur_Background = false;

   m_bCustomFrameBefore = true;

#if defined(APPLE_IOS) || defined(VSNORD)

   m_bWindowFrame = false;

#else

   m_bWindowFrame = true;

#endif

   m_bLayered = true;

   m_pframeschema = NULL;

   m_pdocumenttemplate = NULL;

   //m_phelpertask = new helper_task(this);

}


simple_frame_window::~simple_frame_window()
{

   //m_phelpertask->m_pframe = NULL;

   //m_phelpertask->m_bRun = false;

}


prodevian_translucent_simple_frame_window::~prodevian_translucent_simple_frame_window()
{

}


void simple_frame_window::assert_valid() const
{

   ::user::frame_window::assert_valid();

}

void simple_frame_window::dump(dump_context & dumpcontext) const
{

   ::user::frame_window::dump(dumpcontext);

}

void simple_frame_window::install_message_routing(::message::sender * pinterface)
{
   ::user::frame_window::install_message_routing(pinterface);
   IGUI_MSG_LINK(WM_CREATE, pinterface, this, &simple_frame_window::_001OnCreate);
   IGUI_MSG_LINK(WM_NCACTIVATE, pinterface, this, &simple_frame_window::_001OnNcActivate);
#ifdef WINDOWSEX
   IGUI_MSG_LINK(WM_DDE_INITIATE, pinterface, this, &simple_frame_window::_001OnDdeInitiate);
#endif
   IGUI_MSG_LINK(WM_DESTROY, pinterface, this, &simple_frame_window::_001OnDestroy);
   IGUI_MSG_LINK(WM_CLOSE, pinterface, this, &simple_frame_window::_001OnClose);
   IGUI_MSG_LINK(WM_SIZE, pinterface, this, &simple_frame_window::_001OnSize);
   IGUI_MSG_LINK(WM_MOVE, pinterface, this, &simple_frame_window::_001OnMove);
   IGUI_MSG_LINK(WM_SYSCOMMAND, pinterface, this, &simple_frame_window::_001OnSysCommand);
   IGUI_MSG_LINK(WM_GETMINMAXINFO, pinterface, this, &simple_frame_window::_001OnGetMinMaxInfo);
   IGUI_MSG_LINK(WM_MOUSEMOVE, pinterface, this, &simple_frame_window::_001OnMouseMove);
   IGUI_MSG_LINK(WM_DISPLAYCHANGE, pinterface, this, &simple_frame_window::_001OnDisplayChange);
   IGUI_MSG_LINK(WM_SHOWWINDOW, pinterface, this, &simple_frame_window::_001OnShowWindow);
   IGUI_MSG_LINK(WM_DWMNCRENDERINGCHANGED, pinterface, this, &simple_frame_window::_001OnDwm);
   IGUI_MSG_LINK(WM_NCCALCSIZE, pinterface, this, &simple_frame_window::_001OnNcCalcSize);

   connect_command_probe("transparent_frame", &simple_frame_window::_001OnUpdateToggleTransparentFrame);
   connect_command("transparent_frame", &simple_frame_window::_001OnToggleTransparentFrame);

   connect_command_probe("view_full_screen", &simple_frame_window::_001OnUpdateViewFullScreen);
   connect_command("view_full_screen", &simple_frame_window::_001OnViewFullScreen);

   connect_command("app_exit", &simple_frame_window::_001OnAppExit);

   IGUI_MSG_LINK(WM_APPEXIT, pinterface, this, &simple_frame_window::_001OnAppExit);
   IGUI_MSG_LINK(WM_ACTIVATEAPP, pinterface, this, &simple_frame_window::_001OnActivateApp);
   IGUI_MSG_LINK(WM_ACTIVATE, pinterface, this, &simple_frame_window::_001OnActivate);

#ifdef WINDOWSEX

   IGUI_MSG_LINK(System.m_uiWindowsTaskbarCreatedMessage, pinterface, this, &simple_frame_window::_001OnTaskbarCreated);

#endif

}




bool simple_frame_window::IsFullScreen()
{

   return WfiIsFullScreen();

}


sp(::user::interaction) simple_frame_window::WindowDataGetWnd()
{

   return this;

}


void simple_frame_window::_001OnDestroy(::message::message * pobj)
{

   pobj->previous();

   try
   {

      if (m_pnotifyicon.is_set())
      {

         m_pnotifyicon->Destroy();

         m_pnotifyicon.release();

      }

   }
   catch(...)
   {

   }

   if(m_phelpertask.is_set())
   {

      ::multithreading::post_quit_and_wait(m_phelpertask, seconds(5));

      m_phelpertask.release();

   }

}


sp(::user::wndfrm::frame::frame) simple_frame_window::create_frame_schema()
{

   if(Application.wndfrm() == NULL)
   {

      return NULL;

   }

   if(Application.m_puiMain != NULL)
   {

      sp(::simple_frame_window) pframe = Application.m_puiMain;

      if(pframe.is_set())
      {

         auto pschemaRef = pframe->m_workset.m_pframeschema;

         if(pschemaRef.is_set())
         {

            sp(::user::wndfrm::frame::frame) pschema = Application.wndfrm()->get_frame_schema(pschemaRef->m_strLibrary, pschemaRef->m_strName);

            if(pschema.is_set())
            {

               if(GetExStyle() & WS_EX_TOOLWINDOW)
               {

                  //pschema->m_bHollow = false;

               }

               pschema->set_style(pschemaRef->m_strStyle);

               return pschema;

            }

         }

      }

   }

   sp(::user::wndfrm::frame::frame) pschema = Application.wndfrm()->get_frame_schema(m_varFrame["wndfrm"], m_varFrame["schema"]);

   pschema->set_style(m_varFrame["style"]);

   return pschema;

}


void simple_frame_window::_001OnCreate(::message::message * pobj)
{

   SCAST_PTR(::message::create, pcreate, pobj);

#if !defined(APPLE_IOS) && !defined(VSNORD)

   if (m_pdocumenttemplate->m_strMatter.has_char())
   {

      m_varFrame = Application.file().as_json("matter://" + m_pdocumenttemplate->m_strMatter + "/frame.json");

   }

#endif

   if (m_varFrame["schema"].is_empty())
   {

      m_varFrame["schema"] = "005";

   }

   if (m_varFrame["style"].is_empty())
   {

      m_varFrame["style"] = "DarkWarmBlue";

   }

   if (m_varFrame["control_box"]["transparent_button"]["visible"].is_false()
         || !m_bTransparentFrameEnable)
   {

      m_workset.m_ebuttonaHide.add(::user::wndfrm::frame::button_transparent_frame);

   }
   if (m_varFrame["control_box"]["dock_button"]["visible"].is_false())
   {

      m_workset.m_ebuttonaHide.add(::user::wndfrm::frame::button_dock);

   }


   sp(::user::place_holder) pplaceholder = GetParent();

   if (pplaceholder != NULL)
   {
      sp(::user::place_holder_container) pcontainer = pplaceholder->GetParent();
      if (pcontainer != NULL)
      {
         pcontainer->on_hold(this, pplaceholder);
      }
   }

   if (m_bAutoWindowFrame)
   {
      if(Application.handler()->m_varTopicQuery.has_property("client_only"))
      {
         m_bWindowFrame = false;
      }
      else
      {
#if defined(METROWIN) || defined(APPLE_IOS)
         m_bWindowFrame = GetParent() == NULL || GetParent()->m_pimpl != NULL;
#else
         m_bWindowFrame = GetParent() == NULL;
#endif
      }
   }


   on_select_user_style();


   if (pobj->previous())
   {

      return;

   }

   if (GetParent() == NULL)
   {

      if (m_workset.m_ebuttonaHide.contains(::user::wndfrm::frame::button_transparent_frame))
      {

         m_bTransparentFrame = false;

      }
      else
      {

         fork([&]()
         {

            data_get("transparent_frame", m_bTransparentFrame);

            set_need_layout();

            set_need_redraw();

         });

      }

   }

   if (m_bWindowFrame)
   {

      sp(::user::wndfrm::frame::frame) pinteractionframe = NULL;

      try
      {

         pinteractionframe = create_frame_schema();

      }
      catch (::exception::exception * pexception)
      {

         esp671 esp(pexception);

      }
      catch (...)
      {

         pcreate->m_lresult = -1;

         pcreate->m_bRet = true;

         return;

      }

      if(pinteractionframe == NULL)
      {

         pcreate->m_lresult = -1;

         pcreate->m_bRet = true;

         return;

      }

      m_pframeschema = pinteractionframe;

      m_workset.AttachFrameSchema(m_pframeschema);

      if (!m_workset.update(
            this,
            this,
            this,
            this))
      {
         pcreate->m_bRet = false;
         return;
      }

#if defined(LINUX) || defined(APPLEOS)

      m_workset.SetActiveFlag(TRUE);

#endif

   }

   m_strTitle = Application.get_app_user_friendly_task_bar_name();

   defer_synch_layered();

   create_bars();

   defer_set_icon();

   defer_create_notification_icon();

   m_pimpl->show_task(m_bShowTask);

   if(GetParent() == NULL)
   {

      if(m_phelpertask.is_null())
      {

         m_phelpertask = canew(helper_task(this));

      }

   }

   pcreate->m_bRet = false;

}



void simple_frame_window::_001OnShowWindow(::message::message * pobj)
{

   SCAST_PTR(::message::show_window, pshow, pobj);

   if(pshow->m_bShow)
   {

      output_debug_string("\nsimple_frame_window::_001OnShowWindow TRUE " + string(typeid(*this).name()));

   }
   else
   {

      output_debug_string("\nsimple_frame_window::_001OnShowWindow FALSE " + string(typeid(*this).name()));

   }

   defer_set_icon();

   if(m_bDefaultNotifyIcon)
   {

      if(m_pnotifyicon != NULL)
      {
         m_pnotifyicon->step();

      }
      OnUpdateToolWindow(pshow->m_bShow);

   }

}


void simple_frame_window::_001OnDisplayChange(::message::message * pobj)
{

   SCAST_PTR(::message::base, pbase, pobj);

   post_simple_command(simple_command_load_window_rect, (LPARAM)FALSE);

   pobj->m_bRet = true;

   pbase->set_lresult(0);

   Default();

}



void simple_frame_window::_001OnTaskbarCreated(::message::message * pobj)
{

   defer_create_notification_icon();

}


void simple_frame_window::_001OnSize(::message::message * pobj)
{

   UNREFERENCED_PARAMETER(pobj);

   m_dwLastSizeMove = get_tick_count();

   m_bPendingSaveWindowPlacement = true;

}


void simple_frame_window::_001OnMove(::message::message * pobj)
{

   UNREFERENCED_PARAMETER(pobj);

   m_dwLastSizeMove = get_tick_count();

   m_bPendingSaveWindowPlacement = true;

}


bool simple_frame_window::on_create_client(::user::create_struct * lpcs, ::create * pcreate)
{

   return ::user::frame_window::on_create_client(lpcs, pcreate);

}


bool simple_frame_window::pre_create_window(::user::create_struct& cs)
{

   if (!::user::frame_window::pre_create_window(cs))
   {

      return false;

   }

   //cs.style = WS_OVERLAPPEDWINDOW & ~WS_THICKFRAME;
   cs.style |= WS_POPUP;
   cs.style &= ~WS_VISIBLE;
   cs.style |= WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX;

   return true;

}


void simple_frame_window::on_layout()
{

   if (m_bWindowFrame && m_workset.IsAppearanceEnabled())
   {

      m_workset.on_layout();

   }
   else
   {

      ::user::frame_window::on_layout();

   }

}


void simple_frame_window::ViewOnActivateFrame(sp(::user::impact) pview, UINT user, sp(::user::interaction) pframe)
{
   UNREFERENCED_PARAMETER(pview);
   UNREFERENCED_PARAMETER(user);
   UNREFERENCED_PARAMETER(pframe);
   //   if(pview != NULL)
   //      pview->OnActivateFrame(WA_INACTIVE, (sp(::user::simple_frame_window)) pframe);
}

void simple_frame_window::_001OnGetMinMaxInfo(::message::message * pobj)
{
#ifdef WINDOWSEX
   SCAST_PTR(::message::base, pbase, pobj);
   MINMAXINFO FAR * lpMMI = (MINMAXINFO FAR*) pbase->m_lparam.m_lparam;
   if (IsFullScreen())
   {
      lpMMI->ptMaxSize.y = m_FullScreenWindowRect.height();
      lpMMI->ptMaxTrackSize.y = lpMMI->ptMaxSize.y;
      lpMMI->ptMaxSize.x = m_FullScreenWindowRect.width();
      lpMMI->ptMaxTrackSize.x = lpMMI->ptMaxSize.x;
   }
#else
   _throw(todo(get_app()));
#endif
}


void simple_frame_window::ShowControlBars(bool bShow, bool bLeaveFullScreenBarsOnHide)
{

   UINT nShow;

   if (bShow)
   {

      nShow = SW_SHOW;

   }
   else
   {

      nShow = SW_HIDE;

   }

   POSITION pos = m_toolbarmap.get_start_position();

   id idKey;

   ::user::toolbar * pbar;

   while (pos != NULL)
   {

      m_toolbarmap.get_next_assoc(pos, idKey, pbar);

      try
      {

         if(pbar != NULL && (bShow || (!pbar->m_bFullScreenBar || !bLeaveFullScreenBarsOnHide)))
         {

            pbar->ShowWindow(nShow);

         }

      }
      catch (...)
      {

      }

   }

   on_layout();

}


void simple_frame_window::WfiOnFullScreen()
{

   ShowControlBars(false, true);

   _001WindowFullScreen();

}

bool simple_frame_window::WfiToggleTransparentFrame()
{

   if (m_workset.m_ebuttonaHide.contains(::user::wndfrm::frame::button_transparent_frame))
   {

      m_bTransparentFrame = false;

      return false;

   }

   m_bTransparentFrame = !m_bTransparentFrame;

   data_set("transparent_frame",m_bTransparentFrame);

   set_need_layout();

   set_need_redraw();

   return true;

}


bool simple_frame_window::frame_is_transparent()
{

   return m_bTransparentFrame && m_bTransparentFrameEnable;

}


void simple_frame_window::WfiOnExitFullScreen()
{

   ShowControlBars(true);

   WorkSetClientInterface::WfiOnExitFullScreen();

}


void simple_frame_window::_001OnViewFullScreen(::message::message * pobj)
{

   UNREFERENCED_PARAMETER(pobj);

   ToggleFullScreen();

}


void simple_frame_window::_001OnMouseMove(::message::message * pobj)
{

   UNREFERENCED_PARAMETER(pobj);

}


void simple_frame_window::_001OnUpdateViewFullScreen(::message::message * pobj)
{
   SCAST_PTR(::user::command, pcommand, pobj);
   pcommand->Enable();
   pcommand->_001SetCheck(WfiIsFullScreen());
   pcommand->m_bRet = true;
}


void simple_frame_window::ToggleFullScreen()
{

   if (WfiIsFullScreen())
   {

      WfiRestore(false);

   }
   else
   {

      WfiFullScreen();

   }

}


bool simple_frame_window::_001CanEnterScreenSaver()
{
   return true;
}

void simple_frame_window::_001OnSysCommand(::message::message * pobj)
{
   SCAST_PTR(::message::base, pbase, pobj);

   if (pbase->m_wparam == SC_SCREENSAVE)
   {
      if (!_001CanEnterScreenSaver())
      {
         pbase->m_bRet = true;
         pbase->set_lresult(0);
         return;
      }
   }

   if (m_bWindowFrame)
   {
      if (pbase->m_wparam == SC_MAXIMIZE)
      {
         WfiMaximize();
         pbase->m_bRet = true;
         pbase->set_lresult(0);
      }
      else if (pbase->m_wparam == SC_RESTORE)
      {
         if (WfiIsFullScreen())
         {
            WfiFullScreen();
         }
         else
         {
            WfiRestore(false);
         }
         pbase->m_bRet = true;
         pbase->set_lresult(0);
      }
      else if (pbase->m_wparam == SC_MINIMIZE)
      {
         WfiMinimize();
         pbase->m_bRet = true;
         pbase->set_lresult(0);
      }
   }

}


void simple_frame_window::_001OnToggleCustomFrame(::message::message * pobj)
{
   UNREFERENCED_PARAMETER(pobj);
   SetCustomFrame(!GetCustomFrame());
}

void simple_frame_window::_001OnUpdateToggleCustomFrame(::message::message * pobj)
{
   SCAST_PTR(::user::command, pcommand, pobj);
   pcommand->Enable();
   pcommand->_001SetCheck(m_bWindowFrame);
}


void simple_frame_window::_001OnToggleTransparentFrame(::message::message * pobj)
{

   UNREFERENCED_PARAMETER(pobj);

   WfiToggleTransparentFrame();

}


void simple_frame_window::_001OnUpdateToggleTransparentFrame(::message::message * pobj)
{

   SCAST_PTR(::user::command, pcommand, pobj);

   pcommand->Enable();

   //if (GetTopLevelFrame()->frame_is_transparent())
   //{

   //   MessageBox(NULL, "ft", "", MB_OK);

   //}
   //else
   //{

   //   MessageBox(NULL, "fnt", "", MB_OK);

   //}

   pcommand->_001SetCheck(frame_is_transparent());

}


void simple_frame_window::ActivateFrame(int32_t nCmdShow)
{

   ::user::frame_window::ActivateFrame(nCmdShow);
}

void simple_frame_window::GetBorderRect(LPRECT lprect)
{
   *lprect = m_rectBorder;
}

void simple_frame_window::SetBorderRect(const RECT & rect)
{
   m_rectBorder = rect;
}

void simple_frame_window::SetCustomFrame(bool bCustom)
{
   m_bWindowFrame = bCustom;
   m_workset.Enable(bCustom);
   on_layout();
   set_need_redraw();

}

bool simple_frame_window::GetCustomFrame()
{
   return m_bWindowFrame;
}


void simple_frame_window::_001OnAppExit(::message::message * pobj)
{

   if (get_parent() != NULL)
   {

      pobj->m_bRet = false;

      return;

   }

   //if (!m_bDefaultNotifyIcon)
   //m_bDefaultNotifyIcon = false;
   //{

   //_001OnClose(pobj);

   // return;

   //}

   if(pobj != NULL)
   {

      pobj->m_bRet = true;

   }

   System.request_exit();


}


void simple_frame_window::_001OnClose(::message::message * pobj)
{

   if ((bool)m_varFrame["hide_on_close"])
   {

      ShowWindow(SW_HIDE);

      if (pobj != NULL)
      {

         pobj->m_bRet = true;

      }

      return;

   }

   if(m_bDefaultNotifyIcon)
   {

      if(pobj != NULL)
      {

         SCAST_PTR(::message::base, pbase, pobj);

         pbase->m_bRet = true;

      }

#ifdef LINUX
      //if(IsWindowVisible())
      if(::user::get_edesktop() == ::user::desktop_unity_gnome
            || ::user::get_edesktop() == ::user::desktop_ubuntu_gnome)
      {

         ShowWindow(SW_HIDE);

      }
      else
      {

         WfiMinimize();

      }
#else

      if(IsWindowVisible())
      {

         ShowWindow(SW_HIDE);

      }

#endif // LINUX

//      else
//      {
//
//         ShowWindow(SW_SHOW);
//
//         InitialFramePosition(true);
//
//      }

      return;

   }

   if (m_bModal)
   {
      EndModalLoop(IDOK);
      pobj->m_bRet = true;
      return;
   }
   else if (GetTopLevelFrame() != NULL && GetTopLevelFrame()->m_bModal)
   {
      GetTopLevelFrame()->EndModalLoop(IDOK);
      pobj->m_bRet = true;
      return;
   }

   if (pobj)
   {

      pobj->m_bRet = true;

   }

   bool bHideWindow = false;

   {

      {

         // Note: only queries the active document
         ::user::document * pdocument = GetActiveDocument();

         if (pdocument != NULL && !pdocument->can_close_frame(this))
         {

            // document can't close right now -- don't close it
            return;

         }

      }

      ::aura::application * papp = &Application;

      if (GetParent() != NULL)
      {

         bHideWindow = true;

      }
      else if (papp->is_system() || papp->is_session())
      {

         // TODO: instead of closing all applications in process System.m_apptra, should close application that make part of
         // cube, bergedge, session or system.

         ::aura::application_ptra appptra = System.get_appptra();

         for (int32_t i = 0; i <  appptra.get_count(); i++)
         {

            sp(::aura::application) pappChild = appptra[i];

            if (!App(pappChild.m_p)._001CloseApplicationByUser(this))
               return;

         }

      }
      else if(Application.GetVisibleTopLevelFrameCountExcept(this) <= 0)
      {

         //if (!papp->_001CloseApplicationByUser(this))
         // return;

         post_message(WM_APPEXIT);

         return;

      }
      else
      {

         bHideWindow = true;

      }

   }

   if(bHideWindow)
   {

      ShowWindow(SW_HIDE);

   }

}

#ifdef WINDOWSEX

void simple_frame_window::OnNcCalcSize(bool bCalcValidRects, NCCALCSIZE_PARAMS FAR* lpncsp)
{
   UNREFERENCED_PARAMETER(bCalcValidRects);
   if(m_workset.IsEnabled() && m_workset.m_pframeschema != NULL)
   {
      m_workset.OnNcCalcSize(&lpncsp->rgrc[0]);
   }
   else
   {
      // trans      ::user::frame_window::OnNcCalcSize(bCalcValidRects, lpncsp);
   }

}

#endif

void simple_frame_window::_001OnActivateApp(::message::message * pobj)
{

   SCAST_PTR(::message::base, pbase, pobj);

   pbase->previous();

   //bool bActive = pbase->m_wparam != FALSE;

   if (GetParent() == NULL && GetExStyle() & WS_EX_LAYERED)
   {

      //if (bActive)
      //{

      //   if (WfiIsIconic())
      //   {

      //      WfiRestore();

      //   }
      //   ::SetActiveWindow(get_handle());
      //}

      pbase->m_bRet = true;

      pbase->m_lresult = 0;

   }
}

void simple_frame_window::_001OnActivate(::message::message * pobj)
{

   SCAST_PTR(::message::activate, pactivate, pobj);

   pactivate->previous();

//   bool bMinimized = HIWORD(pactivate->m_lparam);

   int iActive = LOWORD(pactivate->m_wparam);
   if (iActive)
   {

      if (GetExStyle() & WS_EX_LAYERED)
      {

         if (iActive == WA_CLICKACTIVE)
         {

            //   if (bMinimized || WfiIsIconic())
            //   {

            //      WfiRestore();

            //   }
            //   else
            //   {

            //      WfiMinimize();

            //   }

            //}
            //else if (bMinimized)
            //{



            //   WfiRestore();


         }

         pactivate->m_bRet = true;

         pactivate->m_lresult = 0;

      }

   }
   else
   {

      //if (GetExStyle() & WS_EX_LAYERED)
      //{

      //   if (pactivate->m_lparam == 0)
      //   {

      //      if (!WfiIsIconic())
      //      {

      //         WfiMinimize(true);

      //      }

      //   }

      pactivate->m_bRet = true;

      pactivate->m_lresult = 0;


      //

//         if (!bMinimized && !WfiIsIconic())
//         {
//
////            WfiMinimize();
//
//         }


      //}

   }

}


void simple_frame_window::_001OnNcActivate(::message::message * pobj)
{

   SCAST_PTR(::message::nc_activate, pncactivate, pobj);

   // stay active if WF_STAYACTIVE bit is on
   //if (m_nFlags & WF_STAYACTIVE)
   //   pncactivate->m_bActive = TRUE;

   // but do not stay active if the window is disabled
   if (!is_window_enabled())
      pncactivate->m_bActive = FALSE;

   if (!pncactivate->m_bActive)
   {

      output_debug_string("test");

   }

   /*if(m_bWindowFrame)
   {
   m_workset.SetActiveFlag(pncactivate->m_bActive);
   pncactivate->set_lresult(TRUE); // bStop
   pncactivate->m_bRet = true;
   return;
   }
   else*/
   {
      // do not call the base class because it will call Default()
      //  and we may have changed bActive.
      pncactivate->set_lresult(DefWindowProc(WM_NCACTIVATE, pncactivate->m_bActive, 0)); // bStop
      pncactivate->m_bRet = pncactivate->get_lresult() != 0;
      return;
   }
}



bool simple_frame_window::LoadFrame(const char * pszMatter, uint32_t dwDefaultStyle, ::user::interaction * pParentWnd, ::create * pcreate)
{

   UNREFERENCED_PARAMETER(pParentWnd);

   // only do this once
   //   ASSERT_VALID_IDR(nIDResource);
   //   ASSERT(m_nIDHelp == 0 || m_nIDHelp == nIDResource);

   m_strMatterHelp = pszMatter;    // ID for help context (+HID_BASE_RESOURCE)

   //   string strFullString;
   //   if (strFullString.load_string(nIDResource))
   //      __extract_sub_string(m_strTitle, strFullString, 0);    // first sub-string

   const char * lpszTitle = m_strTitle;

   if (pParentWnd == NULL)
      pParentWnd = Application.get_request_parent_ui(this, pcreate);

   dwDefaultStyle &= ~WS_VISIBLE;

   ::rect rectFrame;

   sp(::user::place_holder) pholder;

   if(pParentWnd != NULL && (pholder = pParentWnd).is_set())
   {

      pholder->GetClientRect(rectFrame);

   }
   else
   {

      rectFrame = null_rect();

   }

   if(pParentWnd == NULL)
   {

      m_bLayoutEnable = false;

   }

   output_debug_string("\nm_bLayoutEnable FALSE");

   ::user::create_struct cs(0L, NULL, lpszTitle, dwDefaultStyle, rectFrame, pcreate);

   if (!create_window_ex(cs, pParentWnd))
   {

      return false;   // will self destruct on failure normally

   }


   /* trans   // save the default menu handle
      ASSERT(get_handle() != NULL);
      m_hMenuDefault = ::GetMenu(get_handle()); */

   // load accelerator resource
   //   LoadAccelTable(MAKEINTRESOURCE(nIDResource));

   if (pcreate == NULL)   // send initial update
      send_message_to_descendants(WM_INITIALUPDATE, 0, (LPARAM)0, TRUE, TRUE);

   return TRUE;

}




void simple_frame_window::_001OnDdeInitiate(::message::message * pobj)
{
   SCAST_PTR(::message::base, pbase, pobj);
   pbase->set_lresult(DefWindowProc((uint32_t)pbase->m_wparam, pbase->m_lparam, pbase->get_lresult()));
}


void simple_frame_window::pre_translate_message(::message::message * pmessage)
{

   if(pmessage->m_id == message_display_change)
   {

      Wfi();

   }
   else if (pmessage->m_id == WM_MOUSEMOVE)
   {

   }
   else if(pmessage->m_id == WM_KEYDOWN || pmessage->m_id == WM_SYSKEYDOWN)
   {

      SCAST_PTR(::message::key, pkey, pmessage);

      if(pkey->m_ekey == ::user::key_alt || pkey->m_ekey == ::user::key_lalt || pkey->m_ekey == ::user::key_ralt)
      {

         m_bFullScreenAlt = false;

      }
      else if(pkey->m_ekey == ::user::key_control || pkey->m_ekey == ::user::key_lcontrol || pkey->m_ekey == ::user::key_rcontrol)
      {

         m_bFullScreenCtrl = false;

      }
      else if(pkey->m_ekey == ::user::key_return)
      {

         if (Session.is_key_pressed(::user::key_control) && Session.is_key_pressed(::user::key_alt))
         {

            m_bFullScreenAlt = true;

            m_bFullScreenCtrl = true;

            if (!IsFullScreen())
            {

               if (DeferFullScreen(true, false))
               {

                  pmessage->m_bRet = true;

                  return;

               }

            }

         }

      }

   }
   else if(pmessage->m_id == WM_KEYUP || pmessage->m_id == WM_SYSKEYUP)
   {

      SCAST_PTR(::message::key, pkey, pmessage);

      if(pkey->m_ekey == ::user::key_alt || pkey->m_ekey == ::user::key_lalt || pkey->m_ekey == ::user::key_ralt)
      {

         if (IsFullScreen() && Session.is_key_pressed(::user::key_control) && !m_bFullScreenAlt && !m_bFullScreenCtrl)
         {

            if (WfiRestore(m_eappearanceBefore != ::user::appearance_full_screen))
            {

               pmessage->m_bRet = true;

               m_bFullScreenAlt = false;

               return;

            }

         }

         m_bFullScreenAlt = false;

      }
      else if(pkey->m_ekey == ::user::key_control || pkey->m_ekey == ::user::key_lcontrol || pkey->m_ekey == ::user::key_rcontrol)
      {

         if(IsFullScreen() && Session.is_key_pressed(::user::key_alt) && !m_bFullScreenAlt && !m_bFullScreenCtrl)
         {

            if(WfiRestore(m_eappearanceBefore != ::user::appearance_full_screen))
            {

               pmessage->m_bRet = true;

               m_bFullScreenAlt = false;

               return;

            }

         }

         m_bFullScreenAlt = false;

      }

   }

   return ::user::frame_window::pre_translate_message(pmessage);

}


void simple_frame_window::InitialFramePosition(bool bForceRestore)
{

   try
   {

      if(m_bFrameMoveEnable)
      {

         if(Application.handler()->m_varTopicQuery.has_property("wfi_maximize")
               && (GetParent() == NULL
#if defined(ANDROID) || defined(METROWIN) || defined(APPLE_IOS)
                   || GetParent() == System.m_possystemwindow->m_pui
#endif
                  ))
         {

            WfiMaximize();

         }
         else if(Application.handler()->m_varTopicQuery.has_property("client_only")
                 || Application.handler()->m_varTopicQuery.has_property("full_screen"))
         {

            if(m_workset.IsAppearanceEnabled())
            {

               WfiFullScreen();

            }
            else
            {

               best_monitor(NULL,::null_rect(),true);

            }

         }
         else
         {

            WindowDataLoadWindowRect(bForceRestore,true);

            WindowDataEnableSaveWindowRect(true);

         }

      }

      ActivateTopParent();

      BringToTop(-1);

      if (m_workset.IsAppearanceEnabled())
      {

         if (m_workset.get_appearance() != NULL && m_workset.GetAppearance() == ::user::appearance_iconic)
         {

            WfiRestore(false);

         }

      }

      //on_layout();

      if (m_palphasource != NULL)
      {

         m_palphasource->on_alpha_target_initial_frame_position();

      }

   }
   catch(...)
   {

   }

   m_bLayoutEnable = true;

   output_debug_string("\nm_bLayoutEnable TRUE");

   m_bInitialFramePosition = false;


}


void simple_frame_window::_001OnDeferPaintLayeredWindowBackground(::draw2d::graphics * pgraphics)
{

   if(m_papp == NULL
         || m_papp->m_psession == NULL
         || m_papp->m_psession->m_psavings == NULL)
   {

      return;

   }


   if (Session.savings().is_trying_to_save(::aura::resource_processing)
         || Session.savings().is_trying_to_save(::aura::resource_translucent_background))
   {

      rect rectClient;

      GetClientRect(rectClient);

      pgraphics->fill_solid_rect(rectClient, RGB(0, 0, 0));

   }
   else
   {

      ::user::frame_window::_001OnDeferPaintLayeredWindowBackground(pgraphics);

   }

}

void simple_frame_window::_000OnDraw(::draw2d::graphics * pgraphicsParam)
{

   defer_check_layout();

   defer_check_zorder();

   windowing_output_debug_string("\nsimple_frame_window::_000OnDraw A");

   if (!IsWindowVisible() || WfiIsIconic())
      return;

   windowing_output_debug_string("\nsimple_frame_window::_000OnDraw B");

   rect rectClient;

   GetWindowRect(rectClient);

   rectClient -= rectClient.top_left();

   bool bDib = false;

   double dAlpha = get_alpha();

   ::draw2d::graphics * pgraphics = pgraphicsParam;

   if(dAlpha == 0.0)
   {

      windowing_output_debug_string("Alpha is Zero\n");

   }

   if(rectClient.area() > 0 && dAlpha > 0.0 && dAlpha < 1.0 && GetExStyle() & WS_EX_LAYERED)
   {

      if(m_dibAlpha.is_null())
      {

         m_dibAlpha.alloc(allocer());

      }

      m_dibAlpha->create(rectClient.get_size());

      m_dibAlpha->Fill(0,0,0,0);

      pgraphics = m_dibAlpha->get_graphics();

      pgraphics->SetViewportOrg(pgraphics->GetViewportOrg());

      bDib = true;

   }

   ::user::style_context style(this);

   if(dAlpha > 0.0)
   {

      bool bBlurBackground = _001GetFlag(::user::flag_blur_background);

      int iDrawingOrder = DRAWING_ORDER_CLIENT_OVER;

      if (!bBlurBackground)
      {

         iDrawingOrder = _001GetInt(::user::int_top_level_drawing_order);

         while (style)
         {

            if (style->_001OnDrawMainFrameBackground(pgraphics, this))
            {

               break;

            }

            style.next();

         }

      }

#if TEST

      pgraphics->fill_solid_rect(0, 0, 100, 100, ARGB(128, 255, 0, 0));

#endif

      if (iDrawingOrder == DRAWING_ORDER_CLIENT_OVER)
      {

         _001DrawThis(pgraphics);

         _001DrawChildren(pgraphics);

      }
      else
      {

         draw_frame_and_control_box_over(pgraphics);

      }

      _008CallOnDraw(pgraphics);

#if TEST

      pgraphics->fill_solid_rect(0, 100, 100, 100, ARGB(128, 0, 0, 255));

#endif

   }

   if(bDib)
   {

      pgraphicsParam->set_alpha_mode(::draw2d::alpha_mode_blend);

      pgraphicsParam->alpha_blend(null_point(),rectClient.get_size(),pgraphics,null_point(),dAlpha);

   }

}


void simple_frame_window::_001OnDraw(::draw2d::graphics * pgraphics)
{

   bool bBlurBackground = _001GetFlag(::user::flag_blur_background);

   if(bBlurBackground)
   {

      class imaging & imaging = Application.imaging();

      rect rectClient;

      GetClientRect(rectClient);

      //rectClient.offset(rectClient.top_left());

      if(Session.savings().is_trying_to_save(::aura::resource_translucent_background))
      {

         //pgraphics->fill_solid_rect(rectClient, RGB(150, 220, 140));

      }
      else if(Session.savings().is_trying_to_save(::aura::resource_processing)
              || Session.savings().is_trying_to_save(::aura::resource_blur_background))
      {

         imaging.color_blend(pgraphics,rectClient,RGB(150,180,140),150);

      }
      else
      {
#ifndef LINUX
         if(rectClient.get_size() != m_dibBk->size())
         {
            m_dibBk->create(rectClient.get_size());
            m_dibBk->Fill(0,200,200,190);
            //HMODULE hmodule = ::LoadLibrary("ca2performance.dll");
            //::visual::fastblur *( *pfnNew )(sp(::aura::application)) = (::visual::fastblur *(*)(sp(::aura::application))) ::GetProcAddress(hmodule, "new_fastblur");
            m_fastblur.alloc(allocer());
            m_fastblur.initialize(rectClient.get_size(),2);
         }
         if(m_fastblur.is_set() && m_fastblur->area() > 0)
         {

            m_fastblur->get_graphics()->BitBlt(0,0,rectClient.width(),rectClient.height(),pgraphics,0,0,SRCCOPY);
            m_fastblur.blur();
            imaging.bitmap_blend(
            m_fastblur->get_graphics(),
            null_point(),
            rectClient.get_size(),
            m_dibBk->get_graphics(),
            null_point(),
            49);
            pgraphics->from(rectClient.get_size(),
                            m_fastblur->get_graphics(),
                            null_point(),
                            SRCCOPY);
         }
#endif
      }

   }

   draw_frame(pgraphics);


}


bool simple_frame_window::on_before_set_parent(sp(::user::interaction) pinterface)
{

   WindowDataSaveWindowRect();

   if (!::user::box::on_before_set_parent(pinterface))
   {

      return false;

   }

   return true;

}


void simple_frame_window::on_set_parent(::user::interaction * puiParent)
{

   ::user::frame_window::on_set_parent(puiParent);

   if (puiParent == NULL)
   {

      if (m_bLayered)
      {

         ModifyStyleEx(0, WS_EX_LAYERED);

      }

   }


   if(puiParent == NULL)
   {

      if(m_phelpertask.is_null())
      {

         m_phelpertask = canew(helper_task(this));

      }

   }
   else
   {

      if(m_phelpertask.is_set())
      {

         m_phelpertask->post_quit();

         m_phelpertask.release();

      }


   }
   m_workset.m_pwndEvent = this;

   if (m_pupdowntarget != NULL && wfi_is_up_down())
   {

      // an updowntarget always show the frame for upping/downing

      m_bWindowFrame = true;

      m_workset.Enable(true);

      if (puiParent == NULL)
      {

         m_workset.m_bSizingEnabled = true;

         m_workset.m_bMovingEnabled = true;

      }
      else
      {

         m_workset.m_bSizingEnabled = false;

         m_workset.m_bMovingEnabled = false;

      }

      m_workset.install_message_routing(m_pimpl);

      m_workset.m_pframeschema->get_control_box()->set_need_layout();

   }
   else
   {

      if (m_bAutoWindowFrame)
      {

         if (!m_bWindowFrame)
         {

            m_bWindowFrame = m_bCustomFrameBefore;

         }

         if (!m_workset.IsEnabled())
         {

            m_workset.Enable(true);

         }

      }
      else
      {

         if (puiParent != NULL)
         {

            m_bCustomFrameBefore = m_bWindowFrame;

            m_bWindowFrame = false;

            m_workset.Enable(false);

         }
         else
         {

            m_bWindowFrame = m_bCustomFrameBefore;

            m_workset.Enable(m_bWindowFrame);

         }
      }

   }

   if (puiParent == NULL || puiParent->is_frame_window())
   {

      WindowDataLoadWindowRect(false);

      WindowDataEnableSaveWindowRect(true);

   }

   set_need_layout();

   set_need_redraw();

}


bool simple_frame_window::GetClientRect(LPRECT lprect)
{

   if (m_bWindowFrame && m_pframeschema != NULL && !WfiIsFullScreen() && !frame_is_transparent())
   {

      return m_pframeschema->get_window_client_rect(lprect);

   }
   else
   {

      return ::user::frame_window::GetClientRect(lprect);

   }

}


bool simple_frame_window::is_application_main_window()
{

   return Application.m_puiMain == this;

}


bool simple_frame_window::LoadToolBar(sp(::type) sptype, id idToolBar, const char * pszToolBar, uint32_t dwCtrlStyle, uint32_t dwStyle)
{

   sp(::user::toolbar) ptoolbar = m_toolbarmap[idToolBar];

   if(ptoolbar.is_null())
   {

      ptoolbar = Application.alloc(sptype);

      if(ptoolbar == NULL)
         return false;

      ptoolbar->create_toolbar(this,dwCtrlStyle,dwStyle);

   }

   if(ptoolbar == NULL)
      return false;

   string strMatter = Application.dir().matter(pszToolBar);

   if (ptoolbar->oprop("matter_annotation") == strMatter)
   {

      return true;

   }

   string strXml = Application.file().as_string(strMatter);

   if(!ptoolbar->LoadXmlToolBar(strXml))
   {

      return false;

   }

   m_toolbarmap.set_at(idToolBar,ptoolbar);

   AddControlBar(ptoolbar);

   ptoolbar->set_need_layout();

   ptoolbar->oprop("matter_annotation") = strMatter;

   set_need_layout();

   return true;

}


void simple_frame_window::defer_create_notification_icon()
{

   if (!m_bDefaultNotifyIcon)
   {

      return;

   }

   if (m_pnotifyicon.is_set())
   {

      m_pnotifyicon->Destroy();

   }

   if (m_piconNotify.is_null())
   {

      m_piconNotify = canew(::visual::icon(get_app()));

      const char * pszAppName = Application.m_strAppName;

      m_piconNotify->load_app_tray_icon(pszAppName);

   }

   m_pnotifyicon = canew(::user::notify_icon(get_app()));

   m_pnotifyicon->create_notify_icon(1, this, m_piconNotify);

   //if (m_workset.m_pframeschema != NULL)
   {

      //m_workset.m_pframeschema->m_spcontrolbox->hide_button(::user::wndfrm::frame::button_minimize);
      m_workset.m_bMinimizeToTray = true;

   }

}




// persistent frame implemenation using updowntarget
bool simple_frame_window::WndFrameworkDownUpGetUpEnable()
{

   return m_pupdowntarget != NULL && wfi_is_up_down() && wfi_is_down();

}

bool simple_frame_window::WndFrameworkDownUpGetDownEnable()
{

   return m_pupdowntarget != NULL && wfi_is_up_down() && wfi_is_up();

}


void simple_frame_window::WfiOnDown()
{

   frame_Attach();

}


void simple_frame_window::WfiOnUp()
{

   frame_Detach();

}

bool simple_frame_window::WfiIsMoving()
{

   return m_bWindowFrame && m_workset.GetMovingManager() != NULL && m_workset.GetMovingManager()->IsMoving();

}


bool simple_frame_window::WfiIsSizing()
{

   return m_bWindowFrame && m_workset.GetSizingManager() != NULL && m_workset.GetSizingManager()->IsSizing();

}



bool simple_frame_window::create_window(const char * lpszClassName,const char * lpszWindowName,uint32_t dwStyle,const RECT & rect,sp(::user::interaction) pParentWnd,const char * lpszMenuName,uint32_t dwExStyle, ::create * pcreate)
{

   return ::user::frame_window::create_window(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, lpszMenuName, dwExStyle, pcreate);

}


void simple_frame_window::route_command_message(::user::command * pcommand)
{

   m_workset.route_command_message(pcommand);

   if (pcommand->m_bRet)
   {

      return;

   }

   if (pcommand->m_pcommandtargetSource == this)
   {

      // then pump through frame
      ::user::frame_window::route_command_message(pcommand);

      if (pcommand->m_bRet)
      {

         return;

      }

   }

   // pump through current ::user::impact FIRST
   sp(::user::impact) pview = GetActiveView();

   if (pview != NULL)
   {

      pview->route_command_message(pcommand);

      if (pcommand->m_bRet)
      {

         return;

      }

   }

   for (auto & pview : m_viewptraCommandHandlers)
   {

      if (pview != NULL && pview != GetActiveView())
      {

         pview->route_command_message(pcommand);

         if (pcommand->m_bRet)
         {

            return;

         }

      }

   }

   pview = get_child_by_id("pane_first");

   if (pview != NULL)
   {

      pview->route_command_message(pcommand);

      if (pcommand->m_bRet)
      {

         return;

      }

   }

   if (pcommand->m_pcommandtargetSource != this)
   {

      // then pump through frame
      ::user::frame_window::route_command_message(pcommand);

      if (pcommand->m_bRet)
      {

         return;

      }

   }

   // then pump through parent
   sp(::user::interaction) puiParent = GetParent();

   if (puiParent != NULL)
   {

      puiParent->route_command_message(pcommand);

      if (pcommand->m_bRet)
      {

         return;

      }

   }

   // last but not least, pump through cast
   ::aura::application * papp = get_app();

   if (papp != NULL)
   {

      papp->route_command_message(pcommand);

      if (pcommand->m_bRet)
      {

         return;

      }

   }

   sp(command_target) ptarget = Session.get_keyboard_focus();

   if (ptarget != NULL && ptarget != this)
   {

      ptarget->route_command_message(pcommand);

      if (pcommand->m_bRet)
      {

         return;

      }

   }

}


#ifdef WINDOWSEX



void simple_frame_window::OnDropFiles(HDROP hDropInfo)
{

   SetActiveWindow();      // activate us first !
   UINT nFiles = ::DragQueryFile(hDropInfo, (UINT)-1, NULL, 0);

   ::file::patha patha;
   wchar_t szFileName[_MAX_PATH];
   for (UINT iFile = 0; iFile < nFiles; iFile++)
   {

      if (::DragQueryFileW(hDropInfo, iFile, szFileName, _MAX_PATH))
      {

         patha.add(szFileName);

      }

   }
   ::DragFinish(hDropInfo);

   Session.on_frame_window_drop_files(this, patha);

}

// query end session for main frame will attempt to close it all down
bool simple_frame_window::OnQueryEndSession()
{
   ::base::application* pApp = &System;
   if(pApp != NULL && pApp->m_puiMain == this)
      return App(pApp).save_all_modified();

   return TRUE;
}


void simple_frame_window::OnEndSession(bool bEnding)
{

   if(!bEnding)
      return;

   Application.close(::core::end_system);

}


#else

//void simple_frame_window::OnDropFiles(HDROP hDropInfo)
//{
//
//   UNREFERENCED_PARAMETER(hDropInfo);
//
//}
//


#endif






LRESULT simple_frame_window::OnDDEInitiate(WPARAM wParam, LPARAM lParam)
{


#ifdef WINDOWSEX

   ::core::application* pApp = &System;
   if (pApp != NULL &&
         LOWORD(lParam) != 0 && HIWORD(lParam) != 0 &&
         (ATOM)LOWORD(lParam) == pApp->m_atomApp &&
         (ATOM)HIWORD(lParam) == pApp->m_atomSystemTopic)
   {
      // make duplicates of the incoming atoms (really adding a reference)
      char szAtomName[_MAX_PATH];
      GlobalGetAtomName(pApp->m_atomApp, szAtomName, _MAX_PATH - 1);
      GlobalAddAtom(szAtomName);
      GlobalGetAtomName(pApp->m_atomSystemTopic, szAtomName, _MAX_PATH - 1);
      GlobalAddAtom(szAtomName);

      // send the WM_DDE_ACK (caller will delete duplicate atoms)
      ::SendMessage((oswindow)wParam, WM_DDE_ACK, (WPARAM)get_handle(),
                    MAKELPARAM(pApp->m_atomApp, pApp->m_atomSystemTopic));
   }

#else

   ::exception::throw_not_implemented(get_app());

#endif

   return 0L;
}


// always ACK the execute command - even if we do nothing
LRESULT simple_frame_window::OnDDEExecute(WPARAM wParam, LPARAM lParam)
{


#ifdef WINDOWSEX

   // unpack the DDE message
   uint_ptr unused;
   HGLOBAL hData;
   //IA64: Assume DDE LPARAMs are still 32-bit
   VERIFY(UnpackDDElParam(WM_DDE_EXECUTE, lParam, &unused, (uint_ptr*)&hData));

   // get the command string
   const char * lpsz = (const char *)GlobalLock(hData);
   string strCommand;
   try
   {
      strCommand = lpsz;
      GlobalUnlock(hData);
   }
   catch (memory_exception * pe)
   {
      GlobalUnlock(hData);
      pe->Delete();
   }


   // acknowledge now - before attempting to execute
   ::PostMessage((oswindow)wParam, WM_DDE_ACK, (WPARAM)get_handle(),
                 //IA64: Assume DDE LPARAMs are still 32-bit
                 ReuseDDElParam(lParam, WM_DDE_EXECUTE, WM_DDE_ACK,
                                (UINT)0x8000, (uint_ptr)hData));

   // don't execute the command when the window is disabled
   if (!is_window_enabled())
   {
      TRACE(::aura::trace::category_AppMsg, 0, "Warning: DDE command '%s' ignored because window is disabled.\n",
            strCommand.GetString());
      return 0;
   }

   // execute the command
   LPTSTR lpszCommand = strCommand.GetBuffer();
   if (!System.OnDDECommand(lpszCommand))
      TRACE(::aura::trace::category_AppMsg, 0, "Error: failed to execute DDE command '%s'.\n", lpszCommand);
   strCommand.ReleaseBuffer();

#else

   ::exception::throw_not_implemented(get_app());

#endif

   return 0L;

}

LRESULT simple_frame_window::OnDDETerminate(WPARAM wParam, LPARAM lParam)
{

#ifdef WINDOWSEX

   ::PostMessage((oswindow)wParam, WM_DDE_TERMINATE, (WPARAM)get_handle(), lParam);

#else

   ::exception::throw_not_implemented(get_app());

#endif

   return 0L;

}


void simple_frame_window::NotifyFloatingWindows(uint32_t dwFlags)
{
   ASSERT_VALID(this);
   // trans   ASSERT(get_handle() != NULL);

   // get top level parent frame window first unless this is a child window
   sp(::user::frame_window) pParent = (GetStyle() & WS_CHILD) ? this : GetTopLevelFrame();
   ASSERT(pParent != NULL);
   if (dwFlags & (FS_DEACTIVATE | FS_ACTIVATE))
   {
      // update parent window activation state
      bool bActivate = !(dwFlags & FS_DEACTIVATE);
      bool bEnabled = pParent->is_window_enabled();

      if (bActivate && bEnabled && pParent != this)
      {
         // Excel will try to Activate itself when it receives a
         // WM_NCACTIVATE so we need to keep it from doing that here.
         //m_nFlags |= WF_KEEPMINIACTIVE;
         pParent->send_message(WM_NCACTIVATE, TRUE);
         //m_nFlags &= ~WF_KEEPMINIACTIVE;
      }
      else
      {
         pParent->send_message(WM_NCACTIVATE, FALSE);
      }
   }

   // then update the state of all floating windows owned by the parent
#ifdef WINDOWSEX

   sp(::user::interaction) oswindowDesktop = System.get_desktop_window();

   if (oswindowDesktop.is_null())
      return;

   sp(::user::interaction) oswindow = oswindowDesktop->get_wnd(GW_CHILD);

   while (oswindow != NULL)
   {

      if (::user::is_descendant(pParent, oswindow))
         oswindow->send_message(WM_FLOATSTATUS, dwFlags);

      oswindow = oswindow->get_wnd(GW_HWNDNEXT);

   }

#else
   _throw(todo(get_app()));
#endif
}



// query end session for main frame will attempt to close it all down
void simple_frame_window::_001OnQueryEndSession(::message::message * pobj)
{
   SCAST_PTR(::message::base, pbase, pobj);
   if (&System != NULL && System.m_puiMain == this)
   {
      pbase->set_lresult(System.save_all_modified());
      pbase->m_bRet = true;
      return;
   }
   pbase->set_lresult(TRUE);
   return;
}


void simple_frame_window::on_control_event(::user::control_event * pevent)
{

   m_workset.on_control_event(pevent);

   if(pevent->m_bRet)
   {

      return;

   }

   return ::user::frame_window::on_control_event(pevent);

}


string simple_frame_window::get_window_default_matter()
{

   if (m_pdocumenttemplate == NULL)
   {

      return frame_window::get_window_default_matter();

   }

   return m_pdocumenttemplate->m_strMatter;

}


void simple_frame_window::guserbaseOnInitialUpdate(::message::message * pobj)
{
   SCAST_PTR(::message::base, pbase, pobj);
   ::user::FrameInitialUpdate * pfiu = (::user::FrameInitialUpdate *)pbase->m_lparam.m_lparam;
   if (pfiu != NULL)
   {
      sp(::user::frame_window) pframe = (this);
      // if the frame does not have an active ::user::impact, set to first pane
      sp(::user::impact) pview = NULL;
      if (pframe->GetActiveView() == NULL)
      {
         sp(::user::interaction) pwindow = pframe->GetDescendantWindow("pane_first");
         if (pwindow != NULL && base_class < ::user::impact >::bases(pwindow))
         {
            pview = (pwindow.m_p);
            pframe->SetActiveView(pview, FALSE);
         }
      }

      if (pfiu->m_bMakeVisible)
      {
         // send initial update to all views (and other controls) in the frame
         pframe->send_message_to_descendants(WM_INITIALUPDATE, 0, (LPARAM)0, TRUE, TRUE);

         // give ::user::impact a chance to save the focus (CFormView needs this)
         if (pview != NULL)
            pview->OnActivateFrame(WA_INACTIVE, pframe);

         // finally, activate the frame
         // (send the default show command unless the main desktop window)
         int32_t nCmdShow = -1;      // default
         ::core::application* pApp = &System;
         if (pApp != NULL && pApp->m_puiMain == pframe)
         {
            nCmdShow = System.m_nCmdShow; // use the parameter from WinMain
            System.m_nCmdShow = -1; // set to default after first time
         }
         bool bFullScreen;
         data_get("FullScreen", bFullScreen);
         if (bFullScreen)
         {
            WfiFullScreen();
         }
         else
         {
            pframe->ActivateFrame(nCmdShow);
         }
         if (pview != NULL)
            pview->OnActivateView(TRUE, pview, pview);

      }

      sp(::user::document) pdoc = pfiu->m_pdoc;
      // update frame counts and frame title (may already have been visible)
      if (pdoc != NULL)
         pdoc->update_frame_counts();
      pframe->on_update_frame_title(TRUE);

      set_need_redraw();
   }
   pbase->set_lresult(0);
}


void simple_frame_window::_001OnClip(::draw2d::graphics * pgraphics)
{

}


void simple_frame_window::draw_frame_and_control_box_over(::draw2d::graphics * pgraphics)
{

   if (!is_this_visible())
      return;


   ::user::interaction_spa uia;

   {

      synch_lock sl(m_pmutex);

      uia = m_uiptraChild;

   }

   {

      ::draw2d::savedc k(pgraphics);

      //if (0)
      {
         try
         {

            for (auto & pui : uia)
            {

               if (!base_class < ::user::wndfrm::frame::control_box > ::bases(pui))
               {

                  pui->_000OnDraw(pgraphics);

               }

            }

         }
         catch (...)
         {

         }

      }

   }



   _001DrawThis(pgraphics);



   if (!frame_is_transparent() || this == GetActiveWindow())
   {

      ::draw2d::savedc k(pgraphics);

      try
      {

         for (auto & pui : uia)
         {

            if (base_class < ::user::wndfrm::frame::control_box > ::bases(pui))
            {

               string str;

               pui->get_window_text(str);

               if (str == "r")
               {

                  //TRACE0("x button");

               }

               if (pui->IsWindowVisible())
               {

                  if (str == "r")
                  {

                     //TRACE0("x button visible");

                  }

                  pui->_000OnDraw(pgraphics);

               }

            }

         }

      }
      catch (...)
      {

      }

   }

   _008CallOnDraw(pgraphics);

}


void simple_frame_window::draw_frame(::draw2d::graphics * pgraphics)
{

   if (m_bWindowFrame && !Session.savings().is_trying_to_save(::aura::resource_display_bandwidth))
   {

      ::user::wndfrm::frame::WorkSetClientInterface::_001OnDraw(pgraphics);

   }

}


bool simple_frame_window::WfiOnMove(bool bTracking)
{

   return true;

}


bool simple_frame_window::WfiOnSize(bool bTracking)
{

   return true;

}


void simple_frame_window::WfiOnClose()
{

   post_message(WM_CLOSE);

}


void simple_frame_window::WfiOnMaximize()
{

   _001WindowMaximize();

}


void simple_frame_window::WfiOnMinimize(bool bNoActivate)
{

   _001WindowMinimize(bNoActivate);

}


void simple_frame_window::WfiOnRestore()
{

   _001WindowRestore();

}


void simple_frame_window::WfiOnDock(::user::e_appearance eappearance)
{

   _001WindowDock(eappearance);

}


bool simple_frame_window::DeferFullScreen(bool bFullScreen, bool bRestore)
{
   if (bFullScreen)
   {
      sp(::user::interaction) pwndParentFrame = GetParentFrame();
      if (pwndParentFrame == NULL)
      {
         if (!WfiIsFullScreen())
         {
            WfiFullScreen();
            return true;
         }
         else
         {
            return false;
         }
      }
      simple_frame_window * pframe = dynamic_cast <simple_frame_window *> (pwndParentFrame.m_p);
      if (pframe == NULL)
      {
         if (!WfiIsFullScreen())
         {
            WfiFullScreen();
            return true;
         }
         else
         {
            return false;
         }
      }

      if (pframe->DeferFullScreen(bFullScreen, bRestore))
         return true;

      if (!WfiIsFullScreen())
      {
         WfiFullScreen();
         return true;
      }
      else
      {
         return false;
      }
   }
   else
   {
      if (WfiIsFullScreen())
      {
         WfiRestore(false);
         return true;
      }
      sp(::user::interaction) pwndParentFrame = GetParentFrame();
      if (pwndParentFrame == NULL)
      {
         return false;
      }
      simple_frame_window * pframe = dynamic_cast <simple_frame_window *> (pwndParentFrame.m_p);
      if (pframe == NULL)
      {
         return false;
      }
      return pframe->DeferFullScreen(bFullScreen, bRestore);
   }
}


bool simple_frame_window::calc_layered()
{

   if (m_bLayered && _001GetTranslucency() != ::user::translucency_none)
   {
      return !Session.savings().is_trying_to_save(::aura::resource_processing)
             && !Session.savings().is_trying_to_save(::aura::resource_display_bandwidth);
   }
   else
   {

      return false;

   }

}


//bool simple_frame_window::get_translucency(::user::e_translucency & etranslucency, ::user::e_element eelement, ::user::interaction * pui)
//{
//
//   if (m_etranslucency != ::user::translucency_undefined)
//   {
//
//      etranslucency = m_etranslucency;
//
//      return true;
//
//   }
//
//   return ::user::frame_window::get_translucency(etranslucency, eelement, pui);
//
//}


void simple_frame_window::data_on_after_change(::message::message * pobj)
{

   box::data_on_after_change(pobj);

   SCAST_PTR(database::change_event, phint, pobj);

   if (phint->m_datakey == "ca2.savings")
   {

      defer_synch_layered();

   }

}




void simple_frame_window::on_simple_command(::message::simple_command * psimplecommand)
{

   ::user::frame_window::on_simple_command(psimplecommand);

}


class ::mini_dock_frame_window* simple_frame_window::CreateFloatingFrame(uint32_t dwStyle)
{

   UNREFERENCED_PARAMETER(dwStyle);

   return NULL;

}


















bool simple_frame_window::set_appearance(::user::e_appearance eappearance)
{

   bool bOk1 = ::user::frame_window::set_appearance(eappearance);

   m_workset.SetAppearance(eappearance);

   if(eappearance == ::user::appearance_full_screen)
   {

      WfiOnAfterFullScreen();

   }

   return bOk1;

}


bool simple_frame_window::create_bars()
{

   if(!on_create_bars())
      return false;

   if (!m_bInitialFramePosition)
   {

      set_need_layout();

   }

   return true;

}


bool simple_frame_window::on_create_bars()
{

   if(!m_bDefaultCreateToolbar)
   {

      return true;

   }

   ::file::path path = Application.dir().matter(m_pdocumenttemplate->m_strMatter / "toolbar.xml");

   if (Application.file().exists(path))
   {

      LoadToolBar(m_pdocumenttemplate->m_strMatter, m_pdocumenttemplate->m_strMatter / "toolbar.xml");

   }

   return true;

}


void simple_frame_window::InitialUpdateFrame(::user::document * pDoc,bool bMakeVisible)
{

   ::user::frame_window::InitialUpdateFrame(pDoc,bMakeVisible);

}


void simple_frame_window::_001OnTimer(::timer * ptimer)
{

   ::user::frame_window::_001OnTimer(ptimer);

   ::user::wndfrm::frame::WorkSetClientInterface::_001OnTimer(ptimer);

}


void simple_frame_window::OnNotifyIconContextMenu(UINT uiNotifyIcon)
{

   point pt;

   Session.get_cursor_pos(&pt);

   string strMatter = "popup_notification.xml";

   string strPath = Application.dir().matter(strMatter);

   string strXml = Application.file().as_string(strPath);

   string strExtraXml = notification_area_extra_get_xml_menu();

   if (m_workset.m_pframeschema != NULL)
   {

      if (m_workset.m_pframeschema->get_control_box()->has_button(::user::wndfrm::frame::button_transparent_frame))
      {

         if (!strExtraXml.contains_ci("\"transparent_frame\""))
         {

            strExtraXml += "<item id=\"transparent_frame\">Transparent Frame</item>";

         }

      }

   }

   if (strExtraXml.has_char())
   {

      string strToken = "<!--EXTRA_MENU!-->";

      if (strXml.find(strToken) >= 0)
      {

         strXml.replace(strToken, strExtraXml);

      }
      else
      {

         strXml.replace("</menubar>", "<separator/>" + strExtraXml + "</menubar>");

      }

   }

   track_popup_xml_string_menu(strXml, 0, pt);

}


void simple_frame_window::OnNotifyIconLButtonDblClk(UINT uiNotifyIcon)
{
   UNREFERENCED_PARAMETER(uiNotifyIcon);
}

void simple_frame_window::OnNotifyIconLButtonDown(UINT uiNotifyIcon)
{
   InitialFramePosition(true);
   UNREFERENCED_PARAMETER(uiNotifyIcon);
}


void simple_frame_window::OnNotifyIconOpen(UINT uiNotifyIcon)
{

   if(m_bDefaultNotifyIcon)
   {

      InitialFramePosition(true);

   }

}


void simple_frame_window::OnNotifyIconClose(UINT uiNotifyIcon)
{

   if(m_bDefaultNotifyIcon)
   {

      post_message(WM_CLOSE);

   }

}


void simple_frame_window::OnNotifyIconQuit(UINT uiNotifyIcon)
{

   if(m_bDefaultNotifyIcon)
   {

      post_message(WM_APPEXIT);

   }

}


bool simple_frame_window::__close_is_closed()
{

   return !IsWindowVisible();

}


bool simple_frame_window::notify_icon_frame_is_opened()
{

   return !__close_is_closed();

}



void simple_frame_window::OnInitialFrameUpdate(bool bMakeVisible)
{

   if(!m_bDefaultNotifyIcon)
   {

      ::user::frame_window::OnInitialFrameUpdate(bMakeVisible);

      return;

   }

   OnUpdateToolWindow(bMakeVisible);

   if(bMakeVisible)
   {

      InitialFramePosition();

   }

}


void simple_frame_window::OnUpdateToolWindow(bool bVisible)
{

   if (!m_bDefaultNotifyIcon)
   {

      return;

   }

   if(!bVisible)
   {

      defer_dock_application(false);

   }

   if (m_pimpl == NULL)
   {

      return;

   }

   m_pimpl->show_task(bVisible && m_bShowTask);

}

void simple_frame_window::show_task(bool bShow)
{

   if (m_pimpl == NULL)
   {

      return;

   }

   m_pimpl->show_task(bShow);

}


//::user::front_end_schema * simple_frame_window::get_user_front_end_schema()
//{
//
//   if (m_workset.m_pframeschema == NULL)
//   {
//
//      return NULL;
//
//   }
//
//   return m_workset.m_pframeschema->get_user_front_end_schema();
//
//}


bool simple_frame_window::IsNotifyIconEnabled()
{

   return m_bDefaultNotifyIcon;

}


//bool simple_frame_window::get_color(COLORREF & cr, ::user::e_color ecolor, ::user::interaction * pui)
//{
//
//   if (m_workset.m_pframeschema != NULL)
//   {
//
//
//      if (m_workset.m_pframeschema->get_color(cr, ecolor, pui))
//      {
//
//         return true;
//
//      }
//
//   }
//
//   return ::user::frame_window::get_color(cr, ecolor, pui);
//
//}
//
//
void simple_frame_window::on_select_user_style()
{

   if (m_pstyle.is_null())
   {

      string strSchema = m_varFrame["wndfrm"];

      if (strSchema.has_char() || GetParent() == NULL
#ifdef METROWIN
            || GetParent() == System.m_possystemwindow->m_pui
#endif
         )
      {

         m_pstyle = Session.get_user_theme(strSchema, get_app());

      }

   }

   //::user::frame_window::on_select_user_style();

}


void simple_frame_window::nextstyle(::user::style_context * pcontext)
{

   if (pcontext->m_pstyle == this && m_bWindowFrame && m_workset.m_pframeschema.is_set())
   {

      pcontext->m_pstyle = m_workset.m_pframeschema;

   }
   else if (m_pstyle.is_set())
   {

      pcontext->m_pstyle = m_pstyle;

   }
   else if (get_parent() == NULL
#ifdef METROWIN
            || get_parent() == System.m_possystemwindow->m_pui
#endif
           )
   {

      Session.userstyle(pcontext);

   }
   else
   {

      pcontext->m_pstyle = get_parent();

   }

}




void simple_frame_window::notification_area_extra_action(const char * pszId)
{

   //sp(::user::interaction) pwnd = GetOwner();

   sp(::user::interaction) pwnd = this;

   ::user::command command((::id) pszId);

   pwnd->_001SendCommand(&command);

}


string simple_frame_window::notification_area_extra_get_xml_menu()
{

   string strXml;

   if (notification_area_extra_action_count() > 0)
   {

      for (int i = 0; i < notification_area_extra_action_count(); i++)
      {

         {

            ::aura::malloc < char * > pszName;
            ::aura::malloc < char * > pszId;
            ::aura::malloc < char * > pszLabel;
            ::aura::malloc < char * > pszAccelerator;
            ::aura::malloc < char * > pszDescription;


            notification_area_extra_action_info(
            &pszName.m_p,
            &pszId.m_p,
            &pszLabel.m_p,
            &pszAccelerator.m_p,
            &pszDescription.m_p, i);

            string strName(pszName);

            strName.replace("_", "");

            strXml += "<item id = \"" + string(pszId) + "\">" + strName + "</item>\r\n";

         }

      }

   }

   return strXml;

}






void simple_frame_window::_001OnDwm(::message::message * pobj)
{

#ifdef WINDOWSEX

   SCAST_PTR(::message::base, pbase, pobj);

   WPARAM wparam;
   LPARAM lparam;

   wparam = pbase->m_wparam;
   lparam = pbase->m_lparam;
   //return Default();
   BOOL enabled = FALSE;
   DwmIsCompositionEnabled(&enabled);
   //data->composition_enabled = enabled;

   if (enabled)
   {
      /* The window needs a frame to show a shadow, so give it the smallest
      amount of frame possible */
      //MARGINS m={0,0,0,1};
      MARGINS m = { 0,0,0,0 };
      DWORD  dw = DWMNCRP_ENABLED;
      DwmExtendFrameIntoClientArea(get_safe_handle(), &m);
      DwmSetWindowAttribute(get_safe_handle(), DWMWA_NCRENDERING_POLICY,
                            &dw, sizeof(DWORD));
   }
   else
   {
   }

   //update_region(data);
   //      long dwEx = ::GetWindowLong(GetSafeHwnd(),GWL_EXSTYLE);
   //      dwEx &= ~(WS_EX_LAYERED);
   //      ::SetWindowLong(GetSafeHwnd(),GWL_EXSTYLE,dwEx);
   //      ::InvalidateRect(GetSafeHwnd(),NULL,true);
   //      ::UpdateWindow(GetSafeHwnd());
   //      //MoveAnchorsImmediatelly(hwndDlg);
   pbase->m_bRet = true;
   pbase->set_lresult(0);

#endif

}


void simple_frame_window::_001OnNcCalcSize(::message::message * pmessage)
{

#ifdef WINDOWSEX

   SCAST_PTR(::message::nc_calc_size, pcalcsize, pmessage);

   BOOL bCalcValidRects = pcalcsize->GetCalcValidRects();
   NCCALCSIZE_PARAMS* lpncsp = pcalcsize->m_pparams;

   // TODO: Add your message handler code here and/or call default
   //if(bCalcValidRects)
   //{
   //   TRACE("1");
   //   lpncsp->rgrc[0].left = lpncsp->lppos->x + 1;
   //   lpncsp->rgrc[0].right = lpncsp->lppos->x + lpncsp->lppos->cx - 1;
   //   lpncsp->rgrc[0].top = lpncsp->lppos->y + 32;
   //   lpncsp->rgrc[0].bottom = lpncsp->lppos->y + lpncsp->lppos->cy - 1;
   //}
   //else
   //{
   //   CRect * prect = (CRect *) lpncsp;
   //   prect->top += 32;
   //   prect->left++;
   //   prect->bottom--;
   //   prect->right--;

   //   TRACE("2");
   //}
   RECT nonclient = lpncsp->rgrc[0];
   //CMiniFrameWnd::OnNcCalcSize(bCalcValidRects, lpncsp);
   RECT client = lpncsp->rgrc[0];
   if (WfiIsZoomed())
   {
      WINDOWINFO wi = {};
      wi.cbSize = sizeof(wi);
      ::GetWindowInfo(get_safe_handle(), &wi);

      /* Maximized windows always have a non-client border that hangs over
      the edge of the screen, so the size proposed by WM_NCCALCSIZE is
      fine. Just adjust the top border to remove the window title. */
      lpncsp->rgrc[0].left = client.left;
      lpncsp->rgrc[0].top = nonclient.top + wi.cyWindowBorders;
      lpncsp->rgrc[0].right = client.right;
      lpncsp->rgrc[0].bottom = client.bottom;

      HMONITOR mon = MonitorFromWindow(get_safe_handle(), MONITOR_DEFAULTTOPRIMARY);
      MONITORINFO mi = {};
      mi.cbSize = sizeof(mi);
      GetMonitorInfoW(mon, &mi);

      /* If the client rectangle is the same as the monitor's rectangle,
      the shell assumes that the window has gone fullscreen, so it removes
      the topmost attribute from any auto-hide appbars, making them
      inaccessible. To avoid this, reduce the size of the client area by
      one pixel on a certain edge. The edge is chosen based on which side
      of the monitor is likely to contain an auto-hide appbar, so the
      missing client area is covered by it. */
      if (EqualRect(&lpncsp->rgrc[0], &mi.rcMonitor))
      {
         if (has_autohide_appbar(ABE_BOTTOM, mi.rcMonitor))
            lpncsp->rgrc[0].bottom--;
         else if (has_autohide_appbar(ABE_LEFT, mi.rcMonitor))
            lpncsp->rgrc[0].left++;
         else if (has_autohide_appbar(ABE_TOP, mi.rcMonitor))
            lpncsp->rgrc[0].top++;
         else if (has_autohide_appbar(ABE_RIGHT, mi.rcMonitor))
            lpncsp->rgrc[0].right--;
      }
   }
   else
   {
      /* For the non-maximized case, set the output RECT to what it was
      before WM_NCCALCSIZE modified it. This will make the client size the
      same as the non-client size. */
      lpncsp->rgrc[0] = nonclient;

   }

#endif

}



