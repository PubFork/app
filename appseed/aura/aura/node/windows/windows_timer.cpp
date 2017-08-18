#include "framework.h"
// Thank you TBS!!

VOID CALLBACK aura_timer_TimerRoutine(PVOID lpParam, BOOLEAN TimerOrWaitFired);



bool timer::impl_start()
{
   
   
   
   m_bSet = true;
   
   if(!CreateTimerQueueTimer(&m_hTimer,m_hTimerQueue,(WAITORTIMERCALLBACK)aura_timer_TimerRoutine,this,m_dwMillis,0,WT_EXECUTEONLYONCE | WT_EXECUTELONGFUNCTION))
   {
      
      m_bSet = false;
      
      return false;
      
   }
   
   return true;

   
}
      
      
void timer::impl_init()
{
         
   m_hTimer = NULL;
         
   m_hTimerQueue = CreateTimerQueue();
         
   if(NULL == m_hTimerQueue)
   {
            
      throw - 1;
            
   }
         
}
      
void timer::impl_term()
{
         
   stop(false);
         
   if(m_hTimerQueue != NULL && m_hTimerQueue != INVALID_HANDLE_VALUE)
   {
            
      DeleteTimerQueue(m_hTimerQueue);
            
   }
         
}
      
      
void timer::impl_stop(bool bWaitCompletion)
{
         
   if(m_hTimerQueue != NULL && m_hTimer != NULL)
   {
            
      DeleteTimerQueueTimer(m_hTimerQueue,m_hTimer, bWaitCompletion ? INVALID_HANDLE_VALUE : NULL);
            
      m_hTimer = NULL;
            
   }
         
}
      


bool timer::impl_restart()
{
   
   DeleteTimerQueueTimer(m_hTimerQueue, m_hTimer, NULL);

   if(!CreateTimerQueueTimer(&m_hTimer,m_hTimerQueue,(WAITORTIMERCALLBACK)aura_timer_TimerRoutine,this,m_dwMillis,0,WT_EXECUTEONLYONCE | WT_EXECUTELONGFUNCTION))
   {
   
      return false;
   
   }

   return true;

}






VOID CALLBACK aura_timer_TimerRoutine(PVOID lpParam, BOOLEAN TimerOrWaitFired)
{
   
   if (!g_bAura)
   {
      output_debug_string("there is timer on (aura_timer_TimerRoutine) and aura is going away (!g_bAura)\n");
      return;
   }
   
   ::timer * ptimer = (::timer *)lpParam;
   
   if (g_axisoninitthread)
   {

      g_axisoninitthread();
      
   }
   
   on_init_thread();
   
   //if (!on_init_thread())
   //{
   //   ::aura::del(ptimer);
   //   //return -34;
   //   return;
   
   //}
   
   bool bOk = false;
   
   try
   {
      
      ptimer->call_on_timer();
      
      bOk = true;
      
   }
   catch (::exception::base &)
   {
      
   }
   catch (...)
   {
      
   }
   
   try
   {
      
      if (g_axisontermthread)
      {
         g_axisontermthread();
         
      }
      
      on_term_thread();
      
   }
   catch (...)
   {
      
   }
   
   
}
