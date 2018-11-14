#pragma once



CLASS_DECL_AURA HTHREAD start_thread(uint32_t (*)(void *), void * pv, int32_t iPriority = 0);

CLASS_DECL_AURA HTHREAD create_thread(LPSECURITY_ATTRIBUTES lpsa, uint_ptr cbStack, uint32_t (*)(void *), void * pv, uint32_t uiFlags, IDTHREAD * puiId);




CLASS_DECL_AURA IDTHREAD get_current_thread_id();


class error;

CLASS_DECL_AURA thread* __begin_thread(::aura::application * papp,__THREADPROC pfnThreadProc,LPVOID pParam,int32_t epriority = ::multithreading::priority_normal,UINT nStackSize = 0,uint32_t dwCreateFlags = 0,LPSECURITY_ATTRIBUTES lpSecurityAttrs = NULL, IDTHREAD * puiId = NULL, error * perror = NULL);

template < class T >
T * c_new(T * p)
{
   p->m_ulFlags |= (uint64_t) ::object::flag_heap_alloc;
   return p;
}

#define cnew(x) c_new(new x)

template < class THREAD_TYPE >
THREAD_TYPE * __begin_thread(::aura::application * papp,int32_t epriority = ::multithreading::priority_normal,UINT nStackSize = 0,uint32_t dwCreateFlags = 0,LPSECURITY_ATTRIBUTES lpSecurityAttrs = NULL, IDTHREAD * puiId = NULL)
{

   THREAD_TYPE * pthread = new THREAD_TYPE(papp);

   pthread->begin(epriority,nStackSize,dwCreateFlags,lpSecurityAttrs, puiId);

   return pthread;

}


CLASS_DECL_AURA HTHREAD get_current_thread();





CLASS_DECL_AURA bool on_init_thread();
CLASS_DECL_AURA bool on_term_thread();


CLASS_DECL_AURA void __init_thread();
CLASS_DECL_AURA void __term_thread();


CLASS_DECL_AURA bool __os_init_thread();
CLASS_DECL_AURA bool __os_term_thread();


CLASS_DECL_AURA bool __node_init_thread(::thread * pthread);
CLASS_DECL_AURA bool __node_term_thread(::thread * pthread);


CLASS_DECL_AURA void __init_threading_count();
CLASS_DECL_AURA void __term_threading_count();


CLASS_DECL_AURA void __inc_threading_count();
CLASS_DECL_AURA void __dec_threading_count();


class CLASS_DECL_AURA keep_threading_count
{
public:


   keep_threading_count()
   {

      __inc_threading_count();

   }


   ~keep_threading_count()
   {

      __dec_threading_count();

   }


};


#define THREAD_FLAGS_FAST_PATH 1ULL
#define THREAD_FLAGS_ZIP_IS_DIR 2ULL
#define THREAD_FLAGS_IS_TIMER 4ULL

CLASS_DECL_AURA u64 & thread_flags();
CLASS_DECL_AURA void thread_set_flag(u64 uFlag, bool bSet = true);
CLASS_DECL_AURA void thread_set_fast_path(bool bFastPath = true);
CLASS_DECL_AURA bool thread_is_fast_path();
CLASS_DECL_AURA void thread_set_zip_is_dir(bool bZipIsDir = true);
CLASS_DECL_AURA bool thread_zip_is_dir();
CLASS_DECL_AURA void thread_set_is_timer(bool bIsTimer = true);
CLASS_DECL_AURA bool thread_is_timer();


CLASS_DECL_AURA bool __wait_threading_count(::duration dur);
CLASS_DECL_AURA bool __wait_threading_count_except(::thread * pthread,::duration dur);


CLASS_DECL_AURA ::thread * get_thread();
CLASS_DECL_AURA void set_thread(::thread * pthread);


CLASS_DECL_AURA bool get_thread_run();

CLASS_DECL_AURA void __node_init_multithreading();
CLASS_DECL_AURA void __node_term_multithreading();



namespace multithreading
{


   CLASS_DECL_AURA void init_multithreading();
   CLASS_DECL_AURA void term_multithreading();

   CLASS_DECL_AURA void __node_on_init_thread(thread * pthread);
   CLASS_DECL_AURA void __node_on_term_thread(thread * pthread);

   CLASS_DECL_AURA uint32_t __on_thread_finally(thread * pthread);

   CLASS_DECL_AURA extern comparable_eq_array <IDTHREAD> * s_piaThread;
   CLASS_DECL_AURA extern pointer_array < ::thread * > * s_pthreadptra;
   CLASS_DECL_AURA extern mutex * s_pmutex;


} // namespace multithreading



CLASS_DECL_AURA void __end_thread(::aura::application * papp);

CLASS_DECL_AURA void __term_thread(::aura::application * papp);






#ifdef WINDOWS

///  \brief    global function to wait on a object item for a specified time
///  \param    waitableItem item to wait for (can be event, socket, file, semaphore, ...)
///  \param    duration time period to wait for item (default: infinite)
///  \return   result of waiting action as defined in wait_result
inline wait_result wait(event_base & waitableItem,const duration & duration = duration::infinite())
{
   return waitableItem.wait(duration);
}

///  \brief    global function to wait on a object item for a specified time
///  \param    waitableItem item to wait for (item can be thread, event, socket, file, semaphore, ...)
///  \param    duration time period to wait for item (default: infinite)
///  \return   result of waiting action as defined in wait_result
wait_result wait(size_t numberOfItems,event_base * waitableItems[],const duration & duration = duration::infinite(),bool waitForAll = false);

#else

///  \brief    global function to wait on a object item for a specified time
///  \param    waitableItem item to wait for (can be event, socket, file, semaphore, ...)
///  \param    duration time period to wait for item (default: infinite)
///  \return   result of waiting action as defined in wait_result
wait_result wait(event_base & waitableItem,const duration & duration = duration::infinite());

///  \brief    global function to wait on a object item for a specified time
///  \param    waitableItem item to wait for (item can be thread, event, socket, file, semaphore, ...)
///  \param    duration time period to wait for item (default: infinite)
///  \return   result of waiting action as defined in wait_result
wait_result wait(size_t numberOfItems,event_base * waitableItems[],const duration& duration = duration::infinite(),bool waitForAll = false);

#endif




CLASS_DECL_AURA void thread_alloc_ready(bool bReady);









//CLASS_DECL_AURA mutex & user_mutex();
CLASS_DECL_AURA mutex & message_dispatch_mutex();




typedef void SIMPLE_PROCEDURE(void);
typedef SIMPLE_PROCEDURE * PPROC_SIMPLE;

CLASS_DECL_AURA extern PPROC_SIMPLE g_axisoninitthread;
CLASS_DECL_AURA extern PPROC_SIMPLE g_axisontermthread;
