#pragma once


#include "aura/os/ansios/ansios_file.h"


#include "linux_debug.h"

#include "linux_graphics.h"




BEGIN_EXTERN_C

off_t tell64(int fd);

END_EXTERN_C






int_bool axis_TranslateMessage(const MESSAGE * lpmessage);
LRESULT axis_DispatchMessage(const MESSAGE * lpmessage);


oswindow GetCapture();
oswindow SetCapture(oswindow window);
WINBOOL ReleaseCapture();
oswindow SetFocus(oswindow window);
oswindow GetFocus();
oswindow GetWindow(oswindow window, int iParentHood);
oswindow GetActiveWindow();
oswindow SetActiveWindow(oswindow window);
WINBOOL DestroyWindow(oswindow window);
oswindow GetDesktopWindow();


#include "linux_windowing.h"





