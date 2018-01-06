//
//  ios_windowing.hpp
//  ios_aura
//
//  Created by Camilo Sasuke Tsumanuma on 10/12/17.
//
#pragma once


int GetMainScreenRect(LPRECT lprect);

int GetScreenRect(LPRECT lprect, int iMonitor);

int GetScreenCount();

int GetWkspaceRect(LPRECT lprect, int iMonitor);

int GetWkspaceCount();


//
//  ios_window.h
//  aura
//
//  Created by Camilo Sasuke Tsumanuma on 2013-09-17.
//
//


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







#define GetWindowLong GetWindowLongA
#define SetWindowLong SetWindowLongA


void DeactivateWindow(oswindow window);


oswindow GetWindow(oswindow window, int iParentHood);



