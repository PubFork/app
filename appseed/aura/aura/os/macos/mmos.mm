#include <CoreFoundation/CoreFoundation.h>


void macos_desktop_image_changed();


bool mm2_get_file_image(unsigned int * pcr, int cx, int cy, int iScan, const char * psz);


void ns_main_async(dispatch_block_t block)
{
   
   //   dispatch_block_t block = ^{
   //      // Code for the method goes here
   //   };
   //
   
   if ([NSThread isMainThread])
   {
      
      block();
      
   }
   else
   {
      
      dispatch_async(dispatch_get_main_queue(), block);
      
   }
   
}


void ns_main_sync(dispatch_block_t block)
{
   
   //   dispatch_block_t block = ^{
   //      // Code for the method goes here
   //   };
   //
   
   if ([NSThread isMainThread])
   {
      
      block();
      
   }
   else
   {
      
      dispatch_sync(dispatch_get_main_queue(), block);
      
   }
   
}


void main_async_runnable(runnable * prunnable)
{
   
   ns_main_async(^
                 {

                    prunnable->run();

                 });
   
   //[[mmos get] runRunnableOnMainThread: prunnable];
   
}


void main_synch_runnable(runnable * prunnable)
{
   
   ns_main_sync(^
                {

                   prunnable->run();

                });
   
   //[[mmos get] runRunnableOnMainThread: prunnable];
   
}


@implementation mmos


+ (id)get
{
   
   static mmos * s_mmos = NULL;
   
   if(s_mmos == NULL)
   {
      
      s_mmos = ([[self alloc] init]);
      
      s_mmos->theLock = [[NSRecursiveLock alloc] init];
      
      s_mmos->m_ppszWallpaper = NULL;
      
      s_mmos->m_llWallpaper = 0;
      
      s_mmos->m_iIcon = 0;
      
      [s_mmos monitorWallpaper];
      
      [s_mmos monitorIconForFile];
      
      [[s_mmos dd_invokeOnMainThreadAndWaitUntilDone: TRUE] deferWallpaper:NULL];
      
   }
   
   return s_mmos;
   
}


- (void)get_user_wallpaper:(void **)charpp forScreen:(NSScreen *) s;
{
   
   char ** ppsz = (char **) charpp;
   
   NSURL * purl = [[NSWorkspace sharedWorkspace] desktopImageURLForScreen:s];
   
   if(purl == NULL)
   {
      
      *ppsz = NULL;
      
   }
   else
   {
   
      *ppsz = strdup([[purl absoluteString] UTF8String]);
                     
   }
   
}


- (void)get_user_wallpaper:(void *)charppp getCount:(void *) llp
{

   long long * pll = (long long *) llp;

   NSArray<NSScreen *> * screenArray = [NSScreen screens];

   *pll = [screenArray count];
   
   char ** p = (char **) malloc(*pll * sizeof(char*));
   
   char *** ppsz = (char ***) charppp;
   
   *ppsz = p;

   for (int i = 0; i < *pll; i++)
   {
   
      NSScreen * screen = [screenArray objectAtIndex: i];
      
      [self get_user_wallpaper: (void **)&p[i] forScreen:screen];
   
   }
   
}


- (void)desktopImageChanged:(NSNotification *)notification
{
   
   macos_desktop_image_changed();
   
}


-(void)applicationActivity:(NSNotification *)notification
{
   
   NSRunningApplication *app = [[notification userInfo] objectForKey:@"NSWorkspaceApplicationKey"];
   
   if([app.localizedName isEqualToString:@"ScreenSaverEngine"])
   {
      
      macos_desktop_image_changed();
      
   }
   
}


-(void)monitorWallpaper
{
   
   NSRunLoop* myRunLoop = [NSRunLoop mainRunLoop];
   
   NSMethodSignature *sgn = [self methodSignatureForSelector:@selector(deferWallpaper:)];
   
   NSInvocation *inv = [NSInvocation invocationWithMethodSignature: sgn];
   
   [inv setTarget: self];
   
   [inv setSelector: @selector(deferWallpaper:)];
   
   NSTimer *t = [NSTimer timerWithTimeInterval: 0.1
                                    invocation:inv
                                       repeats:YES];
   
   [myRunLoop addTimer:t forMode:NSDefaultRunLoopMode];
   
}


-(void)runRunnableOnMainThread:(runnable *)prunnable
{
   
   [[self dd_invokeOnMainThread] runRunnable: prunnable];
   
}


-(void)runRunnable:(runnable *)prunnable
{
   
   prunnable->run();
   
}


-(void)deferWallpaper:(NSTimer *)timer
{
   
   char ** ppsz = NULL;
   
   long long ll;
   
   [self get_user_wallpaper: (void *) &ppsz getCount: (void *) &ll];
   
   [self->theLock lock];
   
   char ** ppszOld = self->m_ppszWallpaper;
   
   long long llOld = self->m_llWallpaper;
   
   if(ppsz != NULL)
   {
      
      self->m_ppszWallpaper = ppsz;
      
      self->m_llWallpaper = ll;
      
      for(long long i = 0; i < llOld; i++)
      {
         
         free(ppszOld[i]);
         
      }
      
      free(ppszOld);
      
   }

   [self->theLock unlock];
   
}


-(void)monitorIconForFile
{
   
   NSRunLoop* myRunLoop = [NSRunLoop mainRunLoop];
   
   NSMethodSignature *sgn = [self methodSignatureForSelector:@selector(deferIconForFile:)];

   NSInvocation *inv = [NSInvocation invocationWithMethodSignature: sgn];

   [inv setTarget: self];

   [inv setSelector:@selector(deferIconForFile:)];
   
   NSTimer *t = [NSTimer timerWithTimeInterval: 0.1 invocation:inv repeats:YES];
   
   [myRunLoop addTimer:t forMode:NSDefaultRunLoopMode];
   
}


-(void)deferIconForFile:(NSTimer *)timer
{

   if(self->m_iIcon != 1)
   {
      
      return;
      
   }
      
   if(self->m_pszIcon == NULL)
   {
      
      self->m_iIcon = 0;
      
      return;
      
   }
   
   mm2_get_file_image(self->m_picon, self->m_cxIcon, self->m_cyIcon, self->m_iScanIcon, self->m_pszIcon);
   
   self->m_iIcon = 0;
   
}


@end


bool mm1a_get_file_image(unsigned int * pcr, int cx, int cy, int iScan, const char * psz)
{
   
   mmos * os = [mmos get];
   
   if(os->m_iIcon == 0)
   {

      os->m_pszIcon = psz;

      os->m_picon = pcr;

      os->m_cxIcon = cx;

      os->m_cyIcon = cy;

      os->m_iScanIcon = iScan;

      os->m_iIcon = 1;

      while(os->m_iIcon != 0)
      {
         
         Sleep(5);
         
      }

   }
   
   return true;
      
}


void ns_set_this_process_binary_default_browser()
{
   
   CFBundleRef bundle = CFBundleGetMainBundle();
   
   CFURLRef url = CFBundleCopyBundleURL(bundle);
   
   LSRegisterURL(url, true);
   
   CFStringRef identifier = CFBundleGetIdentifier(bundle);
   
   LSSetDefaultHandlerForURLScheme(CFSTR("http"), identifier);
   
}


void ns_log(const char * pszLog)
{
 
   NSString * strLog = [[NSString alloc]initWithUTF8String:pszLog];
   
   NSLog(@"%@", strLog);
   
}



