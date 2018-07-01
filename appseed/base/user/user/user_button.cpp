#include "framework.h"


namespace user
{


   button::button()
   {

      user_button_construct();
      
   }


   button::button(::aura::application * papp) :
      object(papp),
      ::user::interaction(papp)
   {

      user_button_construct();

   }


   button::~button()
   {

      if (m_pmenuitem.is_set())
      {

         m_pmenuitem->m_pui = NULL;
         m_pmenuitem->m_pmenu = NULL;

      }

      ::aura::del(m_pbitmap);
      ::aura::del(m_plist);
      set_button_style(style_none);

   }

   
   void button::user_button_construct()
   {
     
      m_erectMargin = rect_button_margin;
      m_erectBorder = rect_button_border;
      m_erectPadding = rect_button_padding;
      m_eintTextAlign = int_button_draw_text_flags;
      
      
      m_estockicon = stock_icon_none;
      m_estyle = style_none;
      m_pbitmap = NULL;
      m_plist = NULL;
      m_iHover = -1;
      m_echeck = ::check::unchecked;
      m_iClick = 0;
      
   }
   

   void button::install_message_routing(::message::sender * pinterface)
   {

      ::user::control::install_message_routing(pinterface);

      IGUI_MSG_LINK(WM_CREATE, pinterface, this, &button::_001OnCreate);
      IGUI_MSG_LINK(WM_LBUTTONDOWN, pinterface, this, &button::_001OnLButtonDown);
      IGUI_MSG_LINK(WM_LBUTTONUP, pinterface, this, &button::_001OnLButtonUp);
      IGUI_MSG_LINK(WM_MBUTTONDOWN, pinterface, this, &button::_001OnMButtonDown);
      IGUI_MSG_LINK(WM_MBUTTONUP, pinterface, this, &button::_001OnMButtonUp);
      IGUI_MSG_LINK(WM_MOUSEMOVE, pinterface, this, &button::_001OnMouseMove);
      IGUI_MSG_LINK(WM_MOUSELEAVE, pinterface, this, &button::_001OnMouseLeave);
      IGUI_MSG_LINK(WM_KEYDOWN, pinterface, this, &button::_001OnKeyDown);

   }


   void button::_001OnDraw(::draw2d::graphics * pgraphics)
   {

      if (m_estyle == style_push)
      {

         _001OnButtonDrawPush(pgraphics);

      }
      else if (m_estyle == style_list)
      {

         _001OnButtonDrawList(pgraphics);

      }
      else if (m_estyle == style_bitmap)
      {

         _001OnButtonDrawBitmap(pgraphics);

      }
      else if (m_estyle == style_image_and_text)
      {

         _001OnButtonDrawImageAndText(pgraphics);

      }
      else
      {

         _001OnButtonDrawNormal(pgraphics);

      }

   }


   void button::_001OnLButtonDown(::message::message * pobj)
   {

      SCAST_PTR(::message::mouse, pmouse, pobj);

      pobj->previous();

      e_element eelement;

      if (hit_test(pmouse->m_pt, eelement) >= 0)
      {

         if (!simple_process_system_message(pobj, ::user::event_button_down))
         {

            pmouse->m_bRet = true;

         }

      }

   }


   void button::_001OnMButtonDown(::message::message * pobj)
   {

      SCAST_PTR(::message::mouse, pmouse, pobj);

      pobj->previous();

      e_element eelement;

      if (hit_test(pmouse->m_pt, eelement) >= 0)
      {

         if (!simple_process_system_message(pobj, ::user::event_m_button_down))
         {

            pmouse->m_bRet = true;

         }

      }

   }


   void button::_001OnMButtonUp(::message::message * pobj)
   {

      SCAST_PTR(::message::mouse, pmouse, pobj);

      pobj->previous();

      e_element eelement;

      if (hit_test(pmouse->m_pt, eelement) >= 0)
      {

         if (!simple_process_system_message(pobj, ::user::event_m_button_up))
         {

            pmouse->m_bRet = true;

         }

      }

   }


   bool button::is_pressed()
   {

      return Session.m_puiLastLButtonDown == this;

   }


   void button::_001OnLButtonUp(::message::message * pobj)
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

            ev.m_actioncontext.signalize(::action::source_user);

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


   void button::_001OnMouseMove(::message::message * pobj)
   {

      SCAST_PTR(::message::mouse, pmouse, pobj);

      e_element eelement;

      index iHover = hit_test(pmouse->m_pt, eelement);
      if (iHover != m_iHover)
      {
         index iOldHover = m_iHover;
         m_iHover = iHover;
         RedrawWindow();

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


   void button::_001OnMouseLeave(::message::message * pobj)
   {

      SCAST_PTR(::message::base, pbase, pobj);
      index iOldHover = m_iHover;
      m_iHover = -1;
      if (iOldHover >= 0)
      {
         RedrawWindow();
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

   index button::hit_test(point pt, e_element & eelement)
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


   ::size button::calc_text_size()
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


   void button::resize_to_fit()
   {

      if (m_estyle == style_simple)
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
      else if (m_estyle == style_bitmap)
      {

         class size size = m_pbitmap->m_dib->size();

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

   //void button::_001SetButtonText(const char * lpcszText)
   //{
   //   m_istrButtonText = lpcszText;
   //}



   void button::_001SetCheck(::check::e_check echeck, ::action::context actioncontext)
   {

      UNREFERENCED_PARAMETER(actioncontext);

      m_echeck = echeck;

   }


   ::check::e_check button::_001GetCheck()
   {

      return m_echeck;

   }


   void button::_001OnCreate(::message::message * pobj)
   {

      UNREFERENCED_PARAMETER(pobj);

      if (m_estyle == style_none)
      {

         set_button_style(style_normal);

      }


   }


   void button::on_layout()
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


   bool button::create_control(class control_descriptor * pdescriptor)
   {

      return control::create_control(pdescriptor);


   }


   void button::_002OnDraw(::draw2d::graphics * pgraphics)
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
      else if (is_pressed() || _001GetCheck() == ::check::checked)
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
      else if (is_pressed() || _001GetCheck() == ::check::checked)
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
      if (m_pbitmap->m_dib.is_set())
      {
         if (m_pbitmap->m_dib->m_size.cx > 0 && m_pbitmap->m_dib->m_size.cy > 0)
         {
            rect rectDib;
            rectDib = m_rectText;
            rectDib.bottom = MIN(rectText.top + m_pbitmap->m_dib->m_size.cy, rectText.bottom);
            rectDib.right = MIN(rectText.left + m_pbitmap->m_dib->m_size.cx, rectText.right);
            //m_dib->to(pgraphics, rectDib);
            m_pbitmap->m_dib->bitmap_blend(pgraphics, rectDib);
            rectText.left += m_pbitmap->m_dib->m_size.cx;
         }
      }


      ::draw2d::brush_sp brushText(allocer());


      pgraphics->SelectObject(brushText);

      string strText(get_window_text());

      select_font(pgraphics, font_button);

      pgraphics->draw_text(strText, rectText, DT_LEFT | DT_TOP);

   }


   bool button::keyboard_focus_is_focusable()
   {

      return is_window_enabled() && IsWindowVisible();

   }


   void button::_001OnKeyDown(::message::message * pmessage)
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


   COLORREF button::get_button_text_color()
   {

      COLORREF crText;

      if (!is_window_enabled())
      {

         crText = _001GetColor(color_button_text_disabled, ARGB(255, 0, 0, 0));

      }
      else if (is_pressed() || _001GetCheck() == ::check::checked)
      {

         crText = _001GetColor(color_button_text_press, ARGB(255, 0, 0, 0));

      }
      else if (m_iHover >= 0)
      {

         crText = _001GetColor(color_button_text_hover, ARGB(255, 0, 0, 0));

      }
      else
      {

         crText = _001GetColor(color_button_text, ARGB(255, 0, 0, 0));

      }

      return crText;

   }


   void button::_001OnButtonDrawBackground(::draw2d::graphics * pgraphics)
   {

      rect rectClient;

      GetClientRect(rectClient);

      COLORREF crBackground;

      if (!is_window_enabled())
      {

         crBackground = _001GetColor(color_button_background_disabled, ARGB(255, 180, 180, 180));

      }
      else if (is_pressed() || _001GetCheck() == ::check::checked)
      {

         crBackground = _001GetColor(color_button_background_press, ARGB(255, 240, 240, 240));

      }
      else if (m_iHover >= 0)
      {

         crBackground = _001GetColor(color_button_background_hover, ARGB(255, 240, 240, 240));

      }
      else
      {

         crBackground = _001GetColor(color_button_background, ARGB(255, 240, 240, 240));

      }

      pgraphics->set_alpha_mode(::draw2d::alpha_mode_blend);

      pgraphics->fill_solid_rect(rectClient, crBackground);

   }


   void button::_001OnButtonDrawTextLayer(::draw2d::graphics * pgraphics, LPRECT lprectText)
   {

      rect rectText(lprectText);

      if (m_estockicon == stock_icon_none)
      {

         string strText;

         get_window_text(strText);

         if (strText.has_char())
         {

            COLORREF crText = get_button_text_color();

            pgraphics->set_text_color(crText);

            int iDrawTextFlags;

            if (m_estyle == style_image_and_text)
            {

               iDrawTextFlags = _001GetInt(int_button_draw_text_and_image_flags, DT_LEFT | DT_BOTTOM | DT_SINGLELINE);

            }
            else
            {

               iDrawTextFlags = _001GetInt(m_eintTextAlign, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

            }

            pgraphics->draw_text(strText, rectText, iDrawTextFlags);

         }

      }
      else
      {

         COLORREF crText = get_button_text_color();

         pgraphics->set_text_color(crText);

         ::draw2d::pen_sp pen(allocer());

         pen->m_cr = crText;

         pen->m_dWidth = 1.0;

         pgraphics->SelectObject(pen);

         class rect rectIcon(rectText);

         rectIcon.deflate(rectIcon.width() / 4, rectIcon.height() / 4);

         pgraphics->draw_stock_icon(rectIcon, m_estockicon);

      }

   }


   void button::_001OnButtonDrawNormal(::draw2d::graphics * pgraphics)
   {

      rect rectClient;

      GetClientRect(rectClient);

      select_font(pgraphics, font_button);

      rect rectMargin = _001GetRect(m_erectMargin);

      rect rectBorder = _001GetRect(m_erectBorder);

      rectClient.deflate(rectMargin);

      rectClient.deflate(rectBorder);

      _001OnButtonDrawBackground(pgraphics);

      rect rectPadding = _001GetRect(m_erectPadding);

      rectClient.deflate(rectPadding);

      _001OnButtonDrawTextLayer(pgraphics, rectClient);

   }


   void button::_001OnButtonDrawBitmap(::draw2d::graphics * pgraphics)
   {

      select_font(pgraphics, font_button);

      _001OnButtonDrawBackground(pgraphics);

      if (!(m_pbitmap->m_dib.is_set() && m_pbitmap->m_dib->area() > 0))
      {

         return;

      }

      ASSERT(m_pbitmap->m_dib.is_set() && m_pbitmap->m_dib->area() > 0); // required

      // use the main bitmap for up, the selected bitmap for down
      ::draw2d::dib * pdib = m_pbitmap->m_dib;

      if(_001GetCheck() == ::check::checked && m_pbitmap->m_dibSel.is_set() && m_pbitmap->m_dibSel->area() > 0)
         pdib = m_pbitmap->m_dibSel;
      else if(m_iHover >= 0 && is_window_enabled() && m_pbitmap->m_dibHover.is_set() && m_pbitmap->m_dibHover->area() > 0)
         pdib = m_pbitmap->m_dibHover;
      else if(Session.get_focus_ui() == this && m_pbitmap->m_dibFocus.is_set() && m_pbitmap->m_dibFocus->area() > 0)
         pdib = m_pbitmap->m_dibFocus;   // third image for focused
      else if(!is_window_enabled() && m_pbitmap->m_dibDisabled.is_set() && m_pbitmap->m_dibDisabled->area() > 0)
         pdib = m_pbitmap->m_dibDisabled;   // last image for disabled

      rect rectClient;

      GetClientRect(rectClient);

      rect rectMargin = _001GetRect(m_erectMargin);

      rect rectBorder = _001GetRect(m_erectBorder);

      rectClient.deflate(rectMargin);

      rectClient.deflate(rectBorder);

      rect rectPadding = _001GetRect(m_erectPadding);

      rectClient.deflate(rectPadding);

      if (pdib->area() > 0 && rectClient.area() > 0)
      {

         rect rectAspect;

         rectAspect.left = 0;

         rectAspect.top = 0;

         double dW = (double) rectClient.width() / (double)pdib->m_size.cx;

         double dH = (double) rectClient.height() / (double) pdib->m_size.cy;

         double dMin = MIN(MIN(dW, dH), 1.0);

         rectAspect.right = pdib->m_size.cx * dMin;

         rectAspect.bottom = pdib->m_size.cy * dMin;

         rectAspect.Align(align_center, rectClient);

         pgraphics->SetStretchBltMode(HALFTONE);

         pgraphics->set_alpha_mode(::draw2d::alpha_mode_blend);

         pgraphics->draw(rectAspect, pdib->get_graphics(), rect(pdib->m_size));

      }

   }


   void button::_001OnButtonDrawImageAndText(::draw2d::graphics * pgraphics)
   {

      select_font(pgraphics, font_button);

      _001OnButtonDrawBackground(pgraphics);

      rect rectClient;

      GetClientRect(rectClient);

      rect rectPadded(rectClient);

      int iPadding = _001GetInt(::user::int_element_padding);

      rectPadded.deflate(iPadding, iPadding);

      if (!(m_pbitmap->m_dib.is_set() && m_pbitmap->m_dib->area() > 0))
         return;

      ASSERT(m_pbitmap->m_dib.is_set() && m_pbitmap->m_dib->area() > 0); // required

      // use the main bitmap for up, the selected bitmap for down
      ::draw2d::dib * pdib = m_pbitmap->m_dib;

      if (_001GetCheck() == ::check::checked && m_pbitmap->m_dibSel.is_set() && m_pbitmap->m_dibSel->area() > 0)
         pdib = m_pbitmap->m_dibSel;
      else if (m_iHover >= 0 && is_window_enabled() && m_pbitmap->m_dibHover.is_set() && m_pbitmap->m_dibHover->area() > 0)
         pdib = m_pbitmap->m_dibHover;
      else if (Session.get_focus_ui() == this && m_pbitmap->m_dibFocus.is_set() && m_pbitmap->m_dibFocus->area() > 0)
         pdib = m_pbitmap->m_dibFocus;   // third image for focused
      else if (!is_window_enabled() && m_pbitmap->m_dibDisabled.is_set() && m_pbitmap->m_dibDisabled->area() > 0)
         pdib = m_pbitmap->m_dibDisabled;   // last image for disabled

      rect rectAspect(rectPadded);

      if (pdib->area() > 0 && rectClient.area() > 0)
      {

         rectAspect.left = 0;

         rectAspect.top = 0;

         double dW = (double)rectPadded.width() / (double)pdib->m_size.cx;

         double dH = (double)rectPadded.height() / (double)pdib->m_size.cy;

         double dMin = MIN(MIN(dW, dH), 1.0);

         rectAspect.right = pdib->m_size.cx * dMin;

         rectAspect.bottom = pdib->m_size.cy * dMin;

         rectAspect.Align(align_bottom_left, rectPadded);

         pgraphics->SetStretchBltMode(HALFTONE);

         pgraphics->set_alpha_mode(::draw2d::alpha_mode_blend);

         pgraphics->draw(rectAspect, pdib->get_graphics(), rect(pdib->m_size));

         rectAspect.left = rectAspect.right + iPadding;
         rectAspect.right = rectPadded.right;
         rectAspect.top = rectPadded.top;
         rectAspect.bottom = rectPadded.bottom;

      }

      _001OnButtonDrawTextLayer(pgraphics, rectAspect);

   }


   void button::_001OnButtonDrawPush(::draw2d::graphics * pgraphics)
   {

      rect rectClient;

      GetClientRect(rectClient);

      color color;

      color.set_rgb(_001GetColor(::user::color_button_background));

      COLORREF cr;

      if(_001GetCheck() == ::check::checked)
      {

         color.hls_rate(0.0,- 0.2,- 0.3);

      }

      if(m_iHover >= 0)
      {

         color.hls_rate(0.0,0.2,0.0);

      }

      cr = color;

      class color colorExt1TL;
      class color colorExt2TL;
      class color colorExt1BR;
      class color colorExt2BR;

      colorExt1TL.set_rgb(cr);
      colorExt2TL.set_rgb(cr);
      colorExt1BR.set_rgb(cr);
      colorExt2BR.set_rgb(cr);

      if(_001GetCheck() == ::check::checked)
      {

         colorExt1TL.hls_rate(0.0,- 0.5,0.0);
         colorExt2TL.hls_rate(0.0,- 0.2,0.0);
         colorExt2BR.hls_rate(0.0,0.2,0.0);
         colorExt1BR.hls_rate(0.0,0.85,0.0);

      }
      else
      {

         colorExt1TL.hls_rate(0.0,0.85,0.0);
         colorExt2TL.hls_rate(0.0,0.2,0.0);
         colorExt2BR.hls_rate(0.0,- 0.2,0.0);
         colorExt1BR.hls_rate(0.0,- 0.5,0.0);

      }

      class imaging & imaging = Application.imaging();

      rect rect = rectClient;
      imaging.color_blend_3dRect(pgraphics,rect,colorExt1TL,215,colorExt1BR,215);
      rect.deflate(1,1,1,1);
      imaging.color_blend_3dRect(pgraphics,rect,colorExt1TL,210,colorExt1BR,210);
      rect.deflate(1,1,1,1);
      imaging.color_blend_3dRect(pgraphics,rect,colorExt2TL,205,colorExt2BR,205);
      rect.deflate(1,1,1,1);
      imaging.color_blend_3dRect(pgraphics,rect,colorExt2TL,200,colorExt2BR,200);
      rect.deflate(1,1,1,1);
      imaging.color_blend(pgraphics,rect.left,rect.top,rect.width(),rect.height(),cr,200);
      rect.deflate(1,1,1,1);

      int32_t x1 = rect.left;
      int32_t x2 = x1 + rect.width() / 3;

      rect.left = x1;
      rect.right = x2;
      rect.bottom = rect.top + 5;
      ::draw2d::pen_sp pen(pgraphics,1,colorExt1TL);
      pgraphics->SelectObject(pen);
      imaging.color_blend_3dRect(pgraphics,rect,colorExt1TL,220,colorExt1BR,220);


   }


   void button::set_button_style(e_style estyle)
   {

      if(m_estyle == estyle)
         return;

      on_exit_button_style(m_estyle);

      m_estyle = estyle;

      on_enter_button_style(estyle);

   }


   void button::on_enter_button_style(e_style estyle)
   {

      if(estyle == style_bitmap || estyle == style_image_and_text)
      {

         m_pbitmap = new bitmap();

      }
      else if(estyle == style_list)
      {

         m_plist = new list();

         m_plist->m_pimagelistNormal         = NULL;
         m_plist->m_pimagelistItemHover      = NULL;
         m_plist->m_pimagelistSubItemHover   = NULL;

      }
      else if(estyle == style_push)
      {

         SetTimer(16384,100,NULL);

      }


   }


   void button::on_exit_button_style(e_style estyle)
   {

      if(estyle == style_bitmap || estyle == style_image_and_text)
      {

         ::aura::del(m_pbitmap);

      }
      else if(estyle == style_list)
      {

         ::aura::del(m_plist);

      }
      else if(estyle == style_push)
      {

         KillTimer(16384);

      }

   }





   bool button::LoadBitmaps(::var var,::var varSel,::var varFocus,::var varDisabled,::var varHover)
   {

      if (m_estyle != style_bitmap &&
            m_estyle != style_image_and_text)
      {

         set_button_style(style_bitmap);

      }

      if(!var.is_empty())
      {

         m_pbitmap->m_dib.alloc(allocer());

         m_pbitmap->m_dib.load_from_file(var);

      }

      if(!varSel.is_empty())
      {

         m_pbitmap->m_dibSel.alloc(allocer());

         m_pbitmap->m_dibSel.load_from_file(varSel);

      }


      if(!varFocus.is_empty())
      {

         m_pbitmap->m_dibFocus.alloc(allocer());

         m_pbitmap->m_dibFocus.load_from_file(varFocus);

      }


      if(!varDisabled.is_empty())
      {

         m_pbitmap->m_dibDisabled.alloc(allocer());

         m_pbitmap->m_dibDisabled.load_from_file(varDisabled);

      }


      if(!varHover.is_empty())
      {

         m_pbitmap->m_dibHover.alloc(allocer());

         m_pbitmap->m_dibHover.load_from_file(varHover);

      }

      return m_pbitmap->m_dib.is_set() && m_pbitmap->m_dib->area() > 0;

   }






   void button::pre_translate_message(::message::message * pobj)
   {

      // Relay events from this button to the tool tip tool handler
      BaseToolTipRelayEvent(pobj);

      return ::user::control::pre_translate_message(pobj);

   }


   void button::BaseToolTipGetRect(LPRECT lprect)
   {
      // use window client rect as the tool rect
      GetClientRect(lprect);
   }

   int32_t button::BaseToolTipGetIndex()
   {
      // use window dialog control id as the index
      return (int32_t)GetDlgCtrlId();
   }


   void button::_001OnButtonDrawList(::draw2d::graphics * pgraphics)
   {
      rect rectClient;
      bool bItemHover;
      bool bSubItemHover;



      ::aura::draw_context * pdrawcontext = pgraphics->::core::simple_chain < ::aura::draw_context >::get_last();

      if(pdrawcontext != NULL)
      {
         rectClient     = pdrawcontext->m_rectClient;
         bItemHover     = pdrawcontext->m_bListItemHover;
         bSubItemHover  = pdrawcontext->m_bListSubItemHover;
      }
      else
      {
         if(get_form() != NULL)
            return;
         GetClientRect(rectClient);
         bItemHover     = get_hover() >= 0;
         bSubItemHover  = get_hover() >= 0;
      }

      point pt = rectClient.top_left();
      pt += size(1,1);

      if(bSubItemHover)
      {
         pgraphics->draw3d_rect(
         rectClient,
         RGB(255,255,255),
         RGB(155,155,105));

         if(m_plist->m_pimagelistSubItemHover != NULL)
         {
            m_plist->m_pimagelistSubItemHover->draw(
            pgraphics,
            m_plist->m_iImageSubItemHover,
            pt,
            0);
         }
         else if(m_plist->m_pimagelistItemHover != NULL)
         {
            m_plist->m_pimagelistItemHover->draw(
            pgraphics,
            m_plist->m_iImageItemHover,
            pt,
            0);
         }
         else if(m_plist->m_pimagelistNormal != NULL)
         {
            m_plist->m_pimagelistNormal->draw(
            pgraphics,
            m_plist->m_iImageNormal,
            pt,
            0);
         }
      }
      else if(bItemHover)
      {
         if(m_plist->m_pimagelistItemHover != NULL)
         {
            m_plist->m_pimagelistItemHover->draw(
            pgraphics,
            m_plist->m_iImageItemHover,
            pt,
            0);
         }
         else if(m_plist->m_pimagelistSubItemHover != NULL)
         {
            m_plist->m_pimagelistSubItemHover->draw(
            pgraphics,
            m_plist->m_iImageSubItemHover,
            pt,
            0);
         }
         else if(m_plist->m_pimagelistNormal != NULL)
         {
            m_plist->m_pimagelistNormal->draw(
            pgraphics,
            m_plist->m_iImageNormal,
            pt,
            0);
         }
      }
      else
      {
         if(m_plist->m_pimagelistNormal != NULL)
         {
            m_plist->m_pimagelistNormal->draw(
            pgraphics,
            m_plist->m_iImageNormal,
            pt,
            0);
         }
         else if(m_plist->m_pimagelistItemHover != NULL)
         {
            m_plist->m_pimagelistItemHover->draw(
            pgraphics,
            m_plist->m_iImageItemHover,
            pt,
            0);
         }
         else if(m_plist->m_pimagelistSubItemHover != NULL)
         {
            m_plist->m_pimagelistSubItemHover->draw(
            pgraphics,
            m_plist->m_iImageSubItemHover,
            pt,
            0);
         }
      }

   }


   void button::BaseToolTipRelayEvent(class ::message::message *)
   {
   }


   bool button::is_custom_draw()
   {

      return m_estyle == style_list;

   }


   bool button::has_action_hover()
   {

      return m_iHover >= 0;

   }

   void button::set_stock_icon(e_stock_icon eicon)
   {

      m_estockicon = eicon;

   }


   e_stock_icon button::get_stock_icon()
   {

      return m_estockicon;

   }


} // namespace user




