#include "framework.h" // previously aura/user/user.h


namespace aura
{


   timer_array::timer_array(::aura::application * papp):
      object(papp)
   {

      defer_create_mutex();

   }


   timer_array::~timer_array()
   {

      delete_all_timers(); // besides virtual

   }


   bool timer_array::create_timer(uint_ptr nIDEvent,UINT nEllapse, PFN_TIMER pfnTimer, bool bPeriodic, void * pvoidData)
   {

      if(nEllapse < 800)
      {

//         string str;
//
//         str.Format("creating fast timer: %d\n", nEllapse);
//
//         ::output_debug_string(str);

      }

      delete_timer(nIDEvent);

      synch_lock sl(m_pmutex);

      timer * ptimer = canew(timer(get_app(), nIDEvent, pfnTimer, pvoidData, m_pmutex));

      children_add(ptimer);

      ptimer->m_pcallback = this;

      m_map.set_at(nIDEvent, ptimer);

      sl.unlock();

      bool bOk = true;

      try
      {

         if(!ptimer->start(nEllapse,bPeriodic))
         {

            bOk = false;

         }

      }
      catch(...)
      {

         bOk = false;

      }

      if(!bOk)
      {

         delete_timer(nIDEvent);

      }

      return bOk;

   }


   bool timer_array::delete_timer(uint_ptr nIDEvent)
   {

      synch_lock sl(m_pmutex);

      MAP::pair * ppair = m_map.PLookup(nIDEvent);

      if (ppair == NULL)
      {

         return true;

      }

      auto ptimer = ppair->m_element2;

      m_map.remove_key(nIDEvent);

      ptimer->m_pmutex = NULL;

      ptimer->stop();

      sl.unlock();

      return true;

   }


   bool timer_array::on_timer(timer * ptimer)
   {

      if(ptimer->m_pcallback == this)
      {

         _001OnTimer(ptimer);

      }

      if(!ptimer->m_bPeriodic)
      {

         delete_timer(ptimer->m_nIDEvent);

      }

      return true;

   }


   void timer_array::_001OnTimer(::timer * ptimer)
   {

      if (m_pcallback != NULL)
      {

         m_pcallback->on_timer(ptimer);

      }

   }


   void timer_array::safe_pre_term()
   {

      delete_all_timers();

      ::timer_callback::safe_pre_term();

   }


   void timer_array::delete_all_timers()
   {

      {

         auto mapCopy = m_map;

         for(auto & pair : mapCopy)
         {

            pair.m_element2->post_quit();

         }

      }

      wait_quit(one_minute());

      MAP::pair * ppair = NULL;

restart:

      ppair = m_map.PGetFirstAssoc();

      if(ppair != NULL)
      {

         delete_timer(ppair->m_element1);

         goto restart;

      }

   }


} // namespace user






