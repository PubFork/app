#pragma once


class CLASS_DECL_AURA single_lock :
   virtual public sync_interface
{
public:


   sync_object *        m_pobjectSync;
   HANDLE               m_hobject;
   bool                 m_bAcquired;

   explicit single_lock(sync_object * pobject, bool bInitialLock = false);
   ~single_lock();

   wait_result wait();
   wait_result wait(const duration & duration);
   bool unlock();
   bool unlock(LONG lCount, LPLONG lPrevCount = NULL);
   bool IsLocked();


};
