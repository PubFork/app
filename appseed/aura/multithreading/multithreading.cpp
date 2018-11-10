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

      ::aura::del(s_pthreadptra);

      ::aura::del(s_piaThread);

      ::aura::del(s_pmutex);

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


   CLASS_DECL_AURA uint32_t __on_thread_finally(thread * pthreadParam)
   {

      int nExitCode = -1;

      if (::is_null(pthreadParam))
      {

         return -1;

      }

      {

         sp(::thread) pthread = pthreadParam;

         try
         {

            {

               synch_lock sl(pthread->m_pmutex);

               if (pthread->m_pevSleep.is_set())
               {

                  pthread->m_pevSleep->SetEvent();

                  pthread->m_pevSleep.release();

               }

            }

            __node_term_thread(pthread);

            ::multithreading::__node_on_term_thread(pthread);

            ::aura::application * papp = pthread->get_app();

            try
            {

               nExitCode = pthread->m_error.get_exit_code();

            }
            catch (...)
            {

            }

            try
            {

               pthread->m_idroute.remove_all();

            }
            catch(...)
            {

            }

            try
            {

               pthread->release_parents();

            }
            catch (...)
            {

            }

            pthread->set_os_data(NULL);

            __end_thread(papp);

         }
         catch(...)
         {

         }

      }

      try
      {

         ::release(pthreadParam);

      }
      catch(...)
      {

      }

      set_thread_off(::GetCurrentThreadId());

      return nExitCode;

   }


} // namespace multithreading





thread_pointer < u64 > t_pflags;


u64 & thread_flags()
{

   if (t_pflags == NULL)
   {

      t_pflags = new u64;

      *t_pflags = 0ULL;

   }

   return *t_pflags;

}


CLASS_DECL_AURA void thread_set_flag(u64 uFlag, bool bSet)
{

   auto & u = thread_flags();

   if (bSet)
   {

      u |= uFlag;

   }
   else
   {

      u &= ~uFlag;

   }

}


CLASS_DECL_AURA void thread_set_fast_path(bool bFastPath)
{

   thread_set_flag(THREAD_FLAGS_FAST_PATH, bFastPath);

}


CLASS_DECL_AURA bool thread_is_fast_path()
{

   return (thread_flags() & THREAD_FLAGS_FAST_PATH) != 0ULL;

}


CLASS_DECL_AURA void thread_set_zip_is_dir(bool bZipIsDir)
{

   thread_set_flag(THREAD_FLAGS_ZIP_IS_DIR, bZipIsDir);

}


CLASS_DECL_AURA bool thread_zip_is_dir()
{

   return (thread_flags() & THREAD_FLAGS_ZIP_IS_DIR) != 0ULL;

}



thread_pointer < ::thread > t_pthread;

::thread * get_thread()
{

   if (t_pthread == NULL)
   {

      t_pthread = new thread(::aura::system::g_p);

   }

   return t_pthread;

}


CLASS_DECL_AURA ::thread * get_thread_raw()
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


   CLASS_DECL_AURA bool post_quit_and_wait(const duration & duration)
   {

      return post_quit_and_wait(t_pthread, duration);

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


   bool post_quit_and_wait(::thread * pthreadParam, const duration & duration)
   {

      sp(::thread) pthread;

      try
      {

         pthread = pthreadParam;

      }
      catch (...)
      {

         return true;

      }

      if (pthread.is_null())
      {

         return true;

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

         return pthread->wait(duration).succeeded();

      }
      catch (...)
      {

      }

      return true;

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

            /// this is quite dangerous
            //synch_lock slThread(pthread->m_pmutex);

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






