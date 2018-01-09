#include "framework.h"



DWORD get_last_error()
{
    
    return get_thread_int("dwLastError");
    
}


DWORD set_last_error(DWORD dwLastError)
{
    
    set_thread_int("dwLastError", (int) dwLastError);
    
    return dwLastError;
    
}


void Sleep(DWORD dwMillis)
{
    
    timespec ts;
    
    ts.tv_sec = dwMillis / 1000;
    
    ts.tv_nsec = (dwMillis % 1000) * 1000 * 1000;
    
    timespec tsRem;
    
    nanosleep(&ts, &tsRem);
    
}



