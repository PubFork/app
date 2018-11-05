#pragma once


//#include "macos_ns_exception.h"

#include "macos_multithreading.h"



#include "macos_main.h"


bool ns_open_file(const char * psz);
void ns_set_this_default_browser();

int32_t raw_main_command_line(const char * pszCommandLine, int argc, char *argv[]);

int32_t aura_main_command_line(const char * pszParams, int argc, char *argv[]);

#ifdef cplusplus
string macos_error_string(OSStatus status);
string macos_error_description(OSStatus status);
#endif


