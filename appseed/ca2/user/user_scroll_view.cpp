#include "framework.h"


namespace user
{


   scroll_view::scroll_view(::ca::application * papp) :
      ca(papp)
   {

      m_pscrollbarHorz = NULL;
      m_pscrollbarVert = NULL;


      m_scrollinfo.m_ptScroll.x = 0;
      m_scrollinfo.m_ptScroll.y = 0;
      m_scrollinfo.m_rectMargin.left = 0;
      m_scrollinfo.m_rectMargin.top = 0;
      m_scrollinfo.m_rectMargin.right = 0;
      m_scrollinfo.m_rectMargin.bottom = 0;
      m_scrollinfo.m_bVScroll = false;
      m_scrollinfo.m_bHScroll = false;
      m_scrollinfo.m_sizeTotal.cx = 0;
      m_scrollinfo.m_sizeTotal.cy = 0;
      m_scrollinfo.m_sizePage.cx = 0;
      m_scrollinfo.m_sizePage.cy = 0;
      m_scrollinfo.m_sizeLine.cx = 0;
      m_scrollinfo.m_sizeLine.cy = 0;

   }

   scroll_view::~scroll_view()
   {
   }

   void scroll_view::GetClientRect(LPRECT lprect)
   {
      rect rectClient;
      control::GetClientRect(rectClient);
      /*rectClient.left               += m_scrollinfo.m_rectMargin.left;
      rectClient.top                += m_scrollinfo.m_rectMargin.top;
      rectClient.right              += m_scrollinfo.m_rectMargin.right;
      rectClient.bottom             += m_scrollinfo.m_rectMargin.bottom;*/
      m_scrollinfo.m_iScrollHeight  = GetSystemMetrics(SM_CYHSCROLL);
      m_scrollinfo.m_iScrollWidth   = GetSystemMetrics(SM_CXVSCROLL);

      m_scrollinfo.m_sizeClient.cx = rectClient.width();
      if(m_scrollinfo.m_bVScroll)
      {
         m_scrollinfo.m_sizeClient.cx -= m_scrollinfo.m_iScrollWidth;
      }
      m_scrollinfo.m_sizeClient.cy = rectClient.height();
      if(m_scrollinfo.m_bHScroll)
      {
         m_scrollinfo.m_sizeClient.cy -= m_scrollinfo.m_iScrollHeight;
      }
      
      m_scrollinfo.m_sizePage.cx    = m_scrollinfo.m_sizeClient.cx;
      m_scrollinfo.m_sizePage.cy    = m_scrollinfo.m_sizeClient.cy;

      if(rectClient.area() <= 0)
      {
         m_scrollinfo.m_bHScroll = false;
         m_scrollinfo.m_bVScroll = false;
      }
      else
      {
         m_scrollinfo.m_bVScroll       = (m_scrollinfo.m_sizeTotal.cy + m_scrollinfo.m_rectMargin.height()) > (rectClient.height() - m_scrollinfo.m_iScrollHeight);
         m_scrollinfo.m_bHScroll       = (m_scrollinfo.m_sizeTotal.cx + m_scrollinfo.m_rectMargin.width()) > (rectClient.width() - m_scrollinfo.m_iScrollWidth);
      }

      _001UpdateScrollBars();

      *lprect = rectClient;
   }

   void scroll_view::_001LayoutScrollBars()
   {
      rect rectClient;

      GetClientRect(rectClient);
       
      int ifswp = SWP_SHOWWINDOW | SWP_NOCOPYBITS;

      _001DeferCreateScrollBars();

      if(m_pscrollbarHorz != NULL)
      {
         if(m_scrollinfo.m_bHScroll)
         {
            m_pscrollbarHorz->SetWindowPos(ZORDER_TOP, 0, rectClient.bottom - m_scrollinfo.m_iScrollHeight, rectClient.width() - m_scrollinfo.m_iScrollWidth, m_scrollinfo.m_iScrollHeight, ifswp);
         }
         else
         {
            m_pscrollbarHorz->ShowWindow(SW_HIDE);
         }
      }

      if(m_pscrollbarVert != NULL)
      {
         if(m_scrollinfo.m_bVScroll)
         {
            m_pscrollbarVert->SetWindowPos(ZORDER_TOP, rectClient.right - m_scrollinfo.m_iScrollWidth, rectClient.top, m_scrollinfo.m_iScrollWidth, rectClient.height() - m_scrollinfo.m_iScrollHeight - rectClient.top, ifswp);
         }
         else
         {
            m_pscrollbarVert->ShowWindow(SW_HIDE);
         }
      }
       
   }


   void scroll_view::_001DeferCreateScrollBars()
   {

      if(m_scrollinfo.m_bHScroll)
      {
         if(m_pscrollbarHorz == NULL)
            create_scroll_bar(scroll_bar::orientation_horizontal);

      }

      if(m_scrollinfo.m_bVScroll)
      {
         if(m_pscrollbarVert == NULL)
            create_scroll_bar(scroll_bar::orientation_vertical);
      }
       
   }

   void scroll_view::_001OnCreate(gen::signal_object * pobj)
   {

      SCAST_PTR(::gen::message::create, pcreate, pobj);

      if(pcreate->previous())
         return;

   }

   void scroll_view::_001OnSize(gen::signal_object * pobj)
   {
      pobj->previous();
      _001LayoutScrollBars();
   }

   void scroll_view::_001OnUser9654(gen::signal_object * pobj) 
   {
      SCAST_PTR(::gen::message::base, pbase, pobj);
      if(pbase->m_wparam == 0)
      {
         if(pbase->m_lparam == 0)
         {
            _001RedrawWindow();
         }
      }
   }

   void scroll_view::_001OnVScroll(gen::signal_object * pobj) 
   {
      
      
      SCAST_PTR(::gen::message::scroll, pscroll, pobj);


      keeper < bool > keepVScroll(&m_scrollinfo.m_bVScroll, true, false, true);


      m_scrollinfo.m_ptScroll.y = pscroll->m_nPos;


      _001OnUpdateScrollPosition();


      PostMessage(WM_USER + 9654, 0, 0);

      
   }


   void scroll_view::_001OnHScroll(gen::signal_object * pobj) 
   {
      
      
      SCAST_PTR(::gen::message::scroll, pscroll, pobj);
      
      
      keeper < bool > keepHScroll(&m_scrollinfo.m_bHScroll, true, false, true);
      
      
      m_scrollinfo.m_ptScroll.x = pscroll->m_nPos;
      
      
      _001OnUpdateScrollPosition();


      PostMessage(WM_USER + 9654, 0, 0);


   }

   int scroll_view::get_wheel_scroll_delta()
   {

      return 1;

   }

   void scroll_view::_001OnUpdateScrollPosition()
   {
      
      
      _001UpdateScrollBars();


   }


   void scroll_view::_001OnMouseWheel(gen::signal_object * pobj)
   {
      
      SCAST_PTR(::gen::message::mouse_wheel, pmousewheel, pobj);

      if(pmousewheel->GetDelta() > 0)
      {
         if(m_iWheelDelta > 0)
         {
            m_iWheelDelta += pmousewheel->GetDelta();
         }
         else
         {
            m_iWheelDelta = pmousewheel->GetDelta();
         }
      }
      else if(pmousewheel->GetDelta() < 0)
      {
         if(m_iWheelDelta < 0)
         {
            m_iWheelDelta += pmousewheel->GetDelta();
         }
         else
         {
            m_iWheelDelta = pmousewheel->GetDelta();
         }
      }

      index iDelta = m_iWheelDelta / WHEEL_DELTA;

      m_iWheelDelta -= (short) (WHEEL_DELTA * iDelta);

      m_scrollinfo.m_ptScroll.y -= (LONG) (iDelta * get_wheel_scroll_delta());

      if(m_scrollinfo.m_ptScroll.y > m_scrollinfo.m_sizeTotal.cy + m_scrollinfo.m_rectMargin.bottom)
         m_scrollinfo.m_ptScroll.y = m_scrollinfo.m_sizeTotal.cy + m_scrollinfo.m_rectMargin.bottom; 


      _001OnUpdateScrollPosition();

      



      pmousewheel->set_lresult(0);
      pmousewheel->m_bRet = true;


   }


   void scroll_view::_001UpdateScrollBars()
   {

      _001DeferCreateScrollBars();

      if(m_scrollinfo.m_ptScroll.y < m_scrollinfo.m_rectMargin.top)
      {
         m_scrollinfo.m_ptScroll.y = m_scrollinfo.m_rectMargin.top;
      }
      else
      {
         if(m_scrollinfo.m_ptScroll.y > m_scrollinfo.m_sizeTotal.cy + m_scrollinfo.m_rectMargin.bottom)
            m_scrollinfo.m_ptScroll.y = m_scrollinfo.m_sizeTotal.cy + m_scrollinfo.m_rectMargin.bottom; 
      }

      if(m_scrollinfo.m_ptScroll.x < m_scrollinfo.m_rectMargin.left)
      {
         m_scrollinfo.m_ptScroll.x = m_scrollinfo.m_rectMargin.left;
      }
      else
      {
         if(m_scrollinfo.m_ptScroll.x > m_scrollinfo.m_sizeTotal.cx + m_scrollinfo.m_rectMargin.right)
            m_scrollinfo.m_ptScroll.x = m_scrollinfo.m_sizeTotal.cx + m_scrollinfo.m_rectMargin.right; 
      }

      ::user::scroll_info si;

      if(m_pscrollbarHorz != NULL)
      {
         si.fMask       = SIF_ALL;
         si.nMin        = m_scrollinfo.m_rectMargin.left;
         si.nMax        = m_scrollinfo.m_sizeTotal.cx + m_scrollinfo.m_rectMargin.right;
         si.nPage       = (uint) m_scrollinfo.m_sizePage.cx;
         si.nPos        = m_scrollinfo.m_ptScroll.x;
         si.nTrackPos   = m_scrollinfo.m_ptScroll.x;
         m_pscrollbarHorz->_001SetScrollInfo(&si);
      }

      if(m_pscrollbarVert != NULL)
      {
         si.fMask       = SIF_ALL;
         si.nMin        = m_scrollinfo.m_rectMargin.top;
         si.nMax        = m_scrollinfo.m_sizeTotal.cy + m_scrollinfo.m_rectMargin.bottom;
         si.nPage       = (uint) m_scrollinfo.m_sizePage.cy;
         si.nPos        = m_scrollinfo.m_ptScroll.y;
         si.nTrackPos   = m_scrollinfo.m_ptScroll.y;
         m_pscrollbarVert->_001SetScrollInfo(&si);
      }


   }



   void scroll_view::install_message_handling(::gen::message::dispatch * pinterface)
   {
      
      
      control::install_message_handling(pinterface);

      IGUI_WIN_MSG_LINK(WM_CREATE,          pinterface, this, &scroll_view::_001OnCreate);
      IGUI_WIN_MSG_LINK(WM_SIZE,            pinterface, this, &scroll_view::_001OnSize);
      IGUI_WIN_MSG_LINK(WM_VSCROLL,         pinterface, this, &scroll_view::_001OnVScroll);
      IGUI_WIN_MSG_LINK(WM_HSCROLL,         pinterface, this, &scroll_view::_001OnHScroll);
      IGUI_WIN_MSG_LINK(WM_MOUSEWHEEL,      pinterface, this, &scroll_view::_001OnMouseWheel);

      IGUI_WIN_MSG_LINK(WM_USER + 9654,     pinterface, this, &scroll_view::_001OnUser9654);


   }


   void scroll_view::create_scroll_bar(scroll_bar::e_orientation eorientation)
   {

      if(eorientation == scroll_bar::orientation_horizontal)
      {
         if(m_pscrollbarHorz != NULL)
            return;
      }
      else
      {
         if(m_pscrollbarVert != NULL)
            return;
      }
      
      scroll_bar * pbar = new simple_scroll_bar(get_app());

      class rect rectNull;

      rectNull.null();

      if(!pbar->create(eorientation, WS_CHILD | WS_VISIBLE, rectNull, this, 7000 + eorientation))
      {
         delete pbar;
         return;
      }

      if(eorientation == scroll_bar::orientation_horizontal)
      {
         m_pscrollbarHorz = pbar;
      }
      else
      {
         m_pscrollbarVert = pbar;
      }
      
   }


   void scroll_view::_001GetViewRect(LPRECT lprect)
   {

      GetClientRect(lprect);

   }



   void scroll_view::_001GetViewClientRect(LPRECT lprect)
   {

      rect rectClient;

      GetClientRect(rectClient);

      rect rectTotal;

      _001GetViewRect(&rectTotal);


      index iTotalHeight = (index)rectTotal.height();

      index iTotalWidth = (index)rectTotal.width();

      index iClientHeight = (index)rectClient.height();

      index iClientWidth = (index)rectClient.width();

      index iScrollHeight =  iClientHeight - GetSystemMetrics(SM_CYHSCROLL);

      index iScrollWidth = iClientWidth - GetSystemMetrics(SM_CXVSCROLL);

      bool bHScroll = false;

      bool bVScroll = false;

      if(iTotalWidth > iClientWidth)
      {
         bHScroll = true;
         if(iTotalHeight > iScrollHeight)
         {
            bVScroll = true;
         }
      }
      else if(iTotalHeight > iClientHeight)
      {
         bVScroll = true;
         if(iTotalWidth > iScrollWidth)
         {
            bHScroll = true;
         }
      }

      lprect->left = 0;
      lprect->top = 0;

      if(bVScroll)
         lprect->right = (LONG) (lprect->left + iScrollWidth);
      else
         lprect->right = (LONG) (lprect->left + iClientWidth);
      if(bHScroll)
         lprect->bottom = (LONG) (lprect->top + iScrollHeight);
      else
         lprect->bottom = (LONG) (lprect->top + iClientHeight);

   }


   void scroll_view::SetScrollSizes()
   {

      rect rectTotal;

      _001GetViewRect(&rectTotal);

      size sizeTotal = rectTotal.size();

      m_scrollinfo.m_sizeTotal = sizeTotal;

      rect rectViewClient;
      _001GetViewClientRect(&rectViewClient);

      m_scrollinfo.m_sizeTotal = sizeTotal;
      m_scrollinfo.m_sizePage = rectViewClient.size();

      if(m_scrollinfo.m_ptScroll.y > (m_scrollinfo.m_sizeTotal.cy - m_scrollinfo.m_sizePage.cy))
      {
         m_scrollinfo.m_ptScroll.y = (m_scrollinfo.m_sizeTotal.cy - m_scrollinfo.m_sizePage.cy);
      }

   }


}  // namespace ex1



