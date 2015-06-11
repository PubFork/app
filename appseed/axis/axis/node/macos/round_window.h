//
//  round_window.h
//  os
//
//  Created by Camilo Sasuke Tsumanuma on 6/8/13.
//  Copyright (c) 2013 ca2 Desenvolvimento de Sofware Ltda. All rights reserved.
//

#pragma once


#include "app/appseed/axis/user/user/user_key_enum.h"


class round_window
{
public:


bool m_bDirty;
   
#ifdef __OBJC__
   RoundWindow * m_proundwindow;
#else
   void * m_proundwindow;
#endif
   
   
   virtual void round_window_draw(CGContextRef cgc) = 0;
   virtual void round_window_mouse_down(double x, double y) = 0;
   virtual void round_window_mouse_up(double x, double y) = 0;
   virtual void round_window_mouse_moved(double x, double y) = 0;
   virtual void round_window_mouse_dragged(double x, double y) = 0;
   virtual bool round_window_key_down(unsigned int uiKeyCode) = 0;
   virtual bool round_window_key_up(unsigned int uiKeyCode) = 0;
   
   
   virtual void round_window_invalidate();
   virtual void round_window_show();
   virtual void round_window_hide();
   virtual void round_window_redraw();
   
   virtual void round_window_order_front();
   virtual void round_window_make_key_window();
   virtual void round_window_make_key_window_and_order_front();
   virtual void round_window_make_main_window();
   
   virtual void round_window_close();
   
   
};


void ns_shared_application();
NSWindow * new_round_window(round_window * pwindow, CGRect rect);
void ns_app_run();
void ui_app_run(int argc, char * argv[]);


