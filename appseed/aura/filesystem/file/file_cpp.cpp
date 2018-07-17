#include "framework.h"


namespace file
{


   CLASS_DECL_AURA string system_short_name()
   {

#ifdef METROWIN

      return "metro";

#else

      return file_as_string_dup(::dir::localconfig() / "system_short_name.txt").trimmed();

#endif

   }


} // namespace file



