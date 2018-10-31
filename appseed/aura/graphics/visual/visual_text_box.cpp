#include "framework.h"


namespace visual
{


   text_box::text_box()
   {

      m_bOk = false;

   }


   text_box::~text_box()
   {

   }


   void text_box::update(font_list * plist, int iBox, string strText)
   {

      m_dib->create(m_size);

      m_dib->get_graphics()->set_alpha_mode(::draw2d::alpha_mode_set);

      m_dib->get_graphics()->fill_solid_rect(rect(m_size), plist->m_dwaBg[iBox]);

      m_dib->get_graphics()->set_alpha_mode(::draw2d::alpha_mode_blend);

      m_dib->get_graphics()->selectFont(m_font);

      m_dib->get_graphics()->set_text_color(plist->m_dwaFg[iBox]);

      m_dib->get_graphics()->text_out(plist->m_rectMargin.left, plist->m_rectMargin.top, strText);

      m_bOk = true;

   }


} // namespace visual



