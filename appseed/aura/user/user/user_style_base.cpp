#include "framework.h" // from "base/user/user.h"


namespace user
{


   style_context::style_context(style * pstyleSource)
   {

      m_pstyleSource = pstyleSource;

      m_econtroltype = pstyleSource->get_control_type();

      m_pstyle = pstyleSource;

   }


   style_context & style_context::operator = (style * pstyleSource)
   {

      m_pstyleSource = pstyleSource;

      m_econtroltype = pstyleSource->get_control_type();

      m_pstyle = pstyleSource;

      return *this;

   }

   void style_context::next()
   {

      m_pstyle->nextstyle(this);

   }

   //   style::style(::aura::application * papp) :
   //   ::object(papp)
   //   {
   //
   //      m_plibrary = NULL;
   //      m_etranslucency      = translucency_undefined;
   //
   //   }
   //
   //
   //   style::~style()
   //   {
   //
   //      ::aura::del(m_plibrary);
   //
   //   }
   //
   //   void style::initialize_style_menu()
   //   {
   //
   //      style & style = *this;
   //
   //      style.m_pfont->create_point_font(FONT_SANS,9.0);
   //
   //      style[style_menu_button] = operator[](style_menu_button);
   //      style[style_menu_close] = operator[](style_menu_close);
   //      style[style_menu_popup] = operator[](style_menu_popup);
   //      style[style_system_menu_button] = operator[](style_system_menu_button);
   //      style[style_system_menu_close] = operator[](style_system_menu_close);
   //      style[style_system_menu_popup] = operator[](style_system_menu_popup);
   //
   //      style.m_iElementPadding = 3;
   //      style.m_rectItemMargin.left = 4;
   //      style.m_rectItemMargin.top = 4;
   //      style.m_rectItemMargin.right = 4;
   //      style.m_rectItemMargin.bottom = 4;
   //
   //   }
   //
   //   void style::initialize_style_button()
   //   {
   //
   //      color color;
   //      color.set_rgb(Session.get_default_color(COLOR_HIGHLIGHT));
   //
   //
   //      m_pfont.alloc(allocer());
   //      m_pfont->create_point_font(FONT_SANS,11.0);
   //      set_color(color_text_normal,ARGB(255,0,0,0));
   //      set_color(color_text_press,color | (0xff << 24));
   //      set_color(color_text_disabled,ARGB(255,127,127,127));
   //      set_color(color_text_hover,color | (0xff << 24));
   //      set_color(color_background,Session.get_default_color(COLOR_3DFACE) | (0xff << 24));
   //      set_color(color_background_press,Session.get_default_color(COLOR_3DFACE) | (0xff << 24));
   //      set_color(color_background_disabled,Session.get_default_color(COLOR_3DFACE) | (0xff << 24));
   //      set_color(color_background_hover,Session.get_default_color(COLOR_3DFACE) | (0xff << 24));
   //      m_bBorder      = true;
   //      m_etranslucency = ::user::translucency_none;
   //
   //   }
   //
   //   void style::initialize_style_menu_button()
   //   {
   //
   //      color color;
   //      color.set_rgb(Session.get_default_color(COLOR_HIGHLIGHT));
   //
   //
   //      m_pfont.alloc(allocer());
   //      m_pfont->create_point_font(FONT_SANS, 12.0);
   //      set_color(color_text_normal,ARGB(184,0,0,0));
   //      set_color(color_text_press,color | (184 << 24));
   //      set_color(color_text_disabled,ARGB(184,127,127,127));
   //      set_color(color_text_hover,color | (184 << 24));
   //      set_color(color_background,ARGB(84, 180, 192, 255));
   //      set_color(color_background_press,ARGB(184,180,192,255));
   //      set_color(color_background_disabled,ARGB(84,180,192,255));
   //      set_color(color_background_hover,ARGB(127,180,192,255));
   //      m_bBorder      = false;
   //      m_etranslucency = ::user::translucency_present;
   //
   //
   //   }
   //
   //
   //   void style::initialize_style_menu_popup()
   //   {
   //
   //
   //      color color;
   //      color.set_rgb(Session.get_default_color(COLOR_HIGHLIGHT));
   //
   //
   //      m_pfont.alloc(allocer());
   //      m_pfont->create_point_font(FONT_SANS, 9.0, FW_BOLD);
   //      set_color(color_text_normal,ARGB(184,0,0,0));
   //      set_color(color_text_press,color | (184 << 24));
   //      set_color(color_text_disabled,ARGB(184,127,127,127));
   //      set_color(color_text_hover,color | (184 << 24));
   //      set_color(color_background, Session.get_default_color(COLOR_3DHIGHLIGHT) | (184 << 24));
   //      set_color(color_background_press,Session.get_default_color(COLOR_3DHIGHLIGHT) | (184 << 24));
   //      set_color(color_background_disabled,Session.get_default_color(COLOR_3DHIGHLIGHT) | (184 << 24));
   //      set_color(color_background_hover,Session.get_default_color(COLOR_3DHIGHLIGHT) | (184 << 24));
   //      m_bBorder      = false;
   //      m_etranslucency = ::user::translucency_present;
   //
   //
   //   }
   //   void style::initialize_style_system_menu_button()
   //   {
   //
   //      color color;
   //      color.set_rgb(Session.get_default_color(COLOR_HIGHLIGHT));
   //
   //
   //      m_pfont.alloc(allocer());
   //      m_pfont->create_point_font("Marlett", 11.0);
   //      set_color(color_text_normal,ARGB(184,0,0,0));
   //      set_color(color_text_press,color | (184 << 24));
   //      set_color(color_text_disabled,ARGB(184,127,127,127));
   //      set_color(color_text_hover,color | (184 << 24));
   //      set_color(color_background,Session.get_default_color(COLOR_3DFACE) | (184 << 24));
   //      set_color(color_background_press,Session.get_default_color(COLOR_3DFACE) | (184 << 24));
   //      set_color(color_background_disabled,Session.get_default_color(COLOR_3DFACE) | (184 << 24));
   //      set_color(color_background_hover,Session.get_default_color(COLOR_3DFACE) | (184 << 24));
   //      m_bBorder      = false;
   //      m_etranslucency = ::user::translucency_present;
   //
   //   }
   //
   //
   //   void style::initialize_style_system_menu_close()
   //   {
   //
   //      m_pfont.alloc(allocer());
   //      m_pfont->create_point_font("Marlett",11.0);
   //      set_color(color_text_normal,ARGB(184,190, 90, 80));
   //      set_color(color_text_press,ARGB(223,255,0,0));
   //      set_color(color_text_disabled,ARGB(184,127,127,127));
   //      set_color(color_text_hover,ARGB(184,255,49,49));
   //      set_color(color_background,ARGB(184,208,192,192));
   //      set_color(color_background_press,ARGB(223,255,192,192));
   //      set_color(color_background_disabled,ARGB(184,192,192,192));
   //      set_color(color_background_hover,ARGB(184,223,192,192));
   //      m_bBorder      = false;
   //      m_etranslucency = ::user::translucency_present;
   //
   //   }
   //
   //
   //   void style::initialize_style_system_menu_popup()
   //   {
   //
   //      initialize_style_system_menu_button();
   //
   //   }
   //
   //
   //   void style::initialize_style()
   //   {
   //
   //      style & style = *this;
   //
   //      style[style_menu].alloc(allocer());
   //      style[style_button].alloc(allocer());
   //      style[style_menu_button].alloc(allocer());
   //      style[style_menu_popup].alloc(allocer());
   //      style[style_system_menu_button].alloc(allocer());
   //      style[style_system_menu_popup].alloc(allocer());
   //
   //      style[style_menu]->initialize_style_menu();
   //      style[style_button]->initialize_style_button();
   //      style[style_menu_button]->initialize_style_menu_button();
   //      style[style_menu_popup]->initialize_style_menu_popup();
   //      style[style_system_menu_button]->initialize_style_system_menu_button();
   //      style[style_system_menu_popup]->initialize_style_system_menu_popup();
   //
   //
   //      color color;
   //      color.set_rgb(Session.get_default_color(COLOR_HIGHLIGHT));
   //
   //      class color colorHover(color);
   //      colorHover.hls_rate(0.0, 0.3, 0.0);
   //
   //      class color colorPress(color);
   //      colorPress.hls_rate(0.0, 0.7, 0.0);
   //
   //
   //
   //
   //
   //
   //         m_crTextNormal = ARGB(255, 0, 0, 0);
   //
   //      }
   //
   //
   //      void style::DrawCheck(check::e_check echeck, const RECT & rect, ::draw2d::graphics * pgraphics)
   //      {
   //
   //
   //
   //         if(echeck == check::checked)
   //         {
   //            point_array pta;
   //
   //            pta.add(point(2, 10));
   //            pta.add(point(6, 14));
   //            pta.add(point(14, 6));
   //            pta.add(point(14, 2));
   //            pta.add(point(6, 12));
   //            pta.add(point(2, 8));
   //
   //            pta.offset(rect.left, rect.top);
   //
   //            pgraphics->Polygon(pta);
   //
   //         }
   //
   //
   //   }
   //
   //
   //   bool style::get_color(COLORREF & cr, e_color ecolor)
   //   {
   //
   //      if (m_mapColor.Lookup(ecolor, cr))
   //      {
   //
   //         return true;
   //
   //      }
   //
   //      return false;
   //
   //   }
   //
   //
   //   bool style::get_font(::draw2d::font_sp & spfont, e_font efont, ::user::interaction * pui)
   //   {
   //
   //      if(m_pfont.is_set())
   //      {
   //
   //         spfont = m_pfont;
   //
   //         return true;
   //
   //      }
   //
   //      return false;
   //
   //   }
   //
   //
   //   bool style::select_text_color(::draw2d::graphics * pgraphics,e_color ecolor)
   //   {
   //
   //      COLORREF cr;
   //
   //      if(!get_color(cr, ecolor))
   //      {
   //
   //         return false;
   //
   //      }
   //
   //      pgraphics->set_text_color(cr);
   //
   //      return true;
   //
   //   }
   //
   //
   //   bool style::select_solid_brush(::draw2d::graphics * pgraphics,e_color ecolor)
   //   {
   //
   //      COLORREF cr;
   //
   //      if(!get_color(cr, ecolor))
   //      {
   //
   //         return false;
   //
   //      }
   //
   //      ::draw2d::brush_sp brush(allocer());
   //
   //      brush->create_solid(cr);
   //
   //      pgraphics->SelectObject(brush);
   //
   //      return true;
   //
   //   }
   //
   //
   //   bool style::select_font(::draw2d::graphics * pgraphics, e_font efont, ::user::interaction * pui)
   //   {
   //
   //      ::draw2d::font_sp font;
   //
   //      if(!get_font(font, efont, pui))
   //      {
   //
   //         font.alloc(allocer());
   //
   //         if (!font->create_point_font(FONT_SANS, 12.0))
   //         {
   //
   //            return false;
   //
   //         }
   //
   //      }
   //
   //      pgraphics->select_font(font);
   //
   //      return true;
   //
   //   }
   //
   //
   //   bool style::get_translucency(e_translucency & etranslucency)
   //   {
   //
   //      if(m_etranslucency != translucency_undefined)
   //      {
   //
   //         etranslucency = m_etranslucency;
   //
   //         return true;
   //
   //      }
   //
   //      return false;
   //
   //   }
   //
   //
   //   bool style::on_ui_event(e_event eevent, e_object eobject, ::user::interaction * pui)
   //   {
   //
   //      return false;
   //
   //   }
   //
   //
   //   COLORREF style::_001GetColor(e_color ecolor, COLORREF crDefault)
   //   {
   //
   //      COLORREF cr;
   //
   //      if (get_color(cr, ecolor))
   //         return cr;
   //
   //      return crDefault;
   //
   //   }
   //
   //   COLORREF style::_001GetColor(e_color ecolor)
   //   {
   //
   //      COLORREF cr;
   //
   //      if (get_color(cr, ecolor))
   //         return cr;
   //
   //      if (ecolor == color_text)
   //      {
   //
   //         return ARGB(255, 0, 0, 0);
   //
   //      }
   //      else if (ecolor == color_text_selected)
   //      {
   //
   //         return ARGB(255, 255, 255, 255);
   //
   //      }
   //      else if (ecolor == color_text_highlight)
   //      {
   //
   //         return ARGB(255, 55, 105, 255);
   //
   //      }
   //      else if (ecolor == color_text_selected_highlight)
   //      {
   //
   //         return ARGB(255, 102, 153, 255);
   //
   //      }
   //      else if (ecolor == color_background)
   //      {
   //
   //         if (_001IsTranslucent())
   //         {
   //
   //            return ARGB(60, 255, 255, 255);
   //
   //         }
   //         else
   //         {
   //
   //            return ARGB(255, 255, 255, 255);
   //
   //         }
   //
   //      }
   //      else if (ecolor == color_face)
   //      {
   //
   //         if (_001IsTranslucent())
   //         {
   //
   //            return ARGB(120, 0, 0, 0);
   //
   //         }
   //         else
   //         {
   //
   //            return ARGB(255,80, 80, 80);
   //
   //         }
   //
   //      }
   //      else if (ecolor == color_face_lite)
   //      {
   //
   //         if (_001IsTranslucent())
   //         {
   //
   //            return ARGB(80, 0, 0, 0);
   //
   //         }
   //         else
   //         {
   //
   //            return ARGB(255, 120, 120, 120);
   //
   //         }
   //
   //      }
   //      else if (ecolor == color_background_selected)
   //      {
   //
   //         if (_001IsTranslucent())
   //         {
   //
   //            return ARGB(184, 0, 0, 127);
   //
   //         }
   //         else
   //         {
   //
   //            return ARGB(255, 0, 0, 127);
   //
   //         }
   //
   //      }
   //      else if (ecolor == color_background_selected)
   //      {
   //
   //         if (_001IsTranslucent())
   //         {
   //
   //            return ARGB(184, 0, 0, 127);
   //
   //         }
   //         else
   //         {
   //
   //            return ARGB(255, 0, 0, 127);
   //
   //         }
   //
   //      }
   //      else if (ecolor == color_border)
   //      {
   //
   //         return ARGB(255, 84, 90, 80);
   //
   //      }
   //      else if (ecolor == color_border_hover)
   //      {
   //
   //         return ARGB(255, 84, 190, 80);
   //
   //      }
   //      else if (ecolor == color_text_hover)
   //      {
   //
   //         return ARGB(255, 84, 184, 255);
   //
   //      }
   //      else if (ecolor == color_list_header)
   //      {
   //
   //         return ARGB(255, 80, 80, 80);
   //
   //      }
   //      else if (ecolor == color_background)
   //      {
   //
   //         return ARGB(255, 255, 255, 255);
   //
   //      }
   //      else if (ecolor == color_text_normal)
   //      {
   //
   //         return ARGB(255, 0, 0, 0);
   //
   //      }
   //      else if (ecolor == color_background_hover)
   //      {
   //
   //         return ARGB(255, 255, 255, 255);
   //
   //      }
   //      else if (ecolor == color_text_hover)
   //      {
   //
   //         return ARGB(255, 0, 0, 0);
   //
   //      }
   //      else if (ecolor == color_list_header_background)
   //      {
   //
   //         return ARGB(80, 0, 0, 0);
   //
   //      }
   //      else if (ecolor == color_list_item_background)
   //      {
   //
   //         return ARGB(127, 0, 0, 0);
   //
   //      }
   //      else if (ecolor == color_button_background_disabled)
   //      {
   //
   //         return _001GetColor(color_background_disabled);
   //
   //      }
   //      else if (ecolor == color_button_background_hover)
   //      {
   //
   //         return _001GetColor(color_background_hover);
   //
   //      }
   //      else if (ecolor == color_button_background)
   //      {
   //
   //         return _001GetColor(color_background);
   //
   //      }
   //      else if (ecolor == color_button_background_press)
   //      {
   //
   //         return _001GetColor(color_background_press);
   //
   //      }
   //      else if (ecolor == color_button_text_disabled)
   //      {
   //
   //         return _001GetColor(color_text_disabled);
   //
   //      }
   //      else if (ecolor == color_button_text_hover)
   //      {
   //
   //         return _001GetColor(color_text_hover);
   //
   //      }
   //      else if (ecolor == color_button_text)
   //      {
   //
   //         return _001GetColor(color_text_normal);
   //
   //      }
   //      else if (ecolor == color_button_text_press)
   //      {
   //
   //         return _001GetColor(color_text_press);
   //
   //      }
   //      else if (ecolor == color_edit_background)
   //      {
   //
   //         return ARGB(128, 255, 255, 255);
   //
   //      }
   //      else if (ecolor == color_edit_text)
   //      {
   //
   //         return ARGB(128, 0, 0, 0);
   //
   //      }
   //      else if (ecolor == color_edit_text_selected)
   //      {
   //
   //         return ARGB(128, 255, 255, 255);
   //
   //      }
   //      else if (ecolor == color_edit_background_selected)
   //      {
   //
   //         return ARGB(128, 0, 0, 128);
   //
   //      }
   //      else if(ecolor == color_split_layout_background)
   //      {
   //
   //         return ARGB(128, 255, 255, 255);
   //
   //      }
   //      else if (ecolor == color_list_background)
   //      {
   //
   //         return ARGB(128, 255, 255, 255);
   //
   //      }
   //      else if (ecolor == color_toolbar_background)
   //      {
   //
   //         return ARGB(128, 255, 255, 255);
   //
   //      }
   //      else if (ecolor == color_list_header_separator)
   //      {
   //
   //         return ARGB(128, 0, 0, 0);
   //
   //      }
   //      else if (ecolor == color_view_background)
   //      {
   //
   //         return 0;
   //
   //      }
   //      else if (ecolor == color_scrollbar_background)
   //      {
   //
   //         return ARGB(127, 127, 127, 127);
   //
   //      }
   //
   //      _throw(invalid_argument_exception(get_app()));
   //
   //   }
   //
   //
   //   e_translucency style::_001GetTranslucency(e_translucency etranslucencyDefault)
   //   {
   //
   //      e_translucency etranslucency = translucency_undefined;
   //
   //      if (get_translucency(etranslucency))
   //      {
   //
   //         if (etranslucency != translucency_undefined)
   //         {
   //
   //            return etranslucency;
   //
   //         }
   //
   //      }
   //
   //      return etranslucencyDefault;
   //
   //   }
   //
   //
   //
   //   bool style::_001IsTranslucent()
   //   {
   //
   //      e_translucency etranslucency = _001GetTranslucency();
   //
   //      return etranslucency == translucency_present || etranslucency == translucency_total;
   //
   //   }
   //
   //
   //   bool style::_001IsBackgroundBypass()
   //   {
   //
   //      return _001GetTranslucency() == translucency_total;
   //
   //   }
   //
   //
   //   bool style::_001HasTranslucency()
   //   {
   //
   //      e_translucency etranslucency = _001GetTranslucency();
   //
   //      return etranslucency == translucency_present || etranslucency == translucency_total;
   //
   //   }
   //
   //
   //   bool style::_001IsTransparent()
   //   {
   //
   //      return _001GetTranslucency() == translucency_total;
   //
   //   }
   //
   //
   //
   //   bool style::select_layered_frame()
   //   {
   //
   //
   //      m_etranslucency = translucency_present;
   //
   //      return true;
   //
   //   }
   //
   //
   //
   ////   bool style::select_text_color(::draw2d::graphics * pgraphics, e_color ecolor)
   ////   {
   ////
   ////      COLORREF crText;
   ////
   ////      if (!get_color(crText, ecolor))
   ////         return false;
   ////
   ////      return pgraphics->set_text_color(crText);
   ////
   ////   }
   //
   //
   ////   bool style::select_font(::draw2d::graphics * pgraphics, e_font efont, ::user::interaction * pui)
   ////   {
   ////
   ////      ::draw2d::font_sp spfont;
   ////
   ////      if (!get_font(spfont, efont, pui))
   ////      {
   ////
   ////         spfont.alloc(allocer());
   ////
   ////         if (!spfont->create_point_font(FONT_SANS, 12.0))
   ////         {
   ////
   ////            return false;
   ////
   ////         }
   ////
   ////      }
   ////
   ////      if (spfont.is_null())
   ////         return false;
   ////
   ////      return pgraphics->set_font(spfont);
   ////
   ////   }
   //
   //
   //   bool style::simple_ui_draw_focus_rect(::user::interaction * pui, ::draw2d::graphics * pgraphics)
   //   {
   ////
   ////      if (m_puserstyle != NULL && m_puserstyle != this)
   ////      {
   ////
   ////         if (m_puserstyle->simple_ui_draw_focus_rect(pui, pgraphics))
   ////            return true;
   ////
   ////      }
   //
   //
   //
   //      bool bError = pui->m_ptooltip.is_set()
   //         && pui->m_ptooltip->IsWindowVisible()
   //         && pui->get_tooltip()->m_bError;
   //
   //      rect rectClient;
   //
   //      pui->::user::interaction::GetClientRect(rectClient);
   //
   //      pgraphics->set_alpha_mode(::draw2d::alpha_mode_blend);
   //
   //      int32_t iStyle = 1;
   //
   //      rectClient.left--;
   //      rectClient.top--;
   //
   //      if (m_pauraapp != NULL && (Session.get_keyboard_focus() == pui || pui->has_action_hover()))
   //      {
   //
   //         ::draw2d::brush_sp brush(allocer());
   //
   //         if (pui->has_action_hover() && !pui->has_text_input())
   //         {
   //
   //            brush->create_solid(ARGB(184, 150, 230, 180));
   //
   //            pgraphics->SelectObject(brush);
   //
   //            pgraphics->fill_rect(rectClient);
   //
   //         }
   //
   //         if (iStyle == 1)
   //         {
   //
   //            bool bHover = pui->has_action_hover();
   //
   //            if (pui->has_action_hover())
   //            {
   //
   //               ::draw2d::pen_sp pen(pgraphics, 1.0, pui->get_action_hover_border_color());
   //
   //               pgraphics->draw_rect(rectClient, pen);
   //
   //            }
   //            else
   //            {
   //
   //               //::draw2d::pen_sp pen(pgraphics, 1.0, ARGB(255, 108, 149, 255));
   //               ::draw2d::pen_sp pen(pgraphics, 1.0, ARGB(184, 84, 90, 80));
   //
   //               pgraphics->draw_rect(rectClient, pen);
   //
   //            }
   //
   //
   //            if (Session.get_keyboard_focus() == pui)
   //            {
   //
   //               rectClient.left--;
   //               rectClient.right++;
   //               rectClient.top--;
   //               rectClient.bottom++;
   //
   //               {
   //
   //                  //::draw2d::pen_sp pen(pgraphics, 1.0, ARGB(255, 108, 149, 255));
   //                  ::draw2d::pen_sp pen(pgraphics, 1.0, bError ? ARGB(195, 255, 130, 120) : bHover? ARGB(220, 120, 190, 255) : ARGB(220, 150, 190, 235));
   //
   //                  pgraphics->draw_rect(rectClient, pen);
   //
   //               }
   //
   //               rectClient.left--;
   //               rectClient.right++;
   //               rectClient.top--;
   //               rectClient.bottom++;
   //
   //               {
   //
   //                  /*::draw2d::path_sp pathRound(allocer());
   //
   //                  pathRound->begin_figure(true, ::draw2d::fill_mode_winding);
   //
   //                  pathRound->add_round_rect(rectClient, 1 * 2);
   //
   //                  pathRound->end_figure(true);*/
   //
   //                  //::draw2d::pen_sp pen(pgraphics, 1.0, ARGB(84, 108, 149, 255));
   //                  ::draw2d::pen_sp pen(pgraphics, 1.0, bError ? ARGB(155, 255, 150, 140) : bHover?ARGB(200, 140, 200, 255 ) : ARGB(200, 150, 210, 235));
   //
   //                  pgraphics->SelectObject(pen);
   //
   //                  pgraphics->draw_rect(rectClient, pen);
   //
   //               }
   //
   //               rectClient.left--;
   //               rectClient.right++;
   //               rectClient.top--;
   //               rectClient.bottom++;
   //
   //               {
   //
   //                  ::draw2d::path_sp pathRound(allocer());
   //
   //                  pathRound->begin_figure(true, ::draw2d::fill_mode_winding);
   //
   //                  pathRound->add_round_rect(rectClient, 1 * 2);
   //
   //                  pathRound->end_figure(true);
   //
   //                  //::draw2d::pen_sp pen(pgraphics, 1.0, ARGB(72, 108, 149, 255));
   //                  ::draw2d::pen_sp pen(pgraphics, 1.0, bError ? ARGB(135, 255, 170, 160) : bHover ? ARGB(160, 160, 210, 255) : ARGB(160, 180, 220, 255));
   //
   //                  pgraphics->SelectObject(pen);
   //
   //                  pgraphics->draw_rect(rectClient, pen);
   //
   //               }
   //
   //               rectClient.left--;
   //               rectClient.right++;
   //               rectClient.top--;
   //               rectClient.bottom++;
   //
   //               {
   //
   //                  ::draw2d::path_sp pathRound(allocer());
   //
   //                  pathRound->begin_figure(true, ::draw2d::fill_mode_winding);
   //
   //                  pathRound->add_round_rect(rectClient, 1 * 2);
   //
   //                  pathRound->end_figure(true);
   //
   //                  //::draw2d::pen_sp pen(pgraphics, 1.0, ARGB(60, 108, 149, 255));
   //                  ::draw2d::pen_sp pen(pgraphics, 1.0, bError ? ARGB(105, 255, 190, 180) : bHover ? ARGB(120, 180, 220, 255):  ARGB(120, 200, 230, 235));
   //
   //                  pgraphics->SelectObject(pen);
   //
   //                  pgraphics->draw_rect(rectClient, pen);
   //
   //               }
   //
   //
   //               rectClient.left--;
   //               rectClient.right++;
   //               rectClient.top--;
   //               rectClient.bottom++;
   //
   //               {
   //
   //                  ::draw2d::path_sp pathRound(allocer());
   //
   //                  pathRound->begin_figure(true, ::draw2d::fill_mode_winding);
   //
   //                  pathRound->add_round_rect(rectClient, 1 * 2);
   //
   //                  pathRound->end_figure(true);
   //
   //                  //::draw2d::pen_sp pen(pgraphics, 1.0, ARGB(48, 108, 149, 255));
   //                  ::draw2d::pen_sp pen(pgraphics, 1.0, bError ? ARGB(75, 255, 210, 200) : bHover ? ARGB(80, 200, 230, 255) : ARGB(80, 220, 231, 235));
   //
   //                  pgraphics->SelectObject(pen);
   //
   //                  pgraphics->draw_rect(rectClient, pen);
   //
   //               }
   //
   //
   //
   //               rectClient.left--;
   //               rectClient.right++;
   //               rectClient.top--;
   //               rectClient.bottom++;
   //
   //               {
   //
   //                  ::draw2d::path_sp pathRound(allocer());
   //
   //                  pathRound->begin_figure(true, ::draw2d::fill_mode_winding);
   //
   //                  pathRound->add_round_rect(rectClient, 1 * 2);
   //
   //                  pathRound->end_figure(true);
   //
   //                  //::draw2d::pen_sp pen(pgraphics, 1.0, ARGB(36, 108, 149, 255));
   //                  ::draw2d::pen_sp pen(pgraphics, 1.0, bError ? ARGB(45, 255, 230, 220) : bHover ? ARGB(40, 220, 240, 255) : ARGB(40, 230, 235, 240));
   //
   //                  pgraphics->SelectObject(pen);
   //
   //                  pgraphics->draw_rect(rectClient, pen);
   //
   //               }
   //
   //
   //
   //
   //               /*
   //               rectClient.left--;
   //               rectClient.right++;
   //               rectClient.top--;
   //               rectClient.bottom++;
   //
   //               {
   //
   //               ::draw2d::path_sp pathRound(allocer());
   //
   //               pathRound->begin_figure(true, ::draw2d::fill_mode_winding);
   //
   //               pathRound->add_round_rect(rectClient, 1 * 2);
   //
   //               pathRound->end_figure(true);
   //
   //               //::draw2d::pen_sp pen(pgraphics, 1.0, ARGB(24, 108, 149, 255));
   //
   //               ::draw2d::pen_sp pen(pgraphics, 1.0, ARGB(25, 240, 250, 255));
   //
   //               pgraphics->SelectObject(pen);
   //
   //               pgraphics->draw_rect(rectClient, pen);
   //
   //               }
   //               */
   //
   //            }
   //
   //         }
   //         else
   //         {
   //
   //            ::draw2d::pen_sp pen(pgraphics, 3.0, ARGB(255, 90, 80, 255));
   //
   //            pgraphics->draw_rect(rectClient, pen);
   //
   //         }
   //
   //      }
   //      else
   //      {
   //
   //         ::draw2d::pen_sp pen(pgraphics, 1.0, ARGB(255, 149, 149, 123));
   //
   //         pgraphics->draw_rect(rectClient, pen);
   //
   //      }
   //
   //      return true;
   //
   //   }
   //
   //
   //   bool style::_001TabOnDrawSchema01(::draw2d::graphics * pgraphics, tab * ptab)
   //   {
   //
   //      return false;
   //
   //   }
   //
   //
   //   void style::_001OnTabPaneDrawTitle(::user::tab_pane & pane, ::user::tab * ptab, ::draw2d::graphics * pgraphics, LPCRECT lpcrect, ::draw2d::brush_sp & brushText)
   //   {
   //
   //      if (Session.userstyle() != this)
   //      {
   //
   //         Session.userstyle()->_001OnTabPaneDrawTitle(pane, ptab, pgraphics, lpcrect, brushText);
   //
   //      }
   //
   //   }
   //
   //
   //   bool style::_001OnTabLayout(::user::tab * ptab)
   //   {
   //
   //      return false;
   //
   //   }
   //
   //
   //   bool style::_001GetMainFrameTranslucency(::user::e_translucency & etranslucency)
   //   {
   //
   //      return false;
   //
   //   }
   //
   //
   //   bool style::_001OnDrawMainFrameBackground(::draw2d::graphics * pgraphics, ::user::frame_window * pframe)
   //   {
   //
   //      return false;
   //
   //   }
   //
   //
   //   void style::_001DrawCheckBox(::draw2d::graphics * pgraphics, LPCRECT lpcrectClient, ::check::e_check echeck)
   //   {
   //
   //
   //      int w = width(lpcrectClient);
   //
   //      int h = height(lpcrectClient);
   //
   //      if (w <= 0 || h <= 0)
   //      {
   //
   //         return;
   //
   //      }
   //
   //      pgraphics->OffsetViewportOrg(lpcrectClient->left, lpcrectClient->top);
   //
   //      // if no image
   //      {
   //         rect rectCheckBox;
   //         rectCheckBox.left = 0;
   //         rectCheckBox.top = 0;
   //         rectCheckBox.right = 15 * w / 15;
   //         rectCheckBox.bottom = 15 * h / 15;
   //         if (echeck == check::tristate)
   //         {
   //            pgraphics->fill_solid_rect(rectCheckBox, ARGB(255, 220, 220, 220));
   //         }
   //         pgraphics->draw3d_rect(rectCheckBox, ARGB(255, 128, 128, 128), ARGB(255, 128, 128, 128));
   //         if (echeck == check::tristate
   //            || echeck == check::checked)
   //         {
   //            ::draw2d::pen_sp pen(allocer());
   //            pen->create_solid(1 * (w + h) / 30, echeck == check::checked ? ARGB(255, 0, 0, 0) : ARGB(255, 96, 96, 96));
   //            pgraphics->SelectObject(pen);
   //            pgraphics->move_to(2 * w / 15, 8 * h / 15);
   //            pgraphics->line_to(6 * w / 15, 12 * h / 15);
   //            pgraphics->line_to(13 * w / 15, 5 * h / 15);
   //            pgraphics->move_to(2 * w / 15, 9 * h / 15);
   //            pgraphics->line_to(6 * w / 15, 13 * h / 15);
   //            pgraphics->line_to(13 * w / 15, 6 * h / 15);
   //         }
   //
   //      }
   //
   //      pgraphics->OffsetViewportOrg(-lpcrectClient->left, -lpcrectClient->top);
   //
   //   }
   //
   //
   //   bool style::_001DrawToolbarItem(::draw2d::graphics * pgraphics, int32_t iItem, ::user::toolbar * ptoolbar)
   //   {
   //
   //      return false;
   //
   //   }
   //
   //
   //   bool style::_001DrawSimpleScrollBar(::draw2d::graphics * pgraphics, simple_scroll_bar * pbar)
   //   {
   //
   //      return false;
   //
   //   }
   //
   //
   //   bool style::_001DrawScrollBar(::draw2d::graphics * pgraphics, ::user::scroll_bar * pbar)
   //   {
   //
   //      return false;
   //
   //   }
   //
   //
   //   ::user::interaction * style::create_menu_button()
   //   {
   //
   //      return canew(::user::button(get_app()));
   //
   //   }
   //
   //
   //   bool style::prepare_menu(::user::menu_item * pitem)
   //   {
   //
   //      if(!prepare_menu_button(pitem))
   //      {
   //
   //         return false;
   //
   //      }
   //
   //      return true;
   //
   //   }
   //
   //
   //
   //
   //
   //   bool style::set_color(e_color ecolor,COLORREF cr)
   //   {
   //
   //      m_mapColor[ecolor] = cr;
   //
   //      return true;
   //
   //   }
   //
   //
   //   bool style::prepare_menu_button(::user::menu_item * pitem)
   //   {
   //
   //      if(!::user::style::prepare_menu_button(pitem))
   //      {
   //
   //         return false;
   //
   //      }
   //
   //      sp(::user::button) pbutton = pitem->m_pui;
   //
   //      if(pbutton->m_id == "close")
   //      {
   //
   //         pbutton->m_puserstyle = get(style_system_menu_close);
   //
   //         pbutton->resize_to_fit();
   //
   //         pbutton->set_stock_icon(stock_icon_close);
   //
   //         return true;
   //
   //      }
   //      else
   //      {
   //
   //         pbutton->m_puserstyle = get(style_system_menu_button);
   //
   //         int cx = pbutton->width();
   //
   //         int cy = pbutton->height();
   //
   //         pbutton->m_pitem = pitem;
   //
   //         pbutton->m_rectCheckBox.left = m_rectItemMargin.left;
   //         pbutton->m_rectCheckBox.top = m_rectItemMargin.top;
   //         pbutton->m_rectCheckBox.bottom = cy - m_rectItemMargin.bottom;
   //         pbutton->m_rectCheckBox.right = pbutton->m_rectCheckBox.left + pitem->m_pmenu->m_iCheckBoxSize;
   //
   //         pbutton->m_rectText.left = pbutton->m_rectCheckBox.right + m_iElementPadding;
   //         pbutton->m_rectText.top = m_rectItemMargin.top;
   //         pbutton->m_rectText.bottom = cy - m_rectItemMargin.bottom;
   //         pbutton->m_rectText.right = cx - m_rectItemMargin.right;
   //
   //      }
   //
   //      return true;
   //
   //   }


   bool style_base::_001OnDrawSplitLayout(::draw2d::graphics * pgraphics, ::user::split_layout * psplitlayout)
   {

      return false;

   }


   bool style_base::get_color(COLORREF & cr, e_color ecolor, style_context * pcontext)
   {

      return false;

   }


   bool style_base::get_font(::draw2d::font_sp & font, e_font efont, style_context * pcontext)
   {

      return false;

   }


   bool style_base::get_translucency(e_translucency & etranslucency, e_element eelement, style_context * pcontext)
   {

      return false;

   }


   bool style_base::get_flag(bool & bSet, e_flag eflag, style_context * pcontext)
   {

      return false;

   }


   bool style_base::get_rect(RECT & rect, e_rect erect, style_context * pcontext)
   {

      return false;

   }


   bool style_base::get_int(int & i, e_int eint, style_context * pcontext)
   {

      return false;

   }


   bool style_base::get_double(double & d, e_double edouble, style_context * pcontext)
   {

      return false;

   }


   e_control_type style_base::get_control_type()
   {

      return control_type_none;

   }


} // namespace user











