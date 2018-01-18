#include <stdlib.h>
#include "ace.h"

BEGIN_EXTERN_C

//PFN_MEMORY_ALLOC g_pfnAceAlloc = &malloc;
//PFN_MEMORY_REALLOC g_pfnAceRealloc = &realloc;
//PFN_MEMORY_FREE g_pfnAceFree = &free;
PFN_MEMORY_ALLOC g_pfnAceAlloc = NULL;
PFN_MEMORY_REALLOC g_pfnAceRealloc = NULL;
PFN_MEMORY_FREE g_pfnAceFree = NULL;
PFN_MEMORY_SIZE g_pfnAceSize = NULL;


int g_ace_set = 0;


#define INITIAL_ACE 0xFFFFFFFFFFFFFFF7
#define ACE_SET 0xFFFFFFFFFFFFFFFF


CLASS_DECL_ACE void * ace_memory_alloc(size_t s)
{

   int64_t * p;

   if(g_ace_set)
   {

      p = (int64_t *) g_pfnAceAlloc(s + sizeof(int64_t));

      p[0] = ACE_SET;

   }
   else
   {

      p = (int64_t *) malloc(s + sizeof(int64_t));

      p[0] = INITIAL_ACE;

   }

   p++;

   return p;

}


CLASS_DECL_ACE void * ace_memory_realloc(void * pParam, size_t s)
{

   int64_t * p = (int64_t *) pParam;

   p--;

   if(p[0] == ACE_SET)
   {

      p = (int64_t *) g_pfnAceRealloc(p, s + sizeof(int64_t));

      p[0] = 1;

   }
   else if(p[0] == INITIAL_ACE)
   {

      p = (int64_t *) realloc(p, s + sizeof(int64_t));

      p[0] = 0;

   }
   else
   {

      return g_pfnAceRealloc(pParam, s);

   }

   p++;

   return p;

}


CLASS_DECL_ACE void ace_memory_free(void * pParam)
{

   int64_t * p = (int64_t *) pParam;

   if(((int_ptr) p) < 1024 * 16)
   {

      return;

   }

   p--;

   if(p[0] == ACE_SET)
   {

      g_pfnAceFree(p);

   }
   else if(p[0] == INITIAL_ACE)
   {

      free(p);

   }
   else
   {

      g_pfnAceFree(pParam);

   }


}


CLASS_DECL_ACE size_t ace_memory_size(void * pParam)
{

   int64_t * p = (int64_t *) pParam;

   p--;

   if(p[0] == ACE_SET)
   {

      return g_pfnAceSize(p) - sizeof(int64_t);

   }
   else if(p[0] == INITIAL_ACE)
   {

      throw "memory size error: invalid call";

   }
   else
   {

      return g_pfnAceSize(pParam);

   }

   return 0;

}

CLASS_DECL_ACE void ace_set_alloc(PFN_MEMORY_ALLOC palloc, PFN_MEMORY_REALLOC prealloc, PFN_MEMORY_FREE pfree, PFN_MEMORY_SIZE psize)
{

   g_pfnAceAlloc = palloc;

   g_pfnAceRealloc = prealloc;

   g_pfnAceFree = pfree;

   g_pfnAceSize = psize;

   g_ace_set = 1;

}

const char * g_pszCacheDir;

CLASS_DECL_EXPORT void android_set_cache_dir(const char * pszDir)
{

   g_pszCacheDir = pszDir;

}

CLASS_DECL_EXPORT const char * android_get_cache_dir()
{
   return g_pszCacheDir;
}


const char * g_pszIosHome;

CLASS_DECL_EXPORT void ios_set_home(const char * pszDir)
{

   g_pszIosHome = pszDir;

}

CLASS_DECL_EXPORT const char * ios_get_home()
{
   return g_pszIosHome;
}

const char * g_pszIosTemp;


CLASS_DECL_EXPORT void ios_set_temp(const char * pszDir)
{

   g_pszIosTemp = pszDir;

}

CLASS_DECL_EXPORT const char * ios_get_temp()
{
   return g_pszIosTemp;
}


END_EXTERN_C
