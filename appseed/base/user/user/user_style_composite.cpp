//#include "framework.h" // from "base/user/user.h"


namespace user
{


   style_composite::style_composite()
   {

      m_plibrary           = NULL;

   }


   style_composite::~style_composite()
   {
      
      ::aura::del(m_plibrary);

   }
   
   
   void style_composite::initialize_style_menu()
   {
   
   }
   
   
   void style_composite::initialize_style_button()
   {
   
   }
   
   
   void style_composite::initialize_style_menu_button()
   {
      
   }
   
   
   void style_composite::initialize_style_menu_popup()
   {
   
   }
   

   void style_composite::initialize_style_system_menu_button()
   {
      
   }
   

   void style_composite::initialize_style_system_menu_close()
   {
      
   }
   
   
   void style_composite::initialize_style_system_menu_popup()
   {
      
   }
   
   
   void style_composite::initialize_style()
   {
      
      m_map[style_menu].alloc(allocer());
      m_map[style_button].alloc(allocer());
      m_map[style_menu_button].alloc(allocer());
      m_map[style_menu_popup].alloc(allocer());
      m_map[style_system_menu_button].alloc(allocer());
      m_map[style_system_menu_popup].alloc(allocer());
      
      m_map[style_menu]->initialize_style_menu();
      m_map[style_button]->initialize_style_button();
      m_map[style_menu_button]->initialize_style_menu_button();
      m_map[style_menu_popup]->initialize_style_menu_popup();
      m_map[style_system_menu_button]->initialize_style_system_menu_button();
      m_map[style_system_menu_popup]->initialize_style_system_menu_popup();

   }
   
   
//   style * style_composite::style_get(e_style estyle)
//   {
//      
//      return userstyle()->get(estyle);
//   
//   }

   
   ::user::interaction * style_composite::create_menu_button()
   {

      return userstyle()->create_menu_button();
   
   }
   
   
   bool style_composite::prepare_menu(::user::menu_item * pitem)
   {
      
      return userstyle()->prepare_menu(pitem);
   
   }

   bool style_composite::prepare_menu_button(::user::menu_item * pitem)
   {

      return userstyle()->prepare_menu_button(pitem);
   
   }

   
   bool style_composite::_001OnDrawMainFrameBackground(::draw2d::graphics * pgraphics,::user::frame_window * pframe)
   {
      
      return userstyle()->_001OnDrawMainFrameBackground(pgraphics, pframe);
      
   }
   
   
   
   void style_composite::DrawCheck(check::e_check echeck, const RECT & rect, ::draw2d::graphics * pgraphics)
   {

      return userstyle()->DrawCheck(echeck, rect, pgraphics);
   
   }

   
   bool style_composite::simple_ui_draw_focus_rect(::user::interaction * pui,::draw2d::graphics * pgraphics)
   {

      return userstyle()->simple_ui_draw_focus_rect(pui, pgraphics);
   
   }
   

   bool style_composite::on_ui_event(e_event eevent, e_object eobject, ::user::interaction * pui)
   {

      return userstyle()->on_ui_event(eevent, eobject, pui);
   
   }
   
   
   bool style_composite::_001TabOnDrawSchema01(::draw2d::graphics * pgraphics,tab * ptab)
   {

      return userstyle()->_001TabOnDrawSchema01(pgraphics, ptab);
   
   }
   

   void style_composite::_001OnTabPaneDrawTitle(::user::tab_pane & pane,::user::tab * ptab,::draw2d::graphics * pgraphics,LPCRECT lpcrect,::draw2d::brush_sp & brushText)
   {

      return userstyle()->_001OnTabPaneDrawTitle(pane, ptab, pgraphics, lpcrect, brushText);
   
   }

   
   bool style_composite::_001OnTabLayout(::user::tab * ptab)
   {

      return userstyle()->_001OnTabLayout(ptab);
   
   }
   

   void style_composite::_001DrawCheckBox(::draw2d::graphics * pgraphics, LPCRECT lpcrectClient, ::check::e_check echeck)
   {

      return userstyle()->_001DrawCheckBox(pgraphics, lpcrectClient, echeck);
   
   }
   

   bool style_composite::_001DrawToolbarItem(::draw2d::graphics * pgraphics, int32_t iItem, ::user::toolbar * ptoolbar)
   {

      return userstyle()->_001DrawToolbarItem(pgraphics, iItem, ptoolbar);
   
   }

   
   bool style_composite::_001DrawSimpleScrollBar(::draw2d::graphics * pgraphics, simple_scroll_bar * pbar)
   {
      
      return userstyle()->_001DrawSimpleScrollBar(pgraphics, pbar);
   
   }

   
   bool style_composite::_001DrawScrollBar(::draw2d::graphics * pgraphics, ::user::scroll_bar * pbar)
   {
      
      return userstyle()->_001DrawScrollBar(pgraphics, pbar);
   
   }
   
   
   bool style_composite::get_color(COLORREF & cr,e_color ecolor)
   {
      
      return userstyle()->get_color(cr, ecolor);
   
   }
   
   
   bool style_composite::get_font(::draw2d::font_sp & font, e_font efont)
   {

      return userstyle()->get_font(font, efont);
   
   }
   

   bool style_composite::get_translucency(e_translucency & etranslucency, e_element eelement)
   {
   
      return userstyle()->get_translucency(etranslucency, eelement);
   
   }
   
   
   bool style_composite::has_flag(e_flag eflag)
   {
      
      
      return userstyle()->has_flag(eflag);
   
   }
   
   
   rect style_composite::get_rect(e_rect erect)
   {

      return userstyle()->get_rect(erect);
   
   }
   

   int style_composite::get_int(e_int eint)
   {
      
      return userstyle()->get_int(eint);
   
   }


   bool style_composite::select_text_color(::draw2d::graphics * pgraphics,e_color ecolor)
   {
   
      COLORREF cr;
   
      if(!style_color(cr, ecolor))
      {
      
         return false;
      
      }
   
      pgraphics->set_text_color(cr);
   
      return true;
   
   }


   bool style_composite::select_solid_brush(::draw2d::graphics * pgraphics,e_color ecolor)
   {
   
      COLORREF cr;
   
      if(!style_color(cr, ecolor))
      {
      
         return false;
      
      }
   
      ::draw2d::brush_sp brush(allocer());
   
      brush->create_solid(cr);
   
      pgraphics->SelectObject(brush);
   
      return true;
   
   }


   bool style_composite::select_font(::draw2d::graphics * pgraphics, e_font efont)
   {
   
      ::draw2d::font_sp font;
   
      if(!style_font(font, efont))
      {
      
         font.alloc(allocer());
      
         if (!font->create_point_font(FONT_SANS, 12.0))
         {
         
            return false;
         
         }
      
      }
   
      pgraphics->select_font(font);
   
      return true;
   
   }

   
   bool style_composite::select_text_color(e_color ecolor)
   {
      
      ::draw2d::graphics * pgraphics = style_get_graphics();
      
      if(pgraphics == NULL)
      {
         
         return false;
         
      }
      
      return select_text_color(pgraphics, ecolor);
      
   }
   
   
   bool style_composite::select_solid_brush(e_color ecolor)
   {
      
      ::draw2d::graphics * pgraphics = style_get_graphics();
      
      if(pgraphics == NULL)
      {
         
         return false;
         
      }
      
      return select_solid_brush(pgraphics, ecolor);
      
   }
   
   
   bool style_composite::select_font(e_font efont)
   {
      
      ::draw2d::graphics * pgraphics = style_get_graphics();
      
      if(pgraphics == NULL)
      {
         
         return false;
         
      }
      
      return select_font(pgraphics, efont);
      
   }
   
   

   COLORREF style_composite::_001GetColor(e_color ecolor, COLORREF crDefault)
   {
   
      COLORREF cr;
   
      if (get_color(cr, ecolor))
         return cr;
   
      return crDefault;
   
   }


//   COLORREF style_composite::_001GetColor(e_color ecolor, COLORREF crDefault)
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


   COLORREF style_composite::_001GetColor(e_color ecolor)
   {
   
      COLORREF cr;
   
      if (get_color(cr, ecolor))
         return cr;
   
      return 0;
   
   }
   
   
   e_translucency style_composite::_001GetTranslucency(e_element eelement, e_translucency etranslucencyDefault)
   {
      
      e_translucency etranslucency = translucency_undefined;
      
      if (get_translucency(etranslucency, eelement))
      {
         
         if (etranslucency != translucency_undefined)
         {
            
            return etranslucency;
            
         }
         
      }
      
      return etranslucencyDefault;
      
   }
   
   
   bool style_composite::_001IsTranslucent(e_element eelement)
   {
      
      e_translucency etranslucency = _001GetTranslucency(eelement);
      
      return etranslucency == translucency_present || etranslucency == translucency_total;
      
   }
   
   
   bool style_composite::_001IsBackgroundBypass(e_element eelement)
   {
      
      return _001GetTranslucency(eelement) == translucency_total;
      
   }
   
   
   bool style_composite::_001HasTranslucency(e_element eelement)
   {
      
      e_translucency etranslucency = _001GetTranslucency(eelement);
      
      return etranslucency == translucency_present || etranslucency == translucency_total;
      
   }
   
   
   bool style_composite::_001IsTransparent(e_element eelement)
   {
      
      return _001GetTranslucency(eelement) == translucency_total;
      
   }
   
   
   


   void style_composite::on_select_userstyle()
   {
   
      e_style estyle = get_style();
   
      sp(::user::style) puserstyle = Session.m_puserstyle;
   
      if(puserstyle == NULL)
      {
      
         puserstyle = Application.m_puserstyle;
      
         if(puserstyle == NULL)
         {
         
            puserstyle = Session.m_puserstyle;
            
            if(puserstyle == NULL)
            {
            
               puserstyle = canew(style(get_app()));
               
            }
            
         }
         
      }
      
      if(estyle == style_default)
      {
    
         m_puserstyle = puserstyle;
      
      }
      else
      {
      
         sp(::user::style) puserstyleNext = puserstyle->style_get(estyle);
      
         if(puserstyleNext.is_set())
         {
      
            m_puserstyle = puserstyleNext;
         
         }
         else
         {
         
            m_puserstyle = puserstyle;
         
         }
      
      }
   
   }


   ::user::style_base * style_composite::parent_userstyle()
   {
   
      return NULL;
   
   }




   bool style_composite::style_color(COLORREF & cr,e_color ecolor)
   {
   
      return userstyle()->get_color(cr, ecolor);
   
   }


   bool style_composite::style_font(::draw2d::font_sp & font, e_font efont)
   {
   
      return userstyle()->get_font(font, efont);
   
   }


   bool style_composite::style_translucency(e_translucency & etranslucency, e_element eelement)
   {
   
      return userstyle()->get_translucency(etranslucency, eelement);
   
   }


   bool style_composite::style_flag(e_flag eflag)
   {
   
      return userstyle()->has_flag(eflag);
   
   }


   rect style_composite::style_rect(e_rect erect)
   {
   
      return userstyle()->get_rect(erect);
   
   }


   int style_composite::style_int(e_int eint)
   {
   
      return userstyle()->get_int(eint);
   
   }

   
   ::draw2d::graphics * style_composite::style_get_graphics()
   {
      
      return NULL;
      
   }

   
   
   
} // namespace user











