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

#ifdef APPLEOS


#define ALIGN_BYTE_COUNT (sizeof(size_t) * 2)


#else


//#define ALIGN_BYTE_COUNT (sizeof(size_t))


#define ALIGN_BYTE_COUNT 16


#endif
int g_ace_set = 0;


#define INITIAL_ACE 0xff
#define ACE_SET 0xf7


CLASS_DECL_ACE void * ace_memory_alloc(size_t s)
{

   byte * p;

   if(g_ace_set)
   {

      p = (byte *) g_pfnAceAlloc(s + ALIGN_BYTE_COUNT);

      p[0] = ACE_SET;

   }
   else
   {

      p = (byte *) malloc(s + ALIGN_BYTE_COUNT);

      p[0] = INITIAL_ACE;

   }

   p+=ALIGN_BYTE_COUNT;

   return p;

}


CLASS_DECL_ACE void * ace_memory_realloc(void * pParam, size_t s)
{

   byte * p = (byte *) pParam;

   p-=ALIGN_BYTE_COUNT;

   if(p[0] == ACE_SET)
   {

      p = (byte *) g_pfnAceRealloc(p, s + ALIGN_BYTE_COUNT);

      p[0] = ACE_SET;

   }
   else if(p[0] == INITIAL_ACE)
   {

      p = (byte *) realloc(p, s + ALIGN_BYTE_COUNT);

      p[0] = INITIAL_ACE;

   }
   else
   {

      return g_pfnAceRealloc(pParam, s);

   }

   p+=ALIGN_BYTE_COUNT;

   return p;

}


CLASS_DECL_ACE void ace_memory_free(void * pParam)
{

   byte * p = (byte *) pParam;

   if(((int_ptr) p) < 1024 * 16)
   {

      return;

   }

   p-=ALIGN_BYTE_COUNT;

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

   byte * p = (byte *)pParam;

   p -= ALIGN_BYTE_COUNT;

   if (p[0] == ACE_SET)
   {

      return g_pfnAceSize(p) - ALIGN_BYTE_COUNT;

   }
   else if (p[0] == INITIAL_ACE)
   {

      throw "memory size error: invalid call";

   }
   else
   {

      return g_pfnAceSize(pParam) - ALIGN_BYTE_COUNT;

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


static char * g_pszCacheDir;


CLASS_DECL_EXPORT void nodeos_set_cache_dir(const char * pszDir)
{

   if (g_pszCacheDir != NULL)
   {

      free(g_pszCacheDir);

   }

   g_pszCacheDir = _strdup(pszDir);

}


CLASS_DECL_EXPORT const char * android_get_cache_dir()
{

   return g_pszCacheDir;

}


static char * g_pszHome;


CLASS_DECL_EXPORT void nodeos_set_home(const char * pszDir)
{

   if (g_pszHome != NULL)
   {

      free(g_pszHome);

   }

   g_pszHome = _strdup(pszDir);

}


CLASS_DECL_EXPORT const char * nodeos_get_home()
{

   return g_pszHome;

}


static char * g_pszTemp = NULL;


CLASS_DECL_EXPORT void nodeos_set_temp(const char * pszDir)
{

   if (g_pszTemp != NULL)
   {

      free(g_pszTemp);

   }

   g_pszTemp = _strdup(pszDir);

}


CLASS_DECL_EXPORT const char * nodeos_get_temp()
{

   return g_pszTemp;

}


END_EXTERN_C
