#include "framework.h"


namespace user
{


   still::still() :
      still(get_app())
   {

      m_eintTextAlign = int_still_draw_text_flags;
      m_erectMargin = rect_button_margin;
      m_erectBorder = rect_button_border;
      m_erectPadding = rect_button_padding;
      //set_user_schema(schema_button);

   }


   still::still(::aura::application * papp) :
      object(papp),
      ::user::interaction(papp)
   {

      m_eintTextAlign = int_still_draw_text_flags;
      m_estockicon = stock_icon_none;
      m_estyle = style_none;
      m_iHover = -1;
      m_echeck = ::check::unchecked;
      m_iClick = 0;

   }

   still::~still()
   {

      if (m_pmenuitem.is_set())
      {

         m_pmenuitem->m_pui = NULL;
         m_pmenuitem->m_pmenu = NULL;

      }

   }


   void still::install_message_routing(::message::sender * pinterface)
   {

      ::user::control::install_message_routing(pinterface);

      IGUI_MSG_LINK(WM_CREATE, pinterface, this, &still::_001OnCreate);
      IGUI_MSG_LINK(WM_LBUTTONDOWN, pinterface, this, &still::_001OnLButtonDown);
      IGUI_MSG_LINK(WM_LBUTTONUP, pinterface, this, &still::_001OnLButtonUp);
      IGUI_MSG_LINK(WM_MBUTTONDOWN, pinterface, this, &still::_001OnMButtonDown);
      IGUI_MSG_LINK(WM_MBUTTONUP, pinterface, this, &still::_001OnMButtonUp);
      IGUI_MSG_LINK(WM_MOUSEMOVE, pinterface, this, &still::_001OnMouseMove);
      IGUI_MSG_LINK(WM_MOUSELEAVE, pinterface, this, &still::_001OnMouseLeave);
      IGUI_MSG_LINK(WM_KEYDOWN, pinterface, this, &still::_001OnKeyDown);

   }






   void still::_001OnDraw(::draw2d::graphics * pgraphics)
   {

      if (m_estyle == style_image)
      {

         _001OnDrawImage(pgraphics);

      }
      else
      {

         string strText;

         get_window_text(strText);

         rect rectClient;
         GetClientRect(rectClient);

         rect rectMargin = _001GetRect(m_erectMargin);

         rect rectBorder = _001GetRect(m_erectBorder);

         rectClient.deflate(rectMargin);

         rectClient.deflate(rectBorder);

         //if(m_puserstyle == NULL)
         //{

         //   if(m_iHover == 0 || Session.m_puiLastLButtonDown == this)
         //   {

         //      pgraphics->fill_solid_rect(rectClient,ARGB(255,127,127,127));

         //      pgraphics->set_text_color(ARGB(255,0,100,255));

         //   }
         //   else
         //   {

         //      pgraphics->fill_solid_rect(rectClient,ARGB(255,127,127,127));

         //      pgraphics->set_text_color(ARGB(255,0,0,0));

         //   }

         //}
         //else
         {
            if (!is_window_enabled())
            {

               pgraphics->fill_solid_rect(rectClient, _001GetColor(color_background_disabled));

               pgraphics->set_text_color(_001GetColor(color_text_disabled, ARGB(255, 160, 160, 160)));

            }
            else if (should_hover() && (m_iHover == 0 || Session.m_puiLastLButtonDown == this))
            {

               pgraphics->fill_solid_rect(rectClient, _001GetColor(color_background_hover));

               pgraphics->set_text_color(_001GetColor(color_text_hover));

            }
            else
            {

               //pgraphics->draw3d_rect(rectClient,m_puserstyle->_001GetColor(color_border),m_puserstyle->_001GetColor(color_border));

               //rectClient.deflate(1,1);

               pgraphics->fill_solid_rect(rectClient, _001GetColor(color_background));

               pgraphics->set_text_color(_001GetColor(color_text));

            }

         }

         rect rectPadding = _001GetRect(m_erectPadding);

         rectClient.deflate(rectPadding);

         if (m_estockicon == stock_icon_none)
         {

            int iDrawTextFlags = _001GetInt(m_eintTextAlign, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

            select_font(pgraphics, font_default);

            pgraphics->draw_text(strText, rectClient, iDrawTextFlags);

         }
         else
         {

            //::draw2d::brush_sp brush(allocer());

            //brush->create_solid(pgraphics->get_current_pen()->m_cr);

            //pgraphics->SelectObject(brush);

            ::draw2d::pen_sp pen(allocer());

            pen->m_cr = pgraphics->get_current_brush()->m_cr;

            pen->m_dWidth = 1.0;

            pgraphics->SelectObject(pen);

            class rect rectIcon(rectClient);

            rectIcon.deflate(rectIcon.width() / 4, rectIcon.height() / 4);

            pgraphics->draw_stock_icon(rectIcon, m_estockicon);


         }

      }

   }


   void still::_001OnLButtonDown(::message::message * pobj)
   {

      SCAST_PTR(::message::mouse, pmouse, pobj);

      pobj->previous();

      e_element eelement;

      if (hit_test(pmouse->m_pt, eelement) >= 0)
      {

         if (!simple_process_system_message(pobj, ::user::event_button_down))
         {

            Session.m_puiLastLButtonDown = this;

            pmouse->m_bRet = true;

         }

      }

   }


   void still::_001OnMButtonDown(::message::message * pobj)
   {

      SCAST_PTR(::message::mouse, pmouse, pobj);

      pobj->previous();

      e_element eelement;

      if (hit_test(pmouse->m_pt, eelement) >= 0)
      {

         if (!simple_process_system_message(pobj, ::user::event_m_button_down))
         {

            //Session.m_puiLastLButtonDown = this;

            pmouse->m_bRet = true;

         }

      }

   }


   void still::_001OnMButtonUp(::message::message * pobj)
   {

      SCAST_PTR(::message::mouse, pmouse, pobj);

      pobj->previous();

      e_element eelement;

      if (hit_test(pmouse->m_pt, eelement) >= 0)
      {

         if (!simple_process_system_message(pobj, ::user::event_m_button_up))
         {

            //Session.m_puiLastLButtonDown = this;

            pmouse->m_bRet = true;

         }



      }

   }

   bool still::is_pressed()
   {
      return Session.m_puiLastLButtonDown == this;
   }

   void still::_001OnLButtonUp(::message::message * pobj)
   {

      SCAST_PTR(::message::mouse, pmouse, pobj);

      e_element eelement;

      point pt = pmouse->m_pt;

      ScreenToClient(&pt);

      if (hit_test(pmouse->m_pt, eelement) >= 0 && Session.m_puiLastLButtonDown == this)
      {

         Session.m_puiLastLButtonDown = NULL;

         pobj->m_bRet = _001OnClick(pmouse->m_nFlags, pt);

         if (pobj->m_bRet)
         {

            pmouse->set_lresult(1);

         }
         else
         {

            ::user::control_event ev;

            ev.m_puie = this;

            ev.m_eevent = ::user::event_button_clicked;

            on_control_event(&ev);

            pobj->m_bRet = ev.m_bRet;

            if (!pobj->m_bRet)
            {

               ::user::command command;

               command.m_id = m_id;

               command.m_puiOther = this;

               route_command_message(&command);

               pobj->m_bRet = command.m_bRet;

            }

            if (pobj->m_bRet)
            {

               pmouse->set_lresult(1);

            }

         }

      }

   }


   void still::_001OnMouseMove(::message::message * pobj)
   {

      SCAST_PTR(::message::mouse, pmouse, pobj);

      e_element eelement;

      index iHover = hit_test(pmouse->m_pt, eelement);
      if (iHover != m_iHover)
      {
         index iOldHover = m_iHover;
         m_iHover = iHover;
         set_need_redraw();

         if (iHover >= 0)
         {

            track_mouse_hover();

         }


         if (iOldHover == -1)
         {
            ::user::control_event ev;
            ev.m_puie = this;
            ev.m_eevent = ::user::event_mouse_enter;
            GetParent()->send_message(
            ::message::message_event, 0, (LPARAM)&ev);
            //               m_bActionHover = true;
         }
         else if (iHover == -1)
         {
            ::user::control_event ev;
            ev.m_puie = this;
            ev.m_eevent = ::user::event_mouse_leave;
            GetParent()->send_message(
            ::message::message_event, 0, (LPARAM)&ev);
            //             m_bActionHover = false;
         }
      }
      pobj->m_bRet = false;

   }


   void still::_001OnMouseLeave(::message::message * pobj)
   {

      SCAST_PTR(::message::base, pbase, pobj);
      index iOldHover = m_iHover;
      m_iHover = -1;
      if (iOldHover >= 0)
      {
         set_need_redraw();
         ::user::control_event ev;
         ev.m_puie = this;
         ev.m_eevent = ::user::event_mouse_leave;
         if (GetParent() != NULL)
         {
            GetParent()->send_message(::message::message_event, 0, (LPARAM)&ev);
         }
      }

      pbase->m_bRet = false;

   }

   index still::hit_test(point pt, e_element & eelement)
   {
      rect rectWindow;
      GetWindowRect(rectWindow);
      if (rectWindow.contains(pt))
      {
         eelement = element_area;
         return 0;
      }
      else
      {
         eelement = element_none;
         return -1;
      }
   }


   ::size still::calc_text_size()
   {

      ::draw2d::memory_graphics pgraphics(allocer());

      if (pgraphics.is_null())
         return size(0, 0);

      select_font(pgraphics, font_button);

      string strText(m_strWindowText);

      size size = pgraphics->GetTextExtent(strText);

      ::draw2d::text_metric tm;

      pgraphics->get_text_metrics(&tm);

      ::size sizeTotal;

      sizeTotal.cx = size.cx;

      sizeTotal.cy = tm.tmHeight;

      return sizeTotal;

   }


   void still::resize_to_fit()
   {

      if (m_estyle == style_text)
      {

         ::draw2d::memory_graphics pgraphics(allocer());

         select_font(pgraphics, font_button);

         string str;
         get_window_text(str);
         size size = pgraphics->GetTextExtent(str);

         rect rect(0, 0, 0, 0);
         rect.right = LONG(size.cx * 1.6);
         rect.bottom = LONG(size.cy * 1.4);

         SetWindowPos(0, 0, 0, rect.width(), rect.height(), SWP_NOMOVE);


      }
      else if (m_estyle == style_image)
      {

         class size size = m_dib->size();

         SetWindowPos(0, 0, 0, size.cx, size.cy, SWP_NOMOVE | SWP_NOZORDER);

      }
      else
      {

         ::size sizeTotal = calc_text_size();

         sizeTotal.cx = (LONG)(sizeTotal.cx * 1.6);

         sizeTotal.cy = (LONG)(sizeTotal.cy * 1.4);

         SetWindowPos(0, 0, 0, sizeTotal.cx, sizeTotal.cy, SWP_NOMOVE);

      }

   }

   //void still::_001SetButtonText(const char * lpcszText)
   //{
   //   m_istrButtonText = lpcszText;
   //}



   void still::_001SetCheck(::check::e_check echeck, ::action::context actioncontext)
   {

      UNREFERENCED_PARAMETER(actioncontext);

      m_echeck = echeck;

   }


   ::check::e_check still::_001GetCheck()
   {

      return m_echeck;

   }


   void still::_001OnCreate(::message::message * pobj)
   {

      UNREFERENCED_PARAMETER(pobj);

      if (m_estyle == style_none)
      {

         set_button_style(style_text);

      }


   }


   void still::on_layout()
   {

      rect rectClient;

      GetClientRect(rectClient);


      ::size sizeText = calc_text_size();

      ::rect rect;

      rect.left = rectClient.left + (rectClient.width() - sizeText.cx) / 2;

      rect.top = rectClient.top + (rectClient.height() - sizeText.cy) / 2;

      rect.right = rect.left + sizeText.cx;

      rect.bottom = rect.top + sizeText.cy;

      m_rectText = rect;

   }


   bool still::create_control(class control_descriptor * pdescriptor)
   {

      return control::create_control(pdescriptor);


   }


   void still::_002OnDraw(::draw2d::graphics * pgraphics)
   {

      //if(m_puserstyle == NULL)
      //   return;



      rect rectClient;

      GetClientRect(rectClient);

      COLORREF crBk;
      if (!is_window_enabled())
      {
         crBk = _001GetColor(color_button_background_disabled);
      }
      else if (is_pressed())
      {
         crBk = _001GetColor(color_button_background_press);
      }
      else if (m_iHover >= 0)
      {
         crBk = _001GetColor(color_button_background_hover);
      }
      else
      {
         crBk = _001GetColor(color_button_background);
      }


      if (_001IsTranslucent())
      {
         class imaging & imaging = Application.imaging();
         imaging.color_blend(
         pgraphics,
         rectClient,
         crBk,
         127);
      }
      else
      {
         pgraphics->fill_solid_rect(rectClient, crBk);
      }


      COLORREF crBorder;
      if (!is_window_enabled())
      {
         crBorder = ARGB(255, 127, 127, 127);
      }
      else if (is_pressed())
      {
         crBorder = ARGB(255, 255, 255, 255);
      }
      else if (m_iHover >= 0)
      {
         crBorder = ARGB(255, 100, 100, 200);
      }
      else
      {
         crBorder = ARGB(255, 10, 10, 100);
      }

      if (_001GetFlag(flag_border))
      {

         pgraphics->draw3d_rect(rectClient, crBorder, crBorder);

      }

      //      pgraphics->SetBkMode(TRANSPARENT);

      rectClient.left += 3;
      rectClient.top += 3;
      rect rectText = m_rectText;
      //      string str = ::str::international::utf8_to_unicode(str);
      if (m_dib.is_set())
      {
         if (m_dib->m_size.cx > 0 && m_dib->m_size.cy > 0)
         {
            rect rectDib;
            rectDib = m_rectText;
            rectDib.bottom = MIN(rectText.top + m_dib->m_size.cy, rectText.bottom);
            rectDib.right = MIN(rectText.left + m_dib->m_size.cx, rectText.right);
            //m_dib->to(pgraphics, rectDib);
            m_dib->bitmap_blend(pgraphics, rectDib);
            rectText.left += m_dib->m_size.cx;
         }
      }


      ::draw2d::brush_sp brushText(allocer());


      if (!is_window_enabled())
      {
         //         pgraphics->set_text_color(m_puserstyle->m_crTextDisabled);
         brushText->create_solid(_001GetColor(color_button_text_disabled));
      }
      else if (is_pressed())
      {
         //         pgraphics->set_text_color(m_puserstyle->m_crTextPress);
         brushText->create_solid(_001GetColor(color_button_text_press));
      }
      else if (m_iHover >= 0)
      {
         //         pgraphics->set_text_color(m_puserstyle->m_crTextHover);
         brushText->create_solid(_001GetColor(color_button_text_hover));
      }
      else
      {
         //         pgraphics->set_text_color(m_puserstyle->m_crTextNormal);
         brushText->create_solid(_001GetColor(color_button_text));
      }

      pgraphics->SelectObject(brushText);

      string strText(get_window_text());

      select_font(pgraphics, font_button);

      pgraphics->draw_text(strText, rectText, DT_LEFT | DT_TOP);

   }


   bool still::keyboard_focus_is_focusable()
   {

      //return is_window_enabled() && IsWindowVisible();
      return false;

   }


   void still::_001OnKeyDown(::message::message * pmessage)
   {

      SCAST_PTR(::message::key, pkey, pmessage);

      ::user::e_key iKey = pkey->m_ekey;

      if (iKey == ::user::key_return || iKey == ::user::key_space)
      {

         ::user::control_event ev;
         ev.m_puie = this;
         ev.m_eevent = ::user::event_button_clicked;
         ev.m_pmessage = pmessage;
         on_control_event(&ev);
         pmessage->m_bRet = ev.m_bRet;
         if (pmessage->m_bRet)
         {
            pkey->set_lresult(1);
         }

      }

   }


   void still::_001OnDrawImage(::draw2d::graphics * pgraphics)
   {

      string strText;

      get_window_text(strText);

      rect rectClient;
      GetClientRect(rectClient);


      //if (m_puserstyle == NULL)
      //{

      //   if (m_iHover == 0 || Session.m_puiLastLButtonDown == this)
      //   {

      //      pgraphics->fill_solid_rect(rectClient, ARGB(255, 127, 127, 127));

      //   }
      //   else
      //   {

      //      pgraphics->fill_solid_rect(rectClient, ARGB(255, 127, 127, 127));

      //   }

      //}
      //else
      {
         if (!is_window_enabled())
         {

            pgraphics->fill_solid_rect(rectClient, _001GetColor(color_button_background_disabled));

         }
         else if (m_iHover == 0 || Session.m_puiLastLButtonDown == this)
         {

            //pgraphics->draw3d_rect(rectClient,m_puserstyle->_001GetColor(color_border_hover),m_puserstyle->_001GetColor(color_border_hover));

            //rectClient.deflate(1,1);

            pgraphics->fill_solid_rect(rectClient, _001GetColor(color_button_background_hover));

         }
         else
         {

            pgraphics->fill_solid_rect(rectClient, _001GetColor(color_button_background));

         }

      }


      if (!(m_dib.is_set() && m_dib->area() > 0))
         return;

      ASSERT(m_dib.is_set() && m_dib->area() > 0); // required

      // use the main bitmap for up, the selected bitmap for down
      ::draw2d::dib * pdib = m_dib;

      if (pdib->area() > 0 && rectClient.area() > 0)
      {

         rect rectAspect;

         rectAspect.left = 0;

         rectAspect.top = 0;

         double dW = (double)rectClient.width() / (double)pdib->m_size.cx;

         double dH = (double)rectClient.height() / (double)pdib->m_size.cy;

         double dMin = MAX(MIN(dW, dH), 1.0);

         rectAspect.right = pdib->m_size.cx * dMin;

         rectAspect.bottom = pdib->m_size.cy * dMin;

         rectAspect.Align(align_center, rectClient);

         pgraphics->draw(rectClient, pdib->get_graphics(), rect(pdib->m_size));

      }

   }


   void still::set_button_style(e_style estyle)
   {

      if (m_estyle == estyle)
         return;

      on_exit_button_style(m_estyle);

      m_estyle = estyle;

      on_enter_button_style(estyle);

   }


   void still::on_enter_button_style(e_style estyle)
   {



   }


   void still::on_exit_button_style(e_style estyle)
   {

   }





   bool still::LoadBitmaps(::var var, ::var varSel, ::var varFocus, ::var varDisabled, ::var varHover)
   {

      set_button_style(style_image);

      if (!var.is_empty())
      {

         m_dib.alloc(allocer());

         m_dib.load_from_file(var);

      }

      //if (!varSel.is_empty())
      //{

      //   m_pbitmap->m_dibSel.alloc(allocer());

      //   m_pbitmap->m_dibSel.load_from_file(varSel);

      //}


      //if (!varFocus.is_empty())
      //{

      //   m_pbitmap->m_dibFocus.alloc(allocer());

      //   m_pbitmap->m_dibFocus.load_from_file(varFocus);

      //}


      //if (!varDisabled.is_empty())
      //{

      //   m_pbitmap->m_dibDisabled.alloc(allocer());

      //   m_pbitmap->m_dibDisabled.load_from_file(varDisabled);

      //}


      //if (!varHover.is_empty())
      //{

      //   m_pbitmap->m_dibHover.alloc(allocer());

      //   m_pbitmap->m_dibHover.load_from_file(varHover);

      //}

      return m_dib.is_set() && m_dib->area() > 0;

   }






   void still::pre_translate_message(::message::message * pobj)
   {

      // Relay events from this still to the tool tip tool handler
      BaseToolTipRelayEvent(pobj);

      return ::user::control::pre_translate_message(pobj);

   }


   void still::BaseToolTipGetRect(LPRECT lprect)
   {
      // use window client rect as the tool rect
      GetClientRect(lprect);
   }

   int32_t still::BaseToolTipGetIndex()
   {
      // use window dialog control id as the index
      return (int32_t)GetDlgCtrlId();
   }



   void still::BaseToolTipRelayEvent(class ::message::message *)
   {

   }


   bool still::has_action_hover()
   {

      return m_iHover >= 0;

   }


   void still::set_stock_icon(e_stock_icon eicon)
   {

      m_estockicon = eicon;

   }


   e_stock_icon still::get_stock_icon()
   {

      return m_estockicon;

   }


   bool still::should_hover()
   {

      return has_link();

   }


   bool still::has_link()
   {

      return m_strLink.has_char();

   }


} // namespace user




