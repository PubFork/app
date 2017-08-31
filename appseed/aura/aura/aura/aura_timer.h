#pragma once


class CLASS_DECL_AURA timer :
   public thread
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
   bool                 m_bSet;
   bool                 m_bPeriodic;
   void *               m_pvoidData;
   bool                 m_bRet;
   bool                 m_bDeal;
   bool                 m_bKill;
   DWORD                m_dwMillis;
   bool                 m_bDestroying;


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

   bool call_on_timer();

   virtual bool on_timer();
   
   bool impl_start();
   bool impl_restart();
   void impl_stop(bool bWaitCompletion);


};


