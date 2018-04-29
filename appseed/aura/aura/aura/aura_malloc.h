//
//  aura_malloc.h
//  aura
//
//  Created by Camilo Sasuke Tsumanuma on 26/11/17. tbs in <3
//

#pragma once

namespace aura
{

   //    template < typename P >
   //    void free(P * & p)
   //    {
   //
   //        if(p != NULL)
   //        {
   //
   //            ::free((void *) p);
   //
   //            p = NULL;
   //
   //        }
   //
   //    }

   template < typename POINTER >
   class malloc
   {
   public:


      POINTER     m_p;
      int64_t     m_iSize;

      malloc(POINTER p = NULL)
      {

         m_iSize = -1;
         m_p = p;

      }

      ~malloc()
      {

         free();

      }

      operator POINTER() { return (POINTER) m_p; }


      POINTER alloc(size_t size)
      {

         if(m_p != NULL)
         {

            m_p = (POINTER) ::realloc(m_p, size);

         }
         else
         {

            m_p = (POINTER) ::malloc(size);

         }

         if (m_p != NULL)
         {

            m_iSize = size;

         }

         return m_p;

      }

      POINTER calloc(::count c)
      {

         free();

         m_iSize = c * sizeof(*m_p);

         m_p = calloc(m_iSize);

         if (m_p == NULL)
         {

            m_iSize = -1;

         }

         return m_p;

      }

      void free()
      {

         ::aura::free(m_p);

         m_iSize = -1;

      }

      template < typename POINTER2 >
      malloc & operator = ( POINTER2 p)
      {

         if((POINTER)p == m_p)
         {

            return *this;

         }

         free();

         m_p = (POINTER)p;

         return *this;

      }

   };

} // namespace aura

