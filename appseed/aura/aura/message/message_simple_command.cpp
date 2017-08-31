#include "framework.h"


namespace message
{


   simple_command::simple_command(::aura::application * papp) :
      base(papp)
   {

      m_id.m_emessagetype = ::message::type_user_simple_command;
      m_esimplecommand = simple_command_none;

   }


   void simple_command::set(::user::primitive * pwnd, UINT uiMessage, WPARAM wparam, ::lparam lparam, LRESULT & lresult)
   {

      ::message::base::set(pwnd, uiMessage, wparam, lparam, lresult);

      m_esimplecommand = (e_simple_command)wparam;

   }


} // namespace message


