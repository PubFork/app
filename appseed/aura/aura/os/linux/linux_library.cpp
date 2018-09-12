#include "framework.h"
#include <dlfcn.h>
#include <link.h>


CLASS_DECL_AURA void * __node_library_touch(const char * pszPath, string & strMessage)
{

   link_map * map = (link_map *) dlopen(NULL, RTLD_NOW);

   map = map->l_next->l_next;

   ::file::path path(pszPath);

   if(!::str::ends_ci(path, ".so"))
   {

      path += ".so";

   }

   if(!::str::begins_ci(path, "/") && !::str::begins_ci(path, "lib"))
   {

      path = "lib" + path;

   }

   while (map != NULL)
   {

      ::file::path pathItem(map->l_name);

      if(path == pathItem || path == pathItem.name())
      {

         return __node_library_open(map->l_name, strMessage);

      }

      map = map->l_next;

   }

   return NULL;

}

CLASS_DECL_AURA void * __node_library_open(const char * pszPath, string & strMessage)
{

   string strPath(pszPath);

   if(strPath == "os")
   {

      strPath = "ca2os";

   }
   else if(strPath == "app_sphere")
   {

      strPath = "basesphere";

   }

   if(strstr_dup(strPath, ".") == NULL)
      strPath += ".so";

   if(strstr((const char *) strPath, "/") == NULL && !str_begins_dup(strPath, "lib"))
      strPath = "lib" + strPath;

   void * plibrary = dlopen(strPath, RTLD_LOCAL | RTLD_NOW | RTLD_NODELETE);

   if(plibrary == NULL)
   {

      // pubs.opengroup.org contribution

      int iError = errno;

      const char * psz = strerror(iError);

      if(psz != NULL)
      {

         strMessage += psz;

      }

      char *errstr;

      errstr = dlerror();

      if (errstr != NULL)
      {

         strMessage += errstr;

      }

   }
   else
   {

      strMessage += "Successfully loaded library ";

      strMessage += pszPath;

   }

   return plibrary;

}


CLASS_DECL_AURA void * __node_library_open_ca2(const char * pszPath, string & strMessage)
{

   void * plibrary = dlopen(pszPath, RTLD_LOCAL | RTLD_NOW | RTLD_NODELETE);

   int iError = errno;

   const char * psz = strerror(iError);

   if(psz != NULL)
   {

      strMessage += psz;

   }

   const char * psz2 = dlerror();

   if(psz2 != NULL)
   {

      strMessage += psz2;

   }

   return plibrary;

}


CLASS_DECL_AURA bool __node_library_close(void * plibrary)
{

   if(plibrary == NULL)
      return false;

   return dlclose(plibrary) == 0;

}


CLASS_DECL_AURA void * __node_library_raw_get(void * plibrary,const char * pszEntryName)
{

   return dlsym(plibrary, pszEntryName);

}




























