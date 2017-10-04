//
//  ios_app.cpp
//  aura
//
//  Created by Camilo Sasuke Tsumanuma on 10/07/15.
//
//




ui_window_ptr new_round_window(plane_system * psystem, CGRect rect);




//
//  app_system.cpp
//  app
//
//  Created by Camilo Sasuke Tsumanuma on 12/05/14.
//  Copyright (c) 2014 Camilo Sasuke Tsumanuma. All rights reserved.
//








::base::system * create_base_system()
{
   
   ::aura::system * paurasystem = create_aura_system();
   
   if(paurasystem == NULL)
      return NULL;
      
   ::base::system * pbasesystem = dynamic_cast<::base::system *>(paurasystem);
   
   if(pbasesystem == NULL)
   {
      
      ::aura::del(paurasystem);
      
      return NULL;
      
   }
   
   return pbasesystem;
   
}


//
//ui_window_ptr init_part_2ex(plane_system * psystem, CGRect rect)
//{
//   
//   return psystem->init_part_2ex(rect);
//   
//}
//
//
//
//void system_begin_main(plane_system * psystem)
//{
//   
//   //psystem->begin();
//  
//}
//
//void plane_system::begin()
//{
//   
//   m_psystem->begin();
//   
//}
//
//
