#pragma once


namespace user
{


   class CLASS_DECL_AURA style :
      virtual public style_base
   {
   public:


      sp(color_map)              m_mapColor;
      sp(font_map)               m_mapFont;
      sp(translucency_map)       m_mapTranslucency;
      sp(flag_map)               m_mapFlag;
      sp(rect_map)               m_mapRect;
      sp(::user::int_map)        m_mapInt;
      sp(::user::double_map)     m_mapDouble;

      ::user::style *            m_puserstyle;

      ::draw2d::graphics *       m_pgraphics;


      //bool                     m_bBorder;
      //COLORREF                 m_crTextNormal;
      //rect                     m_rectItemMargin;
      //int                      m_iElementPadding;



      style();
      style(::aura::application * papp);
      virtual ~style();

      void default_style_construct();

      virtual ::user::menu_interaction * create_menu_button(menu_item * pitem) override;
      virtual bool prepare_menu(::user::menu_item * pitem) override;
      virtual bool prepare_menu_button(::user::menu_item * pitem) override;


//      virtual void initialize_style() override;


      virtual bool _001OnDrawMainFrameBackground(::draw2d::graphics * pgraphics,::user::frame * pframe) override;

      virtual void DrawCheck(::check::e_check echeck, const RECT & rect, ::draw2d::graphics * pgraphics) override;

      virtual bool select_layered_frame();

      virtual bool simple_ui_draw_focus_rect(::user::interaction * pui,::draw2d::graphics * pgraphics) override;

      virtual bool on_ui_event(e_event eevent, e_object eobject, ::user::interaction * pui) override;

      virtual bool _001TabOnDrawSchema01(::draw2d::graphics * pgraphics,tab * ptab) override;

      virtual bool _001OnDrawMenuInteraction(::draw2d::graphics * pgraphics, menu_interaction * pbutton) override;

      virtual void _001OnTabPaneDrawTitle(::user::tab_pane & pane,::user::tab * ptab,::draw2d::graphics * pgraphics,LPCRECT lpcrect,::draw2d::brush_sp & brushText) override;

      virtual bool _001OnTabLayout(::user::tab * ptab) override;

//      virtual bool _001GetMainFrameTranslucency(::user::e_translucency & etranslucency) override;

      virtual void _001DrawCheckBox(::draw2d::graphics * pgraphics, LPCRECT lpcrectClient, ::check::e_check echeck) override;

      virtual bool _001DrawToolbarItem(::draw2d::graphics * pgraphics, int32_t iItem, ::user::toolbar * ptoolbar) override;

      virtual bool _001DrawSimpleScrollBar(::draw2d::graphics * pgraphics, simple_scroll_bar * pbar) override;

      virtual bool _001DrawScrollBar(::draw2d::graphics * pgraphics, ::user::scroll_bar * pbar) override;


      // these are utility functions
      // the utility functions should be based on this class functions
      // specially the style_base pure function overrides
      // that way, if some styled class overriding any style_base pure function
      // will affect the return of the utility function.
      // so, it should be very avoided using the m_pstylebase compositor
      // to implement the utility functions
      //virtual bool _001GetMainFrameTranslucency(::user::e_translucency & etranslucency);

      virtual bool select_text_color(::user::interaction * pui, ::draw2d::graphics * pgraphics, e_color ecolor = color_text);
      virtual bool select_solid_brush(::user::interaction * pui, ::draw2d::graphics * pgraphics, e_color ecolor);
      virtual bool select_font(::user::interaction * pui, ::draw2d::graphics * pgraphics, e_font efont = font_default);



      virtual bool select_text_color(::user::interaction * pui, e_color ecolor = color_text);
      virtual bool select_solid_brush(::user::interaction * pui, e_color ecolor);
      virtual bool select_font(::user::interaction * pui, e_font efont = font_default);



      virtual COLORREF           _001GetColor(::user::interaction * pui, e_color ecolor, COLORREF crDefault = 0);
      virtual ::draw2d::font_sp  _001GetFont(::user::interaction * pui, e_font efont, ::draw2d::font * pfont = NULL);
      virtual e_translucency     _001GetTranslucency(::user::interaction * pui, e_element eelement = element_none, e_translucency etranslucencyDefault = translucency_undefined);
      virtual bool               _001GetFlag(::user::interaction * pui, ::user::e_flag eflag, bool bDefault = false);
      virtual RECT               _001GetRect(::user::interaction * pui, ::user::e_rect erect, rect rectDefault = ::null_rect());
      virtual int                _001GetInt(::user::interaction * pui, ::user::e_int eint, int iDefault = 0);
      virtual double             _001GetDouble(::user::interaction * pui, ::user::e_double edouble, double dDefault = 0.0);

      virtual bool _001IsBackgroundBypass(::user::interaction * pui, e_element eelement = element_none);
      virtual bool _001IsTransparent(::user::interaction * pui, e_element eelement = element_none);
      virtual bool _001IsTranslucent(::user::interaction * pui, e_element eelement = element_none);
      virtual bool _001HasTranslucency(::user::interaction * pui, e_element eelement = element_none);




      virtual bool get_color(COLORREF & cr, e_color eusercolor, style_context * pcontext) override;
      virtual bool get_font(::draw2d::font_sp & sp, e_font efont, style_context * pcontext) override;
      virtual bool get_translucency(e_translucency & etranslucency, e_element element, style_context * pcontext) override;
      virtual bool get_flag(bool & bSet, e_flag eflag, style_context * pcontext) override;
      virtual bool get_rect(RECT & rect, e_rect erect, style_context * pcontext) override;
      virtual bool get_int(int & i, e_int eint, style_context * pcontext) override;
      virtual bool get_double(double & d, e_double edouble, style_context * pcontext) override;


      //virtual void select_default();


//      virtual void set_user_schema(::user::e_schema eschema);
      //    virtual void select_user_schema();


      virtual void select(::draw2d::graphics * pgraphics);

      //virtual void defer_create_user_schema(::user::e_schema eschema);
      virtual bool create_point_font(e_font efont, const char * pszFamilyName, double dFontSize, int iFontWeight = FW_NORMAL);
      virtual bool create_color(e_color eusercolor, COLORREF cr);
      virtual bool create_opaque_color(e_color eusercolor, COLORREF cr);
      virtual bool create_opaque_color(e_color eusercolor, ::e_color ecolor);
      virtual bool create_session_default_opaque_color(e_color eusercolor, uint64_t ui);
      virtual bool create_session_default_color(e_color eusercolor, BYTE bAlpha, uint64_t ui);
      virtual bool create_flag(e_flag eflag, bool bSet = true);
      virtual bool create_translucency(e_element eelement, e_translucency etranslucency);
      virtual bool create_rect_coord(e_rect erect, LONG l, LONG t, LONG r, LONG b);
      virtual bool create_rect_dim(e_rect erect, LONG l, LONG t, LONG r, LONG b);
      virtual bool create_rect(e_rect erect, LPCRECT lpcrect);
      virtual bool create_int(e_int eint, int i);


      virtual e_control_type get_control_type() override;


      virtual ::draw2d::graphics * style_get_graphics();

      virtual void nextstyle(style_context * pcontext);

      virtual style * userstyle();


   };



} // namespace user




