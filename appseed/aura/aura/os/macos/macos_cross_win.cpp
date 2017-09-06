#include "framework.h"

void ns_Sleep(unsigned int uiMillis);

thread_int_ptr < DWORD > m_dwLastError;

DWORD GetLastError()
{
    return m_dwLastError;
}

DWORD SetLastError(DWORD dwLastError)
{
    m_dwLastError = dwLastError;
   return m_dwLastError;
}


void Sleep(DWORD dwMillis)
{

   DWORD dwSeconds = dwMillis / 1000;

   dwMillis %= 1000;

   if(dwSeconds > 0)
   {
    
      if(dwMillis > 500)
      {
         
         dwMillis = 0;
         
         dwSeconds++;
         
      }
      
      sleep(dwMillis);
      
   }
   else
   {
   
      usleep(dwMillis / 1000);
      
   }
   
}



