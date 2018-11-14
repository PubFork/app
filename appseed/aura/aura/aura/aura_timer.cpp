#include "framework.h"


timer::timer(::aura::application * papp, uint_ptr uiTimer, PFN_TIMER pfnTimer, void * pvoidData, sync_object * pmutex) :
   ::object(papp)
{

   impl_init();

   m_nIDEvent = uiTimer;

   m_pfnTimer = pfnTimer;

   m_pvoidData = pvoidData;

   ::aura::del(m_pmutex);

   m_pmutex = pmutex;

   m_pcallback = NULL;

}


timer::~timer()
{

   stop();

   impl_term();

   m_pmutex = NULL;

}


bool timer::start(int millis, bool bPeriodic)
{

   synch_lock sl(m_pmutex);

   m_bPeriodic = bPeriodic;

   m_dwMillis = millis;

   if(m_ptimerRunning.is_set())
   {

      return true;

   }

   m_ptimerRunning = this;

   try
   {

      if(!impl_start())
      {

         m_ptimerRunning.release();

         return false;

      }

   }
   catch(...)
   {

      m_ptimerRunning.release();

      return false;

   }

   return true;

}


void timer::stop()
{

   try
   {

      post_quit();

   }
   catch(...)
   {

   }

   try
   {

      if (m_pcallback != NULL)
      {

         m_pcallback->children_remove(this);

         m_pcallback = NULL;

      }

   }
   catch (...)
   {

   }

}


void timer::call_on_timer()
{

   bool bRepeat = true;
   
   thread_set_is_timer();

   try
   {

      if(!thread_get_run())
      {

         bRepeat = false;

      }

   }
   catch(...)
   {

      bRepeat = false;

   }

   if(bRepeat)
   {

      ::set_thread(this);

      m_bTemporary = true;

      try
      {

         on_timer();

      }
      catch(...)
      {

      }

   }

   if(bRepeat)
   {

      try
      {

         if (m_bPeriodic)
         {

            if(!impl_restart())
            {

               bRepeat = false;

            }

         }
         else
         {

            bRepeat = false;

         }

      }
      catch (...)
      {

         bRepeat = false;

      }

   }

   if(!bRepeat)
   {

      try
      {
         
         m_ptimerRunning->release_parents();

         m_ptimerRunning.release();

      }
      catch(...)
      {

      }

   }

}


void timer::on_timer()
{

   m_bRet = false;

   if (m_pfnTimer != NULL)
   {

      m_pfnTimer(this);

      return;

   }

   if (m_pcallback != NULL)
   {

      m_pcallback->on_timer(this);

      return;

   }

}


void timer::children_add(::aura::application * papp)
{
   
}


void timer::wait_quit(duration durationTimeout)
{

   Sleep(10);
   

}

void timer::safe_pre_term()
{
   
   release_parents();
   
}

void timer::post_quit()
{
   
   try
   {
      
      if(m_bRunThisThread)
      {
         
         m_bRunThisThread = false;
         
      }
      
   }
   catch (...)
   {
   
   }
   
}



