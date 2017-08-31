#pragma once


#include "ansios_file.h"
#include "ansios_thread.h"
#include "ansios_multithreading.h"



//extern int_bool (* g_messageboxa)(oswindow interaction_impl, const char * psz, const char * pszTitle, uint32_t uiFlags);


void set_command_line_dup(const char * psz);
string get_command_line_dup();
