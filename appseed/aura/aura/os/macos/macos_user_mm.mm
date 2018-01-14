        //
//  macos_user.mm
//  base
//
//  Created by Camilo Sasuke Tsumanuma on 2013-09-17.
//
//

#include "macos_mm.h"
#include "aura/aura/node/macos/RoundWindowApp.h"



void copy(LPRECT lprectDst, const CGRect & rectSrc);


namespace macos
{

   CGFloat get_system_main_menu_bar_height()
   {
      return [[[NSApplication sharedApplication] mainMenu] menuBarHeight];
   }

   CGFloat get_system_dock_height()
   {
      return [[[NSApplication sharedApplication] mainMenu] menuBarHeight];
   }

} // namespace macos


CGRect g_rectWorkspace;


void mm_init_workspace_rect()
{
   
   g_rectWorkspace = [[NSScreen mainScreen] frame];
   
}


CGRect mm_get_workspace_rect()
{
   
   return g_rectWorkspace;
   
}


 
 
int GetMainScreenRect(LPRECT lprect)
{
   
   window_copy(lprect, [[NSScreen mainScreen] frame]);
   
   return 0;
   
}

int GetScreenRect(LPRECT lprect, int iMonitor)
{
   
   if([NSScreen screens] == nil)
   {
      
      return -1;
      
   }
   
   if(iMonitor >= [NSScreen screens].count)
   {
      
      return -1;
      
   }
   
   try
   {
      
      window_copy(lprect, [[[NSScreen screens] objectAtIndex:iMonitor ] frame]);
      
   }
   catch (...)
   {
      
      return -1;
      
   }
                   
   
   
   return iMonitor;
   
}


int GetScreenCount()
{
   
   return (int) [[NSScreen screens] count];
   
}



int GetWkspaceRect(LPRECT lprect, int iMonitor)
{
   
   window_copy(lprect, [[[NSScreen screens] objectAtIndex:iMonitor ] visibleFrame]);
   
   return iMonitor;
   
}


int GetWkspaceCount()
{
   
   return (int) [[NSScreen screens] count];
   
}




void ns_app_run()
{
   
   [NSApp run];
   
}







oswindow SetActiveWindow(oswindow window);



CGContextRef get_nswindow_cgcontext(oswindow oswindow)
{
   
   return (CGContextRef) [[oswindow->window() graphicsContext] graphicsPort];
   
}





WINBOOL SetForegroundWindow(oswindow window)
{
   
   if(!::IsWindow(window))
      return FALSE;
   
   [[NSApp dd_invokeOnMainThreadAndWaitUntilDone:FALSE] activateIgnoringOtherApps:YES];
   
   //   [NSApp setWindow : window->window()];
   
   [[window->window() dd_invokeOnMainThreadAndWaitUntilDone:FALSE] makeKeyWindow];
   
   [[window->window() dd_invokeOnMainThreadAndWaitUntilDone:FALSE] makeMainWindow];
   
   SetActiveWindow(window);
   
   return TRUE;
   
}


WINBOOL BringWindowToTop(oswindow window)
{
   
   if(!::IsWindow(window))
      return FALSE;
   
   [[window->window() dd_invokeOnMainThreadAndWaitUntilDone:FALSE] orderFront: NSApp];
   
   [[window->window() dd_invokeOnMainThreadAndWaitUntilDone:FALSE] orderFrontRegardless];
   
   return TRUE;
   
}




const char * mm_keyboard_input_source()
{
   
   TISInputSourceRef source = TISCopyCurrentKeyboardInputSource();
   NSString *s = (__bridge NSString *)(TISGetInputSourceProperty(source, kTISPropertyInputSourceID));
   
   if(s == nil)
      return strdup("");
   
   return strdup([s UTF8String]);
}
