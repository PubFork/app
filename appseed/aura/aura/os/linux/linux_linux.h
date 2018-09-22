#pragma once


#include <wchar.h>


#include "linux_graphics.h"
#include "linux_process.h"
//#include "linux_cross_win_gdi.h"
#include "linux_cross_win_file.h"
#include "linux_desktop_file.h"
#include "linux_file.h"
#include "linux_file_watcher.h"



#define ENABLE_BINRELOC



DWORD get_tick_count();




#define _fileno   fileno
#define _unlink   unlink





CLASS_DECL_AURA DWORD get_last_error();
CLASS_DECL_AURA void set_last_error(DWORD dw);


CLASS_DECL_AURA bool _istlead(int32_t ch);




bool c_xstart();

extern oswindow g_oswindowDesktop;



CLASS_DECL_AURA bool main_initialize();
CLASS_DECL_AURA bool main_finalize();

/*
bool os_on_start_application(::aura::application * papp);
::file::path app_desktop_file_path(::aura::application * papp);
::file::path app_desktop_file_path(::aura::application * papp, string strAppId);
bool linux_prepare_app_desktop_file(::aura::application * papp);
bool linux_prepare_app_desktop_file(::aura::application * papp, string strAppId);
*/

#include "linux_x11.h"

#include "linux.inl"



