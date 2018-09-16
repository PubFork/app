#pragma once


#if defined(USE_PANGO)

#include <pango/pangocairo.h>

#endif


namespace draw2d_cairo
{


   class CLASS_DECL_DRAW2D_CAIRO font :
      virtual public ::draw2d::font
   {
   public:

#if defined(USE_PANGO)

      // this structure stores a description of the style of font you'd most like
      PangoFontDescription *        m_pdesc;

#else

      FT_Face                    m_ft;
      cairo_font_face_t *        m_pface;
      cairo_user_data_key_t      m_keyDone;
      cairo_scaled_font_t *      m_pfont;

#endif



      font(::aura::application * papp);
      virtual ~font();


      virtual bool destroy();


      virtual void * get_os_data() const;

      virtual void dump(dump_context & dumpcontext) const;


      virtual ::draw2d::font::e_char_set calc_char_set(::draw2d::graphics * pgraphics) override;

   };


} // namespace draw2d_cairo



