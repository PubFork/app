#pragma once



namespace draw2d_quartz2d
{
   
   class graphics;

   
   class brush;
   class pen;
   class font;
   class path;
   
   
   class CLASS_DECL_DRAW2D_QUARTZ2D graphics :
      virtual public ::draw2d::graphics
   {
   public:

      
      int                           m_iSaveDC;
      bool                          m_bOwnDC;
      CGContextRef                  m_pdc;
      CGLayerRef                    m_layer;
//      CGAffineTransform             m_affine;
      
      int32_t                       m_iType;
#ifdef __MM
      NSColor *                     m_nscolorFore;
      NSColor *                     m_nscolorBack;
#else
      void *                        m_pnscolorFore;
      void *                        m_pnscolorBack;
#endif
      
      bool                          m_bForeColor;
      bool                          m_bBackColor;
      uint64_t                      m_uiForeColor;
      uint64_t                      m_uiBackColor;
      bool                          m_bPrinting;
      
      
      graphics(::aura::application * papp);
      virtual ~graphics();
      
      
      /* xxx      Gdiplus::Graphics & g()
       {
       if(m_pgraphics == NULL)
       {
       m_pgraphics = ::Gdiplus::Graphics::FromHDC(get_handle1());
       }
       return *m_pgraphics;
       }*/
      
      //::user::window * GetWindow() const;
      
      //static ::draw2d::graphics * PASCAL from_handle(HDC hDC);
      //static void PASCAL DeleteTempMap();
      //bool Attach(HDC hdc);   // Attach/Detach affects only the Output DC
      //HDC Detach();
      
      //virtual void SetAttribDC(HDC hDC);  // Set the Attribute DC
      //virtual void SetOutputDC(HDC hDC);  // Set the Output DC
      //virtual void ReleaseAttribDC();     // Release the Attribute DC
      //virtual void ReleaseOutputDC();     // Release the Output DC
      
      bool IsPrinting() override;            // TRUE if being used for printing
      
      ::draw2d::pen_sp get_current_pen() override;
      ::draw2d::brush_sp get_current_brush() override;
      ::draw2d::palette_sp get_current_palette() override;
      ::draw2d::font_sp get_current_font() override;
      ::draw2d::bitmap_sp get_current_bitmap() override;
      
      
      //pen *       COCOA_pen();
      //brush *     COCOA_brush();
      //font *      COCOA_font();
      
      // for bidi and mirrored localization
      DWORD GetLayout() override;
      DWORD SetLayout(DWORD dwLayout) override;
      
      
      virtual double get_dpix() override;
      
      // Constructors
      bool CreateDC(const char * lpszDriverName, const char * lpszDeviceName, const char * lpszOutput, const void * lpInitData) override;
      bool CreateIC(const char * lpszDriverName, const char * lpszDeviceName, const char * lpszOutput, const void * lpInitData) override;
      bool CreateCompatibleDC(::draw2d::graphics * pgraphics) override;
      
      bool DeleteDC() override;
      
      // Device-Context Functions
      virtual int32_t SaveDC() override;
      virtual bool RestoreDC(int32_t nSavedDC) override;
      int32_t GetDeviceCaps(int32_t nIndex) override;
      UINT SetBoundsRect(const RECT & lpRectBounds, UINT flags) override;
      UINT GetBoundsRect(LPRECT lpRectBounds, UINT flags) override;
      // xxx      bool ResetDC(const DEVMODE* lpDevMode);
      
      // Drawing-Tool Functions
      point GetBrushOrg() override;
      point SetBrushOrg(int32_t x, int32_t y) override;
      point SetBrushOrg(POINT point) override;
      int32_t EnumObjects(int32_t nObjectType,
                          int32_t (CALLBACK* lpfn)(LPVOID, LPARAM), LPARAM lpData) override;
      
      // Type-safe selection helpers
   public:
      virtual ::draw2d::object* SelectStockObject(int32_t nIndex) override;
      ::draw2d::pen* SelectObject(::draw2d::pen* pPen) override;
      ::draw2d::brush* SelectObject(::draw2d::brush* pBrush) override;
      virtual ::draw2d::font* SelectObject(::draw2d::font* pFont) override;
      ::draw2d::bitmap* SelectObject(::draw2d::bitmap* pBitmap) override;
      int32_t SelectObject(::draw2d::region* pRgn) override;       // special return for regions
      ::draw2d::object* SelectObject(::draw2d::object* pObject);
      
      
      // ::draw2d::object* provided so compiler doesn't use SelectObject(HGDIOBJ)
      
      virtual bool SelectFont(::draw2d::font * pfont) override;

      
      // color and color Palette Functions
      COLORREF GetNearestColor(COLORREF crColor) override;
      ::draw2d::palette* SelectPalette(::draw2d::palette* pPalette, bool bForceBackground) override;
      UINT RealizePalette() override;
      void UpdateColors() override;
      
      // Drawing-Attribute Functions
      COLORREF GetBkColor() const;
      int32_t GetBkMode() const;
      int32_t GetPolyFillMode() override;
      int32_t GetROP2() override;
      int32_t GetStretchBltMode() override;
      
      virtual COLORREF SetBkColor(COLORREF crColor);
      int32_t SetBkMode(int32_t nBkMode);
      int32_t SetPolyFillMode(int32_t nPolyFillMode) override;
      int32_t SetROP2(int32_t nDrawMode) override;
      int32_t SetStretchBltMode(int32_t nStretchMode) override;
      
      // xxx      bool GetColorAdjustment(LPCOLORADJUSTMENT lpColorAdjust) const;
      // xxx      bool SetColorAdjustment(const COLORADJUSTMENT* lpColorAdjust);
      
#if (_WIN32_WINNT >= 0x0500)
      
      COLORREF GetDCBrushColor() const;
      COLORREF SetDCBrushColor(COLORREF crColor);
      
      COLORREF GetDCPenColor() const;
      COLORREF SetDCPenColor(COLORREF crColor);
      
#endif
      
      // Graphics mode
      int32_t SetGraphicsMode(int32_t iMode) override;
      int32_t GetGraphicsMode() override;
      
      // World transform
      bool SetWorldTransform(const XFORM* pXform);
      bool ModifyWorldTransform(const XFORM* pXform,DWORD iMode);
      bool GetWorldTransform(XFORM* pXform) const;
      
      // Mapping Functions
      virtual int32_t GetMapMode() override;
      virtual point GetViewportOrg() override;
      virtual int32_t SetMapMode(int32_t nMapMode) override;
      // Viewport Origin
      virtual point SetViewportOrg(int32_t x, int32_t y) override;
      virtual point SetViewportOrg(POINT point) override;
      virtual point OffsetViewportOrg(int32_t nWidth, int32_t nHeight) override;
      
      // Viewport Extent
      virtual size GetViewportExt() override;
      virtual size SetViewportExt(int32_t cx, int32_t cy) override;
      virtual size SetViewportExt(SIZE size) override;
      virtual size ScaleViewportExt(int32_t xNum, int32_t xDenom, int32_t yNum, int32_t yDenom) override;
      
      // Window Origin
      point GetWindowOrg() override;
      point SetWindowOrg(int32_t x, int32_t y) override;
      point SetWindowOrg(POINT point) override;
      point OffsetWindowOrg(int32_t nWidth, int32_t nHeight) override;
      
      // Window extent
      size GetWindowExt() override;
      virtual size SetWindowExt(int32_t cx, int32_t cy) override;
      size SetWindowExt(SIZE size) override;
      virtual size ScaleWindowExt(int32_t xNum, int32_t xDenom, int32_t yNum, int32_t yDenom) override;
      
      // Coordinate Functions
      void DPtoLP(LPPOINT lpPoints, int32_t nCount = 1) const;
      void DPtoLP(LPRECT lpRect) override;
      void DPtoLP(LPSIZE lpSize) override;
      void LPtoDP(LPPOINT lpPoints, int32_t nCount = 1) const;
      void LPtoDP(LPRECT lpRect) override;
      void LPtoDP(LPSIZE lpSize) override;
      
      // Special Coordinate Functions (useful for dealing with metafiles and OLE)
      void DPtoHIMETRIC(LPSIZE lpSize) override;
      void LPtoHIMETRIC(LPSIZE lpSize) override;
      void HIMETRICtoDP(LPSIZE lpSize) override;
      void HIMETRICtoLP(LPSIZE lpSize) override;
      
      // Region Functions
      bool FillRgn(::draw2d::region* pRgn, ::draw2d::brush* pBrush) override;
      bool FrameRgn(::draw2d::region* pRgn, ::draw2d::brush* pBrush, int32_t nWidth, int32_t nHeight) override;
      bool InvertRgn(::draw2d::region* pRgn) override;
      bool PaintRgn(::draw2d::region* pRgn) override;
      
      // Clipping Functions
      virtual int32_t GetClipBox(LPRECT lpRect) override;
      virtual bool PtVisible(int32_t x, int32_t y) override;
      virtual bool PtVisible(POINT point) override;
      virtual bool RectVisible(const RECT & lpRect) override;
      virtual int32_t SelectClipRgn(::draw2d::region* pRgn) override;
      virtual int32_t ExcludeClipRect(int32_t x1, int32_t y1, int32_t x2, int32_t y2) override;
      virtual int32_t ExcludeClipRect(const RECT & lpRect) override;
      //int32_t ExcludeUpdateRgn(::user::interaction * pWnd);
      virtual int32_t IntersectClipRect(int32_t x1, int32_t y1, int32_t x2, int32_t y2) override;
      virtual int32_t IntersectClipRect(const RECT & lpRect) override;
      virtual int32_t OffsetClipRgn(int32_t x, int32_t y) override;
      virtual int32_t OffsetClipRgn(SIZE size) override;
      virtual int32_t SelectClipRgn(::draw2d::region* pRgn, int32_t nMode) override;
      
      // Line-Output Functions
      virtual pointd current_position() override;
      //      point MoveTo(int32_t x, int32_t y);
      //    point MoveTo(POINT point);
      virtual bool line_to(LPCPOINTD lppt) override;
      //  bool LineTo(POINT point);
      virtual bool Arc(int32_t x1, int32_t y1, int32_t x2, int32_t y2, int32_t x3, int32_t y3, int32_t x4, int32_t y4) override;
      virtual bool Arc(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4) override;
      virtual bool Arc(double x, double y, double w, double h, double start, double end) override;
      virtual bool Arc(const RECT & lpRect, POINT ptStart, POINT ptEnd) override;
      virtual bool Polyline(const POINT* lpPoints, count nCount) override;
      
      virtual bool AngleArc(int32_t x, int32_t y, int32_t nRadius, float fStartAngle, float fSweepAngle) override;
      virtual bool ArcTo(int32_t x1, int32_t y1, int32_t x2, int32_t y2, int32_t x3, int32_t y3, int32_t x4, int32_t y4) override;
      virtual bool ArcTo(const RECT & lpRect, POINT ptStart, POINT ptEnd) override;
      virtual int32_t GetArcDirection() override;
      virtual int32_t SetArcDirection(int32_t nArcDirection) override;
      
      bool PolyDraw(const POINT* lpPoints, const BYTE* lpTypes, int32_t nCount);
      bool PolylineTo(const POINT* lpPoints, int32_t nCount);
      bool PolyPolyline(const POINT* lpPoints,
                        const DWORD* lpPolyPoints, int32_t nCount);
      
      bool PolyBezier(const POINT* lpPoints, int32_t nCount);
      bool PolyBezierTo(const POINT* lpPoints, int32_t nCount);
      
      // Simple Drawing Functions
      virtual bool fill_rect(LPCRECT lpcrect, ::draw2d::brush* pBrush) override;
      virtual void frame_rect(LPCRECT lpcrect, ::draw2d::brush* pBrush) override;
      
      virtual bool draw_rect(LPCRECT lpcrect, ::draw2d::pen* ppen) override;
      
      
      virtual void invert_rect(LPCRECT lpcrect) override;
      virtual bool DrawIcon(int32_t x, int32_t y, ::visual::icon * picon) override;
      virtual bool DrawIcon(POINT point, ::visual::icon * picon) override;
      virtual bool DrawIcon(int32_t x, int32_t y, ::visual::icon * picon, int32_t cx, int32_t cy, UINT istepIfAniCur, HBRUSH hbrFlickerFreeDraw, UINT diFlags) override;
      virtual bool DrawState(point pt, size size, HBITMAP hBitmap, UINT nFlags,
                     HBRUSH hBrush = NULL) override;
      virtual bool DrawState(point pt, size size, ::draw2d::bitmap* pBitmap, UINT nFlags,
                     ::draw2d::brush* pBrush = NULL) override;
/*      bool DrawState(point pt, size size, HICON hIcon, UINT nFlags,
                     HBRUSH hBrush = NULL);
      bool DrawState(point pt, size size, HICON hIcon, UINT nFlags,
                     ::draw2d::brush* pBrush = NULL);*/
      virtual bool DrawState(point pt, size size, const char * lpszText, UINT nFlags,
                     bool bPrefixText = TRUE, int32_t nTextLen = 0, HBRUSH hBrush = NULL) override;
      virtual bool DrawState(point pt, size size, const char * lpszText, UINT nFlags,
                     bool bPrefixText = TRUE, int32_t nTextLen = 0, ::draw2d::brush* pBrush = NULL) override;
      //xxx      bool DrawState(point pt, size size, DRAWSTATEPROC lpDrawProc,
      //xxx         LPARAM lData, UINT nFlags, HBRUSH hBrush = NULL);
      //xxx      bool DrawState(point pt, size size, DRAWSTATEPROC lpDrawProc,
      //xxx         LPARAM lData, UINT nFlags, ::draw2d::brush* pBrush = NULL);
      
      // Ellipse and Polygon Functions
      virtual bool Chord(int32_t x1, int32_t y1, int32_t x2, int32_t y2, int32_t x3, int32_t y3,
                 int32_t x4, int32_t y4) override;
      virtual bool Chord(const RECT & lpRect, POINT ptStart, POINT ptEnd) override;
      virtual void DrawFocusRect(const RECT & lpRect) override;

      bool DrawEllipse(int32_t x1, int32_t y1, int32_t x2, int32_t y2) override;
      bool DrawEllipse(const RECT & lpRect) override;
      
      bool FillEllipse(int32_t x1, int32_t y1, int32_t x2, int32_t y2) override;
      bool FillEllipse(const RECT & lpRect) override;
      
      bool DrawEllipse(double x1, double y1, double x2, double y2) override;
      bool DrawEllipse(const RECTD & lpRect) override;
      
      bool FillEllipse(double x1, double y1, double x2, double y2) override;
      bool FillEllipse(const RECTD & lpRect) override;
      
      bool Pie(int32_t x1, int32_t y1, int32_t x2, int32_t y2, int32_t x3, int32_t y3, int32_t x4, int32_t y4) override;
      bool Pie(const RECT & lpRect, POINT ptStart, POINT ptEnd) override;
      virtual bool set_polygon(const POINTD * lpPoints, count nCount);
      virtual bool set_polygon(const POINT * lpPoints, count nCount);
      virtual bool fill_polygon(const POINTD * lpPoints, count nCount) override;
      virtual bool fill_polygon(const POINT* lpPoints, count nCount) override;
      virtual bool polygon(LPCPOINTD lpPoints,count nCount) override;
      virtual bool rectangle(LPCRECTD lpcrect) override;
      virtual bool draw_rect(LPCRECTD lpcrect) override;
      virtual bool fill_rect(LPCRECTD lpRect) override;
      bool round_rect(LPCRECT lpcrect, LPCPOINT lppt) override;
      
      // Bitmap Functions
      bool PatBlt(int32_t x, int32_t y, int32_t nWidth, int32_t nHeight, DWORD dwRop) override;
      using ::draw2d::graphics::BitBlt;
      bool BitBltRaw(int32_t x, int32_t y, int32_t nWidth, int32_t nHeight, ::draw2d::graphics * pgraphicsSrc,
                  int32_t xSrc, int32_t ySrc, DWORD dwRop) override;
      bool StretchBltRaw(int32_t x, int32_t y, int32_t nWidth, int32_t nHeight, ::draw2d::graphics * pgraphicsSrc,
                      int32_t xSrc, int32_t ySrc, int32_t nSrcWidth, int32_t nSrcHeight, DWORD dwRop) override;
      COLORREF GetPixel(int32_t x, int32_t y) override;
      COLORREF GetPixel(POINT point) override;
      COLORREF SetPixel(int32_t x, int32_t y, COLORREF crColor) override;
      COLORREF SetPixel(POINT point, COLORREF crColor) override;
      bool FloodFill(int32_t x, int32_t y, COLORREF crColor) override;
      bool ExtFloodFill(int32_t x, int32_t y, COLORREF crColor, UINT nFillType) override;
      bool MaskBlt(int32_t x, int32_t y, int32_t nWidth, int32_t nHeight, ::draw2d::graphics * pgraphicsSrc,
                   int32_t xSrc, int32_t ySrc, ::draw2d::bitmap& maskBitmap, int32_t xMask, int32_t yMask,
                   DWORD dwRop) override;
      bool PlgBlt(LPPOINT lpPoint, ::draw2d::graphics * pgraphicsSrc, int32_t xSrc, int32_t ySrc,
                  int32_t nWidth, int32_t nHeight, ::draw2d::bitmap& maskBitmap, int32_t xMask, int32_t yMask) override;
      bool SetPixelV(int32_t x, int32_t y, COLORREF crColor) override;
      bool SetPixelV(POINT point, COLORREF crColor) override;
      bool GradientFill(TRIVERTEX* pVertices, WINULONG nVertices,
                        void * pMesh, WINULONG nMeshElements, DWORD dwMode) override;
      bool TransparentBlt(int32_t xDest, int32_t yDest, int32_t nDestWidth, int32_t nDestHeight,
                          ::draw2d::graphics * pgraphicsSrc, int32_t xSrc, int32_t ySrc, int32_t nSrcWidth, int32_t nSrcHeight,
                          UINT clrTransparent) override;
      
      virtual bool alpha_blendRaw(int32_t xDest, int32_t yDest, int32_t nDestWidth, int32_t nDestHeight, ::draw2d::graphics * pgraphicsSrc, int32_t xSrc, int32_t ySrc, int32_t nSrcWidth, int32_t nSrcHeight, double dOpacity) override;
      
      /*bool alpha_blend(int32_t xDest, int32_t yDest, int32_t nDestWidth, int32_t nDestHeight,
       ::draw2d::graphics * pgraphicsSrc, int32_t xSrc, int32_t ySrc, int32_t nSrcWidth, int32_t nSrcHeight,
       BLENDFUNCTION blend);*/
      
      // Text Functions
      virtual bool internal_show_text(double x, double y, double w, UINT nFormat, const char * lpszString, int32_t nCount, CGTextDrawingMode emode, bool bDraw = true, CGFloat * pascent = NULL, CGFloat * pdescent = NULL, CGFloat * pleading = NULL, CGFloat * pwidth = NULL, ::draw2d::pen * ppen=NULL, ::draw2d::brush * pbrush = NULL, ::draw2d::font * pfont = NULL);
      
      virtual bool internal_show_text(::draw2d::font_sp spfont,::draw2d::brush_sp spbrush,::draw2d::pen_sp sppen, double x, double y, double w, UINT nFormat, const char * lpszString, int32_t nCount, CGTextDrawingMode emode, bool bDraw = true, CGFloat * pascent = NULL, CGFloat * pdescent = NULL, CGFloat * pleading = NULL, CGFloat * pwidth = NULL);
      
      void internal_draw_text(CGTextDrawingMode emode, double x, double y, CTLineRef line, ::draw2d::brush * pbrush);
      
      virtual bool BitBltAlphaBlend(int32_t x, int32_t y, int32_t nWidth, int32_t nHeight, ::draw2d::graphics * pgraphicsSrc, int32_t xSrc, int32_t ySrc, uint32_t dwRop) override;
      
      
      virtual bool text_out(int32_t x, int32_t y, const char * lpszString, strsize nCount) override;
      
      virtual bool text_out(int32_t x, int32_t y, const string & str) override;
      virtual bool TextOutRaw(double x, double y, const char * lpszString, strsize nCount) override;
      virtual bool text_out(double x, double y, const string & str) override;
      virtual bool ExtTextOut(int32_t x, int32_t y, UINT nOptions, const RECT & lpRect,
                              const char * lpszString, UINT nCount, LPINT lpDxWidths);
      bool ExtTextOut(int32_t x, int32_t y, UINT nOptions, const RECT & lpRect,
                      const string & str, LPINT lpDxWidths) override;
      virtual size TabbedTextOut(int32_t x, int32_t y, const char * lpszString, int32_t nCount,
                                 int32_t nTabPositions, LPINT lpnTabStopPositions, int32_t nTabOrigin);
      size TabbedTextOut(int32_t x, int32_t y, const string & str,
                         int32_t nTabPositions, LPINT lpnTabStopPositions, int32_t nTabOrigin);
      
      virtual int32_t draw_text(const char * lpszString, int32_t nCount, const RECT & lpRect, UINT nFormat);
      virtual bool draw_text(const string & str, const RECT & lpRect, UINT nFormat) override;
      virtual bool draw_text(const string & strParam,const RECTD & lpRect,UINT nFormat) override;
      
      virtual int32_t draw_text_ex(LPTSTR lpszString, int32_t nCount, const RECT & lpRect, UINT nFormat, LPDRAWTEXTPARAMS lpDTParams);
      virtual bool draw_text_ex(const string & str, const RECT & lpRect, UINT nFormat, LPDRAWTEXTPARAMS lpDTParams) override;
      
      sized GetTextExtent(const char * lpszString, strsize nCount, int32_t iIndex);
      sized GetTextExtent(const char * lpszString, strsize nCount) override;
      sized GetTextExtent(const string & str) override;
      bool GetTextExtent(sized & size, const char * lpszString, strsize nCount, int32_t iIndex) ;
      bool GetTextExtent(sized & size, const char * lpszString, strsize nCount) override;
      bool GetTextExtent(sized & size, const string & str) override;
      size GetOutputTextExtent(const char * lpszString, strsize nCount) override;
      size GetOutputTextExtent(const string & str) override;
      size GetTabbedTextExtent(const char * lpszString, strsize nCount, int32_t nTabPositions, LPINT lpnTabStopPositions);
      size GetTabbedTextExtent(const string & str, int32_t nTabPositions, LPINT lpnTabStopPositions);
      size GetOutputTabbedTextExtent(const char * lpszString, strsize nCount, int32_t nTabPositions, LPINT lpnTabStopPositions);
      size GetOutputTabbedTextExtent(const string & str, int32_t nTabPositions, LPINT lpnTabStopPositions) ;
      virtual bool GrayString(::draw2d::brush* pBrush,
                              bool (CALLBACK* lpfnOutput)(HDC, LPARAM, int32_t), LPARAM lpData,
                              int32_t nCount, int32_t x, int32_t y, int32_t nWidth, int32_t nHeight) override;
      UINT GetTextAlign() override;
      UINT SetTextAlign(UINT nFlags) override;
      int32_t GetTextFace(int32_t nCount, LPTSTR lpszFacename);
      int32_t GetTextFace(string & rString) override;
       bool get_text_metrics(::draw2d::text_metric * lpMetrics) override;
       bool get_output_text_metrics(::draw2d::text_metric * lpMetrics) override;
      int32_t SetTextJustification(int32_t nBreakExtra, int32_t nBreakCount) override;
      int32_t GetTextCharacterExtra() override;
      int32_t SetTextCharacterExtra(int32_t nCharExtra) override;
      
      //xxx      DWORD GetCharacterPlacement(const char * lpString, int32_t nCount, int32_t nMaxExtent, LPGCP_RESULTS lpResults, DWORD dwFlags) const;
      //xxx      DWORD GetCharacterPlacement(string & str, int32_t nMaxExtent, LPGCP_RESULTS lpResults, DWORD dwFlags) const;
      
#if (_WIN32_WINNT >= 0x0500)
      
      bool GetTextExtentExPointI(LPWORD pgiIn, int32_t cgi, int32_t nMaxExtent, LPINT lpnFit, LPINT alpDx, __out_opt LPSIZE lpSize) const;
      bool GetTextExtentPointI(LPWORD pgiIn, int32_t cgi, __out_opt LPSIZE lpSize) const;
      
#endif
      
      
      
      // Advanced Drawing
      bool DrawEdge(LPRECT lpRect, UINT nEdge, UINT nFlags);
      bool DrawFrameControl(LPRECT lpRect, UINT nType, UINT nState);
      
      // Scrolling Functions
      bool ScrollDC(int32_t dx, int32_t dy, const RECT & lpRectScroll, const RECT & lpRectClip,
                    ::draw2d::region* pRgnUpdate, LPRECT lpRectUpdate) override;
      
      // font Functions
      bool GetCharWidth(UINT nFirstChar, UINT nLastChar, LPINT lpBuffer) override;
      bool GetOutputCharWidth(UINT nFirstChar, UINT nLastChar, LPINT lpBuffer) override;
      DWORD SetMapperFlags(DWORD dwFlag) override;
      size GetAspectRatioFilter() override;
      
      //xxx      bool GetCharABCWidths(UINT nFirstChar, UINT nLastChar, LPABC lpabc) const;
      DWORD GetFontData(DWORD dwTable, DWORD dwOffset, LPVOID lpData, DWORD cbData) override;
      //xxx      int32_t GetKerningPairs(int32_t nPairs, LPKERNINGPAIR lpkrnpair) const;
      //xxx      UINT GetOutlineTextMetrics(UINT cbData, LPOUTLINETEXTMETRIC lpotm) const;
      //xxx      DWORD GetGlyphOutline(UINT nChar, UINT nFormat, LPGLYPHMETRICS lpgm,
      //xxx    DWORD cbBuffer, LPVOID lpBuffer, const MAT2* lpmat2) const;
      
      //xxx      bool GetCharABCWidths(UINT nFirstChar, UINT nLastChar,
      //xxx         LPABCFLOAT lpABCF) const;
      bool GetCharWidth(UINT nFirstChar, UINT nLastChar,
                        float* lpFloatBuffer) override;
      
      DWORD GetFontLanguageInfo() override;
      
#if (_WIN32_WINNT >= 0x0500)
      
      bool GetCharABCWidthsI(UINT giFirst, UINT cgi, LPWORD pgi, LPABC lpabc) const;
      bool GetCharWidthI(UINT giFirst, UINT cgi, LPWORD pgi, LPINT lpBuffer) const;
      
#endif
      
      // Printer/Device Escape Functions
      virtual int32_t Escape(int32_t nEscape, int32_t nCount, const char * lpszInData, LPVOID lpOutData) override;
      int32_t Escape(int32_t nEscape, int32_t nInputSize, const char * lpszInputData, int32_t nOutputSize, char * lpszOutputData) override;
      int32_t DrawEscape(int32_t nEscape, int32_t nInputSize, const char * lpszInputData) override;
      
      // Escape helpers
      int32_t StartDoc(const char * lpszDocName) override;  // old Win3.0 version
      //xxx      int32_t StartDoc(LPDOCINFO lpDocInfo);
      int32_t StartPage() override;
      int32_t EndPage() override;
      int32_t SetAbortProc(bool (CALLBACK* lpfn)(HDC, int32_t)) override;
      int32_t AbortDoc() override;
      int32_t EndDoc() override;
      
      // MetaFile Functions
      //xxx      bool PlayMetaFile(HMETAFILE hMF);
      bool PlayMetaFile(HENHMETAFILE hEnhMetaFile, const RECT & lpBounds);
      bool AddMetaFileComment(UINT nDataSize, const BYTE* pCommentData) override;
      // can be used for enhanced metafiles only
      
      // Path Functions
      virtual bool abort_path() override;
      virtual bool begin_path() override;
      virtual bool close_figure() override;
      virtual bool end_path() override;
      virtual bool fill_path() override;
      virtual bool flatten_path() override;
      virtual bool stroke_and_fill_path() override;
      virtual bool stroke_path() override;
      virtual bool widen_path() override;
      
      bool draw_path(::draw2d::path * ppath) override;
      bool fill_path(::draw2d::path * ppath) override;
      
      bool draw_path(::draw2d::path * ppath, ::draw2d::pen * ppen) override;
      bool fill_path(::draw2d::path * ppath, ::draw2d::brush * pbrush) override;

      bool draw_inline_path(::draw2d::path * ppath, ::draw2d::pen * ppen);
      bool fill_inline_path(::draw2d::path * ppath, ::draw2d::brush * pbrush);
      
      
      float GetMiterLimit() override;
      bool SetMiterLimit(float fMiterLimit) override;
      int32_t GetPath(LPPOINT lpPoints, LPBYTE lpTypes, int32_t nCount) ;
      bool SelectClipPath(int32_t nMode) override;
      
      // Misc Helper Functions
      static ::draw2d::brush* PASCAL GetHalftoneBrush(::base::application * papp);
      void DrawDragRect(const RECT & lpRect, SIZE size,
                        const RECT & lpRectLast, SIZE sizeLast,
                        ::draw2d::brush* pBrush = NULL, ::draw2d::brush* pBrushLast = NULL) override;
      virtual void fill_solid_rect(LPCRECT lpcrect, COLORREF clr) override;
      virtual void draw3d_rect(LPCRECT lpRect, COLORREF clrTopLeft, COLORREF clrBottomRight) override;
      
      virtual void assert_valid() const override;
      virtual void dump(dump_context & dumpcontext) const override;
      
      virtual void set_alpha_mode(::draw2d::e_alpha_mode ealphamode) override;
      
      virtual void set_text_rendering(::draw2d::e_text_rendering etextrendering) override;
      
      virtual void * get_os_data() const override;
      //      virtual HDC get_handle() const;
      //    virtual HDC get_handle1() const;
      //  virtual HDC get_handle2() const;
      
      virtual bool attach(void * pdata) override;
      virtual void * detach() override;
      
      
      //xxx      virtual Gdiplus::FillMode gdiplus_get_fill_mode();
      
      bool blur(bool bExpand, double dRadius, const RECT & lpcrect) override;
      
     
      
      // platform-specific or platform-internals
      bool clip(const ::draw2d::region * pregion);
      bool add_path(const ::draw2d::region * pregion);
      bool set(const ::draw2d::brush * pbrush);
      bool set_pen(const ::draw2d::brush * pbrush, double dWidth);
      bool set(const ::draw2d::pen * ppen);
      //bool set(const ::draw2d::font * pfont);
      bool set(const ::draw2d::path * ppath);
      bool set(const ::draw2d::path::element & e);
      bool set(const ::draw2d::path::arc & arc);
      bool set(const ::draw2d::path::move & move);
      bool set(const ::draw2d::path::line & line);
      bool fill_inline(const ::draw2d::path * ppath, ::draw2d::brush * pbrush);
      bool draw_inline(const ::draw2d::path * ppath, ::draw2d::pen * ppen);
      bool fill_inline(const ::draw2d::path::element & e, ::draw2d::brush * pbrush);
      bool draw_inline(const ::draw2d::path::element & e, ::draw2d::pen * ppen);
      bool set(const ::draw2d::path::string_path & stringpath);
      bool fill_inline(const ::draw2d::path::string_path & stringpath, ::draw2d::brush * pbrush);
      bool draw_inline(const ::draw2d::path::string_path & stringpath, ::draw2d::pen * ppen);
      bool fill_and_draw(::draw2d::brush * pbrush, ::draw2d::pen * ppen);
      bool fill(::draw2d::brush * pbrush);
      bool draw(::draw2d::brush * pbrush);
      bool draw(::draw2d::pen * ppen);
      bool fill_and_draw();
      bool fill();
      bool draw();
      
      
      void internal_set_fill_color(COLORREF cr);
      
      
      virtual void enum_fonts(::draw2d::font::enum_item_array & itema) override;
      
   };
   
   
} // namespace draw2d_quartz2d





