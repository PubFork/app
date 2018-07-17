#include "framework.h" // from "base/user/user.h"


namespace user
{


   style::style()
   {

      m_puserstyle = this;
      m_pgraphics = NULL;

      default_style_construct();

   }


   style::style(::aura::application * papp) :
      ::object(papp)
   {

      m_puserstyle = this;
      m_pgraphics = NULL;

      default_style_construct();

   }

   void style::default_style_construct()
   {

   }

   style::~style()
   {

   }


   //void style::select_default()
   //{

   //   if (m_puserstyle.is_set())
   //   {

   //      m_puserstyleSelect = m_puserstyle;

   //   }
   //   else
   //   {

   //      m_puserstyleSelect = this;

   //   }

   //}








   //void style::initialize_style()
   //{

   //   ::user::style::initialize_style();

   //   color color;
   //   color.set_rgb(Session.get_default_color(COLOR_HIGHLIGHT));

   //   class color colorHover(color);
   //   colorHover.hls_rate(0.0, 0.3, 0.0);

   //   class color colorPress(color);
   //   colorPress.hls_rate(0.0, 0.7, 0.0);

   //   m_eschema = schema_default;

   //   create_opaque_color(color_text, ::color_black);

   //}


   bool style::_001OnDrawMainFrameBackground(::draw2d::graphics * pgraphics, ::user::frame * pframe)
   {

      return false;

   }


   bool style::draw_check(::check::e_check echeck, LPCRECT lpcrect, ::draw2d::graphics * pgraphics)
   {

      if (echeck == ::check::tristate || echeck == ::check::checked)
      {

         int w = ::width(lpcrect);

         int h = ::height(lpcrect);

         ::draw2d::pen_sp pen(allocer());

         pen->create_solid(1 * (w + h) / 30, echeck == ::check::checked ? ARGB(255, 0, 0, 0) : ARGB(255, 96, 96, 96));

         pgraphics->SelectObject(pen);

         pgraphics->move_to(2 * w / 15, 8 * h / 15);
         pgraphics->line_to(6 * w / 15, 12 * h / 15);
         pgraphics->line_to(13 * w / 15, 5 * h / 15);
         pgraphics->move_to(2 * w / 15, 9 * h / 15);
         pgraphics->line_to(6 * w / 15, 13 * h / 15);
         pgraphics->line_to(13 * w / 15, 6 * h / 15);

      }

      return true;

   }


   bool style::select_text_color(::user::interaction * pui, ::draw2d::graphics * pgraphics, e_color ecolor)
   {

      COLORREF cr;

      style_context style(pui);

      if (!get_color(cr, ecolor, &style))
      {

         return false;

      }

      pgraphics->set_text_color(cr);

      return true;

   }


   bool style::select_solid_brush(::user::interaction * pui, ::draw2d::graphics * pgraphics, e_color ecolor)
   {

      COLORREF cr;

      style_context style(pui);

      if (!get_color(cr, ecolor, &style))
      {

         return false;

      }

      ::draw2d::brush_sp brush(allocer());

      brush->create_solid(cr);

      pgraphics->SelectObject(brush);

      return true;

   }


   bool style::select_font(::user::interaction * pui, ::draw2d::graphics * pgraphics, e_font efont)
   {

      ::draw2d::font_sp font;

      style_context style(pui);

      if (!get_font(font, efont, &style))
      {

         return false;

      }

      if (is_set(pgraphics))
      {

         pgraphics->select_font(font);

      }

      return true;

   }


   bool style::select_text_color(::user::interaction * pui, e_color ecolor)
   {

      ::draw2d::graphics * pgraphics = style_get_graphics();

      if (pgraphics == NULL)
      {

         return false;

      }

      return select_text_color(pui, pgraphics, ecolor);

   }


   bool style::select_solid_brush(::user::interaction * pui, e_color ecolor)
   {

      ::draw2d::graphics * pgraphics = style_get_graphics();

      if (pgraphics == NULL)
      {

         return false;

      }

      return select_solid_brush(pui, pgraphics, ecolor);

   }


   bool style::select_font(::user::interaction * pui, e_font efont)
   {

      ::draw2d::graphics * pgraphics = style_get_graphics();

      if (pgraphics == NULL)
      {

         return false;

      }

      return select_font(pui, pgraphics, efont);

   }



   COLORREF style::_001GetColor(e_color ecolor, COLORREF crDefault)
   {

      COLORREF cr;

      style_context style(this);

      if (get_color(cr, ecolor, &style))
      {

         return cr;

      }

      return crDefault;

   }


   ::draw2d::font_sp style::_001GetFont(e_font efont, ::draw2d::font * pfontDefault)
   {

      ::draw2d::font_sp font;

      style_context style(this);

      if (get_font(font, efont, &style))
      {

         return font;

      }

      return pfontDefault;

   }


   e_translucency style::_001GetTranslucency(e_element eelement, e_translucency etranslucencyDefault)
   {

      e_translucency etranslucency = translucency_undefined;

      style_context style(this);

      if (get_translucency(etranslucency, eelement, &style))
      {

         if (etranslucency != translucency_undefined)
         {

            return etranslucency;

         }

      }

      return etranslucencyDefault;

   }


   bool style::_001GetFlag(e_flag eflag, bool bDefault)
   {

      bool bSet = bDefault;

      style_context style(this);

      if (get_flag(bSet, eflag, &style))
      {

         return bSet;

      }

      return bDefault;

   }


   RECT style::_001GetRect(e_rect erect, rect rectDefault)
   {

      ::rect rect(rectDefault);

      style_context style(this);

      style_rect stylerect;

      if (get_rect(stylerect, erect, &style))
      {

         stylerect.get_rect(rect, style.m_pstyleSource->m_pgraphics);

         return rect;

      }

      return rectDefault;

   }


   int style::_001GetInt(e_int eint, int iDefault)
   {

      int i = iDefault;

      style_context style(this);

      if (get_int(i, eint, &style))
      {

         return i;

      }

      return iDefault;

   }


   double style::_001GetDouble(e_double edouble, double dDefault)
   {

      double d = dDefault;

      style_context style(this);

      if (get_double(d, edouble, &style))
      {

         return d;

      }

      return dDefault;

   }


   bool style::_001IsTranslucent(e_element eelement)
   {

      e_translucency etranslucency = _001GetTranslucency(eelement);

      return etranslucency == translucency_present || etranslucency == translucency_total;

   }


   bool style::_001IsBackgroundBypass(e_element eelement)
   {

      return _001GetTranslucency(eelement) == translucency_total;

   }


   bool style::_001HasTranslucency(e_element eelement)
   {

      e_translucency etranslucency = _001GetTranslucency(eelement);

      return etranslucency == translucency_present || etranslucency == translucency_total;

   }


   bool style::_001IsTransparent(e_element eelement)
   {

      return _001GetTranslucency(eelement) == translucency_total;

   }


   bool style::get_color(COLORREF & cr, e_color ecolor, style_context * pcontext)
   {

      if (userstyle()->m_mapColor.is_set() && userstyle()->m_mapColor->Lookup(ecolor, cr))
      {

         return true;

      }

      userstyle()->nextstyle(pcontext);

      if(pcontext->m_pstyle.is_null())
      {

         return false;

      }

      return pcontext->m_pstyle->get_color(cr, ecolor, pcontext);

   }


   bool style::get_font(::draw2d::font_sp & font, e_font efont, style_context * pcontext)
   {

      if (userstyle()->m_mapFont.is_set() && userstyle()->m_mapFont->Lookup(efont, font))
      {

         return true;

      }

      userstyle()->nextstyle(pcontext);

      if (pcontext->m_pstyle.is_null())
      {

         if (efont == font_default)
         {

            return false;

         }

         (*pcontext) = pcontext->m_pstyleSource;

         return pcontext->m_pstyle->get_font(font, font_default, pcontext);

      }

      return pcontext->m_pstyle->get_font(font, efont, pcontext);

   }


   bool style::get_translucency(e_translucency & etranslucency, e_element eelement, style_context * pcontext)
   {

      if (userstyle()->m_mapTranslucency.is_set())
      {

         if (userstyle()->m_mapTranslucency->Lookup(eelement, etranslucency)
               && etranslucency != translucency_undefined)
         {

            return true;

         }
         else if (
         eelement != element_none
         && userstyle()->m_mapTranslucency->Lookup(element_none, etranslucency)
         && etranslucency != translucency_undefined)
         {

            return true;

         }

      }

      userstyle()->nextstyle(pcontext);

      if (pcontext->m_pstyle.is_null())
      {

         return false;

      }

      return pcontext->m_pstyle->get_translucency(etranslucency, eelement, pcontext);

   }


   bool style::get_flag(bool & bSet, e_flag eflag, style_context * pcontext)
   {

      if (userstyle()->m_mapFlag.is_set() && userstyle()->m_mapFlag->Lookup(eflag, bSet))
      {

         return true;

      }

      userstyle()->nextstyle(pcontext);

      if (pcontext->m_pstyle.is_null())
      {

         return false;

      }

      return pcontext->m_pstyle->get_flag(bSet, eflag, pcontext);

   }


   bool style::get_rect(style_rect & rect, e_rect erect, style_context * pcontext)
   {

      if (userstyle()->m_mapRect.is_set() && userstyle()->m_mapRect->Lookup(erect, (style_rect &) rect))
      {

         return true;

      }

      userstyle()->nextstyle(pcontext);

      if (pcontext->m_pstyle.is_null())
      {

         return false;

      }

      return pcontext->m_pstyle->get_rect(rect, erect, pcontext);

   }


   bool style::get_int(int & i, e_int eint, style_context * pcontext)
   {

      if (userstyle()->m_mapInt.is_set() && userstyle()->m_mapInt->Lookup(eint, i))
      {

         return true;

      }

      userstyle()->nextstyle(pcontext);

      if (pcontext->m_pstyle.is_null())
      {

         return false;

      }

      return pcontext->m_pstyle->get_int(i, eint, pcontext);

   }


   bool style::get_double(double & d, e_double edouble, style_context * pcontext)
   {

      if (userstyle()->m_mapDouble.is_set() && userstyle()->m_mapDouble->Lookup(edouble, d))
      {

         return true;

      }

      userstyle()->nextstyle(pcontext);

      if (pcontext->m_pstyle.is_null())
      {

         return false;

      }

      return pcontext->m_pstyle->get_double(d, edouble, pcontext);

   }


   bool style::on_ui_event(e_event eevent, e_object eobject, ::user::interaction * pui)
   {

      return false;

   }






   bool style::set_translucent()
   {


      create_translucency(element_none, translucency_present);

      return true;

   }


   bool style::simple_ui_draw_focus_rect(::user::interaction * pui, ::draw2d::graphics * pgraphics)
   {

      bool bError = pui->m_ptooltip.is_set()
                    && pui->m_ptooltip->IsWindowVisible()
                    && pui->get_tooltip()->m_bError;

      ::draw2d::savedc savedc(pgraphics);

      ::draw2d::matrix mRot;

      mRot.append(::draw2d::matrix::rotation(pui->get_rotate()));

      pgraphics->prepend(mRot);

      ::draw2d::matrix mTrans;

      rect rectWindow;

      pui->GetWindowRect(rectWindow);

      point ptCenter;

      if (pui->GetParent() != NULL)
      {

         pui->GetParent()->ScreenToClient(rectWindow);

      }

      ptCenter = rectWindow.center();

      point ptOffset = ptCenter - rectWindow.top_left();

      mTrans.append(::draw2d::matrix::translation(ptOffset.x, ptOffset.y));

      pgraphics->append(mTrans);

      rect rectClient;

      pui->::user::interaction::GetClientRect(rectClient);

      rectClient -= ptOffset;

      pgraphics->set_alpha_mode(::draw2d::alpha_mode_blend);

      int32_t iStyle = 1;

      rectClient.left--;
      rectClient.top--;

      if (m_pauraapp != NULL && (Session.get_keyboard_focus() == pui || pui->has_action_hover()))
      {

         ::draw2d::brush_sp brush(allocer());

         if (pui->has_action_hover() && !pui->has_text_input())
         {

            brush->create_solid(_001GetColor(::user::color_background_hover));

            pgraphics->SelectObject(brush);

            pgraphics->fill_rect(rectClient);

         }

         if (iStyle == 1)
         {

            bool bHover = pui->has_action_hover();

            if (pui->has_action_hover())
            {

               ::draw2d::pen_sp pen(pgraphics, 1.0, pui->get_action_hover_border_color());

               pgraphics->draw_rect(rectClient, pen);

            }
            else
            {

               //::draw2d::pen_sp pen(pgraphics, 1.0, ARGB(255, 108, 149, 255));
               ::draw2d::pen_sp pen(pgraphics, 1.0, ARGB(184, 84, 90, 80));

               pgraphics->draw_rect(rectClient, pen);

            }


            if (Session.get_keyboard_focus() == pui)
            {

               rectClient.left--;
               rectClient.right++;
               rectClient.top--;
               rectClient.bottom++;

               {

                  //::draw2d::pen_sp pen(pgraphics, 1.0, ARGB(255, 108, 149, 255));
                  ::draw2d::pen_sp pen(pgraphics, 1.0, bError ? ARGB(195, 255, 130, 120) : bHover ? ARGB(220, 120, 190, 255) : ARGB(220, 150, 190, 235));

                  pgraphics->draw_rect(rectClient, pen);

               }

               rectClient.left--;
               rectClient.right++;
               rectClient.top--;
               rectClient.bottom++;

               {

                  ::draw2d::pen_sp pen(pgraphics, 1.0, bError ? ARGB(155, 255, 150, 140) : bHover ? ARGB(200, 140, 200, 255) : ARGB(200, 150, 210, 235));

                  pgraphics->SelectObject(pen);

                  pgraphics->draw_rect(rectClient, pen);

               }

               rectClient.left--;
               rectClient.right++;
               rectClient.top--;
               rectClient.bottom++;

               {

                  ::draw2d::path_sp pathRound(allocer());

                  pathRound->begin_figure(true, ::draw2d::fill_mode_winding);

                  pathRound->add_round_rect(rectClient, 1 * 2);

                  pathRound->end_figure(true);

                  //::draw2d::pen_sp pen(pgraphics, 1.0, ARGB(72, 108, 149, 255));
                  ::draw2d::pen_sp pen(pgraphics, 1.0, bError ? ARGB(135, 255, 170, 160) : bHover ? ARGB(160, 160, 210, 255) : ARGB(160, 180, 220, 255));

                  pgraphics->SelectObject(pen);

                  pgraphics->draw_rect(rectClient, pen);

               }

               rectClient.left--;
               rectClient.right++;
               rectClient.top--;
               rectClient.bottom++;

               {

                  ::draw2d::path_sp pathRound(allocer());

                  pathRound->begin_figure(true, ::draw2d::fill_mode_winding);

                  pathRound->add_round_rect(rectClient, 1 * 2);

                  pathRound->end_figure(true);

                  //::draw2d::pen_sp pen(pgraphics, 1.0, ARGB(60, 108, 149, 255));
                  ::draw2d::pen_sp pen(pgraphics, 1.0, bError ? ARGB(105, 255, 190, 180) : bHover ? ARGB(120, 180, 220, 255) : ARGB(120, 200, 230, 235));

                  pgraphics->SelectObject(pen);

                  pgraphics->draw_rect(rectClient, pen);

               }


               rectClient.left--;
               rectClient.right++;
               rectClient.top--;
               rectClient.bottom++;

               {

                  ::draw2d::path_sp pathRound(allocer());

                  pathRound->begin_figure(true, ::draw2d::fill_mode_winding);

                  pathRound->add_round_rect(rectClient, 1 * 2);

                  pathRound->end_figure(true);

                  //::draw2d::pen_sp pen(pgraphics, 1.0, ARGB(48, 108, 149, 255));
                  ::draw2d::pen_sp pen(pgraphics, 1.0, bError ? ARGB(75, 255, 210, 200) : bHover ? ARGB(80, 200, 230, 255) : ARGB(80, 220, 231, 235));

                  pgraphics->SelectObject(pen);

                  pgraphics->draw_rect(rectClient, pen);

               }



               rectClient.left--;
               rectClient.right++;
               rectClient.top--;
               rectClient.bottom++;

               {

                  ::draw2d::path_sp pathRound(allocer());

                  pathRound->begin_figure(true, ::draw2d::fill_mode_winding);

                  pathRound->add_round_rect(rectClient, 1 * 2);

                  pathRound->end_figure(true);

                  //::draw2d::pen_sp pen(pgraphics, 1.0, ARGB(36, 108, 149, 255));
                  ::draw2d::pen_sp pen(pgraphics, 1.0, bError ? ARGB(45, 255, 230, 220) : bHover ? ARGB(40, 220, 240, 255) : ARGB(40, 230, 235, 240));

                  pgraphics->SelectObject(pen);

                  pgraphics->draw_rect(rectClient, pen);

               }




            }

         }
         else
         {

            ::draw2d::pen_sp pen(pgraphics, 3.0, ARGB(255, 90, 80, 255));

            pgraphics->draw_rect(rectClient, pen);

         }

      }
      else
      {

         ::draw2d::pen_sp pen(pgraphics, 1.0, pui->_001GetColor(::user::color_border));

         pgraphics->draw_rect(rectClient, pen);

      }

      return true;

   }


   bool style::_001TabOnDrawSchema01(::draw2d::graphics * pgraphics, tab * ptab)
   {

      return false;

   }


   bool style::_001OnDrawMenuInteraction(::draw2d::graphics * pgraphics, menu_interaction * pinteraction)
   {

      return false;

   }


   void style::_001OnTabPaneDrawTitle(::user::tab_pane & pane, ::user::tab * ptab, ::draw2d::graphics * pgraphics, LPCRECT lpcrect, ::draw2d::brush_sp & brushText)
   {

      Session._001OnDefaultTabPaneDrawTitle(pane, ptab, pgraphics, lpcrect, brushText);

   }


   bool style::_001OnTabLayout(::user::tab * ptab)
   {

      return false;

   }


   //   bool style::_001GetMainFrameTranslucency(::user::e_translucency & etranslucency)
   //   {
   //
   //      return false;
   //
   //   }


   //   bool style::_001OnDrawMainFrameBackground(::draw2d::graphics * pgraphics, ::user::frame_window * pframe)
   //   {
   //
   //      return false;
   //
   //   }


   bool style::_001DrawCheckBox(::draw2d::graphics * pgraphics, ::user::check_box * pcheckbox)
   {

      return false;

   }


   bool style::_001DrawToolbarItem(::draw2d::graphics * pgraphics, int32_t iItem, ::user::toolbar * ptoolbar)
   {

      return false;

   }


   bool style::_001DrawSimpleScrollBar(::draw2d::graphics * pgraphics, simple_scroll_bar * pbar)
   {

      return false;

   }


   bool style::_001DrawScrollBar(::draw2d::graphics * pgraphics, ::user::scroll_bar * pbar)
   {

      return false;

   }


   ::user::menu_interaction * style::create_menu_button(menu_item * pitem)
   {

      return Session.create_menu_button(pitem);

   }


   bool style::prepare_menu(::user::menu_item * pitem)
   {

      if (!prepare_menu_button(pitem))
      {

         return false;

      }

      return true;

   }


   bool style::prepare_menu_button(::user::menu_item * pitem)
   {

      Session.prepare_menu_button(pitem);

      return true;

   }


   bool style::create_color(e_color ecolor, COLORREF cr)
   {

      if (userstyle()->m_mapColor.is_null())
      {

         userstyle()->m_mapColor = canew(color_map);

      }

      (*userstyle()->m_mapColor)[ecolor] = cr;

      return true;

   }


   ::draw2d::font_sp style::create_point_font(e_font efont, const char * pszFamilyName, double dFontSize, int iFontWeight)
   {

      if (userstyle()->m_mapFont.is_null())
      {

         userstyle()->m_mapFont = canew(font_map);

      }

      auto & font = (*userstyle()->m_mapFont)[efont];

      if (font.is_null())
      {

         font.alloc(allocer());

      }

      font->create_point_font(pszFamilyName, dFontSize, iFontWeight);

      return font;

   }


   bool style::create_opaque_color(e_color ecolor, COLORREF cr)
   {

      if (!create_color(ecolor, opaque_color(cr)))
      {

         return false;

      }

      return true;

   }


   bool style::create_opaque_color(e_color eusercolor, ::e_color ecolor)
   {

      if (!create_color(eusercolor, opaque_color(ecolor)))
      {

         return false;

      }

      return true;

   }


   bool style::create_session_default_opaque_color(e_color eusercolor, uint64_t ui)
   {

      if (!create_opaque_color(eusercolor, Session.get_default_color(ui)))
      {

         return false;

      }

      return true;

   }


   bool style::create_session_default_color(e_color eusercolor, BYTE bAlpha, uint64_t ui)
   {

      if (!create_color(eusercolor, alpha_color(bAlpha, Session.get_default_color(ui))))
      {

         return false;

      }

      return true;

   }


   bool style::create_translucency(e_element eelement, e_translucency etranslucency)
   {

      if (userstyle()->m_mapTranslucency.is_null())
      {

         userstyle()->m_mapTranslucency = canew(translucency_map);

      }

      (*userstyle()->m_mapTranslucency)[eelement] = etranslucency;

      return true;

   }


   bool style::create_flag(e_flag eflag, bool bFlag)
   {

      if (userstyle()->m_mapFlag.is_null())
      {

         userstyle()->m_mapFlag = canew(translucency_map);

      }

      (*userstyle()->m_mapFlag)[eflag] = bFlag;

      return true;

   }


   bool style::create_pixel_rect_coord(e_rect erect, double l, double t, double r, double b)
   {

      return create_rect_coord(erect, l, t, r, b, ::draw2d::unit_pixel);

   }


   bool style::create_pixel_rect_dim(e_rect erect, double l, double t, double w, double h)
   {

      return create_rect_dim(erect, l, t, w, h, ::draw2d::unit_pixel);

   }


   bool style::create_pixel_rect(e_rect erect, rectd r)
   {

      return create_rect(erect, r, ::draw2d::unit_pixel);

   }


   bool style::create_point_rect_coord(e_rect erect, double l, double t, double r, double b)
   {

      return create_rect_coord(erect, l, t, r, b, ::draw2d::unit_point);

   }


   bool style::create_point_rect_dim(e_rect erect, double l, double t, double w, double h)
   {

      return create_rect_dim(erect, l, t, w, h, ::draw2d::unit_point);

   }


   bool style::create_point_rect(e_rect erect, rectd r)
   {

      return create_rect(erect, r, ::draw2d::unit_point);

   }


   bool style::create_rect_coord(e_rect erect, double l, double t, double r, double b, ::draw2d::e_unit eunit)
   {

      if (userstyle()->m_mapRect.is_null())
      {

         userstyle()->m_mapRect = canew(rect_map);

      }

      (*userstyle()->m_mapRect)[erect].set_rect_coord(l, t, r, b, eunit);

      return true;

   }


   bool style::create_rect_dim(e_rect erect, double l, double t, double w, double h, ::draw2d::e_unit eunit)
   {

      return create_rect_coord(erect, l, t, l + w, t + h, eunit);

   }


   bool style::create_rect(e_rect erect, rectd r, ::draw2d::e_unit eunit)
   {

      return create_rect_coord(erect, r.left, r.top, r.right, r.bottom, eunit);

   }


   bool style::create_int(e_int eint, int i)
   {

      if (userstyle()->m_mapInt.is_null())
      {

         userstyle()->m_mapInt = canew(::user::int_map);

      }

      (*userstyle()->m_mapInt)[eint] = i;

      return true;

   }


   bool style::create_double(e_double edouble, double d)
   {

      if (userstyle()->m_mapDouble.is_null())
      {

         userstyle()->m_mapDouble = canew(::user::double_map);

      }

      (*userstyle()->m_mapDouble)[edouble] = d;

      return true;

   }

   e_control_type style::get_control_type()
   {

      return control_type_none;

   }


   void style::nextstyle(style_context * pcontext)
   {

      pcontext->m_pstyle.release();

   }


   //void style::defer_create_user_schema(::user::e_schema eschema)
   //{

   //   ::user::style * puserstyle = m_puserstyle;

   //   if (puserstyle == NULL)
   //   {

   //      puserstyle = this;

   //   }

   //   if (eschema == schema_default)
   //   {

   //      m_puserstyleSelect = puserstyle;

   //   }
   //   else
   //   {

   //      auto & spuserstyle = puserstyle->m_map[eschema];

   //      if (spuserstyle.is_null())
   //      {

   //         spuserstyle = canew(style(get_app()));

   //      }

   //      m_puserstyleSelect = spuserstyle;

   //   }

   //}


   //void style::select_user_schema()
   //{

   //   auto eschema = m_eschema;

   //   ::user::style * puserstyle = m_puserstyle;

   //   if (puserstyle == NULL)
   //   {

   //      puserstyle = this;

   //   }

   //   if (eschema == schema_default)
   //   {

   //      m_puserstyleSelect = puserstyle;

   //   }
   //   else
   //   {

   //      auto & spuserstyle = puserstyle->m_map[eschema];

   //      if (spuserstyle.is_set())
   //      {

   //         m_puserstyleSelect = spuserstyle;

   //      }
   //      else
   //      {

   //         m_puserstyleSelect = puserstyle;

   //      }

   //   }

   //}


   //void style::set_user_schema(::user::e_schema eschema)
   //{

   //   m_eschema = eschema;

   //}


   //style * style::style_get(::user::e_schema eschema)
   //{

   //   if (eschema == schema_default)
   //   {

   //      return this;

   //   }

   //   style_sp pstyle;

   //   if (m_map.Lookup(eschema, pstyle))
   //   {

   //      return pstyle;

   //   }

   //   return this;

   //}


   void style::select(::draw2d::graphics * pgraphics)
   {

      m_pgraphics = pgraphics;

   }


   ::draw2d::graphics * style::style_get_graphics()
   {

      return m_pgraphics;

   }

   style * style::userstyle()
   {

      return m_puserstyle;

   }


} // namespace user



