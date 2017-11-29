#include "framework.h"


void throw_memory_exception()
{

   throw new memory_exception(get_app());

}


void throw_error_exception(const char * psz)
{

   throw new error_exception(get_app(),psz);

}

