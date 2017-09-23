#pragma once


void __node_base_factory_exchange(::aura::application * papp);




#if defined(APPLE_IOS)

#include "ios/ios.h"

#elif defined(MACOS)

#include "macos/macos.h"

#elif defined(WINDOWSEX)

#include "windows/windows.h"

#elif defined(METROWIN)

#include "metrowin/metrowin.h"

#endif

