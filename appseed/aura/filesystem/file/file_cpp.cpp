#include "framework.h"


namespace file
{


   CLASS_DECL_AURA string system_short_name()
   {

#ifdef METROWIN

      return "metro";

#else

      ::file::path pathSystemShortName = ::dir::localconfig() / "system_short_name.txt";

      return file_as_string_dup(pathSystemShortName).trimmed();

#endif

   }


} // namespace file



