#include "framework.h"



#ifdef ANDROID

#include "android/_node_android.cpp"

#elif defined(WINDOWSEX)

#include "windows/_windows_node.cpp"

#endif
