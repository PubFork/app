//
//  user_create_struct.cpp
//  aura
//
//  Created by Camilo Sasuke Tsumanuma on 19/06/18.
//

#include "framework.h"

namespace user
{
 
   
   create_struct::create_struct(u32 uiExStyle, const char * pszClassName, const char * pszWindowName, u32 uiStyle, ::rect rect, LPVOID pvCreateParams) :
   create_struct(rect)
   {
      
      dwExStyle = uiExStyle;
      lpszClass = pszClassName;
      lpszName = pszWindowName;
      style = uiStyle;
      lpCreateParams = pvCreateParams;
      
   }

   create_struct::create_struct(LPCRECT lpcrect)
   {
      
      ZEROP(this);
      
      set_rect(lpcrect);
      
   }

   
   void create_struct::set_rect(LPCRECT lpcrect)
   {
   
      x = lpcrect->left;
      y = lpcrect->top;
      cx = ::width(lpcrect);
      cy = ::height(lpcrect);
      
   }

   void create_struct::get_rect(LPRECT lprect)
   {
      
      lprect->left = x;
      lprect->top = y;
      lprect->right = x + cx;
      lprect->bottom = y + cy;
      
   }

   
} // namespace user



