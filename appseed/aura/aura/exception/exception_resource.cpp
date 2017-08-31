#include "framework.h"


resource_exception::resource_exception(::aura::application * papp, const char * pszMessage) :
   object(papp),
   ::call_stack(papp),
   ::exception::base(papp),
   simple_exception(papp, pszMessage)
{

   debug_print(":resource_exception");

}


resource_exception::~resource_exception()
{

}

