//
//  multithreading_thread_impl.h
//  aura
//
//
//
#pragma once


#ifndef WINDOWS

#define QS_ALLEVENTS 0xffff

void __clear_mq();

template <  >
inline bool EqualElements<IDTHREAD>(IDTHREAD r1, IDTHREAD r2)
{
   return id_thread_equals(r1, r2) != 0;
}
template <  >
inline UINT HashKey(IDTHREAD key)
{
   return 0;
}

#endif

#pragma pack(show)

class thread_startup :
   virtual public object
{
public:


   ::thread *              m_pthread;
   manual_reset_event      m_event;
   manual_reset_event      m_event2;
   DWORD                   m_dwCreateFlags;
   bool                    m_bError;
   error                   m_error;
   bool                    m_bSynch;
   int32_t                 m_iPriority;


   thread_startup(::aura::application * papp);
   virtual ~thread_startup();

};



