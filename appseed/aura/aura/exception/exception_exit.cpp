#include "framework.h"


exit_exception::exit_exception(::aura::application * papp, e_exit eexit, const char * pszMessage) :
   object(papp),
   ::call_stack(papp),
   ::exception::base(papp),
   ::simple_exception(papp, pszMessage)
{

   m_eexit = eexit;

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


bool exit_exception::post_quit(::thread * pthread)
{

   try
   {

      if(m_eexit == exit_none)
      {

         return true;

      }

      if(pthread == NULL)
      {

         pthread = ::get_thread();

      }

      if(pthread == NULL)
      {

         return false;

      }

      if(m_eexit == ::exit_thread)
      {

         ::multithreading::post_quit(pthread);

         return true;

      }

      ::aura::application * papp = dynamic_cast < ::aura::application * >(pthread);

      if(papp == NULL)
      {

         papp = pthread->m_papp;

      }

      if(papp == NULL)
      {

         return false;

      }

      if(m_eexit == ::exit_application)
      {

         ::multithreading::post_quit(papp);

         return true;

      }

      ::aura::session * psession = dynamic_cast < ::aura::session * >(papp);

      if(psession == NULL)
      {

         psession = papp->m_psession;

      }

      if(m_eexit == ::exit_session)
      {

         if(psession == NULL)
         {

            return false;

         }

         ::multithreading::post_quit(psession);

         return true;

      }

      ::aura::system * psystem = dynamic_cast < ::aura::system * >(papp);

      if(psystem == NULL)
      {

         psystem = papp->m_psystem;

      }

      if(m_eexit == ::exit_system)
      {

         if(psystem == NULL)
         {

            return false;

         }

         ::multithreading::post_quit(psystem);

         return true;

      }

   }
   catch(...)
   {

   }

   return false;

}
