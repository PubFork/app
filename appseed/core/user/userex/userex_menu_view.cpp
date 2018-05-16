#include "framework.h"


menu_view::menu_view(::aura::application * papp) :
   object(papp),
   ::user::interaction(papp)
{
   m_pcallback = NULL;
}


void menu_view::on_update(::user::impact * pSender, LPARAM lHint, object* phint)
{
   ::user::form_view::on_update(pSender, lHint, phint);
}


void menu_view::on_control_event(::user::control_event * pevent)
{

   Application.on_control_event(pevent);

   if(pevent->m_bRet)
   {

      return;

   }

   if(m_pcallback != NULL)
   {

      m_pcallback->on_control_event(pevent);

   }

   if(GetParent() != NULL)
   {

      GetParent()->on_control_event(pevent);

      if(pevent->m_bRet)
      {

         return;

      }

   }

}


void menu_view::install_message_routing(::message::sender * pinterface)
{
   ::user::form::install_message_routing(pinterface);
   IGUI_MSG_LINK(WM_CREATE, pinterface, this, &menu_view::_001OnCreate);
//   //IGUI_MSG_LINK(WM_TIMER, pinterface, this, &menu_view::_001OnTimer);
   IGUI_MSG_LINK(WM_USER + 123, pinterface, this, &menu_view::_001OnUser123);

}


void menu_view::_001OnCreate(::message::message * pobj)
{
   pobj->previous();
}


void menu_view::_001OnTimer(::timer * ptimer)
{

   ::user::form_view::_001OnTimer(ptimer);;

   if(m_pcallback != NULL)
   {

      ::user::control_event ev;

      ev.m_eevent = ::user::event_timer;

      ev.m_uiEvent = ptimer->m_nIDEvent;

      ev.m_puie = this;

      Application.on_control_event(&ev);

      if(ev.m_bRet)
      {

         return;

      }

      m_pcallback->on_control_event(&ev);

   }

   if(ptimer->m_nIDEvent == 24)
   {

      KillTimer(24);

      GetTopLevelFrame()->EndModalLoop(IDOK);

   }

}


void menu_view::_001OnUser123(::message::message * pobj)
{
   SCAST_PTR(::message::base, pbase, pobj);
   if(pbase->m_wparam == 0x80000001)
   {
      GetTopLevel()->EndModalLoop(IDOK);
      return;
   }
   if(m_pcallback != NULL)
   {
      m_pcallback->OnUser123(pbase->m_wparam, pbase->m_lparam);
   }
}