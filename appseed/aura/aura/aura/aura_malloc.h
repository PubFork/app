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
      
      
      POINTER m_p;
      
      malloc(POINTER p = NULL)
      {
         
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
         
         return m_p;
         
      }
      
      POINTER calloc(::count c)
      {
         
         return alloc(c * sizeof(*m_p));
         
      }
      
      void free()
      {
         
         ::aura::free(m_p);
         
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

