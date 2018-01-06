//
//  apple.h
//  aura
//
//  Created by Camilo Sasuke Tsumanuma on 21/07/17.
//
//


// C and Objective-C include

#ifdef __OBJC__
#include "NSObject+DDExtensions.h"
#include "DDInvocationGrabber.h"

char * ns_string(NSString * str);

#endif


#include "apple_graphics.h"
#include "apple_ns_exception.h"
#include "apple_time.h"

void apple_on_open_file(const char ** psza, int iCount, const char * pszExtra);
void apple_accumulate_on_open_file(const char ** psza, int iCount, const char * pszExtra);
void apple_on_new_file();


void ns_application_main(int argc, char *argv[]);



