#include "framework.h"
//#include <sched.h>
//#include <time.h>
//#include <pthread.h>

CLASS_DECL_AURA void thread_get_os_priority(int32_t * piOsPolicy, sched_param * pparam, int32_t iCa2Priority);

CLASS_DECL_AURA void process_get_os_priority(int32_t * piOsPolicy, sched_param * pparam, int32_t iCa2Priority);

CLASS_DECL_AURA int32_t thread_get_scheduling_priority(int iOsPolicy, const sched_param * pparam);

CLASS_DECL_AURA int32_t process_get_scheduling_priority(int iOsPolicy, const sched_param * pparam);


DWORD MsgWaitForMultipleObjectsEx(DWORD dwSize, sync_object * * pobjectptra, DWORD dwTimeout, DWORD dwWakeMask, DWORD dwFlags)
{

   DWORD start = 0;

   if(dwTimeout != (DWORD) INFINITE)
   {
      start = ::get_tick_count();
   }

   mq * pmq = NULL;

   if(dwWakeMask > 0)
   {

      pmq = __get_mq(GetCurrentThreadId(), false);

      //if(pmq == NULL)
      // return 0;

   }



   int_bool bWaitForAll        = dwFlags & MWMO_WAITALL;
//   int_bool bAlertable         = dwFlags & MWMO_ALERTABLE;
//   int_bool bInputAvailable    =  dwFlags & MWMO_INPUTAVAILABLE;

   timespec delay;

   delay.tv_sec = 0;
   delay.tv_nsec = 1000000;

   if(bWaitForAll)
   {

      while(true)
      {
         int32_t i;
         int32_t j;
         i = 0;
         for(; comparison::lt(i, dwSize);)
         {

            if(pmq != NULL)
            {

               synch_lock sl(&pmq->m_mutex);

               if(pmq->ma.get_count() > 0)
               {

                  return WAIT_OBJECT_0 + dwSize;

               }

            }

            if(dwTimeout != (DWORD) INFINITE && ::get_tick_count() - start >= dwTimeout)
            {

               for(j = 0; j < i; j++)
               {

                  pobjectptra[j]->unlock();

               }

               return WAIT_TIMEOUT;

            }

            if(pobjectptra[i]->lock(millis(1)))
            {

               i++;

            }
            else
            {

               nanosleep(&delay, NULL);

            }

         }
         //      for(j = 0; j < dwSize; j++)
         //    {
         //     pobjectptra[j]->unlock();
         //}

         return WAIT_OBJECT_0;

      }

   }
   else
   {

      int32_t i;
//      int32_t j;
      while(true)
      {

         for(i = 0; comparison::lt(i, dwSize); i++)
         {

            if(pmq != NULL)
            {

               synch_lock sl(&pmq->m_mutex);

               if(pmq->ma.get_count() > 0)
               {

                  return WAIT_OBJECT_0 + dwSize;

               }

            }

            if(dwTimeout != (DWORD) INFINITE && ::get_tick_count() - start >= dwTimeout)
            {

               return WAIT_TIMEOUT;

            }

            if(pobjectptra[i]->lock(millis(0)))
            {

               return WAIT_OBJECT_0 + i;

            }

         }

         nanosleep(&delay, NULL);

      }

   }

}


DWORD MsgWaitForMultipleObjects(DWORD dwSize, sync_object ** pobjectptra, WINBOOL bWaitForAll, DWORD dwTimeout, DWORD dwWakeMask)
{

   return MsgWaitForMultipleObjectsEx(dwSize, pobjectptra, dwTimeout, dwWakeMask, (bWaitForAll ?  MWMO_WAITALL : 0));

}


DWORD WaitForMultipleObjectsEx(DWORD dwSize, sync_object ** pobjectptra, WINBOOL bWaitForAll, DWORD dwTimeout, WINBOOL bAlertable)
{

   return MsgWaitForMultipleObjectsEx(dwSize, pobjectptra, dwTimeout, 0, (bWaitForAll ?  MWMO_WAITALL : 0) | (bAlertable ?  MWMO_ALERTABLE : 0));

}


DWORD WaitForMultipleObjects(DWORD dwSize, sync_object ** pobjectptra, WINBOOL bWaitForAll, DWORD dwTimeout)
{

   return WaitForMultipleObjectsEx(dwSize, pobjectptra, bWaitForAll, dwTimeout, FALSE);

}


DWORD WaitForSingleObjectEx(sync_object * pobject, DWORD dwTimeout, WINBOOL bAlertable)
{

   return WaitForMultipleObjectsEx(1, &pobject, TRUE, dwTimeout, bAlertable);

}


DWORD WaitForSingleObject(sync_object * pobject, DWORD dwTimeout)
{

   return WaitForSingleObjectEx(pobject, dwTimeout, FALSE);

}




thread_data::thread_data()
{

   pthread_key_create(&m_key, NULL);

}


thread_data::~thread_data()
{

   //pthread_key_destroy(&m_key);

}

void * thread_data::get()
{

   return pthread_getspecific(m_key);

}


void thread_data::set(void * p)
{

   pthread_setspecific(m_key,p);

}



CLASS_DECL_AURA HTHREAD get_current_thread()
{

   return ::GetCurrentThread();

}


CLASS_DECL_AURA IDTHREAD get_current_thread_id()
{

   return ::GetCurrentThreadId();

}









void __node_init_multithreading()
{

   //s_pmapHthreadHthread = new map < HTHREAD,HTHREAD,HTHREAD,HTHREAD >();

   //s_pmapDwordHthread = new map < DWORD,DWORD,HTHREAD,HTHREAD >();

   //s_pmapHthreadDword = new map < HTHREAD,HTHREAD,DWORD,DWORD >();

   __node_init_cross_windows_threading();


}



void __node_term_multithreading()
{

   __node_term_cross_windows_threading();

   //delete s_pmapHthreadDword;

   //s_pmapHthreadDword = NULL;

   //delete s_pmapDwordHthread;

   //s_pmapDwordHthread = NULL;

   //delete s_pmapHthreadHthread;

   //s_pmapHthreadHthread = NULL;

}










#if defined(LINUX) // || defined(ANDROID)

bool (* g_pfn_defer_process_x_message)(HTHREAD hthread,LPMESSAGE lpMsg,oswindow oswindow,bool bPeek) = NULL;

bool aura_defer_process_x_message(HTHREAD hthread,LPMESSAGE lpMsg,oswindow oswindow,bool bPeek)
{

   if(g_pfn_defer_process_x_message == NULL)
      return false;

   return (*g_pfn_defer_process_x_message)(hthread, lpMsg, oswindow, bPeek);

}

void set_defer_process_x_message(bool (* pfn)(HTHREAD hthread,LPMESSAGE lpMsg,oswindow oswindow,bool bPeek))
{

   g_pfn_defer_process_x_message = pfn;

}

UINT (* g_x11_thread)(void * pparam) = NULL;

#ifdef LINUX
UINT __x11_thread(void * pparam)
{

   (*g_x11_thread)(pparam);

}
#endif

#endif



extern "C"
void * os_thread_thread_proc(LPVOID lpparameter);









// Converts a Win32 thread priority to WinRT format.
int32_t GetWorkItemPriority(int32_t nPriority)
{
   if(nPriority < 0)
      return nPriority; // WorkItemPriority::Low;
   else if(nPriority > 0)
      return nPriority; // WorkItemPriority::High;
   else
      return nPriority; // WorkItemPriority::Normal;
}




int_bool WINAPI SetThreadPriority(HTHREAD hThread,int32_t nCa2Priority)
{

   int32_t iPolicy;

   sched_param schedparam;

   thread_get_os_priority(&iPolicy,&schedparam,nCa2Priority);

   pthread_setschedparam((pthread_t) hThread,iPolicy,&schedparam);

   return TRUE;

}

int32_t get_os_thread_priority(int32_t iCa2Priority)
{

   return iCa2Priority;

}





int32_t WINAPI GetThreadPriority(HTHREAD  hthread)
{

   int iOsPolicy = SCHED_OTHER;

   sched_param schedparam;

   schedparam.sched_priority = 0;

   pthread_getschedparam((IDTHREAD) hthread,&iOsPolicy,&schedparam);

   return thread_get_scheduling_priority(iOsPolicy,&schedparam);

}




static HTHREAD g_hMainThread = (HTHREAD) NULL;

static IDTHREAD g_uiMainThread = (IDTHREAD) -1;


CLASS_DECL_AURA void set_main_thread(HTHREAD hThread)
{

   // MESSAGE msg;

   // PeekMessage function used to create message queue Windows Desktop
   // PeekMessage(&msg, NULL, 0, 0xffffffff, FALSE);

   g_hMainThread = hThread;

}

CLASS_DECL_AURA void set_main_thread_id(IDTHREAD uiThread)
{

   //   MESSAGE msg;

   // PeekMessage function used to create message queue Windows Desktop
   // PeekMessage(&msg, NULL, 0, 0xffffffff, FALSE);

   g_uiMainThread = uiThread;

}


CLASS_DECL_AURA HTHREAD get_main_thread()
{

   return g_hMainThread;

}


CLASS_DECL_AURA IDTHREAD get_main_thread_id()
{

   return g_uiMainThread;

}


CLASS_DECL_AURA void attach_thread_input_to_main_thread(bool bAttach)
{

}



LPVOID WINAPI thread_get_data(HTHREAD hthread,DWORD dwIndex);


int_bool WINAPI thread_set_data(HTHREAD hthread,DWORD dwIndex,LPVOID lpTlsValue);



DWORD g_dwDebug_post_thread_msg_time;
int g_iDebug_post_thread_msg_time;

CLASS_DECL_AURA int_bool WINAPI PostThreadMessageW(IDTHREAD iThreadId,UINT Msg,WPARAM wParam,LPARAM lParam)
{

   mq * pmq = __get_mq(iThreadId, Msg != WM_QUIT);

   if(pmq == NULL)
      return FALSE;

   synch_lock ml(&pmq->m_mutex);

   MESSAGE msg;

   //zero(&msg, sizeof(msg));

   if(Msg == WM_QUIT)
   {
      ::output_debug_string("\n\n\nWM_QUIT posted to thread " + ::str::from((uint64_t)iThreadId) + "\n\n\n");
   }


   DWORD dwNow = get_tick_count();

   if(dwNow - g_dwDebug_post_thread_msg_time < 1)
   {

      if(g_iDebug_post_thread_msg_time > 10)
      {

//         writeln("PostThreadMessage" flooded?");

      }
      else
      {

         g_iDebug_post_thread_msg_time++;

      }

   }
   else
   {

      g_iDebug_post_thread_msg_time = 0;

   }

   g_dwDebug_post_thread_msg_time = dwNow;



   msg.message = Msg;
   msg.wParam  = wParam;
   msg.lParam  = lParam;
   msg.pt.x    = 0x80000000;
   msg.pt.y    = 0x80000000;
   msg.hwnd    = NULL;

   pmq->ma.add(msg);

   //   void * p = pmq->ma[pmq->ma.get_count() -1].hwnd;

   pmq->m_eventNewMessage.set_event();

   return true;

}








//void thread_layer::wait_thread(DWORD dwMillis)
//{
//
//   try
//   {
//
//      m_hthread->m_pevent->wait(millis(dwMillis));
//
//   }
//   catch(...)
//   {
//
//   }
//
//}
//
//
//
//
//
//thread_layer::~thread_layer()
//{
//
//   delete m_hthread;
//
//}
//
//


CLASS_DECL_AURA HTHREAD GetCurrentThread()
{

   return pthread_self();

}

CLASS_DECL_AURA IDTHREAD GetCurrentThreadId()
{

   return pthread_self();

}


namespace multithreading
{

   CLASS_DECL_AURA bool set_priority(int32_t priority)
   {

      return (::SetThreadPriority(::GetCurrentThread(),priority) != 0);
   }


   CLASS_DECL_AURA int32_t thread_priority()
   {
      return ::GetThreadPriority(::GetCurrentThread());
   }


} // namespace aura







bool on_init_thread()
{

   //attach_thread_input_to_main_thread();

   if(!__os_init_thread())
      return false;

   return true;

}


bool on_term_thread()
{

   bool bOk1 = __os_term_thread();

   return bOk1;

}







//CLASS_DECL_AURA IDTHREAD get_current_thread_id()
//{
//   return ::GetCurrentThreadId();
//}




CLASS_DECL_AURA DWORD_PTR translate_processor_affinity(int iOrder)
{

   return 1 << iOrder;

}



namespace multithreading
{

#ifndef __APPLE__

   CLASS_DECL_AURA int32_t priority()
   {

      int32_t iPolicy = SCHED_OTHER;

      sched_param schedparam = {};

      pthread_getschedparam(pthread_self(), &iPolicy, &schedparam);

      return thread_get_scheduling_priority(iPolicy, &schedparam);

   }

#endif

} // namespace multithreading

