//
//  os.h
//  aura
//
//  Created by Camilo Sasuke Tsumanuma on 05/01/18.
//


// C-includes

#if defined(ANDROID)
#include "aura/aura/os/ansios/ansios.h"
#include "aura/aura/os/android/android.h"
#elif defined(MACOS)
#include "aura/aura/os/ansios/ansios_file.h"
#include "aura/aura/os/ansios/ansios_multithreading.h"
#include "aura/aura/os/ansios/ansios_thread.h"
#include "aura/aura/os/apple/apple.h"
#include "aura/aura/os/macos/macos.h"
#elif defined(LINUX)
#include "aura/aura/os/ansios/ansios.h"
#include "aura/aura/os/linux/linux.h"
#elif defined(METROWIN)
#include "aura/aura/os/windows_common/windows_common_c.h"
#include "aura/aura/os/metrowin/metrowin.h"
#elif defined(WINDOWSEX)
#include "aura/aura/os/windows_common/windows_common_c.h"
#include "aura/aura/os/windows/windows.h"
#elif defined(SOLARIS)
#include "aura/aura/os/solaris/solaris.h"
#elif defined(APPLE_IOS)
#include "aura/aura/os/ansios/ansios_file.h"
#include "aura/aura/os/ansios/ansios_multithreading.h"
#include "aura/aura/os/ansios/ansios_thread.h"
#include "aura/aura/os/apple/apple.h"
#include "aura/aura/os/ios/ios.h"
#else
#error Not Supported Operational System
#endif

