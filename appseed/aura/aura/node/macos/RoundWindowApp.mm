//
//  RoundWindowApp.m
//  axis
//
//  Created by Camilo Sasuke Tsumanuma on 27/09/14.
//
//

#import "macos_mm.h"

int32_t defer_run_system();

int32_t defer_run_system(const char * pszFileName);

void macos_on_app_activate();


@implementation RoundWindowApp


- (void)applicationDidFinishLaunching:(NSNotification *)aNotification
{
   
   //MessageBox(NULL, "applicationDidFinishLaunching", "applicationDidFinishLaunching", MB_OK);
   
   defer_run_system();
   
}


- (BOOL)applicationShouldHandleReopen:(NSApplication *)sender
                    hasVisibleWindows:(BOOL)flag
{
   
   //MessageBox(NULL, "applicationShouldHandleReopen", "applicationShouldHandleReopen", MB_OK);
   
   macos_on_app_activate();

   return YES;
   
}


- (BOOL)applicationOpenUntitledFile:(NSApplication *)sender
{
   
   //MessageBox(NULL, "applicationOpenUntitledFile", "applicationOpenUntitledFile", MB_OK);
   
   defer_run_system();
   
   return YES;
   
}


- (BOOL)application:(NSApplication *)sender openFile:(NSString *)filename
{
   
   //MessageBox(NULL, "application: openFile", "application: openFile", MB_OK);
   
   defer_run_system([filename UTF8String]);
   
   return true;
   
}


//- (void)sendEvent:(NSEvent *)theEvent
//{
//
//   /*
//   
//   char szEvent[128];
//   
//   ZERO(szEvent);
//   
//   if([theEvent type] == NSLeftMouseDown)
//   {
//   
//      strcpy(szEvent, "NSLeftMouseDown");
//      
//   }
//   else if([theEvent type] == NSLeftMouseUp)
//   {
//     
//      strcpy(szEvent, "NSLeftMouseUp");
//      
//   }
//   
//   if(strlen(szEvent) > 0)
//   {
//   
//      char szEventCopy[128];
//   
//      strcpy(szEventCopy, szEvent);
//      
//      printf("\n%s", szEventCopy);
//      
//   }
//   
//   */
//   
//   [super sendEvent:theEvent];
//   
//}



@end
