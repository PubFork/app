#include "framework.h"


namespace user
{


   menu_interaction::menu_interaction(menu_item * pitem) :
      m_pitem(pitem),
      object(pitem->get_app()),
      ::user::interaction(pitem->get_app())
   {

      m_econtroltype = control_type_menu_button;

   }


   menu_interaction::~menu_interaction()
   {

   }


   void menu_interaction::install_message_routing(::message::sender * pinterface)
   {

      ::user::interaction::install_message_routing(pinterface);

      IGUI_MSG_LINK(WM_CREATE, pinterface, this, &menu_interaction::_001OnCreate);

   }


   void menu_interaction::_001OnDrawDefault(::draw2d::graphics * pgraphics)
   {

      rect rectClient;

      GetClientRect(rectClient);

      if (m_id == "separator")
      {

         ::draw2d::pen_sp pen(allocer());

         pen->create_solid(2.0, ARGB(127, 80, 80, 80));

         pgraphics->SelectObject(pen);

         pgraphics->move_to(rectClient.left, (rectClient.top + rectClient.bottom) / 2);

         pgraphics->line_to(rectClient.right, (rectClient.top + rectClient.bottom) / 2);

         return;

      }

      interaction::_001OnDraw(pgraphics);

      if (m_pmenuitem != NULL && m_pmenuitem->m_bPopup)
      {

         ::draw2d::brush_sp br(allocer(), RGB(0, 0, 0));

         ::draw2d::pen_sp pen(allocer());

         pen->create_solid(1, RGB(0, 0, 0));
         pgraphics->SelectObject(pen);
         pgraphics->SelectObject(br);
         rect rectPopupArrow;
         rectPopupArrow.left = rectClient.right - 9;
         rectPopupArrow.right = rectClient.right - 4;
         rectPopupArrow.top = ((rectClient.top + rectClient.bottom) / 2) - 4;
         rectPopupArrow.bottom = ((rectClient.top + rectClient.bottom) / 2) + 4;
         point_array pta;
         pta.add(point(rectPopupArrow.left, rectPopupArrow.bottom));
         pta.add(point(rectPopupArrow.right, (rectPopupArrow.bottom + rectPopupArrow.top) / 2));
         pta.add(point(rectPopupArrow.left, rectPopupArrow.top));
         pta.add(point(rectPopupArrow.left, rectPopupArrow.bottom));
         pgraphics->polygon(pta);
      }

      _001DrawCheck(pgraphics);

   }


   void menu_interaction::_001OnDraw(::draw2d::graphics * pgraphics)
   {

      style_context style(this);

      while (style)
      {

         if (style->_001OnDrawMenuInteraction(pgraphics, this))
         {

            return;

         }

         style.next();

      }

      _001OnDrawDefault(pgraphics);

   }


   void menu_interaction::on_layout()
   {

      //      if (m_puserstyle == NULL)
      //      {
      //
      //         if (m_pitem != NULL)
      //         {
      //
      //            sp(::user::menu) pui = m_pitem->m_pmenu;
      //
      //            if (pui.is_set() && pui->m_puiParent != NULL)
      //            {
      //
      //               m_puserstyle = pui->m_puiParent;
      //
      //            }
      //
      //         }
      //
      //      }

   }

   void menu_interaction::_001OnNcDraw(::draw2d::graphics * pgraphics)
   {

      if (m_id != "separator")
      {

         ::user::interaction::_001OnNcDraw(pgraphics);

      }

   }


   void menu_interaction::_001DrawCheck(::draw2d::graphics * pgraphics)
   {

   }


   void menu_interaction::_001OnCreate(::message::message * pobj)
   {



      pobj->previous();

   }


   void menu_interaction::_001OnMouseMove(::message::message * pobj)
   {

      SCAST_PTR(::message::mouse, pmouse, pobj);

      pmouse->previous();


   }


   void menu_interaction::on_calc_size(calc_size * pcalcsize)
   {

      string strText;

      get_window_text(strText);

      ::draw2d::font_sp pfont;

      style_context style(this);

      get_font(pfont, font_button, &style);

      class size size = pcalcsize->m_pgraphics->GetTextExtent(strText);

      rect rectMargin = _001GetRect(rect_menu_item_margin);

      rect rectBorder = _001GetRect(rect_menu_item_border);

      rect rectPadding = _001GetRect(rect_menu_item_padding);

      size.cx += rectMargin.left + rectBorder.left + rectPadding.left;

      size.cx += m_pitem->m_pmenu->m_iCheckBoxSize;

      size.cx += _001GetInt(int_menu_check_padding);

      if (m_pitem->IsPopup())
      {

         size.cx += _001GetInt(int_menu_check_padding);

         size.cx += m_pitem->m_pmenu->m_iCheckBoxSize;

      }

      size.cx += rectMargin.right + rectBorder.right + rectPadding.right;

      size.cy += rectMargin.top + rectBorder.top + rectPadding.top;

      size.cy += rectMargin.bottom + rectBorder.bottom + rectPadding.bottom;

      pcalcsize->m_size = size;

   }


} // namespace user
