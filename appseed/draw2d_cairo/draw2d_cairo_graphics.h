#pragma once


typedef void FN_CAIRO_TEXT(cairo_t *, const char*);
typedef FN_CAIRO_TEXT * PFN_CAIRO_TEXT;

#if defined(USE_PANGO)

typedef void FN_PANGO_TEXT(cairo_t *cr, PangoLayout *layout) override;
typedef FN_PANGO_TEXT * PFN_PANGO_TEXT;

#endif

namespace draw2d_cairo
{


   class brush;
   class pen;
   class font;
   class object;


   class CLASS_DECL_DRAW2D_CAIRO graphics :
      virtual public ::draw2d::graphics
   {
   public:


      int                        m_iSaveDC;
      int                        m_iSaveDCPositiveClip;
      cairo_t *                  m_pdc;
      int32_t                    m_iType;
      bool                       m_bPrinting;
      int                        m_nStretchBltMode;

#ifdef WINDOWS
      cairo_surface_t *          m_psurfaceAttach;
      HDC                        m_hdcAttach;
#endif

      graphics();
      graphics(::aura::application * papp);
      virtual ~graphics();



      virtual void * detach();

      bool IsPrinting() override;            // TRUE if being used for printing

      ::draw2d::pen_sp     get_current_pen() override;
      ::draw2d::brush_sp   get_current_brush() override;
      ::draw2d::palette_sp get_current_palette() override;
      ::draw2d::font_sp    get_current_font() override;
      ::draw2d::bitmap_sp  get_current_bitmap() override;


      //pen *       lnx_pen();
      //brush *     lnx_brush();
      //font *      lnx_font();

      // for bidi and mirrored localization
      uint32_t GetLayout() override;
      uint32_t SetLayout(uint32_t dwLayout) override;


      virtual double get_dpix() override;

      // Constructors
      bool CreateDC(const char * lpszDriverName, const char * lpszDeviceName, const char * lpszOutput, const void * lpInitData) override;
      bool CreateIC(const char * lpszDriverName, const char * lpszDeviceName, const char * lpszOutput, const void * lpInitData) override;
      bool CreateCompatibleDC(::draw2d::graphics * pgraphics) override;

      bool DeleteDC();

      // Device-Context Functions
      virtual int32_t SaveDC();
      virtual bool RestoreDC(int32_t nSavedDC) override;
      int32_t GetDevicecaps(int32_t nIndex);
      UINT SetBoundsRect(const RECT & lpRectBounds, UINT flags) override;
      UINT GetBoundsRect(LPRECT lpRectBounds, UINT flags) override;
      // xxx      bool ResetDC(const DEVMODE* lpDevMode) override;

      // Drawing-Tool Functions
      point GetBrushOrg() override;
      point SetBrushOrg(int32_t x, int32_t y) override;
      point SetBrushOrg(POINT point) override;
      int32_t EnumObjects(int32_t nObjectType,
                          int32_t(CALLBACK* lpfn)(LPVOID, LPARAM), LPARAM lpData) override;

      // Type-safe selection helpers
   public:
      virtual ::draw2d::object* SelectStockObject(int32_t nIndex) override;
      ::draw2d::pen* SelectObject(::draw2d::pen* pPen) override;
      ::draw2d::brush* SelectObject(::draw2d::brush* pBrush) override;
      virtual ::draw2d::font* SelectObject(::draw2d::font* pFont) override;
      ::draw2d::bitmap* SelectObject(::draw2d::bitmap* pBitmap) override;
      int32_t SelectObject(::draw2d::region* pRgn) override;       // special return for regions
      ::draw2d_cairo::object* SelectObject(::draw2d_cairo::object* pObject);
      // ::draw2d_cairo::object* provided so compiler doesn't use SelectObject(HGDIOBJ)

// color and color Palette Functions
      COLORREF GetNearestColor(COLORREF crColor) override;
      ::draw2d::palette* SelectPalette(::draw2d::palette* pPalette, bool bForceBackground) override;
      UINT RealizePalette();
      void UpdateColors();

      int32_t GetPolyFillMode() override;
      int32_t GetROP2() override;
      int32_t GetStretchBltMode() override;

      int32_t SetPolyFillMode(int32_t nPolyFillMode) override;
      int32_t SetROP2(int32_t nDrawMode) override;
      int32_t SetStretchBltMode(int32_t nStretchMode) override;

      // xxx      bool GetColorAdjustment(LPCOLORADJUSTMENT lpColorAdjust) override;
      // xxx      bool SetColorAdjustment(const COLORADJUSTMENT* lpColorAdjust) override;

#if (_WIN32_WINNT >= 0x0500)

      COLORREF GetDCBrushColor() override;
      COLORREF SetDCBrushColor(COLORREF crColor) override;

      COLORREF GetDCPenColor() override;
      COLORREF SetDCPenColor(COLORREF crColor) override;

#endif

      // Graphics mode
      int32_t SetGraphicsMode(int32_t iMode) override;
      int32_t GetGraphicsMode() override;

      // World transform
      bool SetWorldTransform(const XFORM* pXform);
      bool ModifyWorldTransform(const XFORM* pXform, uint32_t iMode);
      bool GetWorldTransform(XFORM* pXform);

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
      void DPtoLP(LPPOINT lpPoints, count nCount = 1) override;
      void DPtoLP(LPRECT lpRect) override;
      void DPtoLP(LPSIZE lpSize) override;
      void LPtoDP(LPPOINT lpPoints, count nCount = 1) override;
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
      bool PtVisible(POINT point) override;
      virtual bool RectVisible(const RECT & lpRect) override;
      int32_t SelectClipRgn(::draw2d::region* pRgn) override;
      int32_t ExcludeClipRect(int32_t x1, int32_t y1, int32_t x2, int32_t y2) override;
      int32_t ExcludeClipRect(const RECT & lpRect) override;
      int32_t ExcludeUpdateRgn(::user::primitive * pwindow);
      virtual int32_t IntersectClipRect(int32_t x1, int32_t y1, int32_t x2, int32_t y2) override;
      int32_t OffsetClipRgn(int32_t x, int32_t y) override;
      int32_t OffsetClipRgn(SIZE size) override;
      int32_t SelectClipRgn(::draw2d::region* pRgn, int32_t nMode) override;

      // Line-Output Functions
      pointd current_position() override;
      bool move_to(LPCPOINT ppt) override;
      bool move_to(LPCPOINTD ppt) override;
      //    point MoveTo(POINT point) override;
      bool line_to(LPCPOINTD ppt) override;
      //  bool LineTo(POINT point) override;
      virtual bool draw_line(LPCPOINT ppt1, LPCPOINT ppt2, ::draw2d::pen * ppen) override;
      virtual bool draw_line(LPCPOINTD ppt1, LPCPOINTD ppt2, ::draw2d::pen * ppen) override;
      bool Arc(int32_t x1, int32_t y1, int32_t x2, int32_t y2, int32_t x3, int32_t y3, int32_t x4, int32_t y4) override;
      bool Arc(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4) override;
      bool Arc(double x, double y, double w, double h, double start, double extends) override;
      bool Arc(const RECT & lpRect, POINT ptStart, POINT ptEnd) override;
      bool Polyline(const POINT* lpPoints, count nCount) override;

      bool AngleArc(int32_t x, int32_t y, int32_t nRadius, float fStartAngle, float fSweepAngle) override;
      bool ArcTo(int32_t x1, int32_t y1, int32_t x2, int32_t y2, int32_t x3, int32_t y3, int32_t x4, int32_t y4) override;
      bool ArcTo(const RECT & lpRect, POINT ptStart, POINT ptEnd) override;
      int32_t GetArcDirection() override;
      int32_t SetArcDirection(int32_t nArcDirection) override;

      bool PolyDraw(const POINT* lpPoints, const BYTE* lpTypes, count nCount) override;
      bool PolylineTo(const POINT* lpPoints, count nCount) override;
      bool PolyPolyline(const POINT* lpPoints, const INT * lpPolyPoints, count nCount) override;

      bool PolyBezier(const POINT* lpPoints, count nCount) override;
      bool PolyBezierTo(const POINT* lpPoints, count nCount) override;

      // Simple Drawing Functions
      bool fill_rect(LPCRECT lpcrect, ::draw2d::brush* pBrush) override;
      bool draw_rect(LPCRECT lpcrect, ::draw2d::pen * ppen) override;
      void frame_rect(LPCRECT lpcrect, ::draw2d::brush* pBrush) override;
      void invert_rect(LPCRECT lpcrect) override;

      bool DrawIcon(int32_t x, int32_t y, ::visual::icon * picon) override;
      bool DrawIcon(POINT point, ::visual::icon * picon) override;
      bool DrawIcon(int32_t x, int32_t y, ::visual::icon * picon, int32_t cx, int32_t cy, UINT istepIfAniCur, HBRUSH hbrFlickerFreeDraw, UINT diFlags) override;
      bool DrawState(point pt, size size, HBITMAP hBitmap, UINT nFlags,
                     HBRUSH hBrush = NULL) override;
      bool DrawState(point pt, size size, ::draw2d::bitmap* pBitmap, UINT nFlags,
                     ::draw2d::brush* pBrush = NULL) override;
      bool DrawState(point pt, size size, const char * lpszText, UINT nFlags,
                     bool bPrefixText = TRUE, int32_t nTextLen = 0, HBRUSH hBrush = NULL) override;
      bool DrawState(point pt, size size, const char * lpszText, UINT nFlags,
                     bool bPrefixText = TRUE, int32_t nTextLen = 0, ::draw2d::brush* pBrush = NULL) override;




      bool Chord(int32_t x1, int32_t y1, int32_t x2, int32_t y2, int32_t x3, int32_t y3,
                 int32_t x4, int32_t y4) override;
      bool Chord(const RECT & lpRect, POINT ptStart, POINT ptEnd) override;
      void DrawFocusRect(const RECT & lpRect) override;

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

      virtual bool fill_polygon(const POINTD * lpPoints, count nCount) override;
      virtual bool fill_polygon(const POINT* lpPoints, count nCount) override;

      virtual bool draw_polygon(const POINTD * lpPoints, count nCount) override;
      virtual bool draw_polygon(const POINT* lpPoints, count nCount) override;


      bool polygon(LPCPOINT lpPoints, count nCount) override;
      bool polygon(LPCPOINTD lpPoints, count nCount) override;
      bool rectangle(LPCRECT lpRect) override;
      //virtual bool draw_rect(int32_t x1, int32_t y1, int32_t x2, int32_t y2) override;
      //virtual bool DrawRectangle(const RECT & lpRect) override;
      //virtual bool FillRectangle(int32_t x1, int32_t y1, int32_t x2, int32_t y2) override;
      //virtual bool FillRectangle(const RECT & lpRect) override;
      //bool roundRect(int32_t x1, int32_t y1, int32_t x2, int32_t y2, int32_t x3, int32_t y3) override;
      bool round_rect(LPCRECT lpRect, LPCPOINT point) override;

      // Bitmap Functions
      bool PatBlt(int32_t x, int32_t y, int32_t nWidth, int32_t nHeight, uint32_t dwRop) override;
      bool BitBltRaw(int32_t x, int32_t y, int32_t nWidth, int32_t nHeight, ::draw2d::graphics * pgraphicsSrc,
                     int32_t xSrc, int32_t ySrc, uint32_t dwRop) override;
      bool StretchBltRaw(int32_t x, int32_t y, int32_t nWidth, int32_t nHeight, ::draw2d::graphics * pgraphicsSrc,
                         int32_t xSrc, int32_t ySrc, int32_t nSrcWidth, int32_t nSrcHeight, uint32_t dwRop) override;
      COLORREF GetPixel(int32_t x, int32_t y) override;
      COLORREF GetPixel(POINT point) override;
      COLORREF SetPixel(int32_t x, int32_t y, COLORREF crColor) override;
      COLORREF SetPixel(POINT point, COLORREF crColor) override;
      bool FloodFill(int32_t x, int32_t y, COLORREF crColor) override;
      bool ExtFloodFill(int32_t x, int32_t y, COLORREF crColor, UINT nFillType) override;
      bool MaskBlt(int32_t x, int32_t y, int32_t nWidth, int32_t nHeight, ::draw2d::graphics * pgraphicsSrc,
                   int32_t xSrc, int32_t ySrc, ::draw2d::bitmap& maskBitmap, int32_t xMask, int32_t yMask,
                   uint32_t dwRop) override;
      bool PlgBlt(LPPOINT lpPoint, ::draw2d::graphics * pgraphicsSrc, int32_t xSrc, int32_t ySrc,
                  int32_t nWidth, int32_t nHeight, ::draw2d::bitmap& maskBitmap, int32_t xMask, int32_t yMask) override;
      bool SetPixelV(int32_t x, int32_t y, COLORREF crColor) override;
      bool SetPixelV(POINT point, COLORREF crColor) override;
      bool GradientFill(TRIVERTEX* pVertices, WINULONG nVertices,
                        void * pMesh, WINULONG nMeshElements, uint32_t dwMode) override;
      bool TransparentBlt(int32_t xDest, int32_t yDest, int32_t nDestWidth, int32_t nDestHeight,
                          ::draw2d::graphics * pgraphicsSrc, int32_t xSrc, int32_t ySrc, int32_t nSrcWidth, int32_t nSrcHeight,
                          UINT clrTransparent) override;

      virtual bool alpha_blendRaw(int32_t xDest, int32_t yDest, int32_t nDestWidth, int32_t nDestHeight, ::draw2d::graphics * pgraphicsSrc, int32_t xSrc, int32_t ySrc, int32_t nSrcWidth, int32_t nSrcHeight, double dOpacity) override;

      /*bool alpha_blend(int32_t xDest, int32_t yDest, int32_t nDestWidth, int32_t nDestHeight,
        ::draw2d::graphics * pgraphicsSrc, int32_t xSrc, int32_t ySrc, int32_t nSrcWidth, int32_t nSrcHeight,
        BLENDFUNCTION blend);*/

      // Text Functions
      virtual bool text_out(int32_t x, int32_t y, const char * lpszString, strsize nCount) override;
      virtual bool text_out(int32_t x, int32_t y, const string & str) override;
      virtual bool TextOutRaw(double x, double y, const char * lpszString, strsize nCount) override;
      virtual bool text_out(double x, double y, const string & str) override;
      virtual bool ExtTextOut(int32_t x, int32_t y, UINT nOptions, const RECT & lpRect, const char * lpszString, strsize nCount, LPINT lpDxWidths) override;
      virtual bool ExtTextOut(int32_t x, int32_t y, UINT nOptions, const RECT & lpRect, const string & str, LPINT lpDxWidths) override;
      virtual size TabbedTextOut(int32_t x, int32_t y, const char * lpszString, strsize nCount, count nTabPositions, LPINT lpnTabStopPositions, int32_t nTabOrigin) override;
      virtual size TabbedTextOut(int32_t x, int32_t y, const string & str, count nTabPositions, LPINT lpnTabStopPositions, int32_t nTabOrigin) override;

#if defined(USE_PANGO)
      //virtual bool internal_draw_text_cairo(const char * lpszString, strsize nCount, const RECT & lpRect, UINT nFormat, PFN_CAIRO_TEXT pfnText);
      virtual bool internal_draw_text_pango(const char * lpszString, strsize nCount, const RECTD & lpRect, UINT nFormat, PFN_PANGO_TEXT pfnText);
      virtual bool internal_draw_text(const char * lpszString, strsize nCount, const RECTD & lpRect, UINT nFormat);
#else
      virtual bool internal_draw_text(const char * lpszString, strsize nCount, const RECT & lpRect, UINT nFormat, PFN_CAIRO_TEXT ftext);
#endif
      virtual bool draw_text(const char * lpszString, strsize nCount, const RECT & lpRect, UINT nFormat) override;
      virtual bool draw_text(const string & str, const RECT & lpRect, UINT nFormat) override;

      virtual bool draw_text_ex(LPTSTR lpszString, strsize nCount, const RECT & lpRect, UINT nFormat, LPDRAWTEXTPARAMS lpDTParams);
      virtual bool draw_text_ex(const string & str, const RECT & lpRect, UINT nFormat, LPDRAWTEXTPARAMS lpDTParams) override;

      sized GetTextExtent(const char * lpszString, strsize nCount, strsize iIndex) override;
      sized GetTextExtent(const char * lpszString, strsize nCount) override;
      sized GetTextExtent(const string & str) override;
      bool _GetTextExtent(sized & size, const char * lpszString, strsize nCount, strsize iIndex);
      bool GetTextExtent(sized & size, const char * lpszString, strsize nCount, strsize iIndex) override;
      bool GetTextExtent(sized & size, const char * lpszString, strsize nCount) override;
      bool GetTextExtent(sized & size, const string & str) override;
      size GetOutputTextExtent(const char * lpszString, strsize nCount) override;
      size GetOutputTextExtent(const string & str) override;
      size GetTabbedTextExtent(const char * lpszString, strsize nCount, count nTabPositions, LPINT lpnTabStopPositions) override;
      size GetTabbedTextExtent(const string & str, count nTabPositions, LPINT lpnTabStopPositions) override;
      size GetOutputTabbedTextExtent(const char * lpszString, strsize nCount, count nTabPositions, LPINT lpnTabStopPositions) override;
      size GetOutputTabbedTextExtent(const string & str, count nTabPositions, LPINT lpnTabStopPositions) override;
      virtual bool GrayString(::draw2d::brush* pBrush, bool (CALLBACK* lpfnOutput)(HDC, LPARAM, int32_t), LPARAM lpData, int32_t nCount, int32_t x, int32_t y, int32_t nWidth, int32_t nHeight) override;
      UINT GetTextAlign() override;
      UINT SetTextAlign(UINT nFlags) override;
      int32_t GetTextFace(count nCount, LPTSTR lpszFacename) override;
      int32_t GetTextFace(string & rString) override;
      bool get_text_metrics(::draw2d::text_metric * lpMetrics) override;
      bool get_output_text_metrics(::draw2d::text_metric * lpMetrics) override;
      int32_t SetTextJustification(int32_t nBreakExtra, int32_t nBreakCount) override;
      int32_t GetTextCharacterExtra() override;
      int32_t SetTextCharacterExtra(int32_t nCharExtra) override;

      //xxx      uint32_t GetCharacterPlacement(const char * lpString, int32_t nCount, int32_t nMaxExtent, LPGCP_RESULTS lpResults, uint32_t dwFlags) override;
      //xxx      uint32_t GetCharacterPlacement(string & str, int32_t nMaxExtent, LPGCP_RESULTS lpResults, uint32_t dwFlags) override;

#if (_WIN32_WINNT >= 0x0500)

      bool GetTextExtentExPointI(LPWORD pgiIn, int32_t cgi, int32_t nMaxExtent, LPINT lpnFit, LPINT alpDx, __out_opt LPSIZE lpSize) override;
      bool GetTextExtentPointI(LPWORD pgiIn, int32_t cgi, __out_opt LPSIZE lpSize) override;

#endif



      // Advanced Drawing
      bool DrawEdge(const RECT & lpRect, UINT nEdge, UINT nFlags) override;
      bool DrawFrameControl(const RECT & lpRect, UINT nType, UINT nState) override;

      // Scrolling Functions
      bool ScrollDC(int32_t dx, int32_t dy, const RECT & lpRectScroll, const RECT & lpRectClip,
                    ::draw2d::region* pRgnUpdate, LPRECT lpRectUpdate) override;

      // font Functions
      bool GetCharWidth(UINT nFirstChar, UINT nLastChar, LPINT lpBuffer) override;
      bool GetOutputCharWidth(UINT nFirstChar, UINT nLastChar, LPINT lpBuffer) override;
      uint32_t SetMapperFlags(uint32_t dwFlag) override;
      size GetAspectRatioFilter() override;

      //xxx      bool GetCharABCWidths(UINT nFirstChar, UINT nLastChar, LPABC lpabc) override;
      uint32_t GetFontData(uint32_t dwTable, uint32_t dwOffset, LPVOID lpData, uint32_t cbData) override;
      //xxx      int32_t GetKerningPairs(int32_t nPairs, LPKERNINGPAIR lpkrnpair) override;
      //xxx      UINT GetOutlineTextMetrics(UINT cbData, LPOUTLINETEXTMETRICW lpotm) override;
      //xxx      uint32_t GetGlyphOutline(UINT nChar, UINT nFormat, LPGLYPHMETRICS lpgm,
      //xxx    uint32_t cbBuffer, LPVOID lpBuffer, const MAT2* lpmat2) override;

      //xxx      bool GetCharABCWidths(UINT nFirstChar, UINT nLastChar,
      //xxx         LPABCFLOAT lpABCF) override;
      bool GetCharWidth(UINT nFirstChar, UINT nLastChar,
                        float* lpFloatBuffer) override;

      uint32_t GetFontLanguageInfo() override;

#if (_WIN32_WINNT >= 0x0500)

      bool GetCharABCWidthsI(UINT giFirst, UINT cgi, LPWORD pgi, LPABC lpabc) override;
      bool GetCharWidthI(UINT giFirst, UINT cgi, LPWORD pgi, LPINT lpBuffer) override;

#endif

      // Printer/Device Escape Functions
      virtual int32_t Escape(int32_t nEscape, int32_t nCount, const char * lpszInData, LPVOID lpOutData) override;
      int32_t Escape(int32_t nEscape, int32_t nInputSize, const char * lpszInputData, int32_t nOutputSize, char * lpszOutputData) override;
      int32_t DrawEscape(int32_t nEscape, int32_t nInputSize, const char * lpszInputData) override;

      // Escape helpers
      int32_t StartDoc(const char * lpszDocName) override;  // old Win3.0 version
//xxx      int32_t StartDoc(LPDOCINFO lpDocInfo) override;
      int32_t StartPage();
      int32_t EndPage();
      int32_t SetAbortProc(bool (CALLBACK* lpfn)(HDC, int32_t));
      int32_t AbortDoc();
      int32_t EndDoc();

      // MetaFile Functions
      //xxx      bool PlayMetaFile(HMETAFILE hMF) override;
//      bool PlayMetaFile(HENHMETAFILE hEnhMetaFile, const RECT & lpBounds) override;
  //    bool AddMetaFileComment(UINT nDataSize, const BYTE* pCommentData) override;
      // can be used for enhanced metafiles only

// Path Functions
      bool abort_path() override;
      bool begin_path() override;
      bool close_figure() override;
      bool end_path() override;
      bool fill_path() override;
      bool flatten_path() override;
      bool stroke_and_fill_path() override;
      bool stroke_path() override;
      bool widen_path() override;

      bool draw_path(::draw2d::path * ppath) override;
      bool fill_path(::draw2d::path * ppath) override;

      bool draw_path(::draw2d::path * ppath, ::draw2d::pen * ppen) override;
      bool fill_path(::draw2d::path * ppath, ::draw2d::brush * pbrush) override;

      float GetMiterLimit() override;
      bool SetMiterLimit(float fMiterLimit) override;
      int32_t GetPath(LPPOINT lpPoints, LPBYTE lpTypes, count nCount) override;
      bool SelectClipPath(int32_t nMode) override;

      // Misc Helper Functions
      static ::draw2d::brush* PASCAL GetHalftoneBrush(::aura::application * papp);
      void DrawDragRect(const RECT & lpRect, SIZE size,
                        const RECT & lpRectLast, SIZE sizeLast,
                        ::draw2d::brush* pBrush = NULL, ::draw2d::brush* pBrushLast = NULL) override;
      //void fill_solid_rect(const RECT64 * lpRect, COLORREF clr) override;
      void fill_solid_rect(LPCRECT lpRect, COLORREF clr) override;
      void fill_solid_rect(LPCRECTD lpRect, COLORREF clr) override;
      //void fill_solid_rect(int32_t x, int32_t y, int32_t cx, int32_t cy, COLORREF clr) override;
      void draw3d_rect(LPCRECT  lpRect, COLORREF clrTopLeft, COLORREF clrBottomRight) override;
      //void draw3d_rect(int32_t x, int32_t y, int32_t cx, int32_t cy,
        //              COLORREF clrTopLeft, COLORREF clrBottomRight) override;




      // Implementation
   public:
      virtual void assert_valid() const override;
      virtual void dump(dump_context & dumpcontext) const override;

      //      HGDIOBJ SelectObject(HGDIOBJ) override;      // do not use for regions

      virtual void set_alpha_mode(::draw2d::e_alpha_mode ealphamode) override;

      virtual void set_text_rendering(::draw2d::e_text_rendering etextrendering) override;

      virtual void * get_os_data() const override;
      //      virtual HDC get_handle() override;
      //    virtual HDC get_handle1() override;
      //  virtual HDC get_handle2() override;

      virtual bool attach(void * pdata) override;


      //xxx      virtual Gdiplus::FillMode gdiplus_get_fill_mode();

      bool blur(bool bExpand, double dRadius, const RECT & lpcrect) override;

      //protected:
      // used for implementation of non-virtual SelectObject calls
      //static ::draw2d_cairo::object* PASCAL SelectGdiObject(::aura::application * papp, HDC hDC, HGDIOBJ h) override;


      // platform-specific or platform-internals
      bool set_os_color(COLORREF cr);
      bool set(const ::draw2d::brush * pbrush, double x = 0.0, double y = 0.0);
      bool set(const ::draw2d::pen * ppen);
#if !defined(USE_PANGO)
      bool set(const ::draw2d::font * pfont);
#endif
      bool set(const ::draw2d::path * ppath);
      bool set(const ::draw2d::path::element & e);
      bool set(const ::draw2d::path::arc & arc);
      bool set(const ::draw2d::path::move & move);
      bool set(const ::draw2d::path::line & line);
      bool set(const ::draw2d::path::rect & r);
      bool set(const ::draw2d::path::string_path & str);
      bool fill_and_draw(::draw2d::brush * pbrush, ::draw2d::pen * ppen);
      bool fill(::draw2d::brush * pbrush, double xOrg  = 0.0, double yOrg = 0.0);
      bool draw(::draw2d::pen * ppen);
      bool fill_and_draw();
      bool fill(double xOrg = 0.0, double yOrg = 0.0);
      bool draw();


      virtual bool _get(::draw2d::matrix & matrix);
      virtual bool _set(const ::draw2d::matrix & matrix);
//      virtual bool append(const ::draw2d::matrix & matrix);
  //    virtual bool prepend(const ::draw2d::matrix & matrix);


      virtual bool flush();

#ifdef WINDOWS

      virtual bool Attach(HDC hdc) override;
      virtual HDC Detach() override;

#endif

      virtual void enum_fonts(::draw2d::font::enum_item_array & itema) override;

      virtual string get_font_path(string str);

   };


   CLASS_DECL_AURA string q_valid_string(string str);


} // namespace win





