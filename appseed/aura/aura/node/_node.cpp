#include "framework.h"


#if defined(ANDROID)

#include "ansios/_node_ansios.cpp"
#include "android/_node_android.cpp"

#elif defined(WINDOWSEX)

#include "ansios/_node_ansios.cpp"
#include "windows/_node_windows.cpp"

#elif defined(MACOS)

#include "apple/_node_apple.cpp"
#include "macos/_node_macos.cpp"

#elif defined(APPLE_IOS)

#include "apple/_node_apple.cpp"
#include "ios/_node_ios.cpp"

#elif defined(LINUX)

#include "ansios/_node_ansios.cpp"
#include "linux/_node_linux.cpp"

#elif defined(METROWIN)

#include "metrowin/_node_metrowin.cpp"

#else

#error "Not implemented?!"

#endif


