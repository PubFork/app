#pragma once


enum e_exit
{
   
   exit_none,
   exit_thread,
   exit_application,
   exit_session,
   exit_system,
   
};


class CLASS_DECL_AURA exit_exception : 
   virtual public simple_exception
{
public:

   
   int         m_iCheck;
   e_exit      m_eexit;
   
   
   exit_exception(::aura::application * papp, e_exit eexit, const char * pszMessage = NULL);
   exit_exception(const exit_exception & e);
   virtual ~exit_exception();

   virtual void post_quit(::thread * pthread);

};
