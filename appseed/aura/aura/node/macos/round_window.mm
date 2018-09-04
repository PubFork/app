//
//  round_window.cpp
//  os
//
//  Created by Camilo Sasuke Tsumanuma on 6/8/13.
//  Copyright (c) 2013 ca2 Desenvolvimento de Sofware Ltda. All rights reserved.
//
#import "macos_mm.h"
#import "RoundWindow.h"


NSWindow * new_round_window(round_window * pwindow, CGRect rect)
{
   
   // rect.origin.x        = 0;
   
   rect.origin.y           = (int) [[NSScreen mainScreen]frame].size.height - (rect.origin.y + rect.size.height);
   
   // rect.size.width      = 0;
   // rect.size.height     = 0;
   
/* 
 
   rect.origin.x           = 100;
   rect.origin.y           = 100;
   rect.size.width         = 800;
   rect.size.height        = 500;
 
*/
   
   pwindow->m_proundwindow = [RoundWindow alloc];
   
   pwindow->m_proundwindow->m_pwindow = pwindow;
   
   return [[pwindow->m_proundwindow dd_invokeOnMainThreadAndWaitUntilDone: TRUE ] initWithContentRect : rect styleMask : 0 backing : NSBackingStoreBuffered defer : false ];
   
}


// void ns_app_close()
// {
   
//    [NSApp terminate:nil];
   
// }


round_window::round_window()
{
   
   
}
round_window::~round_window()
{
   
   
}



void round_window::round_window_set_title(const char * pszTitle)
{
   
   NSString * str = [NSString stringWithUTF8String:pszTitle];
   
   [m_proundwindow setTitle:str];
   
}


void round_window::round_window_get_title(char * pszTitle, int iSize)
{
   
   NSString * str = [m_proundwindow title];
   
   strncpy(pszTitle, [str UTF8String], iSize);
   
}


void round_window::round_window_destroy()
{
   
   if(m_proundwindow == NULL)
   {
      
      return;
      
   }
   
   [[NSNotificationCenter defaultCenter] removeObserver: m_proundwindow];

   [m_proundwindow setReleasedWhenClosed: YES];
   
   m_proundwindow->m_pwindow = NULL;
   
   ns_main_async(^
                 {
                    
                 [m_proundwindow close];

                 m_proundwindow = NULL;
                 
              });
   
}


void round_window::round_window_show()
{
   
   [[m_proundwindow->m_controller dd_invokeOnMainThreadAndWaitUntilDone:TRUE] showWindow : m_proundwindow];
                        
   [[m_proundwindow dd_invokeOnMainThreadAndWaitUntilDone:TRUE] windowDidExpose];
   
}


void round_window::round_window_hide()
{
    
   ns_main_async(^
              {
                 
                 [m_proundwindow orderOut : m_proundwindow];
                 
              });
   
}


void round_window::round_window_order_front()
{
   
   ns_main_async(^
              {
                 
                 [m_proundwindow orderFront : m_proundwindow];
                 
              });
   
}


void round_window::round_window_make_key_window()
{

   ns_main_async(^
              {
                 
                 [m_proundwindow makeKeyWindow];
                 
              });
   
}


void round_window::round_window_make_key_window_and_order_front()
{
   
   ns_main_async(^
              {
                 
                 [m_proundwindow makeKeyAndOrderFront: m_proundwindow];
                 
              });
   
}


void round_window::round_window_make_main_window()
{
   
   ns_main_async(^
              {
                 
                 [m_proundwindow makeMainWindow];
                 
              });
   
}


void round_window::round_window_redraw()
{

   ns_main_async(^
                 {
                    
                    [m_proundwindow display];
                    
                 });
   
}


void round_window::round_window_redraw_sync()
{
   
   ns_main_sync(^
                 {
                    
                    [m_proundwindow display];
                    
                 });
   
}



void round_window::round_window_invalidate()
{
   
   [[m_proundwindow->m_controller dd_invokeOnMainThread] setViewsNeedDisplay : TRUE];
   
}


bool nsapp_activation_policy_is_regular()
{
   
   if(NSApp.activationPolicy == NSApplicationActivationPolicyRegular)
   {
      
      return true;
      
   }
   
   return false;
   
}


bool nsapp_activation_policy_is_accessory()
{
   
   if(NSApp.activationPolicy == NSApplicationActivationPolicyAccessory)
   {
      
      return true;
      
   }
   
   return false;
   
}


void nsapp_activation_policy_regular()
{
      ns_main_async(^{
   [NSApp  setActivationPolicy:NSApplicationActivationPolicyRegular];
      });
   
}


void nsapp_activation_policy_accessory()
{
   ns_main_async(^{
      [NSApp setActivationPolicy:NSApplicationActivationPolicyAccessory];
       
       } );
   
}


void nsapp_activation_policy_prohibited()
{
     ns_main_async(^{
   [NSApp setActivationPolicy:NSApplicationActivationPolicyProhibited];
     });
   
}


void nsapp_activate_ignoring_other_apps(int i)
{
   
   ns_main_async(^{
   if(i)
   {
      
      [NSApp activateIgnoringOtherApps: YES];
      
   }
   else
   {
      
      [NSApp activateIgnoringOtherApps: NO];
      
   }
                 
                 });
   
}





NSWindow * get_os_window_ns_window(oswindow hwnd)
{
   return hwnd->m_nswindow;
   
}
