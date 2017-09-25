#pragma once


#ifdef WINDOWSEX

#include "windows/windows.h"

#elif defined(APPLE_IOS)

#include "ios/ios.h"

#elif defined(MACOS)

#include "macos/macos.h"

#endif


void __node_axis_factory_exchange(::aura::application * papp);



CLASS_DECL_AXIS void __trace_message(const char * lpszPrefix,::message::message * pobj);
CLASS_DECL_AXIS void __trace_message(const char * lpszPrefix,LPMESSAGE lpmsg);



