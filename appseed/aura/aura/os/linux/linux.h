#pragma once


#include "aura/os/ansios/ansios_file.h"


#include "linux_debug.h"

#include "linux_graphics.h"




BEGIN_EXTERN_C

off_t tell64(int fd);

END_EXTERN_C






int_bool axis_TranslateMessage(const MESSAGE * lpmessage);
LRESULT axis_DispatchMessage(const MESSAGE * lpmessage);


oswindow get_capture();
oswindow set_capture(oswindow window);
WINBOOL release_capture();
oswindow set_focus(oswindow window);
oswindow get_focus();
oswindow get_window(oswindow window, int iParentHood);
oswindow get_active_window();
oswindow set_active_window(oswindow window);
WINBOOL destroy_window(oswindow window);
oswindow get_desktop_window();



#include "linux_windowing.h"





