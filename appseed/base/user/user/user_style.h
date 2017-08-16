#pragma once


namespace user
{

   
   class CLASS_DECL_BASE style_simple :
      virtual public style
   {
   public:
      
      
      
      color_map               m_mapColor;
      ::draw2d::font_sp       m_pfont;
      ETranslucency           m_etranslucency;
      bool                    m_bBorder;
      
      COLORREF                m_crTextNormal;
      //rect                    m_rectItemMargin;
      //int                     m_iElementPadding;
      
      flag_map                m_mapFlag;
      rect_map                m_mapRect;
      ::user::int_map         m_mapInt;
      


      
      style_simple(::aura::application * papp);
      virtual ~style_simple();
      
      
      
      virtual void initialize_style_menu();
      virtual void initialize_style_button();
      virtual void initialize_style_menu_button();
      virtual void initialize_style_menu_popup();
      virtual void initialize_style_system_menu_button();
      virtual void initialize_style_system_menu_close();
      virtual void initialize_style_system_menu_popup();
      virtual void initialize_style();

      
      
      virtual void DrawCheck(check::e_check echeck, const RECT & rect, ::draw2d::graphics * pgraphics);


      virtual ::user::interaction * create_menu_button();
      
      virtual bool prepare_menu(::user::menu_item * pitem);
      
      virtual bool prepare_menu_button(::user::menu_item * pitem);

      virtual bool select_layered_frame();

      virtual bool simple_ui_draw_focus_rect(::user::interaction * pui,::draw2d::graphics * pgraphics);

      virtual bool on_ui_event(e_event eevent, e_object eobject, ::user::interaction * pui);

      virtual bool _001TabOnDrawSchema01(::draw2d::graphics * pgraphics,tab * ptab);
      
      virtual void _001OnTabPaneDrawTitle(::user::tab_pane & pane,::user::tab * ptab,::draw2d::graphics * pgraphics,LPCRECT lpcrect,::draw2d::brush_sp & brushText);

      virtual bool _001OnTabLayout(::user::tab * ptab);

      virtual bool _001GetMainFrameTranslucency(::user::ETranslucency & etranslucency);

      virtual bool _001OnDrawMainFrameBackground(::draw2d::graphics * pgraphics,::user::frame_window * pframe);


      virtual void _001DrawCheckBox(::draw2d::graphics * pgraphics, LPCRECT lpcrectClient, ::check::e_check echeck);

      virtual bool _001DrawToolbarItem(::draw2d::graphics * pgraphics, int32_t iItem, ::user::toolbar * ptoolbar);

      virtual bool _001DrawSimpleScrollBar(::draw2d::graphics * pgraphics, simple_scroll_bar * pbar);

      virtual bool _001DrawScrollBar(::draw2d::graphics * pgraphics, ::user::scroll_bar * pbar);

      virtual bool set_color(e_color ecolor, COLORREF cr);

      
   };
   

} // namespace user




