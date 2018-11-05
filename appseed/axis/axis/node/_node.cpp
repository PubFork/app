#include "framework.h"



#ifdef ANDROID

#include "android/_node_android.cpp"

#elif defined(WINDOWSEX)

#include "windows/_node_windows.cpp"

#elif defined(METROWIN)

#include "metrowin/_node_metrowin.cpp"

#else

#include "windows/_windows_node.cpp"

#endif
