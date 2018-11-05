#include "framework.h" // from "base/user/user.h"
//
//
//namespace user
//{
//
//
//   style_composite::style_composite()
//   {
//
//      m_puserstyleselect = null;
//
//      m_plibrary           = null;
//
//   }
//
//
//   style_composite::~style_composite()
//   {
//
//      ::aura::del(m_plibrary);
//
//   }
//
//
//   void style_composite::initialize_style_menu()
//   {
//
//   }
//
//
//   void style_composite::initialize_style_button()
//   {
//
//   }
//
//
//   void style_composite::initialize_style_menu_button()
//   {
//
//   }
//
//
//   void style_composite::initialize_style_menu_popup()
//   {
//
//   }
//
//
//   void style_composite::initialize_style_system_menu_button()
//   {
//
//   }
//
//
//   void style_composite::initialize_style_system_menu_close()
//   {
//
//   }
//
//
//   void style_composite::initialize_style_system_menu_popup()
//   {
//
//   }
//
//
//   void style_composite::initialize_style_set()
//   {
//
//      m_map[schema_default].alloc(allocer());
//
//      m_map[schema_default]->initialize_style();
//
//   }
//
//
//   style * style_composite::style_get(e_style estyle)
//   {
//
//      return userstyle()->get(estyle);
//
//   }
//
//
//   ::user::menu_interaction * style_composite::create_menu_button(menu_item * pitem)
//   {
//
//      return userstyle()->create_menu_button(pitem);
//
//   }
//
//
//   bool style_composite::prepare_menu(::user::menu_item * pitem)
//   {
//
//      return userstyle()->prepare_menu(pitem);
//
//   }
//
//   bool style_composite::prepare_menu_button(::user::menu_item * pitem)
//   {
//
//      return userstyle()->prepare_menu_button(pitem);
//
//   }
//
//
//   bool style_composite::_001ondrawmainframebackground(::draw2d::graphics * pgraphics,::user::frame * pframe)
//   {
//
//      return userstyle()->_001ondrawmainframebackground(pgraphics, pframe);
//
//   }
//
//
//
//   void style_composite::drawcheck(::check::e_check echeck, const rect & rect, ::draw2d::graphics * pgraphics)
//   {
//
//      return userstyle()->drawcheck(echeck, rect, pgraphics);
//
//   }
//
//
//   bool style_composite::simple_ui_draw_focus_rect(::user::interaction * pui,::draw2d::graphics * pgraphics)
//   {
//
//      return userstyle()->simple_ui_draw_focus_rect(pui, pgraphics);
//
//   }
//
//
//   bool style_composite::on_ui_event(e_event eevent, e_object eobject, ::user::interaction * pui)
//   {
//
//      return userstyle()->on_ui_event(eevent, eobject, pui);
//
//   }
//
//
//   bool style_composite::_001tabondrawschema01(::draw2d::graphics * pgraphics,tab * ptab)
//   {
//
//      return userstyle()->_001tabondrawschema01(pgraphics, ptab);
//
//   }
//
//
//   bool style_composite::_001ondrawmenuinteraction(::draw2d::graphics * pgraphics, menu_interaction * pui)
//   {
//
//      return userstyle()->_001ondrawmenuinteraction(pgraphics, pui);
//
//   }
//
//
//   void style_composite::_001ontabpanedrawtitle(::user::tab_pane & pane,::user::tab * ptab,::draw2d::graphics * pgraphics,lpcrect lpcrect,::draw2d::brush_sp & brushtext)
//   {
//
//      return userstyle()->_001ontabpanedrawtitle(pane, ptab, pgraphics, lpcrect, brushtext);
//
//   }
//
//
//   bool style_composite::_001ontablayout(::user::tab * ptab)
//   {
//
//      return userstyle()->_001ontablayout(ptab);
//
//   }
//
//
//   void style_composite::_001drawcheckbox(::draw2d::graphics * pgraphics, lpcrect lpcrectclient, ::check::e_check echeck)
//   {
//
//      return userstyle()->_001drawcheckbox(pgraphics, lpcrectclient, echeck);
//
//   }
//
//
//   bool style_composite::_001drawtoolbaritem(::draw2d::graphics * pgraphics, int32_t iitem, ::user::toolbar * ptoolbar)
//   {
//
//      return userstyle()->_001drawtoolbaritem(pgraphics, iitem, ptoolbar);
//
//   }
//
//
//   bool style_composite::_001drawsimplescrollbar(::draw2d::graphics * pgraphics, simple_scroll_bar * pbar)
//   {
//
//      return userstyle()->_001drawsimplescrollbar(pgraphics, pbar);
//
//   }
//
//
//   bool style_composite::_001drawscrollbar(::draw2d::graphics * pgraphics, ::user::scroll_bar * pbar)
//   {
//
//      return userstyle()->_001drawscrollbar(pgraphics, pbar);
//
//   }
//
//
//
//
//   bool style_composite::select_text_color(::user::interaction * pui, ::draw2d::graphics * pgraphics, e_color ecolor)
//   {
//
//      colorref cr;
//
//      if(!style_color(cr, ecolor, pui))
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
//   bool style_composite::select_solid_brush(::user::interaction * pui, ::draw2d::graphics * pgraphics, e_color ecolor)
//   {
//
//      colorref cr;
//
//      if(!style_color(cr, ecolor, pui))
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
//      pgraphics->selectobject(brush);
//
//      return true;
//
//   }
//
//
//   bool style_composite::select_font(::user::interaction * pui, ::draw2d::graphics * pgraphics, e_font efont)
//   {
//
//      ::draw2d::font_sp font;
//
//      if(!style_font(font, efont, pui))
//      {
//
//         font.alloc(allocer());
//
//         if (!font->create_point_font(font_sans, 12.0))
//         {
//
//            return false;
//
//         }
//
//      }
//
//      if(is_set(pgraphics))
//      {
//
//         pgraphics->select_font(font);
//
//      }
//
//      return true;
//
//   }
//
//
//   bool style_composite::select_text_color(::user::interaction * pui, e_color ecolor)
//   {
//
//      ::draw2d::graphics * pgraphics = style_get_graphics();
//
//      if(pgraphics == null)
//      {
//
//         return false;
//
//      }
//
//      return select_text_color(pui, pgraphics, ecolor);
//
//   }
//
//
//   bool style_composite::select_solid_brush(::user::interaction * pui, e_color ecolor)
//   {
//
//      ::draw2d::graphics * pgraphics = style_get_graphics();
//
//      if(pgraphics == null)
//      {
//
//         return false;
//
//      }
//
//      return select_solid_brush(pui, pgraphics, ecolor);
//
//   }
//
//
//   bool style_composite::select_font(::user::interaction * pui, e_font efont)
//   {
//
//      ::draw2d::graphics * pgraphics = style_get_graphics();
//
//      if(pgraphics == null)
//      {
//
//         return false;
//
//      }
//
//      return select_font(pui, pgraphics, efont);
//
//   }
//
//
//
//   colorref style_composite::_001getcolor(::user::interaction * pui, e_color ecolor, colorref crdefault)
//   {
//
//      colorref cr;
//
//      if (style_color(cr, ecolor, pui))
//         return cr;
//
//      return crdefault;
//
//   }
//
//
//   ::draw2d::font_sp style_composite::_001getfont(::user::interaction * pui, e_font efont, ::draw2d::font * pfont)
//   {
//
//      ::draw2d::font_sp font;
//
//      if (style_font(font, efont, pui))
//         return font;
//
//      if (pfont == null)
//      {
//
//         font.alloc(allocer());
//
//         font->create_pixel_font(font_sans, 9.0);
//
//         return font;
//
//      }
//
//      return pfont;
//
//   }
//
//
//   e_translucency style_composite::_001gettranslucency(::user::interaction * pui, e_element eelement, e_translucency etranslucencydefault)
//   {
//
//      e_translucency etranslucency = translucency_undefined;
//
//      if (style_translucency(etranslucency, eelement, pui))
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
//      return etranslucencydefault;
//
//   }
//
//
//   bool style_composite::_001getflag(::user::interaction * pui, e_flag eflag, bool bdefault)
//   {
//
//      bool bset = bdefault;
//
//      if (style_flag(bset, eflag, pui))
//         return bset;
//
//      return bdefault;
//
//   }
//
//
//   rect style_composite::_001getrect(::user::interaction * pui, e_rect erect, rect rectdefault)
//   {
//
//      ::rect rect(rectdefault);
//
//      if (style_rect(rect, erect, pui))
//         return rect;
//
//      return rectdefault;
//
//   }
//
//
//   int style_composite::_001getint(::user::interaction * pui, e_int eint, int idefault)
//   {
//
//      int i = idefault;
//
//      if (style_int(i, eint, pui))
//         return i;
//
//      return idefault;
//
//   }
//
//
//   double style_composite::_001getdouble(::user::interaction * pui, e_double edouble, double ddefault)
//   {
//
//      double d = ddefault;
//
//      if (style_double(d, edouble, pui))
//         return d;
//
//      return ddefault;
//
//   }
//
//
//   bool style_composite::_001istranslucent(::user::interaction * pui, e_element eelement)
//   {
//
//      e_translucency etranslucency = _001gettranslucency(pui, eelement);
//
//      return etranslucency == translucency_present || etranslucency == translucency_total;
//
//   }
//
//
//   bool style_composite::_001isbackgroundbypass(::user::interaction * pui, e_element eelement)
//   {
//
//      return _001gettranslucency(pui, eelement) == translucency_total;
//
//   }
//
//
//   bool style_composite::_001hastranslucency(::user::interaction * pui, e_element eelement)
//   {
//
//      e_translucency etranslucency = _001gettranslucency(pui, eelement);
//
//      return etranslucency == translucency_present || etranslucency == translucency_total;
//
//   }
//
//
//   bool style_composite::_001istransparent(::user::interaction * pui, e_element eelement)
//   {
//
//      return _001gettranslucency(pui, eelement) == translucency_total;
//
//   }
//
//
//
//
//
//   void style_composite::on_select_user_style()
//   {
//
//      e_schema eschema = get_user_style();
//
//      sp(::user::style) puserstyle = m_puserstyle;
//
//      if (puserstyle.is_null())
//      {
//
//         puserstyle = session.m_puserstyle;
//
//         if (puserstyle == null)
//         {
//
//            puserstyle = application.m_puserstyle;
//
//            if (puserstyle == null)
//            {
//
//               puserstyle = session.m_puserstyle;
//
//               if (puserstyle == null)
//               {
//
//                  session.m_puserstyle = session.get_user_style("", get_app());
//
//                  puserstyle = session.m_puserstyle;
//
//                  if (puserstyle == null)
//                  {
//
//                     puserstyle = this;
//
//                  }
//
//               }
//
//            }
//
//         }
//
//      }
//
//      if(eschema == schema_default)
//      {
//
//         m_puserstyleselect = puserstyle;
//
//      }
//      else
//      {
//
//         sp(::user::style) puserstylenext = puserstyle->style_get(eschema);
//
//         if(puserstylenext.is_set())
//         {
//
//            m_puserstyleselect = puserstylenext;
//
//         }
//         else
//         {
//
//            m_puserstyleselect = puserstyle;
//
//         }
//
//      }
//
//   }
//
//
//   ::user::style * style_composite::parent_userstyle()
//   {
//
//      return null;
//
//   }
//
//
//
//
//   bool style_composite::style_color(colorref & cr, e_color ecolor, ::user::interaction * pui)
//   {
//
//      if (pui->get_color(cr, ecolor, pui))
//      {
//
//         return true;
//
//      }
//
//      ::user::frame * pframe = pui->getparentframe();
//
//      while (pframe != null)
//      {
//
//         if (pframe->get_color(cr, ecolor, pui))
//         {
//
//            return true;
//
//         }
//
//         pframe = pframe->getparentframe();
//
//      }
//
//      pframe = pui->getownerframe();
//
//      while (pframe != null)
//      {
//
//         if (pframe->get_color(cr, ecolor, pui))
//         {
//
//            return true;
//
//         }
//
//         pframe = pframe->getparentframe();
//
//      }
//
//      if (get_color(cr, ecolor, pui))
//      {
//
//         return true;
//
//      }
//
//      return userstyle_color(cr, ecolor, pui);
//
//   }
//
//
//   bool style_composite::style_font(::draw2d::font_sp & font, e_font efont, ::user::interaction * pui)
//   {
//
//
//      if (pui->get_font(font, efont, pui))
//      {
//
//         return true;
//
//      }
//
//      ::user::frame * pframe = pui->getparentframe();
//
//      while (pframe != null)
//      {
//
//         if (pframe->get_font(font, efont, pui))
//         {
//
//            return true;
//
//         }
//
//         pframe = pframe->getparentframe();
//
//      }
//
//      pframe = pui->getownerframe();
//
//      while (pframe != null)
//      {
//
//         if (pframe->get_font(font, efont, pui))
//         {
//
//            return true;
//
//         }
//
//         pframe = pframe->getparentframe();
//
//      }
//
//      if (get_font(font, efont, pui))
//      {
//
//         return true;
//
//      }
//
//      return userstyle_font(font, efont, pui);
//
//   }
//
//
//   bool style_composite::style_translucency(e_translucency & etranslucency, e_element eelement, ::user::interaction * pui)
//   {
//
//
//      if (pui->get_translucency(etranslucency, eelement, pui))
//      {
//
//         return true;
//
//      }
//
//      ::user::frame * pframe = pui->getparentframe();
//
//      while (pframe != null)
//      {
//
//         if (pframe->get_translucency(etranslucency, eelement, pui))
//         {
//
//            return true;
//
//         }
//
//         pframe = pframe->getparentframe();
//
//      }
//
//      pframe = pui->getownerframe();
//
//      while (pframe != null)
//      {
//
//         if (pframe->get_translucency(etranslucency, eelement, pui))
//         {
//
//            return true;
//
//         }
//
//         pframe = pframe->getparentframe();
//
//      }
//
//      if (get_translucency(etranslucency, eelement, pui))
//      {
//
//         return true;
//
//      }
//
//      return userstyle_translucency(etranslucency, eelement, pui);
//
//   }
//
//
//   bool style_composite::style_flag(bool & bset, e_flag eflag, ::user::interaction * pui)
//   {
//
//      if (pui->get_flag(bset, eflag, pui))
//      {
//
//         return true;
//
//      }
//
//      ::user::frame * pframe = pui->getparentframe();
//
//      while (pframe != null)
//      {
//
//         if (pframe->get_flag(bset, eflag, pui))
//         {
//
//            return true;
//
//         }
//
//         pframe = pframe->getparentframe();
//
//      }
//
//      pframe = pui->getownerframe();
//
//      while (pframe != null)
//      {
//
//         if (pframe->get_flag(bset, eflag, pui))
//         {
//
//            return true;
//
//         }
//
//         pframe = pframe->getparentframe();
//
//      }
//
//      if (get_flag(bset, eflag, pui))
//      {
//
//         return true;
//
//      }
//
//      return userstyle_flag(bset, eflag, pui);
//
//   }
//
//
//   bool style_composite::style_rect(rect & rect, e_rect erect, ::user::interaction * pui)
//   {
//
//      if (pui->get_rect(rect, erect, pui))
//      {
//
//         return true;
//
//      }
//
//      ::user::frame * pframe = pui->getparentframe();
//
//      while (pframe != null)
//      {
//
//         if (pframe->get_rect(rect, erect, pui))
//         {
//
//            return true;
//
//         }
//
//         pframe = pframe->getparentframe();
//
//      }
//
//      pframe = pui->getownerframe();
//
//      while (pframe != null)
//      {
//
//         if (pframe->get_rect(rect, erect, pui))
//         {
//
//            return true;
//
//         }
//
//         pframe = pframe->getparentframe();
//
//      }
//
//      if (get_rect(rect, erect, pui))
//      {
//
//         return true;
//
//      }
//
//      return userstyle_rect(rect, erect, pui);
//
//   }
//
//
//   bool style_composite::style_int(int & i, e_int eint, ::user::interaction * pui)
//   {
//
//      if (pui->get_int(i, eint, pui))
//      {
//
//         return true;
//
//      }
//
//      ::user::frame * pframe = pui->getparentframe();
//
//      while (pframe != null)
//      {
//
//         if (pframe->get_int(i, eint, pui))
//         {
//
//            return true;
//
//         }
//
//         pframe = pframe->getparentframe();
//
//      }
//
//      pframe = pui->getownerframe();
//
//      while (pframe != null)
//      {
//
//         if (pframe->get_int(i, eint, pui))
//         {
//
//            return true;
//
//         }
//
//         pframe = pframe->getparentframe();
//
//      }
//
//      if (get_int(i, eint, pui))
//      {
//
//         return true;
//
//      }
//
//      return userstyle_int(i, eint, pui);
//
//   }
//
//
//   bool style_composite::style_double(double & d, e_double edouble, ::user::interaction * pui)
//   {
//
//      if (pui->get_double(d, edouble, pui))
//      {
//
//         return true;
//
//      }
//
//      ::user::frame * pframe = pui->getparentframe();
//
//      while (pframe != null)
//      {
//
//         if (pframe->get_double(d, edouble, pui))
//         {
//
//            return true;
//
//         }
//
//         pframe = pframe->getparentframe();
//
//      }
//
//      pframe = pui->getownerframe();
//
//      while (pframe != null)
//      {
//
//         if (pframe->get_double(d, edouble, pui))
//         {
//
//            return true;
//
//         }
//
//         pframe = pframe->getparentframe();
//
//      }
//
//      if (get_double(d, edouble, pui))
//      {
//
//         return true;
//
//      }
//
//      return userstyle_double(d, edouble, pui);
//
//   }
//
//
//   bool style_composite::userstyle_color(colorref & cr, e_color ecolor, ::user::interaction * pui)
//   {
//
//      ::user::style * puserstyle = userstyle();
//
//      if (puserstyle != null && puserstyle->get_color(cr, ecolor, pui))
//      {
//
//         return true;
//
//      }
//
//      if (ecolor == color_text)
//      {
//
//         cr = argb(255, 0, 0, 0);
//
//      }
//      else if (ecolor == color_text_selected)
//      {
//
//         cr = argb(255, 255, 255, 255);
//
//      }
//      else if (ecolor == color_text_highlight)
//      {
//
//         cr = argb(255, 55, 105, 255);
//
//      }
//      else if (ecolor == color_background_highlight)
//      {
//
//         cr = argb(100, 110, 150, 255);
//
//      }
//      else if (ecolor == color_text_selected_highlight)
//      {
//
//         cr = argb(255, 102, 153, 255);
//
//      }
//      else if (ecolor == color_background_selected_highlight)
//      {
//
//         cr = argb(100, 80, 100, 200);
//
//      }
//      else if (ecolor == color_background)
//      {
//
//         if (_001istranslucent(pui))
//         {
//
//            cr = argb(60, 255, 255, 255);
//
//         }
//         else
//         {
//
//            cr = argb(255, 255, 255, 255);
//
//         }
//
//      }
//      else if (ecolor == color_face)
//      {
//
//         if (_001istranslucent(pui))
//         {
//
//            cr = argb(120, 0, 0, 0);
//
//         }
//         else
//         {
//
//            cr = argb(255, 80, 80, 80);
//
//         }
//
//      }
//      else if (ecolor == color_face_lite)
//      {
//
//         if (_001istranslucent(pui))
//         {
//
//            cr = argb(80, 0, 0, 0);
//
//         }
//         else
//         {
//
//            cr = argb(255, 120, 120, 120);
//
//         }
//
//      }
//      else if (ecolor == color_tab_layout_background)
//      {
//
//         if (_001istranslucent(pui))
//         {
//
//            cr = argb(80, 255, 255, 255);
//
//         }
//         else
//         {
//
//            cr = argb(255, 255, 255, 255);
//
//         }
//
//      }
//      else if (ecolor == color_tab_client_background)
//      {
//
//         if (_001istranslucent(pui))
//         {
//
//            cr = argb(0, 0, 0, 0);
//
//         }
//         else
//         {
//
//            cr = argb(255, 255, 255, 255);
//
//         }
//
//      }
//      else if (ecolor == color_background_selected)
//      {
//
//         if (_001istranslucent(pui))
//         {
//
//            cr = argb(184, 0, 0, 127);
//
//         }
//         else
//         {
//
//            cr = argb(255, 0, 0, 127);
//
//         }
//
//      }
//      else if (ecolor == color_background_selected)
//      {
//
//         if (_001istranslucent(pui))
//         {
//
//            cr = argb(184, 0, 0, 127);
//
//         }
//         else
//         {
//
//            cr = argb(255, 0, 0, 127);
//
//         }
//
//      }
//      else if (ecolor == color_border)
//      {
//
//         cr = argb(255, 84, 90, 80);
//
//      }
//      else if (ecolor == color_border_hover)
//      {
//
//         cr = argb(255, 84, 190, 80);
//
//      }
//      else if (ecolor == color_text_hover)
//      {
//
//         cr = argb(255, 84, 184, 255);
//
//      }
//      else if (ecolor == color_list_header)
//      {
//
//         cr = argb(255, 80, 80, 80);
//
//      }
//      else if (ecolor == color_background)
//      {
//
//         cr = argb(255, 255, 255, 255);
//
//      }
//      else if (ecolor == color_text_normal)
//      {
//
//         cr = argb(255, 0, 0, 0);
//
//      }
//      else if (ecolor == color_background_hover)
//      {
//
//         cr = argb(255, 255, 255, 255);
//
//      }
//      else if (ecolor == color_background_press)
//      {
//
//         cr = argb(255, 215, 200, 255);
//
//      }
//      else if (ecolor == color_text_hover)
//      {
//
//         cr = argb(255, 0, 0, 0);
//
//      }
//      else if (ecolor == color_list_header_background)
//      {
//
//         cr = argb(80, 0, 0, 0);
//
//      }
//      else if (ecolor == color_list_item_background)
//      {
//
//         cr = argb(127, 0, 0, 0);
//
//      }
//      else if (ecolor == color_button_background_disabled)
//      {
//
//         return get_color(cr, color_background_disabled, pui);
//
//      }
//      else if (ecolor == color_button_background_hover)
//      {
//
//         return get_color(cr, color_background_hover, pui);
//
//      }
//      else if (ecolor == color_button_background)
//      {
//
//         return get_color(cr, color_background_selected, pui);
//
//      }
//      else if (ecolor == color_button_background_press)
//      {
//
//         return get_color(cr, color_background_press, pui);
//
//      }
//      else if (ecolor == color_button_text_disabled)
//      {
//
//         return get_color(cr, color_text_disabled, pui);
//
//      }
//      else if (ecolor == color_button_text_hover)
//      {
//
//         return get_color(cr, color_text_hover, pui);
//
//      }
//      else if (ecolor == color_button_text)
//      {
//
//         return get_color(cr, color_text_selected, pui);
//
//      }
//      else if (ecolor == color_button_text_press)
//      {
//
//         return get_color(cr, color_text_press, pui);
//
//      }
//      else if (ecolor == color_edit_background)
//      {
//
//         cr = argb(128, 255, 255, 255);
//
//      }
//      else if (ecolor == color_edit_text)
//      {
//
//         cr = argb(128, 0, 0, 0);
//
//      }
//      else if (ecolor == color_edit_text_selected)
//      {
//
//         cr = argb(128, 255, 255, 255);
//
//      }
//      else if (ecolor == color_edit_text_empty)
//      {
//
//         cr = argb(128, 96, 96, 96);
//
//      }
//      else if (ecolor == color_edit_background_selected)
//      {
//
//         cr = argb(128, 0, 0, 128);
//
//      }
//      else if (ecolor == color_split_layout_background)
//      {
//
//         cr = argb(128, 255, 255, 255);
//
//      }
//      else if (ecolor == color_list_background)
//      {
//
//         cr = argb(128, 255, 255, 255);
//
//      }
//      else if (ecolor == color_toolbar_background)
//      {
//
//         cr = argb(128, 255, 255, 255);
//
//      }
//      else if (ecolor == color_list_header_separator)
//      {
//
//         cr = argb(128, 0, 0, 0);
//
//      }
//      else if (ecolor == color_view_background)
//      {
//
//         cr = 0;
//
//      }
//      else if (ecolor == color_scrollbar_background)
//      {
//
//         cr = argb(127, 127, 127, 127);
//
//      }
//      else if (ecolor == color_action_hover_border_color)
//      {
//
//         cr = argb(255, 83, 104, 255);
//
//      }
//      else if (ecolor == color_list_item_text)
//      {
//
//         return style_color(cr, color_text_normal, pui);
//
//      }
//      else if (ecolor == color_list_item_text_hover)
//      {
//
//         return style_color(cr, color_text_highlight, pui);
//
//      }
//      else if (ecolor == color_list_item_text_selected)
//      {
//
//         return style_color(cr, color_text_selected, pui);
//
//      }
//      else if (ecolor == color_list_item_text_selected_hover)
//      {
//
//         return style_color(cr, color_text_selected_highlight, pui);
//
//      }
//      else if (ecolor == color_list_item_background)
//      {
//
//         return style_color(cr, color_background, pui);
//
//      }
//      else if (ecolor == color_list_item_background_hover)
//      {
//
//         return style_color(cr, color_background_highlight, pui);
//
//      }
//      else if (ecolor == color_list_item_background_selected)
//      {
//
//         return style_color(cr, color_background_selected, pui);
//
//      }
//      else if (ecolor == color_list_item_background_selected_hover)
//      {
//
//         return style_color(cr, color_background_selected_highlight, pui);
//
//      }
//      else
//      {
//
//         _throw(invalid_argument_exception(get_app()));
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
//   bool style_composite::userstyle_font(::draw2d::font_sp & font, e_font efont, ::user::interaction * pui)
//   {
//
//      ::user::style * puserstyle = userstyle();
//
//      if (puserstyle != null && puserstyle->get_font(font, efont, pui))
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
//   bool style_composite::userstyle_translucency(e_translucency & etranslucency, e_element eelement, ::user::interaction * pui)
//   {
//
//      ::user::style * puserstyle = userstyle();
//
//      if (puserstyle != null && puserstyle->get_translucency(etranslucency, eelement, pui))
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
//   bool style_composite::userstyle_flag(bool & bset, e_flag eflag, ::user::interaction * pui)
//   {
//
//      ::user::style * puserstyle = userstyle();
//
//      if (puserstyle != null && puserstyle->get_flag(bset, eflag, pui))
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
//   bool style_composite::userstyle_rect(rect & rect, e_rect erect, ::user::interaction * pui)
//   {
//
//      ::user::style * puserstyle = userstyle();
//
//      if (puserstyle != null && puserstyle->get_rect(rect, erect, pui))
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
//   bool style_composite::userstyle_int(int & i, e_int eint, ::user::interaction * pui)
//   {
//
//      ::user::style * puserstyle = userstyle();
//
//      if (puserstyle != null && puserstyle->get_int(i, eint, pui))
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
//   bool style_composite::userstyle_double(double & d, e_double edouble, ::user::interaction * pui)
//   {
//
//      ::user::style * puserstyle = userstyle();
//
//      if (puserstyle != null && puserstyle->get_double(d, edouble, pui))
//      {
//
//         return true;
//
//      }
//
//
//      if ((int)edouble >= (int)double_default_one_min
//            && (int)edouble <= (int)double_default_one_max)
//      {
//
//         d = 1.0;
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
//   style * style_composite::userstyle()
//   {
//
//      return m_puserstyleselect;
//
//   }
//
//
//   ::draw2d::graphics * style_composite::style_get_graphics()
//   {
//
//      return null;
//
//   }
//
//
//
//
//} // namespace user
//
//
//
//
//
//
//
//
//
//
//
