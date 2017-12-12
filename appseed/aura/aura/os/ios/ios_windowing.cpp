//
//  ios_windowing.cpp
//  ios_aura
//
//  Created by Camilo Sasuke Tsumanuma on 10/12/17.
//
#include "framework.h"


::user::interaction * get_system_window_interaction(::aura::system::os_system_window * psystemwindow)
{
   
   if(psystemwindow == NULL)
   {
      
      return NULL;
      
   }
   
   return psystemwindow->m_pui;
   
}
