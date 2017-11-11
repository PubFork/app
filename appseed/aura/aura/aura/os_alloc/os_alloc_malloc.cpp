#ifdef LINUX
#include <malloc.h>
#endif

BEGIN_EXTERN_C


void check_bounds(byte * p)
{

   uint_ptr * pui = (uint_ptr *)p;

   byte a[256];

   ZERO(a);

   if (memcmp(&p[sizeof(uint_ptr)], a, sizeof(a)) != 0)
   {

      output_debug_string("memory corruption before allocation");

   }
   if (memcmp(&p[sizeof(uint_ptr) + 256 + *pui], a, sizeof(a)) != 0)
   {

      output_debug_string("memory corruption after allocation");

   }

}


void * os_impl_alloc(size_t size)
{

   return malloc(size);

}


void * os_impl_realloc(void * p, size_t size)
{

   return realloc(p, size);

}


void os_impl_free(void * p)
{

   free(p);

}


size_t os_impl_size(void * p)
{

#ifdef __APPLE__

   return malloc_size(p);

#elif defined(WINDOWS)

   return _msize(p);

#else

   return malloc_usable_size(p);

#endif

}


END_EXTERN_C


