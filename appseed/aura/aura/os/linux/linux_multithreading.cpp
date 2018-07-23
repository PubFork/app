#include "framework.h"
//#include <sched.h>





void get_os_priority(int32_t * piPolicy, sched_param * pparam, int32_t nCa2Priority);



namespace process
{

   CLASS_DECL_AURA bool set_priority(int32_t priority)
	{

      int32_t iPolicy = SCHED_OTHER;

      sched_param schedparam;

      schedparam.sched_priority = 0;

      get_os_priority(&iPolicy, &schedparam, priority);

      sched_setscheduler(0, iPolicy, &schedparam);

      return true;

	}




} // namespace core




























void __node_init_thread()
{

}

void __node_term_thread()
{

}














bool __os_init_thread()
{


   //__clear_mq();

   return true;

}



bool __os_term_thread()
{

   __clear_mq();
   thread_shutdown();

   return true;

}






int get_current_process_affinity_order()
{

   return get_processor_count();

}






#if defined(RASPBIAN)

::thread_object < _TEB > t_pteb;

struct _TEB * WINAPI NtCurrentTeb(void)
{

   return t_pteb;

}

#endif


   #include <sys/time.h>



uint64_t get_nanos()
{


   #ifdef RASPBIAN

   struct timeval tv;

   if(gettimeofday(&tv, NULL) != 0)
   {

      return 0;

   }

   return tv.tv_sec * 1000 * 1000 * 1000 + tv.tv_usec * 1000;

   #else
   struct timespec ts;
   if (clock_gettime(CLOCK_REALTIME, &ts) != 0)
   {
      //error
      return 0;
   }

   return ts.tv_sec * 1000 * 1000 * 1000 + ts.tv_nsec;
   #endif

}
