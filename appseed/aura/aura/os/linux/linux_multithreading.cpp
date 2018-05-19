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


namespace multithreading
{

   CLASS_DECL_AURA int32_t priority()
	{

      int32_t iPolicy = SCHED_OTHER;

      sched_param schedparam = {};

      pthread_getschedparam(pthread_self, &iPolicy, &schedparam);

      return thread_get_scheduling_priority(iPolicy, &schedparam);

	}


} // namespace multithreading



























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
