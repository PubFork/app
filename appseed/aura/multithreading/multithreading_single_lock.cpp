#include "framework.h"


single_lock::single_lock(sync_object * psyncobject, bool bInitialLock)
{

   m_pobjectSync = psyncobject;

   m_bAcquired = FALSE;

   if (bInitialLock)
   {

      lock();

   }

}


wait_result single_lock::wait()
{

   ::wait_result result(::wait_result::Event0);

   if(m_bAcquired)
   {

      return result;

   }

   if(m_pobjectSync == NULL)
   {

      return result;

   }

   try
   {

      result = m_pobjectSync->wait();

   }
   catch(...)
   {

      result = ::wait_result(::wait_result::Failure);

   }

   m_bAcquired = result.succeeded();

   return result;

}


::wait_result single_lock::wait(const duration & durationTimeOut)
{

   ::wait_result result(::wait_result::Event0);

   if(m_bAcquired)
   {

      return result;

   }

   if(m_pobjectSync == NULL)
   {

      return result;

   }

   try
   {

      result = m_pobjectSync->wait(durationTimeOut);

   }
   catch(...)
   {

      result = ::wait_result(::wait_result::Failure);

   }

   m_bAcquired = result.succeeded();

   return result;

}


bool single_lock::unlock()
{

   if(m_pobjectSync == NULL)
   {

      return true;

   }

   if (m_bAcquired)
   {

      try
      {

         if(m_pobjectSync->unlock())
         {

            m_bAcquired = false;

         }

      }
      catch(...)
      {

      }

   }

   // successfully unlocking means it isn't acquired
   return !m_bAcquired;

}


bool single_lock::unlock(LONG lCount, LPLONG lpPrevCount /* = NULL */)
{
   ASSERT(m_pobjectSync != NULL);
   if (m_bAcquired)
      m_bAcquired = !m_pobjectSync->unlock(lCount, lpPrevCount);

   // successfully unlocking means it isn't acquired
   return !m_bAcquired;
}


single_lock::~single_lock()
{

   unlock();

   /*if(::get_thread() != NULL)
   {

      if(::get_thread()->m_pslUser == this)
      {
         ::get_thread()->m_pslUser = NULL;
      }

   }*/

}


bool single_lock::IsLocked()
{

   return m_bAcquired;

}


