#include "framework.h"


namespace user
{


   simple_view::simple_view(::aura::application * papp) :
      object(papp)
   {

   }

   simple_view::~simple_view()
   {
   }


   void simple_view::install_message_routing(::message::sender * psender)
   {

      ::user::impact::install_message_routing(psender);

   }


   void simple_view::assert_valid() const
   {

      ::user::impact::assert_valid();

   }


   void simple_view::dump(dump_context & dumpcontext) const
   {

      ::user::impact::dump(dumpcontext);

   }


   void simple_view::on_update(::user::impact * pSender, LPARAM lHint, object* phint)
   {

      ::user::impact::on_update(pSender, lHint, phint);

   }


   void simple_view::_001OnDraw(::draw2d::graphics * pgraphics)
   {

      for (auto & text : m_texta)
      {

         pgraphics->selectFont(text.m_font);

         pgraphics->set_text_color(text.m_color.get_rgba());

         pgraphics->set_alpha_mode(::draw2d::alpha_mode_blend);

         pgraphics->text_out(text.m_point.x, text.m_point.y, text.m_strText);

      }


   }


} // namespace user