#include "framework.h"



namespace message
{

   
   sender::sender()
   {

      m_pmutexIdRoute = new mutex();

   }


   sender::~sender()
   {
      
      try
      {
      
         synch_lock sl(m_pmutexIdRoute);

         for (auto & idroute : m_idroute)
         {
            
            try
            {

               for (auto & route : idroute.m_element2)
               {
               
                  try
                  {
               
                     synch_lock sl(route->m_preceiver->m_pmutex);
                  
                     route->m_preceiver->m_sendera.remove(this);
                  
                  }
                  catch(...)
                  {
               
                  }

               }
               
            }
            catch(...)
            {
               
            }

         }
         
      }
      catch(...)
      {
         
      }
      
      ::aura::del(m_pmutexIdRoute);

   }

   void sender::remove_receiver(::message::receiver * preceiver)
   {

      for (auto & id_route_array : m_idroute)
      {

         id_route_array.m_element2.pred_remove([=](auto & pitem)
         {

            return pitem->m_preceiver == preceiver;

         });

      }
      
      preceiver->m_sendera.remove(this);

   }

   
   void sender::route_message(::message::message * pmessage)
   {

      {

         synch_lock sl(m_pmutexIdRoute);

         pmessage->m_routea = m_idroute[pmessage->m_id];

      }

      pmessage->m_iRouteIndex = pmessage->m_routea.get_upper_bound();

      pmessage->m_psender = this;

      for(;pmessage->m_iRouteIndex >= 0; pmessage->m_iRouteIndex--)
      {

         pmessage->route();

         if (pmessage->m_bRet)
         {

            break;

         }

      }

   }

   
   void sender::remove_all_routes()
   {

      synch_lock sl(m_pmutexIdRoute);
      
      for (auto & id_route_array : m_idroute)
      {
         
         id_route_array.m_element2.pred_each([=](auto & pitem)
                                               {
                                                  
                                                  pitem->m_preceiver->m_sendera.remove(this);
                                                  
                                               });
         
      }

   }


   e_prototype sender::GetMessagePrototype(UINT uiMessage, UINT uiCode)
   {
      switch (uiMessage)
      {
      case WM_SIZE:
         return PrototypeSize;
      case WM_HSCROLL:
      case WM_VSCROLL:
         return PrototypeScroll;
      case WM_CREATE:
      case WM_NCCREATE:
         return PrototypeCreate;
      case WM_MOVE:
         return PrototypeMove;
      case WM_ACTIVATE:
         return PrototypeActivate;
      case WM_MEASUREITEM:
         return PrototypeMeasureItem;
#ifdef WINDOWS
      case WM_NOTIFY:
         return PrototypeNotify;
#endif
      case WM_COMMAND:
      {
         switch (uiCode)
         {
         //case CN_UPDATE_::user::command:
           // return PrototypeUpdateCommandUserInterface;
         default:
            return PrototypeCommand;
         }
      }
      case WM_MOUSEMOVE:
      case WM_LBUTTONDOWN:
      case WM_LBUTTONUP:
      case WM_LBUTTONDBLCLK:
      case WM_RBUTTONDOWN:
      case WM_RBUTTONUP:
      case WM_RBUTTONDBLCLK:
      case WM_MBUTTONDOWN:
      case WM_MBUTTONUP:
      case WM_MBUTTONDBLCLK:
      case WM_NCMOUSEMOVE:
      case WM_NCLBUTTONDOWN:
      case WM_NCLBUTTONUP:
         return PrototypeMouse;
#ifdef WINDOWS
      case WM_MOUSEWHEEL:
         return PrototypeMouseWheel;
#endif
      case WM_NCACTIVATE:
         return PrototypeNcActivate;
      case WM_TIMER:
         return PrototypeTimer;
      case WM_KEYDOWN:
      case WM_KEYUP:
      case WM_CHAR:
      case WM_DEADCHAR:
      case WM_SYSKEYDOWN:
      case WM_SYSKEYUP:
      case WM_SYSCHAR:
      case WM_SYSDEADCHAR:
#if(_WIN32_WINNT >= 0x0501)
      case WM_UNICHAR:
#endif
         return PrototypeKey;
      case WM_NCHITTEST:
         return PrototypeNcHitTest;
      case WM_SETCURSOR:
         return PrototypeSetCursor;
      case WM_ERASEBKGND:
         return PrototypeEraseBkgnd;
      case WM_SHOWWINDOW:
         return PrototypeShowWindow;
      case WM_INITMENUPOPUP:
         return PrototypeInitMenuPopup;
         /*#ifdef WINDOWS
         case WM_CTLCOLOR:
         if(pba)
         return PrototypeCtlColor;
         case WM_CTLCOLOR + WM_REFLECT_AXIS:
         return PrototypeCtlColorReflect;
         #endif*/
      case WM_SETFOCUS:
         return PrototypeSetFocus;
      case WM_WINDOWPOSCHANGING:
      case WM_WINDOWPOSCHANGED:
         return PrototypeWindowPos;
      case WM_NCCALCSIZE:
         return PrototypeNcCalcSize;
      case WM_PAINT:
         return PrototypeNone;
      default:
         return PrototypeNone;
      }
   }


} // namespace message
