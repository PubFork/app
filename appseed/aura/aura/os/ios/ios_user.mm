//
//  macos_user.mm
//  base
//
//  Created by Camilo Sasuke Tsumanuma on 2013-09-17.
//
//


WINBOOL get_nswindow_rect(oswindow oswindow, LPRECT lprect);




WINBOOL move_nswindow(oswindow hwnd, int x, int y)
{
   
//   RECT rect;
   
//   get_nswindow_rect(hwnd, &rect);
   
   CGPoint point;
   
   point.x = x;
   point.y = [[UIScreen mainScreen] applicationFrame].size.height - y;
   
//   [hwnd->window() setFrameTopLeftPoint : point];
   
   return 1;
   
   
}




void ns_redraw_window(oswindow w)
{
   
//   [w->window() display];
   
}

int ui_open_url(const char * pszUrl)
{
   
   NSString * strUrl = [NSString stringWithUTF8String:pszUrl];
   
   if(strUrl == NULL)
      return 0;
   
   NSURL * url = [NSURL URLWithString:strUrl];
   
   if(url == NULL)
   {
      
      //[strUrl release];
      
      return 0;
      
   }
   
  // [strUrl release];
   
   BOOL b = [[UIApplication sharedApplication] openURL:url];   
   
//   [url release];

   return b ? 1 : 0;

}


CGRect g_rectWorkspace;


void mm_init_workspace_rect()
{
   
   g_rectWorkspace = [[UIScreen mainScreen] frame];
   
}


CGRect mm_get_workspace_rect()
{
   
   return g_rectWorkspace;
   
}
