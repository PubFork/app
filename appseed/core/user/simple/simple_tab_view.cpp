#include "framework.h"


simple_tab_view::simple_tab_view(::aura::application * papp) :
   object(papp),
   ::user::interaction(papp), 
   ::user::tab(papp),
   place_holder_container(papp)
{
}


simple_tab_view::~simple_tab_view()
{
}


// simple_tab_view diagnostics


void simple_tab_view::assert_valid() const
{
   ::user::impact::assert_valid();
}


void simple_tab_view::dump(dump_context & dumpcontext) const
{
   ::user::impact::dump(dumpcontext);
}


void simple_tab_view::on_layout()
{
   ::user::tab::on_layout();
}








bool simple_tab_view::GetClientRect(LPRECT lprect)
{
   
   if(!::user::impact::GetClientRect(lprect))
   {

      return false;

   }

   return true;

}





void simple_tab_view::_001OnCreate(::message::message * pobj)
{

   SCAST_PTR(::message::create, pcreate, pobj);

   if(pcreate->previous())
      return;
   
   if(!::user::control::create_window(null_rect(), this, 1))
   {
      pcreate->set_lresult(-1);
      return;
   }

}


void simple_tab_view::_001OnDraw(::draw2d::graphics * pgraphics)
{

   ::user::tab::_001OnDraw(pgraphics);

}

void simple_tab_view::install_message_routing(::message::sender * pinterface)
{
   ::user::impact::install_message_routing(pinterface);
   ::user::tab::install_message_routing(pinterface);
}


void simple_tab_view::_001OnLButtonUp(::message::message * pobj)
{
   SCAST_PTR(::message::mouse, pmouse, pobj);
   ::user::tab::_001OnLButtonUp(pobj);
   if(pmouse->m_bRet)
      return;
   if(pmouse->m_bRet)
      return;
}

void simple_tab_view::_001OnMouseMove(::message::message * pobj)
{
   SCAST_PTR(::message::mouse, pmouse, pobj);
   ::user::tab::_001OnMouseMove(pobj);
   if(pmouse->m_bRet)
      return;
   if(pmouse->m_bRet)
      return;
}

void simple_tab_view::_001OnMouseLeave(::message::message * pobj)
{
   SCAST_PTR(::message::mouse, pmouse, pobj);
   ::user::tab::_001OnMouseLeave(pobj);
   if(pmouse->m_bRet)
      return;
   if(pmouse->m_bRet)
      return;
}
