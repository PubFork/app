#include "framework.h"


namespace user
{



   menu::menu() :
      menu(get_app())
   {

   }


   menu::menu(::aura::application * papp) :
      ::object(papp),
      m_itemClose(papp)
   {

      m_iFlags = 0;
      m_bPositionHint = false;
      m_itemClose.m_id = "close";
      m_itemClose.m_pmenu = this;
      m_bAutoDelete = true;
      m_puserstyle = NULL;
      m_bOwnItem = true;
      m_puiParent = NULL;
      m_puiNotify = NULL;
      m_pmenuParent = NULL;
      m_psubmenu = NULL;
      m_iHoverSubMenu = -1;
      m_bInline = false;
      m_bMenuOk = false;

   }


   menu::menu(::aura::application * papp, ::user::menu_item * pitem) :
      ::object(papp),
      m_itemClose(papp)
   {

      m_iFlags = 0;
      m_bPositionHint = false;
      m_iHoverSubMenu = -1;
      m_puiParent = NULL;
      m_puiNotify = NULL;
      m_pmenuParent = NULL;
      m_psubmenu = NULL;
      m_bAutoDelete = true;
      m_puserstyle = NULL;
      m_pitem = pitem;
      m_bOwnItem = false;
      m_bInline = false;
      m_bMenuOk = false;

   }


   menu::~menu()
   {

   }


   void menu::install_message_routing(::message::sender * psender)
   {

      ::user::control::install_message_routing(psender);

      //IGUI_MSG_LINK(WM_IDLEUPDATECMDUI  , psender, this, &menu::_001OnIdleUpdateCmdUI);
      IGUI_MSG_LINK(WM_CREATE       , psender, this, &menu::_001OnCreate);
      IGUI_MSG_LINK(WM_DESTROY      , psender, this, &menu::_001OnDestroy);
      IGUI_MSG_LINK(WM_NCACTIVATE   , psender, this, &menu::_001OnNcActivate);
      IGUI_MSG_LINK(WM_NCCALCSIZE   , psender, this, &menu::_001OnNcCalcSize);
      IGUI_MSG_LINK(WM_ENABLE       , psender, this, &menu::_001OnEnable);
      IGUI_MSG_LINK(WM_SHOWWINDOW   , psender, this, &menu::_001OnShowWindow);

      IGUI_MSG_LINK(WM_SHOWWINDOW   , psender, this, &menu::_001OnShowWindow);
      IGUI_MSG_LINK(WM_DESTROY      , psender, this, &menu::_001OnDestroy);


   }


   void menu::hint_flags(int iFlags)
   {

      m_iFlags = iFlags;

   }


   void menu::hint_position(point pt)
   {

      m_bPositionHint = true;

      m_ptPositionHint = pt;

   }


   void menu::hints(int iFlags, point pt)
   {

      hint_flags(iFlags);

      hint_position(pt);

   }


   bool menu::create_menu(const stringa & straCommand, const stringa & straCommandTitle)
   {

      if (m_pitem.is_null())
      {

         m_pitem = Application.alloc(System.type_info < menu_item >());

      }

      return m_pitem->create_menu(straCommand, straCommandTitle);

   }


   void menu::destroy_menu()
   {

      try
      {

         interaction_spa uiptra = m_uiptraChild;

         for (index i = 0; i < uiptra.get_count(); i++)
         {

            try
            {

               uiptra[i]->DestroyWindow();

            }
            catch (...)
            {

            }

         }

      }
      catch (...)
      {


      }

      m_uiptraChild.remove_all();

      m_pitem.release();

   }




   bool menu::load_menu(::xml::node * lpnode)
   {

      if (m_pitem.is_null())
      {

         m_pitem = Application.alloc(System.type_info < menu_item >());

      }

      if (m_pitem.is_null())
      {

         return false;

      }

      m_pitem->m_pmenu = this;

      return m_pitem->load_menu(lpnode);

   }


   bool menu::load_xml_menu(const char * pszMatter)
   {

      if (m_pitem.is_null())
      {

         m_pitem = Application.alloc(System.type_info < menu_item >());

      }

      xml::document doc(get_app());

      string strPath = Application.dir().matter(pszMatter);

      string strXml = Application.file().as_string(strPath);

      if (!doc.load(strXml))
      {

         return false;

      }

      return load_menu(doc.get_root());

   }


   void menu::_001OnShowWindow(::message::message * pobj)
   {

      SCAST_PTR(::message::show_window, pshow, pobj);

      TRACE("menu::_001OnShowWindow bShow = %d", pshow->m_bShow);

   }


   void menu::_001OnDestroy(::message::message * pobj)
   {

      if (m_pmenuParent != NULL)
      {

         m_pmenuParent->m_psubmenu.release();

      }

      if (m_psubmenu.is_set() && m_psubmenu->m_pmenuParent != NULL)
      {

         m_psubmenu->m_pmenuParent = NULL;

      }

      m_pitem.release();

   }


   ::user::menu_item * menu::GetSubMenu(int32_t i)
   {

      return get_item()->m_spitema->element_at(i);

   }


   bool menu::create_menu(::user::interaction * puiNotify, ::user::interaction * puiParent)
   {

      m_puiParent = puiParent;

      if (puiNotify != NULL)
      {

         m_puiNotify = puiNotify;

      }
      else if (m_puiNotify == NULL)
      {

         m_puiNotify = m_puiParent;

      }

      m_pmenuParent = NULL;

      LPVOID lpvoid = NULL;

      if (m_puserstyle == NULL)
      {

         ::user::interaction * pui = m_puiParent;

         while (pui != NULL)
         {

            m_puserstyle = pui->m_puserstyle;

            if (m_puserstyle != NULL)
            {

               break;

            }

            pui = pui->GetParent();

         }

         if (m_puserstyle == NULL)
         {

            ::user::interaction * pui = m_puiNotify;

            while (pui != NULL)
            {

               m_puserstyle = pui->m_puserstyle;

               if (m_puserstyle != NULL)
               {

                  break;

               }

               pui = pui->GetParent();

            }

         }

      }

      if (!IsWindow())
      {

         int iStyleEx = 0;

         if (puiParent == NULL)
         {

            iStyleEx = WS_EX_LAYERED | WS_EX_TOOLWINDOW;

         }

         if (!create_window_ex(iStyleEx, NULL, NULL, 0, rect(0, 0, 0, 0), puiParent, id(), lpvoid))
         {

            return false;

         }

         if (puiNotify != NULL)
         {

            SetOwner(puiNotify);

         }

      }

      if (m_itemClose.m_pui.is_null())
      {

         m_itemClose.m_pui = create_menu_button();

      }

      {

         control_descriptor descriptor;

         descriptor.m_puiParent = this;

         descriptor.m_id = "close";

         descriptor.m_iItem = 65536;

         if (!m_itemClose.m_pui->create_control(&descriptor))
         {

            return false;

         }

      }

      m_itemClose.m_pui->set_window_text("r");

      if (!m_pitem->create_buttons(this))
      {

         ASSERT(FALSE);

         return false;

      }

      return true;


   }



   bool menu::create_inline_menu(::user::interaction * puiNotify, ::user::interaction * puiParent)
   {

      m_bMenuOk = false;

      if (!create_menu(puiNotify, puiParent))
      {

         return false;

      }

      m_bInline = true;

      update_command(m_pitem);

      m_bMenuOk = true;

      //      create_buttons(m_pitem);

      //on_layout();

      //rect rectClient;

      //puiParent->GetClientRect(rectClient);

      //SetWindowPos(0, 0, 0, rectClient.width(), rectClient.height(), SWP_SHOWWINDOW | SWP_NOZORDER);

      set_need_layout();

      SetTimer(::user::timer_command_probe, 300, NULL);

      return true;

   }



   bool menu::track_popup_menu(::user::interaction * puiNotify, ::user::interaction * puiParent)
   {

      if (!create_menu(puiNotify, puiParent))
      {

         return false;

      }

      if (!m_bPositionHint)
      {

         Session.get_cursor_pos(m_ptPositionHint);

      }

      layout_menu(m_ptPositionHint);

      m_bMenuOk = true;

      set_need_layout();

      SetActiveWindow();

      SetForegroundWindow();

      BringWindowToTop();

      return true;

   }


   void menu::layout_menu(point pt)
   {

      if (GetParent() != NULL)
      {

         GetParent()->ScreenToClient(&pt);

      }

      m_ptTrack = pt;

      ::draw2d::memory_graphics pgraphics(allocer());

      select_font(pgraphics, ::user::font_list_item);

      size size = pgraphics->GetTextExtent(unitext("XXXMMMÁÇg"));

      int32_t iMaxHeight = size.cy;

      int32_t iMaxWidth = size.cx;

      m_iCheckBoxSize = iMaxHeight;

      m_iHeaderHeight = size.cy;

      sp(::user::menu_item) pitem = get_item();

      sp(::user::menu_item_ptra) spitema = pitem->m_spitema;

      rect rectMargin = get_rect(rect_menu_margin);

      int iElementPadding = get_int(int_menu_button_padding);

      for (int32_t i = 0; i < spitema->get_size(); i++)
      {

         string strButtonText = spitema->element_at(i)->m_pui->get_window_text();

         class size size = pgraphics->GetTextExtent(strButtonText);

         size.cx += rectMargin.left;

         size.cx += rectMargin.right;

         size.cx += m_puserstyle->get_int(int_menu_button_padding);

         size.cx += m_iCheckBoxSize;

         if (spitema->element_at(i)->IsPopup())
         {

            size.cx += m_puserstyle->get_int(int_menu_button_padding);

            size.cx += m_iCheckBoxSize;

         }

         size.cy += rectMargin.top;

         size.cy += rectMargin.bottom;

         if (size.cy > iMaxHeight)
         {

            iMaxHeight = size.cy;

         }

         if (size.cx > iMaxWidth)
         {

            iMaxWidth = size.cx;

         }

      }

      m_iItemHeight = iMaxHeight;

      m_size.cx = iMaxWidth + rectMargin.left + rectMargin.right;

      ::count iItemCount = spitema->get_size();

      int32_t iSeparatorCount = pitem->m_iSeparatorCount;

      int x = rectMargin.left;

      string str;

      int cx = iMaxWidth;

      int cy;

      int y = rectMargin.top;

      y += m_iItemHeight;

      y += iElementPadding;

      for (int32_t i = 0; i < iItemCount; i++)
      {

         ::user::menu_item * pitem = spitema->element_at(i);

         if (pitem->m_id == "separator")
         {

            cy = rectMargin.top;

            cy += rectMargin.bottom;

         }
         else
         {

            cy = m_iItemHeight;

         }

         //pitem->m_pui = Application.create_menu_interaction();
         //
         //pitem->m_pmenu = this;
         //
         //pitem->m_pui->create_window(null_rect(), this, pitem->m_id);
         //

         prepare_menu(pitem);

         pitem->m_pui->SetWindowPos(0, x, y, cx, cy, SWP_SHOWWINDOW | SWP_NOZORDER);

         y += cy;

         y += iElementPadding;

      }

      y -= iElementPadding;

      y += rectMargin.bottom;

      m_size.cy = y;


      //m_itemClose->m_button.resize_to_fit();

      Session.userstyle()->prepare_menu(&m_itemClose);

      m_itemClose.m_pui->MoveWindow(0, 0);

      rect rectWindow;

      rectWindow.left = pt.x;
      rectWindow.top = pt.y;
      rectWindow.right = rectWindow.left + m_size.cx;
      rectWindow.bottom = rectWindow.top + m_size.cy;

      rect rectMonitor;

      if (Session.get_best_monitor(rectMonitor, rectWindow) >= 0)
      {

         rectMonitor.deflate(16, 16);

         if (rectWindow.left < rectMonitor.left)
         {

            rectWindow.offset(rectMonitor.left - rectWindow.left, 0);

         }
         else if (rectWindow.right > rectMonitor.right)
         {

            rectWindow.offset(rectMonitor.right - rectWindow.right, 0);

         }

         if (rectWindow.top < rectMonitor.top)
         {

            rectWindow.offset(0, rectMonitor.top - rectWindow.top);

         }
         else if (rectWindow.bottom > rectMonitor.bottom)
         {

            rectWindow.offset(0, rectMonitor.bottom - rectWindow.bottom);

         }

      }

      SetWindowPos(ZORDER_TOPMOST, rectWindow, SWP_FRAMECHANGED | SWP_SHOWWINDOW);

      SetTimer(::user::timer_command_probe, 100, NULL);

   }


   void menu::_001OnDraw(::draw2d::graphics * pgraphics)
   {

      COLORREF crBackground = 0;

      get_color(crBackground, ::user::color_background);

      if ((crBackground & ARGB(255, 0, 0, 0)) != 0)
      {

         rect rectClient;

         GetClientRect(rectClient);

         pgraphics->FillSolidRect(rectClient, ARGB(255, 255, 255, 255));

      }

      ::user::interaction::_001OnDraw(pgraphics);

   }




   void menu::_001OnLButtonDown(::message::message * pobj)
   {

      pobj->previous();

   }


   void menu::defer_close()
   {

      ::user::control_event ev;

      ev.m_bRet = false;

      ev.m_eevent = ::user::event_context_menu_close;

      ::user::interaction * puiTarget = get_target_window();

      if (puiTarget != NULL)
      {

         BaseOnControlEvent(&ev);

      }

      if (!m_bInline && !ev.m_bRet)
      {

         post_message(WM_CLOSE);

      }

   }


   bool menu::BaseOnControlEvent(::user::control_event * pevent)
   {

      if (pevent->m_eevent == ::user::event_button_clicked)
      {

         if (pevent->m_puie == m_itemClose.m_pui)
         {

            defer_close();

         }
         else
         {

            sp(::user::menu_item) pitem = get_item(pevent->m_puie);

            if (pitem != NULL && !pitem->m_bPopup)
            {

               if (::str::begins((const char *)pevent->m_puie->m_id, astr.stringSysCommand))
               {

                  ::user::interaction * puiTarget = get_target_window();

                  if (puiTarget != NULL)
                  {

                     ::user::command command(pevent->m_puie->m_id);

                     puiTarget->_001SendCommand(&command);

                  }

               }
               else
               {

                  ::user::interaction * puiNotify = m_puiNotify;

                  id idCommand = pevent->m_puie->m_id;

                  defer_close();

                  // this may be destroyed by WM_CLOSE above

                  if (puiNotify != NULL)
                  {

                     ::user::command command(idCommand);

                     puiNotify->_001SendCommand(&command);

                  }

                  pevent->m_bProcessed = true;

               }
            }
         }
         return true;
      }
      else if (pevent->m_eevent == ::user::event_mouse_enter)
      {

         if (pevent->m_puie != m_itemClose.m_pui)
         {

            if (!m_bInline)
            {

               if (pevent->m_puie->m_id != m_idSubMenu)
               {
                  if (m_psubmenu != NULL
                     && m_idSubMenu.has_char())
                  {
                     m_psubmenu->send_message(WM_CLOSE);
                     m_psubmenu = NULL;
                     m_idSubMenu = "";
                  }
                  /*
                   SetTimer(timer_menu, BaseWndMenuTiming, NULL);
                   if(m_pitem->m_pitema->element_at(pevent->m_pcontrol->m_uiId)->m_bPopup)
                   {
                   m_iTimerMenu = pevent->m_pcontrol->m_uiId;
                   }
                   else
                   {
                   m_iTimerMenu = -1;
                   }
                   }
                   else*/
                  {
                     sp(::user::menu_item) pitem = get_item(pevent->m_puie);

                     //sp(::user::menu_item) pitemThis = get_item();

                     //sp(::user::menu_item_ptra) spitema = pitemThis->m_spitema;

                     //sp(::user::menu_item) pitem = spitema->find(pevent->m_puie->m_id);

                     if (pitem.is_set())
                     {

                        if (pitem->m_bPopup)
                        {

                           m_idSubMenu = pevent->m_puie->m_id;

                           m_psubmenu = canew(menu(get_app(), pitem));

                           rect rect;

                           pevent->m_puie->GetWindowRect(rect);

                           m_psubmenu->hint_position(rect.top_right());

                           m_psubmenu->track_popup_menu(this, m_puiNotify);

                        }
                        else
                        {

                           ::user::control_event ev;

                           ev.m_eevent = ::user::event_menu_hover;

                           ev.m_id = pitem->m_id;

                           ::user::interaction * puiTarget = get_target_window();

                           if (puiTarget == NULL)
                           {

                              return false;

                           }

                           return puiTarget->BaseOnControlEvent(&ev);

                        }

                     }

                  }

               }

            }

         }

         return true;

      }
      else if (pevent->m_eevent == ::user::event_mouse_leave)
      {
         if (pevent->m_puie->m_id == m_idTimerMenu)
         {
            KillTimer(timer_menu);
            m_idTimerMenu.is_empty();
         }
         return true;
      }


      if (::user::control::BaseOnControlEvent(pevent))
      {

         return true;

      }

      return false;

   }


   //void menu_list_window::_001OnTimer(::timer * ptimer)
   //{

   //   ::user::menu::_001OnTimer(ptimer);

   //   if (ptimer->m_nIDEvent == ::user::timer_update_menu_::user::command)
   //   {

   //      update_::user::command(m_pitem);

   //      RedrawWindow();

   //   }

   //}


   void menu::_001OnTimer(::timer * ptimer)
   {

      ::user::control::_001OnTimer(ptimer);

      sp(::user::menu_item) pitemThis = get_item();

      if (pitemThis == NULL)
      {

         return;

      }

      sp(::user::menu_item_ptra) spitema = pitemThis->m_spitema;

      if (ptimer->m_nIDEvent == timer_menu)
      {
         KillTimer(timer_menu);
         if (m_idSubMenu.has_char())
         {
            m_psubmenu->send_message(WM_CLOSE);
            m_psubmenu = NULL;
            m_idSubMenu.is_empty();
         }

         if (m_idTimerMenu.has_char())
         {

            m_idSubMenu = m_idTimerMenu;

            m_psubmenu = canew(menu(get_app(), spitema->find(m_idTimerMenu)));

            rect rect;

            spitema->find(m_idTimerMenu)->m_pui->GetWindowRect(rect);

            m_psubmenu->hint_position(rect.top_right());

            m_psubmenu->track_popup_menu(this, m_puiNotify);
         }

         m_idTimerMenu.is_empty();

      }
      else if (ptimer->m_nIDEvent == ::user::timer_command_probe)
      {

         update_command(m_pitem);

         //if(spitema != NULL)
         //{
         //   ::user::command commandui(get_app());
         //   commandui.m_pitema          = spitema;
         //   for(int32_t i = 0; i < spitema->get_size(); i++)
         //   {
         //      
         //      commandui.m_iIndex    = i;
         //      commandui.m_id        = spitema->element_at(i)->m_id;
         //      commandui.m_pOther    = spitema->element_at(i)->m_pui;
         //      
         //      sp(::user::interaction) puiTarget = get_target_window();
         //      
         //      if(puiTarget != NULL)
         //      {
         //         /* xxx if(pwndParent->on_command(0,
         //          MAKELONG((int32_t)CN_UPDATE_::user::command, WM_COMMAND+WM_REFLECT_BASE),
         //          &commandui, NULL))
         //          continue;*/
         //         if(puiTarget->_001SendUpdateCmdUi(&commandui))
         //            continue;
         //      }
         //   }
         //}
      }


   }




   void menu::_001OnCreate(::message::message * pobj)
   {

      pobj->previous();

      UNREFERENCED_PARAMETER(pobj);

   }



   //    void menu::_001OnIdleUpdateCmdUI(::message::message * pobj)
   //    {
   //       UNREFERENCED_PARAMETER(pobj);
   //       //      SCAST_PTR(::message::base, pbase, pobj);

   //       sp(::user::menu_item) pitemThis = get_item();

   //       sp(::user::menu_item_ptra) spitema = pitemThis->m_spitema;

   //       if(spitema != NULL)
   //       {
   //          ::user::command commandui(get_app());
   //          commandui.m_pitema          = spitema;
   //          for(int32_t i = 0; i < spitema->get_size(); i++)
   //          {

   //             commandui.m_iIndex    = i;
   //             commandui.m_id        = spitema->element_at(i)->m_id;
   //             commandui.m_pOther    = spitema->element_at(i)->m_pui;

   //             sp(::user::interaction) pwndParent = m_puiNotify;
   //             if(pwndParent != NULL)
   //             {
   //                /*
   //                 if(pwndParent->on_command(0,
   //                 MAKELONG((int32_t)CN_UPDATE_::user::command, WM_COMMAND+WM_REFLECT_BASE),
   //                 &commandui, NULL))
   //                 continue;
   //                 */

   //                if(pwndParent->_001SendUpdateCmdUi(&commandui))
   //                   continue;
   //             }

   //          }
   //       }
   //    }


   void menu::_001OnEnable(::message::message * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
   }


   void menu::_001OnNcActivate(::message::message * pobj)
   {
      SCAST_PTR(::message::base, pbase, pobj);
      pbase->m_bRet = true;
      pbase->set_lresult(DefWindowProc(WM_NCACTIVATE, pbase->m_wparam, -1));
   }

   void menu::_001OnNcCalcSize(::message::message * pobj)
   {
      SCAST_PTR(::message::base, pbase, pobj);

      if (pbase->m_wparam == TRUE)
      {
         pbase->m_bRet = true;
         pbase->set_lresult(0);
      }
      else
      {
         LPRECT lprect = (LPRECT)pbase->m_lparam.m_lparam;
         lprect->left = m_ptTrack.x;
         lprect->top = m_ptTrack.y;
         lprect->right = lprect->left + m_size.cx;
         lprect->bottom = lprect->left + m_size.cx;
         pbase->m_bRet = true;
         pbase->set_lresult(0);
      }
   }

   void menu::_001OnClose(::message::message * pobj)
   {

      if (!m_bInline)
      {

         DestroyWindow();

      }

      pobj->m_bRet = true;

   }

   bool menu::pre_create_window(::user::create_struct& cs)
   {

      cs.dwExStyle = WS_EX_LAYERED | WS_EX_TOPMOST | WS_EX_TOOLWINDOW;

      cs.style &= ~WS_VISIBLE;

      return TRUE;

   }




   sp(::user::menu_item) menu::get_item()
   {

      return m_pitem;

   }


   sp(::user::menu_item) menu::get_item(::user::interaction * pui)
   {

      sp(::user::interaction) pbutton = pui;

      if (pbutton.is_null())
         return NULL;

      return pbutton->m_pmenuitem;

      //if(pbutton.)


      //sp(::user::menu_item) pitemThis = get_item();

      //sp(::user::menu_item_ptra) spitema = pitemThis->m_spitema;


      //for(auto & pitem : *spitema.m_p)
      //{
      //   
      //   if(&pitem->m_button == pbutton.m_p)
      //   {

      //      return pitem;

      //   }

      //}

      //return NULL;

   }

   bool menu::get_color(COLORREF & cr, ::user::e_color ecolor)
   {

      if (ecolor == ::user::color_background)
      {

         cr = ARGB(84 + 77, 185, 184, 177);

         return true;

      }
      else
      {

         return ::user::control::get_color(cr, ecolor);

      }

   }


   bool menu::get_translucency(::user::e_translucency & etranslucency, ::user::e_element eelement)
   {

      etranslucency = ::user::translucency_present;

      return true;

   }


   ::user::interaction * menu::get_target_window()
   {

      ::user::interaction * puiTarget = m_puiNotify;

      if (puiTarget == NULL)
      {

         return NULL;

      }

      if (dynamic_cast <::user::impact *> (puiTarget) != NULL)
      {

         puiTarget = puiTarget->GetParentFrame();

      }

      return puiTarget;

   }


   bool menu::has_pending_graphical_update()
   {

      return true;

   }



   void menu::update_command(menu_item * pitemParent)
   {

      if (m_puiNotify == NULL)
      {

         return;

      }

      if (pitemParent == NULL)
      {

         return;

      }

      if (pitemParent->m_spitema == NULL)
      {

         return;

      }

      ::user::menu_command command(get_app());

      command.m_pitema = pitemParent->m_spitema;

      command.m_iCount = pitemParent->m_spitema->get_size();

      for (command.m_iIndex = 0; command.m_iIndex < command.m_iCount; command.m_iIndex++)
      {

         menu_item * pitem = pitemParent->m_spitema->element_at(command.m_iIndex);

         command.m_id = pitem->m_id;

         command.m_puiOther = pitem->m_pui;

         m_puiNotify->on_command_probe(&command);

         pitem->m_pmenu->update_command(pitem);

      }

      set_need_redraw();

   }


} // namespace user




