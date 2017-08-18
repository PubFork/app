#include "framework.h" // from "base/user/user.h"
//#include "base/user/user.h"


namespace user
{

   menu_command_ui::menu_command_ui(::aura::application * papp) :
   command_ui(papp)
   {
      
   }
   
   
   void menu_command_ui::Enable(bool bOn, ::action::context actioncontext)
   {
      
      m_bEnableChanged = TRUE;
      
      m_pOther->enable_window(bOn != FALSE);
      
   }
   
   
   void menu_command_ui::_001SetCheck(check::e_check echeck, ::action::context actioncontext)
   {
      
      ASSERT(echeck == check::checked || echeck == check::unchecked || echeck == check::tristate); // 0=>off, 1=>on, 2=>indeterminate
      
      m_pOther->_001SetCheck(echeck, actioncontext);
      
   }
   
   
   void menu_command_ui::SetText(const char * pszText, ::action::context actioncontext)
   {
      
      m_pOther->_001SetText(pszText, actioncontext);
      
   }
   
   
} // namespace user




