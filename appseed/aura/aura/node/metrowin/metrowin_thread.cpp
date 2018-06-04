#include "framework.h"
//#include "metrowin.h"
//#include <process.h>    // for _beginthreadex and _endthreadex
//#include <ddeml.h>  // for MSGF_DDEMGR

namespace metrowin
{
   class thread;
} // namespace metrowin

bool CLASS_DECL_AURA __internal_pump_message();
LRESULT CLASS_DECL_AURA __internal_process_wnd_proc_exception(::exception::base*, const MSG* pMsg);
bool __internal_pre_translate_message(MSG* pMsg);
bool __internal_is_idle_message(MSG* pMsg);
//__STATIC void CLASS_DECL_AURA __pre_init_dialog(sp(::user::interaction) pWnd, LPRECT lpRectOld, uint32_t* pdwStyleOld);
//__STATIC void CLASS_DECL_AURA __post_init_dialog(sp(::user::interaction) pWnd, const RECT& rectOld, uint32_t dwStyleOld);


//__declspec(thread) HHOOK t_hHookOldMsgFilter = NULL;
//
//
//LRESULT CALLBACK __message_filter_hook(int32_t code,WPARAM wParam,LPARAM lParam);


void CLASS_DECL_AURA __init_thread()
{

   //if(t_hHookOldMsgFilter == NULL)
   //{

   //   t_hHookOldMsgFilter = ::SetWindowsHookEx(WH_MSGFILTER,__message_filter_hook,NULL,::GetCurrentThreadId());

   //}

}


void CLASS_DECL_AURA __term_thread()
{


}


bool __node_init_thread(::thread * pthread)
{

   try
   {

      pthread->::exception::translator::attach();

   }
   catch(...)
   {

      return false;

   }

   return true;

}



bool __node_term_thread(::thread * pthread)
{

   bool bOk1 = false;

   try
   {

      if(pthread != NULL)
      {

         pthread->::exception::translator::detach();

      }

      bOk1 = true;

   }
   catch(...)
   {

   }

   return bOk1;

}
