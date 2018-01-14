//
//  c_os_cross_win_user.cpp
//  c
//
//  Created by Snow Leopard User on 06/11/2011.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "framework.h"
//#include "ios_internal.h"




int ui_MessageBoxA(void * oswindow, const char * pszMessageParam, const char * pszHeaderParam, unsigned int uType );



int MessageBoxANative(oswindow hwnd, const char * message, const char * header, unsigned int message_type )
{
   
   string strMessage(message); // string "absorbs" NULL pointers into ""
   
   string strHeader(header); // string "absorbs" NULL pointers into ""
   
   return ui_MessageBoxA((void *) hwnd, strMessage, strHeader, message_type);
   
}






int MessageBoxW(oswindow hwnd, const unichar * message, const unichar * header, unsigned int message_type )
{
   
   string strMessage(message); // string "absorbs" wide strings into utf8
   
   string strHeader(header); // string "absorbs" wide strings into utf8
   
   return MessageBoxANative(hwnd, strMessage, strHeader, message_type);
   
}
