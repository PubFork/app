#include "framework.h"
#include "aura/aura/os/os.h"
#include "aura/aura/os/os_os.h"


namespace multithreading
{


   CLASS_DECL_AURA comparable_eq_array<IDTHREAD> * s_piaThread = NULL;
   CLASS_DECL_AURA pointer_array < ::thread * > * s_pthreadptra = NULL;
   CLASS_DECL_AURA mutex * s_pmutex = NULL;


   CLASS_DECL_AURA void init_multithreading()
   {
      s_pmutex = new mutex(NULL);
      s_piaThread = new comparable_eq_array<IDTHREAD>;
      s_pthreadptra = new pointer_array < ::thread * >;

      __node_init_multithreading();

   }


   CLASS_DECL_AURA void term_multithreading()
   {

      __node_term_multithreading();

      delete s_pthreadptra;
      s_pthreadptra = NULL;

      delete s_piaThread;
      s_piaThread = NULL;

      delete s_pmutex;
      s_pmutex = NULL;

   }

   CLASS_DECL_AURA void __node_on_init_thread(thread * pthread)
   {

      synch_lock sl(s_pmutex);

      ::set_thread(pthread);

      processor_cache_oriented_set_thread_memory_pool(0); // set default handler cache oriented thread memory pool index to 0 ("zero") (The First One)

      __init_thread();

      s_piaThread->add(pthread->get_os_int());

      s_pthreadptra->add(pthread);

   }


   CLASS_DECL_AURA void __node_on_term_thread(thread * pthread)
   {

      synch_lock sl(s_pmutex);

      s_piaThread->remove(pthread->get_os_int());

      s_pthreadptra->remove(pthread);

      __term_thread();

   }


   CLASS_DECL_AURA uint32_t __on_thread_finally(thread * thread)
   {

      int nExitCode = -1;

      if (thread == NULL)
      {

         return -1;

      }

      {

         sp(::thread) pthread = thread;

         try
         {

            pthread->unregister_from_required_threads();

         }
         catch(...)
         {


         }

         try
         {

            synch_lock sl(pthread->m_pmutex);

            for (auto pobject : pthread->m_objectptraDependent)
            {

               pobject->threadrefa_remove(pthread);

            }

         }
         catch (...)
         {

         }

         try
         {

            pthread->threadrefa_post_quit();

         }
         catch (...)
         {

         }

         try
         {

            pthread->threadrefa_wait(one_minute());

         }
         catch (...)
         {

         }

         try
         {

            __node_term_thread(pthread);

            ::multithreading::__node_on_term_thread(pthread);

            ::aura::application * papp = pthread->get_app();

            nExitCode = pthread->m_error.get_exit_code();

            try
            {

               pthread->m_idroute.remove_all();

            }
            catch(...)
            {

            }

            try
            {

               pthread->thread_term();

            }
            catch(...)
            {

            }

            __end_thread(papp);

         }
         catch(...)
         {

         }

      }

      try
      {

         ::release(thread);

      }
      catch(...)
      {

      }

      set_thread_off(::GetCurrentThreadId());

      return nExitCode;

   }


} // namespace multithreading




thread_pointer < ::thread > t_pthread;




::thread * get_thread()
{

   return t_pthread;

}

bool get_thread_run()
{

   if(t_pthread == NULL) // system threads don't have generally associated ca2 thread object
   {
      // and have short life, so it is safe to keep it running
      return true;

   }

   try
   {

      return t_pthread->thread_get_run();

   }
   catch (...)
   {

   }

   return false;

}


namespace multithreading
{


   CLASS_DECL_AURA void post_quit()
   {

      post_quit(t_pthread);

   }


   CLASS_DECL_AURA void post_quit_and_wait(const duration & duration)
   {

      post_quit_and_wait(t_pthread, duration);

   }



   void post_quit(::thread * pthread)
   {

      if (pthread == NULL)
      {

         return;

      }

      try
      {

         pthread->post_quit();

      }
      catch (...)
      {


      }

   }


   void post_quit_and_wait(::thread * pthread, const duration & duration)
   {

      if (pthread == NULL)
      {

         return;

      }

      try
      {

         pthread->post_quit();

      }
      catch (...)
      {

      }

      try
      {

         if (pthread != NULL)
         {

            pthread->wait(duration).succeeded();

         }

      }
      catch (...)
      {

      }

   }




} // namespace multithreading



void set_thread(::thread* pthread)
{

   t_pthread = pthread;

}





thread* __begin_thread(::aura::application * papp,__THREADPROC pfnThreadProc,LPVOID pParam,int32_t epriority,UINT nStackSize,uint32_t dwCreateFlags,LPSECURITY_ATTRIBUTES lpSecurityAttrs, IDTHREAD * puiId, error * perror)
{

   ASSERT(pfnThreadProc != NULL);

   thread* pThread = canew(thread(papp,pfnThreadProc,pParam));

   ASSERT_VALID(pThread);

   if(!pThread->create_thread(epriority,nStackSize, dwCreateFlags,lpSecurityAttrs, puiId, perror))
   {

      pThread->Delete();

      return NULL;

   }

   return pThread;

}







//mutex & user_mutex()
//{
//
//   //static mutex * s_pmutexUser = new mutex();
//
//   //return *s_pmutexUser;
//   return *((mutex *)NULL);
//
//}

mutex * s_pmutexMessageDispatch = NULL;

mutex & message_dispatch_mutex()
{


   return *s_pmutexMessageDispatch;

}



::aura::application * get_app()
{

   thread * pthread = get_thread();

   if(pthread == NULL)
      return NULL;

   return pthread->get_app();

}




void do_events()
{

   ::thread * pthread = ::get_thread();

   if(pthread == NULL)
      return;

   pthread->do_events();

}


void do_events(const duration & duration)
{

   ::thread * pthread = ::get_thread();

   if(pthread == NULL)
      return;

   pthread->do_events(duration);

}



void thread_ptra::post_quit()
{

   try
   {

      synch_lock sl(m_pmutex);

      for (index i = 0; i < get_count(); i++)
      {

         ::thread * pthread = element_at(i);

         try
         {

            synch_lock slThread(pthread->m_pmutex);

            pthread->post_quit();

         }
         catch (...)
         {

            remove(pthread);

            break;

         }

      }

   }
   catch (...)
   {

   }

}


::count thread_ptra::get_count_except_current_thread()
{

   thread * pthread = ::get_thread();

   ::count c = 0;

   for(index i = 0; i < spa(thread)::get_count(); i++)
   {

      ::thread * pthreadItem = element_at(i);

      if(pthreadItem != pthread && pthreadItem != NULL)
      {

         TRACE("\nthread_ptra::get_count_except_current_thread %s", typeid(*pthreadItem).name());

         c++;

      }

   }

   return c;

}


void thread_ptra::wait(const duration & duration, synch_lock & sl)
{

   ::datetime::time timeEnd = ::datetime::time::get_current_time() + MAX(seconds(2), duration);

   try
   {

//      synch_lock sl(psyncParent);
//
      ::count cCount = get_count_except_current_thread();

      ::datetime::time timeNow = ::datetime::time::get_current_time();

      while (cCount > 0 &&  timeNow < timeEnd)
      {

         sl.unlock();

         timeNow = ::datetime::time::get_current_time();

         cCount = get_count_except_current_thread();

         Sleep(500);

         sl.lock();

      }

   }
   catch (...)
   {

   }

}



