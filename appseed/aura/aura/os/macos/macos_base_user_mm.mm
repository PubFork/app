//
//  macos_user.mm
//  base
//
//  Created by Camilo Sasuke Tsumanuma on 2013-09-17.
//
//

#import "macos_user.h"
#include "aura/aura/os/os.h"
#include "aura/aura/os/os_os.h"


WINBOOL get_nswindow_rect(oswindow oswindow, LPRECT lprect);
void copy(LPRECT lprectDst, const CGRect & rectSrc);


bool oswindow_data::is_window_visible()
{
   
   return [window() isVisible];
   
}


bool oswindow_data::is_iconic()
{
   
   return [window() isMiniaturized] != FALSE;
   
}


bool oswindow_data::iconify()
{
   
   [window() miniaturize : 0];
   
   return 1;
   
}


bool oswindow_data::show_window(int32_t nCmdShow)
{

   if(nCmdShow == SW_HIDE)
   {
   
//   printf("\nhide window");
      
      ns_main_async(^
      {
         [m_nswindow orderOut : nil];
      });

   }
   else if(nCmdShow == SW_SHOWNOACTIVATE)
   {

      ns_main_async(^
                    {
                       [m_nswindow orderFront : nil];
                    });

   }
   else
   {
  //    printf("\nshow window");
//
      
      
      defer_dock_application(true);
      
      nsapp_activate_ignoring_other_apps(1);
      
      //[[m_nswindow dd_invokeOnMainThreadAndWaitUntilDone:TRUE ]showWindow: nil];

      ns_main_async(^
                    {
                       [m_nswindow makeKeyAndOrderFront : nil];
                    });

      
//      [[m_nswindow dd_invokeOnMainThreadAndWaitUntilDone:TRUE ]display];
      
   }
   
   return 1;
   
}


bool oswindow_data::client_to_screen(POINT *lppoint)
{
   RECT rect;
   get_nswindow_rect(this, &rect);
   lppoint->x += rect.left;
   lppoint->y += rect.top;
   return true;
}

bool oswindow_data::screen_to_client(POINT *lppoint)
{
   RECT rect;
   get_nswindow_rect(this, &rect);
   lppoint->x -= rect.left;
   lppoint->y -= rect.top;
   return true;
}


WINBOOL move_nswindow(oswindow hwnd, int x, int y);


WINBOOL set_nswindow_frame(oswindow hwnd, LPCRECT lpcrect, int iDisplay)
{
   
   NSRect rect;
   
   NSRect rectScreen = [[[NSScreen screens] objectAtIndex:0] frame];
   
   rect.origin.x     = lpcrect->left;
   rect.origin.y     = rectScreen.size.height   -     lpcrect->bottom;
   rect.size.width   = lpcrect->right           -     lpcrect->left;
   rect.size.height  = lpcrect->bottom          -     lpcrect->top;
   
   //rect.origin.x     = 500;
   //rect.origin.y     = 100;
   //rect.size.width   = 500;
   //rect.size.height  = 500;
   
   //printf("\nset nswindow frame (%f, %f)[%f, %f]", rect.origin.x, rect.origin.y, rect.size.width, rect.size.height);

   ns_main_async(^
              {
      
                 [hwnd->window() setFrame : rect display : iDisplay];
      
              });
   
   return 1;
   
}


WINBOOL move_nswindow(oswindow hwnd, int x, int y)
{
   
   NSPoint point;

   NSRect rectScreen = [[[NSScreen screens] objectAtIndex:0] frame];
   
   point.x = x;
   
   point.y = rectScreen.size.height - y;
   
//   printf("\nmove nswindow (%f, %f)", point.x, point.y);
   
   ns_main_async(^
              {
                        
                 [hwnd->window() setFrameTopLeftPoint : point];
      
              });
   
   return 1;
   
}


WINBOOL make_key_and_order_front_nswindow(oswindow hwnd)
{

//   printf("\nmake_key_and_order_front_nswindow");

   ns_main_async(^
   {
                        
      [hwnd->window() makeKeyAndOrderFront: nil];
      
   });
   
   return 1;
   
}


WINBOOL order_front_nswindow(oswindow hwnd)
{

   //   printf("\norder_front_nswindow");
   
   ns_main_async(^
              {
                        
                 [hwnd->window() orderFront: nil];
                 
              });
   
   return 1;
   
}


WINBOOL nswindow_set_level_main_menu(oswindow hwnd)
{
   
   ns_main_async(^
                 {
                    
                    [hwnd->window() setLevel: NSMainMenuWindowLevel];
                    
                 });
   
   return 1;
   
}


WINBOOL nswindow_set_level_floating(oswindow hwnd)
{
   
   ns_main_async(^
                 {
                    
                    [hwnd->window() setLevel: NSFloatingWindowLevel];
                    
                 });
   
   return 1;
   
}


WINBOOL nswindow_set_level_normal(oswindow hwnd)
{
   
   ns_main_async(^
                 {
                    
                    [hwnd->window() setLevel: NSNormalWindowLevel];
                    
                 });
   
   return 1;
   
}


WINBOOL nswindow_is_level_main_menu(oswindow hwnd)
{
   
   return hwnd->window().level == NSMainMenuWindowLevel;
   
}


WINBOOL nswindow_is_level_floating(oswindow hwnd)
{
   
   return hwnd->window().level == NSFloatingWindowLevel;
   
}


WINBOOL nswindow_is_level_normal(oswindow hwnd)
{
   
   return hwnd->window().level == NSNormalWindowLevel;
   
}



//CLASS_DECL_THREAD NSAutoreleasePool * g_ns_pool = NULL;
//
//
//
//
//NSAutoreleasePool * new_ns_pool()
//{
//   
//   NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];
//   
//   return pool;
//   
//}
//
//
//void release_pool(NSAutoreleasePool * pool)
//{
//   
//   [pool release];
//   
//}

void on_start_thread()
{
   
//   g_ns_pool = new_ns_pool();
   
}


void on_end_thread()
{
   
//   release_pool(g_ns_pool);
   
  // g_ns_pool = NULL;
   
}


void ns_redraw_window(oswindow w)
{
   
   [[w->window() dd_invokeOnMainThreadAndWaitUntilDone:TRUE] display];
   
}


WINBOOL get_nswindow_rect(oswindow oswindow, LPRECT lprect)
{
   
   NSRect rect = [oswindow->window() frame];
   
   lprect->left        = rect.origin.x;
   lprect->bottom      = [[NSScreen mainScreen] frame ].size.height - rect.origin.y;
   lprect->right       = rect.origin.x  + rect.size.width;
   lprect->top         = lprect->bottom - rect.size.height;
   
   return 1;
   
}




WINBOOL SetWindowPos(oswindow hwnd, oswindow hwndInsertAfter, int x, int y, int cx, int cy, UINT uFlags)
{
   
   bool  bMove = !(uFlags & SWP_NOMOVE);

   bool  bSize = !(uFlags & SWP_NOSIZE);
   
   if(bMove && bSize)
   {
      
      RECT rect;
      
      rect.left      = x;
      rect.top       = y;
      rect.right     = rect.left + cx;
      rect.bottom    = rect.top + cy;
      
      set_nswindow_frame(hwnd, &rect, (uFlags & SWP_SHOWWINDOW) != 0);
      
   }
   else if(bSize)
   {
      
      RECT rect;
      
      GetWindowRect(hwnd, &rect);
      
      rect.right     = rect.left + cx;
      rect.bottom    = rect.top + cy;
      
      set_nswindow_frame(hwnd, &rect, (uFlags & SWP_SHOWWINDOW) != 0);
      
   }
   else if(bMove)
   {
      
      move_nswindow(hwnd, x, y);
      
   }
   
   if(!(uFlags & SWP_NOZORDER))
   {
      
      int_ptr iInsertAfter = (int_ptr) hwndInsertAfter;
      
      if(iInsertAfter == ZORDER_TOPMOST)
      {
         
         if(nswindow_is_level_floating(hwnd))
         {
            
            order_front_nswindow(hwnd);
            
         }
         else
         {
         
            nswindow_set_level_floating(hwnd);
            
         }
         
      }
      else if(iInsertAfter == ZORDER_TOP)
      {
         
         nswindow_set_level_normal(hwnd);
         //order_front_nswindow(hwnd);
         
      }
      
   }
   
   return 1;
   
}



bool macos_set_user_wallpaper(int iScreen, const char * psz)
{

   NSArray<NSScreen *> * screenArray = [NSScreen screens];
   
   unsigned long screenCount = [screenArray count];
   
   if(iScreen < 0 || iScreen >= screenCount)
   {
      
      return false;
      
   }

   NSString * str = [NSString stringWithUTF8String: psz];
   
   NSString * path = str;
   
   NSURL * url = [NSURL fileURLWithPath: path];
   
/*   NSDictionary * options = [NSDictionary dictionaryWithObjectsAndKeys:nil, NSWorkspaceDesktopImageFillColorKey, [NSNumber numberWithBool:NO], NSWorkspaceDesktopImageAllowClippingKey, [NSNumber numberWithInteger:NSImageScaleProportionallyUpOrDown], NSWorkspaceDesktopImageScalingKey, nil]; */
   NSDictionary * options = [NSDictionary dictionaryWithObjectsAndKeys:
      [NSColor colorWithCalibratedRed:0.51 green:0.49 blue:0.89 alpha:1.0], NSWorkspaceDesktopImageFillColorKey,
                             [NSNumber numberWithBool:YES], NSWorkspaceDesktopImageAllowClippingKey, [NSNumber numberWithInteger:NSImageScaleProportionallyUpOrDown], NSWorkspaceDesktopImageScalingKey, nil];
   
   NSError * error;
   
   bool bOk = true;
   
      NSScreen * screen = [screenArray objectAtIndex: iScreen];
      
      NSURL * u = [[NSWorkspace sharedWorkspace] desktopImageURLForScreen: screen];
      
      NSLog(@"current wallpaper %s (screen=%d)", [[u absoluteString] UTF8String], iScreen);
      
      NSLog(@"gonna set to %s", [[url absoluteString] UTF8String]);
      
      error = NULL;
      
      [[[NSWorkspace sharedWorkspace] dd_invokeOnMainThreadAndWaitUntilDone:FALSE ] setDesktopImageURL:url forScreen: screen options:options error:&error];
      
      if(error != NULL)
      {
         
         bOk = false;
         
      }

   return bOk;
   
}


long long mm_get_user_wallpaper(long long llScreen, char ** ppsz);


long long mm_get_user_wallpaper(long long llScreen, char ** ppsz)
{
   
   mmos * p = [mmos get];
   
   [p->theLock lock];
   
   long long llCount = p->m_llWallpaper;

   if(llScreen < 0 || llScreen >= llCount || p->m_ppszWallpaper == NULL)
   {

      (*ppsz) = NULL;

   }
   else
   {
   
      (*ppsz) = strdup(p->m_ppszWallpaper[llScreen]);

   }
   
   [p->theLock unlock];
   
   return llCount;
                         
   
}





