#include "framework.h"



namespace draw2d
{


   font::enum_item::enum_item()
   {

   }


   font::enum_item::enum_item(string strName) :
      m_strFile(strName),
      m_strName(strName)
   {

   }


   font::enum_item::enum_item(string strFile, string strName) :
      m_strFile(strFile),
      m_strName(strName)
   {

   }


   font::enum_item::~enum_item()
   {

   }


   font::font()
   {

      m_strFontFamilyName  = FONT_SERIF;
      m_dFontSize          = 17.0;
      m_dFontWidth         = 1.0;
      m_eunitFontSize      = ::draw2d::unit_point;
      m_iFontWeight        = 400;
      m_bItalic            = false;
      m_bUnderline         = false;
      m_bStrikeout         = false;
      m_etextrendering     = text_rendering_undefined;
      m_echarset           = char_set_none;

   }


   font::font(const font & font)
   {

      operator = (font);

   }


   font::~font()
   {

   }


#ifdef DEBUG


   void font::dump(dump_context & dumpcontext) const
   {

      UNREFERENCED_PARAMETER(dumpcontext);

      ::exception::throw_interface_only(get_app());

   }


#endif


   bool font::create_pixel_font(const char * lpszFacename, double dSize, int32_t iWeight, bool bItalic, bool bUnderline, bool bStrikeOut, double dWidth)
   {

      synch_lock sl(m_pmutex);

#ifdef WINDOWS

      if(stricmp(lpszFacename, FONT_SANS) == 0)
      {

         m_strFontFamilyName = FONT_SANS;

      }
      else
      {

         m_strFontFamilyName     = lpszFacename;

      }

#else

      m_strFontFamilyName     = lpszFacename;

#endif

      m_dFontSize             = dSize;
      m_dFontWidth            = 1.0;
      m_eunitFontSize         = ::draw2d::unit_pixel;
      m_iFontWeight           = iWeight;
      m_bItalic               = bItalic;
      m_bUnderline            = bUnderline;
      m_bStrikeout            = bStrikeOut;
      m_bUpdated              = false;

      return true;

   }


   bool font::create_point_font(const char * lpszFacename, double dSize, int32_t iWeight, bool bItalic, bool bUnderline, bool bStrikeOut, double dWidth)
   {

      synch_lock sl(m_pmutex);

      m_strFontFamilyName     = lpszFacename;
#ifdef MACOS
      m_dFontSize             = dSize * 1.2;
#elif defined(VSNORD)
      m_dFontSize             = dSize * 1.6;
#else
      m_dFontSize             = dSize;
#endif
      m_dFontWidth            = 1.0;
      m_eunitFontSize         = ::draw2d::unit_point;
      m_iFontWeight           = iWeight;
      m_bItalic               = bItalic;
      m_bUnderline            = bUnderline;
      m_bStrikeout            = bStrikeOut;
      m_bUpdated              = false;

      return true;

   }


   font & font::operator = (const font & fontSrc)
   {

      synch_lock sl(m_pmutex);

      if(this != &fontSrc)
      {

         m_strFontFamilyName     = fontSrc.m_strFontFamilyName;
         m_dFontSize             = fontSrc.m_dFontSize;
         m_dFontWidth            = fontSrc.m_dFontWidth;
         m_eunitFontSize         = fontSrc.m_eunitFontSize;
         m_iFontWeight           = fontSrc.m_iFontWeight;
         m_bItalic               = fontSrc.m_bItalic;
         m_bUnderline            = fontSrc.m_bUnderline;
         m_bStrikeout            = fontSrc.m_bStrikeout;
         m_echarseta             = fontSrc.m_echarseta;
         m_echarset              = fontSrc.m_echarset;
         m_bUpdated              = false;

      }

      return *this;

   }


   void font::set_family_name(const char * pszFamilyName)
   {

      synch_lock sl(m_pmutex);

      m_strFontFamilyName  = pszFamilyName;
      m_bUpdated           = false;


   }


   void font::set_size(double dSize, e_unit eunit)
   {

      synch_lock sl(m_pmutex);

      m_dFontSize       = dSize;
      m_eunitFontSize   = eunit;
      m_bUpdated        = false;

   }


   void font::set_bold(bool bBold)
   {

      synch_lock sl(m_pmutex);

      if(bBold)
      {

         m_iFontWeight  = FW_BOLD;

      }
      else
      {

         m_iFontWeight  = FW_NORMAL;

      }

      m_bUpdated     = false;

   }


   void font::set_italic(bool bItalic)
   {

      synch_lock sl(m_pmutex);

      m_bItalic      = bItalic;
      m_bUpdated     = false;

   }


   void font::set_underline(bool bUnderline)
   {

      synch_lock sl(m_pmutex);

      m_bUnderline   = bUnderline;
      m_bUpdated     = false;

   }


   void font::set_strikeout(bool bStrikeout)
   {

      synch_lock sl(m_pmutex);

      m_bStrikeout   = bStrikeout;
      m_bUpdated     = false;

   }


   font::e_char_set font::get_char_set(graphics * pgraphics)
   {

      if (m_echarset == char_set_none)
      {

         m_echarset = calc_char_set(pgraphics);

      }

      return m_echarset;

   }


   font::e_char_set font::calc_char_set(graphics * pgraphics)
   {

      if (m_echarseta.get_count() == 1)
      {

         return m_echarseta[0];

      }

      return char_set_default;

   }


   string font::get_sample_text(e_char_set echarset)
   {

      if (echarset == char_set_chinesebig5)
      {

         return unitext("示例文本");

      }
      else if (echarset == char_set_gb2312)
      {

         return unitext("示例文本");

      }
      else if (echarset == char_set_shiftjis)
      {

         return unitext("サンプルテキスト");

      }
      else if (echarset == char_set_hebrew)
      {

         return unitext("טקסט לדוגמה");

      }
      else if (echarset == char_set_arabic)
      {

         return unitext("نص بسيط");

      }
      else if (echarset == char_set_greek)
      {

         return unitext("Δείγμα κειμένου");

      }
      else if (echarset == char_set_turkish)
      {

         return unitext("Örnek yazı");

      }
      else if (echarset == char_set_vietnamese)
      {

         return unitext("văn bản mẫu");

      }
      else if (echarset == char_set_thai)
      {

         return unitext("ตัวอย่างข้อความ");

      }
      else if (echarset == char_set_easteurope)
      {

         return unitext("Sample Text");

      }
      else if (echarset == char_set_russian)
      {

         return unitext("Образец текста");

      }
      else if (echarset == char_set_johab)
      {

         return unitext("샘플 텍스트");

      }
      else if (echarset == char_set_hangul)
      {

         return unitext("샘플 텍스트");

      }

      return "";

   }


   string font::get_sample_text(::draw2d::graphics * pgraphics)
   {

      auto ecs = get_char_set(pgraphics);

      string str = get_sample_text(ecs);

      if (str.has_char())
      {

         return str;

      }

      return m_strFontFamilyName;

   }


   double font::get_pixel_font_height(::draw2d::graphics * pgraphics)
   {

      if (m_eunitFontSize == unit_point)
      {

         return m_dFontSize * pgraphics->get_dpiy() / 72.0;

      }

      return m_dFontSize;

   }


} // namespace draw2d


