#include "framework.h"


namespace user
{


   control::control()
   {

      m_puiLabel = NULL;
      m_pdrawcontext = NULL;
      m_pdescriptor = NULL;
      m_iHover = -1;
      m_bControlExCommandEnabled = true;
      m_pform = NULL;
      m_pformcallback = NULL;
      m_ulFlags &= ~object::flag_auto_delete;
      m_bDefaultWalkPreTranslateParentTree = true;

   }


   control::~control()
   {

   }


   void control::install_message_routing(::message::sender * psender)
   {

      //      ::user::impact::install_message_routing(psender);
      ::user::box::install_message_routing(psender);
      IGUI_MSG_LINK(WM_MOUSEMOVE, psender, this, &::user::control::_001OnMouseMove);

#ifdef WINDOWS

      IGUI_MSG_LINK(WM_MOUSELEAVE, psender, this, &::user::control::_001OnMouseLeave);

#else

      //::exception::throw_not_implemented(get_app());

#endif

      IGUI_MSG_LINK(WM_KEYDOWN, psender, this, &::user::control::_001OnKeyDown);

      IGUI_MSG_LINK(WM_ENABLE, psender, this, &::user::control::_001OnEnable);
      IGUI_MSG_LINK(WM_SETFOCUS, psender, this, &::user::control::_001OnSetFocus);
      IGUI_MSG_LINK(WM_KILLFOCUS, psender, this, &::user::control::_001OnKillFocus);

   }


   void control::_003OnCustomDraw(::draw2d::graphics * pgraphics, ::aura::draw_context * pdrawcontext)
   {

      pgraphics->chain(pdrawcontext);

      _000OnDraw(pgraphics);

      pgraphics->unchain(pdrawcontext);

   }


   bool control::_003IsCustomMessage()
   {

      return m_bCustomWindowProc;

   }


   void control::_003CallCustomDraw(::draw2d::graphics * pgraphics, ::aura::draw_context * pdrawcontext)
   {

      _003OnCustomDraw(pgraphics, pdrawcontext);

   }


   bool control::_003CallCustomWindowProc(sp(::user::interaction) pwnd, UINT message, WPARAM wparam, LPARAM lparam, LRESULT & lresult)
   {

      m_pwndCustomWindowProc = pwnd;

      keep <bool> keepOnCustomMessage(&m_bCustomWindowProc, true, false, true);

      ::message::base base(get_app(), pwnd, message, wparam, lparam, lresult);

      _003CustomWindowProc(&base);

      return base.m_bRet;

   }


   void control::_003CustomWindowProc(::message::message * pobj)
   {

      UNREFERENCED_PARAMETER(pobj);

   }


   bool control::operator == (const class control_descriptor & control_descriptor) const
   {

      return *m_pdescriptor == control_descriptor;

   }


   bool control::operator == (const class control & control) const
   {

      return operator == (*control.m_pdescriptor);

   }


   void control_descriptor::set_control_type(e_control_type econtroltype)
   {

      m_econtroltype = econtroltype;

      switch (m_econtroltype)
      {
      case control_type_edit:

         //         m_typeinfo = System.type_info < CSimpleFormListEdit > ();

         break;

      case control_type_combo_box:
      {

         //_throw(todo(get_app()));

//            m_data.m_pcombobox = new Ex1FormInterfaceComboBox;

      }
      break;
      default:
         break;
      }

   }


   e_control_type control_descriptor::get_control_type()
   {

      return m_econtroltype;

   }


   index control::GetEditItem()
   {

      return m_iEditItem;

   }


   index control::GetEditSubItem()
   {

      return control_descriptor().m_iSubItem;

   }


   void control::SetEditItem(index iItem)
   {

      m_iEditItem = iItem;

   }


   void control::SetEditSubItem(index iSubItem)
   {

      descriptor().m_iSubItem = iSubItem;

   }


   bool control::get_data(sp(::user::interaction)pwnd, var &var)
   {

      string str;

      if (control_descriptor().get_control_type() == control_type_edit)
      {

         sp(::user::edit_text) pedit = pwnd.m_p;

         if (pedit == NULL)
            return false;

         pedit->_001GetText(str);

      }
      else
      {

         sp(::user::edit_text) pedit = this;

         if (pedit == NULL)
            return false;

         pedit->_001GetText(str);

      }

      switch (control_descriptor().get_data_type())
      {
      case control_data_type_string:
      {
         var = str;
      }
      return true;
      case control_data_type_natural:
      {
         var = atoi(str);
         return true;
      }
      break;
      default:
         return false;
      }

   }


   bool control::Validate(string & strParam)
   {

      switch (control_descriptor().get_data_type())
      {
      case control_data_type_string:
         return true;
      case control_data_type_natural:
      {
         string str = strParam;
         str.trim_left();
         str.trim_right();
         for (int32_t i = 0; i < str.get_length(); i++)
         {
            if (str[i] >= L'0'
                  && str[i] <= L'9')
            {
            }
            else
            {
               return false;
            }

         }
         return true;
      }
      break;
      default:
         return true;
      }
   }


   control_ddx_dbflags::control_ddx_dbflags(::database::key key, int_ptr value)
   {

      m_key = key;
      m_value = value;

   }


   bool control::_001IsPointInside(point64 point)
   {

      return ::user::interaction::_001IsPointInside(point);

   }


   class control_descriptor & control::descriptor()
   {

      return *m_pdescriptor;

   }


   bool control::create_control(class control_descriptor * pdescriptorParam)
   {

      sp(control_descriptor) pdescriptor;

      if (pdescriptorParam->is_heap())
      {

         pdescriptor = pdescriptorParam;

      }
      else
      {

         pdescriptor = canew(control_descriptor(*pdescriptorParam));

      }

      try
      {

         if (!create_window(pdescriptor->m_rect, pdescriptor->m_puiParent, pdescriptor->m_id))
         {

            return false;

         }

      }
      catch (...)
      {

         return false;

      }




      m_pdescriptor = pdescriptor;

      m_pdescriptor->m_bCreated = true;

      m_pdescriptor->m_controlmap[m_pdescriptor->m_iItem] = this;

      return true;

   }






   bool control::GetWindowRect(LPRECT lprect)
   {

      if (m_pdrawcontext != NULL)
      {

         *lprect = m_pdrawcontext->m_rectWindow;

         return true;

      }

      return ::user::box::GetWindowRect(lprect);

   }



   bool control::GetClientRect(LPRECT lprect)
   {

      if (m_pdrawcontext != NULL)
      {

         *lprect = m_pdrawcontext->m_rectClient;

         offset(lprect, -m_pdrawcontext->m_rectClient.top_left());

         return true;

      }


      return ::user::box::GetClientRect(lprect);

   }


   index control::get_hover()
   {

      return m_iHover;

//      POINT pt;
//
//      Session.get_cursor_pos(&pt);
//
//      ScreenToClient(&pt);
//
//      rect rect;
//
//      GetWindowRect(rect);
//
//      if (!rect.contains(pt))
//      {
//
//         return -1;
//
//      }
//
//      return 0;

   }




   bool control::IsControlCommandEnabled()
   {
      return m_bControlExCommandEnabled;
   }

   void control::EnableControlCommand(bool bEnable)
   {
      m_bControlExCommandEnabled = bEnable;
      ControlExGetWnd()->set_need_redraw();
   }

   ::user::interaction * control::ControlExGetWnd()
   {
      return this;
   }


   void control::_001OnSetFocus(::message::message * pmessage)
   {

      //if (!::user::box::keyboard_focus_OnSetFocus())
      //{

      //   return false;

      //}

      ::user::control_event ev;

      ev.m_puie = this;

      ev.m_eevent = ::user::event_set_focus;

      on_control_event(&ev);

      pmessage->m_bRet =  ev.m_bRet;

   }


   void control::_001OnKillFocus(::message::message * pmessage)
   {

      SCAST_PTR(::message::kill_focus, pkillfocus, pmessage);

      ::user::control_event ev;

      ev.m_puie = this;

      ev.m_id = m_id;

      ev.m_eevent = ::user::event_kill_focus;

      on_control_event(&ev);

      pkillfocus->m_bRet = ev.m_bRet;

   }


   void control_cmd_ui::Enable(bool bOn)
   {

      m_bEnableChanged = TRUE;

      sp(::user::interaction) pwnd = m_puiOther;

      ASSERT(pwnd != NULL);

      ASSERT_KINDOF(::user::interaction, pwnd);

      sp(::user::interaction) pcontrol = pwnd->get_child_by_id(m_idControl);

      sp(control) pcontrolex = (pcontrol.m_p);

      if (pcontrolex != NULL)
      {

         if (bOn)
         {

            if (pwnd->is_window_enabled() && !pcontrolex->IsControlCommandEnabled())
            {

               pcontrolex->EnableControlCommand(true);

            }

         }
         else
         {

            if (pcontrolex->IsControlCommandEnabled())
            {

               pcontrolex->EnableControlCommand(false);

            }

         }

      }
      else
      {

         if (pcontrol != NULL)
         {

            if (bOn)
            {

               if (!pcontrol->is_window_enabled())
               {

                  pcontrol->enable_window();

               }

            }
            else
            {

               if (pcontrol->is_window_enabled())
               {

                  pcontrol->enable_window(FALSE);

               }

            }

         }

      }

   }


   void control_cmd_ui::SetCheck(int32_t nCheck)
   {
      ASSERT(nCheck >= 0 && nCheck <= 2); // 0=>off, 1=>on, 2=>indeterminate
      /*sp(::user::interaction) pwnd = (sp(::user::interaction))m_pOther;
      ASSERT(pToolBar != NULL);
      ASSERT_KINDOF(simple_toolbar, pToolBar);
      ASSERT(m_nIndex < m_nIndexMax);

      UINT nNewStyle = pToolBar->GetButtonStyle(m_nIndex) &
                  ~(TBBS_CHECKED | TBBS_INDETERMINATE);
      if (nCheck == 1)
          nNewStyle |= TBBS_CHECKED;
      else if (nCheck == 2)
          nNewStyle |= TBBS_INDETERMINATE;
      ASSERT(!(nNewStyle & TBBS_SEPARATOR));
      pToolBar->SetButtonStyle(m_nIndex, nNewStyle | TBBS_CHECKBOX);*/
   }

   void control_cmd_ui::SetText(const char *)
   {
      // ignore it
   }


   id control_cmd_ui::GetControlCommand(id id)
   {
      ::id idCommand;
      if (m_mapControlCommand.Lookup(id, idCommand))
      {
         return id;
      }
      return id;
   }


//   LRESULT control_view_impl::BaseControlExOnIdleUpdateCmdUI(WPARAM wParam, LPARAM)
//   {
//      sp(::user::interaction) pview = get_window();
//
//      // handle delay hide/show
//      bool bVis = (pview->GetStyle() & WS_VISIBLE) != 0;
//
//      // the style must be visible
//      if (bVis)
//      {
//         sp(::user::frame_window) pTarget = pview->GetOwner();
//         if (pTarget == NULL)
//            pTarget = pview->GetParentFrame();
//         if (pTarget != NULL)
//            BaseControlExOnUpdateCmdUI(pTarget, wParam != FALSE);
//      }
//
//      return 0L;
//
//   }
//
//
//   void control_view_impl::BaseControlExOnUpdateCmdUI(sp(::user::frame_window) pTarget, bool bDisableIfNoHndler)
//   {
//
//      sp(::user::interaction) pview = get_window();
//
//      ::user::command & state = m_commandui;
//
//      state.m_puiOther = pview;
//
//      sp(::user::interaction) pwndIterator = pview->GetTopWindow();
//
//      sp(::user::interaction) pwnd;
//
//      sp(control) pcontrolex;
//
//      for (; pwndIterator != NULL; pwndIterator = pwndIterator->get_next_window())
//      {
//
//         pwnd = pwndIterator->GetTopLevel();
//
//         pcontrolex = NULL;
//
//         if (pwnd != NULL)
//         {
//            //#ifdef WINDOWSEX
//            //            pwnd->send_message(control::g_uiMessage, control::MessageParamGetBaseControlExPtr, (LPARAM) &pcontrolex);
//            //#else
//            _throw(todo(pwnd->get_app()));
//            //#endif
//         }
//         if (pcontrolex != NULL)
//         {
//
//            id idControl = pwnd->GetDlgCtrlId();
//
//            // xxx         state.m_nIndex = uiID;
//            state.m_iCount = -1;
//            state.m_id = m_commandui.GetControlCommand(idControl);
//            state.m_bContinueRouting = FALSE;
//
//            // ignore separators
//            if ((pwnd->GetStyle() & WS_VISIBLE))
//            {
//               // allow reflections
//               if (pview->on_command_probe(&state))
//               {
//                  continue;
//               }
//
//               // allow the toolbar itself to have update handlers
//               if (pview->on_command_probe(&state))
//                  //               {
//                    //                state.DoUpdate(pTarget, bDisableIfNoHndler);
//                  continue;
//               //           }
//
//                          // allow the owner to process the update
//               state.DoUpdate(pTarget, bDisableIfNoHndler);
//            }
//         }
//      }
//
//      // update the dialog controls added to the toolbar
//  //  UpdateDialogControls(pTarget, bDisableIfNoHndler);
//   }
//
//
//   sp(::user::interaction) control_view_impl::get_window()
//   {
//      return  (this);
//   }
//
//
//   bool control_view_impl::BaseControlExOnCommand(WPARAM wParam, LPARAM lParam)
//   {
//
//      UNREFERENCED_PARAMETER(lParam);
//
//      if (get_window() != NULL)
//      {
//
//#ifdef WINDOWS
//
//         UINT uiMessage = ((wParam >> 16) & 0xffff);
//
//
//         if (uiMessage == BN_CLICKED)
//         {
//            //xxx id idCommand = m_commandui.GetControlCommand(wParam & 0xffff);
//            //::user::command command(idCommand);
//            //xxx get_window()->GetParentFrame()->_001SendCommand(&command);
//         }
//
//#endif
//
//      }
//
//      return FALSE;
//
//   }



   void control::BaseControlExOnMouseMove(UINT nFlags, point point)
   {
      UNREFERENCED_PARAMETER(nFlags);
      UNREFERENCED_PARAMETER(point);
      sp(::user::interaction) pwnd = ControlExGetWnd();

      class point ptCursor;
      Session.get_cursor_pos(&ptCursor);

      e_element eelement;

      index iHover = hit_test(ptCursor, eelement);

      if (iHover != -1)
      {

         if (m_iHover != iHover || Session.GetCapture() != pwnd)
         {

            m_iHover = iHover;

            pwnd->SetCapture();

            pwnd->set_need_redraw();

         }

      }
      else
      {

         if (m_iHover != -1)
         {

            m_iHover = -1;

            Session.ReleaseCapture();

            pwnd->set_need_redraw();

         }

      }

   }


   void control::_001OnMouseMove(::message::message * pobj)
   {
      SCAST_PTR(::message::mouse, pmouse, pobj);

      index iHover = hit_test(pmouse->m_pt, m_eelementHover);

      if (m_iHover != iHover)
      {

         m_iHover = iHover;

         if (m_iHover >= 0)
         {

            track_mouse_leave();

         }

         set_need_redraw();

      }

   }


   void control::_001OnMouseLeave(::message::message * pmessage)
   {

      m_iHover = -1;

      m_eelementHover = element_none;

      ::user::control_event ev;

      ev.m_id = m_id;

      ev.m_puie = this;

      ev.m_eevent = event_mouse_leave;

      ev.m_pmessage = pmessage;

      on_control_event(&ev);
   }


// the value -1 indicates outside the control,
// other values may be control specific and are client hits
   index control::hit_test(point ptScreen, e_element & eelement)
   {

      ::user::interaction * pwnd = ControlExGetWnd();

      rect rectWindow;

      pwnd->GetWindowRect(rectWindow);

      if (rectWindow.contains(ptScreen))
      {

         eelement = element_client;

         return 0;

      }
      else
      {

         eelement = element_none;

         return -1;

      }

   }


   control_cmd_ui::control_cmd_ui()
   {

   }


   void control::on_control_event(::user::control_event * pevent)
   {

      ::user::interaction * puiBind = get_bind_ui();

      if (puiBind != NULL)
      {

         puiBind->on_control_event(pevent);

         if (pevent->m_bRet)
         {

            return;

         }

      }

      ::user::form * pform = get_form();

      if (pform != NULL)
      {

         pform->on_control_event(pevent);

         if (pevent->m_bRet)
         {

            return;

         }

      }

      ::user::interaction * puiParent = GetParent();

      if (puiParent != NULL && puiParent != pform)
      {

         puiParent->on_control_event(pevent);

         if (pevent->m_bRet)
         {

            return;

         }

      }

      ::user::interaction * puiOwner = GetOwner();

      if (puiOwner != NULL && puiOwner != pform && puiOwner != puiParent)
      {

         puiOwner->on_control_event(pevent);

         if (pevent->m_bRet)
         {

            return;

         }

      }

   }


   bool control::simple_process_system_message(::message::message * pmessage, ::user::e_event eevent)
   {

      SCAST_PTR(::message::base, pbase, pmessage);

      if (eevent == ::user::event_button_down)
      {

         Session.m_puiLastLButtonDown = this;

      }

      ::user::control_event ev;

      ev.m_puie = this;

      ev.m_eevent = eevent;

      ev.m_pmessage = pmessage;

      on_control_event(&ev);

      pmessage->m_bRet = ev.m_bRet;

      if (pmessage->m_bRet)
      {

         if (pbase != NULL)
         {

            pbase->set_lresult(1);

         }

      }

      return ev.m_bRet;

   }


   void control::_001OnDraw(::draw2d::graphics * pgraphics)
   {

      ::user::box::_001OnDraw(pgraphics);
   }


   void control::route_command_message(::user::command * pcommand)
   {

      ::user::box::route_command_message(pcommand);

      if (pcommand->m_bRet)
      {

         return;

      }

      sp(::user::interaction) puiParent = get_parent();

      while (puiParent.is_set() && puiParent->is_place_holder())
      {

         puiParent = puiParent->get_parent();

      }

      if (puiParent != NULL)
      {

         puiParent->route_command_message(pcommand);

      }


   }


   void control::_001OnKeyDown(::message::message * pobj)
   {

      UNREFERENCED_PARAMETER(pobj);
      //      SCAST_PTR(::message::key,pkey,pobj);


   }


   void control::_001OnEnable(::message::message * pobj)
   {

      SCAST_PTR(::message::enable, penable, pobj);

      if (m_puiLabel != NULL)
      {

         m_puiLabel->enable_window(penable->get_enable());

      }

   }


   bool control::get_element_rect(LPRECT lprect, e_element eelement)
   {

      if (eelement == element_drop_down)
      {

         rect rectClient;

         ((control *)this)->GetClientRect(rectClient);

         //int32_t iMargin = rectClient.height() / 8;
         int32_t iMargin = 0;

         rect rectDropDown;

         rectDropDown = rectClient;

         int32_t iW = rectClient.height() * 5 / 8;

         rectDropDown.right -= iMargin;
         rectDropDown.bottom -= iMargin;
         rectDropDown.top += iMargin;
         rectDropDown.left = rectDropDown.right - iW;

         *lprect = rectDropDown;

         return true;

      }
      else if (eelement == element_combo_edit)
      {

         rect rectClient;

         GetClientRect(rectClient);

         rect rectDropDown;

         get_element_rect(rectDropDown, element_drop_down);

         rect rectEdit = rectClient;

         rectEdit.right = rectDropDown.left;

         //rect rectPadding = _001GetRect(::user::rect_edit_padding);

         //rectEdit.deflate(rectPadding);

         *lprect = rectEdit;

         return true;

      }

      return false;

   }


   void control::get_simple_drop_down_open_arrow_polygon(point_array & pointa)
   {

      rect rectDropDown;

      get_element_rect(rectDropDown, element_drop_down);

      int32_t cx = rectDropDown.width() / 3;

      int32_t cy = cx * 2 / 3;

      point ptCenter = rectDropDown.center();

      pointa.add(ptCenter.x - cx / 2, ptCenter.y - cy / 2);

      pointa.add(ptCenter.x + cx / 2, ptCenter.y - cy / 2);

      pointa.add(ptCenter.x, ptCenter.y + cy / 2);

   }



} // namespace core



