#pragma once


#ifdef METROWIN

#include <d2d1_1.h>

#endif


namespace draw2d
{

   class CLASS_DECL_AURA device_lock
   {
   public:

      static ID2D1Factory1 * g_pfactory;

      comptr < ID2D1Multithread > m_D2DMultithread;

      device_lock()
      {

         if (g_pfactory != NULL)
         {

            g_pfactory->QueryInterface(IID_PPV_ARGS(&m_D2DMultithread));

            m_D2DMultithread->Enter();

         }

      }

      ~device_lock()
      {

         if (m_D2DMultithread.m_p != NULL)
         {

            m_D2DMultithread->Leave();

         }

      }




   };


   class CLASS_DECL_AURA lock :
      public synch_lock
   {
   public:

      static mutex * g_pmutex;

      lock() :
         synch_lock(g_pmutex)
      {

      }

      virtual ~lock()
      {

      }

   };


} // namespace draw2d


