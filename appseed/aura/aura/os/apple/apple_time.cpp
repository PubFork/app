//
//  apple_time.cpp
//  aura
//
//  Created by Camilo Sasuke Tsumanuma on 01/10/17.
//

#include "framework.h"



//#include <mach/clock.h>
//#include <mach/mach.h>
#include <mach/mach_time.h>

//extern clock_serv_t g_cclock;
extern double g_machtime_conversion_factor;

void ns_Sleep(unsigned int uiMillis);

uint64_t get_nanos()
{
   
   return mach_absolute_time() * g_machtime_conversion_factor;
   
   //   mach_timespec_t mts;
   //
   //   clock_get_time(g_cclock, &mts);
   //
   //   return ((uint64_t) mts.tv_sec * (uint64_t)1000 * (uint64_t)1000 * (uint64_t)1000 )+ ((uint64_t) mts.tv_nsec);
   
}
