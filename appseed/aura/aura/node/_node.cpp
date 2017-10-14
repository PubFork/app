#include "framework.h"


#if defined(ANDROID)

#include "ansios/_node_ansios.cpp"
#include "android/_node_android.cpp"

#elif defined(WINDOWSEX)

#include "ansios/_node_ansios.cpp"
#include "windows/_node_windows.cpp"

#else

#include "apple/_node_apple.cpp"
#include "ios/_node_ios.cpp"
#include "linux/_node_linux.cpp"
#include "macos/_node_macos.cpp"
#include "metrowin/_node_metrowin.cpp"


#endif


