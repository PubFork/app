#include "framework.h"


namespace user
{


   menu_button::menu_button(menu_item * pitem):
      object(pitem->get_app()),
      ::user::interaction(pitem->get_app()),
      ::user::menu_interaction(pitem),
      ::user::button(pitem->get_app())
   {

      m_econtroltype = control_type_menu_button;

      m_erectMargin = rect_menu_item_margin;
      m_erectBorder = rect_menu_item_border;
      m_erectPadding = rect_menu_item_padding;
      m_eintTextAlign = int_menu_item_draw_text_flags;

      m_flagNonClient.unsignalize(::user::interaction::non_client_focus_rect);


   }


   menu_button::~menu_button()
   {

   }


   void menu_button::install_message_routing(::message::sender * pinterface)
   {

      ::user::button::install_message_routing(pinterface);

      IGUI_MSG_LINK(WM_CREATE, pinterface, this, &menu_button::_001OnCreate);

   }


   bool menu_button::create_window(const RECT & rect, ::user::interaction *pparent, id id)
   {

      if (!button::create_window(rect, pparent, id))
      {

         return false;

      }

      return true;

   }


   void menu_button::_001OnDrawDefault(::draw2d::graphics * pgraphics)
   {

      rect rectClient;

      GetClientRect(rectClient);

      if (m_id == "separator")
      {

         pgraphics->set_alpha_mode(::draw2d::alpha_mode_blend);

         pgraphics->fill_solid_rect(rectClient, _001GetColor(color_button_background));

         ::draw2d::pen_sp pen(allocer());

         pen->create_solid(1.0, ARGB(127, 80, 80, 80));

         pgraphics->SelectObject(pen);

         pgraphics->move_to(rectClient.left + rectClient.width() / 8, (rectClient.top + rectClient.bottom) / 2);

         pgraphics->line_to(rectClient.right - rectClient.width() / 8, (rectClient.top + rectClient.bottom) / 2);

         return;

      }

      button::_001OnDraw(pgraphics);

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


   void menu_button::_001OnDraw(::draw2d::graphics * pgraphics)
   {

      if (m_puserstyle != NULL && m_puserstyle->_001OnDrawMenuInteraction(pgraphics, this))
      {

         return;

      }

      _001OnDrawDefault(pgraphics);

   }


   void menu_button::on_layout()
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

   void menu_button::_001OnNcDraw(::draw2d::graphics * pgraphics)
   {

      if (m_id != "separator")
      {

         ::user::button::_001OnNcDraw(pgraphics);

      }

   }

   void menu_button::_001DrawCheck(::draw2d::graphics * pgraphics)
   {

      UINT uiImage = 0xffffffffu;

      if(m_pmenuitem != NULL)
      {

         uiImage = BaseMenuCentral::GetMenuCentral(get_app())->CommandToImage(m_pmenuitem->m_id);

      }

      if(uiImage != 0xffffffffu)
      {



         rect rectImage = m_rectCheckBox;
         rect rectImageBorder = rectImage;
         rectImageBorder.inflate(2, 2);
         ::image_list::info ii;
         sp(image_list) pimagelist;
         if(!is_window_enabled())
         {
            pimagelist = BaseMenuCentral::GetMenuCentral(get_app())->MenuV033GetImageListHueLight();
         }
         else
         {
            pimagelist = BaseMenuCentral::GetMenuCentral(get_app())->MenuV033GetImageList();
         }
         pimagelist->get_image_info(uiImage, &ii);
         rect & rectImageInfo(ii.m_rect);
         rectImage.offset(1, 1);
         rectImage.top     = rectImage.bottom - rectImageInfo.height();
         rectImage.right   = rectImage.left + rectImageInfo.width();

         if(m_echeck == ::check::checked)
         {

            pgraphics->fill_solid_rect(rectImageBorder, RGB(127, 127, 127));

            pgraphics->draw3d_rect(rectImageBorder, Session.get_default_color(COLOR_3DSHADOW), Session.get_default_color(COLOR_3DHILIGHT));

         }

         pimagelist->draw(
         pgraphics,
         uiImage,
         rectImage.top_left(),
         0);
      }
      else
      {

         m_puserstyle->DrawCheck(m_echeck, m_rectCheckBox, pgraphics);

      }

   }


   void menu_button::_001OnCreate(::message::message * pobj)
   {

      pobj->previous();

   }


   void menu_button::_001OnMouseMove(::message::message * pobj)
   {

      SCAST_PTR(::message::mouse,pmouse,pobj);

      pmouse->previous();


   }


   bool menu_button::keyboard_focus_is_focusable()
   {

      return false;


   }


   void menu_button::on_calc_size(calc_size * pcalcsize)
   {

      sp(::draw2d::font) pfont = _001GetFont(font_button);

      pcalcsize->m_pgraphics->SelectObject(pfont);

      select(pcalcsize->m_pgraphics);

      string strButtonText;

      strButtonText = get_window_text();

      class ::size size = pcalcsize->m_pgraphics->GetTextExtent(strButtonText);

      rect rectMargin = _001GetRect(rect_menu_item_margin);

      rect rectBorder = _001GetRect(rect_menu_item_border);

      rect rectPadding = _001GetRect(rect_menu_item_padding);

      size.cx += rectMargin.left + rectBorder.left + rectPadding.left;

      size.cx += rectMargin.right;

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
