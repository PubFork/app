#include "framework.h" // from "base/user/user.h"
//#include "base/user/user.h"


namespace user
{


   menu_command::menu_command(::aura::application * papp) :
   ::user::command(papp)
   {
      
   }
   
   
   void menu_command::Enable(bool bOn, ::action::context actioncontext)
   {
      
      m_bEnableChanged = TRUE;
      
      m_puiOther->enable_window(bOn != FALSE);
      
   }
   
   
   void menu_command::_001SetCheck(check::e_check echeck, ::action::context actioncontext)
   {
      
      ASSERT(echeck == check::checked || echeck == check::unchecked || echeck == check::tristate); // 0=>off, 1=>on, 2=>indeterminate
      
      m_puiOther->_001SetCheck(echeck, actioncontext);
      
   }
   
   
   void menu_command::SetText(const char * pszText, ::action::context actioncontext)
   {
      
      m_puiOther->_001SetText(pszText, actioncontext);
      
   }
   
   
} // namespace user




