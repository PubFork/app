#pragma once


namespace draw2d
{



   class CLASS_DECL_AURA text_metric
   {
   public:


      LONG        tmHeight;
      LONG        tmAscent;
      LONG        tmDescent;
      LONG        tmInternalLeading;
      LONG        tmExternalLeading;
      LONG        tmAveCharWidth;
      LONG        tmMaxCharWidth;
      LONG        tmWeight;
      LONG        tmOverhang;
      LONG        tmDigitizedAspectX;
      LONG        tmDigitizedAspectY;
      WCHAR       tmFirstChar;
      WCHAR       tmLastChar;
      WCHAR       tmDefaultChar;
      WCHAR       tmBreakChar;
      BYTE        tmItalic;
      BYTE        tmUnderlined;
      BYTE        tmStruckOut;
      BYTE        tmPitchAndFamily;
      BYTE        tmCharSet;

   };

   class CLASS_DECL_AURA font :
      virtual public ::draw2d::object
   {
   public:


      enum e_char_set
      {

         char_set_none,
         char_set_ansi,
         char_set_default,
         char_set_symbol,
         char_set_shiftjis,
         char_set_hangeul,
         char_set_hangul,
         char_set_gb2312,
         char_set_chinesebig5,
         char_set_johab,
         char_set_hebrew,
         char_set_arabic,
         char_set_greek,
         char_set_turkish,
         char_set_vietnamese,
         char_set_thai,
         char_set_easteurope,
         char_set_russian,
         char_set_mac,
         char_set_baltic,
         char_set_count

      };


      typedef comparable_array < e_char_set > char_set_array;


      class CLASS_DECL_AURA enum_item :
         virtual public object
      {
      public:


         string                  m_strFile;
         string                  m_strName;
         char_set_array          m_echarseta;


         enum_item();
         enum_item(string strName);
         enum_item(string strFile, string strName);
         virtual ~enum_item();

         bool operator < (const enum_item & item) const
         {

            int iCompare = m_strName.compare(item.m_strName);

            if (iCompare < 0)
               return true;

            if (iCompare > 0)
               return false;

            //iCompare = ((int)m_echarset) - ((int) item.m_echarset);

            //if (iCompare < 0)
            // return true;

            //if (iCompare > 0)
            // return false;

            return m_strFile.compare(item.m_strFile);

         }

         bool operator == (const enum_item & item) const
         {

            return m_strFile == item.m_strFile
                   && m_strName == item.m_strName;
            //                   && m_echarset == item.m_echarset;

         }

         bool operator != (const enum_item & item) const { return !this->operator==(item);  }

      };


      using enum_item_array = spa(enum_item);


      string                  m_strFontFamilyName;
      double                  m_dFontSize;
      double                  m_dFontWidth;
      e_unit                  m_eunitFontSize;
      int32_t                 m_iFontWeight;
      bool                    m_bItalic;
      bool                    m_bUnderline;
      bool                    m_bStrikeout;
      char_set_array          m_echarseta;
      e_char_set              m_echarset;
      e_text_rendering_hint_hint   m_etextrenderinghint;


      font();
      font(const font & font);
      virtual ~font();

#ifdef DEBUG

      virtual void dump(dump_context & dumpcontext) const;

#endif

      virtual bool create_pixel_font(
      const char * lpszFacename,
      double dSize,
      int32_t iWeight = 400,
      bool bItalic = false,
      bool bUnderline = false,
      bool bStrikeOut = false,
      double dWidth = 1.0);

      virtual bool create_point_font(
      const char * lpszFacename,
      double dSize,
      int32_t iWeight = 400,
      bool bItalic = false,
      bool bUnderline = false,
      bool bStrikeOut = false,
      double dWidth = 1.0);


      //    int32_t nEscapement
      //    int32_t nOrientation
      //    BYTE nCharSet
      //    BYTE nOutPrecision
      //    BYTE nClipPrecision
      //    BYTE nQuality
      //    BYTE nPitchAndFamily

      font & operator = (const font & font);

      virtual void set_family_name(const char * pszFamilyName);
      virtual void set_size(double dSize, e_unit = unit_point);
      virtual void set_bold(bool bBold = true);
      virtual void set_italic(bool bItalic = true);
      virtual void set_underline(bool bUnderline = true);
      virtual void set_strikeout(bool bStrikeout = true);

      virtual e_char_set calc_char_set(::draw2d::graphics * pgraphics);
      virtual e_char_set get_char_set(::draw2d::graphics * pgraphics);
      virtual string get_sample_text(::draw2d::graphics * pgraphics);

      static string get_sample_text(e_char_set echarsset);

      virtual double get_pixel_font_height(::draw2d::graphics * pgraphics);

   };


   typedef smart_pointer < font > font_sp;

#ifdef WINDOWS

   CLASS_DECL_AURA void wingdi_enum_fonts(::draw2d::font::enum_item_array & itema, bool bRaster, bool bTrueType, bool bOther);
   CLASS_DECL_AURA font::e_char_set wingdi_get_cs(int iCharSet);

#endif


} // namespace draw2d






