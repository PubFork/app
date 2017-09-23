#pragma once


#define CA2_X11_WINDOW_LONG "ca2_x11_window_long"
#define CA2_X11_WINDOW_LONG_STYLE "ca2_x11_window_long_style"
#define CA2_X11_WINDOW_LONG_STYLE_EX "ca2_x11_window_long_style_ex"



#include "linux_osdisplay.h"


#include "linux_oswindow.h"


#include "linux_user_impl.h"


#include "base/graphics/graphics_window_graphics.h"


#include "linux_window_xlib.h"



WINBOOL IsWindowVisibleRaw(oswindow w);
