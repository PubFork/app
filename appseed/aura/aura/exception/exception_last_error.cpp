#include "framework.h"


last_error_exception::last_error_exception(::aura::application * papp) :
   object(papp),
   ::call_stack(papp),
   ::exception::base(papp),
   hresult_exception(papp, HRESULT_FROM_WIN32(::get_last_error()))
{

   debug_print(":last_error_exception(%d)",::get_last_error());

}


last_error_exception::~last_error_exception()
{

}
