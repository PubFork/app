#include "framework.h"


void throw_memory_exception()
{

   _throw(memory_exception(get_app()));

}


void throw_error_exception(const char * psz)
{

   _throw(error_exception(get_app(),psz));

}

