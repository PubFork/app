//
//  c_os_cross_win_gdi.mm
//  c
//
//  Created by Camilo Sasuke Tsumanuma on 12/22/11.
//  Copyright (c) 2011 ca2 Desenvolvimento de Sofware Ltda. All rights reserved.
//

#include "ios_mm.h"


//oswindow set_active_window(oswindow window);



//CGContextRef get_nswindow_cgcontext(oswindow oswindow)
//{
//
////    return (CGContextRef) [[oswindow->window() graphicsContext] graphicsPort];
//    
//    return 0;
//
//}


int GetMainScreenRect(LPRECT lprect)
{

   CGRect rect = [[UIScreen mainScreen] bounds];

   lprect->left        = rect.origin.x;
   lprect->bottom      = rect.size.height - rect.origin.y;
   lprect->right       = rect.origin.x  + rect.size.width;
   lprect->top         = lprect->bottom - rect.size.height;
   
}



int GetScreenRect(LPRECT lprect, int iMonitor)
{
   return GetMainScreenRect(lprect);
}

int GetScreenCount()
{
   return 1;
}

int GetWkspaceRect(LPRECT lprect, int iMonitor)
{
   return GetMainScreenRect(lprect);
   
}
int GetWkspaceCount()
{
   return 1;
}



//WINBOOL SetForegroundWindow(oswindow window)
//{
//   
//   if(!::is_window(window))
//      return FALSE;
//   
//    /*
//     
//   [NSApp activateIgnoringOtherApps:YES];
//   
////   [NSApp setWindow : window->window()];
//
//   [window->window() makeKeyAndOrderFront: NSApp];
//   
//   [window->window() orderFrontRegardless];
//     
//     */
//   
//   set_active_window(window);
//   
//   return TRUE;
//   
//}
//
//
//WINBOOL BringWindowToTop(oswindow window)
//{
//   
//   if(!::is_window(window))
//      return FALSE;
//    
//   /*
//   
//   [NSApp activateIgnoringOtherApps:YES];
//   
////   [NSApp setWindow : window->window()];
//   
//   [window->window() makeKeyAndOrderFront: NSApp];
//   
//   [window->window() orderFrontRegardless];
//     
//   */
//   
//   set_active_window(window);
//   
//   return TRUE;
//   
//}




