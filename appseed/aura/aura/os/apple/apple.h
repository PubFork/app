//
//  apple.h
//  aura
//
//  Created by Camilo Sasuke Tsumanuma on 21/07/17.
//
//

#ifdef __OBJC__
#include "NSObject+DDExtensions.h"
#include "DDInvocationGrabber.h"
#endif


#include "apple_graphics.h"
#include "apple_ns_exception.h"
#include "apple_time.h"

void apple_on_open_file(const char ** psza, int iCount, const char * pszExtra);
void apple_accumulate_on_open_file(const char ** psza, int iCount, const char * pszExtra, int iMillisDelay);
void apple_on_new_file();

#ifndef __OBJC__
string apple_bundle_identifier();
string apple_executable_path();
#endif


