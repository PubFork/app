//
//  RoundWindowApp.m
//  axis
//
//  Created by Camilo Sasuke Tsumanuma on 27/09/14.
//
//

#import "macos_mm.h"
int file_put_contents_dup(const char * path, const char * contents);
void file_add_contents_raw(const char * path, const char * psz);
int32_t defer_run_system();
uint32_t __start_system_with_file(const char * pszFileName);
int32_t defer_run_system(const char * pszFileName);

int32_t defer_run_system(char * * psza, int c);

void macos_on_app_activate();



@implementation RoundWindowApp


@synthesize windowcontroller;

- (void)applicationWillFinishLaunching:(NSNotification *)notification
{
NSAppleEventManager *appleEventManager = [NSAppleEventManager sharedAppleEventManager];// 1
[appleEventManager setEventHandler:self andSelector:@selector(handleGetURLEvent:withReplyEvent:) forEventClass:kInternetEventClass andEventID:kAEGetURL];
   
}

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
   
   file_put_contents_dup("/eco/001.txt", "applicationOpenUntitledFile");
   //MessageBox(NULL, "applicationOpenUntitledFile", "applicationOpenUntitledFile", MB_OK);
   
   defer_run_system();
   
   //__start_system_with_file(NULL);
   
   return YES;
   
}



- (BOOL)application:(NSApplication *)sender openFile:(NSString *)filename
{
   
   file_put_contents_dup("/eco/002.txt", "applicationOpenFile");
   file_put_contents_dup("/eco/003.txt", [filename UTF8String]);

   //MessageBox(NULL, "application: openFile", "application: openFile", MB_OK);
   
   defer_run_system([filename UTF8String]);
   
   return true;
   
}



- (void)application:(NSApplication *)sender openFiles:(NSArray<NSString *> *)filenames
{
   
   file_put_contents_dup("/eco/004.txt", "openFiles");
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
      
      file_add_contents_raw("/eco/004.txt", psz);

      
      psza[ul] = psz;
      
   }
   
   defer_run_system(psza, (int) ulCount);
   
   
}
- (void)application:(NSApplication *)application open:(NSURL * )url
{
   file_put_contents_dup("/eco/006.txt", "open");
   file_add_contents_raw("/eco/006.txt", [[url absoluteString] UTF8String]);
   
   //MessageBox(NULL, "application: openFile", "application: openFile", MB_OK);
   
   defer_run_system([[url absoluteString] UTF8String]);
}

- (BOOL)application:(id)sender
  openFileWithoutUI:(NSString *)filename;
{
   file_put_contents_dup("/eco/007.txt", "openFileWithoutUI");
   file_add_contents_raw("/eco/007.txt", [filename UTF8String]);
   
   //MessageBox(NULL, "application: openFile", "application: openFile", MB_OK);
   
   defer_run_system([filename UTF8String]);
}

- (void)application:(NSApplication *)application openURLs:(NSArray<NSURL *> *)urls
{
   file_put_contents_dup("/eco/005.txt", "openURLs");
   unsigned long ulCount = [urls count];
   
   if(ulCount <= 0)
   {
      
      return;
      
   }
   
   char ** psza = (char **) malloc(ulCount * sizeof(char*));
   
   for(unsigned long ul = 0; ul < ulCount; ul++)
   {
      
      char * psz = strdup([[[urls objectAtIndex:ul] absoluteString] UTF8String]);
      
      NSLog(@"XXXXX %s", psz);
      
      file_add_contents_raw("/eco/005.txt", psz);
      
      
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
- (void)handleGetURLEvent:(NSAppleEventDescriptor *)event
           withReplyEvent:(NSAppleEventDescriptor *)replyEvent {
   
   // Extract the URL from the Apple event and handle it here.
   NSString* url = [[event paramDescriptorForKeyword:keyDirectObject] stringValue];
   NSLog(@"%@", url);
   
   file_put_contents_dup("/eco/008.txt", "handleGetURLEvent");
   file_add_contents_raw("/eco/008.txt", [url UTF8String]);
   
   //MessageBox(NULL, "application: openFile", "application: openFile", MB_OK);
   
   defer_run_system([url UTF8String]);
}
@end


void ns_application_main(int argc, char *argv[])
{
   
   NSApplication * application = [NSApplication sharedApplication];
   
   RoundWindowApp * appDelegate = [[RoundWindowApp alloc] init];
   
   [application setDelegate:appDelegate];
   
   [NSApplication sharedApplication];
   
   [NSApp setActivationPolicy:NSApplicationActivationPolicyRegular];
   
   id menubar = [NSMenu alloc];
   
   id appMenuItem = [NSMenuItem alloc];
   
   [menubar addItem:appMenuItem];
   
   [NSApp setMainMenu:menubar];
   
   id appMenu = [NSMenu alloc];
   
   id appName = [[NSProcessInfo processInfo] processName];
   
   id quitTitle = [@"Quit " stringByAppendingString:appName];
   
   id quitMenuItem = [[NSMenuItem alloc] initWithTitle:quitTitle
                                                action:@selector(terminate:) keyEquivalent:@"q"];
   
   [appMenu addItem:quitMenuItem];
   
   [appMenuItem setSubmenu:appMenu];
   
   [NSApp activateIgnoringOtherApps:YES];
   
   [NSApp run];
   
}
