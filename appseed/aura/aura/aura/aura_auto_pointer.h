#pragma once


template < typename T >
class auto_pointer
{
public:

   T * m_p;

   auto_pointer()
   {

      m_p = NULL;

   }


   auto_pointer(T * p)
   {

      m_p = p;

   }


   auto_pointer(const auto_pointer & op)
   {

      m_p = op.m_p;

   }


   auto_pointer(auto_pointer && op)
   {

      m_p = op.m_p;

      op.m_p = NULL;

   }


   ~auto_pointer()
   {

      destroy();

   }


   void destroy()
   {

      ::aura::del(m_p);

   }


   T * detach()
   {

      T * p = m_p;

      m_p = NULL;

      return p;

   }


   T * release()
   {

      return detach();

   }


   T * get()
   {

      return m_p;

   }


   T * get() const
   {

      return m_p;

   }

   operator T *()
   {

      return m_p;

   }


   operator T *() const
   {

      return m_p;

   }


   T & operator *()
   {

      return*m_p;

   }


   const T & operator *() const
   {

      return*m_p;

   }

   void reset(T * p)
   {

      if (p == m_p)
      {

         return;

      }

      destroy();

      m_p = p;

   }


   auto_pointer & operator = (T * p)
   {

      reset(p);

      return *this;

   }

   auto_pointer & operator = (const auto_pointer & op)
   {

      reset(op.m_p);

      return *this;

   }


   auto_pointer & operator = (auto_pointer && op)
   {

      if (op.m_p == m_p)
      {

         return *this;

      }

      destroy();

      m_p = op.m_p;

      op.m_p = NULL;

      return *this;

   }


   T * operator ->()
   {

      return m_p;

   }


   const T * operator ->() const
   {

      return m_p;

   }

};

// Remember you always can restore with #define ap(x) __AP(x),
// or #undef ap and use more verbore __AP,
// or even you may #undef both and use explicit ::auto_pointer < x >!
#define __AP(x) ::auto_pointer < x >
#define ap(x) __AP(x)