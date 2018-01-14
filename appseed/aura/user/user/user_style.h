#pragma once


namespace user
{


   class CLASS_DECL_AURA style :
      virtual public style_composite
   {
      public:



         color_map                  m_mapColor;
         font_map                   m_mapFont;
         translucency_map           m_mapTranslucency;
         flag_map                   m_mapFlag;
         rect_map                   m_mapRect;
         ::user::int_map            m_mapInt;
         ::user::double_map         m_mapDouble;

         e_schema                   m_eschema;

         ::draw2d::graphics *       m_pgraphics;




         //bool                     m_bBorder;
         //COLORREF                 m_crTextNormal;
         //rect                     m_rectItemMargin;
         //int                      m_iElementPadding;



         style();
         style(::aura::application * papp);
         virtual ~style();


         virtual ::user::interaction * create_menu_button(::aura::application * papp) override;
         virtual bool prepare_menu(::user::menu_item * pitem) override;
         virtual bool prepare_menu_button(::user::menu_item * pitem) override;


         virtual void initialize_style_menu() override;
         virtual void initialize_style_button() override;
         virtual void initialize_style_menu_button() override;
         virtual void initialize_style_menu_popup() override;
         virtual void initialize_style_system_menu_button() override;
         virtual void initialize_style_system_menu_close() override;
         virtual void initialize_style_system_menu_popup() override;
         virtual void initialize_style() override;


         virtual bool _001OnDrawMainFrameBackground(::draw2d::graphics * pgraphics,::user::frame * pframe) override;

      virtual void DrawCheck(::check::e_check echeck, const RECT & rect, ::draw2d::graphics * pgraphics) override;

         virtual bool select_layered_frame();

         virtual bool simple_ui_draw_focus_rect(::user::interaction * pui,::draw2d::graphics * pgraphics) override;

         virtual bool on_ui_event(e_event eevent, e_object eobject, ::user::interaction * pui) override;

         virtual bool _001TabOnDrawSchema01(::draw2d::graphics * pgraphics,tab * ptab) override;

         virtual void _001OnTabPaneDrawTitle(::user::tab_pane & pane,::user::tab * ptab,::draw2d::graphics * pgraphics,LPCRECT lpcrect,::draw2d::brush_sp & brushText) override;

         virtual bool _001OnTabLayout(::user::tab * ptab) override;

//      virtual bool _001GetMainFrameTranslucency(::user::e_translucency & etranslucency) override;

         virtual void _001DrawCheckBox(::draw2d::graphics * pgraphics, LPCRECT lpcrectClient, ::check::e_check echeck) override;

         virtual bool _001DrawToolbarItem(::draw2d::graphics * pgraphics, int32_t iItem, ::user::toolbar * ptoolbar) override;

         virtual bool _001DrawSimpleScrollBar(::draw2d::graphics * pgraphics, simple_scroll_bar * pbar) override;

         virtual bool _001DrawScrollBar(::draw2d::graphics * pgraphics, ::user::scroll_bar * pbar) override;


         virtual bool get_color(COLORREF & cr, e_color eusercolor, ::user::interaction * pui) override;
         virtual bool get_font(::draw2d::font_sp & sp, e_font efont, ::user::interaction * pui) override;
         virtual bool get_translucency(e_translucency & etranslucency, e_element element, ::user::interaction * pui) override;
         virtual bool get_flag(bool & bSet, e_flag eflag, ::user::interaction * pui) override;
         virtual bool get_rect(RECT & rect, e_rect erect, ::user::interaction * pui) override;
         virtual bool get_int(int & i, e_int eint, ::user::interaction * pui) override;
         virtual bool get_double(double & d, e_double edouble, ::user::interaction * pui) override;


         virtual void select_default();


         virtual void set_user_schema(::user::e_schema eschema);
         virtual void select_user_schema();


         virtual void select(::draw2d::graphics * pgraphics);

         virtual void defer_create_user_schema(::user::e_schema eschema);
         virtual bool create_point_font(e_font efont, const char * pszFamilyName, double dFontSize, int iFontWeight = FW_NORMAL);
         virtual bool create_color(e_color eusercolor, COLORREF cr);
         virtual bool create_opaque_color(e_color eusercolor, COLORREF cr);
         virtual bool create_opaque_color(e_color eusercolor, ::e_color ecolor);
         virtual bool create_session_default_opaque_color(e_color eusercolor, uint64_t ui);
         virtual bool create_session_default_color(e_color eusercolor, BYTE bAlpha, uint64_t ui);
         virtual bool create_flag(e_flag eflag, bool bSet = true);
         virtual bool create_translucency(e_element eelement, e_translucency etranslucency);
         virtual bool create_rect(e_rect erect, LONG l, LONG t, LONG r, LONG b);
         virtual bool create_int(e_int eint, int i);


         virtual e_schema get_user_style() override;


         virtual ::draw2d::graphics * style_get_graphics() override;
         virtual style * style_get(e_schema eschema) override;

         virtual style * userstyle() override;


   };



} // namespace user




