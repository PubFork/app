#pragma once


class CLASS_DECL_AURA timer :
   virtual public thread
{
public:


   enum e
   {
      e_start = 1000000,
      hover = e_start,
      e_end

   };

   uint_ptr             m_nIDEvent;
   PFN_TIMER            m_pfnTimer;
   timer_callback *     m_pcallback;
   bool                 m_bPeriodic;
   void *               m_pvoidData;
   sp(timer)            m_ptimerRunning;
   DWORD                m_dwMillis;

   bool                 m_bRet; // for event handlers ( _001OnTimer() )


#ifdef METROWIN


   ThreadPoolTimer ^    m_timer;
   timer *              m_ptimer;

#elif defined(WINDOWS)

   HANDLE               m_hTimerQueue;
   HANDLE               m_hTimer;

#elif defined(APPLEOS)

   void *               m_timer;
   void *               m_queue;

#else


   timer_t              m_timerid;
   struct sigevent      m_sev;
   struct itimerspec    m_its;

#endif



   timer(::aura::application * papp,uint_ptr uiTimer = 0,PFN_TIMER pfnTimer = NULL,void * pvoidData = NULL, mutex * pmutex = NULL);
   virtual ~timer();


   void impl_init();
   void impl_term();



   bool start(int millis, bool bPeriodic);

   void stop(bool bWaitCompletion);

   void call_on_timer();

   virtual void on_timer();

   bool impl_start();
   bool impl_restart();
   void impl_stop();


};


