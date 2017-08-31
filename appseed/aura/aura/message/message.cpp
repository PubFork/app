#include "framework.h"


namespace message
{

   class ::message::sender * CreateSignal()
   {
      return new class ::message::sender();
   }



   UINT translate_to_os_message(UINT uiMessage)
   {

#ifdef WINDOWS

      switch(uiMessage)
      {
      case message_create:
         return WM_CREATE;
      default:
         return uiMessage;
      };
#elif defined(LINUX) ||  defined(APPLEOS) || defined(VSNORD)
      switch(uiMessage)
      {
      case message_create:
         return WM_CREATE;
      default:
         return uiMessage;
      };

#else
      switch(uiMessage)
      {
      default:
         return uiMessage;
      };
#endif

   }


   CLASS_DECL_AURA bool is_idle_message(::message::message * pobj)
   {

      SCAST_PTR(::message::base,pbase,pobj);

      // Return FALSE if the message just dispatched should _not_
      // cause on_idle to be run.  Messages which do not usually
      // affect the state of the ::fontopus::user interface and happen very
      // often are checked for.

      if(pbase == NULL)
         return FALSE;

      // redundant WM_MOUSEMOVE and WM_NCMOUSEMOVE
      if(pbase->is_message() && (pbase->m_id == WM_MOUSEMOVE || pbase->m_id == WM_NCMOUSEMOVE))
      {
         return TRUE;
      }

      // WM_PAINT and WM_SYSTIMER (caret blink)
      return pbase->m_id != WM_PAINT && pbase->m_id != 0x0118;

   }



   CLASS_DECL_AURA bool is_idle_message(LPMESSAGE lpmsg)
   {

      // Return FALSE if the message just dispatched should _not_
      // cause on_idle to be run.  Messages which do not usually
      // affect the state of the ::fontopus::user interface and happen very
      // often are checked for.

      if(lpmsg == NULL)
         return false;

      // redundant WM_MOUSEMOVE and WM_NCMOUSEMOVE
      if(lpmsg->message == WM_MOUSEMOVE || lpmsg->message == WM_NCMOUSEMOVE)
      {
         return true;
      }

      // WM_PAINT and WM_SYSTIMER (caret blink)
      return lpmsg->message != WM_PAINT && lpmsg->message != 0x0118;

   }




} // namespace message








