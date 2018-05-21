#include "framework.h"


namespace user
{


   theme::theme(::aura::application * papp) :
      object(papp)
   {

      m_plibrary = NULL;

   }


   theme::~theme()
   {

      ::aura::del(m_plibrary);

   }


   void theme::initialize_theme()
   {

      create_int(int_still_draw_text_flags, DT_LEFT | DT_BOTTOM | DT_SINGLELINE);
      create_int(int_menu_item_draw_text_flags, DT_LEFT | DT_VCENTER | DT_SINGLELINE);
      create_color(color_edit_text_empty, ARGB(127, 0x80, 0x80, 0x80));


   }


//
//   void theme::nextstyle(style_context * pcontext)
//   {
//
//      if (pcontext->m_econtroltype != control_none
//            && m_map.Lookup(pcontext->m_econtroltype, pcontext->m_pstyle))
//      {
//
//         return;
//
//      }
//
//      pcontext->m_pstyle = this;
//
//   }
//
//   void theme::initialize_theme()
//   {
//
//      theme_current_control(control_menu);
//
//      create_int(int_menu_check_padding, 3);
//      create_int(int_button_draw_text_flags, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
//      create_int(int_menu_item_draw_text_flags, DT_LEFT | DT_VCENTER | DT_SINGLELINE);
//
//      create_rect_coord(rect_menu_margin, 4, 4, 4, 4);
//      create_rect_coord(rect_menu_border, 0, 0, 0, 0);
//      create_rect_coord(rect_menu_padding, 0, 0, 0, 0);
//      create_rect_coord(rect_menu_item_margin, 0, 0, 0, 1);
//      create_rect_coord(rect_menu_item_border, 0, 0, 0, 0);
//      create_rect_coord(rect_menu_item_padding, 2, 2, 2, 2);
//
//
//
//      theme_current_control(control_type_button);
//
//      create_point_font(font_default, FONT_SANS, 11.0);
//
//      create_opaque_color(color_text_normal, ::color_black);
//      create_session_default_opaque_color(color_text_press, COLOR_HIGHLIGHT);
//      create_opaque_color(color_text_disabled, ::color_gray);
//      create_session_default_opaque_color(color_text_hover, COLOR_HIGHLIGHT);
//      create_session_default_opaque_color(color_background, COLOR_3DFACE);
//      create_session_default_opaque_color(color_background_press, COLOR_3DFACE);
//      create_session_default_opaque_color(color_background_disabled, COLOR_3DFACE);
//      create_session_default_opaque_color(color_background_hover, COLOR_3DFACE);
//      create_flag(flag_border);
//      create_translucency(element_none, ::user::translucency_none);
//
//
//
//      theme_current_control(control_menu_button);
//
//      create_point_font(font_default, FONT_SANS, 12.0);
//
//      create_color(color_text_normal, alpha_color(200, ::color_black));
//      create_session_default_color(color_text_press, 200, COLOR_HIGHLIGHT);
//      create_color(color_text_disabled, alpha_color(200, ::color_gray));
//      create_session_default_color(color_text_hover, 200, COLOR_HIGHLIGHT);
//      create_color(color_background, ARGB(100, 180, 192, 255));
//      create_color(color_background_press, ARGB(200, 180, 192, 255));
//      create_color(color_background_disabled, ARGB(100, 180, 192, 255));
//      create_color(color_background_hover, ARGB(125, 180, 192, 255));
//      create_flag(flag_border);
//      create_translucency(element_none, ::user::translucency_present);
//
//
//
//      theme_current_control(control_menu_popup);
//
//      create_point_font(font_default, FONT_SANS, 9.0, FW_BOLD);
//      create_color(color_text_normal, alpha_color(200, ::color_black));
//      create_session_default_color(color_text_press, 200, COLOR_HIGHLIGHT);
//      create_color(color_text_disabled, alpha_color(200, ::color_gray));
//      create_session_default_color(color_text_hover, 200, COLOR_HIGHLIGHT);
//      create_session_default_color(color_background, 200, COLOR_3DHIGHLIGHT);
//      create_session_default_color(color_background_press, 200, COLOR_3DHIGHLIGHT);
//      create_session_default_color(color_background_disabled, 200, COLOR_3DHIGHLIGHT);
//      create_session_default_color(color_background_hover, 200, COLOR_3DHIGHLIGHT);
//      create_flag(flag_border, false);
//      create_translucency(element_none, ::user::translucency_present);
//
//
//
//      theme_current_control(control_system_menu_button);
//
//      create_point_font(font_default, "Marlett", 11.0);
//
//      create_color(color_text_normal, alpha_color(200, ::color_black));
//      create_session_default_color(color_text_press, 200, COLOR_HIGHLIGHT);
//      create_color(color_text_disabled, alpha_color(200, ::color_gray));
//      create_session_default_color(color_text_hover, 200, COLOR_HIGHLIGHT);
//      create_session_default_color(color_background, 200, COLOR_3DFACE);
//      create_session_default_color(color_background_press, 200, COLOR_3DFACE);
//      create_session_default_color(color_background_disabled, 200, COLOR_3DFACE);
//      create_session_default_color(color_background_hover, 200, COLOR_3DFACE);
//      create_flag(flag_border, false);
//      create_translucency(element_none, ::user::translucency_present);
//
//
//      theme_current_control(control_system_menu_close);
//
//      create_point_font(font_default, "Marlett", 11.0);
//      create_color(color_text_normal, ARGB(200, 200, 100, 80));
//      create_color(color_text_press, ARGB(225, 255, 0, 0));
//      create_color(color_text_disabled, ARGB(200, 127, 127, 127));
//      create_color(color_text_hover, ARGB(200, 255, 50, 50));
//      create_color(color_background, ARGB(200, 210, 192, 192));
//      create_color(color_background_press, ARGB(225, 255, 192, 192));
//      create_color(color_background_disabled, ARGB(200, 192, 192, 192));
//      create_color(color_background_hover, ARGB(200, 223, 192, 192));
//      create_flag(flag_border, false);
//      create_translucency(element_none, ::user::translucency_present);
//
//
//      theme_current_control(control_system_menu_popup);
//
//      create_point_font(font_default, "Marlett", 11.0);
//
//      create_color(color_text_normal, alpha_color(200, ::color_black));
//      create_session_default_color(color_text_press, 200, COLOR_HIGHLIGHT);
//      create_color(color_text_disabled, alpha_color(200, ::color_gray));
//      create_session_default_color(color_text_hover, 200, COLOR_HIGHLIGHT);
//      create_session_default_color(color_background, 200, COLOR_3DFACE);
//      create_session_default_color(color_background_press, 200, COLOR_3DFACE);
//      create_session_default_color(color_background_disabled, 200, COLOR_3DFACE);
//      create_session_default_color(color_background_hover, 200, COLOR_3DFACE);
//      create_flag(flag_border, false);
//      create_translucency(element_none, ::user::translucency_present);
//
//
//   }
//
//   //virtual ::user::menu_interaction * create_menu_button(menu_item * pitem) override;
//   //virtual bool prepare_menu(::user::menu_item * pitem) override;
//   //virtual bool prepare_menu_button(::user::menu_item * pitem) override;
//
//
//   //virtual bool _001OnDrawMainFrameBackground(::draw2d::graphics * pgraphics, ::user::frame * pframe) override;
//   //virtual void DrawCheck(check::e_check echeck, const RECT & rect, ::draw2d::graphics * pgraphics) override;
//   //virtual bool simple_ui_draw_focus_rect(::user::interaction * pui, ::draw2d::graphics * pgraphics) override;
//   //virtual bool on_ui_event(e_event eevent, e_object eobject, ::user::interaction * pui) override;
//   //virtual bool _001TabOnDrawSchema01(::draw2d::graphics * pgraphics, tab * ptab) override;
//   //virtual bool _001OnDrawMenuInteraction(::draw2d::graphics * pgraphics, menu_interaction * pbutton) override;
//   //virtual void _001OnTabPaneDrawTitle(::user::tab_pane & pane, ::user::tab * ptab, ::draw2d::graphics * pgraphics, LPCRECT lpcrect, ::draw2d::brush_sp & brushText) override;
//   //virtual bool _001OnTabLayout(::user::tab * ptab) override;
//   //virtual void _001DrawCheckBox(::draw2d::graphics * pgraphics, LPCRECT lpcrectClient, ::check::e_check echeck) override;
//   //virtual bool _001DrawToolbarItem(::draw2d::graphics * pgraphics, int32_t iItem, ::user::toolbar * ptoolbar) override;
//   //virtual bool _001DrawSimpleScrollBar(::draw2d::graphics * pgraphics, simple_scroll_bar * pbar) override;
//   //virtual bool _001DrawScrollBar(::draw2d::graphics * pgraphics, ::user::scroll_bar * pbar) override;
//
//
//   //virtual bool select_text_color(::user::interaction * pui, ::draw2d::graphics * pgraphics, e_color ecolor = color_text);
//   //virtual bool select_solid_brush(::user::interaction * pui, ::draw2d::graphics * pgraphics, e_color ecolor);
//   //virtual bool select_font(::user::interaction * pui, ::draw2d::graphics * pgraphics, e_font efont = font_default);
//
//
//
//   //virtual bool select_text_color(::user::interaction * pui, e_color ecolor = color_text);
//   //virtual bool select_solid_brush(::user::interaction * pui, e_color ecolor);
//   //virtual bool select_font(::user::interaction * pui, e_font efont = font_default);
//
//
//
//   //virtual COLORREF           _001GetColor(::user::interaction * pui, e_color ecolor, COLORREF crDefault = 0);
//   //virtual ::draw2d::font_sp  _001GetFont(::user::interaction * pui, e_font efont, ::draw2d::font * pfont = NULL);
//   //virtual e_translucency     _001GetTranslucency(::user::interaction * pui, e_element eelement = element_none, e_translucency etranslucencyDefault = translucency_undefined);
//   //virtual bool               _001GetFlag(::user::interaction * pui, ::user::e_flag eflag, bool bDefault = false);
//   //virtual RECT               _001GetRect(::user::interaction * pui, ::user::e_rect erect, rect rectDefault = ::null_rect());
//   //virtual int                _001GetInt(::user::interaction * pui, ::user::e_int eint, int iDefault = 0);
//   //virtual double             _001GetDouble(::user::interaction * pui, ::user::e_double edouble, double dDefault = 0.0);
//
//   //virtual bool _001IsBackgroundBypass(::user::interaction * pui, e_element eelement = element_none);
//   //virtual bool _001IsTransparent(::user::interaction * pui, e_element eelement = element_none);
//   //virtual bool _001IsTranslucent(::user::interaction * pui, e_element eelement = element_none);
//   //virtual bool _001HasTranslucency(::user::interaction * pui, e_element eelement = element_none);
//
//
//
//
//
//
//   //virtual ::user::style * userstyle() = 0;
//
//
//
//   //virtual void on_select_user_style();
//   //virtual ::user::style * parent_userstyle();
//   //virtual style * style_get(e_schema eschema) = 0;
//
//
//   //virtual ::draw2d::graphics * style_get_graphics();
//
//
//   //virtual bool userstyle_color(COLORREF & cr, e_color ecolor, ::user::interaction * pui);
//   //virtual bool userstyle_font(::draw2d::font_sp & sp, e_font efont, ::user::interaction * pui);
//   //virtual bool userstyle_translucency(e_translucency & etranslucency, e_element eelement, ::user::interaction * pui);
//   //virtual bool userstyle_flag(bool & bSet, ::user::e_flag eflag, ::user::interaction * pui);
//   //virtual bool userstyle_rect(RECT & rect, ::user::e_rect erect, ::user::interaction * pui);
//   //virtual bool userstyle_int(int & i, ::user::e_int eint, ::user::interaction * pui);
//   //virtual bool userstyle_double(double & d, ::user::e_double edouble, ::user::interaction * pui);
//
//
//   //virtual bool style_color(COLORREF & cr, e_color ecolor, ::user::interaction * pui);
//   //virtual bool style_font(::draw2d::font_sp & sp, e_font efont, ::user::interaction * pui);
//   //virtual bool style_translucency(e_translucency & etranslucency, e_element eelement, ::user::interaction * pui);
//   //virtual bool style_flag(bool & bSet, ::user::e_flag eflag, ::user::interaction * pui);
//   //virtual bool style_rect(RECT & rect, ::user::e_rect erect, ::user::interaction * pui);
//   //virtual bool style_int(int & i, ::user::e_int eint, ::user::interaction * pui);
//   //virtual bool style_double(double & d, ::user::e_double edouble, ::user::interaction * pui);
//
//   void theme::theme_current_control(e_control econtrol)
//   {
//
//      if (econtrol == control_none)
//      {
//
//         m_puserstyle = this;
//
//         return;
//
//      }
//
//      style_sp & pstyle = m_map[econtrol];
//
//      if (pstyle.is_null())
//      {
//
//         pstyle = canew(style(get_app()));
//
//      }
//
//      m_puserstyle = pstyle;
//
//   }
//
//
//   //::user::style * theme::userstyle()
//   //{
//
//   //   return m_puserstyleThemeCurrentSchema;
//
//   //}
//
//
} // namespace user



