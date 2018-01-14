#pragma once




typedef int32_t HRes;


/////////////////////////////////////////////////////////////////////////////
// Verify that a NULL-terminated string points to valid memory
inline bool __is_valid_string(const unichar * psz, size_t nMaxLength = INT_MAX)
{
#ifdef WINDOWS
   (nMaxLength);
#endif
   return (psz != NULL);
}

// Verify that a NULL-terminated string points to valid memory
inline bool __is_valid_string(const char * psz, size_t nMaxLength = UINT_MAX)
{
#ifdef WINDOWS
   (nMaxLength);
#endif
   return (psz != NULL);
}

// Verify that a pointer points to valid memory
inline bool __is_valid_address(const void * p, size_t nBytes, bool bReadWrite = TRUE)
{
#ifdef WINDOWS
   (bReadWrite);
   (nBytes);
#endif
   return (p != NULL);
}

