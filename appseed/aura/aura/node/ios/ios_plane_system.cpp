//
//  ios_plane_system.cpp
//  ios_aura
//
//  Created by Camilo Sasuke Tsumanuma on 03/10/17.
//

#include "framework.h"



//ui_window_ptr new_round_window(plane_system * psystem, CGRect rect);




//
//  app_system.cpp
//  app
//
//  Created by Camilo Sasuke Tsumanuma on 12/05/14.
//  Copyright (c) 2014 Camilo Sasuke Tsumanuma. All rights reserved.
//


plane_system * new_system(const char * pszId)
{
   
   on_init_thread();
   
   return new ::plane_system(pszId);
   
}


//::base::system * create_base_system()
//{
//   
//   ::aura::system * paurasystem = create_aura_system();
//   
//   if(paurasystem == NULL)
//      return NULL;
//   
//   ::base::system * pbasesystem = dynamic_cast<::base::system *>(paurasystem);
//   
//   if(pbasesystem == NULL)
//   {
//      
//      ::aura::del(paurasystem);
//      
//      return NULL;
//      
//   }
//   
//   return pbasesystem;
//   
//}


plane_system::plane_system(const char * pszId)
{
   
   m_psystem = create_aura_system();
   
   m_psystem->m_pplanesystem = this;
   
   m_psystem->initialize_native_window1();
   
   ::command::command * pinitmaindata  = new ::command::command;
   
   pinitmaindata->m_strCommandLine        = pszId;
   
   m_psystem->startup_command(pinitmaindata);
   
}


ui_window_ptr init_part_2ex(plane_system * psystem, CGRect rect)
{
   
   return psystem->init_part_2ex(rect);
   
}


ui_window_ptr plane_system::init_part_2ex(CGRect rect)
{
   
   //m_psystem->m_window = ios_start_window(this, rect);
   
   //int nReturnCode = 0;
   
   manual_reset_event ev(m_psystem);
   
   m_psystem->m_peventReady = &ev;
   
   if(!m_psystem->begin_synch())
      return NULL;
   
   ev.wait();
   
   ::rect r;
   
   r.left = rect.origin.x;
   r.top = rect.origin.y;
   r.right = r.left + rect.size.width;
   r.bottom = r.top + rect.size.height;
   
   ui_window_ptr pwindow = m_psystem->initialize_native_window2(r);
   
   //::user::native_window_initialize initialize;
   
   //initialize.pwindow = this;
   //initialize.window = m_window.Get();
   
   //m_psystem->m_posdata->m_pui->initialize(&initialize);
   
   //m_psystem->m_ptwf = create_twf_2ex();
   
   //m_psystem->m_ptwf->twf_start();
   
   stringa straLibrary = m_psystem->handler()->m_varTopicQuery["app"].stra();
   
   for(int i = 0; i < m_psystem->handler()->m_varTopicQuery["app"].array_get_count(); i++)
   {
      string strApp = m_psystem->handler()->m_varTopicQuery["app"].at(i);
   }
   
   straLibrary.replace("\\", "_");
   straLibrary.replace("-", "_");
   
   for(int i = 0; i < straLibrary.get_count(); i++)
   {
      string strLibrary = straLibrary[i];
      strsize iFind = strLibrary.find("/");
      if(iFind >= 0)
         strLibrary = strLibrary.Left(iFind) + '_' + strLibrary.Mid(iFind + 1);
      iFind = strLibrary.find("/", iFind + 1);
      if(iFind >= 0)
         strLibrary.Truncate(iFind);
      m_psystem->m_mapAppLibrary[m_psystem->handler()->m_varTopicQuery["app"][i]] = strLibrary;
   }
   
   for(int i = 0; i < m_psystem->handler()->m_varTopicQuery["app"].get_count(); i++)
   {
      string strApp = m_psystem->handler()->m_varTopicQuery["app"][i];
   }
   
   m_psystem->m_mapAppLibrary["app/ca2/cube"] = "ca2";
   m_psystem->m_mapAppLibrary["app/ca2/bergedge"] = "ca2";
   
   return pwindow;
}


void system_begin_main(plane_system * psystem)
{
   
   //psystem->begin();
   
}

void plane_system::begin()
{
   
   m_psystem->begin();
   
}



