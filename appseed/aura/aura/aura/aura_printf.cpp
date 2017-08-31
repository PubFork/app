// print formatted.cpp

// based on:
// LIBCTINY - Matt Pietrek 2001
// MSDN Magazine, January 2001

// 08/12/06 (mv)

#include "framework.h"
//#include <wchar.h>
#include <stdio.h>
#include <stdarg.h>



int32_t printf_dup(const char *format, ...)
{
    va_list args;
    va_start(args, format);
    int32_t ret = vprintf_dup(format, args);
    va_end(args);

	return ret;
}

int32_t wprintf_dup(const unichar *format, ...)
{
	va_list args;
	va_start(args, format);
	int32_t ret = vwprintf_dup(format, args);
	va_end(args);

	return ret;
}



int32_t vprintf_dup(const char *format, va_list args)
{

    return vprintf(format, args);

}


int32_t vwprintf_dup(const unichar *format, va_list args)
{

#if defined(APPLEOS) || defined(LINUX) || defined(ANDROID)

   unichar32 * v = utf16_to_utf32(format);

   int i = vwprintf((wchar_t *) v, args);

   free(v);

   return i;

#elif defined(SOLARIS)

    return vwprintf(format, args);

#else

   return vwprintf(format, args);

#endif

}


#ifdef APPLEOS

mutex * g_pmutexCvt = NULL;

int32_t ecvt_r(double d, int i, int *__restrict pi1, int *__restrict pi2, char * sz, size_t size) /* LEGACY */
{

   synch_lock ml(g_pmutexCvt);

   char * psz = ecvt(d, i, pi1, pi2);

   if(psz == NULL)
      return -1;

   if(strlen(psz) > (size - 1))
      return -1;

   strcpy(sz, psz);

   return 0;

}

int32_t fcvt_r(double d, int i, int *__restrict pi1, int *__restrict pi2, char * sz, size_t size) /* LEGACY */
{

   synch_lock ml(g_pmutexCvt);

   char * psz = fcvt(d, i, pi1, pi2);

   if(psz == NULL)
      return -1;

   if(strlen(psz) > (size - 1))
      return -1;

   strcpy(sz, psz);

   return 0;

}

#endif
