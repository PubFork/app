#include "framework.h"


namespace user
{


   const int32_t g_base_menu_indent = 11;


   menu_list_window::menu_list_window():
      menu_list_window(get_app())
   {

      construct_user_style(schema_menu);

   }


   menu_list_window::menu_list_window(::aura::application * papp) :
      object(papp),
      menu(papp),
      m_itemClose(papp)
   {

      m_bAutoDelete        = true;
      m_bOwnItem           = false;
      m_puiNotify          = NULL;
      m_bAutoClose         = true;

   }


   menu_list_window::menu_list_window(::aura::application * papp, menu_item * pitem) :
      object(papp),
      menu(papp),
      m_itemClose(papp)
   {

      m_puiNotify          = NULL;
      m_bAutoClose         = true;
      m_bAutoDelete        = true;
      m_bOwnItem           = false;

   }


   menu_list_window::~menu_list_window()
   {

   }


   void menu_list_window::install_message_handling(::message::dispatch * pinterface)
   {

      menu::install_message_handling(pinterface);

      IGUI_WIN_MSG_LINK(WM_CREATE, pinterface, this, &menu_list_window::_001OnCreate);
      IGUI_WIN_MSG_LINK(WM_DESTROY, pinterface, this, &menu_list_window::_001OnDestroy);
      IGUI_WIN_MSG_LINK(WM_CLOSE, pinterface, this, &menu_list_window::_001OnClose);

   }

   
   void menu_list_window::_001OnCreate(signal_details * pobj)
   {

      UNREFERENCED_PARAMETER(pobj);

   }

   
   void menu_list_window::_001OnClose(signal_details * pobj)
   {
      
      destroy_menu();
      
   }


   void menu_list_window::_001OnDestroy(signal_details * pobj)
   {

      pobj->m_bRet = false;

   }

//   bool menu_list_window::track_popup_menu(::user::interaction * pwndParent, ::user::interaction * pwndNotify)
//   {
//      
//      ASSERT(pwndParent != NULL);
//      
//      return _TrackPopupMenu(pwndParent, pwndNotify);
//      
//   }
   

   bool menu_list_window::track_popup_menu(::user::interaction * puiNotify, ::user::interaction * puiParent)
   {

      if(!::user::menu::track_popup_menu(puiNotify, puiParent))
      {
       
         return false;
         
      }

//      if(!IsWindow())
//      {
//
//         if(!create_window(NULL, NULL, WS_VISIBLE | WS_CHILD, null_rect(), pwndParent, 0))
//            return false;
//
//         if(!m_itemClose.m_pui->create_window(null_rect(), this, ChildIdClose))
//            return false;
//
//         m_itemClose.m_pui->install_message_handling(this);
//
//         m_itemClose.m_button.set_window_text("r");
//         m_itemClose.m_button.m_pschema = m_pschema->m_pschemaSysMenuButton;
//      }

      update_command_ui(m_pitem);
//      _CreateButtons(m_pitem);

      //user::AppGet()->AddFrame(this);

  //    on_layout();

      rect rectClient;
//
//      pwndParent->GetClientRect(rectClient);
//
//
//      SetWindowPos(0, 0, 0, rectClient.width(), rectClient.height(), SWP_SHOWWINDOW | SWP_NOZORDER);

      puiParent->GetClientRect(rectClient);


      SetWindowPos(0, 0, 0, rectClient.width(), rectClient.height(), SWP_SHOWWINDOW | SWP_NOZORDER);

      SetTimer(::user::timer_update_menu_command_ui,300,NULL);

      return true;
   }


   bool menu_list_window::menu_fill(::user::interaction * puiFill, ::user::interaction * puiNotify)
   {

      m_puiNotify = puiNotify;

      if(!IsWindow())
      {

         if(!create_window(NULL,NULL,WS_VISIBLE | WS_CHILD,null_rect(),puiFill,0))
            return false;

      }
      else
      {
         
         if(GetParent() != puiFill)
         {
            
            SetParent(puiFill);
            
         }
         
      }
      
      if(m_itemClose.m_pui.is_null())
      {
       
         m_itemClose.m_pui = userstyle()->create_menu_button();
         
      }

      if(!m_itemClose.m_pui->IsWindow())
      {
         
         if(!m_itemClose.m_pui->create_window(null_rect(), this, ChildIdClose))
            return false;

         m_itemClose.m_pui->install_message_handling(this);

         m_itemClose.m_pui->set_window_text("r");
         
         m_itemClose.m_pui->select_user_style(::user::schema_system_menu_close);
         
         //m_itemClose.m_pui->m_pschema = m_pschema->m_pschemaSysMenuButton;
         
      }

      update_command_ui(m_pitem);
      
      create_buttons(m_pitem);

      on_layout();

      rect rectClient;

      puiFill->GetClientRect(rectClient);

      SetWindowPos(0, 0, 0, rectClient.width(), rectClient.height(), SWP_SHOWWINDOW | SWP_NOZORDER);

      SetTimer(::user::timer_update_menu_command_ui, 300, NULL);

      return true;
      
   }
   

   void menu_list_window::update_command_ui(menu_item * pitemParent)
   {
      
      if(m_puiNotify == NULL)
      {
         
         return;
         
      }

      if (pitemParent == NULL)
      {

         return;

      }

      if(pitemParent->m_spitema == NULL)
      {
         
         return;

      }

      ::user:: menu_command_ui commandui(get_app());

      commandui.m_pitema = pitemParent->m_spitema;

      for(int32_t i = 0; i < pitemParent->m_spitema->get_size(); i++)
      {

         menu_item * pitem = pitemParent->m_spitema->element_at(i);

         commandui.m_iIndex       = i;
         commandui.m_id           = pitem->m_id;
         commandui.m_pOther       = pitem->m_pui;

         if(m_puiNotify->on_simple_update(&commandui))
            continue;

         update_command_ui(pitem);

      }

   }


   void menu_list_window::_001OnTimer(::timer * ptimer)
   {
      
      ::user::menu::_001OnTimer(ptimer);
      
      if(ptimer->m_nIDEvent == ::user::timer_update_menu_command_ui)
      {
         
         update_command_ui(m_pitem);
         
         RedrawWindow();
         
      }

   }


   void menu_list_window::calc_size(menu_item * pitemParent, ::draw2d::graphics * pgraphics, int32_t & iMaxWidth, int32_t & iMaxHeight)
   {
      
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
      
      COLORREF crBackground = 0;

      get_color(crBackground, ::user::color_background);

      if ((crBackground & ARGB(255, 0, 0, 0)) != 0)
      {

         rect rectClient;

         GetClientRect(rectClient);

         pgraphics->FillSolidRect(rectClient, ARGB(255, 255, 255, 255));

      }

//      if(_001IsTranslucent())
//      {
//         class imaging & imaging = System.visual().imaging();
//         imaging.color_blend(
//            pgraphics,
//            rectClient,
//            RGB(200, 255, 255),
//            127);
//      }
//      else
//      {
//#ifdef WINDOWSEX
//         pgraphics->FillSolidRect(rectClient, Session.get_default_color(COLOR_WINDOW));
//#else
//         throw todo(get_app());
//#endif
//      }*/

      ::user::interaction::_001OnDraw(pgraphics);

   }


   bool menu_list_window::get_color(COLORREF & cr,e_color ecolor)
   {
      
      bool bOk = menu::get_color(cr,ecolor);

      if(ecolor == color_background)
      {
         cr &= 0x00ffffff;
         cr |= (84 << 24);
      }


      return bOk;

   }


   void menu_list_window::create_buttons(menu_item * pitemParent)
   {
      if(pitemParent->m_spitema == NULL)
         return;
      for(int32_t i = 0; i < pitemParent->m_spitema->get_size(); i++)
      {
         menu_item * pitem = pitemParent->m_spitema->element_at(i);
         if(!pitem->m_pui->IsWindow())
         {
            pitem->m_pui->create_window(null_rect(), this, pitem->m_id);
            pitem->m_pui->m_id = pitem->m_id;
            
            //if(pitem->m_bPopup)
            //{

            //   pitem->m_button.m_pschema = m_pschema->m_pschemaPopupButton;

            //}
            //else
            //{

            //   pitem->m_button.m_pschema = m_pschema->m_pschemaItemButton;

            //}

            pitem->m_pui->m_pmenuitem = pitem;

            pitem->m_pmenu = this;

         }
         
        create_buttons(pitem);
         
      }
      
   }
   

   bool menu_list_window::BaseOnControlEvent(::user::control_event * pevent)
   {

      sp(menu_item) pitemThis = get_item();
      
      sp(menu_item_ptra) spitema;
      
      if(pitemThis.is_set())
      {
         
         spitema = pitemThis->m_spitema;
         
      }

      if(pevent->m_eevent == ::user::event_button_clicked)
      {
         
         if(pevent->m_puie == m_itemClose.m_pui)
         {
            
            if(m_bAutoClose)
            {
               
               send_message(WM_CLOSE);
               
            }
            
            if(base_class < ::user::place_holder > ::bases(GetParent()))
            {
               
               GetParent()->GetParent()->send_message(m_uiMessage);
               
            }
            else
            {
            
               GetParent()->send_message(m_uiMessage);
            
            }
            
            return true;
            
         }
         else
         {
            
            if(pevent->m_puie->m_id != "separator" && pitemThis.is_set())
            {

               menu_item * pitem = pitemThis->find(pevent->m_puie->m_id);

               if(pitem != NULL && !pitem->m_bPopup)
               {
                  
                  if (m_puiNotify != NULL)
                  {

                     m_puiNotify->_001SendCommand(pitem->m_id);

                  }
                  
                  if(m_bAutoClose)
                  {
                     
                     send_message(WM_CLOSE);
                     
                  }
                  
                  if(base_class < ::user::place_holder > ::bases(GetParent()))
                  {
                     
                     GetParent()->GetParent()->send_message(m_uiMessage);
                     
                  }
                  else
                  {
                     
                     GetParent()->send_message(m_uiMessage);
                     
                  }
                  
                  return true;

               }
               
            }
            
         }
         
      }
      
      return false;
      
   }

   
   void menu_list_window::destroy_menu()
   {
      
      {
      
         interaction_spa uiptra = m_uiptraChild;
      
         for(index i = 0; i < uiptra.get_count(); i++)
         {
         
            uiptra[i]->DestroyWindow();
         
         }
         
      }
      
      m_uiptraChild.remove_all();
      
      ::user::menu::destroy_menu();
      
   }


} // namespace user




