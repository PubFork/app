


bool timer::impl_start()
{

::Windows::Foundation::TimeSpan span;

span.Duration = millis * 1000 * 10;

auto pred = [this](ThreadPoolTimer ^)
{
   
   try
   {
      
      call_on_timer();
      
   }
   catch (...)
   {
      
   }
   
};

//if (bPeriodic)
//{

//   m_ptimer->m_timer = ThreadPoolTimer::CreatePeriodicTimer(ref new TimerElapsedHandler(pred), span); // TimeSpan is 100 nanoseconds

//}
//   else

m_bSet = true;


{
   
   m_ptimer->m_timer = ThreadPoolTimer::CreateTimer(ref new TimerElapsedHandler(pred), span);
   
   if(m_ptimer->m_timer == nullptr)
   {
      
      m_bSet = false;
      
   }
   
}


}


   void impl_init()
   {
      
      m_timer     = nullptr;
      m_ptimer    = NULL;
      
   }


   void impl_term()
   {
      
      if (m_timer != nullptr)
      {
         
         m_timer->Cancel();
         
         m_timer = nullptr;
         
      }
      
   }
   
   
   void impl_stop(bool bWaitCompletion)
   {
      
      if (m_timer != nullptr)
      {
         
         m_timer->Cancel();
         
         m_timer = nullptr;
         
      }
      
   }
   
   
};




bool timer::impl_restart()
{
   
   m_ptimer->m_timer->Cancel();
   
   m_ptimer->m_timer = nullptr;
   
   ::Windows::Foundation::TimeSpan span;
   
   span.Duration = m_dwMillis * 1000 * 10;
   
   auto pred = [this](ThreadPoolTimer ^)
   {
      
      try
      {
         
         call_on_timer();
         
      }
      catch(...)
      {
         
      }
      
   };
   
   
   m_ptimer->m_timer = ThreadPoolTimer::CreateTimer(ref new TimerElapsedHandler(pred),span);
   

return true;

}
