#include "framework.h"


//::user::command::user::command(::aura::application * papp) :
//   ::message::base(papp)
//{
//   
//      m_iIndex                      = 0;
//      m_iCount                      = 0;
//      m_pMenu                       = NULL;
//      m_pSubMenu                    = NULL;
//      m_pParentMenu                 = NULL;
//      m_pOther                      = NULL;
//      m_bEnableChanged              = FALSE;
//      m_bContinueRouting            = FALSE;
//      m_bEnableIfHasCommandHandler  = true;
//   
//}
//
//::user::command::user::command(class ::message::sender * psignal):
//   ::message::base(psignal)
//{
//
//   
//   m_iIndex                      = 0;
//   m_iCount                      = 0;
//   m_pMenu                       = NULL;
//   m_pSubMenu                    = NULL;
//   m_pParentMenu                 = NULL;
//   m_pOther                      = NULL;
//   m_bEnableChanged              = FALSE;
//   m_bContinueRouting            = FALSE;
//   m_bEnableIfHasCommandHandler  = true;
//   
//}
//
//
//
//void ::user::command::reset(class ::message::sender * psignal)
//{
//
//   ::message::message::reset(psignal);
//
//}
//
//
//// default ::user::command implementation only works for Menu Items
//void ::user::command::Enable(bool bOn,::action::context actioncontext)
//{
//
//   if(m_pMenu != NULL)
//   {
//
//      if(m_pSubMenu != NULL)
//         return; // don't change popup menus indirectly
//
//      ENSURE(m_iIndex < m_iCount);
//
//   }
//   else
//   {
//
//      // enable/disable a control (i.e. child interaction_impl)
//      ENSURE(m_pOther != NULL);
//
//      Application.enable_window(m_pOther,bOn);
//
//   }
//
//   m_bEnableChanged = TRUE;
//
//}
//
//void ::user::command::_001SetCheck(bool bCheck,::action::context actioncontext)
//{
//
//   _001SetCheck((check::e_check) (bCheck ? check::checked : check::unchecked),actioncontext);
//
//}
//
//
//void ::user::command::_001SetCheck(check::e_check nCheck,::action::context actioncontext)
//{
//
//   if(m_pMenu != NULL)
//   {
//      if(m_pSubMenu != NULL)
//         return; // don't change popup menus indirectly
//
//      // place checkmark next to menu item
//      ENSURE(m_iIndex < m_iCount);
//   }
//   else if(m_pOther != NULL)
//   {
//
//#ifdef WINDOWS
//
//      // we can only check buttons or controls acting like buttons
//      ENSURE(m_pOther != NULL);
//      if(Application.send_message(m_pOther,WM_GETDLGCODE) & DLGC_BUTTON)
//         Application.send_message(m_pOther,BM_SETCHECK,nCheck);
//      // otherwise ignore it
//
//#endif
//
//   }
//}
//
//
//__STATIC void __load_dot_bitmap(); // for swap tuning
//
//void ::user::command::SetRadio(bool bOn,::action::context actioncontext)
//{
//   _001SetCheck(bOn != FALSE,actioncontext); // this default works for most things as well
//   if(m_pMenu != NULL)
//   {
//      if(m_pSubMenu != NULL)
//         return; // don't change popup menus indirectly
//
//      // for menu item - use dot instead of checkmark
//      ENSURE(m_iIndex < m_iCount);
//
//      /*      if (afxData.hbmMenuDot == NULL)
//      __load_dot_bitmap();    // in INIT segment
//      */
//   }
//}
//
//void ::user::command::SetText(const char * lpszText,::action::context actioncontext)
//{
//   ENSURE_ARG(lpszText != NULL);
//   ASSERT(__is_valid_string(lpszText));
//
//   {
//      ENSURE(m_pOther != NULL);
//      Application.set_window_text(m_pOther,lpszText);
//   }
//}
//
//bool ::user::command::DoUpdate(command_target* pTarget,bool bDisableIfNoHndler)
//{
//   if(m_id.is_empty())
//      return TRUE;     // ignore invalid IDs
//
//   ENSURE_VALID(pTarget);
//
//   m_bEnableChanged = FALSE;
//   bool bResult = pTarget->_001SendUpdateCmdUi(this);
//
//   if(!bResult)
//      Enable(FALSE);
//
//   return bResult;
//}
//
//
//
