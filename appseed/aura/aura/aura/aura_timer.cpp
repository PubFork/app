#include "framework.h"


timer::timer(::aura::application * papp, uint_ptr uiTimer, PFN_TIMER pfnTimer, void * pvoidData, mutex * pmutex) :
   ::object(papp)
{
   
   impl_init();
   
   m_nIDEvent = uiTimer,
   m_pfnTimer = pfnTimer,
   m_pvoidData = pvoidData;
   m_pmutex = pmutex;
   
   m_bDestroying = false;
   m_pcallback = NULL;
   
   m_bRet = false;
   m_bKill = false;
   m_bDeal = false;
   
}


timer::~timer()
{
   
   stop(true);
   
   impl_term();
   
   m_pmutex = NULL;
   
}




bool timer::start(int millis, bool bPeriodic)
{
   
   if(m_bSet)
   {
      
      stop(true);
      
   }
   
   m_bPeriodic = bPeriodic;
   
   m_dwMillis = millis;
   
   if(!impl_start())
   {
      
      return false;
      
   }
   
   
   return true;
   
}





void timer::stop(bool bWaitCompletion)
{
   
   try
   {
      
      m_bKill = true;
      
   }
   catch (...)
   {
      
   }
   
   try
   {
      
      impl_stop(bWaitCompletion);
      
   }
   catch(...)
   {
      
   }
   
   
   
}


bool timer::call_on_timer()
{
   
   if(!g_bAura)
   {
      
      output_debug_string("there is timer on (timer::call_on_timer) and aura has gone (!g_bAura)\n");
      
      return  false;
      
   }
   
   ::set_thread(this);
   
   try
   {
      
      synch_lock sl(m_pmutex);
      
      if (m_bKill || m_bDestroying || m_bDeal)
      {
         
         return true;
         
      }
      
      m_bDeal = true;
      
      m_bRet = false;
      
      sl.unlock();
      
      on_timer();
      
      if(!m_bPeriodic)
      {
         
         stop(false);
         
         post_quit();
         
      }
      
      /// pump any messages in queue
      MESSAGE msg;
      
      while(::PeekMessage(&msg,NULL,0,0,PM_NOREMOVE) != FALSE)
      {
         
         if(!thread_get_run() || !pump_message())
         {
            
            
            break;
            
         }
         
      }
      
      sl.lock();
      
      m_bDeal = false;
      
      if (!m_bPeriodic || m_bKill || !thread_get_run())
      {
         
         
         if (!m_bDestroying)
         {
            
            m_bDestroying = true;
            
            sl.unlock();
            
         }
         
         return false;
         
      }
      
      if (m_bPeriodic)
      {
         
         if(!impl_restart())
         {
            
            return false;
            
         }
            
         
      }
      
      return !m_bRet;
      
   }
   catch (...)
   {
      
   }
   
   return false;
   
}

bool timer::on_timer()
{
   
   if (m_pfnTimer != NULL)
   {
      
      if (!m_pfnTimer(this) && m_bPeriodic)
         return false;
      
   }
   
   if (m_pcallback != NULL)
   {
      
      m_pcallback->on_timer(this);
      
   }
   
   return !m_bRet;
   
}



