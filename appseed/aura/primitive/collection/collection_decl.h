#pragma once



template < typename T > class numeric_array;
typedef CLASS_DECL_AURA numeric_array < index > index_array;
typedef CLASS_DECL_AURA numeric_array < count > count_array;



#ifdef LINUX
#include <initializer_list>
#endif

namespace constructor
{


   template < class TYPE >
   class def
   {
   public:

      inline static void construct(void * p)
      {
         ::new(p) TYPE;
      }
      inline static void construct(void * p, ::count c)
      {
         while (c > 0)
         {
            ::new(p) TYPE;
            ((TYPE*&)p)++;
            c--;
         }
      }



   };


   template < class TYPE >
   class zero
   {
   public:

      inline static void construct(void * p)
      {

         ::zero(p, sizeof(TYPE));

      }

      inline static void construct(void * p, ::count c)
      {

         while (c > 0)
         {

            ::zero(p, sizeof(TYPE));

            ((byte*&)p) += sizeof(TYPE);

            c--;

         }

      }



   };


   template < class TYPE >
   class nodef
   {
   public:

      inline static void construct(void * p)
      {
         UNREFERENCED_PARAMETER(p);
      }
      inline static void construct(void * p, ::count c)
      {
         UNREFERENCED_PARAMETER(p);
         UNREFERENCED_PARAMETER(c);
      }

   };


} // namespace constructor

namespace destructor
{


   template < class TYPE >
   class def
   {
   public:

      inline static void destruct(TYPE * p)
      {
         p->~TYPE();
      }
      inline static void destruct(TYPE * p, ::count c)
      {
         while (c > 0)
         {
            p->~TYPE();
            p++;
            c--;
         }
      }



   };





   template < class TYPE >
   class nodef
   {
   public:

      inline static void destruct(TYPE * p)
      {
         UNREFERENCED_PARAMETER(p);
      }
      inline static void destruct(TYPE * p, ::count c)
      {
         UNREFERENCED_PARAMETER(p);
         UNREFERENCED_PARAMETER(c);
      }

   };


} // namespace destructor


namespace copier
{


   template < class TYPE >
   class def
   {
   public:

      inline static void copy(TYPE *pdst, const TYPE * psrc)
      {

         *pdst = *psrc;

      }

      inline static void copy(TYPE *pdst, const TYPE * psrc, ::count c)
      {

         while (c > 0)
         {
            *pdst = *psrc;
            pdst++;
            psrc++;
            c--;
         }

      }


   };


} // namespace copier


namespace heap
{

   template < class TYPE, class POOL >
   class allocator
   {
   public:

#if MEMDLEAK  || defined(__MCRTDBG)
      inline static TYPE * alloc(::count c, const char * pszFile, int iLine)
      {

         return (TYPE *)POOL::alloc(sizeof(TYPE) * c, pszFile, iLine);

      }
#else
      inline static TYPE * alloc(::count c)
      {

         return (TYPE *)POOL::alloc(sizeof(TYPE) * c);

      }
#endif


      inline static void _free(TYPE * p)
      {

         POOL::_free((void *)p);

      }


   };


   template < class TYPE >
   class def :
      public allocator < TYPE, default_memory_allocator>
   {

   };


   template < class TYPE >
   class processor_cache_oriented : // would it help for data-orientation-assumation ??!?!
      public allocator < TYPE, processor_cache_oriented_memory_allocator >
   {


   };


   template < class TYPE >
   class sys :
      public allocator < TYPE, system_memory_allocator>
   {

   };



} // namespace memory


namespace allocator
{


   template < class TYPE >
   class allocator
   {
   public:

      inline static void construct(TYPE * p)
      {
         constructor::nodef< TYPE >::construct(p);
      }

      inline static void construct(TYPE * p, ::count c)
      {
         constructor::nodef< TYPE >::construct(p, c);

      }

      inline static void destruct(TYPE * p)
      {
         destructor::nodef < TYPE >::destruct(p);
      }
      inline static void destruct(TYPE * p, ::count c)
      {
         destructor::nodef < TYPE >::destruct(p, c);
      }


      inline static void copy(TYPE *pdst, const TYPE * psrc)
      {

         copier::def< TYPE >::copy(pdst, psrc);

      }


      inline static void copy(TYPE *pdst, const TYPE * psrc, ::count c)
      {

         copier::def< TYPE >::copy(pdst, psrc, c);

      }

      inline static TYPE * alloc(::count c)
      {

         return heap::def < TYPE >::alloc(c);

      }


      inline static void _free(TYPE * p)
      {

         heap::def < TYPE >::_free(p);

      }

   };


   template < class TYPE >
   class def
   {

   public:

      inline static void construct(TYPE * p)
      {
         constructor::def< TYPE >::construct(p);
      }

      inline static void construct(TYPE * p, ::count c)
      {
         constructor::def< TYPE >::construct(p, c);

      }

      inline static void destruct(TYPE * p)
      {
         destructor::def< TYPE>::destruct(p);
      }
      inline static void destruct(TYPE * p, ::count c)
      {
         destructor::def< TYPE>::destruct(p, c);
      }


      inline static void copy(TYPE *pdst, const TYPE * psrc)
      {

         copier::def< TYPE >::copy(pdst, psrc);

      }


      inline static void copy(TYPE *pdst, const TYPE * psrc, ::count c)
      {

         copier::def< TYPE >::copy(pdst, psrc, c);

      }

#if MEMDLEAK  || defined(__MCRTDBG)
      inline static TYPE * alloc(::count c, const char * pszFile, int iLine)
      {

         return heap::def < TYPE >::alloc(c, pszFile, iLine);

      }
#else
      inline static TYPE * alloc(::count c)
      {

         return heap::def < TYPE >::alloc(c);

      }

#endif


      inline static void _free(TYPE * p)
      {

         heap::def < TYPE >::_free(p);

      }


   };

   template < class TYPE >
   class nodef
   {

   public:

      inline static void construct(TYPE * p)
      {
         constructor::nodef< TYPE >::construct(p);
      }

      inline static void construct(TYPE * p, ::count c)
      {
         constructor::nodef< TYPE >::construct(p, c);

      }

      inline static void destruct(TYPE * p)
      {
         destructor::nodef< TYPE>::destruct(p);
      }
      inline static void destruct(TYPE * p, ::count c)
      {
         destructor::nodef< TYPE>::destruct(p, c);
      }


      inline static void copy(TYPE *pdst, const TYPE * psrc)
      {

         copier::def< TYPE >::copy(pdst, psrc);

      }


      inline static void copy(TYPE *pdst, const TYPE * psrc, ::count c)
      {

         copier::def< TYPE >::copy(pdst, psrc, c);

      }

#if MEMDLEAK || defined(__MCRTDBG)
      inline static TYPE * alloc(::count c, const char  * pszFile, int iLine)
      {

         return heap::def < TYPE >::alloc(c, pszFile, iLine);

      }
#else
      inline static TYPE * alloc(::count c)
      {

         return heap::def < TYPE >::alloc(c);

      }
#endif


      inline static void _free(TYPE * p)
      {

         heap::def < TYPE >::_free(p);

      }


   };


   template < class TYPE >
   class zero
   {

   public:

      inline static void construct(TYPE * p)
      {
         constructor::zero< TYPE >::construct(p);
      }

      inline static void construct(TYPE * p, ::count c)
      {
         constructor::zero< TYPE >::construct(p, c);

      }

      inline static void destruct(TYPE * p)
      {
         destructor::nodef< TYPE>::destruct(p);
      }
      inline static void destruct(TYPE * p, ::count c)
      {
         destructor::nodef< TYPE>::destruct(p, c);
      }


      inline static void copy(TYPE *pdst, const TYPE * psrc)
      {

         copier::def< TYPE >::copy(pdst, psrc);

      }


      inline static void copy(TYPE *pdst, const TYPE * psrc, ::count c)
      {

         copier::def< TYPE >::copy(pdst, psrc, c);

      }

#if MEMDLEAK || defined(__MCRTDBG)
      inline static TYPE * alloc(::count c, const char * pszFile, int iLine)
      {

         return heap::def < TYPE >::alloc(c, pszFile, iLine);

      }
#else
      inline static TYPE * alloc(::count c)
      {

         return heap::def < TYPE >::alloc(c);

      }
#endif


      inline static void _free(TYPE * p)
      {

         heap::def < TYPE >::_free(p);

      }


   };

   template < class TYPE >
   class sys
   {

   public:

      inline static void construct(TYPE * p)
      {
         constructor::def< TYPE >::construct(p);
      }

      inline static void construct(TYPE * p, ::count c)
      {
         constructor::def< TYPE >::construct(p, c);

      }

      inline static void destruct(TYPE * p)
      {
         destructor::def< TYPE>::destruct(p);
      }
      inline static void destruct(TYPE * p, ::count c)
      {
         destructor::def< TYPE>::destruct(p, c);
      }


      inline static void copy(TYPE *pdst, const TYPE * psrc)
      {

         copier::def< TYPE >::copy(pdst, psrc);

      }


      inline static void copy(TYPE *pdst, const TYPE * psrc, ::count c)
      {

         copier::def< TYPE >::copy(pdst, psrc, c);

      }

#if MEMDLEAK || defined(__MCRTDBG)
      inline static TYPE * alloc(::count c, const char * pszFile, int iLine)
      {

         return heap::sys < TYPE >::alloc(c, pszFile, iLine);

      }
#else
      inline static TYPE * alloc(::count c)
      {

         return heap::sys < TYPE >::alloc(c);

      }
#endif

      inline static void _free(TYPE * p)
      {

         heap::sys < TYPE >::_free(p);

      }


   };

} // namespace allocator



#include "collection_array_base.h"
#include "collection_array.h"



