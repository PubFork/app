#pragma once


struct NSVGimage;

namespace draw2d
{


   class CLASS_DECL_AURA graphics :
      virtual public ::core::simple_chain < ::aura::draw_context >
   {
   public:


      ::aura::str_context *         m_puistrcontext;
      ::aura::draw_context *        m_pdrawcontext;
      ::draw2d::dib *               m_pdibAlphaBlend;
      point                         m_ptAlphaBlend;
      ::job *                       m_pjob;


      ::draw2d::dib *               m_pdibDraw2dGraphics;
      ::draw2d::bitmap_sp           m_spbitmap;
      ::draw2d::pen_sp              m_sppen;
      ::draw2d::brush_sp            m_spbrush;
      ::draw2d::font_sp             m_spfont;
      ::draw2d::region_sp           m_spregion;


      pointd                        m_pt;

      e_alpha_mode                  m_ealphamode;
      e_smooth_mode                 m_esmoothmode;
      e_text_rendering              m_etextrendering;
      f64                        m_dFontFactor;

      bool                          m_bPrinting;


      graphics(::aura::application * papp);
      virtual ~graphics();


      virtual void assert_valid() const override;
      virtual void dump(dump_context & dumpcontext) const override;




      void draw_ca2(int x,int y,int z,COLORREF crBk,COLORREF cr);
      void draw_ca2_with_border(int x,int y,int z,int b,COLORREF crBk,COLORREF cr,COLORREF crOut);
      void draw_ca2_border2(int x,int y,int z,int bOut,int bIn,COLORREF crBk,COLORREF cr,COLORREF crBorderOut,COLORREF crIn);
      void draw_ca2_with_border2(int x,int y,int z,int bOut,int bIn,COLORREF crBk,COLORREF cr,COLORREF crBorderOut,COLORREF crIn);


      virtual bool is_set();

      virtual void * get_os_data() const;
      virtual void * get_os_data_ex(int i) const;
      virtual void release_os_data_ex(int i, void * p);

      template < typename T >
      T * get_typed_os_data(int i) const
      {
         return (T *) get_os_data_ex(i);
      }

      virtual bool attach(void * pdata);
      virtual void * detach();


//      virtual bool attach(HDC hdc);
//      virtual HDC detach();


      virtual bool prefer_mapped_dib_on_mix();


      virtual ::aura::str_context * str_context();
      virtual ::aura::draw_context * draw_context();


      virtual void set_alpha_mode(e_alpha_mode ealphamode);

      virtual void set_smooth_mode(e_smooth_mode esmoothmode);

      virtual void set_text_rendering(e_text_rendering etextrendering);

      virtual bool blur(bool bExpand, f64 dRadius, const RECT & rect);

      virtual void set_solid_pen(f64 dWidth, COLORREF cr);

      virtual bool IsPrinting() const;            // TRUE if being used for printing

      virtual ::draw2d::pen_sp      get_current_pen() const;
      virtual ::draw2d::brush_sp    get_current_brush() const;
      virtual ::draw2d::palette_sp  get_current_palette() const;
      virtual ::draw2d::font_sp     get_current_font() const;
      virtual ::draw2d::bitmap_sp   get_current_bitmap() const;

      // for bidi and mirrored localization
      virtual u32 GetLayout() const;
      virtual u32 SetLayout(u32 dwLayout);

      // Constructors
      virtual bool CreateDC(const char * lpszDriverName, const char * lpszDeviceName, const char * lpszOutput, const void * lpInitData);
      virtual bool CreateIC(const char * lpszDriverName, const char * lpszDeviceName, const char * lpszOutput, const void * lpInitData);
      virtual bool CreateCompatibleDC(::draw2d::graphics * pgraphics);
      virtual bool CreateWindowDC(oswindow wnd);

      virtual void on_begin_draw(oswindow wnd, SIZE sz);
      virtual void on_end_draw(oswindow wnd);

      virtual bool DeleteDC();


      // Device-Context Functions
      virtual i32 SaveDC();
      virtual bool RestoreDC(i32 nSavedDC);
      virtual i32 GetDeviceCaps(i32 nIndex) const;
      virtual UINT SetBoundsRect(const RECT & rectBounds,UINT flags);
      virtual UINT GetBoundsRect(LPRECT rectBounds,UINT flags);
#ifdef WINDOWS
      virtual bool ResetDC(const DEVMODE* lpDevMode);
#endif

      // Drawing-Tool Functions
      virtual point GetBrushOrg() const;
      virtual point SetBrushOrg(i32 x, i32 y);
      virtual point SetBrushOrg(POINT point);
      virtual i32 EnumObjects(i32 nObjectType,
                              i32 (CALLBACK* lpfn)(LPVOID, LPARAM), LPARAM lpData);


      virtual bool set_text_color(COLORREF clr);

      // Type-safe selection helpers
   public:
      virtual ::draw2d::object* SelectStockObject(i32 nIndex);
      virtual ::draw2d::pen* SelectObject(::draw2d::pen* pPen);
      virtual ::draw2d::brush* SelectObject(::draw2d::brush* pBrush);
      virtual ::draw2d::font* SelectObject(::draw2d::font* pFont);
      virtual ::draw2d::bitmap* SelectObject(::draw2d::bitmap* pBitmap);
      virtual i32 SelectObject(::draw2d::region* pRgn);       // special return for regions


      // color and color Palette Functions
      virtual COLORREF GetNearestColor(COLORREF crColor) const;
      virtual ::draw2d::palette* SelectPalette(::draw2d::palette* pPalette, bool bForceBackground);
      virtual UINT RealizePalette();
      virtual void UpdateColors();

      // Drawing-Attribute Functions
      virtual i32 GetPolyFillMode() const;
      virtual i32 GetROP2() const;
      virtual i32 GetStretchBltMode() const;


      virtual f64 get_dpix() const;

      virtual i32 SetPolyFillMode(i32 nPolyFillMode);
      virtual i32 SetROP2(i32 nDrawMode);
      virtual i32 SetStretchBltMode(i32 nStretchMode);


      virtual bool flush();
      virtual bool sync_flush();





#ifdef WINDOWSEX
      virtual bool GetColorAdjustment(LPCOLORADJUSTMENT lpColorAdjust) const;
      virtual bool SetColorAdjustment(const COLORADJUSTMENT* lpColorAdjust);
#endif

#if (_WIN32_WINNT >= 0x0500)

      virtual COLORREF GetDCBrushColor() const;
      virtual COLORREF SetDCBrushColor(COLORREF crColor);

      virtual COLORREF GetDCPenColor() const;
      virtual COLORREF SetDCPenColor(COLORREF crColor);

#endif

      // Graphics mode
      virtual i32 SetGraphicsMode(i32 iMode);
      virtual i32 GetGraphicsMode() const;

      // World transform
#ifdef WINDOWS
      virtual bool SetWorldTransform(const XFORM* pXform);
      virtual bool ModifyWorldTransform(const XFORM* pXform,u32 iMode);
      virtual bool GetWorldTransform(XFORM* pXform) const;
#endif

      // Mapping Functions
      virtual i32 GetMapMode() const;
      virtual point GetViewportOrg() const;
      virtual i32 SetMapMode(i32 nMapMode);
      // Viewport Origin
      virtual point SetViewportOrg(i32 x, i32 y);
      virtual point SetViewportOrg(POINT point);
      virtual point OffsetViewportOrg(i32 nWidth, i32 nHeight);

      // Viewport Extent
      virtual size GetViewportExt() const;
      virtual size SetViewportExt(i32 cx, i32 cy);
      virtual size SetViewportExt(SIZE size);
      virtual size ScaleViewportExt(i32 xNum, i32 xDenom, i32 yNum, i32 yDenom);

      // Window Origin
      virtual point GetWindowOrg() const;
      virtual point SetWindowOrg(i32 x, i32 y);
      virtual point SetWindowOrg(POINT point);
      virtual point OffsetWindowOrg(i32 nWidth, i32 nHeight);

      // Window extent
      virtual size GetWindowExt() const;
      virtual size SetWindowExt(i32 cx, i32 cy);
      virtual size SetWindowExt(SIZE size);
      virtual size ScaleWindowExt(i32 xNum, i32 xDenom, i32 yNum, i32 yDenom);

      // Coordinate Functions
      virtual void DPtoLP(LPPOINT lpPoints,count nCount = 1) const;
      virtual void DPtoLP(LPRECT lpRect) const;
      virtual void DPtoLP(LPSIZE lpSize) const;
      virtual void LPtoDP(LPPOINT lpPoints,count nCount = 1) const;
      virtual void LPtoDP(LPRECT lpRect) const;
      virtual void LPtoDP(LPSIZE lpSize) const;

      // Special Coordinate Functions (useful for dealing with metafiles and OLE)
      virtual void DPtoHIMETRIC(LPSIZE lpSize) const;
      virtual void LPtoHIMETRIC(LPSIZE lpSize) const;
      virtual void HIMETRICtoDP(LPSIZE lpSize) const;
      virtual void HIMETRICtoLP(LPSIZE lpSize) const;

      // Region Functions
      virtual bool FillRgn(::draw2d::region* pRgn, ::draw2d::brush* pBrush);
      virtual bool FrameRgn(::draw2d::region* pRgn, ::draw2d::brush* pBrush, i32 nWidth, i32 nHeight);
      virtual bool InvertRgn(::draw2d::region* pRgn);
      virtual bool PaintRgn(::draw2d::region* pRgn);

      // Clipping Functions
      virtual i32 GetClipBox(LPRECT lpRect) const;
      virtual i32 GetClipBox(rect64 * lpRect) const;
      virtual bool PtVisible(i32 x, i32 y) const;
      virtual bool PtVisible(POINT point) const;
      virtual bool RectVisible(const RECT & rect) const;
      virtual i32 SelectClipRgn(::draw2d::region* pRgn);
      virtual i32 ExcludeClipRect(i32 x1, i32 y1, i32 x2, i32 y2);
      virtual i32 ExcludeClipRect(const RECT & rect);
//      virtual i32 ExcludeUpdateRgn(::window_sp pwindow);
      virtual i32 IntersectClipRect(i32 x1, i32 y1, i32 x2, i32 y2);
      virtual i32 IntersectClipRect(const RECT & rect);
      virtual i32 OffsetClipRgn(i32 x, i32 y);
      virtual i32 OffsetClipRgn(SIZE size);
      virtual i32 SelectClipRgn(::draw2d::region* pRgn, i32 nMode);


      virtual pointd current_position();

      virtual bool move_to(LPCPOINT point);
      virtual bool move_to(LPCPOINTD point);

      virtual bool line_to(LPCPOINT point);
      virtual bool line_to(LPCPOINTD point);

      virtual bool draw_line(LPCPOINT ppt1, LPCPOINT ppt2);
      virtual bool draw_line(LPCPOINT ppt1, LPCPOINT ppt2, ::draw2d::pen * ppen);

      virtual bool draw_line(LPCPOINTD ppt1, LPCPOINTD ppt2);
      virtual bool draw_line(LPCPOINTD ppt1, LPCPOINTD ppt2, ::draw2d::pen * ppen);

      virtual bool draw_error_line(LPCPOINT ppt1, LPCPOINT ppt2, i32 iStyle);
      virtual bool draw_error_line(LPCPOINTD ppt1, LPCPOINTD ppt2, i32 iStyle);



      virtual bool draw_rectangle(LPCRECT lpcrect);
      virtual bool draw_rectangle(LPCRECT lpcrect,::draw2d::pen * ppen);
      virtual bool draw_rectangle(LPCRECTD lpcrect);
      virtual bool draw_rectangle(LPCRECTD lpcrect, ::draw2d::pen * ppen);




      virtual bool Arc(i32 x1, i32 y1, i32 x2, i32 y2, i32 x3, i32 y3, i32 x4, i32 y4);
      virtual bool Arc(const RECT & rect,POINT ptStart,POINT ptEnd);
      virtual bool Arc(i32 x1, i32 y1, i32 x2, i32 y2, f64 start, f64 extends);
      virtual bool Arc(const RECT & rect,f64 start,f64 extends);
      virtual bool Polyline(const POINT* lpPoints,count nCount);


      virtual bool Arc(f64 x1,f64 y1,f64 x2,f64 y2,f64 x3,f64 y3,f64 x4,f64 y4);
      virtual bool Arc(const RECTD & lpRect,POINTD ptStart,POINTD ptEnd);
      virtual bool Arc(f64 x1,f64 y1,f64 x2,f64 y2,f64 start,f64 extends);
      virtual bool Arc(const RECTD & lpRect,f64 start,f64 extends);

      virtual bool AngleArc(i32 x, i32 y, i32 nRadius, float fStartAngle, float fSweepAngle);
      virtual bool ArcTo(i32 x1, i32 y1, i32 x2, i32 y2, i32 x3, i32 y3, i32 x4, i32 y4);
      virtual bool ArcTo(const RECT & rect,POINT ptStart,POINT ptEnd);
      virtual i32 GetArcDirection() const;
      virtual i32 SetArcDirection(i32 nArcDirection);

      virtual bool PolyDraw(const POINT* lpPoints, const BYTE* lpTypes,count nCount);
      virtual bool PolylineTo(const POINT* lpPoints,count nCount);
      virtual bool PolyPolyline(const POINT* lpPoints, const INT * lpPolyPoints,count nCount);

      virtual bool PolyBezier(const POINT* lpPoints,count nCount);
      virtual bool PolyBezierTo(const POINT* lpPoints,count nCount);

      // Simple Drawing Functions
      virtual void FillRect(const RECT & ect,::draw2d::brush* pBrush);
      virtual void FrameRect(const RECT & ect,::draw2d::brush* pBrush);
      virtual void InvertRect(const RECT &  lpRect);
      virtual bool DrawIcon(i32 x, i32 y, ::visual::icon * picon);
      virtual bool DrawIcon(POINT point, ::visual::icon * picon);
      virtual bool DrawIcon(i32 x, i32 y, ::visual::icon * picon, i32 cx, i32 cy, UINT istepIfAniCur, HBRUSH hbrFlickerFreeDraw, UINT diFlags);
      virtual bool DrawState(point pt, size size, HBITMAP hBitmap, UINT nFlags,
                             HBRUSH hBrush = NULL);
      virtual bool DrawState(point pt, size size, ::draw2d::bitmap* pBitmap, UINT nFlags,
                             ::draw2d::brush* pBrush = NULL);
#ifdef WINDOWS
      virtual bool DrawState(point pt, size size, HICON hIcon, UINT nFlags,
                             HBRUSH hBrush = NULL);
      virtual bool DrawState(point pt, size size, HICON hIcon, UINT nFlags,
                             ::draw2d::brush* pBrush = NULL);
#endif
      virtual bool DrawState(point pt, size size, const char * lpszText, UINT nFlags,
                             bool bPrefixText = TRUE, i32 nTextLen = 0, HBRUSH hBrush = NULL);
      virtual bool DrawState(point pt, size size, const char * lpszText, UINT nFlags,
                             bool bPrefixText = TRUE, i32 nTextLen = 0, ::draw2d::brush* pBrush = NULL);
#ifdef WINDOWSEX
      virtual bool DrawState(point pt, size size, DRAWSTATEPROC lpDrawProc,
                             LPARAM lData, UINT nFlags, HBRUSH hBrush = NULL);
      virtual bool DrawState(point pt, size size, DRAWSTATEPROC lpDrawProc,
                             LPARAM lData, UINT nFlags, ::draw2d::brush* pBrush = NULL);
#endif
      // Ellipse and Polygon Functions
      virtual bool Chord(i32 x1, i32 y1, i32 x2, i32 y2, i32 x3, i32 y3,
                         i32 x4, i32 y4);
      virtual bool Chord(const RECT &  lpRect, POINT ptStart, POINT ptEnd);
      virtual void DrawFocusRect(const RECT &  lpRect);
      virtual bool Ellipse(i32 x1, i32 y1, i32 x2, i32 y2);
      virtual bool Ellipse(const RECT &  lpRect);
      virtual bool DrawEllipse(i32 x1, i32 y1, i32 x2, i32 y2);
      virtual bool DrawEllipse(const RECT &  lpRect);
      virtual bool FillEllipse(i32 x1, i32 y1, i32 x2, i32 y2);
      virtual bool FillEllipse(const RECT &  lpRect);


      virtual bool Ellipse(f64 x1,f64 y1,f64 x2,f64 y2);
      virtual bool Ellipse(const RECTD & lpRect);
      virtual bool DrawEllipse(f64 x1,f64 y1,f64 x2,f64 y2);
      virtual bool DrawEllipse(const RECTD & lpRect);
      virtual bool FillEllipse(f64 x1,f64 y1,f64 x2,f64 y2);
      virtual bool FillEllipse(const RECTD & lpRect);

      virtual bool Pie(i32 x1, i32 y1, i32 x2, i32 y2, i32 x3, i32 y3, i32 x4, i32 y4);
      virtual bool Pie(const RECT &  lpRect, POINT ptStart, POINT ptEnd);
      virtual bool fill_polygon(const POINTD * lpPoints,count nCount);
      virtual bool fill_polygon(const POINT* lpPoints,count nCount);
      virtual bool fill_polygon(point_array & pta);
      virtual bool fill_polygon(pointd_array & pta);
      virtual bool draw_polygon(const POINT* lpPoints,count nCount);
      virtual bool draw_polygon(const POINTD* lpPoints,count nCount);
      virtual bool draw_polygon(point_array & pta);
      virtual bool draw_polygon(pointd_array & pta);
      virtual bool Polygon(point_array & pta);
      virtual bool Polygon(pointd_array & pta);
      virtual bool Polygon(const POINT* lpPoints,count nCount);
      virtual bool Polygon(const POINTD* lpPoints,count nCount);
      virtual bool PolyPolygon(const POINT* lpPoints,const INT * lpPolyCounts,count nCount);
      virtual bool Rectangle(i32 x1, i32 y1, i32 x2, i32 y2);
      virtual bool Rectangle(const RECT &  lpRect);
      virtual bool DrawRectangle(i32 x1, i32 y1, i32 x2, i32 y2);
      virtual bool DrawRectangle(const RECT &  lpRect);
      virtual bool FillRectangle(i32 x1, i32 y1, i32 x2, i32 y2);
      virtual bool FillRectangle(const RECT &  lpRect);
      virtual bool RoundRect(i32 x1, i32 y1, i32 x2, i32 y2, i32 x3, i32 y3);
      virtual bool RoundRect(const RECT &  lpRect, POINT point);

      // Bitmap Functions
      virtual bool from(point ptDst, size size, ::draw2d::graphics * pgraphicsSrc, point ptSrc, u32 dwRop);
      virtual bool from(size size, ::draw2d::graphics * pgraphicsSrc, point ptSrc, u32 dwRop);
      virtual bool from(size size, ::draw2d::graphics * pgraphicsSrc, u32 dwRop);
      virtual bool PatBlt(i32 x, i32 y, i32 nWidth, i32 nHeight, u32 dwRop);

      virtual bool BitBlt(i32 x, i32 y, i32 nWidth, i32 nHeight, ::draw2d::graphics * pgraphicsSrc, i32 xSrc = 0, i32 ySrc = 0, u32 dwRop = SRCCOPY);
      virtual bool BitBlt(const RECT &  lpcrect, ::draw2d::graphics * pgraphicsSrc, POINT ptSrc = ::null_point(), u32 dwRop = SRCCOPY);
      virtual bool BitBlt(POINT ptDst, SIZE size, ::draw2d::graphics * pgraphicsSrc, POINT ptSrc = ::null_point(), u32 dwRop = SRCCOPY);

      virtual bool BitBltRaw(i32 x, i32 y, i32 nWidth, i32 nHeight, ::draw2d::graphics * pgraphicsSrc, i32 xSrc = 0, i32 ySrc = 0, u32 dwRop = SRCCOPY);
      virtual bool BitBltAlphaBlend(i32 x, i32 y, i32 nWidth, i32 nHeight, ::draw2d::graphics * pgraphicsSrc, i32 xSrc = 0, i32 ySrc = 0, u32 dwRop = SRCCOPY);

      virtual bool StretchBlt(rect rectDst, ::draw2d::graphics * pgraphicsSrc);

      virtual bool StretchBlt(rect rectDst, ::draw2d::graphics * pgraphicsSrc, rect rectSrc, u32 dwRop = SRCCOPY);

      virtual bool StretchBlt(i32 x, i32 y, i32 nWidth, i32 nHeight, ::draw2d::graphics * pgraphicsSrc, i32 xSrc, i32 ySrc, i32 nSrcWidth, i32 nSrcHeight, u32 dwRop = SRCCOPY);

      virtual bool StretchBltRaw(i32 x, i32 y, i32 nWidth, i32 nHeight, ::draw2d::graphics * pgraphicsSrc, i32 xSrc, i32 ySrc, i32 nSrcWidth, i32 nSrcHeight, u32 dwRop = SRCCOPY);
      virtual bool StretchBltAlphaBlend(i32 x, i32 y, i32 nWidth, i32 nHeight, ::draw2d::graphics * pgraphicsSrc, i32 xSrc, i32 ySrc, i32 nSrcWidth, i32 nSrcHeight, u32 dwRop = SRCCOPY);

      virtual COLORREF GetPixel(i32 x, i32 y) const;
      virtual COLORREF GetPixel(POINT point) const;
      virtual COLORREF SetPixel(i32 x, i32 y, COLORREF crColor);
      virtual COLORREF SetPixel(POINT point, COLORREF crColor);
      virtual bool FloodFill(i32 x, i32 y, COLORREF crColor);
      virtual bool ExtFloodFill(i32 x, i32 y, COLORREF crColor, UINT nFillType);
      virtual bool MaskBlt(i32 x, i32 y, i32 nWidth, i32 nHeight, ::draw2d::graphics * pgraphicsSrc,
                           i32 xSrc, i32 ySrc, ::draw2d::bitmap& maskBitmap, i32 xMask, i32 yMask,
                           u32 dwRop);
      virtual bool PlgBlt(LPPOINT lpPoint, ::draw2d::graphics * pgraphicsSrc, i32 xSrc, i32 ySrc,
                          i32 nWidth, i32 nHeight, ::draw2d::bitmap& maskBitmap, i32 xMask, i32 yMask);
      virtual bool SetPixelV(i32 x, i32 y, COLORREF crColor);
      virtual bool SetPixelV(POINT point, COLORREF crColor);
      virtual bool GradientFill(TRIVERTEX* pVertices, WINULONG nVertices,
                                void * pMesh, WINULONG nMeshElements, u32 dwMode);
      virtual bool TransparentBlt(i32 xDest, i32 yDest, i32 nDestWidth, i32 nDestHeight,
                                  ::draw2d::graphics * pgraphicsSrc, i32 xSrc, i32 ySrc, i32 nSrcWidth, i32 nSrcHeight,
                                  UINT clrTransparent);

      virtual bool alpha_blend(i32 xDest, i32 yDest, i32 nDestWidth, i32 nDestHeight, ::draw2d::graphics * pgraphicsSrc, i32 xSrc, i32 ySrc, i32 nSrcWidth, i32 nSrcHeight, f64 dOpacity);
      virtual bool alpha_blend(point ptDst, size szDst,::draw2d::graphics * pgraphicsSrc, point ptSrc, size szSrc, f64 dOpacity);
      virtual bool alpha_blend(point ptDst, size sz,::draw2d::graphics * pgraphicsSrc, point ptSrc, f64 dOpacity);
      virtual bool alpha_blend(point ptDst, size sz,::draw2d::graphics * pgraphicsSrc, f64 dOpacity);
      virtual bool alpha_blend(rect & r, ::draw2d::graphics * pgraphicsSrc, f64 dOpacity);
      virtual bool alpha_blend(size sz,::draw2d::graphics * pgraphicsSrc, point ptSrc, f64 dOpacity);
      virtual bool alpha_blend(size sz,::draw2d::graphics * pgraphicsSrc, f64 dOpacity);

      virtual bool alpha_blendRaw(i32 xDest, i32 yDest, i32 nDestWidth, i32 nDestHeight, ::draw2d::graphics * pgraphicsSrc, i32 xSrc, i32 ySrc, i32 nSrcWidth, i32 nSrcHeight, f64 dRate);
      virtual bool alpha_blendAlphaBlend(i32 xDest, i32 yDest, i32 nDestWidth, i32 nDestHeight, ::draw2d::graphics * pgraphicsSrc, i32 xSrc, i32 ySrc, i32 nSrcWidth, i32 nSrcHeight, f64 dRate);


      /*      virtual bool alpha_blend(i32 xDest, i32 yDest, i32 nDestWidth, i32 nDestHeight,
              ::draw2d::graphics * pgraphicsSrc, i32 xSrc, i32 ySrc, i32 nSrcWidth, i32 nSrcHeight,
              BLENDFUNCTION blend);*/
      /*      virtual bool alpha_blend(point ptDst, size szDst,::draw2d::graphics * pgraphicsSrc, point ptSrc, size szSrc, BLENDFUNCTION blend);
            virtual bool alpha_blend(point ptDst, size sz,::draw2d::graphics * pgraphicsSrc, point ptSrc, BLENDFUNCTION blend);
            virtual bool alpha_blend(point ptDst, size sz,::draw2d::graphics * pgraphicsSrc, BLENDFUNCTION blend);
            virtual bool alpha_blend(size sz,::draw2d::graphics * pgraphicsSrc, point ptSrc, BLENDFUNCTION blend);
            virtual bool alpha_blend(size sz,::draw2d::graphics * pgraphicsSrc, BLENDFUNCTION blend);*/

      // Text Functions
      virtual bool text_out(i32 x, i32 y, const char * lpszString, strsize nCount);
      virtual bool text_out(i32 x, i32 y, const string & str);
      virtual bool text_out(f64 x, f64 y, const char * lpszString, strsize nCount);
      virtual bool text_out(f64 x, f64 y, const string & str);
      virtual bool ExtTextOut(i32 x, i32 y, UINT nOptions, const RECT &  lpRect, const char * lpszString, strsize nCount, LPINT lpDxWidths);
      virtual bool ExtTextOut(i32 x, i32 y, UINT nOptions, const RECT &  lpRect, const string & str, LPINT lpDxWidths);
      virtual size TabbedTextOut(i32 x, i32 y, const char * lpszString, strsize nCount, count nTabPositions, LPINT lpnTabStopPositions, i32 nTabOrigin);
      virtual size TabbedTextOut(i32 x, i32 y, const string & str, count nTabPositions, LPINT lpnTabStopPositions, i32 nTabOrigin);


      virtual bool TextOutRaw(f64 x, f64 y, const char * lpszString, strsize nCount);
      virtual bool TextOutAlphaBlend(f64 x, f64 y, const char * lpszString, strsize nCount);


      virtual i32 draw_text(const char * lpszString,strsize nCount,const RECT & lpRect,UINT nFormat);
      virtual i32 draw_text(const string & str, const RECT & lpRect, UINT nFormat);
      virtual i32 draw_text(const char * lpszString,strsize nCount,const RECTD & lpRect,UINT nFormat);
      virtual i32 draw_text(const string & str,const RECTD & lpRect,UINT nFormat);

#ifndef METROWIN
      virtual i32 draw_text_ex(const char * lpszString,strsize nCount,const RECT & lpRect,UINT nFormat,LPDRAWTEXTPARAMS lpDTParams);
      virtual i32 draw_text_ex(const string & str,const RECT & lpRect,UINT nFormat,LPDRAWTEXTPARAMS lpDTParams);
      virtual i32 draw_text_ex(const char * lpszString,strsize nCount,const RECTD & lpRect,UINT nFormat,LPDRAWTEXTPARAMS lpDTParams);
      virtual i32 draw_text_ex(const string & str,const RECTD & lpRect,UINT nFormat,LPDRAWTEXTPARAMS lpDTParams);
#endif

      virtual ::count GetEachCharTextExtent(array < size > & sizea, const string & str, strsize iStart = 0, strsize iCount = -1);
      virtual sized GetTextExtent(const char * lpszString, strsize nCount, strsize iIndex) const;
      virtual sized GetTextBegin(const char * lpszString, strsize nCount, strsize iIndex) const;
      virtual sized GetTextExtent(const char * lpszString, strsize nCount) const;
      virtual sized GetTextExtent(const string & str) const;
      virtual bool GetTextExtent(sized & size, const char * lpszString, strsize nCount, strsize iIndex) const;
      virtual bool GetTextExtent(sized & size, const char * lpszString, strsize nCount) const;
      virtual bool GetTextExtent(sized & size, const string & str) const;
      virtual size GetOutputTextExtent(const char * lpszString, strsize nCount) const;
      virtual size GetOutputTextExtent(const string & str) const;
      virtual size GetTabbedTextExtent(const char * lpszString, strsize nCount, count nTabPositions, LPINT lpnTabStopPositions) const;
      virtual size GetTabbedTextExtent(const string & str, count nTabPositions, LPINT lpnTabStopPositions) const;
      virtual size GetOutputTabbedTextExtent(const char * lpszString, strsize nCount, count nTabPositions, LPINT lpnTabStopPositions) const;
      virtual size GetOutputTabbedTextExtent(const string & str, count nTabPositions, LPINT lpnTabStopPositions) const;
      virtual bool GrayString(::draw2d::brush* pBrush, bool (CALLBACK* lpfnOutput)(HDC, LPARAM, i32), LPARAM lpData, i32 nCount, i32 x, i32 y, i32 nWidth, i32 nHeight);
      virtual UINT GetTextAlign() const;
      virtual UINT SetTextAlign(UINT nFlags);
      virtual i32 GetTextFace(count nCount, LPTSTR lpszFacename) const;
      virtual i32 GetTextFace(string & rString) const;


      virtual bool get_text_metrics(text_metric * lpMetrics) const;
      virtual bool get_output_text_metrics(text_metric * lpMetrics) const;


      virtual i32 SetTextJustification(i32 nBreakExtra, i32 nBreakCount);
      virtual i32 GetTextCharacterExtra() const;
      virtual i32 SetTextCharacterExtra(i32 nCharExtra);

#ifdef WINDOWSEX

      virtual u32 GetCharacterPlacement(const char * lpString, strsize nCount, strsize nMaxExtent, LPGCP_RESULTS lpResults, u32 dwFlags) const;
      virtual u32 GetCharacterPlacement(string & str, strsize nMaxExtent, LPGCP_RESULTS lpResults, u32 dwFlags) const;

#endif

#if (_WIN32_WINNT >= 0x0500)

      virtual bool GetTextExtentExPointI(LPWORD pgiIn, i32 cgi, i32 nMaxExtent, LPINT lpnFit, LPINT alpDx, __out_opt LPSIZE lpSize) const;
      virtual bool GetTextExtentPointI(LPWORD pgiIn, i32 cgi, __out_opt LPSIZE lpSize) const;

#endif



      // Advanced Drawing
      virtual bool DrawEdge(const RECT & lpRect,UINT nEdge,UINT nFlags);
      virtual bool DrawFrameControl(const RECT & lpRect,UINT nType,UINT nState);

      // Scrolling Functions
      virtual bool ScrollDC(i32 dx, i32 dy, const RECT &  lpRectScroll, const RECT &  lpRectClip,
                            ::draw2d::region* pRgnUpdate, LPRECT lpRectUpdate);

      // font Functions
      virtual bool GetCharWidth(UINT nFirstChar, UINT nLastChar, LPINT lpBuffer) const;
      virtual bool GetOutputCharWidth(UINT nFirstChar, UINT nLastChar, LPINT lpBuffer) const;
      virtual u32 SetMapperFlags(u32 dwFlag);
      virtual size GetAspectRatioFilter() const;

#ifdef WINDOWSEX

      virtual bool GetCharABCWidths(UINT nFirstChar, UINT nLastChar, LPABC lpabc) const;

#endif

      virtual u32 GetFontData(u32 dwTable, u32 dwOffset, LPVOID lpData, u32 cbData) const;

#ifdef WINDOWSEX

      virtual i32 GetKerningPairs(i32 nPairs, LPKERNINGPAIR lpkrnpair) const;
      virtual UINT GetOutlineTextMetrics(UINT cbData, LPOUTLINETEXTMETRICW lpotm) const;
      virtual u32 GetGlyphOutline(UINT nChar, UINT nFormat, LPGLYPHMETRICS lpgm, u32 cbBuffer, LPVOID lpBuffer, const MAT2* lpmat2) const;

      virtual bool GetCharABCWidths(UINT nFirstChar, UINT nLastChar, LPABCFLOAT lpABCF) const;

#endif

      virtual bool GetCharWidth(UINT nFirstChar, UINT nLastChar, float * lpFloatBuffer) const;

      virtual u32 GetFontLanguageInfo() const;

#if defined(WINDOWSEX) && (_WIN32_WINNT >= 0x0500)

      virtual bool GetCharABCWidthsI(UINT giFirst, UINT cgi, LPWORD pgi, LPABC lpabc) const;
      virtual bool GetCharWidthI(UINT giFirst, UINT cgi, LPWORD pgi, LPINT lpBuffer) const;

#endif

      // Printer/Device Escape Functions
      virtual i32 Escape(i32 nEscape, i32 nCount, const char * lpszInData, LPVOID lpOutData);
      virtual i32 Escape(i32 nEscape, i32 nInputSize, const char * lpszInputData, i32 nOutputSize, char * lpszOutputData);
      virtual i32 DrawEscape(i32 nEscape, i32 nInputSize, const char * lpszInputData);

      // Escape helpers
      virtual i32 StartDoc(const char * lpszDocName);  // old Win3.0 version

#ifdef WINDOWSEX

      virtual i32 StartDoc(LPDOCINFO lpDocInfo);

#endif

      virtual i32 StartPage();
      virtual i32 EndPage();
      virtual i32 SetAbortProc(bool (CALLBACK* lpfn)(HDC, i32));
      virtual i32 AbortDoc();
      virtual i32 EndDoc();

      // MetaFile Functions
#ifdef WINDOWS
      virtual bool PlayMetaFile(HMETAFILE hMF);
      virtual bool PlayMetaFile(HENHMETAFILE hEnhMetaFile, const RECT &  lpBounds);
#endif
      virtual bool AddMetaFileComment(UINT nDataSize, const BYTE* pCommentData);
      // can be used for enhanced metafiles only

      virtual bool abort_path();
      virtual bool begin_path();
      virtual bool close_figure();
      virtual bool end_path();
      virtual bool fill_path();
      virtual bool flatten_path();
      virtual bool stroke_and_fill_path();
      virtual bool stroke_path();
      virtual bool widen_path();
      virtual float GetMiterLimit() const;
      virtual bool SetMiterLimit(float fMiterLimit);
      virtual i32 GetPath(LPPOINT lpPoints, LPBYTE lpTypes,count nCount) const;
      virtual bool SelectClipPath(i32 nMode);

      virtual bool draw_path(::draw2d::path * ppath, ::draw2d::pen * ppen);
      virtual bool draw_path(::draw2d::path * ppath);
      virtual bool fill_path(::draw2d::path * ppath, ::draw2d::brush * pbrush);
      virtual bool fill_path(::draw2d::path * ppath);
      virtual bool path(::draw2d::path * ppath);

      // Misc Helper Functions
      virtual ::draw2d::brush * GetHalftoneBrush();
      virtual void DrawDragRect(const RECT &  lpRect, SIZE size,
                                const RECT &  lpRectLast, SIZE sizeLast,
                                ::draw2d::brush* pBrush = NULL, ::draw2d::brush* pBrushLast = NULL);
      virtual void FillSolidRect(const RECT64 * lpRect, COLORREF clr);
      virtual void FillSolidRect(const RECT &  lpRect, COLORREF clr);
      virtual void FillSolidRect(f64 x, f64 y, f64 cx, f64 cy, COLORREF clr);
      virtual void FillSolidRect(i32 x, i32 y, i32 cx, i32 cy, COLORREF clr);
      virtual void Draw3dRect(const RECT &  lpRect, COLORREF clrTopLeft, COLORREF clrBottomRight);
      virtual void Draw3dRect(i32 x, i32 y, i32 cx, i32 cy,
                              COLORREF clrTopLeft, COLORREF clrBottomRight);

      virtual bool SelectFont(::draw2d::font * pfont);
      virtual bool selectFont(::draw2d::font * pfont);
      virtual bool select_font(::draw2d::font * pfont);
      virtual bool SetFont(::draw2d::font * pfont);
      virtual bool setFont(::draw2d::font * pfont);
      virtual bool set_font(::draw2d::font * pfont);



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
      bool draw_round_rect(const RECT & r, ::draw2d::pen * ppen, i32 radius);
      bool draw_round_top_left(const RECT & r, ::draw2d::pen * ppen, i32 radius);
      bool draw_round_bottom_right(const RECT & r, ::draw2d::pen * ppen, i32 radius);

      bool draw_round_rect(const RECT & r, COLORREF color, i32 radius, i32 width);
      bool draw_round_top_left(const RECT & r, COLORREF color, i32 radius, i32 width);
      bool draw_round_bottom_right(const RECT & r, COLORREF color, i32 radius, i32 width);


      bool draw_stock_icon(const RECT & rect, e_stock_icon eicon);


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
      bool fill_round_rect(const RECT & r, COLORREF color, i32 radius);

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
      bool fill_round_rect(const RECT & r, ::draw2d::brush * pbrush, i32 radius);


      bool round_rect(const RECT & r, i32 radius);

      virtual i32 _DrawText(const char * lpcsz, strsize iCount, const RECT &  lpcrect, UINT uiFormat, ::draw2d::font * pfontUnderline = NULL);
      virtual i32 _DrawText(const string & str, const RECT &  lpcrect, UINT uiFormat, ::draw2d::font * pfontUnderline = NULL);

#ifdef WINDOWSEX

      virtual bool Attach(HDC hdc);
      virtual HDC Detach();
      virtual bool AttachPrinter(HDC hdc);
      virtual HDC DetachPrinter();

#endif

      virtual void debug();


      virtual void enum_fonts(::draw2d::font::enum_item_array & itema);
      virtual void sorted_fonts(::draw2d::font::enum_item_array & itema);


      virtual float nanosvg_distPtSeg(float x, float y, float px, float py, float qx, float qy);
      virtual void nanosvg_cubicBez(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, float tol, int level);
      virtual void nanosvg_drawPath(float* pts, int npts, char closed, float tol, COLORREF lineColor);
      virtual void nanosvg_drawControlPts(float* pts, int npts);
      virtual void nanosvg_drawframe(NSVGimage* pimage, int x, int y, int w, int h);
      // virtual void nanosvg_resizecb(int width, int height, int x, int y, int w, int h);

      virtual bool nanosvg(string str, int x, int y, int w, int h);

      virtual bool is_valid_update_window_thread();



   };

   class CLASS_DECL_AURA graphics_sp :
      public smart_pointer < graphics >
   {
   public:

      graphics_sp()
      {
      }

      graphics_sp(graphics * p) :
         smart_pointer < graphics > (p)
      {
      }


      graphics_sp(const smart_pointer < graphics > & p) :
         smart_pointer < graphics > (p)
      {
      }

      graphics_sp(const ::aura::allocatorsp & allocer) :
         smart_pointer < graphics > (allocer)
      {
      }

   };


   class CLASS_DECL_AURA memory_graphics :
      public graphics_sp
   {
   public:

      memory_graphics();
      memory_graphics(const ::aura::allocatorsp & allocer);
      void alloc(const ::aura::allocatorsp & allocer);
      virtual ~memory_graphics();

   };

   class CLASS_DECL_AURA savedc
   {
   public:


      graphics *     m_pgraphics;
      int            m_iSavedDC;

      savedc(graphics * pgraphics);
      ~savedc();


   };

} // namespace draw2d


#ifdef DEBUG

CLASS_DECL_AURA dump_context & operator<<(dump_context & dumpcontext, SIZE size);
CLASS_DECL_AURA dump_context & operator<<(dump_context & dumpcontext, POINT point);
CLASS_DECL_AURA dump_context & operator<<(dump_context & dumpcontext, const RECT& rect);

#endif



namespace draw2d
{


//#else
//
//
//   class device_lock
//   {
//   public:
//
//      device_lock()
//      {
//
//      }
//
//      ~device_lock()
//      {
//
//
//      }
//
//
//
//
//   };
//
//   class lock
//   {
//   public:
//
//      lock()
//      {
//
//      }
//
//      ~lock()
//      {
//
//
//      }
//
//
//
//
//   };
//
//
//#endif
//

} // namespace draw2d


