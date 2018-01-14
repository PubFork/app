#include "framework.h"

#if defined(LINUX) || defined(APPLEOS)

//#include <sys/time.h>

#endif


namespace aura
{


   namespace profiler
   {

      void initialize()
      {


      }


      CLASS_DECL_AURA int64_t micros()
      {

         return ::get_nanos() / 1000;

      }


   } // namespace profiler


} // namespace aura




