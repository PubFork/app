#pragma once


#ifdef WINDOWS

typedef HANDLE HTHREAD;

typedef uint32_t IDTHREAD;

inline int id_thread_equals(IDTHREAD a, IDTHREAD b) {return a==b;}

#else

#include <pthread.h>

#define HTHREAD pthread_t

#define IDTHREAD pthread_t

inline int id_thread_equals(IDTHREAD a, IDTHREAD b) {return pthread_equal(a, b);}

#endif

BEGIN_EXTERN_C

CLASS_DECL_AURA uint32_t thread_alloc();
CLASS_DECL_AURA int_bool thread_free(uint32_t dwIndex);
CLASS_DECL_AURA void * thread_get_data(uint32_t dwIndex);
CLASS_DECL_AURA int_bool thread_set_data(uint32_t dwIndex,void * lpTlsValue);
CLASS_DECL_AURA void thread_shutdown();

END_EXTERN_C

CLASS_DECL_AURA void set_main_thread(HTHREAD hThread);
CLASS_DECL_AURA void set_main_thread_id(IDTHREAD uiThread);
CLASS_DECL_AURA HTHREAD get_main_thread();
CLASS_DECL_AURA IDTHREAD get_main_thread_id();

