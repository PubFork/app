#include "framework.h"


#ifndef WINDOWSEX

#include "windows/_os_cross_windows.cpp"

#endif


#if !defined(ANDROID) && !defined(APPLE) && !defined(LINUX)

#include "ansios/_os_cross_ansios.cpp"

#endif