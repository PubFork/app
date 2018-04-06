#pragma once




template < class root_derived >
inline int64_t add_ref(root_derived * pca);

template < class root_derived >
inline int64_t release(root_derived * & pca);

// ::ca::null_class back link to operational system oswindow.h
//
//
//
//
// operational system NULL/void itself to a windowing service
//
// Curitiba, inha-metro-win-ubuntu-mountain-lion-macos 4 de novembro de 2012
template < class T >
class smart_pointer
{
public:



   T * m_p;


   smart_pointer();
   smart_pointer(const lparam & lparam);
   smart_pointer(const smart_pointer < T > & t);
#ifdef MOVE_SEMANTICS
   smart_pointer(smart_pointer < T > && t);
#endif
   smart_pointer(const ::aura::allocatorsp & t);
#ifdef MOVE_SEMANTICS
   smart_pointer(::aura::allocatorsp && t);
#endif
   template < class T2 >
   smart_pointer(T2 * p)
   {
      if(p == NULL)
      {
         m_p = NULL;
         return;
      }
      m_p = dynamic_cast < T * > (p);
      if(m_p != NULL) ::add_ref(p);
   }
   smart_pointer(T * p);

   template < class T2 >
   smart_pointer(const T2 * p)
   {
      if(p == NULL)
      {
         m_p = NULL;
         return;
      }
      m_p = dynamic_cast < T * > ((T2 *) p);
      if(m_p != NULL) ::add_ref(p);
   }

   template < class T2 >
   smart_pointer(const smart_pointer < T2 > & t)
   {
      m_p = NULL;
      operator = (dynamic_cast < T * >(t.m_p));
   }


#ifdef MOVE_SEMANTICS
   template < class T2 >
   smart_pointer(smart_pointer < T2 > && t)
   {
      if(t.m_p != NULL)
      {
         m_p = dynamic_cast < T * >(t.m_p);
         if(m_p != NULL)
         {
            t.m_p = NULL;
         }
      }
      else
      {
         m_p = NULL;
      }
   }
#endif

   ~smart_pointer();


   inline T * operator ->();
   inline T * operator ->() const ;
   inline T & operator *();
   inline T & operator *() const ;
   inline operator T * ();
   inline operator T * const () const;
   inline T * get_();
   inline const T * get_() const;
   inline operator lparam ();
   inline operator lparam () const;
   //inline operator void * ();
   //inline operator void * () const;

   inline bool is_null() const;
   inline bool is_set() const;

   inline smart_pointer & operator = (const smart_pointer < T > & t);
#ifdef MOVE_SEMANTICS
   inline smart_pointer & operator = (smart_pointer < T > && t);
#endif
   inline smart_pointer & operator = (const lparam & lparam);

   template < class T2 >
   inline smart_pointer & operator = (T2 * p)
   {
      return operator = (dynamic_cast < T * > (p));
   }


   inline smart_pointer & operator = (T * p);

   template < class T2 >
   inline smart_pointer & operator = (const smart_pointer < T2 > & t)
   {
      return operator = (dynamic_cast < T * > (t.m_p));
   }

#ifdef MOVE_SEMANTICS
   template < class T2 >
   inline smart_pointer & operator = (smart_pointer < T2 > && t)
   {
      T * pOld = m_p;
      if(t.m_p != NULL)
      {
         m_p = dynamic_cast < T * >(t.m_p);
         if(m_p != NULL)
         {
            t.m_p = NULL;
         }
      }
      else
      {
         m_p = NULL;
      }
      if(pOld != NULL)
      {
         ::release(pOld);
      }
      return *this;
   }
#endif

   void release();
   inline T * detach();


   template < class T2 >
   inline T2 * cast()
   {
      return dynamic_cast < T2 * > (m_p);
   }

   template < class T2 >
   inline T2 * cast() const
   {
      return dynamic_cast < T2 * > (m_p);
   }

   template < class T2 >
   inline bool is() const
   {
      return cast < T2 > () != NULL;
   }

//      bool operator ==(const smart_pointer & p) const { return m_p == p.m_p; }
//      bool operator !=(const smart_pointer & p) const { return m_p != p.m_p; }
//      bool operator ==(const T * p) const { return m_p == p; }
//      bool operator !=(const T * p) const { return m_p != p; }
   template < typename T2 >
   inline bool operator ==(const T2 * p) const { return m_p == p; }
   template < typename T2 >
   inline bool operator !=(const T2 * p) const { return m_p != p; }
   inline bool operator ==(const T * p) const { return m_p == p; }
   inline bool operator !=(const T * p) const { return m_p != p; }
   //bool operator ==(void * p) const { return m_p == (T *) p; }
   //bool operator !=(void * p) const { return m_p != (T *) p; }



   void oattrib(const sp(T) & o);
   void copy(T * po) { return oattrib(po); }


   //sp(T) clone() const;

   void alloc(const ::aura::allocatorsp & spallocator);



};




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

   HRESULT CoCreateInstance(REFCLSID rclsid, LPUNKNOWN pUnkOuter = NULL, DWORD dwClsContext = CLSCTX_ALL)
   {

      Release();

      if (!defer_co_initialize_ex(false))
      {

         return E_FAIL;

      }

      return ::CoCreateInstance(rclsid, pUnkOuter, dwClsContext, __uuidof(TYPE), (void **)&m_p);

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

   TYPE * operator ->() const
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


   SIZE_T         m_size;


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

