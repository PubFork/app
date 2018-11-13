//
//  aura_application_ptra.cpp
//  aura
//
//  Created by Camilo Sasuke Tsumanuma on 12/11/18.
//

#include "framework.h"


namespace aura
{

   
   application_ptra::application_ptra(::aura::application * papp) :
      ::object(papp)
   {
   
      if(::is_set(m_papp))
      {
         
         m_papp->defer_create_mutex();
         
         m_pmutex = m_papp->m_pmutex;
         
      }
      
   }

   application_ptra::application_ptra(const application_ptra & a):
   spa(application)(a)
   {
      
   }
   
   
   application_ptra & application_ptra::operator = (const application_ptra & a)
   {
      
      spa(application)::operator = (a);
      
      return *this;
      
   }
   
   
#if defined(MOVE_SEMANTICS)
   
   
   application_ptra::application_ptra(application_ptra && a):
   spa(application)(a)
   {
      
   }
   
   
   application_ptra & application_ptra::operator = (application_ptra && a)
   {
      
      spa(application)::operator = (a);
      
      return *this;
      
   }
   
#endif

   application_ptra::~application_ptra()
   {
      
      if(::is_set(m_papp))
      {
         
         if(m_papp->m_pmutex == m_pmutex)
         {
          
            m_pmutex = NULL;
            
         }
         
      }
      
   }

   
   application * application_ptra::find_by_app_name(string strAppName)
   {
      
      synch_lock sl(m_pmutex);
      
      restart:
   
      for (auto & papp : *this)
      {
      
         try
         {
         
            if (papp.is_null())
            {
               
               remove(papp);
               
               goto restart;
               
            }
         
            if (papp->m_strAppName == strAppName)
            {
            
               return papp;
            
            }
            
         }
         catch (...)
         {
         
         }
      
      }
   
      return NULL;
   
   }


   application * application_ptra::find_running_defer_try_quit_damaged(string strAppName)
   {
   
      sp(application) papp = find_by_app_name(strAppName);
   
      if (papp.is_null())
      {
         
         return NULL;
         
      }
   
      if (papp->safe_is_running())
      {
         
         return papp;
         
      }
   
      try
      {
      
         papp->post_quit();
      
      }
      catch (...)
      {
      
      }
   
      try
      {
         
         papp.release();
         
      }
      catch (...)
      {
         
      }
   
      return NULL;
   
   }


   bool application_ptra::lookup(string strAppName, sp(::aura::application) & papp)
   {
   
      papp = find_running_defer_try_quit_damaged(strAppName);
      
      return papp.is_set();
   
   }
   

} // namespace aura




