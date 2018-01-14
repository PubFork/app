#include "framework.h"


CLASS_DECL_AURA void throw_cast_overflow()
{

   throw ::simple_exception(get_app(), "cast overflow");

}
