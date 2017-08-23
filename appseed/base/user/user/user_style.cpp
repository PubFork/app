#include "framework.h" // from "base/user/user.h"


namespace user
{


   style::style() :
      style(get_app())
   {

   }


   style::style(::aura::application * papp) :
      ::object(papp)
   {

      m_eschema = schema_default;

      m_pgraphics = NULL;

   }


   style::~style()
   {

      ::aura::del(m_plibrary);

   }


   void style::select_default()
   {

      if (m_puserstyle.is_set())
      {

         m_puserstyleSelect = m_puserstyle;

      }
      else
      {

         m_puserstyleSelect = this;

      }

   }


   //void style::defer_create_user_schema(e_schema eschema)
   //{

   //   select_default();

   //   if (eschema != ::user::schema_default)
   //   {

   //      m_puserstyleSelect->m_map[eschema] = canew(style(get_app()));

   //      m_puserstyleSelect = m_puserstyleSelect->m_map[eschema];

   //   }

   //}


   void style::initialize_style_menu()
   {


      m_mapInt[int_menu_button_padding] = 3;
      m_mapRect[rect_menu_margin].left = 4;
      m_mapRect[rect_menu_margin].top = 4;
      m_mapRect[rect_menu_margin].right = 4;
      m_mapRect[rect_menu_margin].bottom = 4;

   }

   void style::initialize_style_button()
   {

      defer_create_user_schema(schema_button);

      create_point_font(font_default, FONT_SANS, 11.0);

      create_opaque_color(color_text_normal, ::color_black);
      create_session_default_opaque_color(color_text_press, COLOR_HIGHLIGHT);
      create_opaque_color(color_text_disabled, ::color_gray);
      create_session_default_opaque_color(color_text_hover, COLOR_HIGHLIGHT);
      create_session_default_opaque_color(color_background_normal, COLOR_3DFACE);
      create_session_default_opaque_color(color_background_press, COLOR_3DFACE);
      create_session_default_opaque_color(color_background_disabled, COLOR_3DFACE);
      create_session_default_opaque_color(color_background_hover, COLOR_3DFACE);
      create_flag(flag_border);
      create_translucency(element_none, ::user::translucency_none);

   }


   void style::initialize_style_menu_button()
   {

      defer_create_user_schema(schema_menu_button);

      create_point_font(font_default, FONT_SANS, 12.0);

      create_color(color_text_normal, alpha_color(200, ::color_black));
      create_session_default_color(color_text_press, 200, COLOR_HIGHLIGHT);
      create_color(color_text_disabled, alpha_color(200, ::color_gray));
      create_session_default_color(color_text_hover, 200, COLOR_HIGHLIGHT);
      create_color(color_background_normal, ARGB(100, 180, 192, 255));
      create_color(color_background_press, ARGB(200, 180, 192, 255));
      create_color(color_background_disabled, ARGB(100, 180, 192, 255));
      create_color(color_background_hover, ARGB(125, 180, 192, 255));
      create_flag(flag_border);
      create_translucency(element_none, ::user::translucency_present);


   }


   void style::initialize_style_menu_popup()
   {

      defer_create_user_schema(schema_menu_popup);

      create_point_font(font_default, FONT_SANS, 9.0, FW_BOLD);
      create_color(color_text_normal, alpha_color(200, ::color_black));
      create_session_default_color(color_text_press, 200, COLOR_HIGHLIGHT);
      create_color(color_text_disabled, alpha_color(200, ::color_gray));
      create_session_default_color(color_text_hover, 200, COLOR_HIGHLIGHT);
      create_session_default_color(color_background_normal, 200, COLOR_3DHIGHLIGHT);
      create_session_default_color(color_background_press, 200, COLOR_3DHIGHLIGHT);
      create_session_default_color(color_background_disabled, 200, COLOR_3DHIGHLIGHT);
      create_session_default_color(color_background_hover, 200, COLOR_3DHIGHLIGHT);
      create_flag(flag_border, false);
      create_translucency(element_none, ::user::translucency_present);

   }


   void style::initialize_style_system_menu_button()
   {

      defer_create_user_schema(schema_system_menu_button);

      create_point_font(font_default, "Marlett", 11.0);

      create_color(color_text_normal, alpha_color(200, ::color_black));
      create_session_default_color(color_text_press, 200, COLOR_HIGHLIGHT);
      create_color(color_text_disabled, alpha_color(200, ::color_gray));
      create_session_default_color(color_text_hover, 200, COLOR_HIGHLIGHT);
      create_session_default_color(color_background_normal, 200, COLOR_3DFACE);
      create_session_default_color(color_background_press, 200, COLOR_3DFACE);
      create_session_default_color(color_background_disabled, 200, COLOR_3DFACE);
      create_session_default_color(color_background_hover, 200, COLOR_3DFACE);
      create_flag(flag_border, false);
      create_translucency(element_none, ::user::translucency_present);

   }


   void style::initialize_style_system_menu_close()
   {

      defer_create_user_schema(schema_system_menu_close);

      create_point_font(font_default, "Marlett", 11.0);
      create_color(color_text_normal, ARGB(200, 200, 100, 80));
      create_color(color_text_press, ARGB(225, 255, 0, 0));
      create_color(color_text_disabled, ARGB(200, 127, 127, 127));
      create_color(color_text_hover, ARGB(200, 255, 50, 50));
      create_color(color_background_normal, ARGB(200, 210, 192, 192));
      create_color(color_background_press, ARGB(225, 255, 192, 192));
      create_color(color_background_disabled, ARGB(200, 192, 192, 192));
      create_color(color_background_hover, ARGB(200, 223, 192, 192));
      create_flag(flag_border, false);
      create_translucency(element_none, ::user::translucency_present);

   }


   void style::initialize_style_system_menu_popup()
   {

      defer_create_user_schema(schema_system_menu_popup);

      create_point_font(font_default, "Marlett", 11.0);

      create_color(color_text_normal, alpha_color(200, ::color_black));
      create_session_default_color(color_text_press, 200, COLOR_HIGHLIGHT);
      create_color(color_text_disabled, alpha_color(200, ::color_gray));
      create_session_default_color(color_text_hover, 200, COLOR_HIGHLIGHT);
      create_session_default_color(color_background_normal, 200, COLOR_3DFACE);
      create_session_default_color(color_background_press, 200, COLOR_3DFACE);
      create_session_default_color(color_background_disabled, 200, COLOR_3DFACE);
      create_session_default_color(color_background_hover, 200, COLOR_3DFACE);
      create_flag(flag_border, false);
      create_translucency(element_none, ::user::translucency_present);

   }


   void style::initialize_style()
   {

      ::user::style_composite::initialize_style();

      color color;
      color.set_rgb(Session.get_default_color(COLOR_HIGHLIGHT));

      class color colorHover(color);
      colorHover.hls_rate(0.0, 0.3, 0.0);

      class color colorPress(color);
      colorPress.hls_rate(0.0, 0.7, 0.0);

      m_eschema = schema_default;

      create_opaque_color(color_text, ::color_black);

   }


   bool style::_001OnDrawMainFrameBackground(::draw2d::graphics * pgraphics, ::user::frame_window * pframe)
   {

      return false;

   }


   void style::DrawCheck(check::e_check echeck, const RECT & rect, ::draw2d::graphics * pgraphics)
   {



      if (echeck == check::checked)
      {
         point_array pta;

         pta.add(point(2, 10));
         pta.add(point(6, 14));
         pta.add(point(14, 6));
         pta.add(point(14, 2));
         pta.add(point(6, 12));
         pta.add(point(2, 8));

         pta.offset(rect.left, rect.top);

         pgraphics->Polygon(pta);

      }


   }


   bool style::get_color(COLORREF & cr, e_color ecolor)
   {

      if (m_mapColor.Lookup(ecolor, cr))
      {

         return true;

      }

      if (ecolor == color_text)
      {

         cr = ARGB(255, 0, 0, 0);

      }
      else if (ecolor == color_text_selected)
      {

         cr = ARGB(255, 255, 255, 255);

      }
      else if (ecolor == color_text_highlight)
      {

         cr = ARGB(255, 55, 105, 255);

      }
      else if (ecolor == color_text_selected_highlight)
      {

         cr = ARGB(255, 102, 153, 255);

      }
      else if (ecolor == color_background)
      {

         if (_001IsTranslucent())
         {

            cr = ARGB(60, 255, 255, 255);

         }
         else
         {

            cr = ARGB(255, 255, 255, 255);

         }

      }
      else if (ecolor == color_face)
      {

         if (_001IsTranslucent())
         {

            cr = ARGB(120, 0, 0, 0);

         }
         else
         {

            cr = ARGB(255, 80, 80, 80);

         }

      }
      else if (ecolor == color_face_lite)
      {

         if (_001IsTranslucent())
         {

            cr = ARGB(80, 0, 0, 0);

         }
         else
         {

            cr = ARGB(255, 120, 120, 120);

         }

      }
      else if (ecolor == color_tab_layout_background)
      {

         if (_001IsTranslucent())
         {

            cr = ARGB(80, 255, 255, 255);

         }
         else
         {

            cr = ARGB(255, 255, 255, 255);

         }

      }
      else if (ecolor == color_tab_client_background)
      {

         if (_001IsTranslucent())
         {

            cr = ARGB(0, 0, 0, 0);

         }
         else
         {

            cr = ARGB(255, 255, 255, 255);

         }

      }
      else if (ecolor == color_background_selected)
      {

         if (_001IsTranslucent())
         {

            cr = ARGB(184, 0, 0, 127);

         }
         else
         {

            cr = ARGB(255, 0, 0, 127);

         }

      }
      else if (ecolor == color_background_selected)
      {

         if (_001IsTranslucent())
         {

            cr = ARGB(184, 0, 0, 127);

         }
         else
         {

            cr = ARGB(255, 0, 0, 127);

         }

      }
      else if (ecolor == color_border_normal)
      {

         cr = ARGB(255, 84, 84, 77);

      }
      else if (ecolor == color_border_hover)
      {

         cr = ARGB(255, 84, 184, 77);

      }
      else if (ecolor == color_text_hover)
      {

         cr = ARGB(255, 84, 184, 255);

      }
      else if (ecolor == color_list_header)
      {

         cr = ARGB(255, 80, 80, 80);

      }
      else if (ecolor == color_background_normal)
      {

         cr = ARGB(255, 255, 255, 255);

      }
      else if (ecolor == color_text_normal)
      {

         cr = ARGB(255, 0, 0, 0);

      }
      else if (ecolor == color_background_hover)
      {

         cr = ARGB(255, 255, 255, 255);

      }
      else if (ecolor == color_text_hover)
      {

         cr = ARGB(255, 0, 0, 0);

      }
      else if (ecolor == color_list_header_background)
      {

         cr = ARGB(80, 0, 0, 0);

      }
      else if (ecolor == color_list_item_background)
      {

         cr = ARGB(127, 0, 0, 0);

      }
      else if (ecolor == color_button_background_disabled)
      {

         return get_color(cr, color_background_disabled);

      }
      else if (ecolor == color_button_background_hover)
      {

         return get_color(cr, color_background_hover);

      }
      else if (ecolor == color_button_background_normal)
      {

         return get_color(cr, color_background_normal);

      }
      else if (ecolor == color_button_background_press)
      {

         return get_color(cr, color_background_press);

      }
      else if (ecolor == color_button_text_disabled)
      {

         return get_color(cr, color_text_disabled);

      }
      else if (ecolor == color_button_text_hover)
      {

         return get_color(cr, color_text_hover);

      }
      else if (ecolor == color_button_text_normal)
      {

         return get_color(cr, color_text_normal);

      }
      else if (ecolor == color_button_text_press)
      {

         return get_color(cr, color_text_press);

      }
      else if (ecolor == color_edit_background)
      {

         cr = ARGB(128, 255, 255, 255);

      }
      else if (ecolor == color_edit_text)
      {

         cr = ARGB(128, 0, 0, 0);

      }
      else if (ecolor == color_edit_text_selected)
      {

         cr = ARGB(128, 255, 255, 255);

      }
      else if (ecolor == color_edit_background_selected)
      {

         cr = ARGB(128, 0, 0, 128);

      }
      else if (ecolor == color_split_layout_background)
      {

         cr = ARGB(128, 255, 255, 255);

      }
      else if (ecolor == color_list_background)
      {

         cr = ARGB(128, 255, 255, 255);

      }
      else if (ecolor == color_toolbar_background)
      {

         cr = ARGB(128, 255, 255, 255);

      }
      else if (ecolor == color_list_header_separator)
      {

         cr = ARGB(128, 0, 0, 0);

      }
      else if (ecolor == color_view_background)
      {

         cr = 0;

      }
      else if (ecolor == color_scrollbar_background)
      {

         cr = ARGB(127, 127, 127, 127);

      }
      else
      {

         throw invalid_argument_exception(::get_thread_app());


         return false;

      }

      return true;

   }


   bool style::get_font(::draw2d::font_sp & font, e_font efont)
   {

      if (m_mapFont.Lookup(efont, font))
      {

         return true;

      }

      if (m_mapFont.Lookup(font_default, font))
      {

         return true;

      }

      m_mapFont[font_default].alloc(allocer());

      m_mapFont[font_default]->create_point_font(FONT_SANS, 9.0);

      return false;

   }




   bool style::get_translucency(e_translucency & etranslucency, e_element eelement)
   {

      if (!m_mapTranslucency.Lookup(eelement, etranslucency)
         || etranslucency == translucency_undefined)
      {

         if (!m_mapTranslucency.Lookup(element_none, etranslucency)
            || etranslucency == translucency_undefined)
         {

            etranslucency = translucency_undefined;

            return false;

         }

      }

      return false;

   }


   bool style::on_ui_event(e_event eevent, e_object eobject, ::user::interaction * pui)
   {

      return false;

   }






   bool style::select_layered_frame()
   {


      create_translucency(element_none, translucency_present);

      return true;

   }



   //   bool style::select_text_color(::draw2d::graphics * pgraphics, e_color ecolor)
   //   {
   //
   //      COLORREF crText;
   //
   //      if (!get_color(crText, ecolor))
   //         return false;
   //
   //      return pgraphics->set_text_color(crText);
   //
   //   }


   //   bool style::select_font(::draw2d::graphics * pgraphics, e_font efont, ::user::interaction * pui)
   //   {
   //
   //      ::draw2d::font_sp spfont;
   //
   //      if (!get_font(spfont, efont, pui))
   //      {
   //
   //         spfont.alloc(allocer());
   //
   //         if (!spfont->create_point_font(FONT_SANS, 12.0))
   //         {
   //
   //            return false;
   //
   //         }
   //
   //      }
   //
   //      if (spfont.is_null())
   //         return false;
   //
   //      return pgraphics->set_font(spfont);
   //
   //   }


   bool style::simple_ui_draw_focus_rect(::user::interaction * pui, ::draw2d::graphics * pgraphics)
   {
      //
      //      if (m_puserstyle != NULL && m_puserstyle != this)
      //      {
      //
      //         if (m_puserstyle->simple_ui_draw_focus_rect(pui, pgraphics))
      //            return true;
      //
      //      }



      bool bError = pui->m_ptooltip.is_set()
         && pui->m_ptooltip->IsWindowVisible()
         && pui->get_tooltip()->m_bError;

      rect rectClient;

      pui->::user::interaction::GetClientRect(rectClient);

      pgraphics->set_alpha_mode(::draw2d::alpha_mode_blend);

      int32_t iStyle = 1;

      rectClient.left--;
      rectClient.top--;

      if (m_pauraapp != NULL && (Session.get_keyboard_focus() == pui || pui->has_action_hover()))
      {

         ::draw2d::brush_sp brush(allocer());

         if (pui->has_action_hover() && !pui->has_text_input())
         {

            brush->create_solid(ARGB(184, 150, 230, 180));

            pgraphics->SelectObject(brush);

            pgraphics->FillRectangle(rectClient);

         }

         if (iStyle == 1)
         {

            bool bHover = pui->has_action_hover();

            if (pui->has_action_hover())
            {

               ::draw2d::pen_sp pen(pgraphics, 1.0, pui->get_action_hover_border_color());

               pgraphics->DrawRect(rectClient, pen);

            }
            else
            {

               //::draw2d::pen_sp pen(pgraphics, 1.0, ARGB(255, 108, 149, 255));
               ::draw2d::pen_sp pen(pgraphics, 1.0, ARGB(184, 84, 84, 77));

               pgraphics->DrawRect(rectClient, pen);

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

                  pgraphics->DrawRect(rectClient, pen);

               }

               rectClient.left--;
               rectClient.right++;
               rectClient.top--;
               rectClient.bottom++;

               {

                  /*::draw2d::path_sp pathRound(allocer());

                  pathRound->begin_figure(true, ::draw2d::fill_mode_winding);

                  pathRound->add_round_rect(rectClient, 1 * 2);

                  pathRound->end_figure(true);*/

                  //::draw2d::pen_sp pen(pgraphics, 1.0, ARGB(84, 108, 149, 255));
                  ::draw2d::pen_sp pen(pgraphics, 1.0, bError ? ARGB(155, 255, 150, 140) : bHover ? ARGB(200, 140, 200, 255) : ARGB(200, 150, 210, 235));

                  pgraphics->SelectObject(pen);

                  pgraphics->DrawRect(rectClient, pen);

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

                  pgraphics->DrawRect(rectClient, pen);

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

                  pgraphics->DrawRect(rectClient, pen);

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

                  pgraphics->DrawRect(rectClient, pen);

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

                  pgraphics->DrawRect(rectClient, pen);

               }




               /*
               rectClient.left--;
               rectClient.right++;
               rectClient.top--;
               rectClient.bottom++;

               {

               ::draw2d::path_sp pathRound(allocer());

               pathRound->begin_figure(true, ::draw2d::fill_mode_winding);

               pathRound->add_round_rect(rectClient, 1 * 2);

               pathRound->end_figure(true);

               //::draw2d::pen_sp pen(pgraphics, 1.0, ARGB(24, 108, 149, 255));

               ::draw2d::pen_sp pen(pgraphics, 1.0, ARGB(25, 240, 250, 255));

               pgraphics->SelectObject(pen);

               pgraphics->DrawRect(rectClient, pen);

               }
               */

            }

         }
         else
         {

            ::draw2d::pen_sp pen(pgraphics, 3.0, ARGB(255, 84, 77, 255));

            pgraphics->DrawRect(rectClient, pen);

         }

      }
      else
      {

         ::draw2d::pen_sp pen(pgraphics, 1.0, ARGB(255, 149, 149, 123));

         pgraphics->DrawRect(rectClient, pen);

      }

      return true;

   }


   bool style::_001TabOnDrawSchema01(::draw2d::graphics * pgraphics, tab * ptab)
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


   void style::_001DrawCheckBox(::draw2d::graphics * pgraphics, LPCRECT lpcrectClient, ::check::e_check echeck)
   {


      int w = width(lpcrectClient);

      int h = height(lpcrectClient);

      if (w <= 0 || h <= 0)
      {

         return;

      }

      pgraphics->OffsetViewportOrg(lpcrectClient->left, lpcrectClient->top);

      // if no image
      {
         rect rectCheckBox;
         rectCheckBox.left = 0;
         rectCheckBox.top = 0;
         rectCheckBox.right = 15 * w / 15;
         rectCheckBox.bottom = 15 * h / 15;
         if (echeck == check::tristate)
         {
            pgraphics->FillSolidRect(rectCheckBox, ARGB(255, 220, 220, 220));
         }
         pgraphics->Draw3dRect(rectCheckBox, ARGB(255, 128, 128, 128), ARGB(255, 128, 128, 128));
         if (echeck == check::tristate
            || echeck == check::checked)
         {
            ::draw2d::pen_sp pen(allocer());
            pen->create_solid(1 * (w + h) / 30, echeck == check::checked ? ARGB(255, 0, 0, 0) : ARGB(255, 96, 96, 96));
            pgraphics->SelectObject(pen);
            pgraphics->MoveTo(2 * w / 15, 8 * h / 15);
            pgraphics->LineTo(6 * w / 15, 12 * h / 15);
            pgraphics->LineTo(13 * w / 15, 5 * h / 15);
            pgraphics->MoveTo(2 * w / 15, 9 * h / 15);
            pgraphics->LineTo(6 * w / 15, 13 * h / 15);
            pgraphics->LineTo(13 * w / 15, 6 * h / 15);
         }

      }

      pgraphics->OffsetViewportOrg(-lpcrectClient->left, -lpcrectClient->top);

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


   ::user::interaction * style::create_menu_button()
   {

      return canew(::user::button(get_app()));

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

      sp(::user::button) pbutton = pitem->m_pui;

      if (pbutton->m_id == "close")
      {

         pbutton->set_user_schema(::user::schema_menu_close);

         pbutton->resize_to_fit();

         pbutton->set_stock_icon(stock_icon_close);

         return true;

      }
      else
      {

         pbutton->set_user_schema(schema_menu_button);

         int cx = pbutton->width();

         int cy = pbutton->height();

         pbutton->m_pmenuitem = pitem;

         rect rectMargin = pbutton->style_rect(::user::rect_menu_margin);

         int iCheckBoxSize = pbutton->style_int(::user::int_check_box_size);

         int iElementPadding = pbutton->style_int(::user::int_element_padding);

         auto & rectCheckBox = pbutton->m_rectCheckBox;

         rectCheckBox.left = rectMargin.left;
         rectCheckBox.top = rectMargin.top;
         rectCheckBox.bottom = cy - rectMargin.bottom;
         rectCheckBox.right = rectCheckBox.left + iCheckBoxSize;

         auto & rectText = pbutton->m_rectText;

         rectText.left = rectCheckBox.right + iElementPadding;
         rectText.top = rectMargin.top;
         rectText.bottom = cy - rectMargin.bottom;
         rectText.right = cx - rectMargin.right;
         
      }

      return true;

   }


   bool style::create_color(e_color ecolor, COLORREF cr)
   {

      userstyle()->m_mapColor[ecolor] = cr;

      return true;

   }


   bool style::has_flag(e_flag eflag)
   {

      return userstyle()->m_mapFlag[eflag];

   }


   rect style::get_rect(e_rect erect)
   {

      return userstyle()->m_mapRect[erect];

   }


   int style::get_int(e_int eint)
   {

      return userstyle()->m_mapInt[eint];

   }


   bool style::create_point_font(e_font efont, const char * pszFamilyName, double dFontSize, int iFontWeight)
   {

      auto & font = userstyle()->m_mapFont[efont];

      if (font.is_null())
      {

         font.alloc(allocer());

      }

      if (!font->create_point_font(pszFamilyName, dFontSize, iFontWeight))
      {

         return false;

      }

      return true;

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

      userstyle()->m_mapTranslucency[eelement] = etranslucency;

      return true;

   }


   bool style::create_flag(e_flag eflag, bool bFlag)
   {

      userstyle()->m_mapFlag[eflag] = bFlag;

      return true;

   }


   bool style::create_rect(e_rect erect, LONG l, LONG t, LONG r, LONG b)
   {

      userstyle()->m_mapRect[erect] = rect(l, t, r, b);

      return true;

   }

   bool style::create_int(e_int eint, int i)
   {

      userstyle()->m_mapInt[eint] = i;

      return true;

   }


   e_schema style::get_user_style()
   {

      return m_eschema;

   }


   void style::defer_create_user_schema(::user::e_schema eschema)
   {

      ::user::style * puserstyle = m_puserstyle;

      if (puserstyle == NULL)
      {

         puserstyle = this;

      }

      if (eschema == schema_default)
      {

         m_puserstyleSelect = puserstyle;

      }
      else
      {

         auto & spuserstyle = puserstyle->m_map[eschema];

         if (spuserstyle.is_null())
         {

            spuserstyle = canew(style(get_app()));

         }

         m_puserstyleSelect = spuserstyle;

      }

   }


   void style::select_user_schema()
   {

      auto eschema = m_eschema;

      ::user::style * puserstyle = m_puserstyle;

      if (puserstyle == NULL)
      {

         puserstyle = this;

      }

      if (eschema == schema_default)
      {

         m_puserstyleSelect = puserstyle;

      }
      else
      {

         auto & spuserstyle = puserstyle->m_map[eschema];

         if (spuserstyle.is_set())
         {

            m_puserstyleSelect = spuserstyle;

         }
         else
         {

            m_puserstyleSelect = puserstyle;

         }

      }

   }


   void style::set_user_schema(::user::e_schema eschema)
   {

      m_eschema = eschema;

   }


   style * style::style_get(::user::e_schema eschema)
   {

      if (eschema == schema_default)
      {

         return this;

      }

      style_sp pstyle;

      if (m_map.Lookup(eschema, pstyle))
      {

         return pstyle;

      }

      return this;

   }


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

      style * puserstyle = style_composite::userstyle();

      if (puserstyle != NULL)
      {

         return puserstyle;

      }

      return this;

   }


} // namespace user











