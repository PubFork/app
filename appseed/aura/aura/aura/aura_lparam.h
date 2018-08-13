#pragma once


class simple_object;


class CLASS_DECL_AURA lparam
{
public:


   LPARAM m_lparam;

   lparam(LPARAM lparam = 0) { m_lparam = lparam; }

#if !defined(VSNORD) && !defined(RASPBIAN)

   lparam(int i) { m_lparam = (LPARAM) i; }

#endif

#if OSBIT != 64

   lparam(int64_t i) { m_lparam = (LPARAM)i; }

#endif

   /// catching/receiving object
   inline lparam(void * p) { m_lparam = (LPARAM)p;  }

   /// posting/sending object
   inline lparam(::simple_object * pobject);

   /// posting/sending object
   template < typename T >
   inline lparam(sp(T) & p) :
      lparam((::simple_object *) p.m_p)
   {
   }


   lparam(const lparam & lparam)
   {

      m_lparam = lparam.m_lparam;

   }


   operator LPARAM &()
   {

      return m_lparam;

   }

   operator LPARAM () const
   {

      return m_lparam;

   }

   operator void * &()
   {

      return (void * &) m_lparam;

   }

   operator void * () const
   {

      return (void *) m_lparam;

   }



   template < typename T >
   T * cast() const
   {

      return (T *) m_lparam;

   }


   lparam & operator = (const lparam & lparam)
   {

      m_lparam = lparam.m_lparam;

      return *this;

   }


   lparam & operator = (LPARAM lparam)
   {

      m_lparam = lparam;

      return *this;

   }


   inline int x() const
   {

      return GET_X_LPARAM(m_lparam);

   }


   inline int y() const
   {

      return GET_Y_LPARAM(m_lparam);

   }


};



