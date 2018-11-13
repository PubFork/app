// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Copyright (c) Microsoft Corporation. All rights reserved.
#include "framework.h"
#include "metrowin.h"

#undef System

#pragma push_macro("System")
#undef System
using namespace Windows::Foundation;
using namespace Windows::System::Threading;
#pragma pop_macro("System")


mutex * g_pmutexThreadIdHandleLock = NULL;
mutex * g_pmutexThreadIdLock = NULL;


thread_data::thread_data()
{

   m_dwIndex = thread_alloc();

}


thread_data::~thread_data()
{

   thread_free(m_dwIndex);

}


void * thread_data::get()
{

   return tls_get_value(m_dwIndex);

}


void thread_data::set(void * p)
{

   thread_set_data(m_dwIndex,(LPVOID)p);

}


// Converts a Win32 thread priority to WinRT format.
WorkItemPriority GetWorkItemPriority(int nPriority)
{
   if (nPriority < 0)
      return WorkItemPriority::Low;
   else if (nPriority > 0)
      return WorkItemPriority::High;
   else
      return WorkItemPriority::Normal;
}


HTHREAD start_thread(uint32_t ( * pfn)(void *), void * pv, int iPriority)
{

   UNREFERENCED_PARAMETER(iPriority);

   return create_thread(NULL, 0, pfn, pv, 0, NULL);

}


void attach_thread_input_to_main_thread(int_bool bAttach)
{

}


void _on_aura_thread_detach()
{

}


BOOL WINAPI PostThreadMessageW(IDTHREAD iThreadId,UINT message,WPARAM wparam,LPARAM lparam)
{

   mq * pmq = __get_mq(iThreadId, message != WM_QUIT);

   if(pmq == NULL)
   {

      return FALSE;

   }

   synch_lock ml(&pmq->m_mutex);

   MESSAGE msg;

   msg.hwnd       = NULL;
   msg.message    = message;
   msg.wParam     = wparam;
   msg.lParam     = lparam;
   msg.pt.x       = 0x80000000;
   msg.pt.y       = 0x80000000;
   msg.time       = -1;

   pmq->ma.add(msg);

   pmq->m_eventNewMessage.set_event();

   return true;

}


namespace multithreading
{


   bool set_priority(int32_t priority)
   {

      return ::SetThreadPriority(::GetCurrentThread(), priority) != FALSE;

   }


   int32_t priority()
   {

      return ::GetThreadPriority(::GetCurrentThread());

   }


} // namespace multithreading


bool on_init_thread()
{

   if(!__os_init_thread())
   {

      return false;

   }

   return true;

}


bool on_term_thread()
{

   bool bOk1 = __os_term_thread();

   return bOk1;

}


void __node_init_multithreading()
{

   __node_init_cross_windows_threading();

}


void __node_term_multithreading()
{

   __node_term_cross_windows_threading();

}

thread_int_ptr < HRESULT > t_hresultCoInitialize;

bool __os_init_thread()
{

   return true;

}


bool __os_term_thread()
{

   __clear_mq(true);

   thread_shutdown();

   if(SUCCEEDED(t_hresultCoInitialize))
   {

      CoUninitialize();

   }

   return true;

}


DWORD WinMsgWaitForMultipleObjects(DWORD dwSize,const HANDLE * lphandles,DWORD dwTimeout,DWORD dwWakeMask,DWORD dwFlags)
{

   HANDLE * ph = new HANDLE[dwSize + 1];

   memcpy(ph,lphandles,sizeof(HANDLE) *dwSize);

   ph[dwSize] = (HANDLE) __get_mq(get_current_thread_id(), true)->m_eventNewMessage.m_object;

   DWORD r = ::WaitForMultipleObjectsEx(dwSize + 1,ph,dwFlags & MWMO_WAITALL,dwTimeout,dwWakeMask & MWMO_ALERTABLE);

   delete ph;

   return r;

}


void _on_os_hthread_end()
{

}


IDTHREAD get_current_thread_id()
{

   return ::GetCurrentThreadId();

}


HTHREAD get_current_thread()
{

   return ::GetCurrentThread();

}


HTHREAD g_hMainThread = NULL;
UINT g_uiMainThread = -1;


void set_main_thread(HTHREAD hThread)
{

   g_hMainThread = hThread;

}


void set_main_thread_id(UINT uiThread)
{

   g_uiMainThread = uiThread;

}


HTHREAD get_main_thread()
{

   return g_hMainThread;

}


UINT   get_main_thread_id()
{

   return g_uiMainThread;

}



