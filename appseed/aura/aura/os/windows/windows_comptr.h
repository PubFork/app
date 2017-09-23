#pragma once


namespace windows
{


   template < typename TYPE >
   class comptr
   {
      public:

         TYPE * m_p;

         comptr()
         {
            m_p = NULL;

         }

         comptr(const comptr & ptr)
         {
            if (ptr.m_p != NULL)
            {
               ptr.m_p->AddRef();
            }
            m_p = ptr.m_p;

         }

         comptr(TYPE * p)
         {
            if (p != NULL)
            {
               p->AddRef();
            }
            m_p = p;
         }






         ~comptr()
         {

            Release();

         }

         HRESULT CoCreateInstance(REFCLSID rclsid,LPUNKNOWN pUnkOuter = NULL,DWORD dwClsContext = CLSCTX_ALL)
         {

            Release();

            if (!defer_co_initialize_ex(false))
            {

               return E_FAIL;

            }

            return ::CoCreateInstance(rclsid,pUnkOuter,dwClsContext,__uuidof(TYPE),(void **)&m_p);

         }

         template < class IFACE >
         HRESULT As(comptr < IFACE > & iface)
         {

            if (m_p == NULL)
            {

               return E_FAIL;

            }

            return m_p->QueryInterface< IFACE >(&iface);

         }


         TYPE * operator ->()
         {

            return (TYPE *)m_p;

         }


         TYPE * detach()
         {

            TYPE * p = operator ->();

            m_p = NULL;

            return p;

         }

         operator void ** ()
         {

            Release();

            return (void **) &(TYPE * &)m_p;

         }

         TYPE ** operator & ()
         {

            Release();

            return &(TYPE * &)m_p;

         }


         operator TYPE * ()
         {

            return (TYPE *)m_p;

         }

         comptr & operator = (TYPE * p)
         {

            if (m_p != p)
            {

               if (p != NULL)
               {

                  p->AddRef();


               }

               if (m_p != NULL)
               {

                  m_p->Release();

               }

               m_p = p;

            }

            return *this;

         }


         comptr & operator = (const comptr & ptr)
         {

            if (&ptr != this)
            {

               if (ptr.m_p != NULL)
               {

                  ptr.m_p->AddRef();


               }

               if (m_p != NULL)
               {

                  m_p->Release();

               }

               m_p = ptr.m_p;

            }

            return *this;

         }


         ULONG Release()
         {

            ULONG ul = 0;

            try
            {

               if (m_p != NULL)
               {

                  ul = m_p->Release();

               }

            }
            catch (...)
            {


            }

            m_p = NULL;


            return ul;

         }


         bool is_null()
         {

            return m_p == NULL;

         }


         bool is_set()
         {

            return !is_null();

         }


   };


} // namespace windows






template < typename POINTER_TYPE >
class co_task_pointer
{
   public:


      POINTER_TYPE m_p;


      co_task_pointer()
      {

         m_p = NULL;

      }


      ~co_task_pointer()
      {

         if (m_p != NULL)
         {

            ::CoTaskMemFree(m_p);

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

         return &m_p;

      }

      const POINTER_TYPE * operator &() const
      {

         return &m_p;

      }


};


#define cotaskp(POINTER_TYPE) co_task_pointer < POINTER_TYPE >