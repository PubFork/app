#include "framework.h"



typedef uint32_t THREAD_FUNCTION(void *);
typedef THREAD_FUNCTION * PFN_THREAD_FUNCTION;



CLASS_DECL_AURA PPROC_SIMPLE g_axisoninitthread = NULL;
CLASS_DECL_AURA PPROC_SIMPLE g_axisontermthread = NULL;



struct create_thread_data :
   virtual public simple_object
{

   PFN_THREAD_FUNCTION     m_pfn;

   void *                  m_pv;

   create_thread_data(PFN_THREAD_FUNCTION pfn, void * pv)
   {
      m_pfn = pfn;
      m_pv = pv;
   }
#ifdef WINDOWS
   static DWORD WINAPI os_thread_proc(void * p)
   {
      return (DWORD)proc(p);
   }
#else
   static void * os_thread_proc(void * p)
   {
      return (void *)(int_ptr) proc(p);
   }
#endif


   static int32_t proc(void * p)
   {

      sp(create_thread_data) pdata((const LPARAM &) p);

      if (g_axisoninitthread)
      {
         g_axisoninitthread();

      }

      if(!on_init_thread())
      {

         return -34;

      }

      int32_t iRet = pdata->m_pfn(pdata->m_pv);

      try
      {
         if (g_axisontermthread)
         {
            g_axisontermthread();

         }

         on_term_thread();

      }
      catch(...)
      {
      }

      return iRet;

   }


};


CLASS_DECL_AURA HTHREAD create_thread(LPSECURITY_ATTRIBUTES lpsa,uint_ptr cbStack,PFN_THREAD_FUNCTION pfn,void * pv,uint32_t uiFlags,IDTHREAD * puiId)
{

#ifdef WINDOWS

   DWORD dwId = 0;

   sp(::create_thread_data) posthreaddata = canew(create_thread_data(pfn, pv));

   HTHREAD hthread = CreateThread(lpsa,cbStack,&create_thread_data::os_thread_proc, (LPVOID)(::lparam)posthreaddata, uiFlags, &dwId);

   if(hthread == NULL)
   {

      return NULL;

   }

   try
   {
      if(puiId != NULL)
      {
         *puiId = (IDTHREAD) dwId;
      }
   }
   catch(...)
   {
   }

   return hthread;
#else

   pthread_t thread;

   pthread_attr_t threadAttr;

   pthread_attr_init(&threadAttr);

   if(cbStack > 0)
   {

      pthread_attr_setstacksize(&threadAttr,120 * 1024); // Set the stack size of the thread

   }

   //int iPolicy;

   //sched_param schedparam; // scheduling priority

   //thread_get_os_priority(&iPolicy,&schedparam,nPriority);

   //pthread_attr_setschedpolicy(&threadAttr,iPolicy);

   //pthread_attr_setschedparam(&threadAttr,&schedparam);

   pthread_attr_setdetachstate(&threadAttr,PTHREAD_CREATE_DETACHED); // Set thread to detached state. No need for pthread_join

   pthread_create(&thread,&threadAttr,&create_thread_data::os_thread_proc,(LPVOID)new create_thread_data(pfn,pv)); // Create the thread

   if(puiId != NULL)
   {

      *puiId = thread;

   }

   return thread;

#endif

}




