// Thank you TBS!!

VOID CALLBACK aura_timer_TimerRoutine(PVOID lpParam, BOOLEAN TimerOrWaitFired);



bool timer::impl_start()
{
   
   
   
   m_bSet = true;
   
   if(!CreateTimerQueueTimer(&m_ptimer->m_hTimer,m_ptimer->m_hTimerQueue,(WAITORTIMERCALLBACK)aura_timer_TimerRoutine,m_ptimer,m_dwMillis,0,WT_EXECUTEONLYONCE | WT_EXECUTELONGFUNCTION))
   {
      
      m_bSet = false;
      
      return false;
      
   }
   
   return true;

   
}


      
      
      Timer()
      {
         
         m_hTimer = NULL;
         
         m_ptimer = NULL;
         
         m_hTimerQueue = CreateTimerQueue();
         
         if(NULL == m_hTimerQueue)
         {
            
            throw - 1;
            
         }
         
      }
      
      ~Timer()
      {
         
         stop(false);
         
         if(m_hTimerQueue != NULL && m_hTimerQueue != INVALID_HANDLE_VALUE)
         {
            
            DeleteTimerQueue(m_hTimerQueue);
            
         }
         
      }
      
      
      void stop(bool bWaitCompletion)
      {
         
         if(m_hTimerQueue != NULL && m_hTimer != NULL)
         {
            
            DeleteTimerQueueTimer(m_hTimerQueue,m_hTimer, bWaitCompletion ? INVALID_HANDLE_VALUE : NULL);
            
            m_hTimer = NULL;
            
         }
         
      }
      
   };
   
}


bool timer::impl_restart()
{
   
DeleteTimerQueueTimer(m_ptimer->m_hTimerQueue, m_ptimer->m_hTimer, NULL);

if(!CreateTimerQueueTimer(&m_ptimer->m_hTimer,m_ptimer->m_hTimerQueue,(WAITORTIMERCALLBACK)aura_timer_TimerRoutine,m_ptimer,m_dwMillis,0,WT_EXECUTEONLYONCE | WT_EXECUTELONGFUNCTION))
{
   
   return false;
   
}



}






VOID CALLBACK aura_timer_TimerRoutine(PVOID lpParam, BOOLEAN TimerOrWaitFired)
{
   
   if (!g_bAura)
   {
      output_debug_string("there is timer on (aura_timer_TimerRoutine) and aura is going away (!g_bAura)\n");
      return;
   }
   
   ::aura::Timer * ptimer = (::aura::Timer *)lpParam;
   
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
      
      ptimer->m_ptimer->call_on_timer();
      
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
   
   if (!bOk)
   {
      
      ::aura::del(ptimer);
      
   }
   
}
