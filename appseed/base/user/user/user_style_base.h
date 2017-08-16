#pragma once


namespace user
{

   
   class CLASS_DECL_BASE style :
      virtual public object
   {
   public:
      
      
      using style_map = ::map < e_style, e_style, sp(style) >;
      
      
      style_map               m_map;
      

      ::aura::library *       m_plibrary;

      
      style(::aura::application * papp = NULL);
      virtual ~style();
      
      
      virtual void initialize_style_menu();
      virtual void initialize_style_button();
      virtual void initialize_style_menu_button();
      virtual void initialize_style_menu_popup();
      virtual void initialize_style_system_menu_button();
      virtual void initialize_style_system_menu_close();
      virtual void initialize_style_system_menu_popup();
      virtual void initialize_style();

      
      style * get(e_style estyle)
      {
         
         if(estyle == style_default)
         {
            
            return this;
            
         }
         
         style * pstyle = m_map[estyle];
         
         if(pstyle == NULL)
         {
          
            return this;
            
         }
         
         return pstyle;
         
      }
  
      sp(style) & operator[](e_style estyle)
      {
         
         return m_map[estyle];
         
      }
      

      virtual bool select_layered_frame();
      
      
      virtual ::user::interaction * create_menu_button();
      
      virtual bool prepare_menu(::user::menu_item * pitem);
      
      virtual bool prepare_menu_button(::user::menu_item * pitem);
      

      virtual void DrawCheck(check::e_check echeck, const RECT & rect, ::draw2d::graphics * pgraphics);


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

      virtual bool select_text_color(::draw2d::graphics * pgraphics,e_color ecolor = color_text);
      virtual bool select_solid_brush(::draw2d::graphics * pgraphics,e_color ecolor);
      virtual bool select_font(::draw2d::graphics * pgraphics, e_font efont, ::user::interaction * pui);
      
      
      virtual bool get_color(COLORREF & cr,e_color ecolor);
      virtual bool get_font(::draw2d::font_sp & sp, e_font efont, ::user::interaction * pui);
      virtual bool get_translucency(ETranslucency & etranslucency);
      
      virtual COLORREF        _001GetColor(e_color ecolor, COLORREF crDefault);
      virtual COLORREF        _001GetColor(e_color ecolor);
      virtual ETranslucency   _001GetTranslucency(ETranslucency etranslucencyDefault = TranslucencyUndefined);
      
      virtual bool _001IsBackgroundBypass();
      virtual bool _001IsTransparent();
      virtual bool _001IsTranslucent();
      virtual bool _001HasTranslucency();
      
      virtual bool set_color(e_color ecolor, COLORREF cr);

      
   };
   

} // namespace user




