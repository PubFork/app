#include "framework.h" // from "base/user/user.h"
//#include "base/user/user.h"


namespace user
{


   menu_command::menu_command(::aura::application * papp) :
   ::user::command(papp)
   {
      
   }
   
   
   void menu_command::delete_this()
   {
   
      ::user::command::delete_this();
      
   }
   
   
   void menu_command::Enable(bool bOn, ::action::context actioncontext)
   {
      
      ::user::command::Enable(bOn, actioncontext);
      
      if (m_puiOther != NULL)
      {

         m_puiOther->enable_window(bOn != FALSE);

      }
      
   }
   
   
   void menu_command::_001SetCheck(::check::e_check echeck, ::action::context actioncontext)
   {
      
      ASSERT(echeck == ::check::checked || echeck == ::check::unchecked || echeck == ::check::tristate); // 0=>off, 1=>on, 2=>indeterminate

      ::user::command::_001SetCheck(echeck, actioncontext);
      
      if (m_puiOther != NULL)
      {
         
         sp(::user::check) pcheck = m_puiOther;
         
         if(pcheck.is_set())
         {

            pcheck->_001SetCheck(echeck, actioncontext);
            
         }

      }
      
   }
   
   
   void menu_command::_001SetText(const string & strText, ::action::context actioncontext)
   {
      
      if (m_puiOther != NULL)
      {
         
         sp(::user::edit_text) pedit = m_puiOther;
         
         if(pedit.is_set())
         {
            
            pedit->_001SetText(strText, actioncontext);
            
         }
         
      }
      
   }
   
   
} // namespace user




