#include "framework.h"




const int32_t simple_list_header_control::s_iDividerWidth = 4;

simple_list_header_control::simple_list_header_control(::aura::application * papp) :
   object(papp),
   ::user::list_header(papp)
{
   
      
   
}

simple_list_header_control::~simple_list_header_control()
{
}



void simple_list_header_control::install_message_routing(::message::sender * pinterface)
{
   ::user::list_header::install_message_routing(pinterface);
#ifdef WINDOWSEX
   IGUI_MSG_LINK(HDN_ENDTRACK, pinterface, this, &simple_list_header_control::_001OnEndTrack);
   IGUI_MSG_LINK(HDN_TRACK, pinterface, this, &simple_list_header_control::_001OnTrack);
   IGUI_MSG_LINK(HDN_ENDDRAG, pinterface, this, &simple_list_header_control::_001OnEndDrag);
#endif
   IGUI_MSG_LINK(WM_CREATE, pinterface, this, &simple_list_header_control::_001OnCreate);
   //IGUI_MSG_LINK(WM_LBUTTONDOWN, pinterface, this, &simple_list_header_control::_001OnLButtonDown);
   //IGUI_MSG_LINK(WM_LBUTTONUP, pinterface, this, &simple_list_header_control::_001OnLButtonUp);
   //IGUI_MSG_LINK(WM_MOUSEMOVE, pinterface, this, &simple_list_header_control::_001OnMouseMove);
}

/*int32_t simple_list_header_control::GetItemWidth(int32_t iItem)
{
   HDITEM hditem;

   hditem.mask = HDI_WIDTH | HDI_TEXT;

   char pszText[1024];

   hditem.pszText = pszText;
   hditem.cchTextMax = 1024;

   get_item(iItem, &hditem);

   return hditem.cxy;

}*/

void simple_list_header_control::_001OnEndTrack(::message::message * pobj)
{

   SCAST_PTR(::message::notify, pnotify, pobj);

   GetParent()->send_message(::user::list::MESSAGE_ENDCOLUMNHEADERTRACK);

   pnotify->m_bRet = false;

}


void simple_list_header_control::_001OnTrack(::message::message * pobj)
{

   SCAST_PTR(::message::notify, pnotify, pobj);

   GetParent()->send_message(::user::list::MESSAGE_COLUMNHEADERTRACK);

   pnotify->m_bRet = false;

}


void simple_list_header_control::_001OnCreate(::message::message * pobj) 
{

   SCAST_PTR(::message::create, pcreate, pobj);

   pcreate->m_bRet = false;

}


void simple_list_header_control::_001OnEndDrag(::message::message * pobj)
{

   SCAST_PTR(::message::notify, pnotify, pobj);

   GetParent()->send_message(::user::list::MESSAGE_ENDCOLUMNHEADERDRAG);

   pnotify->set_lresult(FALSE);
   
   pnotify->m_bRet = false;
   
}

/*void simple_list_header_control::OnGetDispInfo(NMHDR* pNMHDR, LRESULT* pResult)
{
   LPNMHDDISPINFO lpdi = (LPNMHDDISPINFO) pNMHDR;
   CTransparentWndInterface * ptwi = NULL;
   CTransparentWndInterface::CGetProperty getp;
   getp.m_eproperty = CTransparentWndInterface::PropertyInterface;
   GetParent()->SendMessage(CTransparentWndInterface::MessageGetProperty, 0, (LPARAM) &getp);
   ptwi = getp.m_pinterface;
   if(ptwi != NULL)
   {
      ::user::list * plist = dynamic_cast<::user::list *>(ptwi);
      if(plist != NULL)
      {
         if(lpdi->mask & HDI_TEXT
            && lpdi->iItem >= 0 &&
            lpdi->iItem < plist->_001GetColumnCount())
         {
            string & str = m_strBuffer;
            str.load_string(plist->_001GetColumnTextId(lpdi->iItem));
            lpdi->pszText = (LPTSTR) (const char *) str;
            lpdi->cchTextMax = str.get_length();
         }*/
/*         if(lpdi->mask & HDI_TEXT
            && lpdi->lParam >= 0 &&
            lpdi->lParam < plist->_001GetColumnCount())
         {
            string & str = m_strBuffer;
            str.load_string(plist->_001GetColumnTextId(lpdi->lParam));
            lpdi->pszText = (LPTSTR) (const char *) str;
            lpdi->cchTextMax = str.get_length();
         }
      }
   }

}*/

/*LPARAM simple_list_header_control::GetItemLParam(int32_t iItem)
{
   HDITEM hditem;

   hditem.mask = HDI_LPARAM;

   get_item(iItem, &hditem);

   return hditem.lParam;
}*/

bool simple_list_header_control::create_window(UINT nStyle, const RECT & rect, sp(::user::interaction)pwndParent, UINT nID)
{
   return ::user::interaction::create_window(NULL, NULL, nStyle, rect, pwndParent, nID) != 0;
}



