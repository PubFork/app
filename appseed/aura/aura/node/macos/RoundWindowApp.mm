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

int32_t defer_run_system(char * * psza, int c);

void macos_on_app_activate();


@implementation RoundWindowApp


@synthesize windowcontroller;

- (void)applicationDidFinishLaunching:(NSNotification *)aNotification
{
   
   //MessageBox(NULL, "applicationDidFinishLaunching", "applicationDidFinishLaunching", MB_OK);
   
   defer_run_system();
   
}


- (BOOL)applicationShouldHandleReopen:(NSApplication *)sender hasVisibleWindows:(BOOL)flag
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



- (void)application:(NSApplication *)sender openFiles:(NSArray<NSString *> *)filenames
{
   
   unsigned long ulCount = [filenames count];
   
   if(ulCount <= 0)
   {
      
      return;
      
   }
   
   char ** psza = (char **) malloc(ulCount * sizeof(char*));
   
   for(unsigned long ul = 0; ul < ulCount; ul++)
   {
      
      char * psz = strdup([[filenames objectAtIndex:ul] UTF8String]);
      
      NSLog(@"XXXXX %s", psz);
      
      psza[ul] = psz;
      
   }
   
   defer_run_system(psza, (int) ulCount);
   
   
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
