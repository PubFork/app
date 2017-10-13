#include "framework.h"


#include "os_alloc.cpp"
#include "os_binreloc.cpp"
#include "os_file.cpp"
#include "os_process.cpp"
#include "os_windowing.cpp"


#include "cross/_os_cross.cpp"


#if !defined(ANDROID)
#include "os_file.cpp"
#include "os_http.cpp"
#include "os_os.cpp"
#include "os_thread.cpp"
#include "os_serial.cpp"
#endif


#if defined(ANDROID)
#include "ansios/_os_ansios.cpp"
#include "android/_os_android.cpp"
#endif


