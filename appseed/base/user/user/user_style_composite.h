#pragma once


namespace user
{


   class CLASS_DECL_BASE style :
      virtual public style_base
   {
   public:
      
      
      using style_map = ::map < e_style, e_style, sp(style) >;
      
      style_map               m_map;
      
      ::aura::library *       m_plibrary;
      
      ::user::style_sp        m_puserstyle;

      
      style();
      virtual ~style();
      

      // these are style_base pure virtual functions
      // "implementation"
      // these are style_base pure virtual functions
      // composition
      // these function should be always be a composition
      // based on userstyle()
      virtual void initialize_style_menu() override;
      virtual void initialize_style_button() override;
      virtual void initialize_style_menu_button() override;
      virtual void initialize_style_menu_popup() override;
      virtual void initialize_style_system_menu_button() override;
      virtual void initialize_style_system_menu_close() override;
      virtual void initialize_style_system_menu_popup() override;
      virtual void initialize_style() override;
      virtual ::user::interaction * create_menu_button() override;
      virtual bool prepare_menu(::user::menu_item * pitem) override;
      virtual bool prepare_menu_button(::user::menu_item * pitem) override;
      virtual bool _001OnDrawMainFrameBackground(::draw2d::graphics * pgraphics,::user::frame_window * pframe) override;
      virtual void DrawCheck(check::e_check echeck, const RECT & rect, ::draw2d::graphics * pgraphics) override;
      virtual bool simple_ui_draw_focus_rect(::user::interaction * pui,::draw2d::graphics * pgraphics) override;
      virtual bool on_ui_event(e_event eevent, e_object eobject, ::user::interaction * pui) override;
      virtual bool _001TabOnDrawSchema01(::draw2d::graphics * pgraphics,tab * ptab) override;
      virtual void _001OnTabPaneDrawTitle(::user::tab_pane & pane,::user::tab * ptab,::draw2d::graphics * pgraphics,LPCRECT lpcrect,::draw2d::brush_sp & brushText) override;
      virtual bool _001OnTabLayout(::user::tab * ptab) override;
      virtual void _001DrawCheckBox(::draw2d::graphics * pgraphics, LPCRECT lpcrectClient, ::check::e_check echeck) override;
      virtual bool _001DrawToolbarItem(::draw2d::graphics * pgraphics, int32_t iItem, ::user::toolbar * ptoolbar) override;
      virtual bool _001DrawSimpleScrollBar(::draw2d::graphics * pgraphics, simple_scroll_bar * pbar) override;
      virtual bool _001DrawScrollBar(::draw2d::graphics * pgraphics, ::user::scroll_bar * pbar) override;
      
      virtual bool get_color(COLORREF & cr,e_color ecolor) override;
      virtual bool get_font(::draw2d::font_sp & sp, e_font efont, ::user::interaction * pui) override;
      virtual bool get_translucency(ETranslucency & etranslucency) override;

      virtual bool has_flag(::user::e_flag eflag) override;
      virtual rect get_rect(::user::e_rect erect) override;
      virtual int get_int(::user::e_int eint) override;
      
      
      
      // these are exception of rule above
      virtual style * get(e_style estyle) override;
      virtual sp(style) & operator[](e_style estyle) override;
     
      
      
      
      
      // these are utility functions
      // the utility functions should be based on this class functions
      // specially the style_base pure function overrides
      // that way, if some styled class overriding any style_base pure function
      // will affect the return of the utility function.
      // so, it should be very avoided using the m_pstylebase compositor
      // to implement the utility functions
      virtual bool _001GetMainFrameTranslucency(::user::ETranslucency & etranslucency);

      virtual bool select_text_color(::draw2d::graphics * pgraphics,e_color ecolor = color_text);
      virtual bool select_solid_brush(::draw2d::graphics * pgraphics,e_color ecolor);
      virtual bool select_font(::draw2d::graphics * pgraphics, e_font efont, ::user::interaction * pui);

      virtual COLORREF        _001GetColor(e_color ecolor, COLORREF crDefault);
      virtual COLORREF        _001GetColor(e_color ecolor);
      virtual ETranslucency   _001GetTranslucency(ETranslucency etranslucencyDefault = TranslucencyUndefined);
      
      virtual bool _001IsBackgroundBypass();
      virtual bool _001IsTransparent();
      virtual bool _001IsTranslucent();
      virtual bool _001HasTranslucency();
      

      
      
      

      // special utility functions
      // they are very suitable for style containers that contains that style
      // by deriving from this style class
      virtual ::user::style_base * userstyle();
      virtual ::user::style_base * parent_userstyle();
      virtual ::user::style_base * userstyle(::user::e_style estyle);


      
   };
   

} // namespace user




