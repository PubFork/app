#include "framework.h"


#ifdef ANDROID

#include "android/_os_android.cpp"
#include "ansios/_os_ansios.cpp"

#elif defined(WINDOWSEX)

#include "windows/_os_windows.cpp"

#elif defined(METROWIN)

#include "metrowin/_os_metrowin.cpp"

#endif


