#include "framework.h"


namespace user
{


   const int32_t g_base_menu_indent = 11;


   menu_list_window::menu_list_window():
      menu_list_window(get_app())
   {

      m_econtroltype = control_type_menu;
      m_bInline = true;

   }


   menu_list_window::menu_list_window(::aura::application * papp) :
      object(papp),
      menu(papp)
   {

      m_bAutoDelete        = true;
      m_bOwnItem           = false;
      m_puiNotify          = NULL;
      m_bAutoClose         = true;
      m_bInline            = true;

   }


   menu_list_window::menu_list_window(::aura::application * papp, menu_item * pitem) :
      object(papp),
      menu(papp)
   {

      m_puiNotify          = NULL;
      m_bAutoClose         = true;
      m_bAutoDelete        = true;
      m_bOwnItem           = false;
      m_bInline            = true;

   }


   menu_list_window::~menu_list_window()
   {

   }


   void menu_list_window::install_message_routing(::message::sender * pinterface)
   {

      menu::install_message_routing(pinterface);

      IGUI_MSG_LINK(WM_CREATE, pinterface, this, &menu_list_window::_001OnCreate);
      IGUI_MSG_LINK(WM_DESTROY, pinterface, this, &menu_list_window::_001OnDestroy);
      IGUI_MSG_LINK(WM_CLOSE, pinterface, this, &menu_list_window::_001OnClose);

   }


   void menu_list_window::_001OnCreate(::message::message * pobj)
   {

      UNREFERENCED_PARAMETER(pobj);

   }


   void menu_list_window::_001OnClose(::message::message * pobj)
   {

      UNREFERENCED_PARAMETER(pobj);

   }


   void menu_list_window::_001OnDestroy(::message::message * pobj)
   {

      UNREFERENCED_PARAMETER(pobj);

   }


   void menu_list_window::_001OnTimer(::timer * ptimer)
   {

      ::user::menu::_001OnTimer(ptimer);

   }


   void menu_list_window::calc_size(menu_item * pitemParent, ::draw2d::graphics * pgraphics, int32_t & iMaxWidth, int32_t & iMaxHeight)
   {

      if (!m_bMenuOk)
      {

         return;

      }

      if(pitemParent == NULL)
      {

         return;

      }

      if(pitemParent->m_spitema == NULL)
      {

         return;

      }

      for(int32_t i = 0; i < pitemParent->m_spitema->get_size(); i++)
      {

         menu_item * pitem = pitemParent->m_spitema->element_at(i);

         if(pitem->m_pui == NULL)
         {

            continue;

         }

         size size = pgraphics->GetTextExtent(pitem->m_pui->get_window_text());

         size.cx += pitem->m_iLevel * g_base_menu_indent;

         if(pitem->IsPopup())
            size.cx += 12 + 16;

         if(size.cy > iMaxHeight)
            iMaxHeight = size.cy;

         if(size.cx > iMaxWidth)
            iMaxWidth = size.cx;

         calc_size(pitem, pgraphics, iMaxWidth, iMaxHeight);

      }

   }


   void menu_list_window::on_layout()
   {

      if (!m_bMenuOk)
      {

         return;

      }

      if(GetParent() == NULL)
      {

         return;

      }

      sp(menu_item) pitem = get_item();

      if(pitem == NULL)
      {

         return;

      }

      rect rectClient;

      GetParent()->GetClientRect(rectClient);

      ::draw2d::memory_graphics pgraphics(allocer());

      select_font(pgraphics);

      size size = pgraphics->GetTextExtent("XXXMMM");

      int32_t iMaxHeight = size.cy;

      int32_t iMaxWidth = size.cx;

      m_iHeaderHeight = size.cy;

      calc_size(m_pitem, pgraphics, iMaxWidth, iMaxHeight);

      m_iItemHeight = iMaxHeight + 6 + 2;

      m_size.cx = iMaxWidth + 4;

      m_size.cy = m_iHeaderHeight + pitem->m_iSeparatorCount * 3 + pitem->m_iFullHeightItemCount * m_iItemHeight + 4;

      rect rect(4, m_iHeaderHeight + 4, m_size.cx - 8, 4);

      string str;

      layout_buttons(m_pitem, iMaxWidth + 4, rect, rectClient);

      auto & puiClose = m_itemClose.m_pui;

      if(puiClose->IsWindow())
      {

         puiClose->resize_to_fit();

         puiClose->MoveWindow(m_size.cx - puiClose->width() - 2, 2);

      }

   }


   void menu_list_window::layout_buttons(menu_item * pitemParent, int32_t iMaxWidth, LPRECT lprect, LPCRECT lpcrectBound)
   {

      if (!m_bMenuOk)
      {

         return;

      }

      if(pitemParent->m_spitema == NULL)
         return;

      for(int32_t i = 0; i < pitemParent->m_spitema->get_size(); i++)
      {
         menu_item * pitem = pitemParent->m_spitema->element_at(i);
         if(pitem->m_id  == "separator")
         {
            lprect->bottom = lprect->top + 3;
         }
         else
         {
            lprect->bottom = lprect->top + m_iItemHeight - 2;
         }
         if(lprect->bottom > lpcrectBound->bottom)
         {
            lprect->left += iMaxWidth + 16;
            lprect->top = lpcrectBound->top;
            if(pitem->m_id == "separator")
               continue;
            lprect->bottom = lprect->top + m_iItemHeight - 2;
         }

         if(pitem->m_pui == NULL)
         {

            continue;

         }

         pitem->m_pui->SetWindowPos(
         0,
         lprect->left + pitem->m_iLevel * g_base_menu_indent,
         lprect->top,
         iMaxWidth - pitem->m_iLevel * g_base_menu_indent,
         lprect->bottom - lprect->top,
         0);

         lprect->top = lprect->bottom + 2;

         layout_buttons(pitem, iMaxWidth, lprect, lpcrectBound);

      }

   }


   void menu_list_window::_001OnDraw(::draw2d::graphics * pgraphics)
   {

      ::user::interaction::_001OnDraw(pgraphics);

   }

} // namespace user




