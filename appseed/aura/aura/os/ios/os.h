//
//  os.h
//  aura
//
//  Created by Carlos Gustavo Cecyn Lundgren on 08/07/15.
//
//

#pragma once


#ifdef __cplusplus

#ifdef __OBJC__

typedef UIWindow * ui_window_ptr;

#else

typedef void * ui_window_ptr;

#endif

struct plane_system
{
   
   ::aura::system *    m_psystem;
   
   plane_system(const char * pszId);
   
   ui_window_ptr init_part_2ex(CGRect rect);
   
   void begin();
   
};

#endif


#include "ios_file_watcher.h"


int GetMainScreenRect(LPRECT lprect);

int GetScreenRect(LPRECT lprect, int iMonitor);

int GetScreenCount();

int GetWkspaceRect(LPRECT lprect, int iMonitor);

int GetWkspaceCount();


#pragma once



#include <stdarg.h>
#include <wchar.h>

#include "ios_process.h"
#include "ios_cross_win_gdi.h"
#include "ios_file_watcher.h"
//#include "ios_thread.h"



//#define ENABLE_BINRELOC


DWORD get_tick_count();

//#define ARGB(a, r,g,b)          ((COLORREF)(((BYTE)(r)|((WORD)((BYTE)(g))<<8))|(((DWORD)(BYTE)(b))<<16)|(((DWORD)(BYTE)(a))<<24)))


#define _fileno   fileno
#define _unlink   unlink


/*
 #define STATUS_WAIT_0            ((DWORD   ) 0x00000000L)
 #define STATUS_ABANDONED_WAIT_0  ((DWORD   ) 0x00000080L)
 #define STATUS_USER_APC          ((DWORD   ) 0x000000C0L)
 #define STATUS_TIMEOUT           ((DWORD   ) 0x00000102L)
 */

#define WAIT_FAILED              ((DWORD   ) 0xFFFFFFFFL)
#define WAIT_OBJECT_0            ((DWORD   ) STATUS_WAIT_0 + 0)

#define WAIT_ABANDONED           ((DWORD   ) STATUS_ABANDONED_WAIT_0 + 0)
#define WAIT_ABANDONED_0         ((DWORD   ) STATUS_ABANDONED_WAIT_0 + 0)

#define WAIT_IO_COMPLETION                   STATUS_USER_APC

// based on Windows implementation and also a good limit for iterations with nanosleep and multiple locks in objects up to MAXIMUM_WAIT_OBJECTS in a single call
#define MAXIMUM_WAIT_OBJECTS      64


/*WINBOOL
 WINAPI
 __win_CloseThread(
 HANDLE hThread
 );
 */

oswindow GetCapture();
oswindow SetCapture(oswindow window);
WINBOOL ReleaseCapture();
oswindow SetFocus(oswindow window);
oswindow GetFocus();
oswindow GetActiveWindow();
oswindow SetActiveWindow(oswindow window);


//void GetMainScreenRect(LPRECT lprect);

WINBOOL SetForegroundWindow(oswindow window);
WINBOOL BringWindowToTop(oswindow window);

void ns_redraw_window(oswindow window);



void copy(CGRect & rect, LPCRECT lpcrect);
void copy(LPRECT lprect, const CGRect & rectSrc);
void window_copy(CGRect & rect, LPCRECT lpcrect);
void window_copy(LPRECT lprect, const CGRect & rectSrc);
#ifdef MM
void copy(NSRect & rect, LPCRECT lpcrect);
void copy(LPRECT lprect, const NSRect & rectSrc);
void window_copy(NSRect & rect, LPCRECT lpcrect);
void window_copy(LPRECT lprect, const NSRect & rectSrc);
#endif