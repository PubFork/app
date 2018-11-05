void * CreateDispatchQueue();

void CancelDispatchSource(void * p);

void * CreateDispatchTimer(uint64_t interval, uint64_t leeway, void * queue, void(*timer)(void * p), void * p);
void * ResetDispatchTimer(void * timer, uint64_t interval, uint64_t leeway);

void ReleaseDispatch(void * p);

void aura_timer(void * p);


void timer::impl_init()
{
   
   m_queue = NULL;
   m_timer = NULL;
   
}

bool timer::impl_start()
{
   
   if(m_queue == NULL)
   {
      
      m_queue = CreateDispatchQueue();
      
      if (m_queue == NULL)
      {
         
         return false;
         
      }
      
   }
   
   m_timer = CreateDispatchTimer(m_dwMillis, MAX(1, m_dwMillis / 20), m_queue, aura_timer, this);
   
   if (m_timer == NULL)
   {
      
      return false;
      
   }

   return true;

}
      
void timer::impl_term()
{
         
   if (m_queue != NULL)
   {
            
      ReleaseDispatch(m_queue);
            
      m_queue = NULL;
            
   }
         
}
      
      
      
void timer::impl_stop()
{
         
         if (m_timer != NULL)
         {
            
            CancelDispatchSource(m_timer);
            
            ReleaseDispatch(m_timer);
            
            m_timer = NULL;
            
         }
         

}




bool timer::impl_restart()
{
   
   
   m_timer = ResetDispatchTimer(m_timer, m_dwMillis, MAX(1, m_dwMillis / 20));
   
   if (m_timer == NULL)
   {
      
      return false;
      
   }

   return true;

}






void aura_timer(void * p)
{
   
   ::timer * ptimer = (::timer *)p;
   
   ptimer->call_on_timer();
   
}



