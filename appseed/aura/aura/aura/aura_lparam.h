#pragma once


class object;


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

   inline lparam(::object * pobject);


   lparam(const lparam & lparam)
   {

      m_lparam = lparam.m_lparam;

   }


   operator LPARAM &()
   {

      return m_lparam;

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



