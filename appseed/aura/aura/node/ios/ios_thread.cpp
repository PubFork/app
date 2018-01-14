#include "framework.h"
#include <fcntl.h>


//struct ___THREAD_STARTUP : ::ios::thread_startup
//{
//   ::ios::thread* pThread;    // thread for new thread
//   DWORD dwCreateFlags;    // thread creation flags
//   bool bError;    // TRUE if error during startup
//};
//
//
//WINBOOL CLASS_DECL_AURA AfxInternalPumpMessage();
//LRESULT CLASS_DECL_AURA AfxInternalProcessWndProcException(::exception::aura*, const MESSAGE* pMsg);
//__STATIC void CLASS_DECL_AURA __pre_init_dialog(::user::interaction * pWnd, LPRECT lpRectOld, DWORD* pdwStyleOld);
//__STATIC void CLASS_DECL_AURA __post_init_dialog(::user::interaction * pWnd, const RECT& rectOld, DWORD dwStyleOld);

//namespace ios
//{
//
//   thread_startup::thread_startup() :
//   hEvent(get_app(), false, true),
//   hEvent2(get_app(), false, true)
//   {
//   }
//
//   thread_startup::~thread_startup()
//   {
//   }
//
//} // namespace ca2





//struct _AFX_THREAD_STARTUP : ::ios::thread_startup
//{
//   ::ios::thread* pThread;    // thread for new thread
//   DWORD dwCreateFlags;    // thread creation flags
//   WINBOOL bError;    // TRUE if error during startup
//};
//
//
//UINT APIENTRY __thread_entry(void * pParam)
//{
//   _AFX_THREAD_STARTUP* pStartup = (_AFX_THREAD_STARTUP*)pParam;
//   ASSERT(pStartup != NULL);
//   ASSERT(pStartup->pThread != NULL);
//   ASSERT(!pStartup->bError);
//
//   ::ios::thread* pThread = pStartup->pThread;
//
//   try
//   {
//
//      __init_thread();
//
//   }
//   catch(::exception::aura *)
//   {
//      pStartup->bError = TRUE;
//      pStartup->hEvent.set_event();
//      __end_thread(pThread->m_paxisapp, (UINT)-1, FALSE);
//      ASSERT(FALSE);  // unreachable
//   }
//
//   pStartup->m_pthread = pStartup->pThread;
//
//   pThread->thread_entry(pStartup);
//
//
//   pStartup->hEvent.set_event();
//
//   // wait for thread to be resumed
//   pStartup->hEvent2.wait();
//
//   delete pStartup;
//
//   pStartup = NULL;
//
//
//   int32_t n = pThread->m_p->main();
//
//   return pThread->thread_term(n);
//}

//
//namespace ios
//{
//
//   thread_pointer < ::thread > t_pthread;
//
//
//   CLASS_DECL_AURA ::thread * __get_thread()
//   {
//
//      return t_pthread;
//
//   }
//
//
//   CLASS_DECL_AURA void __set_thread(::thread * pthread)
//   {
//
//      t_pthread = pthread;
//
//   }
//
//
//} // namespace ios
//



//
//
//
//void CLASS_DECL_AURA __end_thread(::aura::application * papp, UINT nExitCode, bool bDelete)
//{
//
//   ::ios::thread* pThread = ::ios::__get_thread();
//
//   if (pThread != NULL)
//   {
//      ASSERT_VALID(pThread);
//      //ASSERT(pThread != System::smart_pointer < ::application *>::m_p);
//
//      if (bDelete)
//         pThread->Delete();
//      pState->m_pCurrentWinThread = NULL;
//   }
//
//   // allow cleanup of any thread local objects
//   __term_thread(papp);
//
//   // allow C-runtime to cleanup, and exit the thread
//   //   _endthreadex(nExitCode);
//}
//
//void CLASS_DECL_AURA __term_thread(::aura::application * papp, HINSTANCE hInstTerm)
//{
//
//
//   try
//   {
//      // cleanup the rest of the thread local data
////      if (ios::__thread_data != NULL)
//  //       ios::__thread_data->delete_data();
//      //__thread_data->DeleteValues(hInstTerm, FALSE);
//   }
//   catch( ::exception::aura* e )
//   {
//      e->Delete();
//   }
//}
//




bool __node_init_thread(::thread * pthread)
{

   UNREFERENCED_PARAMETER(pthread);

   return true;

}



bool __node_term_thread(::thread * pthread)
{

   UNREFERENCED_PARAMETER(pthread);

   return true;

}



