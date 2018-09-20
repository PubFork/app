#include "framework.h"


interlocked_long::interlocked_long()
{
#if defined(WINDOWS) || defined(APPLEOS)
   m_plong = (long *) aligned_memory_alloc(sizeof(long));
#else
   m_plong = (long *) malloc(sizeof(long));
#endif
   *m_plong = 0;
}

interlocked_long::~interlocked_long()
{
   if(m_plong != NULL)
   {
#if defined(WINDOWS) || defined(APPLEOS)
      memory_free(m_plong);
#else
      free(m_plong);
#endif
   }
}



void interlocked_long::add(long l)
{
#ifdef WINDOWS
   InterlockedExchangeAdd(m_plong, l);
#else
   __sync_fetch_and_add(m_plong, l);
#endif
}


void interlocked_long::subtract(long l)
{
#ifdef WINDOWS
   InterlockedExchangeAdd(m_plong, -l);
#else
   __sync_fetch_and_sub(m_plong, l);
#endif
}

interlocked_long & interlocked_long::operator = (long l)
{
#ifdef WINDOWS
   InterlockedExchange(m_plong, l);
#else
   __sync_(m_plong, l);
#endif
   return *this;
}

//bool interlocked_long::operator == (long i) const
//{
//   return *m_plong == i;
//}
//
//bool interlocked_long::operator > (long i) const
//{
//   return *m_plong > i;
//}
//
//bool interlocked_long::operator >= (long i) const
//{
//   return *m_plong >= i;
//}
//
//bool interlocked_long::operator < (long i) const
//{
//   return *m_plong < i;
//}
//
//bool interlocked_long::operator <= (long i) const
//{
//   return *m_plong <= i;
//}
//
//bool interlocked_long::operator != (long i) const
//{
//   return *m_plong != i;
//}


interlocked_long & interlocked_long::operator++()
{

   add(1);

   return *this;

}


interlocked_long & interlocked_long::operator--()
{

   subtract(1);

   return *this;

}


long interlocked_long::operator++(int)
{

   long l = *m_plong;

   add(1);

   return l;

}


long interlocked_long::operator--(int)
{

   long l = *m_plong;

   subtract(1);

   return l;

}



