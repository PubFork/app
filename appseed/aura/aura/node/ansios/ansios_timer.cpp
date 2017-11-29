#include "framework.h"



#include <signal.h>
#include <time.h>




void aura_timer_handler(sigval sigval);


void timer::impl_init()
{

   ZERO(m_sev);

   m_sev.sigev_notify = SIGEV_THREAD;

   m_sev.sigev_signo = 0;

   m_sev.sigev_value.sival_ptr = this;

   m_sev.sigev_notify_function = aura_timer_handler;

   if (timer_create(CLOCK_REALTIME, &m_sev, &m_timerid) == -1)
      _throw(- 1);

}




bool timer::impl_start()
{
/* Start the timer */

itimerspec & its = m_its;

its.it_value.tv_sec = m_dwMillis / 1000; // expiration

its.it_value.tv_nsec = (m_dwMillis * 1000 * 1000) % (1000 * 1000 * 1000); // expiration


/*if (bPeriodic)
 {

 /// This is not used because overrun.
 /// The timer will may create new threads, and it maybe a lot of threads, besides the previous triggered threads did not finished their work.

 its.it_interval.tv_sec = millis / 1000; // freq period

 its.it_interval.tv_nsec = (millis * 1000 * 1000) % (1000 * 1000 * 1000); // freq period

 }
 else*/
{

   its.it_interval.tv_sec = 0; // no freq

   its.it_interval.tv_nsec = 0; // no freq

}

m_bSet = true;

if (timer_settime(m_timerid, 0, &its, NULL) == -1)
{

   m_bSet = false;

   return false;

}

return true;

}


void timer::impl_term()
{

   timer_delete(m_timerid);

}


void timer::impl_stop(bool bWaitCompletion)
{

   UNREFERENCED_PARAMETER(bWaitCompletion);

   timer_settime(m_timerid, 0, NULL, NULL);

}




bool timer::impl_restart()
{


   if (timer_settime(m_timerid, 0, &m_its, NULL) == -1)
         return false;

   return true;

}





void aura_timer_handler(sigval sigval)
{

   ::timer * ptimer = (::timer *)sigval.sival_ptr;

   try
   {

      ptimer->call_on_timer();

   }
   catch(...)
   {

   }

}




