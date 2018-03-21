#include "framework.h"


#include "os_alloc.cpp"
#include "os_binreloc.cpp"
#include "os_file.cpp"
#include "os_process.cpp"
#include "os_windowing.cpp"


#include "cross/_os_cross.cpp"


#if !defined(ANDROID)
#include "os_debug.cpp"
#include "os_http.cpp"
#include "os_thread.cpp"
#endif
#include "os_os.cpp"


#if !defined(ANDROID) && !defined(METROWIN)
#include "os_serial.cpp"
#endif


#if defined(ANDROID)
#include "ansios/_os_ansios.cpp"
#include "android/_os_android.cpp"
#elif defined(WINDOWSEX)

#include "ansios/_os_ansios.cpp"
#include "windows/_os_windows.cpp"
#include "windows_common/_os_windows_common.cpp"
#elif defined(LINUX)
#include "ansios/_os_ansios.cpp"
#include "linux/_os_linux.cpp"
#include "x11/_os_x11.cpp"
#elif defined(METROWIN)

#include "ansios/_os_ansios.cpp"
#include "metrowin/_os_metrowin.cpp"
#include "windows_common/_os_windows_common.cpp"

#else
#include "ansios/_os_ansios.cpp"
#include "android/_os_android.cpp"
#include "ansios/_os_ansios.cpp"
#include "metrowin/_os_metrowin.cpp"
#include "windows_common/_os_windows_common.cpp"
#include "ansios/_os_ansios.cpp"
#include "linux/_os_linux.cpp"
#include "x11/_os_x11.cpp"
#include "ansios/_os_ansios.cpp"
#include "windows/_os_windows.cpp"
#include "windows_common/_os_windows_common.cpp"


#endif


