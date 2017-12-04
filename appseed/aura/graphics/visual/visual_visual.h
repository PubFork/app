#pragma once


namespace visual
{


   class CLASS_DECL_AURA visual  :
      virtual public ::aura::department
   {
   public:
      
      
      map < int32_t, int32_t, sp(memory) > m_alpha_spread__24CC_filterMap;
      map < int32_t, int32_t, sp(memory) > m_alpha_spread__32CC_filterMap;


      map < e_cursor, e_cursor, cursor *, cursor * >     m_cursormap;
      class ::visual::api *                              m_pvisualapi;
      class font_department *                            m_pfontdepartment;



      visual(::aura::application * papp);
      virtual ~visual();


      virtual void construct(::aura::application * papp);

      virtual bool process_init() override;
      
      virtual bool init() override;
      virtual bool init1() override;

      virtual void term() override;


      virtual class api & api();
            


      class font_department & fonts();
      cursor * set_system_default_cursor(e_cursor ecursor);
      cursor * set_cursor_file(e_cursor ecursor,const ::file::path & psz, bool bFromCache = true);
      ::count set_cursor_set_from_matter(const ::file::path & pszMatter);
      ::count set_cursor_set_from_dir(const ::file::path & pszDir, bool bFromCache = true);
      ::count set_cursor_set_system_default();
      cursor * get_cursor(e_cursor ecursor);

      virtual void term_instance() override;

      virtual bool embossed_text_out(
         ::draw2d::graphics * pgraphics, 
         LPCRECT lpcrect, 
         string strText, 
         ::visual::fastblur & dib2,
         ::draw2d::font * pfont, 
         int iDrawTextFlags,
         COLORREF crText,
         COLORREF crGlow, 
         int iSpreadRadius,
         int iBlurRadius,
         int iBlur, 
         bool bUpdate,
         double dAlpha = 1.0);


      template < typename PRED >
      bool emboss_pred(
         ::draw2d::graphics * pgraphics,
         LPCRECT lpcrect,
         PRED pred,
         ::visual::fastblur & dib2,
         COLORREF crGlow,
         int iSpreadRadius,
         int iBlurRadius,
         int iBlur,
         bool bUpdate,
         double dAlpha = 1.0);
      
      virtual void alpha_spread__24CC(LPBYTE lpbDest, int32_t xDest, int32_t yDest, int32_t wDest, int32_t cx, int32_t cy, LPBYTE lpbSrc, int32_t ySrc, int32_t xSrc, int32_t wSrc, BYTE bMin, int32_t iRadius);
      virtual bool channel_spread__32CC(::draw2d::dib * pdibDst, ::draw2d::dib * pdibSrc, int32_t iChannel, int32_t iRadius, COLORREF crSpreadSetColor);

   };


} // namespace visual


