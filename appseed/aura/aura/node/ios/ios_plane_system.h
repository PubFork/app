//
//  ios_plane_system.hpp
//  ios_aura
//
//  Created by Camilo Sasuke Tsumanuma on 03/10/17.
//

#pragma once

#ifdef __cplusplus

#ifdef __OBJC__

typedef UIWindow * ui_window_ptr;
typedef void * aura_system_ptr;

#else

typedef void * ui_window_ptr;
typedef ::aura::system * aura_system_ptr;

#endif


struct plane_system
{
   
   aura_system_ptr    m_psystem;
   
   plane_system(const char * pszId);
   
   ui_window_ptr init_part_2ex(CGRect rect);
   
   void begin();
   
};

#endif


