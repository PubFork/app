#include "framework.h"


namespace user
{


   bool gsettings_get(string & str, const char * pszSchema, const char * pszKey)
   {

      char * psz = gsettings_get_malloc(pszSchema, pszKey);

      if(psz == NULL)
      {

         return false;

      }

      try
      {

         str = psz;

      }
      catch(...)
      {

      }

      try
      {

         ::free(psz);

      }
      catch(...)
      {

      }

      return true;

   }


}



