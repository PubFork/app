void * CreateDispatchQueue();

void CancelDispatchSource(void * p);

void * CreateDispatchTimer(uint64_t interval, uint64_t leeway, void * queue, void(*timer)(void * p), void * p);

void ReleaseDispatch(void * p);

void aura_timer(void * p);




namespace aura
{
   
   class Timer :
   public ::timer
   {
   public:
      
      
      void *               m_queue;
      void *               m_timer;
      bool                 m_bFirst;
      
      Timer()
      {
         
         m_queue = NULL;
         m_timer = NULL;
         
      }
      
      ~Timer()
      {
         
         if (m_queue != NULL)
         {
            
            ReleaseDispatch(m_queue);
            
            m_queue = NULL;
            
         }
         
      }
      
      
      
      void stop(bool bWaitCompletion)
      {
         
         int iRetry = 1000;
         
         while(iRetry >= 0 && m_bDeal)
         {
            
            Sleep(5);
            
            iRetry--;
            
         }
         
         if (m_timer != NULL)
         {
            
            CancelDispatchSource(m_timer);
            
            ReleaseDispatch(m_timer);
            
            m_timer = NULL;
            
         }
         
         m_bSet = false;
         
      }
      
   };
}
