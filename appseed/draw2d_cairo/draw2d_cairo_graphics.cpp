#include "framework.h"
#include <math.h>

// https://www.codeproject.com/Articles/2293/Retrieving-Font-Name-from-TTF-File
// Philip Patrick
// Team Leader Varonis
// Israel Israel

typedef struct _tagTT_OFFSET_TABLE
{
   u16	uMajorVersion;
   u16	uMinorVersion;
   u16	uNumOfTables;
   u16	uSearchRange;
   u16	uEntrySelector;
   u16	uRangeShift;
} TT_OFFSET_TABLE;

typedef struct _tagTT_TABLE_DIRECTORY
{
   char	szTag[4];			//table name
   u32	uCheckSum;			//Check sum
   u32	uOffset;			//Offset from beginning of file
   u32	uLength;			//length of the table in bytes
} TT_TABLE_DIRECTORY;

typedef struct _tagTT_NAME_TABLE_HEADER
{
   u16	uFSelector;			//format selector. Always 0
   u16	uNRCount;			//Name Records count
   u16	uStorageOffset;		//Offset for strings storage, from start of the table
} TT_NAME_TABLE_HEADER;

typedef struct _tagTT_NAME_RECORD
{
   u16	uPlatformID;
   u16	uEncodingID;
   u16	uLanguageID;
   u16	uNameID;
   u16	uStringLength;
   u16	uStringOffset;	//from start of storage area
} TT_NAME_RECORD;

#define SWAPWORD(x)		MAKEWORD(HIBYTE(x), LOBYTE(x))
#define SWAPLONG(x)		MAKELONG(SWAPWORD(HIWORD(x)), SWAPWORD(LOWORD(x)))

class ttf_util :
   virtual public ::object
{
public:


   ttf_util(::aura::application * papp) :
      ::object(papp)
   {


   }


   string GetFontNameFromFile(::file::path lpszFilePath)
   {

      ::file::file_sp f = Application.file().get_file(lpszFilePath, ::file::mode_read | ::file::share_deny_write);

      string csRetVal;

      if (f.is_null())
      {

         return "";

      }

      TT_OFFSET_TABLE ttOffsetTable;
      f->read(&ttOffsetTable, sizeof(TT_OFFSET_TABLE));
      ttOffsetTable.uNumOfTables = SWAPWORD(ttOffsetTable.uNumOfTables);
      ttOffsetTable.uMajorVersion = SWAPWORD(ttOffsetTable.uMajorVersion);
      ttOffsetTable.uMinorVersion = SWAPWORD(ttOffsetTable.uMinorVersion);

      //check is this is a true type font and the version is 1.0
      if (ttOffsetTable.uMajorVersion != 1 || ttOffsetTable.uMinorVersion != 0)
         return csRetVal;

      TT_TABLE_DIRECTORY tblDir;
      WINBOOL bFound = FALSE;
      string csTemp;

      for (int i = 0; i < ttOffsetTable.uNumOfTables; i++)
      {
         f->read(&tblDir, sizeof(TT_TABLE_DIRECTORY));
         strncpy(csTemp.GetBuffer(5), tblDir.szTag, 4);
         csTemp.ReleaseBuffer(4);
         if (csTemp.compare_ci("name") == 0)
         {
            bFound = TRUE;
            tblDir.uLength = SWAPLONG(tblDir.uLength);
            tblDir.uOffset = SWAPLONG(tblDir.uOffset);
            break;
         }
      }

      if (bFound)
      {
         f->seek(tblDir.uOffset, ::file::seek_begin);
         TT_NAME_TABLE_HEADER ttNTHeader;
         f->read(&ttNTHeader, sizeof(TT_NAME_TABLE_HEADER));
         ttNTHeader.uNRCount = SWAPWORD(ttNTHeader.uNRCount);
         ttNTHeader.uStorageOffset = SWAPWORD(ttNTHeader.uStorageOffset);
         TT_NAME_RECORD ttRecord;
         bFound = FALSE;

         for (int i = 0; i < ttNTHeader.uNRCount; i++)
         {
            f->read(&ttRecord, sizeof(TT_NAME_RECORD));
            ttRecord.uNameID = SWAPWORD(ttRecord.uNameID);
            if (ttRecord.uNameID == 1)
            {
               ttRecord.uStringLength = SWAPWORD(ttRecord.uStringLength);
               ttRecord.uStringOffset = SWAPWORD(ttRecord.uStringOffset);
               int nPos = f->get_position();
               f->seek(tblDir.uOffset + ttRecord.uStringOffset + ttNTHeader.uStorageOffset, ::file::seek_begin);

               //bug fix: see the post by SimonSays to read more about it
               char * lpszNameBuf = csTemp.GetBuffer(ttRecord.uStringLength + 1);
               memset(lpszNameBuf, 0, ttRecord.uStringLength + 1);
               f->read(lpszNameBuf, ttRecord.uStringLength);
               csTemp.ReleaseBuffer();
               if (csTemp.get_length() > 0)
               {

                  csRetVal = csTemp;

                  break;

               }

               f->seek(nPos, ::file::seek_begin);

            }

         }

      }

      f->close();

      return csRetVal;

   }

};



void copy(cairo_matrix_t & cairomatrix, const ::draw2d::matrix & matrix)
{

   cairomatrix.xx = matrix.a1;
   cairomatrix.yx = matrix.a2;
   cairomatrix.xy = matrix.b1;
   cairomatrix.yy = matrix.b2;
   cairomatrix.x0 = matrix.c1;
   cairomatrix.y0 = matrix.c2;

}


void copy(::draw2d::matrix & matrix, const cairo_matrix_t & cairomatrix)
{

   matrix.a1 = cairomatrix.xx;
   matrix.a2 = cairomatrix.yx;
   matrix.b1 = cairomatrix.xy;
   matrix.b2 = cairomatrix.yy;
   matrix.c1 = cairomatrix.x0;
   matrix.c2 = cairomatrix.y0;

}


#if defined(LINUX)

#include <fontconfig/fontconfig.h>

#include <pango/pangocairo.h>

mutex *        g_pmutexFc = NULL;

FcBool         g_fcResult;

FcConfig *     g_fcConfig;

string_to_string *      g_pmapFontPath;

//#elif defined(WINDOWS)
//
//class font_fam_callback
//{
//public:
//
//   stringa                    m_stra;
//   ::draw2d::font::csa        m_csa;
//
//};
//
//BOOL CALLBACK EnumFamCallBackW(LPLOGFONTW lplf, LPNEWTEXTMETRICW lpntm, DWORD dwFontType, LPVOID p)
//{
//
//   font_fam_callback * pc = (font_fam_callback *)p;
//
//   int iType = -1;
//
//   if (dwFontType & RASTER_FONTTYPE)
//   {
//
//      iType = 0;
//
//   }
//   else if (dwFontType & TRUETYPE_FONTTYPE)
//   {
//
//      iType = 1;
//
//   }
//   else
//   {
//
//      iType = 2;
//
//   }
//
//   if (iType == 1)
//   {
//
//      if (pc->m_stra.add_unique(lplf->lfFaceName))
//      {
//
//         if (wcsicmp(lplf->lfFaceName, L"Gulim") == 0)
//         {
//            output_debug_string("Gulim");
//         }
//         pc->m_csa.add(::draw2d::wingdi_get_cs(lplf->lfCharSet));
//
//      }
//
//   }
//
//   //int far * aiFontCount = (int far *) aFontCount;
//
//   //// Record the number of raster, TrueType, and vector
//   //// fonts in the font-count array.
//
//   //if (FontType & RASTER_FONTTYPE)
//   //   aiFontCount[0]++;
//   //else if (FontType & TRUETYPE_FONTTYPE)
//   //   aiFontCount[2]++;
//   //else
//   //   aiFontCount[1]++;
//
//   //if (aiFontCount[0] || aiFontCount[1] || aiFontCount[2])
//   //   return TRUE;
//   //else
//   //   return FALSE;
//
//   //UNREFERENCED_PARAMETER(lplf);
//   //UNREFERENCED_PARAMETER(lpntm);
//
//
//   return true;
//
//}


#endif

string_map < FT_Face > * g_pmapFontFace = NULL;

string_map < cairo_font_face_t * > * g_pmapCairoFontFace = NULL;

string_to_int * g_pmapFontError = NULL;

string_to_int * g_pmapFontError2 = NULL;

extern CLASS_DECL_AURA array<object * > * g_paAura;



namespace draw2d_cairo
{




   FT_Face g_ft = NULL;
   int g_iFtLevel = -1;

   graphics::graphics(::aura::application * papp) :
      ::object(papp),
      ::draw2d::graphics(papp)
   {

      m_iSaveDC = 0;

#ifdef WINDOWS
      m_psurfaceAttach = NULL;
      m_hdcAttach = NULL;
#endif

      m_bPrinting = FALSE;
      m_pdibAlphaBlend = NULL;
      m_pdc = NULL;
      m_etextrenderinghint = ::draw2d::text_rendering_hint_anti_alias_grid_fit;

      m_spfont.alloc(allocer());
      m_spfont->m_strFontFamilyName = FONT_SANS;
      m_spfont->m_dFontSize = 12.0;
      m_iSaveDCPositiveClip = -1;

      m_nStretchBltMode = HALFTONE;

   }


   void graphics::assert_valid() const
   {

      object::assert_valid();

   }


   void graphics::dump(dump_context & dumpcontext) const
   {

      object::dump(dumpcontext);

      dumpcontext << "\n";

   }


   graphics::~graphics()
   {

      synch_lock ml(cairo_mutex());

      if (m_pdc != NULL)
      {

         cairo_destroy(m_pdc);

         m_pdc = NULL;

      }

   }


   bool graphics::IsPrinting()
   {

      return m_bPrinting;

   }


   bool graphics::CreateDC(const char * lpszDriverName, const char * lpszDeviceName, const char * lpszOutput, const void * lpInitData)
   {

      _throw(not_supported_exception(get_app()));

   }


   bool graphics::CreateIC(const char * lpszDriverName, const char * lpszDeviceName, const char * lpszOutput, const void * lpInitData)
   {

      _throw(not_supported_exception(get_app()));

   }


   bool graphics::CreateCompatibleDC(::draw2d::graphics * pgraphics)
   {

      synch_lock ml(cairo_mutex());

      if (m_pdc != NULL)
      {

         cairo_destroy(m_pdc);

         m_pdc = NULL;

      }

      if (pgraphics == NULL)
      {

         cairo_surface_t * psurface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, 1, 1);

         if (psurface == NULL)
         {

            return false;

         }

         m_pdc = cairo_create(psurface);

         cairo_surface_destroy(psurface);

         return m_pdc != NULL;

      }
      else
      {

         cairo_surface_t * psurface = cairo_get_target((cairo_t *)pgraphics->get_os_data());

         if (cairo_surface_status(psurface) != CAIRO_STATUS_SUCCESS)
         {

            return false;

         }

         cairo_surface_t * psurfaceNew = cairo_surface_create_similar(psurface, cairo_surface_get_content(psurface), 1, 1);

         if (psurfaceNew == NULL)
         {

            return false;

         }

         m_pdc = cairo_create(psurfaceNew);

         cairo_surface_destroy(psurfaceNew);

         return m_pdc != NULL;

      }

      return true;

   }


   int32_t graphics::ExcludeUpdateRgn(::user::primitive * pwindow)
   {

      ::exception::throw_not_implemented(get_app());

      return 0;

   }


   int32_t graphics::GetDevicecaps(int32_t nIndex)
   {

      ::exception::throw_not_implemented(get_app());

      return 0;

   }


   point graphics::GetBrushOrg()
   {

      ::exception::throw_not_implemented(get_app());

      return point(0, 0);

   }


   point graphics::SetBrushOrg(int32_t x, int32_t y)
   {

      ::exception::throw_not_implemented(get_app());

      return point(0, 0);

   }


   point graphics::SetBrushOrg(POINT point)
   {

      ::exception::throw_not_implemented(get_app());

      return ::point(0, 0);

   }


   int32_t graphics::EnumObjects(int32_t nObjectType, int32_t(CALLBACK* lpfn)(LPVOID, LPARAM), LPARAM lpData)
   {

      ::exception::throw_not_implemented(get_app());

      return 0;

   }


   ::draw2d::bitmap* graphics::SelectObject(::draw2d::bitmap* pbitmap)
   {

      synch_lock ml(cairo_mutex());

      if (pbitmap == NULL)
      {

         return NULL;

      }

      if (m_pdc != NULL)
      {

         cairo_destroy(m_pdc);

         m_pdc = NULL;

      }

      m_pdc = cairo_create((cairo_surface_t *)pbitmap->get_os_data());

      set_text_rendering_hint(::draw2d::text_rendering_hint_anti_alias_grid_fit);

      m_spbitmap = pbitmap;

      return m_spbitmap;

   }


   ::draw2d_cairo::object* graphics::SelectObject(draw2d_cairo::object* pObject)
   {

      return NULL;

   }


   COLORREF graphics::GetNearestColor(COLORREF crColor)
   {

      return crColor;

   }


   UINT graphics::RealizePalette()
   {

      return 0;

   }


   void graphics::UpdateColors()
   {

   }


   int32_t graphics::GetPolyFillMode()
   {

      synch_lock ml(cairo_mutex());

      cairo_fill_rule_t fillrule = cairo_get_fill_rule(m_pdc);

      if(fillrule == CAIRO_FILL_RULE_WINDING)
      {

         return ::draw2d::fill_mode_winding;

      }

      return ::draw2d::fill_mode_alternate;

   }


   int32_t graphics::GetROP2()
   {

      return 0;

   }


   int32_t graphics::GetStretchBltMode()
   {

      return 0;

   }


   int32_t graphics::GetMapMode()
   {

      return 0;

   }


   int32_t graphics::GetGraphicsMode()
   {

      return 0;

   }


   bool graphics::GetWorldTransform(XFORM* pXform)
   {

      return 0;

   }


   size graphics::GetViewportExt()
   {

      return ::size(0, 0);

   }


   point graphics::GetWindowOrg()
   {

      return ::point(0, 0);

   }


   size graphics::GetWindowExt()
   {

      return ::size(0, 0);

   }

   // non-virtual helpers calling virtual mapping functions
   point graphics::SetViewportOrg(POINT point)
   {

      return SetViewportOrg(point.x, point.y);

   }


   size graphics::SetViewportExt(SIZE size)
   {

      return ::size(0, 0);

   }


   point graphics::SetWindowOrg(POINT point)
   {

      return ::point(0, 0);

   }


   size graphics::SetWindowExt(SIZE size)
   {

      return ::size(0, 0);

   }


   void graphics::DPtoLP(LPPOINT lpPoints, count nCount)
   {

   }


   void graphics::DPtoLP(LPRECT lpRect)
   {

   }


   void graphics::LPtoDP(LPPOINT lpPoints, count nCount)
   {

   }


   void graphics::LPtoDP(LPRECT lpRect)
   {

   }


   bool graphics::FillRgn(::draw2d::region* pRgn, ::draw2d::brush* pBrush)
   {

      ::exception::throw_not_implemented(get_app());

      return false;

   }


   bool graphics::FrameRgn(::draw2d::region* pRgn, ::draw2d::brush* pBrush, int32_t nWidth, int32_t nHeight)
   {

      ::exception::throw_not_implemented(get_app());

      return false;

   }


   bool graphics::InvertRgn(::draw2d::region* pRgn)
   {

      ::exception::throw_not_implemented(get_app());

      return false;

   }


   bool graphics::PaintRgn(::draw2d::region* pRgn)
   {

      ::exception::throw_not_implemented(get_app());

      return false;

   }


   bool graphics::PtVisible(int32_t x, int32_t y)
   {

      ::exception::throw_not_implemented(get_app());

      return false;

   }


   bool graphics::PtVisible(POINT point)
   {

      ::exception::throw_not_implemented(get_app());

      return false;

   }


   bool graphics::RectVisible(const RECT & lpRect)
   {

      ::exception::throw_not_implemented(get_app());

      return false;

   }


   pointd graphics::current_position()
   {

      return ::draw2d::graphics::current_position();

   }


   bool graphics::Arc(int32_t x1, int32_t y1, int32_t x2, int32_t y2, int32_t x3, int32_t y3, int32_t x4, int32_t y4)
   {

      synch_lock ml(cairo_mutex());

      double centerx = (x2 + x1) / 2.0;

      double centery = (y2 + y1) / 2.0;

      double radiusx = abs(x2 - x1) / 2.0;

      double radiusy = abs(y2 - y1) / 2.0;

      if (radiusx == 0.0 || radiusy == 0.0)
      {

         return false;

      }

      double start = atan2(y3 - centery, x3 - centerx);

      double end = atan2(y4 - centery, x4 - centerx);

      cairo_keep keep(m_pdc);

      cairo_translate(m_pdc, centerx, centery);

      cairo_scale(m_pdc, radiusx, radiusy);

      cairo_arc(m_pdc, 0.0, 0.0, 1.0, start, end);

      return draw();

   }


   bool graphics::Arc(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4)
   {

      synch_lock ml(cairo_mutex());

      double centerx = (x2 + x1) / 2.0;

      double centery = (y2 + y1) / 2.0;

      double radiusx = fabs(x2 - x1) / 2.0;

      double radiusy = fabs(y2 - y1) / 2.0;

      if (radiusx == 0.0 || radiusy == 0.0)
      {

         return false;

      }

      double start = atan2(y3 - centery, x3 - centerx);

      double end = atan2(y4 - centery, x4 - centerx);

      cairo_keep keep(m_pdc);

      cairo_translate(m_pdc, centerx, centery);

      cairo_scale(m_pdc, radiusx, radiusy);

      cairo_arc(m_pdc, 0.0, 0.0, 1.0, start, end);

      return draw();

   }


   bool graphics::Arc(double x, double y, double w, double h, double start, double extends)
   {

      synch_lock ml(cairo_mutex());

      double end = start + extends;

      cairo_keep keep(m_pdc);

      cairo_translate(m_pdc, x + w / 2.0, y + h / 2.0);

      cairo_scale(m_pdc, w / 2.0, h / 2.0);

      if (extends > 0)
      {

         cairo_arc(m_pdc, 0.0, 0.0, 1.0, start * 3.1415 / 180.0, end * 3.1415 / 180.0);

      }
      else
      {

         cairo_arc_negative(m_pdc, 0.0, 0.0, 1.0, start * 3.1415 / 180.0, end * 3.1415 / 180.0);

      }

      keep.restore();

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

      return draw_polygon(lpPoints, nCount);

   }


   bool graphics::fill_rect(LPCRECT lpRect, ::draw2d::brush * pbrush)
   {

      synch_lock ml(cairo_mutex());

      if (lpRect->right <= lpRect->left || lpRect->bottom <= lpRect->top)
      {

         return false;

      }

      cairo_rectangle(m_pdc, lpRect->left, lpRect->top, lpRect->right - lpRect->left, lpRect->bottom - lpRect->top);

      fill(pbrush);

      return true;

   }


   void graphics::frame_rect(LPCRECT lpRect, ::draw2d::brush* pBrush)
   {

      fill_solid_rect(lpRect, pBrush->m_cr);

   }


   bool graphics::draw_rect(LPCRECT lpcrect, ::draw2d::pen * ppen)
   {

      synch_lock ml(cairo_mutex());

      if (lpcrect->right <= lpcrect->left || lpcrect->bottom <= lpcrect->top)
      {

         return false;

      }

      cairo_rectangle(m_pdc, lpcrect->left, lpcrect->top, lpcrect->right - lpcrect->left, lpcrect->bottom - lpcrect->top);

      draw(ppen);

      return true;

   }


   void graphics::invert_rect(LPCRECT lpcrect)
   {

      ::exception::throw_not_implemented(get_app());

      return;

   }


   bool graphics::DrawIcon(int32_t x, int32_t y, ::visual::icon * picon)
   {

      ::exception::throw_not_implemented(get_app());

      return false;

   }


   bool graphics::DrawIcon(POINT point, ::visual::icon * picon)
   {

      ::exception::throw_not_implemented(get_app());

      return false;

   }


   bool graphics::DrawIcon(int32_t x, int32_t y, ::visual::icon * picon, int32_t cx, int32_t cy, UINT istepIfAniCur, HBRUSH hbrFlickerFreeDraw, UINT diFlags)
   {


#ifdef WINDOWS

      try
      {

         if (picon == NULL)
            return FALSE;

         if (m_pdc == NULL)
            return FALSE;

         if (cx <= 0 || cx <= 0)
            return false;


         bool bOk = FALSE;

         BITMAPINFO info;
         COLORREF * pcolorref;

         ZeroMemory(&info, sizeof(BITMAPINFO));

         info.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
         info.bmiHeader.biWidth = cx;
         info.bmiHeader.biHeight = -cy;
         info.bmiHeader.biPlanes = 1;
         info.bmiHeader.biBitCount = 32;
         info.bmiHeader.biCompression = BI_RGB;
         info.bmiHeader.biSizeImage = cx * cy * 4;

         HBITMAP hbitmap = ::CreateDIBSection(NULL, &info, DIB_RGB_COLORS, (void **)&pcolorref, NULL, 0);

         HDC hdc = ::CreateCompatibleDC(NULL);

         HBITMAP hbitmapOld = (HBITMAP) ::SelectObject(hdc, hbitmap);

         if (::DrawIconEx(hdc, 0, 0, (HICON)picon->m_picon, cx, cy, istepIfAniCur, NULL, DI_IMAGE | DI_MASK))
         {

            ::SelectObject(hdc, hbitmapOld);

            try
            {

               //Gdiplus::Bitmap b(cx, cy, cx * 4 , PixelFormat32bppARGB, (BYTE *) pcolorref);

               ::draw2d::bitmap_sp b(allocer());

               b->CreateBitmap(this, cx, cy, 1, 32, pcolorref, cx * sizeof(COLORREF));

               cairo_surface_t * psurface = (cairo_surface_t *)b->get_os_data();

               if (psurface == NULL)
                  return false;

               cairo_pattern_t * ppattern = cairo_pattern_create_for_surface(psurface);

               if (ppattern == NULL)
                  return false;

               cairo_matrix_t matrix;

               cairo_matrix_t matrixOld;

               cairo_keep keep(m_pdc);

               cairo_translate(m_pdc, x, y);

               cairo_pattern_get_matrix(ppattern, &matrixOld);

               cairo_matrix_init_translate(&matrix, 0, 0);

               cairo_pattern_set_matrix(ppattern, &matrix);

               cairo_rectangle(m_pdc, 0, 0, cx, cy);

               cairo_clip(m_pdc);

               cairo_set_source(m_pdc, ppattern);

               cairo_paint(m_pdc);

               cairo_pattern_set_matrix(ppattern, &matrixOld);

               cairo_pattern_destroy(ppattern);
            }
            catch (...)
            {
            }

         }

         ::DeleteDC(hdc);

         ::DeleteObject(hbitmap);

         return bOk;

      }
      catch (...)
      {
      }

#endif

      return false;

   }


   bool graphics::DrawState(point pt, size size, HBITMAP hBitmap, UINT nFlags, HBRUSH hBrush)
   {

      ::exception::throw_not_implemented(get_app());

      return false;

   }


   bool graphics::DrawState(point pt, size size, ::draw2d::bitmap* pBitmap, UINT nFlags, ::draw2d::brush* pBrush)
   {

      ::exception::throw_not_implemented(get_app());

      return false;

   }


   bool graphics::DrawState(point pt, size size, const char * lpszText, UINT nFlags, bool bPrefixText, int32_t nTextLen, HBRUSH hBrush)
   {

      ::exception::throw_not_implemented(get_app());

      return false;

   }


   bool graphics::DrawState(point pt, size size, const char * lpszText, UINT nFlags, bool bPrefixText, int32_t nTextLen, ::draw2d::brush* pBrush)
   {

      ::exception::throw_not_implemented(get_app());

      return false;

   }


   bool graphics::DrawEdge(const RECT & lpRect, UINT nEdge, UINT nFlags)
   {

      ::exception::throw_not_implemented(get_app());

      return false;

   }


   bool graphics::DrawFrameControl(const RECT & lpRect, UINT nType, UINT nState)
   {

      ::exception::throw_not_implemented(get_app());

      return false;

   }


   bool graphics::Chord(int32_t x1, int32_t y1, int32_t x2, int32_t y2, int32_t x3, int32_t y3, int32_t x4, int32_t y4)
   {

      ::exception::throw_not_implemented(get_app());

      return false;

   }


   bool graphics::Chord(const RECT & lpRect, POINT ptStart, POINT ptEnd)
   {

      ::exception::throw_not_implemented(get_app());

      return false;

   }


   void graphics::DrawFocusRect(const RECT & lpRect)
   {

      ::exception::throw_not_implemented(get_app());

   }


   bool graphics::DrawEllipse(int32_t x1, int32_t y1, int32_t x2, int32_t y2)
   {

      synch_lock ml(cairo_mutex());

      double centerx = (x2 + x1) / 2.0;

      double centery = (y2 + y1) / 2.0;

      double radiusx = abs(x2 - x1) / 2.0;

      double radiusy = abs(y2 - y1) / 2.0;

      if (radiusx == 0.0 || radiusy == 0.0)
      {

         return false;

      }

      cairo_keep keep(m_pdc);

      //cairo_new_sub_path(m_pdc);

      cairo_translate(m_pdc, centerx, centery);

      //cairo_scale(m_pdc, radiusx -m_sppen->m_dWidth /2.0, radiusy -m_sppen->m_dWidth /2.0);

      //cairo_scale(m_pdc, radiusx, radiusy);

      double dDeflate;

#ifdef LINUX

      dDeflate = m_sppen->m_dWidth / (3 * 3.1416); // magical number

#else

      dDeflate = m_sppen->m_dWidth / (2 * 3.1416); // magical number

#endif

      cairo_scale(m_pdc, radiusx - dDeflate, radiusy - dDeflate);

      cairo_arc(m_pdc, 0.0, 0.0, 1.0, 0.0, 2.0 * 3.1415);

      keep.pulse();

      set(m_sppen);

      cairo_stroke(m_pdc);

      return true;

   }


   bool graphics::DrawEllipse(const RECT & lprect)
   {

      return DrawEllipse(lprect.left, lprect.top, lprect.right, lprect.bottom);

   }


   bool graphics::FillEllipse(int32_t x1, int32_t y1, int32_t x2, int32_t y2)
   {

      synch_lock ml(cairo_mutex());

      double centerx = (x2 + x1) / 2.0;

      double centery = (y2 + y1) / 2.0;

      double radiusx = abs(x2 - x1) / 2.0;

      double radiusy = abs(y2 - y1) / 2.0;

      if (radiusx == 0.0 || radiusy == 0.0)
      {

         return false;

      }

      cairo_keep keep(m_pdc);

      cairo_new_sub_path(m_pdc);

      cairo_translate(m_pdc, centerx, centery);

      cairo_scale(m_pdc, radiusx, radiusy);

      cairo_arc(m_pdc, 0.0, 0.0, 1.0, 0.0, 2.0 * 3.1415);

      keep.restore();

      fill();

      return true;

   }


   bool graphics::FillEllipse(const RECT & lpRect)
   {

      return FillEllipse(lpRect.left, lpRect.top, lpRect.right, lpRect.bottom);

   }


   bool graphics::DrawEllipse(double x1, double y1, double x2, double y2)
   {

      synch_lock ml(cairo_mutex());

      double centerx = (x2 + x1) / 2.0;

      double centery = (y2 + y1) / 2.0;

      double radiusx = fabs(x2 - x1) / 2.0;

      double radiusy = fabs(y2 - y1) / 2.0;

      if (radiusx == 0.0 || radiusy == 0.0)
      {

         return false;

      }

      cairo_keep keep(m_pdc);

      cairo_new_sub_path(m_pdc);

      cairo_translate(m_pdc, centerx, centery);

      cairo_scale(m_pdc, radiusx - m_sppen->m_dWidth / 2.0, radiusy - m_sppen->m_dWidth / 2.0);

      cairo_arc(m_pdc, 0.0, 0.0, 1.0, 0.0, 2.0 * 3.1415);

      keep.pulse();

      set(m_sppen);

      cairo_stroke(m_pdc);

      return true;

   }


   bool graphics::DrawEllipse(const RECTD & lprect)
   {

      return DrawEllipse(lprect.left, lprect.top, lprect.right, lprect.bottom);

   }


   bool graphics::FillEllipse(double x1, double y1, double x2, double y2)
   {

      synch_lock ml(cairo_mutex());

      double centerx = (x2 + x1) / 2.0;

      double centery = (y2 + y1) / 2.0;

      double radiusx = fabs(x2 - x1) / 2.0;

      double radiusy = fabs(y2 - y1) / 2.0;

      if (radiusx == 0.0 || radiusy == 0.0)
      {

         return false;

      }

      cairo_keep keep(m_pdc);

      cairo_new_sub_path(m_pdc);

      cairo_translate(m_pdc, centerx, centery);

      cairo_scale(m_pdc, radiusx, radiusy);

      cairo_arc(m_pdc, 0.0, 0.0, 1.0, 0.0, 2.0 * 3.1415);

      //keep.restore();

      return fill();

   }


   bool graphics::FillEllipse(const RECTD & lpRect)
   {

      return FillEllipse(lpRect.left, lpRect.top, lpRect.right, lpRect.bottom);

   }


   bool graphics::Pie(int32_t x1, int32_t y1, int32_t x2, int32_t y2, int32_t x3, int32_t y3, int32_t x4, int32_t y4)
   {

      ::exception::throw_not_implemented(get_app());

      return false;

   }


   bool graphics::Pie(const RECT & lpRect, POINT ptStart, POINT ptEnd)
   {

      ::exception::throw_not_implemented(get_app());

      return false;

   }


   bool graphics::fill_polygon(const POINTD * pa, count nCount)
   {

      synch_lock ml(cairo_mutex());

      if (nCount <= 0)
      {

         return true;

      }

      cairo_move_to(m_pdc, pa[0].x, pa[0].y);

      for (int32_t i = 1; i < nCount; i++)
      {

         cairo_line_to(m_pdc, pa[i].x, pa[i].y);

      }

      fill();

      return true;

   }


   bool graphics::fill_polygon(const POINT* pa, count nCount)
   {

      synch_lock ml(cairo_mutex());

      if (nCount <= 0)
      {

         return true;

      }

      cairo_move_to(m_pdc, pa[0].x, pa[0].y);

      for (int32_t i = 1; i < nCount; i++)
      {

         cairo_line_to(m_pdc, pa[i].x, pa[i].y);

      }

      fill();

      return true;

   }


   bool graphics::draw_polygon(const POINTD * pa, count nCount)
   {

      synch_lock ml(cairo_mutex());

      if (nCount <= 0)
      {

         return true;

      }

      cairo_move_to(m_pdc, pa[0].x, pa[0].y);

      for (int32_t i = 1; i < nCount; i++)
      {

         cairo_line_to(m_pdc, pa[i].x, pa[i].y);

      }

      draw();

      return true;

   }


   bool graphics::draw_polygon(const POINT* pa, count nCount)
   {

      synch_lock ml(cairo_mutex());

      if (nCount <= 0)
      {

         return true;

      }

      cairo_move_to(m_pdc, pa[0].x, pa[0].y);

      for (int32_t i = 1; i < nCount; i++)
      {

         cairo_line_to(m_pdc, pa[i].x, pa[i].y);

      }

      draw();

      return true;

   }


   bool graphics::polygon(LPCPOINT pa, count nCount)
   {

      synch_lock ml(cairo_mutex());

      if (nCount <= 0)
      {

         return true;

      }

      cairo_move_to(m_pdc, pa[0].x, pa[0].y);

      for (int32_t i = 1; i < nCount; i++)
      {

         cairo_line_to(m_pdc, pa[i].x, pa[i].y);

      }

      return fill_and_draw();

   }


   bool graphics::polygon(LPCPOINTD pa, count nCount)
   {

      synch_lock ml(cairo_mutex());

      if (nCount <= 0)
      {

         return true;

      }

      cairo_move_to(m_pdc, pa[0].x, pa[0].y);

      for (int32_t i = 1; i < nCount; i++)
      {

         cairo_line_to(m_pdc, pa[i].x, pa[i].y);

      }

      return fill_and_draw();

   }


   bool graphics::rectangle(LPCRECT lpRect)
   {

      synch_lock ml(cairo_mutex());

      cairo_rectangle(m_pdc, lpRect->left, lpRect->top, ::width(lpRect), ::height(lpRect));

      return fill_and_draw();

   }


   bool graphics::round_rect(LPCRECT lpRect, LPCPOINT point)
   {

      ::exception::throw_not_implemented(get_app());

      return false;

   }


   bool graphics::PatBlt(int32_t x, int32_t y, int32_t nWidth, int32_t nHeight, uint32_t dwRop)
   {

      ::exception::throw_not_implemented(get_app());

      return false;

   }


   bool graphics::BitBltRaw(int32_t x, int32_t y, int32_t nWidth, int32_t nHeight, ::draw2d::graphics * pgraphicsSrc, int32_t xSrc, int32_t ySrc, uint32_t dwRop)
   {

      synch_lock ml(cairo_mutex());

      cairo_keep keep(m_pdc);

      try
      {

         if (pgraphicsSrc == NULL)
         {

            return false;

         }

         if (nWidth <= 0 || nHeight <= 0)
         {

            return false;

         }

         cairo_surface_t * psurface = cairo_get_target((cairo_t *)pgraphicsSrc->get_os_data());

         if (psurface == NULL)
         {

            return false;

         }

         cairo_pattern_t * ppattern = cairo_pattern_create_for_surface(psurface);

         if (ppattern == NULL)
         {

            return false;

         }

         cairo_matrix_t matrix;

         cairo_matrix_t matrixOld;

         cairo_translate(m_pdc, x, y);

         cairo_pattern_get_matrix(ppattern, &matrixOld);

         cairo_matrix_init_translate(&matrix, xSrc, ySrc);

         cairo_pattern_set_matrix(ppattern, &matrix);

         cairo_rectangle(m_pdc, 0, 0, nWidth, nHeight);

         cairo_clip(m_pdc);

         cairo_set_source(m_pdc, ppattern);

         if (m_ealphamode == ::draw2d::alpha_mode_blend)
         {

            cairo_set_operator(m_pdc, CAIRO_OPERATOR_OVER);

         }
         else if (m_ealphamode == ::draw2d::alpha_mode_set)
         {

            cairo_set_operator(m_pdc, CAIRO_OPERATOR_SOURCE);

         }

         if (m_spregion.is_set() && !m_spregion.cast < region >()->is_simple_positive_region())
         {

            m_spregion.cast < region >()->mask(m_pdc);

         }
         else
         {

            cairo_paint(m_pdc);

         }

         cairo_pattern_set_matrix(ppattern, &matrixOld);

         cairo_pattern_destroy(ppattern);

         return true;

      }
      catch (...)
      {

         return false;

      }

   }


   bool graphics::StretchBltRaw(double xDst, double yDst, double nDstWidth, double nDstHeight, ::draw2d::graphics * pgraphicsSrc, int32_t xSrc, int32_t ySrc, int32_t nSrcWidth, int32_t nSrcHeight, uint32_t dwRop)
   {

      synch_lock ml(cairo_mutex());

      cairo_keep keep(m_pdc);

      if (pgraphicsSrc == NULL)
      {

         return false;

      }

      if (nSrcWidth <= 0 || nSrcHeight <= 0 || nDstWidth <= 0 || nDstHeight <= 0)
      {

         return false;

      }

      if (pgraphicsSrc == NULL || pgraphicsSrc->get_os_data() == NULL)
      {

         return false;

      }

      cairo_surface_t * psurface = cairo_get_target((cairo_t *)pgraphicsSrc->get_os_data());

      if (psurface == NULL)
      {

         return false;

      }

      cairo_pattern_t * ppattern = cairo_pattern_create_for_surface(psurface);

      if (ppattern == NULL)
      {

         return false;

      }

      cairo_matrix_t matrix;

      cairo_matrix_t matrixOld;

      cairo_pattern_get_matrix(ppattern, &matrixOld);

      cairo_translate(m_pdc, xDst, yDst);

      cairo_matrix_init_translate(&matrix, xSrc, ySrc);

      cairo_matrix_scale(&matrix, (double)nSrcWidth / (double)nDstWidth, (double)nSrcHeight / (double)nDstHeight);

      cairo_pattern_set_matrix(ppattern, &matrix);

      cairo_rectangle(m_pdc, 0, 0, nDstWidth, nDstHeight);

      cairo_clip(m_pdc);

      cairo_set_source(m_pdc, ppattern);

      if (m_nStretchBltMode == 0)
      {

         cairo_pattern_set_filter(cairo_get_source(m_pdc), CAIRO_FILTER_NEAREST);

      }
      else if (m_nStretchBltMode == HALFTONE)
      {

         cairo_pattern_set_filter(cairo_get_source(m_pdc), CAIRO_FILTER_GOOD);

      }
      else
      {

         cairo_pattern_set_filter(cairo_get_source(m_pdc), CAIRO_FILTER_FAST);

      }

      if (m_spregion.is_set() && !m_spregion.cast < region >()->is_simple_positive_region())
      {

         m_spregion.cast < region >()->mask(m_pdc);

      }
      else
      {

         cairo_paint(m_pdc);

      }

      cairo_pattern_set_matrix(ppattern, &matrixOld);

      cairo_pattern_destroy(ppattern);

      return true;

   }


   COLORREF graphics::GetPixel(int32_t x, int32_t y)
   {

      ::exception::throw_not_implemented(get_app());

      return false;

   }


   COLORREF graphics::GetPixel(POINT point)
   {

      ::exception::throw_not_implemented(get_app());

      return false;

   }


   COLORREF graphics::SetPixel(int32_t x, int32_t y, COLORREF crColor)
   {

      ::exception::throw_not_implemented(get_app());

      return false;

   }


   COLORREF graphics::SetPixel(POINT point, COLORREF crColor)
   {

      ::exception::throw_not_implemented(get_app());

      return false;

   }


   bool graphics::FloodFill(int32_t x, int32_t y, COLORREF crColor)
   {

      ::exception::throw_not_implemented(get_app());

      return false;

   }


   bool graphics::ExtFloodFill(int32_t x, int32_t y, COLORREF crColor, UINT nFillType)
   {

      ::exception::throw_not_implemented(get_app());

      return false;

   }


   // true blend
   // COLOR_DEST = SRC_ALPHA * COLOR_SRC  + (1 - SRC_ALPHA) * COLOR_DST

   // double blend
   //// COLOR_DEST = SRC_ALPHA * BLEND_ALPHA * COLOR_SRC  + (1 - SRC_ALPHA * BLEND_ALPHA) * COLOR_DST


   bool graphics::text_out(int32_t x, int32_t y, const string & str)
   {

      return ::draw2d::graphics::text_out(double(x), double(y), str);

   }


   bool graphics::text_out(double x, double y, const string & str)
   {

      return text_out((int) x, (int) y, str, (int32_t)str.get_length());

   }


   bool graphics::ExtTextOut(int32_t x, int32_t y, UINT nOptions, const RECT & lpRect, const char * lpszString, strsize nCount, LPINT lpDxWidths)
   {

      ::exception::throw_not_implemented(get_app());

      return false;

   }


   bool graphics::ExtTextOut(int32_t x, int32_t y, UINT nOptions, const RECT & lpRect, const string & str, LPINT lpDxWidths)
   {

      ::exception::throw_not_implemented(get_app());

      return false;

   }


   size graphics::TabbedTextOut(int32_t x, int32_t y, const char * lpszString, strsize nCount, count nTabPositions, LPINT lpnTabStopPositions, int32_t nTabOrigin)
   {

      ::exception::throw_not_implemented(get_app());

      return ::size(0, 0);

   }


   size graphics::TabbedTextOut(int32_t x, int32_t y, const string & str, count nTabPositions, LPINT lpnTabStopPositions, int32_t nTabOrigin)
   {

      ::exception::throw_not_implemented(get_app());

      return ::size(0, 0);

   }


   size graphics::GetTabbedTextExtent(const char * lpszString, strsize nCount, count nTabPositions, LPINT lpnTabStopPositions)
   {

      ::exception::throw_not_implemented(get_app());

      return ::size(0, 0);

   }


   size graphics::GetTabbedTextExtent(const string & str, count nTabPositions, LPINT lpnTabStopPositions)
   {

      ::exception::throw_not_implemented(get_app());

      return ::size(0, 0);

   }


   size graphics::GetOutputTabbedTextExtent(const char * lpszString, strsize nCount, count nTabPositions, LPINT lpnTabStopPositions)
   {

      ::exception::throw_not_implemented(get_app());

      return ::size(0, 0);

   }


   size graphics::GetOutputTabbedTextExtent(const string & str, count nTabPositions, LPINT lpnTabStopPositions)
   {

      ::exception::throw_not_implemented(get_app());

      return ::size(0, 0);

   }


   bool graphics::GrayString(::draw2d::brush* pBrush, bool (CALLBACK* lpfnOutput)(HDC, LPARAM, int32_t), LPARAM lpData, int32_t nCount, int32_t x, int32_t y, int32_t nWidth, int32_t nHeight)
   {

      ::exception::throw_not_implemented(get_app());

      return false;

   }


   UINT graphics::GetTextAlign()
   {

      ::exception::throw_not_implemented(get_app());

      return 0;

   }


   int32_t graphics::GetTextFace(count nCount, LPTSTR lpszFacename)
   {

      ::exception::throw_not_implemented(get_app());

      return 0;

   }


   int32_t graphics::GetTextFace(string & rString)
   {

      ::exception::throw_not_implemented(get_app());

      return 0;

   }


   bool graphics::get_text_metrics(::draw2d::text_metric * lpMetrics)
   {

      synch_lock sl(cairo_mutex());

      if(m_spfont.is_null())
      {

         return false;

      }

      if(m_spfont->m_dFontWidth <= 0.0)
      {

         return false;

      }

#if defined(USE_PANGO)

      PangoFontMap * pfontmap = pango_cairo_font_map_get_default ();

      PangoContext * pcontext = pango_font_map_create_context(pfontmap);

      PangoFontDescription * pdesc = (PangoFontDescription *) m_spfont->get_os_data();

      PangoFont * pfont = pango_font_map_load_font(pfontmap, pcontext, pdesc);

      int iHeight = 0;

      PangoLayout * playout;                            // layout for a paragraph of text

      playout = pango_cairo_create_layout(m_pdc);                 // init pango layout ready for use

      pango_layout_set_text(playout, unitext("ÁÚMGgçy"), -1);          // sets the text to be associated with the layout (final arg is length, -1
      // to calculate automatically when passing a nul-terminated string)
      pango_layout_set_font_description(playout, (PangoFontDescription *) m_spfont->get_os_data());            // assign the previous font description to the layout

      pango_cairo_update_layout(m_pdc, playout);                  // if the target surface or transformation properties of the cairo instance
      // have changed, update the pango layout to reflect this
      int width = 0;

      PangoRectangle pos;

      pango_layout_get_pixel_size(playout, &width, &iHeight);

//      iHeight = pango_font_description_get_size(pdesc);
//
//      if(pango_font_description_get_size_is_absolute(pdesc))
//      {
//
//         iHeight /= PANGO_SCALE;
//
//      }
//      else
//      {
//
//         iHeight = iHeight * 1.333333333333333333 / PANGO_SCALE;
//
//      }

      PangoFontMetrics * pfontmetrics = pango_font_get_metrics(pfont, NULL);

      lpMetrics->tmAscent = (LONG) pango_font_metrics_get_ascent(pfontmetrics) / PANGO_SCALE;

      lpMetrics->tmDescent = (LONG) pango_font_metrics_get_descent(pfontmetrics) / PANGO_SCALE;

      lpMetrics->tmHeight = (LONG) iHeight;

      lpMetrics->tmExternalLeading = (LONG)(lpMetrics->tmHeight - (lpMetrics->tmAscent + lpMetrics->tmDescent));

      lpMetrics->tmInternalLeading = (LONG)0;

      lpMetrics->tmExternalLeading = (LONG)0;

      lpMetrics->tmAveCharWidth = (LONG)pango_font_metrics_get_approximate_char_width (pfontmetrics);

      pango_font_metrics_unref(pfontmetrics);

      g_object_unref(pcontext);

#else

      ((::draw2d_cairo::graphics *) this)->set(m_spfont);

      cairo_font_extents_t e;

      cairo_font_extents(m_pdc, &e);

      lpMetrics->tmAscent = (LONG)e.ascent;

      lpMetrics->tmDescent = (LONG)e.descent;

      lpMetrics->tmHeight = (LONG)e.height;

      lpMetrics->tmExternalLeading = (LONG)(e.height - (e.ascent + e.descent));

      lpMetrics->tmInternalLeading = (LONG)0;

      lpMetrics->tmExternalLeading = (LONG)0;

      string str(L"123AWZwmc123AWZwmcpQçg");

      ::size size = GetTextExtent(str);

      lpMetrics->tmAveCharWidth = (LONG)(size.cx * m_spfont->m_dFontWidth / (double)str.get_length());

#endif

      return true;

   }


   bool graphics::get_output_text_metrics(::draw2d::text_metric * lpMetrics)
   {

      ::exception::throw_not_implemented(get_app());

      return false;

   }


   int32_t graphics::GetTextCharacterExtra()
   {

      ::exception::throw_not_implemented(get_app());

      return 0;

   }


   bool graphics::GetCharWidth(UINT nFirstChar, UINT nLastChar, LPINT lpBuffer)
   {

      ::exception::throw_not_implemented(get_app());

      return false;

   }


   bool graphics::GetOutputCharWidth(UINT nFirstChar, UINT nLastChar, LPINT lpBuffer)
   {

      ::exception::throw_not_implemented(get_app());

      return false;

   }


   uint32_t graphics::GetFontLanguageInfo()
   {

      ::exception::throw_not_implemented(get_app());

      return 0;

   }


   size graphics::GetAspectRatioFilter()
   {

      ::exception::throw_not_implemented(get_app());

      return size(0, 0);

   }


   bool graphics::ScrollDC(int32_t dx, int32_t dy, const RECT & lpRectScroll, const RECT & lpRectClip, ::draw2d::region* pRgnUpdate, LPRECT lpRectUpdate)
   {

      ::exception::throw_not_implemented(get_app());

      return false;

   }


   // Printer Escape Functions
   int32_t graphics::Escape(int32_t nEscape, int32_t nCount, const char * lpszInData, LPVOID lpOutData)
   {

      ::exception::throw_not_implemented(get_app());

      return 0;

   }


   // graphics 3.1 Specific functions
   UINT graphics::SetBoundsRect(const RECT & lpRectBounds, UINT flags)
   {

      ::exception::throw_not_implemented(get_app());

      return 0;

   }


   UINT graphics::GetBoundsRect(LPRECT lpRectBounds, UINT flags)
   {

      ::exception::throw_not_implemented(get_app());

      return 0;

   }


   uint32_t graphics::GetFontData(uint32_t dwTable, uint32_t dwOffset, LPVOID lpData, uint32_t cbData)
   {

      ::exception::throw_not_implemented(get_app());

      return 0;

   }


   int32_t graphics::StartPage()
   {

      ::exception::throw_not_implemented(get_app());

      return 0;

   }


   int32_t graphics::EndPage()
   {

      ::exception::throw_not_implemented(get_app());

      return 0;

   }


   int32_t graphics::SetAbortProc(bool (CALLBACK* lpfn)(HDC, int32_t))
   {

      ::exception::throw_not_implemented(get_app());

      return 0;

   }


   int32_t graphics::AbortDoc()
   {

      ::exception::throw_not_implemented(get_app());

      return 0;

   }


   int32_t graphics::EndDoc()
   {

      ::exception::throw_not_implemented(get_app());

      return 0;

   }


   bool graphics::MaskBlt(int32_t x, int32_t y, int32_t nWidth, int32_t nHeight, ::draw2d::graphics * pgraphicsSrc, int32_t xSrc, int32_t ySrc, ::draw2d::bitmap& maskBitmap, int32_t xMask, int32_t yMask, uint32_t dwRop)
   {

      ::exception::throw_not_implemented(get_app());

      return false;

   }


   bool graphics::PlgBlt(LPPOINT lpPoint, ::draw2d::graphics * pgraphicsSrc, int32_t xSrc, int32_t ySrc, int32_t nWidth, int32_t nHeight, ::draw2d::bitmap& maskBitmap, int32_t xMask, int32_t yMask)
   {

      ::exception::throw_not_implemented(get_app());

      return false;

   }


   bool graphics::SetPixelV(int32_t x, int32_t y, COLORREF crColor)
   {

      ::exception::throw_not_implemented(get_app());

      return false;

   }


   bool graphics::SetPixelV(POINT point, COLORREF crColor)
   {

      ::exception::throw_not_implemented(get_app());

      return false;

   }


   bool graphics::AngleArc(int32_t x, int32_t y, int32_t nRadius, float fStartAngle, float fSweepAngle)
   {

      ::exception::throw_not_implemented(get_app());

      return false;

   }


   bool graphics::ArcTo(const RECT & lpRect, POINT ptStart, POINT ptEnd)
   {

      ::exception::throw_not_implemented(get_app());

      return false;

   }


   int32_t graphics::GetArcDirection()
   {

      ::exception::throw_not_implemented(get_app());

      return 0;

   }


   bool graphics::PolyPolyline(const POINT* lpPoints, const INT * lpPolyPoints, count nCount)
   {

      ::exception::throw_not_implemented(get_app());

      return false;

   }


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


   bool graphics::PolyBezier(const POINT* lpPoints, count nCount)
   {

      ::exception::throw_not_implemented(get_app());

      return false;

   }


   int32_t graphics::DrawEscape(int32_t nEscape, int32_t nInputSize, const char * lpszInputData)
   {

      ::exception::throw_not_implemented(get_app());

      return 0;

   }


   int32_t graphics::Escape(int32_t nEscape, int32_t nInputSize, const char * lpszInputData, int32_t nOutputSize, char * lpszOutputData)
   {

      ::exception::throw_not_implemented(get_app());

      return 0;

   }


   bool graphics::GetCharWidth(UINT nFirstChar, UINT nLastChar, float* lpFloatBuffer)
   {

      ::exception::throw_not_implemented(get_app());

      return false;

   }


   bool graphics::abort_path()
   {

      ::exception::throw_not_implemented(get_app());

      return false;

   }


   bool graphics::begin_path()
   {

      ::exception::throw_not_implemented(get_app());

      return false;

   }


   bool graphics::close_figure()
   {

      ::exception::throw_not_implemented(get_app());

      return false;

   }


   bool graphics::end_path()
   {

      ::exception::throw_not_implemented(get_app());

      return false;

   }


   bool graphics::fill_path()
   {

      ::exception::throw_not_implemented(get_app());

      return false;

   }


   bool graphics::flatten_path()
   {

      ::exception::throw_not_implemented(get_app());

      return false;

   }


   float graphics::GetMiterLimit()
   {

      ::exception::throw_not_implemented(get_app());

      return 0.f;

   }


   int32_t graphics::GetPath(LPPOINT lpPoints, LPBYTE lpTypes, count nCount)
   {

      ::exception::throw_not_implemented(get_app());

      return 0;

   }


   bool graphics::SetMiterLimit(float fMiterLimit)
   {

      ::exception::throw_not_implemented(get_app());

      return false;

   }


   bool graphics::stroke_and_fill_path()
   {

      ::exception::throw_not_implemented(get_app());

      return false;

   }


   bool graphics::stroke_path()
   {

      ::exception::throw_not_implemented(get_app());

      return false;

   }


   bool graphics::widen_path()
   {

      ::exception::throw_not_implemented(get_app());

      return false;

   }


   bool graphics::draw_path(::draw2d::path * ppath)
   {

      synch_lock ml(cairo_mutex());

      if (!set(ppath))
      {

         return false;

      }

      return draw();

   }


   bool graphics::fill_path(::draw2d::path * ppath)
   {

      synch_lock ml(cairo_mutex());

      if (!set(ppath))
      {

         return false;

      }

      return fill();

   }


   bool graphics::draw_path(::draw2d::path * ppath, ::draw2d::pen * ppen)
   {

      synch_lock ml(cairo_mutex());

      if (!set(ppath))
      {

         return false;

      }

      return draw(ppen);

   }


   bool graphics::fill_path(::draw2d::path * ppath, ::draw2d::brush * pbrush)
   {

      synch_lock ml(cairo_mutex());

      if (!set(ppath))
      {

         return false;

      }

      return fill(pbrush);

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

      synch_lock ml(cairo_mutex());

      cairo_keep keep(m_pdc);

      try
      {

         if (pgraphicsSrc == NULL)
         {

            return false;

         }

         if (nDstWidth <= 0 || nDstWidth <= 0)
         {

            return false;

         }

         if (pgraphicsSrc->get_os_data() == NULL)
         {

            return false;

         }

         cairo_surface_t * psurface = cairo_get_target((cairo_t *)pgraphicsSrc->get_os_data());

         if (psurface == NULL)
         {

            return false;

         }

         cairo_pattern_t * ppattern = cairo_pattern_create_for_surface(psurface);

         if (ppattern == NULL)
         {

            return false;

         }

         cairo_matrix_t matrix;

         cairo_matrix_t matrixOld;

         cairo_translate(m_pdc, xDst, yDst);

         cairo_pattern_get_matrix(ppattern, &matrixOld);

         cairo_matrix_init_translate(&matrix, xSrc, ySrc);

         cairo_pattern_set_matrix(ppattern, &matrix);

         cairo_rectangle(m_pdc, 0, 0, nDstWidth, nDstHeight);

         cairo_clip(m_pdc);

         cairo_set_source(m_pdc, ppattern);

         if (m_ealphamode == ::draw2d::alpha_mode_blend)
         {

            cairo_set_operator(m_pdc, CAIRO_OPERATOR_OVER);

         }
         else if (m_ealphamode == ::draw2d::alpha_mode_set)
         {

            cairo_set_operator(m_pdc, CAIRO_OPERATOR_SOURCE);

         }

         if (m_spregion.is_set() && !m_spregion.cast < region >()->is_simple_positive_region())
         {

            m_spregion.cast < region >()->mask(m_pdc);

         }
         else
         {

            cairo_paint_with_alpha(m_pdc, dRate);

         }

         cairo_pattern_set_matrix(ppattern, &matrixOld);

         cairo_pattern_destroy(ppattern);

         return true;

      }
      catch (...)
      {

         return false;

      }

   }


   bool graphics::TransparentBlt(int32_t xDest, int32_t yDest, int32_t nDestWidth, int32_t nDestHeight, ::draw2d::graphics * pgraphicsSrc, int32_t xSrc, int32_t ySrc, int32_t nSrcWidth, int32_t nSrcHeight, UINT crTransparent)
   {

      ::exception::throw_not_implemented(get_app());

      return false;

   }


   bool graphics::GradientFill(TRIVERTEX* pVertices, WINULONG nVertices, void * pMesh, WINULONG nMeshElements, uint32_t dwMode)
   {

      ::exception::throw_not_implemented(get_app());

      return false;

   }


#if (_WIN32_WINNT >= 0x0500)

   // Always Inline. Functions only in Win98/Win2K or later

   COLORREF graphics::GetDCBrushColor()
   {

      ::exception::throw_not_implemented(get_app());

      return 0;

   }


   COLORREF graphics::SetDCBrushColor(COLORREF crColor)
   {

      ::exception::throw_not_implemented(get_app());

      return 0;

   }


   COLORREF graphics::GetDCPenColor()
   {

      ::exception::throw_not_implemented(get_app());

      return 0;

   }


   COLORREF graphics::SetDCPenColor(COLORREF crColor)
   {

      ::exception::throw_not_implemented(get_app());

      return 0;

   }


#endif


#if (_WIN32_WINNT >= 0x0500)


   bool graphics::GetCharABCWidthsI(UINT giFirst, UINT cgi, LPWORD pgi, LPABC lpabc)
   {

      ::exception::throw_not_implemented(get_app());

      return false;

   }


   bool graphics::GetCharWidthI(UINT giFirst, UINT cgi, LPWORD pgi, LPINT lpBuffer)
   {

      ::exception::throw_not_implemented(get_app());

      return false;

   }


#endif


#if (_WIN32_WINNT >= 0x0500)


   bool graphics::GetTextExtentExPointI(LPWORD pgiIn, int32_t cgi, int32_t nMaxExtent, LPINT lpnFit, LPINT alpDx, LPSIZE lpSize)
   {

      ::exception::throw_not_implemented(get_app());

      return false;

   }


   bool graphics::GetTextExtentPointI(LPWORD pgiIn, int32_t cgi, LPSIZE lpSize)
   {

      ::exception::throw_not_implemented(get_app());

      return false;

   }


#endif


   /////////////////////////////////////////////////////////////////////////////
   // More coordinate transforms (in separate file to avoid transitive refs)


#define HIMETRIC_INCH   2540    // HIMETRIC units per inch


   void graphics::DPtoHIMETRIC(LPSIZE lpSize)
   {

      ::exception::throw_not_implemented(get_app());

   }


   void graphics::HIMETRICtoDP(LPSIZE lpSize)
   {

      ::exception::throw_not_implemented(get_app());

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


   ::draw2d::brush * PASCAL graphics::GetHalftoneBrush(::aura::application * papp)
   {

      return NULL;

   }


   void graphics::DrawDragRect(const RECT & lpRect, SIZE size, const RECT & lpRectLast, SIZE sizeLast, ::draw2d::brush* pBrush, ::draw2d::brush* pBrushLast)
   {

      ::exception::throw_not_implemented(get_app());

   }


   void graphics::draw3d_rect(LPCRECT lpcrect, COLORREF clrTopLeft, COLORREF clrBottomRight)
   {

      synch_lock ml(cairo_mutex());

      int x = lpcrect->left;

      int y = lpcrect->top;

      int cx = ::width(lpcrect);

      int cy = ::height(lpcrect);

      fill_solid_rect_dim(x, y, cx - 1, 1, clrTopLeft);

      fill_solid_rect_dim(x, y, 1, cy - 1, clrTopLeft);

      fill_solid_rect_dim(x + cx - 1, y, 1, cy, clrBottomRight);

      fill_solid_rect_dim(x, y + cy - 1, cx, 1, clrBottomRight);

   }


   bool graphics::DeleteDC()
   {

      synch_lock ml(cairo_mutex());

      if (m_pdc == NULL)
      {

         return true;

      }

      cairo_destroy(m_pdc);

      m_pdc = NULL;

      return true;

   }


   int32_t graphics::StartDoc(const char * lpszDocName)
   {

      ::exception::throw_not_implemented(get_app());

      return 0;

   }


   int32_t graphics::SaveDC()
   {

      synch_lock sl(cairo_mutex());

      m_iSaveDC++;

      cairo_save(m_pdc);

      return m_iSaveDC;

   }


   bool graphics::RestoreDC(int32_t nSavedDC)
   {

      synch_lock sl(cairo_mutex());

      bool bRestored = false;

      while (m_iSaveDC >= nSavedDC)
      {

         cairo_restore(m_pdc);

         m_iSaveDC--;

         bRestored = true;

      }

      if (m_iSaveDC < m_iSaveDCPositiveClip)
      {

         m_iSaveDCPositiveClip = -1;

      }

      return bRestored;

   }


   ::draw2d::object* graphics::SelectStockObject(int32_t nIndex)
   {

      return NULL;

   }


   ::draw2d::pen* graphics::SelectObject(::draw2d::pen* ppen)
   {

      m_sppen = ppen;

      return m_sppen;

   }


   ::draw2d::brush* graphics::SelectObject(::draw2d::brush* pbrush)
   {

      m_spbrush = pbrush;

      return m_spbrush;

   }


   ::draw2d::font* graphics::SelectObject(::draw2d::font* pfont)
   {

      if (!select_font(pfont))
      {

         return NULL;

      }

      return m_spfont;

   }


   int32_t graphics::SelectObject(::draw2d::region* pRgn)
   {

      ::exception::throw_not_implemented(get_app());

      return false;

   }


   ::draw2d::palette* graphics::SelectPalette(::draw2d::palette* pPalette, bool bForceBackground)
   {

      return NULL;

   }


   int32_t graphics::SetPolyFillMode(int32_t nPolyFillMode)
   {

      ::exception::throw_not_implemented(get_app());

      return 0;

   }


   int32_t graphics::SetROP2(int32_t nDrawMode)
   {

      ::exception::throw_not_implemented(get_app());

      return 0;

   }


   int32_t graphics::SetStretchBltMode(int32_t nStretchMode)
   {

      m_nStretchBltMode = nStretchMode;

      return 1;

   }


   int32_t graphics::SetGraphicsMode(int32_t iMode)
   {

      ::exception::throw_not_implemented(get_app());

      return 0;

   }


   bool graphics::SetWorldTransform(const XFORM* pXform)
   {

      ::exception::throw_not_implemented(get_app());

      return false;

   }


   bool graphics::ModifyWorldTransform(const XFORM* pXform, uint32_t iMode)
   {

      ::exception::throw_not_implemented(get_app());

      return false;

   }


   int32_t graphics::SetMapMode(int32_t nMapMode)
   {

      return 0;

   }


   point graphics::GetViewportOrg()
   {

      return ::draw2d::graphics::GetViewportOrg();

   }


   point graphics::SetViewportOrg(int32_t x, int32_t y)
   {

      return ::draw2d::graphics::SetViewportOrg(x, y);

   }


   point graphics::OffsetViewportOrg(int32_t nWidth, int32_t nHeight)
   {

      return ::draw2d::graphics::OffsetViewportOrg(nWidth, nHeight);

   }


   size graphics::SetViewportExt(int32_t x, int32_t y)
   {

      ::exception::throw_not_implemented(get_app());

      return ::size(0, 0);

   }


   size graphics::ScaleViewportExt(double xNum, double xDenom, double yNum, double yDenom)
   {

      return ::draw2d::graphics::ScaleViewportExt(xNum, xDenom, yNum, yDenom);

   }


   point graphics::SetWindowOrg(int32_t x, int32_t y)
   {

      ::exception::throw_not_implemented(get_app());

      return ::point(0, 0);

   }


   point graphics::OffsetWindowOrg(int32_t nWidth, int32_t nHeight)
   {

      ::exception::throw_not_implemented(get_app());

      return ::point(0, 0);

   }


   size graphics::SetWindowExt(int32_t x, int32_t y)
   {

      ::exception::throw_not_implemented(get_app());

      return ::size(0, 0);

   }


   size graphics::ScaleWindowExt(int32_t xNum, int32_t xDenom, int32_t yNum, int32_t yDenom)
   {

      ::exception::throw_not_implemented(get_app());

      return ::size(0, 0);

   }


   int32_t graphics::GetClipBox(LPRECT lpRect)
   {

      return 0;

   }


   int32_t graphics::SelectClipRgn(::draw2d::region * pregion)
   {

      synch_lock ml(cairo_mutex());

      if (pregion == NULL)
      {

         if (m_iSaveDCPositiveClip >= 0)
         {

            // is better in  cairo to restore the DC instead of resetting clipping

            //RestoreDC(m_iSaveDCPositiveClip);
            // cairo_reset_clip(m_pdc);

            m_iSaveDCPositiveClip = -1;

         }

         m_spregion.release();

      }
      else
      {

         if (m_spregion.is_null())
         {

            m_spregion.alloc(allocer());

         }

         m_spregion = pregion;

         if (m_spregion.cast < region >()->is_simple_positive_region())
         {

            //if (m_iSaveDCPositiveClip > 0)
            //{

            //   RestoreDC(m_iSaveDCPositiveClip);

            //}

            //m_iSaveDCPositiveClip = SaveDC();

            m_spregion.cast < region >()->clip(m_pdc);

         }

      }

      return 0;

   }


   int32_t graphics::ExcludeClipRect(int32_t x1, int32_t y1, int32_t x2, int32_t y2)
   {

      ::exception::throw_not_implemented(get_app());

      return 0;

   }


   int32_t graphics::ExcludeClipRect(const RECT & lpRect)
   {

      ::exception::throw_not_implemented(get_app());

      return 0;

   }


   int32_t graphics::IntersectClipRect(int32_t x1, int32_t y1, int32_t x2, int32_t y2)
   {

      synch_lock ml(cairo_mutex());

      cairo_rectangle(m_pdc, x1, y1, x2 - x1, y2 - y1);

      cairo_clip(m_pdc);

      return 0;

   }


   int32_t graphics::OffsetClipRgn(int32_t x, int32_t y)
   {

      ::exception::throw_not_implemented(get_app());

      return 0;

   }

   int32_t graphics::OffsetClipRgn(SIZE size)
   {

      ::exception::throw_not_implemented(get_app());

      return 0;

   }


   bool graphics::move_to(LPCPOINT ppt)
   {

      synch_lock ml(cairo_mutex());

      point point(0, 0);

      if (cairo_has_current_point(m_pdc))
      {

         double dx = 0.;

         double dy = 0.;

         cairo_get_current_point(m_pdc, &dx, &dy);

         point.x = (LONG)dx;

         point.y = (LONG)dy;

      }

      cairo_move_to(m_pdc, ppt->x, ppt->y);

      m_pt = *ppt;

      return true;

   }


   bool graphics::move_to(LPCPOINTD ppt)
   {

      synch_lock ml(cairo_mutex());

      pointd point(0., 0.);

      if (cairo_has_current_point(m_pdc))
      {

         double dx = 0.;

         double dy = 0.;

         cairo_get_current_point(m_pdc, &dx, &dy);

         point.x = dx;

         point.y = dy;

      }

      cairo_move_to(m_pdc, ppt->x,ppt->y);

      m_pt = *ppt;

      return true;

   }


   UINT graphics::SetTextAlign(UINT nFlags)
   {

      return 0;

   }


   int32_t graphics::SetTextJustification(int32_t nBreakExtra, int32_t nBreakCount)
   {

      ::exception::throw_not_implemented(get_app());

      return 0;

   }


   int32_t graphics::SetTextCharacterExtra(int32_t nCharExtra)
   {

      ::exception::throw_not_implemented(get_app());

      return 0;

   }


   uint32_t graphics::SetMapperFlags(uint32_t dwFlag)
   {

      ::exception::throw_not_implemented(get_app());

      return 0;

   }


   uint32_t graphics::GetLayout()
   {

      ::exception::throw_not_implemented(get_app());

      return 0;

   }


   uint32_t graphics::SetLayout(uint32_t dwSetLayout)
   {

      ::exception::throw_not_implemented(get_app());

      return 0;

   }


   bool graphics::ArcTo(int32_t x1, int32_t y1, int32_t x2, int32_t y2, int32_t x3, int32_t y3, int32_t x4, int32_t y4)
   {

      ::exception::throw_not_implemented(get_app());

      return false;

   }


   int32_t graphics::SetArcDirection(int32_t nArcDirection)
   {

      ::exception::throw_not_implemented(get_app());

      return 0;

   }


   bool graphics::PolyDraw(const POINT* lpPoints, const BYTE* lpTypes, count nCount)
   {

      ::exception::throw_not_implemented(get_app());

      return false;

   }


   bool graphics::PolylineTo(const POINT* lpPoints, count nCount)
   {

      ::exception::throw_not_implemented(get_app());

      return false;

   }


   bool graphics::PolyBezierTo(const POINT* lpPoints, count nCount)
   {

      ::exception::throw_not_implemented(get_app());

      return 0;

   }


   bool graphics::SelectClipPath(int32_t nMode)
   {

      ::exception::throw_not_implemented(get_app());

      return 0;

   }


   int32_t graphics::SelectClipRgn(::draw2d::region* pRgn, int32_t nMode)
   {

      return SelectClipRgn(pRgn);

   }


   void graphics::LPtoDP(LPSIZE lpSize)
   {

      ::exception::throw_not_implemented(get_app());

      return;

   }


   void graphics::DPtoLP(LPSIZE lpSize)
   {

      ::exception::throw_not_implemented(get_app());

      return;

   }


   bool graphics::draw_text(const char * lpszString, strsize nCount, const RECT & lpRect, UINT nFormat)
   {

      return draw_text(string(lpszString, nCount), lpRect, nFormat);

   }


#if defined(USE_PANGO)


   bool graphics::draw_text(const string & strParam, const RECT & rect, UINT nFormat)
   {

      synch_lock ml(cairo_mutex());

      cairo_keep keep(m_pdc);

      RECTD rectd;

      rectd.left = rect.left;

      rectd.top = rect.top;

      rectd.right = rect.right;

      rectd.bottom = rect.bottom;

      return internal_draw_text(strParam, strParam.get_length(), rectd, nFormat);

   }


   bool graphics::internal_draw_text(const char * lpszString, strsize nCount, const RECTD & rectd, UINT nFormat)
   {

      return internal_draw_text_pango(lpszString, nCount, rectd, nFormat, &pango_cairo_show_layout);

   }


   bool graphics::internal_draw_text_pango(const char * lpszString, strsize nCount, const RECTD & rectd, UINT nFormat, PFN_PANGO_TEXT pfnPango)
   {

      synch_lock ml(cairo_mutex());

      if(m_spfont.is_null())
      {

         return false;

      }

      if(m_spfont->m_dFontSize <= 0.0 || m_spfont->m_dFontWidth <= 0.0)
      {

         return false;

      }

      ::draw2d::savedc savedc(this);

      PangoLayout * playout;                            // layout for a paragraph of text

      // drawing will start from).
      playout = pango_cairo_create_layout(m_pdc);                 // init pango layout ready for use

      //pango_layout_set_width(playout, width(rectd));

      //pango_layout_set_height(playout, height(rectd));

      pango_layout_set_text(playout, lpszString, -1);          // sets the text to be associated with the layout (final arg is length, -1

      pango_layout_set_font_description(playout, (PangoFontDescription *) m_spfont->get_os_data());            // assign the previous font description to the layout

      //pango_cairo_update_layout(m_pdc, playout);                  // if the target surface or transformation properties of the cairo instance

      PangoRectangle r;

      pango_layout_get_pixel_extents (playout, NULL, &r);

      pointd ptRef;

      if(nFormat & DT_BOTTOM)
      {

         cairo_translate(m_pdc, 0, rectd.bottom - r.height);

         ptRef.y = rectd.bottom - r.height;

      }
      else if(nFormat & DT_VCENTER)
      {

         cairo_translate(m_pdc, 0, ((rectd.top + rectd.bottom) / 2 - (r.height / 2)));

         ptRef.y = ((rectd.top + rectd.bottom) / 2 - (r.height / 2));

      }
      else
      {

         cairo_translate(m_pdc, 0, rectd.top);

         ptRef.y = rectd.top;

      }

      if(nFormat & DT_RIGHT)
      {

         cairo_translate(m_pdc, rectd.right - r.width, 0);

         ptRef.x = rectd.right - r.width;

      }
      else if(nFormat & DT_CENTER)
      {

         cairo_translate(m_pdc, ((rectd.left + rectd.right) / 2) - (r.width/2), 0);

         ptRef.x = ((rectd.left + rectd.right) / 2) - (r.width/2);

      }
      else
      {

         cairo_translate(m_pdc, rectd.left, 0);

         ptRef.x = rectd.left;

      }

      cairo_scale(m_pdc, m_spfont->m_dFontWidth, 1.0);

      pango_cairo_update_layout(m_pdc, playout);

      if(m_spbrush.is_set())
      {

         set(m_spbrush, ptRef.x, ptRef.y);

      }

      // have changed, update the pango layout to reflect this
      (*pfnPango)(m_pdc, playout);                    // draw the pango layout onto the cairo surface

      g_object_unref(playout);                         // free the layout

   }


#else


   bool graphics::draw_text(const string & strParam, const RECT & lpRect, UINT nFormat)
   {

      return internal_draw_text(strParam, strParam.get_length(), lpRect, nFormat, &cairo_show_text);

   }


   bool graphics::internal_draw_text(const char * lpszString, strsize nCount, const RECT & lpRect, UINT nFormat, PFN_CAIRO_TEXT ftext)
   {

      string str(lpszString, nCount);

      str = ::str::q_valid(str);

      if (str.is_empty())
      {

         return -1;

      }

      synch_lock ml(cairo_mutex());

      if (m_spfont.is_null())
      {

         return false;

      }

      if (m_spfont->m_dFontWidth <= 0.0)
      {

         return -1;

      }

      cairo_keep keep(m_pdc);

      set(m_spfont);

      cairo_font_extents_t e;

      cairo_font_extents(m_pdc, &e);

      size sz = GetTextExtent(str);

      double dx;

      double dy;

      if (nFormat & DT_RIGHT)
      {

         dx = lpRect.right - lpRect.left - sz.cx;

      }
      else if (nFormat & DT_CENTER)
      {

         dx = ((lpRect.right - lpRect.left) - (sz.cx)) / 2.0;

      }
      else
      {

         dx = 0.;

      }

      if (nFormat & DT_BOTTOM)
      {

         dy = lpRect.bottom - lpRect.top - e.ascent;

      }
      else if (nFormat & DT_VCENTER)
      {

         dy = ((lpRect.bottom - lpRect.top) - (e.ascent)) / 2.0;

      }
      else
      {

         dy = 0.;

      }

      if (m_spfont->m_dFontWidth != 1.0)
      {

         cairo_matrix_t m;

         cairo_get_matrix(m_pdc, &m);

         cairo_matrix_scale(&m, m_spfont->m_dFontWidth, 1.0);

         cairo_set_matrix(m_pdc, &m);

      }

      if (m_spbrush.is_set())
      {

         set_os_color(m_spbrush->m_cr);

      }

      if (nFormat & DT_EXPANDTABS)
      {

         str.replace("\t", "        ");

      }
      else
      {

         str.replace("\t", "");

      }

      if (nFormat & DT_SINGLELINE)
      {

         str.replace("\n", "");

         str.replace("\r", "");

      }

      stringa stra;

      stra.add_lines(str);

      int i = 0;

      for (auto & strLine : stra)
      {

         cairo_move_to(m_pdc, lpRect.left + dx, lpRect.top + dy + e.ascent + sz.cy * (i) / stra.get_size());

         (*ftext)(m_pdc, strLine);

         cairo_status_t status = cairo_status(m_pdc);

         if (status != CAIRO_STATUS_SUCCESS)
         {

            const char * pszStatus = cairo_status_to_string(status);

            TRACE("cairo error : graphics::draw_text %d %s", status, pszStatus);

         }

         i++;

      }

      return 1;

   }


#endif


   bool graphics::draw_text_ex(LPTSTR lpszString, strsize nCount, const RECT & lpRect, UINT nFormat, LPDRAWTEXTPARAMS lpDTParams)
   {

      ::exception::throw_not_implemented(get_app());

      return 0;

   }


   bool graphics::draw_text_ex(const string & str, const RECT & lpRect, UINT nFormat, LPDRAWTEXTPARAMS lpDTParams)
   {

      ::exception::throw_not_implemented(get_app());

      return 0;

   }


   sized graphics::GetTextExtent(const char * lpszString, strsize nCount, strsize iIndex)
   {

      sized sz;

      if (!GetTextExtent(sz, lpszString, nCount, iIndex))
      {

         return ::sized(0.0, 0.0);

      }

      return sz;

   }


   sized graphics::GetTextExtent(const char * lpszString, strsize nCount)
   {

      return GetTextExtent(lpszString, nCount, -1);

   }


   sized graphics::GetTextExtent(const string & str)
   {

      return GetTextExtent(str, str.get_length());

   }


   size graphics::GetOutputTextExtent(const char * lpszString, strsize nCount)
   {

      ::exception::throw_not_implemented(get_app());

      return ::sized(0, 0);

   }


   size graphics::GetOutputTextExtent(const string & str)
   {

      ::exception::throw_not_implemented(get_app());

      return ::size(0, 0);

   }


   bool graphics::GetTextExtent(sized & size, const char * lpszString, strsize nCount, strsize iIndex)
   {

      string str(lpszString, min_non_neg(iIndex, nCount));

      str = ::str::q_valid(str);

      if(str.is_empty())
      {

         return false;

      }

      synch_lock ml(cairo_mutex());

      if(m_spfont.is_null())
      {

         return false;

      }

      if(m_spfont->m_dFontWidth <= 0.0)
      {

         return false;

      }

      if (iIndex < 0)
      {

         iIndex = (int32_t)nCount;

      }

      stringa stra;

      stra.add_lines(str, true);

#if defined(USE_PANGO)

      if(stra.get_count() == 1 && iIndex < nCount && iIndex >= 0)
      {

         PangoLayout * playout;                            // layout for a paragraph of text

         playout = pango_cairo_create_layout(m_pdc);                 // init pango layout ready for use

         pango_layout_set_text(playout, lpszString, -1);          // sets the text to be associated with the layout (final arg is length, -1
         // to calculate automatically when passing a nul-terminated string)
         pango_layout_set_font_description(playout, (PangoFontDescription *) m_spfont->get_os_data());            // assign the previous font description to the layout

         pango_cairo_update_layout(m_pdc, playout);                  // if the target surface or transformation properties of the cairo instance
         // have changed, update the pango layout to reflect this
         int width = 0;

         int height = 0;

         PangoRectangle pos;

         pango_layout_index_to_pos(playout, iIndex, &pos);

         pango_layout_get_pixel_size(playout, &width, &height);

         size.cx = (double) pos.x / (double) PANGO_SCALE;

         size.cy = height;

         g_object_unref(playout);                         // free the layout

         return true;

      }

#endif

      sized s0(0.0, 0.0);

      size.cx = 0.0;

      size.cy = 0.0;

      for (auto & str : stra)
      {

         _GetTextExtent(s0, str, str.get_length(), str.get_length());

         size.cx = MAX(size.cx, s0.cx);

         size.cy += s0.cy;

      }

      return true;

   }


   bool graphics::_GetTextExtent(sized & size, const char * lpszString, strsize nCount, strsize iIndex)
   {

      if (iIndex < 0)
      {

         iIndex = (int32_t)nCount;

      }

      string str(lpszString, MIN(iIndex, nCount));

      str = ::str::q_valid(str);

      if (str.is_empty())
      {

         return false;

      }

      synch_lock ml(cairo_mutex());

      if(m_spfont.is_null())
      {

         return false;

      }

      if(m_spfont->m_dFontWidth <= 0.0)
      {

         return false;

      }

      cairo_keep keep(m_pdc);

#if defined(USE_PANGO)

      PangoLayout * playout;                            // layout for a paragraph of text

      playout = pango_cairo_create_layout(m_pdc);                 // init pango layout ready for use

      pango_layout_set_text(playout, lpszString, -1);          // sets the text to be associated with the layout (final arg is length, -1
      // to calculate automatically when passing a nul-terminated string)
      pango_layout_set_font_description(playout, (PangoFontDescription *) m_spfont->get_os_data());            // assign the previous font description to the layout

      pango_cairo_update_layout(m_pdc, playout);                  // if the target surface or transformation properties of the cairo instance
      // have changed, update the pango layout to reflect this
      int width = 0;

      int height = 0;

      pango_layout_get_pixel_size (playout, &width, &height);

      g_object_unref(playout);                         // free the layout

      size.cx = width * m_spfont->m_dFontWidth;

      size.cy = height;
#else

      ((graphics *)this)->set(m_spfont);

      cairo_text_extents_t ex;

      cairo_font_extents_t e;

      if (::str::begins(str, unitext("バーチャルマシン")))
      {

         TRACE("Likely to fail in certain circumstances");

      }

      cairo_font_extents(m_pdc, &e);

      if (!str.has_char())
      {

         size.cx = 0;

         size.cy = e.height;

         return true;

      }

      cairo_text_extents(m_pdc, str, &ex);

      cairo_status_t status = cairo_status(m_pdc);

      if (status != CAIRO_STATUS_SUCCESS)
      {

         const char * pszStatus = cairo_status_to_string(status);

         TRACE("cairo error : graphics::_GetTextExtent %d %s", status, pszStatus);

      }

      size.cx = (LONG)(ex.x_advance * m_spfont->m_dFontWidth);

      size.cy = (LONG)e.height;

#endif

      return true;

   }


   bool graphics::GetTextExtent(sized & size, const char * lpszString, strsize nCount)
   {

      return GetTextExtent(size, lpszString, nCount, -1);

   }


   bool graphics::GetTextExtent(sized & size, const string & str)
   {

      return GetTextExtent(size, str, str.get_length());

   }


   void graphics::fill_solid_rect(LPCRECT lpRect, COLORREF clr)
   {

      synch_lock ml(cairo_mutex());

      if (lpRect->right <= lpRect->left || lpRect->bottom <= lpRect->top)
      {

         return;

      }

      set_os_color(clr);

      cairo_rectangle(m_pdc, lpRect->left, lpRect->top, lpRect->right - lpRect->left, lpRect->bottom - lpRect->top);

      cairo_fill(m_pdc);

   }


   void graphics::fill_solid_rect(LPCRECTD lpRect, COLORREF clr)
   {

      synch_lock ml(cairo_mutex());

      if (lpRect->right <= lpRect->left || lpRect->bottom <= lpRect->top)
      {

         return;

      }

      set_os_color(clr);

      cairo_rectangle(m_pdc, lpRect->left, lpRect->top, lpRect->right - lpRect->left, lpRect->bottom - lpRect->top);

      cairo_fill(m_pdc);

   }


   bool graphics::text_out(int32_t x, int32_t y, const char * lpszString, strsize nCount)
   {

      return text_out(x, y, string(lpszString, nCount));

   }


   bool graphics::TextOutRaw(double x, double y, const char * lpszString, strsize nCount)
   {

      synch_lock ml(cairo_mutex());

      cairo_keep keep(m_pdc);

#if defined(USE_PANGO)

      ::rectd r = ::rectd(pointd(x, y), sized(65535.0, 65535.0));

      internal_draw_text(lpszString, nCount, r, 0);

#else

      ::rect rect = ::rect_dim(
                    LONG(x),
                    LONG(y),
                    65535,
                    65535
                    );

      internal_draw_text(lpszString, nCount, rect, 0, &cairo_show_text);

      return true;

#endif

      return true;

   }


   bool graphics::line_to(LPCPOINTD ppt)
   {

      synch_lock ml(cairo_mutex());

      cairo_move_to(m_pdc, m_pt.x, m_pt.y);

      cairo_line_to(m_pdc, ppt->x, ppt->y);

      draw();

      m_pt = *ppt;

      return true;

   }


   bool graphics::draw_line(LPCPOINT ppt1, LPCPOINT ppt2, ::draw2d::pen * ppen)
   {

      synch_lock ml(cairo_mutex());

      cairo_move_to(m_pdc, ppt1->x, ppt1->y);

      cairo_line_to(m_pdc, ppt2->x, ppt2->y);

      draw(ppen);

      m_pt = *ppt2;

      return true;

   }


   bool graphics::draw_line(LPCPOINTD ppt1, LPCPOINTD ppt2, ::draw2d::pen * ppen)
   {

      synch_lock ml(cairo_mutex());

      cairo_move_to(m_pdc, ppt1->x, ppt1->y);

      cairo_line_to(m_pdc, ppt2->x, ppt2->y);

      draw(ppen);

      m_pt = *ppt2;

      return true;

   }


   bool graphics::set_alpha_mode(::draw2d::e_alpha_mode ealphamode)
   {

      synch_lock ml(cairo_mutex());

      try
      {

         if (m_pdc == NULL)
         {

            return false;

         }

         if (ealphamode == ::draw2d::alpha_mode_blend)
         {

            cairo_set_operator(m_pdc, CAIRO_OPERATOR_OVER);

         }
         else if (ealphamode == ::draw2d::alpha_mode_set)
         {

            cairo_set_operator(m_pdc, CAIRO_OPERATOR_SOURCE);

         }

         ::draw2d::graphics::set_alpha_mode(ealphamode);

         return true;

      }
      catch (...)
      {

      }

      return false;

   }


   bool graphics::set_text_rendering_hint(::draw2d::e_text_rendering_hint etextrenderinghint)
   {

      return ::draw2d::graphics::set_text_rendering_hint(etextrenderinghint);

   }


   void * graphics::get_os_data() const
   {

      return (void *)m_pdc;

   }


   bool graphics::attach(void * pdata)
   {

      synch_lock ml(cairo_mutex());

      if (m_pdc != NULL)
      {

         cairo_destroy(m_pdc);

         m_pdc = NULL;

      }

      m_pdc = (cairo_t *)pdata;

      return true;

   }


   void cairo_image_surface_blur(cairo_surface_t* surface, double radius)
   {

      synch_lock ml(cairo_mutex());

      // Steve Hanov, 2009
      // Released into the public domain.

      // get width, height
      int32_t width = cairo_image_surface_get_width(surface);

      int32_t height = cairo_image_surface_get_height(surface);

      unsigned char* dst = (unsigned char*)malloc(width*height * 4);

      unsigned* precalc = (unsigned*)malloc(width*height * sizeof(unsigned));

      unsigned char* src = cairo_image_surface_get_data(surface);

      double mul = 1.f / ((radius * 2)*(radius * 2));

      int32_t channel;

      // The number of times to perform the averaging. According to wikipedia,
      // three iterations is good enough to pass for a gaussian.
      const int32_t MAX_ITERATIONS = 3;

      int32_t iteration;

      memcpy(dst, src, width*height * 4);

      for (iteration = 0; iteration < MAX_ITERATIONS; iteration++)
      {

         for (channel = 0; channel < 4; channel++)
         {

            int32_t x, y;

            // precomputation step.
            unsigned char* pix = src;

            unsigned* pre = precalc;

            pix += channel;

            for (y = 0; y < height; y++)
            {

               for (x = 0; x < width; x++)
               {

                  int32_t tot = pix[0];

                  if (x > 0) tot += pre[-1];

                  if (y > 0) tot += pre[-width];

                  if (x > 0 && y > 0) tot -= pre[-width - 1];

                  *pre++ = tot;

                  pix += 4;

               }

            }

            // blur step.
            pix = dst + (int32_t)radius * width * 4 + (int32_t)radius * 4 + channel;

            for (y = (int32_t)radius; y < height - radius; y++)
            {

               for (x = (int32_t)radius; x < width - radius; x++)
               {

                  int32_t l = (int32_t)(x < radius ? 0 : x - radius);

                  int32_t t = (int32_t)(y < radius ? 0 : y - radius);

                  int32_t r = (int32_t)(x + radius >= width ? width - 1 : x + radius);

                  int32_t b = (int32_t)(y + radius >= height ? height - 1 : y + radius);

                  int32_t tot = precalc[r + b*width] + precalc[l + t*width] -
                                precalc[l + b*width] - precalc[r + t*width];

                  *pix = (unsigned char)(tot*mul);

                  pix += 4;

               }

               pix += (int32_t)radius * 2 * 4;

            }

         }

         memcpy(src, dst, width*height * 4);

      }

      free(dst);

      free(precalc);

   }


   bool graphics::blur(bool bExpand, double dRadius, const RECT & lpcrect)
   {

      synch_lock ml(cairo_mutex());

      cairo_pattern_t * ppattern = cairo_get_source(m_pdc);

      if (ppattern == NULL)
      {

         return false;

      }

      cairo_surface_t * psurfaceSrc = NULL;

      cairo_pattern_get_surface(ppattern, &psurfaceSrc);

      /*

      cairo_surface_t * psurface = cairo_surface_create_for_rectangle(psurfaceSrc, lpcrect.left, lpcrect.top, width(lpcrect), height(lpcrect));

      cairo_image_surface_blur(psurface, dRadius);

      */

      return true;

   }


   double graphics::get_dpix()
   {

      return 72.0;

   }


   bool graphics::set(const ::draw2d::brush * pbrush, double x, double y)
   {

      synch_lock ml(cairo_mutex());

      if (pbrush->m_etype == ::draw2d::brush::type_radial_gradient_color)
      {

         cairo_pattern_t * ppattern = cairo_pattern_create_radial(pbrush->m_pt.x - x, pbrush->m_pt.y - y, 0, pbrush->m_pt2.x - x, pbrush->m_pt2.y - y, MAX(pbrush->m_size.cx, pbrush->m_size.cy));

         cairo_pattern_add_color_stop_rgba(ppattern, 0., argb_get_r_value(pbrush->m_cr1) / 255.0, argb_get_g_value(pbrush->m_cr1) / 255.0, argb_get_b_value(pbrush->m_cr1) / 255.0, argb_get_a_value(pbrush->m_cr1) / 255.0);

         cairo_pattern_add_color_stop_rgba(ppattern, 1., argb_get_r_value(pbrush->m_cr2) / 255.0, argb_get_g_value(pbrush->m_cr2) / 255.0, argb_get_b_value(pbrush->m_cr2) / 255.0, argb_get_a_value(pbrush->m_cr2) / 255.0);

         cairo_set_source(m_pdc, ppattern);

         cairo_pattern_destroy(ppattern);

      }
      else if (pbrush->m_etype == ::draw2d::brush::type_linear_gradient_point_color)
      {

         cairo_pattern_t * ppattern = cairo_pattern_create_linear(pbrush->m_pt1.x - x, pbrush->m_pt1.y - y, pbrush->m_pt2.x - x, pbrush->m_pt2.y - y);

         cairo_pattern_add_color_stop_rgba(ppattern, 0., argb_get_r_value(pbrush->m_cr1) / 255.0, argb_get_g_value(pbrush->m_cr1) / 255.0, argb_get_b_value(pbrush->m_cr1) / 255.0, argb_get_a_value(pbrush->m_cr1) / 255.0);

         cairo_pattern_add_color_stop_rgba(ppattern, 1., argb_get_r_value(pbrush->m_cr2) / 255.0, argb_get_g_value(pbrush->m_cr2) / 255.0, argb_get_b_value(pbrush->m_cr2) / 255.0, argb_get_a_value(pbrush->m_cr2) / 255.0);

         cairo_set_source(m_pdc, ppattern);

         cairo_pattern_destroy(ppattern);

      }
      else if (pbrush->m_etype == ::draw2d::brush::type_pattern)
      {

         cairo_surface_t * psurface = cairo_get_target((cairo_t *)pbrush->m_dib->get_graphics()->get_os_data());

         if (psurface == NULL)
            return false;

         cairo_pattern_t * ppattern = cairo_pattern_create_for_surface(psurface);

         if (ppattern == NULL)
            return false;

         cairo_set_source(m_pdc, ppattern);

         cairo_pattern_destroy(ppattern);

      }
      else
      {

         cairo_set_source_rgba(m_pdc, argb_get_r_value(pbrush->m_cr) / 255.0, argb_get_g_value(pbrush->m_cr) / 255.0, argb_get_b_value(pbrush->m_cr) / 255.0, argb_get_a_value(pbrush->m_cr) / 255.0);

      }

      return true;

   }


   bool graphics::set(const ::draw2d::pen * ppen)
   {

      synch_lock ml(cairo_mutex());

      if (ppen->m_etype == ::draw2d::pen::type_brush)
      {

         set(ppen->m_br);

      }
      else
      {

         cairo_set_source_rgba(m_pdc, argb_get_r_value(ppen->m_cr) / 255.0, argb_get_g_value(ppen->m_cr) / 255.0, argb_get_b_value(ppen->m_cr) / 255.0, argb_get_a_value(ppen->m_cr) / 255.0);

      }

      cairo_set_line_width(m_pdc, ppen->m_dWidth);

      return true;

   }


#if !defined(USE_PANGO)


   bool graphics::set(const ::draw2d::font * pfontParam)
   {

      synch_lock ml(cairo_mutex());

      //cairo_select_font_face(m_pdc, pfont->m_strFontFamilyName, pfont->m_bItalic ? CAIRO_FONT_SLANT_ITALIC : CAIRO_FONT_SLANT_NORMAL, pfont->m_iFontWeight > 650 ? CAIRO_FONT_WEIGHT_BOLD : CAIRO_FONT_WEIGHT_NORMAL);

      if (pfontParam == NULL)
      {

         return false;

      }

      ::draw2d_cairo::font * pfont = dynamic_cast <::draw2d_cairo::font *> ((::draw2d::font *) pfontParam);

      if (pfont == NULL)
      {

         return false;

      }
      //
      ///*if(pfont->m_ft != NULL)
      //{
      //
      // return true;
      //
      //}
      //
      //      //synch_lock sl(&user_mutex());
      //
      //      pfont->destroy();
      //
      ////      int status;
      //
      //      int iError = 0;
      //
      //      string strPath;
      //
      //
      int iError;

      string  strPath = get_font_path(pfont->m_strFontFamilyName);

      if (g_pmapFontError->Lookup(strPath, iError))
      {

         g_pmapFontFace->Lookup(strPath, pfont->m_ft);

      }
      else
      {

         pfont->m_ft = NULL;

         iError = FT_New_Face((FT_Library)System.ftlibrary(), strPath, 0, &pfont->m_ft);

         if (iError == 0)
         {

            iError = FT_Select_Charmap(pfont->m_ft, /* target face object */ FT_ENCODING_UNICODE); /* encoding */

         }

         g_pmapFontError->set_at(strPath, iError);

         g_pmapFontFace->set_at(strPath, pfont->m_ft);

      }

      if (iError != 0 || pfont->m_ft == NULL)
      {

         string strFont = pfont->m_strFontFamilyName;

         cairo_select_font_face(m_pdc, strFont, pfont->m_bItalic ? CAIRO_FONT_SLANT_ITALIC : CAIRO_FONT_SLANT_NORMAL, pfont->m_iFontWeight > 650 ? CAIRO_FONT_WEIGHT_BOLD : CAIRO_FONT_WEIGHT_NORMAL);

      }
      else
      {

         if (!g_pmapCairoFontFace->Lookup(strPath, pfont->m_pface))
         {

            pfont->m_pface = cairo_ft_font_face_create_for_ft_face(pfont->m_ft, 0);

            g_pmapCairoFontFace->set_at(strPath, pfont->m_pface);

            cairo_font_face_reference(pfont->m_pface);

         }

         //         cairo_font_options_t * poptions = cairo_font_options_create ();
         //
         //         cairo_matrix_t m;
         //
         //         cairo_matrix_init_identity(&m);
         //
         //         cairo_matrix_t m2;
         //
         //         cairo_matrix_init_identity(&m2);
         //
         //         pfont->m_pfont = cairo_scaled_font_create(pfont->m_pface, &m, &m2, poptions);
         //
         //         cairo_set_scaled_font(m_pdc, pfont->m_pfont);
         //
         //         cairo_font_options_destroy(poptions);
         //         */
         //
         cairo_set_font_face(m_pdc, pfont->m_pface);

      }

      if (pfont->m_eunitFontSize == ::draw2d::unit_pixel)
      {

         cairo_set_font_size(m_pdc, pfont->m_dFontSize);

      }
      else
      {

         cairo_set_font_size(m_pdc, pfont->m_dFontSize * 96.0 / 72.0);

      }

      return true;

   }


#endif


   bool graphics::fill_and_draw()
   {

      synch_lock ml(cairo_mutex());

      bool bPen = m_sppen->m_etype != ::draw2d::pen::type_null;

      cairo_keep keep(m_pdc);

      if (m_spbrush->m_etype != ::draw2d::brush::type_null)
      {

         set(m_spbrush);

         set_alpha_mode(m_ealphamode);

         if (bPen)
         {

            cairo_fill_preserve(m_pdc);

         }
         else
         {

            cairo_fill(m_pdc);

         }

      }

      keep.pulse();

      if (bPen)
      {

         set(m_sppen);

         set_alpha_mode(m_ealphamode);

         cairo_stroke(m_pdc);


      }

      return true;

   }


   bool graphics::fill(::draw2d::brush * pbrush, double xOrg, double yOrg)
   {

      synch_lock ml(cairo_mutex());

      if (pbrush == NULL || pbrush->m_etype == ::draw2d::brush::type_null)
      {

         return true;

      }

      cairo_keep keep(m_pdc);

      if (m_spregion.is_set() && !m_spregion.cast < region >()->is_simple_positive_region())
      {

         cairo_set_antialias(m_pdc, CAIRO_ANTIALIAS_BEST);

         cairo_push_group(m_pdc);

         set(pbrush, xOrg, yOrg);

         cairo_fill(m_pdc);

         cairo_pop_group_to_source(m_pdc);

         m_spregion.cast < region >()->mask(m_pdc);

      }
      else
      {

         set(pbrush, xOrg, yOrg);

         cairo_fill(m_pdc);

      }

      return true;

   }


   bool graphics::draw(::draw2d::pen * ppen)
   {

      synch_lock ml(cairo_mutex());

      if (ppen == NULL || ppen->m_etype == ::draw2d::pen::type_null)
      {

         return true;

      }

      cairo_keep keep(m_pdc);

      set(ppen);

      cairo_stroke(m_pdc);

      return true;

   }


   bool graphics::set(const ::draw2d::path * ppathParam)
   {

      if(ppathParam == NULL)
      {

         return false;

      }

      ::draw2d_cairo::path * ppath = dynamic_cast <::draw2d_cairo::path *> ((::draw2d::path *) ppathParam);

      if(ppath == NULL)
      {

         return false;

      }

      synch_lock ml(cairo_mutex());

      cairo_keep keep(m_pdc);

      cairo_new_sub_path(m_pdc);

      if (ppath->m_bFill)
      {

         if (ppath->m_efillmode == ::draw2d::fill_mode_alternate)
         {

            cairo_set_fill_rule(m_pdc, CAIRO_FILL_RULE_EVEN_ODD);

         }
         else
         {

            cairo_set_fill_rule(m_pdc, CAIRO_FILL_RULE_WINDING);

         }

      }

      for (int32_t i = 0; i < ppath->m_elementa.get_count(); i++)
      {

         set(ppath->m_elementa(i));

      }

      return true;

   }


   bool graphics::set(const ::draw2d_cairo::path::element & e)
   {

      synch_lock ml(cairo_mutex());

      switch (e.m_etype)
      {
      case ::draw2d::path::element::type_arc:

         set(e.u.m_arc);

         break;

      case ::draw2d::path::element::type_line:

         set(e.u.m_line);

         break;

      case ::draw2d::path::element::type_move:

         set(e.u.m_move);

         break;

      case ::draw2d::path::element::type_rect:

         set(e.u.m_rect);

         break;

      case ::draw2d::path::element::type_end:
      {

         if (e.u.m_end.m_bClose)
         {

            cairo_close_path(m_pdc);

         }

      }

      break;

      case ::draw2d::path::element::type_string:
      {

         set(e.m_stringpath);

      }
      break;

      default:

         _throw(simple_exception(get_app(), "unexpected simple os graphics element type"));

      }

      return false;

   }


   bool graphics::set(const ::draw2d_cairo::path::arc & a)
   {

      if (a.m_dRadiusX <= 0.0000001)
      {

         return 0;

      }

      if (a.m_dRadiusY <= 0.0000001)
      {

         return 0;

      }

      synch_lock ml(cairo_mutex());

      cairo_keep keep(m_pdc);

      cairo_translate(m_pdc, a.m_xCenter, a.m_yCenter);

      cairo_scale(m_pdc, 1.0, a.m_dRadiusY / a.m_dRadiusX);

      cairo_arc(m_pdc, 0.0, 0.0, a.m_dRadiusX, a.m_dAngle1, a.m_dAngle2);

      return true;

   }


   bool graphics::set(const ::draw2d_cairo::path::line & l)
   {

      synch_lock ml(cairo_mutex());

      if (!cairo_has_current_point(m_pdc))
      {

         cairo_move_to(m_pdc, l.m_x + 0.5, l.m_y + 0.5);

      }
      else
      {

         cairo_line_to(m_pdc, l.m_x + 0.5, l.m_y + 0.5);

      }

      return true;

   }


   bool graphics::set(const ::draw2d_cairo::path::rect & r)
   {

      synch_lock ml(cairo_mutex());

      cairo_rectangle(m_pdc, r.m_x, r.m_y, r.m_cx, r.m_cy);

      return true;

   }


   bool graphics::set(const ::draw2d_cairo::path::string_path & stringpath)
   {

      synch_lock ml(cairo_mutex());

      ::rectd r = ::rectd(pointd(stringpath.m_x, stringpath.m_y), sized(65535.0, 65535.0));

#if defined(USE_PANGO)

      internal_draw_text_pango(stringpath.m_strText, stringpath.m_strText.get_length(), r, 0, &pango_cairo_layout_path);

#else

      ::RECT rect;

      ::copy(&rect, &r);

      internal_draw_text(stringpath.m_strText, stringpath.m_strText.get_length(), rect, 0, &cairo_text_path);

#endif

      cairo_status_t status = cairo_status(m_pdc);

      if(status != CAIRO_STATUS_SUCCESS)
      {

         const char * pszStatus = cairo_status_to_string(status);

         TRACE("cairo error : graphics::set(string_path) %d %s", status, pszStatus);

      }

      return true;

   }


   bool graphics::set(const ::draw2d_cairo::path::move & p)
   {

      synch_lock ml(cairo_mutex());

      cairo_move_to(m_pdc, p.m_x + 0.5, p.m_y + 0.5);

      return true;

   }


   bool graphics::fill(double xOrg, double yOrg)
   {

      return fill(m_spbrush, xOrg, yOrg);

   }


   bool graphics::draw()
   {

      return draw(m_sppen);

   }


   void * graphics::detach()
   {

      synch_lock ml(cairo_mutex());

      cairo_t * p = m_pdc;

      m_pdc = NULL;

      return p;

   }


   bool graphics::set_os_color(COLORREF cr)
   {

      synch_lock ml(cairo_mutex());

      cairo_set_source_rgba(m_pdc, argb_get_r_value(cr) / 255.0, argb_get_g_value(cr) / 255.0, argb_get_b_value(cr) / 255.0, argb_get_a_value(cr) / 255.0);

      return true;

   }


   bool graphics::flush()
   {

      synch_lock ml(cairo_mutex());

      cairo_pattern_t * ppattern = cairo_get_source(m_pdc);

      if (ppattern == NULL)
      {

         return true;

      }

      cairo_surface_t * psurface = NULL;

      cairo_pattern_get_surface(ppattern, &psurface);

      if (psurface == NULL)
      {

         return true;

      }

      cairo_surface_flush(psurface);

      return true;

   }


#ifdef WINDOWS


   bool graphics::Attach(HDC hdc)
   {

      synch_lock ml(cairo_mutex());

      if (m_hdcAttach != NULL)
      {

         Detach();

      }

      m_psurfaceAttach = cairo_win32_surface_create(hdc);

      if (m_psurfaceAttach == NULL)
      {

         return false;

      }

      m_pdc = cairo_create(m_psurfaceAttach);

      if (m_pdc == NULL)
      {

         cairo_surface_destroy(m_psurfaceAttach);

         return false;

      }

      m_hdcAttach = hdc;

      return false;

   }

   HDC graphics::Detach()
   {

      synch_lock ml(cairo_mutex());

      if (m_hdcAttach == NULL)
      {

         return NULL;

      }

      HDC hdc = m_hdcAttach;

      cairo_surface_destroy(m_psurfaceAttach);

      m_psurfaceAttach = NULL;

      return hdc;

   }


#endif // WINDOWS


#if defined(USE_PANGO)


   void graphics::enum_fonts(::draw2d::font::enum_item_array & itema)
   {

      synch_lock ml(cairo_mutex());

      PangoFontMap * pfontmap = pango_cairo_font_map_get_default();

      PangoFontFamily ** families;

      int n_families = 0;

      pango_font_map_list_families(pfontmap, &families, &n_families);

      printf("Total fonts: %d", n_families);

      sp(::draw2d::font::enum_item) item;

      for (int i = 0; i < n_families; i++)
      {

         item = canew(::draw2d::font::enum_item);

         PangoFontFamily * pfamily = families[i];

         item->m_strFile = pango_font_family_get_name(pfamily);

         item->m_strName = item->m_strFile;

         itema.add(item);

      }

      g_free(families);

   }


#else


   void graphics::enum_fonts(::draw2d::font::enum_item_array & itema)
   {

#if defined(LINUX)

      synch_lock ml(cairo_mutex());

      FcPattern *    pat;

      FcObjectSet *  os;

      FcFontSet *    fs;

      FcChar8 *      s;

      FcChar8 *      file;

      int            i;

      if (!g_fcResult)
      {

         g_fcResult = FcInit();

      }

      if (!g_fcConfig)
      {

         g_fcConfig = FcConfigGetCurrent();

         FcConfigSetRescanInterval(g_fcConfig, 30);

      }

      pat = FcPatternCreate();

      os = FcObjectSetBuild(FC_FAMILY, FC_STYLE, FC_FILE, NULL);

      fs = FcFontList(g_fcConfig, pat, os);

      printf("Total fonts: %d", fs->nfont);

      sp(::draw2d::font::enum_item) item;

      for (i = 0; fs && i < fs->nfont; i++)
      {

         item = canew(::draw2d::font::enum_item);

         FcPattern * font = fs->fonts[i];//FcFontSetFont(fs, i);

         //FcPatternPrint(font);

         s = FcNameUnparse(font);

         string str((const char *)s);

         int iFind = str.find(":");

         if (iFind > 0)
         {

            str = str.Left(iFind);

         }

         if (FcPatternGetString(font, FC_FILE, 0, &file) == FcResultMatch)
         {

            //printf("Filename: %s", file);

            item->m_strFile = (const char *)file;

         }
         else
         {

            item->m_strFile = str;

         }

         //printf("Font: %s\n", str.c_str());
         //printf("Font: %s\n", s);

         item->m_strName = str;

         item->m_ecs = ::draw2d::font::cs_default;

         itema.add(item);

         free(s);

      }

      if (fs != NULL)
      {

         FcFontSetDestroy(fs);

      }

#elif defined(WINDOWS)

      ::draw2d::wingdi_enum_fonts(itema, false, true, false);

#elif defined(ANDROID)

      synch_lock ml(cairo_mutex());

      sp(::draw2d::font::enum_item) item = canew(::draw2d::font::enum_item);

      item->m_strFile = "monospace";

      item->m_strName = "monospace";

      itema.add(item);

      item = canew(::draw2d::font::enum_item);

      item->m_strFile = "serif";

      item->m_strName = "serif";

      itema.add(item);

      item = canew(::draw2d::font::enum_item);

      item->m_strFile = "normal";

      item->m_strName = "normal";

      itema.add(item);

      ::file::patha patha;

      ::dir::ls(patha, "/system/fonts");

      ttf_util util(get_app());

      for (auto & path : patha)
      {

         item = canew(::draw2d::font::enum_item);

         item->m_strFile = path;

         item->m_strName = util.GetFontNameFromFile(path);

         if (item->m_strName.is_empty())
         {

            item->m_strName = path.title();

         }

         itema.add(item);


      }

#else

      _throw(not_implemented(get_app()));

#endif

   }


#endif


   string graphics::get_font_path(string str)
   {

#ifdef LINUX

      synch_lock ml(cairo_mutex());

      if (str.find("/") >= 0)
      {

         return str;

      }

      if (str == "TakaoPGothic")
      {

         output_debug_string("searching TakaoPGothic");

      }

      string strPath;

      if (!g_pmapFontPath->Lookup(str, strPath))
      {

         stringa straPath;

         stringa stra;

         ::draw2d::font::enum_item_array itema;

         enum_fonts(itema);

         if (str == "TakaoPGothic")
         {

            output_debug_string("searching TakaoPGothic");

         }

         int iFind = stra.find_first_ci(str);

         if (iFind >= 0)
         {

            strPath = straPath[iFind];

         }
         else
         {

            iFind = stra.find_first_begins_ci(str + " Regular");

            if (iFind >= 0)
            {

               strPath = straPath[iFind];

            }
            else
            {

               iFind = stra.find_first_begins_ci(str + ",");

               if (iFind >= 0)
               {

                  strPath = straPath[iFind];

               }
               else
               {

                  iFind = stra.find_first_begins_ci(str + " ");

                  if (iFind >= 0)
                  {

                     strPath = straPath[iFind];

                  }
                  else
                  {

                     strPath = str;

                  }


               }

            }

         }

         g_pmapFontPath->set_at(str, strPath);

      }

      return strPath;

#else

      return str;

#endif

   }


   bool graphics::_get(::draw2d::matrix & matrix)
   {

      synch_lock ml(cairo_mutex());

      cairo_matrix_t cairomatrix;

      cairo_get_matrix(m_pdc, &cairomatrix);

      copy(matrix, cairomatrix);

      return true;

   }


   bool graphics::_set(const ::draw2d::matrix & matrix)
   {

      synch_lock ml(cairo_mutex());

      cairo_matrix_t cairomatrix;

      copy(cairomatrix, matrix);

      cairo_set_matrix(m_pdc, &cairomatrix);

      return true;

   }


} // namespace draw2d_cairo



