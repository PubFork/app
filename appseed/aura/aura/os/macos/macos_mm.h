//
//  macos_mm.h
//  aura
//
//  Created by Camilo Sasuke Tsumanuma on 2013-09-17.
//
//
#pragma once

#include "aura/aura/aura/aura.h"

#ifdef DEBUG
#undef DEBUG
#define DEBUG 1
#else
#define DEBUG 0
#endif

#import <Foundation/Foundation.h>
#import <AppKit/AppKit.h>

#if DEBUG
#undef DEBUG
#define DEBUG
#else
#undef DEBUG
#endif

#include "app/appseed/aura/aura/os/apple/apple.h"

//#include "NSObject+DDExtensions.h"
//#include "DDInvocationGrabber.h"
#include "mmos.h"
#include "macos_user.h"

#undef _

#define _(str) (__ns_get_text(str))

NSString * __ns_get_text(NSString * str);
NSString * __ns_get_text(const char * psz);

//#include "macos_windowing.h"
