#pragma once


namespace visual
{


   class CLASS_DECL_AURA text_box
   {
   public:


      ::draw2d::dib_sp     m_dib;
      ::draw2d::font_sp    m_font;
      rect                 m_rect;
      bool                 m_bOk;
      size                 m_size;


      text_box();
      ~text_box();


      void update(font_list * pdata, int iBox, string strText);


   };


} // namespace visual



