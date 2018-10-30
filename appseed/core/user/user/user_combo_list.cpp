#include "framework.h"


namespace user
{


   combo_list::combo_list()
   {

      defer_create_mutex();

      m_bComboList = true;

      m_puiDeactivateTogether = NULL;

      m_puiDeactivateTogetherSet = NULL;

      m_pcombo = NULL;

      m_iHover = -1;

      m_iBorder = 6;

   }


   combo_list::combo_list(::aura::application * papp) :
      object(papp)
   {

      defer_create_mutex();

      m_bComboList = true;

      m_puiDeactivateTogether = NULL;

      m_puiDeactivateTogetherSet = NULL;

      m_pcombo = NULL;

      m_iHover = -1;

      m_iBorder = 6;

      m_bMovingComboBox = false;

   }


   combo_list::~combo_list()
   {


   }


   void combo_list::install_message_routing(::message::sender * psender)
   {

      ::user::control::install_message_routing(psender);

      IGUI_MSG_LINK(WM_SETFOCUS, psender, this, &combo_list::_001OnSetFocus);
      IGUI_MSG_LINK(WM_KILLFOCUS, psender, this, &combo_list::_001OnKillFocus);
      IGUI_MSG_LINK(WM_CLOSE, psender, this, &combo_list::_001OnClose);
      //IGUI_MSG_LINK(WM_ACTIVATE, psender, this, &combo_list::_001OnActivate);
      IGUI_MSG_LINK(WM_MOUSEACTIVATE, psender, this, &combo_list::_001OnMouseActivate);
      IGUI_MSG_LINK(WM_KEYDOWN, psender, this, &combo_list::_001OnKeyDown);
      IGUI_MSG_LINK(WM_KEYUP, psender, this, &combo_list::_001OnKeyUp);
      IGUI_MSG_LINK(WM_LBUTTONDOWN, psender, this, &combo_list::_001OnLButtonDown);
      IGUI_MSG_LINK(WM_LBUTTONUP, psender, this, &combo_list::_001OnLButtonUp);
      IGUI_MSG_LINK(WM_MBUTTONDOWN, psender, this, &combo_list::_001OnMButtonDown);
      IGUI_MSG_LINK(WM_RBUTTONDOWN, psender, this, &combo_list::_001OnRButtonDown);
      IGUI_MSG_LINK(WM_MOUSEMOVE, psender, this, &combo_list::_001OnMouseMove);
      IGUI_MSG_LINK(WM_SHOWWINDOW, psender, this, &combo_list::_001OnShowWindow);

   }


   void combo_list::_001OnDraw(::draw2d::graphics * pgraphics)
   {

      ::draw2d::savedc savedc(pgraphics);

      if (m_pcombo == NULL)
      {

         return;

      }

      _001OnDrawComboList(pgraphics);

   }


   void combo_list::_001OnDrawComboList(::draw2d::graphics * pgraphics)
   {

      ::count iListItemCount = m_pcombo->_001GetListCount();

      string strItem;

      rect rectClient;

      GetClientRect(rectClient);

      ::draw2d::brush_sp brBk(allocer());

      brBk->create_solid(ARGB(230, 255, 255, 255));

      pgraphics->SelectObject(brBk);

      pgraphics->fill_rect(rectClient);

      rect rectItem;

      rectItem = rectClient;

      rectItem.bottom = rectClient.top;

      if (m_pcombo->m_bEdit)
      {

         rectItem.bottom += _001GetItemHeight();

      }

      point ptCursor;

      Session.get_cursor_pos(&ptCursor);

      ScreenToClient(&ptCursor);

      if (m_pcombo != NULL)
      {

         m_pcombo->select_font(pgraphics, font_plain_edit);

      }
      else
      {

         select_font(pgraphics, font_plain_edit);

      }

      index iHover = m_iHover;

      if (iHover < 0 || iHover >= iListItemCount)
      {

         iHover = -1;

      }

      index iCurSel = m_pcombo->_001GetCurSel();

      ::draw2d::brush_sp br(allocer());

      for (index iItem = 0; iItem < iListItemCount; iItem++)
      {

         rectItem.top = rectItem.bottom;

         rectItem.bottom = rectItem.top + _001GetItemHeight();

         COLORREF crBk;

         COLORREF cr;

         if (iItem == iHover)
         {

            if (iItem == iCurSel)
            {

               crBk = _001GetColor(::user::color_list_item_background_selected_hover);

               cr = _001GetColor(::user::color_list_item_text_selected_hover);

            }
            else
            {

               crBk = _001GetColor(::user::color_list_item_background_hover);

               cr = _001GetColor(::user::color_list_item_text_hover);

            }

         }
         else if (iItem == iCurSel)
         {

            crBk = _001GetColor(::user::color_list_item_background_selected);

            cr = _001GetColor(::user::color_list_item_text_selected);

         }
         else
         {

            crBk = _001GetColor(::user::color_list_item_background);

            cr = _001GetColor(::user::color_list_item_text);

         }

         brBk->create_solid(crBk);

         br->create_solid(cr);

         pgraphics->SelectObject(brBk);

         pgraphics->fill_rect(rectItem);

         m_pcombo->_001GetListText(iItem, strItem);

         pgraphics->SelectObject(br);

         pgraphics->draw_text(strItem, rectItem, 0);

      }

   }


   void combo_list::query_full_size(LPSIZE lpsize)
   {

      //ShowWindow(SW_HIDE);

      //int i = 0;
      //while (IsWindowVisible() && i < 10)
      //{

      //   Sleep(5);

      //   i++;


      //}

      synch_lock sl(m_pmutex);

      if (!((combo_list *)this)->IsWindow())
         return;

      ::draw2d::graphics_sp pgraphics(((combo_list *) this)->allocer());

      pgraphics->CreateCompatibleDC(NULL);

      if (m_pcombo != NULL)
      {

         m_pcombo->select_font(pgraphics, font_plain_edit);

      }
      else
      {

         select_font(pgraphics, font_plain_edit);

      }

      pgraphics->set_text_rendering_hint(::draw2d::text_rendering_hint_anti_alias);

      string strItem;

      size sz;

      lpsize->cx = 0;

      m_iItemHeight = 0;

      ::count ca = m_pcombo->_001GetListCount();

      for (index i = 0; i < ca; i++)
      {

         m_pcombo->_001GetListText(i, strItem);

         sz = pgraphics->GetTextExtent(strItem);

         if (sz.cx > lpsize->cx)
         {

            lpsize->cx = sz.cx;

         }

         if (sz.cy > m_iItemHeight)
         {

            m_iItemHeight = sz.cy;

            if (sz.cy != 18)
            {

               output_debug_string("\nCOMBO LIST ITEM HEIGHT != 18\n");

            }

         }

      }

      m_iItemHeight += 4;

      int iAddUp = 0;

      if (m_pcombo->m_bEdit)
      {

         iAddUp = 1;

      }

      lpsize->cy = (LONG)(_001GetItemHeight() * (m_pcombo->_001GetListCount() + iAddUp));

      lpsize->cx += m_iBorder * 2;

      ::rect rectComboClient;

      m_pcombo->GetClientRect(rectComboClient);

      lpsize->cx = MAX(lpsize->cx, rectComboClient.width());

   }


   void combo_list::on_change_combo_sel(index iSel)
   {



   }


   int32_t combo_list::_001GetItemHeight() const
   {

      return m_iItemHeight;

   }

   bool combo_list::GetClientRect(RECT64 * lprect)
   {

      if (!::user::control::GetClientRect(lprect))
      {

         return false;

      }

      ::deflate_rect(lprect, m_iBorder);

      return true;

   }


   bool combo_list::keyboard_focus_is_focusable()
   {

      return true;

   }


   bool combo_list::keyboard_focus_OnKillFocus(oswindow oswindowNew)
   {

      if (IsWindowVisible())
      {

         ShowWindow(SW_HIDE);

         if (m_pcombo != NULL && m_pcombo->IsWindowVisible())
         {

            m_pcombo->SetFocus();

         }

      }

      return true;

   }


   bool combo_list::pre_create_window(::user::create_struct & cs)
   {

      if (cs.style & WS_BORDER)
      {
#ifdef WINDOWSEX
         cs.dwExStyle |= WS_EX_CLIENTEDGE;
#endif
         cs.style &= ~WS_BORDER;
      }

      cs.dwExStyle |= WS_EX_LAYERED;
      cs.dwExStyle |= WS_EX_TOOLWINDOW;
      cs.dwExStyle |= WS_EX_TOPMOST;
      //cs.dwExStyle |= WS_EX_NOACTIVATE;

      return TRUE;
   }


   void combo_list::_001OnShowWindow(::message::message * pobj)
   {

      SCAST_PTR(::message::show_window, pshowwindow, pobj);

      if (pshowwindow->m_bShow)
      {

#ifdef WINDOWS

         keyboard_set_focus();




         //if (get_handle() != ::GetFocus())
         //{

         //   SetFocus();

         //}

         //keyboard_set_focus();

#endif

      }
      else
      {

         output_debug_string("combo_list hide");

      }

   }


   void combo_list::_001OnKillFocus(::message::message * pobj)
   {

      SCAST_PTR(::message::kill_focus, pkillfocus, pobj);

      oswindow oswindowThis = get_safe_handle();

      oswindow oswindowNew = pkillfocus->m_oswindowNew;

      if(oswindowThis != oswindowNew
            && !m_bMovingComboBox)
      {

         ShowWindow(SW_HIDE);

      }

      pkillfocus->m_bRet = true;

      pkillfocus->set_lresult(0);

   }


   void combo_list::_001OnSetFocus(::message::message * pobj)
   {

//      SCAST_PTR(::message::set_focus, psetfocus, pobj);

      //psetfocus->m_bRet = true;

      //psetfocus->set_lresult(0);

      m_iHover = m_pcombo->m_iSel;

   }



   void combo_list::_001OnActivate(::message::message * pobj)
   {

      SCAST_PTR(::message::activate, pactivate, pobj);

      sp(::user::interaction) pActive = (pactivate->m_nState == WA_INACTIVE ? pactivate->m_pWndOther : this);

      if (pactivate->m_nState == WA_INACTIVE)
      {

         point ptCursor;

         Session.get_cursor_pos(&ptCursor);

         m_pcombo->ScreenToClient(&ptCursor);

         //if(m_pcombo->hit_test(ptCursor) != element_drop_down)
         //{

         //   m_pcombo->_001ShowDropDown(false);

         //}




         //if(pActive != m_puiDeactivateTogether)
         //{

         //   ::user::wndfrm::frame::WorkSet * pset = m_puiDeactivateTogetherSet;

         //   if(pset != NULL)
         //   {

         //      pset->SetActiveFlag(FALSE);

         //   }

         //}



      }
      else
      {

         Session.set_keyboard_focus(this);


      }

   }


   void combo_list::_001OnMouseActivate(::message::message * pobj)
   {

      SCAST_PTR(::message::mouse_activate, pactivate, pobj);

      pactivate->m_lresult = MA_NOACTIVATE;

      pactivate->m_bRet = true;


   }

   void combo_list::_001OnLButtonUp(::message::message * pobj)
   {

      SCAST_PTR(::message::mouse, pmouse, pobj);

      pmouse->m_bRet = true;

   }

   void combo_list::_001OnKeyDown(::message::message * pobj)
   {

      SCAST_PTR(::message::key, pkey, pobj);

      if (pkey->m_ekey == ::user::key_escape)
      {

         m_pcombo->ShowDropDown(false);

      }
      else if (pkey->m_ekey == ::user::key_tab)
      {

         m_pcombo->ShowDropDown(false);

         sp(::user::elemental) pelemental = m_pcombo->keyboard_get_next_focusable();

         if (pelemental.is_set())
         {

            pelemental->keyboard_set_focus();

         }


      }
      else if (pkey->m_ekey == ::user::key_down)
      {

         m_iHover = MIN(m_iHover + 1, m_pcombo->_001GetListCount() - 1);

      }
      else if (pkey->m_ekey == ::user::key_up)
      {

         m_iHover = MAX(m_iHover - 1, 0);

      }
      else if (pkey->m_ekey == ::user::key_return)
      {

         m_pcombo->_001SetCurSel(m_iHover, ::action::source_user);

         m_pcombo->ShowDropDown(false);

         sp(::user::elemental) pelemental = m_pcombo->keyboard_get_next_focusable();

         if (pelemental.is_set())
         {

            pelemental->keyboard_set_focus();

         }

      }

   }


   void combo_list::_001OnKeyUp(::message::message * pobj)
   {

      UNREFERENCED_PARAMETER(pobj);

   }

   void combo_list::_001OnLButtonDown(::message::message * pobj)
   {

      SCAST_PTR(::message::mouse, pmouse, pobj);

      point pt = pmouse->m_pt;

      ScreenToClient(&pt);

      rect rectClient;

      GetClientRect(rectClient);

      if (rectClient.contains(pt))
      {

         e_element eelement;

         index iItem = hit_test(pt, eelement);

         if (eelement == element_item)
         {

            m_pcombo->_001ShowDropDown(false);

            ::user::control_event ev;

            ev.m_puie = this;

            ev.m_id = m_id;

            ev.m_eevent = ::user::event_after_change_cur_sel;

            ev.m_actioncontext = ::action::source_user;

            ev.m_iItem = iItem;

            on_control_event(&ev);

         }

      }

      pobj->m_bRet = true;

   }


   void combo_list::_001OnMButtonDown(::message::message * pobj)
   {

      SCAST_PTR(::message::mouse, pmouse, pobj);

      point pt = pmouse->m_pt;

      ScreenToClient(&pt);

      rect rectClient;

      GetClientRect(rectClient);

      if (rectClient.contains(pt))
      {

      }
      else
      {

         m_pcombo->_001ShowDropDown(false);

      }

      pobj->m_bRet = true;

   }


   void combo_list::_001OnRButtonDown(::message::message * pobj)
   {

      SCAST_PTR(::message::mouse, pmouse, pobj);

      point pt = pmouse->m_pt;

      ScreenToClient(&pt);

      rect rectClient;

      GetClientRect(rectClient);

      if (rectClient.contains(pt))
      {

      }
      else
      {

         m_pcombo->_001ShowDropDown(false);

      }

      pobj->m_bRet = true;

   }


   void combo_list::_001OnMouseMove(::message::message * pobj)
   {

      SCAST_PTR(::message::mouse, pmouse, pobj);

      pobj->m_bRet = true;

      point pt = pmouse->m_pt;

      ScreenToClient(&pt);

      e_element eelement;

      index iHover = hit_test(pt, eelement);

      if (iHover != m_iHover)
      {

         m_iHover = iHover;

         set_need_redraw();

      }

   }


   void combo_list::_001OnClose(::message::message * pobj)
   {

      pobj->m_bRet = true;

      ShowWindow(SW_HIDE);

   }


   index combo_list::hit_test(point pt, e_element & eelement)
   {

      if (m_pcombo == NULL)
      {

         return -1;

      }

      ::count ca = m_pcombo->_001GetListCount();

      rect rectClient;

      GetClientRect(rectClient);

      rect rectItem;

      rectItem = rectClient;

      int iAddUp = 0;

      if (m_pcombo->m_bEdit)
      {

         iAddUp = 1;

      }

      for (int32_t i = 0; i < ca; i++)
      {

         rectItem.top = rectClient.top + (_001GetItemHeight() * (iAddUp + i));

         rectItem.bottom = rectItem.top + _001GetItemHeight();

         if (rectItem.contains(pt))
         {

            eelement = element_item;

            return i;

         }


      }

      rectItem.top = rectClient.top;

      rectItem.bottom = rectItem.top + _001GetItemHeight();

      if (rectItem.contains(pt))
      {

         eelement = element_search_edit;

         return 0;

      }

      eelement = element_none;

      return -1;

   }


   bool combo_list::ShowWindow(int nCmdShow)
   {

      if (nCmdShow == SW_HIDE)
      {

         output_debug_string("hiding combo list");

      }
      else
      {

         output_debug_string("showing combo list");

      }

      return ::user::control::ShowWindow(nCmdShow);

   }

   bool combo_list::has_pending_graphical_update()
   {

      return m_bRedraw;

   }


   void combo_list::on_drop_down(rect rectWindow, size sizeFull)
   {

      rect rectMonitor;

      Session.get_best_monitor(rectMonitor, rectWindow);

      rect rectList;

      rectList.left = rectWindow.left;
      rectList.right = rectWindow.left + MAX(rectWindow.width(), sizeFull.cx);
      rectList.top = rectWindow.bottom;
      rectList.bottom = rectWindow.bottom + sizeFull.cy;

      if (rectList.bottom > rectMonitor.bottom -m_iBorder)
      {

         rectList.bottom = rectMonitor.bottom - m_iBorder;

         rect rectListOver;

         rectListOver.left = rectWindow.left;
         rectListOver.right = rectWindow.left + sizeFull.cx;
         rectListOver.bottom = rectWindow.top;
         rectListOver.top = rectWindow.top - sizeFull.cy;

         if (rectListOver.top < rectMonitor.top + m_iBorder)
         {

            rectListOver.top = rectMonitor.top + m_iBorder;

            if (rectListOver.height() > rectList.height())
            {

               rectList = rectListOver;

            }

         }

      }

      if (rectList.right > rectMonitor.right - m_iBorder)
      {

         rectList.offset(rectMonitor.right - (rectList.right-m_iBorder), 0);

      }

      if (rectList.left < rectMonitor.left)
      {

         rectList.move_to_x(0);

      }

      m_iHover = m_pcombo->_001GetCurSel();

      if (m_iHover < 0)
      {

         m_iHover = 0;

      }

//#ifdef WINDOWS
//
//      SetWindowPos(ZORDER_TOPMOST,
//                   rectList.left - m_iBorder,
//                   rectList.top - m_iBorder,
//                   rectList.width() + m_iBorder * 2,
//                   rectList.height() + m_iBorder * 2, SWP_SHOWWINDOW | SWP_NOACTIVATE);
//
//      ShowWindow(SW_SHOW);
//
//#else

      SetWindowPos(ZORDER_TOPMOST,
                   rectList.left - m_iBorder,
                   rectList.top - m_iBorder,
                   rectList.width() + m_iBorder * 2,
                   rectList.height() + m_iBorder * 2, SWP_SHOWWINDOW | SWP_NOACTIVATE);

      //ShowWindow(SW_SHOWNOACTIVATE);

      keyboard_set_focus();

      set_need_redraw();

//#endif

   }


   //bool combo_list::get_font(::draw2d::font_sp & spfont, e_font efont, ::user::interaction * pui)
   //{

   //   if (m_spfont.is_set())
   //   {

   //      spfont = m_spfont;

   //      return true;

   //   }

   //   return ::user::style::get_font(spfont);

   //}

} // namespace user




