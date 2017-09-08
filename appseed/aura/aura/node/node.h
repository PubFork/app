#pragma once


#ifdef WINDOWSEX

#include "windows/windows.h"

#elif defined(METROWIN)

#include "metrowin/metrowin.h"

#elif defined(MACOS)

#include "macos/macos.h"

#elif defined(APPLE_IOS)

#include "ios/ios.h"

#elif defined(LINUX)

#include "linux/linux.h"

#endif


CLASS_DECL_AURA void __node_aura_factory_exchange(::aura::application * papp);
CLASS_DECL_AURA void __node_init_main_data(::aura::application * papp,HINSTANCE hInstance,HINSTANCE hPrevInstance,LPTSTR lpCmdLine,int32_t nCmdShow);

