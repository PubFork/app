#include "framework.h" // from "base/user/user.h"


namespace user
{


   style_composite::style_composite()
   {

      m_puserstyleSelect = NULL;

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

      m_map[schema_menu].alloc(allocer());
      m_map[schema_button].alloc(allocer());
      m_map[schema_menu_button].alloc(allocer());
      m_map[schema_menu_popup].alloc(allocer());
      m_map[schema_system_menu_button].alloc(allocer());
      m_map[schema_system_menu_popup].alloc(allocer());

      m_map[schema_menu]->initialize_style_menu();
      m_map[schema_button]->initialize_style_button();
      m_map[schema_menu_button]->initialize_style_menu_button();
      m_map[schema_menu_popup]->initialize_style_menu_popup();
      m_map[schema_system_menu_button]->initialize_style_system_menu_button();
      m_map[schema_system_menu_popup]->initialize_style_system_menu_popup();

   }


//   style * style_composite::style_get(e_style estyle)
//   {
//
//      return userstyle()->get(estyle);
//
//   }


   ::user::interaction * style_composite::create_menu_button(::aura::application * papp)
   {

      return userstyle()->create_menu_button(papp);

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




   bool style_composite::select_text_color(::user::interaction * pui, ::draw2d::graphics * pgraphics, e_color ecolor)
   {

      COLORREF cr;

      if(!style_color(cr, ecolor, pui))
      {

         return false;

      }

      pgraphics->set_text_color(cr);

      return true;

   }


   bool style_composite::select_solid_brush(::user::interaction * pui, ::draw2d::graphics * pgraphics, e_color ecolor)
   {

      COLORREF cr;

      if(!style_color(cr, ecolor, pui))
      {

         return false;

      }

      ::draw2d::brush_sp brush(allocer());

      brush->create_solid(cr);

      pgraphics->SelectObject(brush);

      return true;

   }


   bool style_composite::select_font(::user::interaction * pui, ::draw2d::graphics * pgraphics, e_font efont)
   {

      ::draw2d::font_sp font;

      if(!style_font(font, efont, pui))
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


   bool style_composite::select_text_color(::user::interaction * pui, e_color ecolor)
   {

      ::draw2d::graphics * pgraphics = style_get_graphics();

      if(pgraphics == NULL)
      {

         return false;

      }

      return select_text_color(pui, pgraphics, ecolor);

   }


   bool style_composite::select_solid_brush(::user::interaction * pui, e_color ecolor)
   {

      ::draw2d::graphics * pgraphics = style_get_graphics();

      if(pgraphics == NULL)
      {

         return false;

      }

      return select_solid_brush(pui, pgraphics, ecolor);

   }


   bool style_composite::select_font(::user::interaction * pui, e_font efont)
   {

      ::draw2d::graphics * pgraphics = style_get_graphics();

      if(pgraphics == NULL)
      {

         return false;

      }

      return select_font(pui, pgraphics, efont);

   }



   COLORREF style_composite::_001GetColor(::user::interaction * pui, e_color ecolor, COLORREF crDefault)
   {

      COLORREF cr;

      if (style_color(cr, ecolor, pui))
         return cr;

      return crDefault;

   }


   ::draw2d::font_sp style_composite::_001GetFont(::user::interaction * pui, e_font efont, ::draw2d::font * pfont)
   {

      ::draw2d::font_sp font;

      if (style_font(font, efont, pui))
         return font;

      if (pfont == NULL)
      {

         font.alloc(allocer());

         font->create_pixel_font(FONT_SANS, 9.0);

         return font;

      }

      return pfont;

   }


   e_translucency style_composite::_001GetTranslucency(::user::interaction * pui, e_element eelement, e_translucency etranslucencyDefault)
   {

      e_translucency etranslucency = translucency_undefined;

      if (style_translucency(etranslucency, eelement, pui))
      {

         if (etranslucency != translucency_undefined)
         {

            return etranslucency;

         }

      }

      return etranslucencyDefault;

   }


   bool style_composite::_001GetFlag(::user::interaction * pui, e_flag eflag, bool bDefault)
   {

      bool bSet = bDefault;

      if (style_flag(bSet, eflag, pui))
         return bSet;

      return bDefault;

   }


   RECT style_composite::_001GetRect(::user::interaction * pui, e_rect erect, rect rectDefault)
   {

      ::rect rect(rectDefault);

      if (style_rect(rect, erect, pui))
         return rect;

      return rectDefault;

   }


   int style_composite::_001GetInt(::user::interaction * pui, e_int eint, int iDefault)
   {

      int i = iDefault;

      if (style_int(i, eint, pui))
         return i;

      return iDefault;

   }


   double style_composite::_001GetDouble(::user::interaction * pui, e_double edouble, double dDefault)
   {

      double d = dDefault;

      if (style_double(d, edouble, pui))
         return d;

      return dDefault;

   }


   bool style_composite::_001IsTranslucent(::user::interaction * pui, e_element eelement)
   {

      e_translucency etranslucency = _001GetTranslucency(pui, eelement);

      return etranslucency == translucency_present || etranslucency == translucency_total;

   }


   bool style_composite::_001IsBackgroundBypass(::user::interaction * pui, e_element eelement)
   {

      return _001GetTranslucency(pui, eelement) == translucency_total;

   }


   bool style_composite::_001HasTranslucency(::user::interaction * pui, e_element eelement)
   {

      e_translucency etranslucency = _001GetTranslucency(pui, eelement);

      return etranslucency == translucency_present || etranslucency == translucency_total;

   }


   bool style_composite::_001IsTransparent(::user::interaction * pui, e_element eelement)
   {

      return _001GetTranslucency(pui, eelement) == translucency_total;

   }





   void style_composite::on_select_user_style()
   {

      e_schema eschema = get_user_style();

      sp(::user::style) puserstyle = m_puserstyle;

      if (puserstyle.is_null())
      {

         puserstyle = Session.m_puserstyle;

         if (puserstyle == NULL)
         {

            puserstyle = Application.m_puserstyle;

            if (puserstyle == NULL)
            {

               puserstyle = Session.m_puserstyle;

               if (puserstyle == NULL)
               {

                  puserstyle = canew(style(get_app()));

               }

            }

         }

      }

      if(eschema == schema_default)
      {

         m_puserstyleSelect = puserstyle;

      }
      else
      {

         sp(::user::style) puserstyleNext = puserstyle->style_get(eschema);

         if(puserstyleNext.is_set())
         {

            m_puserstyleSelect = puserstyleNext;

         }
         else
         {

            m_puserstyleSelect = puserstyle;

         }

      }

   }


   ::user::style * style_composite::parent_userstyle()
   {

      return NULL;

   }




   bool style_composite::style_color(COLORREF & cr, e_color ecolor, ::user::interaction * pui)
   {

      if (pui->get_color(cr, ecolor, pui))
      {

         return true;

      }

      ::user::frame_window * pframe = pui->GetParentFrame();

      while (pframe != NULL)
      {

         if (pframe->get_color(cr, ecolor, pui))
         {

            return true;

         }

         pframe = pframe->GetParentFrame();

      }

      pframe = pui->GetOwnerFrame();

      while (pframe != NULL)
      {

         if (pframe->get_color(cr, ecolor, pui))
         {

            return true;

         }

         pframe = pframe->GetParentFrame();

      }

      if (get_color(cr, ecolor, pui))
      {

         return true;

      }

      return userstyle_color(cr, ecolor, pui);

   }


   bool style_composite::style_font(::draw2d::font_sp & font, e_font efont, ::user::interaction * pui)
   {


      if (pui->get_font(font, efont, pui))
      {

         return true;

      }

      ::user::frame_window * pframe = pui->GetParentFrame();

      while (pframe != NULL)
      {

         if (pframe->get_font(font, efont, pui))
         {

            return true;

         }

         pframe = pframe->GetParentFrame();

      }

      pframe = pui->GetOwnerFrame();

      while (pframe != NULL)
      {

         if (pframe->get_font(font, efont, pui))
         {

            return true;

         }

         pframe = pframe->GetParentFrame();

      }

      if (get_font(font, efont, pui))
      {

         return true;

      }

      return userstyle_font(font, efont, pui);

   }


   bool style_composite::style_translucency(e_translucency & etranslucency, e_element eelement, ::user::interaction * pui)
   {


      if (pui->get_translucency(etranslucency, eelement, pui))
      {

         return true;

      }

      ::user::frame_window * pframe = pui->GetParentFrame();

      while (pframe != NULL)
      {

         if (pframe->get_translucency(etranslucency, eelement, pui))
         {

            return true;

         }

         pframe = pframe->GetParentFrame();

      }

      pframe = pui->GetOwnerFrame();

      while (pframe != NULL)
      {

         if (pframe->get_translucency(etranslucency, eelement, pui))
         {

            return true;

         }

         pframe = pframe->GetParentFrame();

      }

      if (get_translucency(etranslucency, eelement, pui))
      {

         return true;

      }

      return userstyle_translucency(etranslucency, eelement, pui);

   }


   bool style_composite::style_flag(bool & bSet, e_flag eflag, ::user::interaction * pui)
   {

      if (pui->get_flag(bSet, eflag, pui))
      {

         return true;

      }

      ::user::frame_window * pframe = pui->GetParentFrame();

      while (pframe != NULL)
      {

         if (pframe->get_flag(bSet, eflag, pui))
         {

            return true;

         }

         pframe = pframe->GetParentFrame();

      }

      pframe = pui->GetOwnerFrame();

      while (pframe != NULL)
      {

         if (pframe->get_flag(bSet, eflag, pui))
         {

            return true;

         }

         pframe = pframe->GetParentFrame();

      }

      if (get_flag(bSet, eflag, pui))
      {

         return true;

      }

      return userstyle_flag(bSet, eflag, pui);

   }


   bool style_composite::style_rect(RECT & rect, e_rect erect, ::user::interaction * pui)
   {

      if (pui->get_rect(rect, erect, pui))
      {

         return true;

      }

      ::user::frame_window * pframe = pui->GetParentFrame();

      while (pframe != NULL)
      {

         if (pframe->get_rect(rect, erect, pui))
         {

            return true;

         }

         pframe = pframe->GetParentFrame();

      }

      pframe = pui->GetOwnerFrame();

      while (pframe != NULL)
      {

         if (pframe->get_rect(rect, erect, pui))
         {

            return true;

         }

         pframe = pframe->GetParentFrame();

      }

      if (get_rect(rect, erect, pui))
      {

         return true;

      }

      return userstyle_rect(rect, erect, pui);

   }


   bool style_composite::style_int(int & i, e_int eint, ::user::interaction * pui)
   {

      if (pui->get_int(i, eint, pui))
      {

         return true;

      }

      ::user::frame_window * pframe = pui->GetParentFrame();

      while (pframe != NULL)
      {

         if (pframe->get_int(i, eint, pui))
         {

            return true;

         }

         pframe = pframe->GetParentFrame();

      }

      pframe = pui->GetOwnerFrame();

      while (pframe != NULL)
      {

         if (pframe->get_int(i, eint, pui))
         {

            return true;

         }

         pframe = pframe->GetParentFrame();

      }

      if (get_int(i, eint, pui))
      {

         return true;

      }

      return userstyle_int(i, eint, pui);

   }


   bool style_composite::style_double(double & d, e_double edouble, ::user::interaction * pui)
   {

      if (pui->get_double(d, edouble, pui))
      {

         return true;

      }

      ::user::frame_window * pframe = pui->GetParentFrame();

      while (pframe != NULL)
      {

         if (pframe->get_double(d, edouble, pui))
         {

            return true;

         }

         pframe = pframe->GetParentFrame();

      }

      pframe = pui->GetOwnerFrame();

      while (pframe != NULL)
      {

         if (pframe->get_double(d, edouble, pui))
         {

            return true;

         }

         pframe = pframe->GetParentFrame();

      }

      if (get_double(d, edouble, pui))
      {

         return true;

      }

      return userstyle_double(d, edouble, pui);

   }


   bool style_composite::userstyle_color(COLORREF & cr, e_color ecolor, ::user::interaction * pui)
   {

      ::user::style * puserstyle = userstyle();

      if (puserstyle != NULL && puserstyle->get_color(cr, ecolor, pui))
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
      else if (ecolor == color_background_highlight)
      {

         cr = ARGB(100, 110, 150, 255);

      }
      else if (ecolor == color_text_selected_highlight)
      {

         cr = ARGB(255, 102, 153, 255);

      }
      else if (ecolor == color_background_selected_highlight)
      {

         cr = ARGB(100, 80, 100, 200);

      }
      else if (ecolor == color_background)
      {

         if (_001IsTranslucent(pui))
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

         if (_001IsTranslucent(pui))
         {

            cr = ARGB(120, 0, 0, 0);

         }
         else
         {

            cr = ARGB(255, 80, 80, 80);

         }

      }
      else if (ecolor == color_face_lite)
      {

         if (_001IsTranslucent(pui))
         {

            cr = ARGB(80, 0, 0, 0);

         }
         else
         {

            cr = ARGB(255, 120, 120, 120);

         }

      }
      else if (ecolor == color_tab_layout_background)
      {

         if (_001IsTranslucent(pui))
         {

            cr = ARGB(80, 255, 255, 255);

         }
         else
         {

            cr = ARGB(255, 255, 255, 255);

         }

      }
      else if (ecolor == color_tab_client_background)
      {

         if (_001IsTranslucent(pui))
         {

            cr = ARGB(0, 0, 0, 0);

         }
         else
         {

            cr = ARGB(255, 255, 255, 255);

         }

      }
      else if (ecolor == color_background_selected)
      {

         if (_001IsTranslucent(pui))
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

         if (_001IsTranslucent(pui))
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

         cr = ARGB(255, 84, 90, 80);

      }
      else if (ecolor == color_border_hover)
      {

         cr = ARGB(255, 84, 190, 80);

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
      else if (ecolor == color_background_press)
      {

         cr = ARGB(255, 215, 200, 255);

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

         return get_color(cr, color_background_disabled, pui);

      }
      else if (ecolor == color_button_background_hover)
      {

         return get_color(cr, color_background_hover, pui);

      }
      else if (ecolor == color_button_background_normal)
      {

         return get_color(cr, color_background_normal, pui);

      }
      else if (ecolor == color_button_background_press)
      {

         return get_color(cr, color_background_press, pui);

      }
      else if (ecolor == color_button_text_disabled)
      {

         return get_color(cr, color_text_disabled, pui);

      }
      else if (ecolor == color_button_text_hover)
      {

         return get_color(cr, color_text_hover, pui);

      }
      else if (ecolor == color_button_text_normal)
      {

         return get_color(cr, color_text_normal, pui);

      }
      else if (ecolor == color_button_text_press)
      {

         return get_color(cr, color_text_press, pui);

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
      else if (ecolor == color_split_layout_background)
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
      else if (ecolor == color_action_hover_border_color)
      {

         cr = ARGB(255, 83, 104, 255);

      }
      else
      {

         throw invalid_argument_exception(::get_thread_app());

         return false;

      }

      return true;

   }


   bool style_composite::userstyle_font(::draw2d::font_sp & font, e_font efont, ::user::interaction * pui)
   {

      ::user::style * puserstyle = userstyle();

      if (puserstyle != NULL && puserstyle->get_font(font, efont, pui))
      {

         return true;

      }

      return false;

   }


   bool style_composite::userstyle_translucency(e_translucency & etranslucency, e_element eelement, ::user::interaction * pui)
   {

      ::user::style * puserstyle = userstyle();

      if (puserstyle != NULL && puserstyle->get_translucency(etranslucency, eelement, pui))
      {

         return true;

      }

      return false;

   }


   bool style_composite::userstyle_flag(bool & bSet, e_flag eflag, ::user::interaction * pui)
   {

      ::user::style * puserstyle = userstyle();

      if (puserstyle != NULL && puserstyle->get_flag(bSet, eflag, pui))
      {

         return true;

      }

      return false;

   }


   bool style_composite::userstyle_rect(RECT & rect, e_rect erect, ::user::interaction * pui)
   {

      ::user::style * puserstyle = userstyle();

      if (puserstyle != NULL && puserstyle->get_rect(rect, erect, pui))
      {

         return true;

      }

      return false;

   }


   bool style_composite::userstyle_int(int & i, e_int eint, ::user::interaction * pui)
   {

      ::user::style * puserstyle = userstyle();

      if (puserstyle != NULL && puserstyle->get_int(i, eint, pui))
      {

         return true;

      }

      return false;

   }


   bool style_composite::userstyle_double(double & d, e_double edouble, ::user::interaction * pui)
   {

      ::user::style * puserstyle = userstyle();

      if (puserstyle != NULL && puserstyle->get_double(d, edouble, pui))
      {

         return true;

      }

      return false;

   }


   style * style_composite::userstyle()
   {

      return m_puserstyleSelect;

   }


   ::draw2d::graphics * style_composite::style_get_graphics()
   {

      return NULL;

   }




} // namespace user











