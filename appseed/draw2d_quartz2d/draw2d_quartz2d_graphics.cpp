#include "framework.h"
#include <math.h>
#include <memory.h>
#include <CoreFoundation/CFDictionary.h>


//extern "C"
unsigned long apple_get_fonts(char *** p);
double nsfont_get_ctweight(int iWeight);

void copy(CGRect &r, LPCRECTD pr)
{
   
   r.origin.x = pr->left;
   r.origin.y = pr->top;
   r.size.width = width(pr);
   r.size.height = height(pr);

}


namespace draw2d_quartz2d
{

   
   void copy(CGAffineTransform & affine, const ::draw2d::matrix & m)
   {
      
      affine.a = m.a1;
      affine.b = m.a2;
      affine.c = m.b1;
      affine.d = m.b2;
      affine.tx = m.c1;
      affine.ty = m.c2;
      
   }
   
   
   void copy(::draw2d::matrix & m, const CGAffineTransform & affine)
   {
      
      m.a1 = affine.a;
      m.a2 = affine.b;
      m.b1 = affine.c;
      m.b2 = affine.d;
      m.c1 = affine.tx;
      m.c2 = affine.ty;

   }

   
   graphics::graphics(::aura::application * papp) :
      ::object(papp),
      ::draw2d::graphics(papp)
   {
      m_iType = -1;
      defer_create_mutex();

      m_iSaveDC         = 0;
      m_bPrinting       = FALSE;
      m_pdibAlphaBlend  = NULL;
      m_etextrendering  = ::draw2d::text_rendering_anti_alias_grid_fit;
      m_bOwnDC          = true;
      m_pdc             = NULL;
      m_layer           = NULL;

   }

 
   void graphics::assert_valid() const
   {

      ::draw2d::graphics::assert_valid();

   }


   void graphics::dump(dump_context & dumpcontext) const
   {
      
      ::draw2d::graphics::dump(dumpcontext);

      dumpcontext << "\n";

   }
   

   graphics::~graphics()
   {

      DeleteDC();

   }


   bool graphics::IsPrinting()
   {
      
      return m_bPrinting;
      
   }
   

   bool graphics::CreateDC(const char * lpszDriverName, const char * lpszDeviceName, const char * lpszOutput, const void * lpInitData)
   {
      _throw(not_supported_exception(get_app()));
      //return Attach(::CreateDC(lpszDriverName, lpszDeviceName, lpszOutput, (const DEVMODE*)lpInitData));
   }

   bool graphics::CreateIC(const char * lpszDriverName, const char * lpszDeviceName, const char * lpszOutput, const void * lpInitData)
   {
      _throw(not_supported_exception(get_app()));
      //return Attach(::CreateIC(lpszDriverName, lpszDeviceName, lpszOutput, (const DEVMODE*) lpInitData));
   }


   CGContextRef MyCreateBitmapContext(int cx, int cy)
   {

      CGContextRef    context = NULL;

      int             size;

      int             scan;

      scan                 = (cx * 4);

      size                 = (scan * cy);

      CGColorSpaceRef colorspace = CGColorSpaceCreateDeviceRGB();

      context              = CGBitmapContextCreate(NULL, cx, cy, 8, scan, colorspace, kCGImageAlphaPremultipliedLast);

      CGColorSpaceRelease(colorspace);

      if(context== NULL)
      {

         return NULL;

      }

      return context;

   }


   bool graphics::CreateCompatibleDC(::draw2d::graphics * pgraphics)
   {

      DeleteDC();

      m_pdc             = NULL;

      CGContextRef cg   = NULL;

      if(pgraphics == NULL || pgraphics->get_os_data() == NULL)
      {

         cg = MyCreateBitmapContext(1, 1);

      }
      else
      {

         cg = (CGContextRef) pgraphics->get_os_data();

      }

      CGSize size;

      size.width = 1;

      size.height = 1;

      m_layer = CGLayerCreateWithContext(cg, size, NULL);

      if(m_layer != NULL)
      {

         m_pdc = CGLayerGetContext(m_layer);

      }

      if(m_pdc == NULL)
      {

         CGLayerRelease(m_layer);

         m_layer = NULL;

      }

      if(pgraphics == NULL || pgraphics->get_os_data() == NULL)
      {

         CGContextRelease(cg);

      }

      if(m_layer == NULL)
      {

         CGContextRelease(cg);
         
         return false;

      }

//      if(m_pdc != NULL)
//      {
//
//         m_affine = CGContextGetCTM(m_pdc);
//
//      }

      m_bOwnDC = true;

      return true;

   }


   int32_t graphics::GetDeviceCaps(int32_t nIndex)
   {
      /*      ASSERT(get_handle2() != NULL);
       return ::GetDeviceCaps(get_handle2(), nIndex);*/
      _throw(not_implemented(get_app()));
      return 0;

   }


   point graphics::GetBrushOrg()
   {
      /*      ASSERT(get_handle1() != NULL);
       POINT point;
       VERIFY(::GetBrushOrgEx(get_handle1(), &point));
       return point;*/
      _throw(not_implemented(get_app()));
      return point(0, 0);

   }

   point graphics::SetBrushOrg(int32_t x, int32_t y)
   {
      /*      ASSERT(get_handle1() != NULL);
       POINT point;
       VERIFY(::SetBrushOrgEx(get_handle1(), x, y, &point));
       return point;*/
      _throw(not_implemented(get_app()));
      return point(0, 0);

   }

   point graphics::SetBrushOrg(POINT point)
   {
      /*      ASSERT(get_handle1() != NULL);
       VERIFY(::SetBrushOrgEx(get_handle1(), point.x, point.y, &point));
       return point;*/
      _throw(not_implemented(get_app()));
      return ::point(0, 0);

   }

   int32_t graphics::EnumObjects(int32_t nObjectType, int32_t (CALLBACK* lpfn)(LPVOID, LPARAM), LPARAM lpData)
   {
      /*      ASSERT(get_handle2() != NULL);
       return ::EnumObjects(get_handle2(), nObjectType, (GOBJENUMPROC)lpfn, lpData);*/
      _throw(not_implemented(get_app()));
      return 0;

   }


   ::draw2d::bitmap* graphics::SelectObject(::draw2d::bitmap * pbitmap)
   {
      
      
      if(m_iType != -1)
      {
         
         //TRACE("occluding device context?!!?");
         
      }

      sp(::draw2d_quartz2d::bitmap) pbitmapQuartz = pbitmap;

      if(pbitmapQuartz.is_set())
      {

         DeleteDC();

         attach(pbitmapQuartz->m_pdc);

         m_bOwnDC = false;
           
         m_spbitmap = pbitmap;

      }

      return m_spbitmap;
      
   }


   ::draw2d::object* graphics::SelectObject(::draw2d::object * pobject)
   {

       sp(::draw2d::bitmap) pbitmap = pobject;

        if(pbitmap.is_set())
        {

            return SelectObject(pbitmap);

        }
      sp(::draw2d::pen) ppen = pobject;
      
      if(ppen.is_set())
      {
         
         return SelectObject(ppen);
         
      }

      sp(::draw2d::brush) pbrush = pobject;
      
      if(pbrush.is_set())
      {
         
         return SelectObject(pbrush);
         
      }
      sp(::draw2d::font) pfont = pobject;
      
      if(pfont.is_set())
      {
         
         return SelectObject(pfont);
         
      }
      
      sp(::draw2d::region) pregion = pobject;
      
      if(pregion.is_set())
      {
         
         SelectObject(pregion);
         
         return pregion;
         
      }

       return NULL;

   }

   /*   HGDIOBJ graphics::SelectObject(HGDIOBJ hObject) // Safe for NULL handles
    {

    UINT uiType = GetObjectType(hObject);

    if(uiType == OBJ_BITMAP)
    {

    HBITMAP hbitmap = (HBITMAP) hObject;

    if(m_spbitmap.is_null())
    m_spbitmap.create(get_app());

    if(m_spbitmap.is_null())
    return NULL;

    (dynamic_cast < ::win::bitmap * > (m_spbitmap.m_p))->m_pbitmap = new Gdiplus::Bitmap(hbitmap, NULL);

    if(m_pgraphics != NULL)
    {
    delete m_pgraphics;
    }

    m_pgraphics = new Gdiplus::Graphics((Gdiplus::Bitmap *) m_spbitmap->get_os_data());

    set_text_rendering(::draw2d::text_rendering_anti_alias_grid_fit);

    return hbitmap;

    }

     ASSERT(get_handle1() == get_handle2()); // ASSERT a simple graphics object
    //return (hObject != NULL) ? ::SelectObject(get_handle1(), hObject) : NULL; */
   /*    return NULL;
    }*/

   COLORREF graphics::GetNearestColor(COLORREF crColor)
   {
      //_throw(not_implemented(get_app()));
      return crColor;
      //      return ::GetNearestColor(get_handle2(), crColor);
   }

   UINT graphics::RealizePalette()
   {
      //      return ::RealizePalette(get_handle1());
      return 0;
   }

   void graphics::UpdateColors()
   {
      //::UpdateColors(get_handle1());

   }

//   COLORREF graphics::GetBkColor()
//   {
//      //return ::GetBkColor(get_handle2());
//      return 0;
//   }
//
//   int32_t graphics::GetBkMode()
//   {
//      //return ::GetBkMode(get_handle2());
//      return 0;
//   }

   int32_t graphics::GetPolyFillMode()
   {
      //return ::GetPolyFillMode(get_handle2());
//      return cairo_get_fill_rule(m_pdc) == CAIRO_FILL_RULE_WINDING ? ::ca2::fill_mode_winding : ::ca2::fill_mode_alternate;
      return 0;
   }

   int32_t graphics::GetROP2()
   {
      //return ::GetROP2(get_handle2());
      return 0;
   }

   int32_t graphics::GetStretchBltMode()
   {
      //return ::GetStretchBltMode(get_handle2());
      return 0;
   }

   int32_t graphics::GetMapMode()
   {
      //return ::GetMapMode(get_handle2());
      return 0;
   }

   int32_t graphics::GetGraphicsMode()
   {
      //return ::GetGraphicsMode(get_handle2());
      return 0;
   }

//   bool graphics::GetWorldTransform(XFORM* pXform)
//   {
//
//      //return ::GetWorldTransform(get_handle2(),pXform) != FALSE;
//      return 0;
//
//   }

   size graphics::GetViewportExt()
   {
      /*SIZE size;
       ::GetViewportExtEx(get_handle2(), &size);
       return size;*/

      return ::size(0, 0);
   }

   point graphics::GetWindowOrg()
   {
      /*POINT point;
       ::GetWindowOrgEx(get_handle2(), &point);
       return point;*/
      return ::point(0, 0);
   }

   size graphics::GetWindowExt()
   {
      /*SIZE size;
       ::GetWindowExtEx(get_handle2(), &size);
       return size;*/
      return ::size(0, 0);
   }

   // non-virtual helpers calling virtual mapping functions
   point graphics::SetViewportOrg(POINT point)
   {

      return SetViewportOrg(point.x, point.y);

   }

   size graphics::SetViewportExt(SIZE size)
   {
      //return SetViewportExt(size.cx, size.cy);
      return ::size(0, 0);
   }

   point graphics::SetWindowOrg(POINT point)
   {
      //return SetWindowOrg(point.x, point.y);
      return ::point(0, 0);
   }

   size graphics::SetWindowExt(SIZE size)
   {
      //return SetWindowExt(size.cx, size.cy);
      return ::size(0, 0);
   }

//   void graphics::DPtoLP(LPPOINT lpPoints, int32_t nCount)
//   {
//      //::DPtoLP(get_handle2(), lpPoints, nCount);
//   }

   void graphics::DPtoLP(LPRECT lpRect)
   {
      //::DPtoLP(get_handle2(), (LPPOINT)lpRect, 2);
   }

//   void graphics::LPtoDP(LPPOINT lpPoints, int32_t nCount)
//   {
//      //::LPtoDP(get_handle2(), lpPoints, nCount);
//   }

   void graphics::LPtoDP(LPRECT lpRect)
   {
      //::LPtoDP(get_handle2(), (LPPOINT)lpRect, 2);
   }

   bool graphics::FillRgn(::draw2d::region* pRgn, ::draw2d::brush* pBrush)
   {

      _throw(not_implemented(get_app()));
      //return ::FillRgn(get_handle1(), (HRGN)pRgn->get_os_data(), (HBRUSH)pBrush->get_os_data()) != FALSE;
      return false;

   }

   bool graphics::FrameRgn(::draw2d::region* pRgn, ::draw2d::brush* pBrush, int32_t nWidth, int32_t nHeight)
   {

      //      return ::FrameRgn(get_handle1(), (HRGN)pRgn->get_os_data(), (HBRUSH)pBrush->get_os_data(), nWidth, nHeight) != FALSE;
      _throw(not_implemented(get_app()));
      return false;

   }

   bool graphics::InvertRgn(::draw2d::region* pRgn)
   {

      //    ASSERT(get_handle1() != NULL);

      //      return ::InvertRgn(get_handle1(), (HRGN)pRgn->get_os_data()) != FALSE;
      _throw(not_implemented(get_app()));
      return false;


   }

   bool graphics::PaintRgn(::draw2d::region* pRgn)
   {

      //      ASSERT(get_handle1() != NULL);

      //    return ::PaintRgn(get_handle1(), (HRGN)pRgn->get_os_data())  != FALSE;
      _throw(not_implemented(get_app()));
      return false;

   }

   bool graphics::PtVisible(int32_t x, int32_t y)
   {

      //    ASSERT(get_handle1() != NULL);

      //      return ::PtVisible(get_handle1(), x, y) != FALSE;
      _throw(not_implemented(get_app()));
      return false;

   }

   bool graphics::PtVisible(POINT point)
   {

      //      ASSERT(get_handle1() != NULL);

      //      return PtVisible(point.x, point.y);

      _throw(not_implemented(get_app()));
      return false;

   }

   bool graphics::RectVisible(const RECT & lpRect)
   {

      //      ASSERT(get_handle1() != NULL);

      //      return ::RectVisible(get_handle1(), lpRect) != FALSE;

      _throw(not_implemented(get_app()));
      return false;

   }

   
   pointd graphics::current_position()
   {
      
      return m_pt;

   }
   

   bool graphics::Arc(int32_t x1, int32_t y1, int32_t x2, int32_t y2, int32_t x3, int32_t y3, int32_t x4, int32_t y4)
   {

      return ::draw2d::graphics::Arc(x1, y1, x2, y2, x3, y3, x4, y4);

   }
   
   
   bool graphics::Arc(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4)
   {
      
      return ::draw2d::graphics::Arc(x1, y1, x2, y2, x3, y3, x4, y4);
      
   }
   
   
   bool graphics::Arc(double x, double y, double w, double h, double start, double extends)
   {
      
      double end = start + extends;
   
      CGContextSaveGState(m_pdc);
      
      CGContextTranslateCTM(m_pdc, x + w/2.0, y + h/2.0);
      
      CGContextScaleCTM(m_pdc, w/2.0, h/2.0);
      
      CGContextAddArc(m_pdc, 0.f, 0.f, 1.0f, start * 3.1415 / 180.0, end * 3.1415 / 180.0, end < 0.0);
      
      CGContextRestoreGState(m_pdc);
      
      return draw();
      
   }


   bool graphics::Arc(const RECT & lpRect, POINT ptStart, POINT ptEnd)
   {

      return Arc(
                 lpRect.left,
                 lpRect.top,
                 lpRect.right,
                 lpRect.bottom,
                 ptStart.x,
                 ptStart.y,
                 ptEnd.x,
                 ptEnd.y);

   }

   bool graphics::Polyline(const POINT* lpPoints, count nCount)
   {

      /*ASSERT(get_handle1() != NULL);

       return ::Polyline(get_handle1(), lpPoints, nCount) != FALSE;*/

//      _throw(not_implemented(get_app()));

      if(nCount < 2)
         return false;

      CGContextBeginPath(m_pdc);

      set_polygon(lpPoints, nCount);

      if(!draw())
         return false;

      return true;

   }

   
   bool graphics::fill_rect(LPCRECT lpRect, ::draw2d::brush* pBrush)
   {

      CGRect rect;

      copy(rect, lpRect);

      CGContextBeginPath(m_pdc);

      CGContextAddRect(m_pdc, rect);

      fill(pBrush);
                                 
      return true;

   }
                                 
                                 
   void graphics::frame_rect(LPCRECT lpRect, ::draw2d::brush* pBrush)
   {

      CGRect rect;
      
      copy(rect, lpRect);
      
      CGContextBeginPath(m_pdc);
      
      CGContextAddRect(m_pdc, rect);

      draw(pBrush);
      
   }


   bool graphics::draw_rect(LPCRECT lpRect, ::draw2d::pen* ppen)
   {

      CGRect rect;

      copy(rect, lpRect);

      set(ppen);

      CGContextStrokeRect(m_pdc, rect);

      return true;

   }


   bool graphics::draw_rect(LPCRECTD lpRect)
   {
      
      rect r(lpRect);
      
      draw_rect(r, m_sppen);
      
      return true;
      
   }

   void graphics::invert_rect(LPCRECT lpRect)
   {

      _throw(not_implemented(get_app()));
      return;

      //      ASSERT(get_handle1() != NULL); ::InvertRect(get_handle1(), lpRect);

   }

   bool graphics::DrawIcon(int32_t x, int32_t y, ::visual::icon * picon)
   {

      _throw(not_implemented(get_app()));
      return false;


      //    ASSERT(get_handle1() != NULL);

      //  if(picon == NULL)
      //   return false;

      //      return ::DrawIcon(get_handle1(), x, y, (HICON) picon->m_picon) != FALSE;

   }

   bool graphics::DrawIcon(POINT point, ::visual::icon * picon)
   {

      _throw(not_implemented(get_app()));
      return false;
      /*      ASSERT(get_handle1() != NULL);

       if(picon == NULL)
       return false;

       return ::DrawIcon(get_handle1(), point.x, point.y, (HICON) picon->m_picon) != FALSE;*/

   }

   bool graphics::DrawIcon(int32_t x, int32_t y, ::visual::icon * picon, int32_t cx, int32_t cy, UINT istepIfAniCur, HBRUSH hbrFlickerFreeDraw, UINT diFlags)
   {

      return false;

      /*      try
       {

       if(picon == NULL)
       return FALSE;

       if(m_pgraphics == NULL)
       return FALSE;

       bool bOk = FALSE;

       BITMAPINFO info;
       COLORREF * pcolorref;

       ZeroMemory(&info, sizeof (BITMAPINFO));

       info.bmiHeader.biSize          = sizeof (BITMAPINFOHEADER);
       info.bmiHeader.biWidth         = cx;
       info.bmiHeader.biHeight        = - cy;
       info.bmiHeader.biPlanes        = 1;
       info.bmiHeader.biBitCount      = 32;
       info.bmiHeader.biCompression   = BI_RGB;
       info.bmiHeader.biSizeImage     = cx * cy * 4;

       HBITMAP hbitmap = ::CreateDIBSection(NULL, &info, DIB_RGB_COLORS, (void **) &pcolorref, NULL, NULL);

       HDC hdc = ::CreateCompatibleDC(NULL);

       HBITMAP hbitmapOld = (HBITMAP) ::SelectObject(hdc, hbitmap);

       if(::DrawIconEx(hdc, 0, 0, (HICON) picon->m_picon, cx, cy, istepIfAniCur, NULL, DI_IMAGE | DI_MASK))
       {

       ::SelectObject(hdc, hbitmapOld);

       try
       {

       Gdiplus::Bitmap b(cx, cy, cx * 4 , PixelFormat32bppARGB, (BYTE *) pcolorref);

       bOk = m_pgraphics->DrawImage(&b, x, y, 0, 0, cx, cy, Gdiplus::UnitPixel) == Gdiplus::Ok;

       }
       catch(...)
       {
       }

       }

       ::DeleteDC(hdc);

       ::DeleteObject(hbitmap);

       return bOk;

       }
       catch(...)
       {
       return FALSE;
       }
       */
      //return ::DrawIconEx(get_handle1(), x, y, picon->m_hicon, cx, cy, istepIfAniCur, hbrFlickerFreeDraw, diFlags);

   }

   bool graphics::DrawState(point pt, size size, HBITMAP hBitmap, UINT nFlags, HBRUSH hBrush)
   {

      _throw(not_implemented(get_app()));
      return false;
      //      ASSERT(get_handle1() != NULL);
      //      return ::DrawState(get_handle1(), hBrush, NULL, (LPARAM)hBitmap, 0, pt.x, pt.y, size.cx, size.cy, nFlags|DST_BITMAP) != FALSE;

   }

   bool graphics::DrawState(point pt, size size, ::draw2d::bitmap* pBitmap, UINT nFlags, ::draw2d::brush* pBrush)
   {

      _throw(not_implemented(get_app()));
      return false;
      //      ASSERT(get_handle1() != NULL);
      //      return ::DrawState(get_handle1(), (HBRUSH)pBrush->get_os_data(), NULL, (LPARAM)pBitmap->get_os_data(), 0, pt.x, pt.y, size.cx, size.cy, nFlags|DST_BITMAP) != FALSE;

   }

   /*
   bool graphics::DrawState(point pt, size size, HICON hIcon, UINT nFlags, HBRUSH hBrush)
   {

      _throw(not_implemented(get_app()));
      return false;
      //      ASSERT(get_handle1() != NULL);
      //      return ::DrawState(get_handle1(), hBrush, NULL, (LPARAM)hIcon, 0, pt.x, pt.y, size.cx, size.cy, nFlags|DST_ICON) != FALSE;

   }


   bool graphics::DrawState(point pt, size size, HICON hIcon, UINT nFlags, ::draw2d::brush* pBrush)
   {

      _throw(not_implemented(get_app()));
      return false;
      //      ASSERT(get_handle1() != NULL);
      //      return ::DrawState(get_handle1(), (HBRUSH)pBrush->get_os_data(), NULL, (LPARAM)hIcon, 0, pt.x, pt.y, size.cx, size.cy, nFlags|DST_ICON) != FALSE;

   }*/

   bool graphics::DrawState(point pt, size size, const char * lpszText, UINT nFlags, bool bPrefixText, int32_t nTextLen, HBRUSH hBrush)
   {

      _throw(not_implemented(get_app()));
      return false;
      //      ASSERT(get_handle1() != NULL);
      //      return ::DrawState(get_handle1(), hBrush,  NULL, (LPARAM)lpszText, (WPARAM)nTextLen, pt.x, pt.y, size.cx, size.cy, nFlags|(bPrefixText ? DST_PREFIXTEXT : DST_TEXT)) != FALSE;

   }

   bool graphics::DrawState(point pt, size size, const char * lpszText, UINT nFlags, bool bPrefixText, int32_t nTextLen, ::draw2d::brush* pBrush)
   {

      _throw(not_implemented(get_app()));
      return false;
      //      ASSERT(get_handle1() != NULL);
      //      return ::DrawState(get_handle1(), (HBRUSH)pBrush->get_os_data(), NULL, (LPARAM)lpszText, (WPARAM)nTextLen, pt.x, pt.y, size.cx, size.cy, nFlags|(bPrefixText ? DST_PREFIXTEXT : DST_TEXT)) != FALSE;

   }

   /*

    bool graphics::DrawState(point pt, size size, DRAWSTATEPROC lpDrawProc, LPARAM lData, UINT nFlags, HBRUSH hBrush)
    {

    _throw(not_implemented(get_app()));
    return false;

    //      ASSERT(get_handle1() != NULL);
    //      return ::DrawState(get_handle1(), hBrush, lpDrawProc, lData, 0, pt.x, pt.y, size.cx, size.cy, nFlags|DST_COMPLEX) != FALSE;

    }

    bool graphics::DrawState(point pt, size size, DRAWSTATEPROC lpDrawProc, LPARAM lData, UINT nFlags, ::draw2d::brush* pBrush)
    {

    _throw(not_implemented(get_app()));
    return false;

    //      ASSERT(get_handle1() != NULL);
    //      return ::DrawState(get_handle1(), (HBRUSH)pBrush->get_os_data(), lpDrawProc, lData, 0, pt.x, pt.y, size.cx, size.cy, nFlags|DST_COMPLEX) != FALSE;

    }

    */

   bool graphics::DrawEdge(LPRECT lpRect, UINT nEdge, UINT nFlags)
   {

      _throw(not_implemented(get_app()));
      return false;

      //      ASSERT(get_handle1() != NULL);
      //      return ::DrawEdge(get_handle1(), lpRect, nEdge, nFlags) != FALSE;

   }

   bool graphics::DrawFrameControl(LPRECT lpRect, UINT nType, UINT nState)
   {

      _throw(not_implemented(get_app()));
      return false;
      //      ASSERT(get_handle1() != NULL);
      //      return ::DrawFrameControl(get_handle1(), lpRect, nType, nState) != FALSE;

   }

   bool graphics::Chord(int32_t x1, int32_t y1, int32_t x2, int32_t y2, int32_t x3, int32_t y3, int32_t x4, int32_t y4)
   {
      _throw(not_implemented(get_app()));
      return false;

      //      ASSERT(get_handle1() != NULL);
      //      return ::Chord(get_handle1(), x1, y1, x2, y2, x3, y3, x4, y4) != FALSE;
   }

   bool graphics::Chord(const RECT & lpRect, POINT ptStart, POINT ptEnd)
   {

      _throw(not_implemented(get_app()));
      return false;

      //ASSERT(get_handle1() != NULL);
      //return ::Chord(get_handle1(), lpRect.left, lpRect.top, lpRect.right, lpRect.bottom, ptStart.x, ptStart.y, ptEnd.x, ptEnd.y) != FALSE;

   }

   void graphics::DrawFocusRect(const RECT & lpRect)
   {

      _throw(not_implemented(get_app()));

      //ASSERT(get_handle1() != NULL); ::DrawFocusRect(get_handle1(), lpRect);

   }

   bool graphics::DrawEllipse(int32_t x1, int32_t y1, int32_t x2, int32_t y2)
   {

//      double centerx    = (x2 + x1) / 2.0;
//      double centery    = (y2 + y1) / 2.0;
//
//      double radiusx    = abs(x2 - x1) / 2.0;
//      double radiusy    = abs(y2 - y1) / 2.0;
//
//      if(radiusx == 0.0 || radiusy == 0.0)
//         return false;
//
//      cairo_translate(m_pdc, centerx, centery);
//
//      cairo_scale(m_pdc, radiusx, radiusy);
//
//      cairo_arc(m_pdc, 0.0, 0.0, 1.0, 0.0, 2.0 * 3.1415);
//
//      draw();
//
//      cairo_scale(m_pdc, 1.0 / radiusx, 1.0 / radiusy);
//
//      cairo_translate(m_pdc, -centerx,  -centery);

      CGRect rect;

      rect.origin.x     = x1;
      rect.origin.y     = y1;
      rect.size.width   = x2 - x1;
      rect.size.height  = y2 - y1;

      set(m_sppen);

      CGContextStrokeEllipseInRect(m_pdc, rect);

      return true;

   }


   bool graphics::DrawEllipse(const RECT & lprect)
   {


      return DrawEllipse(lprect.left, lprect.top, lprect.right, lprect.bottom);


      /*return ::Ellipse(get_handle1(), lpRect.left, lpRect.top,
       lpRect.right, lpRect.bottom); */

   }


   bool graphics::FillEllipse(int32_t x1, int32_t y1, int32_t x2, int32_t y2)
   {

//      double centerx    = (x2 + x1) / 2.0;
//
//      double centery    = (y2 + y1) / 2.0;
//
//      double radiusx    = abs(x2 - x1) / 2.0;
//
//      double radiusy    = abs(y2 - y1) / 2.0;
//
//      if(radiusx == 0.0 || radiusy == 0.0)
//         return false;
//
//      cairo_translate(m_pdc, centerx, centery);
//
//      cairo_scale(m_pdc, radiusx, radiusy);
//
//      cairo_arc(m_pdc, 0.0, 0.0, 1.0, 0.0, 2.0 * 3.1415);
//
//      fill();
//
//      cairo_scale(m_pdc, 1.0 / radiusx, 1.0 / radiusy);
//
//      cairo_translate(m_pdc, -centerx,  -centery);

      CGRect rect;

      rect.origin.x     = x1;
      rect.origin.y     = y1;
      rect.size.width   = x2 - x1;
      rect.size.height  = y2 - y1;

      //set(m_spbrush);

      CGContextAddEllipseInRect(m_pdc, rect);

      return fill();

   }


   bool graphics::FillEllipse(const RECT & lpRect)
   {

      /*return ::Ellipse(get_handle1(), lpRect.left, lpRect.top,
       lpRect.right, lpRect.bottom); */

      return FillEllipse(lpRect.left, lpRect.top, lpRect.right, lpRect.bottom);

   }

   bool graphics::DrawEllipse(double x1, double y1, double x2, double y2)
   {

      //      double centerx    = (x2 + x1) / 2.0;
      //      double centery    = (y2 + y1) / 2.0;
      //
      //      double radiusx    = abs(x2 - x1) / 2.0;
      //      double radiusy    = abs(y2 - y1) / 2.0;
      //
      //      if(radiusx == 0.0 || radiusy == 0.0)
      //         return false;
      //
      //      cairo_translate(m_pdc, centerx, centery);
      //
      //      cairo_scale(m_pdc, radiusx, radiusy);
      //
      //      cairo_arc(m_pdc, 0.0, 0.0, 1.0, 0.0, 2.0 * 3.1415);
      //
      //      draw();
      //
      //      cairo_scale(m_pdc, 1.0 / radiusx, 1.0 / radiusy);
      //
      //      cairo_translate(m_pdc, -centerx,  -centery);

      CGRect rect;

      rect.origin.x     = x1;
      rect.origin.y     = y1;
      rect.size.width   = x2 - x1;
      rect.size.height  = y2 - y1;

      set(m_sppen);

      CGContextStrokeEllipseInRect(m_pdc, rect);

      return true;

   }


   bool graphics::DrawEllipse(const RECTD & lprect)
   {


      return DrawEllipse(lprect.left, lprect.top, lprect.right, lprect.bottom);


      /*return ::Ellipse(get_handle1(), lpRect.left, lpRect.top,
       lpRect.right, lpRect.bottom); */

   }


   bool graphics::FillEllipse(double x1, double y1, double x2, double y2)
   {

      //      double centerx    = (x2 + x1) / 2.0;
      //
      //      double centery    = (y2 + y1) / 2.0;
      //
      //      double radiusx    = abs(x2 - x1) / 2.0;
      //
      //      double radiusy    = abs(y2 - y1) / 2.0;
      //
      //      if(radiusx == 0.0 || radiusy == 0.0)
      //         return false;
      //
      //      cairo_translate(m_pdc, centerx, centery);
      //
      //      cairo_scale(m_pdc, radiusx, radiusy);
      //
      //      cairo_arc(m_pdc, 0.0, 0.0, 1.0, 0.0, 2.0 * 3.1415);
      //
      //      fill();
      //
      //      cairo_scale(m_pdc, 1.0 / radiusx, 1.0 / radiusy);
      //
      //      cairo_translate(m_pdc, -centerx,  -centery);

      CGRect rect;

      rect.origin.x     = x1;
      rect.origin.y     = y1;
      rect.size.width   = x2 - x1;
      rect.size.height  = y2 - y1;

      //set(m_spbrush);

      CGContextAddEllipseInRect(m_pdc, rect);

      return fill();

   }


   bool graphics::FillEllipse(const RECTD & lpRect)
   {

      /*return ::Ellipse(get_handle1(), lpRect.left, lpRect.top,
       lpRect.right, lpRect.bottom); */

      return FillEllipse(lpRect.left, lpRect.top, lpRect.right, lpRect.bottom);

   }


   bool graphics::Pie(int32_t x1, int32_t y1, int32_t x2, int32_t y2, int32_t x3, int32_t y3, int32_t x4, int32_t y4)
   {

      _throw(not_implemented(get_app()));
      return false;

      /*      ASSERT(get_handle1() != NULL);
       return ::Pie(get_handle1(), x1, y1, x2, y2, x3, y3, x4, y4) != FALSE;*/

   }

   bool graphics::Pie(const RECT & lpRect, POINT ptStart, POINT ptEnd)
   {

      _throw(not_implemented(get_app()));
      return false;


      /*      ASSERT(get_handle1() != NULL);
       return ::Pie(get_handle1(), lpRect.left, lpRect.top, lpRect.right, lpRect.bottom, ptStart.x, ptStart.y, ptEnd.x, ptEnd.y) != FALSE;*/

   }

   bool graphics::set_polygon(const POINTD * pa, count nCount)
   {
   
   CGContextMoveToPoint(m_pdc, pa[0].x, pa[0].y);
   
   for(int32_t i = 1; i < nCount; i++)
   {
      
      CGContextAddLineToPoint(m_pdc, pa[i].x, pa[i].y);
      
   }
      
      return true;
      
   }
   
   
   bool graphics::set_polygon(const POINT * pa, count nCount)
   {
      
      CGContextMoveToPoint(m_pdc, pa[0].x, pa[0].y);
      
      for(int32_t i = 1; i < nCount; i++)
      {
         
         CGContextAddLineToPoint(m_pdc, pa[i].x, pa[i].y);
         
      }
      
      return true;
      
   }

   
   bool graphics::fill_polygon(const POINTD * pa, count nCount)
   {

      if(nCount <= 0)
         return TRUE;

      CGContextBeginPath(m_pdc);
      
      set_polygon(pa, nCount);

      CGContextClosePath(m_pdc);

      fill();

      return true;

   }

   bool graphics::fill_polygon(const POINT* pa, count nCount)
   {

      if(nCount <= 0)
         return TRUE;

      CGContextBeginPath(m_pdc);

      set_polygon(pa, nCount);

      CGContextClosePath(m_pdc);

      fill();

      return true;

   }


   bool graphics::draw_polygon(const POINTD * pa, count nCount)
   {
      
      if(nCount <= 0)
         return TRUE;
      
      CGContextBeginPath(m_pdc);
      
      set_polygon(pa, nCount);
      
      CGContextClosePath(m_pdc);
      
      draw();
      
      return true;
      
   }
   
   bool graphics::draw_polygon(const POINT* pa, count nCount)
   {
      
      if(nCount <= 0)
         return TRUE;
      
      CGContextBeginPath(m_pdc);
      
      set_polygon(pa, nCount);
      
      CGContextClosePath(m_pdc);
      
      draw();
      
      return true;
      
   }


   bool graphics::polygon(LPCPOINTD pa, count nCount)
   {

      if(nCount <= 0)
         return TRUE;

      CGContextBeginPath(m_pdc);

      set_polygon(pa, nCount);

      CGContextClosePath(m_pdc);

      return fill_and_draw();

   }



   bool graphics::rectangle(LPCRECTD lpcrect)
   {

      CGRect rect;
      
      copy(rect, lpcrect);

      set(m_spbrush);

      CGContextFillRect(m_pdc, rect);

      set(m_sppen);

      CGContextStrokeRect(m_pdc, rect);

      return true;

   }
   

   bool graphics::fill_rect(LPCRECTD lpcrect)
   {

      CGRect rect;
      
      copy(rect, lpcrect);
      
      CGContextAddRect(m_pdc, rect);

      return fill();

   }


   bool graphics::round_rect(LPCRECT lpRect, LPCPOINT point)
   {

      //ASSERT(get_handle1() != NULL);
      //return ::RoundRect(get_handle1(), lpRect.left, lpRect.top, lpRect.right, lpRect.bottom, point.x, point.y) != FALSE;
      _throw(not_implemented(get_app()));
      return false;


   }

   bool graphics::PatBlt(int32_t x, int32_t y, int32_t nWidth, int32_t nHeight, DWORD dwRop)
   {

      //      ASSERT(get_handle1() != NULL);
      //      return ::PatBlt(get_handle1(), x, y, nWidth, nHeight, dwRop) != FALSE;

      _throw(not_implemented(get_app()));
      return false;


   }


   bool graphics::BitBltRaw(int32_t x, int32_t y, int32_t nWidth, int32_t nHeight, ::draw2d::graphics * pgraphicsSrc, int32_t xSrc, int32_t ySrc, DWORD dwRop)
   {
      
      synch_lock sl(m_pmutex);
      
      try
      {

         if(pgraphicsSrc == NULL)
         {
            
            return false;
            
         }
         
         synch_lock slSrc(pgraphicsSrc->m_pmutex);
         
         if(pgraphicsSrc->get_os_data() == NULL)
         {

            return false;

         }
         
         sp(::draw2d_quartz2d::dib) pdibSrc = pgraphicsSrc->m_pdibDraw2dGraphics;
         
         sp(::draw2d::graphics) pdibGraphics;
         
         if(pdibSrc.is_set())
         {
            
            pdibGraphics = pdibSrc->get_graphics();
            
         }
         else
         {
            
            TRACE("pdibSrc NULL");
            
            
         }

         CGContextRef pdcSrc = (CGContextRef) pgraphicsSrc->get_os_data();

         CGImageRef image = CGBitmapContextCreateImage(pdcSrc);

         if(image == NULL)
         {

            return false;

         }
         
         size_t SrcW = CGImageGetWidth(image);
         
         size_t SrcH = CGImageGetHeight(image);
         
         CGRect rect;

         rect.origin.x = x;
         rect.origin.y = y;
         rect.size.width = nWidth;
         rect.size.height = nHeight;

         CGRect rectSub;
         
         if(::comparison::gt(xSrc, SrcW))
         {
          
            CGImageRelease(image);
            
            return true;
            
         }

         if(::comparison::gt(ySrc, SrcH))
         {
            
            CGImageRelease(image);
            
            return true;
            
         }
         
         rectSub.origin.x = 0;
         rectSub.origin.y = 0;
         rectSub.size.width = SrcW;
         rectSub.size.height = SrcH;
         
         if(m_spregion.is_null())
         {
         
         if(xSrc == 0 && ySrc == 0 && nWidth == SrcW && nHeight == SrcH )
         {
         
            CGContextDrawImage(m_pdc, rect, image);
            
         }
         else
         {
         
            CGContextSaveGState(m_pdc);
         
            CGContextClipToRect(m_pdc, rect);

            rect.origin.x -= xSrc;
            rect.origin.y -= ySrc;
            rect.size.width = SrcW;
            rect.size.height =  SrcH;
         
            CGContextDrawImage(m_pdc, rect, image);
            
            CGContextRestoreGState(m_pdc);

         }
         }
         else
         {
            
            CGContextSaveGState(m_pdc);
            
            clip(m_spregion);
            
            if(xSrc == 0 && ySrc == 0 && nWidth == SrcW && nHeight == SrcH )
            {
               
            }
            else
            {
               CGContextClipToRect(m_pdc, rect);
               
               rect.origin.x -= xSrc;
               rect.origin.y -= ySrc;
               rect.size.width = SrcW;
               rect.size.height =  SrcH;
            }
            
            
            if(rect.origin.x < 0)
            {
               rect.size.width += rect.origin.x;
               rect.origin.x = 0;
            }
            if(rect.origin.y < 0)
            {
               rect.size.height += rect.origin.y;
               rect.origin.y = 0;
            }
            
            CGContextDrawImage(m_pdc, rect, image);
            
            CGContextRestoreGState(m_pdc);
            
         }
            
         
         CGImageRelease(image);
         
         //CGContextRestoreGState(pdcSrc);

         return true;

      }
      catch(...)
      {

         return false;

      }

   }


   bool graphics::StretchBltRaw(int32_t xDst, int32_t yDst, int32_t nDstWidth, int32_t nDstHeight, ::draw2d::graphics * pgraphicsSrc, int32_t xSrc, int32_t ySrc, int32_t nSrcWidth, int32_t nSrcHeight, DWORD dwRop)
   {

      if(nDstWidth <= 0 || nDstHeight <= 0 || nSrcWidth <= 0 || nSrcHeight <= 0)
      {
         
         return false;
         
      }


      try
      {

         if(pgraphicsSrc == NULL)
         {
            
            return false;
            
         }

         if(pgraphicsSrc->get_os_data() == NULL)
         {
          
            return false;
            
         }
         
         CGImageRef image = CGBitmapContextCreateImage((CGContextRef) pgraphicsSrc->get_os_data());

         if(image == NULL)
               return false;

         size_t SrcW = CGImageGetWidth(image);

         size_t SrcH = CGImageGetHeight(image);
         
         CGRect rect;

         rect.origin.x = xDst;
         rect.origin.y = yDst;
         rect.size.width = nDstWidth;
         rect.size.height = nDstHeight;
         
         if(xSrc == 0 && ySrc == 0 && SrcW == nSrcWidth && SrcH == nSrcHeight)
         {
            
            CGContextDrawImage(m_pdc, rect, image);
            
         }
         else
         {
         
            CGRect rectSub;

            rectSub.origin.x = xSrc;
            rectSub.origin.y = ySrc;
            rectSub.size.width = nSrcWidth;
            rectSub.size.height = nSrcHeight;
         
            CGImageRef imageSub = CGImageCreateWithImageInRect(image, rectSub);

            if(imageSub != NULL)
            {

               CGContextDrawImage(m_pdc, rect, imageSub);

               CGImageRelease(imageSub);

            }
            
         }

         CGImageRelease(image);

         return true;

      }
      catch(...)
      {

         return false;

      }

      return true;

   }


   COLORREF graphics::GetPixel(int32_t x, int32_t y)
   {

      _throw(not_implemented(get_app()));
      return false;

      //      ASSERT(get_handle1() != NULL);
      //      return ::GetPixel(get_handle1(), x, y);

   }

   
   COLORREF graphics::GetPixel(POINT point)
   {

      _throw(not_implemented(get_app()));

      return false;

   }
   

   COLORREF graphics::SetPixel(int32_t x, int32_t y, COLORREF crColor)
   {

      _throw(not_implemented(get_app()));

      return false;

   }
   

   COLORREF graphics::SetPixel(POINT point, COLORREF crColor)
   {

      _throw(not_implemented(get_app()));

      return false;

   }

   
   bool graphics::FloodFill(int32_t x, int32_t y, COLORREF crColor)
   {

      _throw(not_implemented(get_app()));

      return false;

   }

   
   bool graphics::ExtFloodFill(int32_t x, int32_t y, COLORREF crColor, UINT nFillType)
   {

      _throw(not_implemented(get_app()));
      
      return false;

   }

   
   bool graphics::BitBltAlphaBlend(int32_t x, int32_t y, int32_t nWidth, int32_t nHeight, ::draw2d::graphics * pgraphicsSrc, int32_t xSrc, int32_t ySrc, uint32_t dwRop)
   {
      
      if (m_pdibAlphaBlend != NULL)
      {
         
         rect rectIntersect(m_ptAlphaBlend, m_pdibAlphaBlend->size());
         
         rect rectBlt(point((int64_t)x, (int64_t)y), size(nWidth, nHeight));
         
         if (rectIntersect.intersect(rectIntersect, rectBlt))
         {
            
            ::draw2d::dib_sp dib1(allocer());
            
            dib1->create(rectBlt.get_size());
               
            dib1->get_graphics()->set_alpha_mode(::draw2d::alpha_mode_set);
               
            if (!dib1->from(null_point(), pgraphicsSrc, point(xSrc, ySrc), rectBlt.get_size()))
            {
               
               return false;
               
            }
            
            dib1->blend(point(0, 0), m_pdibAlphaBlend, point((int)MAX(0, x - m_ptAlphaBlend.x), (int)MAX(0, y - m_ptAlphaBlend.y)), rectBlt.get_size());
            
            set_alpha_mode(::draw2d::alpha_mode_blend);
               
            BitBltRaw(x, y, nWidth, nHeight, dib1->get_graphics(), 0, 0, dwRop);
               
            return true;
            
         }
         
      }
      
      return false;
      
   }
   

   // true blend
   // COLOR_DEST = SRC_ALPHA * COLOR_SRC  + (1 - SRC_ALPHA) * COLOR_DST

   // double blend
   //// COLOR_DEST = SRC_ALPHA * BLEND_ALPHA * COLOR_SRC  + (1 - SRC_ALPHA * BLEND_ALPHA) * COLOR_DST

   bool graphics::text_out(int32_t x, int32_t y, const string & str)
   {

      if (m_pdibAlphaBlend != NULL)
      {
         
         rect rectIntersect(m_ptAlphaBlend, m_pdibAlphaBlend->size());
         
         rect rectText(point((int64_t)x, (int64_t)y), ::size(GetTextExtent(str)));
         
         if (rectIntersect.intersect(rectIntersect, rectText))
         {
            
            rectText.bottom = rectText.top + rectText.height() * 2;
            
            ::draw2d::dib_sp dib1(allocer());
            
            dib1->create(rectText.get_size());
            dib1->Fill(0, 0, 0, 0);
            dib1->get_graphics()->SelectObject(get_current_font());
            dib1->get_graphics()->SelectObject(get_current_brush());
            dib1->get_graphics()->text_out(0, 0, str);
            
            dib1->blend(null_point(), m_pdibAlphaBlend, point((int)MAX(0, x - m_ptAlphaBlend.x), (int)MAX(0, y - m_ptAlphaBlend.y)), rectText.get_size());
               
            set_alpha_mode(::draw2d::alpha_mode_blend);
               
            BitBltRaw((int)x, (int)y, rectText.width(), rectText.height(), dib1->get_graphics(), 0, 0, SRCCOPY);
            
         }
         
      }
      
      return text_out(x, y, str, (int32_t) str.get_length());

   }
   

   bool graphics::text_out(double x, double y, const string & str)
   {
      
      if(m_pdibAlphaBlend != NULL)
      {

         //   return TRUE;
            rect rectIntersect(m_ptAlphaBlend, m_pdibAlphaBlend->size());
            rect rectText(point((int64_t) x, (int64_t) y), ::size(GetTextExtent(str)));
            if(rectIntersect.intersect(rectIntersect, rectText))
            {
               
               return true;
               
//               ::draw2d::dib_sp dib0(allocer());
//               dib0->create(rectText.size());
//               dib0->get_graphics()->set_text_color(RGB(255, 255, 255));
//               dib0->get_graphics()->SelectObject(get_current_font());
//
//               dib0->get_graphics()->text_out(0, 0, str);
//
//               dib0->ToAlpha(0);
//               ::draw2d::dib_sp dib1(allocer());
//               dib1->create(rectText.size());
//               dib1->get_graphics()->set_text_color(m_spbrush->m_cr);
//               dib1->get_graphics()->SelectObject(get_current_font());
//
//               dib1->get_graphics()->text_out(0, 0, str);
//
//               dib1->channel_from(visual::rgba::channel_alpha, dib0);
//               ::draw2d::dib_sp dib2(allocer());
//               dib2->create(rectText.size());
//               dib2->Fill(255, 0, 0, 0);
//               dib2->from(point((int64_t) MAX(0, m_ptAlphaBlend.x - x), (int64_t) MAX(0, m_ptAlphaBlend.y - y)),
//                          m_pdibAlphaBlend->get_graphics(), point((int64_t) MAX(0, x - m_ptAlphaBlend.x), (int64_t) MAX(0, y - m_ptAlphaBlend.y)), rectText.size());
//               dib1->channel_multiply(visual::rgba::channel_alpha, dib2);
//               /*::draw2d::dib_sp dib3(get_app());
//                dib1->mult_alpha(dib3);*/
//
//               keep < ::draw2d::dib * > keep(&m_pdibAlphaBlend, NULL, m_pdibAlphaBlend, true);
//
//               return BitBlt(point((int64_t) x, (int64_t) y), rectText.size(), dib1->get_graphics(), null_point());

               /*BLENDFUNCTION bf;
                bf.BlendOp     = AC_SRC_OVER;
                bf.BlendFlags  = 0;
                bf.SourceConstantAlpha = 0xFF;
                bf.AlphaFormat = AC_SRC_ALPHA;
                return ::AlphaBlend(get_handle1(), x, y,
                rectText.width(), rectText.height(), WIN_HDC(dib1->get_graphics()), 0, 0, rectText.width(),
                rectText.height(), bf) != FALSE; */
            }
      }

      //ASSERT(get_handle1() != NULL);
      //wstring wstr = ::str::international::utf8_to_unicode(str);
      return text_out(x, y, str, (int32_t) str.get_length());

   } // call virtual
   

   bool graphics::ExtTextOut(int32_t x, int32_t y, UINT nOptions, const RECT & lpRect, const char * lpszString, UINT nCount, LPINT lpDxWidths)
   {

      _throw(not_implemented(get_app()));
      return false;

      //      ASSERT(get_handle1() != NULL);
      //      return ::ExtTextOut(get_handle1(), x, y, nOptions, lpRect, lpszString, nCount, lpDxWidths) != FALSE;

   }

   bool graphics::ExtTextOut(int32_t x, int32_t y, UINT nOptions, const RECT & lpRect, const string & str, LPINT lpDxWidths)
   {

      _throw(not_implemented(get_app()));
      return false;

      //      ASSERT(get_handle1() != NULL);
      //      return ::ExtTextOut(get_handle1(), x, y, nOptions, lpRect, str, (UINT)str.get_length(), lpDxWidths) != FALSE;

   }

   size graphics::TabbedTextOut(int32_t x, int32_t y, const char * lpszString, int32_t nCount, int32_t nTabPositions, LPINT lpnTabStopPositions, int32_t nTabOrigin)
   {

      _throw(not_implemented(get_app()));
      return ::size(0, 0);

      //      ASSERT(get_handle1() != NULL);
      //      return ::TabbedTextOut(get_handle1(), x, y, lpszString, nCount, nTabPositions, lpnTabStopPositions, nTabOrigin);

   }

   size graphics::TabbedTextOut(int32_t x, int32_t y, const string & str, int32_t nTabPositions, LPINT lpnTabStopPositions, int32_t nTabOrigin)
   {

      _throw(not_implemented(get_app()));
      return ::size(0, 0);

      //      ASSERT(get_handle1() != NULL);
      //      return ::TabbedTextOut(get_handle1(), x, y, str, (int32_t)str.get_length(), nTabPositions, lpnTabStopPositions, nTabOrigin);

   }


   size graphics::GetTabbedTextExtent(const char * lpszString, strsize nCount, int32_t nTabPositions, LPINT lpnTabStopPositions)
   {

      _throw(not_implemented(get_app()));
      return ::size(0, 0);

      //      ASSERT(get_handle2() != NULL);
      //      return ::GetTabbedTextExtent(get_handle2(), lpszString, (int32_t) nCount, nTabPositions, lpnTabStopPositions);

   }

   size graphics::GetTabbedTextExtent(const string & str, int32_t nTabPositions, LPINT lpnTabStopPositions)
   {

      _throw(not_implemented(get_app()));
      return ::size(0, 0);

      //      ASSERT(get_handle2() != NULL);
      //      return ::GetTabbedTextExtent(get_handle2(), str, (int32_t) str.get_length(), nTabPositions, lpnTabStopPositions);

   }

   size graphics::GetOutputTabbedTextExtent(const char * lpszString, strsize nCount, int32_t nTabPositions, LPINT lpnTabStopPositions)
   {

      _throw(not_implemented(get_app()));
      return ::size(0, 0);

      //      ASSERT(get_handle1() != NULL);
      //      return ::GetTabbedTextExtent(get_handle1(), lpszString, (int32_t) nCount, nTabPositions, lpnTabStopPositions);

   }

   size graphics::GetOutputTabbedTextExtent(const string & str, int32_t nTabPositions, LPINT lpnTabStopPositions)
   {

      _throw(not_implemented(get_app()));
      return ::size(0, 0);

      //      ASSERT(get_handle1() != NULL);
      //      return ::GetTabbedTextExtent(get_handle1(), str, (int32_t) str.get_length(), nTabPositions, lpnTabStopPositions);

   }

   bool graphics::GrayString(::draw2d::brush* pBrush, bool (CALLBACK* lpfnOutput)(HDC, LPARAM, int32_t), LPARAM lpData, int32_t nCount,int32_t x, int32_t y, int32_t nWidth, int32_t nHeight)
   {

      _throw(not_implemented(get_app()));
      return false;

      //      ASSERT(get_handle1() != NULL);
      //      return ::GrayString(get_handle1(), (HBRUSH)pBrush->get_os_data(),(GRAYSTRINGPROC)lpfnOutput, lpData, nCount, x, y, nWidth, nHeight) != FALSE;

   }

   UINT graphics::GetTextAlign()
   {

      _throw(not_implemented(get_app()));
      return 0;

      //      ASSERT(get_handle2() != NULL);
      //      return ::GetTextAlign(get_handle2());

   }

   int32_t graphics::GetTextFace(int32_t nCount, LPTSTR lpszFacename)
   {

      _throw(not_implemented(get_app()));
      return 0;

      //      ASSERT(get_handle2() != NULL);
      //      return ::GetTextFace(get_handle2(), nCount, lpszFacename);

   }

   int32_t graphics::GetTextFace(string & rString)
   {

      _throw(not_implemented(get_app()));
      return 0;

   }

   bool graphics::get_text_metrics(::draw2d::text_metric * lpMetrics)
   {

      string str(L"123AWZwmc123AWZwmcpQg");

      CGFloat ascent, descent, leading, width;
      
      const_cast < graphics * > (this)->internal_show_text(0, 0, 0, DT_TOPLEFT, str, (int) str.get_length(), kCGTextInvisible, false, &ascent, &descent, &leading, &width);

      lpMetrics->tmAscent              = ascent;
      lpMetrics->tmDescent             = descent;
      lpMetrics->tmHeight              = ascent + descent + leading;

      lpMetrics->tmInternalLeading     = leading;
      lpMetrics->tmExternalLeading     = leading;

      lpMetrics->tmAveCharWidth        = (LONG) (width * (m_spfont.is_null() ? 1.0 : m_spfont->m_dFontWidth) / (double) str.get_length());

      return true;

   }


    bool graphics::get_output_text_metrics(::draw2d::text_metric * lpMetrics)
   {

      _throw(not_implemented(get_app()));
      return false;

      //      ASSERT(get_handle1() != NULL);
      //      return ::GetTextMetrics(get_handle1(), lpMetrics) != FALSE;

   }


   int32_t graphics::GetTextCharacterExtra()
   {

      _throw(not_implemented(get_app()));
      return 0;

      //      ASSERT(get_handle2() != NULL);
      //      return ::GetTextCharacterExtra(get_handle2());

   }

   bool graphics::GetCharWidth(UINT nFirstChar, UINT nLastChar, LPINT lpBuffer)
   {

      _throw(not_implemented(get_app()));
      return false;

      //      ASSERT(get_handle2() != NULL);
      //      return ::GetCharWidth(get_handle2(), nFirstChar, nLastChar, lpBuffer) != FALSE;

   }

   bool graphics::GetOutputCharWidth(UINT nFirstChar, UINT nLastChar, LPINT lpBuffer)
   {

      _throw(not_implemented(get_app()));
      return false;

      //      ASSERT(get_handle1() != NULL);
      //      return ::GetCharWidth(get_handle1(), nFirstChar, nLastChar, lpBuffer) != FALSE;

   }


   DWORD graphics::GetFontLanguageInfo()
   {

      _throw(not_implemented(get_app()));
      
      return 0;

   }
   

   /*

    DWORD graphics::GetCharacterPlacement(const char * lpString, int32_t nCount, int32_t nMaxExtent, LPGCP_RESULTS lpResults, DWORD dwFlags)
    {

    _throw(not_implemented(get_app()));
    return 0;

    //      ASSERT(get_handle1() != NULL);
    //      return ::GetCharacterPlacement(get_handle1(), lpString, nCount, nMaxExtent, lpResults, dwFlags);

    }

    DWORD graphics::GetCharacterPlacement(string & str, int32_t nMaxExtent, LPGCP_RESULTS lpResults, DWORD dwFlags)
    {

    _throw(not_implemented(get_app()));
    return 0;

    //      ASSERT(get_handle1() != NULL);
    //      return ::GetCharacterPlacement(get_handle1(), (const char *)str, (int32_t) str.get_length(), nMaxExtent, lpResults, dwFlags);

    }

    */

   size graphics::GetAspectRatioFilter()
   {

      _throw(not_implemented(get_app()));
      return size(0, 0);

      //      ASSERT(get_handle2() != NULL);
      //      SIZE size;
      //      VERIFY(::GetAspectRatioFilterEx(get_handle2(), &size));
      //      return size;

   }


   bool graphics::ScrollDC(int32_t dx, int32_t dy, const RECT & lpRectScroll, const RECT & lpRectClip, ::draw2d::region* pRgnUpdate, LPRECT lpRectUpdate)
   {

      _throw(not_implemented(get_app()));
      return false;

      //      ASSERT(get_handle1() != NULL);
      //      return ::ScrollDC(get_handle1(), dx, dy, lpRectScroll, lpRectClip, (HRGN)pRgnUpdate->get_os_data(), lpRectUpdate) != FALSE;

   }

   // Printer Escape Functions
   int32_t graphics::Escape(int32_t nEscape, int32_t nCount, const char * lpszInData, LPVOID lpOutData)
   {

      _throw(not_implemented(get_app()));
      return 0;

      //      ASSERT(get_handle1() != NULL);
      //      return ::Escape(get_handle1(), nEscape, nCount, lpszInData, lpOutData);

   }

   // graphics 3.1 Specific functions
   UINT graphics::SetBoundsRect(const RECT & lpRectBounds, UINT flags)
   {

      _throw(not_implemented(get_app()));
      return 0;

      //      ASSERT(get_handle1() != NULL);
      //      return ::SetBoundsRect(get_handle1(), lpRectBounds, flags);

   }

   UINT graphics::GetBoundsRect(LPRECT lpRectBounds, UINT flags)
   {

      _throw(not_implemented(get_app()));
      return 0;

   }


   DWORD graphics::GetFontData(DWORD dwTable, DWORD dwOffset, LPVOID lpData, DWORD cbData)
   {

      _throw(not_implemented(get_app()));

      return 0;

   }


   int32_t graphics::StartPage()
   {

      _throw(not_implemented(get_app()));
   
      return 0;

   }

   
   int32_t graphics::EndPage()
   {

      _throw(not_implemented(get_app()));
      
      return 0;

   }


   int32_t graphics::SetAbortProc(bool (CALLBACK* lpfn)(HDC, int32_t))
   {

      _throw(not_implemented(get_app()));
      return 0;

      //      ASSERT(get_handle1() != NULL);
      //      return ::SetAbortProc(get_handle1(), (ABORTPROC)lpfn);

   }

   int32_t graphics::AbortDoc()
   {

      _throw(not_implemented(get_app()));
      return 0;

      //      ASSERT(get_handle1() != NULL);
      //      return ::AbortDoc(get_handle1());

   }

   int32_t graphics::EndDoc()
   {

      _throw(not_implemented(get_app()));
      return 0;

      //      ASSERT(get_handle1() != NULL);
      //      return ::EndDoc(get_handle1());

   }

   bool graphics::MaskBlt(int32_t x, int32_t y, int32_t nWidth, int32_t nHeight, ::draw2d::graphics * pgraphicsSrc, int32_t xSrc, int32_t ySrc, ::draw2d::bitmap& maskBitmap, int32_t xMask, int32_t yMask, DWORD dwRop)
   {

      _throw(not_implemented(get_app()));
      return false;

      //      ASSERT(get_handle1() != NULL);
      //      return ::MaskBlt(get_handle1(), x, y, nWidth, nHeight, WIN_HDC(pgraphicsSrc), xSrc, ySrc,  (HBITMAP)maskBitmap.get_os_data(), xMask, yMask, dwRop) != FALSE;

   }

   bool graphics::PlgBlt(LPPOINT lpPoint, ::draw2d::graphics * pgraphicsSrc, int32_t xSrc, int32_t ySrc, int32_t nWidth, int32_t nHeight, ::draw2d::bitmap& maskBitmap, int32_t xMask, int32_t yMask)
   {

      _throw(not_implemented(get_app()));
      return false;

      //      ASSERT(get_handle1() != NULL);
      //      return ::PlgBlt(get_handle1(), lpPoint, WIN_HDC(pgraphicsSrc), xSrc, ySrc, nWidth, nHeight, (HBITMAP)maskBitmap.get_os_data(), xMask, yMask) != FALSE;

   }

   bool graphics::SetPixelV(int32_t x, int32_t y, COLORREF crColor)
   {

      _throw(not_implemented(get_app()));
      return false;

      //      ASSERT(get_handle1() != NULL);
      //      return ::SetPixelV(get_handle1(), x, y, crColor) != FALSE;

   }

   bool graphics::SetPixelV(POINT point, COLORREF crColor)
   {

      _throw(not_implemented(get_app()));
      return false;

      //      ASSERT(get_handle1() != NULL);
      //      return ::SetPixelV(get_handle1(), point.x, point.y, crColor) != FALSE;

   }

   bool graphics::AngleArc(int32_t x, int32_t y, int32_t nRadius, float fStartAngle, float fSweepAngle)
   {

      _throw(not_implemented(get_app()));
      return false;

      //      ASSERT(get_handle1() != NULL);
      //      return ::AngleArc(get_handle1(), x, y, nRadius, fStartAngle, fSweepAngle) != FALSE;

   }

   bool graphics::ArcTo(const RECT & lpRect, POINT ptStart, POINT ptEnd)
   {

      _throw(not_implemented(get_app()));
      return false;

      //      ASSERT(get_handle1() != NULL);
      //      return ArcTo(lpRect.left, lpRect.top, lpRect.right, lpRect.bottom, ptStart.x, ptStart.y, ptEnd.x, ptEnd.y);

   }

   int32_t graphics::GetArcDirection()
   {

      _throw(not_implemented(get_app()));
      return 0;

      //      ASSERT(get_handle2() != NULL);
      //      return ::GetArcDirection(get_handle2());

   }

   bool graphics::PolyPolyline(const POINT* lpPoints, const DWORD* lpPolyPoints, int32_t nCount)
   {

      _throw(not_implemented(get_app()));
      return false;

      //      ASSERT(get_handle1() != NULL);
      //      return ::PolyPolyline(get_handle1(), lpPoints, lpPolyPoints, nCount) != FALSE;

   }

   /*

    bool graphics::GetColorAdjustment(LPCOLORADJUSTMENT lpColorAdjust)
    {

    _throw(not_implemented(get_app()));
    return false;

    //      ASSERT(get_handle2() != NULL);
    //      return ::GetColorAdjustment(get_handle2(), lpColorAdjust) != FALSE;

    }

    */

   ::draw2d::pen_sp graphics::get_current_pen()
   {

      return m_sppen;

   }

   ::draw2d::brush_sp graphics::get_current_brush()
   {

      return m_spbrush;

   }

   ::draw2d::palette_sp graphics::get_current_palette()
   {

      return (::draw2d::palette *)NULL;

   }

   
   ::draw2d::font_sp graphics::get_current_font()
   {

      return m_spfont;

   }

   
   ::draw2d::bitmap_sp graphics::get_current_bitmap()
   {

      return m_spbitmap;

   }

   bool graphics::PolyBezier(const POINT* lpPoints, int32_t nCount)
   {

      _throw(not_implemented(get_app()));
      return false;

      //      ASSERT(get_handle1() != NULL);
      //      return ::PolyBezier(get_handle1(), lpPoints, nCount) != FALSE;

   }

   int32_t graphics::DrawEscape(int32_t nEscape, int32_t nInputSize, const char * lpszInputData)
   {

      _throw(not_implemented(get_app()));
      return 0;

      //      ASSERT(get_handle1() != NULL);
      //      return ::DrawEscape(get_handle1(), nEscape, nInputSize, lpszInputData);

   }

   int32_t graphics::Escape(int32_t nEscape, int32_t nInputSize, const char * lpszInputData,  int32_t nOutputSize, char * lpszOutputData)
   {

      _throw(not_implemented(get_app()));
      return 0;

      //       ASSERT(get_handle1() != NULL);
      //       return ::ExtEscape(get_handle1(), nEscape, nInputSize, lpszInputData, nOutputSize, lpszOutputData);

   }

   /*

    bool graphics::GetCharABCWidths(UINT nFirstChar, UINT nLastChar, LPABCFLOAT lpABCF)
    {

    _throw(not_implemented(get_app()));
    return false;

    //      ASSERT(get_handle2() != NULL);
    //      return ::GetCharABCWidthsFloat(get_handle2(), nFirstChar, nLastChar, lpABCF) != FALSE;

    }

    */

   bool graphics::GetCharWidth(UINT nFirstChar, UINT nLastChar, float* lpFloatBuffer)
   {

      _throw(not_implemented(get_app()));
      return false;

      //      ASSERT(get_handle2() != NULL);
      //      return ::GetCharWidthFloat(get_handle2(), nFirstChar, nLastChar, lpFloatBuffer) != FALSE;

   }

   bool graphics::abort_path()
   {

      _throw(not_implemented(get_app()));
      return false;

      /*
       if(m_ppath != NULL)
       {
       delete m_ppath;
       m_ppath = NULL;
       }
       return true;
       */

   }

   bool graphics::begin_path()
   {

      _throw(not_implemented(get_app()));
      return false;

      /*
       if(m_ppath != NULL)
       delete m_ppath;

       m_ppath = new Gdiplus::GraphicsPath;

       return m_ppath != NULL;
       */

   }

   bool graphics::close_figure()   {

      _throw(not_implemented(get_app()));
      return false;

      /*
       ASSERT(m_ppath != NULL);
       return m_ppath->CloseFigure() == Gdiplus::Status::Ok;
       */
   }

   bool graphics::end_path()   {

      _throw(not_implemented(get_app()));
      return false;

      /*
       if(m_ppath == NULL)
       return FALSE;

       m_ppathPaint   = m_ppath;
       m_ppath        = NULL;

       return true;
       */
   }

   bool graphics::fill_path()   {

      _throw(not_implemented(get_app()));
      return false;

      //      return m_pgraphics->FillPath(gdiplus_brush(), m_ppath) == Gdiplus::Status::Ok;

   }

   bool graphics::flatten_path()   {

      _throw(not_implemented(get_app()));
      return false;

      //      return m_ppath->Flatten() == Gdiplus::Status::Ok;

   }

   float graphics::GetMiterLimit()
   {

      _throw(not_implemented(get_app()));
      return 0.f;

      //      ASSERT(get_handle1() != NULL);
      //      float fMiterLimit;
      //      VERIFY(::GetMiterLimit(get_handle1(), &fMiterLimit));
      //      return fMiterLimit;

   }

   int32_t graphics::GetPath(LPPOINT lpPoints, LPBYTE lpTypes, int32_t nCount)
   {

      _throw(not_implemented(get_app()));
      return 0;

      //      ASSERT(get_handle1() != NULL);
      //      return ::GetPath(get_handle1(), lpPoints, lpTypes, nCount);

   }

   bool graphics::SetMiterLimit(float fMiterLimit)
   {

      _throw(not_implemented(get_app()));
      return false;

      //      ASSERT(get_handle1() != NULL);
      //      return ::SetMiterLimit(get_handle1(), fMiterLimit, NULL) != FALSE;

   }

   bool graphics::stroke_and_fill_path()   {

      _throw(not_implemented(get_app()));
      return false;

      //      bool bOk1 = m_pgraphics->FillPath(gdiplus_brush(), m_ppathPaint) == Gdiplus::Status::Ok;

      //      bool bOk2 = m_pgraphics->DrawPath(gdiplus_pen(), m_ppathPaint) == Gdiplus::Status::Ok;

      //      return bOk1 && bOk2;

   }

   bool graphics::stroke_path()
   {

      _throw(not_implemented(get_app()));
      return false;

      //      return m_pgraphics->DrawPath(gdiplus_pen(), m_ppathPaint) == Gdiplus::Status::Ok;

   }

   bool graphics::widen_path()   {

      _throw(not_implemented(get_app()));
      return false;

      //      return m_ppath->Widen(gdiplus_pen()) == Gdiplus::Status::Ok;

   }


   bool graphics::draw_path(::draw2d::path * ppath)
   {

      if(!set(ppath))
         return false;

      draw();

      draw_inline(ppath, m_sppen);

      return true;

   }

   bool graphics::fill_path(::draw2d::path * ppath)
   {

      if(!set(ppath))
         return false;

      fill();

      fill_inline(ppath, m_spbrush);

      return true;

   }

   bool graphics::draw_path(::draw2d::path * ppath, ::draw2d::pen * ppen)
   {

      if(!set(ppath))
         return false;

      draw(ppen);

      draw_inline(ppath, ppen);

      return true;
   }


   bool graphics::fill_path(::draw2d::path * ppath, ::draw2d::brush * pbrush)
   {

      if(!set(ppath))
         return false;



      fill(pbrush);

      fill_inline(ppath, pbrush);

      return true;

   }


   bool graphics::draw_inline_path(::draw2d::path * ppath, ::draw2d::pen * ppen)
   {

      if(!set(ppath))
         return false;

      return draw(ppen);

   }


   bool graphics::fill_inline_path(::draw2d::path * ppath, ::draw2d::brush * pbrush)
   {

      if(!set(ppath))
         return false;

      return fill(pbrush);

   }


   bool graphics::AddMetaFileComment(UINT nDataSize, const BYTE* pCommentData)
   {

      _throw(not_implemented(get_app()));
      return false;

      //      ASSERT(get_handle1() != NULL);
      //      return ::GdiComment(get_handle1(), nDataSize, pCommentData) != FALSE;

   }


   /*bool CALLBACK metaCallback(
    EmfPlusRecordType recordType,
    uint32_t flags,
    uint32_t dataSize,
    const unsigned char* pStr,
    void* callbackData)
    {
    // Play only EmfPlusRecordTypeFillEllipse records.
    if (recordType == EmfPlusRecordTypeFillEllipse)
    {
    // Explicitly cast callbackData as a metafile pointer, and use it to call
    // the PlayRecord method.
    static_cast < Metafile* > (callbackData)->PlayRecord(recordType, flags, dataSize, pStr);
    }
    return TRUE;
    }

    VOID Example_EnumerateMetafile9(HDC hdc)
    {
    Graphics graphics(hdc);
    // Create a Metafile object from an existing disk metafile.
    Metafile* pMeta = new Metafile(L"SampleMetafile.emf", hdc);
    {
    // Fill a rectangle and an ellipse in pMeta.
    Graphics metaGraphics(pMeta);
    metaGraphics.FillRectangle(&SolidBrush(Color(255, 0, 0, 0)), 0, 0, 100, 100);
    metaGraphics.FillEllipse(&SolidBrush(Color(255, 255, 0, 0)), 100, 0, 200, 100);
    }
    // Enumerate pMeta to the destination rectangle, passing pMeta as the callback data.
    graphics.EnumerateMetafile(
    pMeta,
    Rect(0, 0, 300, 50),
    metaCallback,
    pMeta);
    // Draw pMeta as an image.
    graphics.DrawImage(pMeta, Point(0, 150));
    delete pMeta;;
    }*/

   bool graphics::PlayMetaFile(HENHMETAFILE hEnhMF, const RECT & lpBounds)
   {

      _throw(not_implemented(get_app()));
      return false;


      /*      Gdiplus::RectF rect((Gdiplus::REAL) lpBounds->left, (Gdiplus::REAL) lpBounds->top, (Gdiplus::REAL) width(lpBounds), (Gdiplus::REAL) height(lpBounds));

       Gdiplus::Metafile* pMeta = new Gdiplus::Metafile(hEnhMF, false);

       //m_pgraphcis->EnumerateMetafile(pMeta, rect, metaCallback, PMETAHEADER);

       bool bOk = m_pgraphics->DrawImage(pMeta, rect) == Gdiplus::Status::Ok;

       delete pMeta;

       return bOk ? TRUE : FALSE;*/
      //return ::PlayEnhMetaFile(get_handle1(), hEnhMF, lpBounds);

   }

   // true blend
   // COLOR_DEST = SRC_ALPHA * COLOR_SRC  + (1 - SRC_ALPHA) * COLOR_DST

   // double blend
   // COLOR_DEST = SRC_ALPHA * BLEND_ALPHA * COLOR_SRC  + (1 - SRC_ALPHA * BLEND_ALPHA) * COLOR_DST

   // Thank you
   // Jiju George T
   // Web Developer
   // India India
   // Member

   bool graphics::alpha_blendRaw(int32_t xDst, int32_t yDst, int32_t nDstWidth, int32_t nDstHeight, ::draw2d::graphics * pgraphicsSrc, int32_t xSrc, int32_t ySrc, int32_t nSrcWidth, int32_t nSrcHeight, double dRate)
   {

//      if(m_pdibAlphaBlend != NULL)
//      {
//         
//         
//         rect rectIntersect(m_ptAlphaBlend, m_pdibAlphaBlend->size());
//         
//         
//         ::draw2d::dib * pdibWork = NULL;
//         ::draw2d::dib * pdibWork2 = NULL;
//         //         ::draw2d::dib * pdibWork3 = NULL;
//         ::draw2d::dib * pdibWork4 = NULL;
//         
//         
//         class point ptSrc(xSrc, ySrc);
//         class point ptDest(xDst, yDst);
//         class size size(nDstWidth, nDstHeight);
//         
//         
//         
//         ::draw2d::dib_sp spdib;
//         if(pdibWork == NULL)
//         {
//            spdib.alloc(allocer());
//            pdibWork = spdib;
//         }
//         if(pdibWork == NULL)
//            return false;
//         if(!pdibWork->create(size))
//            return false;
//         if(!pdibWork->from(null_point(), pgraphicsSrc, ptSrc, size))
//            return false;
//         
//         
//         
//         
//         ::draw2d::dib_sp spdib2;
//         if(pdibWork2 == NULL)
//         {
//            spdib2.alloc(allocer());
//            pdibWork2 = spdib2;
//         }
//         
//         
//         ::draw2d::dib_sp spdib4;
//         if(pdibWork4 == NULL)
//         {
//            spdib4.alloc(allocer());
//            pdibWork4 = spdib4;
//         }
//         if(pdibWork4 == NULL)
//            return false;
//         if(!pdibWork4->create(size))
//            return false;
//         
//         
//         pdibWork4->Fill(255, 0, 0, 0);
//         
//         pdibWork4->from(point(MAX(0, m_ptAlphaBlend.x - xDst), MAX(0, m_ptAlphaBlend.y - yDst)),
//                         m_pdibAlphaBlend->get_graphics(), point(MAX(0, xDst - m_ptAlphaBlend.x), MAX(0, yDst - m_ptAlphaBlend.y)), size);
//         
//         pdibWork->channel_multiply(visual::rgba::channel_alpha, pdibWork4);
//         
//         
//         ::keep < ::draw2d::dib * > keep2(&m_pdibAlphaBlend, NULL, m_pdibAlphaBlend, true);
//         
//         
//         return BitBlt(ptDest.x, ptDest.y, size.cx, size.cy, pdibWork->get_graphics(), ptSrc.x, ptSrc.y, SRCCOPY);
//         
//         
//      }


      CGContextSetAlpha(m_pdc, (CGFloat) dRate);
      StretchBltRaw(xDst, yDst, nDstWidth, nDstHeight, pgraphicsSrc, xSrc, ySrc, nSrcWidth, nSrcHeight, SRCCOPY);
      CGContextSetAlpha(m_pdc, (CGFloat) 1.f);

      return true;

   }


   /*bool graphics::alpha_blend(int32_t xDest, int32_t yDest, int32_t nDestWidth, int32_t nDestHeight,
    ::draw2d::graphics * pgraphicsSrc, int32_t xSrc, int32_t ySrc, int32_t nSrcWidth, int32_t nSrcHeight, BLENDFUNCTION blend)
    {

    _throw(not_implemented(get_app()));
    //if(get_handle1() == NULL)
    // return false;


    if(m_pdibAlphaBlend != NULL)
    {


    rect rectIntersect(m_ptAlphaBlend, m_pdibAlphaBlend->size());


    ::draw2d::dib * pdibWork = NULL;
    ::draw2d::dib * pdibWork2 = NULL;
    //         ::draw2d::dib * pdibWork3 = NULL;
    ::draw2d::dib * pdibWork4 = NULL;


    class point ptSrc(xSrc, ySrc);
    class point ptDest(xDest, yDest);
    class size size(nDestWidth, nDestHeight);



    ::draw2d::dib_sp spdib;
    if(pdibWork == NULL)
    {
    spdib.create(get_app());
    pdibWork = spdib;
    }
    if(pdibWork == NULL)
    return false;
    if(!pdibWork->create(size))
    return false;
    if(!pdibWork->from(null_point(), pgraphicsSrc, ptSrc, size))
    return false;




    ::draw2d::dib_sp spdib2;
    if(pdibWork2 == NULL)
    {
    spdib2.create(get_app());
    pdibWork2 = spdib2;
    }


    ::draw2d::dib_sp spdib4;
    if(pdibWork4 == NULL)
    {
    spdib4.create(get_app());
    pdibWork4 = spdib4;
    }
    if(pdibWork4 == NULL)
    return false;
    if(!pdibWork4->create(size))
    return false;


    pdibWork4->Fill(255, 0, 0, 0);

    pdibWork4->from(point(max(0, m_ptAlphaBlend.x - xDest), max(0, m_ptAlphaBlend.y - yDest)),
    m_pdibAlphaBlend->get_graphics(), point(max(0, xDest - m_ptAlphaBlend.x), max(0, yDest - m_ptAlphaBlend.y)), size);

    pdibWork->channel_multiply(visual::rgba::channel_alpha, pdibWork4);


    keeper < ::draw2d::dib * > keep(&m_pdibAlphaBlend, NULL, m_pdibAlphaBlend, true);


    return System.imaging().true_blend(this, ptDest, size, pdibWork->get_graphics(), ptSrc);


    }

    return ::AlphaBlend(get_handle1(), xDest, yDest,
    nDestWidth, nDestHeight, WIN_HDC(pgraphicsSrc), xSrc, ySrc, nSrcWidth,
    nSrcHeight, blend) != FALSE;
    }*/


   bool graphics::TransparentBlt(int32_t xDest, int32_t yDest, int32_t nDestWidth, int32_t nDestHeight, ::draw2d::graphics * pgraphicsSrc, int32_t xSrc, int32_t ySrc, int32_t nSrcWidth, int32_t nSrcHeight, UINT crTransparent)
   {

      _throw(not_implemented(get_app()));
      return false;

      //      ASSERT(get_handle1() != NULL);
      //      return ::TransparentBlt(get_handle1(), xDest, yDest, nDestWidth, nDestHeight, WIN_HDC(pgraphicsSrc), xSrc, ySrc, nSrcWidth, nSrcHeight, crTransparent) != FALSE;

   }

   bool graphics::GradientFill(TRIVERTEX* pVertices, WINULONG nVertices, void * pMesh, WINULONG nMeshElements, DWORD dwMode)
   {

      _throw(not_implemented(get_app()));
      return false;

   }


#define HIMETRIC_INCH   2540    // HIMETRIC units per inch

   void graphics::DPtoHIMETRIC(LPSIZE lpSize)
   {

      _throw(not_implemented(get_app()));

      /*
       ASSERT(__is_valid_address(lpSize, sizeof(SIZE)));

       int32_t nMapMode;
       if (this != NULL && (nMapMode = GetMapMode()) < MM_ISOTROPIC && nMapMode != MM_TEXT)
       {
       // when using a constrained ::collection::map mode, ::collection::map against physical inch
       ((::draw2d::graphics *)this)->SetMapMode(MM_HIMETRIC);
       DPtoLP(lpSize);
       ((::draw2d::graphics *)this)->SetMapMode(nMapMode);
       }
       else
       {
       // ::collection::map against logical inch for non-constrained mapping modes
       int32_t cxPerInch, cyPerInch;
       if (this != NULL)
       {
       ASSERT_VALID(this);
       ASSERT(get_handle1() != NULL);  // no HDC attached or created?
       cxPerInch = GetDeviceCaps(LOGPIXELSX);
       cyPerInch = GetDeviceCaps(LOGPIXELSY);
       }
       else
       {
       //            cxPerInch = afxData.cxPixelsPerInch;
       //          cyPerInch = afxData.cyPixelsPerInch;
       }
       ASSERT(cxPerInch != 0 && cyPerInch != 0);
       lpSize->cx = MulDiv(lpSize->cx, HIMETRIC_INCH, cxPerInch);
       lpSize->cy = MulDiv(lpSize->cy, HIMETRIC_INCH, cyPerInch);
       }

       */

   }

   void graphics::HIMETRICtoDP(LPSIZE lpSize)
   {

      _throw(not_implemented(get_app()));

      /*      ASSERT(__is_valid_address(lpSize, sizeof(SIZE)));

       int32_t nMapMode;
       if (this != NULL && (nMapMode = GetMapMode()) < MM_ISOTROPIC &&
       nMapMode != MM_TEXT)
       {
       // when using a constrained ::collection::map mode, ::collection::map against physical inch
       ((::draw2d::graphics *)this)->SetMapMode(MM_HIMETRIC);
       LPtoDP(lpSize);
       ((::draw2d::graphics *)this)->SetMapMode(nMapMode);
       }
       else
       {
       // ::collection::map against logical inch for non-constrained mapping modes
       int32_t cxPerInch, cyPerInch;
       if (this != NULL)
       {
       ASSERT_VALID(this);
       ASSERT(get_handle1() != NULL);  // no HDC attached or created?
       cxPerInch = GetDeviceCaps(LOGPIXELSX);
       cyPerInch = GetDeviceCaps(LOGPIXELSY);
       }
       else
       {
       //            cxPerInch = afxData.cxPixelsPerInch;
       //          cyPerInch = afxData.cyPixelsPerInch;
       }
       ASSERT(cxPerInch != 0 && cyPerInch != 0);
       lpSize->cx = MulDiv(lpSize->cx, cxPerInch, HIMETRIC_INCH);
       lpSize->cy = MulDiv(lpSize->cy, cyPerInch, HIMETRIC_INCH);
       }

       */

   }

   void graphics::LPtoHIMETRIC(LPSIZE lpSize)
   {
      ASSERT(__is_valid_address(lpSize, sizeof(SIZE)));

      LPtoDP(lpSize);
      DPtoHIMETRIC(lpSize);
   }

   void graphics::HIMETRICtoLP(LPSIZE lpSize)
   {
      ASSERT(__is_valid_address(lpSize, sizeof(SIZE)));

      HIMETRICtoDP(lpSize);
      DPtoLP(lpSize);
   }

   /////////////////////////////////////////////////////////////////////////////
   // special graphics drawing primitives/helpers

   ::draw2d::brush* PASCAL graphics::GetHalftoneBrush(::base::application * papp)
   {
      /*      ::ca2::LockGlobals(CRIT_HALFTONEBRUSH);
       if (gen_HalftoneBrush == NULL)
       {
       WORD grayPattern[8];
       for (int32_t i = 0; i < 8; i++)
       grayPattern[i] = (WORD)(0x5555 << (i & 1));
       HBITMAP grayBitmap = CreateBitmap(8, 8, 1, 1, grayPattern);
       if (grayBitmap != NULL)
       {
       gen_HalftoneBrush = ::CreatePatternBrush(grayBitmap);
       ::DeleteObject(grayBitmap);
       }
       }
       if (!gen_WingdixTerm)
       gen_WingdixTerm = (char)!atexit(&__win_gdi_x_term);
       ::ca2::UnlockGlobals(CRIT_HALFTONEBRUSH);

       //      return ::win::brush::from_handle(papp, gen_HalftoneBrush);*/
      return NULL;
   }

   void graphics::DrawDragRect(const RECT & lpRect, SIZE size, const RECT & lpRectLast, SIZE sizeLast, ::draw2d::brush* pBrush, ::draw2d::brush* pBrushLast)
   {

      _throw(not_implemented(get_app()));

      /*
       ASSERT(__is_valid_address(lpRect, sizeof(RECT), FALSE));
       ASSERT(lpRectLast == NULL ||
       __is_valid_address(lpRectLast, sizeof(RECT), FALSE));

       // first, determine the update region and select it
       ::draw2d::region rgnNew;
       ::draw2d::region rgnOutside, rgnInside;
       rgnOutside.CreateRectRgnIndirect(lpRect);
       rect rect = *lpRect;
       rect.inflate(-size.cx, -size.cy);
       rect.intersect(rect, lpRect);
       rgnInside.CreateRectRgnIndirect(rect);
       rgnNew.CreateRectRgn(0, 0, 0, 0);
       rgnNew.CombineRgn(&rgnOutside, &rgnInside, RGN_XOR);

       ::draw2d::brush* pBrushOld = NULL;
       if (pBrush == NULL)
       {
       pBrush = graphics::GetHalftoneBrush(get_app());
       }

       ENSURE(pBrush);

       if (pBrushLast == NULL)
       {
       pBrushLast = pBrush;
       }

       ::draw2d::region rgnLast, rgnUpdate;
       if (lpRectLast != NULL)
       {
       // find difference between new region and old region
       rgnLast.CreateRectRgn(0, 0, 0, 0);
       rgnOutside.SetRectRgn(lpRectLast);
       rect = *lpRectLast;
       rect.inflate(-sizeLast.cx, -sizeLast.cy);
       rect.intersect(rect, lpRectLast);
       rgnInside.SetRectRgn(rect);
       rgnLast.CombineRgn(&rgnOutside, &rgnInside, RGN_XOR);

       // only diff them if brushes are the same
       if (pBrush->get_os_data() == pBrushLast->get_os_data())
       {
       rgnUpdate.CreateRectRgn(0, 0, 0, 0);
       rgnUpdate.CombineRgn(&rgnLast, &rgnNew, RGN_XOR);
       }
       }
       if (pBrush->get_os_data() != pBrushLast->get_os_data() && lpRectLast != NULL)
       {
       // brushes are different -- erase old region first
       SelectClipRgn(&rgnLast);
       GetClipBox(&rect);
       pBrushOld = SelectObject(pBrushLast);
       PatBlt(rect.left, rect.top, rect.width(), rect.height(), PATINVERT);
       SelectObject(pBrushOld);
       pBrushOld = NULL;
       }

       // draw into the update/new region
       SelectClipRgn(rgnUpdate.get_os_data() != NULL ? &rgnUpdate : &rgnNew);
       GetClipBox(&rect);
       pBrushOld = SelectObject(pBrush);
       PatBlt(rect.left, rect.top, rect.width(), rect.height(), PATINVERT);

       // cleanup DC
       if (pBrushOld != NULL)
       SelectObject(pBrushOld);
       SelectClipRgn(NULL);

       */

   }

   /*void graphics::FillSolidRect(const RECT & lpRect, COLORREF clr)
    {
    ::SetBkColor(get_handle1(), clr);
    ::ExtTextOut(get_handle1(), 0, 0, ETO_OPAQUE, lpRect, NULL, 0, NULL);
    }*/


   void graphics::draw3d_rect(LPCRECT lpRect, COLORREF clrTopLeft, COLORREF clrBottomRight)
   {
      LONG x = lpRect->left;
      LONG y = lpRect->top;
      LONG cx = width(lpRect);
      LONG cy = height(lpRect);
      fill_solid_rect_dim(x, y, cx - 1, 1, clrTopLeft);
      fill_solid_rect_dim(x, y, 1, cy - 1, clrTopLeft);
      fill_solid_rect_dim(x + cx - 1, y, 1, cy, clrBottomRight);
      fill_solid_rect_dim(x, y + cy - 1, cx, 1, clrBottomRight);
   }






   //::draw2d::graphics * PASCAL ::win::graphics::from_handle(HDC hDC)
   //{
   //hdc_map* pMap = afxMapHDC(TRUE); //create ::collection::map if not exist
   //ASSERT(pMap != NULL);
   //      ::draw2d::graphics * pgraphics = (::draw2d::graphics *)pMap->from_handle(hDC);
   //    ASSERT(pgraphics == NULL || (dynamic_cast<::win::graphics * >(pgraphics))->get_handle1() == hDC);
   //  return pgraphics;
   // return NULL;
   //}

   /*

    bool graphics::Attach(HDC hdc)
    {

    if(hdc == NULL)
    return false;

    if(m_hdc == hdc)
    {

    if(m_pgraphics != NULL)
    return true;

    }

    if(hdc != NULL)
    {

    m_pgraphics = new ::Gdiplus::Graphics(hdc);

    set_text_rendering(::draw2d::text_rendering_anti_alias_grid_fit);

    m_hdc = hdc;

    }

    return m_pgraphics != NULL;

    ASSERT(get_handle1() == NULL);      // only attach once, detach on destroy
    ASSERT(get_handle2() == NULL);    // only attach to an is_empty DC

    if (hDC == NULL)
    {
    return FALSE;
    }
    // remember early to avoid leak
    set_handle1(hDC);
    hdc_map* pMap = afxMapHDC(TRUE); // create ::collection::map if not exist
    ASSERT(pMap != NULL);
    pMap->set_permanent(get_handle1(), this);

    SetAttribDC(get_handle1());     // Default to same as output
    return TRUE;*/
   //   }

   /* HDC graphics::Detach()
    {

    if(m_hdc == NULL)
    return NULL;

    if(m_pgraphics == NULL)
    return NULL;

    delete m_pgraphics;
    m_pgraphics = NULL;

    HDC hdc = m_hdc;
    m_hdc = NULL;

    return hdc;

    }
    */

   bool graphics::DeleteDC()
   {

      if(m_layer != NULL)
      {

         //CGLayerRelease(m_layer);

         m_layer = NULL;

         if(m_bOwnDC)
         {

            CGContextRelease(m_pdc);

         }

         m_pdc = NULL;

      }
      else
      {

         m_pdc = NULL;

         m_layer = NULL;

      }
      
      m_pdibDraw2dGraphics = NULL;
      
      m_etextrendering  = ::draw2d::text_rendering_anti_alias_grid_fit;

      return true;

   }


   /*

    void graphics::SetAttribDC(HDC hDC)  // Set the Attribute DC
    {
    //      set_handle2(hDC);
    }

    void graphics::SetOutputDC(HDC hDC)  // Set the Output DC
    {
    #ifdef DEBUG
          hdc_map* pMap = afxMapHDC();
    if (pMap != NULL && pMap->lookup_permanent(get_handle1()) == this)
    {
    TRACE(::ca2::trace::category_AppMsg, 0, "Cannot Set Output hDC on Attached graphics.\n");
    ASSERT(FALSE);
    }*/
   //#endif
   //    set_handle1(hDC);
   //}
   /*
    void graphics::ReleaseAttribDC()     // Release the Attribute DC
    {
    //      set_handle2(NULL);
    }

    void graphics::ReleaseOutputDC()     // Release the Output DC
    {
    #ifdef DEBUG
          hdc_map* pMap = afxMapHDC();
    if (pMap != NULL && pMap->lookup_permanent(get_handle1()) == this)
    {
    TRACE(::ca2::trace::category_AppMsg, 0, "Cannot Release Output hDC on Attached graphics.\n");
    ASSERT(FALSE);
    }*/
   //#endif
   //set_handle1(NULL);
   //

   /////////////////////////////////////////////////////////////////////////////
   // Out-of-line routines

   int32_t graphics::StartDoc(const char * lpszDocName)
   {

      _throw(not_implemented(get_app()));
      return 0;

      /*
       DOCINFO di;
       memset(&di, 0, sizeof(DOCINFO));
       di.cbSize = sizeof(DOCINFO);
       di.lpszDocName = lpszDocName;
       return StartDoc(&di);
       */

   }

   int32_t graphics::SaveDC()
   {
      
      
      CGContextSaveGState(m_pdc);
      
      m_iSaveDC++;
      

      return m_iSaveDC;

      /*
       int32_t nRetVal = 0;
       if(get_handle2() != NULL)
       nRetVal = ::SaveDC(get_handle2());
       if(get_handle1() != NULL && get_handle1() != get_handle2() && ::SaveDC(get_handle1()) != 0)
       nRetVal = -1;   // -1 is the only valid restore value for complex DCs
       return nRetVal;
       */

   }

   bool graphics::RestoreDC(int32_t nSavedDC)
   {
      
      bool bRestored = false;
      
      while(m_iSaveDC >= MAX(1, nSavedDC))
      {
         
         CGContextRestoreGState(m_pdc);
         
         m_iSaveDC--;
         
         bRestored = true;
         
      }
      
      

      return bRestored;

      /*
       bool bRetVal = TRUE;
       if(get_handle1() != NULL && get_handle1() != get_handle2())
       bRetVal = ::RestoreDC(get_handle1(), nSavedDC) != FALSE;
       if(get_handle2() != NULL)
       bRetVal = (bRetVal && ::RestoreDC(get_handle2(), nSavedDC) != FALSE);
       return bRetVal;
       */

   }

   //   ::draw2d::object* PASCAL graphics::SelectGdiObject(::base::application * papp, HDC hDC, HGDIOBJ h)
   // {
   //      return ::win::object::from_handle(papp, ::SelectObject(hDC, h));
   //}

   ::draw2d::object* graphics::SelectStockObject(int32_t nIndex)
   {
      /*      HGDIOBJ hObject = ::GetStockObject(nIndex);
       HGDIOBJ hOldObj = NULL;
       ASSERT(hObject != NULL);
       if(get_handle1() != NULL && get_handle1() != get_handle2())
       hOldObj = ::SelectObject(get_handle1(), hObject);
       if(get_handle2() != NULL)
       hOldObj = ::SelectObject(get_handle2(), hObject);
       return ::win::object::from_handle(get_app(), hOldObj);*/

      return NULL;
   }

   ::draw2d::pen* graphics::SelectObject(::draw2d::pen* pPen)
   {
      /*HGDIOBJ hOldObj = NULL;
       if(pPen == NULL)
       return NULL;
       if(get_handle1() != NULL && get_handle1() != get_handle2())
       hOldObj = ::SelectObject(get_handle1(), pPen->get_os_data());
       if(get_handle2() != NULL)
       hOldObj = ::SelectObject(get_handle2(), pPen->get_os_data());
       return dynamic_cast < pen * > (::win::object::from_handle(get_app(), hOldObj));*/
      m_sppen = pPen;
      return m_sppen;
   }

   ::draw2d::brush * graphics::SelectObject(::draw2d::brush* pBrush)
   {

      m_spbrush = pBrush;

      return m_spbrush;

   }


   ::draw2d::font* graphics::SelectObject(::draw2d::font * pfont)
   {

      if(!select_font(pfont))
         return NULL;

      return m_spfont;

   }
   

   int32_t graphics::SelectObject(::draw2d::region * pRgn)
   {

      _throw(not_implemented(get_app()));
      return false;

      /*
       int32_t nRetVal = GDI_ERROR;
       if(get_handle1() != NULL && get_handle1() != get_handle2())
       nRetVal = (int32_t)(int_ptr)::SelectObject(get_handle1(), (HGDIOBJ) pRgn->get_os_data());
       if(get_handle2() != NULL)
       nRetVal = (int32_t)(int_ptr)::SelectObject(get_handle2(), (HGDIOBJ) pRgn->get_os_data());
       return nRetVal;
       */

   }

   ::draw2d::palette* graphics::SelectPalette(::draw2d::palette* pPalette, bool bForceBackground)
   {
      return NULL;
      //      return dynamic_cast < ::draw2d::palette * > (::win::object::from_handle(get_app(), ::SelectPalette(get_handle1(), (HPALETTE)pPalette->get_os_data(), bForceBackground)));
   }

   COLORREF graphics::SetBkColor(COLORREF crColor)
   {

//      _throw(not_implemented(get_app()));
      return 0;


      /*
       COLORREF crRetVal = CLR_INVALID;
       if(get_handle1() != NULL && get_handle1() != get_handle2())
       crRetVal = ::SetBkColor(get_handle1(), crColor);
       if(get_handle2() != NULL)
       crRetVal = ::SetBkColor(get_handle2(), crColor);
       return crRetVal;
       */

   }

   int32_t graphics::SetBkMode(int32_t nBkMode)
   {

      return 0;

      /*      int32_t nRetVal = 0;
       if(get_handle1() != NULL && get_handle1() != get_handle2())
       nRetVal = ::SetBkMode(get_handle1(), nBkMode);
       if(get_handle2() != NULL)
       nRetVal = ::SetBkMode(get_handle2(), nBkMode);
       return nRetVal;*/
   }

   int32_t graphics::SetPolyFillMode(int32_t nPolyFillMode)
   {

      _throw(not_implemented(get_app()));
      return 0;

      /*
       int32_t nRetVal = 0;
       if(get_handle1() != NULL && get_handle1() != get_handle2())
       nRetVal = ::SetPolyFillMode(get_handle1(), nPolyFillMode);
       if(get_handle2() != NULL)
       nRetVal = ::SetPolyFillMode(get_handle2(), nPolyFillMode);
       return nRetVal;
       */

   }

   int32_t graphics::SetROP2(int32_t nDrawMode)
   {

      _throw(not_implemented(get_app()));
      return 0;

      /*
       int32_t nRetVal = 0;
       if(get_handle1() != NULL && get_handle1() != get_handle2())
       nRetVal = ::SetROP2(get_handle1(), nDrawMode);
       if(get_handle2() != NULL)
       nRetVal = ::SetROP2(get_handle2(), nDrawMode);
       return nRetVal;
       */

   }

   int32_t graphics::SetStretchBltMode(int32_t nStretchMode)
   {

//      _throw(not_implemented(get_app()));
      //return 0;


       if(nStretchMode == 0)
       {
          
          CGContextSetInterpolationQuality(m_pdc, kCGInterpolationDefault);
          
       }
       else if(nStretchMode == HALFTONE)
       {
          
          CGContextSetInterpolationQuality(m_pdc, kCGInterpolationHigh);
          
       }
       else
       {
       
          CGContextSetInterpolationQuality(m_pdc,kCGInterpolationLow);

       }
      
       return 1;
      
      /*int32_t nRetVal = 0;
       if(get_handle1() != NULL && get_handle1() != get_handle2())
       nRetVal = ::SetStretchBltMode(get_handle1(), nStretchMode);
       if(get_handle2() != NULL)
       nRetVal = ::SetStretchBltMode(get_handle2(), nStretchMode);
       return nRetVal;*/
   }

   int32_t graphics::SetGraphicsMode(int32_t iMode)
   {

      _throw(not_implemented(get_app()));
      return 0;

      /*
       int32_t nRetVal = 0;
       if(get_handle1() != NULL && get_handle1() != get_handle2())
       {
       nRetVal = ::SetGraphicsMode(get_handle1(), iMode);
       }
       if(get_handle2() != NULL)
       {
       nRetVal = ::SetGraphicsMode(get_handle2(), iMode);
       }
       return nRetVal;
       */

   }

   bool graphics::SetWorldTransform(const XFORM* pXform)
   {

      _throw(not_implemented(get_app()));
      return false;

      /*
       bool nRetVal = 0;
       if(get_handle1() != NULL && get_handle1() != get_handle2())
       {
       nRetVal = ::SetWorldTransform(get_handle1(), pXform) != FALSE;
       }
       if(get_handle2() != NULL)
       {
       nRetVal = ::SetWorldTransform(get_handle2(), pXform) != FALSE;
       }
       return nRetVal;
       */

   }

   bool graphics::ModifyWorldTransform(const XFORM* pXform,DWORD iMode)
   {

      _throw(not_implemented(get_app()));
      return false;


      /*
       bool nRetVal = 0;
       if(get_handle1() != NULL && get_handle1() != get_handle2())
       {
       nRetVal = ::ModifyWorldTransform(get_handle1(), pXform, iMode) != FALSE;
       }
       if(get_handle2() != NULL)
       {
       nRetVal = ::ModifyWorldTransform(get_handle2(), pXform, iMode) != FALSE;
       }
       return nRetVal;
       */

   }

   int32_t graphics::SetMapMode(int32_t nMapMode)
   {

      _throw(not_implemented(get_app()));
      return 0;


      /*
       int32_t nRetVal = 0;
       if(get_handle1() != NULL && get_handle1() != get_handle2())
       nRetVal = ::SetMapMode(get_handle1(), nMapMode);
       if(get_handle2() != NULL)
       nRetVal = ::SetMapMode(get_handle2(), nMapMode);
       return nRetVal;
       */

   }

   point graphics::GetViewportOrg()
   {
      
//      synch_lock sl(m_pmutex);
//
//      CGAffineTransform affine = CGContextGetCTM(m_pdc);
//
//      return point(affine.tx, affine.ty);
      
      return ::draw2d::graphics::GetViewportOrg();

   }
   

   bool graphics::_get(::draw2d::matrix & matrix)
   {
      
      synch_lock sl(m_pmutex);
      
      CGAffineTransform affine = CGContextGetCTM(m_pdc);
      
      copy(matrix, affine);

      return true;
      
   }
   
   
   bool graphics::_set(const ::draw2d::matrix & matrix)
   {
      
      synch_lock sl(m_pmutex);
      
      CGAffineTransform affine = CGContextGetCTM(m_pdc);
      
      ::draw2d::matrix m;
      
      copy(m, affine);

      ::draw2d::matrix m1;
      
      copy(m1, affine);

      m.invert();
      
      CGAffineTransform affine3;
      
      copy(affine3, m);

      CGContextConcatCTM(m_pdc, affine3);

      //CGAffineTransform affine2 = CGContextGetCTM(m_pdc);

      CGAffineTransform affine4;

      copy(affine4, matrix);
      
      CGContextConcatCTM(m_pdc, affine4);
      
      return true;

   }


   point graphics::SetViewportOrg(int32_t x, int32_t y)
   {

      return ::draw2d::graphics::SetViewportOrg(point(x, y));
//      synch_lock sl(m_pmutex);
//
//      CGAffineTransform affine = CGContextGetCTM(m_pdc);
//
//      CGContextTranslateCTM(m_pdc, x - affine.tx, y - affine.ty);
//
//      return point(affine.tx, affine.ty);

   }


   point graphics::OffsetViewportOrg(int32_t nWidth, int32_t nHeight)
   {

//      synch_lock sl(m_pmutex);
//
//      CGAffineTransform affine = CGContextGetCTM(m_pdc);
//
//      CGContextTranslateCTM(m_pdc, nWidth, nHeight);
//
//      return point(affine.tx, affine.ty);
      return ::draw2d::graphics::OffsetViewportOrg(nWidth, nHeight);
      
   }

   size graphics::SetViewportExt(int32_t x, int32_t y)
   {

      _throw(not_implemented(get_app()));
      return ::size(0, 0);

      /*
       size size(0, 0);
       if(get_handle1() != NULL && get_handle1() != get_handle2())
       ::SetViewportExtEx(get_handle1(), x, y, &size);
       if(get_handle2() != NULL)
       ::SetViewportExtEx(get_handle2(), x, y, &size);
       return size;
       */
   }

   size graphics::ScaleViewportExt(int32_t xNum, int32_t xDenom, int32_t yNum, int32_t yDenom)
   {

      _throw(not_implemented(get_app()));
      return ::size(0, 0);

      /*
       size size(0, 0);
       if(get_handle1() != NULL && get_handle1() != get_handle2())
       ::ScaleViewportExtEx(get_handle1(), xNum, xDenom, yNum, yDenom, &size);
       if(get_handle2() != NULL)
       ::ScaleViewportExtEx(get_handle2(), xNum, xDenom, yNum, yDenom, &size);
       return size;
       */

   }

   point graphics::SetWindowOrg(int32_t x, int32_t y)
   {

      _throw(not_implemented(get_app()));
      return ::point(0, 0);

      /*
       point point(0, 0);
       if(get_handle1() != NULL && get_handle1() != get_handle2())
       ::SetWindowOrgEx(get_handle1(), x, y, &point);
       if(get_handle2() != NULL)
       ::SetWindowOrgEx(get_handle2(), x, y, &point);
       return point;
       */
   }

   point graphics::OffsetWindowOrg(int32_t nWidth, int32_t nHeight)
   {

      _throw(not_implemented(get_app()));
      return ::point(0, 0);

      /*
       point point(0, 0);
       if(get_handle1() != NULL && get_handle1() != get_handle2())
       ::OffsetWindowOrgEx(get_handle1(), nWidth, nHeight, &point);
       if(get_handle2() != NULL)
       ::OffsetWindowOrgEx(get_handle2(), nWidth, nHeight, &point);
       return point;
       */

   }

   size graphics::SetWindowExt(int32_t x, int32_t y)
   {

      _throw(not_implemented(get_app()));
      return ::size(0, 0);

      /*
       size size(0, 0);
       if(get_handle1() != NULL && get_handle1() != get_handle2())
       ::SetWindowExtEx(get_handle1(), x, y, &size);
       if(get_handle2() != NULL)
       ::SetWindowExtEx(get_handle2(), x, y, &size);
       return size;
       */

   }

   size graphics::ScaleWindowExt(int32_t xNum, int32_t xDenom, int32_t yNum, int32_t yDenom)
   {

      _throw(not_implemented(get_app()));
      return ::size(0, 0);

      /*
       size size(0, 0);
       if(get_handle1() != NULL && get_handle1() != get_handle2())
       ::ScaleWindowExtEx(get_handle1(), xNum, xDenom, yNum, yDenom, &size);
       if(get_handle2() != NULL)
       ::ScaleWindowExtEx(get_handle2(), xNum, xDenom, yNum, yDenom, &size);
       return size;
       */

   }

   int32_t graphics::GetClipBox(LPRECT lpRect)
   {

      ::SetRectEmpty(lpRect);

//      _throw(not_implemented(get_app()));
      return 0;

      /*      return ::GetClipBox(get_handle1(), lpRect);*/
   }

   int32_t graphics::SelectClipRgn(::draw2d::region * pregion)
   {

      if(pregion == NULL)
      {

//         cairo_reset_clip(m_pdc);
         
         m_spregion.release();

      }
      else
      {

         m_spregion = pregion;

         //cairo_clip(m_pdc);

      }

      return 0;

      /*
       int32_t nRetVal = ERROR;
       if(get_handle1() != NULL && get_handle1() != get_handle2())
       nRetVal = ::SelectClipRgn(get_handle1(), pRgn == NULL ? NULL : (HRGN) pRgn->get_os_data());
       if(get_handle2() != NULL)
       nRetVal = ::SelectClipRgn(get_handle2(), pRgn == NULL ? NULL : (HRGN) pRgn->get_os_data());
       return nRetVal;
       */

   }

   int32_t graphics::ExcludeClipRect(int32_t x1, int32_t y1, int32_t x2, int32_t y2)
   {

      _throw(not_implemented(get_app()));
      return 0;

      /*
       int32_t nRetVal = ERROR;
       if(get_handle1() != NULL && get_handle1() != get_handle2())
       nRetVal = ::ExcludeClipRect(get_handle1(), x1, y1, x2, y2);
       if(get_handle2() != NULL)
       nRetVal = ::ExcludeClipRect(get_handle2(), x1, y1, x2, y2);
       return nRetVal;
       */

   }

   int32_t graphics::ExcludeClipRect(const RECT & lpRect)
   {

      _throw(not_implemented(get_app()));
      return 0;

      /*
       int32_t nRetVal = ERROR;
       if(get_handle1() != NULL && get_handle1() != get_handle2())
       nRetVal = ::ExcludeClipRect(get_handle1(), lpRect.left, lpRect.top,
       lpRect.right, lpRect.bottom);
       if(get_handle2() != NULL)
       nRetVal = ::ExcludeClipRect(get_handle2(), lpRect.left, lpRect.top,
       lpRect.right, lpRect.bottom);
       return nRetVal;
       */

   }

   int32_t graphics::IntersectClipRect(int32_t x1, int32_t y1, int32_t x2, int32_t y2)
   {

      _throw(not_implemented(get_app()));
      return 0;

      /*
       int32_t nRetVal = ERROR;
       if(get_handle1() != NULL && get_handle1() != get_handle2())
       nRetVal = ::IntersectClipRect(get_handle1(), x1, y1, x2, y2);
       if(get_handle2() != NULL)
       nRetVal = ::IntersectClipRect(get_handle2(), x1, y1, x2, y2);
       return nRetVal;
       */

   }

   int32_t graphics::IntersectClipRect(const RECT & lpRect)
   {

      //_throw(not_implemented(get_app()));
      CGRect rect;
      
      rect.origin.x     = lpRect.left;
      rect.origin.y     = lpRect.top;
      rect.size.width   = lpRect.right - lpRect.left;
      rect.size.height  = lpRect.bottom - lpRect.top;
      CGContextAddRect(m_pdc, rect);
      CGContextClip(m_pdc);
      
      return 0;

      /*      int32_t nRetVal = ERROR;
       if(get_handle1() != NULL && get_handle1() != get_handle2())
       nRetVal = ::IntersectClipRect(get_handle1(), lpRect.left, lpRect.top, lpRect.right, lpRect.bottom);
       if(get_handle2() != NULL)
       nRetVal = ::IntersectClipRect(get_handle2(), lpRect.left, lpRect.top, lpRect.right, lpRect.bottom);
       return nRetVal;
       */

   }

   int32_t graphics::OffsetClipRgn(int32_t x, int32_t y)
   {

      _throw(not_implemented(get_app()));
      return 0;

      /*
       int32_t nRetVal = ERROR;
       if(get_handle1() != NULL && get_handle1() != get_handle2())
       nRetVal = ::OffsetClipRgn(get_handle1(), x, y);
       if(get_handle2() != NULL)
       nRetVal = ::OffsetClipRgn(get_handle2(), x, y);
       return nRetVal;
       */

   }

   int32_t graphics::OffsetClipRgn(SIZE size)
   {

      _throw(not_implemented(get_app()));
      return 0;

      /*
       int32_t nRetVal = ERROR;
       if(get_handle1() != NULL && get_handle1() != get_handle2())
       nRetVal = ::OffsetClipRgn(get_handle1(), size.cx, size.cy);
       if(get_handle2() != NULL)
       nRetVal = ::OffsetClipRgn(get_handle2(), size.cx, size.cy);
       return nRetVal;
       */
   }

   /*point graphics::MoveTo(int32_t x, int32_t y)
    {
    point point(0, 0);
    if(get_handle1() != NULL && get_handle1() != get_handle2())
    ::MoveToEx(get_handle1(), x, y, &point);
    if(get_handle2() != NULL)
    ::MoveToEx(get_handle2(), x, y, &point);
    return point;
    }*/

   UINT graphics::SetTextAlign(UINT nFlags)
   {

      _throw(not_implemented(get_app()));
      return 0;

      /*
       UINT nRetVal = GDI_ERROR;
       if(get_handle1() != NULL && get_handle1() != get_handle2())
       ::SetTextAlign(get_handle1(), nFlags);
       if(get_handle2() != NULL)
       nRetVal = ::SetTextAlign(get_handle2(), nFlags);
       return nRetVal;
       */

   }

   int32_t graphics::SetTextJustification(int32_t nBreakExtra, int32_t nBreakCount)
   {

      _throw(not_implemented(get_app()));
      return 0;

      /*
       int32_t nRetVal = 0;
       if(get_handle1() != NULL && get_handle1() != get_handle2())
       nRetVal = ::SetTextJustification(get_handle1(), nBreakExtra, nBreakCount);
       if(get_handle2() != NULL)
       nRetVal = ::SetTextJustification(get_handle2(), nBreakExtra, nBreakCount);
       return nRetVal;
       */

   }

   int32_t graphics::SetTextCharacterExtra(int32_t nCharExtra)
   {

      _throw(not_implemented(get_app()));
      return 0;

      /*
       ASSERT(get_handle1() != NULL);
       int32_t nRetVal = 0x8000000;
       if(get_handle1() != NULL && get_handle1() != get_handle2())
       nRetVal = ::SetTextCharacterExtra(get_handle1(), nCharExtra);
       if(get_handle2() != NULL)
       nRetVal = ::SetTextCharacterExtra(get_handle2(), nCharExtra);
       return nRetVal;
       */

   }

   DWORD graphics::SetMapperFlags(DWORD dwFlag)
   {

      _throw(not_implemented(get_app()));
      return 0;

      /*
       ASSERT(get_handle1() != NULL);
       DWORD dwRetVal = GDI_ERROR;
       if(get_handle1() != NULL && get_handle1() != get_handle2())
       dwRetVal = ::SetMapperFlags(get_handle1(), dwFlag);
       if(get_handle2() != NULL)
       dwRetVal = ::SetMapperFlags(get_handle2(), dwFlag);
       return dwRetVal;
       */

   }

   //   typedef DWORD (CALLBACK* __GDIGETLAYOUTPROC)(HDC);
   //   typedef DWORD (CALLBACK* __GDISETLAYOUTPROC)(HDC, DWORD);

   DWORD graphics::GetLayout()
   {

      _throw(not_implemented(get_app()));
      return 0;

      /*
       HINSTANCE hInst = ::GetModuleHandleA("GDI32.DLL");
       ASSERT(hInst != NULL);
       DWORD dwGetLayout = LAYOUT_LTR;
       __GDIGETLAYOUTPROC pfn;
       pfn = (__GDIGETLAYOUTPROC) GetProcAddress(hInst, "GetLayout");
       // if they API is available, just call it. If it is not
       // available, indicate an error.
       if (pfn != NULL)
       dwGetLayout = (*pfn)(get_handle1());
       else
       {
       dwGetLayout = GDI_ERROR;
       set_last_error(ERROR_CALL_NOT_IMPLEMENTED);
       }
       return dwGetLayout;
       */

   }

   DWORD graphics::SetLayout(DWORD dwSetLayout)
   {

      _throw(not_implemented(get_app()));
      return 0;

      /*
       HINSTANCE hInst = ::GetModuleHandleA("GDI32.DLL");
       ASSERT(hInst != NULL);
       DWORD dwGetLayout = LAYOUT_LTR;
       __GDISETLAYOUTPROC pfn;
       pfn = (__GDISETLAYOUTPROC) GetProcAddress(hInst, "SetLayout");
       // If the API is availalbe, just call it. If it's not available,
       // setting anything other than LAYOUT_LTR is an error.
       if (pfn != NULL)
       dwGetLayout = (*pfn)(get_handle1(), dwSetLayout);
       else if (dwSetLayout != LAYOUT_LTR)
       {
       dwGetLayout = GDI_ERROR;
       set_last_error(ERROR_CALL_NOT_IMPLEMENTED);
       }
       return dwGetLayout;
       */

   }
   /*
    void window::ScreenToClient(LPRECT lpRect)
    {
    ASSERT(::IsWindow(get_handle1()));
    ::ScreenToClient(get_handle1(), (LPPOINT)lpRect);
    ::ScreenToClient(get_handle1(), ((LPPOINT)lpRect)+1);
    if (GetExStyle() & WS_EX_LAYOUTRTL)
    rect::swap_left_right(lpRect);
    }

    void window::ClientToScreen(LPRECT lpRect)
    {
    ASSERT(::IsWindow(get_handle1()));
    ::ClientToScreen(get_handle1(), (LPPOINT)lpRect);
    ::ClientToScreen(get_handle1(), ((LPPOINT)lpRect)+1);
    if (GetExStyle() & WS_EX_LAYOUTRTL)
    rect::swap_left_right(lpRect);
    }*/


   /////////////////////////////////////////////////////////////////////////////
   // Advanced Win32 GDI functions

   bool graphics::ArcTo(int32_t x1, int32_t y1, int32_t x2, int32_t y2, int32_t x3, int32_t y3, int32_t x4, int32_t y4)
   {

      _throw(not_implemented(get_app()));
      return false;

      /*
       ASSERT(get_handle1() != NULL);
       bool bResult = ::ArcTo(get_handle1(), x1, y1, x2, y2, x3, y3, x4, y4) != FALSE;
       if (get_handle1() != get_handle2())
       {
       point pt;
       VERIFY(::GetCurrentPositionEx(get_handle1(), &pt));
       VERIFY(::MoveToEx(get_handle2(), pt.x, pt.y, NULL));
       }
       return bResult;
       */

   }

   int32_t graphics::SetArcDirection(int32_t nArcDirection)
   {


      _throw(not_implemented(get_app()));
      return 0;

      /*
       ASSERT(get_handle1() != NULL);
       int32_t nResult = 0;
       if (get_handle1() != get_handle2())
       nResult = ::SetArcDirection(get_handle1(), nArcDirection);
       if (get_handle2() != NULL)
       nResult = ::SetArcDirection(get_handle2(), nArcDirection);
       return nResult;
       */

   }

   bool graphics::PolyDraw(const POINT* lpPoints, const BYTE* lpTypes, int32_t nCount)
   {

      _throw(not_implemented(get_app()));
      return false;

      /*
       ASSERT(get_handle1() != NULL);
       bool bResult = ::PolyDraw(get_handle1(), lpPoints, lpTypes, nCount) != FALSE;
       if (get_handle1() != get_handle2())
       {
       point pt;
       VERIFY(::GetCurrentPositionEx(get_handle1(), &pt));
       VERIFY(::MoveToEx(get_handle2(), pt.x, pt.y, NULL));
       }
       return bResult;
       */

   }

   bool graphics::PolylineTo(const POINT* lpPoints, int32_t nCount)
   {

      _throw(not_implemented(get_app()));
      return false;

      /*
       ASSERT(get_handle1() != NULL);
       bool bResult = ::PolylineTo(get_handle1(), lpPoints, nCount) != FALSE;
       if (get_handle1() != get_handle2())
       {
       point pt;
       VERIFY(::GetCurrentPositionEx(get_handle1(), &pt));
       VERIFY(::MoveToEx(get_handle2(), pt.x, pt.y, NULL));
       }
       return bResult;
       */

   }

   /*
    bool graphics::SetColorAdjustment(const COLORADJUSTMENT* lpColorAdjust)
    {

    _throw(not_implemented(get_app()));
    return false;


    ASSERT(get_handle1() != NULL);
    bool bResult = FALSE;
    if (get_handle1() != get_handle2())
    bResult = ::SetColorAdjustment(get_handle1(), lpColorAdjust) != FALSE;
    if (get_handle2() != NULL)
    bResult = ::SetColorAdjustment(get_handle2(), lpColorAdjust) != FALSE;
    return bResult;
    */

   //   }

   bool graphics::PolyBezierTo(const POINT* lpPoints, int32_t nCount)
   {

      _throw(not_implemented(get_app()));
      return 0;

      /*
       ASSERT(get_handle1() != NULL);
       bool bResult = ::PolyBezierTo(get_handle1(), lpPoints, nCount) != FALSE;
       if (get_handle1() != get_handle2())
       {
       point pt;
       VERIFY(::GetCurrentPositionEx(get_handle1(), &pt));
       VERIFY(::MoveToEx(get_handle2(), pt.x, pt.y, NULL));
       }
       return bResult;
       */

   }

   bool graphics::SelectClipPath(int32_t nMode)
   {

      _throw(not_implemented(get_app()));
      return 0;

      /*
       ASSERT(get_handle1() != NULL);

       // output DC always holds the current path
       if (!::SelectClipPath(get_handle1(), nMode))
       return FALSE;

       // transfer clipping region into the attribute DC
       bool bResult = TRUE;
       if (get_handle1() != get_handle2())
       {
       HRGN hRgn = ::CreateRectRgn(0, 0, 0, 0);
       if (::GetClipRgn(get_handle1(), hRgn) < 0 || !::SelectClipRgn(get_handle2(), hRgn))
       {
       TRACE(::ca2::trace::category_AppMsg, 0, "Error: unable to transfer clip region in graphics::SelectClipPath!\n");
       bResult = FALSE;
       }
       ::DeleteObject(hRgn);
       }
       return bResult;
       */

   }

   int32_t graphics::SelectClipRgn(::draw2d::region* pRgn, int32_t nMode)
   {

      if(nMode == RGN_AND)
      {
         
         add_path(pRgn);
         CGContextClip(m_pdc);
         
      }
      
//      _throw(not_implemented(get_app()));
      return 0;

      /*      ASSERT(get_handle1() != NULL);
       int32_t nRetVal = ERROR;
       if (get_handle1() != get_handle2())
       nRetVal = ::ExtSelectClipRgn(get_handle1(), (HRGN)pRgn->get_os_data(), nMode);
       if (get_handle2() != NULL)
       nRetVal = ::ExtSelectClipRgn(get_handle2(), (HRGN)pRgn->get_os_data(), nMode);
       return nRetVal;
       */

   }


   /////////////////////////////////////////////////////////////////////////////
   // Coordinate transforms

   void graphics::LPtoDP(LPSIZE lpSize)
   {

      _throw(not_implemented(get_app()));
      return;

      /*
       ASSERT(__is_valid_address(lpSize, sizeof(SIZE)));

       size sizeWinExt = GetWindowExt();
       size sizeVpExt = GetViewportExt();
       lpSize->cx = MulDiv(lpSize->cx, abs(sizeVpExt.cx), abs(sizeWinExt.cx));
       lpSize->cy = MulDiv(lpSize->cy, abs(sizeVpExt.cy), abs(sizeWinExt.cy));
       */

   }

   void graphics::DPtoLP(LPSIZE lpSize)
   {

      _throw(not_implemented(get_app()));
      return;

   }



   int32_t graphics::draw_text(const char * lpszString, int32_t nCount, const RECT & lpRect, UINT nFormat)
   {

      return draw_text(string(lpszString, nCount), lpRect, nFormat);

   }


   bool graphics::draw_text(const string & str, const RECT & lpRect, UINT nFormat)
   {

      ::draw2d::graphics::draw_text(str, lpRect, nFormat);

      return 1;

   }

   
   int32_t graphics::draw_text_ex(LPTSTR lpszString, int32_t nCount, const RECT & lpRect, UINT nFormat, LPDRAWTEXTPARAMS lpDTParams)
   {

      _throw(not_implemented(get_app()));

      return 0;

   }
   

   bool graphics::draw_text_ex(const string & str, const RECT & lpRect, UINT nFormat, LPDRAWTEXTPARAMS lpDTParams)
   {

      _throw(not_implemented(get_app()));
      return 0;

   }

   
   sized graphics::GetTextExtent(const char * lpszString, strsize nCount, int32_t iIndex)
   {

      sized sz;
      
      if (!GetTextExtent(sz, lpszString, nCount, iIndex))
         return ::size(0, 0);
      
      return size((int) sz.cx, (int) sz.cy);
      
   }
   

   sized graphics::GetTextExtent(const char * lpszString, strsize nCount)
   {

      class sized sized;

      if(!GetTextExtent(sized, lpszString, nCount, (int) nCount))
         return ::size(0, 0);

      return ::size(sized.cx, sized.cy);

   }


   sized graphics::GetTextExtent(const string & str)
   {

      class sized size;

      if(!GetTextExtent(size, str, str.get_length(), (int)str.get_length()))
         return ::size(0, 0);

      return ::size((long) size.cx, (long) size.cy);

   }

   
   size graphics::GetOutputTextExtent(const char * lpszString, strsize nCount)
   {

      _throw(not_implemented(get_app()));
      return ::size(0, 0);

   }

   
   size graphics::GetOutputTextExtent(const string & str)
   {

      _throw(not_implemented(get_app()));
      return ::size(0, 0);

   }


   bool graphics::GetTextExtent(sized & size, const char * lpszString, strsize nCount, int32_t iIndex)
   {

      CGFloat ascent, descent, leading, width;
      
      stringa stra;
      
      stra.add_lines(string(lpszString, 0, MIN(iIndex, nCount)));
                     
      size.cy = 0;
                     
      size.cx = 0;
      
      for(auto str : stra)
      {
      
         const_cast < graphics * > (this)->internal_show_text(0, 0, 0, DT_TOPLEFT, str, (int32_t) str.get_length(), kCGTextInvisible, false, &ascent, &descent, &leading, &width);

         size.cy += ascent + descent + leading;
         
//         if(leading <= 0)
//         {
//
//            size.cy += descent;
//
//         }

         size.cx = MAX(size.cx, width);
         
      }

      return true;

   }

   
   bool graphics::GetTextExtent(sized & size, const char * lpszString, strsize nCount)
   {

      return GetTextExtent(size, lpszString, nCount, (int32_t) nCount);
      
   }
   

   bool graphics::GetTextExtent(sized & size, const string & str)
   {

      return GetTextExtent(size, str, str.get_length());

   }



   void graphics::fill_solid_rect(LPCRECT lpRect, COLORREF clr)
   {

      CGRect rect;

      copy(rect, lpRect);

      internal_set_fill_color(clr);

      CGContextFillRect(m_pdc, rect);

   }


   bool graphics::text_out(int32_t x, int32_t y, const char * lpszString, strsize nCount)
   {

      return ::draw2d::graphics::text_out(double(x), double(y), lpszString, nCount);

   }
   

   bool graphics::TextOutRaw(double x, double y, const char * lpszString, strsize nCount)
   {

      return internal_show_text(x, y, 0, DT_TOPLEFT, lpszString, (int32_t) nCount, kCGTextFill);

   }


   bool graphics::internal_show_text(double x, double y, double wAlign, UINT nFormat, const char * lpszString, int32_t nCount, CGTextDrawingMode emode, bool bDraw, CGFloat * pascent, CGFloat * pdescent, CGFloat * pleading, CGFloat * pwidth, ::draw2d::pen * ppen, ::draw2d::brush * pbrush, ::draw2d::font * pfont)
   {
      
      if(pfont == NULL && m_spfont.is_null())
      {
       
         m_spfont.alloc(allocer());
         
         m_spfont->create_pixel_font(FONT_SANS, 16.0);
         
      }

      return internal_show_text(pfont == NULL ? m_spfont.m_p : pfont, pbrush == NULL ? m_spbrush.m_p : pbrush, ppen == NULL ? m_sppen.m_p : ppen, x, y, wAlign, nFormat, lpszString, nCount, emode, bDraw, pascent,pdescent, pleading, pwidth);

   }

   
   bool graphics::draw_line(LPCPOINTD lppt1, LPCPOINTD lppt2, ::draw2d::pen * ppen)
   {
      
      CGContextBeginPath(m_pdc);
      
      CGContextMoveToPoint(m_pdc, lppt1->x, lppt1->y);
      
      CGContextAddLineToPoint(m_pdc, lppt2->x, lppt2->y);
      
      draw(ppen);
      
      m_pt = *lppt2;
      
      return true;

   }

   bool graphics::line_to(LPCPOINTD lppt)
   {

      CGContextBeginPath(m_pdc);

      CGContextMoveToPoint(m_pdc, m_pt.x, m_pt.y);

      CGContextAddLineToPoint(m_pdc, lppt->x, lppt->y);

      draw();

      m_pt = *lppt;

      return true;

   }


   void graphics::set_alpha_mode(::draw2d::e_alpha_mode ealphamode)
   {

      try
      {

         if(m_pdc == NULL)
         {

            return;

         }

         ::draw2d::graphics::set_alpha_mode(ealphamode);

         if(m_ealphamode == ::draw2d::alpha_mode_blend)
         {

            CGContextSetBlendMode(m_pdc, kCGBlendModeNormal);

         }
         else if(m_ealphamode == ::draw2d::alpha_mode_set)
         {

            CGContextSetBlendMode(m_pdc, kCGBlendModeCopy);

         }

      }
      catch(...)
      {

      }

   }


   void graphics::set_text_rendering(::draw2d::e_text_rendering etextrendering)
   {

      m_etextrendering = etextrendering;

   }


   void * graphics::get_os_data() const
   {

      return (void *) m_pdc;

   }


   bool graphics::attach(void * pdata)
   {

      m_iType = 10;
      
      m_pdc = (CGContextRef) pdata;

      m_bOwnDC = false;

      return true;

   }


   void * graphics::detach()
   {

      CGContextRef pgraphics = m_pdc;

      m_pdc = NULL;

      return pgraphics;

   }


   bool graphics::blur(bool bExpand, double dRadius, const RECT & lpcrect)
   {

//      cairo_pattern_t * ppattern = cairo_get_source(m_pdc);
//
//      if(ppattern == NULL)
//         return false;
//
//      cairo_surface_t * psurfaceSrc = NULL;
//
//      cairo_pattern_get_surface(ppattern, &psurfaceSrc);
//
//      cairo_surface_t * psurface = cairo_surface_create_for_rectangle(psurfaceSrc, lpcrect->left, lpcrect->top, width(lpcrect), height(lpcrect));
//
//      cairo_image_surface_blur(psurface, dRadius);

      return true;

   }


   double graphics::get_dpix()
   {

      //      return m_pgraphics->GetDpiX();
      return 72.0;

   }

   bool graphics::clip(const ::draw2d::region * pregion)
   {
      
      if(pregion == NULL)
      {
         
         return true;
         
      }
      
      if(pregion->m_etype == ::draw2d::region::type_combine)
      {

         if(pregion->m_ecombine == ::draw2d::region::combine_intersect)
         {
         
            add_path(pregion->m_pregion1);
            
            CGContextEOClip(m_pdc);
            
            add_path(pregion->m_pregion2);
            
            CGContextEOClip(m_pdc);
         
         }
         
      }
      else
      {
      
         add_path(pregion);
      
         CGContextEOClip(m_pdc);
         
      }
      
      return true;
      
   }
   
   bool graphics::add_path(const ::draw2d::region * pregion)
   {
      
      if(pregion == NULL)
         return true;
   
      if(pregion->m_etype == ::draw2d::region::type_rect)
      {
         
         CGRect r;
         
         r.origin.x = pregion->m_x1;
         r.origin.y = pregion->m_y1;
         r.size.width = pregion->m_x2 - pregion->m_x1;
         r.size.height = pregion->m_y2 - pregion->m_y1;
         
         CGContextAddRect (m_pdc, r);
         
      }
      else if(pregion->m_etype == ::draw2d::region::type_polygon)
      {
         
         CGContextBeginPath (m_pdc);
         
         set_polygon(pregion->m_lppoints, pregion->m_nCount);
         
         CGContextClosePath (m_pdc);
         
      }
      else if(pregion->m_etype == ::draw2d::region::type_oval)
      {
         
         CGRect r;
         
         r.origin.x = pregion->m_x1;
         r.origin.y = pregion->m_y1;
         r.size.width = pregion->m_x2 - pregion->m_x1;
         r.size.height = pregion->m_y2 - pregion->m_y1;

         
         CGContextAddEllipseInRect(m_pdc, r);
         
      }
      else if(pregion->m_etype == ::draw2d::region::type_combine)
      {
         
         _throw(simple_exception(get_app(), "not supported"));
         
      }
      
      return true;
      
   }
   

   bool graphics::set(const ::draw2d::brush * pbrush)
   {

//      cairo_set_source_rgba(m_pdc, argb_get_r_value(pbrush->m_cr) / 255.0, argb_get_g_value(pbrush->m_cr) / 255.0, argb_get_b_value(pbrush->m_cr) / 255.0, argb_get_a_value(pbrush->m_cr) / 255.0);

      if(pbrush == NULL || pbrush->m_etype == ::draw2d::brush::type_linear_gradient_point_color)
         return false;

      CGContextSetRGBFillColor(m_pdc, argb_get_r_value(pbrush->m_cr) / 255.0, argb_get_g_value(pbrush->m_cr) / 255.0, argb_get_b_value(pbrush->m_cr) / 255.0, argb_get_a_value(pbrush->m_cr) / 255.0);

      return true;

   }


   bool graphics::set(const ::draw2d::pen * ppen)
   {

//      cairo_set_source_rgba(m_pdc, argb_get_r_value(ppen->m_cr) / 255.0, argb_get_g_value(ppen->m_cr) / 255.0, argb_get_b_value(ppen->m_cr) / 255.0, argb_get_a_value(ppen->m_cr) / 255.0);
//
//      cairo_set_line_width(m_pdc, ppen->m_dWidth);

      if(ppen == NULL)
         return false;
      
      if(ppen->m_etype == ::draw2d::pen::type_brush && ppen->m_br.is_set())
      {
         
         if(ppen->m_br->m_etype == ::draw2d::brush::type_solid)
         {

            CGContextSetRGBStrokeColor(m_pdc, argb_get_r_value(ppen->m_br->m_cr) / 255.0, argb_get_g_value(ppen->m_br->m_cr) / 255.0, argb_get_b_value(ppen->m_br->m_cr) / 255.0, argb_get_a_value(ppen->m_br->m_cr) / 255.0);
            
         }
         
      }
      else
      {

         CGContextSetRGBStrokeColor(m_pdc, argb_get_r_value(ppen->m_cr) / 255.0, argb_get_g_value(ppen->m_cr) / 255.0, argb_get_b_value(ppen->m_cr) / 255.0, argb_get_a_value(ppen->m_cr) / 255.0);
         
      }

      CGContextSetLineWidth(m_pdc, ppen->m_dWidth);

      
      return true;

   }

   
   bool graphics::set_pen(const ::draw2d::brush * pbrush, double dWidth)
   {
      
      if(pbrush == NULL || pbrush->m_etype == ::draw2d::brush::type_null)
      {
         
         return false;
         
      }
      
      CGContextSetRGBStrokeColor(m_pdc, argb_get_r_value(pbrush->m_cr) / 255.0, argb_get_g_value(pbrush->m_cr) / 255.0, argb_get_b_value(pbrush->m_cr) / 255.0, argb_get_a_value(pbrush->m_cr) / 255.0);
      
      CGContextSetLineWidth(m_pdc, dWidth);
      
      
      return true;
      
   }


   bool graphics::SelectFont(::draw2d::font * pfont)
   {

      m_spfont = pfont;

      return true;

   }

   
   bool graphics::fill_and_draw()
   {

      fill(m_spbrush);

      draw(m_sppen);

      return true;

   }


   bool graphics::fill(::draw2d::brush * pbrush)
   {
      
      CGContextRef pgraphics = m_pdc;
      
      CGContextSaveGState(pgraphics);

      bool bOk = false;
      
      try
      {
      
         bOk = _fill(pbrush, true);
         
      }
      catch (...)
      {
         
      }
      
      CGContextRestoreGState(pgraphics);
      
      return bOk;

   }
   
   
   bool graphics::_fill(::draw2d::brush * pbrush, bool bContextClip)
   {
      
      if(pbrush == NULL || pbrush->m_etype == ::draw2d::brush::type_null)
         return true;
      
      CGContextRef pgraphics = m_pdc;
      
      if(pbrush->m_etype == ::draw2d::brush::type_radial_gradient_color)
      {
         
         if(bContextClip)
         {
            
            CGContextClip(pgraphics);
            
         }
         
         clip(m_spregion);
         
         CGPoint myStartPoint, myEndPoint;
         
         CGContextTranslateCTM(pgraphics, pbrush->m_pt.x, pbrush->m_pt.y);
         
         CGContextScaleCTM(pgraphics, pbrush->m_size.cx, pbrush->m_size.cy);
         
         myStartPoint.x = 0;
         
         myStartPoint.y = 0;
         
         myEndPoint.x = 0;
         
         myEndPoint.y = 0;
         
         CGContextDrawRadialGradient(pgraphics, (CGGradientRef) pbrush->get_os_data(), myStartPoint, 0, myEndPoint, 1.0f, kCGGradientDrawsBeforeStartLocation);
         
      }
      else if(pbrush->m_etype == ::draw2d::brush::type_linear_gradient_point_color)
      {
         
         if(bContextClip)
         {
            
            CGContextClip(pgraphics);
            
         }

         clip(m_spregion);
         
         CGPoint myStartPoint, myEndPoint;
         
         myStartPoint.x = pbrush->m_pt1.x;
         
         myStartPoint.y = pbrush->m_pt1.y;
         
         myEndPoint.x = pbrush->m_pt2.x;
         
         myEndPoint.y = pbrush->m_pt2.y;
         
         CGContextDrawLinearGradient(pgraphics, (CGGradientRef) pbrush->get_os_data(), myStartPoint, myEndPoint, 0);
         
      }
      else if(pbrush->m_etype == ::draw2d::brush::type_pattern)
      {
         
         if(bContextClip)
         {
            
            CGContextClip(pgraphics);
            
         }

         clip(m_spregion);
         
         BitBlt(0, 0, pbrush->m_dib->m_size.cx, pbrush->m_dib->m_size.cy, pbrush->m_dib->get_graphics(), 0,0, 0);
         
         //CGContextRestoreGState(pgraphics);
         
      }
      else
      {
         
         if(m_spregion.is_null())
         {
            
            CGContextSetFillColorWithColor(pgraphics, (CGColorRef) pbrush->get_os_data());
            
            CGContextFillPath(pgraphics);
            
         }
         else
         {

            CGContextSetFillColorWithColor(pgraphics, (CGColorRef) pbrush->get_os_data());
            
            if(bContextClip)
            {
               
               CGContextClip(pgraphics);
               
            }

            clip(m_spregion);
            
            CGContextAddRect(pgraphics, CGContextGetClipBoundingBox(pgraphics));
            
            CGContextFillPath(pgraphics);
            
         }
         
      }
      
      return true;
      
   }


   bool graphics::draw(::draw2d::pen * ppen)
   {

      if(ppen == NULL || ppen->m_etype == ::draw2d::pen::type_null)
         return true;

      //if(ppen->m_etype == ::draw2d::pen::type_solid)
      {
         

         CGContextSaveGState(m_pdc);

         set(ppen);
         
         if(ppen->m_etype == ::draw2d::pen::type_brush && ppen->m_br.is_set()
            && (ppen->m_br->m_etype == ::draw2d::brush::type_linear_gradient_point_color
                || ppen->m_br->m_etype == ::draw2d::brush::type_radial_gradient_color
                || ppen->m_br->m_etype == ::draw2d::brush::type_pattern)
            )
         {
            
            CGContextReplacePathWithStrokedPath(m_pdc);
            
            // Turn the fillable path in to a clipping region.
//            CGContextClip(m_pdc);
            
            fill(ppen->m_br);

         }
         else
         {

            CGContextStrokePath(m_pdc);
            
         }

         CGContextRestoreGState(m_pdc);

      }

      return true;

   }
   
   
   bool graphics::draw(::draw2d::brush * pbrush)
   {
      
      if(pbrush == NULL || pbrush->m_etype == ::draw2d::brush::type_null)
         return true;
      
      //if(ppen->m_etype == ::draw2d::pen::type_solid)
      {
         
         
         CGContextSaveGState(m_pdc);
         
         set(pbrush);
         
         if(pbrush->m_etype == ::draw2d::brush::type_linear_gradient_point_color
                || pbrush->m_etype == ::draw2d::brush::type_radial_gradient_color
                || pbrush->m_etype == ::draw2d::brush::type_pattern)
            
         {
            
            CGContextReplacePathWithStrokedPath(m_pdc);
            
            // Turn the fillable path in to a clipping region.
            //CGContextClip(m_pdc);
            
            fill(pbrush);
            
         }
         else
         {
            
            CGContextStrokePath(m_pdc);
            
         }
         
         CGContextRestoreGState(m_pdc);
         
      }
      
      return true;
      
   }


   bool graphics::set(const ::draw2d::path * ppathParam)
   {
      
      if(ppathParam == NULL)
      {
         
         return false;
         
      }
      
      if(m_pdc == NULL)
      {
         
         return false;
         
      }

      CGContextBeginPath(m_pdc);

      CGContextAddPath(m_pdc, (CGMutablePathRef) ppathParam->get_os_data());

      return true;

   }
   
   
   bool graphics::draw_inline(const ::draw2d::path * ppath, ::draw2d::pen * ppen)
   {

      for(int32_t i = 0; i < ppath->m_elementa.get_count(); i++)
      {

         draw_inline(ppath->m_elementa(i), ppen);

      }

      return true;

   }
   
   
   bool graphics::fill_inline(const ::draw2d::path * ppath, ::draw2d::brush * pbrush)
   {

      for(int32_t i = 0; i < ppath->m_elementa.get_count(); i++)
      {

         fill_inline(ppath->m_elementa(i), pbrush);

      }

      return true;

   }



   bool graphics::set(const ::draw2d_quartz2d::path::element & e)
   {

      switch(e.m_etype)
      {
         case ::draw2d::path::element::type_arc:
            set(e.u.m_arc);
            break;
         case ::draw2d::path::element::type_line:
            set(e.u.m_line);
            break;
         case ::draw2d::path::element::type_string:
           // set(e.m_stringpath);
            break;
         case ::draw2d::path::element::type_end:
//            cairo_close_path(m_pdc);
            break;
         default:
            break;
      }

      return false;

   }
   

   bool graphics::draw_inline(const ::draw2d_quartz2d::path::element & e, ::draw2d::pen * ppen)
   {

      switch(e.m_etype)
      {
         case ::draw2d::path::element::type_string:
          draw_inline(e.m_stringpath, ppen);
            break;
         default:
            break;
      }

      return false;

   }
   
   
   bool graphics::fill_inline(const ::draw2d_quartz2d::path::element & e, ::draw2d::brush * pbrush)
   {

      switch(e.m_etype)
      {
         case ::draw2d::path::element::type_string:
            fill_inline(e.m_stringpath, pbrush);
            break;
         default:
         break;
      }

      return false;

   }

   bool graphics::set(const ::draw2d_quartz2d::path::arc & a)
   {

//      cairo_translate(m_pdc, a.m_xCenter, a.m_yCenter);
//
//      cairo_scale(m_pdc, 1.0, a.m_dRadiusY / a.m_dRadiusX);
//
//      cairo_arc(m_pdc, 0.0, 0.0, a.m_dRadiusX, a.m_dAngle1, a.m_dAngle2);
//
//      cairo_scale(m_pdc, 1.0, a.m_dRadiusX / a.m_dRadiusY);
//
//      cairo_translate(m_pdc, -a.m_xCenter, -a.m_yCenter);

      return true;

   }

   bool graphics::set(const ::draw2d_quartz2d::path::line & l)
   {

//      if(!cairo_has_current_point(m_pdc))
//      {
//
//         cairo_move_to(m_pdc, l.m_x, l.m_y);
//
//      }
//      else
//      {
//
//         cairo_line_to(m_pdc, l.m_x, l.m_y);
//
//      }

      return true;

   }


   bool graphics::set(const ::draw2d_quartz2d::path::move & p)
   {

//      cairo_move_to(m_pdc, p.m_x, p.m_y);


      return true;

   }

   bool graphics::set(const ::draw2d_quartz2d::path::string_path & stringpath)
   {
      return true;

   }
   
   
   bool graphics::draw_inline(const ::draw2d_quartz2d::path::string_path & stringpath, ::draw2d::pen * ppen)
   {

      string str(stringpath.m_strText);
      
      synch_lock ml(m_pmutex);
      
      double dx;
      
      double dy;
      
      dx = 0.;

      dy = 0.;

      str.replace("\t", "        ");

      stringa stra;
         
      stra.add_lines(str);
         
      int offsety = 0;
      
      CGFloat ascent, descent, leading, width;
      
      for(auto str : stra)
      {
            
         internal_show_text(stringpath.m_x + dx,stringpath.m_y + dy + offsety, 0, DT_TOPLEFT, str, (int)str.get_length(), kCGTextStroke, true, &ascent, &descent, &leading, &width, ppen, NULL, stringpath.m_spfont);
            
         offsety += ascent + descent + leading;
         
//         if(leading <= 0)
//         {
//            
//            offsety += descent;
//            
//         }
         
      }
         
      return true;

   }
   
   
   bool graphics::fill_inline(const ::draw2d_quartz2d::path::string_path & stringpath, ::draw2d::brush * pbrush)
   {
      
      string str(stringpath.m_strText);
      
      synch_lock ml(m_pmutex);
      
      double dx;
      
      double dy;
      
      dx = 0.;

      dy = 0.;

      str.replace("\t", "        ");
         
      stringa stra;
         
      stra.add_lines(str);
         
      int offsety = 0;
      
      CGFloat ascent, descent, leading, width;
      
      for(auto str : stra)
      {
            
         internal_show_text(stringpath.m_x + dx, stringpath.m_y + dy + offsety, 0, DT_TOPLEFT,  str, (int)str.get_length(), kCGTextFill, true, &ascent, &descent, &leading, &width, NULL, pbrush, stringpath.m_spfont);
            
         offsety += ascent + descent + leading;
         
//         if(leading <= 0)
//         {
//
//            offsety += descent;
//
//         }
         
      }
      
      return true;

   }


   bool graphics::fill()
   {

      if(m_spbrush.is_set())
         m_spbrush->defer_update();

      return fill(m_spbrush);

   }

   bool graphics::draw()
   {

      return draw(m_sppen);

   }

   void graphics::internal_set_fill_color(COLORREF cr)
   {

      CGContextSetRGBFillColor(m_pdc, argb_get_r_value(cr) / 255.0f, argb_get_g_value(cr) / 255.0f, argb_get_b_value(cr) / 255.0f, argb_get_a_value(cr) / 255.0f);

   }


   void graphics::enum_fonts(::draw2d::font::enum_item_array & itema)
   {
      
      char ** p;
      
      unsigned long c = apple_get_fonts(&p);
      
      if(c > 0)
      {
         
         for(unsigned long ui = 0; ui < c; ui++)
         {
            
            itema.add(canew(::draw2d::font::enum_item(p[ui], p[ui],::draw2d::font::cs_default)));
            
            free(p[ui]);
            
         }
         
         free(p);
         
      }
      
   }

   
   bool graphics::draw_text(const string & strParam,const RECTD & lpRect,UINT nFormat)
   {
      
      string str(strParam);
      
      synch_lock ml(m_pmutex);
      
      //double dx;
      
      //double dy;
      
      
      if(nFormat & DT_EXPANDTABS)
      {
         
         str.replace("\t", "        ");
         
      }
      else
      {
         
         str.replace("\t", "");
         
      }
      
      
      double y;
      
      if(nFormat & DT_BOTTOM)
      {
       
         y = lpRect.bottom;
         
      }
      else if(nFormat & DT_VCENTER)
      {
         
         y = lpRect.top + ::height(lpRect) / 2.0;
         
      }
      else
      {
         
         y = lpRect.top;
         
      }
      
         
      
      if(nFormat & DT_SINGLELINE)
      {
         
         str.replace("\r\n", " ");
         
         str.replace("\n", " ");
         
         str.replace("\r", " ");
         
         internal_show_text(
                            lpRect.left,
                            y,
                            ::width(lpRect),
                            nFormat,
                            str,
                            (int) str.get_length(),
                            kCGTextFill,
                            true,
                            NULL,
                            NULL,
                            NULL,
                            NULL,
                            NULL,
                            m_spbrush,
                            m_spfont);

      }
      else
      {
         
         stringa stra;
         
         stra.add_lines(str);
         
         //CGFloat ascent, descent, leading, width;
         
         CGFloat ascent, descent, leading;
         
         if(!(nFormat & DT_BOTTOM) && ! (nFormat & DT_VCENTER))
         {
         
            for(auto str : stra)
            {
            
               internal_show_text(
                               lpRect.left,
                               y,
                               ::width(lpRect),
                               nFormat,
                               str,
                               (int) str.get_length(),
                               kCGTextFill,
                               true,
                               &ascent,
                               &descent,
                               &leading,
                               NULL,
                               NULL,
                               m_spbrush,
                               m_spfont);
            
               y += ascent + descent + leading;
            
//               if(leading <= 0)
//               {
//
//                  y += descent;
//
//               }
               
            }
            
         }
         else if(nFormat & DT_BOTTOM)
         {
               
            for(auto str : stra)
            {
                  
               internal_show_text(
                                  lpRect.left,
                                  y,
                                  ::width(lpRect),
                                  nFormat,
                                  str,
                                  (int) str.get_length(),
                                  kCGTextFill,
                                  true,
                                  &ascent,
                                  &descent,
                                  &leading,
                                  NULL,
                                  NULL,
                                  m_spbrush,
                                  m_spfont);
                  
                  y -= ascent + descent + leading;
                  
//                  if(leading <= 0)
//                  {
//
//                     y -= descent;
//
//                  }
               
               }
            
            }
            else if(nFormat & DT_VCENTER)
            {
               
               rectd rectUpper(lpRect);

               rectd rectLower(lpRect);
               
               rectUpper.bottom = y;
               
               rectLower.top = y;

               if(stra.get_count() % 2 == 1)
               {
                  
                  internal_show_text(
                                     lpRect.left,
                                     y,
                                     ::width(lpRect),
                                     nFormat,
                                     stra[stra.get_middle_index()],
                                     (int) str.get_length(),
                                     kCGTextFill,
                                     true,
                                     &ascent,
                                     &descent,
                                     &leading,
                                     NULL,
                                     NULL,
                                     m_spbrush,
                                     m_spfont);
                  
                  double dy = ascent + descent + leading;
                  
//                  if(leading <= 0)
//                  {
//
//                     dy += descent;
//
//                  }
                  
                  rectUpper.bottom -= dy/2.0;
                  
                  rectLower.top += dy/2.0;
                  
               }
              
               if(stra.get_count() >= 2)
               {
                  
                  draw_text(
                            stra.implode("\n", 0, stra.get_middle_index() + 1),
                            rectUpper,
                            (nFormat & ~DT_VCENTER) | DT_BOTTOM);
                  
                  draw_text(
                            stra.implode("\n", stra.get_middle_index() + 1),
                            rectLower,
                            (nFormat & ~DT_VCENTER) | DT_TOP);
                  
               }
               
            }
            
         }
         
      return 1;
      
   }


   bool graphics::internal_show_text(::draw2d::font_sp spfont,::draw2d::brush_sp spbrush,::draw2d::pen_sp sppen, double x, double y, double wAlign, UINT nFormat, const char * lpszString, int32_t nCount, CGTextDrawingMode emode, bool bDraw, CGFloat * pascent, CGFloat * pdescent, CGFloat * pleading, CGFloat * pwidth)
   {
      
      synch_lock sl(m_pmutex);

      CGContextRef pgraphics = m_pdc;
   
      string str(lpszString, nCount);
   
      sp(::draw2d_quartz2d::font) f = spfont;
      
      synch_lock slFont(spfont->m_pmutex);
      
      if(str.trimmed().is_empty())
      {
         
         return true;
         
      }
      
      bool bFill = false;
      
      bool bStroke = false;
      
      COLORREF crFill;
      
      COLORREF crStroke;
      
      ::draw2d::brush * pbrush = NULL;
      
      bool bCacheLine = false;
      
      if(bDraw)
      {
         
         if(emode == kCGTextFill || emode == kCGTextFillStroke)
         {
            
            if(spbrush.is_set() &&
               (spbrush->m_etype == ::draw2d::brush::type_linear_gradient_point_color
                || spbrush->m_etype == ::draw2d::brush::type_radial_gradient_color
                || spbrush->m_etype == ::draw2d::brush::type_pattern))
            {
               
               pbrush = spbrush;
               
               emode = kCGTextClip;
               
            }
            else
            {
               
               bFill = true;
               
               crFill = spbrush.is_null() ? ARGB(255, 0, 0, 0) : spbrush->m_cr;

            }
            
         }
         
         if(emode == kCGTextStroke|| emode == kCGTextFillStroke)
         {

            bStroke = true;
               
            crStroke = sppen.is_null() ? ARGB(255, 0, 0, 0) : sppen->m_cr;
               
         }
            
      }
   
      if(!f->m_bUpdated)
      {
         
         f->destroy();
         
      }
      else if(!bDraw)
      {
         
         auto passoc = f->m_mapMetrics.PLookup(str);
         
         if(passoc != NULL)
         {
            
            ::draw2d_quartz2d::font::metrics & m = passoc->m_element2;
            
            m.get(pascent, pdescent, pleading, pwidth);
            
            return true;
            
         }
                                   
      }
      else if(strpbrk(str, "0123456789") == NULL)
      {
           
         auto passoc = f->m_mapMetrics.PLookup(str);
            
         if(passoc != NULL)
         {
            
            ::draw2d_quartz2d::font::metrics & m = passoc->m_element2;
               
            CTLineRef line = m.m_map[emode][crFill][crStroke];
               
            if(line != NULL)
            {
               
               m.align(x, y, wAlign, nFormat);
               
               CGContextSaveGState(pgraphics);
               
               internal_draw_text(emode, x, y + m.ascent, line, pbrush);
               
               CGContextRestoreGState(pgraphics);
               
               m.get(pascent, pdescent, pleading, pwidth);
                                     
               return true;
                  
            }
               
         }

         bCacheLine = true;
         
      }
      
      ::draw2d_quartz2d::font::metrics & m = f->m_mapMetrics[str];
      
      CFStringRef stringI = CFStringCreateWithCString(NULL, str, kCFStringEncodingUTF8);

      if(stringI == NULL)
      {
         
         return false;
         
      }
      
      CFStringRef string = CFStringCreateMutableCopy(NULL, 0, stringI);

      if(stringI == NULL)
      {
         
         CFRelease(stringI);
         
         return false;
         
      }

      CGContextSaveGState(pgraphics);
      
      
      array < CFTypeRef >  pkeys;
      
      array < CFTypeRef >  pvals;
      
      array < CFTypeRef >  cfrel;
      
      array < CGColorRef > crrel;

      if(f->m_fontName == NULL)
      {

         f->m_fontName = CFStringCreateWithCString(kCFAllocatorDefault, f->m_strFontFamilyName, kCFStringEncodingUTF8);
         
      }
   
      if(f->m_fontD == NULL)
      {
         
         array < CFTypeRef >  pkeyTraits;
         
         array < CFTypeRef >  pvalTraits;
         
         array < CFTypeRef >  pkeyAttrs;
         
         array < CFTypeRef >  pvalAttrs;
         
         CTFontSymbolicTraits symValue = 0;
         
         CTFontSymbolicTraits symMask = 0;
   
         int iWeight = f->m_iFontWeight;
         
         double dCoreTextWeight = nsfont_get_ctweight(iWeight);
         
         if(dCoreTextWeight != 0.0)
         {

            CFNumberRef dFontWeight = CFNumberCreate(kCFAllocatorDefault, kCFNumberDoubleType, &dCoreTextWeight);
            
            cfrel.add(dFontWeight);
            
            pkeyTraits.add(kCTFontWeightTrait);
            
            pvalTraits.add(dFontWeight);

            if(dCoreTextWeight > 0.0)
            {
               
               symValue |= kCTFontTraitBold;
               
               symMask |= kCTFontTraitBold;
               
            }

         }
         
         if(f->m_bItalic)
         {
            
            symValue |= kCTFontTraitItalic;
            
            symMask |= kCTFontTraitItalic;
            
         }
         
         CFDictionaryRef traits1 = NULL;
         
         if(pkeyTraits.has_elements())
         {
            
            traits1 = CFDictionaryCreate(
                                             kCFAllocatorDefault,
                                             pkeyTraits.get_data(),
                                             pvalTraits.get_data(),
                                             pkeyTraits.get_size(),
                                             &kCFTypeDictionaryKeyCallBacks,
                                             &kCFTypeDictionaryValueCallBacks);
            
            pkeyAttrs.add(kCTFontTraitsAttribute);
            
            pvalAttrs.add(traits1);
            
            cfrel.add(traits1);
            
         }

         CFDictionaryRef attributes1 = NULL;
         
         if(pkeyAttrs.has_elements())
         {
            
            attributes1 = CFDictionaryCreate(
                                                          kCFAllocatorDefault,
                                                          pkeyAttrs.get_data(),
                                                          pvalAttrs.get_data(),
                                                          pkeyAttrs.get_size(),
                                                          &kCFTypeDictionaryKeyCallBacks,
                                                          &kCFTypeDictionaryValueCallBacks);
            
            pkeyAttrs.add(kCTFontTraitsAttribute);
            
            pvalAttrs.add(traits1);

            
            cfrel.add(attributes1);
            
         }

         CTFontDescriptorRef fontdesc = CTFontDescriptorCreateWithNameAndSize(f->m_fontName, 48.f);
         
         if(symMask != 0)
         {
         
            CTFontDescriptorRef fontdescSym = CTFontDescriptorCreateCopyWithSymbolicTraits(fontdesc, symValue, symMask);
            
            if(fontdescSym != NULL)
            {
               
               CFRelease(fontdesc);
               
               fontdesc = fontdescSym;
               
            }
            
         }
         
         if(attributes1 != NULL)
         {
         
            
            f->m_fontD = CTFontDescriptorCreateCopyWithAttributes(fontdesc, attributes1);
            
            if(f->m_fontD != NULL)
            {
               
               f->m_fontD = fontdesc;
               
            }
            else
            {
         
               CFRelease(fontdesc);
               
            }
            
         }
         else
         {
            
            f->m_fontD = fontdesc;
            
         }
         
      }
   
      double dFontSize;
   
      if(spfont.is_null())
      {
      
         dFontSize = 12.0;
      
      }
      else
      {
      
         dFontSize = spfont->m_dFontSize;
      
      }
   
      if(f->m_font == NULL)
      {
   
         f->m_font =  CTFontCreateWithFontDescriptor(f->m_fontD, dFontSize, NULL);
      
      }

      pkeys.add(kCTFontAttributeName);
      
      pvals.add(f->m_font);
      
      if(f->m_bUnderline)
      {
         
         int iUnderlineStyle = kCTUnderlineStyleSingle;
         
         CFNumberRef num = CFNumberCreate(kCFAllocatorDefault, kCFNumberIntType, &iUnderlineStyle);
         
         cfrel.add(num);
         
         pkeys.add(kCTUnderlineStyleAttributeName);
         
         pvals.add(num);
         
      }

      if(emode != kCGTextInvisible && bDraw)
      {

         CGColorSpaceRef rgbColorSpace = CGColorSpaceCreateDeviceRGB();

         CGFloat components[4];

         if(bFill)
         {
         
            components[0] = argb_get_r_value(crFill) / 255.f;
            components[1] = argb_get_g_value(crFill) / 255.f;
            components[2] = argb_get_b_value(crFill) / 255.f;
            components[3] = argb_get_a_value(crFill) / 255.f;

            pkeys.add(kCTForegroundColorAttributeName);
            pvals.add(CGColorCreate(rgbColorSpace, components));
            crrel.add((CGColorRef)pvals.last());

         }
      
         if(bStroke)
         {

            double dStroke = sppen.is_null() ? 3.0 : sppen->m_dWidth * 100.0 / dFontSize;

            pkeys.add(kCTStrokeWidthAttributeName);
            pvals.add(CFNumberCreate(kCFAllocatorDefault, kCFNumberDoubleType, &dStroke));
            cfrel.add(pvals.last());

            components[0] = argb_get_r_value(crStroke) / 255.f;
            components[1] = argb_get_g_value(crStroke) / 255.f;
            components[2] = argb_get_b_value(crStroke) / 255.f;
            components[3] = argb_get_a_value(crStroke) / 255.f;

            pkeys.add(kCTStrokeColorAttributeName);
            pvals.add(CGColorCreate(rgbColorSpace, components));
            crrel.add((CGColorRef)pvals.last());

         }

         CGColorSpaceRelease(rgbColorSpace);

      }

      CFDictionaryRef attributes = CFDictionaryCreate(
                      kCFAllocatorDefault,
                      pkeys.get_data(),
                      pvals.get_data(),
                      pkeys.get_size(),
                      &kCFTypeDictionaryKeyCallBacks,
                      &kCFTypeDictionaryValueCallBacks);

      CFAttributedStringRef attrString = CFAttributedStringCreate(kCFAllocatorDefault, string, attributes);

      CTLineRef line = CTLineCreateWithAttributedString(attrString);

      CFRelease(string);
      
      CFRelease(stringI);
      
      CFRelease(attributes);

      m.width = CTLineGetTypographicBounds(line, &m.ascent,  &m.descent, &m.leading);

      if(bDraw)
      {
         
         m.align(x, y, wAlign, nFormat);

         internal_draw_text(emode, x, y + m.ascent, line, pbrush);
         
      }
      
      if(!bCacheLine)
      {

         CFRelease(line);
         
      }

      for(index i = 0; i < cfrel.count(); i++)
      {
      
         CFRelease(cfrel[i]);
   
      }

      for(index i = 0; i < crrel.count(); i++)
      {
      
         CGColorRelease(crrel[i]);
   
      }

      m.get(pascent, pdescent, pleading, pwidth);
   
      CGContextRestoreGState(pgraphics);
   
      if(bCacheLine)
      {
            
         m.m_map[emode][crFill][crStroke] = line;
            
      }
      
      f->m_bUpdated = true;
   
      return true;

   }
   
   
   void graphics::internal_draw_text(CGTextDrawingMode emode, double x, double y, CTLineRef line, ::draw2d::brush * pbrush)
   {
      
      CGContextRef pgraphics = m_pdc;
      
//      CGContextSetTextMatrix(pgraphics, CGAffineTransformScale(CGAffineTransformMakeTranslation(x, y), 1.f, -1.f));

      //CGContextTranslateCTM(pgraphics, x, y);
      //CGContextScaleCTM(pgraphics, 1.0, -1.0);
      
      CGContextSetTextMatrix(pgraphics, CGAffineTransformIdentity);
      CGContextTranslateCTM(pgraphics, x, y);
      CGContextScaleCTM(pgraphics, 1.0, -1.0);
//      CGContextSetTextMatrix(pgraphics, CGAffineTransformScale(CGAffineTransformMakeTranslation(x, y), 1.f, -1.f));
      CGContextSetTextDrawingMode(pgraphics, emode);
      
      CTLineDraw(line,pgraphics);
      
      CGContextScaleCTM(pgraphics, 1.0, -1.0);
      CGContextTranslateCTM(pgraphics, -x, -y);

      if(pbrush != NULL)
      {
      
         _fill(pbrush, false);
      
      }

   }
   

} // namespace draw2d_quartz2d






CGContextRef CGContextCreate(CGSize size)
{
	
    CGColorSpaceRef space = CGColorSpaceCreateDeviceRGB();
	
    CGContextRef ctx = CGBitmapContextCreate(nil, size.width, size.height, 8, size.width * (CGColorSpaceGetNumberOfComponents(space) + 1), space, kCGImageAlphaPremultipliedLast);

	CGColorSpaceRelease(space);

	return ctx;
    
}


