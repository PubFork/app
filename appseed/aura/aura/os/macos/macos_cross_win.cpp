#include "framework.h"

void ns_Sleep(unsigned int uiMillis);

thread_int_ptr < DWORD > m_dwLastError;

DWORD get_last_error()
{
    return m_dwLastError;
}

void set_last_error(DWORD dwLastError)
{
    m_dwLastError = dwLastError;
   return m_dwLastError;
}


