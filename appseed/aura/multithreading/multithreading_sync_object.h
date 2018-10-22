#pragma once

/////////////////////////////////////////////////////////////////////////////
// Basic synchronization object
// de-templatization on 2012-05-13
/** templatization of sync_object inspired my class
    Mutex from C++ Sockets Library \file Mutex.h
 **   \date  2004-10-30
 **   \author grymse@alhem.net
**/


class CLASS_DECL_AURA sync_interface
{
public:


   virtual bool lock();
   virtual bool lock(const duration & durationTimeout);

   virtual wait_result wait();
   virtual wait_result wait(const duration & durationTimeout);

   virtual bool is_locked() const;

   virtual bool unlock();
   virtual bool unlock(LONG /* lCount */, LPLONG /* lpPrevCount=NULL */);


};

class CLASS_DECL_AURA sync_object :
   virtual public object,
   virtual public sync_interface
{
public:

#ifdef WINDOWS
   HANDLE      m_object;
#endif
   char *                  m_pszName;
   bool                    m_bOwner;


   sync_object(const char * pstrName = NULL);
   virtual ~sync_object();


   virtual void assert_valid() const override;
   virtual void dump(dump_context & dumpcontext) const override;



   virtual void * get_os_data() const;

   operator HANDLE() const;

   //virtual bool lock() override;
   //virtual bool lock(const duration & durationTimeout) override;

   virtual wait_result wait() override;
   virtual wait_result wait(const duration & durationTimeout) override;

   virtual bool is_locked() const override;

   virtual bool unlock() override;
   virtual bool unlock(LONG /* lCount */, LPLONG /* lpPrevCount=NULL */) override;

};


