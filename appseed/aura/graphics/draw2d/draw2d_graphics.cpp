#include "framework.h"
//#include "draw2d.h"
//#include <math.h>


#include "nanosvg.h"

CLASS_DECL_AURA spa(::draw2d::dib) * g_pdiba = NULL;

namespace draw2d
{


   pen_sp::pen_sp(const ::aura::allocatorsp & allocer, double dWidth, COLORREF crColor) :
      ::smart_pointer < pen >(allocer)
   {

      m_p->create_solid(dWidth,crColor);

   }


   bool word_break(::draw2d::graphics * pgraphics,const string & strSource, RECT & rectParam,string &str1,string & str2,int iEll);

   strsize _EncodeV033(string & str);




   graphics::graphics(::aura::application * papp) :
      object(papp)
   {

      m_bPat = false;
      m_bStoreThumbnails      = true;
      m_puistrcontext         = NULL;
      m_pdrawcontext          = NULL;
      m_pdibAlphaBlend        = NULL;
      m_pjob                  = NULL;
      m_dFontFactor           = 1.0;
      m_pdibDraw2dGraphics    = NULL;

   }


   graphics::~graphics()
   {

   }


   bool graphics::prefer_mapped_dib_on_mix()
   {

      return false;

   }


   ::aura::str_context * graphics::str_context()
   {
      return m_puistrcontext;
   }

   ::aura::draw_context * graphics::draw_context()
   {
      return m_pdrawcontext;
   }

   bool graphics::is_set()
   {
      return get_os_data() != 0;
   }


   void *  graphics::get_os_data() const
   {

      _throw(interface_only_exception(get_app()));

      return 0;

   }


   void * graphics::get_os_data_ex(int i) const
   {

      if(i == 0)
      {

         return get_os_data();

      }
      else
      {

         return NULL;

      }

   }


   void graphics::release_os_data_ex(int i, void * p)
   {

   }


   bool graphics::attach(void * pdata)
   {

      _throw(interface_only_exception(get_app()));

      return false;

   }


   void * graphics::detach()
   {

      _throw(interface_only_exception(get_app()));

      return NULL;

   }


   bool graphics::IsPrinting()
   {

      _throw(interface_only_exception(get_app()));

      return false;

   }


   bool graphics::CreateDC(const char * lpszDriverName,  const char * lpszDeviceName, const char * lpszOutput, const void * lpInitData)
   {

      UNREFERENCED_PARAMETER(lpszDriverName);
      UNREFERENCED_PARAMETER(lpszDeviceName);
      UNREFERENCED_PARAMETER(lpszOutput);
      UNREFERENCED_PARAMETER(lpInitData);
      _throw(interface_only_exception(get_app()));

      return false;

   }


   bool graphics::CreateIC(const char * lpszDriverName,  const char * lpszDeviceName, const char * lpszOutput, const void * lpInitData)
   {

      UNREFERENCED_PARAMETER(lpszDriverName);
      UNREFERENCED_PARAMETER(lpszDeviceName);
      UNREFERENCED_PARAMETER(lpszOutput);
      UNREFERENCED_PARAMETER(lpInitData);
      _throw(interface_only_exception(get_app()));

      return false;

   }


   bool graphics::CreateCompatibleDC(::draw2d::graphics * pgraphics)
   {

      UNREFERENCED_PARAMETER(pgraphics);

      _throw(interface_only_exception(get_app()));

      return false;

   }

   bool graphics::CreateWindowDC(oswindow wnd)
   {

      UNREFERENCED_PARAMETER(wnd);

      _throw(interface_only_exception(get_app()));

      return false;

   }


   /*   i32 graphics::ExcludeUpdateRgn(::window_sp pwindow)
      {
         UNREFERENCED_PARAMETER(pwindow);
         _throw(interface_only_exception(get_app()));
      }
      */

   i32 graphics::GetDeviceCaps(i32 nIndex)
   {
      UNREFERENCED_PARAMETER(nIndex);
      _throw(interface_only_exception(get_app()));

      return -1;

   }

   point graphics::GetBrushOrg()
   {

      _throw(interface_only_exception(get_app()));

      return null_point();

   }

   bool graphics::set_text_color(COLORREF clr)
   {

      ::draw2d::brush_sp brush(allocer(), clr);

      if(brush.is_null())
         return false;

      return SelectObject(brush) != FALSE;

   }

   point graphics::SetBrushOrg(i32 x, i32 y)
   {

      UNREFERENCED_PARAMETER(x);
      UNREFERENCED_PARAMETER(y);
      _throw(interface_only_exception(get_app()));

      return null_point();

   }

   point graphics::SetBrushOrg(POINT point)
   {
      UNREFERENCED_PARAMETER(point);
      _throw(interface_only_exception(get_app()));


      return null_point();

   }

   i32 graphics::EnumObjects(i32 nObjectType, i32 (CALLBACK* lpfn)(LPVOID, LPARAM), LPARAM lpData)
   {
      UNREFERENCED_PARAMETER(nObjectType);
      UNREFERENCED_PARAMETER(lpfn);
      UNREFERENCED_PARAMETER(lpData);
      _throw(interface_only_exception(get_app()));

      return -1;

   }

   ::draw2d::bitmap* graphics::SelectObject(::draw2d::bitmap* pBitmap)
   {
      UNREFERENCED_PARAMETER(pBitmap);
      _throw(interface_only_exception(get_app()));

      return NULL;

   }


   bool graphics::SelectFont(::draw2d::font * pfont)
   {
      // SIOOT - Should implemennt one of them
      // OASOWO - otherwise a stack overflow will occur
      // BTAIOM - because these are interface only methods

      m_spfont = pfont;

      return true;

   }

   bool graphics::selectFont(::draw2d::font * pfont)
   {
      return SelectFont(pfont);
   }

   bool graphics::select_font(::draw2d::font * pfont)
   {
      return selectFont(pfont);
   }

   bool graphics::SetFont(::draw2d::font * pfont)
   {
      return select_font(pfont);
   }

   bool graphics::setFont(::draw2d::font * pfont)
   {
      return SetFont(pfont);
   }

   bool graphics::set_font(::draw2d::font * pfont)
   {
      return setFont(pfont);
   }

   COLORREF graphics::GetNearestColor(COLORREF crColor)
   {
      UNREFERENCED_PARAMETER(crColor);
      _throw(interface_only_exception(get_app()));

      return 0;

   }

   UINT graphics::RealizePalette()
   {
      _throw(interface_only_exception(get_app()));

      return -1;

   }

   void graphics::UpdateColors()
   {
      _throw(interface_only_exception(get_app()));



   }


   i32 graphics::GetPolyFillMode()
   {

      _throw(interface_only_exception(get_app()));

      return -1;

   }


   i32 graphics::GetROP2()
   {

      _throw(interface_only_exception(get_app()));

      return -1;

   }


   i32 graphics::GetStretchBltMode()
   {

      _throw(interface_only_exception(get_app()));

      return -1;

   }


   i32 graphics::GetMapMode()
   {

      _throw(interface_only_exception(get_app()));

      return -1;

   }


   i32 graphics::GetGraphicsMode()
   {

      _throw(interface_only_exception(get_app()));

      return -1;

   }


#ifdef WINDOWS

   bool graphics::GetWorldTransform(XFORM* pXform)
   {
      UNREFERENCED_PARAMETER(pXform);
      _throw(interface_only_exception(get_app()));

      return false;

   }

#endif


   point graphics::GetViewportOrg()
   {

      return ::point(m_matrixViewport.c1, m_matrixViewport.c2);

   }


   size graphics::GetViewportExt()
   {

      _throw(interface_only_exception(get_app()));

      return size(0, 0);

   }


   point graphics::GetWindowOrg()
   {

      _throw(interface_only_exception(get_app()));

      return null_point();

   }


   size graphics::GetWindowExt()
   {

      _throw(interface_only_exception(get_app()));

      return size(0, 0);

   }


   point graphics::SetViewportOrg(POINT point)
   {

      return SetViewportOrg(point.x, point.y);

   }


   size graphics::SetViewportExt(SIZE size)
   {

      UNREFERENCED_PARAMETER(size);

      _throw(interface_only_exception(get_app()));

      return ::size(0, 0);

   }


   point graphics::SetWindowOrg(POINT point)
   {

      UNREFERENCED_PARAMETER(point);

      _throw(interface_only_exception(get_app()));

      return null_point();

   }


   size graphics::SetWindowExt(SIZE size)
   {

      UNREFERENCED_PARAMETER(size);

      _throw(interface_only_exception(get_app()));

      return ::size(0, 0);

   }


   void graphics::DPtoLP(LPPOINT lpPoints,count nCount)
   {

      UNREFERENCED_PARAMETER(lpPoints);

      UNREFERENCED_PARAMETER(nCount);

      _throw(interface_only_exception(get_app()));

   }


   void graphics::DPtoLP(LPRECT lpRect)
   {
      UNREFERENCED_PARAMETER(lpRect);
      _throw(interface_only_exception(get_app()));
   }

   void graphics::LPtoDP(LPPOINT lpPoints, count nCount)
   {
      UNREFERENCED_PARAMETER(lpPoints);
      UNREFERENCED_PARAMETER(nCount);
      _throw(interface_only_exception(get_app()));
   }

   void graphics::LPtoDP(LPRECT lpRect)
   {
      UNREFERENCED_PARAMETER(lpRect);
      _throw(interface_only_exception(get_app()));
   }

   bool graphics::FillRgn(::draw2d::region* pRgn, ::draw2d::brush* pBrush)
   {
      UNREFERENCED_PARAMETER(pRgn);
      UNREFERENCED_PARAMETER(pBrush);
      _throw(interface_only_exception(get_app()));

      return false;
   }

   bool graphics::FrameRgn(::draw2d::region* pRgn, ::draw2d::brush* pBrush, i32 nWidth, i32 nHeight)
   {
      UNREFERENCED_PARAMETER(pRgn);
      UNREFERENCED_PARAMETER(pBrush);
      UNREFERENCED_PARAMETER(nWidth);
      UNREFERENCED_PARAMETER(nHeight);
      _throw(interface_only_exception(get_app()));
      return false;
   }

   bool graphics::InvertRgn(::draw2d::region* pRgn)
   {
      UNREFERENCED_PARAMETER(pRgn);
      _throw(interface_only_exception(get_app()));
      return false;

   }

   bool graphics::PaintRgn(::draw2d::region* pRgn)
   {
      UNREFERENCED_PARAMETER(pRgn);
      _throw(interface_only_exception(get_app()));
      return false;
   }

   bool graphics::PtVisible(i32 x, i32 y)
   {
      UNREFERENCED_PARAMETER(x);
      UNREFERENCED_PARAMETER(y);
      _throw(interface_only_exception(get_app()));

      return false;
   }

   bool graphics::PtVisible(POINT point)
   {
      UNREFERENCED_PARAMETER(point);
      _throw(interface_only_exception(get_app()));

      return false;
   }

   bool graphics::RectVisible(const RECT &  lpRect)
   {
      UNREFERENCED_PARAMETER(lpRect);
      _throw(interface_only_exception(get_app()));

      return false;
   }


   pointd graphics::current_position()
   {

      return m_pt;

   }


   bool graphics::move_to(LPCPOINT lppoint)
   {

      return move_to(pointd(lppoint));

   }


   bool graphics::move_to(LPCPOINTD lppoint)
   {

      m_pt = *lppoint;

      return true;

   }


   bool graphics::line_to(LPCPOINT lppoint)
   {

      return line_to(pointd(lppoint));

   }


   bool graphics::line_to(LPCPOINTD lppoint)
   {

      return line_to(point(lppoint));

   }


   bool graphics::draw_line(LPCPOINT lppt1, LPCPOINT lppt2)
   {

      return draw_line(lppt1, lppt2, m_sppen);

   }


   bool graphics::draw_line(LPCPOINT lppt1, LPCPOINT lppt2, ::draw2d::pen * ppen)
   {

      return draw_line(pointd(lppt1), pointd(lppt2), ppen);

   }


   bool graphics::draw_line(LPCPOINTD lppt1, LPCPOINTD lppt2)
   {

      return draw_line(lppt1, lppt2, m_sppen);

   }


   bool graphics::draw_line(LPCPOINTD lppt1, LPCPOINTD lppt2, ::draw2d::pen * ppen)
   {

      return draw_line(point(lppt1), point(lppt2), ppen);

   }


   bool graphics::rectangle(LPCRECT lpcrect)
   {

      return rectangle(rectd(lpcrect));

   }


   bool graphics::rectangle(LPCRECTD lpcrect)
   {

      return rectangle(rect(lpcrect));

   }


   bool graphics::draw_rect(LPCRECT lpcrect)
   {

      return draw_rect(rectd(lpcrect), m_sppen);

   }


   bool graphics::draw_rect(LPCRECTD lpcrect)
   {

      return draw_rect(rect(lpcrect), m_sppen);

   }


   bool graphics::draw_rect(LPCRECT lpcrect, ::draw2d::pen * ppen)
   {

      return draw_rect(rectd(lpcrect), ppen);

   }


   bool graphics::draw_rect(LPCRECTD lpcrect, ::draw2d::pen * ppen)
   {

      return draw_rect(rect(lpcrect), ppen);

   }


   bool graphics::fill_rect(LPCRECT lpcrect)
   {

      return fill_rect(lpcrect, m_spbrush);

   }


   bool graphics::fill_rect(LPCRECTD lpcrect)
   {

      return fill_rect(lpcrect, m_spbrush);

   }


   bool graphics::fill_rect(LPCRECT lpcrect, ::draw2d::brush * pbrush)
   {

      return fill_rect(rectd(lpcrect), pbrush);

   }


   bool graphics::fill_rect(LPCRECTD lpcrect, ::draw2d::brush * pbrush)
   {

      return fill_rect(rect(lpcrect), pbrush);

   }


   bool graphics::Arc(i32 x1, i32 y1, i32 x2, i32 y2, i32 x3, i32 y3, i32 x4, i32 y4)
   {

      UNREFERENCED_PARAMETER(x1);
      UNREFERENCED_PARAMETER(y1);
      UNREFERENCED_PARAMETER(x2);
      UNREFERENCED_PARAMETER(y2);
      UNREFERENCED_PARAMETER(x3);
      UNREFERENCED_PARAMETER(y3);
      UNREFERENCED_PARAMETER(x4);
      UNREFERENCED_PARAMETER(y4);
      _throw(interface_only_exception(get_app()));

      return false;

   }


   bool graphics::Arc(const RECT &  lpRect, POINT ptStart, POINT ptEnd)
   {

      return Arc(lpRect.left,lpRect.top,width(lpRect),height(lpRect),ptStart.x,ptStart.y,ptEnd.x,ptEnd.y);

   }


   bool graphics::Arc(i32 x1, i32 y1, i32 w, i32 h, double start, double extends)
   {

      point ptCenter;

      ptCenter.x = x1 + w / 2;
      ptCenter.y = y1 + h / 2;

      double dx = w / 2.0;
      double dy = h / 2.0;

      double startx = (cos(start * System.math().GetPi() / 180.0) * dx) + ptCenter.x;
      double starty = (sin(start * System.math().GetPi() / 180.0) * dy) + ptCenter.y;

      double endx = (cos((start + extends) * System.math().GetPi() / 180.0) * dx) + ptCenter.x;
      double endy = (sin((start + extends) * System.math().GetPi() / 180.0) * dy) + ptCenter.y;

      return Arc(x1, y1, x1 + w, y1 + h, (i32) startx, (i32) starty, (i32) endx, (i32) endy);

   }

   bool graphics::Arc(const RECT &  lpRect, double start, double extends)
   {
      return Arc(lpRect.left, lpRect.top, width(lpRect), height(lpRect), start, extends);
   }



   bool graphics::Arc(double x1,double y1,double x2,double y2,double x3,double y3,double x4,double y4)
   {
      UNREFERENCED_PARAMETER(x1);
      UNREFERENCED_PARAMETER(y1);
      UNREFERENCED_PARAMETER(x2);
      UNREFERENCED_PARAMETER(y2);
      UNREFERENCED_PARAMETER(x3);
      UNREFERENCED_PARAMETER(y3);
      UNREFERENCED_PARAMETER(x4);
      UNREFERENCED_PARAMETER(y4);
      _throw(interface_only_exception(get_app()));

      return false;
   }


   bool graphics::Arc(const RECTD & lpRect,POINTD ptStart,POINTD ptEnd)
   {

      return Arc(lpRect.left,lpRect.top,width(lpRect), height(lpRect),ptStart.x, ptStart.y, ptEnd.x, ptEnd.y);

   }


   bool graphics::Arc(double x1,double y1,double w,double h,double start,double extends)
   {

      pointd ptCenter;

      ptCenter.x = x1 + w / 2.0;
      ptCenter.y = y1 + h / 2.0;

      double dx = w / 2.0;
      double dy = h / 2.0;

      double startx = (cos(start * System.math().GetPi() / 180.0) * dx) + ptCenter.x;
      double starty = (sin(start * System.math().GetPi() / 180.0) * dy) + ptCenter.y;

      double endx = (cos((start + extends) * System.math().GetPi() / 180.0) * dx) + ptCenter.x;
      double endy = (sin((start + extends) * System.math().GetPi() / 180.0) * dy) + ptCenter.y;

      return Arc(x1,y1,x1 + w,y1 + h,(double)startx,(double)starty,(double)endx,(double)endy);

   }


   bool graphics::Arc(const RECTD & lpRect,double start,double extends)
   {

      return Arc(lpRect.left,lpRect.top,lpRect.right,lpRect.bottom,start,extends);

   }


   bool graphics::Polyline(const POINT* lpPoints,count nCount)
   {
      UNREFERENCED_PARAMETER(lpPoints);
      UNREFERENCED_PARAMETER(nCount);
      _throw(interface_only_exception(get_app()));

      return false;
   }


   void graphics::frame_rect(LPCRECT lpcrect, ::draw2d::brush * pbrush)
   {

      UNREFERENCED_PARAMETER(lpcrect);

      UNREFERENCED_PARAMETER(pbrush);

      _throw(interface_only_exception(get_app()));

   }


   void graphics::invert_rect(LPCRECT lpcrect)
   {

      UNREFERENCED_PARAMETER(lpcrect);

      _throw(interface_only_exception(get_app()));

   }


   bool graphics::DrawIcon(i32 x, i32 y, ::visual::icon * picon)
   {
      UNREFERENCED_PARAMETER(x);
      UNREFERENCED_PARAMETER(y);
      UNREFERENCED_PARAMETER(picon);
      _throw(interface_only_exception(get_app()));

      return false;
   }

   bool graphics::DrawIcon(POINT point, ::visual::icon * picon)
   {
      UNREFERENCED_PARAMETER(point);
      UNREFERENCED_PARAMETER(picon);
      _throw(interface_only_exception(get_app()));


      return false;

   }

   bool graphics::DrawIcon(i32 x, i32 y, ::visual::icon * picon, i32 cx, i32 cy, UINT istepIfAniCur, HBRUSH hbrFlickerFreeDraw, UINT diFlags)
   {
      UNREFERENCED_PARAMETER(x);
      UNREFERENCED_PARAMETER(y);
      UNREFERENCED_PARAMETER(picon);
      UNREFERENCED_PARAMETER(cx);
      UNREFERENCED_PARAMETER(cy);
      UNREFERENCED_PARAMETER(istepIfAniCur);
      UNREFERENCED_PARAMETER(hbrFlickerFreeDraw);
      UNREFERENCED_PARAMETER(diFlags);
      _throw(interface_only_exception(get_app()));

      return false;

   }

   bool graphics::DrawState(point pt, size size, HBITMAP hBitmap, UINT nFlags, HBRUSH hBrush)
   {
      UNREFERENCED_PARAMETER(pt);
      UNREFERENCED_PARAMETER(size);
      UNREFERENCED_PARAMETER(hBitmap);
      UNREFERENCED_PARAMETER(nFlags);
      UNREFERENCED_PARAMETER(hBrush);
      _throw(interface_only_exception(get_app()));

      return false;

   }

   bool graphics::DrawState(point pt, size size, ::draw2d::bitmap* pBitmap, UINT nFlags, ::draw2d::brush* pBrush)
   {
      UNREFERENCED_PARAMETER(pt);
      UNREFERENCED_PARAMETER(size);
      UNREFERENCED_PARAMETER(pBitmap);
      UNREFERENCED_PARAMETER(nFlags);
      UNREFERENCED_PARAMETER(pBrush);
      _throw(interface_only_exception(get_app()));

      return false;
   }

#ifdef WINDOWS

   bool graphics::DrawState(point pt, size size, HICON hIcon, UINT nFlags, HBRUSH hBrush)
   {
      UNREFERENCED_PARAMETER(pt);
      UNREFERENCED_PARAMETER(size);
      UNREFERENCED_PARAMETER(hIcon);
      UNREFERENCED_PARAMETER(nFlags);
      UNREFERENCED_PARAMETER(hBrush);
      _throw(interface_only_exception(get_app()));

      return false;

   }

   bool graphics::DrawState(point pt, size size, HICON hIcon, UINT nFlags, ::draw2d::brush* pBrush)
   {
      UNREFERENCED_PARAMETER(pt);
      UNREFERENCED_PARAMETER(size);
      UNREFERENCED_PARAMETER(hIcon);
      UNREFERENCED_PARAMETER(nFlags);
      UNREFERENCED_PARAMETER(pBrush);
      _throw(interface_only_exception(get_app()));

      return false;

   }

#endif

   bool graphics::DrawState(point pt, size size, const char * lpszText, UINT nFlags, bool bPrefixText, i32 nTextLen, HBRUSH hBrush)
   {
      UNREFERENCED_PARAMETER(pt);
      UNREFERENCED_PARAMETER(size);
      UNREFERENCED_PARAMETER(lpszText);
      UNREFERENCED_PARAMETER(nFlags);
      UNREFERENCED_PARAMETER(bPrefixText);
      UNREFERENCED_PARAMETER(nTextLen);
      UNREFERENCED_PARAMETER(hBrush);
      _throw(interface_only_exception(get_app()));

      return false;

   }

   bool graphics::DrawState(point pt, size size, const char * lpszText, UINT nFlags, bool bPrefixText, i32 nTextLen, ::draw2d::brush* pBrush)
   {
      UNREFERENCED_PARAMETER(pt);
      UNREFERENCED_PARAMETER(size);
      UNREFERENCED_PARAMETER(lpszText);
      UNREFERENCED_PARAMETER(nFlags);
      UNREFERENCED_PARAMETER(bPrefixText);
      UNREFERENCED_PARAMETER(nTextLen);
      UNREFERENCED_PARAMETER(pBrush);
      _throw(interface_only_exception(get_app()));

      return false;


   }

#ifdef WINDOWSEX

   bool graphics::DrawState(point pt, size size, DRAWSTATEPROC lpDrawProc, LPARAM lData, UINT nFlags, HBRUSH hBrush)
   {
      UNREFERENCED_PARAMETER(pt);
      UNREFERENCED_PARAMETER(size);
      UNREFERENCED_PARAMETER(lpDrawProc);
      UNREFERENCED_PARAMETER(lData);
      UNREFERENCED_PARAMETER(nFlags);
      UNREFERENCED_PARAMETER(hBrush);
      _throw(interface_only_exception(get_app()));

      return false;

   }

   bool graphics::DrawState(point pt, size size, DRAWSTATEPROC lpDrawProc, LPARAM lData, UINT nFlags, ::draw2d::brush* pBrush)
   {
      UNREFERENCED_PARAMETER(pt);
      UNREFERENCED_PARAMETER(size);
      UNREFERENCED_PARAMETER(lpDrawProc);
      UNREFERENCED_PARAMETER(lData);
      UNREFERENCED_PARAMETER(nFlags);
      UNREFERENCED_PARAMETER(pBrush);
      _throw(interface_only_exception(get_app()));

      return false;
   }

#endif

   bool graphics::DrawEdge(const RECT & lpRect,UINT nEdge,UINT nFlags)
   {
      UNREFERENCED_PARAMETER(lpRect);
      UNREFERENCED_PARAMETER(nEdge);
      UNREFERENCED_PARAMETER(nFlags);
      _throw(interface_only_exception(get_app()));
      return false;
   }

   bool graphics::DrawFrameControl(const RECT & lpRect,UINT nType,UINT nState)
   {
      UNREFERENCED_PARAMETER(lpRect);
      UNREFERENCED_PARAMETER(nType);
      UNREFERENCED_PARAMETER(nState);
      _throw(interface_only_exception(get_app()));
      return false;
   }

   bool graphics::Chord(i32 x1, i32 y1, i32 x2, i32 y2, i32 x3, i32 y3, i32 x4, i32 y4)
   {
      UNREFERENCED_PARAMETER(x1);
      UNREFERENCED_PARAMETER(y1);
      UNREFERENCED_PARAMETER(x2);
      UNREFERENCED_PARAMETER(y2);
      UNREFERENCED_PARAMETER(x3);
      UNREFERENCED_PARAMETER(y3);
      UNREFERENCED_PARAMETER(x4);
      UNREFERENCED_PARAMETER(y4);
      _throw(interface_only_exception(get_app()));
      return false;
   }

   bool graphics::Chord(const RECT &  lpRect, POINT ptStart, POINT ptEnd)
   {
      UNREFERENCED_PARAMETER(lpRect);
      UNREFERENCED_PARAMETER(ptStart);
      UNREFERENCED_PARAMETER(ptEnd);
      _throw(interface_only_exception(get_app()));
      return false;
   }

   void graphics::DrawFocusRect(const RECT &  lpRect)
   {
      UNREFERENCED_PARAMETER(lpRect);
      _throw(interface_only_exception(get_app()));
   }

   bool graphics::Ellipse(i32 x1, i32 y1, i32 x2, i32 y2)
   {

      bool bFill = FillEllipse(x1, y1, x2, y2);

      bool bDraw = DrawEllipse(x1, y1, x2, y2);

      return bFill && bDraw;

   }

   bool graphics::Ellipse(const RECT &  lpRect)
   {

      bool bFill = FillEllipse(lpRect);

      bool bDraw = DrawEllipse(lpRect);

      return bFill && bDraw;

   }


   bool graphics::DrawEllipse(i32 x1, i32 y1, i32 x2, i32 y2)
   {
      UNREFERENCED_PARAMETER(x1);
      UNREFERENCED_PARAMETER(y1);
      UNREFERENCED_PARAMETER(x2);
      UNREFERENCED_PARAMETER(y2);
      _throw(interface_only_exception(get_app()));
      return false;
   }

   bool graphics::DrawEllipse(const RECT &  lpRect)
   {
      UNREFERENCED_PARAMETER(lpRect);
      _throw(interface_only_exception(get_app()));
      return false;
   }

   bool graphics::FillEllipse(i32 x1, i32 y1, i32 x2, i32 y2)
   {

      ::rect rect(x1, y1, x2, y2);

      return FillEllipse(rect);


   }

   bool graphics::FillEllipse(const RECT &  lpRect)
   {
      UNREFERENCED_PARAMETER(lpRect);
      _throw(interface_only_exception(get_app()));
      return false;
   }


   bool graphics::Ellipse(double x1,double y1,double x2,double y2)
   {

      bool bFill = FillEllipse(x1,y1,x2,y2);

      bool bDraw = DrawEllipse(x1,y1,x2,y2);

      return bFill && bDraw;

   }

   bool graphics::Ellipse(const RECTD & lpRect)
   {

      bool bFill = FillEllipse(lpRect);

      bool bDraw = DrawEllipse(lpRect);

      return bFill && bDraw;

   }


   bool graphics::DrawEllipse(double x1,double y1,double x2,double y2)
   {

      RECTD r;

      r.left = x1;
      r.top = y1;
      r.right = x2;
      r.bottom = y2;

      return DrawEllipse(r);

   }


   bool graphics::DrawEllipse(const RECTD & r)
   {

      return DrawEllipse(r.left, r.top, r.right, r.bottom);

   }


   bool graphics::FillEllipse(double x1,double y1,double x2,double y2)
   {

      ::rectd rect(x1,y1,x2,y2);

      return FillEllipse(rect);


   }

   bool graphics::FillEllipse(const RECTD & lpRect)
   {
      UNREFERENCED_PARAMETER(lpRect);
      _throw(interface_only_exception(get_app()));
      return false;
   }

   bool graphics::Pie(i32 x1, i32 y1, i32 x2, i32 y2, i32 x3, i32 y3, i32 x4, i32 y4)
   {
      UNREFERENCED_PARAMETER(x1);
      UNREFERENCED_PARAMETER(y1);
      UNREFERENCED_PARAMETER(x2);
      UNREFERENCED_PARAMETER(y2);
      UNREFERENCED_PARAMETER(x3);
      UNREFERENCED_PARAMETER(y3);
      UNREFERENCED_PARAMETER(x4);
      UNREFERENCED_PARAMETER(y4);
      _throw(interface_only_exception(get_app()));
      return false;
   }

   bool graphics::Pie(const RECT &  lpRect, POINT ptStart, POINT ptEnd)
   {

      UNREFERENCED_PARAMETER(lpRect);
      UNREFERENCED_PARAMETER(ptStart);
      UNREFERENCED_PARAMETER(ptEnd);

      _throw(interface_only_exception(get_app()));

      return false;

   }


   bool graphics::fill_polygon(LPCPOINTD lppoints,count nCount)
   {

      point_array pta;

      ::lemon::array::copy_points(pta, lppoints, nCount);

      return draw_polygon(pta.get_data(), pta.get_count());

   }


   bool graphics::draw_polygon(LPCPOINTD lppoints,count nCount)
   {

      point_array pta;

      ::lemon::array::copy_points(pta, lppoints, nCount);

      return draw_polygon(pta.get_data(), pta.get_count());

   }


   bool graphics::fill_polygon(LPCPOINT lppoints,count nCount)
   {

      pointd_array pta;

      ::lemon::array::copy_points(pta, lppoints, nCount);

      return fill_polygon(pta.get_data(), pta.get_count());

   }


   bool graphics::draw_polygon(LPCPOINT lppoints,count nCount)
   {

      pointd_array pta;

      ::lemon::array::copy_points(pta, lppoints, nCount);

      return draw_polygon(pta.get_data(), pta.get_count());

   }


   bool graphics::polygon(LPCPOINT ppoints, count nCount)
   {

      bool bOk1 = fill_polygon(ppoints, nCount);

      bool bOk2 = draw_polygon(ppoints, nCount);

      return bOk1 && bOk2;

   }


   bool graphics::polygon(LPCPOINTD ppoints, count nCount)
   {

      bool bOk1 = fill_polygon(ppoints, nCount);

      bool bOk2 = draw_polygon(ppoints, nCount);

      return bOk1 && bOk2;

   }


   bool graphics::poly_polygon(LPCPOINT ppoints, LPCINT pPolyCounts, count nCount)
   {

      bool bOk1 = fill_poly_polygon(ppoints, pPolyCounts, nCount);

      bool bOk2 = draw_poly_polygon(ppoints, pPolyCounts, nCount);

      return bOk1 && bOk2;

   }

   bool graphics::poly_polygon(LPCPOINTD ppoints, LPCINT pPolyCounts, count nCount)
   {

      bool bOk1 = fill_poly_polygon(ppoints, pPolyCounts, nCount);

      bool bOk2 = draw_poly_polygon(ppoints, pPolyCounts, nCount);

      return bOk1 && bOk2;

   }


   bool graphics::draw_poly_polygon(LPCPOINT ppoints, LPCINT pPolyCounts, count nCount)
   {

      bool bOk = true;

      for(int i = 0; i < nCount; i++)
      {

         if (!draw_polygon(ppoints, *pPolyCounts))
         {

            bOk = false;

         }

         ppoints += *pPolyCounts;

         pPolyCounts++;

      }

      return bOk;

   }


   bool graphics::draw_poly_polygon(LPCPOINTD ppoints, LPCINT pPolyCounts, count nCount)
   {

      bool bOk = true;

      for (int i = 0; i < nCount; i++)
      {

         if (!draw_polygon(ppoints, *pPolyCounts))
         {

            bOk = false;

         }

         ppoints += *pPolyCounts;

         pPolyCounts++;

      }

      return bOk;

   }


   bool graphics::fill_poly_polygon(LPCPOINT ppoints, LPCINT pPolyCounts, count nCount)
   {

      bool bOk = true;

      for (int i = 0; i < nCount; i++)
      {

         if (!fill_polygon(ppoints, *pPolyCounts))
         {

            bOk = false;

         }

         ppoints += *pPolyCounts;

         pPolyCounts++;

      }

      return bOk;

   }


   bool graphics::fill_poly_polygon(LPCPOINTD ppoints, LPCINT pPolyCounts, count nCount)
   {

      bool bOk = true;

      for (int i = 0; i < nCount; i++)
      {

         if (!fill_polygon(ppoints, *pPolyCounts))
         {

            bOk = false;

         }

         ppoints += *pPolyCounts;

         pPolyCounts++;

      }

      return bOk;

   }


   bool graphics::round_rect(LPCRECT lpcrect, LPCPOINT lppt)
   {

      return round_rect(::rectd(lpcrect), ::pointd(lppt));

   }


   bool graphics::round_rect(LPCRECTD lpcrect, LPCPOINTD lppt)
   {

      return round_rect(::rect(lpcrect), ::point(lppt));

   }


   bool graphics::PatBlt(i32 x, i32 y, i32 nWidth, i32 nHeight, u32 dwRop)
   {
      UNREFERENCED_PARAMETER(x);
      UNREFERENCED_PARAMETER(y);
      UNREFERENCED_PARAMETER(nWidth);
      UNREFERENCED_PARAMETER(nHeight);
      UNREFERENCED_PARAMETER(dwRop);
      _throw(interface_only_exception(get_app()));
      return false;
   }


   bool graphics::draw(LPCRECT lpcrect, ::draw2d::graphics * pgraphicsSrc, LPCPOINT ppt, u32 dwRop)
   {


      i32 x = lpcrect->left;
      i32 y = lpcrect->top;
      i32 xSrc = ppt->x;
      i32 ySrc = ppt->y;
      i32 nWidth = ::width(lpcrect);
      i32 nHeight = ::height(lpcrect);

      if(m_bPat)
      {

         if(pgraphicsSrc->m_pdibDraw2dGraphics != NULL)
         {

            if(pgraphicsSrc->m_pdibDraw2dGraphics->area() > 0)
            {

               int xs = 0;

               int ys = 0;

               i32 w1 = pgraphicsSrc->m_pdibDraw2dGraphics->m_size.cx;

               i32 h1 = pgraphicsSrc->m_pdibDraw2dGraphics->m_size.cy;

               i32 w0 = w1 - xSrc;

               i32 h0 = h1 - ySrc;

               int w = w0;

               int h = h0;

               for(int i = 0; i < nWidth; i += w)
               {

                  if(i == 0)
                  {

                     w = w0;

                     xs = xSrc;

                  }
                  else
                  {

                     w = w1;

                     xs = 0;

                  }

                  for(int j = 0; j < nHeight; j += h)
                  {

                     if(j == 0)
                     {

                        h = h0;

                        ys = ySrc;

                     }
                     else
                     {

                        h = h1;

                        ys = 0;

                     }

                     if (!BitBltAlphaBlend(x + i, y + j, w, h, pgraphicsSrc, xs, ys, dwRop))
                     {

                        if (!BitBltRaw(x + i, y + j, w, h, pgraphicsSrc, xs, ys, dwRop))
                        {

                        }

                     }


                  }

               }

               return true;

            }

         }

      }


      if (BitBltAlphaBlend(x, y, nWidth, nHeight, pgraphicsSrc, xSrc, ySrc, dwRop))
      {

         return true;

      }

      if (BitBltRaw(x, y, nWidth, nHeight, pgraphicsSrc, xSrc, ySrc, dwRop))
      {

         return true;

      }

      return false;

   }


   bool graphics::BitBltRaw(i32 x, i32 y, i32 nWidth, i32 nHeight, ::draw2d::graphics * pgraphicsSrc, i32 xSrc, i32 ySrc, u32 dwRop)
   {

      return false;

   }


   bool graphics::BitBltAlphaBlend(i32 x, i32 y, i32 nWidth, i32 nHeight, ::draw2d::graphics * pgraphicsSrc, i32 xSrc, i32 ySrc, u32 dwRop)
   {

      // return ::draw2d::graphics::BitBltAlphaBlend(x, y, nWidth, nHeight, pgraphicsSrc, xSrc, ySrc, dwRop);

      if (m_pdibAlphaBlend != NULL)
      {

         // Reference implementation

         rect rectIntersect(m_ptAlphaBlend, m_pdibAlphaBlend->size());

         rect rectBlt(point((int64_t)x, (int64_t)y), size(nWidth, nHeight));

         if (rectIntersect.intersect(rectIntersect, rectBlt))
         {

            // The following commented out code does not work well when there is clipping
            // and some calculations are not precise
            //if (m_pdib != NULL && pgraphicsSrc->m_pdib != NULL)
            //{

            //   point ptOff = GetViewportOrg();

            //   x += ptOff.x;

            //   y += ptOff.y;

            //   return m_pdib->blend(point(x, y), pgraphicsSrc->m_pdib, point(xSrc, ySrc), m_pdibAlphaBlend, point(m_ptAlphaBlend.x - x, m_ptAlphaBlend.y - y), rectBlt.size());

            //}
            //else
            {

               ::draw2d::dib_sp dib1(allocer());
//#ifdef METROWIN
//               g_pdiba->add(dib1);
//#endif

               dib1->create(rectBlt.get_size());

               dib1->get_graphics()->set_alpha_mode(::draw2d::alpha_mode_set);

               if (!dib1->from(null_point(), pgraphicsSrc, point(xSrc, ySrc), rectBlt.get_size()))
                  return false;

               dib1->blend(point(0, 0), m_pdibAlphaBlend, point((int)MAX(0, x - m_ptAlphaBlend.x), (int)MAX(0, y - m_ptAlphaBlend.y)), rectBlt.get_size());

               BitBltRaw(x, y, nWidth, nHeight, dib1->get_graphics(), 0, 0, dwRop);

            }

            return true;

         }



      }

      return false;

   }


   bool graphics::StretchBlt(rect rectDst, ::draw2d::graphics * pgraphicsSrc)
   {

      if(pgraphicsSrc == NULL)
      {

         return false;

      }

      ::draw2d::dib * pdib = pgraphicsSrc->m_pdibDraw2dGraphics;

      if(pdib == NULL)
      {

         return false;

      }

      rect rectSrc(::null_point(), pdib->m_size);

      return StretchBlt(rectDst, pgraphicsSrc, rectSrc);

   }


   bool graphics::draw(LPCRECT lpcrectDst, ::draw2d::graphics * pgraphicsSrc, LPCRECT lpcrectSrc, u32 dwRop)
   {

      return StretchBlt(lpcrectDst, pgraphicsSrc, lpcrectSrc, dwRop);

   }


   bool graphics::StretchBlt(rect rectDst, ::draw2d::graphics * pgraphicsSrc, rect rectSrc, u32 dwRop)
   {

      return StretchBlt(
             rectDst.left,
             rectDst.top,
             rectDst.width(),
             rectDst.height(),
             pgraphicsSrc,
             rectSrc.left,
             rectSrc.top,
             rectSrc.width(),
             rectSrc.height(),
             dwRop);

   }


   bool graphics::StretchBlt(i32 x, i32 y, i32 nWidth, i32 nHeight, ::draw2d::graphics * pgraphicsSrc, i32 xSrc, i32 ySrc, i32 nSrcWidth, i32 nSrcHeight, u32 dwRop)
   {

      if (StretchBltAlphaBlend(x, y, nWidth, nHeight, pgraphicsSrc, xSrc, ySrc, nSrcWidth, nSrcHeight, dwRop))
      {

         return true;

      }

      if (StretchBltRaw(x, y, nWidth, nHeight, pgraphicsSrc, xSrc, ySrc, nSrcWidth, nSrcHeight, dwRop))
      {

         return true;

      }

      return false;

   }


   bool graphics::StretchBltAlphaBlend(i32 xDst, i32 yDst, i32 nDstWidth, i32 nDstHeight, ::draw2d::graphics * pgraphicsSrc, i32 xSrc, i32 ySrc, i32 nSrcWidth, i32 nSrcHeight, u32 dwRop)
   {

      if (m_pdibAlphaBlend != NULL)
      {


         rect rectIntersect(m_ptAlphaBlend, m_pdibAlphaBlend->size());

         rect rectBlt(point((int64_t)xDst, (int64_t)yDst), size(nDstWidth, nDstHeight));

         if (rectIntersect.intersect(rectIntersect, rectBlt))
         {

            ::draw2d::dib * pdibWork = NULL;
            ::draw2d::dib * pdibWork2 = NULL;
            //         ::draw2d::dib * pdibWork3 = NULL;
            ::draw2d::dib * pdibWork4 = NULL;


            class point ptSrc(xSrc, ySrc);
            class point ptDst(xDst, yDst);
            class size sizeSrc(nSrcWidth, nSrcHeight);
            class size sizeDst(nDstWidth, nDstHeight);



            ::draw2d::dib_sp spdib;
            if (pdibWork == NULL)
            {
               spdib.alloc(allocer());
               pdibWork = spdib;
            }
            if (pdibWork == NULL)
               return false;
            if (!pdibWork->create(sizeDst))
               return false;
            if (!pdibWork->get_graphics()->StretchBltRaw(
                  0, 0,
                  nDstWidth, nDstHeight,
                  pgraphicsSrc,
                  xSrc, ySrc,
                  nSrcWidth, nSrcHeight))
               return false;




            ::draw2d::dib_sp spdib2;
            if (pdibWork2 == NULL)
            {
               spdib2.alloc(allocer());
               pdibWork2 = spdib2;
            }


            ::draw2d::dib_sp spdib4;
            if (pdibWork4 == NULL)
            {
               spdib4.alloc(allocer());
               pdibWork4 = spdib4;
            }
            if (pdibWork4 == NULL)
               return false;
            if (!pdibWork4->create(sizeDst))
               return false;


            pdibWork4->Fill(255, 0, 0, 0);

            pdibWork4->from(point(MAX(0, m_ptAlphaBlend.x - xDst), MAX(0, m_ptAlphaBlend.y - yDst)),
                            m_pdibAlphaBlend->get_graphics(), point(MAX(0, xDst - m_ptAlphaBlend.x), MAX(0, yDst - m_ptAlphaBlend.y)), sizeDst);

            pdibWork->channel_multiply(visual::rgba::channel_alpha, pdibWork4);

            BitBltRaw(ptDst.x, ptDst.y, sizeDst.cx, sizeDst.cy, pdibWork->get_graphics(), ptSrc.x, ptSrc.y, SRCCOPY);

            return true;

         }

      }

      return false;

   }


   bool graphics::StretchBltRaw(i32 x, i32 y, i32 nWidth, i32 nHeight, ::draw2d::graphics * pgraphicsSrc, i32 xSrc, i32 ySrc, i32 nSrcWidth, i32 nSrcHeight, u32 dwRop)
   {

      return false;

   }


   COLORREF graphics::GetPixel(i32 x, i32 y)
   {
      UNREFERENCED_PARAMETER(x);
      UNREFERENCED_PARAMETER(y);
      _throw(interface_only_exception(get_app()));
      return 0;
   }

   COLORREF graphics::GetPixel(POINT point)
   {
      UNREFERENCED_PARAMETER(point);
      _throw(interface_only_exception(get_app()));
      return 0;
   }

   COLORREF graphics::SetPixel(i32 x, i32 y, COLORREF crColor)
   {
      UNREFERENCED_PARAMETER(x);
      UNREFERENCED_PARAMETER(y);
      UNREFERENCED_PARAMETER(crColor);
      _throw(interface_only_exception(get_app()));
      return 0;
   }

   COLORREF graphics::SetPixel(POINT point, COLORREF crColor)
   {
      UNREFERENCED_PARAMETER(point);
      UNREFERENCED_PARAMETER(crColor);
      _throw(interface_only_exception(get_app()));
      return 0;
   }

   bool graphics::FloodFill(i32 x, i32 y, COLORREF crColor)
   {
      UNREFERENCED_PARAMETER(x);
      UNREFERENCED_PARAMETER(y);
      UNREFERENCED_PARAMETER(crColor);
      _throw(interface_only_exception(get_app()));
      return false;
   }

   bool graphics::ExtFloodFill(i32 x, i32 y, COLORREF crColor, UINT nFillType)
   {
      UNREFERENCED_PARAMETER(x);
      UNREFERENCED_PARAMETER(y);
      UNREFERENCED_PARAMETER(crColor);
      UNREFERENCED_PARAMETER(nFillType);
      _throw(interface_only_exception(get_app()));
      return false;
   }


   bool graphics::text_out(i32 x, i32 y, const char * lpszString, strsize nCount)
   {

      return text_out((double)x, (double)y, lpszString, nCount);

   }


   bool graphics::text_out(i32 x, i32 y, const string & str)
   {

      return text_out((double) x, (double) y, str);

   }


   bool graphics::text_out(double x, double y, const char * lpszString, strsize nCount)
   {

      if (TextOutAlphaBlend(x, y, lpszString, nCount))
      {

         return true;

      }

      if (TextOutRaw(x, y, lpszString, nCount))
      {

         return true;

      }

      return false;

   }


   bool graphics::TextOutRaw(double x, double y, const char * lpszString, strsize nCount)
   {

      return false;

   }


   bool graphics::TextOutAlphaBlend(double x, double y, const char * lpszString, strsize nCount)
   {

      if (m_pdibAlphaBlend != NULL)
      {

         single_lock sl(m_pmutex);

         if (nCount < 0)
         {

            return false;

         }

         // "Reference" implementation for TextOutAlphaBlend

         rect rectIntersect(m_ptAlphaBlend, m_pdibAlphaBlend->size());

         ::size size = ::size(GetTextExtent(lpszString, nCount));

         //size.cx = size.cx * 110 / 100;

         //size.cy = size.cy * 110 / 100;

         rect rectText(point((int64_t)x, (int64_t)y), size);

         if (rectIntersect.intersect(rectIntersect, rectText))
         {

            ::draw2d::dib_sp dib1(allocer());
//#ifdef METROWIN
//            g_pdiba->add(dib1);
//#endif

            dib1->create(rectText.get_size());

            dib1->get_graphics()->SelectObject(get_current_font());

            dib1->get_graphics()->SelectObject(get_current_brush());

            dib1->get_graphics()->set_alpha_mode(::draw2d::alpha_mode_set);

            dib1->get_graphics()->text_out(0, 0, lpszString, nCount);

            dib1->blend(null_point(), m_pdibAlphaBlend, point((int)MAX(0, x - m_ptAlphaBlend.x), (int)MAX(0, y - m_ptAlphaBlend.y)), rectText.get_size());

            BitBltRaw((int)x, (int)y, rectText.width(), rectText.height(), dib1->get_graphics(), 0, 0, SRCCOPY);

            return true;

         }



      }

      return false;

   }


   bool graphics::text_out(double x, double y, const string & str)
   {

      return text_out(x, y, str, (i32) str.get_length());

   }


   bool graphics::ExtTextOut(i32 x, i32 y, UINT nOptions, const RECT &  lpRect, const char * lpszString, count nCount, LPINT lpDxWidths)
   {
      UNREFERENCED_PARAMETER(x);
      UNREFERENCED_PARAMETER(y);
      UNREFERENCED_PARAMETER(nOptions);
      UNREFERENCED_PARAMETER(lpRect);
      UNREFERENCED_PARAMETER(lpszString);
      UNREFERENCED_PARAMETER(nCount);
      UNREFERENCED_PARAMETER(lpDxWidths);
      _throw(interface_only_exception(get_app()));
      return false;
   }

   bool graphics::ExtTextOut(i32 x, i32 y, UINT nOptions, const RECT &  lpRect, const string & str, LPINT lpDxWidths)
   {
      UNREFERENCED_PARAMETER(x);
      UNREFERENCED_PARAMETER(y);
      UNREFERENCED_PARAMETER(nOptions);
      UNREFERENCED_PARAMETER(lpRect);
      UNREFERENCED_PARAMETER(str);
      UNREFERENCED_PARAMETER(lpDxWidths);
      _throw(interface_only_exception(get_app()));
      return false;
   }

   size graphics::TabbedTextOut(i32 x, i32 y, const char * lpszString, strsize nCount, count nTabPositions, LPINT lpnTabStopPositions, int nTabOrigin)
   {
      UNREFERENCED_PARAMETER(x);
      UNREFERENCED_PARAMETER(y);
      UNREFERENCED_PARAMETER(lpszString);
      UNREFERENCED_PARAMETER(nCount);
      UNREFERENCED_PARAMETER(nTabPositions);
      UNREFERENCED_PARAMETER(lpnTabStopPositions);
      UNREFERENCED_PARAMETER(nTabOrigin);
      _throw(interface_only_exception(get_app()));
      return size(0, 0);
   }

   size graphics::TabbedTextOut(i32 x, i32 y, const string & str, count nTabPositions, LPINT lpnTabStopPositions, int nTabOrigin)
   {
      UNREFERENCED_PARAMETER(x);
      UNREFERENCED_PARAMETER(y);
      UNREFERENCED_PARAMETER(str);
      UNREFERENCED_PARAMETER(nTabPositions);
      UNREFERENCED_PARAMETER(lpnTabStopPositions);
      UNREFERENCED_PARAMETER(nTabOrigin);
      _throw(interface_only_exception(get_app()));
      return size(0, 0);
   }

   size graphics::GetTabbedTextExtent(const char * lpszString, strsize nCount, count nTabPositions, LPINT lpnTabStopPositions)
   {
      UNREFERENCED_PARAMETER(lpszString);
      UNREFERENCED_PARAMETER(nCount);
      UNREFERENCED_PARAMETER(nTabPositions);
      UNREFERENCED_PARAMETER(lpnTabStopPositions);
      _throw(interface_only_exception(get_app()));
      return size(0, 0);
   }


   size graphics::GetTabbedTextExtent(const string & str, count nTabPositions, LPINT lpnTabStopPositions)
   {

      UNREFERENCED_PARAMETER(str);
      UNREFERENCED_PARAMETER(nTabPositions);
      UNREFERENCED_PARAMETER(lpnTabStopPositions);
      _throw(interface_only_exception(get_app()));

      return size(0, 0);

   }


   size graphics::GetOutputTabbedTextExtent(const char * lpszString, strsize nCount,count nTabPositions, LPINT lpnTabStopPositions)
   {

      UNREFERENCED_PARAMETER(lpszString);
      UNREFERENCED_PARAMETER(nCount);
      UNREFERENCED_PARAMETER(nTabPositions);
      UNREFERENCED_PARAMETER(lpnTabStopPositions);
      _throw(interface_only_exception(get_app()));

      return size(0, 0);

   }


   size graphics::GetOutputTabbedTextExtent(const string & str, count nTabPositions, LPINT lpnTabStopPositions)
   {

      UNREFERENCED_PARAMETER(str);
      UNREFERENCED_PARAMETER(nTabPositions);
      UNREFERENCED_PARAMETER(lpnTabStopPositions);
      _throw(interface_only_exception(get_app()));

      return size(0, 0);

   }


   bool graphics::GrayString(::draw2d::brush* pBrush, bool (CALLBACK* lpfnOutput)(HDC, LPARAM, i32), LPARAM lpData, i32 nCount, i32 x, i32 y, i32 nWidth, i32 nHeight)
   {
      UNREFERENCED_PARAMETER(pBrush);
      UNREFERENCED_PARAMETER(lpfnOutput);
      UNREFERENCED_PARAMETER(lpData);
      UNREFERENCED_PARAMETER(nCount);
      UNREFERENCED_PARAMETER(x);
      UNREFERENCED_PARAMETER(y);
      UNREFERENCED_PARAMETER(nWidth);
      UNREFERENCED_PARAMETER(nHeight);
      _throw(interface_only_exception(get_app()));
      return false;
   }

   UINT graphics::GetTextAlign()
   {
      _throw(interface_only_exception(get_app()));
      return -1;
   }

   i32 graphics::GetTextFace(count nCount, LPTSTR lpszFacename)
   {
      UNREFERENCED_PARAMETER(nCount);
      UNREFERENCED_PARAMETER(lpszFacename);
      _throw(interface_only_exception(get_app()));
      return -1;
   }

   i32 graphics::GetTextFace(string & rString)
   {
      UNREFERENCED_PARAMETER(rString);
      _throw(interface_only_exception(get_app()));
      return -1;
   }

   bool graphics::get_text_metrics(text_metric * lpMetrics)
   {
      UNREFERENCED_PARAMETER(lpMetrics);
      _throw(interface_only_exception(get_app()));
      return false;
   }

   bool graphics::get_output_text_metrics(text_metric * lpMetrics)
   {
      UNREFERENCED_PARAMETER(lpMetrics);
      _throw(interface_only_exception(get_app()));
      return false;
   }

   i32 graphics::GetTextCharacterExtra()
   {
      _throw(interface_only_exception(get_app()));
      return -1;
   }

   bool graphics::GetCharWidth(UINT nFirstChar, UINT nLastChar, LPINT lpBuffer)
   {
      UNREFERENCED_PARAMETER(nFirstChar);
      UNREFERENCED_PARAMETER(nLastChar);
      UNREFERENCED_PARAMETER(lpBuffer);
      _throw(interface_only_exception(get_app()));
      return false;
   }

   bool graphics::GetOutputCharWidth(UINT nFirstChar, UINT nLastChar, LPINT lpBuffer)
   {
      UNREFERENCED_PARAMETER(nFirstChar);
      UNREFERENCED_PARAMETER(nLastChar);
      UNREFERENCED_PARAMETER(lpBuffer);
      _throw(interface_only_exception(get_app()));
      return false;
   }

   u32 graphics::GetFontLanguageInfo()
   {
      _throw(interface_only_exception(get_app()));
      return -1;
   }

#ifdef WINDOWSEX

   u32 graphics::GetCharacterPlacement(const char * lpString, strsize nCount, strsize nMaxExtent, LPGCP_RESULTS lpResults, u32 dwFlags)
   {
      UNREFERENCED_PARAMETER(lpString);
      UNREFERENCED_PARAMETER(nCount);
      UNREFERENCED_PARAMETER(nMaxExtent);
      UNREFERENCED_PARAMETER(lpResults);
      UNREFERENCED_PARAMETER(dwFlags);
      _throw(interface_only_exception(get_app()));
      return -1;
   }

   u32 graphics::GetCharacterPlacement(string & str, strsize nMaxExtent, LPGCP_RESULTS lpResults, u32 dwFlags)
   {
      UNREFERENCED_PARAMETER(str);
      UNREFERENCED_PARAMETER(nMaxExtent);
      UNREFERENCED_PARAMETER(lpResults);
      UNREFERENCED_PARAMETER(dwFlags);
      _throw(interface_only_exception(get_app()));
      return -1;
   }

#endif

   size graphics::GetAspectRatioFilter()
   {
      _throw(interface_only_exception(get_app()));
      return size(0, 0);
   }

   bool graphics::ScrollDC(i32 dx, i32 dy, const RECT &  lpRectScroll, const RECT &  lpRectClip, ::draw2d::region * pRgnUpdate, LPRECT lpRectUpdate)
   {
      UNREFERENCED_PARAMETER(dx);
      UNREFERENCED_PARAMETER(dy);
      UNREFERENCED_PARAMETER(lpRectScroll);
      UNREFERENCED_PARAMETER(lpRectClip);
      UNREFERENCED_PARAMETER(pRgnUpdate);
      UNREFERENCED_PARAMETER(lpRectUpdate);
      _throw(interface_only_exception(get_app()));
      return false;
   }

   // Printer Escape Functions
   i32 graphics::Escape(i32 nEscape, i32 nCount, const char * lpszInData, LPVOID lpOutData)
   {
      UNREFERENCED_PARAMETER(nEscape);
      UNREFERENCED_PARAMETER(nCount);
      UNREFERENCED_PARAMETER(lpszInData);
      UNREFERENCED_PARAMETER(lpOutData);
      _throw(interface_only_exception(get_app()));
      return -1;
   }

   // ::draw2d::graphics_sp 3.1 Specific functions
   UINT graphics::SetBoundsRect(const RECT &  lpRectBounds, UINT flags)
   {
      UNREFERENCED_PARAMETER(lpRectBounds);
      UNREFERENCED_PARAMETER(flags);
      _throw(interface_only_exception(get_app()));
      return -1;
   }

   UINT graphics::GetBoundsRect(LPRECT lpRectBounds, UINT flags)
   {
      UNREFERENCED_PARAMETER(lpRectBounds);
      UNREFERENCED_PARAMETER(flags);
      _throw(interface_only_exception(get_app()));
      return -1;
   }

#if !defined(LINUX) && !defined(APPLEOS) && !defined(ANDROID) && !defined(SOLARIS)

   bool graphics::ResetDC(const DEVMODE* lpDevMode)
   {
      UNREFERENCED_PARAMETER(lpDevMode);
      _throw(interface_only_exception(get_app()));
      return false;
   }

#endif


#ifdef WINDOWSEX

   UINT graphics::GetOutlineTextMetrics(UINT cbData, LPOUTLINETEXTMETRICW lpotm)
   {
      UNREFERENCED_PARAMETER(cbData);
      UNREFERENCED_PARAMETER(lpotm);
      _throw(interface_only_exception(get_app()));
      return -1;
   }

   bool graphics::GetCharABCWidths(UINT nFirstChar, UINT nLastChar, LPABC lpabc)
   {
      UNREFERENCED_PARAMETER(nFirstChar);
      UNREFERENCED_PARAMETER(nLastChar);
      UNREFERENCED_PARAMETER(lpabc);
      _throw(interface_only_exception(get_app()));
      return false;
   }

#endif

   u32 graphics::GetFontData(u32 dwTable, u32 dwOffset, LPVOID lpData,  u32 cbData)
   {
      UNREFERENCED_PARAMETER(dwTable);
      UNREFERENCED_PARAMETER(dwOffset);
      UNREFERENCED_PARAMETER(lpData);
      UNREFERENCED_PARAMETER(cbData);
      _throw(interface_only_exception(get_app()));
      return -1;
   }

#ifdef WINDOWSEX

   i32 graphics::GetKerningPairs(i32 nPairs, LPKERNINGPAIR lpkrnpair)
   {
      UNREFERENCED_PARAMETER(nPairs);
      UNREFERENCED_PARAMETER(lpkrnpair);
      _throw(interface_only_exception(get_app()));
      return -1;
   }

   u32 graphics::GetGlyphOutline(UINT nChar, UINT nFormat, LPGLYPHMETRICS lpgm,  u32 cbBuffer, LPVOID lpBuffer, const MAT2* lpmat2)
   {
      UNREFERENCED_PARAMETER(nChar);
      UNREFERENCED_PARAMETER(nFormat);
      UNREFERENCED_PARAMETER(lpgm);
      UNREFERENCED_PARAMETER(cbBuffer);
      UNREFERENCED_PARAMETER(lpBuffer);
      UNREFERENCED_PARAMETER(lpmat2);
      _throw(interface_only_exception(get_app()));
      return -1;
   }

   // ::user::document handling functions
   i32 graphics::StartDoc(LPDOCINFO lpDocInfo)
   {
      UNREFERENCED_PARAMETER(lpDocInfo);
      _throw(interface_only_exception(get_app()));
      return -1;
   }

#endif

   i32 graphics::StartPage()
   {
      _throw(interface_only_exception(get_app()));
      return -1;
   }

   i32 graphics::EndPage()
   {
      _throw(interface_only_exception(get_app()));
      return -1;
   }

   i32 graphics::SetAbortProc(bool (CALLBACK* lpfn)(HDC, i32))
   {
      UNREFERENCED_PARAMETER(lpfn);
      _throw(interface_only_exception(get_app()));
      return -1;
   }

   i32 graphics::AbortDoc()
   {
      _throw(interface_only_exception(get_app()));
      return -1;
   }

   i32 graphics::EndDoc()
   {
      _throw(interface_only_exception(get_app()));
      return -1;
   }

   bool graphics::MaskBlt(i32 x, i32 y, i32 nWidth, i32 nHeight, ::draw2d::graphics * pgraphicsSrc,
                          i32 xSrc, i32 ySrc, ::draw2d::bitmap& maskBitmap, i32 xMask, i32 yMask, u32 dwRop)
   {
      UNREFERENCED_PARAMETER(x);
      UNREFERENCED_PARAMETER(y);
      UNREFERENCED_PARAMETER(nWidth);
      UNREFERENCED_PARAMETER(nHeight);
      UNREFERENCED_PARAMETER(pgraphicsSrc);
      UNREFERENCED_PARAMETER(xSrc);
      UNREFERENCED_PARAMETER(ySrc);
      UNREFERENCED_PARAMETER(maskBitmap);
      UNREFERENCED_PARAMETER(xMask);
      UNREFERENCED_PARAMETER(yMask);
      UNREFERENCED_PARAMETER(dwRop);

      _throw(interface_only_exception(get_app()));
      return false;
   }
   bool graphics::PlgBlt(LPPOINT lpPoint, ::draw2d::graphics * pgraphicsSrc, i32 xSrc, i32 ySrc,
                         i32 nWidth, i32 nHeight, ::draw2d::bitmap& maskBitmap, i32 xMask, i32 yMask)
   {
      UNREFERENCED_PARAMETER(lpPoint);
      UNREFERENCED_PARAMETER(pgraphicsSrc);
      UNREFERENCED_PARAMETER(xSrc);
      UNREFERENCED_PARAMETER(ySrc);
      UNREFERENCED_PARAMETER(nWidth);
      UNREFERENCED_PARAMETER(nHeight);
      UNREFERENCED_PARAMETER(maskBitmap);
      UNREFERENCED_PARAMETER(xMask);
      UNREFERENCED_PARAMETER(yMask);
      UNREFERENCED_PARAMETER(ySrc);
      _throw(interface_only_exception(get_app()));
      return false;
   }

   bool graphics::SetPixelV(i32 x, i32 y, COLORREF crColor)
   {
      UNREFERENCED_PARAMETER(x);
      UNREFERENCED_PARAMETER(y);
      UNREFERENCED_PARAMETER(crColor);
      _throw(interface_only_exception(get_app()));
      return false;
   }

   bool graphics::SetPixelV(POINT point, COLORREF crColor)
   {
      UNREFERENCED_PARAMETER(point);
      UNREFERENCED_PARAMETER(crColor);
      _throw(interface_only_exception(get_app()));
      return false;
   }

   bool graphics::AngleArc(i32 x, i32 y, i32 nRadius, float fStartAngle, float fSweepAngle)
   {
      UNREFERENCED_PARAMETER(x);
      UNREFERENCED_PARAMETER(y);
      UNREFERENCED_PARAMETER(nRadius);
      UNREFERENCED_PARAMETER(fStartAngle);
      UNREFERENCED_PARAMETER(fSweepAngle);
      _throw(interface_only_exception(get_app()));
      return false;
   }

   bool graphics::ArcTo(const RECT &  lpRect, POINT ptStart, POINT ptEnd)
   {
      UNREFERENCED_PARAMETER(lpRect);
      UNREFERENCED_PARAMETER(ptStart);
      UNREFERENCED_PARAMETER(ptEnd);
      _throw(interface_only_exception(get_app()));
      return false;
   }

   i32 graphics::GetArcDirection()
   {
      _throw(interface_only_exception(get_app()));
      return -1;
   }


   bool graphics::PolyPolyline(const POINT* lpPoints, const INT * lpPolyPoints, count nCount)
   {

      UNREFERENCED_PARAMETER(lpPoints);
      UNREFERENCED_PARAMETER(lpPolyPoints);
      UNREFERENCED_PARAMETER(nCount);
      _throw(interface_only_exception(get_app()));

      return false;

   }


#ifdef WINDOWSEX

   bool graphics::GetColorAdjustment(LPCOLORADJUSTMENT lpColorAdjust)
   {
      UNREFERENCED_PARAMETER(lpColorAdjust);
      _throw(interface_only_exception(get_app()));
      return false;
   }

#endif

   ::draw2d::pen_sp graphics::get_current_pen()
   {
      _throw(interface_only_exception(get_app()));
      return NULL;
   }

   ::draw2d::brush_sp graphics::get_current_brush()
   {
      _throw(interface_only_exception(get_app()));
      return NULL;
   }

   ::draw2d::palette_sp graphics::get_current_palette()
   {
      _throw(interface_only_exception(get_app()));
      return NULL;
   }

   ::draw2d::font_sp graphics::get_current_font()
   {
      _throw(interface_only_exception(get_app()));
      return NULL;
   }

   ::draw2d::bitmap_sp graphics::get_current_bitmap()
   {
      _throw(interface_only_exception(get_app()));
      return NULL;
   }

   bool graphics::PolyBezier(const POINT* lpPoints,count nCount)
   {
      UNREFERENCED_PARAMETER(lpPoints);
      UNREFERENCED_PARAMETER(nCount);
      _throw(interface_only_exception(get_app()));
      return false;
   }

   i32 graphics::DrawEscape(i32 nEscape, i32 nInputSize, const char * lpszInputData)
   {
      UNREFERENCED_PARAMETER(nEscape);
      UNREFERENCED_PARAMETER(nInputSize);
      UNREFERENCED_PARAMETER(lpszInputData);
      _throw(interface_only_exception(get_app()));
      return -1;
   }

   i32 graphics::Escape(i32 nEscape, i32 nInputSize, const char * lpszInputData, i32 nOutputSize, char * lpszOutputData)
   {
      UNREFERENCED_PARAMETER(nEscape);
      UNREFERENCED_PARAMETER(nInputSize);
      UNREFERENCED_PARAMETER(lpszInputData);
      UNREFERENCED_PARAMETER(nOutputSize);
      UNREFERENCED_PARAMETER(lpszOutputData);
      _throw(interface_only_exception(get_app()));
      return -1;
   }

#ifdef WINDOWSEX

   bool graphics::GetCharABCWidths(UINT nFirstChar, UINT nLastChar, LPABCFLOAT lpABCF)
   {
      UNREFERENCED_PARAMETER(nFirstChar);
      UNREFERENCED_PARAMETER(nLastChar);
      UNREFERENCED_PARAMETER(lpABCF);
      _throw(interface_only_exception(get_app()));
      return false;
   }

#endif

   bool graphics::GetCharWidth(UINT nFirstChar, UINT nLastChar, float * lpFloatBuffer)
   {
      UNREFERENCED_PARAMETER(nFirstChar);
      UNREFERENCED_PARAMETER(nLastChar);
      UNREFERENCED_PARAMETER(lpFloatBuffer);
      _throw(interface_only_exception(get_app()));
      return false;
   }


   bool graphics::abort_path()
   {

      _throw(interface_only_exception(get_app()));

      return false;

   }


   bool graphics::begin_path()
   {

      _throw(interface_only_exception(get_app()));

      return false;

   }


   bool graphics::close_figure()
   {

      _throw(interface_only_exception(get_app()));

      return false;

   }


   bool graphics::end_path()
   {

      _throw(interface_only_exception(get_app()));

      return false;

   }


   bool graphics::fill_path()
   {

      _throw(interface_only_exception(get_app()));

      return false;

   }


   bool graphics::flatten_path()
   {

      _throw(interface_only_exception(get_app()));

      return false;

   }


   float graphics::GetMiterLimit()
   {

      _throw(interface_only_exception(get_app()));

      return false;

   }


   i32 graphics::GetPath(LPPOINT lpPoints, LPBYTE lpTypes,count nCount)
   {

      UNREFERENCED_PARAMETER(lpPoints);
      UNREFERENCED_PARAMETER(lpTypes);
      UNREFERENCED_PARAMETER(nCount);

      _throw(interface_only_exception(get_app()));

      return false;

   }


   bool graphics::SetMiterLimit(float fMiterLimit)
   {

      UNREFERENCED_PARAMETER(fMiterLimit);

      _throw(interface_only_exception(get_app()));

      return false;

   }


   bool graphics::stroke_and_fill_path()
   {

      _throw(interface_only_exception(get_app()));

      return false;

   }


   bool graphics::stroke_path()
   {

      _throw(interface_only_exception(get_app()));

      return false;

   }


   bool graphics::widen_path()
   {

      _throw(interface_only_exception(get_app()));

      return false;

   }


   bool graphics::draw_path(::draw2d::path * ppath)
   {

      _throw(interface_only_exception(get_app()));

      return false;

   }


   bool graphics::draw_path(::draw2d::path * ppath, ::draw2d::pen * ppen)
   {

      _throw(interface_only_exception(get_app()));

      return false;

   }


   bool graphics::fill_path(::draw2d::path * ppath)
   {

      _throw(interface_only_exception(get_app()));

      return false;

   }


   bool graphics::fill_path(::draw2d::path * ppath, ::draw2d::brush * pbrush)
   {

      _throw(interface_only_exception(get_app()));

      return false;

   }


   bool graphics::path(::draw2d::path * ppath)
   {

      bool bOk1 = fill_path(ppath);

      bool bOk2 = draw_path(ppath);

      return bOk1 && bOk2;

   }


   bool graphics::AddMetaFileComment(UINT nDataSize, const BYTE* pCommentData)
   {
      UNREFERENCED_PARAMETER(nDataSize);
      UNREFERENCED_PARAMETER(pCommentData);
      _throw(interface_only_exception(get_app()));
      return false;
   }

#ifdef WINDOWS

   bool graphics::PlayMetaFile(HENHMETAFILE hEnhMF, const RECT &  lpBounds)
   {
      UNREFERENCED_PARAMETER(hEnhMF);
      UNREFERENCED_PARAMETER(lpBounds);
      _throw(interface_only_exception(get_app()));
      return false;
   }

#endif

   bool graphics::TransparentBlt(i32 xDest, i32 yDest, i32 nDestWidth, i32 nDestHeight,
                                 ::draw2d::graphics * pgraphicsSrc, i32 xSrc, i32 ySrc, i32 nSrcWidth, i32 nSrcHeight, UINT crTransparent)
   {
      UNREFERENCED_PARAMETER(xDest);
      UNREFERENCED_PARAMETER(yDest);
      UNREFERENCED_PARAMETER(nDestWidth);
      UNREFERENCED_PARAMETER(nDestHeight);
      UNREFERENCED_PARAMETER(pgraphicsSrc);
      UNREFERENCED_PARAMETER(xSrc);
      UNREFERENCED_PARAMETER(ySrc);
      UNREFERENCED_PARAMETER(nSrcWidth);
      UNREFERENCED_PARAMETER(nSrcHeight);
      UNREFERENCED_PARAMETER(crTransparent);
      _throw(interface_only_exception(get_app()));
      return false;
   }

   bool graphics::GradientFill(TRIVERTEX* pVertices, WINULONG nVertices, void * pMesh, WINULONG nMeshElements, u32 dwMode)
   {
      UNREFERENCED_PARAMETER(pVertices);
      UNREFERENCED_PARAMETER(nVertices);
      UNREFERENCED_PARAMETER(pMesh);
      UNREFERENCED_PARAMETER(nMeshElements);
      UNREFERENCED_PARAMETER(dwMode);
      _throw(interface_only_exception(get_app()));
      return false;
   }

#ifdef WINDOWS

   COLORREF graphics::GetDCBrushColor()
   {
      _throw(interface_only_exception(get_app()));
      return 0;
   }

   COLORREF graphics::SetDCBrushColor(COLORREF crColor)
   {
      UNREFERENCED_PARAMETER(crColor);
      _throw(interface_only_exception(get_app()));
      return 0;
   }

   COLORREF graphics::GetDCPenColor()
   {
      _throw(interface_only_exception(get_app()));
      return 0;
   }

   COLORREF graphics::SetDCPenColor(COLORREF crColor)
   {
      UNREFERENCED_PARAMETER(crColor);
      _throw(interface_only_exception(get_app()));
      return 0;
   }

#ifndef METROWIN

   bool graphics::GetCharABCWidthsI(UINT giFirst, UINT cgi, LPWORD pgi, LPABC lpabc)
   {
      UNREFERENCED_PARAMETER(giFirst);
      UNREFERENCED_PARAMETER(cgi);
      UNREFERENCED_PARAMETER(pgi);
      UNREFERENCED_PARAMETER(lpabc);
      _throw(interface_only_exception(get_app()));
      return false;
   }

   bool graphics::GetCharWidthI(UINT giFirst, UINT cgi, LPWORD pgi, LPINT lpBuffer)
   {
      UNREFERENCED_PARAMETER(giFirst);
      UNREFERENCED_PARAMETER(cgi);
      UNREFERENCED_PARAMETER(pgi);
      UNREFERENCED_PARAMETER(lpBuffer);
      _throw(interface_only_exception(get_app()));
      return false;
   }

#endif

   bool graphics::GetTextExtentExPointI(LPWORD pgiIn, i32 cgi, i32 nMaxExtent, LPINT lpnFit, LPINT alpDx, LPSIZE lpSize)
   {
      UNREFERENCED_PARAMETER(pgiIn);
      UNREFERENCED_PARAMETER(cgi);
      UNREFERENCED_PARAMETER(nMaxExtent);
      UNREFERENCED_PARAMETER(lpnFit);
      UNREFERENCED_PARAMETER(alpDx);
      UNREFERENCED_PARAMETER(lpSize);
      _throw(interface_only_exception(get_app()));
      return false;
   }

   bool graphics::GetTextExtentPointI(LPWORD pgiIn, i32 cgi, LPSIZE lpSize)
   {
      UNREFERENCED_PARAMETER(pgiIn);
      UNREFERENCED_PARAMETER(cgi);
      UNREFERENCED_PARAMETER(lpSize);
      _throw(interface_only_exception(get_app()));
      return false;
   }

#endif

   void graphics::DPtoHIMETRIC(LPSIZE lpSize)
   {
      UNREFERENCED_PARAMETER(lpSize);
      _throw(interface_only_exception(get_app()));
   }

   void graphics::HIMETRICtoDP(LPSIZE lpSize)
   {
      UNREFERENCED_PARAMETER(lpSize);
      _throw(interface_only_exception(get_app()));
   }

   void graphics::LPtoHIMETRIC(LPSIZE lpSize)
   {
      UNREFERENCED_PARAMETER(lpSize);
      _throw(interface_only_exception(get_app()));
   }

   void graphics::HIMETRICtoLP(LPSIZE lpSize)
   {
      UNREFERENCED_PARAMETER(lpSize);
      _throw(interface_only_exception(get_app()));
   }

   ::draw2d::brush * graphics::GetHalftoneBrush()
   {
      _throw(interface_only_exception(get_app()));
      return NULL;
   }

   // top of windows implementation

   void graphics::DrawDragRect(const RECT &  lpRect, SIZE size, const RECT &  lpRectLast, SIZE sizeLast, ::draw2d::brush* pBrush, ::draw2d::brush* pBrushLast)
   {
      UNREFERENCED_PARAMETER(lpRect);
      UNREFERENCED_PARAMETER(size);
      UNREFERENCED_PARAMETER(lpRectLast);
      UNREFERENCED_PARAMETER(sizeLast);
      UNREFERENCED_PARAMETER(pBrush);
      UNREFERENCED_PARAMETER(pBrushLast);
      _throw(interface_only_exception(get_app()));
   }


   void graphics::fill_solid_rect(LPCRECT lpcrect, COLORREF cr)
   {

      fill_solid_rect(rectd(lpcrect), cr);

   }

   void graphics::fill_solid_rect(LPCRECTD lpcrect, COLORREF cr)
   {

      fill_solid_rect(rect(lpcrect), cr);

   }


   void graphics::draw3d_rect(LPCRECT lpcrect, COLORREF crTopLeft, COLORREF crBottomRight)
   {

      draw3d_rect(rectd(lpcrect), crTopLeft, crBottomRight);

   }


   void graphics::draw3d_rect(LPCRECTD lpcrect, COLORREF crTopLeft, COLORREF crBottomRight)
   {

      draw3d_rect(rect(lpcrect), crTopLeft, crBottomRight);

   }


   void graphics::draw3d_rect(LPCRECT lpcrect, COLORREF cr)
   {

      return draw3d_rect(lpcrect, cr, cr);

   }


   void graphics::draw3d_rect(LPCRECTD lpcrect, COLORREF cr)
   {

      return draw3d_rect(lpcrect, cr, cr);

   }


   void graphics::assert_valid() const
   {

      _throw(interface_only_exception(get_app()));

   }


   void graphics::dump(dump_context & dumpcontext) const
   {

      UNREFERENCED_PARAMETER(dumpcontext);

      _throw(interface_only_exception(get_app()));

   }


   bool graphics::DeleteDC()
   {

      _throw(interface_only_exception(get_app()));

      return false;

   }


   i32 graphics::StartDoc(const char * lpszDocName)
   {

      UNREFERENCED_PARAMETER(lpszDocName);

      _throw(interface_only_exception(get_app()));

      return -1;

   }


   i32 graphics::SaveDC()
   {
      _throw(interface_only_exception(get_app()));
      return -1;
   }

   bool graphics::RestoreDC(i32 nSavedDC)
   {
      UNREFERENCED_PARAMETER(nSavedDC);
      _throw(interface_only_exception(get_app()));
      return false;
   }

   ::draw2d::object* graphics::SelectStockObject(i32 nIndex)
   {
      UNREFERENCED_PARAMETER(nIndex);
      _throw(interface_only_exception(get_app()));
      return NULL;
   }

   ::draw2d::pen* graphics::SelectObject(::draw2d::pen * pPen)
   {
      UNREFERENCED_PARAMETER(pPen);
      _throw(interface_only_exception(get_app()));
      return NULL;
   }

   ::draw2d::brush* graphics::SelectObject(::draw2d::brush * pBrush)
   {
      UNREFERENCED_PARAMETER(pBrush);
      _throw(interface_only_exception(get_app()));
      return NULL;
   }


   ::draw2d::font* graphics::SelectObject(::draw2d::font * pFont)
   {

      set_font(pFont);

      return m_spfont;

   }


   i32 graphics::SelectObject(::draw2d::region * pRgn)
   {
      UNREFERENCED_PARAMETER(pRgn);
      _throw(interface_only_exception(get_app()));
      return -1;
   }

   ::draw2d::palette* graphics::SelectPalette(::draw2d::palette * pPalette, bool bForceBackground)
   {
      UNREFERENCED_PARAMETER(pPalette);
      UNREFERENCED_PARAMETER(bForceBackground);
      _throw(interface_only_exception(get_app()));
      return NULL;
   }


   i32 graphics::SetPolyFillMode(i32 nPolyFillMode)
   {
      UNREFERENCED_PARAMETER(nPolyFillMode);
      _throw(interface_only_exception(get_app()));
      return -1;
   }

   i32 graphics::SetROP2(i32 nDrawMode)
   {
      UNREFERENCED_PARAMETER(nDrawMode);
      _throw(interface_only_exception(get_app()));
      return -1;
   }

   i32 graphics::SetStretchBltMode(i32 nStretchMode)
   {
      UNREFERENCED_PARAMETER(nStretchMode);
      _throw(interface_only_exception(get_app()));
      return -1;
   }


   i32 graphics::SetGraphicsMode(i32 iMode)
   {
      UNREFERENCED_PARAMETER(iMode);
      _throw(interface_only_exception(get_app()));
      return -1;
   }

#ifdef WINDOWS

   bool graphics::SetWorldTransform(const XFORM* pXform)
   {
      UNREFERENCED_PARAMETER(pXform);
      _throw(interface_only_exception(get_app()));
      return false;
   }

   bool graphics::ModifyWorldTransform(const XFORM* pXform, u32 iMode)
   {
      UNREFERENCED_PARAMETER(pXform);
      UNREFERENCED_PARAMETER(iMode);
      _throw(interface_only_exception(get_app()));
      return false;
   }

#endif

   i32 graphics::SetMapMode(i32 nMapMode)
   {
      UNREFERENCED_PARAMETER(nMapMode);
      _throw(interface_only_exception(get_app()));
      return -1;
   }


   point graphics::SetViewportOrg(i32 x, i32 y)
   {

      m_matrixViewport.c1 = x;

      m_matrixViewport.c2 = y;

      update_matrix();

      return ::point(m_matrixViewport.c1, m_matrixViewport.c2);

   }


   void graphics::get_viewport_scale(::draw2d::matrix & matrix)
   {

      matrix = draw2d::matrix();

      matrix.a1 = m_matrixViewport.a1;

      matrix.b2 = m_matrixViewport.b2;

   }


   point graphics::OffsetViewportOrg(i32 nWidth, i32 nHeight)
   {

      m_matrixViewport.c1 += nWidth;

      m_matrixViewport.c2 += nHeight;

      update_matrix();

      return point(m_matrixViewport.c1, m_matrixViewport.c2);

   }


   size graphics::SetViewportExt(i32 x, i32 y)
   {

      UNREFERENCED_PARAMETER(x);

      UNREFERENCED_PARAMETER(y);

      _throw(interface_only_exception(get_app()));

      return size(0, 0);

   }


   size graphics::ScaleViewportExt(i32 xNum, i32 xDenom, i32 yNum, i32 yDenom)
   {

      m_matrixViewport.a1 *= (double)xNum / (double)xDenom;

      m_matrixViewport.b2 *= (double)yNum / (double)yDenom;

      update_matrix();

      return size(0, 0);

   }


   point graphics::SetWindowOrg(i32 x, i32 y)
   {

      UNREFERENCED_PARAMETER(x);

      UNREFERENCED_PARAMETER(y);

      _throw(interface_only_exception(get_app()));

      return null_point();

   }


   point graphics::OffsetWindowOrg(i32 nWidth, i32 nHeight)
   {

      UNREFERENCED_PARAMETER(nWidth);

      UNREFERENCED_PARAMETER(nHeight);

      _throw(interface_only_exception(get_app()));

      return null_point();

   }


   size graphics::SetWindowExt(i32 x, i32 y)
   {
      UNREFERENCED_PARAMETER(x);
      UNREFERENCED_PARAMETER(y);
      _throw(interface_only_exception(get_app()));
      return size(0, 0);
   }

   size graphics::ScaleWindowExt(i32 xNum, i32 xDenom, i32 yNum, i32 yDenom)
   {
      UNREFERENCED_PARAMETER(xNum);
      UNREFERENCED_PARAMETER(xDenom);
      UNREFERENCED_PARAMETER(yNum);
      UNREFERENCED_PARAMETER(yDenom);
      _throw(interface_only_exception(get_app()));
      return size(0, 0);
   }

   i32 graphics::GetClipBox(LPRECT lpRect)
   {
      UNREFERENCED_PARAMETER(lpRect);
      _throw(interface_only_exception(get_app()));
      return -1;
   }

   i32 graphics::GetClipBox(rect64 * lpRect)
   {
      rect rect;
      i32 iClip = GetClipBox(rect);
      rect64 rect64(rect);
      *lpRect = rect64;
      return iClip;
   }

   i32 graphics::SelectClipRgn(::draw2d::region* pRgn)
   {
      UNREFERENCED_PARAMETER(pRgn);
      _throw(interface_only_exception(get_app()));
      return -1;
   }

   i32 graphics::ExcludeClipRect(i32 x1, i32 y1, i32 x2, i32 y2)
   {
      UNREFERENCED_PARAMETER(x1);
      UNREFERENCED_PARAMETER(y1);
      UNREFERENCED_PARAMETER(x2);
      UNREFERENCED_PARAMETER(y2);
      _throw(interface_only_exception(get_app()));
      return -1;
   }

   i32 graphics::ExcludeClipRect(const RECT &  lpRect)
   {
      UNREFERENCED_PARAMETER(lpRect);
      _throw(interface_only_exception(get_app()));
      return -1;
   }


   i32 graphics::IntersectClipRect(i32 x1, i32 y1, i32 x2, i32 y2)
   {

      RECT r;

      r.left = x1;
      r.top = y1;
      r.right = x2;
      r.bottom = y2;

      return IntersectClipRect(r);

   }


   i32 graphics::IntersectClipRect(const RECT &  r)
   {

      return IntersectClipRect(r.left, r.top, r.right, r.bottom);

   }


   i32 graphics::OffsetClipRgn(i32 x, i32 y)
   {
      UNREFERENCED_PARAMETER(x);
      UNREFERENCED_PARAMETER(y);
      _throw(interface_only_exception(get_app()));
      return -1;
   }

   i32 graphics::OffsetClipRgn(SIZE size)
   {
      UNREFERENCED_PARAMETER(size);
      _throw(interface_only_exception(get_app()));
      return -1;
   }


   UINT graphics::SetTextAlign(UINT nFlags)
   {
      UNREFERENCED_PARAMETER(nFlags);
      _throw(interface_only_exception(get_app()));
      return -1;
   }

   i32 graphics::SetTextJustification(i32 nBreakExtra, i32 nBreakCount)
   {
      UNREFERENCED_PARAMETER(nBreakExtra);
      UNREFERENCED_PARAMETER(nBreakCount);
      _throw(interface_only_exception(get_app()));
      return -1;
   }

   i32 graphics::SetTextCharacterExtra(i32 nCharExtra)
   {
      UNREFERENCED_PARAMETER(nCharExtra);
      _throw(interface_only_exception(get_app()));
      return -1;
   }

   u32 graphics::SetMapperFlags(u32 dwFlag)
   {
      UNREFERENCED_PARAMETER(dwFlag);
      _throw(interface_only_exception(get_app()));
      return -1;
   }

   u32 graphics::GetLayout()
   {
      _throw(interface_only_exception(get_app()));
      return -1;
   }

   u32 graphics::SetLayout(u32 dwSetLayout)
   {
      UNREFERENCED_PARAMETER(dwSetLayout);
      _throw(interface_only_exception(get_app()));
      return -1;
   }

   /////////////////////////////////////////////////////////////////////////////
   // Advanced Win32 GDI functions

   bool graphics::ArcTo(i32 x1, i32 y1, i32 x2, i32 y2, i32 x3, i32 y3, i32 x4, i32 y4)
   {
      UNREFERENCED_PARAMETER(x1);
      UNREFERENCED_PARAMETER(y1);
      UNREFERENCED_PARAMETER(x2);
      UNREFERENCED_PARAMETER(y2);
      UNREFERENCED_PARAMETER(x3);
      UNREFERENCED_PARAMETER(y3);
      UNREFERENCED_PARAMETER(x4);
      UNREFERENCED_PARAMETER(y4);
      _throw(interface_only_exception(get_app()));
      return false;
   }

   i32 graphics::SetArcDirection(i32 nArcDirection)
   {
      UNREFERENCED_PARAMETER(nArcDirection);
      _throw(interface_only_exception(get_app()));
      return -1;
   }

   bool graphics::PolyDraw(const POINT* lpPoints, const BYTE* lpTypes,count nCount)
   {
      UNREFERENCED_PARAMETER(lpPoints);
      UNREFERENCED_PARAMETER(lpTypes);
      UNREFERENCED_PARAMETER(nCount);
      _throw(interface_only_exception(get_app()));
      return false;
   }

   bool graphics::PolylineTo(const POINT* lpPoints,count nCount)
   {
      UNREFERENCED_PARAMETER(lpPoints);
      UNREFERENCED_PARAMETER(nCount);
      _throw(interface_only_exception(get_app()));
      return false;
   }


#ifdef WINDOWSEX


   bool graphics::SetColorAdjustment(const COLORADJUSTMENT* lpColorAdjust)
   {

      UNREFERENCED_PARAMETER(lpColorAdjust);
      _throw(interface_only_exception(get_app()));
      return false;

   }


#endif


   bool graphics::PolyBezierTo(const POINT* lpPoints,count nCount)
   {
      UNREFERENCED_PARAMETER(lpPoints);
      UNREFERENCED_PARAMETER(nCount);
      _throw(interface_only_exception(get_app()));
      return false;
   }

   bool graphics::SelectClipPath(i32 nMode)
   {
      UNREFERENCED_PARAMETER(nMode);
      _throw(interface_only_exception(get_app()));
      return false;
   }

   i32 graphics::SelectClipRgn(::draw2d::region* pRgn, i32 nMode)
   {
      UNREFERENCED_PARAMETER(pRgn);
      UNREFERENCED_PARAMETER(nMode);
      _throw(interface_only_exception(get_app()));
      return -1;
   }

#ifdef WINDOWS

   bool graphics::PlayMetaFile(HMETAFILE hMF)
   {
      UNREFERENCED_PARAMETER(hMF);
      _throw(interface_only_exception(get_app()));
      return false;
   }

#endif

   /////////////////////////////////////////////////////////////////////////////
   // Coordinate transforms

   void graphics::LPtoDP(LPSIZE lpSize)
   {
      UNREFERENCED_PARAMETER(lpSize);
      _throw(interface_only_exception(get_app()));
   }


   void graphics::DPtoLP(LPSIZE lpSize)
   {

      UNREFERENCED_PARAMETER(lpSize);

      _throw(interface_only_exception(get_app()));

   }


   ::count graphics::GetEachCharTextExtent(array < sized > & sizea, const string & str, strsize iStart, strsize iCount)
   {

      sizea.remove_all();

      if (str.length() <= 0)
      {

         return 0;

      }

      if (iCount == 0)
      {

         return 0;

      }

      if (iStart < 0)
      {

         iStart = 0;

      }

      if (iStart > str.get_length())
      {

         return 0;

      }

      if (iCount < 0)
      {

         iCount = str.get_length() - iStart;

      }

      if (iStart + iCount > str.get_length())
      {

         iCount = str.get_length() - iStart;

         if (iCount <= 0)
         {

            return 0;

         }

      }

      iCount++;

      strsize iRange = 0;

      strsize iAsciiCharCount = 0;

      strsize iLen;

      const char * pszStart = str;

      const char * psz = pszStart;

      while (*psz && iRange < iStart + iCount)
      {

         const char * pszNext = ::str::utf8_inc(psz);

         if (pszNext == NULL)
         {

            break;

         }

         iLen = pszNext - psz;

         iAsciiCharCount += iLen;

         if (iRange >= iStart)
         {

            sizea.add(GetTextExtent(str, str.get_length(), iAsciiCharCount));

         }

         iRange++;

         if (*pszNext == '\0')
         {

            break;

         }

         psz = pszNext;

      }

      return sizea.get_size();

   }

   sized graphics::GetTextBegin(const char * lpszString, strsize nCount, count iIndex)
   {

      return GetTextExtent(lpszString, nCount, iIndex);

   }


   sized graphics::GetTextExtent(const char * lpszString, strsize nCount,count iIndex)
   {

      return GetTextExtent(lpszString, iIndex);

   }

   sized graphics::GetTextExtent(const char * lpszString, strsize nCount)
   {
      UNREFERENCED_PARAMETER(lpszString);
      UNREFERENCED_PARAMETER(nCount);
      _throw(interface_only_exception(get_app()));
      return sized(0, 0);
   }

   sized graphics::GetTextExtent(const string & str)
   {
      UNREFERENCED_PARAMETER(str);
      _throw(interface_only_exception(get_app()));
      return sized(0, 0);
   }

   bool graphics::GetTextExtent(sized & size, const char * lpszString, strsize nCount, strsize iIndex)
   {

      ::sized sz = GetTextExtent(string(lpszString), nCount, iIndex);

      size.cx = sz.cx;
      size.cy = sz.cy;

      return true;

   }

   bool graphics::GetTextExtent(sized & size, const char * lpszString, strsize nCount)
   {

      ::sized sz = GetTextExtent(string(lpszString), nCount);

      size.cx = sz.cx;
      size.cy = sz.cy;

      return true;

   }

   bool graphics::GetTextExtent(sized & size, const string & str)
   {

      ::sized sz = GetTextExtent(str);

      size.cx = sz.cx;
      size.cy = sz.cy;

      return true;

   }

   size graphics::GetOutputTextExtent(const char * lpszString, strsize nCount)
   {
      UNREFERENCED_PARAMETER(lpszString);
      UNREFERENCED_PARAMETER(nCount);
      _throw(interface_only_exception(get_app()));
      return size(0, 0);
   }

   size graphics::GetOutputTextExtent(const string & str)
   {
      UNREFERENCED_PARAMETER(str);
      _throw(interface_only_exception(get_app()));
      return size(0, 0);
   }


   bool graphics::draw_text(const char * lpszString,strsize nCount,const RECT & lpRect,UINT nFormat)
   {

      return draw_text(string(lpszString, nCount), lpRect, nFormat);

   }


   bool graphics::draw_text(const string & str,const RECT & lpRect,UINT nFormat)
   {

      RECTD r;

      ::copy(&r, &lpRect);

      return draw_text(str, r, nFormat);

   }


   bool graphics::draw_text(const char * lpszString,strsize nCount,const RECTD & lpRect,UINT nFormat)
   {

      return draw_text(string(lpszString,nCount),lpRect,nFormat);

   }


   bool graphics::draw_text(const string & strParam,const RECTD & lpRect,UINT nFormat)
   {

      string str(strParam);

      synch_lock ml(m_pmutex);

      size sz = GetTextExtent(str);

      double dx;

      double dy;

      if(nFormat & DT_RIGHT)
      {

         dx = lpRect.right - lpRect.left - sz.cx;

      }
      else if(nFormat & DT_CENTER)
      {

         dx = ((lpRect.right - lpRect.left) - (sz.cx)) / 2.0;

      }
      else
      {

         dx = 0.;

      }

      if(nFormat & DT_BOTTOM)
      {

         dy = lpRect.bottom - lpRect.top - sz.cy;

      }
      else if(nFormat & DT_VCENTER)
      {

         dy = ((lpRect.bottom - lpRect.top) - (sz.cy)) / 2.0;

      }
      else
      {

         dy = 0.;

      }

      if(nFormat & DT_EXPANDTABS)
      {

         str.replace("\t", "        ");

      }
      else
      {

         str.replace("\t", "");

      }

      if(nFormat & DT_SINGLELINE)
      {

         str.replace("\r", "");

         str.replace("\n", "");

         text_out(lpRect.left + dx,lpRect.top + dy,str);

      }
      else
      {

         size s = GetTextExtent(str);

         stringa stra;

         stra.add_lines(str);

         int offsety = 0;

         for(auto str : stra)
         {

            size s1 = GetTextExtent(str);

            text_out(lpRect.left + dx,lpRect.top + dy + offsety,str);

            offsety += s1.cy;

         }


      }

      return 1;

   }


#ifndef METROWIN


   bool graphics::draw_text_ex(const char * lpszString,strsize nCount,const RECT & lpRect,UINT nFormat,LPDRAWTEXTPARAMS lpDTParams)
   {
      UNREFERENCED_PARAMETER(lpszString);
      UNREFERENCED_PARAMETER(nCount);
      UNREFERENCED_PARAMETER(lpRect);
      UNREFERENCED_PARAMETER(nFormat);
      UNREFERENCED_PARAMETER(lpDTParams);
      _throw(interface_only_exception(get_app()));
      return false;
   }


   bool graphics::draw_text_ex(const string & str,const RECT & lpRect,UINT nFormat,LPDRAWTEXTPARAMS lpDTParams)
   {
      UNREFERENCED_PARAMETER(str);
      UNREFERENCED_PARAMETER(lpRect);
      UNREFERENCED_PARAMETER(nFormat);
      UNREFERENCED_PARAMETER(lpDTParams);
      _throw(interface_only_exception(get_app()));
      return false;
   }


   bool graphics::draw_text_ex(const char * lpszString,strsize nCount,const RECTD & lpRect,UINT nFormat,LPDRAWTEXTPARAMS lpDTParams)
   {
      UNREFERENCED_PARAMETER(lpszString);
      UNREFERENCED_PARAMETER(nCount);
      UNREFERENCED_PARAMETER(lpRect);
      UNREFERENCED_PARAMETER(nFormat);
      UNREFERENCED_PARAMETER(lpDTParams);
      _throw(interface_only_exception(get_app()));
      return false;
   }

   bool graphics::draw_text_ex(const string & str,const RECTD & lpRect,UINT nFormat,LPDRAWTEXTPARAMS lpDTParams)
   {
      UNREFERENCED_PARAMETER(str);
      UNREFERENCED_PARAMETER(lpRect);
      UNREFERENCED_PARAMETER(nFormat);
      UNREFERENCED_PARAMETER(lpDTParams);
      _throw(interface_only_exception(get_app()));
      return false;
   }

#endif


   bool graphics::from(point ptDst, size size, ::draw2d::graphics * pgraphicsSrc, point ptSrc, u32 dwRop)
   {

      return BitBlt(ptDst.x, ptDst.y, size.cx, size.cy, pgraphicsSrc, ptSrc.x, ptSrc.y, dwRop) != FALSE;

   }


   bool graphics::from(size size, ::draw2d::graphics * pgraphicsSrc, point ptSrc, u32 dwRop)
   {

      return from(null_point(), size, pgraphicsSrc, ptSrc, dwRop);

   }


   bool graphics::from(size size, ::draw2d::graphics * pgraphicsSrc, u32 dwRop)
   {

      return from(size, pgraphicsSrc, null_point(), dwRop);

   }


   bool graphics::alpha_blend(point ptDst, size szDst,::draw2d::graphics * pgraphicsSrc, point ptSrc, size szSrc, double dOpacity)
   {

      return alpha_blend(ptDst.x, ptDst.y, szDst.cx, szDst.cy, pgraphicsSrc, ptSrc.x, ptSrc.y, szSrc.cx, szSrc.cy, dOpacity);

   }


   bool graphics::alpha_blend(point ptDst, size size,::draw2d::graphics * pgraphicsSrc, point ptSrc, double dOpacity)
   {

      return alpha_blend(ptDst, size, pgraphicsSrc, ptSrc, size, dOpacity);

   }


   bool graphics::alpha_blend(point ptDst, size size,::draw2d::graphics * pgraphicsSrc, double dOpacity)
   {

      return alpha_blend(ptDst, size, pgraphicsSrc, null_point(), dOpacity);

   }


   bool graphics::alpha_blend(rect & r, ::draw2d::graphics * pgraphicsSrc, double dOpacity)
   {

      return alpha_blend(r.top_left(), r.get_size(), pgraphicsSrc, dOpacity);

   }


   bool graphics::alpha_blend(size size,::draw2d::graphics * pgraphicsSrc, point ptSrc, double dOpacity)
   {

      return alpha_blend(null_point(), size, pgraphicsSrc, ptSrc, dOpacity);

   }


   bool graphics::alpha_blend(size size,::draw2d::graphics * pgraphicsSrc, double dOpacity)
   {

      return alpha_blend(size, pgraphicsSrc, null_point(), dOpacity);

   }


   bool graphics::alpha_blend(i32 xDst, i32 yDst, i32 nDstWidth, i32 nDstHeight, ::draw2d::graphics * pgraphicsSrc, i32 xSrc, i32 ySrc, i32 nSrcWidth, i32 nSrcHeight, double dOpacity)
   {

      if (dOpacity == 1.0)
      {

         if (nSrcHeight == nDstHeight && nSrcWidth == nDstWidth)
         {

            return BitBlt(xDst, yDst, nDstWidth, nDstHeight, pgraphicsSrc, xSrc, ySrc, SRCCOPY);

         }
         else
         {

            return StretchBlt(xDst, yDst, nDstWidth, nDstHeight, pgraphicsSrc, xSrc, ySrc, nSrcWidth, nSrcHeight, SRCCOPY);

         }

      }

      if (alpha_blendAlphaBlend(xDst, yDst, nDstWidth, nDstHeight, pgraphicsSrc, xSrc, ySrc, nSrcWidth, nSrcHeight, dOpacity))
      {

         return true;

      }

      if (alpha_blendRaw(xDst, yDst, nDstWidth, nDstHeight, pgraphicsSrc, xSrc, ySrc, nSrcWidth, nSrcHeight, dOpacity))
      {

         return true;

      }

      return false;

   }




   bool graphics::alpha_blendRaw(i32 xDest, i32 yDest, i32 nDestWidth, i32 nDestHeight, ::draw2d::graphics * pgraphicsSrc, i32 xSrc, i32 ySrc, i32 nSrcWidth, i32 nSrcHeight, double dRate)
   {

      return false;

   }


   bool graphics::alpha_blendAlphaBlend(i32 xDest, i32 yDest, i32 nDestWidth, i32 nDestHeight, ::draw2d::graphics * pgraphicsSrc, i32 xSrc, i32 ySrc, i32 nSrcWidth, i32 nSrcHeight, double dRate)
   {

      if (m_pdibAlphaBlend != NULL)
      {


         rect rectIntersect(m_ptAlphaBlend, m_pdibAlphaBlend->size());


         rect rectBlt(point((int64_t)xDest, (int64_t)yDest), size(nDestWidth, nDestHeight));

         if (rectIntersect.intersect(rectIntersect, rectBlt))
         {

            ::draw2d::dib * pdibWork = NULL;
            ::draw2d::dib * pdibWork2 = NULL;
            //         ::draw2d::dib * pdibWork3 = NULL;
            ::draw2d::dib * pdibWork4 = NULL;


            class point ptSrc(xSrc, ySrc);
            class point ptDest(xDest, yDest);
            class size size(nDestWidth, nDestHeight);



            ::draw2d::dib_sp spdib;
            if (pdibWork == NULL)
            {
               spdib.alloc(allocer());
               pdibWork = spdib;
            }
            if (pdibWork == NULL)
               return false;
            if (!pdibWork->create(size))
               return false;
            if (!pdibWork->from(null_point(), pgraphicsSrc, ptSrc, size))
               return false;




            ::draw2d::dib_sp spdib2;
            if (pdibWork2 == NULL)
            {
               spdib2.alloc(allocer());
               pdibWork2 = spdib2;
            }


            ::draw2d::dib_sp spdib4;
            if (pdibWork4 == NULL)
            {
               spdib4.alloc(allocer());
               pdibWork4 = spdib4;
            }
            if (pdibWork4 == NULL)
               return false;
            if (!pdibWork4->create(size))
               return false;


            pdibWork4->Fill(255, 0, 0, 0);

            pdibWork4->from(point(MAX(0, m_ptAlphaBlend.x - xDest), MAX(0, m_ptAlphaBlend.y - yDest)),
                            m_pdibAlphaBlend->get_graphics(), point(MAX(0, xDest - m_ptAlphaBlend.x), MAX(0, yDest - m_ptAlphaBlend.y)), size);

            pdibWork->channel_multiply(visual::rgba::channel_alpha, pdibWork4);


            BitBltRaw(ptDest.x, ptDest.y, size.cx, size.cy, pdibWork->get_graphics(), ptSrc.x, ptSrc.y, SRCCOPY);

            return true;

         }

      }

      return false;

   }


   bool graphics::set_alpha_mode(e_alpha_mode ealphamode)
   {

      m_ealphamode = ealphamode;

      return true;

   }


   bool graphics::set_smooth_mode(e_smooth_mode esmoothmode)
   {

      m_esmoothmode = esmoothmode;

      return true;

   }


   bool graphics::set_text_rendering_hint_hint(e_text_rendering_hint_hint etextrendering)
   {

      m_etextrenderinghint = etextrendering;

      return true;

   }


   bool graphics::blur(bool bExpand, double dRadius, const RECT & rect)
   {
      _throw(interface_only_exception(get_app()));
      return false;
   }


   bool graphics::set_solid_pen(double dWidth, COLORREF cr)
   {

      if(m_sppen.is_null())
      {

         m_sppen.alloc(allocer());

      }

      m_sppen->create_solid(dWidth, cr);

      return true;

   }


   memory_graphics::memory_graphics()
   {

   }

   memory_graphics::memory_graphics(const ::aura::allocatorsp & allocer) :
      ::draw2d::graphics_sp(allocer)
   {
      ::draw2d::graphics_sp::m_p->CreateCompatibleDC(NULL);
   }

   void memory_graphics::alloc(const ::aura::allocatorsp & allocer)
   {

      if (is_null())
      {

         ::draw2d::graphics_sp::alloc(allocer);

         ::draw2d::graphics_sp::m_p->CreateCompatibleDC(NULL);

      }

   }


   memory_graphics::~memory_graphics()
   {

   }


   double graphics::get_dpix()
   {

      return 96.0;

   }


   double graphics::get_dpiy()
   {

      return 96.0;

   }


   bool graphics::flush()
   {

      return true;

   }


   bool graphics::sync_flush()
   {

      return flush();

   }



   //=============================================================================
   //
   // draw_round_rect()
   //
   // Purpose:     Draws a rounded rectangle with a solid pen
   //
   // Parameters:  pGraphics  - [in]   pointer to the Graphics device
   //          r        - [in]   Rect that defines the round rectangle boundaries
   //          color    - [in]   Color value for the brush
   //          radius      - [in]  radius of the rounded corner
   //          width    - [in]  width of the border
   //
   // Returns:     None
   //
   bool graphics::draw_round_rect(const RECT & rect, ::draw2d::pen * ppen, i32 radius)
   {

      ::draw2d::path_sp path(allocer());

      path->begin_figure(true, ::draw2d::fill_mode_winding);

      path->add_round_rect(rect, 2 * radius);

      path->end_figure(true);

      draw_path(path, ppen);

      return true;

   }


   //=============================================================================
   //
   // draw_round_rect()
   //
   // Purpose:     Draws a rounded rectangle with a solid pen
   //
   // Parameters:  pGraphics  - [in]   pointer to the Graphics device
   //          r        - [in]   Rect that defines the round rectangle boundaries
   //          color    - [in]   Color value for the brush
   //          radius      - [in]  radius of the rounded corner
   //          width    - [in]  width of the border
   //
   // Returns:     None
   //
   bool graphics::draw_round_rect(const RECT & rect, COLORREF cr, i32 radius, i32 width)
   {

      RECT r = rect;

      i32 dia = 2 * radius;

      ::draw2d::pen_sp pen(allocer(), 1.0, cr);

      draw_round_rect(r, pen, radius);


      for (i32 i = 1; i<width; i++)
      {
         dia++;

         // left stroke
         deflate_rect(r, 1, 0);

         draw_round_rect(r, pen, dia / 2);

         // up stroke
         deflate_rect(r, 0, 1);

         draw_round_rect(r, pen, dia / 2);

      }

      return true;

   }


   bool graphics::draw_round_top_left(const RECT & rect, ::draw2d::pen  * ppen, i32 radius)
   {

      ::draw2d::path_sp path(allocer());

      path->begin_figure(false, ::draw2d::fill_mode_winding);

      path->add_round_top_left(rect, 2 * radius);

      path->end_figure(false);

      draw_path(path, ppen);

      return true;

   }


   bool graphics::draw_round_top_left(const RECT & rect, COLORREF cr, i32 radius, i32 width)
   {

      RECT r = rect;

      i32 dia = 2 * radius;

      ::draw2d::pen_sp pen(allocer(), 1.0, cr);

      draw_round_top_left(r, pen, radius);


      for (i32 i = 1; i<width; i++)
      {
         dia++;

         // left stroke
         deflate_rect(r, 1, 0);

         draw_round_top_left(r, pen, dia / 2);

         // up stroke
         deflate_rect(r, 0, 1);

         draw_round_top_left(r, pen, dia / 2);

      }

      return true;

   }


   bool graphics::draw_round_bottom_right(const RECT & rect, ::draw2d::pen  * ppen, i32 radius)
   {

      ::draw2d::path_sp path(allocer());

      path->begin_figure(false, ::draw2d::fill_mode_winding);

      path->add_round_bottom_right(rect, 2 * radius);

      path->end_figure(false);

      draw_path(path, ppen);

      return true;

   }


   bool graphics::draw_round_bottom_right(const RECT & rect, COLORREF cr, i32 radius, i32 width)
   {

      RECT r = rect;

      i32 dia = 2 * radius;

      ::draw2d::pen_sp pen(allocer(), 1.0, cr);

      draw_round_bottom_right(r, pen, radius);

      for (i32 i = 1; i<width; i++)
      {

         dia++;

         // left stroke
         deflate_rect(r, 1, 0);

         draw_round_bottom_right(r, pen, dia / 2);

         // up stroke
         deflate_rect(r, 0, 1);

         draw_round_bottom_right(r, pen, dia / 2);

      }

      return true;

   }

   //=============================================================================
   //
   // fill_round_rect()
   //
   // Purpose:     Fills a rounded rectangle with a solid brush.  Draws the border
   //          first then fills in the rectangle.
   //
   // Parameters:  pGraphics  - [in]   pointer to the Graphics device
   //          r        - [in]   Rect that defines the round rectangle boundaries
   //          color    - [in]   Color value for the brush
   //          radius      - [in]  radius of the rounded corner
   //
   // Returns:     None
   //
   bool graphics::fill_round_rect(const RECT & r, COLORREF cr, i32 radius)
   {

      ::draw2d::brush_sp br(allocer(), cr);

      return fill_round_rect(r, br, radius);

   }

   //=============================================================================
   //
   // fill_round_rect()
   //
   // Purpose:     Fills a rounded rectangle with a solid brush.  Draws the border
   //          first then fills in the rectangle.
   //
   // Parameters:  pGraphics  - [in]   pointer to the Graphics device
   //          pBrush      - [in]  pointer to a Brush
   //          r        - [in]   Rect that defines the round rectangle boundaries
   //          color    - [in]   Color value for the border (needed in case the
   //                         brush is a type other than solid)
   //          radius      - [in]  radius of the rounded corner
   //
   // Returns:     None
   //
   bool graphics::fill_round_rect(const RECT & rect, ::draw2d::brush * pbr, i32 radius)
   {

      ::draw2d::path_sp path(allocer());

      path->begin_figure(true, ::draw2d::fill_mode_winding);

      path->add_round_rect(rect, 2 * radius);

      path->end_figure(true);

      fill_path(path, pbr);

      return true;

   }

   bool graphics::round_rect(const RECT & r, i32 radius)
   {

      bool bOk1 = fill_round_rect(r, m_spbrush, radius);

      bool bOk2 = draw_round_rect(r, m_sppen, radius);

      return bOk1 && bOk2;

   }

   i32 graphics::_DrawText(const string & str, const RECT & rect, UINT uiFormat, ::draw2d::font * pfontUnderline)
   {
      return _DrawText(str, str.get_length(), rect, uiFormat, pfontUnderline);
   }

   i32 graphics::_DrawText(const char * lpcsz, strsize iCount, const RECT & rectParam, UINT uiFormat, ::draw2d::font * pfontUnderline)
   {

      string strParam(lpcsz, iCount);

      strParam = ::str::q_valid(strParam);

      if (strParam.is_empty())
      {

         return -1;

      }

      text_metric tm2;

      get_text_metrics(&tm2);

      int iLineSpacing = tm2.tmHeight;

      ::draw2d::graphics * pgraphics = this;



      wstring wstr = ::str::international::utf8_to_unicode(strParam);

      string str(strParam);

      string str2;

      rect rectClip(rectParam);

      if (rectClip.area() <= 0)
         return 0;

      sized sz;

      sz.cx = 0;

      sz.cy = 0;


      strsize iUnderline = -1;

      if(!(uiFormat & DT_NOPREFIX))
      {
         iUnderline = _EncodeV033(str);
      }

      strsize iLen = str.get_length();

      bool bLastLine = false;

      if((uiFormat & DT_WORDBREAK) != 0)
      {

         bLastLine = !word_break(pgraphics, lpcsz, rectClip, str, str2, (uiFormat & DT_END_ELLIPSIS));

         sz = pgraphics->GetTextExtent(str);


      }
      else if ((uiFormat & DT_END_ELLIPSIS) != 0)
      {

         sz = pgraphics->GetTextExtent(str, (i32)iLen);

         if (sz.cx > rectClip.width())
         {

            const char * pszStart = str;

            const char * psz = pszStart;

            string strLastSample = "...";

            string strSample;

            while (true)
            {

               psz = ::str::utf8_inc(psz);

               strSample = string(pszStart, psz - pszStart) + "...";

               sz = pgraphics->GetTextExtent(strSample);

               if (sz.cx > rectClip.width())
               {

                  str = strLastSample;

                  break;

               }

               strLastSample = strSample;

            }

         }
      }
      else
      {
         sz = pgraphics->GetTextExtent(str);
         /*::GetTextExtentPoint32U(
         (HDC) pgraphics->get_os_data(),
         str,
         iLen,
         &sz);*/
         //         u32 dw = ::get_last_error();
         if (sz.cx > rectClip.width())
         {
            strsize i = iLen;
            if (i < 0)
               i = 0;
            char * lpsz = str.GetBuffer(MAX(0, i));
            while (i > 0)
            {
               sz = pgraphics->GetTextExtent(str, (i32)i);
               if ((int) sz.cx > rectClip.width())
               {
                  i = ::str::utf8_dec(str, &((const char *)str)[i]) - ((const char *)str);
                  if (i <= 0)
                     break;
               }
               else
               {
                  break;
               }
            }
            lpsz[i] = L'\0';
            str.ReleaseBuffer();
         }
      }

      if (str.is_empty())
         return 0;


      ::draw2d::font_sp fontUnderline;
      //      ::draw2d::font * pfont;


      if (iUnderline >= 0)
      {
         if (pfontUnderline == NULL)
         {
            fontUnderline.alloc(allocer());
            pfontUnderline = fontUnderline;
            fontUnderline ->operator=(*pgraphics->get_current_font());
            fontUnderline->set_bold();
         }
      }

      rect rect;
      rect.left = 0;
      rect.top = 0;
      rect.right = (LONG) sz.cx;
      rect.bottom = iLineSpacing;

      i32 align = 0;
      if (uiFormat & DT_BOTTOM)
      {
         align |= ::align_bottom;
      }
      else if (uiFormat & DT_VCENTER)
      {
         align |= ::align_vertical_center;
      }
      else
      {
         align |= ::align_top;
      }
      if (uiFormat & DT_RIGHT)
      {
         align |= ::align_right;
      }
      else if (uiFormat & DT_CENTER)
      {
         align |= ::align_horizontal_center;
      }
      else
      {
         align |= ::align_left;
      }

      rect.Align(align, rectParam);

      if (iUnderline >= 0 && iUnderline < str.get_length())
      {

         ::draw2d::font * pfontOld;

         pgraphics->text_out(rect.left, rect.top, str, (i32)MIN(iUnderline, str.get_length()));
         /*::TextOutU(
         (HDC)pgraphics->get_os_data(),
         rect.left,
         rect.top,
         str,
         MIN(iUnderline, str.get_length()));*/
         if (iUnderline <= str.get_length())
         {
            ::draw2d::font fPrevious = *pgraphics->get_current_font();
            pfontOld = pgraphics->SelectObject(pfontUnderline);
            /*::GetTextExtentPoint32U(
            (HDC)pgraphics->get_os_data(),
            str,
            iUnderline,
            &sz);*/
            sz = pgraphics->GetTextExtent(str, (i32)iUnderline);
            char wch = str[iUnderline];
            /*::TextOutU(
            (HDC)pgraphics->get_os_data(),
            rect.left + sz.cx,
            rect.top,
            &wch,
            1);*/
            pgraphics->text_out(rect.left + sz.cx, (double) rect.top, &wch, 1);
            pgraphics->SelectObject(&fPrevious);
            if (iUnderline + 1 <= str.get_length())
            {
               sz = pgraphics->GetTextExtent(str, (i32)(iUnderline + 1));
               /*::GetTextExtentPoint32U(
               (HDC)pgraphics->get_os_data(),
               str,
               iUnderline + 1,
               &sz);*/
               strsize iCount = str.get_length() - iUnderline - 1;
               pgraphics->text_out(rect.left + sz.cx, (double)rect.top, str.Right(iCount), (i32)iCount);
               /*::TextOutU(
               (HDC)pgraphics->get_os_data(),
               rect.left + sz.cx,
               rect.top,
               str.Right(iCount),
               iCount);*/
            }

            pgraphics->SelectObject(pfontOld);

         }

      }
      else
      {

         pgraphics->text_out(rect.left, rect.top, str);

      }

      if (!bLastLine && str2.get_length() > 0)
      {

         rectClip.top += iLineSpacing;

         _DrawText(str2, str2.get_length(), rectClip, uiFormat);

      }

      return 1;

   }



   bool word_break(::draw2d::graphics * pgraphics, const string & strSource, RECT & rectParam, string &str1, string & str2, int iEll)
   {

      string str;

      rect rectClip(rectParam);

      const char * lpszSource = strSource;

      strsize len = strSource.get_length();

      const char * lpszEnd = lpszSource + len;

//      index iFind = str.find(L' ');

      const char * lpszStart = ::str::utf8_inc(lpszSource);

      size sz;

      const char * lpszSpaceStart = NULL;
      const char * lpszSpaceEnd = NULL;

      const char * lpsz = lpszStart;

      const char * lpszPrevious = lpszSource;

      string strChar;

      int iNewY;

      bool bLastLine = false;

      bool bEnd = false;

      int y = rectParam.top;

      while(lpsz <= lpszEnd)
      {

         sz = pgraphics->GetTextExtent(lpszSource, lpsz - lpszSource);

         iNewY = y + sz.cy;

         if(iNewY + sz.cy > rectParam.bottom)
         {

            bLastLine = true;


            str = strSource;

            strsize iLen = str.length();

            sz = pgraphics->GetTextExtent(str,(i32)iLen);


            if(sz.cx > rectClip.width())
            {

               strsize iSampleLen = strSource.get_length();

               while(iSampleLen > 0)
               {

                  iSampleLen--;

                  str = strSource.Left(iSampleLen) + "...";

                  sz = pgraphics->GetTextExtent(str);

                  if(sz.cx < rectClip.width())
                  {

                     break;

                  }

               }

            }

            str1 = str;

            rectParam.top = y;

            return false;


         }

         if(::str::ch::is_space_char(lpszPrevious))
         {
            lpszSpaceStart       = lpszPrevious;
            do
            {
               lpszSpaceEnd      = lpsz;
               if(!::str::ch::is_space_char(lpsz))
               {
                  break;
               }
               lpszPrevious      = lpsz;
               lpsz              = ::str::utf8_inc(lpsz);
            }
            while(lpsz != NULL);
         }

         if (sz.cx > rectClip.width())
         {

            if(lpsz == lpszStart)
            {
               lpszEnd = lpszStart;
               break;
            }

            if(lpszSpaceStart != NULL)
            {
               // "legit" word break, i.meaning., found mid space in text and split there, instead of slicing a full word in a single-character (above) or the maximum-unclipped (below).
               lpsz = lpszSpaceStart;
               lpszEnd = lpszSpaceEnd;
               break;
            }

            lpsz = ::str::utf8_dec(lpszSource, lpsz);
            lpszEnd = lpsz;

            break;

         }

         lpszPrevious = lpsz;
         lpsz = ::str::utf8_inc(lpsz);

         if(bEnd)
            break;
         else
            bEnd = lpsz >= lpszEnd;

      }

      str1 = string(lpszSource, lpsz - lpszSource);

      str2 = string(lpszEnd);

      rectParam.top = y;

      return true;

   }


   strsize _EncodeV033(string & str)
   {
      strsize iStart = 0;
      strsize iIndex;
      strsize iLen = str.get_length();
      while (true)
      {
         iIndex = str.find(L'&', iStart);
         if (iIndex < 0)
            break;
         if (iIndex + 1 >= iLen)
            break;
         if (str[iIndex + 1] == L'&')
         {
            iIndex++;
            str = str.Left(iIndex) + str.Right(iLen - iIndex - 1);
         }
         else
         {
            // Found !
            str = str.Left(iIndex) + str.Right(iLen - iIndex - 1);
            return iIndex;
         }

         if (iIndex >= str.get_length())
            break;
      }
      // Not Found
      return -1;
   }


#ifdef WINDOWSEX


   bool graphics::Attach(HDC hdc)
   {

      ::exception::throw_not_implemented(get_app());

      return false;

   }


   HDC graphics::Detach()
   {

      ::exception::throw_not_implemented(get_app());

      return NULL;

   }


   bool graphics::AttachPrinter(HDC hdc)
   {

      ::exception::throw_not_implemented(get_app());

      return false;

   }


   HDC graphics::DetachPrinter()
   {

      ::exception::throw_not_implemented(get_app());

      return NULL;

   }

#endif

   bool graphics::draw_stock_icon(const RECT & rectParam, e_stock_icon eicon)
   {
      synch_lock sl(m_pmutex);

      ::draw2d::pen_sp pen(allocer());
      ::draw2d::brush_sp brush(allocer());

      *pen = *m_sppen;
      *brush = *m_spbrush;

      ::rect rect(rectParam);

      if(eicon == stock_icon_close)
      {

         rect.deflate(rect.width() / 7,rect.height() / 7);

         m_sppen->m_dWidth *= 2.0;
         m_sppen->m_bUpdated = false;
         move_to(rect.top_left());
         line_to(rect.bottom_right());
         move_to(rect.bottom_left());
         line_to(rect.top_right());

      }
      else if(eicon == stock_icon_zoom)
      {

         rect.deflate(0, rect.height() / 7);

         draw_rect(rect);

         m_sppen->m_elinecapBeg = ::draw2d::pen::line_cap_flat;
         m_sppen->m_elinecapEnd = ::draw2d::pen::line_cap_flat;
         move_to(rect.top_left() + size(0,(int64_t) (pen->m_dWidth/2.0)));
         line_to(rect.top_right() + size(0,(int64_t)(pen->m_dWidth / 2.0)));
         move_to(rect.top_left() + size(0,(int64_t)(pen->m_dWidth)));
         line_to(rect.top_right() + size(0,(int64_t)(pen->m_dWidth)));
         move_to(rect.top_left() + size(0,(int64_t)(pen->m_dWidth *3.0 / 2.0)));
         line_to(rect.top_right() + size(0,(int64_t)(pen->m_dWidth *3.0 / 2.0)));
         move_to(rect.top_left() + size(0,(int64_t)(pen->m_dWidth*2.0)));
         line_to(rect.top_right() + size(0,(int64_t)(pen->m_dWidth*2.0)));

      }
      else if(eicon == stock_icon_restore)
      {

         rect.deflate(0, rect.height() / 7);

         ::rect rect1(rect);

         rect1.deflate(0, 0, rect.width() / 3, rect.height() / 3);

         ::rect rect2(rect1);

         rect2.Align(align_bottom_right, rect);

         draw_rect(rect2);

         m_sppen->m_elinecapBeg = ::draw2d::pen::line_cap_flat;
         m_sppen->m_elinecapEnd = ::draw2d::pen::line_cap_flat;
         move_to(rect2.top_left() + size(0,(int64_t)(pen->m_dWidth / 2.0)));
         line_to(rect2.top_right() + size(0,(int64_t)(pen->m_dWidth / 2.0)));
         move_to(rect2.top_left() + size(0,(int64_t)(pen->m_dWidth)));
         line_to(rect2.top_right() + size(0,(int64_t)(pen->m_dWidth)));


         move_to(rect1.top_left());
         line_to(rect1.top_right());
         move_to(rect1.top_left() + size(0,(int64_t)(pen->m_dWidth / 2.0)));
         line_to(rect1.top_right() + size(0,(int64_t)(pen->m_dWidth / 2.0)));
         move_to(rect1.top_left() + size(0,(int64_t)(pen->m_dWidth)));
         line_to(rect1.top_right() + size(0,(int64_t)(pen->m_dWidth)));



         m_sppen->m_elinecapBeg = ::draw2d::pen::line_cap_square;
         m_sppen->m_elinecapEnd = ::draw2d::pen::line_cap_square;
         m_sppen->m_bUpdated = false;
         move_to(rect1.top_left() + size(0,(int64_t)(pen->m_dWidth)));
         line_to(rect1.bottom_left());
         line_to(rect2.bottom_left());

         move_to(rect1.top_right() + size(0,(int64_t)(pen->m_dWidth)));
         line_to(point(rect1.right,(int)(rect2.top - (int64_t)(pen->m_dWidth))));

      }
      else if(eicon == stock_icon_iconify)
      {

         rect.deflate(0, rect.height() / 7);


         move_to(rect.bottom_left() - size(0,(int64_t)(pen->m_dWidth*2.0)));
         line_to(rect.bottom_right() - size(0,(int64_t)(pen->m_dWidth*2.0)));
         move_to(rect.bottom_left() - size(0,(int64_t)(pen->m_dWidth*3.0 / 2.0)));
         line_to(rect.bottom_right() - size(0,(int64_t)(pen->m_dWidth*3.0 / 2.0)));
         move_to(rect.bottom_left() - size(0,(int64_t)(pen->m_dWidth)));
         line_to(rect.bottom_right() - size(0,(int64_t)(pen->m_dWidth)));
         move_to(rect.bottom_left() - size(0,(int64_t)(pen->m_dWidth / 2.0)));
         line_to(rect.bottom_right() - size(0,(int64_t)(pen->m_dWidth / 2.0)));
         move_to(rect.bottom_left());
         line_to(rect.bottom_right());

      }
      else if(eicon == stock_icon_transparent_frame)
      {

      }
      else if(eicon == stock_icon_dock)
      {

         rect.deflate(rect.height() / 8, rect.height() / 8);

         DrawEllipse(rect);

         ::rect rect1(rect);

         rect1.deflate((i32)(m_sppen->m_dWidth / 2.0),(i32)(m_sppen->m_dWidth / 2.0));

         DrawEllipse(rect1);

         ::rect rect2(rect);

         rect2.deflate((i32)(m_sppen->m_dWidth),(i32)(m_sppen->m_dWidth));

         DrawEllipse(rect2);

      }
      else if (eicon == stock_icon_notify)
      {

         rect.deflate(rect.height() / 2, rect.height() / 2);

         DrawEllipse(rect);

         ::rect rect1(rect);

         rect1.deflate((i32)(m_sppen->m_dWidth / 2.0), (i32)(m_sppen->m_dWidth / 2.0));

         DrawEllipse(rect1);

         ::rect rect2(rect);

         rect2.deflate((i32)(m_sppen->m_dWidth), (i32)(m_sppen->m_dWidth));

         DrawEllipse(rect2);

      }
      else if (eicon == stock_icon_level_up)
      {

         rect.deflate(rect.height() / 3, rect.height() / 3);

         point_array pta;

         pta.add(rect.bottom_left());

         pta.add(rect.bottom_right());

         pta.add((rect.right + rect.left) / 2, rect.top);

         polygon(pta);

      }
      else if (eicon == stock_icon_level_down)
      {

         rect.deflate(rect.height() / 3, rect.height() / 3);

         point_array pta;

         pta.add(rect.top_left());

         pta.add(rect.top_right());

         pta.add((rect.right + rect.left) / 2, rect.bottom);

         polygon(pta);

      }
      else
      {

         ::exception::throw_not_implemented(get_app());

      }

      *m_sppen = *pen;
      *m_spbrush = *brush;

      return true;

   }

   void graphics::debug()
   {
   }


   bool graphics::draw_error_line(i32 x1, i32 h, i32 x2, i32 iStyle)
   {

      int iR = argb_get_r_value(m_sppen->m_cr);
      int iG = argb_get_g_value(m_sppen->m_cr);
      int iB = argb_get_b_value(m_sppen->m_cr);
      int iA = argb_get_a_value(m_sppen->m_cr);

      if(iStyle == 0)
      {

         draw_line(x1, h, x2, h);

      }
      else
      {

         ::draw2d::dib_sp dib(allocer());

         double w = x2 - x1 + 1;

         dib->create((i32) w,6);

         if (dib->area() <= 0)
         {

            return false;

         }

         dib->Fill(0,0,0,0);

         double dStep = 0.125;
         double dPeriod = 7.0;
         double dTint;
         double dHalfH = 1.33;
         double dHSpan = 0.7;
         double dH = 2.5;
         double dCurl = 2.3;
         double dBaseTint = 2.0;
         double dCircleX;
         double dCircleY;

         for(double dx = 0; dx < w; dx+=dStep)
         {
            dCircleX = fmod(dx,(double)(dPeriod)) ;
            double dSign = dCircleX < (dPeriod / 2.0)? 1.0 : -1.0;
            dCircleX -= dPeriod / 2.0;
            dTint = dBaseTint * 0.51;
            dCircleY = dSign*sqrt(dPeriod *dPeriod / 4.0 - dCircleX*dCircleX) * 0.05;
            {
               double dy = (sin((double)dx * 2.0 * 3.1415 / dPeriod) - fmod(dx,(double)(dPeriod / 2.0)) / (dPeriod * dCurl)) + dCircleY;
               ;
               dy = (dy * dHalfH + dH - dHSpan);
               int x = (int)round(dx);
               int y = (int)round(dy);
               if(x < 0 || y < 0 || x >= dib->m_size.cx || y >= dib->m_size.cy)
               {
               }
               else
               {
                  int A = (dib->m_pcolorref[x + dib->m_iScan * y / sizeof(COLORREF)] >> 24) & 0xff;
                  double fy = 1.0 - fmod(fabs(dy),1.0);
                  double fx = 1.0 - fmod(fabs(dx),1.0);
                  A = (int) (A + ((fx * fy) * 255.0 * dStep*dTint));
                  A = MIN(A,255);
                  dib->m_pcolorref[x + dib->m_iScan * y / sizeof(COLORREF)] =  ARGB((A * iA) / 255,iB,iG,iR);
               }
            }
            dTint = dBaseTint * 0.51;
            {
               double dy = (sin((double)dx * 2.0 * 3.1415 / dPeriod) - fmod(dx,(double)(dPeriod / 2.0)) / (dPeriod * dCurl)) + dCircleY;
               dy = (dy * dHalfH + dH + dHSpan);
               int x = (int)round(dx);
               int y = (int)round(dy);
               if(x < 0 || y < 0 || x >= dib->m_size.cx || y >= dib->m_size.cy)
               {
               }
               else
               {
                  int A = (dib->m_pcolorref[x + dib->m_iScan * y / sizeof(COLORREF)] >> 24) & 0xff;
                  double fy = 1.0 - fmod(fabs(dy),1.0);
                  double fx = 1.0 - fmod(fabs(dx),1.0);
                  A = (int) (A + ((fx * fy) * 255.0 * dStep*dTint));
                  A = MIN(A,255);
                  dib->m_pcolorref[x + dib->m_iScan * y / sizeof(COLORREF)] =  ARGB((A * iA) / 255,iB,iG,iR);
               }

            }

            dTint = dBaseTint * 2.3;

            {
               double dy = (sin((double)dx * 2.0 * 3.1415 / dPeriod) - fmod(dx,(double)(dPeriod / 2.0)) / (dPeriod * dCurl)) + dCircleY;
               dy = (dy * dHalfH + dH);
               int x = (int)round(dx);
               int y = (int)round(dy);
               if(x < 0 || y < 0 || x >= dib->m_size.cx || y >= dib->m_size.cy)
               {
               }
               else
               {
                  int A = (dib->m_pcolorref[x + dib->m_iScan * y / sizeof(COLORREF)] >> 24) & 0xff;
                  double fy = 1.0 - fmod(fabs(dy),1.0);
                  double fx = 1.0 - fmod(fabs(dx),1.0);
                  A = (int) (A + ((fx * fy) * 255.0 * dStep*dTint));
                  A = MIN(A,255);
                  dib->m_pcolorref[x + dib->m_iScan * y / sizeof(COLORREF)] =  ARGB((A * iA) / 255,iB,iG,iR);

               }

            }

         }

         set_alpha_mode(::draw2d::alpha_mode_blend);

         BitBlt(x1,h,dib->m_size.cx,dib->m_size.cy,dib->get_graphics(),0,0);

      }

      return true;

   }


   void graphics::draw_ca2_with_border2(int x,int y,int z,int bOut,int bIn,COLORREF crBk,COLORREF cr,COLORREF crOut,COLORREF crIn)
   {

      draw_ca2(x + bIn + bOut,y + bIn + bOut,z,crBk,cr);

      draw_ca2_border2(x,y,z,bOut,bIn,crBk,cr,crOut,crIn);

   }


   void graphics::draw_ca2_with_border(int x,int y,int z,int b,COLORREF crBk,COLORREF cr,COLORREF crBorder)
   {

      draw_ca2(x + b,y + b,z,crBk,cr);

      int w = z / 19;

      if (w < 1)
      {

         w = 1;

      }

      z = w * 19;

      rect r(x + b,y + b,x + b + z,y + b + z);

      ::draw2d::pen_sp p(allocer());

      p->create_solid(1.0,crBorder);

      for(int i = 0; i < b; i++)
      {

         r.inflate(1,1);

         draw_rect(r,p);

      }

   }


   void graphics::draw_ca2(int x,int y,int z,COLORREF crBk,COLORREF cr)
   {

      ::draw2d::brush_sp b(allocer());

      // black rectangle

      int w = z / 19;

      if(w < 1)
         w = 1;

      z = w * 19;

      b->create_solid(crBk);

      rect r(x,y,x + z,y + z);

      fill_rect(r,b);

      // bottom line

      b->create_solid(cr);

      r.top += w * 13;
      r.bottom -= w;


      // c

      r.left += w;
      r.right = r.left + w * 5;

      rect c = r;

      // c vertical

      c.right = c.left + w;

      fill_rect(c,b);

      c = r;

      c.bottom = c.top + w;

      fill_rect(c,b);

      c = r;

      c.top = c.bottom - w;

      fill_rect(c,b);








      // a

      r.left += w * 6;
      r.right = r.left + w * 5;

      c = r;

      c.bottom = c.top + w;

      fill_rect(c,b);

      c = r;

      c.top = c.bottom - w;

      fill_rect(c,b);

      c = r;

      c.right = c.left + w * 2;
      c.top += w * 2;
      c.bottom = c.top + w;

      fill_rect(c,b);

      c = r;

      c.left += w * 5 / 2;
      c.right = c.left + w;
      c.top += w * 2;
      c.bottom = c.top + w;

      fill_rect(c,b);

      c = r;

      c.left = c.right - w;

      fill_rect(c,b);

      c = r;

      c.right = c.left + w;
      c.top += w * 2;

      fill_rect(c,b);





      // 2

      r.left += w * 6;
      r.right = r.left + w * 5;

      c = r;

      c.bottom = c.top + w;

      fill_rect(c,b);

      c = r;

      c.top = c.bottom - w;

      fill_rect(c,b);

      c = r;

      c.top += w * 2;
      c.bottom = c.top + w;

      fill_rect(c,b);

      c = r;

      c.right = c.left + w;
      c.top += w * 2;

      fill_rect(c,b);

      c = r;

      c.left = c.right - w;
      c.bottom -= w * 2;

      fill_rect(c,b);

   }


   void graphics::draw_ca2_border2(int x,int y,int z,int bOut,int bIn,COLORREF crBk,COLORREF cr,COLORREF crOut,COLORREF crIn)
   {
      int w = z / 19;

      if(w < 1)
         w = 1;

      z = w * 19;


      rect r(x + bIn + bOut,y + bIn + bOut,x + bIn + bOut + z - 1,y + bIn + bOut + z - 1);

      ::draw2d::pen_sp p(allocer());

      p->create_solid(1.0,crIn);

      for(int i = 0; i < bIn; i++)
      {

         r.inflate(1,1);

         draw_rect(r,p);

      }

      p->create_solid(1.0,crOut);

      for(int i = 0; i < bOut; i++)
      {

         r.inflate(1,1);

         draw_rect(r,p);

      }

   }


   void graphics::enum_fonts(::draw2d::font::enum_item_array & itema)
   {

      UNREFERENCED_PARAMETER(itema);

      _throw(not_implemented(get_app()));

   }


   void graphics::sorted_fonts(::draw2d::font::enum_item_array & itema)
   {

      enum_fonts(itema);

      ::sort::array::pred_sort(itema, [&](auto & a, auto & b)
      {

         return a->m_strName < b->m_strName;

      });

   }


   float graphics::nanosvg_distPtSeg(float x, float y, float px, float py, float qx, float qy)
   {

      float pqx, pqy, dx, dy, d, t;
      pqx = qx - px;
      pqy = qy - py;
      dx = x - px;
      dy = y - py;
      d = pqx*pqx + pqy*pqy;
      t = pqx*dx + pqy*dy;
      if (d > 0) t /= d;
      if (t < 0) t = 0;
      else if (t > 1) t = 1;
      dx = px + t*pqx - x;
      dy = py + t*pqy - y;
      return dx*dx + dy*dy;

   }


   void graphics::nanosvg_cubicBez(float x1, float y1, float x2, float y2,
                                   float x3, float y3, float x4, float y4,
                                   float tol, int level)
   {
      float x12, y12, x23, y23, x34, y34, x123, y123, x234, y234, x1234, y1234;
      float d;

      if (level > 12) return;

      x12 = (x1 + x2)*0.5f;
      y12 = (y1 + y2)*0.5f;
      x23 = (x2 + x3)*0.5f;
      y23 = (y2 + y3)*0.5f;
      x34 = (x3 + x4)*0.5f;
      y34 = (y3 + y4)*0.5f;
      x123 = (x12 + x23)*0.5f;
      y123 = (y12 + y23)*0.5f;
      x234 = (x23 + x34)*0.5f;
      y234 = (y23 + y34)*0.5f;
      x1234 = (x123 + x234)*0.5f;
      y1234 = (y123 + y234)*0.5f;

      d = nanosvg_distPtSeg(x1234, y1234, x1, y1, x4, y4);
      if (d > tol*tol)
      {
         nanosvg_cubicBez(x1, y1, x12, y12, x123, y123, x1234, y1234, tol, level + 1);
         nanosvg_cubicBez(x1234, y1234, x234, y234, x34, y34, x4, y4, tol, level + 1);
      }
      else
      {

         line_to(pointd(x4, y4));

      }

   }


   void graphics::nanosvg_drawPath(float* pts, int npts, char closed, float tol, COLORREF cr)
   {

      int i;

      begin_path();

      move_to(pointd(pts[0], pts[1]));

      for (i = 0; i < npts - 1; i += 3)
      {

         float* p = &pts[i * 2];

         nanosvg_cubicBez(p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7], tol, 0);

      }

      if (closed)
      {

         move_to(pointd(pts[0], pts[1]));

      }

      end_path();

   }


   void graphics::nanosvg_drawControlPts(float* pts, int npts)
   {

      int i;

      // Control lines
      //glColor4ubv(lineColor);
      //glBegin(GL_LINES);
      begin_path();

      for (i = 0; i < npts - 1; i += 3)
      {

         float* p = &pts[i * 2];

         move_to(point((i64) p[0], (i64)p[1]));
         line_to(point((i64)p[2], (i64)p[3]));
         line_to(point((i64)p[4], (i64)p[5]));
         line_to(point((i64)p[6], (i64)p[7]));

      }

      end_path();


      // Points
      //glPointSize(6.0f);
      //glColor4ubv(lineColor);

      //glBegin(GL_POINTS);
      //glVertex2f(pts[0], pts[1]);
      //for (i = 0; i < npts - 1; i += 3) {
      // float* p = &pts[i * 2];
      //glVertex2f(p[6], p[7]);
      //}
      //glEnd();

      // Points
      //glPointSize(3.0f);

      //glBegin(GL_POINTS);
      //glColor4ubv(bgColor);
      //glVertex2f(pts[0], pts[1]);
      //for (i = 0; i < npts - 1; i += 3) {
      //   float* p = &pts[i * 2];
      //   glColor4ubv(lineColor);
      //   glVertex2f(p[2], p[3]);
      //   glVertex2f(p[4], p[5]);
      //   glColor4ubv(bgColor);
      //   glVertex2f(p[6], p[7]);
      //}
      //glEnd();

   }


   void graphics::nanosvg_drawframe(NSVGimage* pimage, int x, int y, int width, int height)
   {

      float view[4], cx, cy, hw, hh, aspect, px;

      NSVGshape* shape;

      NSVGpath* path;

      //glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
      //glfwGetFramebufferSize(window, &width, &height);

      //glViewport(0, 0, width, height);

      int n=SaveDC();

      OffsetViewportOrg(x, y);

      //glClearColor(220.0f / 255.0f, 220.0f / 255.0f, 220.0f / 255.0f, 1.0f);
      //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
      //glEnable(GL_BLEND);
      //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
      //glDisable(GL_TEXTURE_2D);
      //glMatrixMode(GL_PROJECTION);
      //glLoadIdentity();

      // Fit view to bounds
      cx = pimage->width*0.5f;
      cy = pimage->height*0.5f;
      hw = pimage->width*0.5f;
      hh = pimage->height*0.5f;

      if (width / hw < height / hh)
      {
         aspect = (float)height / (float)width;
         view[0] = cx - hw * 1.2f;
         view[2] = cx + hw * 1.2f;
         view[1] = cy - hw * 1.2f * aspect;
         view[3] = cy + hw * 1.2f * aspect;
      }
      else
      {
         aspect = (float)width / (float)height;
         view[0] = cx - hh * 1.2f * aspect;
         view[2] = cx + hh * 1.2f * aspect;
         view[1] = cy - hh * 1.2f;
         view[3] = cy + hh * 1.2f;
      }
      // Size of one pixel.
      px = (view[2] - view[1]) / (float)width;

      //glOrtho(view[0], view[2], view[3], view[1], -1, 1);

      //glMatrixMode(GL_MODELVIEW);
      //glLoadIdentity();
      //glDisable(GL_DEPTH_TEST);
      //glColor4ub(255, 255, 255, 255);
      //glEnable(GL_BLEND);
      //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

      // Draw bounds
      //glColor4ub(0, 0, 0, 64);
      //glBegin(GL_LINE_LOOP);
      //glVertex2f(0, 0);
      //glVertex2f(pimage->width, 0);
      //glVertex2f(pimage->width, pimage->height);
      //glVertex2f(0, pimage->height);
      //glEnd();

      ::draw2d::pen_sp pen(allocer());

      pen->create_solid(1.0, ARGB(255, 0, 128, 0));

      SelectObject(pen);

      for (shape = pimage->shapes; shape != NULL; shape = shape->next)
      {

         for (path = shape->paths; path != NULL; path = path->next)
         {

            nanosvg_drawPath(path->pts, path->npts, path->closed, px / 3.0f, ARGB(255, 0, 128, 0));

//            nanosvg_drawControlPts(path->pts, path->npts);

         }

      }

      //glfwSwapBuffers(window);

      RestoreDC(n);

   }

   //void graphics::nanosvg_resizecb(int width, int height)
   //{
   //   // Update and render
   //   NSVG_NOTUSED(width);
   //   NSVG_NOTUSED(height);
   //   //drawframe(window);
   //}


   bool graphics::nanosvg(string str, int x, int y, int w, int h)
   {

      struct NSVGimage* image;

      image = nsvgParse((char *) (const char *) str, "px", 96);

      nanosvg_drawframe(image, x, y, w, h);

      nsvgDelete(image);

      return true;

   }



   bool graphics::is_valid_update_window_thread()
   {

      return true;

   }


   void graphics::on_begin_draw(oswindow wnd, SIZE sz)
   {

   }

   void graphics::on_end_draw(oswindow wnd)
   {


   }

   savedc::savedc(graphics * pgraphics)
   {
      m_pgraphics = pgraphics;
      try
      {
         if (m_pgraphics != NULL)
         {
            m_iSavedDC = m_pgraphics->SaveDC();
            m_matrixViewport = pgraphics->m_matrixViewport;
            m_matrixTransform = pgraphics->m_matrixTransform;
         }
      }
      catch (...)
      {

      }
   }
   savedc::~savedc()
   {
      try
      {
         if (m_pgraphics != NULL)
         {
            m_pgraphics->RestoreDC(m_iSavedDC);
            m_pgraphics->m_matrixViewport = m_matrixViewport;
            m_pgraphics->m_matrixTransform = m_matrixTransform;
         }
      }
      catch (...)
      {

      }

   }

   bool graphics::_get(matrix & matrix)
   {

      return false;

   }


   bool graphics::_set(const matrix & matrix)
   {

      return false;

   }


   bool graphics::get(matrix & matrix)
   {

      matrix = m_matrixTransform;

      return true;

   }


   bool graphics::set(const matrix & matrix)
   {

      m_matrixTransform = matrix;

      update_matrix();

      return true;

   }


   bool graphics::update_matrix()
   {

      matrix matrixViewport;

      matrix matrixViewportScale;

      matrix matrixViewportTranslate;

      matrixViewportScale.a1 = m_matrixViewport.a1;

      matrixViewportScale.b2 = m_matrixViewport.b2;

      matrixViewportTranslate.c1 = m_matrixViewport.c1;

      matrixViewportTranslate.c2 = m_matrixViewport.c2;

      if (!_set(matrixViewportScale * m_matrixTransform * matrixViewportTranslate))
      {

         return false;

      }

      return true;

   }


   bool graphics::append(const matrix & matrix)
   {

      m_matrixTransform.append(matrix);

      update_matrix();

      return true;

   }


   bool graphics::prepend(const matrix & matrix)
   {

      m_matrixTransform.prepend(matrix);

      update_matrix();

      return true;

   }


   void graphics::draw_border(LPCRECT lpcrect, COLORREF cr, int iWidth)
   {

      rect r(lpcrect);

      r.inflate(iWidth + 1, iWidth + 1);

      sp(pen) p = m_sppen;

      pen_sp p1(allocer());

      p1->create_solid(iWidth, cr);

      p1->m_ealign = ::draw2d::pen::align_inset;

      SelectObject(p1);

      draw_rect(r);

      SelectObject(p);

   }


} // namespace draw2d



