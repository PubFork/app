#include "framework.h"
//#include <float.h>




void dump_context::write(float f)
{
   char szBuffer[32];
   ::aura::gcvt_s(szBuffer, 32, f, FLT_DIG);

   write(szBuffer);

}

void dump_context::write(double d)
{
   char szBuffer[32];
   ::aura::gcvt_s(szBuffer, 32, d, DBL_DIG);

   *this << szBuffer;

}

