#pragma once



class CLASS_DECL_AURA nano_timer
{
public:

#ifdef WINDOWS

   HANDLE      m_hTimer;

#endif


   nano_timer()
   {

#ifdef WINDOWSEX

      m_hTimer = ::CreateWaitableTimer(NULL, TRUE, NULL);

#endif

   }


   void wait(u64 uWait)
   {

#ifdef WINDOWS

      LARGE_INTEGER li = {};

      li.QuadPart = - ((LONGLONG) uWait / 100LL);

      if (!SetWaitableTimer(m_hTimer, &li, 0, NULL, NULL, FALSE))
      {

         Sleep(DWORD(uWait / 1000000LL));

      }
      else
      {

         WaitForSingleObject(m_hTimer, INFINITE);

      }

#else

      struct timespec req;

      struct timespec rem;

      req.tv_sec = uWait / 1000000000ULL;

      req.tv_nsec = uWait % 1000000000ULL;

      rem.tv_sec = 0;

      rem.tv_nsec = 0;

      ::nanosleep(&req, &rem);

#endif

   }


   ~nano_timer()
   {

#ifdef WINDOWSEX

      ::CloseHandle(m_hTimer);

#endif

   }

};



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

   uint_ptr                m_nIDEvent;
   PFN_TIMER               m_pfnTimer;
   timer_callback *        m_pcallback;
   bool                    m_bPeriodic;
   void *                  m_pvoidData;
   sp(timer)               m_ptimerRunning;
   DWORD                   m_dwMillis;
   ::user::interaction *   m_pui;

   //bool                 m_bThreadInit;

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



   timer(::aura::application * papp, uint_ptr uiTimer = 0, PFN_TIMER pfnTimer = NULL, void * pvoidData = NULL, sync_object * pmutex = NULL);
   virtual ~timer();


   void impl_init();
   void impl_term();



   bool start(int millis, bool bPeriodic);

   void stop();

   void call_on_timer();

   virtual void on_timer();

   bool impl_start();
   bool impl_restart();
   void impl_stop();


   virtual void children_add(::aura::application * papp);


   virtual void post_quit() override;


   virtual void wait_quit(duration durationTimeout) override;

   virtual void safe_pre_term() override;


};


