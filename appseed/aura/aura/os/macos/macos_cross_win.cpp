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


