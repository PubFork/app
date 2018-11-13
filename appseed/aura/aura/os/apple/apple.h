//
//  apple.h
//  aura
//
//  Created by Camilo Sasuke Tsumanuma on 21/07/17.
//
//
#pragma once

// C and Objective-C include

#ifdef __OBJC__
#include "NSObject+DDExtensions.h"
#include "DDInvocationGrabber.h"

char * ns_string(NSString * str);

#endif


void copy(CGRect & rect, LPCRECT lpcrect);
void copy(LPRECT lprect, const CGRect & rectSrc);

CGRect mm_get_workspace_rect();

void window_copy(CGRect & rect, LPCRECT lpcrect);
void window_copy(LPRECT lprect, const CGRect & rectSrc);


#include "apple_graphics.h"
#include "apple_ns_exception.h"
#include "apple_time.h"

void apple_on_open_file(const char ** psza, int iCount, const char * pszExtra);
void apple_accumulate_on_open_file(const char ** psza, int iCount, const char * pszExtra);
void apple_on_new_file();


void ns_application_main(int argc, char *argv[], const char * pszCommandLine);



int is_window(oswindow window);

void ns_main_sync(dispatch_block_t block);
void ns_main_async(dispatch_block_t block);

