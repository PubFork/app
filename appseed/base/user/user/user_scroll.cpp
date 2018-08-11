#include "framework.h"


namespace user
{


   scroll_x::scroll_x()
   {

      m_scrolldataHorz.m_bScroll = false;
      m_scrolldataHorz.m_iPage = 0;
      m_scrolldataHorz.m_iLine = 0;
      m_scrolldataHorz.m_bScrollEnable = true;
      m_scrolldataHorz.m_iWidth = GetSystemMetrics(SM_CXHSCROLL);

   }


   scroll_x::~scroll_x()
   {


   }


   void scroll_x::layout_scroll_bar()
   {

      rect rectClient;

      ::user::interaction::GetClientRect(rectClient);

      int32_t ifswp = SWP_SHOWWINDOW | SWP_NOCOPYBITS;

      _001DeferCreateXScrollBar();

      if (m_pscrollbarHorz != NULL)
      {

         if ( m_scrolldataHorz.m_bScroll)
         {

            _001GetXScrollInfo(m_pscrollbarHorz->m_scrollinfo);

            ::rect rectNewPos;

            rectNewPos.left = rectClient.left;
            rectNewPos.top = rectClient.bottom - GetSystemMetrics(SM_CYHSCROLL);
            rectNewPos.right = rectNewPos.left + rectClient.width() - get_final_y_scroll_bar_width();
            rectNewPos.bottom = rectNewPos.top + GetSystemMetrics(SM_CYHSCROLL);

            m_pscrollbarHorz->defer_set_window_pos(ZORDER_TOP, rectNewPos, ifswp);

         }
         else if(m_pscrollbarHorz->is_this_visible())
         {

            m_pscrollbarHorz->ShowWindow(SW_HIDE);

         }

      }

   }



   void scroll_x::_001OnDeferCreateXScrollBar()
   {

      if (m_scrolldataHorz.m_bScroll)
      {

         if (m_pscrollbarHorz == NULL)
            create_x_scroll_bar(null_rect());

      }


   }


   void scroll_x::_001DeferCreateXScrollBar()
   {

      bool bCreate = false;

      if (m_scrolldataHorz.m_bScroll)
      {

         if (m_pscrollbarHorz == NULL)
         {

            bCreate = true;

         }

      }


      if (bCreate)
      {

         _001OnDeferCreateXScrollBar();

      }

   }


   void scroll_x::_001OnHScroll(::message::message * pobj)
   {

      SCAST_PTR(::message::scroll, pscroll, pobj);

      {

         synch_lock slUser(m_pmutex);

         if (pscroll->m_nSBCode == SB_LINELEFT)
         {

            set_viewport_offset_x(get_viewport_offset().x - m_scrolldataHorz.m_iLine);

         }
         else if (pscroll->m_nSBCode == SB_PAGELEFT)
         {

            set_viewport_offset_x(get_viewport_offset().x - m_scrolldataHorz.m_iPage);

         }
         else if (pscroll->m_nSBCode == SB_PAGERIGHT)
         {

            set_viewport_offset_x(get_viewport_offset().x + m_scrolldataHorz.m_iPage);

         }
         else if (pscroll->m_nSBCode == SB_LINERIGHT)
         {

            set_viewport_offset_x(get_viewport_offset().x + m_scrolldataHorz.m_iLine);

         }
         else if (pscroll->m_nSBCode == SB_THUMBTRACK)
         {

            set_viewport_offset_x(pscroll->m_nPos);

         }
         else if (pscroll->m_nSBCode == SB_THUMBPOSITION)
         {

            set_viewport_offset_x(pscroll->m_nPos);

         }

      }

   }


   void scroll_x::on_change_viewport_offset()
   {

      synch_lock sl(m_pmutex);

      if (m_pscrollbarHorz.is_set())
      {

         m_pscrollbarHorz->m_scrollinfo.nPos = m_ptScrollPassword1.x;

      }

   }


   bool scroll_x::validate_viewport_offset(point & p)
   {

      if (p.x < 0)
      {

         p.x = 0;

      }
      else
      {

         size sizeTotal = get_total_size();

         size sizePage = get_page_size();

         if (p.x > MAX(0, sizeTotal.cx - sizePage.cx))
         {

            p.x = MAX(0, sizeTotal.cx - sizePage.cx);

         }

      }

      return true;

   }


   void scroll_x::install_message_routing(::message::sender * pinterface)
   {

      IGUI_MSG_LINK(WM_HSCROLL, pinterface, this, &scroll_x::_001OnHScroll);

   }


   void scroll_x::on_change_view_size()
   {

      size sizeTotal = get_total_size();

      m_scrolldataHorz.m_iWidth = GetSystemMetrics(SM_CXHSCROLL);

      rect rectClient;

      GetClientRect(rectClient);

      LONG iTotalHeight = sizeTotal.cy;

      LONG iTotalWidth = sizeTotal.cx;

      LONG iClientHeight = rectClient.height();

      LONG iClientWidth = rectClient.width();

      //LONG iScrollHeight = iClientHeight - GetSystemMetrics(SM_CYHSCROLL);

      LONG iScrollWidth = iClientWidth - GetSystemMetrics(SM_CXVSCROLL);

      m_scrolldataHorz.m_bScroll = false;

      if (iTotalWidth > iClientWidth)
      {

         m_scrolldataHorz.m_bScroll = true;

      }
      else if (iTotalHeight > iClientHeight)
      {

         if (iTotalWidth > iScrollWidth)
         {

            m_scrolldataHorz.m_bScroll = true;

         }

      }

      m_scrolldataHorz.m_bScroll = m_scrolldataHorz.m_bScrollEnable && m_scrolldataHorz.m_bScroll;

      rect rectScroll;

      GetClientRect(rectScroll);

      m_scrolldataHorz.m_iPage = rectScroll.width();

      if (validate_viewport_offset(m_ptScrollPassword1))
      {

         layout_scroll_bar();

         on_change_viewport_offset();

      }

   }


   int scroll_x::get_final_x_scroll_bar_width()
   {

      return m_scrolldataHorz.m_bScroll && m_scrolldataHorz.m_bScrollEnable ? m_scrolldataHorz.m_iWidth : 0;

   }











   scroll_y::scroll_y()
   {

      m_iWheelDeltaScroll = 3;
      m_scrolldataVert.m_bScroll = false;
      m_scrolldataVert.m_iPage = 0;
      m_scrolldataVert.m_iLine = 0;
      m_scrolldataVert.m_bScrollEnable = true;
      m_scrolldataVert.m_iWidth = GetSystemMetrics(SM_CYVSCROLL);

   }

   scroll_y::~scroll_y()
   {

   }


   void scroll_y::layout_scroll_bar()
   {

      rect rectClient;


      scroll_bar_get_client_rect(rectClient);

      int32_t ifswp = SWP_SHOWWINDOW | SWP_NOCOPYBITS;

      _001DeferCreateYScrollBar();

      if (m_pscrollbarVert != NULL)
      {

         if (m_scrolldataVert.m_bScroll)
         {

            _001GetYScrollInfo(m_pscrollbarVert->m_scrollinfo);

            ::rect rectNewPos;

            rectNewPos.left = rectClient.right - GetSystemMetrics(SM_CXVSCROLL);
            rectNewPos.top = rectClient.top;
            rectNewPos.right = rectNewPos.left + GetSystemMetrics(SM_CXVSCROLL);
            rectNewPos.bottom = rectNewPos.top+ rectClient.height() - get_final_x_scroll_bar_width();

            m_pscrollbarVert->defer_set_window_pos(ZORDER_TOP, rectNewPos, ifswp);

         }
         else
         {

            m_pscrollbarVert->ShowWindow(SW_HIDE);

         }

      }

   }



   void scroll_y::_001OnDeferCreateYScrollBar()
   {

      if (m_scrolldataVert.m_bScroll)
      {
         if (m_pscrollbarVert == NULL)
            create_y_scroll_bar(null_rect());
      }

   }



   void scroll_y::_001DeferCreateYScrollBar()
   {

      bool bCreate = false;

      if (m_scrolldataVert.m_bScroll)
      {

         if (m_pscrollbarVert == NULL)
         {

            bCreate = true;

         }

      }

      if (bCreate)
      {

         _001OnDeferCreateYScrollBar();

      }

   }


   void scroll_y::_001OnVScroll(::message::message * pobj)
   {


      SCAST_PTR(::message::scroll, pscroll, pobj);


      if (pscroll->m_nSBCode == SB_LINEUP)
      {

         set_viewport_offset_y(get_viewport_offset().y - m_scrolldataVert.m_iLine);

      }
      else if (pscroll->m_nSBCode == SB_PAGEUP)
      {

         set_viewport_offset_y(get_viewport_offset().y - m_scrolldataVert.m_iPage);

      }
      else if (pscroll->m_nSBCode == SB_PAGEDOWN)
      {

         set_viewport_offset_y(get_viewport_offset().y + m_scrolldataVert.m_iPage);

      }
      else if (pscroll->m_nSBCode == SB_LINEDOWN)
      {

         set_viewport_offset_y(get_viewport_offset().y + m_scrolldataVert.m_iLine);

      }
      else if (pscroll->m_nSBCode == SB_THUMBTRACK)
      {

         set_viewport_offset_y(pscroll->m_nPos);

      }
      else if (pscroll->m_nSBCode == SB_THUMBPOSITION)
      {

         set_viewport_offset_y(pscroll->m_nPos);

      }
   }



   int32_t scroll_y::get_wheel_scroll_delta()
   {

      return m_iWheelDeltaScroll;

   }



   void scroll_y::on_change_viewport_offset()
   {

      synch_lock sl(m_pmutex);

      if (m_pscrollbarVert.is_set())
      {

         m_pscrollbarVert->m_scrollinfo.nPos = m_ptScrollPassword1.y;

      }

   }


   void scroll_y::_001OnMouseWheel(::message::message * pobj)
   {

      if (!m_scrolldataVert.m_bScroll || !m_scrolldataVert.m_bScrollEnable)
      {

         return;

      }

      SCAST_PTR(::message::mouse_wheel, pmousewheel, pobj);

      if (pmousewheel->GetDelta() > 0)
      {
         if (m_iWheelDelta > 0)
         {
            m_iWheelDelta += pmousewheel->GetDelta();
         }
         else
         {
            m_iWheelDelta = pmousewheel->GetDelta();
         }
      }
      else if (pmousewheel->GetDelta() < 0)
      {
         if (m_iWheelDelta < 0)
         {
            m_iWheelDelta += pmousewheel->GetDelta();
         }
         else
         {
            m_iWheelDelta = pmousewheel->GetDelta();
         }
      }

      index iDelta = m_iWheelDelta / WHEEL_DELTA;

      m_iWheelDelta -= (int16_t)(WHEEL_DELTA * iDelta);

      index nPos = m_pscrollbarVert->m_scrollinfo.nPos - iDelta * get_wheel_scroll_delta();

      if (nPos < m_pscrollbarVert->m_scrollinfo.nMin)
         nPos = m_pscrollbarVert->m_scrollinfo.nMin;
      else if (nPos > m_pscrollbarVert->m_scrollinfo.nMax - m_pscrollbarVert->m_scrollinfo.nPage)
         nPos = m_pscrollbarVert->m_scrollinfo.nMax - m_pscrollbarVert->m_scrollinfo.nPage;

      m_pscrollbarVert->m_scrollinfo.nPos =  (int32_t) nPos;

      m_pscrollbarVert->send_scroll_message(SB_THUMBPOSITION);

      pmousewheel->set_lresult(0);

      pmousewheel->m_bRet = true;


   }


   bool scroll_y::validate_viewport_offset(point & p)
   {

      if (p.y < 0)
      {

         p.y = 0;

      }
      else
      {

         size sizeTotal = get_total_size();

         size sizePage = get_page_size();

         if (p.y > MAX(0, sizeTotal.cy - sizePage.cy))
         {

            p.y = MAX(0, sizeTotal.cy - sizePage.cy);

         }

      }

      return true;

   }




   void scroll_y::install_message_routing(::message::sender * pinterface)
   {

      interaction::install_message_routing(pinterface);

      IGUI_MSG_LINK(WM_VSCROLL, pinterface, this, &scroll_y::_001OnVScroll);
      IGUI_MSG_LINK(WM_MOUSEWHEEL, pinterface, this, &scroll_y::_001OnMouseWheel);

   }


   void scroll_y::on_change_view_size()
   {

      size sizeTotal = get_total_size();

      m_scrolldataVert.m_iWidth = GetSystemMetrics(SM_CXVSCROLL);

      rect rectClient;

      GetClientRect(rectClient);

      LONG iTotalHeight = sizeTotal.cy;

      LONG iTotalWidth = sizeTotal.cx;

      LONG iClientHeight = rectClient.height();

      LONG iClientWidth = rectClient.width();

      LONG iScrollHeight = iClientHeight - GetSystemMetrics(SM_CYHSCROLL);

      //LONG iscrollWidth = iClientWidth - GetSystemMetrics(SM_CXVSCROLL);

      m_scrolldataVert.m_bScroll = false;

      if (iTotalWidth > iClientWidth)
      {

         if (iTotalHeight > iScrollHeight)
         {

            m_scrolldataVert.m_bScroll = true;

         }

      }
      else if (iTotalHeight > iClientHeight)
      {

         m_scrolldataVert.m_bScroll = true;

      }

      m_scrolldataVert.m_bScroll = m_scrolldataVert.m_bScrollEnable && m_scrolldataVert.m_bScroll;

      rect rectScroll;

      GetClientRect(rectScroll);

      m_scrolldataVert.m_iPage = rectScroll.height();

      if (validate_viewport_offset(m_ptScrollPassword1))
      {

         layout_scroll_bar();

         on_change_viewport_offset();

      }

   }



   int scroll_y::get_final_y_scroll_bar_width()
   {

      return m_scrolldataVert.m_bScroll && m_scrolldataVert.m_bScrollEnable ? m_scrolldataVert.m_iWidth : 0;

   }

   //
   //void scroll_y::on_layout()
   //{

   //   BASE::on_layout();

   //   on_change_view_size();

   //}


   scroll::scroll()
   {
   }


   scroll::scroll(::aura::application * papp) :
      object(papp)
   {
   }

   scroll::~scroll()
   {
   }


   void scroll::install_message_routing(::message::sender * pinterface)
   {
      scroll_x::install_message_routing(pinterface);
      scroll_y::install_message_routing(pinterface);
   }

   void scroll::on_change_viewport_offset()
   {
      scroll_x::on_change_viewport_offset();
      scroll_y::on_change_viewport_offset();
      ::user::interaction::on_change_viewport_offset();
   }


   bool scroll::validate_viewport_offset(point & p)
   {

      bool xValidated = scroll_x::validate_viewport_offset(p);

      bool yValidated = scroll_y::validate_viewport_offset(p);

      bool iValidated = ::user::interaction::validate_viewport_offset(p);

      return (xValidated || yValidated) && iValidated;

   }


   void scroll::layout_scroll_bar()
   {
      scroll_x::layout_scroll_bar();
      scroll_y::layout_scroll_bar();
   }

   void scroll::on_change_view_size()
   {

      m_scrolldataHorz.m_bScroll = false;

      m_scrolldataVert.m_bScroll = false;



      size sizeTotal = get_total_size();

      rect rectClient;

      GetClientRect(rectClient);

      LONG iTotalHeight = sizeTotal.cy;

      LONG iTotalWidth = sizeTotal.cx;

      LONG iClientHeight = rectClient.height();

      LONG iClientWidth = rectClient.width();

      LONG iScrollHeight = iClientHeight - GetSystemMetrics(SM_CYHSCROLL);

      LONG iscrollWidth = iClientWidth - GetSystemMetrics(SM_CXVSCROLL);

      if (iTotalWidth > iClientWidth)
      {

         m_scrolldataHorz.m_bScroll = true;

         if (iTotalHeight > iScrollHeight)
         {

            m_scrolldataVert.m_bScroll = true;

         }

      }
      else if (iTotalHeight > iClientHeight)
      {

         m_scrolldataVert.m_bScroll = true;

         if (iTotalWidth > iscrollWidth)
         {

            m_scrolldataHorz.m_bScroll = true;

         }

      }

      m_scrolldataHorz.m_bScroll = m_scrolldataHorz.m_bScrollEnable && m_scrolldataHorz.m_bScroll;

      m_scrolldataVert.m_bScroll = m_scrolldataVert.m_bScrollEnable && m_scrolldataVert.m_bScroll;

      if (!m_scrolldataHorz.m_bScroll)
      {

         set_viewport_offset_x(0);

      }


      if (!m_scrolldataVert.m_bScroll)
      {

         set_viewport_offset_y(0);

      }


      rect rectScroll;

      GetClientRect(rectScroll);

      m_scrolldataHorz.m_iPage = rectScroll.width();

      m_scrolldataVert.m_iPage = rectScroll.height();

      if (validate_viewport_offset(m_ptScrollPassword1))
      {

         layout_scroll_bar();

         on_change_viewport_offset();

      }



   }


   void scroll_x::send_xscroll_message(int nSBCode)
   {

      sp(::message::scroll) pscroll = canew(::message::scroll(get_app()));

      pscroll->m_nSBCode = nSBCode;

      if (m_pscrollbarHorz.is_set())
      {

         pscroll->m_nPos = m_pscrollbarHorz->m_scrollinfo.nPos;

      }
      else
      {

         pscroll->m_nPos = get_viewport_offset().x;

      }

      pscroll->m_id = WM_HSCROLL;

      send(pscroll);

   }


   void scroll_x::create_x_scroll_bar(const RECT & rect)
   {

      if (m_pscrollbarHorz != NULL)
         return;

      scroll_bar * pbar = canew(simple_scroll_bar(get_app()));

      if (!pbar->create_window(::orientation_horizontal, WS_CHILD | WS_VISIBLE, null_rect(), this, 7000 + 1))
      {
         delete pbar;
         return;
      }

      m_pscrollbarHorz = pbar;

   }


   void scroll_x::scroll_left_line()
   {

      send_xscroll_message(SB_LINELEFT);

   }


   void scroll_x::scroll_right_line()
   {

      send_xscroll_message(SB_LINERIGHT);

   }


   void scroll_x::scroll_left_page()
   {

      send_xscroll_message(SB_PAGELEFT);

   }


   void scroll_x::scroll_right_page()
   {

      send_xscroll_message(SB_PAGERIGHT);

   }


   void scroll_x::scroll_horz(int nPos)
   {

      set_viewport_offset_x(nPos);

   }


   void scroll_y::send_yscroll_message(int nSBCode)
   {

      sp(::message::scroll) pscroll = canew(::message::scroll(get_app()));

      pscroll->m_nSBCode = nSBCode;

      if (m_pscrollbarVert.is_set())
      {

         pscroll->m_nPos = m_pscrollbarVert->m_scrollinfo.nPos;

      }
      else
      {

         pscroll->m_nPos = get_viewport_offset().y;

      }

      pscroll->m_id = WM_VSCROLL;

      send(pscroll);

   }


   void scroll_y::create_y_scroll_bar(const RECT & rect)
   {

      if (m_pscrollbarVert != NULL)
         return;

      scroll_bar * pbar = canew(simple_scroll_bar(get_app()));

      if (!pbar->create_window(::orientation_vertical, WS_CHILD | WS_VISIBLE, null_rect(), this, 7002))
      {
         delete pbar;
         return;
      }

      m_pscrollbarVert = pbar;

   }


   void scroll_y::scroll_down_line()
   {

      send_yscroll_message(SB_LINEDOWN);

   }


   void scroll_y::scroll_up_line()
   {

      send_yscroll_message(SB_LINEUP);

   }


   void scroll_y::scroll_up_page()
   {

      send_yscroll_message(SB_PAGEUP);

   }


   void scroll_y::scroll_down_page()
   {

      send_yscroll_message(SB_PAGEDOWN);

   }


   void scroll_y::scroll_vert(int nPos)
   {

      set_viewport_offset_y(nPos);

   }

   bool scroll::GetActiveClientRect(LPRECT lprect)
   {

      if (!::user::interaction::GetClientRect(lprect))
      {

         return false;

      }

      size sizeTotal = get_total_size();

      point ptOffset = get_viewport_offset();

      lprect->right = lprect->left + MIN(::width(lprect), sizeTotal.cx - m_scrolldataHorz.m_iPage - ptOffset.x);

      lprect->bottom = lprect->top + MIN(::height(lprect), sizeTotal.cy - m_scrolldataVert.m_iPage - ptOffset.y);

      return true;

   }


   bool scroll::GetClientRect(LPRECT lprect)
   {

      if(!::user::interaction::GetClientRect(lprect))
      {

         return false;

      }

      lprect->right -= get_final_y_scroll_bar_width();
      lprect->bottom -= get_final_x_scroll_bar_width();

      return true;

   }


   bool scroll::GetFocusRect(LPRECT lprect)
   {

      return ::user::interaction::GetClientRect(lprect);

   }


   ::size scroll::get_total_size()
   {

      return m_sizeTotal;

   }


   void scroll::defer_draw_scroll_gap(::draw2d::graphics * pgraphics)
   {

      if (m_scrolldataHorz.m_bScrollEnable && m_scrolldataHorz.m_bScroll
            && m_pscrollbarHorz.is_set() && m_pscrollbarHorz->m_pimpl.is_set()
            && m_scrolldataVert.m_bScrollEnable && m_scrolldataVert.m_bScroll
            && m_pscrollbarVert.is_set() && m_pscrollbarVert->m_pimpl.is_set())
      {

         rect rectClient;

         GetClientRect(rectClient);

         rect r;

         r.top = rectClient.bottom;
         r.left = rectClient.right;
         r.right = (LONG) (r.left + m_pscrollbarVert->m_pimpl->m_rectParentClientRequest.width());
         r.bottom = (LONG) (r.top + m_pscrollbarHorz->m_pimpl->m_rectParentClientRequest.height());

         pgraphics->fill_solid_rect(r, _001GetColor(color_scrollbar_background));

      }

   }


}  // namespace core



