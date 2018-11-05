#pragma once


class CLASS_DECL_AURA simple_exception : 
   virtual public ::exception::base
{
public:
   
   
   simple_exception(::aura::application * papp, const char * pszMessage = NULL);
   simple_exception(const char * pszMessage, ::aura::application * papp = ::get_app());
   virtual ~simple_exception();


   virtual bool get_error_message(string & str, PUINT pnHelpContext = NULL);


};


