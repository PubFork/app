#include "framework.h"


namespace userex
{


   top_edit_view::top_edit_view(::aura::application * papp) :
      object(papp),
      ::user::interaction(papp),
      ::user::plain_edit(papp)
   {

      m_dwDelayedAfterChange = 1000;

      m_ptopview = NULL;

      m_bEnterKeyPressed = false;

   }

   top_edit_view::~top_edit_view()
   {

   }
   void top_edit_view::install_message_routing(::message::sender * psender)
   {

      ::user::show < ::user::plain_edit >::install_message_routing(psender);

      IGUI_MSG_LINK(WM_CREATE, psender, this, &top_edit_view::_001OnCreate);
      IGUI_MSG_LINK(WM_KEYDOWN, psender, this, &top_edit_view::_001OnKeyDown);

   }


   void top_edit_view::_001OnCreate(::message::message * pobj)
   {

      SCAST_PTR(::message::create, pcreate, pobj);

      pcreate->previous();

      if (pcreate->m_bRet)
         return;


      m_ptopview = GetTypedParent < top_view >();


   }


   void top_edit_view::_001OnKeyDown(::message::message * pobj)
   {

      SCAST_PTR(::message::key, pkey, pobj);

      ::user::view_update_hint uh(get_app());

      uh.m_ehint = ::user::view_update_hint::hint_key_down;

      uh.m_pui = this;

      uh.m_ekey = pkey->m_ekey;

      get_document()->update_all_views(this, 0, &uh);

      if (pkey->m_ekey == ::user::key_return)
      {

         m_bEnterKeyPressed = true;

         SetTimer(5544, m_dwDelayedAfterChange, NULL);

      }
      else
      {

         m_bEnterKeyPressed = false;

      }

   }


   void top_edit_view::_001OnTimer(::timer * ptimer)
   {

      ::user::show < ::user::plain_edit >::_001OnTimer(ptimer);


      if (ptimer->m_nIDEvent == 5544)
      {

         KillTimer(ptimer->m_nIDEvent);

         ::user::view_update_hint uh(get_app());

         uh.m_ehint = ::user::view_update_hint::hint_after_change_text_delayed;

         uh.m_pui = this;

         uh.m_bEnterKeyPressed = m_bEnterKeyPressed;

         m_bEnterKeyPressed = false;

         get_document()->update_all_views(this, 0, &uh);

      }


   }


   void top_edit_view::on_update(::user::impact * pSender, LPARAM lHint, object* phint)
   {

   }


   void top_edit_view::_001OnAfterChangeText(::action::context actioncontext)
   {


      if (actioncontext.is_user_source())
      {

         ::user::view_update_hint uh(get_app());

         uh.m_ehint = ::user::view_update_hint::hint_after_change_text;

         uh.m_pui = this;

         get_document()->update_all_views(this, 0, &uh);

         SetTimer(5544, m_dwDelayedAfterChange, NULL);

      }

   }


   bool top_edit_view::keyboard_focus_is_focusable()
   {

      return is_window_enabled() && IsWindowVisible();

   }

   bool top_edit_view::IsWindowVisible()
   {

      return ::user::show < ::user::plain_edit >::IsWindowVisible() && !GetTopLevel()->frame_is_transparent();

   }

   /*
   int64_t top_edit_view::add_ref()
   {
   return ::object::add_ref();
   }
   int64_t top_edit_view::dec_ref()
   {
   return ::object::dec_ref();
   }


   */
} // namespace userex




