#include "framework.h"


namespace user
{

   namespace wndfrm
   {



      namespace frame
      {


         SysMenuManager::SysMenuManager(WorkSet * pwf)
         {
            m_pworkset = pwf;
            m_enumState = state_initial;
         }

         SysMenuManager::~SysMenuManager()
         {

         }

         void SysMenuManager::relay_event(::message::message * pobj)
         {

            SCAST_PTR(::message::base, pbase, pobj);

            if(m_pworkset->GetEventWindow() == NULL || pbase->m_pwnd != m_pworkset->GetEventWindow())
               return;
            if(pbase->m_id == WM_RBUTTONDOWN)
            {
               m_enumState = StateMBDown;
            }
            else if(pbase->m_id == WM_RBUTTONUP)
            {
               if(m_enumState == StateMBDown)
               {
                  //               sp(::user::interaction) pwnd = m_pworkset->GetEventWindow();

                  /*            ::user::menu * pmenu = pwnd->GetSystemMenu(FALSE);
                           if(pmenu != NULL)
                           {
                           pmenu->track_popup_menu(
                           lpMsg->pt.x, lpMsg->pt.y,
                           pwnd);
                           }*/
                  pbase->m_bRet = true;
                  return;
               }
               m_enumState = state_initial;
            }
         }

         void SysMenuManager::message_handler(::user::interaction * pui, ::message::base * pbase)
         {

            switch(pbase->m_id)
            {
            case WM_LBUTTONDBLCLK:
            {
                                    point point(pbase->m_lparam);
                                    if(OnLButtonDblClk((UINT)pbase->m_wparam, point))
                                    {
                                       pbase->set_lresult(0);
                                       pbase->m_bRet = true;
                                       return;
                                    }
                                    break;
            }
            }

            if(pbase->m_id == WM_RBUTTONDOWN)
            {
               m_enumState = StateMBDown;
            }
            if(pbase->m_id == WM_RBUTTONDOWN)
            {
               m_enumState = StateMBDown;
            }
            else if(pbase->m_id == WM_RBUTTONUP)
            {
               if(m_enumState == StateMBDown)
               {
                  //               sp(::user::interaction) pwnd = m_pworkset->GetEventWindow();

                  /*            ::user::menu * pmenu = pwnd->GetSystemMenu(FALSE);
                           if(pmenu != NULL)
                           {
                           point pt(LOWORD(lparam), HIWORD(lparam));
                           pwnd->ClientToScreen(&pt);
                           pmenu->track_popup_menu(
                           pt.x, pt.y,
                           pwnd);
                           }*/
                  pbase->m_bRet = true;
                  return;
               }
               m_enumState = state_initial;
            }
         }

         bool SysMenuManager::OnLButtonDblClk(UINT nFlags, point point)
         {
            UNREFERENCED_PARAMETER(nFlags);
            UNREFERENCED_PARAMETER(point);
            if(m_pworkset == NULL
               || m_pworkset->m_pappearance == NULL)
               return false;
            /*xxx appearance::e_element eelement;
            if(m_pworkset->m_pappearance->hit_test(point, eelement))
            {
            if(eelement == appearance::ElementTopLeftIcon)
            {
            m_pworkset->WindowClose();
            return true;
            }
            }*/
            return false;

         }

         bool SysMenuManager::update(WorkSet * pset)
         {
            m_pworkset = pset;
            return true;
         }


      } // namespace frame





   } // namespace wndfrm






} // namespace user



