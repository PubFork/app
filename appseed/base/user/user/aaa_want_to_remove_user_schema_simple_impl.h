#pragma once


namespace user
{


   class CLASS_DECL_BASE schema_simple_impl:
      virtual public ::user::style
   {
   public:


      map < e_color,e_color,COLORREF,COLORREF >       m_mapColor;
      ::draw2d::font_sp                               m_pfont;
      e_translucency                                   m_etranslucency;


      schema_simple_impl(::aura::application * papp);
      virtual ~schema_simple_impl();

      
      virtual bool prepare_menu_button(::user::menu_item * pitem) override;

      virtual bool get_color(COLORREF & cr, e_color ecolor) override;
      virtual bool get_font(::draw2d::font_sp & font, e_font efont, ::user::interaction * pui) override;
      virtual bool get_translucency(e_translucency & etranslucency) override;
      virtual bool on_ui_event(e_event eevent, e_object eobject, ::user::interaction * pui) override;


      virtual bool set_color(e_color ecolor, COLORREF cr);

   };


} // namespace user





