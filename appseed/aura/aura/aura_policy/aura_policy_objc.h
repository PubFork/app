/////////////////////////////////////////////////////////////////////////////////////////
//
//   No Ca2 Blessings
//
//   Objective-C
//
//   O => much greater then "C"a2
//
//   Explodes!!
//
//   Boom!!
//
//   Fails by Explosion
//
//   Fails by False Identity - Not C
//
//   Fails by focusing!! By objective!! What is the objective?!?!?! What is the Goal?!?!? The Goal?!?!?! No!!! The Goal is Not The Goal!!
//
//

#pragma once


#define __M


#if defined(APPLE_IOS)

#include "aura/os/ios/ios_m.h"

#else

#include "aura/os/macos/macos_mm.h"

#endif


#undef _

#define _(str) (__ns_get_text(str))

NSString * __ns_get_text(NSString * str);

