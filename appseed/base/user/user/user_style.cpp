//#include "framework.h" // from "base/user/user.h"


namespace user
{


   style_simple::style(::aura::application * papp) :
   ::object(papp)
   {

      m_plibrary = NULL;
      m_etranslucency      = TranslucencyUndefined;

   }


   style_simple::~style()
   {
      
      ::aura::del(m_plibrary);

   }
   
   void style_simple::initialize_style_menu()
   {
      
      style & style = *this;
      
      style.m_pfont->create_point_font(FONT_SANS,9.0);
      
      style[style_menu_button] = operator[](style_menu_button);
      style[style_menu_close] = operator[](style_menu_close);
      style[style_menu_popup] = operator[](style_menu_popup);
      style[style_system_menu_button] = operator[](style_system_menu_button);
      style[style_system_menu_close] = operator[](style_system_menu_close);
      style[style_system_menu_popup] = operator[](style_system_menu_popup);
      
      style.m_iElementPadding = 3;
      style.m_rectItemMargin.left = 4;
      style.m_rectItemMargin.top = 4;
      style.m_rectItemMargin.right = 4;
      style.m_rectItemMargin.bottom = 4;

   }

   void style_simple::initialize_style_button()
   {
      
      color color;
      color.set_rgb(Session.get_default_color(COLOR_HIGHLIGHT));
      

      m_pfont.alloc(allocer());
      m_pfont->create_point_font(FONT_SANS,11.0);
      set_color(color_text_normal,ARGB(255,0,0,0));
      set_color(color_text_press,color | (0xff << 24));
      set_color(color_text_disabled,ARGB(255,127,127,127));
      set_color(color_text_hover,color | (0xff << 24));
      set_color(color_background_normal,Session.get_default_color(COLOR_3DFACE) | (0xff << 24));
      set_color(color_background_press,Session.get_default_color(COLOR_3DFACE) | (0xff << 24));
      set_color(color_background_disabled,Session.get_default_color(COLOR_3DFACE) | (0xff << 24));
      set_color(color_background_hover,Session.get_default_color(COLOR_3DFACE) | (0xff << 24));
      m_bBorder      = true;
      m_etranslucency = ::user::TranslucencyNone;

   }

   void style_simple::initialize_style_menu_button()
   {
      
      color color;
      color.set_rgb(Session.get_default_color(COLOR_HIGHLIGHT));
      

      m_pfont.alloc(allocer());
      m_pfont->create_point_font(FONT_SANS, 12.0);
      set_color(color_text_normal,ARGB(184,0,0,0));
      set_color(color_text_press,color | (184 << 24));
      set_color(color_text_disabled,ARGB(184,127,127,127));
      set_color(color_text_hover,color | (184 << 24));
      set_color(color_background_normal,ARGB(84, 180, 192, 255));
      set_color(color_background_press,ARGB(184,180,192,255));
      set_color(color_background_disabled,ARGB(84,180,192,255));
      set_color(color_background_hover,ARGB(127,180,192,255));
      m_bBorder      = false;
      m_etranslucency = ::user::TranslucencyPresent;
      
      
   }
   
   
   void style_simple::initialize_style_menu_popup()
   {
      
      
      color color;
      color.set_rgb(Session.get_default_color(COLOR_HIGHLIGHT));
      

      m_pfont.alloc(allocer());
      m_pfont->create_point_font(FONT_SANS, 9.0, FW_BOLD);
      set_color(color_text_normal,ARGB(184,0,0,0));
      set_color(color_text_press,color | (184 << 24));
      set_color(color_text_disabled,ARGB(184,127,127,127));
      set_color(color_text_hover,color | (184 << 24));
      set_color(color_background_normal, Session.get_default_color(COLOR_3DHIGHLIGHT) | (184 << 24));
      set_color(color_background_press,Session.get_default_color(COLOR_3DHIGHLIGHT) | (184 << 24));
      set_color(color_background_disabled,Session.get_default_color(COLOR_3DHIGHLIGHT) | (184 << 24));
      set_color(color_background_hover,Session.get_default_color(COLOR_3DHIGHLIGHT) | (184 << 24));
      m_bBorder      = false;
      m_etranslucency = ::user::TranslucencyPresent;
      
      
   }
   void style_simple::initialize_style_system_menu_button()
   {
      
      color color;
      color.set_rgb(Session.get_default_color(COLOR_HIGHLIGHT));
      

      m_pfont.alloc(allocer());
      m_pfont->create_point_font("Marlett", 11.0);
      set_color(color_text_normal,ARGB(184,0,0,0));
      set_color(color_text_press,color | (184 << 24));
      set_color(color_text_disabled,ARGB(184,127,127,127));
      set_color(color_text_hover,color | (184 << 24));
      set_color(color_background_normal,Session.get_default_color(COLOR_3DFACE) | (184 << 24));
      set_color(color_background_press,Session.get_default_color(COLOR_3DFACE) | (184 << 24));
      set_color(color_background_disabled,Session.get_default_color(COLOR_3DFACE) | (184 << 24));
      set_color(color_background_hover,Session.get_default_color(COLOR_3DFACE) | (184 << 24));
      m_bBorder      = false;
      m_etranslucency = ::user::TranslucencyPresent;
  
   }
   
   
   void style_simple::initialize_style_system_menu_close()
   {
      
      m_pfont.alloc(allocer());
      m_pfont->create_point_font("Marlett",11.0);
      set_color(color_text_normal,ARGB(184,184,84,77));
      set_color(color_text_press,ARGB(223,255,0,0));
      set_color(color_text_disabled,ARGB(184,127,127,127));
      set_color(color_text_hover,ARGB(184,255,49,49));
      set_color(color_background_normal,ARGB(184,208,192,192));
      set_color(color_background_press,ARGB(223,255,192,192));
      set_color(color_background_disabled,ARGB(184,192,192,192));
      set_color(color_background_hover,ARGB(184,223,192,192));
      m_bBorder      = false;
      m_etranslucency = ::user::TranslucencyPresent;
    
   }
   
   
   void style_simple::initialize_style_system_menu_popup()
   {
      
      initialize_style_system_menu_button();
      
   }

   
   void style_simple::initialize_style()
   {

      style & style = *this;
      
      style[style_menu].alloc(allocer());
      style[style_button].alloc(allocer());
      style[style_menu_button].alloc(allocer());
      style[style_menu_popup].alloc(allocer());
      style[style_system_menu_button].alloc(allocer());
      style[style_system_menu_popup].alloc(allocer());

      style[style_menu]->initialize_style_menu();
      style[style_button]->initialize_style_button();
      style[style_menu_button]->initialize_style_menu_button();
      style[style_menu_popup]->initialize_style_menu_popup();
      style[style_system_menu_button]->initialize_style_system_menu_button();
      style[style_system_menu_popup]->initialize_style_system_menu_popup();

      
      color color;
      color.set_rgb(Session.get_default_color(COLOR_HIGHLIGHT));
      
      class color colorHover(color);
      colorHover.hls_rate(0.0, 0.3, 0.0);
      
      class color colorPress(color);
      colorPress.hls_rate(0.0, 0.7, 0.0);

      
      
      
      
      
         m_crTextNormal = ARGB(255, 0, 0, 0);
         
      }
      
   
      void style_simple::DrawCheck(check::e_check echeck, const RECT & rect, ::draw2d::graphics * pgraphics)
      {
         
         
         
         if(echeck == check::checked)
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


   bool style_simple::get_color(COLORREF & cr, e_color ecolor)
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
            
            cr = ARGB(255,80, 80, 80);
            
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
      else if(ecolor == color_split_layout_background)
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
   

   bool style_simple::get_font(::draw2d::font_sp & spfont, e_font efont, ::user::interaction * pui)
   {

      if(m_pfont.is_set())
      {
      
         spfont = m_pfont;
         
         return true;
         
      }

      return false;

   }


   

   bool style_simple::get_translucency(ETranslucency & etranslucency)
   {

      if(m_etranslucency != TranslucencyUndefined)
      {
      
         etranslucency = m_etranslucency;
      
         return true;
         
      }
      
      return false;

   }

//
//   bool style_simple::on_ui_event(e_event eevent, e_object eobject, ::user::interaction * pui)
//   {
//
//      return false;
//      
//   }
//   




   ETranslucency style_simple::_001GetTranslucency(ETranslucency etranslucencyDefault)
   {

      ETranslucency etranslucency = TranslucencyUndefined;

      if (get_translucency(etranslucency))
      {

         if (etranslucency != TranslucencyUndefined)
         {

            return etranslucency;

         }

      }

      return etranslucencyDefault;

   }



   bool style_simple::_001IsTranslucent()
   {

      ETranslucency etranslucency = _001GetTranslucency();

      return etranslucency == TranslucencyPresent || etranslucency == TranslucencyTotal;

   }


   bool style_simple::_001IsBackgroundBypass()
   {

      return _001GetTranslucency() == TranslucencyTotal;

   }


   bool style_simple::_001HasTranslucency()
   {

      ETranslucency etranslucency = _001GetTranslucency();

      return etranslucency == TranslucencyPresent || etranslucency == TranslucencyTotal;

   }


   bool style_simple::_001IsTransparent()
   {

      return _001GetTranslucency() == TranslucencyTotal;

   }


  
   bool style_simple::select_layered_frame()
   {


      m_etranslucency = TranslucencyPresent;

      return true;

   }



//   bool style_simple::select_text_color(::draw2d::graphics * pgraphics, e_color ecolor)
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


//   bool style_simple::select_font(::draw2d::graphics * pgraphics, e_font efont, ::user::interaction * pui)
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


   bool style_simple::simple_ui_draw_focus_rect(::user::interaction * pui, ::draw2d::graphics * pgraphics)
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
                  ::draw2d::pen_sp pen(pgraphics, 1.0, bError ? ARGB(195, 255, 130, 120) : bHover? ARGB(220, 120, 190, 255) : ARGB(220, 150, 190, 235));

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
                  ::draw2d::pen_sp pen(pgraphics, 1.0, bError ? ARGB(155, 255, 150, 140) : bHover?ARGB(200, 140, 200, 255 ) : ARGB(200, 150, 210, 235));

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
                  ::draw2d::pen_sp pen(pgraphics, 1.0, bError ? ARGB(105, 255, 190, 180) : bHover ? ARGB(120, 180, 220, 255):  ARGB(120, 200, 230, 235));

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


   bool style_simple::_001TabOnDrawSchema01(::draw2d::graphics * pgraphics, tab * ptab)
   {

      return false;

   }


   void style_simple::_001OnTabPaneDrawTitle(::user::tab_pane & pane, ::user::tab * ptab, ::draw2d::graphics * pgraphics, LPCRECT lpcrect, ::draw2d::brush_sp & brushText)
   {

      if (Session.userstyle() != this)
      {

         Session.userstyle()->_001OnTabPaneDrawTitle(pane, ptab, pgraphics, lpcrect, brushText);

      }

   }


   bool style_simple::_001OnTabLayout(::user::tab * ptab)
   {

      return false;

   }


   bool style_simple::_001GetMainFrameTranslucency(::user::ETranslucency & etranslucency)
   {

      return false;

   }


   bool style_simple::_001OnDrawMainFrameBackground(::draw2d::graphics * pgraphics, ::user::frame_window * pframe)
   {

      return false;

   }


   void style_simple::_001DrawCheckBox(::draw2d::graphics * pgraphics, LPCRECT lpcrectClient, ::check::e_check echeck)
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


   bool style_simple::_001DrawToolbarItem(::draw2d::graphics * pgraphics, int32_t iItem, ::user::toolbar * ptoolbar)
   {

      return false;

   }


   bool style_simple::_001DrawSimpleScrollBar(::draw2d::graphics * pgraphics, simple_scroll_bar * pbar)
   {

      return false;

   }


   bool style_simple::_001DrawScrollBar(::draw2d::graphics * pgraphics, ::user::scroll_bar * pbar)
   {

      return false;

   }
   
   
   ::user::interaction * style_simple::create_menu_button()
   {
      
      return canew(::user::button(get_app()));
   
   }
   

   bool style_simple::prepare_menu(::user::menu_item * pitem)
   {
      
      if(!prepare_menu_button(pitem))
      {
         
         return false;
         
      }
      
      return true;
      
   }
   


   
   
   bool style_simple::set_color(e_color ecolor,COLORREF cr)
   {
      
      m_mapColor[ecolor] = cr;
      
      return true;
      
   }
   
   
   bool style_simple::prepare_menu_button(::user::menu_item * pitem)
   {
      
      if(!::user::style_simple::prepare_menu_button(pitem))
      {
         
         return false;
         
      }
      
      sp(::user::button) pbutton = pitem->m_pui;
      
      if(pbutton->m_id == "close")
      {
         
         pbutton->m_puserstyle = get(style_system_menu_close);
         
         pbutton->ResizeToFit();
         
         pbutton->set_stock_icon(stock_icon_close);
         
         return true;
         
      }
      else
      {
         
         pbutton->m_puserstyle = get(style_system_menu_button);
         
         int cx = pbutton->width();
         
         int cy = pbutton->height();
         
         pbutton->m_pitem = pitem;
         
         pbutton->m_rectCheckBox.left = m_rectItemMargin.left;
         pbutton->m_rectCheckBox.top = m_rectItemMargin.top;
         pbutton->m_rectCheckBox.bottom = cy - m_rectItemMargin.bottom;
         pbutton->m_rectCheckBox.right = pbutton->m_rectCheckBox.left + pitem->m_pmenu->m_iCheckBoxSize;
         
         pbutton->m_rectText.left = pbutton->m_rectCheckBox.right + m_iElementPadding;
         pbutton->m_rectText.top = m_rectItemMargin.top;
         pbutton->m_rectText.bottom = cy - m_rectItemMargin.bottom;
         pbutton->m_rectText.right = cx - m_rectItemMargin.right;
         
      }
      
      return true;
      
   }
   

   virtual bool style::has_flag(e_flag eflag)
   {
   return m_mapFlag[eflag]; }
   virtual rect style::get_rect(e_rect erect) {
return m_mapRect[erect]; }
   virtual int style::get_int(e_int eint){
return m_mapInt[eint]; }

} // namespace user











