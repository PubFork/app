#pragma once



template < typename POINTER_TYPE >
class cotaskptr
{
public:


   POINTER_TYPE   m_p;

   cotaskptr()
   {

      m_p = NULL;

   }


   virtual ~cotaskptr()
   {

      free();

   }

   void alloc(SIZE_T size)
   {

      if (m_p != NULL)
      {

         m_p = CoTaskMemRealloc(m_p, size);

      }
      else
      {

         m_p = CoTaskMemAlloc(size);

      }

   }

   bool is_null() const
   {

      return m_p == NULL;

   }

   bool is_set() const
   {

      return m_p != NULL;

   }

   virtual void free()
   {

      if (m_p != NULL)
      {

         ::CoTaskMemFree(m_p);

         m_p = NULL;

      }

   }


   operator POINTER_TYPE()
   {

      return m_p;

   }

   operator const POINTER_TYPE() const
   {

      return m_p;

   }


   POINTER_TYPE operator ->()
   {

      return m_p;

   }


   const POINTER_TYPE operator ->() const
   {

      return m_p;

   }

   POINTER_TYPE * operator &()
   {

      free();

      return &m_p;

   }

   const POINTER_TYPE * operator &() const
   {

      return &m_p;

   }


};


template < typename POINTER_TYPE >
class sec_cotaskptr :
   virtual public cotaskptr < POINTER_TYPE >
{
public:


   DWORD         m_size;


   sec_cotaskptr()
   {

      m_size = 0;
      m_p = NULL;

   }


   virtual ~sec_cotaskptr()
   {

      free();

   }

   using cotaskptr::alloc;
   void alloc()
   {

      alloc(m_size);

   }

   virtual void free() override
   {

      if (m_p != NULL)
      {

         if (m_size > 0)
         {

            SecureZeroMemory(m_p, m_size);

            m_size = 0;

         }

         cotaskptr::free();

      }

   }


};


#define cotaskp(POINTER_TYPE) cotaskptr < POINTER_TYPE >



