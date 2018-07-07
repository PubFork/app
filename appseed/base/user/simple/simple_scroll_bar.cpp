#include "framework.h" // from "base/user/user.h"
#include "simple_scroll_bar.h"


void constraint(POINT & pt, LPCRECT lpcrect)
{

   if (pt.x < lpcrect->left)
   {

      pt.x = lpcrect->left;

   }
   else if (pt.x > lpcrect->right)
   {

      pt.x = lpcrect->right;

   }

   if (pt.y < lpcrect->top)
   {

      pt.y = lpcrect->top;

   }
   else if (pt.y > lpcrect->bottom)
   {

      pt.y = lpcrect->bottom;

   }

}


simple_scroll_bar::simple_scroll_bar(::aura::application * papp) :
   ::object(papp),
   ::user::interaction(papp),
   m_penDraw(allocer()),
   m_brushDraw(allocer()),
   m_rgnA(allocer()), // região da primeira seta
   m_rgnB(allocer()) // região da segunda seta
{
   //m_brushNull->CreateStockObject(NULL_BRUSH);
   m_flagNonClient.unsignalize(non_client_background);
   // m_flagNonClient.unsignalize(non_client_focus_rect);
   m_bTracking          = false;
   m_scrollinfo.nMin    = 0;
   m_scrollinfo.nMax    = 100;
   m_scrollinfo.nPage   = 10;
   m_scrollinfo.nPos    = 0;


   //m_cr = ARGB(127,180,80,120);
   //m_crStrong = ARGB(150, 150, 150, 150);
   //m_crBorder = ARGB(184,180, 180, 180);
   //m_crLiteBorder = ARGB(184,84 + 23,84 + 23,77 + 23);

   //m_crHover = ARGB(100,190,180,250);
   //m_crHoverStrong = ARGB(130, 190, 180, 250);
   //m_crHoverBorder = ARGB(184,160,150,180);
   //m_crHoverLiteBorder = ARGB(184,84 + 23 - 23,84 + 23,77 + 23 + 84);

}

simple_scroll_bar::~simple_scroll_bar()
{
}


void simple_scroll_bar::install_message_routing(::message::sender * pinterface)
{
   ::user::control::install_message_routing(pinterface);
   IGUI_MSG_LINK(WM_MOUSEMOVE, pinterface, this, &simple_scroll_bar::_001OnMouseMove);
   IGUI_MSG_LINK(WM_LBUTTONDOWN, pinterface, this, &simple_scroll_bar::_001OnLButtonDown);
   IGUI_MSG_LINK(WM_LBUTTONUP, pinterface, this, &simple_scroll_bar::_001OnLButtonUp);
   IGUI_MSG_LINK(WM_HSCROLL, pinterface, this, &simple_scroll_bar::_001OnHScroll);
   IGUI_MSG_LINK(WM_CREATE, pinterface, this, &simple_scroll_bar::_001OnCreate);
   IGUI_MSG_LINK(WM_SHOWWINDOW, pinterface, this, &simple_scroll_bar::_001OnShowWindow);
   IGUI_MSG_LINK(WM_DESTROY, pinterface, this, &simple_scroll_bar::_001OnDestroy);

}


bool simple_scroll_bar::create_window(const char * lpszClassName, const char * lpszWindowName, uint32_t dwStyle,const RECT & rect, sp(::user::interaction) pParentWnd, UINT nID, ::create * pcreate)
{

   if(!::user::interaction::create_window(lpszClassName,lpszWindowName,dwStyle,rect,pParentWnd,nID,pcreate))
      return false;

   return true;

}


bool simple_scroll_bar::create_window(e_orientation eorientation,uint32_t dwStyle,const RECT & rect,sp(::user::interaction)pParentWnd,UINT nID)
{

   if(!::user::scroll_bar::create_window(eorientation, dwStyle, rect, pParentWnd, nID))
      return false;

   return true;

}


void simple_scroll_bar::_001OnMouseMove(::message::message * pobj)
{

   SCAST_PTR(::message::mouse, pmouse, pobj);

   point pt = pmouse->m_pt;

   ScreenToClient(&pt);

   if(m_bTracking)
   {

      pt -= m_ptTrackOffset;

      SetTrackingPos(pt);

      send_scroll_message(SB_THUMBTRACK);

      pmouse->set_lresult(1);

      pmouse->m_bRet = true;

      pmouse->m_ecursor = ::visual::cursor_arrow;

   }
   else
   {

      ::user::e_element eelement;

      if(hit_test(pmouse->m_pt,eelement) >= 0)
      {

         pmouse->m_ecursor = ::visual::cursor_arrow;

      }

   }


}


bool simple_scroll_bar::scrollbar_action(::user::e_element eelement, point pt)
{

   switch(m_eelement)
   {
   case ::user::element_scrollbar_rectA:
      return scrollbar_lineA();
   case ::user::element_scrollbar_rectB:
      return scrollbar_lineB();
   case ::user::element_scrollbar_pageA:
      return scrollbar_pageA(pt);
   case ::user::element_scrollbar_pageB:
      return scrollbar_pageB(pt);
   default:
      return false;
   }

}

void simple_scroll_bar::_001OnLButtonDown(::message::message * pobj)
{

   SCAST_PTR(::message::mouse, pmouse, pobj);

   point pt = pmouse->m_pt;

   ScreenToClient(&pt);

   m_eelement = ::user::element_none;

   if(hit_test(pmouse->m_pt,m_eelement) < 0)
   {

      pmouse->m_bRet = false;

      return;

   }

   pmouse->m_bRet = true;

   pmouse->set_lresult(1);

   SetCapture();

   if(m_eelement == ::user::element_scrollbar_rect)
   {

      m_bTracking = true;

      m_ptTrack = pt;

      GetTrackRect(m_rectTrack);

      m_ptTrackOffset = m_ptTrack - m_rectTrack.top_left();

      set_need_redraw();

   }
   else
   {

      if(scrollbar_action(m_eelement, pt))
      {

         SetTimer((uint_ptr) this,300,NULL);

      }

   }

}

void simple_scroll_bar::_001OnLButtonUp(::message::message * pobj)
{

   SCAST_PTR(::message::mouse,pmouse,pobj);

   m_eelement = ::user::element_none;

   KillTimer(((uint_ptr)this));

   KillTimer(((uint_ptr)this)+1);

   ReleaseCapture();

   pmouse->m_bRet = false;

   simple_scroll_bar * pcapture = Session.GetCapture().cast < simple_scroll_bar >();

   if((pcapture != NULL && pcapture == this) || m_bTracking)
   {



      bool bWasTracking = m_bTracking;

      m_bTracking = false;

      if(bWasTracking)
      {

         point pt = pmouse->m_pt;

         ScreenToClient(&pt);

         pt -= m_ptTrackOffset;

         SetTrackingPos(pt);

      }

      send_scroll_message(SB_THUMBPOSITION);

      set_need_redraw();

   }

}


bool simple_scroll_bar::GetTrackRect(LPRECT lpRect)
{

   rect rectClient;

   GetClientRect(rectClient);

   size sizeTrack;

   GetTrackSize(sizeTrack);

   int32_t iPos;

   if (m_bTracking)
   {

      iPos = m_scrollinfo.nTrackPos;

   }
   else
   {

      iPos = m_scrollinfo.nPos;

   }

   if(m_eorientation == orientation_horizontal)
   {

      int32_t iWidth = rectClient.width() - GetSystemMetrics(SM_CXHSCROLL) * 2 - sizeTrack.cx;

      lpRect->top = rectClient.top;

      lpRect->bottom = rectClient.top + sizeTrack.cy;

      if (m_scrollinfo.nMax - m_scrollinfo.nMin - m_scrollinfo.nPage == 0)
      {

         lpRect->left = 0;

      }
      else
      {

         lpRect->left = GetSystemMetrics(SM_CXHSCROLL) + (iPos - m_scrollinfo.nMin) * iWidth / (m_scrollinfo.nMax - m_scrollinfo.nMin - m_scrollinfo.nPage);

      }

      lpRect->right = lpRect->left + sizeTrack.cx;

   }
   else if(m_eorientation == orientation_vertical)
   {

      int32_t iHeight = rectClient.height() - GetSystemMetrics(SM_CYVSCROLL) * 2 - sizeTrack.cy;

      lpRect->left = rectClient.left;

      lpRect->right = lpRect->left + sizeTrack.cx;

      if (m_scrollinfo.nMax - m_scrollinfo.nMin - m_scrollinfo.nPage == 0)
      {

         lpRect->top = 0;

      }
      else
      {

         lpRect->top = GetSystemMetrics(SM_CYVSCROLL) + (iPos - m_scrollinfo.nMin) * iHeight / (m_scrollinfo.nMax - m_scrollinfo.nMin - m_scrollinfo.nPage);

      }

      lpRect->bottom = lpRect->top + sizeTrack.cy;

   }

   return true;

}


bool simple_scroll_bar::_001GetScrollInfo(::user::scroll_info * lpsi)
{
   if(lpsi->fMask & SIF_PAGE)
   {
      lpsi->nPage = m_scrollinfo.nPage;
   }
   if(lpsi->fMask & SIF_POS)
   {
      lpsi->nPos = m_scrollinfo.nPos ;
   }
   if(lpsi->fMask & SIF_RANGE)
   {
      lpsi->nMin = m_scrollinfo.nMin;
      lpsi->nMax = m_scrollinfo.nMax;
   }
   if(lpsi->fMask & SIF_TRACKPOS)
   {
      lpsi->nTrackPos = m_scrollinfo.nTrackPos;
   }
   return TRUE;
}

bool simple_scroll_bar::_001SetScrollInfo(::user::scroll_info * lpsi, bool bRedraw)
{
   if(lpsi->fMask & SIF_PAGE)
   {
      m_scrollinfo.nPage = lpsi->nPage;
   }
   if(lpsi->fMask & SIF_RANGE)
   {
      m_scrollinfo.nMin = lpsi->nMin;
      m_scrollinfo.nMax = lpsi->nMax;
   }
   if(lpsi->fMask & SIF_POS)
   {
      m_scrollinfo.nPos = lpsi->nPos ;
      if(m_scrollinfo.nPos < m_scrollinfo.nMin)
      {
         m_scrollinfo.nPos = m_scrollinfo.nMin;
      }
      else if(m_scrollinfo.nPos > m_scrollinfo.nMax - m_scrollinfo.nPage)
      {
         m_scrollinfo.nPos = m_scrollinfo.nMax - m_scrollinfo.nPage;
      }
   }
   if(lpsi->fMask & SIF_TRACKPOS)
   {
      m_scrollinfo.nTrackPos = lpsi->nTrackPos;
   }
   if(bRedraw)
   {
      //      Redraw();
   }
   return TRUE;
   m_scrollinfo.fMask = SIF_ALL;
   // trans   ::user::interaction::SetScrollInfo(SB_CTL, &m_scrollinfo);
   return true;
}


bool simple_scroll_bar::GetTrackClientRect(LPRECT lpRect)
{

   rect rectClient;

   GetClientRect(rectClient);

   if(m_eorientation == orientation_horizontal)
   {
//      int32_t iWidth = rectClient.width() - GetSystemMetrics(SM_CXHSCROLL) * 2;
      lpRect->bottom = rectClient.bottom;
      lpRect->top = rectClient.top;
      lpRect->left = rectClient.left + GetSystemMetrics(SM_CXHSCROLL);
      lpRect->right = rectClient.right - GetSystemMetrics(SM_CXHSCROLL);
   }
   else if(m_eorientation == orientation_vertical)
   {
//      int32_t iWidth = rectClient.width() - GetSystemMetrics(SM_CYVSCROLL) * 2;
      lpRect->top = rectClient.top + GetSystemMetrics(SM_CYVSCROLL);
      lpRect->bottom = rectClient.bottom - GetSystemMetrics(SM_CYVSCROLL);
      lpRect->left = rectClient.left + 1;
      lpRect->right = rectClient.right - 1;
   }

   return true;

}


int32_t simple_scroll_bar::GetTrackSize(size &size)
{

   rect rectClient;

   GetClientRect(rectClient);

   if(m_eorientation == orientation_horizontal)
   {

      int32_t iWidth = rectClient.width() - GetSystemMetrics(SM_CXHSCROLL) * 2;

      int32_t cx = 0;

      if(iWidth > 0)
      {

         int32_t iRange = (m_scrollinfo.nMax - m_scrollinfo.nMin);

         if (iRange == 0)
         {

            cx = 0;

         }
         else
         {

            cx = (m_scrollinfo.nPage  * iWidth) / iRange;

         }

      }

      if (cx < 5)
      {

         cx = 5;

      }

      size.cx = cx;

      size.cy = rectClient.height();

   }
   else if(m_eorientation == orientation_vertical)
   {

      int32_t iHeight = rectClient.height() - GetSystemMetrics(SM_CYVSCROLL) * 2;

      int32_t cy = 0;

      if(iHeight > 0)
      {

         int32_t iRange = (m_scrollinfo.nMax - m_scrollinfo.nMin);

         if (iRange == 0)
         {

            cy = 0;

         }
         else
         {

            cy = (m_scrollinfo.nPage  * iHeight) / iRange;

         }

      }

      if (cy < 5)
      {

         cy = 5;

      }

      size.cy = cy;

      size.cx = rectClient.width();

   }

   return true;

}


int32_t simple_scroll_bar::SetTrackingPos(point point)
{

   int32_t nPos = 0;

   size sizeTrack;

   GetTrackSize(sizeTrack);

   rect rectClient;

   GetClientRect(rectClient);

   if(m_eorientation == orientation_horizontal)
   {

      int32_t iWidth = rectClient.width() - GetSystemMetrics(SM_CXHSCROLL) * 2 - sizeTrack.cx;

      double dRate = (double)(point.x - GetSystemMetrics(SM_CXHSCROLL)) / (double)iWidth;

      dRate = MIN(1.0, dRate);

      nPos = (int32_t)(dRate * (m_scrollinfo.nMax - m_scrollinfo.nMin - m_scrollinfo.nPage));

      nPos += m_scrollinfo.nMin;

   }
   else if(m_eorientation == orientation_vertical)
   {

      int32_t iHeight = rectClient.height() - GetSystemMetrics(SM_CYVSCROLL) * 2 - sizeTrack.cy;

      double dRate = (double)(point.y - GetSystemMetrics(SM_CYVSCROLL)) / (double) iHeight;

      dRate = MIN(1.0, dRate);

      nPos = (int32_t) (dRate * (m_scrollinfo.nMax - m_scrollinfo.nMin - m_scrollinfo.nPage));

      nPos += m_scrollinfo.nMin;

   }
   else
   {

      ASSERT(FALSE);

   }

   if (nPos < m_scrollinfo.nMin)
   {

      nPos = m_scrollinfo.nMin;

   }
   else if (nPos > m_scrollinfo.nMax)
   {

      nPos = m_scrollinfo.nMax;

   }

   if(m_bTracking)
   {

      m_scrollinfo.nTrackPos = nPos;

   }
   else
   {

      m_scrollinfo.nPos = nPos;

   }

   m_scrollinfo.fMask = SIF_ALL;

   return true;

}


void simple_scroll_bar::_001OnHScroll(::message::message * pobj)
{
   SCAST_PTR(::message::scroll, pscroll, pobj);
   pscroll->m_bRet = false;
}

int32_t simple_scroll_bar::_001GetScrollPos()
{
   if(m_bTracking)
      return m_scrollinfo.nTrackPos;
   else
      return m_scrollinfo.nPos;
}



void simple_scroll_bar::on_layout()
{

   rect rectClient;
   GetClientRect(rectClient);
   class size size = rectClient.get_size();

   int iArrowForce = 4;
   int iArrowStability = size.get_orthogonal_dimension(m_eorientation) - 2 - 3 * 2;

   if(m_eorientation == orientation_horizontal)
   {

      m_rectA.left   = 0;
      m_rectA.top    = 0;
      m_rectA.right  = MIN(GetSystemMetrics(SM_CXHSCROLL),size.cx / 2);
      m_rectA.bottom = size.cy;

      /*
      m_ptaA[0].x = 0;
      m_ptaA[0].y = size.cy / 2;
      m_ptaA[1].x = MIN(GetSystemMetrics(SM_CXHSCROLL), size.cx / 2);
      m_ptaA[1].y = size.cy - 1;
      m_ptaA[2].x = m_ptaA[1].x;
      m_ptaA[2].y = 1;
      m_ptaA[3].x = m_ptaA[0].x;
      m_ptaA[3].y = m_ptaA[0].y;
      */

      m_ptaA[0].x = m_rectA.left + (m_rectA.width() + iArrowForce) / 2;
      m_ptaA[0].y = m_rectA.top + (m_rectA.height() - iArrowStability) / 2;
      m_ptaA[1].x = m_rectA.left + (m_rectA.width() - iArrowForce) / 2;
      m_ptaA[1].y = m_rectA.top + m_rectA.height() / 2;
      m_ptaA[2].x = m_rectA.left + (m_rectA.width() + iArrowForce) / 2;
      m_ptaA[2].y = m_rectA.top + (m_rectA.height() + iArrowStability) / 2;;

      m_rectB.left   = MAX(size.cx - GetSystemMetrics(SM_CXHSCROLL),size.cx / 2);
      m_rectB.top    = 0;
      m_rectB.right  = size.cx;
      m_rectB.bottom = size.cy;

      /*
      m_ptaB[0].x = size.cx;
      m_ptaB[0].y = size.cy / 2;
      m_ptaB[1].x = ;
      m_ptaB[1].y = 1;
      m_ptaB[2].x = m_ptaB[1].x;
      m_ptaB[2].y = size.cy - 1;
      m_ptaB[3].x = m_ptaB[0].x;
      m_ptaB[3].y = m_ptaA[0].y;
      */

      m_ptaB[0].x = m_rectB.left + (m_rectB.width() - iArrowForce) / 2;
      m_ptaB[0].y = m_rectB.top + (m_rectB.height() - iArrowStability) / 2;
      m_ptaB[1].x = m_rectB.left + (m_rectB.width() + iArrowForce) / 2;
      m_ptaB[1].y = m_rectB.top + m_rectB.height() / 2;
      m_ptaB[2].x = m_rectB.left + (m_rectB.width() - iArrowForce) / 2;
      m_ptaB[2].y = m_rectB.top + (m_rectB.height() + iArrowStability) / 2;;

   }
   else if(m_eorientation == orientation_vertical)
   {

      m_rectA.left   = 0;
      m_rectA.top    = 0;
      m_rectA.right  = size.cx;
      m_rectA.bottom = MIN(GetSystemMetrics(SM_CYVSCROLL),size.cy / 2);

      /*
      m_ptaA[0].x = size.cx / 2;
      m_ptaA[0].y = 0;
      m_ptaA[1].x = 1;
      m_ptaA[1].y = MIN(GetSystemMetrics(SM_CYVSCROLL), size.cy / 2);
      m_ptaA[2].x = size.cx - 1;
      m_ptaA[2].y = m_ptaA[1].y;
      m_ptaA[3].x = m_ptaA[0].x;
      m_ptaA[3].y = m_ptaA[0].y;
      */

      m_ptaA[0].x = m_rectA.left + (m_rectA.width() - iArrowStability) / 2;
      m_ptaA[0].y = m_rectA.top + (m_rectA.height() + iArrowForce) / 2;
      m_ptaA[1].x = m_rectA.left + m_rectA.width() / 2;
      m_ptaA[1].y = m_rectA.top +( m_rectA.height() - iArrowForce) / 2;
      m_ptaA[2].x = m_rectA.left + (m_rectA.width() + iArrowStability) / 2;
      m_ptaA[2].y = m_rectA.top + (m_rectA.height() + iArrowForce) / 2;;

      m_rectB.left   = 0;
      m_rectB.top    = MAX(size.cy - GetSystemMetrics(SM_CYVSCROLL),size.cy / 2);
      m_rectB.right  = size.cx;
      m_rectB.bottom = size.cy;

      /*
      m_ptaB[0].x = size.cx / 2;
      m_ptaB[0].y = size.cy;
      m_ptaB[1].x = size.cx - 1;
      m_ptaB[1].y = MAX(size.cy - GetSystemMetrics(SM_CYVSCROLL), size.cy / 2);
      m_ptaB[2].x = 1;
      m_ptaB[2].y = m_ptaB[1].y;
      m_ptaB[3].x = m_ptaA[0].x;
      m_ptaB[3].y = m_ptaB[0].y;
      */
      m_ptaB[0].x = m_rectB.left + (m_rectB.width() - iArrowStability) / 2;
      m_ptaB[0].y = m_rectB.top + (m_rectB.height() - iArrowForce) / 2;
      m_ptaB[1].x = m_rectB.left + m_rectB.width() / 2;
      m_ptaB[1].y = m_rectB.top + (m_rectB.height() + iArrowForce) / 2;
      m_ptaB[2].x = m_rectB.left + (m_rectB.width() + iArrowStability) / 2;
      m_ptaB[2].y = m_rectB.top + (m_rectB.height() - iArrowForce) / 2;;
   }
   else
   {
      ASSERT(FALSE);
   }

   m_rgnA->create_rect(m_rectA);
   m_rgnB->create_rect(m_rectB);


//   psize->m_bRet = false;
}

void simple_scroll_bar::_001OnTimer(::timer * ptimer)
{

   ::user::scroll_bar::_001OnTimer(ptimer);

   point pt;

   Session.get_cursor_pos(&pt);

   ScreenToClient(&pt);

   if(ptimer->m_nIDEvent == (uint_ptr) this)
   {

      KillTimer(ptimer->m_nIDEvent);

      SetTimer(((uint_ptr) this) + 1,10,NULL);

   }
   else if(ptimer->m_nIDEvent == ((uint_ptr) this) + 1)
   {

      if(!scrollbar_action(m_eelement,pt))
      {

         KillTimer(ptimer->m_nIDEvent);

      }

   }

}


bool simple_scroll_bar::scrollbar_lineA()
{

   int32_t nPos = m_scrollinfo.nPos;

   nPos-=3;

   if(nPos < m_scrollinfo.nMin)
      nPos = m_scrollinfo.nMin;

   m_scrollinfo.nPos = nPos;

   if(m_eorientation == orientation_horizontal)
   {
      send_scroll_message(SB_LINELEFT);
   }
   else
   {
      send_scroll_message(SB_LINEUP);
   }

   if(m_scrollinfo.nPos == m_scrollinfo.nMin)
      return false;

   return true;

}


bool simple_scroll_bar::scrollbar_lineB()
{

   int32_t nPos = m_scrollinfo.nPos;

   nPos+=3;

   if(nPos > m_scrollinfo.nMax - m_scrollinfo.nPage)
      nPos = m_scrollinfo.nMax - m_scrollinfo.nPage;

   m_scrollinfo.nPos = nPos;

   if(m_eorientation == orientation_horizontal)
   {
      send_scroll_message(SB_LINERIGHT);
   }
   else
   {
      send_scroll_message(SB_LINEDOWN);
   }

   if(m_scrollinfo.nPos == m_scrollinfo.nMax - m_scrollinfo.nPage)
      return false;

   return true;

}


bool simple_scroll_bar::scrollbar_pageA(point pt)
{

   int32_t nPos = m_scrollinfo.nPos;

   nPos-=m_scrollinfo.nPage ;

   if(nPos < m_scrollinfo.nMin)
      nPos = m_scrollinfo.nMin;

   m_scrollinfo.nPos = nPos;

   if(m_eorientation == orientation_horizontal)
   {
      send_scroll_message(SB_PAGELEFT);
   }
   else
   {
      send_scroll_message(SB_PAGEUP);
   }

   rect rectClient;

   rect rectTrack;

   rect rect;

   GetClientRect(rectClient);

   GetTrackRect(rectTrack);

   GetPageARect(rectClient,rectTrack,rect);

   if(!rect.contains(pt))
      return false;

   if(m_scrollinfo.nPos == m_scrollinfo.nMin)
      return false;

   return true;

}


bool simple_scroll_bar::scrollbar_pageB(point pt)
{

   int32_t nPos = m_scrollinfo.nPos;

   nPos+=m_scrollinfo.nPage ;

   if(nPos > m_scrollinfo.nMax - m_scrollinfo.nPage)
      nPos = m_scrollinfo.nMax - m_scrollinfo.nPage;

   m_scrollinfo.nPos = nPos;

   if(m_eorientation == orientation_horizontal)
   {
      send_scroll_message(SB_PAGERIGHT);
   }
   else
   {
      send_scroll_message(SB_PAGEDOWN);
   }

   rect rectClient;

   rect rectTrack;

   rect rect;

   GetClientRect(rectClient);

   GetTrackRect(rectTrack);

   GetPageBRect(rectClient,rectTrack,rect);

   if(!rect.contains(pt))
      return false;

   if(m_scrollinfo.nPos == m_scrollinfo.nMax - m_scrollinfo.nPage)
      return false;

   return true;

}


//void simple_scroll_bar::OnDraw(::draw2d::dib * pdib)
//{
/*    if(GetExStyle() & WS_EX_TRANSPARENT)
{
return;
}

sp(::user::interaction) pParentWnd = GetParent();
int32_t nPos = m_scrollinfo.nPos;
nPos+=m_scrollinfo.nPage;
if(nPos > m_scrollinfo.nMax - m_scrollinfo.nPage)
nPos = m_scrollinfo.nMax - m_scrollinfo.nPage;
m_scrollinfo.nPos = nPos;

if(m_eorientation == orientation_horizontal)
{
pParentWnd->SendMessage(WM_HSCROLL, MAKEWPARAM(SB_LINERIGHT, m_scrollinfo.nPos), (LPARAM) this->get_handle());
}
else
{
pParentWnd->SendMessage(WM_VSCROLL, MAKEWPARAM(SB_LINEDOWN, m_scrollinfo.nPos), (LPARAM) this->get_handle());
}*/

//}


void simple_scroll_bar::_001OnCreate(::message::message * pobj)
{


   SCAST_PTR(::message::create, pcreate, pobj);


   //if (m_puserstyle == NULL)
   //{

   //   m_puserstyle = GetTopLevel();

   //}

   //if (m_puserstyle == NULL)
   //{

   //   m_puserstyle = Application.userstyle();

   //}

   update_drawing_objects();

   pcreate->set_lresult(0);



}

void simple_scroll_bar::OnDisplayChange(int32_t iBitsPerPixel, size sizeScreen)
{
   UNREFERENCED_PARAMETER(iBitsPerPixel);
   UNREFERENCED_PARAMETER(sizeScreen);
}

void simple_scroll_bar::pre_translate_message(::message::message * pobj)
{

   SCAST_PTR(::message::base, pbase, pobj);

   if(pbase->m_pwnd == this)
   {
      switch(pbase->m_id)
      {
      case WM_DISPLAYCHANGE:
         OnDisplayChange((int32_t) pbase->m_wparam, size(LOWORD(pbase->m_lparam), HIWORD(pbase->m_lparam)));
         pbase->m_bRet = true;
         return;
      default:
         break;
      }
   }

   return ::user::interaction::pre_translate_message(pobj);

}

void simple_scroll_bar::UpdateBitmaps()
{

}

bool simple_scroll_bar::GetPageARect(LPRECT lpRectClient,LPRECT lpRectTrack, LPRECT lpRect)
{

   if(m_eorientation == orientation_horizontal)
   {
      lpRect->left = lpRectClient->left + GetSystemMetrics(SM_CXHSCROLL);
      lpRect->top = lpRectTrack->top;
      lpRect->right = lpRectTrack->left;
      lpRect->bottom = lpRectTrack->bottom;
   }
   else if(m_eorientation == orientation_vertical)
   {
      lpRect->left = lpRectTrack->left;
      lpRect->top = lpRectClient->top + GetSystemMetrics(SM_CYVSCROLL);
      lpRect->right = lpRectTrack->right;
      lpRect->bottom = lpRectTrack->top;
   }

   return true;

}


bool simple_scroll_bar::GetPageBRect(LPRECT lpRectClient,LPRECT lpRectTrack, LPRECT lpRect)
{
   if(m_eorientation == orientation_horizontal)
   {
      lpRect->left = lpRectTrack->right;
      lpRect->top = lpRectTrack->top;
      lpRect->right = lpRectClient->right - GetSystemMetrics(SM_CXHSCROLL);
      lpRect->bottom = lpRectTrack->bottom;
   }
   else if(m_eorientation == orientation_vertical)
   {
      lpRect->left = lpRectTrack->left;
      lpRect->top = lpRectTrack->bottom;
      lpRect->right = lpRectTrack->right;
      lpRect->bottom = lpRectClient->bottom - GetSystemMetrics(SM_CYVSCROLL);
   }

   return true;

}



int32_t simple_scroll_bar::_001SetScrollPos(int32_t iPos)
{
   m_scrollinfo.nPos = iPos ;
   if(m_scrollinfo.nPos < m_scrollinfo.nMin)
   {
      m_scrollinfo.nPos = m_scrollinfo.nMin;
   }
   else if(m_scrollinfo.nPos > m_scrollinfo.nMax - m_scrollinfo.nPage)
   {
      m_scrollinfo.nPos = m_scrollinfo.nMax - m_scrollinfo.nPage;
   }
   //Redraw();
   return true;
}


LRESULT simple_scroll_bar::OnEconoModeChange(WPARAM wParam, LPARAM lParam)
{
   UNREFERENCED_PARAMETER(wParam);
   UNREFERENCED_PARAMETER(lParam);
   update_drawing_objects();
   //Redraw();

   return true;
}

void simple_scroll_bar::update_drawing_objects()
{

}


class trw:
   virtual public ::user::interaction
{
public:

   point pt1;
   point pt2;


   trw(::aura::application * papp): ::object(papp),::user::interaction(papp)
   {

      ::user::create_struct cs(WS_EX_LAYERED,NULL,"",WS_VISIBLE);

      if(create_window_ex(cs))
      {

         TRACE("created trw");

      }

      best_monitor(NULL,null_rect(),true);

   }

   virtual ~trw()
   {

   }


   virtual void _001OnDraw(::draw2d::graphics * pgraphics)
   {
      pgraphics->move_to(pt1);
      pgraphics->line_to(pt2);
   }
};


// Important:
//
// The default _001OnClip implemenstation clips the current window
// to all ascending windows client area intersection.
// The client area of a window excludes its children scroll bars
// region.
// For the scroll bar, this algorithm would clip scroll bar child
// window from its drawing.
// This overload for this scroll bar overcomes this issue.
void simple_scroll_bar::_001OnClip(::draw2d::graphics * pgraphics)
{

   //return;



   try
   {

      rect rectClip;

      ::aura::draw_context * pdrawcontext = pgraphics->::core::simple_chain < ::aura::draw_context >::get_last();

      rect rectClient;

      bool bFirst = true;

      if (pdrawcontext != NULL)
      {

         rectClient = pdrawcontext->m_rectWindow;

         ScreenToClient(rectClient);

         rectClient.bottom++;
         rectClient.right++;

         rectClip = rectClient;

         bFirst = false;

      }

      ::user::interaction * pui = this;

      ::rect rectFocus;

      ::rect rectIntersect;

      index i = 0;

      while (pui != NULL)
      {

         if (i == 1)
         {

            pui->::user::interaction::GetClientRect(rectFocus);

         }
         else
         {

            pui->GetClientRect(rectFocus);

         }

         pui->ClientToScreen(rectFocus);

         ScreenToClient(rectFocus);

         //rectFocus.bottom++;
         //rectFocus.right++;

         if (i == 0)
         {

            rectIntersect = rectFocus;

         }
         else
         {

            rectIntersect.intersect(rectFocus);

         }

         i++;

         pui = pui->GetParent();

      }

      pgraphics->IntersectClipRect(rectIntersect);

   }
   catch (...)
   {

      _throw(simple_exception(get_app(), "no more a window"));

   }

}


void simple_scroll_bar::_001OnDraw(::draw2d::graphics * pgraphics)
{

   ::user::style_context style(this);

   while(style)
   {

      if (style->_001DrawSimpleScrollBar(pgraphics, this))
      {

         return;

      }

      style.next();

   }

   style = this;

   while (style)
   {

      if (style->_001DrawScrollBar(pgraphics, this))
      {

         return;

      }

      style.next();

   }

   _001OnVerisimpleDraw(pgraphics);

}


void simple_scroll_bar::_001OnVerisimpleDraw(::draw2d::graphics * pgraphics)
{

   COLORREF crBackground = _001GetColor(::user::color_background);

   rect rectClient;

   GetClientRect(rectClient);

   if ((crBackground & ARGB(255, 0, 0, 0)) != 0)
   {

      pgraphics->set_alpha_mode(::draw2d::alpha_mode_blend);

      if (Session.savings().is_trying_to_save(::aura::resource_processing))
      {

         pgraphics->fill_solid_rect(rectClient, RGB(255, 255, 255));

      }
      else
      {

         pgraphics->fill_solid_rect(rectClient, ARGB(255, 240, 240, 240));

      }

   }

   rect rectTrack;

   GetTrackRect(rectTrack);

   class ::rect rectWindow;

   GetWindowRect(rectWindow);

   m_brushDraw->create_solid(scrollbar_color_strong(::user::element_scrollbar_rect));

   pgraphics->SelectObject(m_brushDraw);

   pgraphics->fill_rect(rectTrack);

   if (m_bTracking || (bool)oprop("tracking_on"))
   {

      DWORD dwFadeIn = 300;

      DWORD dwFadeOut = 300;

      byte uchAlpha = MAX(0, MIN(255, oprop("tracking_alpha").u32()));

      if (m_bTracking)
      {

         if (!(bool)oprop("tracking_on"))
         {

            oprop("tracking_on") = true;

            oprop("tracking_start") = (uint32_t)(get_tick_count() + uchAlpha * dwFadeIn / 255);

            oprop("tracking_fade_in") = true;

            oprop("tracking_fade_out") = false;

            oprop("tracking_type") = System.math().RandRange(1, 2);

            if (oprop("tracking_simple").i32() == 2)
            {

               int iDeflate = rectTrack.get_size().get_normal(m_eorientation);

               iDeflate /= 2;

               rect rectConstraint(m_rectTrack);

               rectConstraint.deflate(iDeflate, iDeflate);

               constraint(m_ptTrack, rectConstraint);

               m_ptTrackOffset = m_ptTrack - m_rectTrack.top_left();

            }

         }

      }
      else
      {

         if (!(bool)oprop("tracking_fade_out"))
         {

            oprop("tracking_fade_in") = false;

            oprop("tracking_fade_out") = true;

            oprop("tracking_start") = (uint32_t)(get_tick_count() + (255 - uchAlpha) * dwFadeOut / 255);

         }

      }

      point pt1 = rectTrack.top_left() + m_ptTrackOffset;

      ClientToScreen(pt1);

      point pt2;

      Session.get_cursor_pos(&pt2);

      ClientToScreen(pt1);

      if ((bool)oprop("tracking_fade_in"))
      {

         DWORD dwFade = get_tick_count() - oprop("tracking_start").u32();

         if (dwFade < dwFadeIn)
         {

            uchAlpha = (byte)MIN(255, MAX(0, (dwFade * 255 / dwFadeIn)));

         }
         else
         {

            uchAlpha = 255;

            oprop("tracking_fade_in") = false;

         }

      }
      else if ((bool)oprop("tracking_fade_out"))
      {

         DWORD dwFade = get_tick_count() - oprop("tracking_start").u32();

         if (dwFade < dwFadeOut)
         {

            uchAlpha = (byte)(255 - MIN(255, MAX(0, (dwFade * 255 / dwFadeOut))));

         }
         else
         {

            uchAlpha = 0;

            oprop("tracking_on") = false;

            oprop("tracking_fade_out") = false;

         }

      }
      else
      {
         uchAlpha = 255;
      }

      ::rect rectMachineThumb;

      i32 iType = oprop("tracking_type").i32();

      if (iType == 1)
      {

         int iSize = rectTrack.get_size().get_normal(m_eorientation);

         rectMachineThumb.top_left() = rectTrack.top_left() + m_ptTrackOffset - size(iSize / 2, iSize / 2);

         rectMachineThumb.bottom_right() = rectMachineThumb.top_left() + size(iSize, iSize);

         ::rect rectIntersect;

         rectIntersect.intersect(rectMachineThumb, rectTrack);

         int32_t iArea = (int32_t)(MAX(1, rectIntersect.area()));

         rectMachineThumb.inflate(1 + iSize * (iSize * iSize) * 4 / (iArea * 5), 1 + iSize * (iSize * iSize) * 2 / (iArea * 3));

         draw_mac_thumb_simple(pgraphics, rectMachineThumb, rectTrack, uchAlpha);

      }
      else
      {

         int iSize = rectTrack.get_size().get_normal(m_eorientation);

         rectMachineThumb.top_left() = rectTrack.top_left() + m_ptTrackOffset - size(iSize / 2, iSize / 2);

         rectMachineThumb.set_size(iSize, iSize);

         rectMachineThumb.assign_normal(rectTrack, m_eorientation);

         draw_mac_thumb_dots(pgraphics, rectMachineThumb, rectTrack, uchAlpha);

      }

      oprop("tracking_alpha") = uchAlpha;

      set_need_redraw();

   }

   COLORREF cr = scrollbar_color(::user::element_scrollbar_rectA);

   m_brushDraw->create_solid(cr);

   pgraphics->SelectObject(m_brushDraw);

   pgraphics->fill_rect(m_rectA);

   cr = scrollbar_color(::user::element_scrollbar_rectB);

   m_brushDraw->create_solid(cr);

   pgraphics->SelectObject(m_brushDraw);

   pgraphics->fill_rect(m_rectB);

   ::rect rect;

   if (m_eelement == ::user::element_scrollbar_pageA || m_eelementHover == ::user::element_scrollbar_pageA)
   {

      GetPageARect(rectClient, rectTrack, rect);

      cr = scrollbar_color(::user::element_scrollbar_pageA);

      m_brushDraw->create_solid(cr);

      pgraphics->SelectObject(m_brushDraw);

      pgraphics->fill_rect(rect);

   }
   else if (m_eelement == ::user::element_scrollbar_pageB || m_eelementHover == ::user::element_scrollbar_pageB)
   {

      GetPageBRect(rectClient, rectTrack, rect);

      cr = scrollbar_color(::user::element_scrollbar_pageB);

      m_brushDraw->create_solid(cr);

      pgraphics->SelectObject(m_brushDraw);

      pgraphics->fill_rect(rect);

   }

   ::draw2d::pen_sp penArrow(allocer());

   penArrow->m_elinecapBeg = ::draw2d::pen::line_cap_round;

   penArrow->m_elinecapEnd = ::draw2d::pen::line_cap_round;

   penArrow->m_elinejoin = ::draw2d::pen::line_join_round;

   cr = scrollbar_draw_color(::user::element_scrollbar_rectA);

   penArrow->create_solid(1.0, cr);

   pgraphics->SelectObject(penArrow);

   pgraphics->Polyline(m_ptaA, 3);

   cr = scrollbar_draw_color(::user::element_scrollbar_rectB);

   penArrow->create_solid(1.0, cr);

   pgraphics->SelectObject(penArrow);

   pgraphics->Polyline(m_ptaB, 3);

}


void simple_scroll_bar::_001OnShowWindow(::message::message * pobj)
{
   SCAST_PTR(::message::show_window, pshowwindow, pobj);
   pshowwindow->m_bRet = false;

   // xxx   TwiOnShowWindow(bShow, nStatus);
}

void simple_scroll_bar::_001OnDestroy(::message::message * pobj)
{
   UNREFERENCED_PARAMETER(pobj);
}

void simple_scroll_bar::draw_mac_thumb_simple(::draw2d::graphics * pgraphics,LPCRECT lpcrectDraw,LPCRECT lpcrectClip,byte uchAlpha)
{

   ::draw2d::savedc dc(pgraphics);

   pgraphics->SelectClipRgn(NULL);

   rect rectDraw(lpcrectDraw);

   rectDraw.deflate(1,1);

   ::draw2d::pen_sp pen(allocer());

   pen->create_solid(2.0,ARGB(150 * uchAlpha / 255,108, 108, 100));

   pgraphics->SelectObject(pen);

   pgraphics->DrawEllipse(rectDraw);

   ::draw2d::brush_sp brush(allocer());

   ::rect rectDotto(0,0,5,5);

   brush->create_solid(ARGB(150 * uchAlpha / 255,108,108,100));

   pgraphics->SelectObject(brush);

   rectDotto.Align(align_center, rectDraw);

   pgraphics->FillEllipse(rectDotto);

}



void simple_scroll_bar::draw_mac_thumb_dots(::draw2d::graphics * pgraphics,LPCRECT lpcrectDraw,LPCRECT lpcrectClip,byte uchAlpha)
{

   rect rDraw(lpcrectDraw);

   rDraw.bottom--;

   rDraw.right--;

   double iDiv = 10;

   if (m_dibDots.is_null())
   {

      m_dibDots.alloc(allocer());

      m_dibDots->create(rDraw.width() * iDiv, rDraw.height() * iDiv);

      m_dibDots->FillByte(0);

      m_dibDots->g()->set_alpha_mode(::draw2d::alpha_mode_blend);

      double iDiv2 = iDiv / 2;

      double iDiv3 = iDiv2 / 2;

      double x = m_dibDots->m_size.cx / (iDiv * 2);

      double iSize = iDiv3;

      for (int i = 0; i <= iDiv2; i++)
      {

         double y = m_dibDots->m_size.cy / (iDiv * 2);

         for (int j = 0; j <= iDiv2; j++)
         {

            iSize = MAX(abs(m_dibDots->m_size.cx / 2 - x), abs(m_dibDots->m_size.cx / 2 - y));

            iSize = (m_dibDots->m_size.cx / 2) - iSize;

            iSize = pow(iSize, 0.55);

            rectd r(x - iSize, y - iSize, x + iSize, y + iSize);

            m_dibDots->g()->fill_solid_rect(r, ARGB(80, 0, 0, 0));

            y += m_dibDots->m_size.cy / (iDiv2 + 1.0);

         }

         x += m_dibDots->m_size.cx / (iDiv2 + 1.0);

      }

   }

   pgraphics->set_alpha_mode(::draw2d::alpha_mode_blend);

   pgraphics->SetStretchBltMode(HALFTONE);

   pgraphics->alpha_blend(rDraw.top_left(), rDraw.get_size(), m_dibDots->g(), point(iDiv, iDiv), m_dibDots->m_size - size(iDiv*2, iDiv *2), uchAlpha / 255.0);

}


index simple_scroll_bar::hit_test(point pt,::user::e_element & eelement)
{

   ScreenToClient(&pt);

   rect rectTrack;

   GetTrackRect(rectTrack);

   if(rectTrack.contains(pt))
   {

      eelement = ::user::element_scrollbar_rect;

      return 0;

   }

   ::rect rect;

   ::rect rectClient;

   GetClientRect(rectClient);

   GetPageARect(rectClient,rectTrack,rect);

   if(rect.contains(pt))
   {

      eelement = ::user::element_scrollbar_pageA;

      return 0;

   }


   GetPageBRect(rectClient,rectTrack,rect);

   if(rect.contains(pt))
   {

      eelement = ::user::element_scrollbar_pageB;

      return 0;

   }

   if(m_rectA.contains(pt))
   {

      eelement = ::user::element_scrollbar_rectA;

      return 0;

   }

   if(m_rectB.contains(pt))
   {

      eelement = ::user::element_scrollbar_rectB;

      return 0;

   }

   return -1;

}


COLORREF simple_scroll_bar::scrollbar_color_strong(::user::e_element eelement)
{

   if (m_eelement == eelement || m_eelementHover == eelement)
   {

      return _001GetColor(::user::color_scrollbar_strong_hover, ARGB(130, 190, 180, 250));

   }
   else
   {

      return _001GetColor(::user::color_scrollbar_strong, ARGB(150, 150, 150, 150));

   }

}


COLORREF simple_scroll_bar::scrollbar_color(::user::e_element eelement)
{

   if(m_eelement == eelement || m_eelementHover == eelement)
   {

      return _001GetColor(::user::color_scrollbar_hover, ARGB(100, 190, 180, 250));

   }
   else
   {

      return _001GetColor(::user::color_scrollbar, ARGB(150, 150, 150, 150));

   }

}


COLORREF simple_scroll_bar::scrollbar_border_color(::user::e_element eelement)
{

   if(m_eelement == eelement || m_eelementHover == eelement)
   {

      return _001GetColor(::user::color_scrollbar_border_hover, ARGB(190, 180, 180, 180));

   }
   else
   {

      return _001GetColor(::user::color_scrollbar_border, ARGB(190, 160, 160, 160));

   }

}


COLORREF simple_scroll_bar::scrollbar_lite_border_color(::user::e_element eelement)
{

   if(m_eelement == eelement || m_eelementHover == eelement)
   {

      return _001GetColor(::user::color_scrollbar_lite_border_hover, ARGB(190, 90, 110, 180));

   }
   else
   {

      return _001GetColor(::user::color_scrollbar_lite_border, ARGB(190, 110, 110, 100));

   }

}


COLORREF simple_scroll_bar::scrollbar_draw_color(::user::e_element eelement)
{

   if (m_eelement == eelement || m_eelementHover == eelement)
   {

      return _001GetColor(::user::color_scrollbar_draw_hover, ARGB(127, 90, 90, 90));

   }
   else
   {

      return _001GetColor(::user::color_scrollbar_draw, ARGB(127, 65, 65, 65));

   }

}



