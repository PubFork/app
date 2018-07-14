//
//  round_window.cpp
//  os
//
//  Created by Camilo Sasuke Tsumanuma on 6/8/13.
//  Copyright (c) 2013 ca2 Desenvolvimento de Sofware Ltda. All rights reserved.
//
#import "ios_mm.h"
#import "aura/aura/node/ios/RoundWindowApp.h"


#import "aura/aura/os/apple/DDInvocationGrabber.h"
#import "aura/aura/os/apple/NSObject+DDExtensions.h"


#ifdef AURA_LANGUAGE

#error "AURA_LANGUAGE?!?!?!!!???"

#endif


#ifndef __MM

#error "MM?!?!?!!!???"

#endif

UIWindow * new_round_window(round_window * pwindow, CGRect rect)
{
   
   RoundWindow * proundwindow = [RoundWindow alloc];
   
   pwindow->m_proundwindow = proundwindow;
   
   pwindow->m_proundwindow->m_pwindow = pwindow;
  
   return [pwindow->m_proundwindow initWithFrame:[[UIScreen mainScreen] bounds]];

}


void round_window::round_window_show()
{
   
//   [[m_proun dd_invokeOnMainThread] showWindow : m_proundwindow];
   
}


void round_window::round_window_redraw()
{
   
   ns_main_thread(^{
      [m_proundwindow : display ];
   });
   
}


void round_window::round_window_invalidate()
{
   
   [[m_proundwindow dd_invokeOnMainThread] setNeedsDisplay];
   
}


void round_window::round_window_show_keyboard(bool bShow)
{
   
   dispatch_async(dispatch_get_main_queue(), ^{
      //this runs on the main thread.  Use theData
   if(bShow)
   {
    
      [m_proundwindow->m_controller->childContentView roundBecomeFirstResponder];
      
   }
   else
   {
      
      if(m_proundwindow->m_controller->childContentView.isFirstResponder)
      {
      
         [m_proundwindow->m_controller->childContentView resignFirstResponder];
         
      }
      
   }
   }
      );
   
}



//
//  round_window.cpp
//  os
//
//  Created by Camilo Sasuke Tsumanuma on 6/8/13.
//  Copyright (c) 2013 ca2 Desenvolvimento de Sofware Ltda. All rights reserved.
//
//#import "macos_mm.h"





void round_window::round_window_set_title(const char * pszTitle)
{
   
   NSString * str = [NSString stringWithUTF8String:pszTitle];
   
   [[m_proundwindow dd_invokeOnMainThreadAndWaitUntilDone:FALSE] setTitle: str];

   
}


void round_window::round_window_get_title(char * pszTitle, long iSize)
{
   
   NSString * str = [[m_proundwindow dd_invokeOnMainThreadAndWaitUntilDone:FALSE] title];

   strncpy(pszTitle, [str UTF8String], iSize);
   
}


void round_window::round_window_set_sel(long iBeg, long iEnd)
{
   
   UITextView * pview = m_proundwindow->m_controller->childContentView;
   
   UITextPosition * beg = [pview beginningOfDocument];
   
   UITextPosition * selbeg = [pview endOfDocument];
   
   UITextPosition * selend = selbeg;
   
   long iLen = (long) strlen([[pview text] UTF8String]);
   
   if(iBeg >= 0 && iBeg < iLen)
   {
   
      selbeg = [pview positionFromPosition: beg offset: iBeg];
      
   }
   
   if(iEnd >= 0 && iEnd < iLen)
   {
      
      selend = [pview positionFromPosition: beg offset: iEnd];
      
   }
   
   UITextRange * sel = [pview textRangeFromPosition: selbeg toPosition: selend];
   
   [pview setSelectedTextRange: sel];
   
}


void round_window::round_window_get_sel(long & iBeg, long & iEnd)
{
   
   UITextView * pview = m_proundwindow->m_controller->childContentView;
   
   UITextPosition * beg = [pview beginningOfDocument];
   
   UITextPosition * selbeg = [[pview selectedTextRange] start];
   
   UITextPosition * selend = [[pview selectedTextRange] start];
   
   iBeg = [pview offsetFromPosition: beg toPosition: selbeg];
   
   iEnd = [pview offsetFromPosition: beg toPosition: selend];
   
}


void round_window::round_window_set_text(const char * pszText)
{
   
   NSString * text = [[NSString alloc] initWithUTF8String:pszText];
   
   [m_proundwindow->m_controller->childContentView setText: text];
   
}

void round_window::round_window_get_text(char * pszText, long iSize)
{
   
   strncpy(pszText, [[m_proundwindow->m_controller->childContentView text] UTF8String], iSize);
   
}


long round_window::round_window_get_text_length()
{
   
   return strlen([[m_proundwindow->m_controller->childContentView text] UTF8String]);
   
}





void round_window::round_window_destroy()
{
   
   [[m_proundwindow dd_invokeOnMainThreadAndWaitUntilDone:TRUE] close];
   
}


//void round_window::round_window_show()
//{
//   
////   [[m_proundwindow->m_controller dd_invokeOnMainThreadAndWaitUntilDone:TRUE] showWindow : m_proundwindow];
//   
//}


void round_window::round_window_hide()
{
   
//   [[m_proundwindow dd_invokeOnMainThreadAndWaitUntilDone:TRUE] orderOut : m_proundwindow];
   
}

//void round_window::round_window_order_front()
//{
//   
//   [[m_proundwindow dd_invokeOnMainThreadAndWaitUntilDone:TRUE] orderFront : m_proundwindow];
//   
//}
//
//
//void round_window::round_window_make_key_window()
//{
//   
//   [[m_proundwindow dd_invokeOnMainThreadAndWaitUntilDone:TRUE] makeKeyWindow];
//   
//}


//void round_window::round_window_make_key_window_and_order_front()
//{
//   
//   [[m_proundwindow dd_invokeOnMainThreadAndWaitUntilDone:TRUE] makeKeyAndOrderFront: m_proundwindow];
//   
//}
//
//
//void round_window::round_window_make_main_window()
//{
//   
//   [[m_proundwindow dd_invokeOnMainThreadAndWaitUntilDone:TRUE] makeMainWindow];
//   
//}
//
//
//void round_window::round_window_redraw()
//{
//   
//   [[m_proundwindow dd_invokeOnMainThreadAndWaitUntilDone:TRUE] display ];
//   
//}
//
//
//void round_window::round_window_invalidate()
//{
//   
//   //   [[m_proundwindow->m_controller dd_invokeOnMainThread] setViewsNeedDisplay : TRUE];
//   
//}

