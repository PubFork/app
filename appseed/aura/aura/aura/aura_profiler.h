#pragma once


// circles, chain, daisies, sunflowers
// you need to profile the top start for bergedge
// from profiler in beggining bottom for veriwellfair


namespace aura
{


   namespace profiler
   {

#ifdef WINDOWS

      extern CLASS_DECL_AURA int64_t g_iFrequency;

#endif

      CLASS_DECL_AURA void initialize();

      CLASS_DECL_AURA int64_t micros();


      inline float millis()
      {

         return micros() / 1000.0f;

      }

   }


} // namespace aura




