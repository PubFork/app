#include "framework.h"

CLASS_DECL_AURA HFONT wingdi_CreatePointFont(int nPointSize, const char * lpszFaceName, HDC hdc, LOGFONTW* lpLogFont);

namespace win32
{


   font::font()
   {

      m_hfont = NULL;

   }
   font::~font()
   {
      destroy();

   }

   bool font::create_point_font(int iPoint, const char * pszFontFamily, int iWeight)
   {

      destroy();

      HDC hdc = ::CreateCompatibleDC(NULL);

      if (hdc == NULL)
      {

         return false;

      }

      LOGFONTW lf;
      ZERO(lf);
      lf.lfWeight = iWeight;

      m_hfont = wingdi_CreatePointFont(iPoint, pszFontFamily, hdc, &lf);

      ::DeleteDC(hdc);

      return m_hfont != NULL;

   }


   void font::destroy()
   {

      if (m_hfont == NULL)
      {

         return;

      }

      ::DeleteObject(m_hfont);

      m_hfont = NULL;

   }



} //  namespace os


