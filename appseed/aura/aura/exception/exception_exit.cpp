#include "framework.h"


exit_exception::exit_exception(::aura::application * papp, const char * pszMessage) :
   object(papp),
   ::call_stack(papp),
   ::exception::base(papp),
   ::simple_exception(papp, pszMessage)
{

   m_iCheck = 0;

   if(pszMessage == NULL)
   {

      debug_print(":exit(NULL)");

   }
   else
   {

      debug_print(":exit(\"%s\")",pszMessage);

   }

   

}


exit_exception::exit_exception(const exit_exception & e) :
   object(e),
   ::call_stack(e),
   ::exception::base(e),
   ::simple_exception(e)
{
   m_iCheck = e.m_iCheck;
   debug_print(":exit(copy)");

}


exit_exception::~exit_exception()
{

}


void exit_excepation::post_quit(::thread * pthread)
{
   
   try
   {
   
      if(m_eexit == exit_none)
      {
         
         return;
      
      }
   
      if(pthread == NULL)
      {
      
         pthread = ::get_thread();
      
      }
   
      if(pthread == NULL)
      {
      
         return;
      
      }
   
      if(e.m_eexit == ::exit_thread)
      {
   
         ::multithreading::post_quit(pthread);
      
         return;
   
      }
   
      ::aura::application * papp = dynamic_cast < ::aura::application * >(pthread);
   
      if(papp == NULL)
      {
      
         papp = pthread->m_pauraapp;
      
      }
   
      if(papp == NULL)
      {
      
         return;
      
      }
   
      if(e.m_eexit == ::exit_application)
      {
      
         ::multithreading::post_quit(papp);
      
         return;
      
      }
   
      ::aura::session * psession = dynamic_cast < ::aura::session * >(papp);
   
      if(psession == NULL)
      {
      
         psession = papp->m_paurasession;
      
      }
      
      if(e.m_eexit == ::exit_session)
      {
         
         if(psession == NULL)
         {
          
            return NULL;
            
         }
         
         ::multithreading::post_quit(psession)
         
      }
      
      ::aura::system * psystem = dynamic_cast < ::aura::system * >(papp);
      
      if(psystem == NULL)
      {
         
         psystem = papp->m_paurasystem;
         
      }
      
      if(e.m_eexit == ::exit_system)
      {
         
         if(psystem == NULL)
         {
            
            return NULL;
            
         }
         
         ::multithreading::post_quit(psystem)
         
      }

   }
   catch(...)
   {
      
   }

}
