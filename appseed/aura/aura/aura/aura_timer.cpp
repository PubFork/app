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

   m_ptimerRunning = NULL;

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

   if(m_ptimerRunning != NULL)
   {

      return true;

   }

   m_ptimerRunning = this;

   try
   {

      if(!impl_start())
      {

         m_ptimerRunning = NULL;

         return false;

      }

   }
   catch(...)
   {

      m_ptimerRunning = NULL;

      return false;

   }

   register_at_required_threads();

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

         m_pcallback->threadrefa_remove(this);

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

      //try
      //{

      //   // intentionally may repeat the operation
      //   post_quit();

      //}
      //catch(...)
      //{

      //}

      try
      {

         unregister_from_required_threads();

      }
      catch(...)
      {

      }

      try
      {

         synch_lock sl(m_pmutex);

         for (auto pobject : m_objectptraDependent)
         {

            pobject->threadrefa_remove(this);

         }

      }
      catch (...)
      {

      }


      try
      {

         m_ptimerRunning = NULL;

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



