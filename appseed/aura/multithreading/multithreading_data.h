#pragma once


class CLASS_DECL_AURA thread_data
{
public:


#if defined(_POSIX_THREADS) || defined(LINUX)

   pthread_key_t        m_key;

#else

   DWORD                m_dwIndex;

#endif


   thread_data();
   ~thread_data();


   void * get();
   void set(void * p);


};


template < class T >
class thread_pointer :
   public thread_data
{
public:

   inline operator T *() { return (T *)get(); }
   inline T * operator ->() { return operator T *(); }
   inline thread_pointer & operator = (T * pt) { set(pt); return *this; }

};


template < class T >
class thread_int_ptr :
   public thread_data
{
public:

   operator T () { return (T)(int_ptr)get(); }
   thread_int_ptr & operator = (T t) { set((void *)(int_ptr)t); return *this; }

   bool operator == (int_ptr i)
   {
      return ((int_ptr)get()) == i;
   }

};

template < class T >
class thread_object :
   public thread_data
{
public:

   inline operator T *() { if (get() == NULL) { set(new T()); } return (T *)get(); }
   inline T * operator ->() { return operator T *(); }

};



